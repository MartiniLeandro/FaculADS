#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_hash.h"

int hash(char chave[]) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) soma += chave[i];
    return soma % TAMANHO_TABELA;
}

void iniciar_tabela(TabelaHash* t) {
    for (int i = 0; i < TAMANHO_TABELA; i++) t->lista[i] = NULL;
}

void inserir_relacao(TabelaHash* t, char pista[], char suspeito[]) {
    int indice = hash(pista);
    NoLista* n = malloc(sizeof(NoLista));
    strcpy(n->pista, pista);
    strcpy(n->suspeito, suspeito);
    n->prox = t->lista[indice];
    t->lista[indice] = n;
}

char* buscar_suspeito(TabelaHash* t, char pista[]) {
    int indice = hash(pista);
    NoLista* atual = t->lista[indice];
    while (atual) {
        if (strcmp(atual->pista, pista) == 0) return atual->suspeito;
        atual = atual->prox;
    }
    return NULL;
}

void mostrar_relacoes(TabelaHash* t) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        NoLista* atual = t->lista[i];
        while (atual) {
            printf("Pista: %s -> Suspeito: %s\n", atual->pista, atual->suspeito);
            atual = atual->prox;
        }
    }
}
