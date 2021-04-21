/*
 * functions that set up the basic skills for the classes
 *
 * for more information see class_skills.h
 */
#include "class_skills.h"


/*
 * this is a placeholder function for the skill struct to satisfy
 * the effect_t field, which wants a function of this form
 *
 * in the future, playerclass and skilltrees teams should coordinate
 * so that the effect_t field can be a function pointer to a function
 * that will actually execute the skill
 *
 * Paramters:
 *  - sk. a string representing the skill effects
 *
 * Returns:
 *  - the input parameter (placeholder)
 */
char* class_execute_skill(char* sk) {
    return sk;
}

/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 ranger
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_ranger(class_t* class) {
    /* TODO */
    return SUCCESS;
}

/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 rogue
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_rogue(class_t* class) {
    /* TODO */
    return SUCCESS;
}

/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 monk
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_monk(class_t* class) {
    /* TODO */
    return SUCCESS;
}
/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 sorcerer
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_sorcerer(class_t* class) {
    /* TODO */
    return SUCCESS;
}

/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 druid
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_druid(class_t* class) {
    /* TODO */
    return SUCCESS;
}

/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 elementalist
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_elementalist(class_t* class) {
    /* TODO */
    return SUCCESS;
}

/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 bard
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_bard(class_t* class) {
    /* TODO */
    return SUCCESS;
}

/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 wizard
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_wizard(class_t* class) {
    /* TODO */
    return SUCCESS;
}

/*
 * fills in the skill-related structs of a class with the default skills
 * for a level 1 knight
 *
 * Parameters:
 *  - class. the class the skill structs should be placed in
 *
 * Returns:
 *  - status code
 *  - the structs inside the class now contain skills
 */
int get_default_knight(class_t* class) {
    /* TODO */
    return SUCCESS;
}

/* See class_skills.h */
int class_skills_init(class_t* class) {
    skill_inventory_t *combat, *noncombat;
    skill_tree_t *tree;

    combat = inventory_new(MAX_ACTIVE_SKILLS, MAX_PASSIVE_SKILLS);
    noncombat = inventory_new(MAX_ACTIVE_SKILLS, MAX_PASSIVE_SKILLS);
    
    /* tree ID is the ascii values of the first two letters of the name.
     * Should probably have a better system */
    int tid = class->name[0] + class->name[1];
    tree = skill_tree_new(tid, class->name, MAX_SKILLS_IN_TREE);

    if (tree == NULL)
    {
        fprintf(stderr, "Could not allocate memory for skill trees "
                        "in class_skills_init\n");
        return EXIT_FAILURE;
    }
    if (combat == NULL || noncombat == NULL)
    {
        fprintf(stderr, "Could not allocate memory for skill inventories"
                        "in class_skills_init\n");
    }
    class->skilltree = tree;
    class->combat = combat;
    class->noncombat = noncombat;

    int init_success = 0;
    if (!strcmp(class->name, "Ranger"))
    {
        init_success = get_default_ranger(class);
    }
    else if (!strcmp(class->name, "Rogue"))
    {
        init_success = get_default_rogue(class);
    }
    else if (!strcmp(class->name, "Monk"))
    {
        init_success = get_default_monk(class);
    }
    else if (!strcmp(class->name, "Sorcerer"))
    {
        init_success = get_default_sorcerer(class);
    }
    else if (!strcmp(class->name, "Druid"))
    {
        init_success = get_default_druid(class);
    }
    else if (!strcmp(class->name, "Elementalist"))
    {
        init_success = get_default_elementalist(class);
    }
    else if (!strcmp(class->name, "Bard"))
    {
        init_success = get_default_bard(class);
    }
    else if (!strcmp(class->name, "Wizard"))
    {
        init_success = get_default_wizard(class);
    }
    else if (!strcmp(class->name, "Knight"))
    {
        init_success = get_default_knight(class);
    }
    
    if (init_success)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
