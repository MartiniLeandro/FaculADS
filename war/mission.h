#ifndef MISSION_H
#define MISSION_H

typedef struct Game Game;

typedef int (*MissionCheck)(Game *g, int player_id, int param);

int mission_check_conquer_n(Game *g, int player_id, int param);
int mission_check_eliminate_player(Game *g, int player_id, int param);

#endif
