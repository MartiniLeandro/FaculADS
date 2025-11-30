#include "mission.h"
#include "game.h"

int mission_check_conquer_n(Game *g, int player_id, int param){
    if(!g) return 0;
    if(player_id < 0) return 0;
    Game *gg = g;
    int count = 0;
    for(int i=0;i<gg->territory_count;i++) if(gg->territories[i]->owner_id == player_id) count++;
    return count >= param;
}

int mission_check_eliminate_player(Game *g, int player_id, int param){
    if(!g) return 0;
    if(param < 0) return 0;
    for(int i=0;i<g->player_count;i++) if(g->players[i]->id == param) {
        if(g->players[i]->territory_count == 0) return 1;
        else return 0;
    }
    return 0;
}
