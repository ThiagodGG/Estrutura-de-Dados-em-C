#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 10


// --- FUNÇÕES (PROTOTIPOS) ---

// Funcoes para gerar as listas
void gerarListaOrdenada(int lista[], int n);
void gerarListaInversa(int lista[], int n);
void gerarListaAleatoria(int lista[], int n);

// Funcoes de ordenacao
void bubblesort(int lista[], int n);
void inserctionsort(int lista[], int n);
void selectionsort(int lista[], int n);

// Funcoes auxiliares
void imprimirlista(const char* titulo, const int lista[], int n);
void copiarlista(int destino[], const int origem[], int n);

// --- FUNCAO PRINCIPAL (main) ---
int main(){

//  Gerador de numeros aleatorios
srand(time(NULL));

// Ddecclaracao das listas
int listaOrdenada[TAMANHO];
int listaInversa[TAMANHO];
int listaAleatoria[TAMANHO];

// Preenche as listas com os padroes desejados
printf("--- GERANDO LISTAS DE ENTRADA ---\n");
gerarListaOrdenada(listaOrdenada, TAMANHO);
gerarListaInversa(listaInversa, TAMANHO);
gerarListaAleatoria(listaAleatoria, TAMANHO);
printf("------------------------------------------\n\n");

// Declara a lista temmporaria (temp)
int listaTemp[TAMANHO];

// ==================================================
// 1. TESTANDO O BUBBLE SORT
// ==================================================
printf("============ 1. BUBBLE SORT ===============\n");

//a) Melhor caso (lista ordenada)
copiarlista(listaTemp, listaOrdenada, TAMANHO);
bubblesort(listaTemp, TAMANHO);
imprimirlista("Bubble Sort | Melhor Caso (ja ordenada)", listaTemp, TAMANHO);

//b) Pior caso (lista em ordem inversa)
copiarlista(listaTemp, listaInversa, TAMANHO);
bubblesort(listaTemp, TAMANHO);
imprimirlista("Bubble Sort | Pior Caso (ordem inversa)", listaTemp, TAMANHO);

//c) Caso medio (lista aleatoria)
copiarlista(listaTemp, listaAleatoria, TAMANHO);
bubblesort(listaTemp, TAMANHO);
imprimirlista("Bubble Sort | Caso Medio (aleatoria)", listaTemp, TAMANHO);
printf("\n");


// ======================================================
// 2. TESTANDO O INSERCTION SORT
// ======================================================
printf("=============== 2. INSERCTION SORT ================\n");

//a) Melhor caso (lista ordenada)
copiarlista(listaTemp, listaOrdenada, TAMANHO);
inserctionsort(listaTemp, TAMANHO);
imprimirlista("Inserction Sort | Melhor Caso (ja ordenada)", listaTemp, TAMANHO);

//b) Pior caso (lista inversa)
copiarlista(listaTemp, listaInversa, TAMANHO);
inserctionsort(listaTemp, TAMANHO);
imprimirlista("Inserction Sort | Pior Caso (ordem inversa)", listaTemp, TAMANHO);

//c) Caso medio (lista aleatoria)
copiarlista(listaTemp, listaAleatoria, TAMANHO);
inserctionsort(listaTemp, TAMANHO);
imprimirlista("Inserction Sort | Caso Medio (aleatoria)", listaTemp, TAMANHO);
printf("\n");

// =========================================================
// 3. TESTANDO O SELECTION SORT
// =========================================================
printf("============== 3. SELECTION SORT ==============\n");

//a) Melhor caso (lista ordenada)
copiarlista(listaTemp, listaOrdenada, TAMANHO);
selectionsort(listaTemp, TAMANHO);
imprimirlista("Selection Sort | Melhor Caso (ja ordenada)", listaTemp, TAMANHO);

//b) Pior caso (lista inversa)
copiarlista(listaTemp, listaInversa, TAMANHO);
selectionsort(listaTemp, TAMANHO);
imprimirlista("Selection Sort | Pior Caso (ordem inversa)", listaTemp, TAMANHO);

//c) Caso medio (lista aleatoria)
copiarlista(listaTemp, listaAleatoria, TAMANHO);
selectionsort(listaTemp, TAMANHO);
imprimirlista("Selection Sort | Caso Medio (aleatoria)", listaTemp, TAMANHO);
printf("\n");

    return 0; // Fim do programa
}


// ----- IMPLEMENTAÇAO DAS FUNCOES DE ORENAÇAO

/**
* @brief Ordena uma lista usando o algoritimo bubble sort
* @details Logica: Comapara pares de elementos adjacentes e os troca se estiverem
*            na ordem errada. Repete esse processo até que a lista esteja ordenada.
*            Elementos maiores "borbulham" para o final da lista.
*            - Melhor caso: Com a otimização, faz apenas uma passagem.
*            - Pior Caso: lista em ordem inversa
*
*/
void bubblesort(int lista[], int n){
    int i, j, temp;
    int trocou;

    // Numero de passagens pela lista (laço externo)
    for (i = 0; i < n - 1; i++){
        trocou = 0;

        // Comparação de elementos adjacentes (laço interno)
        for (j = 0; j < n - i - 1; j++){

            if (lista[j] > lista[j + 1]){

                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
                trocou = 1;

            }
        }

        // OTIMIZAÇÃO caso nenhuma troca for feita o algoritmo é parado
        if (trocou == 0){
            break;
        }
    }
}

/**
* @brief Ordena uma lista usando o algoritimo inserction sort
* @details Logica: percorre a lista, pega os elemnetos e os insere na posição correta
*
*/

void inserctionsort(int lista[], int n){
    int i, chave, j;

    // Começa do segundo elemento (indice 1)
    for (i = 1; i < n; i++){
        // chave sera inserida
        chave = lista[i];
        // j aponta para o ultimo elemento 
        j = i - 1;

        // Movimento dos elementos da parte ordenada
        while (j >= 0 && lista[j] > chave){
            lista[j + 1] = lista[j];
            j = j - 1;
        }

        // Inserção da chave na posiçao correta
        lista[j + 1] = chave;
    }
}

/**
 * @brief Ordena uma lista usando o algoriitimo slection sort
 * @details Logica: Divide a lista em duas partes e faz a troca entre os elementos dessas duas partes
 * 
 */

 void selectionsort(int lista[], int n){
    int i, j, indice_min, temp;

    // Fronteiras entre parte ordenada e não ordenada
    for (i = 0; i < n - 1; i++){
        indice_min = i;

        // Percorre a parte não ordenada em busca do menor elemento
        for (j = i + 1; j < n; j++){
            if (lista[j] < lista[indice_min]){
                //...atualiza o indice minimo
                indice_min = j;
            }
        }

        // Se o menor elemento não for o primeiro encontrado
        // Troca os de lugar
        if (indice_min != i){
            temp = lista[i];
            lista[i] = lista[indice_min];
            lista[indice_min] = temp;
        }
    }
}

// --- IMPLEMENTAÇÃO DAS FUNCOES AUXILIARES ---

/**
 * @brief Gera uma lista de 'n' elementos em ordem crescente.
 */

void gerarListaOrdenada(int lista[], int n){
    for (int i = 0; i < n; i++){
        lista[i] = i + 1;
    } 
    imprimirlista("Original - Ordenada", lista, n);
}

/**
 * @brief Gera uma lista de 'n' elementos em ordem decrescente
 */

void gerarListaInversa(int lista[], int n){
    for (int i = 0; i < n; i++){
        lista[i] = n - i;
    }
    imprimirlista("Original - Inversa", lista, n);
}

/**
 * @brief Gera uma lista de 'n' elementos aleatorios de 1 ao 100
 */

 void gerarListaAleatoria(int lista[], int n){
    for (int i = 0; i < n; i++){
        lista[i] = rand() % 100 + 1; // Gera numeros entre 1 e 100
    }
    imprimirlista("Original - Aleatoria", lista, n);
 }
