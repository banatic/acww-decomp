/* A sound of overlay 4's scenes, the kind of the last scene actor of overlay 9 that went away
 * (data_021f4b48), and the two flags of a new player's arrival: data_021f4b18 set when the
 * taxi has brought the player into town (ov051 TaxiDriver_UpdateArrive), data_021f4b1c when
 * the town hall's clerk sends the player out (ov054 PostClerk_UpdateLeave); both cleared when
 * overlay 68's welcome sequence (sequence4.c) lets go. While either is set no special
 * character comes (Spawner_ArrivalPending) and the scene starts with the arrival music
 * (music_264.c). */
#ifndef CLEAN_MAIN_BLOCK_020B220C_H
#define CLEAN_MAIN_BLOCK_020B220C_H

#include "types.h"

void Block020b220c_PlaySceneSound(void);
int Block020b220c_GoneKind(void);
void Block020b220c_SetGoneKind(unsigned int kind);
u8 Block020b220c_ArrivedByTaxi(void);
void Block020b220c_ClearArrivedByTaxi(void);
void Block020b220c_SetArrivedByTaxi(void);
u8 Block020b220c_SentOutByClerk(void);
void Block020b220c_ClearSentOutByClerk(void);
void Block020b220c_SetSentOutByClerk(void);

#endif
