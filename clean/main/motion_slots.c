/* The four motion slots of a player's record (motion_slots.h). */
#include "motion_slots.h"

#include "clean.h"
#include "player_record.h"
#include "player_records.h"

/* The current player's slots. */
static u8 *current_slots(void)
{
    return PlayerRecord_Bytes23e8(PlayerRecords_Current());
}

/* func_0203f9e0: the first of the current player's slots holding `number`, or -1. */
int MotionSlots_Find(int number)
{
    u8 *slots = current_slots();

    for (int slot = 0; slot < MOTION_SLOTS; slot++) {
        if (number == MotionSlots_Read(slots, slot)) {
            return slot;
        }
    }
    return -1;
}
CLEAN_AS(func_0203f9e0, MotionSlots_Find)

/* func_0203fa14: what the current player's `slot` holds. */
int MotionSlots_Get(int slot)
{
    return MotionSlots_Read(current_slots(), slot);
}
CLEAN_AS(func_0203fa14, MotionSlots_Get)

/* func_0203fa2c: the current player's `slot` set to `number`. */
void MotionSlots_Set(int slot, int number)
{
    MotionSlots_Put(current_slots(), slot, number);
}
CLEAN_AS(func_0203fa2c, MotionSlots_Set)

/* func_0203fa4c: the current player's first empty slot, or -1. */
int MotionSlots_FindEmpty(void)
{
    return MotionSlots_Find(MOTION_SLOT_EMPTY);
}
CLEAN_AS(func_0203fa4c, MotionSlots_FindEmpty)

/* func_0203fa58: how many of the current player's slots are not empty. */
int MotionSlots_Count(void)
{
    u8 *slots = current_slots();
    int count = 0;

    for (int slot = 0; slot < MOTION_SLOTS; slot++) {
        if (MotionSlots_Read(slots, slot) != MOTION_SLOT_EMPTY) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_0203fa58, MotionSlots_Count)

/* func_0203fa84: every slot empty. */
void MotionSlots_Clear(u8 *slots)
{
    for (int slot = 0; slot < MOTION_SLOTS; slot++) {
        slots[slot] = MOTION_SLOT_EMPTY;
    }
}
CLEAN_AS(func_0203fa84, MotionSlots_Clear)

/* func_0203fa94: `slot` set to `number` (its low byte). */
void MotionSlots_Put(u8 *slots, int slot, int number)
{
    slots[slot] = (u8) number;
}
CLEAN_AS(func_0203fa94, MotionSlots_Put)

/* func_0203fa98: what `slot` holds. */
int MotionSlots_Read(u8 *slots, int slot)
{
    return slots[slot];
}
CLEAN_AS(func_0203fa98, MotionSlots_Read)
