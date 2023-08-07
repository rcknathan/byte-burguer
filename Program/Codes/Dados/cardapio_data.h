// Fun??es que manipulamos dados do card?pio

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// Estrutura de um produto
struct item {
    int idProduto;
    char nomeProduto[100];
    float valorProduto;

    struct item *proximoItem;
};

typedef struct item Item;

Item *listaProdutos, *produtoRemovido = NULL;
FILE *cardapioDB;

// Fun??o que adiciona o produto ? lista encadeada
void adicionarProduto(Item **lista, int id, char *nome, float valor) {
    Item *ponteiroAuxiliar, *novoItem = malloc(sizeof(Item));

    novoItem -> idProduto = id;
    strcpy(novoItem -> nomeProduto, nome);
    novoItem -> valorProduto = valor;
    novoItem -> proximoItem = NULL;

    if(*lista == NULL) { // Se a lista est? vazia...
        *lista = novoItem; // ...A lista recebe o novo item
    }
    else {
        ponteiroAuxiliar = *lista;
        while(ponteiroAuxiliar -> proximoItem != NULL) { // Enquanto o ponteiro para o pr?ximo item n?o for nulo...
            ponteiroAuxiliar = ponteiroAuxiliar -> proximoItem; // ...O ponteiro auxiliar recebe o pr?ximo item
        }
        ponteiroAuxiliar -> proximoItem = novoItem; // O pr?ximo item recebe o novo item quando o while n?o ? mais atendido
    }
}

// Fun??o que pede ao usu?rio as informa??es a serem inseridas na lista encadeada
void input_adicionarProduto() {
    system("cls");

    int id;
    char nome[100];
    float valor;

    cardapioDB = fopen("../DataBase/cardapioDB.txt", "a");

    printf("ID Do Produto: ");
    scanf("%d", &id);
    fprintf(cardapioDB, "%d ", id);

    printf("Nome Do Produto: ");
    fflush(stdin);
    gets(nome);
    fprintf(cardapioDB, "%s ", nome);

    printf("Preço Do Produto: ");
    scanf("%f", &valor);
    fprintf(cardapioDB, "%.2f\n", valor);

    fclose(cardapioDB);

    adicionarProduto(&listaProdutos, id, nome, valor);
}

// Fun??o que remove um produto da lista encadeada atrav?s do ID
Item* removerProduto(Item **lista, int id) {
    Item *ponteiroAuxiliar, *removerItem = NULL;

    if(*lista != NULL) {
        if((*lista) -> idProduto == id) {
            removerItem = *lista;
            *lista = removerItem -> proximoItem;
        }
        else {
            ponteiroAuxiliar = *lista;
            while (ponteiroAuxiliar -> proximoItem && ponteiroAuxiliar -> proximoItem -> idProduto != id) {
                ponteiroAuxiliar = ponteiroAuxiliar->proximoItem;
            }
            if(ponteiroAuxiliar -> proximoItem != NULL) {
                removerItem = ponteiroAuxiliar -> proximoItem;
                ponteiroAuxiliar -> proximoItem = removerItem -> proximoItem;
            }
        }
    }
    return removerItem;
}

void excluirRegistroProdutos(int id) {
    FILE *arquivoOriginal;
    FILE *arquivoModificado;
    Item produto;

    arquivoOriginal = fopen("../DataBase/cardapioDB.txt", "r");
    arquivoModificado = fopen("../DataBase/arquivoTemporarioProdutos.txt", "w");

    while (fgets(produto.nomeProduto, sizeof(produto.nomeProduto), arquivoOriginal) != NULL) {
        sscanf(produto.nomeProduto, "%d %s %f", &(produto.idProduto), produto.nomeProduto, &(produto.valorProduto));
        if (produto.idProduto != id) {
            fprintf(arquivoModificado, "%d %s %.2f\n", produto.idProduto, produto.nomeProduto, produto.valorProduto);
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoModificado);
    remove("../DataBase/cardapioDB.txt");
    rename("../DataBase/arquivoTemporarioProdutos.txt", "../DataBase/cardapioDB.txt");
}

// Fun??o que pede ao usu?rio o ID do produto a ser removido da lista encadeada
void input_removerProduto() {
    system("cls");

    int id;

    printf("ID Do Produto A Ser Removido: ");
    scanf("%d", &id);

    produtoRemovido = removerProduto(&listaProdutos, id);
    excluirRegistroProdutos(id);

    if(produtoRemovido != NULL) {
        system("cls");
        printf("O produto '%s' foi removido com sucesso!", produtoRemovido -> nomeProduto);
        free(produtoRemovido);
    } else {
        system("cls");
        printf("Produto não encontrado!");
    }
    Sleep(2000);
}

// Fun??o que imprime o card?pio, ou seja, cada elemento da lista
void imprimirCardapio(Item *item) {
    system("cls");

    printf("------------------------Cardápio---------------------------\n\n");

    while(item != NULL) {
        printf("%d | %s .............................. R$ %.2f\n", item -> idProduto, item -> nomeProduto, item -> valorProduto);
        item = item -> proximoItem;
    }
    printf("\n\n");

    printf("Pressione qualquer tecla para voltar...");
    getch();
}

// Fun??o que faz a leitura dos itens do card?pio no arquivo ao iniciar o programa e joga na estrutura
void lerCardapio() {
    int id;
    char nome[100];
    float valor;

    cardapioDB = fopen("../DataBase/cardapioDB.txt", "r");

    while(!feof(cardapioDB)) {
        while(fscanf(cardapioDB, "%d %s %f", &id, nome, &valor) == 3) {
            adicionarProduto(&listaProdutos, id, nome, valor);
        }
    }
    fclose(cardapioDB);
}