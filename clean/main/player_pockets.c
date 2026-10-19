/* A player's pockets: letters, item slots and the wallet (player_pockets.h). */
#include "player_pockets.h"

#include "clean.h"
#include "item_traits.h"
#include "letter.h"

static_assert(offsetof(PlayerPockets, letter_defaults) == 0xa00, "PlayerPockets layout");
static_assert(offsetof(PlayerPockets, items) == 0xa4a, "PlayerPockets layout");
static_assert(offsetof(PlayerPockets, bells) == 0xa68, "PlayerPockets layout");
static_assert(offsetof(PlayerPockets, states) == 0xa6c, "PlayerPockets layout");
static_assert(sizeof(PlayerPockets) == 0xa70, "PlayerPockets layout");

/* The largest bag index (from the first bag) PlayerPockets_SmallestBag takes, with and without
 * the biggest bag. */
#define BAG_INDEX_ALL (PLAYER_POCKETS_BAG_LAST - PLAYER_POCKETS_BAG_FIRST)
#define BAG_INDEX_BELOW_BIGGEST (BAG_INDEX_ALL - 1)

/* Sums and differences of bells wrap around as the ARM's do. */
static int wrap_add(int a, int b)
{
    return (int) ((u32) a + (u32) b);
}

static int wrap_sub(int a, int b)
{
    return (int) ((u32) a - (u32) b);
}

static int wrap_mul(int a, int b)
{
    return (int) ((u32) a * (u32) b);
}

/* A shift left by a register, as the ARM does it: by the amount's low byte, nothing left from
 * 32 on. */
static u32 arm_shift_left(u32 value, u32 amount)
{
    amount &= 0xff;
    return amount >= 32 ? 0 : value << amount;
}

static int is_bag(u16 item)
{
    return item >= PLAYER_POCKETS_BAG_FIRST && item <= PLAYER_POCKETS_BAG_LAST;
}

/* func_02098a24: add `amount` bells (or take them, when negative) to the wallet. When it does
 * not hold enough, with `use_bags` == 1 the rest is taken from the bags and the change goes into
 * the wallet (held to 0-99999); else the wallet is emptied. */
void PlayerPockets_AddBells(PlayerPockets *pockets, int amount, int use_bags)
{
    int bells = wrap_add(amount, PlayerPockets_Bells(pockets, 0));
    if (bells < 0) {
        if (use_bags == PLAYER_POCKETS_USE_BAGS) {
            bells = PlayerPockets_PayFromBags(pockets, wrap_sub(0, bells));
            if (bells < 0) {
                bells = 0;
            } else if (bells > PLAYER_POCKETS_WALLET_MAX) {
                bells = PLAYER_POCKETS_WALLET_MAX;
            }
        } else {
            bells = 0;
        }
    }
    PlayerPockets_SetBells(pockets, bells, use_bags);
}
CLEAN_AS(func_02098a24, PlayerPockets_AddBells)

/* func_02098a6c: whether `amount` bells fit (when not negative) or can be paid (when negative):
 * the room and the bells counted as PlayerPockets_BellsRoom and PlayerPockets_Bells do. */
int PlayerPockets_CanChangeBells(PlayerPockets *pockets, int amount, int with_bags, int extra_bags)
{
    if (amount >= 0) {
        return amount <= PlayerPockets_BellsRoom(pockets, with_bags, extra_bags);
    }
    return wrap_sub(0, amount) <= PlayerPockets_Bells(pockets, with_bags);
}
CLEAN_AS(func_02098a6c, PlayerPockets_CanChangeBells)

/* func_02098aa0: set the wallet to `bells`, at least 0. Bells beyond 99,999 go into bags with
 * `use_bags` == 1 (what does not fit is lost); else the wallet is filled. */
void PlayerPockets_SetBells(PlayerPockets *pockets, int bells, int use_bags)
{
    if (bells < 0) {
        bells = 0;
    }
    if (bells > PLAYER_POCKETS_WALLET_MAX) {
        if (use_bags == PLAYER_POCKETS_USE_BAGS) {
            u32 rest = PlayerPockets_PutInBags(pockets, (u32) bells);
            bells = rest <= PLAYER_POCKETS_WALLET_MAX ? (int) rest : PLAYER_POCKETS_WALLET_MAX;
        } else {
            bells = PLAYER_POCKETS_WALLET_MAX;
        }
    }
    pockets->bells = bells;
}
CLEAN_AS(func_02098aa0, PlayerPockets_SetBells)

/* func_02098adc: pay `owed` bells (at least 0) with bags, smallest first, each taken bag's slot
 * emptied (state 0). The change of the last bag; or, when the bags ran out, minus what is still
 * owed. */
int PlayerPockets_PayFromBags(PlayerPockets *pockets, int owed)
{
    if (owed < 0) {
        owed = 0;
    }
    while (owed > 0) {
        int slot = PlayerPockets_SmallestBag(pockets, 1);
        if (slot == -1) {
            break;
        }
        u16 bag = *PlayerPockets_Slot(pockets, slot);
        u16 none = PLAYER_POCKETS_NO_ITEM;
        PlayerPockets_SetSlot(pockets, &none, slot, 0);
        owed = wrap_sub(owed, ItemTraits_Price(&bag));
    }
    return wrap_sub(0, owed);
}
CLEAN_AS(func_02098adc, PlayerPockets_PayFromBags)

/* func_02098b44: put bells beyond 99,999 into bags of the biggest kind: each in an empty slot,
 * else in place of a smaller bag (whose bells it takes over), slot state 0. The bells left. */
u32 PlayerPockets_PutInBags(PlayerPockets *pockets, u32 bells)
{
    u16 biggest = PLAYER_POCKETS_BAG_LAST;
    int biggest_bells = ItemTraits_Price(&biggest);
    while (bells > PLAYER_POCKETS_WALLET_MAX) {
        int slot = PlayerPockets_PlaceForBag(pockets);
        if (slot == -1) {
            break;
        }
        u16 old = *PlayerPockets_Slot(pockets, slot);
        if (is_bag(old)) {
            PlayerPockets_SetSlot(pockets, &biggest, slot, 0);
            bells -= (u32) wrap_sub(biggest_bells, ItemTraits_Price(&old));
        } else {
            if (old != PLAYER_POCKETS_NO_ITEM) {
                break;
            }
            PlayerPockets_SetSlot(pockets, &biggest, slot, 0);
            bells -= (u32) biggest_bells;
        }
    }
    return bells;
}
CLEAN_AS(func_02098b44, PlayerPockets_PutInBags)

/* func_02098be8: where a bag of the biggest kind can go: the first empty slot, else the
 * smallest bag below the biggest; -1 for none. */
int PlayerPockets_PlaceForBag(PlayerPockets *pockets)
{
    const u16 *items = PlayerPockets_Slot(pockets, 0);
    for (int slot = 0; slot < PLAYER_POCKETS_SLOTS; slot++) {
        if (items[slot] == PLAYER_POCKETS_NO_ITEM) {
            return slot;
        }
    }
    return PlayerPockets_SmallestBag(pockets, 0);
}
CLEAN_AS(func_02098be8, PlayerPockets_PlaceForBag)

/* func_02098c2c: the first slot holding the smallest bag in slot state 0, among all bags with
 * `with_biggest` == 1, else among those below the biggest; -1 for none. */
int PlayerPockets_SmallestBag(PlayerPockets *pockets, int with_biggest)
{
    const u16 *items = PlayerPockets_Slot(pockets, 0);
    int smallest = with_biggest == 1 ? BAG_INDEX_ALL : BAG_INDEX_BELOW_BIGGEST;
    int found = -1;
    for (int slot = 0; slot < PLAYER_POCKETS_SLOTS; slot++) {
        if (!is_bag(items[slot]) || PlayerPockets_SlotState(pockets, slot) != 0) {
            continue;
        }
        int index = items[slot] - PLAYER_POCKETS_BAG_FIRST;
        if (index < smallest || (found == -1 && index == smallest)) {
            smallest = index;
            found = slot;
        }
    }
    return found;
}
CLEAN_AS(func_02098c2c, PlayerPockets_SmallestBag)

/* func_02098cc0: the bells the pockets can still take: the wallet's room, plus with
 * `with_bags` == 1 the bags' room (PlayerPockets_BagsRoom). */
int PlayerPockets_BellsRoom(PlayerPockets *pockets, int with_bags, int extra_bags)
{
    int room = wrap_sub(PLAYER_POCKETS_WALLET_MAX, PlayerPockets_Bells(pockets, 0));
    if (room < 0) {
        room = 0;
    }
    if (with_bags == 1) {
        room = wrap_add(room, PlayerPockets_BagsRoom(pockets, extra_bags));
    }
    return room;
}
CLEAN_AS(func_02098cc0, PlayerPockets_BellsRoom)

/* func_02098cf8: the wallet's bells, plus with `with_bags` the bags' (PlayerPockets_BagsBells). */
int PlayerPockets_Bells(PlayerPockets *pockets, int with_bags)
{
    int bells = pockets->bells;
    if (with_bags != 0) {
        bells = wrap_add(bells, PlayerPockets_BagsBells(pockets));
    }
    return bells;
}
CLEAN_AS(func_02098cf8, PlayerPockets_Bells)

/* func_02098d14: the bells bags can still take: a biggest bag's worth for each of
 * `extra_bags` and each empty slot, and for each bag in slot state 0 what it lacks of the
 * biggest. */
int PlayerPockets_BagsRoom(PlayerPockets *pockets, int extra_bags)
{
    u16 *item = PlayerPockets_Slot(pockets, 0);
    u16 biggest = PLAYER_POCKETS_BAG_LAST;
    int biggest_bells = ItemTraits_Price(&biggest);
    int room = wrap_mul(extra_bags, biggest_bells);
    for (int slot = 0; slot < PLAYER_POCKETS_SLOTS; slot++, item++) {
        if (*item == PLAYER_POCKETS_NO_ITEM) {
            room = wrap_add(room, biggest_bells);
        } else if (is_bag(*item) && PlayerPockets_SlotState(pockets, slot) == 0) {
            room = wrap_add(room, wrap_sub(biggest_bells, ItemTraits_Price(item)));
        }
    }
    return room;
}
CLEAN_AS(func_02098d14, PlayerPockets_BagsRoom)

/* func_02098d84: the bells in the bags in slot state 0. */
int PlayerPockets_BagsBells(PlayerPockets *pockets)
{
    u16 *item = PlayerPockets_Slot(pockets, 0);
    int bells = 0;
    for (int slot = 0; slot < PLAYER_POCKETS_SLOTS; slot++, item++) {
        if (is_bag(*item) && PlayerPockets_SlotState(pockets, slot) == 0) {
            bells = wrap_add(bells, ItemTraits_Price(item));
        }
    }
    return bells;
}
CLEAN_AS(func_02098d84, PlayerPockets_BagsBells)

/* func_02098ddc */
u8 *PlayerPockets_LetterDefaults(PlayerPockets *pockets)
{
    return pockets->letter_defaults;
}
CLEAN_AS(func_02098ddc, PlayerPockets_LetterDefaults)

/* func_02098de8: the first empty letter place, or NULL. */
Letter *PlayerPockets_FreeLetter(PlayerPockets *pockets)
{
    int index = PlayerPockets_FreeLetterIndex(pockets);
    if (PlayerPockets_IsLetterIndex(index) == 1) {
        return PlayerPockets_Letter(pockets, index);
    }
    return NULL;
}
CLEAN_AS(func_02098de8, PlayerPockets_FreeLetter)

/* func_02098e10: the index of the first empty letter place, or -1. */
int PlayerPockets_FreeLetterIndex(PlayerPockets *pockets)
{
    Letter *letter = PlayerPockets_Letter(pockets, 0);
    for (int index = 0; index < PLAYER_POCKETS_LETTERS; index++, letter++) {
        if (Letter_State(letter) == 0) {
            return index;
        }
    }
    return -1;
}
CLEAN_AS(func_02098e10, PlayerPockets_FreeLetterIndex)

/* func_02098e44: letter place `index`; NULL outside 0-9. */
Letter *PlayerPockets_Letter(PlayerPockets *pockets, int index)
{
    if (PlayerPockets_IsLetterIndex(index) == 1) {
        return &pockets->letters[index];
    }
    return NULL;
}
CLEAN_AS(func_02098e44, PlayerPockets_Letter)

/* func_02098e64 */
int PlayerPockets_IsLetterIndex(int index)
{
    return index >= 0 && index < PLAYER_POCKETS_LETTERS;
}
CLEAN_AS(func_02098e64, PlayerPockets_IsLetterIndex)

/* func_02098e74: whether the slot's state is 0 (also outside 0-14). */
int PlayerPockets_SlotStateIsZero(PlayerPockets *pockets, int slot)
{
    return PlayerPockets_SlotState(pockets, slot) == 0;
}
CLEAN_AS(func_02098e74, PlayerPockets_SlotStateIsZero)

/* func_02098e8c: the slot's state (0-3); 0 outside 0-14. */
int PlayerPockets_SlotState(PlayerPockets *pockets, int slot)
{
    if (PlayerPockets_IsSlot(slot) == 1) {
        return (int) ((pockets->states >> (slot * 2)) & 3);
    }
    return 0;
}
CLEAN_AS(func_02098e8c, PlayerPockets_SlotState)

/* func_02098eb8: the first empty slot, or -1. */
int PlayerPockets_FreeSlot(PlayerPockets *pockets)
{
    const u16 *items = PlayerPockets_Slot(pockets, 0);
    for (int slot = 0; slot < PLAYER_POCKETS_SLOTS; slot++) {
        if (items[slot] == PLAYER_POCKETS_NO_ITEM) {
            return slot;
        }
    }
    return -1;
}
CLEAN_AS(func_02098eb8, PlayerPockets_FreeSlot)

/* func_02098ee8: set the slot's state. QUIRK: neither is checked: `state` is not cut to two
 * bits, so a larger one also sets the next slots' bits, and a slot past 15 shifts by the ARM's
 * rule (its doubled number's low byte; nothing from 32 on). */
void PlayerPockets_SetSlotState(PlayerPockets *pockets, u32 slot, u32 state)
{
    u32 shift = slot << 1;
    u32 mask = arm_shift_left(3, shift);
    pockets->states = (pockets->states & ~mask) | arm_shift_left(state, shift);
}
CLEAN_AS(func_02098ee8, PlayerPockets_SetSlotState)

/* func_02098f0c: put `*item` in the slot, in `state`; 0 outside 0-14, else 1. */
int PlayerPockets_SetSlot(PlayerPockets *pockets, const u16 *item, int slot, int state)
{
    if (PlayerPockets_IsSlot(slot) != 1) {
        return 0;
    }
    pockets->items[slot] = *item;
    PlayerPockets_SetSlotState(pockets, (u32) slot, (u32) state);
    return 1;
}
CLEAN_AS(func_02098f0c, PlayerPockets_SetSlot)

/* func_02098f48: the slot's item code; NULL outside 0-14. */
u16 *PlayerPockets_Slot(PlayerPockets *pockets, int slot)
{
    if (PlayerPockets_IsSlot(slot) == 1) {
        return &pockets->items[slot];
    }
    return NULL;
}
CLEAN_AS(func_02098f48, PlayerPockets_Slot)

/* func_02098f70 */
int PlayerPockets_IsSlot(int slot)
{
    return slot >= 0 && slot < PLAYER_POCKETS_SLOTS;
}
CLEAN_AS(func_02098f70, PlayerPockets_IsSlot)

/* func_02098f80: empty the letters and the item slots, set up the letter defaults and empty
 * the wallet. QUIRK: the slots' states are left as they were. */
void PlayerPockets_Init(PlayerPockets *pockets)
{
    for (int i = 0; i < PLAYER_POCKETS_LETTERS; i++) {
        Letter_Clear(&pockets->letters[i]);
    }
    LetterDefaults_Init((LetterDefaults *) (void *) pockets->letter_defaults);
    for (int slot = 0; slot < PLAYER_POCKETS_SLOTS; slot++) {
        pockets->items[slot] = PLAYER_POCKETS_NO_ITEM;
    }
    PlayerPockets_SetBells(pockets, 0, PLAYER_POCKETS_USE_BAGS);
}
CLEAN_AS(func_02098f80, PlayerPockets_Init)
