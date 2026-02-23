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

struct Emprestimo {
    int indiceLivro; // Para saber qual livro do array "biblioteca" foi emprestado
    char nomeusuario[TAM_STRING];
};

// Prototipos das funções
void limparbuffer();
void exibirMenu();
void cadastrarLivro(struct Livro *biblioteca, int *totalLivros);
void listarLivros(const struct Livro *biblioteca, int totalLivros);
void realizarEmprestimo(struct Livro *biblioteca, int totalLivros, struct Emprestimo *emprestimos, int *totalEmprestimos);
void listarEmprestimos(const struct Livro *biblioteca, const struct Emprestimo *emprestimos, int totalEmprestimos);
void liberarMemoria(struct Livro *biblioteca, struct Emprestimo *emprestimos);  

// Função principal main()
int main(){
    struct Livro *biblioteca = (struct Livro *) calloc(MAX_LIVROS, sizeof(struct Livro));
    struct Emprestimo *emprestimos = (struct Emprestimo *) malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));

    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1; // retorna 1 para indicar erro.
    }

    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;

    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparbuffer();

        switch (opcao) {
            case 1:
                cadastrarLivro(biblioteca, &totalLivros);
                break;
            case 2:
                listarLivros(biblioteca, totalLivros);
                break;
            case 3:
                realizarEmprestimo(biblioteca, totalLivros, emprestimos, &totalEmprestimos);
                break;
            case 4:
                listarEmprestimos(biblioteca, emprestimos, totalEmprestimos);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                getchar();
        }
    } while (opcao != 0);
    //FFunção para liberar a memoria alocada dinamicamente
    liberarMemoria(biblioteca, emprestimos);
    return 0;
}

// Implementação das funções
void limparbuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void exibirMenu() {
    printf("========================================\n");
    printf("      BIBLIOTECA 2\n");
    printf("========================================\n");
    printf("1 - Cadastrar novo livro\n");
    printf("2 - Listar todos os livros\n");
    printf("3 - Realizar emprestimos\n");
    printf("4 - Listar os emprestimos\n");
    printf("0 - Sair\n");
    printf("----------------------------------------\n");
}
/**
* @brief Função para cadastrar um novo livro na biblioteca
* @param biblioteca Ponteiro para o array de livros
* @param totalLivros Ponteiro para o contador de livros cadastrados
*/
void cadastrarLivro(struct Livro *biblioteca, int *totalLivros) {
    printf("--- Cadastro de novo livro ---\n\n");

    if (*totalLivros < MAX_LIVROS) {
        int indice = *totalLivros; // indice para o novo livro a ser cadastrado

        printf("Digite o nome do livro: ");
        fgets(biblioteca[indice].nome, TAM_STRING, stdin);
        printf("Digite o autor: ");
        fgets(biblioteca[indice].autor, TAM_STRING, stdin);
        printf("Digite a editora: ");
        fgets(biblioteca[indice].editora, TAM_STRING, stdin);

        biblioteca[indice].nome[strcspn(biblioteca[indice].nome, "\n")] = '\0';
        biblioteca[indice].autor[strcspn(biblioteca[indice].autor, "\n")] = '\0';
        biblioteca[indice].editora[strcspn(biblioteca[indice].editora, "\n")] = '\0';

        printf("Digite a edicao: ");
        scanf("%d", &biblioteca[indice].edicao);
        limparbuffer();

        biblioteca[indice].disponivel = 1; //marca o livro como disponivel
        (*totalLivros)++; //incrementa o contador de livros 
        printf("\nLivro cadastrado com sucesso!\n");
    } else {
        printf("Biblioteca cheia! Nao e possivel mais cadastrar livros.\n");
    }
    printf("\nPressione Enter para continuar...");
    getchar(); //Pausa para o usuario ler a mensagem antes de voltar pro menu.
}

/**
* @brief Função para listar todos os livros cadastrados na biblioteca
* @param biblioteca Ponteiro para o array de livros
* @param totalLivros Quantidade total de livros cadastrados
*/

void listarLivros(const struct Livro *biblioteca, int totalLivros) {
    printf("--- Lista de Livros Cadastrados ---\n");

    if (totalLivros == 0) {
        printf("Nenhum livro cadastrado ainda.\n");
    } else {
        for (int i = 0; i < totalLivros; i++) {
            printf("----------------------------------------\n");
            printf("Livro: %d\n", i + 1);
            printf("Nome: %s\n", biblioteca[i].nome);
            printf("Autor: %s\n", biblioteca[i].autor);
            printf("Editora: %s\n", biblioteca[i].editora);
            printf("Edicao: %d\n", biblioteca[i].edicao);
            printf("Disponivel: %s\n", biblioteca[i].disponivel ? "Sim" : "Nao");
        }
        printf("-------------------------------------------\n");
    }
    // Pausa para que o usuario veja a lista antes de limpar a tela
    printf("\nPressione Enter para continuar...");
    getchar();
}

/**
 * @brief Função para realizar um emprestimo de livro
 * @param biblioteca Ponteiro para o array de livros (modificável para atualizar a disponibilidade)
 * @param totalLivros Quantidade total de livros cadastrados
 * @param emprestimos Ponteiro para o array de emprestimos (modificável)
 * @param totalEmprestimos Ponteiro para o contador de emprestimos realizados
 */

void realizarEmprestimo(struct Livro *biblioteca, int totalLivros, struct Emprestimo *emprestimos, int *totalEmprestimos) {
    printf("--- Realizar Emprestimo ---\n\n");

    if (*totalEmprestimos >= MAX_EMPRESTIMOS) {
        printf("Limite de emprestimos atingido!\n");
    } else {
        printf("Livros disponiveis:\n");
        int disponiveis = 0;
        for (int i = 0; i < totalLivros; i++) {
            if (biblioteca[i].disponivel == 1) { // Verifica se o livro está disponível
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

            if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel) {
                printf("Digite o nome do usuario que esta pegando o livro: ");
                fgets(emprestimos[*totalEmprestimos].nomeusuario, TAM_STRING, stdin);
                emprestimos[*totalEmprestimos].nomeusuario[strcspn(emprestimos[*totalEmprestimos].nomeusuario, "\n")] = '\0';

                //Registra o emprestimo
                emprestimos[*totalEmprestimos].indiceLivro = indice;

                //Atualiza a disponibilidade do livro
                biblioteca[indice].disponivel = 0; //marca como indisponivel

                (*totalEmprestimos)++;
                printf("\nLivro emprestado com sucesso!\n");
            } else {
                printf("\nOpcao invalida ou livro indisponivel.\n");
            }
        }
    }
    printf("\nPressione Enter para continuar...");
    getchar();
}

/**
 * @brief Função para listar todos os emprestimos realizados
 * @param biblioteca Ponteiro para o array de livros (para mostrar o nome do livro emprestado)
 * @param emprestimos Ponteiro para o array de emprestimos
 * @param totalEmprestimos Quantidade total de emprestimos realizados
 */

void listarEmprestimos(const struct Livro *biblioteca, const struct Emprestimo *emprestimos, int totalEmprestimos) {
    printf("--- Lista de Emprestimos ---\n");

    if (totalEmprestimos == 0) {
        printf("Nenhum emprestimo realizado.\n");
    } else {
        for (int i = 0; i < totalEmprestimos; i++) {
            int indiceLivro = emprestimos[i].indiceLivro; // Pega o indice do livro emprestado
            // Mostra as infos do emprestimo
            printf("----------------------------------------\n");
            printf("Emprestimo: %d\n", i + 1);
            printf("Livro: %s\n", biblioteca[indiceLivro].nome);
            printf("Usuario: %s\n", emprestimos[i].nomeusuario);
        }
        printf("-------------------------------------------\n");
    }
    // Pausa para que o usuario veja a lista antes de limpar a tela
    printf("\nPressione Enter para continuar...");
    getchar();
}

/**
 * @brief Libera a memoria alocada para os arrays dinamicos.
 */

void liberarMemoria(struct Livro *biblioteca, struct Emprestimo *emprestimos) {
    free(biblioteca);
    free(emprestimos);
    printf("Memoria liberada com sucesso.\n");
}
