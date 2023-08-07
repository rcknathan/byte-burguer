// Controla os dados da opção "Caixa"

#include <stdio.h>

double valorTotal = 0;

// Função Para Retirar Valor Do Caixa
double descontar_Gastos() {
    double subtrair;

    printf("Valor a ser descontado: ");
    scanf("%lf", &subtrair);

    valorTotal -= subtrair;

    system("cls");
    caixa_UI();
    navegar_Caixa();

    return valorTotal;
}

// Função Para Adicionar Valor Ao Caixa
double adicionar_Extra() {
    double somar;

    printf("Valor a ser adicionado: ");
    scanf("%lf", &somar);

    valorTotal += somar;

    system("cls");
    caixa_UI();
    navegar_Caixa();

    return valorTotal;
}