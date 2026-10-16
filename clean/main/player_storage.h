/* The town's storage of 90 items for each of its four players (PlayerStorage, player_record.h;
 * data_021f2fa8, 0x16800 of the state block). 0xfff1 marks an empty place. */
#ifndef CLEAN_MAIN_PLAYER_STORAGE_H
#define CLEAN_MAIN_PLAYER_STORAGE_H

#include "player_record.h"
#include "types.h"

#define PLAYER_STORAGE_NONE 0xfff1

u16 *PlayerStorage_Items(PlayerStorage *storage);
void PlayerStorage_Clear(u16 *items);
void PlayerStorage_Destruct(PlayerStorage *storage);
void PlayerStorage_Construct(PlayerStorage *storage);

#endif
