#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

NoMapa* criar_no_mapa(char nome[]) {
    NoMapa* n = malloc(sizeof(NoMapa));
    strcpy(n->nome, nome);
    n->esquerda = NULL;
    n->direita = NULL;
    return n;
}

NoMapa* inserir_comodo(NoMapa* raiz, char nome[]) {
    if (!raiz) return criar_no_mapa(nome);
    if (strcmp(nome, raiz->nome) < 0) raiz->esquerda = inserir_comodo(raiz->esquerda, nome);
    else raiz->direita = inserir_comodo(raiz->direita, nome);
    return raiz;
}

void mostrar_mapa(NoMapa* raiz) {
    if (!raiz) return;
    mostrar_mapa(raiz->esquerda);
    printf("%s\n", raiz->nome);
    mostrar_mapa(raiz->direita);
}
