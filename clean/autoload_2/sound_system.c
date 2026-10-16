/* The sound system: its music, volumes, effects and start-up (sound_system.h). */
#include "sound_system.h"

#include <stddef.h>
#include <stdint.h>

#include "clean.h"

static_assert(offsetof(SoundSystem, fader) == 0x04, "the music's fader");
static_assert(offsetof(SoundSystem, volume_b) == 0x1c, "the second group's fader");
static_assert(offsetof(SoundSystem, scene) == 0x2c, "the scene's sound");
static_assert(offsetof(SoundSystem, music) == 0x3c, "the music's handle");
static_assert(offsetof(SoundSystem, muted) == 0x4d, "the muting byte");
static_assert(offsetof(SoundSystem, random) == 0x54, "the random state");
static_assert(offsetof(SoundSystem, lowered) == 0x60, "the lowering bytes");
static_assert(offsetof(SoundSystem, tracks_in) == 0x64, "the tracks faded in");
static_assert(offsetof(SoundSystem, stream_length) == 0x68, "the stream's length");
static_assert(offsetof(SoundSystem, arrange_due) == 0x75, "the last byte");
static_assert(sizeof(SoundScene) == 8, "a scene's sound object");
static_assert(offsetof(SoundSceneVtable, on_music) == 0x28, "the music slot");

/* What a player handle points to, as far as these functions read it. */
typedef struct SoundPlayer {
    u8 unk_00[0x38];
    u16 seq_no;    /* 0x38: the sequence it plays (the music's number) */
    u16 seq_index; /* 0x3a: its index in its sequence archive (as the effects' numbers show) */
} SoundPlayer;

/* The tracks of each hourly piece: those every arrangement plays, and those of arrangements
 * 0xb, 0xc and 0xd. All four 0: the piece has no arrangements. */
typedef struct HourlyTracks {
    u16 common;
    u16 arrangement_b;
    u16 arrangement_c;
    u16 arrangement_d;
} HourlyTracks;
extern const HourlyTracks data_0213e8d0[MUSIC_HOURLY_LAST - MUSIC_HOURLY_FIRST + 1];

extern void OS_Terminate(void);
extern u64 OS_GetTick(void);
/* The ROM's symbol name: it gives the priority the sound capture's thread is made one above. */
extern int CARD_GetThreadPriority(void);
extern void *NNS_SndHeapCreate(void *memory, unsigned int size);
extern void NNS_SndCaptureCreateThread(int priority);
extern void NNS_SndCaptureStopEffect(void);
extern void NNS_SndCaptureChangeOutputEffect(int effect);
extern void NNS_SndPlayerSetVolume(SoundHandle *handle, int volume);
extern void NNS_SndPlayerSetPlayerVolume(int player_no, int volume);
extern void NNS_SndPlayerSetTrackVolume(SoundHandle *handle, int track_mask, int volume);
extern void NNS_SndPlayerSetTrackPitch(SoundHandle *handle, int track_mask, int pitch);
extern void NNS_SndPlayerMoveVolume(SoundHandle *handle, int volume, int frames);
extern int NNS_SndPlayerStopSeq(SoundHandle *handle, int fade_frames);
extern void NNS_SndPlayerStopSeqBySeqArcIdx(int seq_arc, int index, int fade_frames);
extern int NNS_SndArcPlayerStartSeq(SoundHandle *handle, int seq_no);
extern void NNS_SndArcStrmMoveVolume(SoundStreamHandle *handle, int volume, int frames);
extern u32 NNS_SndArcStrmGetCurrentPlayingPos(SoundStreamHandle *handle);
extern int NNS_SndArcStrmGetTimeLength(SoundStreamHandle *handle);
/* The pan of the tracks in `track_mask`. */
extern void func_0210b634(SoundHandle *handle, u16 track_mask, int pan);
/* The master volume. */
extern void func_0210ab38(int volume);
/* The stream handle made empty. */
extern void func_0210fbf8(SoundStreamHandle *handle);
/* The stream stopped over `fade_frames`, when there is one. */
extern void func_0210fc50(SoundStreamHandle *handle, int fade_frames);
/* Stream `stream_no` prepared and started at `offset`; whether it started. */
extern int func_0210fc7c(SoundStreamHandle *handle, int stream_no, int offset);
/* The streams' set-up, given the sound heap. */
extern void func_0210fe08(int unk, unsigned int heap);
/* The second of the sound archive's three loaders before NNS_SndArcLoadGroup (their order in
 * the SDK: sequence, sequence archive, bank); whether `seq_arc` was loaded into `heap`. */
extern int func_0210e198(int seq_arc, unsigned int heap);
/* An object of the sound code (data_021fd248) and a value handed to it each frame. */
extern void *func_020f5a4c(void);
extern void func_020f5b04(void *object, int value);
/* The compiler's soft-float helpers: an unsigned int to double, a product, a double to int. */
extern double _dfltu(int value);
extern double _dmul(double a, double b);
extern int func_0213460c(double value);

/* The player of the second effects' handle. */
#define PLAYER_EFFECT_B 10

/* The pan of the effects' tracks: all eight. */
#define ALL_TRACKS 0xff

/* `value` within 0..0x7f. */
static int clamp_volume(int value)
{
    if (value > 0x7f) {
        return 0x7f;
    }
    if (value < 0) {
        return 0;
    }
    return value;
}

/* A sound number seq_arc * 1000 + index started on `handle`. */
static int start_number(int number, SoundHandle *handle)
{
    return Sound_StartSeqArc((u16) (number % 1000), (u16) (number / 1000), handle);
}

/* The same on the default handle. */
static int start_number_default(int number)
{
    return Sound_StartSeqArcDefault((u16) (number % 1000), (u16) (number / 1000));
}

/* func_020f0e60: what the second effects' handle plays stopped at once.
 * QUIRK: the result is the SDK's, which returns nothing. */
void *SoundSystem_StopEffectB(SoundSystem *sys)
{
    return (void *) (intptr_t) Sound_StopSequence(&sys->effect_b, 0);
}
CLEAN_AS(func_020f0e60, SoundSystem_StopEffectB)

/* func_020f0e74: effect `index` of sequence archive 0 started on the second effects' handle,
 * on player 10 with the archive's bank and priority. */
void SoundSystem_PlayEffectB(SoundSystem *sys, int index)
{
    Sound_StartSeqArcEx(&sys->effect_b, PLAYER_EFFECT_B, -1, -1, 0, index);
}
CLEAN_AS(func_020f0e74, SoundSystem_PlayEffectB)

/* func_020f0ea8: a second copy of SoundSystem_PlayEffectB. */
void SoundSystem_PlayEffectBAgain(SoundSystem *sys, int index)
{
    Sound_StartSeqArcEx(&sys->effect_b, PLAYER_EFFECT_B, -1, -1, 0, index);
}
CLEAN_AS(func_020f0ea8, SoundSystem_PlayEffectBAgain)

/* func_020f0edc: the volumes of the two effects' handles from one level: 2 * level + 0x10 and
 * level + 0x50, each at most 0x7f; a negative level counts as 0. */
void SoundSystem_SetEffectLevel(SoundSystem *sys, int level)
{
    int volume = 0x10;
    int volume_b = 0x50;

    if (level >= 0) {
        volume = level * 2 + 0x10;
        volume_b = level + 0x50;
    }
    if (volume > 0x7f) {
        volume = 0x7f;
    }
    if (volume_b > 0x7f) {
        volume_b = 0x7f;
    }
    NNS_SndPlayerSetVolume(&sys->effect, volume);
    NNS_SndPlayerSetVolume(&sys->effect_b, volume_b);
}
CLEAN_AS(func_020f0edc, SoundSystem_SetEffectLevel)

/* func_020f0f34: effect 0x2c of sequence archive 0 started on the default handle; whether it
 * started. */
int SoundSystem_PlayEffect2c(SoundSystem *sys, void *unused)
{
    (void) sys;
    (void) unused;
    return Sound_StartSeqArcDefault(0x2c, 0);
}
CLEAN_AS(func_020f0f34, SoundSystem_PlayEffect2c)

/* func_020f0f48: the byte at 0x71 set to 1 for 1, else to 0. */
void SoundSystem_SetUnk71(SoundSystem *sys, int value)
{
    sys->unk_71 = value == 1 ? 1 : 0;
}
CLEAN_AS(func_020f0f48, SoundSystem_SetUnk71)

/* func_020f0f68: the effects' pan set and applied to the effects that follow it. */
void SoundSystem_SetPan(SoundSystem *sys, char pan)
{
    sys->pan = (u8) pan;
    SoundSystem_ApplyPan(sys, 1);
}
CLEAN_AS(func_020f0f68, SoundSystem_SetPan)

/* func_020f0f7c: the same, only when the pan changes. */
void SoundSystem_ChangePan(SoundSystem *sys, unsigned char pan)
{
    if (sys->pan == pan) {
        return;
    }
    sys->pan = pan;
    SoundSystem_ApplyPan(sys, 1);
}
CLEAN_AS(func_020f0f7c, SoundSystem_ChangePan)

/* func_020f0fb0: the frame's update of the scene (its slot 4): `value` handed on to
 * data_021fd248 once the delay has run out; while it runs, it is counted down instead. */
void SoundSystem_Tick(SoundSystem *sys, int value)
{
    if (sys->delay != 0) {
        sys->delay--;
        return;
    }
    func_020f5b04(func_020f5a4c(), value);
}
CLEAN_AS(func_020f0fb0, SoundSystem_Tick)

/* func_020f0ff0: the part 0x14 bytes into the owner, or NULL without one. */
int *SoundSystem_OwnerData(SoundSystem *sys)
{
    u8 *owner = sys->owner;

    if (owner == NULL) {
        return NULL;
    }
    return (int *) (owner + 0x14);
}
CLEAN_AS(func_020f0ff0, SoundSystem_OwnerData)

/* func_020f1004: the music's fader from silence to full over 60 frames. */
void SoundSystem_FadeInMusic(SoundSystem *sys)
{
    SoundFader_Set(&sys->fader, 0);
    SoundFader_Start(&sys->fader, 0x7f, 60);
}
CLEAN_AS(func_020f1004, SoundSystem_FadeInMusic)

/* func_020f1030: the second group no longer turned down: back from 0x28 to full over 15
 * frames, unless both groups are turned down. */
void SoundSystem_RaiseB(SoundSystem *sys)
{
    sys->b_lowered = 0;
    if (sys->lowered) {
        return;
    }
    SoundFader_Set(&sys->volume_b, 0x28);
    SoundFader_Start(&sys->volume_b, 0x7f, 15);
}
CLEAN_AS(func_020f1030, SoundSystem_RaiseB)

/* func_020f1074: the second group turned down from full to 0x28 over 15 frames, unless both
 * groups are turned down already. */
void SoundSystem_LowerB(SoundSystem *sys)
{
    sys->b_lowered = 1;
    if (sys->lowered) {
        return;
    }
    SoundFader_Set(&sys->volume_b, 0x7f);
    SoundFader_Start(&sys->volume_b, 0x28, 15);
}
CLEAN_AS(func_020f1074, SoundSystem_LowerB)

/* func_020f10b8: both groups back to full over 5 frames, from 0x46 and 0x28. */
void SoundSystem_RaiseBoth(SoundSystem *sys)
{
    sys->lowered = 0;
    SoundFader_Set(&sys->volume_a, 0x46);
    SoundFader_Set(&sys->volume_b, 0x28);
    SoundFader_Start(&sys->volume_a, 0x7f, 5);
    SoundFader_Start(&sys->volume_b, 0x7f, 5);
}
CLEAN_AS(func_020f10b8, SoundSystem_RaiseBoth)

/* func_020f1108: both groups turned down from full, to 0x46 and 0x28, over 15 frames. */
void SoundSystem_LowerBoth(SoundSystem *sys)
{
    sys->lowered = 1;
    SoundFader_Set(&sys->volume_a, 0x7f);
    SoundFader_Set(&sys->volume_b, 0x7f);
    SoundFader_Start(&sys->volume_a, 0x46, 15);
    SoundFader_Start(&sys->volume_b, 0x28, 15);
}
CLEAN_AS(func_020f1108, SoundSystem_LowerBoth)

/* The players of the second group that SoundSystem_LowerB turns down too. */
static const u8 group_b_extra[] = {5, 6, 16, 17, 18, 19, 20};

/* func_020f1158: the volume (within 0..0x7f) of players 5, 6 and 16 to 20. */
void SoundSystem_SetVolumeB(SoundSystem *sys, int volume)
{
    (void) sys;
    volume = clamp_volume(volume);
    for (size_t i = 0; i < sizeof(group_b_extra); i++) {
        NNS_SndPlayerSetPlayerVolume(group_b_extra[i], volume);
    }
}
CLEAN_AS(func_020f1158, SoundSystem_SetVolumeB)

/* func_020f11d0: the two groups' volumes, each within 0..0x7f: the first group's to players
 * 4, 7, 13 and 9, the second's to 8 and 11 and, unless the second group alone is turned
 * down, to 5, 6, 16, 17 and 20.
 * QUIRK: players 18 and 19 then get half the first group's volume, not the second's. */
void SoundSystem_SetVolumes(SoundSystem *sys, int volume_a, int volume_b)
{
    volume_a = clamp_volume(volume_a);
    volume_b = clamp_volume(volume_b);
    int half_a = volume_a >> 1;

    NNS_SndPlayerSetPlayerVolume(4, volume_a);
    NNS_SndPlayerSetPlayerVolume(7, volume_a);
    NNS_SndPlayerSetPlayerVolume(13, volume_a);
    NNS_SndPlayerSetPlayerVolume(9, volume_a);
    NNS_SndPlayerSetPlayerVolume(8, volume_b);
    NNS_SndPlayerSetPlayerVolume(11, volume_b);
    if (sys->b_lowered) {
        return;
    }
    NNS_SndPlayerSetPlayerVolume(5, volume_b);
    NNS_SndPlayerSetPlayerVolume(6, volume_b);
    NNS_SndPlayerSetPlayerVolume(16, volume_b);
    NNS_SndPlayerSetPlayerVolume(17, volume_b);
    NNS_SndPlayerSetPlayerVolume(18, half_a);
    NNS_SndPlayerSetPlayerVolume(19, half_a);
    NNS_SndPlayerSetPlayerVolume(20, volume_b);
}
CLEAN_AS(func_020f11d0, SoundSystem_SetVolumes)

/* func_020f12cc: the effects' pan (0x80 the middle) given to all the tracks of both effects'
 * handles; with `some_effects`, only to the effect handle's sequence and only when it is one
 * of the effects 0xb, 0x92, 0x93 and 0xb3 of its archive. */
void SoundSystem_ApplyPan(SoundSystem *sys, int some_effects)
{
    int pan = sys->pan - 0x80;

    if (!some_effects) {
        func_0210b634(&sys->effect, ALL_TRACKS, pan);
        func_0210b634(&sys->effect_b, ALL_TRACKS, pan);
        return;
    }
    const SoundPlayer *player = sys->effect.player;
    if (player == NULL) {
        return;
    }
    switch (player->seq_index) {
        case 0xb:
        case 0x92:
        case 0x93:
        case 0xb3:
            func_0210b634(&sys->effect, ALL_TRACKS, pan);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020f12cc, SoundSystem_ApplyPan)

/* The music's fader one frame on, applied to both groups when it moves. */
static void follow_fader(SoundSystem *sys)
{
    if (sys->fader.frames != 0) {
        int volume = SoundFader_Step(&sys->fader);
        SoundSystem_SetVolumes(sys, volume, volume);
    }
}

/* func_020f13bc: the frame's volumes. A scene of kind 50 keeps both groups silent while more
 * than 127 is left of the stream ((length - position) * 20 / 1000, at a position past 0), and
 * at 127 left fades them in over 160 frames; scenes of kinds 50 and 51 follow the music's
 * fader with both groups. Then the groups follow their own faders: both while the first
 * moves, else the second alone (on players 5, 6 and 16 to 20 only).
 * QUIRK: the time left is computed unsigned. */
void SoundSystem_UpdateVolumes(SoundSystem *sys)
{
    if (sys->scene == NULL) {
        return;
    }

    if (sys->scene->kind == 50) {
        u32 position = NNS_SndArcStrmGetCurrentPlayingPos(&sys->stream);
        int left = (int) (((u32) sys->stream_length - position) * 20 / 1000);
        if (position != 0) {
            if (left > 127) {
                SoundSystem_SetVolumes(sys, 0, 0);
            } else if (left == 127) {
                SoundFader_Set(&sys->fader, 0);
                SoundFader_Start(&sys->fader, 127, 160);
            }
        }
        follow_fader(sys);
    }
    if (sys->scene->kind == 51) {
        follow_fader(sys);
    }

    if (sys->volume_a.frames != 0) {
        int volume_a = SoundFader_Step(&sys->volume_a);
        int volume_b = SoundFader_Step(&sys->volume_b);
        SoundSystem_SetVolumes(sys, volume_a, volume_b);
    } else if (sys->volume_b.frames != 0) {
        SoundSystem_SetVolumeB(sys, SoundFader_Step(&sys->volume_b));
    }
}
CLEAN_AS(func_020f13bc, SoundSystem_UpdateVolumes)

/* func_020f1520: the frame's fades of the music's tracks. Scenes of kinds 0x28 to 0x31 fade
 * the tracks in `tracks_in` with the music's fader. Scenes of kinds 1 and 3 cross-fade: when
 * the delay runs out the fader goes from silence to full over 600 frames, the tracks in
 * `tracks_in` following it and those in `tracks_out` the other way. */
void SoundSystem_UpdateCrossFade(SoundSystem *sys)
{
    const SoundScene *scene = sys->scene;
    int volume;

    if (scene == NULL) {
        return;
    }
    int kind = scene->kind;

    if (kind >= 0x28 && kind < 0x32 && sys->fader.frames != 0) {
        volume = SoundFader_Step(&sys->fader);
        NNS_SndPlayerSetTrackVolume(&sys->music, sys->tracks_in, volume);
    }

    if (kind == 1 || kind == 3) {
        if (sys->cross_delay > 0) {
            sys->cross_delay--;
        } else if (sys->cross_delay == 0) {
            SoundFader_Set(&sys->fader, 0);
            SoundFader_Start(&sys->fader, 0x7f, 600);
            sys->cross_delay = -1;
        }
        if (sys->fader.frames == 0) {
            return;
        }
        volume = SoundFader_Step(&sys->fader);
        NNS_SndPlayerSetTrackVolume(&sys->music, sys->tracks_in, volume);
        NNS_SndPlayerSetTrackVolume(&sys->music, sys->tracks_out, 0x7f - volume);
    }
}
CLEAN_AS(func_020f1520, SoundSystem_UpdateCrossFade)

/* func_020f161c: the music's sequence stopped.
 * BUG: the original never sets the fade, so the SDK gets whatever the caller left in its
 * second argument register (SoundSystem_EndMusic, the one caller, leaves its own
 * `fade_frames` there). Clean stops at once. REQUIRES: the caller asked for no fade, or the
 * fade does not matter.
 * QUIRK: the result is the SDK's, which returns nothing. */
void *SoundSystem_StopMusic(SoundSystem *sys)
{
    return (void *) (intptr_t) NNS_SndPlayerStopSeq(&sys->music, 0);
}
CLEAN_AS(func_020f161c, SoundSystem_StopMusic)

/* func_020f162c: music `number` started on the music's handle at `volume`. */
void SoundSystem_PlayMusic(SoundSystem *sys, int number, int volume)
{
    NNS_SndArcPlayerStartSeq(&sys->music, number);
    NNS_SndPlayerSetVolume(&sys->music, volume);
}
CLEAN_AS(func_020f162c, SoundSystem_PlayMusic)

/* SoundSystem.arrange_step: from 0, straight to an arrangement; or between arrangements. */
enum {
    STEP_NONE = 0,
    STEP_B_TO_C = 1,
    STEP_C_TO_B = 2,
    STEP_B_TO_D = 3,
    STEP_D_TO_B = 4,
    ARRANGEMENT_B = 0xb,
    ARRANGEMENT_C = 0xc,
    ARRANGEMENT_D = 0xd,
};

/* The cross-fade between arrangements waits this many frames. */
#define CROSS_DELAY 200

/* func_020f165c: the music's arrangement chosen. A change is remembered as a step and made
 * now, or at a later call while it cannot be: only in scenes of kinds 1, 3 and 0x3c, and only
 * on an hourly piece with arrangements. The tracks of no arrangement in use are muted;
 * between arrangements B and C or B and D the tracks cross-fade after a delay
 * (SoundSystem_UpdateCrossFade). A call that gets as far as an hourly piece puts the music's
 * fader at silence and drops a cross-fade's delay first.
 * QUIRK: from arrangement 0 the step is the arrangement itself, and is not due while a fade
 * or a cross-fade's delay runs. */
void SoundSystem_SetArrangement(SoundSystem *sys, int arrangement)
{
    if (sys->arrangement != arrangement) {
        sys->arrange_due = 1;
        switch (sys->arrangement) {
            case 0:
                sys->arrange_step = (u8) arrangement;
                if (sys->cross_delay > 0 || sys->fader.frames != 0) {
                    sys->arrange_due = 0;
                }
                break;
            case ARRANGEMENT_B:
                if (arrangement == ARRANGEMENT_D) {
                    sys->arrange_step = STEP_B_TO_D;
                } else if (arrangement == ARRANGEMENT_C) {
                    sys->arrange_step = STEP_B_TO_C;
                }
                break;
            case ARRANGEMENT_C:
                sys->arrange_step = STEP_C_TO_B;
                break;
            case ARRANGEMENT_D:
                sys->arrange_step = STEP_D_TO_B;
                break;
            default:
                break;
        }
        sys->arrangement = (u8) arrangement;
    }

    if (!sys->arrange_due || sys->scene == NULL) {
        return;
    }
    int kind = sys->scene->kind;
    if (kind != 1 && kind != 3 && kind != 0x3c) {
        return;
    }
    const SoundPlayer *player = sys->music.player;
    if (player == NULL) {
        return;
    }
    unsigned int hour = (u16) (player->seq_no - MUSIC_HOURLY_FIRST);
    if (hour > MUSIC_HOURLY_LAST - MUSIC_HOURLY_FIRST) {
        return;
    }
    sys->cross_delay = -1;
    SoundFader_Start(&sys->fader, 0, 0);
    const HourlyTracks *tracks = &data_0213e8d0[hour];
    if (tracks->common == 0 && tracks->arrangement_b == 0 && tracks->arrangement_c == 0 && tracks->arrangement_d == 0) {
        return;
    }

    u16 heard;
    switch (sys->arrange_step) {
        case STEP_B_TO_C:
            heard = tracks->common | tracks->arrangement_b;
            sys->cross_delay = CROSS_DELAY;
            sys->tracks_in = tracks->arrangement_c;
            sys->tracks_out = tracks->arrangement_b;
            sys->arrange_step = ARRANGEMENT_C;
            break;
        case STEP_C_TO_B:
            heard = tracks->common | tracks->arrangement_c;
            sys->cross_delay = CROSS_DELAY;
            sys->tracks_in = tracks->arrangement_b;
            sys->tracks_out = tracks->arrangement_c;
            sys->arrange_step = ARRANGEMENT_B;
            break;
        case STEP_B_TO_D:
            heard = tracks->common | tracks->arrangement_b;
            sys->cross_delay = CROSS_DELAY;
            sys->tracks_in = tracks->arrangement_d;
            sys->tracks_out = tracks->arrangement_b;
            sys->arrange_step = ARRANGEMENT_D;
            break;
        case STEP_D_TO_B:
            heard = tracks->common | tracks->arrangement_d;
            sys->cross_delay = CROSS_DELAY;
            sys->tracks_in = tracks->arrangement_b;
            sys->tracks_out = tracks->arrangement_d;
            sys->arrange_step = ARRANGEMENT_B;
            break;
        case ARRANGEMENT_B:
            heard = tracks->common | tracks->arrangement_b;
            sys->tracks_in = heard;
            break;
        case ARRANGEMENT_C:
            heard = tracks->common | tracks->arrangement_c;
            sys->tracks_in = heard;
            break;
        case ARRANGEMENT_D:
            heard = tracks->common | tracks->arrangement_d;
            sys->tracks_in = heard;
            break;
        default:
            return;
    }
    NNS_SndPlayerSetTrackVolume(&sys->music, (u16) ~heard, 0);
    sys->arrange_due = 0;
}
CLEAN_AS(func_020f165c, SoundSystem_SetArrangement)

/* The music's tracks left on by each track set of SoundSystem_FadeInTracks (1 to 5) and
 * SoundSystem_SetTracks (1 to 6, 11 to 15); 0 for no set. */
static u16 tracks_of_set(int set)
{
    switch (set) {
        case 1:
            return 0x84;
        case 2:
            return 0x18;
        case 3:
            return 0x1800;
        case 4:
            return 0x700;
        case 5:
            return 0x63;
        case 6:
            return 0xff18;
        case 11:
            return 0xff9c;
        case 12:
            return 0xff84;
        case 13:
            return 0xe79c;
        case 14:
            return 0xf89c;
        case 15:
            return 0xf8ff;
        default:
            return 0;
    }
}

/* func_020f19c0: the music's fader from silence to full over 15 frames, with the tracks of set
 * `set` (1 to 5; others keep the tracks there are). */
void SoundSystem_FadeInTracks(SoundSystem *sys, unsigned int set)
{
    SoundFader_Set(&sys->fader, 0);
    if (set >= 1 && set <= 5) {
        sys->tracks_in = tracks_of_set((int) set);
    }
    SoundFader_Start(&sys->fader, 0x7f, 15);
}
CLEAN_AS(func_020f19c0, SoundSystem_FadeInTracks)

/* func_020f1a54: the tracks of set `set` chosen with the music's fader put at full: sets 1 to 5
 * then fade out over 15 frames, sets 6 and 11 to 15 mute every other track at once. Other
 * sets do nothing past the fader. */
void SoundSystem_SetTracks(SoundSystem *sys, int set)
{
    SoundFader_Set(&sys->fader, 0x7f);
    u16 tracks = tracks_of_set(set);
    if (tracks == 0) {
        return;
    }
    sys->tracks_in = tracks;
    if (set >= 6) {
        NNS_SndPlayerSetTrackVolume(&sys->music, sys->tracks_in, 0);
    } else {
        SoundFader_Start(&sys->fader, 0, 15);
    }
}
CLEAN_AS(func_020f1a54, SoundSystem_SetTracks)

/* func_020f1ba4: the music's volume moved to `volume` (within 0..0x7f) over `frames`, on the
 * stream when there is one. */
void SoundSystem_MoveMusicVolume(SoundSystem *sys, int volume, int frames)
{
    volume = clamp_volume(volume);
    if (sys->stream.stream != NULL) {
        NNS_SndArcStrmMoveVolume(&sys->stream, volume, frames);
    } else {
        NNS_SndPlayerMoveVolume(&sys->music, volume, frames);
    }
}
CLEAN_AS(func_020f1ba4, SoundSystem_MoveMusicVolume)

/* func_020f1c00: the music ended: the stream stopped over `fade_frames` (one more in a scene of
 * kind 51), or else the music's sequence stopped (SoundSystem_StopMusic, which drops the fade)
 * and the scene told. REQUIRES: there is a scene. */
void SoundSystem_EndMusic(SoundSystem *sys, int fade_frames)
{
    if (sys->stream.stream != NULL) {
        if (sys->scene->kind == 51) {
            fade_frames++;
        }
        func_0210fc50(&sys->stream, fade_frames);
        return;
    }
    SoundSystem_StopMusic(sys);
    sys->scene->vtable->on_music(sys->scene, 1, 9999);
}
CLEAN_AS(func_020f1c00, SoundSystem_EndMusic)

/* func_020f1c6c: music `music` started. Numbers 0 and 1 are streams, started from their start;
 * stream 0's length is kept. Others play on the music's handle, the scene told first: at full
 * volume, or silent for 0xb0 to 0xf5; an hourly piece has its arrangement made again.
 * REQUIRES: there is a scene. */
void SoundSystem_ChangeMusic(SoundSystem *sys, unsigned int music)
{
    if (music <= MUSIC_STREAM_LAST) {
        func_0210fc7c(&sys->stream, (int) music, 0);
        if (music == 0) {
            sys->stream_length = NNS_SndArcStrmGetTimeLength(&sys->stream);
        }
        return;
    }

    sys->scene->vtable->on_music(sys->scene, 0, (int) music);
    if (music >= MUSIC_SILENT_FIRST && music <= MUSIC_SILENT_LAST) {
        SoundSystem_PlayMusic(sys, (int) music, 0);
        return;
    }
    SoundSystem_PlayMusic(sys, (int) music, 0x7f);
    if (music >= MUSIC_HOURLY_FIRST && music <= MUSIC_HOURLY_LAST) {
        sys->arrange_due = 1;
    }
}
CLEAN_AS(func_020f1c6c, SoundSystem_ChangeMusic)

/* func_020f1d3c: the next number of the linear congruential generator, its high 16 bits, or
 * those scaled to 0..range-1 (0: not scaled). */
unsigned int SoundSystem_Random(SoundSystem *sys, unsigned int range)
{
    sys->random = sys->random_add + sys->random_mul * sys->random;
    u32 high = sys->random >> 16;
    if (range == 0) {
        return high;
    }
    return ((high * range) >> 16) & 0xffff;
}
CLEAN_AS(func_020f1d3c, SoundSystem_Random)

/* func_020f1d84: sequence archive `seq_arc` loaded into the sound heap; whether it was. */
int SoundSystem_LoadSeqArc(SoundSystem *sys, int seq_arc)
{
    (void) sys;
    return func_0210e198(seq_arc, Sound_GetHeap());
}
CLEAN_AS(func_020f1d84, SoundSystem_LoadSeqArc)

/* func_020f1da4: voice sample `number` (seq_arc * 1000 + index) started at `volume` and with
 * its tracks 0-3 at `pitch`. Voices of kinds 3 and 4 are pitched 400 lower and 600 higher, and
 * louder by 1.38 and 1.23 (in doubles, cut to 8 bits, at most 0x7f). The volume and pitch are
 * set only when the voice's handle has a player. */
void SoundSystem_PlayVoice(SoundSystem *sys, int number, int volume, int pitch)
{
    switch (sys->voice_type) {
        case 3:
            pitch -= 400;
            volume = func_0213460c(_dmul(_dfltu(volume), 1.38)) & 0xff;
            if (volume > 0x7f) {
                volume = 0x7f;
            }
            break;
        case 4:
            pitch += 600;
            volume = func_0213460c(_dmul(_dfltu(volume), 1.23)) & 0xff;
            if (volume > 0x7f) {
                volume = 0x7f;
            }
            break;
        default:
            break;
    }

    start_number(number, &sys->voice);
    if (sys->voice.player != NULL) {
        NNS_SndPlayerSetVolume(&sys->voice, volume);
        NNS_SndPlayerSetTrackPitch(&sys->voice, 0xf, pitch);
    }
}
CLEAN_AS(func_020f1da4, SoundSystem_PlayVoice)

/* func_020f1ecc */
void SoundSystem_SetVoiceType(SoundSystem *sys, int type)
{
    sys->voice_type = type;
}
CLEAN_AS(func_020f1ecc, SoundSystem_SetVoiceType)

/* func_020f1ed4: sound `number` (seq_arc * 1000 + index) stopped wherever it plays, over
 * `fade_frames`. */
void SoundSystem_StopSequence(void *sys, int number, int fade_frames)
{
    (void) sys;
    NNS_SndPlayerStopSeqBySeqArcIdx(number / 1000, number % 1000, fade_frames);
}
CLEAN_AS(func_020f1ed4, SoundSystem_StopSequence)

/* The sound played silent by SoundSystem_PlayOnEffect. */
#define SOUND_SILENT 0x862

/* func_020f1f24: sound `number` started on the effects' handle (silent for 0x862) and panned
 * if it is one of the panned effects. */
void SoundSystem_PlayOnEffect(SoundSystem *sys, int number)
{
    start_number(number, &sys->effect);
    if (number == SOUND_SILENT) {
        NNS_SndPlayerSetVolume(&sys->effect, 0);
    }
    SoundSystem_ApplyPan(sys, 1);
}
CLEAN_AS(func_020f1f24, SoundSystem_PlayOnEffect)

/* func_020f1fb4: sound effect `number` (seq_arc * 1000 + index) played, unless effects are
 * muted. Some play on the effects' handle and 0x861 on the second one, each then panned on
 * all its tracks with the other handle; the rest play on the default handle, 1 and 2 also
 * holding back the scene's frame update for 15 frames. */
void SoundSystem_PlayEffect(SoundSystem *sys, int number)
{
    if (sys->muted) {
        return;
    }

    switch (number) {
        case 3:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 21:
        case 25:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 0x85f:
        case 0x865:
        case 0x866:
        case 0x867:
        case 0x868:
        case 0x869:
        case 0x86a:
        case 0x86b:
        case 0x86c:
        case 0x86d:
        case 0x86e:
        case 0x87f:
        case 0x880:
        case 0x881:
        case 0x882:
            start_number(number, &sys->effect);
            SoundSystem_ApplyPan(sys, 0);
            break;
        case 0x861:
            start_number(number, &sys->effect_b);
            SoundSystem_ApplyPan(sys, 0);
            break;
        case 1:
        case 2:
            sys->delay = 15;
            start_number_default(number);
            break;
        default:
            start_number_default(number);
            break;
    }
}
CLEAN_AS(func_020f1fb4, SoundSystem_PlayEffect)

/* func_020f2338 */
void SoundSystem_StopOutputEffect(void *sys)
{
    (void) sys;
    NNS_SndCaptureStopEffect();
}
CLEAN_AS(func_020f2338, SoundSystem_StopOutputEffect)

/* func_020f2344 */
void SoundSystem_StartOutputEffect(SoundSystem *sys)
{
    Sound_StartOutputEffect(sys->output_effect);
}
CLEAN_AS(func_020f2344, SoundSystem_StartOutputEffect)

/* func_020f2354: the output effect kept and changed to. */
void SoundSystem_ChangeOutputEffect(SoundSystem *sys, int effect)
{
    sys->output_effect = effect;
    NNS_SndCaptureChangeOutputEffect(sys->output_effect);
}
CLEAN_AS(func_020f2354, SoundSystem_ChangeOutputEffect)

/* func_020f2368 */
void SoundSystem_MasterVolumeFull(void)
{
    func_0210ab38(0x7f);
}
CLEAN_AS(func_020f2368, SoundSystem_MasterVolumeFull)

/* func_020f2378 */
void SoundSystem_MasterVolumeOff(void *sys)
{
    (void) sys;
    func_0210ab38(0);
}
CLEAN_AS(func_020f2378, SoundSystem_MasterVolumeOff)

/* func_020f2388: the sound's work of a frame. */
void SoundSystem_Frame(SoundSystem *sys)
{
    Sound_Main();
    SoundSystem_UpdateNothing(sys);
    SoundSystem_UpdateCrossFade(sys);
    SoundSystem_UpdateVolumes(sys);
}
CLEAN_AS(func_020f2388, SoundSystem_Frame)

/* The scenes' own sound heap, made at the start of the memory given to the sound. */
#define SCENE_HEAP_SIZE 0x339c

/* func_020f23b4: the sound started in `size` bytes at `memory`: the scenes' heap first, the
 * sound library (Sound_Init) in the rest, with the archive at `archive_path`. Then the sound
 * capture's thread, output effect 1, the master volume at full, the streams, group 0 of the
 * archive and the handles; the rest of the state cleared. The game stops when the scenes'
 * heap cannot be made.
 * QUIRK: the original also stops when the heap's pointer, just cleared, is not NULL. */
void SoundSystem_Init(SoundSystem *sys, u8 *memory, u32 size, const void *archive_path)
{
    sys->scene_heap = NULL;
    sys->scene_heap = NNS_SndHeapCreate(memory, SCENE_HEAP_SIZE);
    if (sys->scene_heap == NULL) {
        OS_Terminate();
    }
    Sound_Init(memory + SCENE_HEAP_SIZE, size - SCENE_HEAP_SIZE, archive_path, NULL);
    NNS_SndCaptureCreateThread(CARD_GetThreadPriority() - 1);
    sys->output_effect = 1;
    SoundSystem_StartOutputEffect(sys);
    func_0210ab38(0x7f);
    func_0210fe08(10, Sound_GetHeap());
    func_0210fbf8(&sys->stream);
    Sound_LoadGroup(0);
    Sound_InitHandle(&sys->voice);
    Sound_InitHandle(&sys->effect);
    Sound_InitHandle(&sys->music);
    Sound_InitHandle(&sys->effect_b);
    sys->owner = NULL;
    sys->tracks_in = 0;
    sys->stream_length = 0;
    sys->cross_delay = -1;
    sys->tracks_out = 0;
    sys->pan = 0;
    sys->unk_71 = 0;
}
CLEAN_AS(func_020f23b4, SoundSystem_Init)

/* func_020f24bc: the sound system's constructor: the random generator seeded from the tick
 * count (its low 32 bits), with multiplier 0x5d588b65 and increment 0x269ec3. */
SoundSystem *SoundSystem_Construct(SoundSystem *sys)
{
    sys->random = (u32) OS_GetTick();
    sys->random_mul = 0x5d588b65;
    sys->random_add = 0x269ec3;
    sys->muted = 0;
    sys->lowered = 0;
    sys->unk_62 = 0;
    return sys;
}
CLEAN_AS(func_020f24bc, SoundSystem_Construct)
