#ifndef _CONDITION_H
#define _CONDITION_H

#include "game_state_common.h"
#include "player.h"
#include "item.h"


typedef struct attribute_condition{
    item_t *item;
    attribute_t *attribute_to_check; //pointer to attribute
    attribute_value_t expected_value;
} attribute_condition_t;

typedef struct inventory_condition{
    player_t *player_to_check;
    item_t *expected_item;
} inventory_condition_t;

typedef union condition_type{
    attribute_condition_t* attr_type;
    inventory_condition_t* inven_type;
} condition_type_t;

enum condition_tag {ATTRIBUTE,INVENTORY};

typedef struct condition{
    condition_type_t cond;
    enum condition_tag condition_tag;
    struct condition *next;
} condition_t;

/* This typedef is to distinguish between condition_t
* pointers which are used to point to the condition_t structs
* in the traditional sense, and those which are used to enable UTLIST functionality
* on the ondition_t structs as specified in src/common/include
*/
typedef struct condition condition_list_t;

/* valid_inven_condition checks with the game given to make sure that its variables
 * are valid
 * 
 * Parameters:
 *   the game to check against
 *   the condition
 * 
 * Returns:
 *   ITEM_MODIFY_NULL if item does not exist in game
 *   ATTRIBUTE_NULL if attribute is null or does not exist in item
 * 
 *   PLAYER_NULL if player does not exist in game
 * 
 *   SUCCESS otherwise
 */
int valid_inven_condition(game_t *game, inventory_condition_t *condition);

/* delete_condition_llist frees a linked list of action conditions
 * Parameters:
 *  linked list of conditions
 *
 * Returns:
 *  always returns SUCCESS
 */
int delete_condition_llist(condition_list_t *conditions);

/* attribute_condition_new() creates a new attribute condition in an item with given inputs
 * Parameters:
 *  a pointer to the item to be modified
 *  a string representing name of the attribute to add a condition on
 *  the desired value of the attribute
 * Returns:
 *  NULL if item or attribute are NULL, the new condition if succcessful
 */
condition_t *attribute_condition_new(item_t *item_to_modify, char *attribute_name,
				       attribute_value_t new_value);


/* invetory_condition_new() creates a new inventory condition in an item with given inputs
 * Parameters:
 *  a pointer to the player whose inventory to check
 *  a pointer to the item
 * Returns:
 *  NULL if player or item are NULL, the new condition if succcessful
 */
condition_t *inventory_condition_new(player_t *player, item_t *expected_item);

/* check_condition() checks if the actual attribute of an item is equal
 * to the desired attribute
 * Parameters:
 *  a pointer to the item to check
 *  the desired attribute
 * Returns:
 *  true if desired attribute matches the actual, false if not
 */
bool check_condition(condition_t *condition);


/* all_conditions_met() checks if all of the conditions of an action are met
 * Parameters:
 *  a pointer to the item to check
 *  the action
 * Returns:
 *  TRUE if all conditions are met, FALSE if not
 *  2 if action not possible
 */
bool all_conditions_met(condition_list_t *cond_list);


#endif
