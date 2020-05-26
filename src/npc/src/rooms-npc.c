#include "npc/rooms-npc.h"
#include "common-item.h"

/* See rooms-npc.h */
int npcs_in_room_init(npcs_in_room_t *npcs_in_room, char* room_id,
                      char* room_name)
{
    assert(npcs_in_room != NULL);

    strncpy(npcs_in_room->room_name,room_name,strlen(room_name)+1);
    npcs_in_room->room_id = room_id;
    npcs_in_room->npc_list = NULL;
    npcs_in_room->num_of_npcs = 0;

    return SUCCESS;
}


/* See rooms-npc.h */
int npc_mov_init(npc_mov_t *npc_mov, char* npc_id, npc_mov_type_e mov_type,
                char* room_id) {
    assert(npc_mov != NULL);

    strncpy(npc_mov->npc_id,npc_id,strlen(npc_id)+1);
    npc_mov->mov_type = mov_type;
    strncpy(npc_mov->track,room->room_id,strlen(npc_id)+1);
    
    if (mov_type == MOV_DEF)
    {
        LL_APPEND(npc_mov->npc_mov_type->mov_def->npc_path,room);
    }
    else if (mov_type == MOV_INDEF )
    {
        LL_APPEND(npc_mov->npc_mov_type->mov_indef->npc_path,room);
        npc_mov->npc_mov_type->mov_indef->time_in_room = NULL;
    }

    return SUCCESS;
}


/* See rooms-npc.h */
npcs_in_room_t *npcs_in_room_new(long room_id, char* room_name)
 {
    npcs_in_room_t *npcs_in_room;
    npcs_in_room = malloc(sizeof(npcs_in_room_t));
    
    int check = npcs_in_room_init(npcs_in_room, room_id);

    if (npcs_in_room == NULL || npcs_in_room->room_id == 0 || check != SUCCESS)
    {
        return NULL;
    }

    return npcs_in_room;
 }

/* See rooms-npc.h */
npc_mov_t* npc_mov_new(char* npc_id, npc_mov_type_e mov_type, room_t* room) {
    npc_mot_t *npc_mov;
    npc_mov = malloc(sizeof(npc_mov_t));

    if (npc_mov == NULL || npc_mov->room_id == NULL || check != SUCCESS)
    {
        return NULL;
    }
    return npc_mov;
}


/* See rooms-npc.h */
int npcs_in_room_free(npcs_in_roomt_t *npcs_in_room)
{
    assert(npcs_in_room != NULL);

    free(npcs_in_room->room_id);
    free(npcs_in_room->room_name);
    free(npcs_in_room->npc_list);
    free(npcs_in_room->num_of_npcs);
    free(npcs_in_room);
    return SUCCESS;
}


/* See rooms-npc.h */
int npc_mov_free(npc_mov_t *npc_mov) {

    assert(npc_mov != NULL);

    free(npc_mov->npc_mov_type->mov_def);
    free(npc_mov->track);
    free(npc_mov->npc_id);
    free(npc_mov);
}


/* See rooms-npc.h */
int npcs_in_room_get_number(npcs_in_room_t *npcs_in_room)
{
    return npcs_in_room->num_of_npcs;
}


/* See rooms-npc.h */
int add_npc_to_room(npcs_in_room_t *npcs_in_room, npc_t *npc)
{
    npc_t *check;
    HASH_FIND(hh, npcs_in_room->npc_list, npc->npc_id, strlen(npc->npc_id),
             check);
 
    if (check != NULL)
    {
        return FAILURE; //this npc is already in the room
    }
    HASH_ADD_KEYPTR(hh, npcs_in_room->npc_list, npc->npc_id,
                    strlen(npc->npc_id), npc);
    npcs_in_room->num_of_npcs++;

    return SUCCESS;
}

/* See rooms-npc.h */
int register_time_in_room(npc_mov_t *npc_mov, room_t *room, int time) {
    assert(room != NULL);
    
    time_in_room_t *return_time;
    HASH_FIND(hh, npc_mov->npc_mov_type->mov_indef->room_time,
                &room->room_id, strlen(room->room_id), return_time);

    time_in_room_t *new_time_in_room;
    new_time_in_room = malloc(sizeof(time_in_room_t));
    strcpy(new_time_in_room->room_id, room->room_id, strlen(room->room_id)+1); 
    time_in_rooom->sec = time;

   if (return_time != NULL)
   {
      
       HASH_REPLACE(hh, npc_mov->npc_mov_type->mov_indef->room_time,
                    room_id, strlen(room->room_id), new_time_in_room, 
                    return_time);
   }
   else
   {
       HASH_ADD(hh, npc_mov->npc_mov_type->mov_indef->room_time, room_id,
                strlen(room->room_id), new_time_in_room);
   }
   
   return SUCCESS;
}


/* See rooms-npc.h */
int extend_path_def(npc_mov_t *npc_mov, room_t *room_to_add) {
    room_list_t *def_path = npc_mov->npc_mov_type->mov_def->npc_path;
    
    assert(room_to_add != NULL);
    
    LL_APPEND(def_path, room_to_add);

    return SUCCESS;
}  


/* See rooms-npc.h */
int extend_path_indef(npc_mov_t *npc_mov, room_t *room_to_add, int time) {
    room_list_t *indef_path = npc_mov->npc_mov_type->mov_indef->npc_path;
   
    assert(room_to_add != NULL);

    LL_APPEND(indef_path, room_to_add);

    int check = register_time_in_room(npc_mov, room, time);

    if (check != SUCCESS)
        return FAILURE;
    else
        return SUCCESS;
}


/* See rooms-npc.h */
char* track_room(npc_mov_t *npc_mov) {
    return npc_mov->track;
}


/* See rooms-npc.h */
int reverse_path(npc_mov_t *npc) {
    int type = npc_mov->mov_type;

    if (type != 1)
        return FAILURE:
    else
    {
        room_list_t *reversed_path = malloc(sizeof(room_list_t));
        room_list_t *def_path = npc_mov->npc_mov_type->mov_def->npc_path;
        room_t *tmp;
        LL_FOREACH(def_path, tmp) {
            LL_PREPEND(reverse_path, tmp);
        }
        free(def_path);
        npc_mov->mov_type->mov_def->mov_path = reversed_path;
    }
}