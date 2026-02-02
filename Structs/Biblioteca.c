// ================================================================= //
// SISTEMA DE BIBLIOTECA //

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strcspn()

// Constantes //
#define MAX_LIVROS 50
#define TAM_STRING 100

// Definição da estrutura (Struct)
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
};

// Função para limpar o buffer de entrada
void limparbuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// Função principal //
int main(){
    struct Livro biblioteca [MAX_LIVROS];
    int totalLivros = 0;
    int opcao;

// Laço principal
// Exibe o menu de opções
do {

printf("========================================\n");
printf("      BIBLIOTECA 1\n");
printf("========================================\n");
printf("1 - Cadastrar novo livro\n");
printf("2 - Listar todos os livros\n");
printf("3 - Sair\n");
printf("----------------------------------------\n");
printf("Escolha uma opção: ");

// Lê a opção do usuario
scanf("%d", &opcao);
limparbuffer(); //Limpa o \n do scanf. 


// Processamento de opções
switch (opcao){
    case 1: //Cadastro de livro
        printf("--- Cadastro de novo livro ---\n\n");

        if (totalLivros < MAX_LIVROS) {
            printf("Digite o nome do livro: ");
            fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);

            printf("Digite o autor: ");
            fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);

            printf("Digite a editora: ");
            fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);

            biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';
            biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';
            biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0';

            printf("Digite a edição: ");
            scanf("%d", &biblioteca[totalLivros].edicao);
            limparbuffer();

            totalLivros++;

            printf("\nLivro cadastrado com sucesso!\n");
        } else {
            printf("Biblioteca cheia! Não é possivel mais cadastrar livros.\n");
        }

        printf("\nPressione Enter para continuar...");
        getchar(); //Pausa para o usuario ler a mensagem antes de voltar pro menu.
        break;

    case 2: //Listagem de livros
        printf("--- Lista de Livros Cadastrados ---\n");

        if (totalLivros == 0){
            printf("Nenhum livro cadastrado ainda.\n");
        } else {
            for (int i = 0; i < totalLivros; i++){
                printf("----------------------------------------\n");
                printf("Livro: %d\n", i + 1);
                printf("Nome: %s\n", biblioteca[i].nome);
                printf("Autor: %s\n", biblioteca[i].autor);
                printf("Editora: %s\n", biblioteca[i].editora);
                printf("Edição %d\n", biblioteca[i].edicao);
            }
                printf("-------------------------------------------\n");
            }

            // Pausa para que o usuario veja a lista antes de limpar a tela
            printf("\nPressione Enter para continuar...");
            getchar();
            break;

        case 3: //Sair
            printf("\nSaindo do sistema...\n");
            break;

         default: //Opção invalida
            printf("\nOpção invalida! Tente novamente.\n");
            printf("\nPressione enter para continuar...");
            getchar();
            break;
        }
    } while (opcao != 0);
    return 0; // fim do programa
}
