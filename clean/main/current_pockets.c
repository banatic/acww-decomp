/* The pockets of this system's player (current_pockets.h). */
#include "current_pockets.h"

#include "clean.h"
#include "item_code.h"
#include "item_record.h"
#include "player_pockets.h"
#include "player_record.h"
#include "player_records.h"
#include "item_form.h"
#include "item_lists.h"
#include "item_traits.h"

/* An item marked in the record of items when a 0x151f is given in state 0. */
#define CURRENT_POCKETS_151F 0x151f
#define CURRENT_POCKETS_151F_MARK 0x1033
/* The item that is given as an item drawn from a list instead (CurrentPockets_ReceiveAt). */
#define CURRENT_POCKETS_DRAWN_ITEM 0x156b
#define CURRENT_POCKETS_DRAW_KIND 0
#define CURRENT_POCKETS_DRAW_GROUP 3
/* Codes CurrentPockets_Receive takes without putting anything in a slot. */
#define CURRENT_POCKETS_SKIPPED_FIRST 0xa7
#define CURRENT_POCKETS_SKIPPED_LAST 0xc6

/* An item list: func_02063ccc constructs it, func_020638d4 draws an item of it,
 * func_02063cc8 destroys it. */
typedef struct CurrentPocketsItemList {
    int kind;
    int group;
} CurrentPocketsItemList;

/* Whether the slot's item is `*item`: for codes with a variant (ItemCode_HasVariant), the item
 * without its variant is compared. */
static int current_pockets_same_item(const u16 *slot, const u16 *item)
{
    if (ItemCode_HasVariant(slot)) {
        int slot_item = ItemCode_VariantItem(slot);
        return slot_item == ItemCode_VariantItem(item);
    }
    return *slot == *item;
}

/* func_02099e9c: the first slot in state 0 that holds `*item`, or -1. */
int CurrentPockets_FindItem(const u16 *item)
{
    u8 *record = PlayerRecords_Current();
    u16 *slots = PlayerPockets_Slot(PlayerRecord_Pockets(record), 0);
    for (int i = 0; i < PLAYER_POCKETS_SLOTS; i++) {
        if (PlayerPockets_SlotStateIsZero(PlayerRecord_Pockets(record), i) == 0) {
            continue;
        }
        if (current_pockets_same_item(&slots[i], item)) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_02099e9c, CurrentPockets_FindItem)

/* func_02099f1c: `marks` cleared, then each slot in state 0 for which `test` (a function of the
 * game) answers nonzero marked; how many were marked. */
int CurrentPockets_Mark(PocketsMarks *marks, int (*test)(u16 *item))
{
    u8 *record = PlayerRecords_Current();
    PocketsMarks_Clear(marks);
    u16 *slots = PlayerPockets_Slot(PlayerRecord_Pockets(record), 0);
    for (int i = 0; i < PLAYER_POCKETS_SLOTS; i++) {
        if (PlayerPockets_SlotStateIsZero(PlayerRecord_Pockets(record), i) && test(&slots[i])) {
            marks->slots |= (u16) (1u << i);
            marks->count++;
        }
    }
    return marks->count;
}
CLEAN_AS(func_02099f1c, CurrentPockets_Mark)

/* func_02099f7c: `marks` cleared, then each slot in state 0 whose item is of `item_class`
 * (func_0204c520) marked; how many were marked. */
u8 CurrentPockets_MarkClass(PocketsMarks *marks, int item_class)
{
    u8 *record = PlayerRecords_Current();
    PocketsMarks_Clear(marks);
    u16 *slots = PlayerPockets_Slot(PlayerRecord_Pockets(record), 0);
    for (int i = 0; i < PLAYER_POCKETS_SLOTS; i++) {
        if (PlayerPockets_SlotStateIsZero(PlayerRecord_Pockets(record), i) != 0) {
            if (ItemTraits_Class(&slots[i]) == item_class) {
                marks->slots |= (u16) (1u << i);
                marks->count++;
            }
        }
    }
    return marks->count;
}
CLEAN_AS(func_02099f7c, CurrentPockets_MarkClass)

/* func_02099fe0 */
void PocketsMarks_Clear(PocketsMarks *marks)
{
    marks->count = 0;
    marks->slots = 0;
}
CLEAN_AS(func_02099fe0, PocketsMarks_Clear)

/* func_02099fe8: the first empty slot, or -1. */
int CurrentPockets_FreeSlot(void)
{
    return PlayerPockets_FreeSlot(PlayerRecord_Pockets(PlayerRecords_Current()));
}
CLEAN_AS(func_02099fe8, CurrentPockets_FreeSlot)

/* func_0209a000: `*item`, in its pocket form, put in the first empty slot in `state`
 * (CurrentPockets_Set); 0 when there is none. */
int CurrentPockets_Give(const u16 *item, int state)
{
    int slot = CurrentPockets_FreeSlot();
    if (slot == -1) {
        return 0;
    }
    u16 carried;
    ItemForm_ToCarried(&carried, (u16 *) item);
    CurrentPockets_Set(&carried, state, slot);
    return 1;
}
CLEAN_AS(func_0209a000, CurrentPockets_Give)

/* func_0209a034: the slot's item. REQUIRES: slot 0-14 (else NULL is read). */
u16 CurrentPockets_Item(u32 slot)
{
    return *PlayerPockets_Slot(PlayerRecord_Pockets(PlayerRecords_Current()), (int) slot);
}
CLEAN_AS(func_0209a034, CurrentPockets_Item)

/* func_0209a050: the slot emptied, in state 0; nothing outside 0-14. */
void CurrentPockets_Empty(int slot)
{
    u8 *record = PlayerRecords_Current();
    if (PlayerPockets_IsSlot(slot)) {
        u16 none = PLAYER_POCKETS_NO_ITEM;
        PlayerPockets_SetSlot(PlayerRecord_Pockets(record), &none, slot, 0);
    }
}
CLEAN_AS(func_0209a050, CurrentPockets_Empty)

/* func_0209a088: `*item` put in the slot in `state`; nothing outside 0-14. In state 0 an item
 * is marked in the record of items, and a 0x151f also marks 0x1033. */
void CurrentPockets_Set(u16 *item, int state, int slot)
{
    u8 *record = PlayerRecords_Current();
    if (PlayerPockets_IsSlot(slot) == 0) {
        return;
    }
    if (*item != PLAYER_POCKETS_NO_ITEM && state == 0) {
        ItemRecord_SetBit((ItemRecord *) PlayerRecord_ItemRecord(record), item, 0, 1);
    }
    if (state == 0 && *item == CURRENT_POCKETS_151F) {
        u16 mark = CURRENT_POCKETS_151F_MARK;
        ItemRecord_SetBit((ItemRecord *) PlayerRecord_ItemRecord(record), &mark, 0, 1);
    }
    PlayerPockets_SetSlot(PlayerRecord_Pockets(record), item, slot, state);
}
CLEAN_AS(func_0209a088, CurrentPockets_Set)

/* func_0209a110: `*item` put in the first empty slot (CurrentPockets_ReceiveAt); 0 when there
 * is none, else 1. QUIRK: nothing (0xfff1) and the codes 0xa7-0xc6 also give 1 but put nothing
 * in. */
int CurrentPockets_Receive(u16 *item)
{
    int slot = CurrentPockets_FreeSlot();
    if (slot == -1) {
        return 0;
    }
    u16 code = *item;
    if (code == PLAYER_POCKETS_NO_ITEM) {
        return 1;
    }
    if (code >= CURRENT_POCKETS_SKIPPED_FIRST && code <= CURRENT_POCKETS_SKIPPED_LAST) {
        return 1;
    }
    CurrentPockets_ReceiveAt(item, (u32) slot);
    return 1;
}
CLEAN_AS(func_0209a110, CurrentPockets_Receive)

/* func_0209a14c: `*item` put in the slot: a 0x156b as an item drawn for it
 * (CurrentPockets_DrawFor156B) in state 1, any other in its pocket form in state 0. */
void CurrentPockets_ReceiveAt(u16 *item, u32 slot)
{
    u16 given;
    int state = 0;
    if (*item == CURRENT_POCKETS_DRAWN_ITEM) {
        given = CurrentPockets_DrawFor156B();
        state = 1;
    } else {
        u16 carried;
        ItemForm_ToCarried(&carried, item);
        given = carried;
    }
    CurrentPockets_Set(&given, state, (int) slot);
}
CLEAN_AS(func_0209a14c, CurrentPockets_ReceiveAt)

/* func_0209a19c: an item drawn from item list 0, group 3. */
u16 CurrentPockets_DrawFor156B(void)
{
    u16 item;
    CurrentPocketsItemList list;
    ItemList_Construct((ItemList *) &list, CURRENT_POCKETS_DRAW_KIND, CURRENT_POCKETS_DRAW_GROUP);
    ItemLists_Draw(&item, (ItemList *) &list, 0, 0, 1, 1, 0);
    ItemList_Destruct(&list);
    return item;
}
CLEAN_AS(func_0209a19c, CurrentPockets_DrawFor156B)

/* func_0209a1d0: the first empty letter place, or NULL. */
Letter *CurrentPockets_FreeLetter(void)
{
    return PlayerPockets_FreeLetter(PlayerRecord_Pockets(PlayerRecords_Current()));
}
CLEAN_AS(func_0209a1d0, CurrentPockets_FreeLetter)

/* func_0209a1e8: the index of the first empty letter place, or -1. */
int CurrentPockets_FreeLetterIndex(void)
{
    return PlayerPockets_FreeLetterIndex(PlayerRecord_Pockets(PlayerRecords_Current()));
}
CLEAN_AS(func_0209a1e8, CurrentPockets_FreeLetterIndex)
