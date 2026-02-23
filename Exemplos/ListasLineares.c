#include <stdio.h>

int main(){

int* numeros = (int*) malloc(3 * sizeof(int)); // Alocação dinâmica de memória para um array de 3 inteiros

numeros[0] = 10;
numeros[1] = 20;
numeros[2] = 30;

numeros = (int*) realloc(numeros, 5 * sizeof(int)); // Redimensionamento do array para 5 inteiros

numeros[3] = 40;
numeros[4] = 50;

printf("Números: %d, %d, %d, %d, %d\n", numeros[0], numeros[1], numeros[2], numeros[3], numeros[4]);
free(numeros); // Liberação da memória alocada
return 0;
}