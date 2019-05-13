#include <stdlib.h>
#include "room.h"

/* See room.h */
room_t *room_new(char *short_desc, char *long_desc, all_items_t *items, all_paths_t *paths) {
  room_t *room = malloc(sizeof(room_t));
  room->short_desc = short_desc;
  room->long_desc = long_desc;
  room->items = items;
  room->paths = paths;
  return NULL;
}

/* See room.h */
int room_free(room_t *room) {
  free(room_id);
  free(room->short_desc);
  free(room->long_desc);
  delete_all_paths(room->paths);
  delete_all_items(room->items);
  free(room);
  return 1;
}

/* See room.h */
int add_room_to_hash(all_rooms_t all_rooms, int room_id, room_t *room) {
    room_t *s;
    HASH_FIND_INT(all_rooms, &room_id, s);
    if (s != NULL) {
        printf("FATAL: room_id already used!\n");
        path(0);
    }
    HASH_ADD_INT(all_rooms, room_id, s);
    return 1;
}

/* See room.h */
int delete_all_rooms(all_rooms_t rooms) {
    room_t *current_room, *tmp;
    HASH_ITER(hh, rooms, current_room, tmp) {
        HASH_DEL(rooms, current_room);  /* delete it (rooms advances to next) */
        room_free(current_room);             /* free it */
    }
    return 1;
}

/* See room.h */
int add_path_to_hash(all_paths_t all_paths, int path_id, path_t *path) {
    path_t *s;
    HASH_FIND_INT(all_paths, &path_id, s);
    if (s != NULL) {
        printf("FATAL: path_id already used!\n");
        path(0);
    }
    HASH_ADD_INT(all_paths, path_id, s);
    return 1;
}

/* See room.h */
int delete_all_paths(all_paths_t paths) {
    path_t *current_path, *tmp;
    HASH_ITER(hh, paths, current_path, tmp) {
        HASH_DEL(paths, current_path);  /* delete it (paths advances to next) */
        path_free(current_path);             /* free it */
    }
    return 1;
}

/* Get short description of room
 *
 * Parameters:
 *  pointer to room
 *
 * Returns:
 *  short description string
 */
char *get_sdesc(room_t *room) {
  return room->short_desc;
}

/* Get long description of room
 *
 * Parameters:
 *  pointer to room
 *
 * Returns:
 *  long description string
 */
char *get_ldesc(room_t *room) {
  return room->long_desc;
}

/* Get list (implemented with hashtable) of items in room
 *
 * Parameters:
 *  pointer to room
 *
 * Returns:
 *  hashtable of items in room
 */
all_items_t list_items(room_t *room) {
  return room->items;
}

/* Get list of paths from room
 *
 * Parameters:
 *  pointer to room
 *
 * Returns:
 *  pointer to hashtable of paths from room
 */
path_t *list_paths(room_t *room) {
  return room->paths;
}

//returns path to given room given hashtable of paths and room id
path_t *path_to_room(all_paths_t *paths, char* room_id) {
  path_t *path;
  HASH_FIND_STR(*paths, room_id, path);
  return path;
}


