#include "territory.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char *alloc_copy(const char *s){
    if(!s) return NULL;
    size_t n = strlen(s) + 1;
    char *p = malloc(n);
    if(!p) return NULL;
    memcpy(p, s, n);
    return p;
}

Territory *territory_create(int id, const char *name, int initial_troops){
    Territory *t = calloc(1, sizeof(Territory));
    if(!t) return NULL;
    t->id = id;
    t->name = alloc_copy(name ? name : "Territory");
    t->owner_id = -1;
    t->troops = initial_troops;
    t->neighbors = NULL;
    t->neighbor_count = 0;
    return t;
}

int territory_add_neighbor(Territory *a, Territory *b){
    if(!a || !b) return 0;
    for(int i=0;i<a->neighbor_count;i++) if(a->neighbors[i]==b) return 0;
    Territory **tmp = realloc(a->neighbors, sizeof(Territory*) * (a->neighbor_count + 1));
    if(!tmp) return 0;
    a->neighbors = tmp;
    a->neighbors[a->neighbor_count++] = b;
    return 1;
}

int territory_is_neighbor(const Territory *a, const Territory *b){
    if(!a || !b) return 0;
    for(int i=0;i<a->neighbor_count;i++) if(a->neighbors[i]==b) return 1;
    return 0;
}

void territory_print(const Territory *t){
    if(!t) return;
    printf("ID:%d Name:%s Owner:%d Troops:%d Neigh:", t->id, t->name ? t->name : "(null)", t->owner_id, t->troops);
    for(int i=0;i<t->neighbor_count;i++) printf("%d ", t->neighbors[i]->id);
    printf("\n");
}

void territory_free(Territory *t){
    if(!t) return;
    free(t->name);
    free(t->neighbors);
    free(t);
}
