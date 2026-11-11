/* The four reaction slots of a player's record (reaction_slots.h). */
#include "reaction_slots.h"

#include "clean.h"
#include "player_record.h"
#include "player_records.h"

/* The current player's slots. */
static u8 *current_slots(void)
{
    return PlayerRecord_ReactionSlots(PlayerRecords_Current());
}

/* func_0203f9e0: the first of the current player's slots holding `number`, or -1. */
int ReactionSlots_Find(int number)
{
    u8 *slots = current_slots();

    for (int slot = 0; slot < REACTION_SLOTS; slot++) {
        if (number == ReactionSlots_Read(slots, slot)) {
            return slot;
        }
    }
    return -1;
}
CLEAN_AS(func_0203f9e0, ReactionSlots_Find)

/* func_0203fa14: what the current player's `slot` holds. */
int ReactionSlots_At(int slot)
{
    return ReactionSlots_Read(current_slots(), slot);
}
CLEAN_AS(func_0203fa14, ReactionSlots_At)

/* func_0203fa2c: the current player's `slot` set to `number`. */
void ReactionSlots_Set(int slot, int number)
{
    ReactionSlots_Put(current_slots(), slot, number);
}
CLEAN_AS(func_0203fa2c, ReactionSlots_Set)

/* func_0203fa4c: the current player's first empty slot, or -1. */
int ReactionSlots_FindEmpty(void)
{
    return ReactionSlots_Find(REACTION_SLOT_EMPTY);
}
CLEAN_AS(func_0203fa4c, ReactionSlots_FindEmpty)

/* func_0203fa58: how many of the current player's slots are not empty. */
int ReactionSlots_Count(void)
{
    u8 *slots = current_slots();
    int count = 0;

    for (int slot = 0; slot < REACTION_SLOTS; slot++) {
        if (ReactionSlots_Read(slots, slot) != REACTION_SLOT_EMPTY) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_0203fa58, ReactionSlots_Count)

/* func_0203fa84: every slot empty. */
void ReactionSlots_Clear(u8 *slots)
{
    for (int slot = 0; slot < REACTION_SLOTS; slot++) {
        slots[slot] = REACTION_SLOT_EMPTY;
    }
}
CLEAN_AS(func_0203fa84, ReactionSlots_Clear)

/* func_0203fa94: `slot` set to `number` (its low byte). */
void ReactionSlots_Put(u8 *slots, int slot, int number)
{
    slots[slot] = (u8) number;
}
CLEAN_AS(func_0203fa94, ReactionSlots_Put)

/* func_0203fa98: what `slot` holds. */
int ReactionSlots_Read(u8 *slots, int slot)
{
    return slots[slot];
}
CLEAN_AS(func_0203fa98, ReactionSlots_Read)
