/* The pockets of this system's player (PlayerRecords_Current, then PlayerRecord_Pockets): items
 * looked up, given and taken out of the 15 slots, and the letters' places.
 *
 * An item given goes in in its pocket form (func_02061e2c) and, in slot state 0, is marked in
 * the player's record of items (PlayerRecord_ItemRecord); a 0x151f given in state 0 also marks
 * the item 0x1033. */
#ifndef CLEAN_MAIN_CURRENT_POCKETS_H
#define CLEAN_MAIN_CURRENT_POCKETS_H

#include "mail.h"
#include "types.h"

/* The slots that matched a test: one bit for each slot and how many there are. */
typedef struct PocketsMarks {
    u16 slots; /* bit i: slot i */
    u8 count;
} PocketsMarks;

int CurrentPockets_FindItem(const u16 *item);
int CurrentPockets_Mark(PocketsMarks *marks, int (*test)(u16 *item));
u8 CurrentPockets_MarkClass(PocketsMarks *marks, int item_class);
void PocketsMarks_Clear(PocketsMarks *marks);
int CurrentPockets_FreeSlot(void);
int CurrentPockets_Give(const u16 *item, int state);
u16 CurrentPockets_Item(u32 slot);
void CurrentPockets_Empty(int slot);
void CurrentPockets_Set(u16 *item, int state, int slot);
int CurrentPockets_Receive(u16 *item);
void CurrentPockets_ReceiveAt(u16 *item, u32 slot);
u16 CurrentPockets_DrawFor156B(void);
Letter *CurrentPockets_FreeLetter(void);
int CurrentPockets_FreeLetterIndex(void);

#endif
