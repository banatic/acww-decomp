/* Intrusive lists and trees (links.h). Each operation returns FALSE, and does nothing, when it
 * is given no node.
 *
 * REQUIRES: lists and nodes at word-aligned addresses, as every object of the game is; the
 * ARM stores a word to an unaligned address at the aligned one below it. */
#include "links.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"

static_assert(sizeof(ListNode) == 8, "list links");
static_assert(offsetof(TreeNode, next) == 12, "tree links");

/* func_020e8c70: `node` put first in `list`.
 * QUIRK: the node's own `prev` is left as it was, and its `next` too when the list is empty;
 * the callers hand over cleared nodes. */
BOOL List_PushFront(List *list, ListNode *node)
{
    if (node == NULL) {
        return FALSE;
    }
    if (list->first != NULL) {
        list->first->prev = node;
        node->next = list->first;
    } else {
        list->last = node;
    }
    list->first = node;
    return TRUE;
}
CLEAN_AS(func_020e8c70, List_PushFront)

/* func_020e8ca8: `node` put last in `list`. QUIRK: as List_PushFront, the node's `next` (and
 * `prev` in an empty list) are left as they were. */
BOOL List_PushBack(List *list, ListNode *node)
{
    if (node == NULL) {
        return FALSE;
    }
    if (list->last != NULL) {
        list->last->next = node;
        node->prev = list->last;
    } else {
        list->first = node;
    }
    list->last = node;
    return TRUE;
}
CLEAN_AS(func_020e8ca8, List_PushBack)

/* func_020e8ce0: `node` taken out of `list`, its links cleared. */
BOOL List_Remove(List *list, ListNode *node)
{
    if (node == NULL) {
        return FALSE;
    }
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else if (node == list->first) {
        list->first = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else if (node == list->last) {
        list->last = node->prev;
    }
    node->prev = NULL;
    node->next = NULL;
    return TRUE;
}
CLEAN_AS(func_020e8ce0, List_Remove)

/* func_020e8d50: `node` put after `after` in `list`, or first without `after`. */
BOOL List_InsertAfter(List *list, ListNode *node, ListNode *after)
{
    if (after == NULL) {
        return List_PushFront(list, node);
    }
    if (node == NULL) {
        return FALSE;
    }
    node->next = after->next;
    node->prev = after;
    after->next = node;
    if (node->next != NULL) {
        node->next->prev = node;
    } else {
        list->last = node;
    }
    return TRUE;
}
CLEAN_AS(func_020e8d50, List_InsertAfter)

/* func_020e8dbc: `node` taken out of its parent's children, or out of `tree` when it is the top;
 * a node with children of its own stays (FALSE).
 * QUIRK: the top node is found by having no parent, so taking out a node without parent and
 * without a previous sibling empties the tree whatever its siblings. */
BOOL Tree_Detach(Tree *tree, TreeNode *node)
{
    if (node == NULL || node->first_child != NULL) {
        return FALSE;
    }
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else if (node->parent != NULL) {
        node->parent->first_child = node->next;
    } else {
        tree->top = NULL;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    node->prev = NULL;
    node->next = NULL;
    node->parent = NULL;
    return TRUE;
}
CLEAN_AS(func_020e8dbc, Tree_Detach)

/* func_020e8e34: `node` added as the last child of `parent`, or as the tree's top without a
 * parent, which fails (FALSE) when the tree has one already.
 * QUIRK: the node's `next` is left as it was, and its `prev` when it is the first child; the
 * callers attach nodes made by TreeNode_Init. */
BOOL Tree_Attach(Tree *tree, TreeNode *node, TreeNode *parent)
{
    if (node == NULL) {
        return FALSE;
    }
    if (parent == NULL) {
        if (tree->top != NULL) {
            return FALSE;
        }
        tree->top = node;
        return TRUE;
    }
    node->parent = parent;
    TreeNode *last = parent->first_child;
    if (last == NULL) {
        parent->first_child = node;
        return TRUE;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = node;
    node->prev = last;
    return TRUE;
}
CLEAN_AS(func_020e8e34, Tree_Attach)

/* func_020e8ea8: a node with no links. */
void TreeNode_Clear(TreeNode *node)
{
    node->parent = NULL;
    node->first_child = NULL;
    node->prev = NULL;
    node->next = NULL;
}
CLEAN_AS(func_020e8ea8, TreeNode_Clear)

/* func_020e8ec0: the node's constructor; returns it. */
TreeNode *TreeNode_Init(TreeNode *node)
{
    TreeNode_Clear(node);
    return node;
}
CLEAN_AS(func_020e8ec0, TreeNode_Init)
