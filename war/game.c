#include "game.h"
#include "mission.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

static int default_attack(Game *g, int from_id, int to_id, int attacking_troops);

Game *game_create(void){
    Game *g = calloc(1, sizeof(Game));
    if(!g) return NULL;
    g->territories = NULL;
    g->territory_count = 0;
    g->players = NULL;
    g->player_count = 0;
    g->attack_strategy = default_attack;
    srand((unsigned)time(NULL));
    return g;
}

void game_free(Game *g){
    if(!g) return;
    for(int i=0;i<g->territory_count;i++) territory_free(g->territories[i]);
    free(g->territories);
    for(int i=0;i<g->player_count;i++) player_free(g->players[i]);
    free(g->players);
    free(g);
}

int game_add_territory(Game *g, const char *name, int initial_troops){
    if(!g) return -1;
    int id = g->territory_count;
    Territory **tmp = realloc(g->territories, sizeof(Territory*)*(g->territory_count+1));
    if(!tmp) return -1;
    g->territories = tmp;
    Territory *t = territory_create(id, name, initial_troops);
    if(!t) return -1;
    g->territories[g->territory_count++] = t;
    return id;
}

Territory *game_get_territory(Game *g, int id){
    if(!g) return NULL;
    if(id < 0 || id >= g->territory_count) return NULL;
    return g->territories[id];
}

int game_add_player(Game *g, const char *name){
    if(!g) return -1;
    int id = g->player_count;
    Player **tmp = realloc(g->players, sizeof(Player*)*(g->player_count+1));
    if(!tmp) return -1;
    g->players = tmp;
    Player *p = player_create(id, name);
    if(!p) return -1;
    g->players[g->player_count++] = p;
    return id;
}

Player *game_get_player(Game *g, int id){
    if(!g) return NULL;
    if(id < 0 || id >= g->player_count) return NULL;
    return g->players[id];
}

void game_assign_territory(Game *g, int territory_id, int player_id){
    if(!g) return;
    Territory *t = game_get_territory(g, territory_id);
    Player *p = game_get_player(g, player_id);
    if(!t || !p) return;
    if(t->owner_id != -1){
        Player *old = game_get_player(g, t->owner_id);
        if(old) player_remove_territory(old, t->id);
    }
    t->owner_id = p->id;
    player_add_territory(p, t->id);
}

void game_set_attack_strategy(Game *g, int (*strategy)(Game*,int,int,int)){
    if(!g) return;
    g->attack_strategy = strategy ? strategy : default_attack;
}

int game_attack(Game *g, int from_id, int to_id, int attacking_troops){
    if(!g) return -1;
    if(g->attack_strategy) return g->attack_strategy(g, from_id, to_id, attacking_troops);
    return -1;
}

static int default_attack(Game *g, int from_id, int to_id, int attacking_troops){
    Territory *from = game_get_territory(g, from_id);
    Territory *to = game_get_territory(g, to_id);
    if(!from || !to) return -1;
    if(from->owner_id == -1 || to->owner_id == -1) return -1;
    if(from->owner_id == to->owner_id) return -1;
    if(!territory_is_neighbor(from, to)) return -1;
    if(attacking_troops <= 0 || attacking_troops >= from->troops) return -1;
    int atk = 0;
    int def = 0;
    for(int i=0;i<attacking_troops;i++) atk += (rand()%6)+1;
    int defend_troops = to->troops > 2 ? 2 : to->troops;
    for(int i=0;i<defend_troops;i++) def += (rand()%6)+1;
    if(atk > def){
        from->troops -= attacking_troops;
        if(from->troops < 1) from->troops = 1;
        to->troops = attacking_troops;
        Player *old = game_get_player(g, to->owner_id);
        Player *att = game_get_player(g, from->owner_id);
        if(old) player_remove_territory(old, to->id);
        to->owner_id = from->owner_id;
        if(att) player_add_territory(att, to->id);
        return 1;
    } else {
        int lost = attacking_troops/2;
        if(lost < 1) lost = 1;
        from->troops -= lost;
        if(from->troops < 1) from->troops = 1;
        return 0;
    }
}

void game_print_map(const Game *g){
    if(!g) return;
    for(int i=0;i<g->territory_count;i++) territory_print(g->territories[i]);
}

void game_print_players(const Game *g){
    if(!g) return;
    for(int i=0;i<g->player_count;i++) player_print(g->players[i]);
}

int game_check_player_mission(Game *g, int player_id){
    if(!g) return 0;
    Player *p = game_get_player(g, player_id);
    if(!p) return 0;
    if(p->mission_id == 0) return 0;
    if(p->mission_id == 1) return mission_check_conquer_n(g, player_id, p->mission_param);
    if(p->mission_id == 2) return mission_check_eliminate_player(g, player_id, p->mission_param);
    return 0;
}
