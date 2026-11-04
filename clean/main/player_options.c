/* A player's options (player_options.h): the bits of the values and of the changes, and storing
 * the changed options in the current player's record. */
#include "player_options.h"

#include "clean.h"
#include "player_record.h"
#include "player_records.h"

static_assert(sizeof(PlayerOptions) == 2, "the options in use");

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The options in use, and the three ways the game reads them (each one of the getters below on
 * data_021c6998). */
extern PlayerOptions data_021c6998;

/* func_0203d22c */
void PlayerOptions_MarkVoiceChanged(PlayerOptions *options)
{
    options->changed |= PLAYER_OPTIONS_VOICE_CHANGED;
}
CLEAN_AS(func_0203d22c, PlayerOptions_MarkVoiceChanged)

/* func_0203d238 */
void PlayerOptions_MarkStereoChanged(PlayerOptions *options)
{
    options->changed |= PLAYER_OPTIONS_SOUND_CHANGED;
}
CLEAN_AS(func_0203d238, PlayerOptions_MarkStereoChanged)

/* func_0203d244 */
void PlayerOptions_MarkFlagChanged(PlayerOptions *options)
{
    options->changed |= PLAYER_OPTIONS_FLAG_CHANGED;
}
CLEAN_AS(func_0203d244, PlayerOptions_MarkFlagChanged)

/* func_0203d250 */
int PlayerOptions_VoiceChanged(const PlayerOptions *options)
{
    return (options->changed & PLAYER_OPTIONS_VOICE_CHANGED) != 0;
}
CLEAN_AS(func_0203d250, PlayerOptions_VoiceChanged)

/* func_0203d264 */
int PlayerOptions_StereoChanged(const PlayerOptions *options)
{
    return (options->changed & PLAYER_OPTIONS_SOUND_CHANGED) != 0;
}
CLEAN_AS(func_0203d264, PlayerOptions_StereoChanged)

/* func_0203d278 */
int PlayerOptions_FlagChanged(const PlayerOptions *options)
{
    return (options->changed & PLAYER_OPTIONS_FLAG_CHANGED) != 0;
}
CLEAN_AS(func_0203d278, PlayerOptions_FlagChanged)

/* func_0203d28c: the values cleared, and nothing changed. */
void PlayerOptions_Clear(PlayerOptions *options)
{
    PlayerOptions_ClearValues(&options->values);
    options->changed &= (u8) ~PLAYER_OPTIONS_FLAG_CHANGED;
    options->changed &= (u8) ~PLAYER_OPTIONS_SOUND_CHANGED;
    options->changed &= (u8) ~PLAYER_OPTIONS_VOICE_CHANGED;
}
CLEAN_AS(func_0203d28c, PlayerOptions_Clear)

/* func_0203d2b4: an empty function called, `value` given back. */
int PlayerOptions_Empty2B4(int value)
{
    PlayerOptions_Nothing384();
    return value;
}
CLEAN_AS(func_0203d2b4, PlayerOptions_Empty2B4)

/* func_0203d2c4: the same with the other empty function. */
int PlayerOptions_Empty2C4(int value)
{
    PlayerOptions_Nothing390();
    return value;
}
CLEAN_AS(func_0203d2c4, PlayerOptions_Empty2C4)

/* func_0203d2d4: the voice (its low two bits). */
void PlayerOptions_SetVoice(u8 *values, unsigned int voice)
{
    *values = (u8) ((*values & ~PLAYER_OPTIONS_VOICE_MASK) | ((voice & 3) << PLAYER_OPTIONS_VOICE_SHIFT));
}
CLEAN_AS(func_0203d2d4, PlayerOptions_SetVoice)

/* func_0203d2ec */
int PlayerOptions_Voice(const u8 *values)
{
    return (*values & PLAYER_OPTIONS_VOICE_MASK) >> PLAYER_OPTIONS_VOICE_SHIFT;
}
CLEAN_AS(func_0203d2ec, PlayerOptions_Voice)

/* func_0203d2f4 */
void PlayerOptions_ClearStereo(u8 *values)
{
    *values &= (u8) ~PLAYER_OPTIONS_SOUND;
}
CLEAN_AS(func_0203d2f4, PlayerOptions_ClearStereo)

/* func_0203d300 */
void PlayerOptions_SetStereo(u8 *values)
{
    *values |= PLAYER_OPTIONS_SOUND;
}
CLEAN_AS(func_0203d300, PlayerOptions_SetStereo)

/* func_0203d30c */
int PlayerOptions_Stereo(const u8 *values)
{
    return (*values & PLAYER_OPTIONS_SOUND) != 0;
}
CLEAN_AS(func_0203d30c, PlayerOptions_Stereo)

/* func_0203d320 */
void PlayerOptions_ClearFlag(u8 *values)
{
    *values &= (u8) ~PLAYER_OPTIONS_FLAG;
}
CLEAN_AS(func_0203d320, PlayerOptions_ClearFlag)

/* func_0203d32c */
void PlayerOptions_SetFlag(u8 *values)
{
    *values |= PLAYER_OPTIONS_FLAG;
}
CLEAN_AS(func_0203d32c, PlayerOptions_SetFlag)

/* func_0203d338 */
int PlayerOptions_Flag(const u8 *values)
{
    return (*values & PLAYER_OPTIONS_FLAG) != 0;
}
CLEAN_AS(func_0203d338, PlayerOptions_Flag)

/* func_0203d34c: the values taken from `from`. */
void PlayerOptions_CopyFrom(u8 *values, const u8 *from)
{
    MI_CpuCopy8(from, values, 1);
}
CLEAN_AS(func_0203d34c, PlayerOptions_CopyFrom)

/* func_0203d35c: the values copied to `to`. */
void PlayerOptions_CopyTo(const u8 *values, u8 *to)
{
    MI_CpuCopy8(values, to, 1);
}
CLEAN_AS(func_0203d35c, PlayerOptions_CopyTo)

/* func_0203d368: every value 0. */
void PlayerOptions_ClearValues(u8 *values)
{
    PlayerOptions_ClearFlag(values);
    PlayerOptions_ClearStereo(values);
    PlayerOptions_SetVoice(values, 0);
}
CLEAN_AS(func_0203d368, PlayerOptions_ClearValues)

/* func_0203d384: nothing. */
void PlayerOptions_Nothing384(void) {}
CLEAN_AS(func_0203d384, PlayerOptions_Nothing384)

/* func_0203d388: the destructor of the record's byte: nothing. */
void PlayerOptions_Destruct(u8 *values)
{
    (void) values;
}
CLEAN_AS(func_0203d388, PlayerOptions_Destruct)

/* func_0203d38c: its constructor: nothing. */
void PlayerOptions_Construct(u8 *values)
{
    (void) values;
}
CLEAN_AS(func_0203d38c, PlayerOptions_Construct)

/* func_0203d390: nothing. */
void PlayerOptions_Nothing390(void) {}
CLEAN_AS(func_0203d390, PlayerOptions_Nothing390)

/* func_0203d394: each value of the options in use marked changed is stored in the current
 * player's record; then the options in use become the record's values, none changed. */
void PlayerOptions_Store(void)
{
    u8 *stored = PlayerRecord_Field1D3B(PlayerRecords_Current());
    PlayerOptions *in_use = (PlayerOptions *) (uintptr_t) PlayerOptions_InUse();
    u8 values;

    if (PlayerOptions_FlagChanged(in_use)) {
        if (PlayerOptions_FlagInUse() == 1) {
            PlayerOptions_SetFlag(stored);
        } else {
            PlayerOptions_ClearFlag(stored);
        }
    }
    if (PlayerOptions_StereoChanged(in_use)) {
        if (PlayerOptions_StereoInUse() == 1) {
            PlayerOptions_SetStereo(stored);
        } else {
            PlayerOptions_ClearStereo(stored);
        }
    }
    if (PlayerOptions_VoiceChanged(in_use)) {
        PlayerOptions_SetVoice(stored, (unsigned int) PlayerOptions_CurrentVoice());
    }
    PlayerOptions_CopyTo(stored, &values);
    PlayerOptions_Clear(in_use);
    PlayerOptions_CopyFrom(&in_use->values, &values);
}
CLEAN_AS(func_0203d394, PlayerOptions_Store)

/* func_0203d41c: the voice in use, marked changed. */
void PlayerOptions_ChangeVoice(unsigned int voice)
{
    PlayerOptions_SetVoice(&data_021c6998.values, voice);
    PlayerOptions_MarkVoiceChanged(&data_021c6998);
}
CLEAN_AS(func_0203d41c, PlayerOptions_ChangeVoice)

/* func_0203d438: the voice in use. */
int PlayerOptions_CurrentVoice(void)
{
    return PlayerOptions_Voice(&data_021c6998.values);
}
CLEAN_AS(func_0203d438, PlayerOptions_CurrentVoice)

/* func_0203d448: the stereo flag in use set (`on` is 1) or cleared, marked changed. */
void PlayerOptions_ChangeStereo(int on)
{
    if (on == 1) {
        PlayerOptions_SetStereo(&data_021c6998.values);
    } else {
        PlayerOptions_ClearStereo(&data_021c6998.values);
    }
    PlayerOptions_MarkStereoChanged(&data_021c6998);
}
CLEAN_AS(func_0203d448, PlayerOptions_ChangeStereo)

/* func_0203d470: the stereo flag in use. */
int PlayerOptions_StereoInUse(void)
{
    return PlayerOptions_Stereo(&data_021c6998.values);
}
CLEAN_AS(func_0203d470, PlayerOptions_StereoInUse)

/* func_0203d480: the flag in use set (`on` is 1) or cleared, marked changed. */
void PlayerOptions_ChangeFlag(int on)
{
    if (on == 1) {
        PlayerOptions_SetFlag(&data_021c6998.values);
    } else {
        PlayerOptions_ClearFlag(&data_021c6998.values);
    }
    PlayerOptions_MarkFlagChanged(&data_021c6998);
}
CLEAN_AS(func_0203d480, PlayerOptions_ChangeFlag)

/* func_0203d4a8: the flag in use. */
int PlayerOptions_FlagInUse(void)
{
    return PlayerOptions_Flag(&data_021c6998.values);
}
CLEAN_AS(func_0203d4a8, PlayerOptions_FlagInUse)

/* func_0203d4b8: the options in use, as an address. */
int PlayerOptions_InUse(void)
{
    return (int) (uintptr_t) &data_021c6998;
}
CLEAN_AS(func_0203d4b8, PlayerOptions_InUse)
