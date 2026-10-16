/* The member at 0x264 of the field's sound object (music_queue.h, vtable data_020da304): three
 * parts that ask the music queue for musics of their own, told together of the object's
 * creation, frame, reset and deletion, and of the start and end of the scenes 0 and 0x31.
 *
 * - at 0x04 (vtable data_020da2c4, the object's 0x268): the music of the hour from the table
 *   data_020c9f28 at priority 0x24, and a request of priority 0x1b with word 0xc8 from xx:59:50
 *   to xx:00:16, except on December 31st at 23:59 and January 1st at 0:00;
 * - at 0x18 (vtable data_020da324, the object's 0x27c): one music at the scene's start, chosen
 *   from the bytes data_021f4b18 and data_021f4b1c and the flags 0x23 and 1 of the player's
 *   record;
 * - at 0x24 (vtable data_020da2e4, the object's 0x288): the musics of events 0x12, 0x13 and
 *   0xf, by the clock (the object's member at 0x24c).
 *
 * Each part has a byte that makes the scene's end leave its music (set by Music2d0_Start and
 * cleared by Music2d0_Finish through Music264_SetKeep) and a byte set between a scene's start
 * and its end. */
#ifndef CLEAN_MAIN_MUSIC_264_H
#define CLEAN_MAIN_MUSIC_264_H

#include "music_queue.h"
#include "types.h"

/* The member at 0x24c of the object: the clock's reading of this frame and of the one before
 * (filled by func_02037318). */
typedef struct MusicClockReading {
    u32 year;
    u8 day;
    u8 month;
    u8 minute;
    u8 hour;
    u32 second;
} MusicClockReading;

typedef struct MusicClock {
    MusicClockReading now;
    MusicClockReading before; /* 0x0c */
} MusicClock;

/* The hour that no music was asked for. */
#define HOUR_MUSIC_NO_HOUR 24

/* The part at 0x04: the music of the hour. */
typedef struct HourMusic {
    const u32 *vtable;
    Obj021c526c *owner; /* 0x04 */
    u32 hour;           /* 0x08: HOUR_MUSIC_NO_HOUR: none */
    u16 music;          /* 0x0c: MUSIC_NONE: none asked for */
    u8 fade_added;      /* 0x0e: the request of priority 0x1b */
    u8 keep_music;      /* 0x0f: the scene's end leaves the music */
    u8 active;          /* 0x10: between a scene's start and its end */
    u8 unk_11[3];
} HourMusic;

/* The part at 0x18. */
typedef struct Music27c {
    const u32 *vtable;
    Obj021c526c *owner; /* 0x04 */
    u16 music;          /* 0x08: MUSIC_NONE: none asked for */
    u8 keep_music;      /* 0x0a: the scene's end leaves the music */
    u8 active;          /* 0x0b: between a scene's start and its end */
} Music27c;

/* The part at 0x24: the musics of the events, each MUSIC_NONE when none was asked for. */
typedef struct EventMusic {
    const u32 *vtable;
    Obj021c526c *owner; /* 0x04 */
    u16 music_1f;       /* 0x08: priority 0x1f, dropped when not at the head (event 0x13) */
    u16 music_20;       /* 0x0a: priority 0x20 (event 0x13 before 2:00) */
    u16 music_21;       /* 0x0c: priority 0x21 (event 0x13 from 2:00) */
    u16 music_22;       /* 0x0e: priority 0x22 (event 0x12 from 23:00) */
    u16 music_23;       /* 0x10: priority 0x23 (event 0xf) */
    u8 fade_added;      /* 0x12: the request of priority 30 */
    u8 year_changed;    /* 0x13: the clock's year changed since it was last cleared */
    u8 keep_music;      /* 0x14: the scene's end leaves the musics */
    u8 active;          /* 0x15: between a scene's start and its end */
    u8 unk_16[2];
} EventMusic;

typedef struct Music264 {
    const u32 *vtable;
    HourMusic hour;   /* 0x04 */
    Music27c part_18; /* 0x18 */
    EventMusic event; /* 0x24 */
} Music264;

void Music264_SetKeep(Music264 *self, void *keep);
void Music264_OnSceneEnd(Music264 *self);
void Music264_OnSceneStart(Music264 *self);
void Music264_Reset(Music264 *self);
void Music264_Execute(Music264 *self);
void Music264_Delete(Music264 *self);
void Music264_Create(Music264 *self);
Music264 *Music264_DestructDelete(Music264 *self);
Music264 *Music264_Destruct(Music264 *self);
Music264 *Music264_Construct(Music264 *self, Obj021c526c *owner);

int EventMusic_NoteYearChange(EventMusic *self);
void EventMusic_DropFade(EventMusic *self);
void EventMusic_AddFade(EventMusic *self, int value);
void EventMusic_Stop23(EventMusic *self);
void EventMusic_Stop22(EventMusic *self);
void EventMusic_Stop21(EventMusic *self);
void EventMusic_Stop20(EventMusic *self);
void EventMusic_Stop1f(EventMusic *self);
void EventMusic_Start23(EventMusic *self, int music);
void EventMusic_Start22(EventMusic *self, int music);
void EventMusic_Start21(EventMusic *self, u16 music);
void EventMusic_Start20(EventMusic *self, int music);
void EventMusic_Start1f(EventMusic *self, u16 music);
void EventMusic_UpdateEvent0f(EventMusic *self, int on);
void EventMusic_UpdateEvent12(EventMusic *self, int on);
void EventMusic_UpdateEvent13(EventMusic *self, int on);
void EventMusic_Update(EventMusic *self);
void EventMusic_SetKeep(EventMusic *self, int keep);
int EventMusic_OnSceneEnd(EventMusic *self);
void EventMusic_OnSceneStart(EventMusic *self);
void EventMusic_Reset(EventMusic *self);
void EventMusic_Execute(EventMusic *self);
void EventMusic_Delete(EventMusic *self);
void EventMusic_Create(EventMusic *self);
EventMusic *EventMusic_DestructDelete(EventMusic *self);
void EventMusic_Destruct(EventMusic *self);
void EventMusic_Construct(EventMusic *self, Obj021c526c *owner);

void Music27c_Stop(Music27c *self);
void Music27c_Start(Music27c *self, int priority, u16 music, int flag);
void Music27c_SetKeep(Music27c *self, int keep);
void Music27c_OnSceneEnd(Music27c *self);
void Music27c_OnSceneStart(Music27c *self);
void Music27c_Reset(Music27c *self);
void Music27c_Execute(Music27c *self);
void Music27c_Delete(Music27c *self);
void Music27c_Create(Music27c *self);
Music27c *Music27c_DestructDelete(Music27c *self);
void Music27c_Destruct(Music27c *self);
void Music27c_Construct(Music27c *self, Obj021c526c *owner);

void HourMusic_UpdateFade(HourMusic *self);
void HourMusic_DropFade(HourMusic *self);
void HourMusic_AddFade(HourMusic *self, int value);
void HourMusic_UpdateHour(HourMusic *self);
void HourMusic_Stop(HourMusic *self);
void HourMusic_Start(HourMusic *self);
void HourMusic_SetKeep(HourMusic *self, int keep);
int HourMusic_OnSceneEnd(HourMusic *self);
void HourMusic_OnSceneStart(HourMusic *self);
void HourMusic_Reset(HourMusic *self);
void HourMusic_Execute(HourMusic *self);
void HourMusic_Delete(HourMusic *self);
void HourMusic_Create(HourMusic *self);
HourMusic *HourMusic_DestructDelete(HourMusic *self);
void HourMusic_Destruct(HourMusic *self);
void HourMusic_Construct(HourMusic *self, Obj021c526c *owner);

/* The clock at the object's 0x24c: read once a frame, and compared with times of day. */
void MusicClock_Read(MusicClock *self);
int MusicClock_YearChanged(const MusicClock *self);
int MusicClock_HourChanged(const MusicClock *self);
u32 MusicClock_IsBetween(const MusicClock *self, u32 h1, u32 m1, u32 s1, u32 h2, u32 m2, u32 s2);
int MusicClock_IsBetweenInHour(const MusicClock *self, u32 m1, u32 s1, u32 m2, u32 s2);
int MusicClock_IsAt(const MusicClock *self, const u16 *date, const u16 *time);
void MusicClock_Reset(MusicClock *self);
void MusicClock_Execute(MusicClock *self);
void MusicClock_Delete(MusicClock *self);
void MusicClock_Create(MusicClock *self);
void MusicClock_Destruct(MusicClock *self);
void MusicClock_Construct(MusicClock *self);

#endif
