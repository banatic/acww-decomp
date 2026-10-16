/* Four of the scene sound classes (SoundScene in sound_system.h, SceneSound in
 * clean/main/scene_sound.h), named by their kind: 99 (scene 0x32, and every scene in some
 * modes of the game), 60, 52 (scenes 0x2e and 0x30) and 51 (scene 0x2d). Each has its
 * constructor, its destructors (the second also frees the object) and its start (vtable slot
 * 3), which loads a group of the sound archive and makes the players' heaps; class 51 also
 * has its own stop (slot 5). */
#ifndef CLEAN_AUTOLOAD_2_SOUND_SCENE_H
#define CLEAN_AUTOLOAD_2_SOUND_SCENE_H

#include "sound_system.h"

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

#endif
