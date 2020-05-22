#ifndef _NPC_H
#define _NPC_H

#include "game_state_common.h"
#include "item.h"
#include "dialogue.h"
#include "room.h"

/* A non-playable character in game */
typedef struct npc 
{
    /* hh is used for hashtable, as provided in uthash.h */
    UT_hash_handle hh;
    char *npc_id;
    int health;
    convo_t *dialogue; // placeholder for incoming dialogue module
    item_hash_t *inventory;
    npc_mov_t *movement;
} npc_t;

/* This typedef is to distinguish between npc_t pointers which are
* used to point to the npc_t structs in the traditional sense,
* and those which are used to hash npc_t structs with the
* UTHASH macros as specified in src/common/include */
 typedef struct npc npc_hash_t;


/* Struct for adding npcs to rooms */
typedef struct npcs_in_room {
    /* hh is used for hashtable, as provided in uthash.h */
    UT_hash_handle hh;
    char *room_id;
    npc_hash_t *npc_list; //hash table storing the npcs that are in the room
    int num_of_npcs; //number of npcs in the room
} npcs_in_room_t;

typedef struct npcs_in_room npcs_in_room_hash_t;


/* the hash table that holds the time that the npc should be staying in each room */
typedef struct time_in_room {
    UT_hash_handle hh;
    char *room_id;
    int sec;
} time_in_room_t;

/* this is to make the struct hashable */
typedef struct time_in_room time_in_room_hash_t;

/* struct for the definite path movement for npcs 
 * (when a path is defined - when the NPC has a role to play)
 */
typedef struct mov_def {
    path_llist_t *npc_path;
} mov_def_t;

/* the struct for the indefinite path movement for npcs 
 * (when the NPC is meant to move through the world without an interactive purpose,
 *     and only to improve authenticity and user experience)
 */
typedef struct mov_indef {
    path_llist_t *npc_path;
    time_in_room_hash_t *room_time;
} mov_indef_t;


/* the union that holds either the definite or indefinite movement */
typedef union npc_mov_types {
    mov_def_t *mov_def;
    mov_indef_t *mov_indef;
} npc_mov_types_u;

typedef enum mov_type {
   MOV_DEF, MOV_INDEF
} mov_type_e;


/* the main struct that deals with the movement of an npc */
typedef struct npc_mov {
    char *npc_id;
    npc_mov_types_u *npc_mov_type;
    mov_type_e mov_type; //an enum saying which type of movement the npc is doing, this is purely to simplify the implementation
    char *track;
} npc_mov_t;


/*
 * create llist for all the 1-1 paths for a single npc
 * path reversal
 * time in a room
 * types of npc movement
 */

/*
 * Initializes an npc with given health.
 *
 * Parameters:
 *  npc: an npc; must point to already allocated memory
 *  health: the starting health of the npc
 *  npc_id: string referring to npc id; passed implicitly
            from npc_new 
 *  dialogue: pointer to a convo struct for the npc
 *   // placeholder for incoming dialogue module
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int npc_init(npc_t *npc, char *npc_id, int health, convo_t *dialogue);


/*
 * Initializes the struct that holds the npcs inside a certain room
 *
 * Parameters:
 *  npcs_in_room: the npcs in a certain room; must point to already allocated memory
 *  room_id: the id of the room you are referring to
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int npcs_in_room_init(npcs_in_room_t *npcs_in_room, char* room_id);


/*
 * Allocates a new npc in the heap.
 *
 * Parameters:
 *  npc_id: the unique string ID of the npc
 *  health: the starting health of the npc
 *  dialogue: pointer to convo struct for the npc
 *   // placeholder for incoming dialogue module
 *
 * Returns:
 *  pointer to allocated npc
 */
 npc_t *npc_new(char *npc_id, int health, convo_t *dialogue);


/*
 * Allocates a new npcs_in_room struct in the heap
 *
 * Parameters:
 *  room_id: the unique id of the room
 *
 * Returns:
 *  pointer to allocated npcs_in_room struct
 */
 npcs_in_room_t *npcs_in_room_new(char* room_id);


/*
 * Frees resources associated with an npc.
 *
 * Parameters:
 *  npc: the npc to be freed
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occurs.
 */
int npc_free(npc_t *npc);


/*
 * Frees resources associated with an npcs_in_room struct
 *
 * Parameters:
 * npcs_in_room: the npcs_in_room struct to be freed
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occurs.
 */
int npcs_in_room_free(npcs_in_roomt_t *npcs_in_room);


/*
 * Returns the health of an npc.
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  int, the npc's health
 */
int get_npc_health(npc_t *npc);


/*
 * Returns the number of npcs in a room
 *
 * Parameters:
 *  npcs_in_room: the struct holding the npcs in the room
 *
 * Returns:
 *  int, the number of npcs in the room
 */
int get_num_of_npcs(npcs_in_room_t *npcs_in_room);

/*
 * Changes the health of the npc. 
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  int, updated health
 */
int change_npc_health(npc_t *npc, int change, int max);


/*
 * Returns the inventory list
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  hashtable of items, the inventory
 */
item_hash_t* get_npc_inventory(npc_t *npc);


/* Adds an item to the given npc
 *
 * Parameters:
 *  npc struct
 *  item struct
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occured.
 */
int add_item_to_npc(npc_t *npc, item_t *item);


/*
 * Function to get a linked list (utlist) of all the items in the player's inventory
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  linked list of pointers to items (the head element)
 */
item_list_t *get_all_items_in_inv_npc(npc_t *npc);


/* Adds an npc to the given npcs_in_room
 *
 * Parameters:
 *  npcs_in_room_t: pointer to the npcs_in_room struct
 *  npc_t: pointer to an npc
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occured.
 */
int add_npc_to_room(npcs_in_room_t *npcs_in_room, npc_t *npc);

/* extend_path_def()
 * adds a room to the path that the npc will travel through, ONLY when the npc is has a definite path
 * this essentially changes the destination point of the path
 * returns SUCCESS or FAILURE
 */
int extend_path_def(npc_mov_t *npc_mov, room_t *room_to_add);

/* extend_path_indef()
 * adds a room to the path that the npc will travel through, ONLY when the npc is has a indefinite path
 * returns SUCCESS or FAILURE
 */
int extend_path_indef(npc_mov_t *npc_mov, room_t *room_to_add, int time);

/* reverse_path()
 * reverses the path, so that the npc goes back to where it started
 * returns SUCCESS or FAILURE
 */
int reverse_path(npt_mov_t  *npc_mov);

/* change_time_in_room()
 * changes the time spent in a certain room by and npc, ONLY Possible when the npc has an indeinfite path
 * returns SUCCESS or FAILURE
 */
int change_time_in_room(npc_mov_t  *npc_mov, room_t *room_to_change, int time);

/* track_room()
 * returns the room_id of the room that the npc is currently in
 */
char* track_room(npc_mov_t *npc_mov);

/* auto_gen_movement()
 * automatically allows npcs to randomly move through adjacent rooms,
 * while spending an arbitrary time in each room
 */
npc_mov_t *auto_gen_movement(npc_t *npc, room_t *starting_room);

#endif