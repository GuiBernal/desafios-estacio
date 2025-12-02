#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5
#define TAMANHO_PILHA 3
#define TIPOS_PECAS 4

typedef struct {
    char nome;
    int id;
} Peca;

typedef struct {
    Peca pecas[TAMANHO_FILA];
    int frente;
    int tras;
    int tamanho;
} Fila;

typedef struct {
    Peca pecas[TAMANHO_PILHA];
    int topo;
    int tamanho;
} Pilha;

void inicializarFila(Fila *fila) {
    fila->frente = 0;
    fila->tras = 0;
    fila->tamanho = 0;
}

int filaVazia(Fila *fila) {
    return fila->tamanho == 0;
}

int filaCheia(Fila *fila) {
    return fila->tamanho == TAMANHO_FILA;
}

void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
    pilha->tamanho = 0;
}

int pilhaVazia(Pilha *pilha) {
    return pilha->tamanho == 0;
}

int pilhaCheia(Pilha *pilha) {
    return pilha->tamanho == TAMANHO_PILHA;
}

Peca gerarPeca(int id) {
    Peca novaPeca;
    char tipos[TIPOS_PECAS] = {'I', 'O', 'T', 'L'};
    novaPeca.nome = tipos[rand() % TIPOS_PECAS];
    novaPeca.id = id;
    return novaPeca;
}

void inicializarPecas(Fila *fila) {
    for (int i = 0; i < TAMANHO_FILA; i++) {
        fila->pecas[i] = gerarPeca(i);
        fila->tras = (fila->tras + 1) % TAMANHO_FILA;
        fila->tamanho++;
    }
}

void exibirEstado(Fila *fila, Pilha *pilha) {
    printf("\nEstado atual:\n\n");
    
    printf("Fila de peças\t");
    if (filaVazia(fila)) {
        printf("Fila vazia\n");
    } else {
        int posicao = fila->frente;
        for (int i = 0; i < fila->tamanho; i++) {
            printf("[%c %d]", fila->pecas[posicao].nome, fila->pecas[posicao].id);
            if (i < fila->tamanho - 1) {
                printf(" ");
            }
            posicao = (posicao + 1) % TAMANHO_FILA;
        }
        printf("\n");
    }
    
    printf("Pilha de reserva\t");
    if (pilhaVazia(pilha)) {
        printf("(Topo -> base): Pilha vazia\n");
    } else {
        printf("(Topo -> base): ");
        for (int i = pilha->topo; i >= 0; i--) {
            printf("[%c %d]", pilha->pecas[i].nome, pilha->pecas[i].id);
            if (i > 0) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int jogarPeca(Fila *fila, int *proximoId) {
    if (filaVazia(fila)) {
        printf("\nErro: Fila vazia! Não é possível jogar peça.\n");
        return 0;
    }
    
    Peca pecaRemovida = fila->pecas[fila->frente];
    printf("\nPeça jogada: [%c %d]\n", pecaRemovida.nome, pecaRemovida.id);
    
    fila->frente = (fila->frente + 1) % TAMANHO_FILA;
    fila->tamanho--;
    
    Peca novaPeca = gerarPeca(*proximoId);
    (*proximoId)++;
    fila->pecas[fila->tras] = novaPeca;
    fila->tras = (fila->tras + 1) % TAMANHO_FILA;
    fila->tamanho++;
    
    return 1;
}

int reservarPeca(Fila *fila, Pilha *pilha, int *proximoId) {
    if (filaVazia(fila)) {
        printf("\nErro: Fila vazia! Não é possível reservar peça.\n");
        return 0;
    }
    
    if (pilhaCheia(pilha)) {
        printf("\nErro: Pilha de reserva cheia! Não é possível reservar peça.\n");
        return 0;
    }
    
    Peca pecaReservada = fila->pecas[fila->frente];
    printf("\nPeça reservada: [%c %d]\n", pecaReservada.nome, pecaReservada.id);
    
    fila->frente = (fila->frente + 1) % TAMANHO_FILA;
    fila->tamanho--;
    
    pilha->topo++;
    pilha->pecas[pilha->topo] = pecaReservada;
    pilha->tamanho++;
    
    Peca novaPeca = gerarPeca(*proximoId);
    (*proximoId)++;
    fila->pecas[fila->tras] = novaPeca;
    fila->tras = (fila->tras + 1) % TAMANHO_FILA;
    fila->tamanho++;
    
    return 1;
}

int usarPecaReservada(Pilha *pilha) {
    if (pilhaVazia(pilha)) {
        printf("\nErro: Pilha de reserva vazia! Não é possível usar peça reservada.\n");
        return 0;
    }
    
    Peca pecaUsada = pilha->pecas[pilha->topo];
    printf("\nPeça reservada usada: [%c %d]\n", pecaUsada.nome, pecaUsada.id);
    
    pilha->topo--;
    pilha->tamanho--;
    
    return 1;
}

int trocarPecaAtual(Fila *fila, Pilha *pilha) {
    if (filaVazia(fila)) {
        printf("\nErro: Fila vazia! Não é possível trocar peça.\n");
        return 0;
    }
    
    if (pilhaVazia(pilha)) {
        printf("\nErro: Pilha de reserva vazia! Não é possível trocar peça.\n");
        return 0;
    }
    
    Peca temp = fila->pecas[fila->frente];
    fila->pecas[fila->frente] = pilha->pecas[pilha->topo];
    pilha->pecas[pilha->topo] = temp;
    
    printf("\nAção: troca realizada entre a peça da frente da fila e o topo da pilha.\n\n");
    
    return 1;
}

int trocaMultipla(Fila *fila, Pilha *pilha) {
    if (fila->tamanho < 3) {
        printf("\nErro: Fila precisa ter pelo menos 3 peças para realizar a troca múltipla.\n");
        return 0;
    }
    
    if (pilha->tamanho < 3) {
        printf("\nErro: Pilha precisa ter pelo menos 3 peças para realizar a troca múltipla.\n");
        return 0;
    }
    
    Peca temp;
    int posFila = fila->frente;
    int posPilha = pilha->topo;
    
    for (int i = 0; i < 3; i++) {
        temp = fila->pecas[posFila];
        fila->pecas[posFila] = pilha->pecas[posPilha];
        pilha->pecas[posPilha] = temp;
        
        posFila = (posFila + 1) % TAMANHO_FILA;
        posPilha--;
    }
    
    printf("\nAção: troca realizada entre os 3 primeiros da fila e os 3 da pilha.\n\n");
    
    return 1;
}

void exibirMenu() {
    printf("\nOpções disponíveis:\n");
    printf("Código\tAção\n");
    printf("1\tJogar peça da frente da fila\n");
    printf("2\tEnviar peça da fila para a pilha de reserva\n");
    printf("3\tUsar peça da pilha de reserva\n");
    printf("4\tTrocar peça da frente da fila com o topo da pilha\n");
    printf("5\tTrocar os 3 primeiros da fila com as 3 peças da pilha\n");
    printf("0\tSair\n");
}

int main() {
    srand(time(NULL));
    
    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    inicializarPecas(&fila);
    
    int opcao;
    int proximoId = TAMANHO_FILA;
    
    do {
        exibirEstado(&fila, &pilha);
        exibirMenu();
        printf("\nOpção escolhida: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                jogarPeca(&fila, &proximoId);
                break;
            case 2:
                reservarPeca(&fila, &pilha, &proximoId);
                break;
            case 3:
                usarPecaReservada(&pilha);
                break;
            case 4:
                trocarPecaAtual(&fila, &pilha);
                break;
            case 5:
                trocaMultipla(&fila, &pilha);
                break;
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
    
    return 0;
}

