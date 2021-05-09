#ifndef BATTLE_DEFAULT_OBJECTS_H
#define BATTLE_DEFAULT_OBJECTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battle/battle_structs.h"
#include "battle/battle_moves.h"
#include "battle/battle_flow_structs.h"

/*
 * Generates a random integer between two bounds
 *
 * Parameters:
 * - min: the minimum included bound
 * - max: the maximum included bound
 * Returns:
 * - a random integer between min and max
 * Note:
 * - must include "srand(time(0));" before using 
    any of these functions in a file
 */
int randnum(int min, int max);

/*
 * Generates a random weapon item from a list of previously-initialized weapons
 *
 * Parameters: none
 * Returns:
 * - a pointer to a default item
 * 
 * Note: Currently, our consume_item function works with consumables, not weapons.
 * We will leave this function for the future if using weapons is implemented.
 */
item_t *get_random_default_weapon();

/*
 * Generates a random consumable item from a list of previously-initialized consumables
 *
 * Parameters: none
 * Returns:
 * - a pointer to a default item
 */
item_t *get_random_default_consumable();

/*
 * Generates a random move from a list of previously-initialized moves
 *
 * Parameters: none
 * Returns:
 * - a pointer to a default move
 */
move_t *get_random_default_move();

/*
 * Generates a random stat from a list of previously-initialized stats
 *
 * Parameters: none
 * Returns:
 * - a pointer to a default stat
 */
stat_t* get_random_stat();

#endif
