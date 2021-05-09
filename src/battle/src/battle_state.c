#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "battle/battle_state.h"
#include "common/utlist.h"

/* See battle_state.h */
combatant_t *combatant_new(char *name, bool is_friendly, class_t *class, stat_t *stats,
    move_t *moves, item_t *items, difficulty_t ai)
{
    combatant_t *c;
    int rc;
    c = calloc(1, sizeof(combatant_t));

    if(c == NULL)
    {
        fprintf(stderr, "Could not allocate memory for combatant\n");
        return NULL;
    }

    rc = combatant_init(c, name, is_friendly, class, stats, moves, items, ai);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Could not initialize character\n");
        return NULL;
    }

    return c;
}

/* See battle_state.h */
int combatant_init(combatant_t *c, char *name, bool is_friendly, class_t *class, stat_t *stats,
    move_t *moves, item_t *items, difficulty_t ai)
{
    assert(c != NULL);

    c->name = calloc(MAX_NAME_LEN + 1, sizeof(char));
    strncpy(c->name, name, MAX_NAME_LEN);
    c->is_friendly= is_friendly;
    c->class = class;
    c->stats = stats;
    c->moves = moves;
    c->items = items;
    c->ai = ai;
    c->next = NULL;
    c->prev = NULL;

    return SUCCESS;
}

/* battle_state.h */
int combatant_free(combatant_t *c)
{
    if (c == NULL)
    {
        return SUCCESS;
    }

    if (c->name)
    {
        free(c->name);
    }

    if (c->stats)
    {
        free(c->stats);
    }

    if (c->class)
    {
        class_free(c->class);
    }

    move_t *move_elt, *move_tmp;
    DL_FOREACH_SAFE(c->moves, move_elt, move_tmp)
    {
        DL_DELETE(c->moves, move_elt);
        free(move_elt);
    }

    item_t *item_elt, *item_tmp;
    DL_FOREACH_SAFE(c->items, item_elt, item_tmp)
    {
        DL_DELETE(c->items, item_elt);
        free(item_elt);
    }

    free(c);

    return SUCCESS;
}

/* See battle_state.h */
int combatant_free_all(combatant_t *c)
{
    combatant_t *elt, *tmp;
    DL_FOREACH_SAFE(c, elt, tmp)
    {
        DL_DELETE(c, elt);
        combatant_free(elt);
    }
    return SUCCESS;
}

/* See battle_state.h */
battle_t *battle_new(combatant_t *player, combatant_t *enemy,
    environment_t env, turn_t turn)
{
    battle_t *b;
    int rc;
    b = calloc(1, sizeof(battle_t));

    if(b == NULL)
    {
        fprintf(stderr, "Could not allocate memory for battle struct\n");
        return NULL;
    }

    rc = battle_init(b, player, enemy, env, turn);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Could not initialize battle struct\n");
        return NULL;
    }

    return b;
}

/* See battle_state.h */
int battle_init(battle_t *b, combatant_t *player, combatant_t *enemy,
    environment_t env, turn_t turn)
{
    assert(b != NULL);

    b->player = player;
    b->enemy = enemy;
    b->environment = env;
    b->turn = turn;

    return SUCCESS;
}

/* See battle_state.h */
int battle_free(battle_t *b)
{
    assert(b != NULL);

    combatant_free_all(b->player);
    combatant_free_all(b->enemy);

    free(b);

    return SUCCESS;
}

/* See battle_state.h */
stat_changes_t *stat_changes_new(){
    stat_changes_t* sc;
    int rc;

    sc = calloc(1, sizeof(stat_changes_t));

    if(sc == NULL)
    {
        fprintf(stderr, "Could not allocate memory for stat changes struct\n");
        return NULL;
    }

    rc = stat_changes_init(sc);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Could not initialize stat changes struct\n");
        return NULL;
    }

    return sc;    
}

/* See battle_state.h */
int stat_changes_init(stat_changes_t *sc){
    assert(sc != NULL);

    sc->speed = 0;
    sc->defense = 0;
    sc->strength = 0;
    sc->dexterity = 0;
    sc->hp = 0;
    sc->max_hp = 0;
    sc->turns_left = -1;
    sc->next = NULL;
    sc->prev = NULL;

    return SUCCESS;
}

/* See battle_state.h */
int stat_changes_free_node(stat_changes_t *sc){
    assert(sc != NULL);
        
    free(sc);

    return SUCCESS;
}

/* See battle_state.h */
int stat_changes_free_all(stat_changes_t *sc){
    stat_changes_t *current = sc;
    stat_changes_t *next = NULL;

    while(current->next != NULL){
        next = current->next;
        free(current);
        current = next;
    }

    return SUCCESS;
}

/* As somewhat higher level functions, do these still belong here or should I move them? */

/* See battle_state.h */
int stat_changes_add_node(stat_changes_t *sc){
    stat_changes_t *current = sc;
    stat_changes_t *new_node = stat_changes_new();

    while(current->next != NULL){
        curent = current->next;
    }

    current->next = new_node;

    return SUCCESS;
}

/* See battle_state.h */
int stat_changes_remove_node(stat_changes_t *sc){
    sc->prev->next = sc->next;

    if(sc->next != NULL){
        sc->next->prev = sc->prev;
    }

    int rc = stat_changes_free_node(sc);
    if(rc != SUCCESS)
    {
        fprintf(stderr, "Could not free stat changes node\n");
        return NULL;
    }

    return SUCCESS;
}

/* See battle_state.h */
int stat_changes_turn_increment(stat_changes_t *sc, combatant_t *c){
    stat_changes_t *current = sc->next;
    stat_changes_t *remove = sc->next;

    while(current != NULL){
        current->turns_left -= 1;
        
        
        if(current->turns_left == 0){
            remove = current;
            current = current->next;

            stat_changes_undo(remove, c);
            stat_changes_remove_node(remove);
        }else{
            current = current->next;
        }
    }

    return SUCCESS;
}

/* See battle_state.h */
int stat_changes_undo(stat_changes_t *sc, combatant_t *c)
{
    c->stats->hp -= sc->hp;
    c->stats->max_hp -= sc->max_hp;
    c->stats->strength -= sc->strength;
    c->stats->defense -= sc->defense;
    c->stats->speed -= sc->speed;
    c->stats->dexterity -= sc->dexterity;

    return SUCCESS;
}

/* See battle_state.h */
int stat_changes_add_item_node(stat_changes_t *sc, item_t *item)
{
    stat_changes_add_node(sc);

    stat_changes_t *current = sc;

    while(sc->next != NULL){
        sc = sc->next;
    }

    sc->hp += item->hp;
    sc->strength += item->attack;
    sc->defense += item->defense;

    return SUCCESS;
}