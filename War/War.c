// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória e manipulação de strings 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// --- Constantes Globais ---
//#define MAX_TERRITORIOS 5
//#define MAX_NOME 30
//#define MAX_COR 10


// --- Criação da Estrutura (struct) ---
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Funções: exibir mapa, missões, exibição de missão por valor...

void exibirmapa (Territorio* mapa, int n){
    printf("\n---MAPA---\n");
    for (int i = 0; i < n; i++){
        printf("[%d] Territorio: %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("===============================\n");
}

void exibirmissoes(char missao[]){
    printf("\nSua missão é: %s\n\n", missao);
}

void atribuirmissao (char* destino, char* missoes[], int totalmissoes){
    int indice = rand() % totalmissoes; 
    strncpy(destino, missoes[indice], 100); 
}


void atacar(Territorio* atacante, Territorio* defensor){

    if (strcmp(atacante->cor,  defensor->cor)==0){
        printf("Ataque invalido, não é possivel atacar territorios aliados\n");
        return;
    }

    if (atacante->tropas <= 1){
        printf("Tropas insuficientes para atacar.\n");
    }


int dadoatacante = rand()% 6 + 1;
int dadodefensor = rand()% 6 + 1;

printf("\nAtaque! %s (%d) vs %s (%d)\n", atacante->nome, dadoatacante, defensor->nome, dadodefensor);

if (dadoatacante > dadodefensor){
    printf("O atacante venceu!\n");

    int tropastransferidas = atacante->tropas / 2;
    defensor->tropas = tropastransferidas;
    atacante->tropas -= tropastransferidas;

    strncpy(defensor->cor, atacante->cor, 10);

} else {
    printf("O atacante perdeu e perde 1 tropa!\n");
    atacante->tropas--;
  }
}

int verificarMissao (char* missao, Territorio* mapa, int tamanho){

    // Missaão 1: Conquistar 3 territorios
    if (strcmp(missao, "Conquistar 3 territorios") == 0){
        int contador = 0;
        for (int i = 0; i < tamanho; i++){
            if (strcmp(mapa[i].cor, "Azul") == 0){
                contador++;
            }
        }
        return contador >= 3;
    }


    // Missão 2: Eliminar a cor vermelha
    if (strcmp(missao, "Eliminar todas as tropas Vermelhas") == 0){
        for (int i = 0; i < tamanho; i++){
            if (strcmp(mapa[i].cor, "Vermelho") == 0){
                return 0;
            }
        }
        return 1;
    }

    // Miissão 3: Conquistar territorio Delta
    if (strcmp(missao, "Conquistar territorio Delta") == 0 ){
        for (int i = 0; i < tamanho; i++){
            if (strcmp(mapa[i].nome, "Delta") == 0 &&
                strcmp(mapa[i].cor, "Azul") == 0){
                return 1;
            }
        }
        return 0;
    }

    return 0;
}

//Liberação de memoria

void liberarmemoria(Territorio* mapa, char* missaojogador){
    free(mapa);
    free(missaojogador);
}


// Função principal
int main(){

    srand(time(NULL));

    int tamanhoMapa = 5;

    // Alocação do mapa
    Territorio* mapa = (Territorio*) calloc(tamanhoMapa, sizeof(Territorio));

    // Iniciação dos territorios
    strcpy(mapa[0].nome, "Alpha");
    strcpy(mapa[0].cor, "Azul");
    mapa[0].tropas = 5;

    strcpy(mapa[1].nome, "Beta");
    strcpy(mapa[1].cor, "vermelho");
    mapa[1].tropas = 4;

    strcpy(mapa[2].nome, "Gamma");
    strcpy(mapa[2].cor, "Azul");
    mapa[2].tropas = 6;

    strcpy(mapa[3].nome, "Delta");
    strcpy(mapa[3].cor, "Vermelho");
    mapa[3].tropas = 3;

    strcpy(mapa[4].nome, "Epsilon");
    strcpy(mapa[4].cor, "Vermelho");
    mapa[4].tropas = 2;

    // Vetor de missoes
    char* missoes[] = {
        "Conquistar 3 territorios",
        "Eliminar todas as tropas Vermelhas",
        "Conquistar territorio Delta",
        "Controlar 2 territorios com mais de 5 tropas",
        "Eliminar todos os territorios Neutros"
    };

int totalMissoes = 5;

// Alocação de memoria da missao do jogador
char* missaoJogador = (char*) malloc(100 * sizeof(char));

// Atribuição da missao (referencia)
atribuirmissao(missaoJogador, missoes, totalMissoes);

//Exibiçao 1 vez
exibirmissoes(missaoJogador);

int turno = 1;
int venceu = 0;

while (!venceu && turno <= 20){

    printf ("\n===== TURNO %d =====\n", turno);

    exibirmapa(mapa, tamanhoMapa);

    int atacante,  defensor;

    printf("Escolha o número do territorio atacante: ");
    scanf("%d", &atacante);

    printf("Escolha o número do territorio defensor: ");
    scanf("%d", &defensor);

    atacante--;
    defensor--;

    if (atacante >= 0 && atacante < tamanhoMapa &&
        defensor >= 0 && defensor < tamanhoMapa){

        atacar(&mapa[atacante], &mapa[defensor]);
    } else {
        printf("Índices invalidos.\n");
    }

    // Verificação silenciosa da missao
    venceu = verificarMissao(missaoJogador, mapa, tamanhoMapa);

    if (venceu){
        printf("\n*** MISSÃO CUMPRIDA! VOCÊ VENCEU! ***\n");
    }

    turno++;
}


if (!venceu){
    printf("\nFim de jogo. Missão falhou.\n");
}

liberarmemoria(mapa,missaoJogador);


return 0;
}


// Função para cadastrar os territórios, onde o usuário insere os dados de cada território, como nome, cor e quantidade de tropas.
// void cadastrarTerritorios (Territorio* mapa, int n){
//    for (int i = 0; i < n; i++) {
//        printf("\nCadastro do Territorio %d\n", i + 1);
//
//        printf("Digite o nome do Territorio: ");
//        scanf("%s", mapa[i].nome);

//        printf("Digite a cor do exercito: ");
//        scanf("%s", mapa[i].cor);

//        printf("Digite a quantidade de tropas: ");
//        scanf("%d", &mapa[i].tropas);
//    }
//}

//Função para exibir os territórios cadastrados, mostrando as informações de cada território, como nome, cor e quantidade de tropas.
//void exibirTerritorios (Territorio* mapa, int n){
//    printf("\n---Territorios Cadastrados---\n");    
//    for (int i = 0; i < n; i++){
//      printf("%d. Territorio: %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
//    }
//}

//Função para simular um ataque entre dois territórios
//void simularAtaque (Territorio* atacante, Territorio* defensor){
//   if (strcmp(atacante->cor, defensor->cor) == 0) {
//        printf("Ataque inválido! %s e %s pertencem ao mesmo jogador.\n", atacante->nome, defensor->nome);
//        return;
//    }
    
//    int dadoatacante = rand() % 6 + 1; // Simula um dado de 6 lados para o atacante
//    int dadodefensor = rand() % 6 + 1; // Simula um dado de 6 lados para o defensor
//    printf("\n Dado do Atacante: %d", dadoatacante);
//    printf("\n Dado do Defensor: %d\n", dadodefensor);

//    if (dadoatacante > dadodefensor){
//        printf("\n O atacante venceu! \n");
//
//        int tropastransferidas = atacante->tropas / 2; // O atacante transfere metade de suas tropas para o território conquistado
//        defensor->tropas = tropastransferidas; // O defensor recebe as tropas transferidas
//        atacante->tropas -= tropastransferidas; // O atacante perde as tropas transferidas

//        strncpy(defensor->cor, atacante->cor, MAX_COR); // O defensor adota a cor do atacante
//    } else {
//        printf("\n O atacante perdeu e perde 1 tropa! \n");
//        if (atacante->tropas > 0){
//            atacante->tropas--; // Garante que o número de tropas do atacante não fique negativo
//        }
//    }
//}
// Função para liberar memoria
//void liberarMemoria (Territorio* mapa){
//    free(mapa);
//}


// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
//int main() {
//    srand(time(NULL)); // Inicializa o gerador de números aleatórios com base no tempo atual

//    int n;
//    printf("Informe o numero de territorios: ");
//    scanf("%d", &n);

//     Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));

//    if (mapa == NULL) {
//        printf("Erro ao alocar memoria para os territorios.\n");
//        return 1; // Encerra o programa com código de erro
//    }

//    cadastrarTerritorios(mapa, n); // Chama a função para cadastrar os territórios
//    exibirTerritorios(mapa, n); // Chama a função para exibir os territórios cadastrados

//    int atk, def;
//    printf("\nInforme o numero do territorio atacante: ");
//    scanf("%d", &atk);

//    printf("\nInforme o numero do territorio defensor: ");
//    scanf("%d", &def);

//    atk--; // Ajusta os índices para 1
//    def--;

//    if (atk >= 0 && atk < n && def >= 0 && def < n){
//        simularAtaque(&mapa[atk], &mapa[def]);
//    } else {
//        printf("\nIndices Invalidos!\n");
//    }

//    exibirTerritorios(mapa, n); // Exibe os territórios após o ataque para mostrar as mudanças
//    liberarMemoria(mapa); // Libera a memória alocada para os territórios

//return 0;
//}



// Vetor de territorios, responsavel por alocar um espaço na memoria para armazenar os 5 territorios. 
// struct Territorio territorios [MAX_TERRITORIOS];

// printf("=== Cadastro de Territorios do Jogo WAR ===\n");
// Laço 'for' para cadastro dos territorios e entrada de dados do usuario.
// for (int i = 0; i < MAX_TERRITORIOS; i++) {
//    printf("\nCadastro do Territorio %d\n", i + 1);

//    printf("Digite o nome do Territorio: ");
//    scanf("%s", territorios[i].nome);

//    printf("Digite a cor do exercito: ");
//    scanf("%s", territorios[i].cor);

//    printf("Digite a quantidade de tropas: ");
//    scanf("%d", &territorios[i].tropas);
// }

// Exibição dos dados e territorios cadastrados. 
// printf("\n---Territorios Cadastrados---\n");

//for (int i = 0; i < MAX_TERRITORIOS; i++){
//    printf("\nTerritorio %d\n", i + 1);
//    printf("Nome: %s\n", territorios[i].nome);
//    printf("Cor: %s\n", territorios[i].cor);
//    printf("Tropas: %d\n", territorios[i].tropas);
//}

//    return 0;
// }

// ============================================================================