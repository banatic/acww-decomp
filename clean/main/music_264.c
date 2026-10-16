/* The member at 0x264 of the field's sound object and its three parts (music_264.h). */
#include "music_264.h"

#include "autoload_2/heap.h"
#include "calendar.h"
#include "clean.h"
#include "date_time.h"
#include "main/session.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_music.h"

static_assert(sizeof(MusicClock) == 0x18, "music clock size");
static_assert(sizeof(HourMusic) == 0x14, "hour music size");
static_assert(offsetof(HourMusic, keep_music) == 0x0f, "hour music keep");
static_assert(sizeof(Music27c) == 0x0c, "music 27c size");
static_assert(sizeof(EventMusic) == 0x18, "event music size");
static_assert(offsetof(EventMusic, active) == 0x15, "event music active");
static_assert(offsetof(Music264, event) == 0x24, "music 264 event");
static_assert(sizeof(Music264) == 0x3c, "music 264 size");

/* The vtables of the member and of its parts. */
extern const u32 data_020da304[];
extern const u32 data_020da2e4[];
extern const u32 data_020da324[];

/* The part at 0x04's functions that this file does not hold: its construct, destruct, create,
 * delete, frame, reset and scene start. */
extern void func_020372f8(HourMusic *self, Obj021c526c *owner);
extern void func_020372ec(HourMusic *self);
extern void func_020372bc(HourMusic *self);
extern void func_020372b4(HourMusic *self);
extern void func_02037298(HourMusic *self);
extern void func_02037278(HourMusic *self);
extern void func_02037260(HourMusic *self);

/* The current scene is 0; the current scene is 0x31. */
extern int func_020b6660(void);
extern int func_020b6640(void);

/* The clock (the object's member at 0x24c): whether it reads from h1:m1:s1 (included) to
 * h2:m2:s2 (excluded), across midnight when the second is earlier; the same with minutes and
 * seconds only; whether its date and time of day are *date (day, month) and *time (minute,
 * hour); whether its year changed since the frame before. */
extern u32 func_0203736c(void *clock, u32 h1, u32 m1, u32 s1, u32 h2, u32 m2, u32 s2);
extern int func_020373c8(void *clock, u32 m1, u32 s1, u32 m2, u32 s2);
extern int func_02037404(void *clock, const u16 *date, const u16 *time);
extern int func_0203734c(void *clock);

/* The number of an event (data_020db6dc, set to 0x12 by func_02041644), and whether an event is
 * on at a date (3 for event 0x12 in the part func_02041644 waits for). */
extern u32 func_02041614(void);
extern int func_0203fc78(int event, const DateTime *when, int arg);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
/* The session. */
extern NetSession *data_020ccf94;
/* Whether a villager part has the state func_0209ac04 looks for. */
extern int func_0209ac04(int part);
/* Two bytes, data_021f4b18 and data_021f4b1c. */
extern u8 func_020b22b8(void);
extern u8 func_020b22dc(void);
/* Clears `size` bytes. */
extern void *func_02137550(void *dst, u32 size);

/* The dates (day, month) December 31st and January 1st, and the time 23:59 (minute, hour). */
extern const u16 data_020da24c;
extern const u16 data_020da248;
extern const u16 data_020da250;
/* The music of each hour. */
extern const u16 data_020c9f28[24];

/* The priorities of the requests made here. */
#define EVENT_MUSIC_FADE_PRIORITY 30
#define EVENT_MUSIC_PRIORITY_1F 0x1f
#define EVENT_MUSIC_PRIORITY_20 0x20
#define EVENT_MUSIC_PRIORITY_21 0x21
#define EVENT_MUSIC_PRIORITY_22 0x22
#define EVENT_MUSIC_PRIORITY_23 0x23
#define HOUR_MUSIC_FADE_PRIORITY 0x1b
#define HOUR_MUSIC_PRIORITY 0x24
/* The word of the fading requests. */
#define MUSIC_264_FADE_VALUE 0xc8

/* The events whose musics are played. */
#define EVENT_0F 0x0f
#define EVENT_12 0x12
#define EVENT_13 0x13

/* ---- The member */

/* func_02036894: whether the scene's end leaves the musics, told to the three parts.
 * QUIRK: `keep` is a flag passed as a pointer (NULL or 1); each part keeps its low byte. */
void Music264_SetKeep(Music264 *self, void *keep)
{
    int value = (int) (uintptr_t) keep;

    HourMusic_SetKeep(&self->hour, value);
    Music27c_SetKeep(&self->part_18, value);
    EventMusic_SetKeep(&self->event, value);
}
CLEAN_AS(func_02036894, Music264_SetKeep)

/* func_020368c0: the scene's end (Music_OnSceneEnd), in scenes 0 and 0x31 only, told to the
 * parts from the last to the first. */
void Music264_OnSceneEnd(Music264 *self)
{
    if (func_020b6660() == 0 && func_020b6640() == 0) {
        return;
    }
    EventMusic_OnSceneEnd(&self->event);
    Music27c_OnSceneEnd(&self->part_18);
    HourMusic_OnSceneEnd(&self->hour);
}
CLEAN_AS(func_020368c0, Music264_OnSceneEnd)

/* func_020368f0: the scene's start (Music_OnSceneStart), in scenes 0 and 0x31 only. */
void Music264_OnSceneStart(Music264 *self)
{
    if (func_020b6660() != 0 || func_020b6640() != 0) {
        func_02037260(&self->hour);
        Music27c_OnSceneStart(&self->part_18);
        EventMusic_OnSceneStart(&self->event);
    }
}
CLEAN_AS(func_020368f0, Music264_OnSceneStart)

/* func_02036920: every part reset (Music_Reset). */
void Music264_Reset(Music264 *self)
{
    func_02037278(&self->hour);
    Music27c_Reset(&self->part_18);
    EventMusic_Reset(&self->event);
}
CLEAN_AS(func_02036920, Music264_Reset)

/* func_02036940: the frame. */
void Music264_Execute(Music264 *self)
{
    func_02037298(&self->hour);
    Music27c_Execute(&self->part_18);
    EventMusic_Execute(&self->event);
}
CLEAN_AS(func_02036940, Music264_Execute)

/* func_02036960: the deletion, from the last part to the first. */
void Music264_Delete(Music264 *self)
{
    EventMusic_Delete(&self->event);
    Music27c_Delete(&self->part_18);
    func_020372b4(&self->hour);
}
CLEAN_AS(func_02036960, Music264_Delete)

/* func_02036980: the creation. */
void Music264_Create(Music264 *self)
{
    func_020372bc(&self->hour);
    Music27c_Create(&self->part_18);
    EventMusic_Create(&self->event);
}
CLEAN_AS(func_02036980, Music264_Create)

/* func_020369a0: the destructor that also frees it (vtable slot 1). */
Music264 *Music264_DestructDelete(Music264 *self)
{
    self->vtable = data_020da304;
    EventMusic_Destruct(&self->event);
    Music27c_Destruct(&self->part_18);
    func_020372ec(&self->hour);
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_020369a0, Music264_DestructDelete)

/* func_020369d0: its destructor (vtable slot 0), the parts from the last to the first. */
Music264 *Music264_Destruct(Music264 *self)
{
    self->vtable = data_020da304;
    EventMusic_Destruct(&self->event);
    Music27c_Destruct(&self->part_18);
    func_020372ec(&self->hour);
    return self;
}
CLEAN_AS(func_020369d0, Music264_Destruct)

/* func_020369fc: its constructor, each part told the owner. */
Music264 *Music264_Construct(Music264 *self, Obj021c526c *owner)
{
    self->vtable = data_020da304;
    func_020372f8(&self->hour, owner);
    Music27c_Construct(&self->part_18, owner);
    EventMusic_Construct(&self->event, owner);
    return self;
}
CLEAN_AS(func_020369fc, Music264_Construct)

/* ---- The part at 0x24: the musics of the events */

/* func_02036a30: the year change noted (it stays noted until EventMusic_UpdateEvent13 or the
 * reset clears it); whether it is noted. */
int EventMusic_NoteYearChange(EventMusic *self)
{
    int changed = func_0203734c(SceneMusic_Clock());
    int noted = (self->year_changed | changed) != 0;

    self->year_changed = (u8) noted;
    return noted;
}
CLEAN_AS(func_02036a30, EventMusic_NoteYearChange)

/* func_02036a5c: the request of priority 30 dropped. */
void EventMusic_DropFade(EventMusic *self)
{
    if (self->fade_added != 0) {
        Music_DropPriority(EVENT_MUSIC_FADE_PRIORITY);
        self->fade_added = 0;
    }
}
CLEAN_AS(func_02036a5c, EventMusic_DropFade)

/* func_02036a78: a request of priority 30 with word `value` added, once. */
void EventMusic_AddFade(EventMusic *self, int value)
{
    if (self->fade_added == 0) {
        Music_AddValue(EVENT_MUSIC_FADE_PRIORITY, value, 0);
        self->fade_added = 1;
    }
}
CLEAN_AS(func_02036a78, EventMusic_AddFade)

/* func_02036a94: the music of priority 0x23 dropped. */
void EventMusic_Stop23(EventMusic *self)
{
    if (self->music_23 != MUSIC_NONE) {
        Music_DropMusic(self->music_23);
        self->music_23 = MUSIC_NONE;
    }
}
CLEAN_AS(func_02036a94, EventMusic_Stop23)

/* func_02036ab4: the music of priority 0x22 dropped. */
void EventMusic_Stop22(EventMusic *self)
{
    if (self->music_22 != MUSIC_NONE) {
        Music_DropMusic(self->music_22);
        self->music_22 = MUSIC_NONE;
    }
}
CLEAN_AS(func_02036ab4, EventMusic_Stop22)

/* func_02036ad4: the music of priority 0x21 dropped. */
void EventMusic_Stop21(EventMusic *self)
{
    if (self->music_21 != MUSIC_NONE) {
        Music_DropMusic(self->music_21);
        self->music_21 = MUSIC_NONE;
    }
}
CLEAN_AS(func_02036ad4, EventMusic_Stop21)

/* func_02036af4: the music of priority 0x20 dropped. */
void EventMusic_Stop20(EventMusic *self)
{
    if (self->music_20 != MUSIC_NONE) {
        Music_DropMusic(self->music_20);
        self->music_20 = MUSIC_NONE;
    }
}
CLEAN_AS(func_02036af4, EventMusic_Stop20)

/* func_02036b14: the music of priority 0x1f dropped (the queue told with its flag 1). */
void EventMusic_Stop1f(EventMusic *self)
{
    if (self->music_1f != MUSIC_NONE) {
        Music_DropMusicFlagged(self->music_1f);
        self->music_1f = MUSIC_NONE;
    }
}
CLEAN_AS(func_02036b14, EventMusic_Stop1f)

/* func_02036b34: `music` asked for at priority 0x23. */
void EventMusic_Start23(EventMusic *self, int music)
{
    Music_Add(EVENT_MUSIC_PRIORITY_23, music, 0x7f, 0);
    self->music_23 = (u16) music;
}
CLEAN_AS(func_02036b34, EventMusic_Start23)

/* func_02036b50: `music` asked for at priority 0x22. */
void EventMusic_Start22(EventMusic *self, int music)
{
    Music_Add(EVENT_MUSIC_PRIORITY_22, music, 0x7f, 0);
    self->music_22 = (u16) music;
}
CLEAN_AS(func_02036b50, EventMusic_Start22)

/* func_02036b6c: `music` asked for at priority 0x21. */
void EventMusic_Start21(EventMusic *self, u16 music)
{
    Music_Add(EVENT_MUSIC_PRIORITY_21, music, 0x7f, 0);
    self->music_21 = music;
}
CLEAN_AS(func_02036b6c, EventMusic_Start21)

/* func_02036b88: `music` asked for at priority 0x20. */
void EventMusic_Start20(EventMusic *self, int music)
{
    Music_Add(EVENT_MUSIC_PRIORITY_20, music, 0x7f, 0);
    self->music_20 = (u16) music;
}
CLEAN_AS(func_02036b88, EventMusic_Start20)

/* func_02036ba4: `music` asked for at priority 0x1f, dropped as soon as it is not at the
 * head. */
void EventMusic_Start1f(EventMusic *self, u16 music)
{
    Music_AddHeadOnly(EVENT_MUSIC_PRIORITY_1F, music);
    self->music_1f = music;
}
CLEAN_AS(func_02036ba4, EventMusic_Start1f)

/* func_02036bbc: while event 0xf is on, music 0x30 at priority 0x23. */
void EventMusic_UpdateEvent0f(EventMusic *self, int on)
{
    if (on != 0) {
        if (self->music_23 != 0x30) {
            EventMusic_Stop23(self);
            EventMusic_Start23(self, 0x30);
        }
    } else {
        EventMusic_Stop23(self);
    }
}
CLEAN_AS(func_02036bbc, EventMusic_UpdateEvent0f)

/* func_02036be4: while event 0x12 is on, from 23:00 to midnight musics 0x31 (to 23:30), 0x32
 * (to 23:50), 0x33 (to 23:55) and 0x34 at priority 0x22, and in the last ten seconds before
 * each change (from 23:58:50 before midnight) a request of priority 30 with word 0xc8. Every
 * reading of the clock is made before any of them is used. */
void EventMusic_UpdateEvent12(EventMusic *self, int on)
{
    void *clock;
    int part1, part2, part3, part4;
    int end1, end2, end3, end4;
    int music = MUSIC_NONE;

    if (on == 0) {
        EventMusic_Stop22(self);
        EventMusic_DropFade(self);
        return;
    }

    clock = SceneMusic_Clock();
    part1 = func_0203736c(clock, 23, 0, 0, 23, 30, 0) != 0;
    part2 = func_0203736c(clock, 23, 30, 0, 23, 50, 0) != 0;
    part3 = func_0203736c(clock, 23, 50, 0, 23, 55, 0) != 0;
    part4 = func_0203736c(clock, 23, 55, 0, 0, 0, 0) != 0;
    if (part1) {
        music = 0x31;
    } else if (part2) {
        music = 0x32;
    } else if (part3) {
        music = 0x33;
    } else if (part4) {
        music = 0x34;
    }

    if (music != MUSIC_NONE) {
        if (self->music_22 != music) {
            EventMusic_Stop22(self);
            EventMusic_Start22(self, music);
        }
    } else {
        EventMusic_Stop22(self);
    }

    end1 = func_0203736c(clock, 23, 29, 50, 23, 30, 0) != 0;
    end2 = func_0203736c(clock, 23, 49, 50, 23, 50, 0) != 0;
    end3 = func_0203736c(clock, 23, 54, 50, 23, 55, 0) != 0;
    end4 = func_0203736c(clock, 23, 58, 50, 0, 0, 0) != 0;
    if (end1 || end2 || end3 || end4) {
        EventMusic_AddFade(self, MUSIC_264_FADE_VALUE);
    } else {
        EventMusic_DropFade(self);
    }
}
CLEAN_AS(func_02036be4, EventMusic_UpdateEvent12)

/* func_02036d24: while event 0x13 is on, before 2:00 music 0x36 at priority 0x20, with music
 * 0x35 at priority 0x1f (held only at the head) when the year has just changed; from 2:00
 * music 0x37 at priority 0x21. */
void EventMusic_UpdateEvent13(EventMusic *self, int on)
{
    void *clock;
    int early, late;

    if (on == 0) {
        EventMusic_Stop1f(self);
        EventMusic_Stop20(self);
        EventMusic_Stop21(self);
        return;
    }

    clock = SceneMusic_Clock();
    early = func_0203736c(clock, 0, 0, 0, 2, 0, 0) != 0;
    late = func_0203736c(clock, 2, 0, 0, 0, 0, 0) != 0;
    if (early) {
        if (self->year_changed != 0) {
            if (self->music_1f != 0x35) {
                EventMusic_Stop1f(self);
                EventMusic_Start1f(self, 0x35);
            }
            self->year_changed = 0;
        }
        if (self->music_20 != 0x36) {
            EventMusic_Stop20(self);
            EventMusic_Start20(self, 0x36);
        }
    } else {
        EventMusic_Stop1f(self);
        EventMusic_Stop20(self);
    }
    if (late) {
        if (self->music_21 != 0x37) {
            EventMusic_Stop21(self);
            EventMusic_Start21(self, 0x37);
        }
    } else {
        EventMusic_Stop21(self);
    }
}
CLEAN_AS(func_02036d24, EventMusic_UpdateEvent13)

/* func_02036ddc: which events are on today, each asked with its own copy of the date, and their
 * musics updated: event 0x13 when it is on; event 0x12 when it is data_020db6dc or answers 3;
 * event 0xf, while linked, when it is on, else when it is data_020db6dc. */
void EventMusic_Update(EventMusic *self)
{
    u32 current = func_02041614();
    DateTime now = {0};
    DateTime copy;
    int event13;
    int event12 = 1;
    int event0f;

    DateTime_Now(&now);

    MI_CpuCopy8(&now, &copy, sizeof(copy));
    event13 = func_0203fc78(EVENT_13, &copy, 0) != 0;

    if (current != EVENT_12) {
        MI_CpuCopy8(&now, &copy, sizeof(copy));
        if (func_0203fc78(EVENT_12, &copy, 0) != 3) {
            event12 = 0;
        }
    }

    if (Session_IsLinked(data_020ccf94) != 0) {
        MI_CpuCopy8(&now, &copy, sizeof(copy));
        event0f = func_0203fc78(EVENT_0F, &copy, 0) != 0;
    } else {
        event0f = current == EVENT_0F;
    }

    EventMusic_UpdateEvent13(self, event13);
    EventMusic_UpdateEvent12(self, event12);
    EventMusic_UpdateEvent0f(self, event0f);
}
CLEAN_AS(func_02036ddc, EventMusic_Update)

/* func_02036e8c: whether the scene's end leaves the musics. */
void EventMusic_SetKeep(EventMusic *self, int keep)
{
    self->keep_music = (u8) keep;
}
CLEAN_AS(func_02036e8c, EventMusic_SetKeep)

/* func_02036e90: the scene's end: unless they are kept, the musics and the request of priority
 * 30 dropped; 0. */
int EventMusic_OnSceneEnd(EventMusic *self)
{
    if (self->keep_music == 0) {
        EventMusic_Stop1f(self);
        EventMusic_Stop20(self);
        EventMusic_Stop21(self);
        EventMusic_Stop22(self);
        EventMusic_Stop23(self);
        EventMusic_DropFade(self);
    }
    self->active = 0;
    return 0;
}
CLEAN_AS(func_02036e90, EventMusic_OnSceneEnd)

/* func_02036ec8: the scene's start: active, and the musics updated. */
void EventMusic_OnSceneStart(EventMusic *self)
{
    self->active = 1;
    EventMusic_Update(self);
}
CLEAN_AS(func_02036ec8, EventMusic_OnSceneStart)

/* func_02036ed4: every music and the request of priority 30 dropped, and every mark cleared. */
void EventMusic_Reset(EventMusic *self)
{
    EventMusic_Stop1f(self);
    EventMusic_Stop20(self);
    EventMusic_Stop21(self);
    EventMusic_Stop22(self);
    EventMusic_Stop23(self);
    EventMusic_DropFade(self);
    self->year_changed = 0;
    self->keep_music = 0;
    self->active = 0;
}
CLEAN_AS(func_02036ed4, EventMusic_Reset)

/* func_02036f08: the frame: while active, the year change noted and the musics updated. */
void EventMusic_Execute(EventMusic *self)
{
    if (self->active != 0) {
        EventMusic_NoteYearChange(self);
        EventMusic_Update(self);
    }
}
CLEAN_AS(func_02036f08, EventMusic_Execute)

/* func_02036f24: the deletion: the reset. */
void EventMusic_Delete(EventMusic *self)
{
    EventMusic_Reset(self);
}
CLEAN_AS(func_02036f24, EventMusic_Delete)

/* func_02036f2c: the creation: no music, no mark. */
void EventMusic_Create(EventMusic *self)
{
    self->music_1f = MUSIC_NONE;
    self->music_20 = MUSIC_NONE;
    self->music_21 = MUSIC_NONE;
    self->music_22 = MUSIC_NONE;
    self->music_23 = MUSIC_NONE;
    self->fade_added = 0;
    self->year_changed = 0;
    self->keep_music = 0;
    self->active = 0;
}
CLEAN_AS(func_02036f2c, EventMusic_Create)

/* func_02036f48: the destructor that also frees it (vtable slot 1). */
EventMusic *EventMusic_DestructDelete(EventMusic *self)
{
    self->vtable = data_020da2e4;
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_02036f48, EventMusic_DestructDelete)

/* func_02036f60: its destructor (vtable slot 0). */
void EventMusic_Destruct(EventMusic *self)
{
    self->vtable = data_020da2e4;
}
CLEAN_AS(func_02036f60, EventMusic_Destruct)

/* func_02036f6c: its constructor: the owner kept, no music, no mark. */
void EventMusic_Construct(EventMusic *self, Obj021c526c *owner)
{
    self->vtable = data_020da2e4;
    self->owner = owner;
    EventMusic_Create(self);
}
CLEAN_AS(func_02036f6c, EventMusic_Construct)

/* ---- The part at 0x18 */

/* func_02036f94: the music asked for dropped. */
void Music27c_Stop(Music27c *self)
{
    if (self->music != MUSIC_NONE) {
        Music_DropMusic(self->music);
        self->music = MUSIC_NONE;
    }
}
CLEAN_AS(func_02036f94, Music27c_Stop)

/* func_02036fb4: `music` asked for at `priority` (full volume, with the byte 0x10 `flag`). */
void Music27c_Start(Music27c *self, int priority, u16 music, int flag)
{
    Music_Add(priority, music, 0x7f, flag);
    self->music = music;
}
CLEAN_AS(func_02036fb4, Music27c_Start)

/* func_02036fd0: whether the scene's end leaves the music. */
void Music27c_SetKeep(Music27c *self, int keep)
{
    self->keep_music = (u8) keep;
}
CLEAN_AS(func_02036fd0, Music27c_SetKeep)

/* func_02036fd4: the scene's end: unless it is kept, the music dropped. */
void Music27c_OnSceneEnd(Music27c *self)
{
    if (self->keep_music == 0) {
        Music27c_Stop(self);
    }
    self->active = 0;
}
CLEAN_AS(func_02036fd4, Music27c_OnSceneEnd)

/* func_02036fec: the scene's start: active, and when no music is asked for:
 * - with data_021f4b18 set, a request of priority 3 running out after 5 frames and music 0x45
 *   at priority 4 (byte 0x10 set);
 * - else with data_021f4b1c set, music 0x4a at priority 0x0d;
 * - else with a player's record: music 0x46 at priority 0x1c when the record has flag 0x23, or
 *   flag 1 with a villager part that func_0209ac04 refuses; else music 0x48 at priority 0x1d
 *   when it has flag 1.
 * QUIRK: flag 1 is tested again before music 0x48. */
void Music27c_OnSceneStart(Music27c *self)
{
    u8 *record;

    self->active = 1;
    if (self->music != MUSIC_NONE) {
        return;
    }

    record = PlayerRecords_Current();
    if (func_020b22b8() != 0) {
        Music_AddValue(3, 0, 5);
        Music27c_Start(self, 4, 0x45, 1);
        return;
    }
    if (func_020b22dc() != 0) {
        Music27c_Start(self, 0x0d, 0x4a, 0);
        return;
    }
    if (record == NULL) {
        return;
    }
    if (PlayerRecord_TestFlag(record, 0x23) == 0) {
        if (PlayerRecord_TestFlag(record, 1) == 0 || func_0209ac04((int) (uintptr_t) PlayerRecord_VillagerPart(record)) != 0) {
            if (PlayerRecord_TestFlag(record, 1) != 0) {
                Music27c_Start(self, 0x1d, 0x48, 0);
            }
            return;
        }
    }
    Music27c_Start(self, 0x1c, 0x46, 0);
}
CLEAN_AS(func_02036fec, Music27c_OnSceneStart)

/* func_0203709c: the music dropped and the marks cleared. */
void Music27c_Reset(Music27c *self)
{
    Music27c_Stop(self);
    self->keep_music = 0;
    self->active = 0;
}
CLEAN_AS(func_0203709c, Music27c_Reset)

/* func_020370b0: the frame: nothing. */
void Music27c_Execute(Music27c *self)
{
    (void) self;
}
CLEAN_AS(func_020370b0, Music27c_Execute)

/* func_020370b4: the deletion: the reset. */
void Music27c_Delete(Music27c *self)
{
    Music27c_Reset(self);
}
CLEAN_AS(func_020370b4, Music27c_Delete)

/* func_020370bc: the creation: no music, no mark. */
void Music27c_Create(Music27c *self)
{
    self->music = MUSIC_NONE;
    self->keep_music = 0;
    self->active = 0;
}
CLEAN_AS(func_020370bc, Music27c_Create)

/* func_020370cc: the destructor that also frees it (vtable slot 1). */
Music27c *Music27c_DestructDelete(Music27c *self)
{
    self->vtable = data_020da324;
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_020370cc, Music27c_DestructDelete)

/* func_020370e4: its destructor (vtable slot 0). */
void Music27c_Destruct(Music27c *self)
{
    self->vtable = data_020da324;
}
CLEAN_AS(func_020370e4, Music27c_Destruct)

/* func_020370f0: its constructor: the owner kept, no music, no mark. */
void Music27c_Construct(Music27c *self, Obj021c526c *owner)
{
    self->vtable = data_020da324;
    self->owner = owner;
    Music27c_Create(self);
}
CLEAN_AS(func_020370f0, Music27c_Construct)

/* ---- The part at 0x04: the music of the hour */

/* func_0203710c: from xx:59:50 to xx:00:16 a request of priority 0x1b with word 0xc8, except
 * while the clock reads December 31st 23:59 or January 1st 0:00. */
void HourMusic_UpdateFade(HourMusic *self)
{
    void *clock = SceneMusic_Clock();
    int fade = func_020373c8(clock, 59, 50, 0, 16);
    u16 dates[2];
    u16 times[2];

    dates[0] = data_020da24c;
    dates[1] = data_020da248;
    times[0] = data_020da250;
    func_02137550(&times[1], sizeof(times[1]));
    if (func_02037404(clock, &dates[0], &times[0]) != 0 || func_02037404(clock, &dates[1], &times[1]) != 0) {
        fade = 0;
    }
    if (fade != 0) {
        HourMusic_AddFade(self, MUSIC_264_FADE_VALUE);
    } else {
        HourMusic_DropFade(self);
    }
}
CLEAN_AS(func_0203710c, HourMusic_UpdateFade)

/* func_02037190: the request of priority 0x1b dropped. */
void HourMusic_DropFade(HourMusic *self)
{
    if (self->fade_added != 0) {
        Music_DropPriority(HOUR_MUSIC_FADE_PRIORITY);
        self->fade_added = 0;
    }
}
CLEAN_AS(func_02037190, HourMusic_DropFade)

/* func_020371ac: a request of priority 0x1b with word `value` added, once. */
void HourMusic_AddFade(HourMusic *self, int value)
{
    if (self->fade_added == 0) {
        Music_AddValue(HOUR_MUSIC_FADE_PRIORITY, value, 0);
        self->fade_added = 1;
    }
}
CLEAN_AS(func_020371ac, HourMusic_AddFade)

/* func_020371c8: when the clock's hour is not the one played, its music in place of the one
 * before. */
void HourMusic_UpdateHour(HourMusic *self)
{
    const MusicClock *clock = SceneMusic_Clock();
    u8 hour = clock->now.hour;

    if (hour != self->hour) {
        HourMusic_Stop(self);
        self->hour = hour;
        HourMusic_Start(self);
    }
}
CLEAN_AS(func_020371c8, HourMusic_UpdateHour)

/* func_020371f0: the music asked for dropped. */
void HourMusic_Stop(HourMusic *self)
{
    if (self->music != MUSIC_NONE) {
        Music_DropMusic(self->music);
        self->music = MUSIC_NONE;
    }
}
CLEAN_AS(func_020371f0, HourMusic_Stop)

/* func_02037210: the music of the hour asked for at priority 0x24.
 * REQUIRES: hour < 24 (it indexes the table unchecked; the game sets it from the clock). */
void HourMusic_Start(HourMusic *self)
{
    u16 music = data_020c9f28[self->hour];

    Music_Add(HOUR_MUSIC_PRIORITY, music, 0x7f, 0);
    self->music = music;
}
CLEAN_AS(func_02037210, HourMusic_Start)

/* func_02037238: whether the scene's end leaves the music. */
void HourMusic_SetKeep(HourMusic *self, int keep)
{
    self->keep_music = (u8) keep;
}
CLEAN_AS(func_02037238, HourMusic_SetKeep)

/* func_0203723c: the scene's end: unless it is kept, the music and the request of priority
 * 0x1b dropped and the hour forgotten; 0. */
int HourMusic_OnSceneEnd(HourMusic *self)
{
    if (self->keep_music == 0) {
        HourMusic_Stop(self);
        self->hour = HOUR_MUSIC_NO_HOUR;
        HourMusic_DropFade(self);
    }
    self->active = 0;
    return 0;
}
CLEAN_AS(func_0203723c, HourMusic_OnSceneEnd)
