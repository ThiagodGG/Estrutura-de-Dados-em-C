#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ---- DECLARAÇO DAS FUNÇÕES (PROTOTIPOS) ----

// 1. Busca sequencial
int buscaSequencialIterativa(const char* lista[], int tamanho, const char* item);
int buscaSequencialRecursiva(const char* lista[], int tamanho, const char* item);
int buscaSequencialRecursiva_aux(const char* lista[], int tamanho, const char* item, int indice);

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
imprimirResultado("Sequencial Recursiva", itemExistente, res3);

int res4 = buscaSequencialRecursiva(listaDeCompras, tamanhoDaLista, itemInexistente);
imprimirResultado("Sequencial Recursiva", itemInexistente, res4);
printf("----------------------------------------------------------------------------\n\n");


// testando a busca Binaria
printf("--- 2. BUSCA BINARIA (requer lista ordenada) ---\n");
// a) versão iterativa
int res5 = buscaBinariaIterativa(listaDeCompras, tamanhoDaLista, itemExistente);
imprimirResultado("Binaria iterativa", itemExistente, res5);

int res6 = buscaBinariaIterativa(listaDeCompras, tamanhoDaLista, itemInexistente);
imprimirResultado("Binaria iterativa", itemInexistente, res6);
printf("\n");

// b) versão recursiva
int res7 = buscaBinariaRecursiva(listaDeCompras, tamanhoDaLista, itemExistente);
imprimirResultado("Binaria Recursiva", itemExistente, res7);

int res8 = buscaBinariaRecursiva(listaDeCompras, tamanhoDaLista, itemInexistente);
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
    for (int i = 0; i < tamanho; i++){
        // Strcmp(str 1, str2) compara duas strings
        // Retorna o indice atual
        if (strcmp(lista[i], item) == 0){
            // Se as strings forem iguais, encontramos o item!
            return i;
        }
    }
    // Se o laço 'for' terminar e não tivermos retornado nada,
    // significa que o ittem nãoo está na lista 
    return -1;
}

/**
 * @brief Fução "involucro" para a buca sequencial recursiva.
 *        Ela esconde a busca a partir do indice 0
 */
int buscaSequencialRecursiva(const char* lista[], int tamanho, const char* item){
    return buscaSequencialRecursiva_aux(lista, tamanho, item, 0);
}

int buscaSequencialRecursiva_aux(const char *lista[], int tamanho, const char *item, int indice)
{
    return 0;
}

/**
 * @brief Função auxiliar que implemnta a forma recursiva
 * @param indice O indice do elemento atual a ser verificado
 * @return O indice do item se encontrado, ou -1 caso contrario
 */
int buscaSequencialRecursiva__aux(const char* lista[], int tamanho, const char* item, int indice){
    // PASSO 1: FALHA NA BUSCA
    if (indice >= tamanho){
        return -1; // Item não encontrado.
    }

    // PASSO 2: SUCESSO NA BUSCA
    if (strcmp(lista[indice], item) == 0){
        return indice;
    }
    //  PASSO RECURSIVO
        return buscaSequencialRecursiva_aux(lista, tamanho, item, indice + 1);
}

// 2. BUSCA BINARIA

/**
 * @brief Busca binaria usando um laço
 * @return o indice do item se encontrando, -1 caso contrario.
 */
int buscaBinariaIterativa(const char* lista[], int tamanho, const char* item){
    int inicio = 0;
    int fim = tamanho - 1;
    int meio;

    while (inicio <= fim){

        // Calcula o indice do meio
        meio = inicio + (fim - inicio) / 2;

        // Compara a string do meio com o item procurado.
        int comparacao = strcmp(lista[meio], item);

        if (comparacao == 0){ // Encontrado
            return meio;
        }
        else if (comparacao > 0){
            fim = meio - 1;
        }
        else {
            inicio = meio + 1;
        }
    }

    // Se o while retornar o inicio passou o fim
    // se o espaço de busca esgotou o item não foi encontrado
    return -1;
}

int buscaBinariaRecursiva(const char *lista[], int tamanho, const char *item){
    return 0;
}


   


/**
 * @brief Função "involucro" para a busca binaria recursiva.
 */
int buscaBinariaRecurisva(const char* lista[], int tamanho, const char* item){
    // Inicia a busca recursiva em toda a lista, do indice 0 até 'tamanho - 1'.
    return buscaBinariaRecursiva_aux(lista, item, 0, tamanho - 1);
} 

/**
 * @brief Função Auxiliar que implementa a logica reecursiva da busca binaria.
 * @param inicio O indice inicial da sub-lista atual.
 * @param fim O indice final da sub-lista atual
 * @return O indice do item se encontrado, ou -1 caso contrario
 */
int buscaBinariaRecursiva_aux(const char* lista[], const char* item, int inicio, int fim){
    // CASO 1: FALHA NA BUSCA
    if (inicio > fim){
        return -1;
    }

    // PASSO RECURSIVO E BASE DE SUCESSO
    int meio = inicio + (fim - inicio) / 2;
    int comparacao = strcmp(lista[meio], item);

    if(comparacao == 0){
        // CASO 2: SUCESSO NA BUSCA
        return meio;
    }
    else if (comparacao > 0){
        return buscaBinariaRecursiva_aux(lista, item, meio + 1, fim);
    }
}

// FUNÇÃO DE IMPRESSÃO

/**
 * @brief Formata e imprime o resultado de uma busca 
 * @param nomeDaBusca O nome do algoritimo utilizado
 * @param item O item que foi procurado 
 * @param resultado O resultado da busca
 */
void imprimirResultado(const char* nomeDaBusca, const char* item, int  resultado){
    printf("[%s] Buscando por \"%s\"...\n", nomeDaBusca, item);
    if (resultado != 1){
        printf("    -> Resultado: Item encontrado no indice %d.\n", resultado);
    } else {
        printf("    -> Resultado: Item não encontrado na lista.\n");
    }
}
