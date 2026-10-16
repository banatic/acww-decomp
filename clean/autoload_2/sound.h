/* The game's use of NitroSystem's sound heap and players: groups of the sound archive loaded
 * into the sound heap with its level saved before, so that they can be unloaded by going back to
 * that level, and sequences stopped. */
#ifndef CLEAN_AUTOLOAD_2_SOUND_H
#define CLEAN_AUTOLOAD_2_SOUND_H

#include "types.h"

int Sound_GetHeapLevel(void);
void Sound_RestoreHeapLevel(int level);
int Sound_LoadGroup(int group);
int Sound_StopSequence(void *handle, int fade_frames);

#endif
