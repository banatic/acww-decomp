/* The main program's melody set (data_021cfbcc, a MelodySet of autoload_2/sound_melody.h) and
 * the town tune it plays.
 *
 * The town tune is kept in the save's state block at 0x173c0 (data_021f3b68) as 16 steps of
 * 4 bits each, step i in bits 4i to 4i+3 of a 64-bit word, and unpacked one step to a byte at
 * data_021cfbbc; the functions below hand the set to the sound layer's (sound.h's SoundSet).
 * Each frame the set is updated (TownTune_Update): the second player's
 * step is kept at data_020df2a0 (-1 while it plays nothing), and a delay at data_021cfbac,
 * set when the first player starts, counts down. */
#ifndef CLEAN_MAIN_TOWN_TUNE_H
#define CLEAN_MAIN_TOWN_TUNE_H

#include "autoload_2/sound_melody.h"
#include "autoload_2/vector.h"
#include "types.h"

/* The tune packed: two words of the 64-bit value, the low one first. */
typedef struct TownTunePacked {
    u32 low;
    u32 high;
} TownTunePacked;

#define TOWN_TUNE_STEPS 16
#define TOWN_TUNE_STEP_BITS 4

/* The delays TownTune_StartFirst sets, in frames. */
#define TOWN_TUNE_DELAY_LONG 400
#define TOWN_TUNE_DELAY_SHORT 20

void TownTune_Update(void);
void TownTune_Init(void);
void TownTune_StoreDefault(void);
void TownTune_StorePreset(void);
int TownTune_PlayRandomPreset(int number);
int TownTune_IsBusy(void);
void TownTune_PlaySeqD3(int index);
void TownTune_StartFirst(int long_delay);
void TownTune_PlayAt(const Vec3 *pos, int kind);
void TownTune_PlayOwn(int number);
void TownTune_Play(unsigned int number);
void TownTune_UseTune(void);
void TownTune_Load(const TownTunePacked *packed);
void TownTune_Store(TownTunePacked *packed);
void TownTune_Unpack(const TownTunePacked *packed, u8 *steps);
void TownTune_Pack(TownTunePacked *packed, const u8 *steps);
void *TownTune_DestructSet(MelodySet *set);

#endif
