#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/openworld/sample_rooms.h"
#include "../../include/openworld/sample_items.h"

/* Tests the functions in sample_rooms.h */

/* Test fix_item_new function for BARN, 0 items */
Test(room, new1_0)
{
	fix_room_t *r;

	r = fix_room_new(BARN, 0);

	cr_assert_not_null(r, "fix_room_new() failed");

	cr_assert_str_eq(r->room_id, "barn", "fix_item_new() didn't set item_id");
	cr_assert_eq(r->room_tag, BARN, "fix_item_new() didn't set item_tag");
	cr_assert_str_eq(r->short_desc, "A red barn",
		"fix_item_new() didn't set shor_desc");
	cr_assert_str_eq(i->long_desc, "A red barn with stables inside",
		"fix_item_new() didn't set long_desc");
	cr_assert_null(r->items, "fix_item_new() didn't set 0 items");
}

/* Test fix_item_new function for BARN, 5 items */
Test(room, new1_5)
{
	fix_room_t *r;

	i = fix_room_new(BARN, 5);

	cr_assert_not_null(r, "fix_room_new() failed");

	int tally = 0;
	item_list_t* tmp = r->items->item;
	while (tmp != NULL) {
		tally++;
		tmp = tmp->next;
	}

	cr_assert_str_eq(r->room_id, "barn", "fix_item_new() didn't set item_id");
	cr_assert_eq(r->room_tag, BARN, "fix_item_new() didn't set item_tag");
	cr_assert_str_eq(r->short_desc, "A red barn",
		"fix_item_new() didn't set shor_desc");
	cr_assert_str_eq(i->long_desc, "A red barn with stables inside",
		"fix_item_new() didn't set long_desc");
	cr_assert_eq(tally, 5, "fix_item_new() didn't set 5 items");
}

/* Test fix_item_new function for THRONE_ROOM, 0 items */
Test(room, new2_0)
{
	fix_room_t *r;

	r = fix_room_new(THRONE_ROOM, 0);

	cr_assert_not_null(r, "fix_room_new() failed");

	cr_assert_str_eq(r->room_id, "throne room", "fix_item_new() didn't set item_id");
	cr_assert_eq(r->room_tag, THRONE_ROOM, "fix_item_new() didn't set item_tag");
	cr_assert_str_eq(r->short_desc, "This is a throne room",
		"fix_item_new() didn't set shor_desc");
	cr_assert_str_eq(i->long_desc, "A regal throne room decked out with lavish items",
		"fix_item_new() didn't set long_desc");
	cr_assert_null(r->items, "fix_item_new() didn't set 0 items");
}

/* Test fix_item_new function for THRONE_ROOM, 5 items */
Test(room, new2_5)
{
	fix_room_t *r;

	r = fix_room_new(THRONE_ROOM, 5);

	cr_assert_not_null(r, "fix_room_new() failed");

	int tally = 0;
	item_list_t* tmp = r->items->item;
	while (tmp != NULL) {
		tally++;
		tmp = tmp->next;
	}

	cr_assert_str_eq(r->room_id, "throne room", "fix_item_new() didn't set item_id");
	cr_assert_eq(r->room_tag, THRONE_ROOM, "fix_item_new() didn't set item_tag");
	cr_assert_str_eq(r->short_desc, "This is a throne room",
		"fix_item_new() didn't set shor_desc");
	cr_assert_str_eq(i->long_desc, "A regal throne room decked out with lavish items",
		"fix_item_new() didn't set long_desc");
	cr_assert_eq(tally, 5, "fix_item_new() didn't set 5 items");
}

/* Test fix_item_init function for BARN, 0 items */
Test(room, init1_0)
{
	fix_room_t *r;

	int rc = fix_room_init(r, BARN, 0);

	cr_assert_eq(rc, SUCCESS, "fix_room_init() failed");

	cr_assert_str_eq(r->room_id, "barn", "fix_item_new() didn't set item_id");
	cr_assert_eq(r->room_tag, BARN, "fix_item_new() didn't set item_tag");
	cr_assert_str_eq(r->short_desc, "A red barn",
		"fix_item_new() didn't set shor_desc");
	cr_assert_str_eq(i->long_desc, "A red barn with stables inside",
		"fix_item_new() didn't set long_desc");
	cr_assert_null(r->items, "fix_item_new() didn't set 0 items");
}

/* Test fix_item_init function for BARN, 5 items */
Test(room, init1_5)
{
	fix_room_t *r;

	int rc = fix_room_init(r, BARN, 5);

	cr_assert_eq(rc, SUCCESS, "fix_room_init() failed");

	int tally = 0;
	item_list_t* tmp = r->items->item;
	while (tmp != NULL) {
		tally++;
		tmp = tmp->next;
	}

	cr_assert_str_eq(r->room_id, "barn", "fix_item_new() didn't set item_id");
	cr_assert_eq(r->room_tag, BARN, "fix_item_new() didn't set item_tag");
	cr_assert_str_eq(r->short_desc, "A red barn",
		"fix_item_new() didn't set shor_desc");
	cr_assert_str_eq(i->long_desc, "A red barn with stables inside",
		"fix_item_new() didn't set long_desc");
	cr_assert_eq(tally, 5, "fix_item_new() didn't set 5 items");
}

/* Test fix_item_init function for THRONE_ROOM, 0 items */
Test(room, init2_0)
{
	fix_room_t *r;

	int rc = fix_room_init(r, THRONE_ROOM, 0);

	cr_assert_eq(rc, SUCCESS, "fix_item_init() failed");

	cr_assert_str_eq(r->room_id, "throne room", "fix_item_new() didn't set item_id");
	cr_assert_eq(r->room_tag, THRONE_ROOM, "fix_item_new() didn't set item_tag");
	cr_assert_str_eq(r->short_desc, "This is a throne room",
		"fix_item_new() didn't set shor_desc");
	cr_assert_str_eq(i->long_desc, "A regal throne room decked out with lavish items",
		"fix_item_new() didn't set long_desc");
	cr_assert_null(r->items, "fix_item_new() didn't set 0 items");
}

/* Test fix_item_init function for THRONE_ROOM, 5 items */
Test(room, init2_5)
{

	fix_room_t *r;

	int rc = fix_room_init(r, THRONE_ROOM, 5);

	cr_assert_eq(rc, SUCCESS, "fix_item_init() failed");

	int tally = 0;
	item_list_t* tmp = r->items->item;
	while (tmp != NULL) {
		tally++;
		tmp = tmp->next;
	}

	cr_assert_str_eq(r->room_id, "throne room", "fix_item_new() didn't set item_id");
	cr_assert_eq(r->room_tag, THRONE_ROOM, "fix_item_new() didn't set item_tag");
	cr_assert_str_eq(r->short_desc, "This is a throne room",
		"fix_item_new() didn't set shor_desc");
	cr_assert_str_eq(i->long_desc, "A regal throne room decked out with lavish items",
		"fix_item_new() didn't set long_desc");
	cr_assert_eq(tally, 5, "fix_item_new() didn't set 5 items");
}

/* Test fix_item_free function for BARN */
Test(room, free1)
{
	fix_room_t* r;
	int rc;

	r = fix_room_new(BARN);

	cr_assert_not_null(r, "fix_room_new() failed");

	rc = fix_room_free(r);

	cr_assert_eq(rc, SUCCESS, "fix_room_free() failed");
}

/* Test fix_item_free function for THRONE_ROOM */
Test(room, free2)
{
	fix_room_t* r;
	int rc;

	r = fix_room_new(THRONE_ROOM);

	cr_assert_not_null(r, "fix_room_new() failed");

	rc = fix_room_free(r);

	cr_assert_eq(rc, SUCCESS, "fix_room_free() failed");
}

/* Test add_item_to_fix_room */
Test(room, add_gen_item) {
	fix_room_t* r;
	fix_item_t* i;
	int rc;

	i = fix_item_new(APPLE);
	cr_assert_not_null(i, "fix_room_new() failed");

	r = fix_room_new(BARN);
	cr_assert_not_null(r, "fix_room_new() failed");

	rc = add_item_to_fix_room(r, i);
	cr_assert_eq(rc, SUCCESS, "add_item_to_fix_room() failed");

}

/* Test add_item_to_barn for 2 items */
Test(room, add_barn_item) {
	fix_room_t* r;
	int item_numbers = 2;
	int rc;

	r = fix_room_new(BARN);
	cr_assert_not_null(r, "fix_room_new() failed");

	rc = add_items_to_barn(r, item_numbers);
	cr_assert_eq(rc, SUCCESS, "add_item_to_barn() failed");

	int tally = 0;
	item_list_t* tmp = r->items->item;
	while (tmp != NULL) {
		tally++;
		tmp = tmp->next;
	}
	cr_assert_eq(tally, item_numbers, "add_item_to_barn() did not add specified items");

}

/* Test add_item_to_cafeteria for 2 items */
Test(room, add_cafeteria_item) {
	fix_room_t* r;
	int item_numbers = 2;
	int rc;

	r = fix_room_new(CAFETERIA);
	cr_assert_not_null(r, "fix_room_new() failed");

	rc = add_items_to_cafeteria(r, item_numbers);
	cr_assert_eq(rc, SUCCESS, "add_items_to_cafeteria() failed");

	int tally = 0;
	item_list_t* tmp = r->items->item;
	while (tmp != NULL) {
		tally++;
		tmp = tmp->next;
	}
	cr_assert_eq(tally, item_numbers, "add_items_to_cafeteria() did not add specified items");

}

/* Test add_item_to_classroom for 2 items */
Test(room, add_classroom_item) {
	fix_room_t* r;
	int item_numbers = 2;
	int rc;

	r = fix_room_new(CLASSROOM);
	cr_assert_not_null(r, "fix_room_new() failed");

	rc = add_items_to_classroom(r, item_numbers);
	cr_assert_eq(rc, SUCCESS, "add_items_to_classroom() failed");

	int tally = 0;
	item_list_t* tmp = r->items->item;
	while (tmp != NULL) {
		tally++;
		tmp = tmp->next;
	}
	cr_assert_eq(tally, item_numbers, "add_items_to_classroom() did not add specified items");

}

/* Test add_item_to_closet for 2 items */
Test(room, add_closet_item) {
	fix_room_t* r;
	int item_numbers = 2;
	int rc;

	r = fix_room_new(CLOSET);
	cr_assert_not_null(r, "fix_room_new() failed");

	rc = add_items_to_closet(r, item_numbers);
	cr_assert_eq(rc, SUCCESS, "add_items_to_closet() failed");

	int tally = 0;
	item_list_t* tmp = r->items->item;
	while (tmp != NULL) {
		tally++;
		tmp = tmp->next;
	}
	cr_assert_eq(tally, item_numbers, "add_items_to_closet() did not add specified items");

}

/* Test add_item_to_dungeon for 2 items */
Test(room, add_dungeon_item) {
	fix_room_t* r;
	int item_numbers = 2;
	int rc;

	r = fix_room_new(DUNGEON);
	cr_assert_not_null(r, "fix_room_new() failed");

	rc = add_items_to_dungeon(r, item_numbers);
	cr_assert_eq(rc, SUCCESS, "add_items_to_dungeon() failed");

	int tally = 0;
	item_list_t* tmp = r->items->item;
	while (tmp != NULL) {
		tally++;
		tmp = tmp->next;
	}
	cr_assert_eq(tally, item_numbers, "add_items_to_dungeon() did not add specified items");

}

/* Test add_item_to_field for 2 items */
Test(room, add_field_item) {
	fix_room_t* r;
	int item_numbers = 2;
	int rc;

	r = fix_room_new(FIELD);
	cr_assert_not_null(r, "fix_room_new() failed");

	rc = add_items_to_dungeon(r, item_numbers);
	cr_assert_eq(rc, SUCCESS, "add_items_to_field() failed");

	int tally = 0;
	item_list_t* tmp = r->items->item;
	while (tmp != NULL) {
		tally++;
		tmp = tmp->next;
	}
	cr_assert_eq(tally, item_numbers, "add_items_to_field() did not add specified items");

}

/* Test add_item_to_hallway for 2 items */
Test(room, add_hallway_item) {
	fix_room_t* r;
	int item_numbers = 2;
	int rc;

	r = fix_room_new(HALLWAY);
	cr_assert_not_null(r, "fix_room_new() failed");

	rc = add_items_to_dungeon(r, item_numbers);
	cr_assert_eq(rc, SUCCESS, "add_items_to_hallway() failed");

	int tally = 0;
	item_list_t* tmp = r->items->item;
	while (tmp != NULL) {
		tally++;
		tmp = tmp->next;
	}
	cr_assert_eq(tally, item_numbers, "add_items_to_hallway() did not add specified items");

}

/* Test add_item_to_kitchen for 2 items */
Test(room, add_kitchen_item) {
	fix_room_t* r;
	int item_numbers = 2;
	int rc;

	r = fix_room_new(KITCHEN);
	cr_assert_not_null(r, "fix_room_new() failed");

	rc = add_items_to_dungeon(r, item_numbers);
	cr_assert_eq(rc, SUCCESS, "add_items_to_kitchen() failed");

	int tally = 0;
	item_list_t* tmp = r->items->item;
	while (tmp != NULL) {
		tally++;
		tmp = tmp->next;
	}
	cr_assert_eq(tally, item_numbers, "add_items_to_kitchen() did not add specified items");

}

/* Test add_item_to_library for 2 items */
Test(room, add_library_item) {
	fix_room_t* r;
	int item_numbers = 2;
	int rc;

	r = fix_room_new(LIBRARY);
	cr_assert_not_null(r, "fix_room_new() failed");

	rc = add_items_to_dungeon(r, item_numbers);
	cr_assert_eq(rc, SUCCESS, "add_items_to_library() failed");

	int tally = 0;
	item_list_t* tmp = r->items->item;
	while (tmp != NULL) {
		tally++;
		tmp = tmp->next;
	}
	cr_assert_eq(tally, item_numbers, "add_items_to_library() did not add specified items");

}

/* Test add_item_to_living for 2 items */
Test(room, add_living_item) {
	fix_room_t* r;
	int item_numbers = 2;
	int rc;

	r = fix_room_new(LIVING);
	cr_assert_not_null(r, "fix_room_new() failed");

	rc = add_items_to_living(r, item_numbers);
	cr_assert_eq(rc, SUCCESS, "add_items_to_living() failed");

	int tally = 0;
	item_list_t* tmp = r->items->item;
	while (tmp != NULL) {
		tally++;
		tmp = tmp->next;
	}
	cr_assert_eq(tally, item_numbers, "add_items_to_living() did not add specified items");

}

/* Test add_item_to_throne for 2 items */
Test(room, add_throne_item) {
	fix_room_t* r;
	int item_numbers = 2;
	int rc;

	r = fix_room_new(THRONE_ROOM);
	cr_assert_not_null(r, "fix_room_new() failed");

	rc = add_items_to_throne(r, item_numbers);
	cr_assert_eq(rc, SUCCESS, "add_items_to_throne() failed");

	int tally = 0;
	item_list_t* tmp = r->items->item;
	while (tmp != NULL) {
		tally++;
		tmp = tmp->next;
	}
	cr_assert_eq(tally, item_numbers, "add_items_to_throne() did not add specified items");

}

/* Test get_sdesc_fix function for CLASSROOM */
Test(room, sdesc1) {
	fix_room_t* r;

	r = fix_room_new(CLASSROOM, 0);

	cr_assert_not_null(r, "fix_room_new() failed");

	char* ret = get_sdesc_fix_item(r);

	cr_assert_str_eq(ret, "A medium-sized classroom with 30 desks",
		"get_sdesc_fix_item() failed");

}

/* Test get_sdesc_fix function for HALLWAY */
Test(room, sdesc2) {
	fix_room_t* r;

	r = fix_room_new(HALLWAY, 0);

	cr_assert_not_null(r, "fix_room_new() failed");

	char* ret = get_sdesc_fix_item(r);

	cr_assert_str_eq(ret, "A well-lit hallway", "get_sdesc_fix_item() failed");

}

/* Test get_ldesc_fix function for CLASSROOM */
Test(room, ldesc1) {
	fix_room_t* r;

	r = fix_room_new(CLASSROOM, 0);

	cr_assert_not_null(r, "fix_room_new() failed");

	char* ret = get_sdesc_fix_item(r);

	cr_assert_str_eq(ret, "A geography teacher's classroom with 30 desks",
		"get_sdesc_fix_item() failed");

}

/* Test get_ldesc_fix function for HALLWAY */
Test(room, ldesc2) {
	fix_room_t* r;

	r = fix_room_new(HALLWAY, 0);

	cr_assert_not_null(r, "fix_room_new() failed");

	char* ret = get_sdesc_fix_item(r);

	cr_assert_str_eq(ret, "A sterile, white hallway with no windows", 
		"get_sdesc_fix_item() failed");

}

/* Test list_fix_items for room with 0 items */
Test(room, item_list1) {
	fix_room_t* r;

	r = fix_room_new(HALLWAY, 0);

	item_list_t* llist = list_fix_items(r);

	cr_assert_not_null(r, "fix_room_new() failed");

	cr_assert_null(r, "list_fix_items() failed");
}

/* Test list_fix_items for room with 5 items */
Test(room, item_list2) {
	fix_room_t* r;

	r = fix_room_new(HALLWAY, 5);

	cr_assert_not_null(r, "fix_room_new() failed");

	item_list_t* llist = list_fix_items(r);

	int tally = 0;
	item_list_t* tmp = r->items->item;
	while (tmp != NULL) {
		tally++;
		tmp = tmp->next;
	}

	cr_assert_eq(tally, 5, "list_fix_items failed");
}

/* Test list_paths for room with 0 paths */
Test(room, path_list1) {
	fix_room_t* r;

	r = fix_room_new(HALLWAY, 0);

	cr_assert_not_null(r, "fix_room_new() failed");

	path_t* paths = list_fix_items(r);

	cr_assert_null(paths, "list_paths() failed");
}

/* Test list_paths for room with 2 paths */
Test(room, path_list2) {
	//Can't do this yet because i'm depending on the
	//game-state definition of paths in their room struct
	//This will be resolved in my "paths struct" issue for
	//the sprint ... but it's not relevant for implementing
	//rooms and items.
}

/* Test generate_room */
Test(room, generate) {
	fix_room_t* r;
	r = generate_room();
	cr_assert_not_null(r, "generate_room() failed");
}