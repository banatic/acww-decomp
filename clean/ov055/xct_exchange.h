/* Overlay 55: the special character with the model npc_sp/model/xct who runs the wireless
 * exchange of the town's exchange block (main's exchange_block.h) with another console, through
 * the exchange library of overlay 67 (autoload_2's network.h: Exchange_Init, Exchange_Start). His
 * lines are of "sp_etc_sequence1". Scene 0x30 names overlay 55 in its SceneInfo
 * (data_ov030_02260084, data_020e55bc); his record at 0x02260ed8 (object profile 0x5e, create
 * function XctExchange_Create) is the one main's profile table data_020e3134 points to.
 *
 * He is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * 0x02260fd4, 0x1bc4 bytes. data_ov055_02261080 points to him from his start to his leaving.
 * While he is there the library slot (main's library_overlay.h) holds overlay 67, and overlay 68
 * again once he leaves.
 *
 * On his start the town's exchange block (ExchangeBlock_OfSlot(4)) is moved into the packet he
 * sends (XctExchange.send, kind 1) and cleared in the town, and the exchange block is saved;
 * a failed save is remembered (save_failed) and refuses the exchange.
 * What comes back (XctExchange.received) is put in place by XctExchange_TakeReceived: a letter
 * (kind 2) becomes the letter waiting for the current player (data_021f37f4) and the town gets
 * its own block back; an exchange block (kind 1) replaces the town's, its bottle drifted once
 * more and set to arrive at once. Without an exchange, XctExchange_RestoreBlock puts the town's
 * own block back. His leaving saves the exchange block again (unless a save failed before).
 *
 * His states (XctExchange.state), each an entry and an update function (C++ members taking him)
 * from the table data_ov055_02261084 (filled at start-up by __sinit_ov055_02260db4), set by
 * XctExchange_SetState:
 *   0  wait:   he stands; once the screen's transition shows the scene, he talks (state 1);
 *   1  talk:   he talks (keeping the camera); once his action is idle, main's entry record takes
 *              scene 0x2c (arguments 2, 2) and he is done (state 2);
 *   2  done:   nothing. */
#ifndef CLEAN_OV055_XCT_EXCHANGE_H
#define CLEAN_OV055_XCT_EXCHANGE_H

#include "main/exchange_block.h"
#include "main/scene_base.h"
#include "main/waiting_letter.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct XctExchange;

/* His talk scene (0xb8 bytes): a scene of class 0x020d9ff8 (main's obj_020d9ff8.h) with vtable
 * 0x02260f44 (xct_exchange_talk.h). */
typedef struct XctExchangeTalk {
    SceneBase base;            /* 0x00: the receiver's message (byte 0x1e) is the line shown */
    u8 unk_80[0x30];           /* 0x80: the scene's commands (scene_command.h) */
    struct XctExchange *owner; /* 0xb0 */
    u32 step;                  /* 0xb4: XCT_EXCHANGE_TALK_STEP_*, data_ov055_02260f0c */
} XctExchangeTalk;

/* What the two consoles exchange (0xa58 bytes, Exchange_Init's size): an exchange block, a
 * letter, and which of the two the packet carries. */
typedef struct XctExchangePacket {
    ExchangeBlock block;  /* 0x000 */
    WaitingLetter letter; /* 0x950 */
    u8 kind;              /* 0xa54: XCT_EXCHANGE_CARRIES_* */
    u8 unk_a55[3];
} XctExchangePacket;

/* XctExchangePacket.kind. */
#define XCT_EXCHANGE_CARRIES_BLOCK 1
#define XCT_EXCHANGE_CARRIES_LETTER 2

/* The size of the special character's scene object he derives from, as far as it is used. */
#define XCT_EXCHANGE_BASE_SIZE 0x654

typedef struct XctExchange {
    u8 base[XCT_EXCHANGE_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                       /* 0x654: enum XctExchangeState */
    XctExchangeTalk talk;            /* 0x658 */
    u8 save_failed;                  /* 0x710: a save of the exchange block failed */
    u8 lid_closed;                   /* 0x711: the lid was closed in the talk's last step */
    u8 unk_712[2];                   /* 0x712 */
    XctExchangePacket send;          /* 0x714 */
    XctExchangePacket received;      /* 0x116c */
} XctExchange;

enum XctExchangeState { XCT_EXCHANGE_WAIT = 0, XCT_EXCHANGE_TALK = 1, XCT_EXCHANGE_DONE = 2, XCT_EXCHANGE_STATES = 3 };

/* A state's functions in data_ov055_02261084. */
typedef struct XctExchangeStep {
    MemberPointer enter;  /* 0x00: int (him); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (him) */
} XctExchangeStep;

/* His object. */
XctExchange *XctExchange_Destruct(XctExchange *xct);
XctExchange *XctExchange_DestructDelete(XctExchange *xct);
void XctExchange_LoadLibrary68(void *unused);
void XctExchange_LoadLibrary67(void *unused);
void XctExchange_SaveBlock(XctExchange *xct);
void XctExchange_PrepareSend(XctExchange *xct);
void XctExchange_OnEvent(XctExchange *xct, int code);
int XctExchange_AgreesToOwnEvent(XctExchange *xct);
int XctExchange_AgreesToTalk(XctExchange *xct);
void XctExchange_RestoreBlock(XctExchange *xct);
void XctExchange_TakeReceived(XctExchange *xct);
void XctExchange_SetState(XctExchange *xct, int state);
int XctExchange_Update(XctExchange *xct);
int XctExchange_ModelName(void);
int XctExchange_TextureName(void);
int XctExchange_Leave(XctExchange *xct);
int XctExchange_Start(XctExchange *xct);
int XctExchange_Init(XctExchange *xct);
void *XctExchange_Create(void);

/* His states. */
int XctExchange_EnterWait(XctExchange *xct);
int XctExchange_UpdateWait(XctExchange *xct);
int XctExchange_EnterTalk(XctExchange *xct);
int XctExchange_UpdateTalk(XctExchange *xct);
int XctExchange_EnterDone(void);
int XctExchange_UpdateDone(void);

#endif
