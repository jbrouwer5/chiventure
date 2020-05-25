#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "conditional_block.h"
#include "game-state/item.h"
#include "ast_block.h"

/* Checks that a new conditional block with type EQ is created without interruption */
Test(conditional_block_t, new_EQ)
{
    conditional_type_t conditional_type = EQ;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);

    conditional_block_t* new_conditional = conditional_block_new(conditional_type, 
                                                                left, right);

    cr_assert_not_null(new_conditional, "conditional_block_new() failed");

    cr_assert_eq(new_conditional->conditional_type, conditional_type, "conditional_block_new() "
                "didn't set new_conditional->conditional_type");
    cr_assert_eq(new_conditional->left, left, "conditional_block_new() didn't set "
                "new_conditional->left");
    cr_assert_eq(new_conditional->right, right, "conditional_block_new() didn't set "
                "new_conditional->right");

    conditional_block_free(new_conditional);
}

/* Checks that a new conditional block with type LTGT is created without interruption */
Test(conditional_block_t, new_LTGT)
{   
    conditional_type_t conditional_type = LTGT;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);

    conditional_block_t* new_conditional = conditional_block_new(conditional_type, 
                                                                left, right);

    cr_assert_not_null(new_conditional, "conditional_block_new() failed");

    cr_assert_eq(new_conditional->conditional_type, conditional_type, "conditional_block_new() "
                "didn't set new_conditional->conditional_type");
    cr_assert_eq(new_conditional->left, left, "conditional_block_new() didn't set "
                "new_conditional->left");
    cr_assert_eq(new_conditional->right, right, "conditional_block_new() didn't set "
                "new_conditional->right");

    conditional_block_free(new_conditional);
}

/* Checks that a new conditional block with type LTEGTE is created without interruption */
Test(conditional_block_t, new_LTEGTE)
{   
    conditional_type_t conditional_type = LTEGTE;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);

    conditional_block_t* new_conditional = conditional_block_new(conditional_type, 
                                                                left, right);

    cr_assert_not_null(new_conditional, "conditional_block_new() failed");

    cr_assert_eq(new_conditional->conditional_type, conditional_type, "conditional_block_new() "
                "didn't set new_conditional->conditional_type");
    cr_assert_eq(new_conditional->left, left, "conditional_block_new() didn't set "
                "new_conditional->left");
    cr_assert_eq(new_conditional->right, right, "conditional_block_new() didn't set "
                "new_conditional->right");

    conditional_block_free(new_conditional);
}

/* Checks that a new conditional block with type IN is created without interruption */
Test(conditional_block_t, new_IN)
{   
    conditional_type_t conditional_type = IN;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);

    conditional_block_t* new_conditional = conditional_block_new(conditional_type, 
                                                                left, right);

    cr_assert_not_null(new_conditional, "conditional_block_new() failed");

    cr_assert_eq(new_conditional->conditional_type, conditional_type, "conditional_block_new() "
                "didn't set new_conditional->conditional_type");
    cr_assert_eq(new_conditional->left, left, "conditional_block_new() didn't set "
                "new_conditional->left");
    cr_assert_eq(new_conditional->right, right, "conditional_block_new() didn't set "
                "new_conditional->right");

    conditional_block_free(new_conditional);
}

/* Checks that a new AST conditional block with type EQ is created without interruption */
Test(conditional_block_t, new_AST_EQ)
{
    conditional_type_t conditional_type = EQ;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);
    block_type_t block_type = CONDITIONAL;
    
    conditional_block_t* new_conditional = conditional_block_new(conditional_type, 
                                                                left, right);

    AST_block_t* new_ast = AST_conditional_block_new(conditional_type, 
                                                                left, right);

    cr_assert_not_null(new_ast, "AST_conditional_block_new() failed");

    cr_assert_eq(new_ast->block, new_conditional, "AST_conditional_block_new() "
                "didn't set new_ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_conditional_block_new() didn't set "
                "new_ast->block_type");

    conditional_block_free(new_conditional);
    AST_block_free(new_ast);
}

/* Checks that a new AST conditional block with type IN is created without interruption */
Test(conditional_block_t, new_AST_IN)
{
    conditional_type_t conditional_type = IN;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);
    block_type_t block_type = CONDITIONAL;
    
    conditional_block_t* new_conditional = conditional_block_new(conditional_type, 
                                                                left, right);

    AST_block_t* new_ast = AST_conditional_block_new(conditional_type, 
                                                                left, right);

    cr_assert_not_null(new_ast, "AST_conditional_block_new() failed");

    cr_assert_eq(new_ast->block, new_conditional, "AST_conditional_block_new() "
                "didn't set new_ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_conditional_block_new() didn't set "
                "new_ast->block_type");

    conditional_block_free(new_conditional);
    AST_block_free(new_ast);
}

/* Checks that a new AST conditional block with type LTGT is created without interruption */
Test(conditional_block_t, new_AST_LTGT)
{
    conditional_type_t conditional_type = LTGT;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);
    block_type_t block_type = CONDITIONAL;
    
    conditional_block_t* new_conditional = conditional_block_new(conditional_type, 
                                                                left, right);

    AST_block_t* new_ast = AST_conditional_block_new(conditional_type, 
                                                                left, right);

    cr_assert_not_null(new_ast, "AST_conditional_block_new() failed");

    cr_assert_eq(new_ast->block, new_conditional, "AST_conditional_block_new() "
                "didn't set new_ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_conditional_block_new() didn't set "
                "new_ast->block_type");

    conditional_block_free(new_conditional);
    AST_block_free(new_ast);
}

/* Checks that a new AST conditional block with type LTEGTE is created without interruption */
Test(conditional_block_t, new_AST_LTEGTE)
{
    conditional_type_t conditional_type = LTEGTE;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);
    block_type_t block_type = CONDITIONAL;
    
    conditional_block_t* new_conditional = conditional_block_new(conditional_type, 
                                                                left, right);

    AST_block_t* new_ast = AST_conditional_block_new(conditional_type, 
                                                                left, right);

    cr_assert_not_null(new_ast, "AST_conditional_block_new() failed");

    cr_assert_eq(new_ast->block, new_conditional, "AST_conditional_block_new() "
                "didn't set new_ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_conditional_block_new() didn't set "
                "new_ast->block_type");

    conditional_block_free(new_conditional);
    AST_block_free(new_ast);
}

/* Checks that a new conditional block with type EQ is initialized without interruption */
Test(conditional_block_t, init_EQ)
{
    conditional_block_t conditional;
    int rc;
    conditional_type_t conditional_type = EQ;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);

    rc = conditional_block_init(&conditional, conditional_type, left, right);

    cr_assert_eq(rc, SUCCESS, "conditional_block_init() failed");
    cr_assert_eq(conditional.conditional_type, conditional_type, "conditional_block_init() "
                "didn't set conditional.conditional_type");
    cr_assert_eq(conditional.left, left, "conditional_block_init() didn't set "
                "conditional.left");
    cr_assert_eq(conditional.right, right, "conditional_block_init() didn't set "
                "conditional.right");
}

/* Checks that a new conditional block with type LTGT is initialized without interruption */
Test(conditional_block_t, init_LTGT)
{
    conditional_block_t conditional;
    int rc;
    conditional_type_t conditional_type = LTGT;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);

    rc = conditional_block_init(&conditional, conditional_type, left, right);

    cr_assert_eq(rc, SUCCESS, "conditional_block_init() failed");
    cr_assert_eq(conditional.conditional_type, conditional_type, "conditional_block_init() "
                "didn't set conditional.conditional_type");
    cr_assert_eq(conditional.left, left, "conditional_block_init() didn't set "
                "conditional.left");
    cr_assert_eq(conditional.right, right, "conditional_block_init() didn't set "
                "conditional.right");
}

/* Checks that a new conditional block with type LTEGTE is initialized without interruption */
Test(conditional_block_t, init_LTEGTE)
{
    conditional_block_t conditional;
    int rc;
    conditional_type_t conditional_type = LTEGTE;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);

    rc = conditional_block_init(&conditional, conditional_type, left, right);

    cr_assert_eq(rc, SUCCESS, "conditional_block_init() failed");
    cr_assert_eq(conditional.conditional_type, conditional_type, "conditional_block_init() "
                "didn't set conditional.conditional_type");
    cr_assert_eq(conditional.left, left, "conditional_block_init() didn't set "
                "conditional.left");
    cr_assert_eq(conditional.right, right, "conditional_block_init() didn't set "
                "conditional.right");
}

/* Checks that a new conditional block with type IN is initialized without interruption */
Test(conditional_block_t, init_IN)
{
    conditional_block_t conditional;
    int rc;
    conditional_type_t conditional_type = IN;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);

    rc = conditional_block_init(&conditional, conditional_type, left, right);

    cr_assert_eq(rc, SUCCESS, "conditional_block_init() failed");
    cr_assert_eq(conditional.conditional_type, conditional_type, "conditional_block_init() "
                "didn't set conditional.conditional_type");
    cr_assert_eq(conditional.left, left, "conditional_block_init() didn't set "
                "conditional.left");
    cr_assert_eq(conditional.right, right, "conditional_block_init() didn't set "
                "conditional.right");
}

/* Checks that a new conditional block with type EQ is freed without interruption */
Test(conditional_block_t, free_EQ)
{
    conditional_block_t* conditional;
    int rc;
    conditional_type_t conditional_type = EQ;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);

    conditional = conditional_block_new(conditional_type, left, right);

    cr_assert_not_null(conditional, "conditional_block_new() failed");

    rc = conditional_block_free(conditional);

    cr_assert_eq(rc, SUCCESS, "conditional_block_free() failed");
}

/* Checks that a new conditional block with type LTGT is freed without interruption */
Test(conditional_block_t, free_LTGT)
{
    conditional_block_t* conditional;
    int rc;
    conditional_type_t conditional_type = LTGT;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);

    conditional = conditional_block_new(conditional_type, left, right);

    cr_assert_not_null(conditional, "conditional_block_new() failed");

    rc = conditional_block_free(conditional);

    cr_assert_eq(rc, SUCCESS, "conditional_block_free() failed");
}
   
/* Checks that a new conditional block with type LTEGTE is freed without interruption */
Test(conditional_block_t, free_LTEGTE)
{
    conditional_block_t* conditional;
    int rc;
    conditional_type_t conditional_type = LTEGTE;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);

    conditional = conditional_block_new(conditional_type, left, right);

    cr_assert_not_null(conditional, "conditional_block_new() failed");

    rc = conditional_block_free(conditional);

    cr_assert_eq(rc, SUCCESS, "conditional_block_free() failed");
}
   
/* Checks that a new conditional block with type IN is freed without interruption */
Test(conditional_block_t, free_IN)
{
    conditional_block_t* conditional;
    int rc;
    conditional_type_t conditional_type = IN;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);

    conditional = conditional_block_new(conditional_type, left, right);

    cr_assert_not_null(conditional, "conditional_block_new() failed");

    rc = conditional_block_free(conditional);

    cr_assert_eq(rc, SUCCESS, "conditional_block_free() failed");
}
   
