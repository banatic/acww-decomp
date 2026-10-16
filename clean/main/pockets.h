/* The current player's 15 pocket slots, as seen from main: each holds an item code
 * (item_code.h) and a two-bit state, read with func_02098f48 / func_02098e8c and written with
 * func_0209a088. Screens take a copy of the slots (Pockets_Save), change the copy and write it
 * back (Pockets_Restore); a second list of 15 codes names items to convert in the copy
 * (Pockets_ConvertListed). */
#ifndef CLEAN_MAIN_POCKETS_H
#define CLEAN_MAIN_POCKETS_H

#include "types.h"

#define POCKET_SLOTS 15

/* Asked of each slot by Pockets_Select: its code and its state. */
typedef int (*PocketPredicate)(u16 *item, int state);

u16 Pockets_Select(PocketPredicate predicate);
void Pockets_ReplaceInCopy(u16 item, u16 replacement);
void Pockets_ConvertListed(int convert);
u16 *Pockets_List(void);
void Pockets_SetList(u16 *items);
void Pockets_Restore(void);
void Pockets_Save(void);

#endif
