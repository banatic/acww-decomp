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
extern PlayerOptions *func_0203d4b8(void); /* &data_021c6998 */
extern int func_0203d4a8(void);            /* its flag */
extern int func_0203d470(void);            /* its sound flag */

/* func_0203d22c */
void PlayerOptions_MarkSettingChanged(PlayerOptions *options)
{
    options->changed |= PLAYER_OPTIONS_SETTING_CHANGED;
}
CLEAN_AS(func_0203d22c, PlayerOptions_MarkSettingChanged)

/* func_0203d238 */
void PlayerOptions_MarkSoundChanged(PlayerOptions *options)
{
    options->changed |= PLAYER_OPTIONS_SOUND_CHANGED;
}
CLEAN_AS(func_0203d238, PlayerOptions_MarkSoundChanged)

/* func_0203d244 */
void PlayerOptions_MarkFlagChanged(PlayerOptions *options)
{
    options->changed |= PLAYER_OPTIONS_FLAG_CHANGED;
}
CLEAN_AS(func_0203d244, PlayerOptions_MarkFlagChanged)

/* func_0203d250 */
int PlayerOptions_SettingChanged(const PlayerOptions *options)
{
    return (options->changed & PLAYER_OPTIONS_SETTING_CHANGED) != 0;
}
CLEAN_AS(func_0203d250, PlayerOptions_SettingChanged)

/* func_0203d264 */
int PlayerOptions_SoundChanged(const PlayerOptions *options)
{
    return (options->changed & PLAYER_OPTIONS_SOUND_CHANGED) != 0;
}
CLEAN_AS(func_0203d264, PlayerOptions_SoundChanged)

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
    options->changed &= (u8) ~PLAYER_OPTIONS_SETTING_CHANGED;
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

/* func_0203d2d4: the setting (its low two bits). */
void PlayerOptions_SetSetting(u8 *values, unsigned int setting)
{
    *values = (u8) ((*values & ~PLAYER_OPTIONS_SETTING_MASK) | ((setting & 3) << PLAYER_OPTIONS_SETTING_SHIFT));
}
CLEAN_AS(func_0203d2d4, PlayerOptions_SetSetting)

/* func_0203d2ec */
int PlayerOptions_Setting(const u8 *values)
{
    return (*values & PLAYER_OPTIONS_SETTING_MASK) >> PLAYER_OPTIONS_SETTING_SHIFT;
}
CLEAN_AS(func_0203d2ec, PlayerOptions_Setting)

/* func_0203d2f4 */
void PlayerOptions_ClearSound(u8 *values)
{
    *values &= (u8) ~PLAYER_OPTIONS_SOUND;
}
CLEAN_AS(func_0203d2f4, PlayerOptions_ClearSound)

/* func_0203d300 */
void PlayerOptions_SetSound(u8 *values)
{
    *values |= PLAYER_OPTIONS_SOUND;
}
CLEAN_AS(func_0203d300, PlayerOptions_SetSound)

/* func_0203d30c */
int PlayerOptions_Sound(const u8 *values)
{
    return (*values & PLAYER_OPTIONS_SOUND) != 0;
}
CLEAN_AS(func_0203d30c, PlayerOptions_Sound)

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
    PlayerOptions_ClearSound(values);
    PlayerOptions_SetSetting(values, 0);
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
    PlayerOptions *in_use = func_0203d4b8();
    u8 values;

    if (PlayerOptions_FlagChanged(in_use)) {
        if (func_0203d4a8() == 1) {
            PlayerOptions_SetFlag(stored);
        } else {
            PlayerOptions_ClearFlag(stored);
        }
    }
    if (PlayerOptions_SoundChanged(in_use)) {
        if (func_0203d470() == 1) {
            PlayerOptions_SetSound(stored);
        } else {
            PlayerOptions_ClearSound(stored);
        }
    }
    if (PlayerOptions_SettingChanged(in_use)) {
        PlayerOptions_SetSetting(stored, (unsigned int) PlayerOptions_CurrentSetting());
    }
    PlayerOptions_CopyTo(stored, &values);
    PlayerOptions_Clear(in_use);
    PlayerOptions_CopyFrom(&in_use->values, &values);
}
CLEAN_AS(func_0203d394, PlayerOptions_Store)

/* func_0203d41c: the setting in use, marked changed. */
void PlayerOptions_ChangeSetting(unsigned int setting)
{
    PlayerOptions_SetSetting(&data_021c6998.values, setting);
    PlayerOptions_MarkSettingChanged(&data_021c6998);
}
CLEAN_AS(func_0203d41c, PlayerOptions_ChangeSetting)

/* func_0203d438: the setting in use. */
int PlayerOptions_CurrentSetting(void)
{
    return PlayerOptions_Setting(&data_021c6998.values);
}
CLEAN_AS(func_0203d438, PlayerOptions_CurrentSetting)

/* func_0203d448: the sound flag in use set (`on` is 1) or cleared, marked changed. */
void PlayerOptions_ChangeSound(int on)
{
    if (on == 1) {
        PlayerOptions_SetSound(&data_021c6998.values);
    } else {
        PlayerOptions_ClearSound(&data_021c6998.values);
    }
    PlayerOptions_MarkSoundChanged(&data_021c6998);
}
CLEAN_AS(func_0203d448, PlayerOptions_ChangeSound)
