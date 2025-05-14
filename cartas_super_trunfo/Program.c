#include <stdio.h>

int main() {
    
    char estado1;
    char codigo1[4];
    char cidade1[100];
    unsigned long int populacao1;
    float area1, pib1;
    int pontos1;
    float densidade1, pib_per_capita1, super_poder1;

    char estado2;
    char codigo2[4];
    char cidade2[100];
    unsigned long int populacao2;
    float area2, pib2;
    int pontos2;
    float densidade2, pib_per_capita2, super_poder2;

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

    densidade1 = populacao1 / area1;
    densidade2 = populacao2 / area2;

    pib_per_capita1 = pib1 * 1000000000 / populacao1;
    pib_per_capita2 = pib2 * 1000000000 / populacao2;

    super_poder1 = (float)populacao1 + area1 + pib1 + pontos1 + pib_per_capita1 + (1 / densidade1);
    super_poder2 = (float)populacao2 + area2 + pib2 + pontos2 + pib_per_capita2 + (1 / densidade2);

    printf("\nCarta 1:\n");
    printf("Estado: %c\n", estado1);
    printf("Codigo: %s\n", codigo1);
    printf("Nome da Cidade: %s\n", cidade1);
    printf("Populacao: %lu\n", populacao1);
    printf("Area: %.2f km2\n", area1);
    printf("PIB: %.2f bilhoes de reais\n", pib1);
    printf("Numero de Pontos Turisticos: %d\n", pontos1);
    printf("Densidade Populacional: %.2f hab/km2\n", densidade1);
    printf("PIB per Capita: %.2f reais\n", pib_per_capita1);
    printf("Super Poder: %.2f\n", super_poder1);

    printf("\nCarta 2:\n");
    printf("Estado: %c\n", estado2);
    printf("Codigo: %s\n", codigo2);
    printf("Nome da Cidade: %s\n", cidade2);
    printf("Populacao: %lu\n", populacao2);
    printf("Area: %.2f km2\n", area2);
    printf("PIB: %.2f bilhoes de reais\n", pib2);
    printf("Numero de Pontos Turisticos: %d\n", pontos2);
    printf("Densidade Populacional: %.2f hab/km2\n", densidade2);
    printf("PIB per Capita: %.2f reais\n", pib_per_capita2);
    printf("Super Poder: %.2f\n", super_poder2);

    printf("\nComparacao de Cartas:\n");
    printf("Populacao: %s venceu (%d)\n", (populacao1 > populacao2 ? "Carta 1" : "Carta 2"), populacao1 > populacao2);
    printf("Area: %s venceu (%d)\n", (area1 > area2 ? "Carta 1" : "Carta 2"), area1 > area2);
    printf("PIB: %s venceu (%d)\n", (pib1 > pib2 ? "Carta 1" : "Carta 2"), pib1 > pib2);
    printf("Pontos Turisticos: %s venceu (%d)\n", (pontos1 > pontos2 ? "Carta 1" : "Carta 2"), pontos1 > pontos2);
    printf("Densidade Populacional: %s venceu (%d)\n", (densidade1 < densidade2 ? "Carta 1" : "Carta 2"), densidade1 < densidade2);
    printf("PIB per Capita: %s venceu (%d)\n", (pib_per_capita1 > pib_per_capita2 ? "Carta 1" : "Carta 2"), pib_per_capita1 > pib_per_capita2);
    printf("Super Poder: %s venceu (%d)\n", (super_poder1 > super_poder2 ? "Carta 1" : "Carta 2"), super_poder1 > super_poder2);

    return 0;
}
