/* Overlay 49: Mabel, the younger of the Able Sisters, in their tailor's shop: the special
 * character of the message file "sp_npc_ysister" with the model npc_sp/model/hgh, object
 * profile record data_ov049_022632f0 (main's profile table data_020e3134 points to it). A scene
 * object of class 0x020da088 (special_scene_object.h) with vtable data_ov049_02263544, 0x978
 * bytes, made by Mabel_Create.
 *
 * She stands behind the counter and turns to the player, walking along the counter's path
 * (ScenePathStep_Choose toward the player's start point) when the player is farther than 5.0.
 * When the player faces an item on display (Mabel_FindShown: the tile 2.0 ahead of the player,
 * at the press of A or a tap on it) she starts an event of kind 6 and tells its price: the
 * clothes, hats, accessories and umbrellas of the shop (talk mode 4), or one of the shop's
 * eight designs (talk mode 5). Her talk scene (MabelTalk, mabel_talk.h, at 0x658) sells them
 * and has the player try clothes on, buys the player's clothes, and copies or swaps designs
 * between the player and the shop.
 *
 * Her states (Mabel.state, MABEL_STATE_*) are C++ pointers to member functions, an entry and an
 * update each, in data_ov049_02263640 (filled at start-up by __sinit_ov049_02262e14), set by
 * Mabel_SetState and run each frame by Mabel_Update:
 *   0  greet:        each frame she asks for an event of kind 6 (to greet the player);
 *   1  stand:        she stands; a turn or a walk when the player moves; with a dated event
 *                    of kind 2 today she acts (state 7) after 100 to 180 frames;
 *   2  turn:         she turns to the player, then stands;
 *   3  walk:         she walks along the counter toward the player, then stands;
 *   4  talk:         she turns to the one she talks with and talks; then the event ends;
 *   5  talk, leave:  the same, then the player is put out of the shop (exit 0);
 *   6  talked:       nothing;
 *   7  act:          her motion of kind 10, then she stands;
 *   8  await:        while the session decides who runs her (linked);
 *   9  other:        another system's player talks to her;
 *   10 linked stand: she stands and turns to the player (state 11);
 *   11 linked turn:  she turns to the player, then state 10;
 *   12 paused:       an event starts: nothing;
 *   13 approach:     she walks toward the player for up to 50 frames, then talks;
 *   14 speaker:      she joined another's talk as a speaker: she stands;
 *   15 turn, ask:    she turns, then asks for an event of kind 6 each frame (talk mode 3). */
#ifndef CLEAN_OV049_MABEL_H
#define CLEAN_OV049_MABEL_H

#include "main/design.h"
#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

enum MabelState {
    MABEL_STATE_GREET = 0,
    MABEL_STATE_STAND = 1,
    MABEL_STATE_TURN = 2,
    MABEL_STATE_WALK = 3,
    MABEL_STATE_TALK = 4,
    MABEL_STATE_TALK_LEAVE = 5,
    MABEL_STATE_TALKED = 6,
    MABEL_STATE_ACT = 7,
    MABEL_STATE_AWAIT = 8,
    MABEL_STATE_OTHER = 9,
    MABEL_STATE_LINKED_STAND = 10,
    MABEL_STATE_LINKED_TURN = 11,
    MABEL_STATE_PAUSED = 12,
    MABEL_STATE_APPROACH = 13,
    MABEL_STATE_SPEAKER = 14,
    MABEL_STATE_TURN_ASK = 15,
    MABEL_STATES = 16
};

/* A state's functions in data_ov049_02263640. */
typedef struct MabelStep {
    MemberPointer enter;  /* 0x00: int (mabel); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (mabel) */
} MabelStep;

/* MabelTalk.mode: what the talk is about, which picks the line it starts with. */
#define MABEL_TALK_MODE_FIRST 0       /* the first greeting today */
#define MABEL_TALK_MODE_AGAIN 1       /* greeted already today (daily bit 15) */
#define MABEL_TALK_MODE_TALKED 2      /* the player talked to her */
#define MABEL_TALK_MODE_SPOT_TAKEN 3  /* the player's start point is claimed */
#define MABEL_TALK_MODE_ITEM 4        /* an item on display: its price */
#define MABEL_TALK_MODE_SHOP_DESIGN 5 /* one of the shop's designs */

struct Mabel;

/* Her talk scene (0xd0 bytes): a scene of class 0x020d9ff8 (main's obj_020d9ff8.h) with vtable
 * data_ov049_022634b4. */
typedef struct MabelTalk {
    SceneBase base;      /* 0x00: the receiver's message (byte 0x1e) is the line shown */
    u8 unk_80[0x30];     /* 0x80: the scene's commands (scene_command.h) */
    struct Mabel *owner; /* 0xb0 */
    u32 mode;            /* 0xb4: MABEL_TALK_MODE_* */
    u32 sequence;        /* 0xb8: MABEL_TALK_SEQUENCE_* (mabel_talk.h) */
    s32 price;           /* 0xbc: the bells of the deal talked about */
    s32 extra_bags;      /* 0xc0: what SceneBells_Fit is asked with, 0 */
    u8 unk_c4[0x0c];     /* 0xc4 */
} MabelTalk;

/* The size of the special character's scene object she derives from, as far as it is used. */
#define MABEL_BASE_SIZE 0x654

typedef struct Mabel {
    u8 base[MABEL_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                /* 0x654: enum MabelState */
    MabelTalk talk;           /* 0x658 */
    s32 tile_x;               /* 0x728: the tile of the item on display talked about */
    s32 tile_z;               /* 0x72c */
    u8 unk_730[4];            /* 0x730 */
    u16 worn;                 /* 0x734: what the player wore before trying an item on */
    u16 worn_second;          /* 0x736: a second item taken off for it, 0xfff1 for none */
    u16 item;                 /* 0x738: the item on display talked about, 0xfff1 for none */
    u8 unk_73a[2];            /* 0x73a */
    Design design;            /* 0x73c: constructed and destroyed with her, not used here */
    u16 act_countdown;        /* 0x970: the frames before she acts (state 7) */
    u16 stand_word;           /* 0x972: the word of her next stand (scene_motion_request.h) */
    u8 bought;                /* 0x974: the item on display was bought in this talk */
    u8 has_event;             /* 0x975: the player has a dated event of kind 2 today */
    u8 design_slot;           /* 0x976: the shop's design talked about, 0 to 7 */
    u8 approach_frames;       /* 0x977: the frames left to walk toward the player (state 13) */
} Mabel;

/* Her vtable slots and questions (mabel.c). */
Mabel *Mabel_Destruct(Mabel *mabel);
void *Mabel_DestructDelete(Mabel *mabel);
int Mabel_CheckSpotTaken(Mabel *mabel);
int Mabel_OfferShown(Mabel *mabel);
int Mabel_FindShown(Mabel *mabel);
void Mabel_OnEvent(Mabel *mabel, int code, int participant);
int Mabel_MayActKind6(Mabel *mabel);
int Mabel_MayAct(Mabel *mabel);
void Mabel_JoinedTalk(Mabel *mabel);
void Mabel_TalkEnded(Mabel *mabel);
void Mabel_SetState(Mabel *mabel, int state);
int Mabel_Update(Mabel *mabel);
int Mabel_ModelName(void);
int Mabel_TextureName(void);
int Mabel_Start(Mabel *mabel);
int Mabel_Init(Mabel *mabel);
void *Mabel_Create(void);

/* Her states (mabel.c). */
int Mabel_UpdateTurnAsk(Mabel *mabel);
int Mabel_EnterTurnAsk(Mabel *mabel);
int Mabel_UpdateSpeaker(void);
void Mabel_EnterSpeaker(Mabel *mabel);
int Mabel_UpdateApproach(Mabel *mabel);
int Mabel_EnterApproach(Mabel *mabel);
int Mabel_UpdatePaused(void);
int Mabel_EnterPaused(void);
int Mabel_UpdateLinkedTurn(Mabel *mabel);
int Mabel_EnterLinkedTurn(Mabel *mabel);
int Mabel_UpdateLinkedStand(Mabel *mabel);
int Mabel_EnterLinkedStand(Mabel *mabel);
int Mabel_UpdateOther(Mabel *mabel);
int Mabel_EnterOther(void);
int Mabel_UpdateAwait(Mabel *mabel);
int Mabel_EnterAwait(void);
int Mabel_UpdateAct(Mabel *mabel);
int Mabel_EnterAct(Mabel *mabel);
int Mabel_UpdateTalked(void);
int Mabel_EnterTalked(void);
int Mabel_UpdateTalkLeave(Mabel *mabel);
int Mabel_EnterTalkLeave(Mabel *mabel);
int Mabel_UpdateTalk(Mabel *mabel);
int Mabel_EnterTalk(Mabel *mabel);
int Mabel_UpdateWalk(Mabel *mabel);
int Mabel_EnterWalk(Mabel *mabel);
int Mabel_UpdateTurn(Mabel *mabel);
int Mabel_EnterTurn(Mabel *mabel);
int Mabel_UpdateStand(Mabel *mabel);
int Mabel_EnterStand(Mabel *mabel);
int Mabel_UpdateGreet(Mabel *mabel);
int Mabel_EnterGreet(Mabel *mabel);

#endif
