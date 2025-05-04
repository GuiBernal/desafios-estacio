#include <stdio.h>

// Constantes para o número de casas a serem movidas por cada peça
#define CASAS_TORRE 5
#define CASAS_BISPO 5
#define CASAS_RAINHA 8

int main() {
    int i;

    // Simulação do movimento da Torre (5 casas para direita) usando for
    printf("\nMovimento da Torre:\n");
    for (i = 1; i <= CASAS_TORRE; i++) {
        printf("Direita\n");
    }

    // Simulação do movimento do Bispo (5 casas na diagonal para cima e direita) usando while
    printf("\nMovimento do Bispo:\n");
    i = 1;
    while (i <= CASAS_BISPO) {
        printf("Cima, Direita\n");
        i++;
    }

    // Simulação do movimento da Rainha (8 casas para esquerda) usando do-while
    printf("\nMovimento da Rainha:\n");
    i = 1;
    do {
        printf("Esquerda\n");
        i++;
    } while (i <= CASAS_RAINHA);

    return 0;
}

