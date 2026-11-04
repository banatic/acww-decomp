/* A player's options: one byte in the player's record (at 0x1d3b, PlayerRecord_Field1D3B) and
 * the options in use (data_021c6998), two bytes: the same byte of values, then a byte saying
 * which of them changed since they were last stored in the player's record
 * (PlayerOptions_Store).
 *
 *   values   bit 0     a flag (func_0203d480 sets it from a two-way choice)
 *            bit 1     stereo (1) or surround (0), from the telephone's sound question: the
 *                      sound capture effect is data_020d1b90[flag]
 *            bits 2-3  the villagers' voice: 0 animal talk, 1 beeps, 2 quiet
 *   changed  bit 0     bit 0 of the values changed
 *            bit 1     the stereo flag changed
 *            bit 2     the voice changed
 *
 * The functions on the values take either object; those on the changes only the options in
 * use. */
#ifndef CLEAN_MAIN_PLAYER_OPTIONS_H
#define CLEAN_MAIN_PLAYER_OPTIONS_H

#include "types.h"

#define PLAYER_OPTIONS_FLAG 0x01
#define PLAYER_OPTIONS_SOUND 0x02
#define PLAYER_OPTIONS_VOICE_SHIFT 2
#define PLAYER_OPTIONS_VOICE_MASK 0x0c

#define PLAYER_OPTIONS_FLAG_CHANGED 0x01
#define PLAYER_OPTIONS_SOUND_CHANGED 0x02
#define PLAYER_OPTIONS_VOICE_CHANGED 0x04

/* The options in use. */
typedef struct PlayerOptions {
    u8 values;
    u8 changed;
} PlayerOptions;

void PlayerOptions_MarkVoiceChanged(PlayerOptions *options);
void PlayerOptions_MarkStereoChanged(PlayerOptions *options);
void PlayerOptions_MarkFlagChanged(PlayerOptions *options);
int PlayerOptions_VoiceChanged(const PlayerOptions *options);
int PlayerOptions_StereoChanged(const PlayerOptions *options);
int PlayerOptions_FlagChanged(const PlayerOptions *options);
void PlayerOptions_Clear(PlayerOptions *options);
int PlayerOptions_Empty2B4(int value);
int PlayerOptions_Empty2C4(int value);
void PlayerOptions_SetVoice(u8 *values, unsigned int voice);
int PlayerOptions_Voice(const u8 *values);
void PlayerOptions_ClearStereo(u8 *values);
void PlayerOptions_SetStereo(u8 *values);
int PlayerOptions_Stereo(const u8 *values);
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
void PlayerOptions_ChangeVoice(unsigned int voice);
int PlayerOptions_CurrentVoice(void);
void PlayerOptions_ChangeStereo(int on);
int PlayerOptions_StereoInUse(void);
void PlayerOptions_ChangeFlag(int on);
int PlayerOptions_FlagInUse(void);
int PlayerOptions_InUse(void);

#endif
