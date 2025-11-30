#include <stdio.h>

int main() {
    char estado1, estado2;
    char codigo1[4], codigo2[4];
    char cidade1[100], cidade2[100];
    unsigned long int populacao1, populacao2;
    float area1, area2, pib1, pib2;
    int pontos1, pontos2;
    float densidade1, densidade2, pib_per_capita1, pib_per_capita2;

    printf("Digite os dados da Carta 1:\n");
    printf("Estado (letra A-H): ");
    scanf(" %c", &estado1);
    printf("Codigo da Carta: ");
    scanf("%s", codigo1);
    printf("Nome da Cidade: ");
    scanf(" %[^\n]%*c", cidade1);
    printf("Populacao: ");
    scanf("%lu", &populacao1);
    printf("Area (em km2): ");
    scanf("%f", &area1);
    printf("PIB (em bilhoes de reais): ");
    scanf("%f", &pib1);
    printf("Numero de Pontos Turisticos: ");
    scanf("%d", &pontos1);

    printf("\nDigite os dados da Carta 2:\n");
    printf("Estado (letra A-H): ");
    scanf(" %c", &estado2);
    printf("Codigo da Carta: ");
    scanf("%s", codigo2);
    printf("Nome da Cidade: ");
    scanf(" %[^\n]%*c", cidade2);
    printf("Populacao: ");
    scanf("%lu", &populacao2);
    printf("Area (em km2): ");
    scanf("%f", &area2);
    printf("PIB (em bilhoes de reais): ");
    scanf("%f", &pib2);
    printf("Numero de Pontos Turisticos: ");
    scanf("%d", &pontos2);

    densidade1 = (area1 != 0) ? populacao1 / area1 : 0;
    densidade2 = (area2 != 0) ? populacao2 / area2 : 0;
    pib_per_capita1 = (populacao1 != 0) ? pib1 * 1000000000 / populacao1 : 0;
    pib_per_capita2 = (populacao2 != 0) ? pib2 * 1000000000 / populacao2 : 0;

    int atributo1, atributo2;
    float valor1_carta1 = 0, valor1_carta2 = 0;
    float valor2_carta1 = 0, valor2_carta2 = 0;

    printf("\nEscolha o primeiro atributo para comparacao:\n");
    printf("1 - Populacao\n2 - Area\n3 - PIB\n4 - Pontos Turisticos\n5 - Densidade Demografica\n");
    printf("Opcao: ");
    scanf("%d", &atributo1);

    printf("\nEscolha o segundo atributo para comparacao (diferente do primeiro):\n");
    for (int i = 1; i <= 5; i++) {
        if (i != atributo1) {
            switch (i) {
                case 1: printf("1 - Populacao\n"); break;
                case 2: printf("2 - Area\n"); break;
                case 3: printf("3 - PIB\n"); break;
                case 4: printf("4 - Pontos Turisticos\n"); break;
                case 5: printf("5 - Densidade Demografica\n"); break;
            }
        }
    }
    printf("Opcao: ");
    scanf("%d", &atributo2);

    if (atributo1 < 1 || atributo1 > 5 || atributo2 < 1 || atributo2 > 5 || atributo1 == atributo2) {
        printf("\nErro: Atributos invalidos ou repetidos. Encerrando o programa.\n");
        return 1;
    }

    switch (atributo1) {
        case 1: valor1_carta1 = populacao1; valor1_carta2 = populacao2; break;
        case 2: valor1_carta1 = area1; valor1_carta2 = area2; break;
        case 3: valor1_carta1 = pib1; valor1_carta2 = pib2; break;
        case 4: valor1_carta1 = pontos1; valor1_carta2 = pontos2; break;
        case 5: valor1_carta1 = densidade1; valor1_carta2 = densidade2; break;
    }

    switch (atributo2) {
        case 1: valor2_carta1 = populacao1; valor2_carta2 = populacao2; break;
        case 2: valor2_carta1 = area1; valor2_carta2 = area2; break;
        case 3: valor2_carta1 = pib1; valor2_carta2 = pib2; break;
        case 4: valor2_carta1 = pontos1; valor2_carta2 = pontos2; break;
        case 5: valor2_carta1 = densidade1; valor2_carta2 = densidade2; break;
    }

    printf("\nComparando %s (Estado %c) com %s (Estado %c):\n\n", cidade1, estado1, cidade2, estado2);

    printf("Atributo %d - %s: %.2f | %s: %.2f\n", atributo1, cidade1, valor1_carta1, cidade2, valor1_carta2);
    printf("Atributo %d - %s: %.2f | %s: %.2f\n", atributo2, cidade1, valor2_carta1, cidade2, valor2_carta2);

    valor1_carta1 = (atributo1 == 5) ? -valor1_carta1 : valor1_carta1;
    valor1_carta2 = (atributo1 == 5) ? -valor1_carta2 : valor1_carta2;
    valor2_carta1 = (atributo2 == 5) ? -valor2_carta1 : valor2_carta1;
    valor2_carta2 = (atributo2 == 5) ? -valor2_carta2 : valor2_carta2;

    float soma1 = valor1_carta1 + valor2_carta1;
    float soma2 = valor1_carta2 + valor2_carta2;

    printf("\nSoma dos atributos:\n");
    printf("%s: %.2f\n", cidade1, soma1);
    printf("%s: %.2f\n", cidade2, soma2);

    if (soma1 > soma2)
        printf("\nResultado: %s venceu!\n", cidade1);
    else if (soma2 > soma1)
        printf("\nResultado: %s venceu!\n", cidade2);
    else
        printf("\nResultado: Empate!\n");

    return 0;
}
