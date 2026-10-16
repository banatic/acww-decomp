/* Sounds placed in space: how far a position is from the listener, the volume a sound has at
 * a distance and the pan it has from its side. Positions are relative to the camera, in 20.12
 * fixed point (clean/main/sound.c makes them); distances are in whole units.
 *
 * - The distance curve (data_021fd248, SoundDistanceCurve): full volume up to `near`, then two
 *   straight ramps, down to `knee_volume` at `knee` and to 0 at `far`. The sound system hands
 *   it a knee distance every frame (SoundSystem_Tick) and the rest follows from that.
 * - The sound slots' three hooks (sound.h, SoundParams): the distance of the slots' source,
 *   the volume at that distance and the pan of the source. */
#ifndef CLEAN_AUTOLOAD_2_SOUND_POSITION_H
#define CLEAN_AUTOLOAD_2_SOUND_POSITION_H

#include "sound.h"
#include "types.h"
#include "vector.h"

/* Volumes are 0 to 127 (0x7f); distances and volumes here are 20.12 fixed point. */
typedef struct SoundDistanceCurve {
    fx32 knee;        /* 0x00: where the gentle ramp meets the steep one */
    fx32 near_volume; /* 0x04: the volume up to `near` */
    fx32 knee_volume; /* 0x08: the volume at `knee` */
    fx32 near;        /* 0x0c: the distance up to which a sound is at `near_volume` */
    fx32 far;         /* 0x10: the distance from which a sound is not heard */
    fx32 slope_near;  /* 0x14: volume per unit from `near` to `knee` */
    fx32 slope_far;   /* 0x18: volume per unit from `knee` to `far` */
} SoundDistanceCurve;

void SoundPosition_ClearHooks(void);
void SoundPosition_InstallHooks(void);
void SoundPosition_SetUnusedFlag(char value);
SoundDistanceCurve *SoundPosition_Curve(void);
int SoundPosition_CurveVolume(SoundDistanceCurve *curve, int distance);
void SoundPosition_SetKnee(SoundDistanceCurve *curve, fx32 knee);
void SoundPosition_ClearCurve(SoundDistanceCurve *curve);
int SoundPosition_HookPan(SoundParams *params);
int SoundPosition_Pan(const Vec3 *pos, int mode);
void SoundPosition_SplitVolumes(int z, int *volume_a, int *volume_b);
int SoundPosition_HookVolume(SoundParams *params);
int SoundPosition_VolumeAt(int distance);
int SoundPosition_HookDistance(SoundParams *params);
int SoundPosition_Distance(const Vec3 *pos, int mode);
void SoundPosition_ApplyToHandle(SoundHandle *handle, const Vec3 *pos);

#endif
