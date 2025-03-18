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

    // Menu de seleção do primeiro atributo
    int opcao1, opcao2;
    printf("\n\nEscolha o primeiro atributo para comparação:");
    printf("\n1 - População");
    printf("\n2 - Área");
    printf("\n3 - PIB");
    printf("\n4 - Pontos Turísticos");
    printf("\n5 - Densidade Populacional");
    printf("\n6 - PIB per capita");
    printf("\nDigite sua escolha (1-6): ");
    scanf("%d", &opcao1);

    // Validação da primeira escolha
    if (opcao1 < 1 || opcao1 > 6) {
        printf("\nOpção inválida! O programa será encerrado.\n");
        return 1;
    }

    // Menu de seleção do segundo atributo (excluindo o primeiro)
    printf("\nEscolha o segundo atributo para comparação:");
    printf("\nOpções disponíveis (exceto a opção %d):", opcao1);
    for (int i = 1; i <= 6; i++) {
        if (i != opcao1) {
            printf("\n%d - ", i);
            switch(i) {
                case 1: printf("População"); break;
                case 2: printf("Área"); break;
                case 3: printf("PIB"); break;
                case 4: printf("Pontos Turísticos"); break;
                case 5: printf("Densidade Populacional"); break;
                case 6: printf("PIB per capita"); break;
            }
        }
    }
    printf("\nDigite sua escolha: ");
    scanf("%d", &opcao2);

    // Validação da segunda escolha
    if (opcao2 < 1 || opcao2 > 6 || opcao2 == opcao1) {
        printf("\nOpção inválida! O programa será encerrado.\n");
        return 1;
    }

    // Variáveis para armazenar os valores dos atributos escolhidos
    float valor1_carta1, valor1_carta2, valor2_carta1, valor2_carta2;
    char *nome_atributo1, *nome_atributo2;
    int invertido1 = 0, invertido2 = 0;  // Para densidade populacional (menor vence)

    // Atribuindo valores e nomes do primeiro atributo
    switch(opcao1) {
        case 1:
            valor1_carta1 = populacao1;
            valor1_carta2 = populacao2;
            nome_atributo1 = "População";
            break;
        case 2:
            valor1_carta1 = area1;
            valor1_carta2 = area2;
            nome_atributo1 = "Área";
            break;
        case 3:
            valor1_carta1 = pib1;
            valor1_carta2 = pib2;
            nome_atributo1 = "PIB";
            break;
        case 4:
            valor1_carta1 = pontos_turisticos1;
            valor1_carta2 = pontos_turisticos2;
            nome_atributo1 = "Pontos Turísticos";
            break;
        case 5:
            valor1_carta1 = densidade1;
            valor1_carta2 = densidade2;
            nome_atributo1 = "Densidade Populacional";
            invertido1 = 1;
            break;
        case 6:
            valor1_carta1 = pib_per_capita1;
            valor1_carta2 = pib_per_capita2;
            nome_atributo1 = "PIB per capita";
            break;
    }

    // Atribuindo valores e nomes do segundo atributo
    switch(opcao2) {
        case 1:
            valor2_carta1 = populacao1;
            valor2_carta2 = populacao2;
            nome_atributo2 = "População";
            break;
        case 2:
            valor2_carta1 = area1;
            valor2_carta2 = area2;
            nome_atributo2 = "Área";
            break;
        case 3:
            valor2_carta1 = pib1;
            valor2_carta2 = pib2;
            nome_atributo2 = "PIB";
            break;
        case 4:
            valor2_carta1 = pontos_turisticos1;
            valor2_carta2 = pontos_turisticos2;
            nome_atributo2 = "Pontos Turísticos";
            break;
        case 5:
            valor2_carta1 = densidade1;
            valor2_carta2 = densidade2;
            nome_atributo2 = "Densidade Populacional";
            invertido2 = 1;
            break;
        case 6:
            valor2_carta1 = pib_per_capita1;
            valor2_carta2 = pib_per_capita2;
            nome_atributo2 = "PIB per capita";
            break;
    }

    // Comparando as cartas
    printf("\nComparando cartas usando %s e %s:", nome_atributo1, nome_atributo2);

    // Primeiro atributo
    printf("\n\nPrimeiro atributo (%s):", nome_atributo1);
    printf("\nCarta 1 - %s: %.2f", cidade1, valor1_carta1);
    printf("\nCarta 2 - %s: %.2f", cidade2, valor1_carta2);

    int vitorias_carta1 = 0;
    int vitorias_carta2 = 0;

    // Comparação do primeiro atributo
    if (invertido1) {
        if (valor1_carta1 < valor1_carta2) vitorias_carta1++;
        else if (valor1_carta2 < valor1_carta1) vitorias_carta2++;
    } else {
        if (valor1_carta1 > valor1_carta2) vitorias_carta1++;
        else if (valor1_carta2 > valor1_carta1) vitorias_carta2++;
    }

    // Segundo atributo
    printf("\n\nSegundo atributo (%s):", nome_atributo2);
    printf("\nCarta 1 - %s: %.2f", cidade1, valor2_carta1);
    printf("\nCarta 2 - %s: %.2f", cidade2, valor2_carta2);

    // Comparação do segundo atributo
    if (invertido2) {
        if (valor2_carta1 < valor2_carta2) vitorias_carta1++;
        else if (valor2_carta2 < valor2_carta1) vitorias_carta2++;
    } else {
        if (valor2_carta1 > valor2_carta2) vitorias_carta1++;
        else if (valor2_carta2 > valor2_carta1) vitorias_carta2++;
    }

    // Resultado final
    printf("\n\nResultado final:");
    printf("\nVitórias da Carta 1 (%s): %d", cidade1, vitorias_carta1);
    printf("\nVitórias da Carta 2 (%s): %d", cidade2, vitorias_carta2);
    printf("\n\nResultado: ");

    if (vitorias_carta1 > vitorias_carta2) {
        printf("Carta 1 (%s) venceu!\n", cidade1);
    } else if (vitorias_carta2 > vitorias_carta1) {
        printf("Carta 2 (%s) venceu!\n", cidade2);
    } else {
        printf("Empate!\n");
    }

    return 0;
}