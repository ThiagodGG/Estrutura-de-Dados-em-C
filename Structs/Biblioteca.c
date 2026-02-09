// ================================================================= //
// SISTEMA DE BIBLIOTECA //

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strcspn()

// Constantes //
#define MAX_LIVROS 50
#define TAM_STRING 100
#define MAX_EMPRESTIMOS 100

// Definição da estrutura (Struct)
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel; // 1 para sim e 0 para não.
};

// Nova struct para armazenar infos sobre emprestimo
struct Emprestimo {
    int indiceLivro; // Para saber qual livro do array "biblioteca" foi emprestado
    char nomeusuario[TAM_STRING];
};

// Função para limpar o buffer de entrada
void limparbuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
};

// Função principal //
// Agora utilizando ponteiros e alocação dinamica de memoria
int main(){
    struct Livro *biblioteca;
    struct Emprestimo *emprestimos;

// Usando calloc para o array de livros, iniciando com a memoria zerada 
biblioteca = (struct Livro *) calloc(MAX_LIVROS, sizeof(struct Livro));

// Usando malloc para o array de emprestimos
emprestimos = (struct Emprestimo *) malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));

// Verificação para saber se a alocação deu certo
if (biblioteca == NULL || emprestimos == NULL) {
    printf("Erro: Falha ao alocar memoria.\n");
    return 1; // retorna 1 para indicar erro.
}

int totalLivros = 0;
int totalEmprestimos = 0;
int opcao;

// Laço principal
// Exibe o menu de opções
do {

printf("========================================\n");
printf("      BIBLIOTECA 2\n");
printf("========================================\n");
printf("1 - Cadastrar novo livro\n");
printf("2 - Listar todos os livros\n");
printf("3 - Realizar emprestimos\n");
printf("4 - Listar os emprestimos\n");
printf("0 - Sair\n");
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

    case 3: //Realizar emprestimo
            printf("--- Reaalizar Emprestimo ---\n\n");

            if (totalEmprestimos >= MAX_EMPRESTIMOS){
                printf("Limite de emprestimos atingido!\n");
            } else {
                printf("Livros disponiveis:\n");
                int disponiveis = 0;
                for (int i = 0; i < totalLivros; i++){
                    if (biblioteca[i].disponivel){
                        printf("%d - %s\n", i + 1, biblioteca[i].nome);
                        disponiveis++;
                    }
                }

                if (disponiveis == 0){
                    printf("Nenhum livro disponivel para emprestimo.\n");
                } else {
                    printf("\nDigite o numero do livro que deseja emprestar: ");
                    int numLivro;
                    scanf("%d", &numLivro);
                    limparbuffer();

                    int indice = numLivro - 1; //converte para o indice do array (0 a N-1). 

                    if(indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel){
                        printf("Digite o nome do usuario que está pegando o livro: ");
                        fgets(emprestimos[totalEmprestimos].nomeusuario,TAM_STRING, stdin);
                        emprestimos[totalEmprestimos].nomeusuario[strcspn(emprestimos[totalEmprestimos].nomeusuario, "\n")] = '\0';

                        //Registra o emprestimo
                        emprestimos[totalEmprestimos].indiceLivro = indice;

                        //Atualiza a disponibilidade do livro
                        biblioteca[indice].disponivel = 0; //marca como indisponivel

                        totalEmprestimos++;
                        printf("\nLivro emprestado com sucesso!\n");
                    } else {
                        printf("\nOpção invalida ou livro indisponivel.\n");
                    }
                }
            }
            printf("\nPressione Enter para continuar...");
            getchar();
            break;
            
    case 4: //Listar emprestimos
            printf("--- Lista de Emprestimos ---\n");

            if (totalEmprestimos == 0){
                printf("Nenhum emprestimo realizado.\n");
            } else {
                for (int i = 0; i < totalEmprestimos; i++){
                    // Mostra as infos do emprestimo
                    printf("----------------------------------------\n");
                    printf("Emprestimo: %d\n", i + 1);
                    printf("Livro: %s\n", biblioteca[emprestimos[i].indiceLivro].nome);
                    printf("Usuario: %s\n", emprestimos[i].nomeusuario);
                }
                    printf("-------------------------------------------\n");
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;  

    case 0: //Sair
            printf("Saindo do sistema. Até mais!\n");
            break;

    default: //Opção invalida
            printf("\nOpção invalida! Tente novamente.\n");
            printf("\nPressione enter para continuar...");
            getchar();
            break;
        }
    } while (opcao != 0);

    // Liberação da memória alocada
    free(biblioteca);
    free(emprestimos);

    printf("Memoria liberada. Encerrando programa.\n");
    
    return 0; // fim do programa
}
