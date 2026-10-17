/* Behaviours 6, 7, 8, 10, 11, 13, 14, 15 and 16 of a villager out walking in the town (its
 * behaviour member at 0x8b8, outdoor_villager.h): their starts, their updates and the steps
 * the updates run, as outdoor_villager_acts.h describes them (each update runs the step its
 * byte `step` names from a table of member pointers filled the first time; a step out of the
 * table does nothing; updates answer 0, starts 1).
 *
 * - 6, told of event 5: the villager makes one of the gestures of its action's motion 7 at
 *   this console's player, chosen by its fondness for the player and its personality, the
 *   player's field actor asked for state 0x11; once the action ends its event is finished
 *   and behaviour 0 is the one to resume.
 * - 7 (its talk then says lines 2): the villager comes up to this console's player: animation
 *   0xdf (at its frame 9 one of two effects and sounds at its joint 16), then walks to the
 *   player; within 0x3000 of the player and facing it, motion kind 11; it turns to face the
 *   player again when the player moves off, walks after the player again, and gives up
 *   (behaviour 0, its record's byte 0x1e halved; lowered by 1 when the player is gone) when the
 *   wait runs out or it has walked 0xc000 from where it started. Behaviours 21 (the count at
 *   0xa06 at its limit) and 19 (the byte at 0xa05) take over.
 * - 8, told an event starts: when it is not paired, its reaction is none and the byte at
 *   0xa04 is clear, it turns to the participant (priority 2) and stands.
 * - 10, it joined a talk as a speaker: it stands (priority 2), the byte at 0x838 set; its
 *   update does nothing.
 * - 11 (while its effect's countdown runs, outdoor_villager.h): it turns to this console's
 *   player and stands until the countdown is out (behaviour 0), or behaviours 21 or 19 take
 *   over (the countdown then cleared).
 * - 13: it is put a little away from the first of the items 0x5014 to 0x501a on the town's
 *   map, facing it; music value 0x12, the state table's index at 0x16c cleared (-1), the event
 *   queue's flag 0x20 set; its update asks for event kind 6 and sets flag 0x1d of the player
 *   actor 4 each frame.
 * - 14, told of event 1 after reaction 0: it turns to the object of its talk and talks; once
 *   the action ends the camera's mode is reset, it turns to angle 0 and walks to its place
 *   moved by (-0x2000, +0x8000); when there (or after 200 frames) its event is finished, it
 *   stands and the event queue's flag 0x20 is cleared.
 * - 15 and 16: the item it holds is brought out or put away. With an item of 0x1380 to 0x139f
 *   (the held item link's action 0x25 group, held_item_link.c) animation 0xcd plays with the
 *   item's own animation (16 runs the item's frames backwards, from the last); without one,
 *   animation 0xd6 while the item's scale grows from 0 to 1.0 (15) or shrinks to 0 (16), by
 *   0x249 a frame. The byte at 0x9f0 is set when the item is out and cleared once it is put
 *   away; 16 takes the item away (0xfff1, none) at the end, and from the villager's held item
 *   at its start. */
#ifndef CLEAN_OV068_OUTDOOR_VILLAGER_MOVES_H
#define CLEAN_OV068_OUTDOOR_VILLAGER_MOVES_H

#include "outdoor_villager.h"
#include "types.h"

int OutdoorVillagerMoves_Update16(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerMoves_Close16(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerMoves_Shrink16(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerMoves_Start16(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerMoves_Update15(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerMoves_Open15(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerMoves_Grow15(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerMoves_Start15(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerMoves_Update14(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerMoves_Arrive14(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerMoves_Walk14(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerMoves_Talk14(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerMoves_Start14(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerMoves_Update13(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerMoves_Start13(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerMoves_Update11(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerMoves_Watch11(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerMoves_Turn11(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerMoves_Start11(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerMoves_Update10(void);
int OutdoorVillagerMoves_Start10(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerMoves_Update8(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerMoves_Turn8(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerMoves_Start8(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerMoves_Update7(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerMoves_Wait7(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerMoves_Turn7(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerMoves_Near7(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerMoves_Walk7(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerMoves_Call7(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerMoves_PlayerInReach(OutdoorVillagerBehaviour *self, u8 *villager, int range);
int OutdoorVillagerMoves_NearStart(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerMoves_Start7(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerMoves_Update6(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerMoves_Idle6(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerMoves_Wait6(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerMoves_Start6(OutdoorVillagerBehaviour *self, u8 *villager);

#endif
