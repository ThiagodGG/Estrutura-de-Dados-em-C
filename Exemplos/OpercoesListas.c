#include <stdio.h>
#include <stdlib.h>

struct No {
    int dado;
    struct No* proximo;
};

void inserirNoInicio(struct No** inicio, int valor) {
    struct No* novoNo = (struct No*) malloc(sizeof(struct No));
    novoNo -> dado = valor;
    novoNo -> proximo = *inicio;
    *inicio = novoNo;

void removerDoInicio (struct No** inicio){
    if (*inicio == NULL){
        struct No* temp = *inicio;
        *inicio = (*inicio) -> proximo;
        free((temp));
    }
}






return 0;
}