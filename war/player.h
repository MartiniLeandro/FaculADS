#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player Player;

struct Player {
    int id;
    char *name;
    int territory_count;
    int *territory_ids;
    int mission_id;
    int mission_param;
};

Player *player_create(int id, const char *name);
void player_add_territory(Player *p, int tid);
void player_remove_territory(Player *p, int tid);
int player_has_territory(const Player *p, int tid);
void player_print(const Player *p);
void player_free(Player *p);

#endif
