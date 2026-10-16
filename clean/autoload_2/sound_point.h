/* Point sounds (clean/main/sound_emitter.h calls them PointSound): sounds at a point, each
 * with its own handle, asked for frame by frame and kept in a list (overlay 4's room objects
 * use them). The list in use is data_021fd234; it has a handle of its own for the sounds
 * started on it directly.
 *
 * A number is seq_arc * 1000 + index, but these sounds always start from sequence archive 1.
 * Each frame the owners ask for their sounds (SoundPoint_PlayAt and SoundPoint_PlayAtB put
 * them in the list), then the list is flushed (SoundPointList_Flush): the sounds finished or
 * no longer asked for are stopped and taken out, and of the rest only the last two play. */
#ifndef CLEAN_AUTOLOAD_2_SOUND_POINT_H
#define CLEAN_AUTOLOAD_2_SOUND_POINT_H

#include "links.h"
#include "sound.h"
#include "types.h"
#include "vector.h"

typedef struct SoundPoint {
    ListNode link;      /* 0x00: in the list in use */
    SoundHandle handle; /* 0x08 */
    Vec3 pos;           /* 0x0c: relative to the listener */
    u16 number;         /* 0x18 */
    u8 play_out;        /* 0x1a: not stopped by a flush while it still plays */
    u8 asked;           /* 0x1b: asked for since the last flush */
} SoundPoint;

typedef struct SoundPointList {
    SoundList list;     /* 0x00: of SoundPoint, linked at their start */
    SoundHandle handle; /* 0x0c */
} SoundPointList;

void SoundPointList_StartSeq(SoundPointList *list, int number, const Vec3 *pos);
unsigned int SoundPointList_Remove(SoundPointList *list, SoundPoint *point);
void SoundPointList_Flush(SoundPointList *list);
void SoundPointList_Add(SoundPointList *list, SoundPoint *point);
void SoundPointList_Init(SoundPointList *list);
SoundPointList *SoundPointList_Release(SoundPointList *list);
void SoundPoint_Release(SoundPoint *point);
void SoundPoint_UpdateMusicVolume(int unused, const Vec3 *pos);
void SoundPoint_SetVariable(SoundPoint *point, short value);
void SoundPoint_PlayAt(SoundPoint *point, int number, const Vec3 *pos);
void SoundPoint_ApplyVolume(SoundPoint *point);
int SoundPoint_IsDone(SoundPoint *point);
void SoundPoint_Stop(SoundPoint *point);
void SoundPoint_Start(SoundPoint *point);
void SoundPoint_PlayAtB(SoundPoint *point, int number, const Vec3 *pos);
void SoundPoint_Init(SoundPoint *point, SoundPointList *list);

#endif
