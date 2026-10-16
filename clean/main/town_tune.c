/* The main program's melody set and the town tune (town_tune.h). */
#include "town_tune.h"

#include "clean.h"
#include "sound.h"

static_assert(sizeof(TownTunePacked) == 8, "packed tune size");
static_assert(offsetof(MelodySet, player_b) == 0x14, "the set's second player");

extern MelodySet data_021cfbcc;           /* the set */
extern u8 data_021cfbbc[TOWN_TUNE_STEPS]; /* the tune, a step to a byte */
extern TownTunePacked data_021f3b68;      /* the tune in the save's state block (0x173c0) */
extern s32 data_021cfbac;                 /* the delay, in frames */
extern s32 data_020df2a0;                 /* the second player's step, -1: none */

#define STEP_MASK 0xf

/* func_0206e8d8: the frame's update: the delay counted down and the set updated. */
void TownTune_Update(void)
{
    if (data_021cfbac != 0) {
        data_021cfbac--;
    }
    data_020df2a0 = SoundSet_Poll(&data_021cfbcc);
}
CLEAN_AS(func_0206e8d8, TownTune_Update)

/* func_0206e904: the set made the sound layer's current one, its second player marked as
 * playing nothing, and the town tune made its melody. */
void TownTune_Init(void)
{
    SoundSet_MakeCurrent(&data_021cfbcc);
    data_020df2a0 = -1;
    TownTune_UseTune();
}
CLEAN_AS(func_0206e904, TownTune_Init)

/* func_0206e928: the sound layer's default melody stored as the town tune of the save. */
void TownTune_StoreDefault(void)
{
    const u8 *melody = SoundSet_Default(&data_021cfbcc);
    if (melody != NULL) {
        TownTune_Pack(&data_021f3b68, melody);
    }
}
CLEAN_AS(func_0206e928, TownTune_StoreDefault)

/* func_0206e94c: the preset melody the set last picked (TownTune_PlayRandomPreset) made its
 * melody and stored as the town tune of the save. */
void TownTune_StorePreset(void)
{
    const u8 *melody = SoundSet_LoadBlock((u8 *) &data_021cfbcc);
    if (melody != NULL) {
        TownTune_Pack(&data_021f3b68, melody);
    }
}
CLEAN_AS(func_0206e94c, TownTune_StorePreset)

/* func_0206e970: a preset melody picked at random and played as sound `number`. */
int TownTune_PlayRandomPreset(int number)
{
    return SoundSet_Load(&data_021cfbcc, (u32) number);
}
CLEAN_AS(func_0206e970, TownTune_PlayRandomPreset)

/* func_0206e980: whether the delay runs or the first player had a step playing at the last
 * update (asked only when there is no delay). */
int TownTune_IsBusy(void)
{
    return data_021cfbac != 0 || SoundSet_WasActive(&data_021cfbcc) != 0;
}
CLEAN_AS(func_0206e980, TownTune_IsBusy)

/* func_0206e9ac: the second player's sound `index` of sequence archive 0xd3. */
void TownTune_PlaySeqD3(int index)
{
    SoundSet_Call020f65fc(&data_021cfbcc, index);
}
CLEAN_AS(func_0206e9ac, TownTune_PlaySeqD3)

/* func_0206e9bc: the set's melody started on the first player, and the delay set: long when
 * `long_delay`, else short. */
void TownTune_StartFirst(int long_delay)
{
    SoundSet_Call020f66f0(&data_021cfbcc);
    data_021cfbac = long_delay ? TOWN_TUNE_DELAY_LONG : TOWN_TUNE_DELAY_SHORT;
}
CLEAN_AS(func_0206e9bc, TownTune_StartFirst)

/* func_0206e9ec: the set's melody played at `pos` as `kind` (MelodySet_PlayAt). */
void TownTune_PlayAt(const Vec3 *pos, int kind)
{
    SoundSet_LoadAt(&data_021cfbcc, pos, kind);
}
CLEAN_AS(func_0206e9ec, TownTune_PlayAt)

/* func_0206ea00: the set's melody played as sound `number`. */
void TownTune_PlayOwn(int number)
{
    SoundSet_LoadOwn(&data_021cfbcc, (u32) number);
}
CLEAN_AS(func_0206ea00, TownTune_PlayOwn)

/* func_0206ea10: the town tune played as sound `number`. */
void TownTune_Play(unsigned int number)
{
    SoundSet_LoadWith(&data_021cfbcc, number, data_021cfbbc);
}
CLEAN_AS(func_0206ea10, TownTune_Play)

/* func_0206ea28: the town tune copied into the set's melody. */
void TownTune_UseTune(void)
{
    SoundSet_SetBlock((u8 *) &data_021cfbcc, data_021cfbbc);
}
CLEAN_AS(func_0206ea28, TownTune_UseTune)

/* func_0206ea3c: the tune `packed` unpacked as the town tune and made the set's melody. */
void TownTune_Load(const TownTunePacked *packed)
{
    TownTune_Unpack(packed, data_021cfbbc);
    TownTune_UseTune();
}
CLEAN_AS(func_0206ea3c, TownTune_Load)

/* func_0206ea54: the sound layer's default melody stored as the town tune of the save.
 * QUIRK: `packed` is not used; the tune is always stored at data_021f3b68 (which is where the
 * state block's tune, the only one passed, is). */
void TownTune_Store(TownTunePacked *packed)
{
    (void) packed;
    TownTune_StoreDefault();
}
CLEAN_AS(func_0206ea54, TownTune_Store)

static u64 packed_value(const TownTunePacked *packed)
{
    return ((u64) packed->high << 32) | packed->low;
}

/* func_0206ea5c: the 16 steps of `packed` unpacked, one to a byte of `steps`. The packed
 * value is read again for each step. */
void TownTune_Unpack(const TownTunePacked *packed, u8 *steps)
{
    for (int i = 0; i < TOWN_TUNE_STEPS; i++) {
        steps[i] = (u8) ((packed_value(packed) >> (i * TOWN_TUNE_STEP_BITS)) & STEP_MASK);
    }
}
CLEAN_AS(func_0206ea5c, TownTune_Unpack)

/* func_0206ea84: the 16 steps of `steps` (their low 4 bits) packed into `packed`, which is
 * cleared first and written again after each step. */
void TownTune_Pack(TownTunePacked *packed, const u8 *steps)
{
    packed->low = 0;
    packed->high = 0;
    for (int i = 0; i < TOWN_TUNE_STEPS; i++) {
        u64 value = packed_value(packed) | ((u64) (steps[i] & STEP_MASK) << (i * TOWN_TUNE_STEP_BITS));
        packed->low = (u32) value;
        packed->high = (u32) (value >> 32);
    }
}
CLEAN_AS(func_0206ea84, TownTune_Pack)

/* func_0206eac0: the set's destructor: its second player's and then its first player's. The
 * set's address is the answer. */
void *TownTune_DestructSet(MelodySet *set)
{
    MelodyPlayer_Destruct(&set->player_b);
    MelodyPlayer_Destruct(&set->player_a);
    return set;
}
CLEAN_AS(func_0206eac0, TownTune_DestructSet)
