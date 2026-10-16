/* The 15 entries of main's queue of events (data_021c72e8, a C++ global array of
 * EventQueueEntry, event_queue.h): an entry is free while its state is EVENT_FREE. */
#ifndef CLEAN_MAIN_EVENT_ENTRIES_H
#define CLEAN_MAIN_EVENT_ENTRIES_H

#include "autoload_2/links.h"
#include "event_queue.h"
#include "types.h"

#define EVENT_ENTRIES 15

/* EventQueueEntry.priority of a constructed entry. */
#define EVENT_ENTRY_NO_PRIORITY 0xff

EventQueueEntry *EventEntries_FindFree(void);
void EventEntries_FreeAll(void);
void EventEntries_FreeList(List *list);
void EventEntries_Free(EventQueueEntry *entry);
void EventEntries_Construct(EventQueueEntry *entry);

#endif
