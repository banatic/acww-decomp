/* The sound heap and players (sound.h). Each failure the game does not expect stops it
 * (OS_Terminate). */
#include "sound.h"

#include <stddef.h>

#include "clean.h"

/* The sound heap (NNSSndHeapHandle). */
extern void *data_021fd048;

extern void OS_Terminate(void);
extern int NNS_SndHeapGetCurrentLevel(void *heap);
extern void NNS_SndHeapLoadState(void *heap, int level);
extern int NNS_SndHeapSaveState(void *heap);
extern int NNS_SndArcLoadGroup(int group, void *heap);
extern int NNS_SndPlayerStopSeq(void *handle, int fade_frames);

/* 0xff is what the callers keep for "no level saved" (func_020eefd4). */
#define NO_LEVEL 0xff

/* func_020eec48: the sound heap's level (the number of states saved). */
int Sound_GetHeapLevel(void)
{
    return NNS_SndHeapGetCurrentLevel(data_021fd048);
}
CLEAN_AS(func_020eec48, Sound_GetHeapLevel)

/* func_020eec60: the sound heap taken back to `level` (Sound_LoadGroup's result), freeing what
 * was loaded since; the game stops on no level, level 0 or a level not reached.
 * QUIRK: the level is read once more at the end and not used. */
void Sound_RestoreHeapLevel(int level)
{
    if (level == NO_LEVEL) {
        OS_Terminate();
    }
    if (level == 0) {
        OS_Terminate();
    }
    NNS_SndHeapLoadState(data_021fd048, level);
    if (level != Sound_GetHeapLevel()) {
        OS_Terminate();
    }
    Sound_GetHeapLevel();
}
CLEAN_AS(func_020eec60, Sound_RestoreHeapLevel)

/* func_020eecb0: a group of the sound archive loaded into the sound heap and the heap's state
 * saved after it; the level before (to unload it with Sound_RestoreHeapLevel), or -1 when the
 * group could not be loaded. The game stops when the state cannot be saved. */
int Sound_LoadGroup(int group)
{
    int level = Sound_GetHeapLevel();
    if (!NNS_SndArcLoadGroup(group, data_021fd048)) {
        return -1;
    }
    if (NNS_SndHeapSaveState(data_021fd048) == -1) {
        OS_Terminate();
    }
    return level;
}
CLEAN_AS(func_020eecb0, Sound_LoadGroup)

/* func_020eed18: the sequence of a player handle stopped, fading out over `fade_frames`; the
 * game stops without a handle. */
int Sound_StopSequence(void *handle, int fade_frames)
{
    if (handle == NULL) {
        OS_Terminate();
    }
    return NNS_SndPlayerStopSeq(handle, fade_frames);
}
CLEAN_AS(func_020eed18, Sound_StopSequence)
