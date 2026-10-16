/* The scene sound classes (SoundScene in sound_system.h, SceneSound in
 * clean/main/scene_sound.h), named by their kind. First 99 (scene 0x32, and every scene in some
 * modes of the game), 60, 52 (scenes 0x2e and 0x30) and 51 (scene 0x2d). Each has its
 * constructor, its destructors (the second also frees the object) and its start (vtable slot
 * 3), which loads a group of the sound archive and makes the players' heaps; class 51 also
 * has its own stop (slot 5). */
#ifndef CLEAN_AUTOLOAD_2_SOUND_SCENE_H
#define CLEAN_AUTOLOAD_2_SOUND_SCENE_H

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
 * 0x08 that follows the music (SoundScenePart). Class 31's destructor and constructor come
 * after these. */

struct SoundScenePart;

/* The part's vtable (0x0213f250), as far as class 41 uses it. */
typedef struct SoundScenePartVtable {
    void (*update)(struct SoundScenePart *part); /* 0x00: its frame update */
} SoundScenePartVtable;

/* The part class 41 owns: built by func_020f9624 (which makes it the sound system's owner),
 * destroyed by func_020f95f8, set up by func_020f97dc and turned on or off by func_020f95f0
 * (its byte 0x28). */
typedef struct SoundScenePart {
    const SoundScenePartVtable *vtable; /* 0x00 */
    u8 unk_04[0x2c];
} SoundScenePart;

typedef struct SoundScene41 {
    SoundScene base;     /* 0x00 */
    SoundScenePart part; /* 0x08 */
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

#endif
