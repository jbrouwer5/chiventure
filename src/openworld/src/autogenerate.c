/* Team RPG-Openworld
*
* autogenerate.c: This file. Function definitions of the functions
* specified in chiventure/include/autogenerate.h
*
* Room module that autogenerates string of rooms connected via paths when
* a "dead-end" room is entered
*
* See chiventure/include/autogenerate.h header file to see function
* prototypes and purposes
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common/utlist.h"
#include "common/uthash.h"
#include "game-state/room.h"
#include "openworld/autogenerate.h"
#include "openworld/gen_structs.h"
#include "openworld/default_rooms.h"

/*      HELPER FUNCTION TO SPLICE INTEGER FROM END
*       source: stackoverflow.com
 *      Remove given section from string. Negative len means remove
 *      everything up to the end.
 */
char *str_slice(char str[], int slice_from, int slice_to)
{
    // if a string is empty, returns nothing
    if (str[0] == '\0')
        return NULL;

    char *buffer;
    size_t str_len, buffer_len;

    // for negative indexes "slice_from" must be less "slice_to"
    if (slice_to < 0 && slice_from < slice_to) {
        str_len = strlen(str);

        // if "slice_to" goes beyond permissible limits
        if (abs(slice_to) > str_len - 1)
            return NULL;

        // if "slice_from" goes beyond permissible limits
        if (abs(slice_from) > str_len)
            slice_from = (-1) * str_len;

        buffer_len = slice_to - slice_from;
        str += (str_len + slice_from);

        // for positive indexes "slice_from" must be more "slice_to"
    } else if (slice_from >= 0 && slice_to > slice_from) {
        str_len = strlen(str);

        // if "slice_from" goes beyond permissible limits
        if (slice_from > str_len - 1)
            return NULL;

        buffer_len = slice_to - slice_from;
        str += slice_from;

        // otherwise, returns NULL
    } else
        return NULL;

    buffer = calloc(buffer_len, sizeof(char));
    strncpy(buffer, str, buffer_len);
    return buffer;
}

/* See autogenerate.h */
bool path_exists_in_dir(room_t *r, char *direction)
{
    // No paths case
    if (r->paths == NULL) {
        return false;
    }

    path_hash_t *current, *tmp;
    HASH_ITER(hh, r->paths, current, tmp) {
        // If the path has the given direction, return true
        if (strcmp(current->direction, direction) == 0) {
            return true;
        }
    }
    return false;
}

/* See autogenerate.h */
room_t* roomspec_to_room(roomspec_t *roomspec, char *room_id)
{
    room_t *res = room_new(room_id, roomspec->short_desc, roomspec->long_desc);

    item_hash_t *current, *tmp;
    HASH_ITER(hh, roomspec->items, current, tmp) {
        assert(SUCCESS == copy_item_to_hash(&res->items, roomspec->items, current->item_id));
    }

    roomspec->num_built++;
    res->paths = NULL;

    return res;
}

/* See autogenerate.h */
int room_generate(game_t *game, gencontext_t *context, char *room_id)
{
    // 2D array of possible directions
    char directions[4][6];
    strncpy(directions[0], "NORTH", 6);
    strncpy(directions[1], "EAST", 5);
    strncpy(directions[2], "SOUTH", 6);
    strncpy(directions[3], "WEST", 5);

    // Random initial direction
    unsigned int first_direction = rand() % 4;

    // Bump directions index by 1 if a path with that direction already exists
    unsigned int bump;
    for (bump = 0; bump < 4; bump++) {
        // Forwards direction + bump
        int forwards = (first_direction + bump) % 4;
        // If path in that direction exists in game->curr_room, bump. Else, create the path
        if (path_exists_in_dir(game->curr_room, directions[forwards])) {
            // Bump if the room already has a path in the given direction
            continue;
        }
        char *copy = NULL, *remainder = NULL, *name = NULL;
        copy = str_slice(room_id, 0, strlen(room_id) - 2);
        remainder = str_slice(room_id, strlen(room_id) - 2, strlen(room_id));

        roomspec_t *hash = make_default_room(copy, NULL, NULL);
        context->speclist = speclist_from_hash(hash);
        // Specify roomspec content from speclist
        roomspec_t *r = random_room_lookup(context->speclist);

        // Adds one generated room from the head of context->speclist only
        room_t *new_room = roomspec_to_room(r, room_id);
        assert(SUCCESS == add_room_to_game(game, new_room));

        // Path to the generated room
        path_t* path_to_room = path_new(new_room, directions[forwards]);
        assert(SUCCESS == add_path_to_room(game->curr_room, path_to_room));

        // Path for the opposite direction
        unsigned int backwards = (forwards + 2) % 4;
        path_t* path_to_room2 = path_new(game->curr_room, directions[backwards]);
        assert(SUCCESS == add_path_to_room(new_room, path_to_room));

        return SUCCESS; // Room was generated
    }

    return FAILURE; // Room was not generated
}

/* See autogenerate.h */
int multi_room_generate(game_t *game, gencontext_t *context, char *room_id)
{
    /* If game->curr_room is not a dead end or there are no roomspec_t elements
    * in context->speclist, then do not autogenerate */
    if (context->speclist == NULL) {
        return FAILURE;
    }

    // Iterate through the speclist field, generating and adding rooms for each
    speclist_t *tmp;
    char buff[MAX_SDESC_LEN + 1] = { 0 }; // Will hold unique room_id
    DL_FOREACH(context->speclist, tmp) {
        // Append num_built value to the roomspec's room_name
        snprintf(buff, MAX_SDESC_LEN, "%s%d", tmp->spec->room_name, tmp->spec->num_built);
        printf("PASSED HERE\n");
        // Increments tmp->spec->num_built
        room_generate(game, context, buff);
        printf("generated a room\n");
    }

    return SUCCESS;
}

/* See autogenerate.h */
speclist_t *speclist_from_hash(roomspec_t *hash)
{
    if (hash == NULL) {
        return NULL;
    } else {
        speclist_t *spec = NULL;
        roomspec_t *current_room = NULL, *tmp = NULL;
        HASH_ITER(hh, hash, current_room, tmp) {
            speclist_t *s = speclist_new(current_room);
            DL_APPEND(spec, s);
        }
        return spec;
    }
}

/* See autogenerate.h */
roomspec_t *random_room_lookup(speclist_t *spec)
{
    int count;
    speclist_t *tmp = NULL, *random = NULL;

    DL_COUNT(spec, tmp, count);
    int idx = rand() % count, i = 0;

    DL_FOREACH(spec, tmp) {
        if (i == idx) {
            item_hash_t *items = random_items(tmp->spec);
            tmp->spec->items = items;
            return tmp->spec;
        }
        i++;
    }
    return NULL;
}


/* See autogenerate.h */
item_hash_t *random_items(roomspec_t *room)
{
    if (room == NULL) return NULL;
    item_hash_t *r_items = room->items;
    int count = HASH_COUNT(room->items);
    int num_items = rand() % 6, num_iters = rand() % count;
    item_hash_t *items = NULL;
    for (int i = 0; i < num_items; i++) {
        int rc = random_item_lookup(&items, room->items, num_iters);
    }
    return items;
}

/* See autogenerate.h */
int random_item_lookup(item_hash_t **dst, item_hash_t *src, int num_iters)
{
    item_hash_t *current = NULL, *tmp = NULL;
    int i = 0;
    HASH_ITER(hh, src, current, tmp) {
        if (i == num_iters) {
            copy_item_to_hash(dst, src, tmp->item_id);
            return SUCCESS;
        }
        i++;
    }

    return FAILURE;
}
                                                                                

