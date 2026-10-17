/* The search for the sound mark nearest a point, over the acre of the point and the eight
 * around it. Each acre's background model (main/bg_models.h) has a "bsd0" file: a count, then
 * marks of a kind and a position in the acre (read like "mgt0", BgModels_MarkAt). Only marks of
 * kinds 5, 0xf, 0x11 and 0x12 are looked at; the town ground (town_ground.h) plays a sound by
 * the kind of the nearest one.
 *
 * Acres are 32.0 units wide and deep (positions >> 17 give an acre's coordinates). */
#ifndef CLEAN_OV003_SOUND_MARK_H
#define CLEAN_OV003_SOUND_MARK_H

#include "autoload_2/vector.h"
#include "types.h"

/* The kinds of marks the search looks at. */
#define SOUND_MARK_KIND_5 5
#define SOUND_MARK_KIND_F 0xf
#define SOUND_MARK_KIND_11 0x11
#define SOUND_MARK_KIND_12 0x12

/* The nearest mark found so far (0x18 bytes; the callers keep it on their stack). */
typedef struct SoundMarkSearch {
    u8 found; /* 0x00 */
    u8 pad_01[3];
    Vec3 position; /* 0x04: its position in the world (y 0) */
    fx32 distance; /* 0x10: its distance in x and z; to begin with 8 acres' width */
    int kind;      /* 0x14: its kind; to begin with SOUND_MARK_KIND_11 */
} SoundMarkSearch;

int SoundMark_Kind(SoundMarkSearch *search);
Vec3 *SoundMark_Position(SoundMarkSearch *search);
void SoundMark_Init(SoundMarkSearch *search);
void SoundMark_Destruct(SoundMarkSearch *search);
int SoundMark_Offer(SoundMarkSearch *search, int distance, const Vec3 *position, int kind);
SoundMarkSearch *SoundMark_FindNearest(SoundMarkSearch *search, const Vec3 *point);
int SoundMark_AcreFile(SoundMarkSearch *search, unsigned int x, unsigned int z);
int SoundMark_AcreBgModel(int unused, unsigned int x, unsigned int z);

#endif
