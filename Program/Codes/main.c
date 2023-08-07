// Função principal rodando o programa

#include <stdio.h>
#include <locale.h>
#include <windows.h>

#ifndef NAVIGATOR_H
#define NAVIGATOR_H
#include "Interface/navigator.h"
#endif

int main() {
    setlocale(LC_ALL, "Portuguese");

    lerCardapio();
    lerComandas();
    navegar_Menu();

    return 0;
}