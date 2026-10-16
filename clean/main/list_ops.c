/* Operations on main's intrusive lists (list_ops.h). */
#include "list_ops.h"

#include "clean.h"

static_assert(offsetof(ListOpsKeyedNode, key) == 0x08, "keyed node");
static_assert(offsetof(ListOpsPriorityNode, priority) == 0x08, "priority node");

/* func_02065c00: the first node of `list` whose key is `key`, or NULL; NULL for key 0. */
ListOpsKeyedNode *ListOps_FindByKey(List *list, int key)
{
    if (key == 0) {
        return NULL;
    }
    for (ListNode *node = list->first; node != NULL; node = node->next) {
        ListOpsKeyedNode *keyed = (ListOpsKeyedNode *) node;
        if (keyed->key == key) {
            return keyed;
        }
    }
    return NULL;
}
CLEAN_AS(func_02065c00, ListOps_FindByKey)

/* func_02065c1c: `node` appended to `list`; always 1. */
int ListOps_Append(List *list, ListNode *node)
{
    List_PushBack(list, node);
    return 1;
}
CLEAN_AS(func_02065c1c, ListOps_Append)

/* func_02065c2c: `node` inserted after the last node of a priority not above its own; always 1.
 * QUIRK: the first node is never compared, so a node always goes after it, whatever their
 * priorities. Into an empty list the node goes as first and last with its own links left as
 * they are. */
int ListOps_InsertByPriority(List *list, ListOpsPriorityNode *node)
{
    if (list->first == NULL) {
        list->first = &node->link;
        list->last = &node->link;
        return 1;
    }

    ListNode *after = list->first;
    for (ListNode *next = after->next; next != NULL; next = next->next) {
        if (((ListOpsPriorityNode *) next)->priority > node->priority) {
            break;
        }
        after = next;
    }
    List_InsertAfter(list, &node->link, after);
    return 1;
}
CLEAN_AS(func_02065c2c, ListOps_InsertByPriority)

/* func_02065c68: `list` emptied: its first and last node forgotten (the nodes are not
 * touched). */
void ListOps_Clear(List *list)
{
    list->first = NULL;
    list->last = NULL;
}
CLEAN_AS(func_02065c68, ListOps_Clear)
