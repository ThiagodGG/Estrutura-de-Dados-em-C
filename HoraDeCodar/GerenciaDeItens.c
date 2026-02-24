#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Biblioteca para manipulação de strings

//Constantes gobais
#define MAX_STR_LEN 50 // Tamanho máximo para strings



//------------------------------------------------------------------------------------------------------
// LISTA ESTATICA PT1
#define TAM_MAX 10 // Tamanho da lista

//Estrutura que representa a lista estatica
typedef struct {
    char dados[TAM_MAX][MAX_STR_LEN]; // Matriz para armazenar os itens 10 linhas (itens) e 50 colunas (caracteres por item)
    int quantidade; //Contador de controle, informa quantos itens estão armazenados na lista
} ListaEstatica;

//Funções da lista estatica

void inicializarListaEstatica(ListaEstatica *lista);

void inserirListaEstatica(ListaEstatica *lista, const char* texto);
void removerListaEstatica(ListaEstatica *lista, const char* texto);
void listarListaestatica(const ListaEstatica *lista);

//------------------------------------------------------------------------------------------------------
// LISTA ENCADEADA PT2

typedef struct No {
    char* dado;             // ponteiro para string (alocada dinamicamente)
    struct No *proximo;
} No;


// Atalho para o tipo de lista encadeada, que é um ponteiro para o nó inicial da lista
typedef No* ListaEncadeada;


//Funções da lista encadeada
void inicializarListaEncadeada(ListaEncadeada *lista);

void inserirListaEncadeada(ListaEncadeada *lista, const char* texto);
void removerListaEncadeada(ListaEncadeada *lista, const char* texto);
void listarListaEncadeada(const ListaEncadeada *lista);
void liberarListaEncadeada(ListaEncadeada *lista); // Função para liberar a memória alocada pela lista encadeada


//------------------------------------------------------------------------------------------------------
// FUNÇÃO PRINCIPAL (main) e MENUS
//------------------------------------------------------------------------------------------------------

void menuListaEstatica();
void menuListaEncadeada();

int main(){
    int opcao;
    do {
        printf("\n------ MANIPULAÇÃO DE LISTAS (TEXTO) ------\n");
        printf("1. Lista Estática\n");
        printf("2. Lista Encadeada\n");
        printf("0. Sair do programa\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                menuListaEstatica();
                break;
            case 2:
                menuListaEncadeada();
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}


// IMPLEMENTAÇÃO DAS FUNÇÕES DE MANIPULAÇÃO DE LISTAS (ESTÁTICA E ENCADEADA) AQUI
// LISTA ESTATICA
void inicializarListaEstatica(ListaEstatica *lista){
    lista->quantidade = 0;
}

void inserirListaEstatica(ListaEstatica *lista, const char* texto){
    // Primeiro verifica se a lista ja atingiu o limite maximo TAM_MAX
    // Se sim a lista esta cheia a função retorna
    if(lista->quantidade == TAM_MAX){
        printf("A lista está cheia! Não é possível inserir mais itens.\n");
        return;
    }
    // A inserção ocorre na primeira linha livre da matriz
    strcpy(lista->dados[lista->quantidade], texto);
    lista->quantidade++; // Incrementa o contador de itens
    printf("Texto \"%s\" inserido com sucesso.\n", texto);
}

void removerListaEstatica(ListaEstatica *lista, const char* texto){
    int i, pos = -1;
    
    for (i = 0; i < lista->quantidade; i++){
      if (strcmp(lista->dados[i], texto) == 0){
        pos = i;
        break;
      }  
    }


    // Tratamento de erro
    if (pos == -1){
        printf("Erro: Texto \"%s\" não encontrado na lista.\n");
        return;
    }

    for (i = pos; i < lista->quantidade - 1; i++){
        strcpy(lista->dados[i], lista->dados[i + 1]);
    }

    //Atualização do contador
    lista->quantidade--;
    printf("Texto \"%s\" removido com sucesso.\n", texto);
}

void listarListaEstatica(const ListaEstatica *lista){
    if (lista->quantidade == 0){
        printf("A lista estatica está vazia.\n");
        return;
    }
    printf("Itens da Lista Estatica:[ ");
    for (int i = 0; i < lista->quantidade; i++){
        printf("\"%s\" ", lista->dados[i]); //usar %s para imprimir strings
    }
    printf("]\n");
}

// LISTA ENCADEADA
void inicializarListaEncadeada(ListaEncadeada *lista){
    *lista = NULL;
}

void inserirListaEncadeada(ListaEncadeada *lista, const char* texto){
    // Alocação de memoria para o novo nó
    No *novoNo = (No*) malloc(sizeof(No));

    if (novoNo == NULL){
        printf("Erro: Falha na alocação de memoria para o novo nó.\n");
        return;
    }

    // Alocação de memoria para a string do nó
    novoNo-> dado = (char*) malloc(strlen(texto) + 1);

    if (novoNo->dado == NULL){
        printf("Erro: Falha na alocação de memoria pra o texto.\n");
        free(novoNo); // Libera o nó alocado anteriormente
        return;
    }

    strcpy(novoNo->dado, texto); // Copia o texto para o campo dado do nó
    novoNo->proximo = *lista;
    *lista = novoNo;

    printf("Texto \"%s\" inserido com sucesso.\n", texto);
}


void removerListaEncadeada(ListaEncadeada *lista, const char* texto){
    No *atual = *lista;
    No *anterior = NULL;

    while (atual != NULL && strcmp(atual->dado, texto) != 0){
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL){
        printf("Erro: Texto \"%s\" não encontrado na lista. \n", texto);
        return;
    }

    if (anterior == NULL){
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual->dado);
    free(atual);
    printf("Texto \"%s\" removido com sucesso.\n", texto);
}

void listarListaEncadeada(const ListaEncadeada *lista){
    No *temp = *lista;
    if (temp == NULL){
        printf("A lista encadeada está vazia.\n");
        return;
    }
    printf("Itens da lista Encadeada: [ ");
    while (temp != NULL){
        printf("\"%s\" ", temp->dado); //Usar %s para imprimir
        temp = temp->proximo;
    }
    printf("]\n");

}

int opcao; // Variável global para armazenar a opção escolhida no menu

void menuListaEstatica(){
    printf("\n------ MENU LISTA ESTÁTICA ------\n");
    printf("1. Inserir item na lista estática\n");
    printf("2. Remover item da lista estática\n");
    printf("3. Listar itens da lista estática\n");
    scanf("%d", &opcao);
}

void menuListaEncadeada(){
    printf("\n------ MENU LISTA ENCADEADA ------\n");
    printf("1. Inserir item na lista encadeada\n");
    printf("2. Remover item da lista encadeada\n");
    printf("3. Listar itens da lista encadeada\n");
    scanf("%d", &opcao);
}


//Funções para liberar memoria
void liberarListaEncadeada(ListaEncadeada *lista){
    No *atual = *lista;
    No *proximo;
    while (atual != NULL){
        proximo = atual->proximo;
        free(atual->dado); // Libera a string
        free(atual); // Libera o nó
        atual = proximo;

    }
}
