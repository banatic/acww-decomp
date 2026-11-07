/* The main program's calls into the game's sound layer (autoload_2, over NNS's sound library).
 * Most only pass their arguments on; those taking a position in the world hand it on relative
 * to data_021c67b8, and only while the camera (data_021c67a4) exists.
 *
 * - SoundSeq: an object of overlay 4's field (at 0x844 in its owner) starting a sequence of a
 *   sequence archive and following a position (func_020f6350, func_020f61e4).
 * - SoundCue: an object with a mode at 0x08 (0 off, 1 playing, 2 waiting until the sound
 *   library's global variable 2 equals its byte 0x0b), used by overlay 4.
 * - MelodySetCall: calls on the town tune's melody set (MelodySet, data_021cfbcc of the main
 *   program, town_tune.h), which plays melodies of 16 steps by sound number and keeps its own
 *   melody at 0x28.
 * - SoundSys: the game's sound state at data_021fd1bc: two volume faders at 0x10 and 0x1c that
 *   lower and restore the music, a fader at 0x04 with a track mask at 0x64, the effects' pan
 *   at 0x70 handed to both players as -128 to 127, and the music's volume. It also owns two sound
 *   handles of its own (at 0x38 and 0x40) and the villagers' speaking voice
 *   (SoundSys_Speak, TalkVoice_Update).
 *   A sound number is an index of the sound archive: (sequence archive * 1000) + index. */
#ifndef CLEAN_MAIN_SOUND_H
#define CLEAN_MAIN_SOUND_H

#include "autoload_2/vector.h"
#include "types.h"

void SoundSeq_Stop(void *seq);
void SoundSeq_UpdateAt(void *seq, const Vec3 *pos);
void SoundSeq_Start(void *seq, u16 number);
void SoundSeq_Init(void *seq);

int SoundCue_TakeStart(void *cue);
u8 SoundCue_ReadVariable(char *cue);
void SoundCue_SetTarget(void *cue, int value);
void SoundCue_Stop(void *cue);
int SoundCue_UpdateAt(void *cue, const Vec3 *pos);
void SoundCue_SetMode(void *cue, int mode);
void SoundCue_Init(void *cue, u16 number);

void *MelodySetCall_DefaultMelody(void *set);
void *MelodySetCall_LoadPreset(u8 *set);
int MelodySetCall_PlayRandomPreset(void *set, u32 number);
u8 MelodySetCall_APlaying(void *set);
int MelodySetCall_Update(void *set);
void MelodySetCall_PlaySeqD3B(void *set, int value);
void MelodySetCall_StartA(void *set);
void MelodySetCall_PlayOwn(void *set, u32 number);
void MelodySetCall_PlayAt(void *set, const Vec3 *pos, int index);
void MelodySetCall_PlayWith(void *set, u32 number, void *block);
void MelodySetCall_SetMelody(u8 *set, const u8 *block);
void MelodySetCall_MakeCurrent(void *set);

void SoundSys_SetPan(int value);
void SoundSys_ChangePan(int value);
void SoundSys_RestoreSecond(void);
void SoundSys_LowerSecond(void);
void SoundSys_RestoreMusic(void);
void SoundSys_LowerMusic(void);
int *SoundSys_OwnerData(void);
void SoundSys_SetArrangement(int mode);
void SoundSys_FadeInTracks(int set);
void SoundSys_FadeOutTracks(int set);
void SoundSys_MoveVolume(int volume, int frames);
void SoundSys_EndMusic(int value);
void SoundSys_ChangeMusic(u32 music);
void SoundSys_StopSound2d(void);
void SoundSys_StartSound2d(void);
void SoundSys_StopHandle40(void);
void SoundSys_StartOnHandle40(int index);
void SoundSys_StartOnHandle40B(int index);
int SoundSys_PlaySound2c(void *unused);
void SoundSys_SetByte71(int value);
void SoundSys_SetHandleLevel(int level);
void SoundSys_SetVoiceType(int mode);
void SoundSys_Speak(int style, int kind, int character, int previous_character);
void SoundSys_SetCaptureEffect(int effect);
void SoundSys_StopSound(int number, int fade_frames);
void SoundSys_StartOnHandle38(int number);
void SoundSys_StartIndexOnHandle38(int index, int value);
void SoundSys_PlaySe(int number);
void SoundSys_MasterVolumeFull(void);
void SoundSys_MasterVolumeOff(void);

#endif
