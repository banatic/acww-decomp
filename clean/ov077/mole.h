/* Overlay 77: the mole, the special character of the message file "sp_npc_reset" with the
 * model npc_sp/model/mol, object profile 0x65 (his record at data_ov077_0227979c, which main's
 * profile table data_020e3134 points to). Main's spawner (main/spawner.h) makes him from its
 * spawn table's entry of code 0xd011, loading this overlay with him; its check answers in
 * scene 0 while part 0x30 of the object at data_021d27ac is set (block_021d27ac_parts.h: the
 * start mode for a player record that was not saved). A scene object of class 0x020da088
 * (special_scene_object.h) with vtable 0x0227988c, 0x728 bytes.
 *
 * He waits under the ground by the building of the codes 0x5014-0x501a on the map until the
 * player comes to one of five tiles before it, then comes up beside it, talks (MoleTalk,
 * mole_talk.h, at 0x658), goes back down, clears part 0x30 and is deleted.
 *
 * His states (MOLE_*), a table of C++ pointers to member functions (an entry and a run for
 * each state, data_ov077_022799a0, filled by __sinit_ov077_02279608), set by Mole_SetState:
 * - MOLE_WAIT (his start): animation 0xfd asked for and the building's tile noted; each frame
 *   his animation is held at frame 0, he faces the player, and when the player is on one of the
 *   tiles before the building he is put on a tile beside it and asks for an event (kind 7);
 *   without the player he is deleted. He is not drawn in this state;
 * - MOLE_RISE (told of event 1, his talk set up): his animation runs and he is solid, with the
 *   effect 0x30 and sound 0x7e6; once animation 0xfd is done, MOLE_TALK;
 * - MOLE_TALK: he turns to the one his talk names and talks; once his action ends, MOLE_SINK;
 * - MOLE_SINK: animation 0xfe and sound 0x7e7; once it is done his event is finished, part
 *   0x30 cleared and he is deleted;
 * - MOLE_TALKED (told the act ended, 8) and MOLE_STATE_0: nothing.
 * At the whole frames 2 and 12 of his animation the effect is started and ended. */
#ifndef CLEAN_OV077_MOLE_H
#define CLEAN_OV077_MOLE_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct Mole;

/* His talk scene (0xc0 bytes): a scene of class 0x020d9ff8 (main's obj_020d9ff8.h) with vtable
 * 0x022797fc (mole_talk.h). */
typedef struct MoleTalk {
    SceneBase scene;    /* 0x00: the receiver's message (byte 0x1e) is the line shown */
    u8 unk_80[0x30];    /* 0x80: the scene's commands (scene_command.h) */
    s32 sequence;       /* 0xb0: MOLE_TALK_SEQ_*, what runs next (MoleTalk_SetSequence) */
    u8 countdown;       /* 0xb4: the frames left before MOLE_TALK_SEQ_WAIT goes on */
    u8 unk_b5[3];       /* 0xb5 */
    struct Mole *owner; /* 0xb8 */
    u8 music_started;   /* 0xbc: his music asked for (slot 0x74) */
    u8 unk_bd[3];       /* 0xbd */
} MoleTalk;

/* The size of the special character's scene object he derives from, as far as it is used. */
#define MOLE_BASE_SIZE 0x654

/* No phrase picked yet (Mole.phrase). */
#define MOLE_NO_PHRASE 0xff

typedef struct Mole {
    u8 base[MOLE_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;               /* 0x654: MOLE_* */
    MoleTalk talk;           /* 0x658 */
    u8 phrase;               /* 0x718: the message of "st_general" his talk picked */
    u8 unk_719[3];           /* 0x719 */
    int building_x;          /* 0x71c: the building's tile */
    int building_z;          /* 0x720 */
    s32 effect;              /* 0x724: the effect's handle (effect_system.h), -1 for none */
} Mole;

/* The states. */
#define MOLE_STATE_0 0
#define MOLE_TALK 1
#define MOLE_TALKED 2
#define MOLE_WAIT 3
#define MOLE_RISE 4
#define MOLE_SINK 5
#define MOLE_STATES 6

/* A state's functions in data_ov077_022799a0. */
typedef struct MoleStep {
    MemberPointer enter; /* 0x00: int (him); the state is taken unless it answers 0 */
    MemberPointer run;   /* 0x08: int (him) */
} MoleStep;
extern MoleStep data_ov077_022799a0[MOLE_STATES];

/* His object. */
Mole *Mole_Destruct(Mole *mole);
Mole *Mole_DestructDelete(Mole *mole);
void Mole_OnEvent(Mole *mole, int code);
int Mole_MayAct(void);
void Mole_SetState(Mole *mole, int state);
int Mole_Update(Mole *mole);
int Mole_ModelName(void);
int Mole_TextureName(void);
int Mole_Draw(Mole *mole);
int Mole_Leave(Mole *mole);
int Mole_Start(Mole *mole);
int Mole_Init(Mole *mole);
Mole *Mole_Create(void);

/* His states. */
int Mole_UpdateSink(Mole *mole);
int Mole_EnterSink(Mole *mole);
int Mole_UpdateRise(Mole *mole);
int Mole_EnterRise(Mole *mole);
int Mole_UpdateWait(Mole *mole);
int Mole_EnterWait(Mole *mole);
int Mole_UpdateTalked(void);
int Mole_EnterTalked(void);
int Mole_UpdateTalk(Mole *mole);
int Mole_EnterTalk(Mole *mole);
int Mole_UpdateState0(void);
int Mole_EnterState0(void);

/* The overlay's static initialiser (ov077_static_init.c). */
int MoleInit_Tables(void);

#endif
