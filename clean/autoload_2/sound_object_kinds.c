/* The sound objects' classes (sound_object_kinds.h). */
#include "sound_object_kinds.h"

#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "sound_position.h"
#include "sound_system.h"

static_assert(offsetof(SoundObjectClass, play) == 0x14, "SoundObjectClass.play");
static_assert(offsetof(SoundObjectBody, raised) == 0x0c, "SoundObjectBody.raised");
static_assert(sizeof(SoundObjectBody) == 0x10, "SoundObjectBody size");
static_assert(offsetof(SoundObject4, round) == 0x10, "SoundObject4.round");
static_assert(sizeof(SoundObject4) == 0x14, "SoundObject4 size");
static_assert(offsetof(SoundObject7, pattern) == 0x14, "SoundObject7.pattern");
static_assert(sizeof(SoundObject7) == 0x18, "SoundObject7 size");
static_assert(offsetof(SoundObject8, frames) == 0x10, "SoundObject8.frames");
static_assert(sizeof(SoundObject8) == 0x14, "SoundObject8 size");
static_assert(offsetof(SoundObject10, frames) == 0x12, "SoundObject10.frames");
static_assert(sizeof(SoundObject10) == 0x14, "SoundObject10 size");

extern SoundSystem data_021fd1bc;

extern void OS_Terminate(void);
extern int NNS_SndArcPlayerStartSeq(SoundHandle *handle, int seq_no);
extern int NNS_SndArcPlayerStartSeqArc(SoundHandle *handle, int seq_arc, int index);
extern void NNS_SndHandleReleaseSeq(SoundHandle *handle);
extern void NNS_SndPlayerSetVolume(SoundHandle *handle, int volume);
extern void NNS_SndPlayerSetTrackVolume(SoundHandle *handle, int track_mask, int volume);
extern void NNS_SndPlayerMoveVolume(SoundHandle *handle, int volume, int frames);
extern int NNS_SndPlayerStopSeq(SoundHandle *handle, int fade_frames);
extern int NNS_SndPlayerWriteVariable(SoundHandle *handle, int index, int value);
extern int NNS_SndPlayerReadVariable(SoundHandle *handle, int index, s16 *value);
/* NNS_SndHandleInit: the handle made empty. */
extern void func_0210b7e0(SoundHandle *handle);
/* The pan of the tracks in `track_mask`. */
extern void func_0210b634(SoundHandle *handle, u16 track_mask, int pan);
/* The tracks in `track_mask` muted or not (NNS_SndPlayerSetTrackMute, by its shape). */
extern void func_0210b6d4(SoundHandle *handle, int track_mask, int mute);

#define VOLUME_FULL 0x7f
/* The tracks the position's pan is given to: 0-3. */
#define POSITION_TRACKS 0x000f
/* The sequence archive SoundObject_PlaySeq starts from, whatever the number says. */
#define OBJECT_SEQ_ARC 1
/* The sequence archive kinds 6, 7, 8 and 10 start from (Sound_StartSeqArc). */
#define KIND_SEQ_ARC 1

static SoundObjectBody *body(void *obj)
{
    return (SoundObjectBody *) obj;
}

/* A random number below `range` from the sound system's generator. */
static unsigned int random_below(unsigned int range)
{
    return SoundSystem_Random(&data_021fd1bc, range);
}

/* The handle's sequence stopped at once, then sequence `index` of the archive started on it. */
static void restart(SoundHandle *handle, int index)
{
    Sound_StopSequence(handle, 0);
    Sound_StartSeqArc(index, KIND_SEQ_ARC, handle);
}

/* func_020f70e8: slot 5 of the base class: nothing. */
void SoundObjectBase_Play(void) {}
CLEAN_AS(func_020f70e8, SoundObjectBase_Play)

/* func_020f726c: kind 255's slot 5: one of pieces 0xad to 0xaf picked at random and started on
 * handle A, its step and phase back to 0. */
void SoundObject255_Play(SoundObjectBody *obj)
{
    obj->step = 0;
    obj->last_pick = (u8) random_below(3);
    obj->phase = 0;
    NNS_SndArcPlayerStartSeq(&obj->handle_a, (u16) (obj->last_pick + 0xad));
}
CLEAN_AS(func_020f726c, SoundObject255_Play)

/* func_020f7218: kind 255: another of pieces 0xad to 0xaf than the last, picked at random and
 * started on handle A. */
void SoundObject255_PlayOther(SoundObjectBody *obj)
{
    unsigned int pick;

    do {
        pick = random_below(3);
    } while ((u8) pick == obj->last_pick);
    obj->last_pick = (u8) pick;
    NNS_SndArcPlayerStartSeq(&obj->handle_a, (u16) (obj->last_pick + 0xad));
}
CLEAN_AS(func_020f7218, SoundObject255_PlayOther)

/* func_020f70ec: kind 255's update: at counts 10, 0x82 and 0x96, sequences 0x503 to 0x506 on
 * handle B by the phase; at 0x18f the phase moves on (0 to 2) and every seventh time another
 * piece plays on handle A. */
void SoundObject255_Update(SoundObjectBody *obj, int count, const Vec3 *pos)
{
    switch (count) {
        case 10:
            if (obj->phase == 0) {
                SoundObject_PlaySeq(obj, 0x503, &obj->handle_b);
            } else if (obj->phase == 1) {
                SoundObject_PlaySeq(obj, 0x505, &obj->handle_b);
            }
            break;
        case 0x82:
            if (obj->phase == 0) {
                SoundObject_PlaySeq(obj, 0x504, &obj->handle_b);
            }
            break;
        case 0x96:
            if (obj->phase == 1) {
                SoundObject_PlaySeq(obj, 0x506, &obj->handle_b);
            }
            break;
        case 0x18f:
            obj->step = (s8) (obj->step + 1);
            if ((u8) obj->step == 7) {
                obj->step = 0;
                SoundObject255_PlayOther(obj);
            }
            obj->phase++;
            if (obj->phase == 3) {
                obj->phase = 0;
            }
            break;
    }
    SoundObjectBase_ApplyPosition(obj, pos);
}
CLEAN_AS(func_020f70ec, SoundObject255_Update)

/* func_020f72b8: kind 9's update: at counts 0 to 4, sequences 0x501 and 0x502 started on the
 * handles that have none, and both handles' variable 0 set to 1; later counts set it to 2
 * (0x5a, both), 3, 4 and 5 (0x8c, 0xe1, 0xeb: handle A) or 3 (0xf5: handle B). */
void SoundObject9_Update(SoundObjectBody *obj, int count, const Vec3 *pos)
{
    switch (count) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            if (obj->handle_a.player == NULL) {
                SoundObject_PlaySeq(obj, 0x501, &obj->handle_a);
            }
            if (obj->handle_b.player == NULL) {
                SoundObject_PlaySeq(obj, 0x502, &obj->handle_b);
            }
            NNS_SndPlayerWriteVariable(&obj->handle_a, 0, 1);
            NNS_SndPlayerWriteVariable(&obj->handle_b, 0, 1);
            break;
        case 0x5a:
            NNS_SndPlayerWriteVariable(&obj->handle_a, 0, 2);
            NNS_SndPlayerWriteVariable(&obj->handle_b, 0, 2);
            break;
        case 0x8c:
            NNS_SndPlayerWriteVariable(&obj->handle_a, 0, 3);
            break;
        case 0xe1:
            NNS_SndPlayerWriteVariable(&obj->handle_a, 0, 4);
            break;
        case 0xeb:
            NNS_SndPlayerWriteVariable(&obj->handle_a, 0, 5);
            break;
        case 0xf5:
            NNS_SndPlayerWriteVariable(&obj->handle_b, 0, 3);
            break;
    }
    SoundObjectBase_ApplyPosition(obj, pos);
}
CLEAN_AS(func_020f72b8, SoundObject9_Update)

/* func_020f7438: kind 9's slot 5: sequences 0x501 on handle A and 0x502 on handle B. */
void SoundObject9_Play(SoundObjectBody *obj)
{
    SoundObject_PlaySeq(obj, 0x501, &obj->handle_a);
    SoundObject_PlaySeq(obj, 0x502, &obj->handle_b);
}
CLEAN_AS(func_020f7438, SoundObject9_Play)

/* func_020f746c: kind 5's update, in two variants that alternate (the step, 0 or 1, moves on at
 * count 0x1df): handle A plays 0x4fc or 0x4fd at count 1 and 0x4fe or 0x4ff at 0xe6, handle B
 * plays 0x500 from count 1 when it has nothing, and the handles' variables are set at the
 * other counts, some only in one variant. */
void SoundObject5_Update(SoundObjectBody *obj, int count, const Vec3 *pos)
{
    switch (count) {
        case 1:
            SoundObject_PlaySeq(obj, obj->step == 0 ? 0x4fc : 0x4fd, &obj->handle_a);
            if (obj->handle_b.player == NULL) {
                SoundObject_PlaySeq(obj, 0x500, &obj->handle_b);
            }
            break;
        case 0x46:
            NNS_SndPlayerWriteVariable(&obj->handle_b, 1, 1);
            break;
        case 0xd2:
            NNS_SndPlayerWriteVariable(&obj->handle_b, 2, 1);
            break;
        case 0xdc:
            NNS_SndPlayerWriteVariable(&obj->handle_b, 1, 0);
            break;
        case 0xe6:
            SoundObject_PlaySeq(obj, obj->step == 0 ? 0x4fe : 0x4ff, &obj->handle_a);
            break;
        case 0xfd:
            if (obj->step == 1) {
                NNS_SndPlayerWriteVariable(&obj->handle_b, 2, 2);
            }
            break;
        case 0x102:
            if (obj->step == 0) {
                NNS_SndPlayerWriteVariable(&obj->handle_b, 2, 2);
            }
            break;
        case 0x118:
            NNS_SndPlayerWriteVariable(&obj->handle_b, 1, 1);
            break;
        case 0x172:
            NNS_SndPlayerWriteVariable(&obj->handle_b, 1, 0);
            NNS_SndPlayerWriteVariable(&obj->handle_b, 2, 1);
            break;
        case 0x17f:
            if (obj->step == 1) {
                NNS_SndPlayerWriteVariable(&obj->handle_a, 0, 2);
            }
            break;
        case 0x186:
            if (obj->step == 0) {
                NNS_SndPlayerWriteVariable(&obj->handle_a, 0, 2);
            }
            break;
        case 0x195:
            if (obj->step == 1) {
                NNS_SndPlayerWriteVariable(&obj->handle_b, 2, 3);
            }
            break;
        case 0x1a9:
            if (obj->step == 0) {
                NNS_SndPlayerWriteVariable(&obj->handle_b, 2, 3);
            }
            break;
        case 0x1df:
            obj->step = (s8) (obj->step + 1);
            if (obj->step == 2) {
                obj->step = 0;
            }
            break;
    }
    SoundObjectBase_ApplyPosition(obj, pos);
}
CLEAN_AS(func_020f746c, SoundObject5_Update)

/* func_020f7774: kind 5's slot 5: back to the first variant; nothing is started. */
void SoundObject5_Play(SoundObjectBody *obj)
{
    obj->step = 0;
}
CLEAN_AS(func_020f7774, SoundObject5_Play)

/* func_020f7780: kind 3's update, in two variants that alternate (the step, 0 or 1, moves on at
 * count 0x15d): handle B plays 0x4f7 (count 1), 0x4f9 (0xbe) and 0x4fa (0x12c) in the first,
 * 0x4f8 (0x78) and 0x4fb (0xd2) in the second. */
void SoundObject3_Update(SoundObjectBody *obj, int count, const Vec3 *pos)
{
    switch (count) {
        case 1:
            if (obj->step == 0) {
                SoundObject_PlaySeq(obj, 0x4f7, &obj->handle_b);
            }
            break;
        case 0x78:
            if (obj->step == 1) {
                SoundObject_PlaySeq(obj, 0x4f8, &obj->handle_b);
            }
            break;
        case 0xbe:
            if (obj->step == 0) {
                SoundObject_PlaySeq(obj, 0x4f9, &obj->handle_b);
            }
            break;
        case 0xd2:
            if (obj->step == 1) {
                SoundObject_PlaySeq(obj, 0x4fb, &obj->handle_b);
            }
            break;
        case 0x12c:
            if (obj->step == 0) {
                SoundObject_PlaySeq(obj, 0x4fa, &obj->handle_b);
            }
            break;
        case 0x15d:
            obj->step = (s8) (obj->step + 1);
            if (obj->step == 2) {
                obj->step = 0;
            }
            break;
    }
    SoundObjectBase_ApplyPosition(obj, pos);
}
CLEAN_AS(func_020f7780, SoundObject3_Update)

/* func_020f78c4: kind 3's slot 5: piece 0xac on handle A, the first variant. */
void SoundObject3_Play(SoundObjectBody *obj)
{
    NNS_SndArcPlayerStartSeq(&obj->handle_a, 0xac);
    obj->step = 0;
}
CLEAN_AS(func_020f78c4, SoundObject3_Play)

/* func_020f78e8: kind 2's update, in three variants (the step, 0 to 2, moves on at count 1):
 * at count 1 handle B gets 0x4f2 when it has nothing and handle A plays 0x4f6, piece 0xf7 or
 * fades to 0x28 by the variant; handle B plays 0x4f3 to 0x4f5 and handle A's variables are set
 * at later counts; in the third variant handle A stops at 0x18f. Then the tracks' volumes are
 * set by the variant. */
void SoundObject2_Update(SoundObjectBody *obj, int count, const Vec3 *pos)
{
    switch (count) {
        case 1:
            if (obj->handle_b.player == NULL) {
                SoundObject_PlaySeq(obj, 0x4f2, &obj->handle_b);
            }
            obj->step = (s8) (obj->step + 1);
            if (obj->step == 3) {
                obj->step = 0;
            }
            switch (obj->step) {
                case 0:
                    SoundObject_PlaySeq(obj, 0x4f6, &obj->handle_a);
                    break;
                case 1:
                    NNS_SndArcPlayerStartSeq(&obj->handle_a, 0xf7);
                    break;
                case 2:
                    NNS_SndPlayerMoveVolume(&obj->handle_a, 0x28, 15);
                    break;
            }
            break;
        case 0x28:
            NNS_SndPlayerWriteVariable(&obj->handle_a, 1, 1);
            break;
        case 0x32:
            NNS_SndPlayerWriteVariable(&obj->handle_a, 0, 2);
            break;
        case 0x96:
            SoundObject_PlaySeq(obj, 0x4f3, &obj->handle_b);
            NNS_SndPlayerWriteVariable(&obj->handle_a, 0, 0);
            break;
        case 0xc8:
            SoundObject_PlaySeq(obj, 0x4f4, &obj->handle_b);
            NNS_SndPlayerWriteVariable(&obj->handle_a, 1, 2);
            break;
        case 0x12c:
            NNS_SndPlayerWriteVariable(&obj->handle_a, 0, 3);
            break;
        case 0x177:
            SoundObject_PlaySeq(obj, 0x4f5, &obj->handle_b);
            break;
        case 0x181:
            if (obj->step == 2) {
                NNS_SndPlayerStopSeq(&obj->handle_a, 15);
            }
            break;
    }

    switch (obj->step) {
        case 0:
            NNS_SndPlayerSetTrackVolume(&obj->handle_a, 0xfff, VOLUME_FULL);
            NNS_SndPlayerSetTrackVolume(&obj->handle_b, 0xfff, VOLUME_FULL);
            break;
        case 1:
            NNS_SndPlayerSetTrackVolume(&obj->handle_a, 0xfff, 100);
            NNS_SndPlayerSetTrackVolume(&obj->handle_b, 0xfff, 0);
            break;
        case 2:
            NNS_SndPlayerSetTrackVolume(&obj->handle_b, 0xfff, 100);
            break;
    }
    SoundObjectBase_ApplyPosition(obj, pos);
}
CLEAN_AS(func_020f78e8, SoundObject2_Update)

/* func_020f7b64: kind 2's slot 5: sequence 0x4f2 on handle B. */
void SoundObject2_Play(SoundObjectBody *obj)
{
    SoundObject_PlaySeq(obj, 0x4f2, &obj->handle_b);
}
CLEAN_AS(func_020f7b64, SoundObject2_Play)

/* func_020f7b7c: kind 2's slot 0: the base class's start, the step set before the first
 * variant (the update's count 1 moves it on to 0). */
void SoundObject2_Start(SoundObjectBody *obj)
{
    SoundObjectBase_Start(obj);
    obj->step = -1;
}
CLEAN_AS(func_020f7b7c, SoundObject2_Start)

/* func_020f7b98: kind 1's slot 5: sequence 0x4f1 on handle A. */
void SoundObject1_Play(SoundObjectBody *obj)
{
    SoundObject_PlaySeq(obj, 0x4f1, &obj->handle_a);
}
CLEAN_AS(func_020f7b98, SoundObject1_Play)

/* func_020f7bb0: kind 0's slot 5: sequence 0x4f0 on handle A. */
unsigned int SoundObject0_Play(SoundObjectBody *obj)
{
    return (unsigned int) SoundObject_PlaySeq(obj, 0x4f0, &obj->handle_a);
}
CLEAN_AS(func_020f7bb0, SoundObject0_Play)

/* func_020f7bc4: sequence `number` started on `handle`, from sequence archive 1 at index
 * number % 1000; the game stops without a handle. `obj` is not used.
 * QUIRK: the thousands of the number are not the archive (all the objects' numbers are in
 * the 1000s anyway). */
int SoundObject_PlaySeq(SoundObjectBody *obj, int number, SoundHandle *handle)
{
    (void) obj;
    if (handle == NULL) {
        OS_Terminate();
    }
    return NNS_SndArcPlayerStartSeqArc(handle, OBJECT_SEQ_ARC, number % 1000);
}
CLEAN_AS(func_020f7bc4, SoundObject_PlaySeq)

/* ciAddUNQUIETFilter (the ROM's symbol name does not fit it): both handles silent without a
 * position, else given the volume of its distance and the pan of its side (tracks 0-3). */
void SoundObjectBase_ApplyPosition(SoundObjectBody *obj, const Vec3 *pos)
{
    if (pos == NULL) {
        NNS_SndPlayerSetVolume(&obj->handle_a, 0);
        NNS_SndPlayerSetVolume(&obj->handle_b, 0);
        return;
    }
    int volume = SoundPosition_VolumeAt(SoundPosition_Distance(pos, 0));
    int pan = SoundPosition_Pan(pos, 0);

    NNS_SndPlayerSetVolume(&obj->handle_a, volume);
    NNS_SndPlayerSetVolume(&obj->handle_b, volume);
    func_0210b634(&obj->handle_a, POSITION_TRACKS, pan);
    func_0210b634(&obj->handle_b, POSITION_TRACKS, pan);
}
CLEAN_AS(ciAddUNQUIETFilter, SoundObjectBase_ApplyPosition)

/* func_020f7cb0: slot 4, both handles silent. */
void SoundObjectBase_Silence(SoundObjectBody *obj)
{
    NNS_SndPlayerSetVolume(&obj->handle_a, 0);
    NNS_SndPlayerSetVolume(&obj->handle_b, 0);
}
CLEAN_AS(func_020f7cb0, SoundObjectBase_Silence)

/* func_020f7cd8: slot 3, `raised` kept and both handles at full volume. */
void SoundObjectBase_Raise(SoundObjectBody *obj, unsigned char raised)
{
    obj->raised = raised;
    NNS_SndPlayerSetVolume(&obj->handle_a, VOLUME_FULL);
    NNS_SndPlayerSetVolume(&obj->handle_b, VOLUME_FULL);
}
CLEAN_AS(func_020f7cd8, SoundObjectBase_Raise)

/* ciSetQuietModeEnumJoinedChannelsA (the ROM's symbol name does not fit it): slot 2 of the base
 * class and of kinds 0 and 1, the position's volume and pan only. */
void SoundObjectBase_Update(SoundObjectBody *obj, int count, const Vec3 *pos)
{
    (void) count;
    SoundObjectBase_ApplyPosition(obj, pos);
}
CLEAN_AS(ciSetQuietModeEnumJoinedChannelsA, SoundObjectBase_Update)

/* func_020f7d14: slot 1, both handles' sequences stopped at once and released. */
void SoundObjectBase_Release(SoundObjectBody *obj)
{
    Sound_StopSequence(&obj->handle_a, 0);
    Sound_StopSequence(&obj->handle_b, 0);
    NNS_SndHandleReleaseSeq(&obj->handle_a);
    NNS_SndHandleReleaseSeq(&obj->handle_b);
}
CLEAN_AS(func_020f7d14, SoundObjectBase_Release)

/* func_020f7d4c: slot 0, the start: the handles made empty, `raised` cleared, the kind's
 * sequences started (slot 5), then both handles silent until the first update. */
void SoundObjectBase_Start(SoundObjectBody *obj)
{
    func_0210b7e0(&obj->handle_a);
    func_0210b7e0(&obj->handle_b);
    obj->raised = 0;
    obj->vtable->play(obj);
    NNS_SndPlayerSetVolume(&obj->handle_a, 0);
    NNS_SndPlayerSetVolume(&obj->handle_b, 0);
}
CLEAN_AS(func_020f7d4c, SoundObjectBase_Start)

/* func_020f7d9c: kind 10's slot 5: sequence 0x526 on handle A, mode 0. */
void SoundObject10_Play(SoundObject10 *obj)
{
    SoundObject_PlaySeq(body(obj), 0x526, &obj->handle_a);
    obj->prev_mode = 0;
    obj->mode = 0;
}
CLEAN_AS(func_020f7d9c, SoundObject10_Play)

/* func_020f7dcc: kind 10's slot 0: the base class's start, the modes and frames cleared. */
void SoundObject10_Start(SoundObject10 *obj)
{
    SoundObjectBase_Start(body(obj));
    obj->mode = 0;
    obj->prev_mode = 0;
    obj->frames = 0;
}
CLEAN_AS(func_020f7dcc, SoundObject10_Start)

/* The chances (out of 100, compared with a roll of 0 to 99) kind 10 uses at a change of mode:
 * a roll up to `group_low` picks group 0 (modes 0-4), up to `group_mid` group 1 (5-9), else
 * group 2 (10-14); a second roll up to `mode_0` picks the group's first mode, up to `mode_1`
 * its second and so on, else its fifth. */
typedef struct Kind10Chances {
    int group_low;
    int group_mid;
    int mode_0;
    int mode_1;
    int mode_2;
    int mode_3;
} Kind10Chances;

/* func_020f7df0: kind 10's update. Every update counts a frame; once a mode has lasted its
 * time (0x78 frames for the first three of each group, 0x46 for the last two, 0x64 for mode
 * 16) a new mode is picked at random, with chances that depend on the old one's group and
 * place. When the new mode's place in its group differs, handle A starts its sequence (0x13e
 * to 0x142 by the place); handle B and the tracks' volumes follow the new group, and after
 * modes 11 and 13 mode 15 or 16 may come instead (sequences 0x143 and 0x144).
 * QUIRK: mode 15's own time (0x8c frames) is never reached: as the first of its group of
 * three (15 % 5 is 0) it ends at 0x78 frames.
 * REQUIRES: `change` is 0 on entry (the ROM leaves it 0 after every update; with 1 and no mode
 * ended it would use the chances of registers never set). */
void SoundObject10_Update(SoundObject10 *obj, int count, const Vec3 *pos)
{
    static const Kind10Chances by_group_short[3] = {
        {0x32, 0x4b, 0x19, 0x32, 0x4b, 0x58},
        {0x28, 0x50, 0x19, 0x32, 0x4b, 0x58},
        {0x28, 0x3c, 0x19, 0x32, 0x4b, 0x58},
    };
    static const Kind10Chances by_group_long[3] = {
        {0x32, 0x4b, 0x23, 0x46, 0x64, 0x64},
        {0x28, 0x50, 0x23, 0x46, 0x64, 0x64},
        {0x28, 0x3c, 0x23, 0x46, 0x64, 0x64},
    };
    Kind10Chances chances = {0, 0, 0, 0, 0, 0};
    int group;
    int place;
    int roll;
    int base;

    obj->frames++;
    group = obj->mode / 5;
    place = obj->mode % 5;
    if (obj->mode == 15 && obj->frames >= 0x8c) {
        obj->change = 1;
        obj->frames = 0;
        chances = by_group_short[0];
    } else if (obj->mode == 16 && obj->frames >= 0x64) {
        obj->change = 1;
        obj->frames = 0;
        chances = by_group_short[0];
    } else if (place <= 2 && obj->frames >= 0x78) {
        obj->change = 1;
        obj->frames = 0;
        chances = by_group_short[group == 0 ? 0 : group == 1 ? 1 : 2];
    } else if (place >= 3 && obj->frames >= 0x46) {
        obj->change = 1;
        obj->frames = 0;
        chances = by_group_long[group == 0 ? 0 : group == 1 ? 1 : 2];
    }

    if (obj->change == 1) {
        Sound_StopSequence(&obj->handle_b, 0);
        obj->prev_mode = obj->mode;

        roll = (s16) random_below(100);
        if (roll <= chances.group_low) {
            base = 0;
        } else if (roll <= chances.group_mid) {
            base = 5;
        } else {
            base = 10;
        }

        roll = (s16) random_below(100);
        if (roll <= chances.mode_0) {
            place = 0;
        } else if (roll <= chances.mode_1) {
            place = 1;
        } else if (roll <= chances.mode_2) {
            place = 2;
        } else if (roll <= chances.mode_3) {
            place = 3;
        } else {
            place = 4;
        }
        obj->mode = (u16) (base + place);
        if (obj->prev_mode % 5 != obj->mode % 5) {
            restart(&obj->handle_a, 0x13e + place);
        }

        if (base / 5 == 0) {
            NNS_SndPlayerSetTrackVolume(&obj->handle_a, 3, 100);
            if (random_below(100) < 0x28 && count > 0x5a) {
                Sound_StartSeqArc(0x146, KIND_SEQ_ARC, &obj->handle_b);
                NNS_SndPlayerSetTrackVolume(&obj->handle_b, 3, 100);
            }
        } else if (base / 5 == 1) {
            NNS_SndPlayerSetTrackVolume(&obj->handle_a, 3, 0x4b);
            Sound_StartSeqArc(0x145, KIND_SEQ_ARC, &obj->handle_b);
        } else {
            NNS_SndPlayerSetTrackVolume(&obj->handle_a, 3, VOLUME_FULL);
            if (random_below(100) < 0x28 && count > 0x5a && obj->mode <= 13) {
                Sound_StartSeqArc(0x146, KIND_SEQ_ARC, &obj->handle_b);
                NNS_SndPlayerSetTrackVolume(&obj->handle_b, 3, 0x50);
            }
        }

        if (obj->prev_mode == 11 || obj->prev_mode == 13) {
            roll = (s16) random_below(100);
            if (roll <= 0x14) {
                restart(&obj->handle_a, 0x143);
                obj->mode = 15;
            } else if (roll <= 0x28) {
                restart(&obj->handle_a, 0x144);
                obj->mode = 16;
            }
        }
        obj->change = 0;
    }
    SoundObjectBase_ApplyPosition(body(obj), pos);
}
CLEAN_AS(func_020f7df0, SoundObject10_Update)

/* func_020f8444: kind 7's slot 5: sequence 0x517 on handle B, pattern 3 (taken as seen). */
void SoundObject7_Play(SoundObject7 *obj)
{
    SoundObject_PlaySeq(body(obj), 0x517, &obj->handle_b);
    obj->pattern = 3;
    obj->shown = obj->pattern;
}
CLEAN_AS(func_020f8444, SoundObject7_Play)

/* func_020f8474: kind 7's slot 0: the base class's start, the mute turn and changes cleared. */
void SoundObject7_Start(SoundObject7 *obj)
{
    SoundObjectBase_Start(body(obj));
    obj->mute_turn = 0;
    obj->changes = 0;
}
CLEAN_AS(func_020f8474, SoundObject7_Start)

/* Kind 7's patterns 1 to 5: the sequences of handles B and A. */
static void play_pattern7(SoundObject7 *obj, int seq_b, int seq_a, u16 pattern)
{
    Sound_StartSeqArc(seq_b, KIND_SEQ_ARC, &obj->handle_b);
    Sound_StartSeqArc(seq_a, KIND_SEQ_ARC, &obj->handle_a);
    obj->pattern = pattern;
}

/* func_020f8494: kind 7's update. Raised to 1, it starts over on pattern 0 (sequences 0x12d
 * and 0x132); at count 0 it picks pattern 1 (two in five) or 2; at count 0x5a (any pattern
 * but 0) one of patterns 3 to 5, at 0x78 (pattern 0) 3 or 4. Each change of pattern counts
 * towards the mute turn (the first always, the second one time in two, then a turn), and while
 * the turn is 1 handle B's tracks 0-5 are muted. */
void SoundObject7_Update(SoundObject7 *obj, int count, const Vec3 *pos)
{
    unsigned int roll;

    if (obj->raised == 1) {
        obj->raised = 0;
        restart(&obj->handle_b, 0x12d);
        restart(&obj->handle_a, 0x132);
        obj->pattern = 0;
        obj->shown = 0;
        obj->mute_turn = 0;
        obj->changes = 0;
    } else if (count == 0) {
        Sound_StopSequence(&obj->handle_b, 0);
        Sound_StopSequence(&obj->handle_a, 0);
        if (random_below(100) < 0x28) {
            play_pattern7(obj, 0x12e, 0x132, 1);
        } else {
            play_pattern7(obj, 0x130, 0x133, 2);
        }
    } else if (count == 0x5a && obj->pattern != 0) {
        roll = random_below(3);
        Sound_StopSequence(&obj->handle_b, 0);
        Sound_StopSequence(&obj->handle_a, 0);
        if (roll == 0) {
            play_pattern7(obj, 0x12f, 0x134, 3);
        } else if (roll == 1) {
            play_pattern7(obj, 0x12f, 0x135, 4);
        } else {
            play_pattern7(obj, 0x131, 0x134, 5);
        }
    } else if (count == 0x78 && obj->pattern == 0) {
        roll = random_below(2);
        Sound_StopSequence(&obj->handle_b, 0);
        Sound_StopSequence(&obj->handle_a, 0);
        if (roll == 0) {
            play_pattern7(obj, 0x12f, 0x134, 3);
        } else {
            play_pattern7(obj, 0x12f, 0x135, 4);
        }
    }

    if (obj->shown != obj->pattern) {
        if (obj->changes == 0) {
            obj->changes++;
        } else if (obj->changes == 1) {
            if (random_below(2) == 0) {
                obj->changes++;
            } else {
                obj->changes = 0;
                obj->mute_turn = (u16) ((obj->mute_turn + 1) % 2);
            }
        } else {
            obj->changes = 0;
            obj->mute_turn = (u16) ((obj->mute_turn + 1) % 2);
        }
        if (obj->mute_turn % 2 == 1) {
            func_0210b6d4(&obj->handle_b, 0x3f, 1);
        }
        obj->shown = obj->pattern;
    }
    SoundObjectBase_ApplyPosition(body(obj), pos);
}
CLEAN_AS(func_020f8494, SoundObject7_Update)

/* func_020f87f0: kind 8's slot 5: sequence 0x51f on handle A, state 0. */
int SoundObject8_Play(SoundObject8 *obj)
{
    SoundObject_PlaySeq(body(obj), 0x51f, &obj->handle_a);
    obj->state = 0;
    return 0;
}
CLEAN_AS(func_020f87f0, SoundObject8_Play)

/* func_020f8818: kind 8's slot 0: the base class's start, the frames cleared. */
void SoundObject8_Start(SoundObject8 *obj)
{
    SoundObjectBase_Start(body(obj));
    obj->frames = 0;
}
CLEAN_AS(func_020f8818, SoundObject8_Start)

/* Kind 8: one of sequences 0x13a to 0x13c on handle B, a third of the time each. */
static void play_random8(SoundObject8 *obj)
{
    unsigned int roll = random_below(100);

    Sound_StopSequence(&obj->handle_b, 0);
    if (roll < 0x21) {
        Sound_StartSeqArc(0x13a, KIND_SEQ_ARC, &obj->handle_b);
    } else if (roll < 0x42) {
        Sound_StartSeqArc(0x13b, KIND_SEQ_ARC, &obj->handle_b);
    } else {
        Sound_StartSeqArc(0x13c, KIND_SEQ_ARC, &obj->handle_b);
    }
}

/* func_020f8834: kind 8's update. Raised to 1, handle A starts over on 0x136; at counts 0,
 * 0x5a, 0x91, 0xb4 and 0xfa handle B plays (0x139, one of 0x13a to 0x13c, 0x13d) and handle A's
 * variables are set at random; at other counts handle A moves on to 0x137 and 0x138 after
 * 0x67 and 0x2bc frames and starts over at 0x384. */
void SoundObject8_Update(SoundObject8 *obj, int count, const Vec3 *pos)
{
    unsigned int roll;

    if (obj->raised == 1) {
        obj->raised = 0;
        restart(&obj->handle_a, 0x136);
        obj->frames = 0;
    } else if (count == 0) {
        if (random_below(100) < 0x46) {
            NNS_SndPlayerWriteVariable(&obj->handle_a, 0, 1);
        }
        restart(&obj->handle_b, 0x139);
    } else if (count == 0x5a) {
        if (random_below(100) < 0x3c) {
            NNS_SndPlayerWriteVariable(&obj->handle_a, 1, 1);
            obj->state = 1;
        }
        play_random8(obj);
    } else if (count == 0x91) {
        play_random8(obj);
    } else if (count == 0xb4) {
        if (random_below(100) < 0x46 && obj->state != 1) {
            NNS_SndPlayerWriteVariable(&obj->handle_a, 1, 1);
            obj->state = 2;
        }
        if (random_below(100) < 0x3c && obj->state != 1) {
            NNS_SndPlayerWriteVariable(&obj->handle_a, 0, 1);
            obj->state = 2;
        }
    } else if (count == 0xfa) {
        roll = random_below(100);
        if (obj->state != 2) {
            if (roll < 0x46) {
                NNS_SndPlayerWriteVariable(&obj->handle_a, 2, 1);
                obj->state = 3;
            } else {
                NNS_SndPlayerWriteVariable(&obj->handle_a, 0, 1);
                obj->state = 4;
            }
        }
        restart(&obj->handle_b, 0x13d);
    } else if (obj->frames == 0x67) {
        restart(&obj->handle_a, 0x137);
    } else if (obj->frames == 0x2bc) {
        restart(&obj->handle_a, 0x138);
    } else if (obj->frames == 0x384) {
        restart(&obj->handle_a, 0x136);
        obj->frames = 0;
    }
    obj->frames++;
    SoundObjectBase_ApplyPosition(body(obj), pos);
}
CLEAN_AS(func_020f8834, SoundObject8_Update)

/* func_020f8b84: kind 6's slot 5: sequences 0x50f on handle B and 0x510 on handle A, with the
 * step set (handle A's sequences follow handle B's changes). */
void SoundObject6_Play(SoundObjectBody *obj)
{
    SoundObject_PlaySeq(obj, 0x50f, &obj->handle_b);
    SoundObject_PlaySeq(obj, 0x510, &obj->handle_a);
    obj->step = 1;
}
CLEAN_AS(func_020f8b84, SoundObject6_Play)

/* Kind 6: handle A starts over on `index` while the step is set. */
static void follow6(SoundObjectBody *obj, int index)
{
    if (obj->step != 0) {
        restart(&obj->handle_a, index);
    }
}

/* func_020f8bbc: kind 6's update: at counts 0, 0x5a, 0xa0, 0x104 and 0x173 handle B's tracks
 * take new volumes and handle A starts over on 0x128 to 0x12c (while the step is set); at
 * 0x1c3 the tracks change again and the step flips. */
void SoundObject6_Update(SoundObjectBody *obj, int count, const Vec3 *pos)
{
    SoundHandle *b = &obj->handle_b;

    if (count == 0) {
        NNS_SndPlayerSetTrackVolume(b, 0x0001, 0x46);
        NNS_SndPlayerSetTrackVolume(b, 0x0002, 0x50);
        NNS_SndPlayerSetTrackVolume(b, 0x000c, 0x78);
        NNS_SndPlayerSetTrackVolume(b, 0x0010, 0x6e);
        follow6(obj, 0x128);
    } else if (count == 0x5a) {
        NNS_SndPlayerSetTrackVolume(b, 0x0001, 0x4b);
        NNS_SndPlayerSetTrackVolume(b, 0x000e, 0x6e);
        NNS_SndPlayerSetTrackVolume(b, 0x0010, 0x6e);
        follow6(obj, 0x129);
    } else if (count == 0xa0) {
        NNS_SndPlayerSetTrackVolume(b, 0x0001, 0x50);
        NNS_SndPlayerSetTrackVolume(b, 0x000e, 0x6e);
        NNS_SndPlayerSetTrackVolume(b, 0x0010, 0x6e);
        follow6(obj, 0x12a);
    } else if (count == 0x104) {
        NNS_SndPlayerSetTrackVolume(b, 0x0001, 0x50);
        NNS_SndPlayerSetTrackVolume(b, 0x000e, 0x6e);
        NNS_SndPlayerSetTrackVolume(b, 0x0010, 0x64);
        follow6(obj, 0x12b);
    } else if (count == 0x173) {
        NNS_SndPlayerSetTrackVolume(b, 0x0001, 0x4b);
        NNS_SndPlayerSetTrackVolume(b, 0x0002, 0);
        NNS_SndPlayerSetTrackVolume(b, 0x000c, 0x5a);
        NNS_SndPlayerSetTrackVolume(b, 0x0010, 0x4b);
        follow6(obj, 0x12c);
    } else if (count == 0x1c3) {
        NNS_SndPlayerSetTrackVolume(b, 0x0001, 0x55);
        NNS_SndPlayerSetTrackVolume(b, 0x000e, 0);
        NNS_SndPlayerSetTrackVolume(b, 0x0010, 0x46);
        obj->step = ((u8) obj->step + 1) % 2 != 0;
    }
    SoundObjectBase_ApplyPosition(obj, pos);
}
CLEAN_AS(func_020f8bbc, SoundObject6_Update)

/* func_020f8e6c: kind 4: handle B's variable 0 when it changed since the last read, else -1.
 * REQUIRES: the variable can be read (the ROM uses a stale stack value otherwise). */
int SoundObject4_ReadChange(SoundObject4 *obj)
{
    s16 value = 0;
    int changed;

    NNS_SndPlayerReadVariable(&obj->handle_b, 0, &value);
    changed = value != obj->last_var ? value : -1;
    obj->last_var = value;
    return changed;
}
CLEAN_AS(func_020f8e6c, SoundObject4_ReadChange)

/* func_020f8eac: kind 4's update (the count is not used): when handle B's variable 0 changes to
 * 1 to 4, handle A plays the matching sequence of the round (0x507 to 0x50a, or 0x50b to
 * 0x50e); the round changes after the fourth. */
void SoundObject4_Update(SoundObject4 *obj, int unused, const Vec3 *pos)
{
    int first = obj->round * 4 + 0x507;

    (void) unused;
    switch (SoundObject4_ReadChange(obj)) {
        case 1:
            SoundObject_PlaySeq(body(obj), first, &obj->handle_a);
            break;
        case 2:
            SoundObject_PlaySeq(body(obj), first + 1, &obj->handle_a);
            break;
        case 3:
            SoundObject_PlaySeq(body(obj), first + 2, &obj->handle_a);
            break;
        case 4:
            SoundObject_PlaySeq(body(obj), first + 3, &obj->handle_a);
            obj->round = (obj->round + 1) % 2;
            break;
    }
    SoundObjectBase_ApplyPosition(body(obj), pos);
}
CLEAN_AS(func_020f8eac, SoundObject4_Update)

/* func_020f8f7c: kind 4's slot 5: piece 0xf6 on handle B, the first round, no variable read. */
void SoundObject4_Play(SoundObject4 *obj)
{
    NNS_SndArcPlayerStartSeq(&obj->handle_b, 0xf6);
    obj->last_var = -1;
    obj->round = 0;
}
CLEAN_AS(func_020f8f7c, SoundObject4_Play)
