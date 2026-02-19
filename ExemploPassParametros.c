#include <stdio.h>


// (ponteiro para int)
void dobrar(int* x){
    *x = (*x) * 2;
}

int main(){
    int numero = 5;
    printf("Valor de numero antes: %d\n", numero);
    dobrar(&numero); 
    printf("Valor de numero depois: %d\n", numero);
    return 0;
}