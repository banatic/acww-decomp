/* A town paired with a player's (16 bytes, the objects of func_020882b0-func_020882f0): a town
 * (StateBlockTown, 14 bytes), then a byte with a count of days in bits 0-3 (10 when paired;
 * func_02088404 takes days off it), a flag in bit 4 and one in bit 5. A player record keeps one
 * at 0x242c (PlayerRecord_Field242C), each exchange block (func_02090040) one at 0x93a
 * (func_02090124) and the state block one at 0x173e2.
 *
 * When players visit each other, each player without a paired town is paired with another
 * player of the session that has none either (over the Wi-Fi Connection, only one who is a
 * friend both ways): each record gets the other's town and 10 days, and one of the two, drawn
 * at random, the flag. Each pairing also goes into the exchange block the player is given
 * (Activity.block_source), from which the player's record takes it when the block has arrived
 * (PairedTown_TakeOwn). */
#ifndef CLEAN_MAIN_PAIRED_TOWN_H
#define CLEAN_MAIN_PAIRED_TOWN_H

#include "activity.h"
#include "types.h"

#define PAIRED_TOWN_SIZE 0x10
#define PAIRED_TOWN_DAYS 10

int PairedTown_AreFriends(Activity *activity, u8 *record, u8 *owner);
void PairedTown_Pair(Activity *activity, int player);
void PairedTown_Note(Activity *activity, u8 *pairing);
void PairedTown_PairAll(Activity *activity);
void PairedTown_PairOwn(Activity *activity);
void PairedTown_TakeOwn(void *unused);

/* The byte after the town: its days in bits 0-3 and the two flags. */
#define PAIRED_TOWN_STATE 0xe
#define PAIRED_TOWN_DAYS_MASK 0x0f
#define PAIRED_TOWN_FLAG_4 0x10
#define PAIRED_TOWN_FLAG_5 0x20

/* The state block keeps the current player's pairing at this offset (PairedTown_SaveCurrent,
 * PairedTown_RestoreCurrent). */
#define PAIRED_TOWN_STATE_BLOCK_OFFSET 0x173e2

void PairedTown_ClearFlag5(u8 *pairing);
void PairedTown_SetFlag5(u8 *pairing);
int PairedTown_Flag5(u8 *pairing);
void PairedTown_SetFlag4(u8 *pairing, u32 flag);
int PairedTown_Flag4(u8 *pairing);
void PairedTown_SetDays(u8 *pairing, u8 days);
int PairedTown_Days(u8 *pairing);
void PairedTown_SetTown(u8 *pairing, const void *town);
u8 *PairedTown_Town(u8 *pairing);
void PairedTown_Reset(u8 *pairing);
void PairedTown_RestoreCurrent(void);
void PairedTown_SaveCurrent(void);
int PairedTown_CurrentFlaggedInLastWeek(void);
int PairedTown_CurrentUnflaggedInLastWeek(void);
void PairedTown_PassDays(int days);
u8 *PairedTown_Destruct(u8 *pairing);
u8 *PairedTown_Construct(u8 *pairing);

#endif
