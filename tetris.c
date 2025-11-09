#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5  // Número fixo de elementos na fila

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome;  // Tipo da peça ('I', 'O', 'T', 'L')
    int id;     // Identificador único
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca pecas[TAMANHO_FILA];
    int frente;
    int tras;
    int contador;
} Fila;

// ------------------ Funções de Controle da Fila ------------------

// Inicializa a fila vazia
void inicializarFila(Fila *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->contador = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *fila) {
    return fila->contador == TAMANHO_FILA;
}

// Verifica se a fila está vazia
int filaVazia(Fila *fila) {
    return fila->contador == 0;
}

// Insere uma nova peça na fila (enqueue)
void enfileirar(Fila *fila, Peca novaPeca) {
    if (filaCheia(fila)) {
        printf("A fila está cheia! Não é possível inserir nova peça.\n");
        return;
    }
    fila->tras = (fila->tras + 1) % TAMANHO_FILA;
    fila->pecas[fila->tras] = novaPeca;
    fila->contador++;
}

// Remove uma peça da frente da fila (dequeue)
Peca desenfileirar(Fila *fila) {
    Peca pecaRemovida = {' ', -1};
    if (filaVazia(fila)) {
        printf("A fila está vazia! Nenhuma peça para jogar.\n");
        return pecaRemovida;
    }
    pecaRemovida = fila->pecas[fila->frente];
    fila->frente = (fila->frente + 1) % TAMANHO_FILA;
    fila->contador--;
    return pecaRemovida;
}

// Exibe todas as peças da fila
void exibirFila(Fila *fila) {
    printf("\n=== Fila de Peças ===\n");
    if (filaVazia(fila)) {
        printf("[Vazia]\n");
        return;
    }

    int i, index;
    for (i = 0; i < fila->contador; i++) {
        index = (fila->frente + i) % TAMANHO_FILA;
        printf("[%c %d] ", fila->pecas[index].nome, fila->pecas[index].id);
    }
    printf("\n");
}

// ------------------ Função para Gerar Peça ------------------

// Gera automaticamente uma nova peça com tipo aleatório e id único
Peca gerarPeca(int idAtual) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = idAtual;
    return nova;
}

// ------------------ Função Principal ------------------

int main() {
    Fila fila;
    inicializarFila(&fila);

    srand(time(NULL));  // Inicializa gerador de números aleatórios
    int idGlobal = 0;   // Controla o ID único das peças
    int opcao;

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAMANHO_FILA; i++) {
        enfileirar(&fila, gerarPeca(idGlobal++));
    }

    do {
        exibirFila(&fila);
        printf("\n=== Menu de Ações ===\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca jogada = desenfileirar(&fila);
                if (jogada.id != -1)
                    printf("Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
                break;
            }
            case 2: {
                Peca nova = gerarPeca(idGlobal++);
                enfileirar(&fila, nova);
                if (!filaCheia(&fila))
                    printf("Peça inserida: [%c %d]\n", nova.nome, nova.id);
                break;
            }
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}


