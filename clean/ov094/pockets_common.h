/* Overlay 094's small helpers that the pockets scenes (ov096/pockets_screen.h,
 * ov098/pockets_town.h, ov100/pockets_box.h) and the letter storage (ov105/letter_storage.h)
 * call: three menu sounds and tests of an item code by its ranges. The insects are items
 * 0x12b0-0x12e7 and the fish 0x12e8-0x131f (ov098/pockets_town.h); the items 0x1408-0x1428 and
 * 0x1471-0x1491 are worn (main/item_traits.h); 0x155f and 0x1560 turn into another item
 * overnight (main/player_record.c). */
#ifndef CLEAN_OV094_POCKETS_COMMON_H
#define CLEAN_OV094_POCKETS_COMMON_H

#include "types.h"

void PocketsSound_Play0d(void);
void PocketsSound_Play0c(void);
void PocketsSound_Play0e(void);
int PocketsItem_CanUse(unsigned int item);
int PocketsItem_Is155d(u16 item);
int PocketsItem_IsDayItem(u16 item);
int PocketsItem_IsIn155fTo1564(u16 item);
int PocketsItem_InLetterRefusedRanges(unsigned int item);

#endif
