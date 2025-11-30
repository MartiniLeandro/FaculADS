#include "player.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char *copystr(const char *s){
    if(!s) return NULL;
    size_t n = strlen(s)+1;
    char *p = malloc(n);
    if(!p) return NULL;
    memcpy(p, s, n);
    return p;
}

Player *player_create(int id, const char *name){
    Player *p = calloc(1, sizeof(Player));
    if(!p) return NULL;
    p->id = id;
    p->name = copystr(name ? name : "Player");
    p->territory_count = 0;
    p->territory_ids = NULL;
    p->mission_id = 0;
    p->mission_param = 0;
    return p;
}

void player_add_territory(Player *p, int tid){
    if(!p) return;
    for(int i=0;i<p->territory_count;i++) if(p->territory_ids[i]==tid) return;
    int *tmp = realloc(p->territory_ids, sizeof(int)*(p->territory_count+1));
    if(!tmp) return;
    p->territory_ids = tmp;
    p->territory_ids[p->territory_count++] = tid;
}

void player_remove_territory(Player *p, int tid){
    if(!p) return;
    int idx = -1;
    for(int i=0;i<p->territory_count;i++) if(p->territory_ids[i]==tid){ idx = i; break; }
    if(idx==-1) return;
    for(int i=idx;i<p->territory_count-1;i++) p->territory_ids[i]=p->territory_ids[i+1];
    p->territory_count--;
    if(p->territory_count==0){ free(p->territory_ids); p->territory_ids = NULL; }
    else {
        int *tmp = realloc(p->territory_ids, sizeof(int)*p->territory_count);
        if(tmp) p->territory_ids = tmp;
    }
}

int player_has_territory(const Player *p, int tid){
    if(!p) return 0;
    for(int i=0;i<p->territory_count;i++) if(p->territory_ids[i]==tid) return 1;
    return 0;
}

void player_print(const Player *p){
    if(!p) return;
    printf("Player %d Name:%s Territories:%d Mission:%d Param:%d\n", p->id, p->name ? p->name : "(null)", p->territory_count, p->mission_id, p->mission_param);
    printf("IDs: ");
    for(int i=0;i<p->territory_count;i++) printf("%d ", p->territory_ids[i]);
    printf("\n");
}

void player_free(Player *p){
    if(!p) return;
    free(p->name);
    free(p->territory_ids);
    free(p);
}
