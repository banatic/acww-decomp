/* The sound system (data_021fd1bc, SoundSystem in sound.h): the music and its volumes, the
 * sound effects' handles, the output effect and the random numbers of the sound code.
 *
 * - The music plays on its own handle, or as a stream (numbers 0 and 1). The hourly pieces
 *   (0x16 to 0x2d) come in arrangements, each a set of their tracks, chosen by the caller
 *   (0xb, 0xc, 0xd: func_020356fc picks one from the game's state); changing arrangement
 *   mutes the tracks not in it, or cross-fades from one set of tracks to the other.
 * - The players are grouped for their volumes: a first group (players 4, 7, 9, 13) and a
 *   second (8, 11, and 5, 6, 16 to 20 unless only the second is turned down), each with a
 *   fader; SoundSystem_LowerBoth and SoundSystem_LowerB turn them down for a while.
 * - Each scene of the game has a sound object (SoundScene) the system knows; its kind says
 *   what the frame's updates do with the music. */
#ifndef CLEAN_AUTOLOAD_2_SOUND_SYSTEM_H
#define CLEAN_AUTOLOAD_2_SOUND_SYSTEM_H

#include "sound.h"
#include "types.h"

struct SoundScene;

/* The scene sound classes' vtable, as far as the sound system uses it (clean/main's
 * scene_sound.h names the other slots). */
typedef struct SoundSceneVtable {
    const void *slots[10]; /* 0x00 */
    /* 0x28: told of the music: (0, number) when one starts, (1, 9999) when it stops */
    void (*on_music)(struct SoundScene *scene, int stopped, int music);
} SoundSceneVtable;

/* A scene's sound object (clean/main's SceneSound). */
typedef struct SoundScene {
    const SoundSceneVtable *vtable; /* 0x00 */
    s8 kind;                        /* 0x04: what the music does; -1 for the base class */
    u8 stopped;                     /* 0x05 */
    u8 started;                     /* 0x06 */
    u8 pad_07;
} SoundScene;

/* The music numbers played as a stream instead of on the music's handle. */
#define MUSIC_STREAM_LAST 1
/* The hourly music, one piece for each hour: its tracks are listed by arrangement. */
#define MUSIC_HOURLY_FIRST 0x16
#define MUSIC_HOURLY_LAST 0x2d
/* Music started silent. */
#define MUSIC_SILENT_FIRST 0xb0
#define MUSIC_SILENT_LAST 0xf5

void *SoundSystem_StopEffectB(SoundSystem *sys);
void SoundSystem_PlayEffectB(SoundSystem *sys, int index);
void SoundSystem_PlayEffectBAgain(SoundSystem *sys, int index);
void SoundSystem_SetEffectLevel(SoundSystem *sys, int level);
int SoundSystem_PlayEffect2c(SoundSystem *sys, void *unused);
void SoundSystem_SetUnk71(SoundSystem *sys, int value);
void SoundSystem_SetPan(SoundSystem *sys, char pan);
void SoundSystem_ChangePan(SoundSystem *sys, unsigned char pan);
void SoundSystem_Tick(SoundSystem *sys, int value);
int *SoundSystem_OwnerData(SoundSystem *sys);
void SoundSystem_FadeInMusic(SoundSystem *sys);
void SoundSystem_RaiseB(SoundSystem *sys);
void SoundSystem_LowerB(SoundSystem *sys);
void SoundSystem_RaiseBoth(SoundSystem *sys);
void SoundSystem_LowerBoth(SoundSystem *sys);
void SoundSystem_SetVolumeB(SoundSystem *sys, int volume);
void SoundSystem_SetVolumes(SoundSystem *sys, int volume_a, int volume_b);
void SoundSystem_ApplyPan(SoundSystem *sys, int some_effects);
void SoundSystem_UpdateVolumes(SoundSystem *sys);
void SoundSystem_UpdateCrossFade(SoundSystem *sys);
void *SoundSystem_StopMusic(SoundSystem *sys);
void SoundSystem_PlayMusic(SoundSystem *sys, int number, int volume);
void SoundSystem_SetArrangement(SoundSystem *sys, int arrangement);
void SoundSystem_FadeInTracks(SoundSystem *sys, unsigned int set);
void SoundSystem_SetTracks(SoundSystem *sys, int set);
void SoundSystem_MoveMusicVolume(SoundSystem *sys, int volume, int frames);
void SoundSystem_EndMusic(SoundSystem *sys, int fade_frames);
void SoundSystem_ChangeMusic(SoundSystem *sys, unsigned int music);
unsigned int SoundSystem_Random(SoundSystem *sys, unsigned int range);
int SoundSystem_LoadSeqArc(SoundSystem *sys, int seq_arc);
void SoundSystem_PlayVoice(SoundSystem *sys, int number, int volume, int pitch);
void SoundSystem_SetVoiceType(SoundSystem *sys, int type);
void SoundSystem_StopSequence(void *sys, int number, int fade_frames);
void SoundSystem_PlayOnEffect(SoundSystem *sys, int number);
void SoundSystem_PlayEffect(SoundSystem *sys, int number);
void SoundSystem_StopOutputEffect(void *sys);
void SoundSystem_StartOutputEffect(SoundSystem *sys);
void SoundSystem_ChangeOutputEffect(SoundSystem *sys, int effect);
void SoundSystem_MasterVolumeFull(void);
void SoundSystem_MasterVolumeOff(void *sys);
void SoundSystem_Frame(SoundSystem *sys);
void SoundSystem_Init(SoundSystem *sys, u8 *memory, u32 size, const void *archive_path);
SoundSystem *SoundSystem_Construct(SoundSystem *sys);

#endif
