/* A class of overlay 4's room objects (vtable 0x02253058, receiver part 0x02253104, 0x8b8 bytes)
 * of kind 0x37 (RoomObject.unk_00C). Its state (RoomObject02253058.state), entered through
 * vtable slot 0x70, runs through tables of member pointers (member_pointer.h):
 *
 * - PUSHED (0): while its entry among two (RoomPushes_FindObject of data_ov004_02259784) is in
 *   state 0 or 2 and RoomPushes_Allowed allows it, the player (actor 4) standing nearer one of
 *   its two cells in front, with that cell free and nobody one step ahead of the entry, counts
 *   up to 7 frames; once the entry has moved more than 0x200 the player is sent to the entry's
 *   point (RoomPlayerActor_RequestPlaceApproach);
 * - WATCH (1): entered with the quarter of the room it stands in (RoomObject02253058.quarter);
 *   in the quarter of this console's player (PlayerRecords_CurrentNumber), with the entry in state 0 or 2, it
 *   is marked to be pushed (mode 1) and counts up to 7 frames, after which it asks the scene for
 *   an event (EventQueue_RequestKind6) unless the session is linked; with the entry in another state it is
 *   marked for the talk (mode 2) when TownObjects_VisitorsHere is at most 1;
 * - the scene's events (vtable slot 0x4c): 0 and 1 start the push (MOVE_PLAYER) in mode 1, else
 *   the talk (TALK_NEXT); 8 goes back to WATCH;
 * - MOVE_PLAYER (2) sends the player to the entry's point and WAIT (3) waits 24 frames;
 * - SEQUENCE (4) takes the receiver, named "sp_etc_sequence4" (state byte 0x19) when
 *   StartKind_IsNewTown or StartKind_IsNewPlayer says so, else "sp_etc_sequence2" (state byte 0); at 0x19 it
 *   ends (SEQUENCE_END, 5: the player is told RoomPlayerActor_RequestPlaceOff once the link closes);
 * - whenever the receiver's state byte is 0 it offers two choices (messages 0xc and 0xd). The
 *   answer in mode 1 ends the sequence (0: SEQUENCE_DONE, 6, which also queues event 0x2e of
 *   SceneTables_EntryRecord; 1: SEQUENCE_END), otherwise it picks (0: CHOOSE_ITEM, 10; 1: TALK_END, 9);
 * - TALK_NEXT (7) goes on to TALK (8), which takes the receiver named "obj_etc_player" in state
 *   4; TALK_END (9) lets the scene go on once the link closes;
 * - CHOOSE_ITEM (10): once the link closes, opens the pockets (group 9) on the items
 *   RoomObject02253058_CanTakeItem accepts; SWAP (11): once group 9 can open again, with an item
 *   chosen (GroupParams_C4CIs1) that item is kept (RoomObject02253058.item) and the pockets'
 *   slot gets this object's item instead, else the scene goes on;
 * - PLACE (12) shrinks it away at the cell RoomObject_FindVariantCell finds and then places the
 *   kept item there (RoomObjects_Spawn); VANISH (13) waits 22 frames, lets the scene go on and
 *   deletes the object.
 *
 * Kind 0x2a (RoomObject.unk_780) also has a set of three glows: each frame a player (actors 0 to
 * 3, in state 8) standing on one of its cells shows the node set's value 1, runs the glows and
 * the animations and plays sound 0. */
#ifndef CLEAN_OV004_ROOM_OBJECT_02253058_H
#define CLEAN_OV004_ROOM_OBJECT_02253058_H

#include "types.h"

#include "room_object.h"
#include "room_object_parts.h"

typedef struct RoomObject02253058 {
    RoomObject base;
    u16 push_frames; /* frames pushed, up to 7 */
    u8 left_half;    /* its x is below half of data_020ca0ec */
    u8 front_half;   /* its z is below 0x16000 */
    u8 quarter;      /* 0 to 3: left and front, right and front, left and back, right and back */
    u8 unk_849;
    u16 wait;      /* frames waited in WAIT */
    u16 wait_gone; /* frames waited in VANISH */
    u8 unk_84e[2];
    int cell_x; /* where the kept item is placed (RoomObject_FindVariantCell) */
    int cell_y;
    s32 mode; /* RoomObject02253058Mode */
    u16 item; /* the item taken from the pockets, 0xfff1 for none */
    u8 state; /* RoomObject02253058State */
    u8 unk_85f;
    GlowSet glows; /* of kind 0x2a */
} RoomObject02253058;

enum RoomObject02253058Mode {
    ROOM_OBJECT_02253058_MODE_NONE = 0,
    ROOM_OBJECT_02253058_MODE_PUSH = 1,
    ROOM_OBJECT_02253058_MODE_TALK = 2
};

enum RoomObject02253058State {
    ROOM_OBJECT_02253058_PUSHED = 0,
    ROOM_OBJECT_02253058_WATCH = 1,
    ROOM_OBJECT_02253058_MOVE_PLAYER = 2,
    ROOM_OBJECT_02253058_WAIT = 3,
    ROOM_OBJECT_02253058_SEQUENCE = 4,
    ROOM_OBJECT_02253058_SEQUENCE_END = 5,
    ROOM_OBJECT_02253058_SEQUENCE_DONE = 6,
    ROOM_OBJECT_02253058_TALK_NEXT = 7,
    ROOM_OBJECT_02253058_TALK = 8,
    ROOM_OBJECT_02253058_TALK_END = 9,
    ROOM_OBJECT_02253058_CHOOSE_ITEM = 10,
    ROOM_OBJECT_02253058_SWAP = 11,
    ROOM_OBJECT_02253058_PLACE = 12,
    ROOM_OBJECT_02253058_VANISH = 13,
    ROOM_OBJECT_02253058_STATE_COUNT = 14
};

/* What RoomObject02253058_CheckStep finds one step ahead. */
enum RoomObject02253058Step {
    ROOM_OBJECT_02253058_STEP_BLOCKED = 0,
    ROOM_OBJECT_02253058_STEP_JOINED = 1, /* itself, or another of its kind joined to it */
    ROOM_OBJECT_02253058_STEP_OPEN = 2    /* an object FurnitureInfo_IndoorBit2 accepts, or nothing at all */
};

void RoomObject02253058_OnChoice(RoomObject02253058 *object);
void RoomObject02253058_OnTalkStep(RoomObject02253058 *object);
void RoomObject02253058_OnSceneEvent(RoomObject02253058 *object, int event);
void RoomObject02253058_UpdateVanish(RoomObject02253058 *object);
int RoomObject02253058_EnterVanish(RoomObject02253058 *object);
void RoomObject02253058_UpdatePlace(RoomObject02253058 *object);
int RoomObject02253058_EnterPlace(RoomObject02253058 *object);
void RoomObject02253058_UpdateSwap(RoomObject02253058 *object);
int RoomObject02253058_EnterSwap(RoomObject02253058 *object);
void RoomObject02253058_UpdateChooseItem(RoomObject02253058 *object);
int RoomObject02253058_CanTakeItem(u16 *item, int state);
int RoomObject02253058_EnterChooseItem(RoomObject02253058 *object);
void RoomObject02253058_UpdateTalkEnd(RoomObject02253058 *object);
int RoomObject02253058_EnterTalkEnd(RoomObject02253058 *object);
void RoomObject02253058_UpdateTalk(RoomObject02253058 *object);
int RoomObject02253058_EnterTalk(RoomObject02253058 *object);
void RoomObject02253058_UpdateTalkNext(RoomObject02253058 *object);
int RoomObject02253058_EnterTalkNext(RoomObject02253058 *object);
void RoomObject02253058_UpdateSequenceDone(RoomObject02253058 *object);
int RoomObject02253058_EnterSequenceDone(RoomObject02253058 *object);
void RoomObject02253058_UpdateSequenceEnd(RoomObject02253058 *object);
int RoomObject02253058_EnterSequenceEnd(RoomObject02253058 *object);
void RoomObject02253058_UpdateSequence(RoomObject02253058 *object);
int RoomObject02253058_EnterSequence(RoomObject02253058 *object);
void RoomObject02253058_UpdateWait(RoomObject02253058 *object);
int RoomObject02253058_EnterWait(RoomObject02253058 *object);
void RoomObject02253058_UpdateMovePlayer(RoomObject02253058 *object);
int RoomObject02253058_EnterMovePlayer(RoomObject02253058 *object);
void RoomObject02253058_UpdateWatch(RoomObject02253058 *object);
int RoomObject02253058_EnterWatch(RoomObject02253058 *object);
void RoomObject02253058_UpdatePushed(RoomObject02253058 *object);
int RoomObject02253058_CellIsFree(const Cell *cell);
int RoomObject02253058_EnterPushed(RoomObject02253058 *object);
void RoomObject02253058_UpdateState(RoomObject02253058 *object);
int RoomObject02253058_EnterState(RoomObject02253058 *object, unsigned int state, int value);
Cell *RoomObject02253058_CellsDestruct(Cell *cells);
Cell *RoomObject02253058_CellsConstruct(Cell *cells);
Cell *RoomObject02253058_PairDestruct(Cell *cells);
Cell *RoomObject02253058_PairConstruct(Cell *cells);
Cell *RoomObject02253058_CellAt(Cell *cells, int index);
void RoomObject02253058_CellsNothing(void);
Cell *RoomObject02253058_CellsClear(Cell *cells);
void RoomObject02253058_PointAhead(RoomObject02253058 *object, Vec3 *out, const Vec3 *point, int angle, const Vec3 *offset);
int RoomObject02253058_CheckStep(RoomObject02253058 *object, Vec3 *point, int angle, Vec3 *offset);
unsigned int RoomObject02253058_ListCells(RoomObject02253058 *object, Cell *cells);
int RoomObject02253058_FrontCells(RoomObject02253058 *object, Cell *cells);
int RoomObject02253058_Vfunc0C(void);
int RoomObject02253058_Vfunc24(void);
int RoomObject02253058_Update(RoomObject02253058 *object);
int RoomObject02253058_Start(RoomObject02253058 *object);
int RoomObject02253058_Vfunc48(RoomObject02253058 *object);
int RoomObject02253058_IsPastPushed(RoomObject02253058 *object);
RoomObject02253058 *RoomObject02253058_Delete(RoomObject02253058 *object);
RoomObject02253058 *RoomObject02253058_Destroy(RoomObject02253058 *object);
RoomObject02253058 *RoomObject02253058_Construct(RoomObject02253058 *object);
void RoomObject02253058_Create(void);
RoomObject02253058 *RoomObject02253058Receiver_Delete(void *receiver);
void RoomObject02253058Receiver_OnChoice(void *receiver);
void RoomObject02253058Receiver_OnTalkStep(void *receiver);
RoomObject02253058 *RoomObject02253058Receiver_Destroy(void *receiver);

#endif
