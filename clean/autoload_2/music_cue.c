/* Music cues (music_cue.h). */
#include "music_cue.h"

#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "music_beat.h"
#include "sound_position.h"
#include "sound_scene.h"
#include "sound_system.h"

static_assert(offsetof(MusicCue, marks) == 0x06, "MusicCue.marks");
static_assert(offsetof(MusicCue, mode) == 0x08, "MusicCue.mode");
static_assert(offsetof(MusicCue, length) == 0x0e, "MusicCue.length");
static_assert(offsetof(MusicCue, reached) == 0x10, "MusicCue.reached");

/* What a player handle points to, as far as these functions read it. */
typedef struct CuePlayer {
    u8 unk_00[0x38];
    u16 seq_no; /* 0x38: the sequence it plays (the music's number) */
} CuePlayer;

extern SoundSystem data_021fd1bc;
/* The sound library's global variables 2 (the beat number, 0 to 15) and 1 (the position in
 * the beat) as last read; MusicCue_Progress may take 0x20 off the second. */
extern s16 data_021fd26c;
extern s16 data_021fd270;

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void NNS_SndPlayerSetVolume(SoundHandle *handle, int volume);
extern int NNS_SndPlayerReadVariable(SoundHandle *handle, int index, s16 *value);
extern int NNS_SndPlayerReadGlobalVariable(int index, s16 *value);
extern int NNS_SndPlayerWriteVariable(SoundHandle *handle, int index, int value);
/* The pan of the tracks in `track_mask`. */
extern void func_0210b634(SoundHandle *handle, u16 track_mask, int pan);
/* The player's tempo, it seems, as a ratio (256: as written). */
extern void func_0210b604(SoundHandle *handle, int ratio);
extern int NNS_SndArcPlayerStartSeq(SoundHandle *handle, int seq_no);
extern void NNS_SndHandleReleaseSeq(SoundHandle *handle);

/* The music whose beat counts double: the position in the beat is halved for it. */
#define MUSIC_HALF_TEMPO 0xf0
/* A span reaching to the cue's `length`. */
#define SPAN_LENGTH 0x63
/* The beat number turns every 16. */
#define BEATS 16
/* The tracks the position's pan is given to: 0-3. */
#define POSITION_TRACKS 0x000f
/* What MusicCue_Update gives while the cue is not playing. */
#define NOT_PLAYING (-0x1000)

/* `value` shifted left as the ARM does, kept to 32 bits. */
static int shl(int value, int shift)
{
    return (int) ((u32) value << shift);
}

/* The current scene's beat: its sound object's part (the scene is of class 10 or 41). */
static const MusicBeat *scene_beat(void)
{
    return &((const SoundScene10 *) data_021fd1bc.scene)->part;
}

/* Whether the music plays MUSIC_HALF_TEMPO; false without music on its handle. */
static int music_is_half_tempo(void)
{
    const CuePlayer *player = data_021fd1bc.music.player;

    return player != NULL && player->seq_no == MUSIC_HALF_TEMPO;
}

/* Beats from `start` to the current beat number, 0 to 15. */
static int beats_since(int start)
{
    int beats = data_021fd26c - start;

    if (beats < 0) {
        beats += BEATS;
    }
    return beats;
}

/* func_020f9948: how far the cue is (0 when the scene has no sound object). Layouts 1 and 3:
 * the beats since `start` and the position in the beat, 4.0 a beat (doubled and turned at
 * 64.0 for a span of 2); the beat's variable 6 says how the position counts (1: 32 a beat, then
 * 16 a beat; else 24 a beat). Other layouts: 0 to 64.0 through the span from the cue's own
 * variable 7, the position counted in 24ths, 32nds or 16ths of a beat (the beat's variable 6
 * 0, or 1 below 0x20 or from it, then taking 0x20 off global variable 1); 0 once the span's end
 * is reached, until `target` is 0.
 * BUG: a span other than 1, 2, 4 and 0x63, or a beat variable 6 other than 0 and 1, leaves the
 * span or the beat's division unset. In the ROM they keep what the only caller, MusicCue_Update,
 * left in those registers: -0x1000 and the cue's address; Clean uses the same.
 * REQUIRES: the cue's variables 7 and 12 can be read in layouts other than 1 and 3 (the ROM
 * uses stale stack values otherwise). */
int MusicCue_Progress(MusicCue *cue)
{
    const MusicBeat *beat;
    int progress;
    int beats;
    int span;
    int division;
    int position;

    if (cue->layout == 1 || cue->layout == 3) {
        progress = shl(beats_since((s16) cue->start), 14);
        if (data_021fd1bc.scene == NULL) {
            return 0;
        }
        beat = scene_beat();
        if (beat->var6 == 1) {
            position = data_021fd270;
            if (position < 0x20) {
                progress += shl(position, 14) >> 5;
            } else {
                progress += shl(position - 0x20, 14) >> 4;
            }
        } else {
            progress += FX_Div(shl(data_021fd270, 14), 0x18000);
        }
        if (cue->span == 2) {
            progress = shl(progress, 1);
            if (progress > 0x40000) {
                progress -= 0x40000;
            }
        }
        return progress;
    }

    s16 start = 0;
    s16 unused = 0;
    NNS_SndPlayerReadVariable(&cue->handle, 7, &start);
    NNS_SndPlayerReadVariable(&cue->handle, 12, &unused);
    beats = beats_since(start);

    switch (cue->span) {
        case 1:
        case 2:
        case 4:
            span = cue->span;
            break;
        case SPAN_LENGTH:
            span = cue->length;
            break;
        default:
            span = NOT_PLAYING;
            break;
    }

    if (data_021fd1bc.scene == NULL) {
        return 0;
    }
    beat = scene_beat();
    switch (beat->var6) {
        case 0:
            division = 0x18;
            break;
        case 1:
            if (data_021fd270 < 0x20) {
                division = 0x20;
            } else {
                data_021fd270 = (s16) (data_021fd270 - 0x20);
                division = 0x10;
            }
            break;
        default:
            division = (int) (uintptr_t) cue;
            break;
    }

    if (cue->reached == 0 && beats >= span) {
        cue->reached = 1;
    }
    if (cue->reached != 0 && cue->target == 0) {
        cue->reached = 0;
    }
    if (cue->reached != 0) {
        return 0;
    }
    position = (int) ((u32) beats * (u32) division + (u32) data_021fd270);
    return shl(FX_Div(shl(position, 12), shl((int) ((u32) span * (u32) division), 12)), 6);
}
CLEAN_AS(func_020f9948, MusicCue_Progress)

/* func_020f9b50: with a position, the handle given its volume and pan (tracks 0-3), then a
 * tempo ratio of the beat's tempo over 120 (256 at 120), halved for MUSIC_HALF_TEMPO; no
 * ratio is given without a scene sound object or without music on its handle. */
void MusicCue_ApplyPosition(MusicCue *cue, const Vec3 *pos)
{
    int volume;
    int pan;
    int ratio;

    if (pos == NULL) {
        return;
    }
    volume = SoundPosition_VolumeAt(SoundPosition_Distance(pos, 0));
    pan = SoundPosition_Pan(pos, 0);
    NNS_SndPlayerSetVolume(&cue->handle, volume);
    func_0210b634(&cue->handle, POSITION_TRACKS, pan);

    if (data_021fd1bc.scene == NULL) {
        return;
    }
    /* QUIRK: the tempo is taken as signed. */
    ratio = FX_Div(shl((s16) scene_beat()->tempo, 20), 120 * 0x1000) >> 12;
    if (data_021fd1bc.music.player == NULL) {
        return;
    }
    if (music_is_half_tempo()) {
        ratio >>= 1;
    }
    func_0210b604(&cue->handle, ratio);
}
CLEAN_AS(func_020f9b50, MusicCue_ApplyPosition)

/* func_020f9c0c: with a sequence playing, the layout (variable 0) and variable 5 kept, and,
 * when variable 1 is not negative, variables 1 to 4 added to the marks as four nibbles.
 * QUIRK: the marks are only ever added to, never cleared here.
 * REQUIRES: the variables can be read (the ROM uses stale stack values otherwise). */
void MusicCue_ReadMarks(MusicCue *cue)
{
    s16 layout = 0;
    s16 nibbles[4] = {0, 0, 0, 0};
    s16 span = 0;

    if (cue->handle.player == NULL) {
        return;
    }
    NNS_SndPlayerReadVariable(&cue->handle, 0, &layout);
    for (int i = 0; i < 4; i++) {
        NNS_SndPlayerReadVariable(&cue->handle, 1 + i, &nibbles[i]);
    }
    NNS_SndPlayerReadVariable(&cue->handle, 5, &span);

    cue->layout = (s8) layout;
    cue->span = (s8) span;
    if (nibbles[0] < 0) {
        return;
    }
    for (int i = 0; i < 4; i++) {
        cue->marks = (u16) (cue->marks | (u32) nibbles[3 - i] << (4 * i));
    }
}
CLEAN_AS(func_020f9c0c, MusicCue_ReadMarks)

/* func_020f9d00: the marks read while the layout is 0 or less; the beat (global variables 2
 * and 1, the second halved for MUSIC_HALF_TEMPO) and the cue's variables 8, 7, 12 and 6.
 * REQUIRES: the cue's variables can be read (the ROM uses stale stack values otherwise). */
void MusicCue_ReadVariables(MusicCue *cue)
{
    s16 beat_no = 0;
    s16 position = 0;
    s16 target = 0;
    s16 start = 0;
    s16 next = 0;
    s16 length = 0;

    if (cue->layout <= 0) {
        MusicCue_ReadMarks(cue);
    }
    NNS_SndPlayerReadGlobalVariable(2, &beat_no);
    NNS_SndPlayerReadGlobalVariable(1, &position);
    NNS_SndPlayerReadVariable(&cue->handle, 8, &target);
    NNS_SndPlayerReadVariable(&cue->handle, 7, &start);
    NNS_SndPlayerReadVariable(&cue->handle, 12, &next);
    NNS_SndPlayerReadVariable(&cue->handle, 6, &length);

    data_021fd26c = beat_no;
    data_021fd270 = position;
    cue->target = (s8) target;
    cue->start = (s8) start;
    cue->next = (s8) next;
    cue->length = (s8) length;

    if (music_is_half_tempo()) {
        data_021fd270 = (s16) (data_021fd270 >> 1);
    }
}
CLEAN_AS(func_020f9d00, MusicCue_ReadVariables)

/* Whether bit `bit` of the marks (step 15 - bit) is set; there are none above bit 15. */
static int marked(const MusicCue *cue, int bit)
{
    return bit <= 15 && ((cue->marks >> bit) & 1) != 0;
}

/* func_020f9e00: once the cue is at its next step (next equal to target), the next marked
 * step after it, or the first marked one, becomes the next and is written to variable 12;
 * 16 when no step is marked. */
void MusicCue_PickNext(MusicCue *cue)
{
    int bit;

    if (cue->next == -1 || cue->next != cue->target) {
        return;
    }
    for (bit = 15 - (cue->target + 1); bit >= 0; bit--) {
        if (marked(cue, bit)) {
            break;
        }
    }
    if (bit < 0) {
        for (bit = 15; bit >= 0; bit--) {
            if (marked(cue, bit)) {
                break;
            }
        }
    }
    cue->next = (s8) (15 - bit);
    NNS_SndPlayerWriteVariable(&cue->handle, 12, cue->next);
}
CLEAN_AS(func_020f9e00, MusicCue_PickNext)

/* func_020f9ea4: the frame's update with the cue at `pos`. Playing: the variables read, the
 * next step picked, the position and tempo applied, and the progress given; waiting: the beat
 * number read and, once it equals `target`, the cue starts playing. -0x1000 when not playing. */
int MusicCue_Update(MusicCue *cue, const Vec3 *pos)
{
    s16 beat_no = 0;

    switch (cue->mode) {
        case 1:
            MusicCue_ReadVariables(cue);
            MusicCue_PickNext(cue);
            MusicCue_ApplyPosition(cue, pos);
            return MusicCue_Progress(cue);
        case 2:
            NNS_SndPlayerReadGlobalVariable(2, &beat_no);
            data_021fd26c = beat_no;
            if (beat_no == cue->target) {
                MusicCue_SetMode(cue, 1);
            }
            break;
    }
    return NOT_PLAYING;
}
CLEAN_AS(func_020f9ea4, MusicCue_Update)

/* func_020f9f48: 3 the first time it is asked while the cue plays, else -1. */
int MusicCue_TakeStart(MusicCue *cue)
{
    if (cue->mode == 1 && cue->started == 0) {
        cue->started = 1;
        return 3;
    }
    return -1;
}
CLEAN_AS(func_020f9f48, MusicCue_TakeStart)

/* func_020f9f74: the cue waits for beat number `value` - 1 (15 for 0).
 * QUIRK: only the value's low byte counts, as a signed byte. */
void MusicCue_SetTarget(MusicCue *cue, int value)
{
    s8 target = (s8) (value - 1);

    cue->target = target < 0 ? 15 : target;
}
CLEAN_AS(func_020f9f74, MusicCue_SetTarget)

/* func_020f9f98: the sound library's global variable 2, the beat number, read and kept (in
 * data_021fd26c); its low byte.
 * REQUIRES: the variable can be read (it always can): the ROM's result is otherwise what its
 * stack held, this one's 0. */
u8 MusicCue_ReadBeat(void)
{
    s16 beat_no = 0;

    NNS_SndPlayerReadGlobalVariable(2, &beat_no);
    data_021fd26c = beat_no;
    return (u8) beat_no;
}
CLEAN_AS(func_020f9f98, MusicCue_ReadBeat)

/* func_020f9fcc: the cue's mode set: 0 off (its sequence stopped at once, and its start not
 * told yet), 1 playing (its sequence started), 2 waiting. Other modes change nothing. */
void MusicCue_SetMode(MusicCue *cue, int mode)
{
    switch (mode) {
        case 0:
            cue->mode = 0;
            cue->started = 0;
            Sound_StopSequence(&cue->handle, 0);
            break;
        case 1:
            cue->mode = 1;
            NNS_SndArcPlayerStartSeq(&cue->handle, cue->seq_no);
            break;
        case 2:
            cue->mode = 2;
            break;
    }
}
CLEAN_AS(func_020f9fcc, MusicCue_SetMode)

/* func_020fa034: the cue's sequence stopped at once and its handle let go. */
void MusicCue_Release(MusicCue *cue)
{
    Sound_StopSequence(&cue->handle, 0);
    NNS_SndHandleReleaseSeq(&cue->handle);
}
CLEAN_AS(func_020fa034, MusicCue_Release)

/* func_020fa054: the cue made afresh for sequence `seq_no`: an empty handle, no marks, no
 * next step, and neither its start told nor its end reached. */
void MusicCue_Init(MusicCue *cue, u16 seq_no)
{
    Sound_InitHandle(&cue->handle);
    cue->seq_no = seq_no;
    cue->marks = 0;
    cue->next = -1;
    cue->started = 0;
    cue->reached = 0;
}
CLEAN_AS(func_020fa054, MusicCue_Init)
