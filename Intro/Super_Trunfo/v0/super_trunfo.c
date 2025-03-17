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

    // Dados da Carta 1
    printf("\nCarta 1:");
    printf("\nEstado: %c", estado1);
    printf("\nCódigo: %s", codigo1);
    printf("\nNome da Cidade: %s", cidade1);
    printf("\nPopulação: %d", populacao1);
    printf("\nÁrea: %.2f km²", area1);
    printf("\nPIB: %.2f bilhões de reais", pib1);
    printf("\nNúmero de Pontos Turísticos: %d", pontos_turisticos1);

    // Dados da Carta 2
    printf("\n\nCarta 2:");
    printf("\nEstado: %c", estado2);
    printf("\nCódigo: %s", codigo2);
    printf("\nNome da Cidade: %s", cidade2);
    printf("\nPopulação: %d", populacao2);
    printf("\nÁrea: %.2f km²", area2);
    printf("\nPIB: %.2f bilhões de reais", pib2);
    printf("\nNúmero de Pontos Turísticos: %d\n", pontos_turisticos2);

    return 0;
}