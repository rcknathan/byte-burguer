// Funções que manipulam os dados das comandas

#include <stdio.h>
#include <stdlib.h>

#ifndef CARDAPIO_DATA_C
#define CARDAPIO_DATA_C
#include "cardapio_data.h"
#endif

// Estrutura de uma comanda
struct comanda {
    int idComanda;
    char nomeCliente[100];
    float valorComanda;
    Item* listaPedidos;

    struct comanda* proximaComanda;
};

typedef struct comanda Comanda;

Comanda *listaComandas, *comandaRemovida = NULL;
FILE *comandasDB;

// Função que adiciona uma comanda à lista de comandas
void adicionarComanda(Comanda **lista, int id, char *nome) {
    Comanda *ponteiroAuxiliar, *novaComanda = malloc(sizeof(Comanda));

    novaComanda -> idComanda = id;
    strcpy(novaComanda -> nomeCliente, nome);
    novaComanda -> proximaComanda = NULL;

    if(*lista == NULL) { // Se a lista está vazia...
        *lista = novaComanda; // ...A lista recebe o novo item
    }
    else {
        ponteiroAuxiliar = *lista;
        while(ponteiroAuxiliar -> proximaComanda != NULL) { // Enquanto o ponteiro para o próximo item não for nulo...
            ponteiroAuxiliar = ponteiroAuxiliar -> proximaComanda; // ...O ponteiro auxiliar recebe o próximo item
        }
        ponteiroAuxiliar -> proximaComanda = novaComanda; // O próximo item recebe o novo item quando o while não é mais atendido
    }
}

// Função que solicita ao usuário as informações a serem inseridas na comanda
void input_adicionarComanda() {
    system("cls");

    int id;
    char nome[100];

    comandasDB = fopen("../DataBase/comandasDB.txt", "a");

    printf("ID Do Cliente: ");
    scanf("%d", &id);
    fprintf(comandasDB, "%d ", id);

    printf("Nome Do Cliente: ");
    fflush(stdin);
    gets(nome);
    fprintf(comandasDB, "%s\n", nome);

    fclose(comandasDB);

    adicionarComanda(&listaComandas, id, nome);
}

// Função que remove uma comanda da lista de comandas
Comanda* removerComanda(Comanda **lista, int id) {
    Comanda *ponteiroAuxiliar, *removerComanda = NULL;

    if(*lista != NULL) {
        if((*lista) -> idComanda == id) {
            removerComanda = *lista;
            *lista = removerComanda -> proximaComanda;
        }
        else {
            ponteiroAuxiliar = *lista;
            while (ponteiroAuxiliar -> proximaComanda && ponteiroAuxiliar -> proximaComanda -> idComanda != id) {
                ponteiroAuxiliar = ponteiroAuxiliar -> proximaComanda;
            }
            if(ponteiroAuxiliar -> proximaComanda != NULL) {
                removerComanda = ponteiroAuxiliar -> proximaComanda;
                ponteiroAuxiliar -> proximaComanda = removerComanda -> proximaComanda;
            }
        }
    }
    return removerComanda;
}

void excluirRegistroComandas(int id) {
    FILE *arquivoOriginal;
    FILE *arquivoModificado;
    Comanda comanda;

    arquivoOriginal = fopen("../DataBase/comandasDB.txt", "r");
    arquivoModificado = fopen("../DataBase/arquivoTemporarioComandas.txt", "w");

    while (fgets(comanda.nomeCliente, sizeof(comanda.nomeCliente), arquivoOriginal) != NULL) {
        sscanf(comanda.nomeCliente, "%d %s", &(comanda.idComanda), comanda.nomeCliente);
        if (comanda.idComanda != id) {
            fprintf(arquivoModificado, "%d %s\n", comanda.idComanda, comanda.nomeCliente);
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoModificado);
    remove("../DataBase/comandasDB.txt");
    rename("../DataBase/arquivoTemporarioComandas.txt", "../DataBase/comandasDB.txt");
}

// Função que solicita ao usuário o ID da comanda a ser removida
void input_removerComanda() {
    system("cls");

    int id;

    printf("Digite O ID Da Comanda A Ser Removida: ");
    scanf("%d", &id);

    comandaRemovida = removerComanda(&listaComandas, id);
    excluirRegistroComandas(id);

    if(comandaRemovida != NULL) {
        system("cls");
        printf("A comanda de %s foi removida com sucesso!", comandaRemovida -> nomeCliente);
        free(comandaRemovida);
    } else {
        system("cls");
        printf("Comanda não encontrada!");
    }
    Sleep(2000);
}

// Função que busca um item na lista de produtos
Item* buscarItem(Item* lista, int id) {
    Item* buscador = lista;
    while (buscador != NULL) {
        if (buscador -> idProduto == id) {
            return buscador;
        }
        buscador = buscador -> proximoItem;
    }
    return NULL;
}

// Função que busca uma comanda na lista de comandas
Comanda* buscarComanda(Comanda* lista, int id) {
    Comanda* buscador = lista;
    while (buscador != NULL) {
        if (buscador -> idComanda == id) {
            return buscador;
        }
        buscador = buscador -> proximaComanda;
    }
    return NULL;
}

// Função que adiciona pedidos à uma determinada comanda
void adicionarPedidos(Comanda* comanda, Item* item) {
    adicionarProduto(&(comanda -> listaPedidos), item -> idProduto, item -> nomeProduto, item -> valorProduto);

    comanda -> valorComanda += item -> valorProduto;
}

// Função que pede ao usuário a comanda e o produto que vai ser inserido à comanda selecionada
void input_adicionarPedidos() {
    system("cls");

    int idComanda;
    int idProduto;
    Comanda* comanda;
    Item* item;

    printf("ID Da Comanda Para Inserir Pedido: ");
    scanf("%d", &idComanda);

    printf("ID Do Produto A Ser Inserido: ");
    scanf("%d", &idProduto);

    comanda = buscarComanda(listaComandas, idComanda);
    item = buscarItem(listaProdutos, idProduto);

    if(comanda == NULL || item == NULL) {
        system("cls");
        printf("ID da comanda e/ou produto inválidos!");
        Sleep(2000);
        navegar_Comandas();
    } else {
        adicionarPedidos(comanda, item);
    }
}

// Função que imprime as comandas
void imprimirComandas(Comanda *comanda) {
    system("cls");

    printf("------------------------Comandas---------------------------\n\n");

    while(comanda != NULL) {
        printf("%d | %s\n\n   Pedidos:\n", comanda -> idComanda, comanda -> nomeCliente);

        Item *pedido = comanda -> listaPedidos;

        while(pedido != NULL) {
            printf("    - %s\n", pedido -> nomeProduto);
            pedido = pedido -> proximoItem;
        }
        printf("\n   Valor Total Do Pedido: R$ %.2f\n", comanda -> valorComanda);
        printf("-----------------------------------------------------------\n\n");
        comanda = comanda -> proximaComanda;
    }
    printf("\n\n");

    printf("Pressione qualquer tecla para voltar...");
    getch();
}

//Função que define uma comanda como paga (Envia o valor da comanda ao caixa e a remove)
void comandaPaga() {
    system("cls");

    int idComanda;
    double valorComanda = 0;
    Comanda* comanda;

    printf("ID da Comanda a ser marcada como paga: ");
    scanf("%d", &idComanda);

    comanda = buscarComanda(listaComandas, idComanda);

    if (comanda != NULL) {
        valorComanda = comanda->valorComanda;

        // Adicionar o valor da comanda ao valorTotal do caixa
        valorTotal += valorComanda;

        // Remove a comanda paga da lista de comandas
        comandaRemovida = removerComanda(&listaComandas, idComanda);
        excluirRegistroComandas(idComanda);

        if(comandaRemovida != NULL) {
            system("cls");
            printf("A comanda de %s foi paga com sucesso!", comandaRemovida -> nomeCliente);
            free(comandaRemovida);
        }
    } else {
        system("cls");
        printf("Comanda não encontrada! ID inválido!");
        Sleep(2000);
        navegar_Comandas();
    }
    Sleep(2000);
}

// Função que faz a leitura dos itens das comandas no arquivo ao iniciar o programa e joga na estrutura
void lerComandas() {
    int id;
    char nome[100];

    comandasDB = fopen("../DataBase/comandasDB.txt", "r");

    while(!feof(comandasDB)) {
        while(fscanf(comandasDB, "%d %s", &id, nome) == 2) {
            adicionarComanda(&listaComandas, id, nome);
        }
    }
    fclose(comandasDB);
}