
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// -----------------------------------------------------------------------------
// --- Constantes e Variáveis Globais ---
// -----------------------------------------------------------------------------

#define MAX_COMPONENTES 20
#define TAM_NOME 30
#define TAM_TIPO 20

long long comparacoes = 0;

typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO = 2,
    ORDENAR_PRIORIDADE = 3
} CriterioOrdenacao;

// -----------------------------------------------------------------------------
// --- Estrutura de Dados ---
// -----------------------------------------------------------------------------
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int prioridade;
} Componente;

// -----------------------------------------------------------------------------
// --- Protótipos das Funções ---
// -----------------------------------------------------------------------------
void limparBufferEntrada();
void exibirMenu(bool ordenadoPorNome);
void cadastrarComponentes(Componente componentes[], int *numComponentes);
void mostrarComponentes(const Componente componentes[], int numComponentes);
void inserirComponente(Componente componentes[], int *numComponentes);
void ordenarComponentes(Componente componentes[], int n, CriterioOrdenacao criterio);
void trocar(Componente *a, Componente *b);
int buscaBinariaPorNome(const Componente componentes[], int n, const char *nomeBusca);
double medirTempo(clock_t inicio, clock_t fim);

// -----------------------------------------------------------------------------
// --- Função Principal (main) ---
// -----------------------------------------------------------------------------
int main() {
    Componente torre[MAX_COMPONENTES];
    int numComponentes = 0;
    int opcao = -1;
    bool ordenadoPorNome = false;
    char nomeBusca[TAM_NOME];

    printf("--- Nível Mestre: Ordenação e Busca Binária ---\n");

    do {
        exibirMenu(ordenadoPorNome);
        if (scanf("%d", &opcao) != 1) {
            limparBufferEntrada();
            opcao = -1;
        }
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                inserirComponente(torre, &numComponentes);
                break;
            case 2: {
                int criterio;
                printf("\nEscolha o critério de ordenação:\n");
                printf("1. Nome\n2. Tipo\n3. Prioridade\n> ");
                if (scanf("%d", &criterio) != 1 || criterio < 1 || criterio > 3) {
                    printf("Critério inválido!\n");
                    limparBufferEntrada();
                    break;
                }
                limparBufferEntrada();
                clock_t inicio = clock();
                comparacoes = 0;
                ordenarComponentes(torre, numComponentes, (CriterioOrdenacao)criterio);
                clock_t fim = clock();
                printf("\nOrdenação concluída!\n");
                printf("Tempo de Execução: %.6f segundos\n", medirTempo(inicio, fim));
                printf("Número de Comparações: %lld\n", comparacoes);
                if (criterio == ORDENAR_NOME) ordenadoPorNome = true;
                else ordenadoPorNome = false;
                mostrarComponentes(torre, numComponentes);
                break;
            }
            case 3:
                if (numComponentes == 0) {
                    printf("\nAdicione componentes antes de buscar!\n");
                    break;
                }
                if (!ordenadoPorNome) {
                    printf("\nA busca binária só pode ser feita após ordenar por NOME!\n");
                    break;
                }
                printf("\nDigite o nome do componente para buscar: ");
                fgets(nomeBusca, TAM_NOME, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0;
                int indice = buscaBinariaPorNome(torre, numComponentes, nomeBusca);
                if (indice != -1) {
                    printf("\nComponente encontrado!\n");
                    printf("| %-29s | %-15s | %-10d |\n", torre[indice].nome, torre[indice].tipo, torre[indice].prioridade);
                } else {
                    printf("\nComponente não encontrado!\n");
                }
                printf("Comparações na Busca: %lld\n", comparacoes);
                break;
            case 4:
                mostrarComponentes(torre, numComponentes);
                break;
            case 0:
                printf("\nSistema encerrado.\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// -----------------------------------------------------------------------------
// --- Funções de Gerenciamento e I/O ---
// -----------------------------------------------------------------------------

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void exibirMenu(bool ordenadoPorNome) {
    printf("\n--- MÓDULO MESTRE DA MOCHILA ---\n");
    printf("1. Adicionar componente\n");
    printf("2. Ordenar componentes\n");
    printf("3. Busca binária por nome %s\n", ordenadoPorNome ? "[PRONTO]" : "[PENDENTE]");
    printf("4. Listar componentes\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

// Não usada mais, entrada agora é manual
void cadastrarComponentes(Componente componentes[], int *numComponentes) {}

void inserirComponente(Componente componentes[], int *numComponentes) {
    if (*numComponentes >= MAX_COMPONENTES) {
        printf("\nMochila cheia!\n");
        return;
    }
    printf("\n--- Adicionar Componente ---\n");
    printf("Nome: ");
    fgets(componentes[*numComponentes].nome, TAM_NOME, stdin);
    componentes[*numComponentes].nome[strcspn(componentes[*numComponentes].nome, "\n")] = 0;
    printf("Tipo: ");
    fgets(componentes[*numComponentes].tipo, TAM_TIPO, stdin);
    componentes[*numComponentes].tipo[strcspn(componentes[*numComponentes].tipo, "\n")] = 0;
    printf("Prioridade (1 a 5): ");
    int prioridade = 0;
    if (scanf("%d", &prioridade) != 1 || prioridade < 1 || prioridade > 5) {
        printf("Prioridade inválida!\n");
        limparBufferEntrada();
        return;
    }
    componentes[*numComponentes].prioridade = prioridade;
    limparBufferEntrada();
    (*numComponentes)++;
    printf("Componente adicionado com sucesso!\n");
}

void mostrarComponentes(const Componente componentes[], int numComponentes) {
    printf("\n--- MOCHILA ORDENADA ---\n");
    printf("----------------------------------------------------------------\n");
    printf("| %-29s | %-15s | %-10s |\n", "NOME", "TIPO", "PRIORIDADE");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < numComponentes; i++) {
        printf("| %-29s | %-15s | %-10d |\n", 
               componentes[i].nome, 
               componentes[i].tipo, 
               componentes[i].prioridade);
    }
    printf("----------------------------------------------------------------\n");
}

void trocar(Componente *a, Componente *b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

double medirTempo(clock_t inicio, clock_t fim) {
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

// Substituído por ordenarComponentes

void ordenarComponentes(Componente componentes[], int n, CriterioOrdenacao criterio) {
    int i, j;
    Componente chave;
    switch (criterio) {
        case ORDENAR_NOME:
            for (i = 1; i < n; i++) {
                chave = componentes[i];
                j = i - 1;
                while (j >= 0) {
                    comparacoes++;
                    if (strcmp(componentes[j].nome, chave.nome) > 0) {
                        componentes[j + 1] = componentes[j];
                        j--;
                    } else {
                        break;
                    }
                }
                componentes[j + 1] = chave;
            }
            break;
        case ORDENAR_TIPO:
            for (i = 1; i < n; i++) {
                chave = componentes[i];
                j = i - 1;
                while (j >= 0) {
                    comparacoes++;
                    if (strcmp(componentes[j].tipo, chave.tipo) > 0) {
                        componentes[j + 1] = componentes[j];
                        j--;
                    } else {
                        break;
                    }
                }
                componentes[j + 1] = chave;
            }
            break;
        case ORDENAR_PRIORIDADE:
            for (i = 1; i < n; i++) {
                chave = componentes[i];
                j = i - 1;
                while (j >= 0) {
                    comparacoes++;
                    if (componentes[j].prioridade < chave.prioridade) {
                        componentes[j + 1] = componentes[j];
                        j--;
                    } else {
                        break;
                    }
                }
                componentes[j + 1] = chave;
            }
            break;
    }
}

void bubbleSortNome(Componente componentes[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                trocar(&componentes[j], &componentes[j + 1]);
            }
        }
    }
}

void insertionSortTipo(Componente componentes[], int n) {
    int i, j;
    Componente chave;
    for (i = 1; i < n; i++) {
        chave = componentes[i];
        j = i - 1;
        while (j >= 0) {
            comparacoes++;
            if (strcmp(componentes[j].tipo, chave.tipo) > 0) {
                 componentes[j + 1] = componentes[j];
                 j = j - 1;
            } else {
                break;
            }
        }
        componentes[j + 1] = chave;
    }
}

void selectionSortPrioridade(Componente componentes[], int n) {
    int i, j, max_idx;
    for (i = 0; i < n - 1; i++) {
        max_idx = i;
        for (j = i + 1; j < n; j++) {
            comparacoes++;
            if (componentes[j].prioridade > componentes[max_idx].prioridade) {
                max_idx = j;
            }
        }
        trocar(&componentes[max_idx], &componentes[i]);
    }
}

int buscaBinariaPorNome(const Componente componentes[], int n, const char *nomeBusca) {
    comparacoes = 0;
    int esquerda = 0;
    int direita = n - 1;
    while (esquerda <= direita) {
        comparacoes++;
        int meio = esquerda + (direita - esquerda) / 2;
        int resultado_comparacao = strcmp(componentes[meio].nome, nomeBusca);
        if (resultado_comparacao == 0) {
            return meio;
        }
        if (resultado_comparacao < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -1;
}