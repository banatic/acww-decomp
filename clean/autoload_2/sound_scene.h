/* The scene sound classes (SoundScene in sound_system.h, SceneSound in
 * clean/main/scene_sound.h), named by their kind. First 99 (scene 0x32, and every scene in some
 * modes of the game), 60, 52 (scenes 0x2e and 0x30) and 51 (scene 0x2d). Each has its
 * constructor, its destructors (the second also frees the object) and its start (vtable slot
 * 3), which loads a group of the sound archive and makes the players' heaps; class 51 also
 * has its own stop (slot 5). */
#ifndef CLEAN_AUTOLOAD_2_SOUND_SCENE_H
#define CLEAN_AUTOLOAD_2_SOUND_SCENE_H

#include "music_beat.h"
#include "sound_system.h"

#include <assert.h>
#include <stddef.h>

void SoundScene99_Start(SoundScene *scene);
SoundScene *SoundScene99_DestructDelete(SoundScene *scene);
SoundScene *SoundScene99_Destruct(SoundScene *scene);
SoundScene *SoundScene99_Construct(SoundScene *scene);

void SoundScene60_Start(SoundScene *scene);
SoundScene *SoundScene60_DestructDelete(SoundScene *scene);
SoundScene *SoundScene60_Destruct(SoundScene *scene);
SoundScene *SoundScene60_Construct(SoundScene *scene);

void SoundScene52_Start(SoundScene *scene);
SoundScene *SoundScene52_DestructDelete(SoundScene *scene);
SoundScene *SoundScene52_Destruct(SoundScene *scene);
SoundScene *SoundScene52_Construct(SoundScene *scene);

void SoundScene51_Stop(SoundScene *scene);
void SoundScene51_Start(SoundScene *scene);
SoundScene *SoundScene51_DestructDelete(SoundScene *scene);
SoundScene *SoundScene51_Destruct(SoundScene *scene);
SoundScene *SoundScene51_Construct(SoundScene *scene);

/* The classes of scenes 0x1b to 0x2c (clean/main/scene_sound.c picks them), named by their
 * kind as the classes above:
 *
 *   kind 50: scene 0x2c         kind 43: scenes 0x23, 0x24   kind 34: scene 0x1e
 *   kind 48: scene 0x29         kind 42: scene 0x22          kind 33: scene 0x1d
 *   kind 47: scene 0x28, 8:00 to 16:59                       kind 32: scene 0x1c
 *   kind 46: scene 0x28, the rest of the day                 kind 31: scene 0x1b
 *   kind 45: scene 0x27         kind 41: scene 0x21          kind 40: scene 0x20
 *   kind 44: scenes 0x25, 0x26  kind 35: scene 0x1f
 *
 * Each loads its own group of the archive; class 41 is 0x38 bytes long and owns a part at
 * 0x08 that follows the music (MusicBeatShow, music_beat.h). Class 31's destructor and constructor come
 * after these. */

typedef struct SoundScene41 {
    SoundScene base;    /* 0x00 */
    MusicBeatShow part; /* 0x08 */
} SoundScene41;

static_assert(offsetof(SoundScene41, part) == 0x08, "SoundScene41.part");
static_assert(sizeof(SoundScene41) == 0x38, "SoundScene41 size");

void SoundScene50_Start(SoundScene *scene);
SoundScene *SoundScene50_DestructDelete(SoundScene *scene);
SoundScene *SoundScene50_Destruct(SoundScene *scene);
SoundScene *SoundScene50_Construct(SoundScene *scene);

void SoundScene48_Start(SoundScene *scene);
SoundScene *SoundScene48_DestructDelete(SoundScene *scene);
SoundScene *SoundScene48_Destruct(SoundScene *scene);
SoundScene *SoundScene48_Construct(SoundScene *scene);

void SoundScene47_Start(SoundScene *scene);
SoundScene *SoundScene47_DestructDelete(SoundScene *scene);
SoundScene *SoundScene47_Destruct(SoundScene *scene);
SoundScene *SoundScene47_Construct(SoundScene *scene);

void SoundScene46_Start(SoundScene *scene);
SoundScene *SoundScene46_DestructDelete(SoundScene *scene);
SoundScene *SoundScene46_Destruct(SoundScene *scene);
SoundScene *SoundScene46_Construct(SoundScene *scene);

void SoundScene45_Start(SoundScene *scene);
SoundScene *SoundScene45_DestructDelete(SoundScene *scene);
SoundScene *SoundScene45_Destruct(SoundScene *scene);
SoundScene *SoundScene45_Construct(SoundScene *scene);

void SoundScene44_Start(SoundScene *scene);
SoundScene *SoundScene44_DestructDelete(SoundScene *scene);
SoundScene *SoundScene44_Destruct(SoundScene *scene);
SoundScene *SoundScene44_Construct(SoundScene *scene);

void SoundScene43_Start(SoundScene *scene);
SoundScene *SoundScene43_DestructDelete(SoundScene *scene);
SoundScene *SoundScene43_Destruct(SoundScene *scene);
SoundScene *SoundScene43_Construct(SoundScene *scene);

void SoundScene42_Start(SoundScene *scene);
SoundScene *SoundScene42_DestructDelete(SoundScene *scene);
SoundScene *SoundScene42_Destruct(SoundScene *scene);
SoundScene *SoundScene42_Construct(SoundScene *scene);

void SoundScene41_Start(SoundScene41 *scene);
void SoundScene41_Update(SoundScene41 *scene, int value);
void SoundScene41_OnMusic(SoundScene41 *scene, int stopped, unsigned int music);
SoundScene41 *SoundScene41_DestructDelete(SoundScene41 *scene);
SoundScene41 *SoundScene41_Destruct(SoundScene41 *scene);
SoundScene41 *SoundScene41_Construct(SoundScene41 *scene);

void SoundScene40_Start(SoundScene *scene);
SoundScene *SoundScene40_DestructDelete(SoundScene *scene);
SoundScene *SoundScene40_Destruct(SoundScene *scene);
SoundScene *SoundScene40_Construct(SoundScene *scene);

void SoundScene35_Start(SoundScene *scene);
SoundScene *SoundScene35_DestructDelete(SoundScene *scene);
SoundScene *SoundScene35_Destruct(SoundScene *scene);
SoundScene *SoundScene35_Construct(SoundScene *scene);

void SoundScene34_Start(SoundScene *scene);
SoundScene *SoundScene34_DestructDelete(SoundScene *scene);
SoundScene *SoundScene34_Destruct(SoundScene *scene);
SoundScene *SoundScene34_Construct(SoundScene *scene);

void SoundScene33_Start(SoundScene *scene);
SoundScene *SoundScene33_DestructDelete(SoundScene *scene);
SoundScene *SoundScene33_Destruct(SoundScene *scene);
SoundScene *SoundScene33_Construct(SoundScene *scene);

void SoundScene32_Start(SoundScene *scene);
SoundScene *SoundScene32_DestructDelete(SoundScene *scene);
SoundScene *SoundScene32_Destruct(SoundScene *scene);
SoundScene *SoundScene32_Construct(SoundScene *scene);

void SoundScene31_Start(SoundScene *scene);
SoundScene *SoundScene31_DestructDelete(SoundScene *scene);
SoundScene *SoundScene31_Destruct(SoundScene *scene);
SoundScene *SoundScene31_Construct(SoundScene *scene);

/* The classes of scenes 6 to 0x1a, named by their kind as the classes above:
 *
 *   kind 30: scene 0x1a         kind 22: scenes 0xb to 0xe and 0x2f
 *   kind 24: scene 0x10         kind 21: scene 0xa
 *   kind 23: scene 0xf          kind 20: scene 9
 *                               kind 19: scenes 6, 7 and 8
 *
 * and the classes clean/main/scene_sound.c picks for the other scenes:
 *
 *   kind 10: when data_020e54a8 is set (0x20 bytes, SoundScene10);
 *   kind 2: when func_020b22b8 or func_020b22dc says so;
 *   kind 3: on the days of events 0xf and 0x12, and of event 0x13 before 2:00;
 *   kind 1: otherwise. Classes 60, 3 and 2 derive from it; it has its own slots 7, 8 and 9,
 *   which reload bank 0x8f after the keyboard's sounds are dropped.
 *
 * Also here: the base class's helpers that make the heaps of players 6, 12, 13, 17, 18 and
 * 19. */

/* Class 10 owns a MusicBeat (music_beat.h) at 0x08, the base class of class 41's part. */
typedef struct SoundScene10 {
    SoundScene base; /* 0x00 */
    MusicBeat part;  /* 0x08 */
    /* 0x1c: 0 when built, 1 once the scene's sounds are loaded (start or slot 8), 2 once the
     * keyboard's sounds replace them (slot 7) */
    u8 stage;
    u8 heap_level; /* 0x1d: the sound heap's level before bank 0x90 */
    u8 pad_1e[2];
} SoundScene10;

static_assert(offsetof(SoundScene10, part) == 0x08, "SoundScene10.part");
static_assert(offsetof(SoundScene10, stage) == 0x1c, "SoundScene10.stage");
static_assert(sizeof(SoundScene10) == 0x20, "SoundScene10 size");

void SoundScene30_Start(SoundScene *scene);
SoundScene *SoundScene30_DestructDelete(SoundScene *scene);
SoundScene *SoundScene30_Destruct(SoundScene *scene);
SoundScene *SoundScene30_Construct(SoundScene *scene);

void SoundScene24_Start(SoundScene *scene);
SoundScene *SoundScene24_DestructDelete(SoundScene *scene);
SoundScene *SoundScene24_Destruct(SoundScene *scene);
SoundScene *SoundScene24_Construct(SoundScene *scene);

void SoundScene23_Start(SoundScene *scene);
SoundScene *SoundScene23_DestructDelete(SoundScene *scene);
SoundScene *SoundScene23_Destruct(SoundScene *scene);
SoundScene *SoundScene23_Construct(SoundScene *scene);

void SoundScene22_Start(SoundScene *scene);
SoundScene *SoundScene22_DestructDelete(SoundScene *scene);
SoundScene *SoundScene22_Destruct(SoundScene *scene);
SoundScene *SoundScene22_Construct(SoundScene *scene);

void SoundScene21_Start(SoundScene *scene);
SoundScene *SoundScene21_DestructDelete(SoundScene *scene);
SoundScene *SoundScene21_Destruct(SoundScene *scene);
SoundScene *SoundScene21_Construct(SoundScene *scene);

void SoundScene20_Start(SoundScene *scene);
SoundScene *SoundScene20_DestructDelete(SoundScene *scene);
SoundScene *SoundScene20_Destruct(SoundScene *scene);
SoundScene *SoundScene20_Construct(SoundScene *scene);

void SoundScene19_Start(SoundScene *scene);
SoundScene *SoundScene19_DestructDelete(SoundScene *scene);
SoundScene *SoundScene19_Destruct(SoundScene *scene);
SoundScene *SoundScene19_Construct(SoundScene *scene);

void SoundScene10_ReloadSounds(SoundScene10 *scene);
void SoundScene10_SetKeyboardMode(SoundScene10 *scene, int mode);
void SoundScene10_OnMusic(SoundScene10 *scene, unsigned char stopped);
void SoundScene10_Update(SoundScene10 *scene, int value);
void SoundScene10_Start(SoundScene10 *scene);
SoundScene10 *SoundScene10_DestructDelete(SoundScene10 *scene);
SoundScene10 *SoundScene10_Destruct(SoundScene10 *scene);
SoundScene10 *SoundScene10_Construct(SoundScene10 *scene);

void SoundScene3_Start(SoundScene *scene);
SoundScene *SoundScene3_DestructDelete(SoundScene *scene);
SoundScene *SoundScene3_Destruct(SoundScene *scene);
SoundScene *SoundScene3_Construct(SoundScene *scene);

void SoundScene2_Start(SoundScene *scene);
SoundScene *SoundScene2_DestructDelete(SoundScene *scene);
SoundScene *SoundScene2_Destruct(SoundScene *scene);
SoundScene *SoundScene2_Construct(SoundScene *scene);

void SoundScene1_Vfunc24(SoundScene *scene, int value);
void SoundScene1_Vfunc20(SoundScene *scene);
int SoundScene1_SetKeyboardMode(SoundScene *scene, int mode);
void SoundScene1_Start(SoundScene *scene);
SoundScene *SoundScene1_DestructBase(SoundScene *scene);
SoundScene *SoundScene1_DestructDelete(SoundScene *scene);
SoundScene *SoundScene1_Destruct(SoundScene *scene);
SoundScene *SoundScene1_Construct(SoundScene *scene);
SoundScene *SoundScene1_ConstructBase(SoundScene *scene);

int SoundScene_CreatePlayer12Heaps(SoundScene *scene);
void SoundScene_CreatePlayer13Heap(SoundScene *scene);
void SoundScene_CreatePlayer18And19Heaps(SoundScene *scene);
void SoundScene_CreatePlayer17Heaps(SoundScene *scene);
void SoundScene_CreatePlayer6Heaps(SoundScene *scene);

/* The base class (vtable 0x0213efb4, kind -1): its slots, constructor and destructors. Its
 * slot 7 makes the keyboard's mode the voice's kind and loads that mode's sounds (sequence
 * archive 0x85, 0x86 or 0x87); slot 8 drops them again. */
void SoundSceneBase_OnMusic(SoundScene *scene, int stopped, int music);
void SoundSceneBase_RestoreHeap(SoundScene *scene);
int SoundSceneBase_SetKeyboardMode(SoundScene *scene, unsigned int mode);
void SoundSceneBase_Unload(SoundScene *scene);
int SoundSceneBase_Stop(SoundScene *scene);
void SoundSceneBase_Update(SoundScene *scene, int value);
void SoundSceneBase_Start(void);
void SoundSceneBase_Vfunc08(SoundScene *scene);
SoundScene *SoundSceneBase_DestructBase(SoundScene *scene);
SoundScene *SoundSceneBase_DestructDelete(SoundScene *scene);
SoundScene *SoundSceneBase_Destruct(SoundScene *scene);
SoundScene *SoundSceneBase_Construct(SoundScene *scene);

/* The loading every class's start begins with: player 0's heap of `player_heap` bytes (unless
 * the system's byte 0x62 is set) and group `group` of the archive. */
void SoundScene_LoadGroup(SoundScene *scene, int player_heap, unsigned char group);
void SoundScene_CreatePlayer5Heap(SoundScene *scene);
void SoundScene_CreatePlayer11Heaps(SoundScene *scene, int count);
void SoundScene_CreatePlayer4Heap(SoundScene *scene);
void SoundScene_StopPlayers(SoundScene *scene, int fade_frames);

#endif
