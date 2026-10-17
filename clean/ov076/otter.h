/* Overlay 76: the otter, the special character of the message file "sp_npc_otter" with the
 * model npc_sp/model/seo, met outdoors. He is made by main's spawner (spawner.h): the spawn
 * table's entry for object profile 0x68 (person code 0xd016) loads overlay 76 with him, and
 * his record at 0x02279708 (create function Otter_Create) is the one main's profile table
 * data_020e3134 points to.
 *
 * He is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * 0x022797d4, 0x728 bytes. On his start he is held (flag 2 at 0x4e8) and notes the angle he
 * faces. The player may talk to him once a day (the current player's daily bit 0x18, set when
 * he hands an item over) and not after he gave something in this visit. His talk scene
 * (OtterTalk, otter_talk.h) can give the player an item, after which he dives and leaves.
 *
 * His states (Otter.state), each an entry and an update function (C++ members taking him) from
 * the table data_ov076_0227988c (filled at start-up by __sinit_ov076_022795ac), set by
 * Otter_SetState:
 *   0  stand:  he stands;
 *   1  talk:   he turns to the talk's partner and talks; once his action is idle his event is
 *              finished (state 2);
 *   2  talked: nothing;
 *   3  turn:   he turns to the angle he started with (half a turn further when he gave
 *              something), then stands (state 0), or dives (state 4) when he gave something;
 *   4  dive:   animation 0xf9 once and sound 0x814; he turns half about and spins back to
 *              angle 0, his head looks ahead and his height is noted. At its whole frame 0xb
 *              his shadow and solidity go; at frame 0x1b the water splashes 3.5 along z from him
 *              (effect 0x16 at height 0, the fish within 5.0 scared, sound 0x7ed); at the
 *              animation's end, state 5;
 *   5  gone:   animation 0xfa, his head locked and his angle 0; he rises 4.0 at once and 0xeb
 *              a frame until he is 20.0 above where he dove, and is deleted. */
#ifndef CLEAN_OV076_OTTER_H
#define CLEAN_OV076_OTTER_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct Otter;

/* His talk scene (0xc4 bytes): a scene of class 0x020d9ff8 (main's obj_020d9ff8.h) with vtable
 * 0x02279744 (otter_talk.h). */
typedef struct OtterTalk {
    SceneBase base;              /* 0x00: the receiver's message (byte 0x1e) is the line shown */
    u8 unk_80[0x30];             /* 0x80: the scene's commands (scene_command.h) */
    s32 sequence;                /* 0xb0: OTTER_TALK_*, what the talk started with */
    struct Otter *owner;         /* 0xb4 */
    u16 item;                    /* 0xb8: the item he gave, 0xfff1 for none */
    u8 unk_ba[2];                /* 0xba */
    MemberPointer after_command; /* 0xbc: run once when a command of the scene ends */
} OtterTalk;

/* The size of the special character's scene object he derives from, as far as it is used. */
#define OTTER_BASE_SIZE 0x654

typedef struct Otter {
    u8 base[OTTER_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                /* 0x654: enum OtterState */
    OtterTalk talk;           /* 0x658 */
    u8 gave;                  /* 0x71c: he gave an item in this visit */
    u8 unk_71d;               /* 0x71d */
    s16 turn_angle;           /* 0x71e: the angle he turns to (state 3) */
    s32 dive_height;          /* 0x720: his height when he dove (fx32) */
    u16 spin;                 /* 0x724: the step of his spin while he dives */
    u8 unk_726[2];            /* 0x726 */
} Otter;

enum OtterState {
    OTTER_STAND = 0,
    OTTER_TALK = 1,
    OTTER_TALKED = 2,
    OTTER_TURN = 3,
    OTTER_DIVE = 4,
    OTTER_GONE = 5,
    OTTER_STATES = 6
};

/* A state's functions in data_ov076_0227988c. */
typedef struct OtterStep {
    MemberPointer enter;  /* 0x00: int (him); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (him) */
} OtterStep;

/* His object. */
Otter *Otter_Destruct(Otter *otter);
Otter *Otter_DestructDelete(Otter *otter);
void Otter_OnEvent(Otter *otter, int code);
int Otter_AgreesToTalk(Otter *otter);
void Otter_SetState(Otter *otter, int state);
int Otter_Update(Otter *otter);
int Otter_ModelName(void);
int Otter_TextureName(void);
int Otter_Start(Otter *otter);
int Otter_Init(Otter *otter);
void *Otter_Create(void);

/* His states. */
int Otter_EnterStand(Otter *otter);
int Otter_UpdateStand(void);
int Otter_EnterTalk(Otter *otter);
int Otter_UpdateTalk(Otter *otter);
int Otter_UpdateTalked(void);
int Otter_EnterTurn(Otter *otter);
int Otter_UpdateTurn(Otter *otter);
int Otter_EnterDive(Otter *otter);
int Otter_UpdateDive(Otter *otter);
int Otter_EnterGone(Otter *otter);
int Otter_UpdateGone(Otter *otter);

#endif
