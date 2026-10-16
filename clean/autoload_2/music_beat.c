/* The music's beat and the part of scene class 41 that follows it (music_beat.h). */
#include "music_beat.h"

#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "sound_system.h"

static_assert(offsetof(MusicBeat, beat_frames) == 0x04, "MusicBeat.beat_frames");
static_assert(offsetof(MusicBeat, new_beat) == 0x0a, "MusicBeat.new_beat");
static_assert(offsetof(MusicBeat, tempo) == 0x0e, "MusicBeat.tempo");
static_assert(offsetof(MusicBeat, var6) == 0x12, "MusicBeat.var6");
static_assert(sizeof(MusicBeat) == 0x14, "MusicBeat size");
static_assert(offsetof(MusicShowState, frame_a) == 0x08, "MusicShowState.frame_a");
static_assert(offsetof(MusicShowState, on) == 0x14, "MusicShowState.on");
static_assert(offsetof(MusicShowState, count) == 0x18, "MusicShowState.count");
static_assert(offsetof(MusicShowState, half) == 0x1a, "MusicShowState.half");
static_assert(offsetof(MusicBeatShow, show) == 0x14, "MusicBeatShow.show");
static_assert(sizeof(MusicBeatShow) == 0x30, "MusicBeatShow size");

/* What a player handle points to, as far as these functions read it. */
typedef struct MusicPlayer {
    u8 unk_00[0x38];
    u16 seq_no; /* 0x38: the sequence it plays (the music's number) */
} MusicPlayer;

/* What the sound driver tells of a player (func_0210b4cc). */
typedef struct MusicDriverPlayerInfo {
    u8 unk_00[6];
    u16 tempo; /* 0x06 */
    u8 unk_08[8];
} MusicDriverPlayerInfo;

extern SoundSystem data_021fd1bc;
/* The classes' vtables. */
extern const MusicBeatVtable data_0213f250; /* MusicBeatShow */
extern const MusicBeatVtable data_0213f25c; /* MusicBeat */

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern int NNS_SndArcPlayerStartSeq(SoundHandle *handle, int seq_no);
extern int NNS_SndPlayerReadVariable(SoundHandle *handle, int index, s16 *value);
extern int NNS_SndPlayerReadGlobalVariable(int index, s16 *value);
extern void *SND_RecvCommandReply(u32 flags);
extern int SND_FlushCommand(u32 flags);
/* The sound driver's state read anew (NNS_SndUpdateDriverInfo, by its shape). */
extern int func_0210aa44(void);
/* What the driver tells of the handle's player; whether it has one (its shape is
 * NNS_SndPlayerReadDriverPlayerInfo's). */
extern int func_0210b4cc(SoundHandle *handle, MusicDriverPlayerInfo *info);
/* What the driver tells of track `track` of the handle's player; whether it has one (its shape
 * is NNS_SndPlayerReadDriverTrackInfo's). */
extern int func_0210b498(SoundHandle *handle, int track, u8 *info);
/* Global variable `index` set (NNS_SndPlayerWriteGlobalVariable, by its shape); always 1. */
extern int func_0210b500(int index, int value);

/* The music that sets MusicShowState.unk_15 and .style when the type is read. */
#define MUSIC_6D 0x6d
#define MUSIC_6E 0x6e
#define MUSIC_A3 0xa3
/* The sequence started on the music's handle while nothing plays there. */
#define SEQ_BEAT_KEEPER 0xf8
/* The tempo a beat is counted at while the music is stopped. */
#define TEMPO_DEFAULT 120
/* 600 in 20.12: frames a beat lasts are 600 / tempo (60 frames a second, 60 seconds). */
#define BEAT_FRAMES_NUMERATOR 0x258000
#define FX_ONE 0x1000

/* `value` shifted left as the ARM does, kept to 32 bits. */
static int shl(int value, int shift)
{
    return (int) ((u32) value << shift);
}

static int music_has_player(void)
{
    return data_021fd1bc.music.player != NULL;
}

static unsigned int music_seq_no(void)
{
    return ((const MusicPlayer *) data_021fd1bc.music.player)->seq_no;
}

/* How each style wraps the count for frame_c and frame_b (style 0 and any other: the 96
 * cycle), and what the wrapped count is divided by for each. */
typedef struct FrameCycle {
    int length;
    fx32 divisor_c;
    fx32 divisor_b;
} FrameCycle;

static FrameCycle frame_cycle(int style)
{
    switch (style) {
        case 1:
            return (FrameCycle){48, 0x1800, 0x2666};
        case 2:
            return (FrameCycle){192, 0x6000, 0x999a};
        default:
            return (FrameCycle){96, 0x3000, 0x4ccd};
    }
}

/* func_020f8fa8: the three frames from the count. frame_a is count / 3. frame_c runs from 0 to
 * 32 once per cycle of the count (its length by the style), starting at 12; type 3 takes the
 * whole count over 4.5 instead. frame_b runs from 0 to 20 once per cycle, starting at 4; type 3
 * takes a 96 cycle with the count 48 ahead while `half` is clear, and with style 3 takes the
 * count (144 ahead while `half` is clear) over 14.4 without a cycle.
 * QUIRK: frames past 32 and 20 are brought back by one turn only. */
void MusicBeatShow_UpdateFrames(MusicBeatShow *part)
{
    MusicShowState *show = &part->show;
    FrameCycle cycle = frame_cycle(show->style);
    int count;
    fx32 divisor;
    fx32 frame;

    show->frame_a = FX_Div(shl(show->count, 12), 3 * FX_ONE);

    count = show->count;
    if (show->type == 3) {
        divisor = 0x4800;
    } else {
        count = (s16) (count % cycle.length);
        divisor = cycle.divisor_c;
    }
    frame = FX_Div(shl(count, 12), divisor) + 12 * FX_ONE;
    if (frame >= 32 * FX_ONE) {
        frame -= 32 * FX_ONE;
    }
    show->frame_c = frame;

    count = show->count;
    if (show->type == 3) {
        if (show->style == 3) {
            if (show->half == 0) {
                count = (s16) (count + 0x90);
            }
            divisor = 0xe666;
        } else {
            if (show->half == 0) {
                count = (s16) (count + 0x30);
            }
            count = (s16) (count % 96);
            divisor = 0x4ccd;
        }
    } else {
        count = (s16) (count % cycle.length);
        divisor = cycle.divisor_b;
    }
    frame = FX_Div(shl(count, 12), divisor) + 4 * FX_ONE;
    if (frame >= 20 * FX_ONE) {
        frame -= 20 * FX_ONE;
    }
    show->frame_b = frame;
}
CLEAN_AS(func_020f8fa8, MusicBeatShow_UpdateFrames)

/* func_020f920c: with music on its handle, variables 0, 2 and 3 kept, and the count
 * (variable 1) with `half` flipped when it went down.
 * REQUIRES: the four variables can be read (the ROM leaves stale stack values otherwise). */
void MusicBeatShow_ReadVariables(MusicBeatShow *part)
{
    MusicShowState *show = &part->show;
    s16 count = 0;
    s16 var0 = 0;
    s16 var2 = 0;
    s16 var3 = 0;

    if (!music_has_player()) {
        return;
    }
    NNS_SndPlayerReadVariable(&data_021fd1bc.music, 1, &count);
    NNS_SndPlayerReadVariable(&data_021fd1bc.music, 0, &var0);
    NNS_SndPlayerReadVariable(&data_021fd1bc.music, 2, &var2);
    NNS_SndPlayerReadVariable(&data_021fd1bc.music, 3, &var3);

    show->var0 = (s8) var0;
    show->var2 = (s8) var2;
    show->var3 = (s8) var3;
    if (show->count > count) {
        show->half = show->half == 0;
    }
    show->count = count;
}
CLEAN_AS(func_020f920c, MusicBeatShow_ReadVariables)

/* func_020f92d0: track_kind from the first of the music's tracks 2 to 13 (track 10 aside)
 * the driver knows and whose info's byte 9 is set: 11 gives 0, 6 gives 1, 3 and 9 give 2, 5 and
 * 8 give 3, 2, 7 and 12 give 4, 4 and 13 give 5; -1 when there is none. Track 10's info is
 * read too. */
void MusicBeatShow_FindTrack(MusicBeatShow *part)
{
    u8 info[28];

    part->show.track_kind = -1;
    for (int track = 2; track <= 13; track++) {
        if (func_0210b498(&data_021fd1bc.music, track, info) == 0 || track == 10 || info[9] == 0) {
            continue;
        }
        switch (track) {
            case 6:
                part->show.track_kind = 1;
                break;
            case 3:
            case 9:
                part->show.track_kind = 2;
                break;
            case 5:
            case 8:
                part->show.track_kind = 3;
                break;
            case 2:
            case 7:
            case 12:
                part->show.track_kind = 4;
                break;
            case 4:
            case 13:
                part->show.track_kind = 5;
                break;
            case 11:
            default:
                part->show.track_kind = 0;
                break;
        }
        return;
    }
}
CLEAN_AS(func_020f92d0, MusicBeatShow_FindTrack)

/* func_020f9408: slot 0, the frame's update while on: the beat's, the tracks', the
 * variables'; then the frames once the type is known. Until then, with music on its handle,
 * the type is read (variable 4), the frames cleared, and unk_15 and the style set by the
 * music playing (unk_15 left as it is for other music). */
void MusicBeatShow_Update(MusicBeatShow *part)
{
    MusicShowState *show = &part->show;
    s16 type = 0;
    unsigned int music;

    if (show->on == 0) {
        return;
    }
    MusicBeat_Update(&part->beat);
    MusicBeatShow_FindTrack(part);
    MusicBeatShow_ReadVariables(part);

    if (show->type != -1) {
        MusicBeatShow_UpdateFrames(part);
        return;
    }
    if (!music_has_player()) {
        return;
    }

    NNS_SndPlayerReadVariable(&data_021fd1bc.music, 4, &type);
    show->type = (s8) type;
    show->frame_a = 0;
    show->frame_b = 0;
    show->frame_c = 0;

    music = music_seq_no();
    if (music == MUSIC_6D || music == MUSIC_A3) {
        show->unk_15 = 1;
    } else if (music == MUSIC_6E) {
        show->unk_15 = 2;
    }

    switch (music) {
        case 0x6d:
        case 0x9f:
        case 0xa2:
        case 0xa4:
            show->style = 1;
            break;
        case 0x67:
        case 0x68:
        case 0x6c:
        case 0x6e:
        case 0x6f:
        case 0x77:
        case 0x85:
        case 0x9e:
        case 0xa6:
            show->style = 2;
            break;
        case 0x94:
            show->style = 3;
            break;
        default:
            show->style = 0;
            break;
    }
}
CLEAN_AS(func_020f9408, MusicBeatShow_Update)

/* func_020f95f0 */
void MusicBeatShow_SetOn(MusicBeatShow *part, unsigned char on)
{
    part->show.on = on;
}
CLEAN_AS(func_020f95f0, MusicBeatShow_SetOn)

/* func_020f95f8: the destructor. QUIRK: the base class's destructor runs twice, once by each
 * of its two copies; each clears the sound system's owner. */
void *MusicBeatShow_Destruct(MusicBeatShow *part)
{
    part->beat.vtable = &data_0213f250;
    MusicBeat_Destruct(&part->beat);
    MusicBeat_DestructCopy(&part->beat);
    return part;
}
CLEAN_AS(func_020f95f8, MusicBeatShow_Destruct)

/* func_020f9624: the constructor; the part becomes the sound system's owner. */
MusicBeatShow *MusicBeatShow_Construct(MusicBeatShow *part)
{
    MusicBeat_ConstructCopy(&part->beat);
    part->beat.vtable = &data_0213f250;
    MusicShowState_Init(&part->show);
    part->show.type = -1;
    part->show.on = 0;
    part->show.style = 0;
    part->show.unk_15 = 1;
    part->show.count = -1;
    part->show.half = 1;
    data_021fd1bc.owner = part;
    return part;
}
CLEAN_AS(func_020f9624, MusicBeatShow_Construct)

/* func_020f9680: the state's set-up (the type, `on` and what follows are left as they are). */
void MusicShowState_Init(MusicShowState *show)
{
    show->track_kind = -1;
    show->var0 = -1;
    show->var2 = -1;
    show->var3 = -1;
    show->frame_c = 0;
    show->frame_b = 0;
    show->frame_a = 0;
}
CLEAN_AS(func_020f9680, MusicShowState_Init)

/* func_020f96b0: the music's tempo from the sound driver (once the driver's replies are all
 * taken and its state read anew), and the frames a beat lasts; nothing when the driver knows
 * no player for the music's handle. */
void MusicBeat_ReadTempo(MusicBeat *beat)
{
    MusicDriverPlayerInfo info;

    while (SND_RecvCommandReply(0) != NULL) {
    }
    func_0210aa44();
    SND_FlushCommand(0);

    if (func_0210b4cc(&data_021fd1bc.music, &info) == 0) {
        return;
    }
    beat->tempo = info.tempo;
    /* QUIRK: the tempo is taken as signed. */
    beat->beat_frames = FX_Div(BEAT_FRAMES_NUMERATOR, shl((s16) beat->tempo, 12));
}
CLEAN_AS(func_020f96b0, MusicBeat_ReadTempo)

/* func_020f9728: slot 0, the frame's update: sequence 0xf8 started on the music's handle when
 * nothing plays there; a new beat when global variable 2 changed; the music's variable 6
 * kept; the tempo read unless it is fixed. Global variable 1 is read and not used.
 * REQUIRES: the variables can be read (the ROM leaves stale stack values otherwise). */
void MusicBeat_Update(MusicBeat *beat)
{
    s16 unused = 0;
    s16 beat_no = 0;
    s16 var6 = 0;

    if (!music_has_player()) {
        NNS_SndArcPlayerStartSeq(&data_021fd1bc.music, SEQ_BEAT_KEEPER);
    }
    NNS_SndPlayerReadGlobalVariable(1, &unused);
    NNS_SndPlayerReadGlobalVariable(2, &beat_no);
    NNS_SndPlayerReadVariable(&data_021fd1bc.music, 6, &var6);

    beat->new_beat = beat_no != beat->beat;
    beat->beat = (s8) beat_no;
    beat->var6 = var6;

    if (beat->fixed_tempo == 0) {
        MusicBeat_ReadTempo(beat);
    }
}
CLEAN_AS(func_020f9728, MusicBeat_Update)

/* func_020f97dc: set up for the music stopped (`fixed_tempo` set: a tempo of 120 from now on)
 * or playing (the tempo set to 120 until it is read, and the music's handle stopped at once).
 * QUIRK: with the music playing, beat_frames is left as it was. */
void MusicBeat_Reset(MusicBeat *beat, unsigned char fixed_tempo)
{
    beat->fixed_tempo = fixed_tempo;
    beat->unk_0b = -1;
    beat->unk_0c = -1;
    beat->unk_09 = 0;
    beat->tempo = TEMPO_DEFAULT;
    if (beat->fixed_tempo != 0) {
        beat->beat_frames = FX_Div(BEAT_FRAMES_NUMERATOR, shl((s16) beat->tempo, 12));
    } else {
        Sound_StopSequence(&data_021fd1bc.music, 0);
    }
}
CLEAN_AS(func_020f97dc, MusicBeat_Reset)

/* func_020f9848: the second copy of the destructor (MusicBeat_Destruct). */
MusicBeat *MusicBeat_DestructCopy(MusicBeat *beat)
{
    beat->vtable = &data_0213f25c;
    data_021fd1bc.owner = NULL;
    return beat;
}
CLEAN_AS(func_020f9848, MusicBeat_DestructCopy)

/* func_020f9868: the destructor; it clears the sound system's owner, whoever it is. */
MusicBeat *MusicBeat_Destruct(MusicBeat *beat)
{
    beat->vtable = &data_0213f25c;
    data_021fd1bc.owner = NULL;
    return beat;
}
CLEAN_AS(func_020f9868, MusicBeat_Destruct)

/* The constructors' body (both copies have it). */
static MusicBeat *construct(MusicBeat *beat)
{
    beat->vtable = &data_0213f25c;
    beat->beat_frames = 0;
    beat->fixed_tempo = 0;
    beat->unk_09 = 0;
    beat->new_beat = 0;
    beat->unk_0b = -1;
    beat->unk_0c = -1;
    beat->tempo = TEMPO_DEFAULT;
    beat->beat = -1;
    func_0210b500(2, -1);
    func_0210b500(1, -1);
    return beat;
}

/* func_020f9888: the constructor; global variables 2 and 1 set to -1. */
MusicBeat *MusicBeat_Construct(MusicBeat *beat)
{
    return construct(beat);
}
CLEAN_AS(func_020f9888, MusicBeat_Construct)

/* func_020f98e8: the second copy of the constructor, the one MusicBeatShow's calls. */
void *MusicBeat_ConstructCopy(MusicBeat *beat)
{
    return construct(beat);
}
CLEAN_AS(func_020f98e8, MusicBeat_ConstructCopy)
