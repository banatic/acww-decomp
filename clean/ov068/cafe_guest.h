/* The cafe's guest: the special character who sits in the cafe at set times of the day, drawn
 * with one of the models npc_sp/model/pga, pgb, poo, ott, wip, xct, mof or end and talking
 * from the message file of its kind ("sp_npc_cf1" to "sp_npc_cf7", "sp_npc_dog"). A special
 * character's scene object (main's special_scene_object.h) of vtable data_ov068_02277e50,
 * 0x750 bytes, made by CafeGuest_Create.
 *
 * Its kind (CafeGuest.kind) is picked when it is set up (CafeGuest_Init) from the clock, the
 * weekday and the day's plan (main's day_plan.h); kind 8 is none, and the guest deletes itself
 * on its first update. Kind 7, on Saturdays from 19:30, plays music: the player may name a
 * song (an item 0x1323-0x1368, one of 70) on a screen of overlay group 9; the guest then plays
 * that song's music (0x63 plus its number), or one of the musics 0xa9-0xac when the name
 * matched no song, follows the music's show (main's music_beat.h) with its face, animation
 * and look, and at the end gives the song's item.
 *
 * The guest lives in five states (CAFE_GUEST_*), each a start and an update called through C++
 * pointers to member functions (data_ov068_02278840, filled when the overlay starts); the
 * events of main's queue move it between them (CafeGuest_OnEvent).
 *
 * It talks through its own scene (CafeGuestScene, vtable data_ov068_02277dc0, a scene of main's
 * class 0x020d9ff8 that runs scene commands, scene_command.h). For kind 7 the scene picks the
 * messages by the scene's phase and the player's answers; its steps (data_ov068_02277d70, a
 * member function and a flag each, filled when the overlay starts) carry the music through:
 *
 *   1 once the talk closes after the name screen: the name taken, the song found (or drawn);
 *   2 each frame once the talk is gone: the lights and the look change, and after 45 frames
 *     the music starts and overlay 93's object is made (func_ov004_02246a2c);
 *   3 each frame: the guest follows the music's show; at its end (func_ov004_02246900), 20
 *     frames on;
 *   4 each frame: after them, the last message (the song given, or not), the music dropped
 *     and the lights back, 30 frames on;
 *   5 each frame: after them, the look straight ahead and the talk opens again. */
#ifndef CLEAN_OV068_CAFE_GUEST_H
#define CLEAN_OV068_CAFE_GUEST_H

#include "main/scene_command.h"
#include "types.h"

/* The guest's kinds: the index of its person code, model, texture and message file. */
#define CAFE_GUEST_KIND_MORNING 0 /* 6:00-6:54 with the day plan's morning bit */
#define CAFE_GUEST_KIND_NIGHT 1   /* 21:00-21:54 except on Saturdays */
#define CAFE_GUEST_KIND_LATE 2    /* weekdays 23:00-23:59, with the plan's night bit and Nook's store at level 3 */
#define CAFE_GUEST_KIND_PLAN_4 3  /* the plan's noon or afternoon value 4 */
#define CAFE_GUEST_KIND_PLAN_1 4  /* value 1 */
#define CAFE_GUEST_KIND_PLAN_2 5  /* value 2 */
#define CAFE_GUEST_KIND_PLAN_3 6  /* value 3 */
#define CAFE_GUEST_KIND_MUSIC 7   /* Saturdays 19:30-23:59: plays music */
#define CAFE_GUEST_KIND_NONE 8
#define CAFE_GUEST_KINDS 9

/* Its states. */
#define CAFE_GUEST_WAIT 0   /* looks about; kind 7 waits for the player at its seat */
#define CAFE_GUEST_TALK 1   /* talks (after event 0) */
#define CAFE_GUEST_PLAY 2   /* talks while the music's show runs */
#define CAFE_GUEST_SEATED 3 /* (after event 1) waits until the player is in state 0x28 */
#define CAFE_GUEST_DONE 4   /* nothing */
#define CAFE_GUEST_STATES 5

/* Its scene's phases (CafeGuestScene.phase): the messages its talk starts with for kind 7. */
#define CAFE_GUEST_PHASE_ASK 0      /* by the hour and what was said today */
#define CAFE_GUEST_PHASE_NAMED 1    /* message 9 with the name the player typed */
#define CAFE_GUEST_PHASE_ANY_SONG 2 /* message 6 with the song's name */
#define CAFE_GUEST_PHASES 3

#define CAFE_GUEST_STEPS 6
#define CAFE_GUEST_NAME_UNITS 10 /* the 16-bit characters of the typed name */

struct CafeGuest;

/* The first 0x14 bytes of a MusicShowState (main's music_beat.h): what the scene copies from the
 * sound system each frame of step 3 to see what changed. */
typedef struct CafeGuestShow {
    s8 type;       /* 0x00: 3 and 4 play animations 0x103 and 0x104 */
    s8 track_kind; /* 0x01: picks the face (-1: "m.0") */
    s8 var0;       /* 0x02: 1 looks ahead, else up */
    s8 var2;       /* 0x03: 0 and 1 end and start a pause */
    s8 var3;       /* 0x04: 2, 0 or 1 switch overlay 93's object */
    u8 pad_05[3];
    fx32 frame_a; /* 0x08: the speed of the model's base animation for types 3 and 4 */
    fx32 frame_b; /* 0x0c */
    fx32 frame_c; /* 0x10 */
} CafeGuestShow;

/* The talk scene (0xd4 bytes). */
typedef struct CafeGuestScene {
    SceneCommandScene base;  /* 0x00 */
    s32 phase;               /* 0xb0: CAFE_GUEST_PHASE_* */
    struct CafeGuest *owner; /* 0xb4 */
    s32 step;                /* 0xb8: of data_ov068_02277d70 */
    CafeGuestShow show;      /* 0xbc: as last seen */
    u8 show_started;         /* 0xd0: the first animation of the show was asked for */
    u8 pad_d1[3];
} CafeGuestScene;

typedef struct CafeGuest {
    u8 unk_000[0x4e8];                     /* the scene object (special_scene_object.h, scene_object.h) */
    u32 flags;                             /* 0x4e8: the scene object's flags (2: held, scene_action.h) */
    u8 unk_4ec[0x166];                     /* 0x4ec */
    u16 song;                              /* 0x652: the song's item, 0x1323-0x1368 */
    u32 music;                             /* 0x654: the music played */
    s32 state;                             /* 0x658: CAFE_GUEST_* */
    CafeGuestScene scene;                  /* 0x65c */
    s32 kind;                              /* 0x730: CAFE_GUEST_KIND_* */
    u16 typed_name[CAFE_GUEST_NAME_UNITS]; /* 0x734: what the player typed on the name screen */
    u16 timer;                             /* 0x748: frames left (Countdown_Tick16) */
    u8 agreed;                             /* 0x74a: the player said yes to messages 1-3 */
    u8 no_such_song;                       /* 0x74b: the name matched no song */
    u8 names_song;                         /* 0x74c: the player said yes to message 5 (will name a song) */
    u8 pad_74d[3];
} CafeGuest;

/* What the talk starts with (the scene's slot 0x78). */
typedef struct CafeGuestTalkStart {
    const char *name; /* the message file */
    u8 message;
} CafeGuestTalkStart;

CafeGuest *CafeGuest_Destruct(CafeGuest *self);
CafeGuest *CafeGuest_DestructDelete(CafeGuest *self);
int CafeGuest_Kind(CafeGuest *self);
unsigned short CafeGuest_DrawSong(void);
int CafeGuest_WaitForListener(CafeGuest *self);
void CafeGuest_OnEvent(CafeGuest *self, int code);
int CafeGuest_MayAct(CafeGuest *self);
void CafeGuestScene_LookAhead(CafeGuestScene *scene);
void CafeGuestScene_GiveSong(CafeGuestScene *scene);
void CafeGuestScene_FollowShow(CafeGuestScene *scene);
void CafeGuestScene_StartMusic(CafeGuestScene *scene);
void CafeGuestScene_TakeName(CafeGuestScene *scene);
void CafeGuestScene_SetStep(CafeGuestScene *scene, unsigned long step);
void CafeGuestScene_OnTalkClosed(CafeGuestScene *scene);
void CafeGuestScene_WhileTalkOpen(CafeGuestScene *scene);
void CafeGuestScene_OnSongAnswer(CafeGuestScene *scene, int answer);
void CafeGuestScene_OnTradeAnswer(int unused, int answer);
void CafeGuestScene_OnListenAnswer(CafeGuestScene *scene, int answer);
void CafeGuestScene_OnAnswerKind7(CafeGuestScene *scene, int answer);
void CafeGuestScene_OnAnswer(CafeGuestScene *scene, int answer);
void CafeGuestScene_ToMusic(CafeGuestScene *scene);
void CafeGuestScene_ToNameScreen(CafeGuestScene *scene);
void CafeGuestScene_OnMessageEndedKind7(CafeGuestScene *scene, void *arg);
void CafeGuestScene_OnMessageEnded(CafeGuestScene *scene, void *arg);
void CafeGuestScene_PutValuesKind7(CafeGuestScene *scene, int unused);
void CafeGuestScene_PutValues(CafeGuestScene *scene, int unused);
void CafeGuestScene_StartTalk(CafeGuestScene *scene, CafeGuestTalkStart *start);
unsigned long CafeGuestScene_Phase(CafeGuestScene *scene);
void CafeGuestScene_SetPhase(CafeGuestScene *scene, unsigned long phase);
void CafeGuestScene_Begin(CafeGuestScene *scene, CafeGuest *owner);
CafeGuestScene *CafeGuestScene_DestructDelete(CafeGuestScene *scene);
CafeGuestScene *CafeGuestScene_Destruct(CafeGuestScene *scene);
CafeGuestScene *CafeGuestScene_Construct(CafeGuestScene *scene);
int CafeGuest_UpdatePlay(CafeGuest *self);
int CafeGuest_StartPlay(CafeGuest *self);
int CafeGuest_UpdateSeated(CafeGuest *self);
int CafeGuest_StartSeated(void);
int CafeGuest_UpdateDone(void);
int CafeGuest_StartDone(void);
int CafeGuest_UpdateTalk(CafeGuest *self);
int CafeGuest_StartTalk(CafeGuest *self);
int CafeGuest_UpdateWait(CafeGuest *self);
int CafeGuest_StartWait(CafeGuest *self);
void CafeGuest_SetState(CafeGuest *self, int state);
int CafeGuest_Update(CafeGuest *self);
unsigned int CafeGuest_ModelName(CafeGuest *self);
int CafeGuest_TextureName(CafeGuest *self);
int CafeGuest_Leave(CafeGuest *self);
int CafeGuest_Start(CafeGuest *self);
int CafeGuest_Init(CafeGuest *self);
CafeGuest *CafeGuest_Create(void);

#endif
