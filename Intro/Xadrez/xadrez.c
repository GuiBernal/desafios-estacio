#include <stdio.h>

// Constantes para o número de casas a serem movidas por cada peça
#define CASAS_TORRE 5
#define CASAS_BISPO 5
#define CASAS_RAINHA 8
#define CASAS_CAVALO_CIMA 2  // Número de casas para cima
#define CASAS_CAVALO_DIREITA 1  // Número de casas para direita

// Função recursiva para o movimento da Torre
void moverTorre(int casas) {
    if (casas <= 0) {
        return;
    }
    printf("Direita\n");
    moverTorre(casas - 1);
}

// Função recursiva para o movimento do Bispo
void moverBispo(int casas) {
    if (casas <= 0) {
        return;
    }
    printf("Cima, Direita\n");
    moverBispo(casas - 1);
}

// Função recursiva para o movimento da Rainha
void moverRainha(int casas) {
    if (casas <= 0) {
        return;
    }
    printf("Esquerda\n");
    moverRainha(casas - 1);
}

// Função para o movimento do Cavalo usando loops complexos
void moverCavalo() {
    int i, j;
    // Loop externo para controlar o movimento vertical
    for (i = 1; i <= CASAS_CAVALO_CIMA; i++) {
        printf("Cima\n");
        // Loop interno para o movimento horizontal
        for (j = 1; j <= CASAS_CAVALO_DIREITA; j++) {
            // Só move para direita após completar os dois movimentos para cima
            if (i == CASAS_CAVALO_CIMA) {
                printf("Direita\n");
            }
        }
    }
}

// Função para o movimento do Bispo usando loops aninhados
void moverBispoLoops() {
    int i, j;
    // Loop externo para movimento vertical
    for (i = 1; i <= CASAS_BISPO; i++) {
        // Loop interno para movimento horizontal
        for (j = 1; j <= CASAS_BISPO; j++) {
            if (i == j) {  // Apenas na diagonal
                printf("Cima, Direita\n");
                break;  // Move para próxima linha após encontrar a diagonal
            }
        }
    }
}

int main() {
    // Movimento da Torre usando recursividade
    printf("\nMovimento da Torre:\n");
    moverTorre(CASAS_TORRE);

    // Movimento do Bispo usando recursividade
    printf("\nMovimento do Bispo (recursivo):\n");
    moverBispo(CASAS_BISPO);

    // Movimento do Bispo usando loops aninhados
    printf("\nMovimento do Bispo (loops aninhados):\n");
    moverBispoLoops();

    // Movimento da Rainha usando recursividade
    printf("\nMovimento da Rainha:\n");
    moverRainha(CASAS_RAINHA);

    // Movimento do Cavalo usando loops complexos
    printf("\nMovimento do Cavalo:\n");
    moverCavalo();

    return 0;
}

