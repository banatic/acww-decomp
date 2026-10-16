/* The sound source class (sound_source.h). */
#include "sound_source.h"

#include <stddef.h>

#include "clean.h"
#include "sound_position.h"
#include "sound_system.h"

static_assert(offsetof(SoundSourceObject, number) == 0x08, "SoundSourceObject.number");
static_assert(offsetof(SoundSourceObject, flags) == 0x0a, "SoundSourceObject.flags");
static_assert(sizeof(SoundSourceObject) == 0x0c, "SoundSourceObject size");

/* NNSSndSeqParam: a sequence's parameters in the sound archive. */
typedef struct SourceSeqParam {
    u16 bank_no;
    u8 volume;
    u8 channel_priority;
    u8 player_priority;
    u8 player_no;
    u16 reserved;
} SourceSeqParam;

extern SoundSystem data_021fd1bc;
/* The tracks a source's pan is given to: 0-3 (0x000f). */
extern const u16 data_0213e858;

extern void OS_Terminate(void);
extern const SourceSeqParam *NNS_SndArcGetSeqArcParam(int seq_arc, int index);
extern void NNS_SndHandleReleaseSeq(SoundHandle *handle);
extern void NNS_SndPlayerSetVolume(SoundHandle *handle, int volume);
extern void NNS_SndPlayerSetTrackVolume(SoundHandle *handle, int track_mask, int volume);
/* The player's priority. */
extern void func_0210b734(SoundHandle *handle, int priority);
/* The pan of the tracks in `track_mask`. */
extern void func_0210b634(SoundHandle *handle, u16 track_mask, int pan);

/* Numbers with a way of their own (seq_arc * 1000 + index). */
#define SOURCE_SPLIT_A 0x4ce   /* volume split between tracks 3 and 12 */
#define SOURCE_SPLIT_B 0x80a   /* volume split between tracks 3 and 12 */
#define SOURCE_RESTART_A 0x803 /* started again at every update */
#define SOURCE_RESTART_B 0x804 /* started again at every update */
#define SOURCE_PAN_SIGN 0x80b  /* panned by side only */
#define SOURCE_VERTICAL 0x80d  /* distance in Y and Z only, pan 0 */
#define SOURCE_DEFAULT 0x837   /* started with the sequence's own parameters */

static int is_playing(const SoundSourceObject *source)
{
    return source->handle.player != NULL;
}

static void stop_if_playing(SoundSourceObject *source)
{
    if (is_playing(source)) {
        Sound_StopSequence(&source->handle, 0);
    }
}

/* The distance of the sound at `pos`, the way its number asks for. */
static int source_distance(unsigned int number, const Vec3 *pos)
{
    switch (number) {
        case SOURCE_VERTICAL:
            return SoundPosition_Distance(pos, 1);
        case 0x7f7:
        case 0x7f8:
        case 0x7fb:
        case 0x7fc:
        case 0x7fe:
        case 0x7ff:
            return SoundPosition_Distance(pos, 2);
        case SOURCE_SPLIT_A:
        case 0x7f9:
        case 0x7fa:
        case 0x7fd:
        case 0x800:
        case 0x801:
        case 0x802:
        case SOURCE_RESTART_A:
        case SOURCE_RESTART_B:
        case 0x805:
        case SOURCE_SPLIT_B:
            return 0;
        default:
            return SoundPosition_Distance(pos, 0);
    }
}

/* The pan of the sound at `pos`, the way its number asks for. */
static int source_pan(unsigned int number, const Vec3 *pos)
{
    switch (number) {
        case SOURCE_PAN_SIGN:
            return SoundPosition_Pan(pos, 1);
        case 0x805:
        case SOURCE_VERTICAL:
            return 0;
        default:
            if (number >= 0x7f7 && number <= 0x804) {
                return SoundPosition_Pan(pos, 2);
            }
            return SoundPosition_Pan(pos, 0);
    }
}

/* func_020f4648: the copy of slot 4 in vtable 0x0213f03c. */
void SoundSourceClass_UpdateB(SoundSourceObject *source, const Vec3 *pos)
{
    SoundSourceClass_Update(source, pos);
}
CLEAN_AS(func_020f4648, SoundSourceClass_UpdateB)

/* func_020f4654: the copy of slot 3 in vtable 0x0213f03c. */
void SoundSourceClass_PlayB(SoundSourceObject *source, unsigned short number)
{
    SoundSourceClass_Play(source, number);
}
CLEAN_AS(func_020f4654, SoundSourceClass_PlayB)

/* func_020f4660: the copy of slot 2 in vtable 0x0213f03c. */
void SoundSourceClass_PlayHeldB(SoundSourceObject *source, unsigned short number)
{
    SoundSourceClass_PlayHeld(source, number);
}
CLEAN_AS(func_020f4660, SoundSourceClass_PlayHeldB)

/* func_020f466c: the copy of slot 0 in vtable 0x0213f03c. */
void SoundSourceClass_InitB(SoundSourceObject *source)
{
    SoundSourceClass_Init(source);
}
CLEAN_AS(func_020f466c, SoundSourceClass_InitB)

/* func_020f4678: the copy of slot 0 in vtable 0x0213f020. */
void SoundSourceClass_InitC(SoundSourceObject *source)
{
    SoundSourceClass_Init(source);
}
CLEAN_AS(func_020f4678, SoundSourceClass_InitC)

/* func_020f4684: the copy of slot 0 in vtable 0x0213f004. */
void SoundSourceClass_InitD(SoundSourceObject *source)
{
    SoundSourceClass_Init(source);
}
CLEAN_AS(func_020f4684, SoundSourceClass_InitD)

/* func_020f4690: slot 4, the frame's update with the position relative to the listener.
 * Nothing happens while the sound system is muted (its byte 0x4d is 1). A changed number stops
 * what plays. A sound asked for is stopped when it is beyond the curve's reach or would be
 * silent; else it is started (when nothing plays, and always for 0x803 and 0x804) and, while
 * it plays, given its priority, its volume and its pan. A sound not asked for and not held is
 * stopped. */
void SoundSourceClass_Update(SoundSourceObject *source, const Vec3 *pos)
{
    unsigned int number;
    int volume;

    if (data_021fd1bc.muted == 1) {
        return;
    }
    if (source->flags & SOURCE_CHANGED) {
        stop_if_playing(source);
        source->flags &= (u8) ~SOURCE_CHANGED;
    }

    if (source->flags & SOURCE_ASKED) {
        number = source->number;
        volume = source_distance(number, pos);
        if (volume > (SoundPosition_Curve()->far >> 12)) {
            stop_if_playing(source);
            source->flags &= (u8) ~SOURCE_ASKED;
            return;
        }
        volume = SoundPosition_VolumeAt(volume);
        if (volume == 0) {
            stop_if_playing(source);
            source->flags &= (u8) ~SOURCE_ASKED;
            return;
        }

        number = source->number;
        if (!is_playing(source) || number == SOURCE_RESTART_A || number == SOURCE_RESTART_B) {
            if (number == SOURCE_DEFAULT) {
                Sound_StartSeqArc((u16) (number % 1000), (u16) (number / 1000), &source->handle);
            } else {
                int priority = SoundSourceClass_Priority((int) number, volume);
                Sound_StartSeqArcEx(&source->handle, -1, -1, priority, (int) (number / 1000), (int) (number % 1000));
            }
        }

        if (is_playing(source)) {
            int pan;

            number = source->number;
            if (number != SOURCE_DEFAULT) {
                func_0210b734(&source->handle, SoundSourceClass_Priority((int) number, volume));
            }
            number = source->number;
            pan = source_pan(number, pos);
            number = source->number;
            if (number == SOURCE_SPLIT_A || number == SOURCE_SPLIT_B) {
                int volume_a;
                int volume_b;

                SoundPosition_SplitVolumes(pos->z, &volume_a, &volume_b);
                NNS_SndPlayerSetTrackVolume(&source->handle, 3, volume_a);
                NNS_SndPlayerSetTrackVolume(&source->handle, 12, volume_b);
            } else {
                NNS_SndPlayerSetVolume(&source->handle, volume);
                func_0210b634(&source->handle, data_0213e858, pan);
            }
        }
        source->flags &= (u8) ~SOURCE_ASKED;
    } else if (!(source->flags & SOURCE_HOLD)) {
        stop_if_playing(source);
    }
    source->flags &= (u8) ~SOURCE_ASKED;
}
CLEAN_AS(func_020f4690, SoundSourceClass_Update)

/* func_020f4b1c: the player priority sound `number` starts with at `volume`: the volume
 * moved by its sequence's player priority (taken relative to 100), within 0 to 0x7f. The game
 * stops when the sequence has no parameters (OS_Terminate does not return). */
int SoundSourceClass_Priority(int number, int volume)
{
    const SourceSeqParam *param = NNS_SndArcGetSeqArcParam(number / 1000, number % 1000);
    int priority;

    if (param == NULL) {
        OS_Terminate();
        return 0; /* not reached */
    }
    priority = volume + (param->player_priority - 100);
    if (priority <= 0) {
        return 0;
    }
    return priority >= 0x7f ? 0x7f : priority;
}
CLEAN_AS(func_020f4b1c, SoundSourceClass_Priority)

/* func_020f4ba8: slot 3: sound `number` asked for this frame. */
void SoundSourceClass_Play(SoundSourceObject *source, unsigned short number)
{
    u8 flags = source->flags;

    if (source->number != number) {
        flags |= SOURCE_CHANGED;
    } else {
        flags &= (u8) ~SOURCE_CHANGED;
    }
    source->number = number;
    flags &= (u8) ~SOURCE_HOLD;
    source->flags = flags | SOURCE_ASKED;
}
CLEAN_AS(func_020f4ba8, SoundSourceClass_Play)

/* func_020f4be8: slot 2: sound `number` asked for, and kept playing while it is not asked
 * for again. */
void SoundSourceClass_PlayHeld(SoundSourceObject *source, unsigned short number)
{
    u8 flags = source->flags;

    if (source->number != number) {
        flags |= SOURCE_CHANGED;
    } else {
        flags &= (u8) ~SOURCE_CHANGED;
    }
    source->number = number;
    source->flags = flags | SOURCE_HOLD | SOURCE_ASKED;
}
CLEAN_AS(func_020f4be8, SoundSourceClass_PlayHeld)

/* func_020f4c28: slot 1: what plays stopped over 5 frames, and the handle released. */
void SoundSourceClass_Release(SoundSourceObject *source)
{
    Sound_StopSequence(&source->handle, 5);
    NNS_SndHandleReleaseSeq(&source->handle);
}
CLEAN_AS(func_020f4c28, SoundSourceClass_Release)

/* func_020f4c4c: slot 0: an empty handle, no number and no flags. */
void SoundSourceClass_Init(SoundSourceObject *source)
{
    Sound_InitHandle(&source->handle);
    source->number = 0;
    source->flags = 0;
}
CLEAN_AS(func_020f4c4c, SoundSourceClass_Init)
