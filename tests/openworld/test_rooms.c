#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/openworld/sample_rooms.h"

/* Tests the functions in sample_rooms.h */

Test(room, get_allowed_defn){
	roomspec_t **rooms = get_allowed_rooms("school", NULL, NULL);
	
	cr_assert_not_null(rooms, "get_allowed_rooms failed");

	cr_assert_str_eq(rooms[0]->room_name, "cafeteria",
		"get_allowed_rooms failed");
	cr_assert_str_eq(rooms[1]->room_name, "classroom",
		"get_allowed_rooms failed");
	cr_assert_str_eq(rooms[2]->room_name, "closet",
		"get_allowed_rooms failed");
	cr_assert_str_eq(rooms[3]->room_name, "hallway",
		"get_alowed_rooms failed");
	cr_assert_str_eq(rooms[4]->room_name, "library",
		"get_alllowed_rooms failed");
}

Test(room, get_allowed_undef_empty) {
	roomspec_t **rooms = get_allowed_rooms("pharmacy", NULL, NULL);

	cr_assert_not_null(rooms, "get_allowed_rooms failed");
	cr_assert_str_eq(rooms[0]->room_name, "pharmacy", 
		"get_allowed_rooms failed");
	cr_assert_null(rooms[0]->short_desc,
		"get_allowed_rooms failed");
	cr_assert_null(rooms[0]->long_desc,
		"get_allowed_rooms failed");
}

Test(room, get_allowed_undef_bogus) {
	roomspec_t **rooms = get_allowed_rooms("pharmacy", "short bogus",
		"long bogus");

	cr_assert_not_null(rooms, "get_allowed_rooms failed");
	cr_assert_str_eq(rooms[0]->room_name, "pharmacy",
		"get_allowed_rooms failed");
	cr_assert_str_eq(rooms[0]->short_desc, "short bogus",
		"get_allowed_rooms failed");
	cr_assert_str_eq(rooms[0]->long_desc, "long bogus",
		"get_allowed_rooms failed");
}

/* testing make_default_room for defined bucket, NULL sh_desc, l_desc*/
Test(room, make_default_defn){
	roomspec_t *hash = make_default_room("school", NULL, NULL);
	cr_assert_not_null(hash, "make_default_room failed");

	printf(hash->room_name);
	printf(hash->items->item_id);
	/*
	cr_assert_str_eq(hash->room_name, "cafeteria",
		"get_allowed_rooms failed");
	cr_assert_str_eq(hash->, "cafeteria",
		"get_allowed_rooms failed");
	cr_assert_str_eq(rooms[1]->room_name, "classroom",
		"get_allowed_rooms failed");
	cr_assert_str_eq(rooms[2]->room_name, "closet",
		"get_allowed_rooms failed");
	cr_assert_str_eq(rooms[3]->room_name, "hallway",
		"get_alowed_rooms failed");
	cr_assert_str_eq(rooms[4]->room_name, "library",
		"get_alllowed_rooms failed");
	*/

}

/* testing make_default_room for undef bucket, bogus sh_desc, l_desc */
Test(room, make_default_undef_bogus) {
	roomspec_t hash = make_default_room("pharmacy", "short bogus", 
		"long bogus");
	cr_assert_not_null(hash, "make_default_room failed");

	printf(hash->room_name);
	printf(hash->items->item_id);

}
