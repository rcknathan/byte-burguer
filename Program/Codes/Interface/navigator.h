// Funções que navegam entre as interfaces
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#ifndef INTERFACE_H
#define INTERFACE_H
#include "interface.h"
#endif

#ifndef COMANDAS_DATA_C
#define COMANDAS_DATA_C
#include "../Dados/comandas_data.h"
#endif

// Variável controladora da navegação entre menus
char escolha;

// Protótipos das funções de navegação
void navegar_Cardapio();
void navegar_Comandas();
void navegar_Caixa();

// Protótipos das funções de apresentação
void apresentar_Erro();

// Função que navega no Menu Principal
void navegar_Menu() {
    system("cls");
    menu_UI();

    escolha = getch();

    switch(escolha) {
        case '1': // Opção "Cardápio"
            navegar_Cardapio();
            break;
        case '2': // Opção "Comandas"
            navegar_Comandas();
            break;
        case '3': // Opção "Caixa"
            navegar_Caixa();
            break;
        case '4': // Opção "Sair"
            system("cls");
            exit(0);
            break;
        default: // Opção Inválida
            apresentar_Erro();
            navegar_Menu();
    }
}

// Função que navega no submenu "Cardápio"
void navegar_Cardapio() {
    system("cls");
    cardapio_UI();

    escolha = getch();

    switch(escolha) {
        case '1': // Opção "Visualizar Cardápio"
            imprimirCardapio(listaProdutos);
            navegar_Cardapio();
            break;
        case '2': // Opção "Adicionar Produto"
            input_adicionarProduto();
            navegar_Cardapio();
            break;
        case '3': // Opção "Remover Produto"
            input_removerProduto();
            navegar_Cardapio();
            break;
        case '4': // Opção "Voltar"
            navegar_Menu();
            break;
        default: // Opção Inválida
            apresentar_Erro();
            navegar_Cardapio();
    }
}

// Função que navega no submenu "Comandas"
void navegar_Comandas() {
    system("cls");
    comandas_UI();

    escolha = getch();

    switch(escolha) {
        case '1': // Opção "Visualizar Comandas"
            imprimirComandas(listaComandas);
            navegar_Comandas();
            break;
        case '2': // Opção "Adicionar Comanda"
            input_adicionarComanda();
            navegar_Comandas();
            break;
        case '3': // Opção "Remover Comanda"  
            input_removerComanda();
            navegar_Comandas();  
            break;
        case '4': // Opção "Inserir Novo Pedido"    
            input_adicionarPedidos();
            navegar_Comandas();
            break;
        case '5': // Opção "Definir Comanda Paga"
            comandaPaga();
            navegar_Comandas();
            break;
        case '6': // Opção "Voltar"
            navegar_Menu();
            break;
        default: // Opção Inválida
            apresentar_Erro();
            navegar_Comandas();
    }
}

// Função que navega no submenu "Caixa"
void navegar_Caixa() {
    system("cls");        
    caixa_UI();

    escolha = getch();

    switch(escolha) {
        case '1': // Opção "Descontar Gastos"
            system("cls");
            descontar_Gastos();
            break;
        case '2': // Opção "Adicionar Extra"
            system("cls");
            adicionar_Extra();
            break;
        case '3': // Opção "Voltar"
            navegar_Menu();
            break;
        default: // Opção Inválida
            apresentar_Erro();
            navegar_Caixa();
    }
}

// Função que apresenta uma mensagem de erro se a opção for inválida
void apresentar_Erro() {
    system("cls");
    erro_UI();
    Sleep(1000);
}