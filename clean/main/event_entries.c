/* The entries of main's queue of events (event_entries.h). */
#include "event_entries.h"

#include "clean.h"

extern EventQueueEntry data_021c72e8[EVENT_ENTRIES];

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

static_assert(sizeof(EventQueueEntry) == 0x1c, "EventQueueEntry size");
static_assert(offsetof(EventQueueEntry, state) == 0x14, "EventQueueEntry layout");

/* func_0203f504: the first free entry (it stays free until filled); NULL when all are taken. */
EventQueueEntry *EventEntries_FindFree(void)
{
    for (int i = 0; i < EVENT_ENTRIES; i++) {
        if (data_021c72e8[i].state == EVENT_FREE) {
            return &data_021c72e8[i];
        }
    }
    return NULL;
}
CLEAN_AS(func_0203f504, EventEntries_FindFree)

/* func_0203f53c: every entry freed.
 * QUIRK: then 15 bytes are cleared, not 15 entries: the first entry's links, its priority and
 * the low three bytes of its first id. */
void EventEntries_FreeAll(void)
{
    for (int i = 0; i < EVENT_ENTRIES; i++) {
        EventEntries_Free(&data_021c72e8[i]);
    }
    MI_CpuFill8(data_021c72e8, 0, EVENT_ENTRIES);
}
CLEAN_AS(func_0203f53c, EventEntries_FreeAll)

/* func_0203f568: each entry of `list` taken out of it and freed. */
void EventEntries_FreeList(List *list)
{
    ListNode *node = list->first;

    while (node != NULL) {
        ListNode *next = node->next;
        List_Remove(list, node);
        EventEntries_Free((EventQueueEntry *) node);
        node = next;
    }
}
CLEAN_AS(func_0203f568, EventEntries_FreeList)

/* func_0203f58c: the entry free, about no object. */
void EventEntries_Free(EventQueueEntry *entry)
{
    entry->state = EVENT_FREE;
    entry->first_id = 0;
    entry->second_id = 0;
}
CLEAN_AS(func_0203f58c, EventEntries_Free)

/* func_0203f598: an entry's constructor: unlinked, with no priority. */
void EventEntries_Construct(EventQueueEntry *entry)
{
    entry->link.prev = NULL;
    entry->link.next = NULL;
    entry->priority = EVENT_ENTRY_NO_PRIORITY;
}
CLEAN_AS(func_0203f598, EventEntries_Construct)
