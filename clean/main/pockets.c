/* A copy of the pocket slots, and the conversions made on it (pockets.h). */
#include "pockets.h"

#include <stdint.h>

#include "clean.h"

/* An item of 0x38e4-0x3933 (20 items of 4 variants each) converts to the item 0x50 codes
 * further on, in its first variant. */
#define CONVERT_FIRST 0x38e4
#define CONVERT_LAST 0x3933
#define CONVERTED_FIRST 0x3934

extern u16 data_021cfce8[POCKET_SLOTS]; /* the copy: each slot's item code */
extern u8 data_021cfcd8[POCKET_SLOTS];  /* and its state */
extern u16 data_021cfd08[POCKET_SLOTS]; /* the list of items to convert */

extern int func_020984e8(void);                            /* the current player's record */
extern int func_02099734(int player);                      /* its pockets (at 0x11a8) */
extern u16 *func_02098f48(void *pockets, int slot);        /* a slot's item code; NULL past 14 */
extern int func_02098e8c(void *pockets, int slot);         /* a slot's state (0-3); 0 past 14 */
extern void func_0209a088(u16 *item, int state, int slot); /* store a slot */

static void *pockets_of(int player)
{
    return (void *) (uintptr_t) func_02099734(player);
}

/* func_0206f9d8: the slots the predicate accepts, one bit each (bit n for slot n). */
u16 Pockets_Select(PocketPredicate predicate)
{
    int player = func_020984e8();
    u16 *items = func_02098f48(pockets_of(player), 0);
    u16 selected = 0;
    for (int slot = 0; slot < POCKET_SLOTS; slot++) {
        int state = func_02098e8c(pockets_of(player), slot);
        if (predicate(items + slot, state) != 0) {
            selected |= (u16) (1u << slot);
        }
    }
    return selected;
}
CLEAN_AS(func_0206f9d8, Pockets_Select)

/* func_0206fa58: in the copy, give the first slot holding `item` in state 0 the code
 * `replacement`. */
void Pockets_ReplaceInCopy(u16 item, u16 replacement)
{
    for (int slot = 0; slot < POCKET_SLOTS; slot++) {
        if (data_021cfce8[slot] == item && data_021cfcd8[slot] == 0) {
            data_021cfce8[slot] = replacement;
            return;
        }
    }
}
CLEAN_AS(func_0206fa58, Pockets_ReplaceInCopy)

/* func_0206fa8c: with `convert`, convert in the copy each listed item of the range that
 * converts (one slot for each time it is listed); then write the copy back to the pockets. */
void Pockets_ConvertListed(int convert)
{
    if (convert != 0) {
        for (int i = 0; i < POCKET_SLOTS; i++) {
            u16 item = data_021cfd08[i];
            if (item >= CONVERT_FIRST && item <= CONVERT_LAST) {
                int index = (item - CONVERT_FIRST) / 4;
                Pockets_ReplaceInCopy(item, (u16) (CONVERTED_FIRST + index * 4));
            }
        }
    }
    Pockets_Restore();
}
CLEAN_AS(func_0206fa8c, Pockets_ConvertListed)

/* func_0206faf0 */
u16 *Pockets_List(void)
{
    return data_021cfd08;
}
CLEAN_AS(func_0206faf0, Pockets_List)

/* func_0206faf8 */
void Pockets_SetList(u16 *items)
{
    for (int i = 0; i < POCKET_SLOTS; i++) {
        data_021cfd08[i] = items[i];
    }
}
CLEAN_AS(func_0206faf8, Pockets_SetList)

/* func_0206fb14: store each slot of the copy back into the pockets. QUIRK: it looks up the
 * player's pockets first and does not use them (func_0209a088 finds them itself). */
void Pockets_Restore(void)
{
    func_02099734(func_020984e8());
    for (int slot = 0; slot < POCKET_SLOTS; slot++) {
        u16 item = data_021cfce8[slot];
        func_0209a088(&item, data_021cfcd8[slot], slot);
    }
}
CLEAN_AS(func_0206fb14, Pockets_Restore)

/* func_0206fb58: copy the pockets' slots. */
void Pockets_Save(void)
{
    void *pockets = pockets_of(func_020984e8());
    for (int slot = 0; slot < POCKET_SLOTS; slot++) {
        data_021cfce8[slot] = *func_02098f48(pockets, slot);
        data_021cfcd8[slot] = (u8) func_02098e8c(pockets, slot);
    }
}
CLEAN_AS(func_0206fb58, Pockets_Save)
