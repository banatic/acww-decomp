/* A player's options: one byte in the player's record (at 0x1d3b, PlayerRecord_Field1D3B) and
 * the options in use (data_021c6998), two bytes: the same byte of values, then a byte saying
 * which of them changed since they were last stored in the player's record
 * (PlayerOptions_Store).
 *
 *   values   bit 0     a flag (func_0203d480 sets it from a two-way choice)
 *            bit 1     the sound flag: the sound capture effect is data_020d1b90[flag]
 *            bits 2-3  a setting of three values (0-2)
 *   changed  bit 0     bit 0 of the values changed
 *            bit 1     the sound flag changed
 *            bit 2     the setting changed
 *
 * The functions on the values take either object; those on the changes only the options in
 * use. */
#ifndef CLEAN_MAIN_PLAYER_OPTIONS_H
#define CLEAN_MAIN_PLAYER_OPTIONS_H

#include "types.h"

#define PLAYER_OPTIONS_FLAG 0x01
#define PLAYER_OPTIONS_SOUND 0x02
#define PLAYER_OPTIONS_SETTING_SHIFT 2
#define PLAYER_OPTIONS_SETTING_MASK 0x0c

#define PLAYER_OPTIONS_FLAG_CHANGED 0x01
#define PLAYER_OPTIONS_SOUND_CHANGED 0x02
#define PLAYER_OPTIONS_SETTING_CHANGED 0x04

/* The options in use. */
typedef struct PlayerOptions {
    u8 values;
    u8 changed;
} PlayerOptions;

void PlayerOptions_MarkSettingChanged(PlayerOptions *options);
void PlayerOptions_MarkSoundChanged(PlayerOptions *options);
void PlayerOptions_MarkFlagChanged(PlayerOptions *options);
int PlayerOptions_SettingChanged(const PlayerOptions *options);
int PlayerOptions_SoundChanged(const PlayerOptions *options);
int PlayerOptions_FlagChanged(const PlayerOptions *options);
void PlayerOptions_Clear(PlayerOptions *options);
int PlayerOptions_Empty2B4(int value);
int PlayerOptions_Empty2C4(int value);
void PlayerOptions_SetSetting(u8 *values, unsigned int setting);
int PlayerOptions_Setting(const u8 *values);
void PlayerOptions_ClearSound(u8 *values);
void PlayerOptions_SetSound(u8 *values);
int PlayerOptions_Sound(const u8 *values);
void PlayerOptions_ClearFlag(u8 *values);
void PlayerOptions_SetFlag(u8 *values);
int PlayerOptions_Flag(const u8 *values);
void PlayerOptions_CopyFrom(u8 *values, const u8 *from);
void PlayerOptions_CopyTo(const u8 *values, u8 *to);
void PlayerOptions_ClearValues(u8 *values);
void PlayerOptions_Nothing384(void);
void PlayerOptions_Destruct(u8 *values);
void PlayerOptions_Construct(u8 *values);
void PlayerOptions_Nothing390(void);
void PlayerOptions_Store(void);
void PlayerOptions_ChangeSetting(unsigned int setting);
int PlayerOptions_CurrentSetting(void);
void PlayerOptions_ChangeSound(int on);

#endif
