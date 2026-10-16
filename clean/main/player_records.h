/* The players' records (0x249c bytes each), by record number: 0-3 are the town's four players
 * (data_021dc7bc, func_02098844), 4-6 are guests from other towns in a linked session
 * (data_021d5738, PlayerRecords_Guests). A session player's record number comes from
 * func_02096284; PlayerRecords_Current is the record of this system's player. */
#ifndef CLEAN_MAIN_PLAYER_RECORDS_H
#define CLEAN_MAIN_PLAYER_RECORDS_H

#include "types.h"

#define PLAYER_RECORD_SIZE 0x249c
#define PLAYER_RECORDS_TOWN 4
#define PLAYER_RECORDS_GUESTS 3
/* The first guest record number. */
#define PLAYER_RECORD_FIRST_GUEST 4

int PlayerRecords_Exists(int number);
u8 *PlayerRecords_Get(int number);
int PlayerRecords_CurrentNumber(void);
u8 *PlayerRecords_Current(void);
u8 *PlayerRecords_OfPlayer(int player);
int PlayerRecords_GuestIndex(int number);
int PlayerRecords_IsGuest(int number);
void PlayerRecords_ClearGuests(void);
void PlayerRecords_ClearThree(u8 *records);
u8 *PlayerRecords_Guests(void);
u8 *PlayerRecords_DestructGuests(u8 *guests);
u8 *PlayerRecords_ConstructGuests(u8 *guests);
u8 *PlayerRecords_NewPlayer(u8 *players, const void *name, int arg, int number);

#endif
