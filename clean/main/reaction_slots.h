/* The reactions a player knows: four bytes of a player's record (at 0x23e8,
 * PlayerRecord_ReactionSlots), each the number of a reaction (1 to 59, the numbers of the acts
 * a villager's talk shows, as Obj020d8c64_TakeNewReaction hands them out) or
 * REACTION_SLOT_EMPTY. A new player's are all empty (ReactionSlots_Clear); overlay 88's
 * reaction teacher (ov088/reaction_npc.h) puts the ones it teaches in them, and overlay 95's
 * keyboard shows them as its emotion tabs (ov095/soft_keyboard.h). */
#ifndef CLEAN_MAIN_REACTION_SLOTS_H
#define CLEAN_MAIN_REACTION_SLOTS_H

#include "types.h"

#define REACTION_SLOTS 4
#define REACTION_SLOT_EMPTY 0xff

int ReactionSlots_Find(int number);
int ReactionSlots_Get(int slot);
void ReactionSlots_Set(int slot, int number);
int ReactionSlots_FindEmpty(void);
int ReactionSlots_Count(void);
void ReactionSlots_Clear(u8 *slots);
void ReactionSlots_Put(u8 *slots, int slot, int number);
int ReactionSlots_Read(u8 *slots, int slot);

#endif
