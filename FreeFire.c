#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// --- Constantes Globais para o Nível Novato ---
#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

// 🚩 OBJETIVO: Criar a struct Item
// Estrutura para representar cada item na mochila.
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// --- Protótipos das Funções ---
void exibirMenu();
void adicionarItem(Item inventario[], int *numItens);
void removerItem(Item inventario[], int *numItens);
void listarItens(const Item inventario[], int numItens);
void limparBufferEntrada();

// --- Função Principal (main) ---
int main() {
    // ⚙️ FUNCIONALIDADE: Vetor estático com capacidade para até 10 itens
    Item mochila[MAX_ITENS];
    int numItens = 0; // Variável de controle: quantidade atual de itens na mochila
    int opcao;

    printf("--- Código da Ilha: Inventário Básico ---\n");
    
    // ⚙️ FUNCIONALIDADE: Menu interativo com switch e do-while
    do {
        exibirMenu();
        
        // Leitura da opção
        if (scanf("%d", &opcao) != 1) {
            limparBufferEntrada();
            opcao = -1; // Opção inválida
        }
        limparBufferEntrada(); // Limpa o buffer após o scanf de números

        switch (opcao) {
            case 1:
                adicionarItem(mochila, &numItens);
                break;
            case 2:
                removerItem(mochila, &numItens);
                break;
            case 3:
                listarItens(mochila, numItens);
                break;
            case 0:
                printf("\nInventário fechado. Boa sorte na fuga!\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções ---

// Apresenta o menu principal ao usuário.
void exibirMenu() {
    printf("\n--- MOCHILA DE SOBREVIVÊNCIA ---\n");
    printf("Itens atuais: %d/%d\n", numItens, MAX_ITENS);
    printf("1. Adicionar item\n");
    printf("2. Remover item (pelo nome)\n");
    printf("3. Listar itens\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

// ⚙️ FUNCIONALIDADE: Adicionar item à mochila
void adicionarItem(Item inventario[], int *numItens) {
    if (*numItens >= MAX_ITENS) {
        printf("\nERRO: Mochila cheia! Capacidade máxima (%d) atingida.\n", MAX_ITENS);
        return;
    }

    printf("\n--- ADICIONAR ITEM ---\n");

    // ENTRADA: Nome
    printf("Nome do item (máx. %d caracteres): ", TAM_NOME - 1);
    fgets(inventario[*numItens].nome, TAM_NOME, stdin);
    // Remove o '\n' adicionado pelo fgets
    inventario[*numItens].nome[strcspn(inventario[*numItens].nome, "\n")] = 0;

    // ENTRADA: Tipo
    printf("Tipo (Arma, Curativo, Munição, etc.): ");
    scanf("%s", inventario[*numItens].tipo);
    limparBufferEntrada(); 

    // ENTRADA: Quantidade
    printf("Quantidade: ");
    if (scanf("%d", &inventario[*numItens].quantidade) != 1 || inventario[*numItens].quantidade <= 0) {
        printf("Quantidade inválida. Operação cancelada.\n");
        limparBufferEntrada();
        return;
    }
    
    // Atualiza o contador de itens
    (*numItens)++; 
    printf("\nItem \"%s\" adicionado com sucesso!\n", inventario[*numItens - 1].nome);
}

// ⚙️ FUNCIONALIDADE: Remover item pelo nome
void removerItem(Item inventario[], int *numItens) {
    if (*numItens == 0) {
        printf("\nMochila vazia. Nada para remover.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n--- REMOVER ITEM ---\n");
    printf("Digite o NOME do item a ser removido: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0; 

    int i, indiceEncontrado = -1;

    // Busca linear simples
    for (i = 0; i < *numItens; i++) {
        if (strcmp(inventario[i].nome, nomeBusca) == 0) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado != -1) {
        // Reorganiza o vetor para preencher a lacuna
        for (i = indiceEncontrado; i < *numItens - 1; i++) {
            inventario[i] = inventario[i + 1];
        }
        (*numItens)--;
        printf("\nItem \"%s\" removido com sucesso!\n", nomeBusca);
    } else {
        printf("\nItem \"%s\" não encontrado na mochila.\n", nomeBusca);
    }
}

// ⚙️ FUNCIONALIDADE: Listar os itens cadastrados (SAÍDA)
void listarItens(const Item inventario[], int numItens) {
    printf("\n--- LISTA DE ITENS ---\n");
    if (numItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    // Saída organizada em formato de tabela
    printf("-----------------------------------------------------------\n");
    printf("| %-29s | %-15s | %-12s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < numItens; i++) {
        printf("| %-29s | %-15s | %-12d |\n", 
               inventario[i].nome, 
               inventario[i].tipo, 
               inventario[i].quantidade);
    }
    printf("-----------------------------------------------------------\n");
}

// Utilitário para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}