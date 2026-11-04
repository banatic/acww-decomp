/* Overlay 85: the turtle as the host of the snow festival (his lines in "sp_npc_turtle5" speak
 * of it), with the message files "sp_npc_turtle5" and "sp_npc_turtle" (model
 * npc_sp/model/ttl, person code 0xd012) at event 0x19: in February, from 6:00 five days before
 * the second Saturday to the end of the day after it (data_020dac08), the week of event 0x11
 * whose notices are "bbs_snowfes". Main's spawner (spawner.h) asks for his object profile 0x5b
 * while the event is on (data_020d06a4), and its spawn table (data_020e1d8c) gives the profile
 * the code 0xd012 and overlay 85, loaded with him; the profile's record is at 0x02279420, which
 * main's profile table data_020e3134 points to. Overlays 84 and 86 are the same turtle at other
 * events.
 *
 * He is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * 0x022794f0, 0x72c bytes, made by TurtleSnowFestival_Create, with his talk scene (TurtleSnowFestivalTalk,
 * turtle_snow_festival_talk.h) at 0x658. On his start he notes the day of event 0x11 (TurtleSnowFestival.festival_day).
 * In his talks the player names one of the town's villagers each day, and on the last day he
 * names the winner, kept in main's event winner record (data_021f3aa4, event_winner.h).
 *
 * His states (TurtleSnowFestival.state), each an entry and an update function (C++ members taking him)
 * from the table data_ov085_022795e0 (filled at start-up by __sinit_ov085_02279368), set by
 * TurtleSnowFestival_SetState:
 *   0  stand:  he takes motion 0 (priority 1);
 *   1  talk:   he turns to the talk's partner and talks; once his action is idle the event
 *              ends: state 2;
 *   2  talked: nothing. */
#ifndef CLEAN_OV085_TURTLE_SNOW_FESTIVAL_H
#define CLEAN_OV085_TURTLE_SNOW_FESTIVAL_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct TurtleSnowFestival;

/* The answers of the list of villagers (TurtleSnowFestivalTalk_OfferVillagers): four villagers and one to
 * go on to the next ones. */
#define TURTLE_SNOW_FESTIVAL_CHOICES 5

/* His talk scene (0xd0 bytes, a scene of main's class 0x020d9ff8 with vtable 0x0227945c). Its
 * receiver's message (byte 0x1e of the scene) is the line shown. */
typedef struct TurtleSnowFestivalTalk {
    SceneBase base;                   /* 0x00 */
    u8 commands[0x30];                /* 0x80: the scene's commands (scene_command.h) */
    struct TurtleSnowFestival *owner; /* 0xb0 */
    s32 item_slot;                    /* 0xb4: the pockets' slot of item 0x37e0, or TURTLE_SNOW_FESTIVAL_TALK_SLOT_* */
    u8 next_villager;                 /* 0xb8: the town's place the list of villagers goes on from */
    u8 unk_b9[3];                     /* 0xb9 */
    s32 choices[TURTLE_SNOW_FESTIVAL_CHOICES]; /* 0xbc: the town's place of each answer of the list, or -1 */
} TurtleSnowFestivalTalk;

/* The size of the special character's scene object he derives from, as far as it is used. */
#define TURTLE_SNOW_FESTIVAL_BASE_SIZE 0x654

typedef struct TurtleSnowFestival {
    u8 base[TURTLE_SNOW_FESTIVAL_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                               /* 0x654: enum TurtleSnowFestivalState */
    TurtleSnowFestivalTalk talk;             /* 0x658 */
    u8 festival_day;                         /* 0x728: the days since event 0x11 started, 0-6 */
    u8 unk_729[3];                           /* 0x729 */
} TurtleSnowFestival;

enum TurtleSnowFestivalState {
    TURTLE_SNOW_FESTIVAL_STAND = 0,
    TURTLE_SNOW_FESTIVAL_TALKING = 1,
    TURTLE_SNOW_FESTIVAL_TALKED = 2,
    TURTLE_SNOW_FESTIVAL_STATES = 3
};

/* A state's functions in data_ov085_022795e0. */
typedef struct TurtleSnowFestivalStep {
    MemberPointer enter;  /* 0x00: int (him); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (him) */
} TurtleSnowFestivalStep;

TurtleSnowFestival *TurtleSnowFestival_Destroy(TurtleSnowFestival *turtle);
void *TurtleSnowFestival_Delete(void *turtle);
void TurtleSnowFestival_OnEvent(TurtleSnowFestival *turtle, int code);
int TurtleSnowFestival_MayAct(TurtleSnowFestival *turtle);
int TurtleSnowFestival_UpdateTalked(void);
int TurtleSnowFestival_UpdateTalk(TurtleSnowFestival *turtle);
int TurtleSnowFestival_EnterTalk(TurtleSnowFestival *turtle);
int TurtleSnowFestival_UpdateStand(void);
int TurtleSnowFestival_EnterStand(TurtleSnowFestival *turtle);
void TurtleSnowFestival_SetState(TurtleSnowFestival *turtle, int state);
int TurtleSnowFestival_Update(TurtleSnowFestival *turtle);
int TurtleSnowFestival_ModelName(void);
int TurtleSnowFestival_TextureName(void);
int TurtleSnowFestival_Start(TurtleSnowFestival *turtle);
int TurtleSnowFestival_Init(TurtleSnowFestival *turtle);
void *TurtleSnowFestival_Create(void);

#endif
