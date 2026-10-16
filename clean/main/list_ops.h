/* Operations on the intrusive lists of links.h that main's queues and registries share: finding
 * a node by the key that follows its link, appending, inserting by a priority that follows its
 * link, and emptying.
 *
 * The scene objects' registry finds and appends (scene_object_base.h), the event queue and the
 * transfer queues insert by priority (event_queue.h, transfer_queue.h), and they and the
 * overlay task empty their lists. */
#ifndef CLEAN_MAIN_LIST_OPS_H
#define CLEAN_MAIN_LIST_OPS_H

#include "autoload_2/links.h"
#include "types.h"

/* A node with a key after its link (ListOps_FindByKey). */
typedef struct ListOpsKeyedNode {
    ListNode link;
    s32 key; /* 0x08: 0 is never found */
} ListOpsKeyedNode;

/* A node with a priority after its link (ListOps_InsertByPriority). */
typedef struct ListOpsPriorityNode {
    ListNode link;
    u8 priority; /* 0x08 */
} ListOpsPriorityNode;

ListOpsKeyedNode *ListOps_FindByKey(List *list, int key);
int ListOps_Append(List *list, ListNode *node);
int ListOps_InsertByPriority(List *list, ListOpsPriorityNode *node);
void ListOps_Clear(List *list);

#endif
