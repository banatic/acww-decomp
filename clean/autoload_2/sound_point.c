/* Point sounds and their list (sound_point.h). */
#include "sound_point.h"

#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "sound_system.h"

static_assert(offsetof(SoundPoint, handle) == 0x08, "SoundPoint.handle");
static_assert(offsetof(SoundPoint, pos) == 0x0c, "SoundPoint.pos");
static_assert(offsetof(SoundPoint, number) == 0x18, "SoundPoint.number");
static_assert(offsetof(SoundPoint, asked) == 0x1b, "SoundPoint.asked");
static_assert(offsetof(SoundPointList, handle) == 0x0c, "SoundPointList.handle");

/* What these functions read of a sequence player. */
typedef struct PointSeqPlayer {
    u8 unk_00[0x38];
    u16 seq_no; /* 0x38: the music's number when it plays the music */
    u16 index;  /* 0x3a: compared with a point sound's index */
} PointSeqPlayer;

extern SoundSystem data_021fd1bc;
/* The list in use. */
extern SoundPointList *data_021fd234;
/* The tracks the music's pan is given to: 0-3 (0x000f). */
extern const u16 data_0213e858;

extern void NNS_FndInitList(SoundList *list, u16 offset);
extern void NNS_SndHandleReleaseSeq(SoundHandle *handle);
extern void NNS_SndPlayerSetVolume(SoundHandle *handle, int volume);
extern int NNS_SndPlayerWriteVariable(SoundHandle *handle, int index, short value);
extern void NNS_SndPlayerStopSeqBySeqArcIdx(int seq_arc, int index, int fade_frames);
/* The pan of the tracks in `track_mask`. */
extern void func_0210b634(SoundHandle *handle, u16 track_mask, int pan);
/* How far `pos` is from the listener, in whole units (`mode` 0: in all three axes). */
extern int func_020f5e50(const Vec3 *pos, int mode);
/* The volume a sound has at a distance. */
extern int func_020f5e24(int distance);
/* The pan a sound at `pos` has (`mode` 0: from X). */
extern int func_020f5c64(const Vec3 *pos, int mode);

/* The sequence archive point sounds start from, whatever their number says. */
#define POINT_SEQ_ARC 1
/* The number played at once rather than put in the list (SoundPoint_PlayAt). */
#define POINT_NUMBER_AT_ONCE 0x4ef
/* SoundPoint_PlayAtB puts the numbers between these (excluded) in the list, to play out. */
#define POINT_QUEUED_ABOVE 0x3e9
#define POINT_QUEUED_BELOW 0x430
/* The music's volume SoundPoint_UpdateMusicVolume keeps at least. */
#define POINT_MUSIC_VOLUME_MIN 0x28
/* With scene kind 10, a flush stops sound 1263 (sequence archive 1, index 0x107) unless the
 * music is one of the silent ones. */
#define POINT_SCENE_KIND_STOPS 10
#define POINT_STOPPED_SEQ_ARC 1
#define POINT_STOPPED_INDEX 0x107

static SoundPoint *first_of(SoundPointList *list)
{
    return (SoundPoint *) (uintptr_t) SoundList_First(&list->list);
}

static SoundPoint *next_of(SoundPointList *list, SoundPoint *point)
{
    return SoundList_Next(&list->list, point);
}

/* func_020f4c70: sound `number`'s index started from sequence archive 1 on the list's own
 * handle, at the volume and pan of `pos`.
 * QUIRK: the archive is 1 whatever the number's thousands say. */
void SoundPointList_StartSeq(SoundPointList *list, int number, const Vec3 *pos)
{
    int volume;
    int pan;

    Sound_StartSeqArc((u16) (number % 1000), POINT_SEQ_ARC, &list->handle);
    volume = func_020f5e24(func_020f5e50(pos, 0));
    pan = func_020f5c64(pos, 0);
    NNS_SndPlayerSetVolume(&list->handle, volume);
    func_0210b634(&list->handle, 0xff, pan);
}
CLEAN_AS(func_020f4c70, SoundPointList_StartSeq)

/* func_020f4d00: `point` taken out of the list. The list is walked to its end, each node
 * compared with `point`; the walk goes on from the point once removed. Returns 0. */
unsigned int SoundPointList_Remove(SoundPointList *list, SoundPoint *point)
{
    SoundPoint *node = first_of(list);

    while (node != NULL) {
        if (node == point) {
            SoundList_Remove(&list->list, point);
        }
        node = next_of(list, node);
    }
    return 0;
}
CLEAN_AS(func_020f4d00, SoundPointList_Remove)

/* func_020f4d4c: the frame's flush. The points done (SoundPoint_IsDone) are stopped and taken
 * out; of those left, all but the last two are stopped and the last two are started (or
 * followed). Then no point counts as asked for. With scene kind 10, sound 1263 is stopped over
 * 5 frames unless the music is a silent one (0xb0 to 0xf5).
 * REQUIRES: a scene in the sound system and, with kind 10, a player on the music's handle (the
 * ROM reads through both without a check). */
void SoundPointList_Flush(SoundPointList *list)
{
    SoundPoint *point;
    int count;

    for (point = first_of(list); point != NULL; point = next_of(list, point)) {
        if (SoundPoint_IsDone(point)) {
            SoundPoint_Stop(point);
            SoundList_Remove(&list->list, point);
        }
    }

    count = list->list.count;
    if (count == 1) {
        SoundPoint_Start((SoundPoint *) (uintptr_t) SoundList_Last(&list->list));
    } else if (count >= 2) {
        if (count > 2) {
            point = first_of(list);
            for (int i = 0; i < count - 2; i++) {
                SoundPoint_Stop(point);
                point = next_of(list, point);
            }
        }
        SoundPoint *last = (SoundPoint *) (uintptr_t) SoundList_Last(&list->list);
        SoundPoint_Start(last);
        SoundPoint_Start(SoundList_Prev(&list->list, last));
    }

    for (point = first_of(list); point != NULL; point = next_of(list, point)) {
        point->asked = 0;
    }

    if (data_021fd1bc.scene->kind != POINT_SCENE_KIND_STOPS) {
        return;
    }
    /* The ROM also checks the music handle's address (a global) for NULL, which never holds. */
    unsigned int music = ((const PointSeqPlayer *) data_021fd1bc.music.player)->seq_no;
    if (music >= MUSIC_SILENT_FIRST && music <= MUSIC_SILENT_LAST) {
        return;
    }
    NNS_SndPlayerStopSeqBySeqArcIdx(POINT_STOPPED_SEQ_ARC, POINT_STOPPED_INDEX, 5);
}
CLEAN_AS(func_020f4d4c, SoundPointList_Flush)

/* func_020f4eec: `point` appended to the list unless it is in it already. */
void SoundPointList_Add(SoundPointList *list, SoundPoint *point)
{
    for (SoundPoint *node = first_of(list); node != NULL; node = next_of(list, node)) {
        if (node == point) {
            return;
        }
    }
    SoundList_Append(&list->list, point);
}
CLEAN_AS(func_020f4eec, SoundPointList_Add)

/* func_020f4f44: an empty list (points linked at their start) and an empty handle. */
void SoundPointList_Init(SoundPointList *list)
{
    NNS_FndInitList(&list->list, 0);
    Sound_InitHandle(&list->handle);
}
CLEAN_AS(func_020f4f44, SoundPointList_Init)

/* func_020f4f64: the list's handle released. */
SoundPointList *SoundPointList_Release(SoundPointList *list)
{
    NNS_SndHandleReleaseSeq(&list->handle);
    return list;
}
CLEAN_AS(func_020f4f64, SoundPointList_Release)

/* func_020f4f80: the point taken out of the list in use, stopped over 5 frames and its handle
 * released. */
void SoundPoint_Release(SoundPoint *point)
{
    SoundPointList_Remove(data_021fd234, point);
    Sound_StopSequence(&point->handle, 5);
    NNS_SndHandleReleaseSeq(&point->handle);
}
CLEAN_AS(func_020f4f80, SoundPoint_Release)

/* func_020f4fb8: while the music plays on its handle, its volume (at least 0x28) and pan set
 * from `pos`. */
void SoundPoint_UpdateMusicVolume(int unused, const Vec3 *pos)
{
    SoundHandle *music = &data_021fd1bc.music;
    int volume;
    int pan;

    (void) unused;
    if (music->player == NULL) {
        return;
    }
    volume = func_020f5e24(func_020f5e50(pos, 0));
    pan = func_020f5c64(pos, 0);
    if (volume < POINT_MUSIC_VOLUME_MIN) {
        volume = POINT_MUSIC_VOLUME_MIN;
    }
    NNS_SndPlayerSetVolume(music, volume);
    func_0210b634(music, data_0213e858, pan);
}
CLEAN_AS(func_020f4fb8, SoundPoint_UpdateMusicVolume)

/* func_020f503c: `value` written to variable 0 of the point's player. */
void SoundPoint_SetVariable(SoundPoint *point, short value)
{
    NNS_SndPlayerWriteVariable(&point->handle, 0, value);
}
CLEAN_AS(func_020f503c, SoundPoint_SetVariable)

/* func_020f5054: sound `number` asked for at `pos`. Number 0x4ef is started (or followed) at
 * once, the others are put in the list in use. Nothing while the sound system is muted. */
void SoundPoint_PlayAt(SoundPoint *point, int number, const Vec3 *pos)
{
    if (data_021fd1bc.muted) {
        return;
    }
    point->number = (u16) number;
    point->pos = *pos;
    point->play_out = 0;
    point->asked = 1;
    if (number == POINT_NUMBER_AT_ONCE) {
        SoundPoint_Start(point);
    } else {
        SoundPointList_Add(data_021fd234, point);
    }
}
CLEAN_AS(func_020f5054, SoundPoint_PlayAt)

/* func_020f50e4: the point's volume and pan set from its position. */
void SoundPoint_ApplyVolume(SoundPoint *point)
{
    int volume = func_020f5e24(func_020f5e50(&point->pos, 0));
    int pan = func_020f5c64(&point->pos, 0);

    NNS_SndPlayerSetVolume(&point->handle, volume);
    func_0210b634(&point->handle, 0xff, pan);
}
CLEAN_AS(func_020f50e4, SoundPoint_ApplyVolume)

/* func_020f5134: whether a flush drops the point: not asked for since the last flush, and
 * either nothing plays or it is not one to play out. */
int SoundPoint_IsDone(SoundPoint *point)
{
    if (point->asked != 0) {
        return 0;
    }
    return point->handle.player == NULL || point->play_out == 0;
}
CLEAN_AS(func_020f5134, SoundPoint_IsDone)

/* func_020f5178: what the point plays stopped, over 15 frames while the sound system is muted
 * and at once otherwise. */
void SoundPoint_Stop(SoundPoint *point)
{
    Sound_StopSequence(&point->handle, data_021fd1bc.muted != 0 ? 15 : 0);
}
CLEAN_AS(func_020f5178, SoundPoint_Stop)

/* func_020f51c4: the point's sound started from sequence archive 1, unless its player already
 * plays that index (one playing another is stopped over 5 frames first); then its volume and
 * pan are set.
 * QUIRK: the archive is 1 whatever the number's thousands say. */
void SoundPoint_Start(SoundPoint *point)
{
    const PointSeqPlayer *player = point->handle.player;
    int index = point->number % 1000;
    int start = 1;

    if (player != NULL) {
        start = player->index != index;
        if (start) {
            Sound_StopSequence(&point->handle, 5);
        }
    }
    if (start) {
        Sound_StartSeqArc((u16) (point->number % 1000), POINT_SEQ_ARC, &point->handle);
    }
    SoundPoint_ApplyVolume(point);
}
CLEAN_AS(func_020f51c4, SoundPoint_Start)

/* func_020f52a0: sound `number` asked for at `pos`, the other way. Numbers 0x3ea to 0x42f are
 * put in the list in use, to play out. The others are started at once on the list's own handle
 * after what the point plays is stopped; the point's own volume is then set.
 * Nothing while the sound system is muted. */
void SoundPoint_PlayAtB(SoundPoint *point, int number, const Vec3 *pos)
{
    if (data_021fd1bc.muted != 0) {
        return;
    }
    point->pos = *pos;
    if (number > POINT_QUEUED_ABOVE && number < POINT_QUEUED_BELOW) {
        point->number = (u16) number;
        point->play_out = 1;
        point->asked = 1;
        SoundPointList_Add(data_021fd234, point);
        return;
    }
    SoundPoint_Stop(point);
    SoundPointList_StartSeq(data_021fd234, (u16) number, &point->pos);
    SoundPoint_ApplyVolume(point);
}
CLEAN_AS(func_020f52a0, SoundPoint_PlayAtB)

/* func_020f5360: the point set up, and `list` made the list in use. */
void SoundPoint_Init(SoundPoint *point, SoundPointList *list)
{
    data_021fd234 = list;
    point->number = 0;
    point->asked = 0;
    point->play_out = 0;
    SoundLink_Clear(&point->link);
    Sound_InitHandle(&point->handle);
}
CLEAN_AS(func_020f5360, SoundPoint_Init)
