/* Sounds placed in space (sound_position.h). */
#include "sound_position.h"

#include <stddef.h>
#include <stdint.h>

#include "clean.h"

static_assert(offsetof(SoundDistanceCurve, near) == 0x0c, "SoundDistanceCurve.near");
static_assert(offsetof(SoundDistanceCurve, slope_far) == 0x18, "SoundDistanceCurve.slope_far");
static_assert(sizeof(SoundDistanceCurve) == 0x1c, "SoundDistanceCurve size");
static_assert(offsetof(SoundParams, source) == 0x04, "SoundParams.source");
static_assert(offsetof(SoundParams, unk_10) == 0x10, "SoundParams.unk_10");

/* The distance curve every sound uses. */
extern SoundDistanceCurve data_021fd248;
/* A byte that only SoundPosition_SetUnusedFlag refers to. */
extern u8 data_021fd238;
/* The slopes of SoundPosition_SplitVolumes's ramps, 20.12, set at start-up (__sinit_020c74c4):
 * 127 / 0.6 (the first part rising), 127 / 0.4 (the first part falling) and 127 / 0.2 (the
 * second part rising). */
extern fx32 data_021fd23c;
extern fx32 data_021fd244;
extern fx32 data_021fd240;

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_Sqrt(fx32 value);
extern void NNS_SndPlayerSetTrackVolume(SoundHandle *handle, int track_mask, int volume);
/* The pan of the tracks in `track_mask`. */
extern void func_0210b634(SoundHandle *handle, u16 track_mask, int pan);
/* The hooks as the game stores them (SoundPosition_HookDistance, SoundPosition_HookVolume and
 * SoundPosition_HookPan). */
extern u32 func_020f5e3c(SoundParams *params);
extern u32 func_020f5e14(SoundParams *params);
extern u32 func_020f5c50(SoundParams *params);

#define FX_ONE 0x1000
#define VOLUME_MAX 0x7f
#define PAN_MIN (-128)
#define PAN_MAX 127
/* The tracks SoundPosition_ApplyToHandle sets: 0-3. */
#define POSITION_TRACKS 0x000f
/* The listener sits 12 units behind the camera's origin in Z (modes 0 and 1). */
#define LISTENER_Z (12 * FX_ONE)
/* Mode 2 measures from (128, 80), with X counted in eighths and Y in quarters. */
#define FLAT_CENTRE_X (128 * FX_ONE)
#define FLAT_CENTRE_Y (80 * FX_ONE)

static fx32 add32(fx32 a, fx32 b)
{
    return (fx32) ((u32) a + (u32) b);
}

static fx32 sub32(fx32 a, fx32 b)
{
    return (fx32) ((u32) a - (u32) b);
}

/* A whole number made 20.12, kept to 32 bits. */
static fx32 to_fx(int value)
{
    return (fx32) ((u32) value << 12);
}

/* `a` times `b` in 20.12, rounded to nearest, kept to 32 bits (FX_Mul). */
static fx32 fx_mul(fx32 a, fx32 b)
{
    return (fx32) (u32) ((u64) ((s64) a * b + 0x800) >> 12);
}

static fx32 fx_square(fx32 value)
{
    return fx_mul(value, value);
}

static int clamp_volume(int volume)
{
    if (volume > VOLUME_MAX) {
        return VOLUME_MAX;
    }
    if (volume < 0) {
        return 0;
    }
    return volume;
}

/* func_020f5988: the sound slots' three hooks taken away. */
void SoundPosition_ClearHooks(void)
{
    Sound_SetUnk10Hook(NULL);
    Sound_SetVolumeHook(NULL);
    Sound_SetPanHook(NULL);
}
CLEAN_AS(func_020f5988, SoundPosition_ClearHooks)

/* func_020f59b4: the sound slots' three hooks set: the source's distance (into
 * SoundParams.unk_10), the volume at that distance and the source's pan. */
void SoundPosition_InstallHooks(void)
{
    Sound_SetUnk10Hook(func_020f5e3c);
    Sound_SetVolumeHook(func_020f5e14);
    Sound_SetPanHook(func_020f5c50);
}
CLEAN_AS(func_020f59b4, SoundPosition_InstallHooks)

/* func_020f5a3c: the byte at data_021fd238 set (the scene sound classes set it to 1 or 0);
 * nothing else in the ROM refers to it. */
void SoundPosition_SetUnusedFlag(char value)
{
    data_021fd238 = (u8) value;
}
CLEAN_AS(func_020f5a3c, SoundPosition_SetUnusedFlag)

/* func_020f5a4c: the distance curve. */
SoundDistanceCurve *SoundPosition_Curve(void)
{
    return &data_021fd248;
}
CLEAN_AS(func_020f5a4c, SoundPosition_Curve)

/* func_020f5a58: the volume (0 to 127) the curve gives at `distance`, in whole units. */
int SoundPosition_CurveVolume(SoundDistanceCurve *curve, int distance)
{
    int volume;

    if (distance >= curve->far >> 12) {
        volume = 0;
    } else if (distance <= curve->near >> 12) {
        volume = curve->near_volume >> 12;
    } else if (distance <= curve->knee >> 12) {
        volume = add32(curve->near_volume, fx_mul(sub32(to_fx(distance), curve->near), curve->slope_near)) >> 12;
    } else {
        volume = add32(curve->knee_volume, fx_mul(sub32(to_fx(distance), curve->knee), curve->slope_far)) >> 12;
    }
    return clamp_volume(volume);
}
CLEAN_AS(func_020f5a58, SoundPosition_CurveVolume)

/* func_020f5b04: the curve made for a knee at `knee` (20.12); nothing when it has that knee
 * already. With x = knee - 11: near_volume = 127 - 3x, knee_volume = 104 - 4x,
 * near = 4 + 2x/3 and far = 17 + 4x/3, and the two slopes join those points. */
void SoundPosition_SetKnee(SoundDistanceCurve *curve, fx32 knee)
{
    fx32 x;
    fx32 ratio;

    if (curve->knee == knee) {
        return;
    }
    curve->knee = knee;
    x = sub32(curve->knee, 11 * FX_ONE);

    curve->near_volume = sub32(127 * FX_ONE, fx_mul(x, 3 * FX_ONE));
    curve->knee_volume = sub32(104 * FX_ONE, fx_mul(x, 4 * FX_ONE));
    ratio = FX_Div(2 * FX_ONE, 3 * FX_ONE);
    curve->near = add32(fx_mul(ratio, x), 4 * FX_ONE);
    ratio = FX_Div(4 * FX_ONE, 3 * FX_ONE);
    curve->far = add32(fx_mul(ratio, x), 17 * FX_ONE);
    curve->slope_near = FX_Div(sub32(curve->near_volume, curve->knee_volume), sub32(curve->near, curve->knee));
    curve->slope_far = FX_Div(curve->knee_volume, sub32(curve->knee, curve->far));
}
CLEAN_AS(func_020f5b04, SoundPosition_SetKnee)

/* func_020f5c20: the curve emptied (at start-up).
 * QUIRK: the knee is kept, so a first SoundPosition_SetKnee with the knee it already has (0
 * at start-up) leaves the curve empty. */
void SoundPosition_ClearCurve(SoundDistanceCurve *curve)
{
    curve->far = 0;
    curve->near = 0;
    curve->knee_volume = 0;
    curve->near_volume = 0;
    curve->slope_far = 0;
    curve->slope_near = 0;
}
CLEAN_AS(func_020f5c20, SoundPosition_ClearCurve)

/* func_020f5c50: the pan hook: the pan of the slots' source (a position). */
int SoundPosition_HookPan(SoundParams *params)
{
    return SoundPosition_Pan(params->source, 0);
}
CLEAN_AS(func_020f5c50, SoundPosition_HookPan)

/* func_020f5c64: the pan (-128 to 127) of a sound at `pos`, by its X in whole units; 0
 * without a position. Mode 0: X from -42 to 41 spread over -111 to 110; mode 1: only the side
 * (-1, 0 or 1); mode 2: X less 128.
 * QUIRK: any other mode gives the address of `pos` itself, limited to the range (127). */
int SoundPosition_Pan(const Vec3 *pos, int mode)
{
    int x;
    int pan;

    if (pos == NULL) {
        return 0;
    }
    x = pos->x >> 12;
    switch (mode) {
        case 0:
            pan = (x + 42) * 221 / 83 - 111;
            break;
        case 1:
            pan = (x > 0) - (x < 0);
            break;
        case 2:
            pan = x - 128;
            break;
        default:
            pan = (int) (uintptr_t) pos;
            break;
    }
    if (pan < PAN_MIN) {
        return PAN_MIN;
    }
    if (pan > PAN_MAX) {
        pan = PAN_MAX;
    }
    return pan;
}
CLEAN_AS(func_020f5c64, SoundPosition_Pan)

/* func_020f5cf8: the volumes (0 to 127) of the two parts of a sound at depth `z` (20.12; 1.0
 * the deepest): the first rises from 0 at 0 to full at 0.6 and falls to 0 at 1.0, the second
 * rises from 0 at 0.6 to full at 0.8 and stays there. */
void SoundPosition_SplitVolumes(int z, int *volume_a, int *volume_b)
{
    int a;
    int b;

    if (z <= 0) {
        a = 0;
    } else if (z <= 0x99a) {
        a = fx_mul(data_021fd23c, z) >> 12;
    } else if (z > FX_ONE) {
        a = 0;
    } else {
        a = sub32(127 * FX_ONE, fx_mul(data_021fd244, z - 0x99a)) >> 12;
    }

    if (z <= 0x99a) {
        b = 0;
    } else if (z >= 0xccd) {
        b = VOLUME_MAX;
    } else {
        b = fx_mul(data_021fd240, z - 0x99a) >> 12;
    }

    *volume_a = clamp_volume(a);
    *volume_b = clamp_volume(b);
}
CLEAN_AS(func_020f5cf8, SoundPosition_SplitVolumes)

/* func_020f5e14: the volume hook: the volume at the distance the distance hook gave. */
int SoundPosition_HookVolume(SoundParams *params)
{
    return SoundPosition_VolumeAt(params->unk_10);
}
CLEAN_AS(func_020f5e14, SoundPosition_HookVolume)

/* func_020f5e24: the volume (0 to 127) a sound has at `distance`, in whole units. */
int SoundPosition_VolumeAt(int distance)
{
    return SoundPosition_CurveVolume(&data_021fd248, distance);
}
CLEAN_AS(func_020f5e24, SoundPosition_VolumeAt)

/* func_020f5e3c: the distance hook: the distance of the slots' source (a position). */
int SoundPosition_HookDistance(SoundParams *params)
{
    return SoundPosition_Distance(params->source, 0);
}
CLEAN_AS(func_020f5e3c, SoundPosition_HookDistance)

/* func_020f5e50: how far `pos` is from the listener, in whole units; 0 without a position.
 * Mode 0: in all three axes; mode 1: in Y and Z only; mode 2: in X and Y from (128, 80), X
 * counted in eighths and Y in quarters.
 * QUIRK: any other mode gives the address of `pos` itself (the game uses modes 0 to 2). */
int SoundPosition_Distance(const Vec3 *pos, int mode)
{
    fx32 x;
    fx32 y;
    fx32 z;

    if (pos == NULL) {
        return 0;
    }
    switch (mode) {
        case 0:
            z = add32(pos->z, LISTENER_Z);
            return FX_Sqrt(add32(fx_square(pos->x), add32(fx_square(pos->y), fx_square(z)))) >> 12;
        case 1:
            z = add32(pos->z, LISTENER_Z);
            return FX_Sqrt(add32(fx_square(pos->y), fx_square(z))) >> 12;
        case 2:
            x = sub32(pos->x, FLAT_CENTRE_X) >> 3;
            y = sub32(pos->y, FLAT_CENTRE_Y) >> 2;
            return FX_Sqrt(add32(fx_square(x), fx_square(y))) >> 12;
        default:
            return (int) (uintptr_t) pos;
    }
}
CLEAN_AS(func_020f5e50, SoundPosition_Distance)

/* func_020f5fa8: the volume and pan of a sound at `pos` given to tracks 0-3 of `handle`. */
void SoundPosition_ApplyToHandle(SoundHandle *handle, const Vec3 *pos)
{
    int volume = SoundPosition_VolumeAt(SoundPosition_Distance(pos, 0));
    int pan = SoundPosition_Pan(pos, 0);

    NNS_SndPlayerSetTrackVolume(handle, POSITION_TRACKS, volume);
    func_0210b634(handle, POSITION_TRACKS, pan);
}
CLEAN_AS(func_020f5fa8, SoundPosition_ApplyToHandle)
