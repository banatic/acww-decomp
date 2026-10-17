/* Overlay 52: the fox in his tent, the special character of the message file "sp_npc_fox" with
 * the model npc_sp/model/fox (Crazy Redd is the game's fox; overlay 3's fox.h is the same
 * character outdoors). His record at 0x02261e60 (create function FoxTent_Create) is the one
 * main's profile table data_020e3134 points to for him. The tent's floor shows the three items
 * of the fox's shop (main's fox_shop.h, data_021f3b30; overlay 4's ShopDisplay_PlaceFox), and
 * the last sale (main's last_sale.h, data_021f3aec) is kept for the next visitor.
 *
 * He is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * 0x02261f40, 0x740 bytes. On his start he claims the map's object 0 (collision_map.h), so it
 * is not reported on the field; when the player stands on it he talks before letting the player
 * out (FoxTent_TalkAtExit).
 *
 * Each frame of most states he looks for a reason to talk (FoxTent_TalkAtExit, then
 * FoxTent_TalkIfLate before 6 a.m., then FoxTent_TalkAboutItem when the player presses A or
 * taps the item in front of him); each asks for an event of kind 6 about him, whose start tells
 * his vtable slot 0x4c (FoxTent_OnEvent) and starts his talk scene with a line chosen by
 * FoxTentTalk.sequence (fox_tent_talk.h).
 *
 * His states (FoxTent.state), each an entry and an update function (C++ members taking him)
 * from the table data_ov052_02262000 (filled at start-up by __sinit_ov052_02261c48), set by
 * FoxTent_SetState:
 *   0  greet:   his talk's sequence 0; he asks for an event of kind 6 each frame;
 *   1  stand:   he stands; when the player is more than 3.0 away and his step towards the
 *               player moves him, he follows (state 3); else when the player is more than an
 *               eighth of a turn off his facing, he turns (state 2);
 *   2  turn:    he turns to face the player, then stands; follows as in state 1;
 *   3  follow:  he walks (runs past 4.0) towards the player until within 3.0 or stopped;
 *   4  follow:  the same as state 3 (nothing here enters it);
 *   5  talk:    he turns to the talk's partner and talks; once his action is idle (and every
 *               answer came, when he waits for them) his event ends: state 7;
 *   6  talk, then out: as 5 keeping the camera; then main's entry record takes exit 0;
 *   7  talked:  nothing;
 *   8  paused:  an event starts: nothing;
 *   9  come:    he walks to the player (up to 50 frames) and then talks: state 5;
 *  10  at exit: he turns to face the player and stands, asking for an event of kind 6. */
#ifndef CLEAN_OV052_FOX_TENT_H
#define CLEAN_OV052_FOX_TENT_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct FoxTent;

/* His talk scene (0xc4 bytes): a scene of class 0x020d9ff8 (main's obj_020d9ff8.h) with vtable
 * 0x02261eb0. */
typedef struct FoxTentTalk {
    SceneBase base;        /* 0x00: the receiver's message (byte 0x1e) is the line shown */
    u8 unk_80[0x30];       /* 0x80: the scene's commands (scene_command.h) */
    u32 sequence;          /* 0xb0: FOX_TENT_TALK_* , what the next talk starts with */
    struct FoxTent *owner; /* 0xb4 */
    s32 price;             /* 0xb8: the price of the item the player faces */
    s32 card_slot;         /* 0xbc: the pocket of the item 0x34a8, -1 not looked for yet, -2 done */
    u8 declined;           /* 0xc0: the player said no to the membership once */
    u8 unk_c1[3];          /* 0xc1 */
} FoxTentTalk;

/* The size of the special character's scene object he derives from, as far as it is used. */
#define FOX_TENT_BASE_SIZE 0x654

/* The items he has told the price of, and his lines' variants. */
#define FOX_TENT_TOLD_ITEMS 3
#define FOX_TENT_LINE_VARIANTS 5

typedef struct FoxTent {
    u8 base[FOX_TENT_BASE_SIZE];            /* 0x000: the special character's scene object */
    s32 state;                              /* 0x654: enum FoxTentState */
    FoxTentTalk talk;                       /* 0x658 */
    u16 stand_word;                         /* 0x71c: the word of his next stand */
    u16 item;                               /* 0x71e: the item the player faces, 0xfff1 for none */
    u16 told[FOX_TENT_TOLD_ITEMS];          /* 0x720: the items he told the price of, 0xfff1 free */
    u8 unk_726[2];                          /* 0x726 */
    s32 item_x;                             /* 0x728: the tile of the item the player faces */
    s32 item_z;                             /* 0x72c */
    u8 awaiting_answers;                    /* 0x730: his talk waits for every answer to come */
    u8 come_frames;                         /* 0x731: the frames he walks before he talks */
    u8 sold;                                /* 0x732: something was sold in this visit */
    u8 offer_used[FOX_TENT_LINE_VARIANTS];  /* 0x733: the variants of his offer said */
    u8 thanks_used[FOX_TENT_LINE_VARIANTS]; /* 0x738: the variants of his thanks said */
    u8 unk_73d[3];                          /* 0x73d */
} FoxTent;

enum FoxTentState {
    FOX_TENT_GREET = 0,
    FOX_TENT_STAND = 1,
    FOX_TENT_TURN = 2,
    FOX_TENT_FOLLOW = 3,
    FOX_TENT_FOLLOW_4 = 4,
    FOX_TENT_TALK = 5,
    FOX_TENT_TALK_THEN_OUT = 6,
    FOX_TENT_TALKED = 7,
    FOX_TENT_PAUSED = 8,
    FOX_TENT_COME = 9,
    FOX_TENT_AT_EXIT = 10,
    FOX_TENT_STATES = 11
};

/* A state's functions in data_ov052_02262000. */
typedef struct FoxTentStep {
    MemberPointer enter;  /* 0x00: int (fox); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (fox) */
} FoxTentStep;

/* His vtable slots and questions. */
FoxTent *FoxTent_Destruct(FoxTent *fox);
FoxTent *FoxTent_DestructDelete(FoxTent *fox);
int FoxTent_TalkIfLate(FoxTent *fox);
int FoxTent_TalkAtExit(FoxTent *fox);
int FoxTent_TalkAboutItem(FoxTent *fox);
int FoxTent_FindFacedItem(FoxTent *fox);
void FoxTent_OnEvent(FoxTent *fox, unsigned int code, int participant);
int FoxTent_MayAct1(FoxTent *fox);
int FoxTent_MayAct(FoxTent *fox);
void FoxTent_SetState(FoxTent *fox, int state);
int FoxTent_Update(FoxTent *fox);
int FoxTent_ModelName(void);
int FoxTent_TextureName(void);
int FoxTent_Start(FoxTent *fox);
int FoxTent_Init(FoxTent *fox);
void *FoxTent_Create(void);

/* His states. */
int FoxTent_EnterGreet(FoxTent *fox);
int FoxTent_UpdateGreet(FoxTent *fox);
int FoxTent_EnterStand(FoxTent *fox);
int FoxTent_UpdateStand(FoxTent *fox);
int FoxTent_EnterTurn(FoxTent *fox);
int FoxTent_UpdateTurn(FoxTent *fox);
int FoxTent_EnterFollow(FoxTent *fox);
int FoxTent_UpdateFollow(FoxTent *fox);
int FoxTent_EnterFollow4(FoxTent *fox);
int FoxTent_UpdateFollow4(FoxTent *fox);
int FoxTent_EnterTalk(FoxTent *fox);
int FoxTent_UpdateTalk(FoxTent *fox);
int FoxTent_EnterTalkThenOut(FoxTent *fox);
int FoxTent_UpdateTalkThenOut(FoxTent *fox);
int FoxTent_EnterTalked(void);
int FoxTent_UpdateTalked(void);
int FoxTent_EnterPaused(void);
int FoxTent_UpdatePaused(void);
int FoxTent_EnterCome(FoxTent *fox);
int FoxTent_UpdateCome(FoxTent *fox);
int FoxTent_EnterAtExit(FoxTent *fox);
int FoxTent_UpdateAtExit(FoxTent *fox);

#endif
