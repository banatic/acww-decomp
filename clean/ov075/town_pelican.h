/* Overlay 75: the pelican of the message file "sp_npc_mpelican" with the model npc_sp/model/plb
 * and its texture plb_tex (person code 0xd008), met in the town. Pete, the game's mail carrier,
 * is a male pelican, but nothing here names him; the post office's pelicans are another file
 * ("sp_npc_pelican"). The spawner's table (main's spawner.h, data_020e1d8c) makes him as object
 * profile 0x54 with code 0xd008 and loads overlay 75 with him; his record at 0x02279918 is what
 * main's profile table data_020e3134 points to for profile 0x54. He is put where the town's
 * near spot says (near_spot.h, part 0x24 of the object at data_021d27ac).
 *
 * He is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * 0x022799fc, 0x71c bytes, made by TownPelican_Create. His talk scene (TownPelicanTalk,
 * town_pelican_talk.h, at 0x658) plays his animation 0xd5 and turns him to the player at the
 * end of the first line of his first talk, after which he counts as met.
 *
 * His states (TownPelican.state), each an entry and an update function (C++ members taking
 * him) from the table data_ov075_02279b08 (filled at start-up by __sinit_ov075_02279724), set
 * by TownPelican_SetState and run each frame by TownPelican_Update:
 *   0  rest:     he takes animation 0xef (and looks nowhere); nothing more;
 *   1  talk:     (met) he turns to the talk's partner and talks, looking at the player, and is
 *                no longer held;
 *   2  talk end: unless met he talks where he is; once his action is idle the event ends:
 *                state 3;
 *   3  talked:   nothing;
 *   4  hidden:   he is not shown until the near spot is found: then he is put there, shown,
 *                and rests (state 0);
 *   5  wander:   in the camera's view he stands or, one frame in eight, walks or turns toward
 *                a free tile 12.0 away, as the faceless cat of overlay 74 does
 *                (ov074/mystery_cat.h) but asking for the walk or the turn even when it is the
 *                motion he has; out of view, nothing.
 * The events he is told of (TownPelican_OnEvent): code 0, state 2; code 3, the talk begins
 * (state 1 once met); code 8, the event ended (state 0, or state 5 once met). */
#ifndef CLEAN_OV075_TOWN_PELICAN_H
#define CLEAN_OV075_TOWN_PELICAN_H

#include "autoload_2/vector.h"
#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct TownPelican;

/* His talk scene (0xc0 bytes): a scene of class 0x020d9ff8 (main's obj_020d9ff8.h) with vtable
 * data_ov075_0227996c. Its receiver's message (byte 0x1e of the scene) is the line shown. */
typedef struct TownPelicanTalk {
    SceneBase base;            /* 0x00 */
    u8 unk_80[0x30];           /* 0x80: the scene's commands (scene_command.h) */
    u32 sequence;              /* 0xb0: TOWN_PELICAN_TALK_SEQUENCE_* (town_pelican_talk.h) */
    u8 step;                   /* 0xb4: the step of the sequence */
    u8 unk_b5[3];              /* 0xb5 */
    struct TownPelican *owner; /* 0xb8 */
    u8 unk_bc[4];              /* 0xbc */
} TownPelicanTalk;

/* The size of the special character's scene object he derives from, as far as it is used. */
#define TOWN_PELICAN_BASE_SIZE 0x654

typedef struct TownPelican {
    u8 base[TOWN_PELICAN_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                       /* 0x654: enum TownPelicanState */
    TownPelicanTalk talk;            /* 0x658 */
    u8 met;                          /* 0x718: set at the end of his first talk's first line */
    u8 walk_frames;                  /* 0x719: the frames his walk or turn may still go on */
    u8 unk_71a[2];                   /* 0x71a */
} TownPelican;

enum TownPelicanState {
    TOWN_PELICAN_REST = 0,
    TOWN_PELICAN_TALK = 1,
    TOWN_PELICAN_TALK_END = 2,
    TOWN_PELICAN_TALKED = 3,
    TOWN_PELICAN_HIDDEN = 4,
    TOWN_PELICAN_WANDER = 5,
    TOWN_PELICAN_STATES = 6
};

/* A state's functions in data_ov075_02279b08. */
typedef struct TownPelicanStep {
    MemberPointer enter;  /* 0x00: int (pelican); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (pelican) */
} TownPelicanStep;

void *TownPelican_Destroy(TownPelican *pelican);
void *TownPelican_Delete(void *pelican);
void TownPelican_OnEvent(TownPelican *pelican, int code);
int TownPelican_MayAct(TownPelican *pelican);
int TownPelican_UpdateTalked(void);
int TownPelican_UpdateTalkEnd(TownPelican *pelican);
int TownPelican_EnterTalkEnd(TownPelican *pelican);
int TownPelican_UpdateTalk(void);
int TownPelican_EnterTalk(TownPelican *pelican);
int TownPelican_UpdateWander(TownPelican *pelican);
int TownPelican_IsSteeringAside(TownPelican *pelican);
int TownPelican_SteerAside(TownPelican *pelican);
int TownPelican_SidePoint(TownPelican *pelican, Vec3 *out, const Vec3 *offset);
int TownPelican_PickWalkPoint(TownPelican *pelican, fx32 *x, fx32 *z);
int TownPelican_InView(TownPelican *pelican);
int TownPelican_IsInViewOf(int unused, const Vec3 *focus, const Vec3 *at);
int TownPelican_EnterWander(TownPelican *pelican);
int TownPelican_UpdateHidden(TownPelican *pelican);
int TownPelican_EnterHidden(u8 *pelican);
int TownPelican_UpdateRest(void);
int TownPelican_EnterRest(TownPelican *pelican);
void TownPelican_SetState(TownPelican *pelican, int state);
int TownPelican_Update(TownPelican *pelican);
int TownPelican_ModelName(void);
int TownPelican_TextureName(void);
int TownPelican_Leave(TownPelican *pelican);
int TownPelican_AnimSpeed(void);
int TownPelican_Start(TownPelican *pelican);
int TownPelican_Init(TownPelican *pelican);
void *TownPelican_Create(void);

#endif
