#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"
#include "pistas.h"
#include "tabela_hash.h"

int main() {
    NoMapa* mapa = NULL;
    NoPista* pistas = NULL;
    TabelaHash tabela;

    iniciar_tabela(&tabela);

    int opcao;
    char texto[80];
    char comodo[50];
    char suspeito[50];

    while (1) {
        printf("\n1 Inserir cômodo\n2 Mostrar mapa\n3 Inserir pista\n4 Mostrar pistas\n5 Relacionar pista a suspeito\n6 Buscar suspeito por pista\n7 Mostrar relações\n8 Sair\nOpcao: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            printf("Nome do cômodo: ");
            fgets(comodo, 50, stdin);
            comodo[strcspn(comodo, "\n")] = 0;
            mapa = inserir_comodo(mapa, comodo);
        }

        else if (opcao == 2) {
            mostrar_mapa(mapa);
        }

        else if (opcao == 3) {
            printf("Digite a pista: ");
            fgets(texto, 80, stdin);
            texto[strcspn(texto, "\n")] = 0;
            pistas = inserir_pista(pistas, texto);
        }

        else if (opcao == 4) {
            mostrar_pistas(pistas);
        }

        else if (opcao == 5) {
            printf("Pista: ");
            fgets(texto, 80, stdin);
            texto[strcspn(texto, "\n")] = 0;

            printf("Suspeito: ");
            fgets(suspeito, 50, stdin);
            suspeito[strcspn(suspeito, "\n")] = 0;

            inserir_relacao(&tabela, texto, suspeito);
        }

        else if (opcao == 6) {
            printf("Pista para buscar: ");
            fgets(texto, 80, stdin);
            texto[strcspn(texto, "\n")] = 0;

            char* resp = buscar_suspeito(&tabela, texto);
            if (resp) printf("Suspeito: %s\n", resp);
            else printf("Nenhuma relação encontrada\n");
        }

        else if (opcao == 7) {
            mostrar_relacoes(&tabela);
        }

        else if (opcao == 8) {
            break;
        }
    }

    return 0;
}
