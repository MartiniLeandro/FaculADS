#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#define TAMANHO_TABELA 20

typedef struct NoLista {
    char pista[80];
    char suspeito[50];
    struct NoLista* prox;
} NoLista;

typedef struct {
    NoLista* lista[TAMANHO_TABELA];
} TabelaHash;

void iniciar_tabela(TabelaHash* t);
void inserir_relacao(TabelaHash* t, char pista[], char suspeito[]);
char* buscar_suspeito(TabelaHash* t, char pista[]);
void mostrar_relacoes(TabelaHash* t);

#endif
