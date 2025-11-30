#ifndef PISTAS_H
#define PISTAS_H

typedef struct NoPista {
    char pista[80];
    struct NoPista* esquerda;
    struct NoPista* direita;
} NoPista;

NoPista* criar_no_pista(char texto[]);
NoPista* inserir_pista(NoPista* raiz, char texto[]);
void mostrar_pistas(NoPista* raiz);
int buscar_pista(NoPista* raiz, char texto[]);

#endif
