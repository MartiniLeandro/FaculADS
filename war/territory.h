#ifndef TERRITORY_H
#define TERRITORY_H

typedef struct Territory Territory;

struct Territory {
    int id;
    char *name;
    int owner_id;
    int troops;
    Territory **neighbors;
    int neighbor_count;
};

Territory *territory_create(int id, const char *name, int initial_troops);
int territory_add_neighbor(Territory *a, Territory *b);
int territory_is_neighbor(const Territory *a, const Territory *b);
void territory_print(const Territory *t);
void territory_free(Territory *t);

#endif
