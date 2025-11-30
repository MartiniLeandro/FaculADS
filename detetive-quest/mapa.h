#ifndef MAPA_H
#define MAPA_H

typedef struct NoMapa {
    char nome[50];
    struct NoMapa *esquerda;
    struct NoMapa *direita;
} NoMapa;

NoMapa* criar_no_mapa(char nome[]);
NoMapa* inserir_comodo(NoMapa* raiz, char nome[]);
void mostrar_mapa(NoMapa* raiz);

#endif
