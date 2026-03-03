#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ---- DECLARAÇO DAS FUNÇÕES (PROTOTIPOS) ----

// 1. Busca sequencial
int buscaSequencialIterativa(const char* lista[], int tamanho, const char* item);
int buscaSequencialRecursiva(const char* lista[], int tamanho, const char* item);
int buscaSequencialrecursiva_aux(const char* lista[], int tamanho, const char* item, int indice);

// 2. Busca binaria
int buscaBinariaIterativa(const char* lista[], int tamanho, const char* item);
int buscaBinariaRecursiva(const char* lista[], int tamanho, const char* item);
int buscaBinariaRecursiva_aux(const char* lista[], const char* item, int inicio, int fim);

// função_aux para imprimir resultados de forma organizada
void imprimirResultado(const char* nomeDaBusca, const char* item, int resultado);


// --- FUNÇÃO PRINCIPAL (main) ---

int main(){

// Para a busca binaria funcionar os itens devem estar organizados alfabeticamente.

const char* listaDeCompras[] = {
    "arroz",
    "batata",
    "cebola",
    "detergente",
    "feijao",
    "leite",
    "macarrao",
    "oelo",
    "sal",
    "tomate"
};

// Calcula o numero de itens na lista de compras
// siizeof(listaDeCompras) -> tamanho total do array em bytes
// sizeof(listaDeCompras[0]) -> tamanho de um elemento (um ponteiro char*) em bytes
// Divisão molda o numero de elementos.

int tamanhoDaLista = sizeof(listaDeCompras) / sizeof(listaDeCompras[0]);

// itens a buscar para demonstrar os algoritmos
const char* itemExistente = "leite";
const char* itemInexistente = "queijo";

printf("--- DEMONSTRAÇÃO DE ALGORITMOS DE BUSCA EM LISTA DE TEXTO ---\n");
printf("Lista utlizada: [arroz, batata, cebola, detergente, feijao, leite, macarrao, oleo, sal, tomate]");
printf("-----------------------------------------------------------------------------------------------\n\n");

// testando a busca sequencial
printf("--- 1. BUSCA SEQUENCIAL ---\n");

// a) versão iterativa
int res1 = buscaSequencialIterativa(listaDeCompras, tamanhoDaLista, itemExistente);
imprimirResultado("Sequencial Iterativa", itemExistente, res1);


int res2 = buscaSequencialIterativa(listaDeCompras, tamanhoDaLista, itemInexistente);
imprimirResultado("Sequencial Iterativa", itemInexistente, res2);
printf("\n");

// b) versão recursiva
int res3 = buscaSequencialRecursiva(listaDeCompras, tamanhoDaLista, itemExistente);
ImprimirResultado("Sequencial Recursiva", itemExistente, res3);

int res4 = buscaSequencialRecursiva(listaDeCompras, tamanhoDaLista, itemInexistente);
imprimirResultado("Sequencial Recursiva", itemInexistente, res4);
printf("----------------------------------------------------------------------------\n\n");


// testando a busca Binaria
printf("--- 2. BUSCA BINARIA (requer lista ordenada) ---\n");
// a) versão iterativa
int res5 = buscaBinariaIterativa(listaDeCompras, tamanhoDaLista, itemExistente);
imprimirResultado("Binaria iterativa", itemExistente, res5);

int res6 = buscaBinariaIterativa(listaDeCompras, tamanhoDaLista, itemInexistente);
imprimirresultado("Binaria iterativa", itemInexistente, res6);
printf("\n");

// b) versão recursiva
int res7 = buscaBinariaRecursiva(listaDeCompras, tamanhoDaLista, itemExistente);
imprimirResultado("Binaria Recursiva", itemExistente, res7);

int res8 = buscaBinariaRecursiva(listaDeCompras, tamanhoDaLista, ItemInexistente);
imprimirResultado("Binaria Recursiva", itemInexistente, res8);
printf("-----------------------------------------------------------------------\n");



    return 0; // Programa finalizado com sucesso
}

// IMPLEMENTAÇÃO DAS FUNÇÕES

// 1. BUSCA SEQUENCIAL


/**
 * @brief Busca sequencial usando um laço (iteração).
 * @param lista O array de strings onde a busca será feita.
 * @param tamanho O numero de elementos na lista
 * @param item A string que esta sendo procurada
 * @return O indice do item se encontrado, ou -1 caso contrario.
 */

int buscaSequencialIterativa(const char* lista[], int tamanho, const char* item){
    // Um laço 'for' percorre cada indice da lista, de  0 até 'tamanho -1'. 
}









