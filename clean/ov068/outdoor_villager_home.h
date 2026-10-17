/* Behaviours 2, 3, 4 and 12 of a villager out walking in the town (its behaviour member at
 * 0x8b8, outdoor_villager.h): going into its house, staying in, coming out, and staying in for
 * good. Each is a start and an update whose steps run by the byte `step`, as
 * outdoor_villager_acts.h describes them.
 *
 * The house's tile is its town record's (VillagerHome_Tile); the villager goes in and comes out
 * at the centre of the tile in front of it (z + 1), facing the house (angle -0x8000) or away
 * from it (0). The house itself is an actor of overlay 3 (character 0x5001 + the villager's
 * index, func_ov003_02220174), asked by func_ov003_02220318 (coming out) and
 * func_ov003_02220340 (going in): each answers nonzero once it lets the villager through.
 *
 * - 2: it turns to face the house (motion kind 3, priority 2), held and with the byte at 0x838
 *   set; once turned (or once a walk, kind 1, ends, in step 1) and the house agrees, animation
 *   0x3b, its shadow off; during it, it is drawn to the tile's centre by 0x400 a frame and
 *   plays its footsteps at frames 8, 12, 22, 27 and 34; at its end behaviour 3.
 * - 3: in its house: standing, unseen (the byte at 0x562 cleared, the state entry's state 0),
 *   its furniture's items stored; asleep (the entry's byte 0x01 is 2) at its sleep time unless
 *   the current player has flag 1. Each frame it is disabled (the byte at 0x561). Asleep, it
 *   wakes once its sleep time is over (the wait then 600 to 639 frames); awake, it waits. When
 *   it comes out: on screen (OutdoorVillagerWalks_OnScreen) behaviour 4 unless this console's
 *   player is within 0x6000; off screen it is put in front of the house at once and walks on
 *   (behaviour 0, showing its held item). Every 900 frames in, its record's byte 0x1e rises
 *   (VillagerEntry_RaiseByte1E).
 * - 4: it is put in front of the house, raised 0x1000, facing away; once the house agrees,
 *   animation 0x3d (its held item drawn by the draw hook at 0x8b0) and the state entry's state
 *   1; at its end its shadow on, its collider 0xd00, no longer held, and behaviour 15 (to bring
 *   its held item out, then behaviour 0) or behaviour 0. During the animation it plays its
 *   footsteps at frames 13, 17, 23, 28, 37 and 40.
 * - 12: as 3, kept in: it stands at the house's own tile, unseen and not shared (the byte at
 *   0x563), and is disabled at its second step; its update does nothing more. */
#ifndef CLEAN_OV068_OUTDOOR_VILLAGER_HOME_H
#define CLEAN_OV068_OUTDOOR_VILLAGER_HOME_H

#include "outdoor_villager.h"
#include "types.h"

int OutdoorVillagerHome_Update4(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerHome_Leave4(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerHome_Open4(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerHome_Start4(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerHome_Update12(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerHome_Hide12(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerHome_Begin12(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerHome_Start12(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerHome_Update3(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerHome_Stay3(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerHome_Begin3(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerHome_Start3(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerHome_Update2(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerHome_Enter2(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerHome_AfterWalk2(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerHome_AfterTurn2(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerHome_Start2(OutdoorVillagerBehaviour *self, u8 *villager);

#endif
