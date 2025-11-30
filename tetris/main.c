#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

int main(void){
    GameState *g = game_create();
    char buf[128];
    game_fill_random(g, 5);
    while(1){
        printf("\n1 Mostrar estruturas\n2 Gerar N futuras\n3 Jogar proxima (consumir)\n4 Reservar proxima (mover para pilha)\n5 Recuperar reserva (mover da pilha para frente)\n6 Mostrar proxima\n0 Sair\nEscolha: ");
        if(!fgets(buf, sizeof(buf), stdin)) break;
        int opt = atoi(buf);
        if(opt==0) break;
        if(opt==1) game_print(g);
        else if(opt==2){
            printf("N: ");
            if(!fgets(buf, sizeof(buf), stdin)) break;
            int n = atoi(buf);
            game_fill_random(g, n);
            printf("Gerado\n");
        } else if(opt==3){
            PieceType p;
            if(game_next_piece(g, &p)) printf("Peca jogada: %s\n", piece_name(p));
            else printf("Fila vazia\n");
        } else if(opt==4){
            if(game_reserve_top(g)) printf("Reservado\n");
            else printf("Falha ao reservar\n");
        } else if(opt==5){
            if(game_retrieve_reserve(g)) printf("Recuperado para frente\n");
            else printf("Nada na pilha\n");
        } else if(opt==6){
            PieceType p;
            if(queue_peek(g->future, &p)) printf("Proxima: %s\n", piece_name(p));
            else printf("Fila vazia\n");
        } else {
            printf("Opcao invalida\n");
        }
    }
    game_free(g);
    return 0;
}
