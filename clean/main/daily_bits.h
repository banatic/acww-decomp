/* A player record's daily bits (the object at 0x23ec, PlayerRecord_Field23EC): 64 bits that
 * are cleared each new day (PlayerRecord_UpdateSinceLastPlay) and the date one was last set.
 * Bit 0x18 is the one the spawner tests (Spawner_PlayerLacksFlag18). */
#ifndef CLEAN_MAIN_DAILY_BITS_H
#define CLEAN_MAIN_DAILY_BITS_H

#include "types.h"

#define DAILY_BITS_WORDS 2

typedef struct DailyBits {
    u8 day; /* 0x0: the date a bit was last set */
    u8 month;
    u8 year;
    u8 unk_3;
    u32 words[DAILY_BITS_WORDS]; /* 0x4 */
} DailyBits;

void DailyBits_Clear(DailyBits *bits, u32 bit);
void DailyBits_Set(DailyBits *bits, u32 bit);
int DailyBits_Test(DailyBits *bits, u32 bit);
void DailyBits_SetDate(u8 *date, const u8 *source);
void DailyBits_ClearAll(DailyBits *bits);
void DailyBits_Destruct(DailyBits *bits);
void DailyBits_Construct(DailyBits *bits);

#endif
