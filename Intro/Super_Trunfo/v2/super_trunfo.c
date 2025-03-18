#include <stdio.h>
#include <string.h>

int main() {
    // Variáveis para a Carta 1
    char estado1;
    char codigo1[4];
    char cidade1[50];
    int populacao1;
    float area1;
    float pib1;
    int pontos_turisticos1;

    // Variáveis para a Carta 2
    char estado2;
    char codigo2[4];
    char cidade2[50];
    int populacao2;
    float area2;
    float pib2;
    int pontos_turisticos2;

    // Leitura da Carta 1
    printf("Cadastro da Carta 1:\n");
    printf("Digite o estado (A-H): ");
    scanf(" %c", &estado1);
    getchar();

    printf("Digite o código da carta (ex: A01): ");
    scanf("%s", codigo1);
    getchar();

    printf("Digite o nome da cidade: ");
    fgets(cidade1, 50, stdin);
    cidade1[strcspn(cidade1, "\n")] = 0;

    printf("Digite a população: ");
    scanf("%d", &populacao1);
    getchar();

    printf("Digite a área (km²): ");
    scanf("%f", &area1);
    getchar();

    printf("Digite o PIB (em bilhões): ");
    scanf("%f", &pib1);
    getchar();

    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &pontos_turisticos1);
    getchar();

    // Leitura da Carta 2
    printf("\nCadastro da Carta 2:\n");
    printf("Digite o estado (A-H): ");
    scanf(" %c", &estado2);
    getchar();

    printf("Digite o código da carta (ex: A01): ");
    scanf("%s", codigo2);
    getchar();

    printf("Digite o nome da cidade: ");
    fgets(cidade2, 50, stdin);
    cidade2[strcspn(cidade2, "\n")] = 0;

    printf("Digite a população: ");
    scanf("%d", &populacao2);
    getchar();

    printf("Digite a área (km²): ");
    scanf("%f", &area2);
    getchar();

    printf("Digite o PIB (em bilhões): ");
    scanf("%f", &pib2);
    getchar();

    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &pontos_turisticos2);
    getchar();

    float densidade1 = populacao1 / area1;
    float pib_per_capita1 = (pib1 * 1000000000) / populacao1;

    float densidade2 = populacao2 / area2;
    float pib_per_capita2 = (pib2 * 1000000000) / populacao2;

    // Dados da Carta 1
    printf("\nCarta 1:");
    printf("\nEstado: %c", estado1);
    printf("\nCódigo: %s", codigo1);
    printf("\nNome da Cidade: %s", cidade1);
    printf("\nPopulação: %d", populacao1);
    printf("\nÁrea: %.2f km²", area1);
    printf("\nPIB: %.2f bilhões de reais", pib1);
    printf("\nNúmero de Pontos Turísticos: %d", pontos_turisticos1);
    printf("\nDensidade Populacional: %.2f hab/km²", densidade1);
    printf("\nPIB per capita: R$ %.2f", pib_per_capita1);

    // Dados da Carta 2
    printf("\n\nCarta 2:");
    printf("\nEstado: %c", estado2);
    printf("\nCódigo: %s", codigo2);
    printf("\nNome da Cidade: %s", cidade2);
    printf("\nPopulação: %d", populacao2);
    printf("\nÁrea: %.2f km²", area2);
    printf("\nPIB: %.2f bilhões de reais", pib2);
    printf("\nNúmero de Pontos Turísticos: %d", pontos_turisticos2);
    printf("\nDensidade Populacional: %.2f hab/km²", densidade2);
    printf("\nPIB per capita: R$ %.2f", pib_per_capita2);

    // Menu de seleção do atributo
    int opcao;
    printf("\n\nEscolha o atributo para comparação:");
    printf("\n1 - População");
    printf("\n2 - Área");
    printf("\n3 - PIB");
    printf("\n4 - Pontos Turísticos");
    printf("\n5 - Densidade Populacional");
    printf("\n6 - PIB per capita");
    printf("\nDigite sua escolha (1-6): ");
    scanf("%d", &opcao);

    // Comparando as cartas
    switch(opcao) {
        case 1:
            printf("\nComparação de cartas (Atributo: População):");
            printf("\nCarta 1 - %s: %d habitantes", cidade1, populacao1);
            printf("\nCarta 2 - %s: %d habitantes", cidade2, populacao2);

            if (populacao1 > populacao2) {
                printf("\nResultado: Carta 1 (%s) venceu!\n", cidade1);
            } else if (populacao2 > populacao1) {
                printf("\nResultado: Carta 2 (%s) venceu!\n", cidade2);
            } else {
                printf("\nResultado: Empate!\n");
            }
            break;

        case 2:
            printf("\nComparação de cartas (Atributo: Área):");
            printf("\nCarta 1 - %s: %.2f km²", cidade1, area1);
            printf("\nCarta 2 - %s: %.2f km²", cidade2, area2);

            if (area1 > area2) {
                printf("\nResultado: Carta 1 (%s) venceu!\n", cidade1);
            } else if (area2 > area1) {
                printf("\nResultado: Carta 2 (%s) venceu!\n", cidade2);
            } else {
                printf("\nResultado: Empate!\n");
            }
            break;

        case 3:
            printf("\nComparação de cartas (Atributo: PIB):");
            printf("\nCarta 1 - %s: %.2f bilhões", cidade1, pib1);
            printf("\nCarta 2 - %s: %.2f bilhões", cidade2, pib2);

            if (pib1 > pib2) {
                printf("\nResultado: Carta 1 (%s) venceu!\n", cidade1);
            } else if (pib2 > pib1) {
                printf("\nResultado: Carta 2 (%s) venceu!\n", cidade2);
            } else {
                printf("\nResultado: Empate!\n");
            }
            break;

        case 4:
            printf("\nComparação de cartas (Atributo: Pontos Turísticos):");
            printf("\nCarta 1 - %s: %d pontos", cidade1, pontos_turisticos1);
            printf("\nCarta 2 - %s: %d pontos", cidade2, pontos_turisticos2);

            if (pontos_turisticos1 > pontos_turisticos2) {
                printf("\nResultado: Carta 1 (%s) venceu!\n", cidade1);
            } else if (pontos_turisticos2 > pontos_turisticos1) {
                printf("\nResultado: Carta 2 (%s) venceu!\n", cidade2);
            } else {
                printf("\nResultado: Empate!\n");
            }
            break;

        case 5:
            printf("\nComparação de cartas (Atributo: Densidade Populacional):");
            printf("\nCarta 1 - %s: %.2f hab/km²", cidade1, densidade1);
            printf("\nCarta 2 - %s: %.2f hab/km²", cidade2, densidade2);

            // Para densidade, menor valor vence
            if (densidade1 < densidade2) {
                printf("\nResultado: Carta 1 (%s) venceu!\n", cidade1);
            } else if (densidade2 < densidade1) {
                printf("\nResultado: Carta 2 (%s) venceu!\n", cidade2);
            } else {
                printf("\nResultado: Empate!\n");
            }
            break;

        case 6:
            printf("\nComparação de cartas (Atributo: PIB per capita):");
            printf("\nCarta 1 - %s: R$ %.2f", cidade1, pib_per_capita1);
            printf("\nCarta 2 - %s: R$ %.2f", cidade2, pib_per_capita2);

            if (pib_per_capita1 > pib_per_capita2) {
                printf("\nResultado: Carta 1 (%s) venceu!\n", cidade1);
            } else if (pib_per_capita2 > pib_per_capita1) {
                printf("\nResultado: Carta 2 (%s) venceu!\n", cidade2);
            } else {
                printf("\nResultado: Empate!\n");
            }
            break;

        default:
            printf("\nOpção inválida! Por favor, escolha um número entre 1 e 6.\n");
    }

    return 0;
}