/* A villager out walking in the town (outdoor_villager.h): the vtable slots of its life as a
 * scene object (start, init, frame, draw, leave), its making, and the things its frame watches:
 * how long this console's player has pushed against it, and the held item it shows.
 *
 * Its slots here: 0x00 start, 0x04 init, 0x0c leave, 0x24 draw, 0x60 told of an item the
 * player swung at it, 0x68 the frame (called first in each frame), 0xa8 whether its state
 * entry is linked, 0xb0 its effect's countdown taken.
 *
 * Starting, it takes its first behaviour by its town record: 13 for the villager the state
 * table names at 0x16c, 12 for the one named at 0x162 and for a status of 3 to 7, 0 (with its
 * held item shown, when it has one) for a status of 0, else 3 (in its house).
 *
 * Each frame: the push count (to 100 at the byte 0xa06, while this console's player walks into
 * it within about 70 degrees of straight at it, and the villager is shown, posed, enabled,
 * idle and remembers the player), the tally of its state entry, its behaviour, its effect, its
 * mood and its watch, and the byte 0xa05 cleared. */
#ifndef CLEAN_OV068_OUTDOOR_VILLAGER_OBJECT_H
#define CLEAN_OV068_OUTDOOR_VILLAGER_OBJECT_H

#include "types.h"

int OutdoorVillagerObject_Frame(u8 *villager);
void OutdoorVillagerObject_ResetActEffects(u8 *villager);
void OutdoorVillagerObject_CountPushed(u8 *villager);
int OutdoorVillagerObject_PushedByPlayer(u8 *villager);
void OutdoorVillagerObject_ShowHeldItem(u8 *villager);
int OutdoorVillagerObject_TakeCountdown(u8 *villager);
int OutdoorVillagerObject_OnItemSwung(u8 *villager, u16 *item);
int OutdoorVillagerObject_Leave(u8 *villager);
int OutdoorVillagerObject_Draw(u8 *villager);
int OutdoorVillagerObject_DrawWithItem(u8 *villager);
int OutdoorVillagerObject_Start(u8 *villager);
int OutdoorVillagerObject_Init(u8 *villager);
int OutdoorVillagerObject_IsLinked(u8 *villager);
u8 *OutdoorVillagerObject_New(void);

#endif
