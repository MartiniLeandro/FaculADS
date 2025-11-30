#ifndef GAME_H
#define GAME_H

#include "territory.h"
#include "player.h"

typedef struct Game {
    Territory **territories;
    int territory_count;
    Player **players;
    int player_count;
    int (*attack_strategy)(struct Game*, int, int, int);
} Game;

Game *game_create(void);
void game_free(Game *g);
int game_add_territory(Game *g, const char *name, int initial_troops);
Territory *game_get_territory(Game *g, int id);
int game_add_player(Game *g, const char *name);
Player *game_get_player(Game *g, int id);
void game_assign_territory(Game *g, int territory_id, int player_id);
int game_attack(Game *g, int from_id, int to_id, int attacking_troops);
void game_set_attack_strategy(Game *g, int (*strategy)(Game*,int,int,int));
void game_print_map(const Game *g);
void game_print_players(const Game *g);
int game_check_player_mission(Game *g, int player_id);

#endif
