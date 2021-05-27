#include <stdlib.h>
#include <string.h>

#include "cli/cmd.h"
#include "cli/cmdlist.h"
#include "cli/operations.h"
#include "common/utlist.h"
#include "ui/ui_ctx.h"
#include "ui/print_functions.h"
#include "action_management/actionmanagement.h"

/* === hashtable helper constructors === */
void add_entry(char *command_name, operation *associated_operation, action_type_t *action, lookup_t **table)
{
    lookup_t *t = malloc(sizeof(lookup_t));
    char *newname = malloc(sizeof(char) * (strlen(command_name) + 1));
    strcpy(newname, command_name);
    t->name = newname;
    t->operation_type = associated_operation;
    t->action = action;
    HASH_ADD_KEYPTR(hh, *table, t->name, strlen(t->name), t);
}

void add_action_entries(lookup_t **table)
{
    list_action_type_t *all_actions = get_supported_actions();

    while(all_actions != NULL)
    {
        action_type_t *curr_action = all_actions->act;

        if(curr_action->kind == 1)
        {
            add_entry(curr_action->c_name, kind1_action_operation, curr_action, table);
        }
        else if(curr_action->kind == 2)
        {
            add_entry(curr_action->c_name, kind2_action_operation, curr_action, table);
        }
        else if(curr_action->kind == 3)
        {
            add_entry(curr_action->c_name, kind3_action_operation, curr_action, table);
        }

        all_actions = all_actions->next;
    }
}

lookup_t *find_entry(char *command_name, lookup_t **table)
{
    lookup_t *t;
    HASH_FIND_STR(*table, command_name, t);
    return t;
}

operation *find_operation(char *command_name, lookup_t **table)
{
    lookup_t *t;
    if((t = find_entry(command_name, table)))
    {
        return t->operation_type;
    }
    return NULL;
}

action_type_t *find_action(char *command_name, lookup_t **table)
{
    return find_entry(command_name, table)->action;
}

void delete_entry(char *command_name, lookup_t **table)
{
    case_insensitize1(command_name);
    lookup_t *t = find_entry(command_name, table);
    HASH_DEL(*table, t);
    free(t->name);
    free(t);
}

/* === hashtable constructors  === */

/* See cmd.h */
lookup_t **lookup_t_new()
{
    lookup_t **t;
    int rc;

    t = malloc(sizeof(*t));

    if(t == NULL)
    {
        return NULL;
    }

    // Important: Set *t to NULL as per uthash documentation
    *t = NULL;

    rc = lookup_t_init(t);
    if(rc != SUCCESS)
    {
        return NULL;
    }

    return t;
}

/* See cmd.h */
int lookup_t_init(lookup_t **t)
{
    assert(t != NULL);

    add_entry("quit", quit_operation, NULL, t);
    add_entry("help", help_operation, NULL, t);
    add_entry("hist", hist_operation, NULL, t);
    add_entry("credits", credits_operation, NULL, t);
    add_entry("look",look_operation, NULL, t);
    add_entry("inv", inventory_operation, NULL, t);
    add_entry("map", map_operation, NULL, t);
    add_entry("switch", switch_operation, NULL, t);
    add_entry("load_wdl", load_wdl_operation, NULL, t);
    add_entry("name", name_operation, NULL, t);
    add_entry("palette", palette_operation, NULL, t);
    add_entry("items", items_in_room_operation, NULL, t);

    add_action_entries(t);

    return SUCCESS;
}


/* See cmd.h */
int lookup_t_free(lookup_t **t)
{
    lookup_t *tmp;
    lookup_t *current_user;
    HASH_ITER(hh, *t, current_user, tmp)
    {
        HASH_DEL(*t, current_user);
        free(current_user->name);
        free(current_user);

    }
    return SUCCESS;
}

/* === command constructors  === */

/* See cmd.h */
cmd *cmd_new(char *tokens[TOKEN_LIST_SIZE])
{
    cmd *c;
    int rc;

    c = malloc(sizeof(cmd));

    if(c == NULL)
    {
        return NULL;
    }
    rc = cmd_init(c, tokens);

    if(rc != SUCCESS)
    {
        return NULL;
    }

    return c;
}

/*See cmd.h*/
int cmd_init(cmd *c, char *tokens[TOKEN_LIST_SIZE])
{
    assert( c != NULL);

    c->tokens = tokens;

    return SUCCESS;
}

/* See cmd.h */
int cmd_free(cmd *c)
{
    if(c == NULL || c->tokens == NULL)
    {
        return SUCCESS;
    }
    free(c);
    return SUCCESS;
}

/* === command debugging === */


/* See cmd.h */
char *cmd_name_tos(cmd *c)
{
    if(c == NULL || c->tokens == NULL || c->tokens[0] == NULL)
    {
        return "ERROR";
    }
    return c->tokens[0];
}

/* See cmd.h */
void cmd_show(cmd *c, chiventure_ctx_t *ctx)
{
    /* note: cmd_name_tos result does not need to be freed
     * since that function returns pointers to string constants
     */
    if (c == NULL || c->tokens == NULL)
    {
        return;
    }

    for(int i = 0; i < TOKEN_LIST_SIZE; i++)
    {
        if(c->tokens[i] != NULL)
        {
            print_to_cli(ctx, c->tokens[i]);
        }
    }
    return;
}

/* === command parsing === */

/* See cmd.h */
cmd *cmd_from_tokens(char **ts, lookup_t **table)
{
    cmd *output = assign_action(ts, table);
    return output;
}

/* See cmd.h */
cmd *cmd_from_string(char *s, chiventure_ctx_t *ctx)
{

    if (s != NULL) 
    {
        command_list_t *new_command = new_command_list(s);
        LL_APPEND(ctx->command_history, new_command);
    }
    
    char **parsed_input = parse(s);
    if (parsed_input == NULL)
    {
        return NULL;
    }
    
    lookup_t **table = ctx->table;
    return cmd_from_tokens(parsed_input, table);
}

/* =================================== */
/* === execution of shell commands === */
/* =================================== */

/* See cmd.h */
int do_cmd(cmd *c, cli_callback callback_func, void *callback_args, chiventure_ctx_t *ctx)
{
    char *outstring;
    /*
     * available commands are QUIT, STATS, CHAR, LOOKUP, HELP, READ
     * all other commands will segfault in the testshell, because there is no game file
     */
    if (strcmp(cmd_name_tos(c),"QUIT")==0)
    {
        (*(c->func_of_cmd))(c->tokens, ctx);

        return CLI_CMD_SUCCESS_QUIT;
    }
    else
    {
        outstring = (*(c->func_of_cmd))(c->tokens, ctx);
        if(callback_func)
        {
            if (outstring != NULL)
            {
                return callback_func(ctx, outstring, callback_args);
            } else
            {
                return CLI_CMD_SUCCESS_NOOUTPUT;
            }
        }
        else
        {
            return CLI_CMD_SUCCESS;
        }
    }
}
