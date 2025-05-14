#include <stdio.h>

void movimento_torre(int casas) {
    if (casas == 0) return;
    printf("Direita\n");
    movimento_torre(casas - 1);
}

void movimento_bispo(int casas) {
    if (casas == 0) return;
    printf("Cima Direita\n");
    movimento_bispo(casas - 1);
}

void movimento_rainha(int casas) {
    if (casas == 0) return;
    printf("Esquerda\n");
    movimento_rainha(casas - 1);
}

void movimento_cavalo() {
    int i, j;

    for (i = 0; i < 2; i++) {

        for (j = 0; j < 1; j++) {
            printf("Cima\n");
        }

        if (i == 1) {
            for (j = 0; j < 1; j++) {
                printf("Direita\n");
            }
            break;
        }
    }
}

int main() {

    int casas_torre = 5;
    int casas_bispo = 5;
    int casas_rainha = 8;

    printf("Movimento da Torre (5 casas para a direita):\n");
    movimento_torre(casas_torre);

    printf("\n");

    printf("Movimento do Bispo (5 casas na diagonal para cima e direita):\n");
    movimento_bispo(casas_bispo);

    printf("\n");

    printf("Movimento da Rainha (8 casas para a esquerda):\n");
    movimento_rainha(casas_rainha);

    printf("\n");

    printf("Movimento do Cavalo (2 casas para cima e 1 casa para a direita):\n");
    movimento_cavalo();

    return 0;
}
