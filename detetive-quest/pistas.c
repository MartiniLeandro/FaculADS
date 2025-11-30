#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pistas.h"

NoPista* criar_no_pista(char texto[]) {
    NoPista* n = malloc(sizeof(NoPista));
    strcpy(n->pista, texto);
    n->esquerda = NULL;
    n->direita = NULL;
    return n;
}

NoPista* inserir_pista(NoPista* raiz, char texto[]) {
    if (!raiz) return criar_no_pista(texto);
    if (strcmp(texto, raiz->pista) < 0) raiz->esquerda = inserir_pista(raiz->esquerda, texto);
    else raiz->direita = inserir_pista(raiz->direita, texto);
    return raiz;
}

void mostrar_pistas(NoPista* raiz) {
    if (!raiz) return;
    mostrar_pistas(raiz->esquerda);
    printf("%s\n", raiz->pista);
    mostrar_pistas(raiz->direita);
}

int buscar_pista(NoPista* raiz, char texto[]) {
    if (!raiz) return 0;
    int cmp = strcmp(texto, raiz->pista);
    if (cmp == 0) return 1;
    if (cmp < 0) return buscar_pista(raiz->esquerda, texto);
    return buscar_pista(raiz->direita, texto);
}
