#include <string.h>
#include <criterion/criterion.h>
#include "npc/dialogue.h"


/*** Node ***/

/* Checks that node_new creates a node with the given parameters */
Test(dialogue, node_new)
{
    node_t *n;

    n = node_new("ID", "Dialogue");

    cr_assert_not_null(n, "node_new() failed");

    cr_assert_eq(strcmp(n->node_id, "ID"), 0, "node_new() didn't set node_id");
    cr_assert_eq(strcmp(n->npc_dialogue, "Dialogue"), 0,
                 "node_new() didn't set dialogue");
    cr_assert_null(n->edges, "node_new() didn't set edges to NULL");
}

/* Checks that node_init initializes a node with the given parameters */
Test(dialogue, node_init)
{
    node_t n;
    int rc;

    n.node_id = NULL;
    n.npc_dialogue = NULL;

    rc = node_init(&n, "ID", "Dialogue");

    cr_assert_eq(rc, SUCCESS, "node_init() failed");

    cr_assert_eq(strcmp(n.node_id, "ID"), 0, "node_new() didn't set node_id");
    cr_assert_eq(strcmp(n.npc_dialogue, "Dialogue"), 0,
                 "node_new() didn't set dialogue");
    cr_assert_null(n.edges, "node_new() didn't set edges to NULL");
}

/* Checks that node_free frees memory allocated to a node */
Test(dialogue, node_free)
{
    node_t *n;
    int rc;

    n = node_new("ID", "Dialogue");

    cr_assert_not_null(n, "node_new() failed");

    rc = node_free(n);

    cr_assert_eq(rc, SUCCESS, "node_free() failed");
}


/*** Edge ***/

/* Checks that edge_new creates an edge with the given parameters */
Test(dialogue, edge_new)
{
    edge_t *e;

    e = edge_new("Quip", node_new("N1", "Dia_1"), node_new("N2", "Dia_2"));

    cr_assert_not_null(e, "edge_new() failed");

    cr_assert_eq(strcmp(e->quip, "Quip"), 0, "edge_new() didn't set quip");
    cr_assert_eq(strcmp(e->from->node_id, "N1"), 0,
                 "edge_new() didn't set from");
    cr_assert_eq(strcmp(e->to->node_id, "N2"), 0,
                 "edge_new() didn't set to");
}

/* Checks that edge_init initializes an edge with the given parameters */
Test(dialogue, edge_init)
{
    edge_t e;
    int rc;

    e.quip = NULL;

    rc = edge_init(&e, "Quip", node_new("N1", "Dia_1"),
                   node_new("N2", "Dia_2"));

    cr_assert_eq(rc, SUCCESS, "edge_init() failed");

    cr_assert_eq(strcmp(e.quip, "Quip"), 0, "edge_new() didn't set quip");
    cr_assert_eq(strcmp(e.from->node_id, "N1"), 0,
                 "edge_new() didn't set from");
    cr_assert_eq(strcmp(e.to->node_id, "N2"), 0,
                 "edge_new() didn't set to");
}

/* Checks that edge_free frees memory allocated to an edge */
Test(dialogue, edge_free)
{
    edge_t *e;
    int rc;

    e = edge_new("Quip", node_new("N1", "Dia_1"), node_new("N2", "Dia_2"));

    cr_assert_not_null(e, "edge_new() failed");

    rc = edge_free(e);

    cr_assert_eq(rc, SUCCESS, "edge_free() failed");
}


/*** Convo ***/

/* Checks that convo_new creates an empty convo */
Test(dialogue, convo_new)
{
    convo_t *c;

    c = convo_new();

    cr_assert_not_null(c, "convo_new() failed");

    cr_assert_eq(c->num_nodes, 0,
                 "convo_new() didn't set num_nodes to 0");
    cr_assert_null(c->all_nodes,
                   "convo_new() didn't set all_nodes to NULL");
    cr_assert_null(c->all_edges,
                   "convo_new() didn't set all_edges to NULL");
    cr_assert_null(c->cur_node,
                   "convo_new() didn't set cur_node to NULL");
}

/* Checks that convo_init initializes a convo */
Test(dialogue, convo_init)
{
    convo_t c;
    int rc;

    rc = convo_init(&c);

    cr_assert_eq(rc, SUCCESS, "convo_init() failed");

    cr_assert_eq(c.num_nodes, 0,
                 "convo_init() didn't set num_nodes to 0");
    cr_assert_null(c.all_nodes,
                   "convo_init() didn't set all_nodes to NULL");
    cr_assert_null(c.all_edges,
                   "convo_init() didn't set all_edges to NULL");
    cr_assert_null(c.cur_node,
                   "convo_init() didn't set cur_node to NULL");
}

/* Checks that convo_free frees memory allocated to a convo */
Test(dialogue, convo_free)
{
    convo_t *c;
    int rc;

    c = convo_new();
    
    cr_assert_not_null(c, "convo_new() failed");

    rc = convo_free(c);

    cr_assert_eq(rc, SUCCESS, "convo_free() failed");
}


/*** Dialogue Building Functions ***/

void check_add_node(int num_nodes)
{
    convo_t *c = convo_new();
    char node_id[3];
    char npc_dialogue[3];
    node_list_t *cur;
    int rc;

    strcpy(node_id, "N_");
    strcpy(npc_dialogue, "D_");

    for (int i = 1; i <= num_nodes && i < 10; i++) {
        node_id[1] = '0' + i;
        npc_dialogue[1] = '0' + i;

        rc = add_node(c, node_id, npc_dialogue);

        cr_assert_eq(rc, SUCCESS, "add_node() failed for Node %d", i);

        if (i == 1) cur = c->all_nodes;
        else cur = cur->next;

        cr_assert_not_null(cur, "add_node() did not append Node %d to "
                           "all_nodes in the convo", i);

        cr_assert_eq(strcmp(cur->node->node_id, node_id), 0,
                     "Expected %s for the node_id of Node %d but add_node set "
                     "a different value", node_id, i);
        cr_assert_eq(strcmp(cur->node->npc_dialogue, npc_dialogue), 0,
                     "Expected %s for the npc_dialogue of Node %d but add_node "
                     "set a different value", npc_dialogue, i);
    }
}

/* Checks that add_node works for 1 node */
Test(dialogue, add_one_node)
{
    check_add_node(1);
}

/* Checks that add_node works for 2 nodes */
Test(dialogue, add_two_nodes)
{
    check_add_node(2);
}

/* Checks that add_node works for 5 nodes */
Test(dialogue, add_five_nodes)
{
    check_add_node(5);
}


void check_add_edge(int num_edges)
{
    convo_t *c = convo_new();
    char quip[3];
    edge_list_t *convo_lst_ptr, *node_lst_ptr;
    int rc;

    add_node(c, "N1", "D1");
    add_node(c, "N2", "D2");

    strcpy(quip, "Q_");

    for (int i = 1; i <= num_edges && i < 10; i++) {
        quip[1] = '0' + i;

        rc = add_edge(c, quip, "N1", "N2");

        cr_assert_eq(rc, SUCCESS, "add_edge() failed for Edge %d", i);

        if (i == 1) {
            convo_lst_ptr = c->all_edges;
            node_lst_ptr = c->all_nodes->node->edges;
        } else {
            convo_lst_ptr = convo_lst_ptr->next;
            node_lst_ptr = node_lst_ptr->next;
        }
        
        cr_assert_not_null(convo_lst_ptr, "add_edge() did not append Edge %d "
                           "to all_edges in the convo", i);
        cr_assert_not_null(node_lst_ptr, "add_edge() did not append Edge %d "
                           "to edges in Node 1", i);

        cr_assert_eq(strcmp(convo_lst_ptr->edge->quip, quip), 0,
                     "Expected %s for the quip of Edge %d but add_edge set "
                     "a different value", quip, i);
        cr_assert_eq(strcmp(convo_lst_ptr->edge->from->node_id, "N1"), 0,
                     "add_edge set the wrong from node for Edge %d", i);
        cr_assert_eq(strcmp(convo_lst_ptr->edge->to->node_id, "N2"), 0,
                     "add_edge set the wrong to node for Edge %d", i);
    }
}

/* Checks that add_edge works for 1 edge */
Test(dialogue, add_one_edge)
{
    check_add_edge(1);
}

/* Checks that add_edge works for 2 edges */
Test(dialogue, add_two_edges)
{
    check_add_edge(2);
}

/* Checks that add_edge works for 5 edges */
Test(dialogue, add_five_edges)
{
    check_add_edge(5);
}

/* Checks that add_edge works for a set of bidirectional edges */
Test(dialogue, add_bidirectional_edges)
{
    convo_t *c = convo_new();
    int rc;

    add_node(c, "N1", "D1");
    add_node(c, "N2", "D2");

    rc = add_edge(c, "Q1", "N1", "N2");
    cr_assert_eq(rc, SUCCESS, "First add_edge() failed");

    rc = add_edge(c, "Q2", "N2", "N1");
    cr_assert_eq(rc, SUCCESS, "Second add_edge() failed");

    cr_assert_eq(strcmp(c->all_nodes->node->edges->edge->quip, "Q1"), 0,
                 "add_edge failed to add edge to Node 1");
    cr_assert_eq(strcmp(c->all_nodes->next->node->edges->edge->quip, "Q2"), 0,
                 "add_edge failed to add edge to Node 2");
}

