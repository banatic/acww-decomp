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

#endif
