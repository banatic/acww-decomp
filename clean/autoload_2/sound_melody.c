/* Melodies, their two players and the sound set (sound_melody.h). */
#include "sound_melody.h"

#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "sound_position.h"
#include "sound_scene.h"
#include "sound_system.h"

static_assert(offsetof(MelodySeq, note_frames) == 0x0b, "MelodySeq.note_frames");
static_assert(offsetof(MelodyPlayer, seq_arc) == 0x08, "MelodyPlayer.seq_arc");
static_assert(offsetof(MelodyPlayer, step_frames) == 0x0e, "MelodyPlayer.step_frames");
static_assert(offsetof(MelodyPlayer, sustain) == 0x11, "MelodyPlayer.sustain");
static_assert(sizeof(MelodyPlayer) == 0x14, "MelodyPlayer size");
static_assert(offsetof(MelodySet, player_b) == 0x14, "MelodySet.player_b");
static_assert(offsetof(MelodySet, melody) == 0x28, "MelodySet.melody");
static_assert(offsetof(MelodySet, a_playing) == 0x38, "MelodySet.a_playing");
static_assert(offsetof(MelodySet, state) == 0x3c, "MelodySet.state");
static_assert(offsetof(SoundScene10, heap_level) == 0x1d, "SoundScene10.heap_level");

extern SoundSystem data_021fd1bc;
/* The melody MelodySeqs play: the sound set's own, taken by MelodySeq_Init. */
extern const u8 *data_021fd268;
/* The sequence archive a MelodySeq played before its last start. */
extern u16 data_021fd264;
/* Where MelodySeq_Start loads a melody's sounds: 1 the sound heap, above the scene's level, or
 * 2 the scene's own heap. Starts at 1; a start while the scene has not started yet uses the
 * other one than the last. */
extern u8 data_0213f0a4;
/* The steps of layout 3 that play the melody's notes, in order (0, 2, 3, ... 33). */
extern const u8 data_02138fd4[13];
/* The default melody. */
extern const u8 data_02138fe4[MELODY_STEPS];
/* The preset melodies (48). */
extern const u8 data_02138ff4[][MELODY_STEPS];

extern int NNS_SndArcPlayerStartSeqArc(SoundHandle *handle, int seq_arc, int index);
extern int NNS_SndPlayerReadVariable(SoundHandle *handle, int index, s16 *value);
extern void NNS_SndHandleReleaseSeq(SoundHandle *handle);
extern void NNS_SndHeapLoadState(void *heap, int level);
extern void NNS_SndPlayerSetVolume(SoundHandle *handle, int volume);
extern void NNS_SndPlayerSetTrackVolume(SoundHandle *handle, int track_mask, int volume);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
/* Two of the sound archive's loaders (the third and the second before NNS_SndArcLoadGroup):
 * item `number` loaded into `heap`. The game loads with the first the sequence archive it
 * starts next, and with the second the archive's number + 0x25f (or the item SoundSet_PlayAt
 * pairs with it). */
extern int func_0210e1d0(int number, void *heap);
extern int func_0210e198(int number, void *heap);
/* The pan of the tracks in `track_mask`. */
extern void func_0210b634(SoundHandle *handle, u16 track_mask, int pan);
/* A player setting next to the pan's; given 256 for a step of 5 frames, 1280 / frames for
 * others (the tempo, it seems). */
extern void func_0210b604(SoundHandle *handle, int value);

/* The variables a melody's sequence 0 sets. */
enum {
    VAR_STEP_FRAMES = 0,
    VAR_END_FRAME = 1,
    VAR_LAYOUT = 2,
    VAR_SUSTAIN = 3,
    VAR_NOTE_PERCENT = 4,
};

/* Random notes are sequences 14 to 19: a step of 13 plus 1 and a number below 6. */
#define MELODY_RANDOM_CHOICES 6
/* The sequence archive and the first index MelodyPlayer_PlaySeqD3 plays from. */
#define SEQ_ARC_D3 0xd3
#define SEQ_D3_FIRST 0x14
#define SEQ_D3_COUNT 14
/* The number MelodySet_PlayWith plays from archive 0xd3 without loading anything. */
#define MELODY_NUMBER_D3 400
/* The numbers below this load archive number + 4 (and item number + 0x263), the others
 * archive number - 0x2e (and item number + 0x231). */
#define MELODY_NUMBER_SPLIT 200
#define PRESET_COUNT 48
/* A MelodyPlayer's last step, by layout: 16 steps, 24 steps (16 notes in groups of two notes
 * and a hold), and 6 steps after layout 3's last note. */
#define LAST_STEP_LAYOUT_0 15
#define LAST_STEP_LAYOUT_1_2 23
#define LAST_STEP_AFTER_LAYOUT_3 6
#define ALL_TRACKS 0xff
/* func_0210b604's value for a step of `frames`: 0x25800 / (120 * frames). */
#define TEMPO_NUMERATOR 0x25800
#define TEMPO_PER_FRAME 120
/* The fade of MelodyPlayer_FadeOut. */
#define FADE_OUT_FRAMES 5

static MelodySet *current_set(void)
{
    return data_021fd1bc.sound_set;
}

static int is_playing(const SoundHandle *handle)
{
    return handle->player != NULL;
}

static void stop_if_playing(SoundHandle *handle)
{
    if (is_playing(handle)) {
        Sound_StopSequence(handle, 0);
    }
}

/* `a` times `b` in 20.12, rounded to nearest, kept to 32 bits (FX_Mul). */
static fx32 fx_mul(fx32 a, fx32 b)
{
    return (fx32) (u32) ((u64) ((s64) a * b + 0x800) >> 12);
}

/* The ROM's signed division (_s32_div_f): a divisor of 0 gives the numerator back. */
static int div_s32(int numerator, int divisor)
{
    if (divisor == 0) {
        return numerator;
    }
    return numerator / divisor;
}

/* --- MelodySeq --- */

/* func_020f6000: the note of the step ends: after the last step the melody is over (the note
 * stopped, the sound set idle, the player inactive and back before its first step) and 1 is
 * returned; else the note is stopped unless the next step holds it (or rests with sustain
 * 1), and 0 is returned. */
int MelodySeq_EndNote(MelodySeq *seq)
{
    u8 next;

    if (seq->step >= MELODY_STEPS - 1) {
        Sound_StopSequence(&seq->handle, 0);
        current_set()->state = MELODY_SET_IDLE;
        seq->active = 0;
        seq->step = -1;
        seq->frame = 0;
        return 1;
    }
    next = data_021fd268[seq->step + 1];
    if (next == MELODY_HOLD) {
        return 0;
    }
    if (next == MELODY_REST && seq->sustain == 1) {
        return 0;
    }
    Sound_StopSequence(&seq->handle, 0);
    return 0;
}
CLEAN_AS(func_020f6000, MelodySeq_EndNote)

/* func_020f609c: the step's note started (the one playing stopped first) with the volume and
 * pan of `pos`; a hold or a rest starts nothing. */
void MelodySeq_PlayStep(MelodySeq *seq, const Vec3 *pos)
{
    u8 note = data_021fd268[seq->step];

    switch (note) {
        case MELODY_RANDOM:
            stop_if_playing(&seq->handle);
            NNS_SndArcPlayerStartSeqArc(&seq->handle, seq->seq_arc,
                                        (u16) (note + 1 + SoundSystem_Random(&data_021fd1bc, MELODY_RANDOM_CHOICES)));
            SoundPosition_ApplyToHandle(&seq->handle, pos);
            break;
        case MELODY_HOLD:
        case MELODY_REST:
            break;
        default:
            stop_if_playing(&seq->handle);
            NNS_SndArcPlayerStartSeqArc(&seq->handle, seq->seq_arc, (u16) (note + 1));
            SoundPosition_ApplyToHandle(&seq->handle, pos);
            break;
    }
}
CLEAN_AS(func_020f609c, MelodySeq_PlayStep)

/* func_020f6194: the note length (variable 4) and sustain (variable 3) read from the player;
 * -1 for a variable that cannot be read. */
void MelodySeq_ReadVariables(MelodySeq *seq)
{
    s16 note_percent = -1;
    s16 sustain = -1;

    NNS_SndPlayerReadVariable(&seq->handle, VAR_NOTE_PERCENT, &note_percent);
    NNS_SndPlayerReadVariable(&seq->handle, VAR_SUSTAIN, &sustain);
    seq->note_percent = (s8) note_percent;
    seq->sustain = (s8) sustain;
}
CLEAN_AS(func_020f6194, MelodySeq_ReadVariables)

/* func_020f61e4: the frame's update, the notes taking the volume and pan of `pos` (NULL: full
 * volume, centre). Until the variables are read, sequence 0 is played and they are read.
 * Then a note's end is looked at once it has lasted its frames, and on each beat the next
 * step plays and the note length is worked out from the beat's.
 * REQUIRES: the current scene's sound object exists and has the beat part (SoundScene10). */
void MelodySeq_Update(MelodySeq *seq, const Vec3 *pos)
{
    const MusicBeat *beat;
    u8 new_beat;
    int percent;
    fx32 beat_frames;

    if (seq->active == 0) {
        return;
    }
    if (seq->note_percent == -1) {
        if (!is_playing(&seq->handle)) {
            Sound_StartSeqArc(0, seq->seq_arc, &seq->handle);
        }
        MelodySeq_ReadVariables(seq);
        return;
    }

    seq->frame++;
    beat = &((SoundScene10 *) data_021fd1bc.scene)->part;
    new_beat = beat->new_beat;
    if (seq->frame >= seq->note_frames) {
        int over = MelodySeq_EndNote(seq);
        seq->frame = 0;
        if (over) {
            return;
        }
    }
    if (new_beat == 0) {
        return;
    }

    seq->step = (s8) (seq->step + 1);
    seq->frame = 0;
    if (seq->step >= MELODY_STEPS) {
        MelodySeq_EndNote(seq);
        return;
    }
    MelodySeq_PlayStep(seq, pos);

    percent = seq->note_percent;
    beat_frames = beat->beat_frames;
    if (percent == 100) {
        seq->note_frames = (u8) (beat_frames >> 12);
        return;
    }
    seq->note_frames = (u8) (fx_mul(beat_frames, FX_Div((fx32) ((u32) percent << 12), 100 << 12)) >> 12);
}
CLEAN_AS(func_020f61e4, MelodySeq_Update)

/* func_020f6350: the melody started on sequence archive `seq_arc` (not while the sound set's
 * second player plays one loaded by number): the sound set marked as playing it, and the
 * archive's sounds loaded unless it is the archive played last and its sequence 0 can start
 * (tried and stopped again). Its sounds go to the sound heap above the scene's level or to
 * the scene's heap (data_0213f0a4), once the scene exists. */
void MelodySeq_Start(MelodySeq *seq, unsigned short seq_arc)
{
    MelodySet *set = current_set();
    SoundScene10 *scene;
    void *heap;
    int loaded = 0;

    if (set->state == MELODY_SET_PLAYER_B) {
        return;
    }
    Sound_StopSequence(&seq->handle, 0);
    set->state = MELODY_SET_SEQ;

    data_021fd264 = seq->seq_arc;
    seq->seq_arc = seq_arc;
    seq->active = 1;
    seq->step = -1;
    if (NNS_SndArcPlayerStartSeqArc(&seq->handle, seq->seq_arc, 0) != 0) {
        if (data_021fd264 == seq->seq_arc) {
            loaded = 1;
        }
        Sound_StopSequence(&seq->handle, 0);
    }
    if (loaded) {
        return;
    }

    scene = (SoundScene10 *) data_021fd1bc.scene;
    if (scene == NULL) {
        return;
    }
    if (scene->base.started != 0) {
        data_0213f0a4 = 2;
    } else {
        data_0213f0a4 = data_0213f0a4 == 1 ? 2 : 1;
    }
    if (data_0213f0a4 == 1) {
        heap = (void *) (uintptr_t) Sound_GetHeap();
        NNS_SndHeapLoadState(heap, scene->heap_level + 1);
    } else {
        /* QUIRK: the sound heap is asked for and not used. */
        heap = data_021fd1bc.scene_heap;
        Sound_GetHeap();
        NNS_SndHeapLoadState(heap, 0);
    }
    func_0210e1d0(seq->seq_arc, heap);
    func_0210e198(seq->seq_arc + 0x25f, heap);
}
CLEAN_AS(func_020f6350, MelodySeq_Start)

/* func_020f64c8: the melody stopped and the handle let go of. */
void MelodySeq_Stop(MelodySeq *seq)
{
    seq->active = 0;
    stop_if_playing(&seq->handle);
    NNS_SndHandleReleaseSeq(&seq->handle);
}
CLEAN_AS(func_020f64c8, MelodySeq_Stop)

/* func_020f6508: set up, inactive, with the current sound set's melody as the one MelodySeqs
 * play. */
void MelodySeq_Init(MelodySeq *seq)
{
    data_021fd268 = MelodySet_Melody(current_set());
    Sound_InitHandle(&seq->handle);
    seq->active = 0;
    seq->step = -1;
    seq->frame = 0;
    seq->sustain = -1;
    seq->note_percent = -1;
}
CLEAN_AS(func_020f6508, MelodySeq_Init)

/* func_020f655c: the destructor: nothing to do. */
void MelodySeq_Destruct(MelodySeq *seq)
{
    (void) seq;
}
CLEAN_AS(func_020f655c, MelodySeq_Destruct)

/* func_020f6560: the constructor: nothing to do (MelodySeq_Init sets it up). */
void MelodySeq_Construct(MelodySeq *seq)
{
    (void) seq;
}
CLEAN_AS(func_020f6560, MelodySeq_Construct)

/* --- MelodySet --- */

/* func_020f6564: sequence archive `seq_arc` loaded into the scene's heap; whether it was. */
int MelodySet_LoadSeqArc(MelodySet *set, int seq_arc)
{
    (void) set;
    return func_0210e1d0(seq_arc, data_021fd1bc.scene_heap);
}
CLEAN_AS(func_020f6564, MelodySet_LoadSeqArc)

/* func_020f6580: the scene's heap emptied and item `number` loaded into it (the second
 * loader). */
void MelodySet_ResetHeapAndLoad(MelodySet *set, int number)
{
    void *heap = data_021fd1bc.scene_heap;

    (void) set;
    NNS_SndHeapLoadState(heap, 0);
    func_0210e198(number, heap);
}
CLEAN_AS(func_020f6580, MelodySet_ResetHeapAndLoad)

/* func_020f65bc: the first player's sequence archive. */
void MelodySet_SetSeqArcA(MelodySet *set, unsigned short seq_arc)
{
    MelodyPlayer_SetSeqArc(&set->player_a, seq_arc);
}
CLEAN_AS(func_020f65bc, MelodySet_SetSeqArcA)

/* func_020f65c8: whether the first player had a step playing at the last update. */
unsigned char MelodySet_APlaying(MelodySet *set)
{
    return set->a_playing;
}
CLEAN_AS(func_020f65c8, MelodySet_APlaying)

/* func_020f65d0: both players' frame updates; the second player's step (-1: none). */
int MelodySet_Update(MelodySet *set)
{
    set->a_playing = MelodyPlayer_Update(&set->player_a) >= 0;
    return MelodyPlayer_Update(&set->player_b);
}
CLEAN_AS(func_020f65d0, MelodySet_Update)

/* func_020f65fc: MelodyPlayer_PlaySeqD3 on the second player. */
void MelodySet_PlaySeqD3B(MelodySet *set, int index)
{
    MelodyPlayer_PlaySeqD3(&set->player_b, index);
}
CLEAN_AS(func_020f65fc, MelodySet_PlaySeqD3B)

/* The sequence archive and the item loaded with it for each kind of MelodySet_PlayAt. */
static const u16 play_at_seq_arc[4] = {0xd4, 0xd7, 0xd5, 0xd6};
static const u16 play_at_item[4] = {0x25f, 0x262, 0x260, 0x261};

/* func_020f660c: the set's melody played by the second player at `pos` (its volume and pan
 * kept for layout 3), from the sequence archive of `kind` (0 to 3), loaded with its item into
 * the emptied scene heap. Nothing while the second player plays a melody loaded by number or
 * a MelodySeq plays; another kind only takes the volume and pan. */
void MelodySet_PlayAt(MelodySet *set, const Vec3 *pos, unsigned int kind)
{
    if (set->state == MELODY_SET_PLAYER_B || set->state == MELODY_SET_SEQ) {
        return;
    }
    set->volume = (s8) (u8) SoundPosition_VolumeAt(SoundPosition_Distance(pos, 0));
    set->pan = (s8) (u8) SoundPosition_Pan(pos, 0);
    set->state = MELODY_SET_AT;
    if (kind >= 4) {
        return;
    }
    MelodySet_ResetHeapAndLoad(set, play_at_item[kind]);
    MelodySet_LoadSeqArc(set, play_at_seq_arc[kind]);
    MelodyPlayer_StartArc(&set->player_b, play_at_seq_arc[kind], set->melody);
}
CLEAN_AS(func_020f660c, MelodySet_PlayAt)

/* func_020f66f0: the set's melody started on the first player. */
void MelodySet_StartA(MelodySet *set)
{
    MelodyPlayer_Start(&set->player_a, set->melody);
}
CLEAN_AS(func_020f66f0, MelodySet_StartA)

/* func_020f6700: the second player's note faded out and the player made inactive. */
void MelodySet_StopB(MelodySet *set)
{
    MelodyPlayer_FadeOut(&set->player_b);
    set->player_b.active = 0;
}
CLEAN_AS(func_020f6700, MelodySet_StopB)

/* func_020f6720: the preset melody the set last picked copied into its melody; the copy. */
u8 *MelodySet_LoadPreset(MelodySet *set)
{
    const u8 *preset = data_02138ff4[set->preset];

    for (int i = 0; i < MELODY_STEPS; i++) {
        set->melody[i] = preset[i];
    }
    return set->melody;
}
CLEAN_AS(func_020f6720, MelodySet_LoadPreset)

/* The loading of MelodySet_PlayOwn and MelodySet_PlayWith: by `number`, the scene's heap
 * emptied and loaded, then `melody` started on the second player. */
static void play_number(MelodySet *set, unsigned int number, const u8 *melody)
{
    unsigned int seq_arc;

    if (number < MELODY_NUMBER_SPLIT) {
        MelodySet_ResetHeapAndLoad(set, (int) (number + 0x263));
        seq_arc = number + 4;
    } else {
        MelodySet_ResetHeapAndLoad(set, (int) (number + 0x231));
        seq_arc = number - 0x2e;
    }
    MelodySet_LoadSeqArc(set, (int) seq_arc);
    MelodyPlayer_StartArc(&set->player_b, (u16) seq_arc, melody);
}

/* func_020f6754: a preset melody picked at random and played by the second player from the
 * sequence archive number + 4 (numbers up to 200), loaded with item number + 0x263; whether
 * it started.
 * QUIRK: a number above 200 plays nothing and returns the set's address. */
int MelodySet_PlayRandomPreset(MelodySet *set, unsigned int number)
{
    unsigned int seq_arc;

    set->state = MELODY_SET_PLAYER_B;
    set->volume = -1;
    if (number > MELODY_NUMBER_SPLIT) {
        return (int) (uintptr_t) set;
    }
    MelodySet_ResetHeapAndLoad(set, (int) (number + 0x263));
    seq_arc = number + 4;
    MelodySet_LoadSeqArc(set, (int) seq_arc);
    set->preset = (u8) SoundSystem_Random(&data_021fd1bc, PRESET_COUNT);
    return MelodyPlayer_StartArc(&set->player_b, (u16) seq_arc, data_02138ff4[set->preset]);
}
CLEAN_AS(func_020f6754, MelodySet_PlayRandomPreset)

/* func_020f67e4: the set's melody played by the second player, from the sequence archive of
 * `number` (number + 4 below 200, else number - 0x2e). */
void MelodySet_PlayOwn(MelodySet *set, unsigned int number)
{
    set->state = MELODY_SET_PLAYER_B;
    set->volume = -1;
    play_number(set, number, set->melody);
}
CLEAN_AS(func_020f67e4, MelodySet_PlayOwn)

/* func_020f688c: `melody` played by the second player, from the sequence archive of `number`
 * as MelodySet_PlayOwn's, or for number 400 from archive 0xd3 without loading anything. */
void MelodySet_PlayWith(MelodySet *set, unsigned int number, const u8 *melody)
{
    set->state = MELODY_SET_PLAYER_B;
    set->volume = -1;
    if (number == MELODY_NUMBER_D3) {
        MelodyPlayer_StartArc(&set->player_b, SEQ_ARC_D3, melody);
        return;
    }
    play_number(set, number, melody);
}
CLEAN_AS(func_020f688c, MelodySet_PlayWith)

/* func_020f6948: the set's melody. */
u8 *MelodySet_Melody(MelodySet *set)
{
    return set->melody;
}
CLEAN_AS(func_020f6948, MelodySet_Melody)

/* func_020f6950: `melody` copied into the set's. */
void MelodySet_SetMelody(MelodySet *set, const u8 *melody)
{
    for (int i = 0; i < MELODY_STEPS; i++) {
        set->melody[i] = melody[i];
    }
}
CLEAN_AS(func_020f6950, MelodySet_SetMelody)

/* func_020f6970: the default melody. */
const u8 *MelodySet_DefaultMelody(void)
{
    return data_02138fe4;
}
CLEAN_AS(func_020f6970, MelodySet_DefaultMelody)

/* func_020f697c: the set made the sound system's current one and set up: both players
 * emptied (the second first), the first on sequence archive 0; nothing playing, volume -1,
 * pan 0, preset 0. Its state is kept. */
void MelodySet_MakeCurrent(MelodySet *set)
{
    data_021fd1bc.sound_set = set;
    MelodyPlayer_Init(&set->player_b);
    MelodyPlayer_Init(&set->player_a);
    MelodyPlayer_SetSeqArc(&set->player_a, 0);
    set->a_playing = 0;
    set->volume = -1;
    set->pan = 0;
    set->preset = 0;
}
CLEAN_AS(func_020f697c, MelodySet_MakeCurrent)

/* --- MelodyPlayer --- */

/* func_020f69cc: the frame's update; the step playing, or -1 when inactive, over or still
 * reading its variables. A step lasts step_frames frames; at its end_frame-th the note's end
 * is looked at, which may end the melody (the player is then reset). */
int MelodyPlayer_Update(MelodyPlayer *player)
{
    int over = 0;

    if (player->active == 0) {
        return -1;
    }
    if (player->step_frames == -1) {
        MelodyPlayer_ReadVariables(player);
        return -1;
    }

    if (player->frame == player->end_frame) {
        over = MelodyPlayer_EndNote(player);
    }
    if (over) {
        MelodyPlayer_Reset(player);
        return player->step;
    }
    if (player->frame == 0 || player->frame == player->step_frames) {
        player->frame = 0;
        player->step = (s8) (player->step + 1);
        MelodyPlayer_PlayStep(player);
    }
    player->frame++;
    return player->step;
}
CLEAN_AS(func_020f69cc, MelodyPlayer_Update)

/* func_020f6a80: the note of the step ends: after the layout's last step the melody is over
 * (the note stopped, the sound set idle) and 1 is returned; else the note is stopped unless
 * the next step holds it (or rests with sustain 1), and 0 is returned. */
int MelodyPlayer_EndNote(MelodyPlayer *player)
{
    int last = 0;
    u8 next;

    switch (player->layout) {
        case 0:
            last = player->step == LAST_STEP_LAYOUT_0;
            break;
        case 1:
        case 2:
            last = player->step == LAST_STEP_LAYOUT_1_2;
            break;
        case 3:
            last = player->step == data_02138fd4[12] + LAST_STEP_AFTER_LAYOUT_3;
            break;
        default:
            break;
    }
    if (last) {
        Sound_StopSequence(&player->handle, 0);
        current_set()->state = MELODY_SET_IDLE;
        return 1;
    }

    next = MelodyPlayer_NoteAt(player, (u8) (player->step + 1));
    if (next == MELODY_HOLD) {
        return 0;
    }
    if (next == MELODY_REST && player->sustain == 1) {
        return 0;
    }
    Sound_StopSequence(&player->handle, 0);
    return 0;
}
CLEAN_AS(func_020f6a80, MelodyPlayer_EndNote)

/* The volume layout 3 gives its steps that play notes, by order (MelodyPlayer_PlayStep). */
static const u8 layout_3_volumes[13] = {0x40, 0x50, 0x60, 0x70, 0x7f, 0x7f, 0x70, 0x60, 0x50, 0x40, 0x30, 0x20, 0x10};

/* func_020f6ba0: the step's note started with the step's tempo; a hold or a rest starts
 * nothing. In layout 3, a step that plays a note also sets the player's volume (rising and
 * falling over the melody), and the sound set's volume and pan are given to all its tracks.
 * QUIRK: a step of 0 frames gives the tempo 0x25800 (the ROM's division by 0). */
void MelodyPlayer_PlayStep(MelodyPlayer *player)
{
    int note = MelodyPlayer_NoteAt(player, (u8) player->step);
    int tempo = div_s32(TEMPO_NUMERATOR, TEMPO_PER_FRAME * player->step_frames);
    int volume = -1;
    MelodySet *set;

    switch (note) {
        case MELODY_RANDOM:
            Sound_StartSeqArc((u16) (SoundSystem_Random(&data_021fd1bc, MELODY_RANDOM_CHOICES) + note + 1), player->seq_arc,
                              &player->handle);
            func_0210b604(&player->handle, tempo);
            break;
        case MELODY_HOLD:
        case MELODY_REST:
            break;
        default:
            Sound_StartSeqArc((u16) (note + 1), player->seq_arc, &player->handle);
            func_0210b604(&player->handle, tempo);
            break;
    }

    if (player->layout != 3) {
        return;
    }
    for (int i = 0; i < 13; i++) {
        if (player->step == data_02138fd4[i]) {
            volume = layout_3_volumes[i];
            break;
        }
    }
    if (volume != -1) {
        NNS_SndPlayerSetVolume(&player->handle, volume);
    }
    set = current_set();
    NNS_SndPlayerSetTrackVolume(&player->handle, ALL_TRACKS, set->volume);
    func_0210b634(&player->handle, ALL_TRACKS, set->pan);
}
CLEAN_AS(func_020f6ba0, MelodyPlayer_PlayStep)

/* func_020f6d78: what step `step` plays, by the player's layout:
 *   0: the melody's step `step`;
 *   1: in each group of three steps, the next two notes on the first and third, a hold on the
 *      second;
 *   2: the same with the hold on the third;
 *   3: the melody's first 13 notes on the steps data_02138fd4 lists, holds between.
 * REQUIRES: the layout is 0 to 3 (the ROM returns whatever a register held otherwise; here a
 * hold). */
u8 MelodyPlayer_NoteAt(MelodyPlayer *player, u8 step)
{
    unsigned int third = step % 3u;
    unsigned int pair = step / 3u * 2u;
    u8 note = MELODY_HOLD;
    int found = 0;

    switch (player->layout) {
        case 0:
            return player->melody[step];
        case 1:
            if (third == 1) {
                return MELODY_HOLD;
            }
            return player->melody[pair + (third != 0)];
        case 2:
            if (third == 2) {
                return MELODY_HOLD;
            }
            return player->melody[pair + (third != 0)];
        case 3:
            for (int i = 0; i < 13; i++) {
                if (step == data_02138fd4[i]) {
                    note = player->melody[i];
                    found = 1;
                }
            }
            return found ? note : MELODY_HOLD;
        default:
            return MELODY_HOLD;
    }
}
CLEAN_AS(func_020f6d78, MelodyPlayer_NoteAt)

/* func_020f6eb4: the step's frames, the end frame, the layout and the sustain read from the
 * player's variables 0 to 3; -1 for a variable that cannot be read. */
void MelodyPlayer_ReadVariables(MelodyPlayer *player)
{
    s16 step_frames = -1;
    s16 end_frame = -1;
    s16 layout = -1;
    s16 sustain = -1;

    NNS_SndPlayerReadVariable(&player->handle, VAR_STEP_FRAMES, &step_frames);
    NNS_SndPlayerReadVariable(&player->handle, VAR_END_FRAME, &end_frame);
    NNS_SndPlayerReadVariable(&player->handle, VAR_LAYOUT, &layout);
    NNS_SndPlayerReadVariable(&player->handle, VAR_SUSTAIN, &sustain);
    player->step_frames = (s8) step_frames;
    player->end_frame = (s8) end_frame;
    player->layout = (s8) layout;
    player->sustain = (s8) sustain;
}
CLEAN_AS(func_020f6eb4, MelodyPlayer_ReadVariables)

/* func_020f6f3c: inactive, before its first step, its variables unread. */
void MelodyPlayer_Reset(MelodyPlayer *player)
{
    player->active = 0;
    player->step = -1;
    player->frame = 0;
    player->sustain = -1;
    player->layout = -1;
    player->end_frame = -1;
    player->step_frames = -1;
}
CLEAN_AS(func_020f6f3c, MelodyPlayer_Reset)

/* func_020f6f70: the note playing faded out over 5 frames. */
void MelodyPlayer_FadeOut(MelodyPlayer *player)
{
    Sound_StopSequence(&player->handle, FADE_OUT_FRAMES);
}
CLEAN_AS(func_020f6f70, MelodyPlayer_FadeOut)

/* func_020f6f80: the sequence archive of its notes. */
void MelodyPlayer_SetSeqArc(MelodyPlayer *player, unsigned short seq_arc)
{
    player->seq_arc = seq_arc;
}
CLEAN_AS(func_020f6f80, MelodyPlayer_SetSeqArc)

/* func_020f6f88: the player reset and, for `index` 0 to 13, sequence 0x14 + index of
 * archive 0xd3 played on its handle (what played there stopped first). */
void MelodyPlayer_PlaySeqD3(MelodyPlayer *player, int index)
{
    MelodyPlayer_Reset(player);
    if ((unsigned int) index >= SEQ_D3_COUNT) {
        return;
    }
    stop_if_playing(&player->handle);
    Sound_StartSeqArc((u16) (index + SEQ_D3_FIRST), SEQ_ARC_D3, &player->handle);
}
CLEAN_AS(func_020f6f88, MelodyPlayer_PlaySeqD3)

/* func_020f6ff4: `melody` started from its sequence archive (sequence 0, which sets the
 * variables; the steps follow at the updates). */
void MelodyPlayer_Start(MelodyPlayer *player, const u8 *melody)
{
    MelodyPlayer_Reset(player);
    stop_if_playing(&player->handle);
    player->melody = melody;
    player->active = 1;
    Sound_StartSeqArc(0, player->seq_arc, &player->handle);
}
CLEAN_AS(func_020f6ff4, MelodyPlayer_Start)

/* func_020f7054: `melody` started from sequence archive `seq_arc`, as MelodyPlayer_Start;
 * whether sequence 0 started. */
int MelodyPlayer_StartArc(MelodyPlayer *player, unsigned short seq_arc, const u8 *melody)
{
    MelodyPlayer_Reset(player);
    stop_if_playing(&player->handle);
    player->seq_arc = seq_arc;
    player->melody = melody;
    player->active = 1;
    return Sound_StartSeqArc(0, player->seq_arc, &player->handle);
}
CLEAN_AS(func_020f7054, MelodyPlayer_StartArc)

/* ENV_SetResourceSet (the ROM's symbol name does not fit it): the player reset and its handle
 * made empty. */
void MelodyPlayer_Init(MelodyPlayer *player)
{
    MelodyPlayer_Reset(player);
    Sound_InitHandle(&player->handle);
}
CLEAN_AS(ENV_SetResourceSet, MelodyPlayer_Init)

/* func_020f70d0: the destructor: the handle's sequence released. */
MelodyPlayer *MelodyPlayer_Destruct(MelodyPlayer *player)
{
    NNS_SndHandleReleaseSeq(&player->handle);
    return player;
}
CLEAN_AS(func_020f70d0, MelodyPlayer_Destruct)
