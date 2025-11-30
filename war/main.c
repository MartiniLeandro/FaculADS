#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

static void flushstdin(){
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}

int main(void){
    Game *g = game_create();
    if(!g) return 1;
    char buf[256];
    while(1){
        printf("\n1 Criar territorio\n2 Conectar territorios\n3 Criar jogador\n4 Atribuir territorio\n5 Imprimir mapa\n6 Imprimir jogadores\n7 Reforcar territorio\n8 Ataque\n9 Definir missao jogador\n10 Checar missao jogador\n0 Sair\nEscolha: ");
        if(!fgets(buf, sizeof(buf), stdin)) break;
        int opt = atoi(buf);
        if(opt==0) break;
        if(opt==1){
            printf("Nome: ");
            if(!fgets(buf, sizeof(buf), stdin)) break;
            buf[strcspn(buf, "\n")] = 0;
            printf("Tropas iniciais: ");
            if(!fgets(buf+200, 56, stdin)) break;
            int t = atoi(buf+200);
            int id = game_add_territory(g, buf, t);
            printf("Territorio criado id=%d\n", id);
        } else if(opt==2){
            int a,b;
            printf("ID A: ");
            if(!fgets(buf, sizeof(buf), stdin)) break;
            a = atoi(buf);
            printf("ID B: ");
            if(!fgets(buf, sizeof(buf), stdin)) break;
            b = atoi(buf);
            Territory *ta = game_get_territory(g,a);
            Territory *tb = game_get_territory(g,b);
            if(!ta||!tb){ printf("IDs invalidos\n"); continue;}
            territory_add_neighbor(ta,tb);
            territory_add_neighbor(tb,ta);
            printf("Conectado %d<->%d\n",a,b);
        } else if(opt==3){
            printf("Nome jogador: ");
            if(!fgets(buf, sizeof(buf), stdin)) break;
            buf[strcspn(buf, "\n")] = 0;
            int pid = game_add_player(g, buf);
            printf("Jogador criado id=%d\n", pid);
        } else if(opt==4){
            int tid,pid;
            printf("ID territorio: ");
            if(!fgets(buf, sizeof(buf), stdin)) break;
            tid = atoi(buf);
            printf("ID jogador: ");
            if(!fgets(buf, sizeof(buf), stdin)) break;
            pid = atoi(buf);
            game_assign_territory(g, tid, pid);
            printf("Atribuido territorio %d a jogador %d\n", tid, pid);
        } else if(opt==5){
            game_print_map(g);
        } else if(opt==6){
            game_print_players(g);
        } else if(opt==7){
            int tid,add;
            printf("ID territorio: ");
            if(!fgets(buf, sizeof(buf), stdin)) break;
            tid = atoi(buf);
            printf("Adicionar tropas: ");
            if(!fgets(buf, sizeof(buf), stdin)) break;
            add = atoi(buf);
            Territory *t = game_get_territory(g, tid);
            if(t){ t->troops += add; printf("Territorio %d agora tem %d tropas\n", tid, t->troops); }
            else printf("Territorio invalido\n");
        } else if(opt==8){
            int from,to,atk;
            printf("Origem ID: ");
            if(!fgets(buf, sizeof(buf), stdin)) break;
            from = atoi(buf);
            printf("Destino ID: ");
            if(!fgets(buf, sizeof(buf), stdin)) break;
            to = atoi(buf);
            printf("Tropas atacantes: ");
            if(!fgets(buf, sizeof(buf), stdin)) break;
            atk = atoi(buf);
            int res = game_attack(g, from, to, atk);
            if(res==1) printf("Conquista!\n");
            else if(res==0) printf("Falha no ataque\n");
            else printf("Ataque invalido\n");
        } else if(opt==9){
            int pid;
            printf("ID jogador: ");
            if(!fgets(buf, sizeof(buf), stdin)) break;
            pid = atoi(buf);
            Player *p = game_get_player(g, pid);
            if(!p){ printf("Jogador invalido\n"); continue; }
            printf("Missao 1=conquistar N 2=eliminar jogador 0=nenhuma: ");
            if(!fgets(buf, sizeof(buf), stdin)) break;
            int m = atoi(buf);
            p->mission_id = m;
            if(m==1){
                printf("Parametro N: ");
                if(!fgets(buf, sizeof(buf), stdin)) break;
                p->mission_param = atoi(buf);
            } else if(m==2){
                printf("Parametro jogador a eliminar (id): ");
                if(!fgets(buf, sizeof(buf), stdin)) break;
                p->mission_param = atoi(buf);
            } else {
                p->mission_param = 0;
            }
            printf("Missao definida\n");
        } else if(opt==10){
            int pid;
            printf("ID jogador: ");
            if(!fgets(buf, sizeof(buf), stdin)) break;
            pid = atoi(buf);
            int ok = game_check_player_mission(g, pid);
            if(ok) printf("Jogador %d cumpriu a missao\n", pid);
            else printf("Jogador %d nao cumpriu a missao\n", pid);
        } else {
            printf("Opcao invalida\n");
        }
    }
    game_free(g);
    return 0;
}
