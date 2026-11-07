/* A player's bed in the house's attic: a class of overlay 4's room objects (vtable 0x02253058,
 * receiver part 0x02253104, 0x8b8 bytes) of kind 0x37 (RoomObject.unk_00C). Pushed against,
 * it asks whether the player is done for the day (sp_etc_sequence2/4 line 0); talked to, it
 * lets the player swap it for a bed from the pockets (PlayerRecord_SetBed). Its state
 * (BedObject.state), entered through vtable slot 0x70, runs through tables of member pointers
 * (member_pointer.h):
 *
 * - PUSHED (0): while its entry among two (RoomPushes_FindObject of data_ov004_02259784) is in
 *   state 0 or 2 and RoomPushes_Allowed allows it, the player (actor 4) standing nearer one of
 *   its two cells in front, with that cell free and nobody one step ahead of the entry, counts
 *   up to 7 frames; once the entry has moved more than 0x200 the player is sent to the entry's
 *   point (RoomPlayerActor_RequestPlaceApproach);
 * - WATCH (1): entered with the quarter of the room it stands in (BedObject.quarter);
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
 *   answer in mode 1 ends the sequence (0: SEQUENCE_DONE, 6, which also sets the exit of
 *   SceneTables_EntryRecord to scene 0x2e; 1: SEQUENCE_END), otherwise it picks (0: CHOOSE_ITEM, 10; 1: TALK_END, 9);
 * - TALK_NEXT (7) goes on to TALK (8), which takes the receiver named "obj_etc_player" in state
 *   4; TALK_END (9) lets the scene go on once the link closes;
 * - CHOOSE_ITEM (10): once the link closes, opens the pockets (group 9) on the items
 *   BedObject_CanTakeItem accepts; SWAP (11): once group 9 can open again, with an item
 *   chosen (GroupParams_C4CIs1) that item is kept (BedObject.item) and the pockets'
 *   slot gets this object's item instead, else the scene goes on;
 * - PLACE (12) shrinks it away at the cell RoomObject_FindFurnitureCell finds and then places the
 *   kept item there (RoomObjects_Spawn); VANISH (13) waits 22 frames, lets the scene go on and
 *   deletes the object.
 *
 * Kind 0x2a (RoomObject.unk_780) also has a set of three glows: each frame a player (actors 0 to
 * 3, in state 8) standing on one of its cells shows the node set's value 1, runs the glows and
 * the animations and plays sound 0. */
#ifndef CLEAN_OV004_BED_OBJECT_H
#define CLEAN_OV004_BED_OBJECT_H

#include "types.h"

#include "room_object.h"
#include "room_object_parts.h"

typedef struct BedObject {
    RoomObject base;
    u16 push_frames; /* frames pushed, up to 7 */
    u8 left_half;    /* its x is below half of data_020ca0ec */
    u8 front_half;   /* its z is below 0x16000 */
    u8 quarter;      /* 0 to 3: left and front, right and front, left and back, right and back */
    u8 unk_849;
    u16 wait;      /* frames waited in WAIT */
    u16 wait_gone; /* frames waited in VANISH */
    u8 unk_84e[2];
    int cell_x; /* where the kept item is placed (RoomObject_FindFurnitureCell) */
    int cell_y;
    s32 mode; /* BedObjectMode */
    u16 item; /* the item taken from the pockets, 0xfff1 for none */
    u8 state; /* BedObjectState */
    u8 unk_85f;
    GlowSet glows; /* of kind 0x2a */
} BedObject;

enum BedObjectMode { BED_OBJECT_MODE_NONE = 0, BED_OBJECT_MODE_PUSH = 1, BED_OBJECT_MODE_TALK = 2 };

enum BedObjectState {
    BED_OBJECT_PUSHED = 0,
    BED_OBJECT_WATCH = 1,
    BED_OBJECT_MOVE_PLAYER = 2,
    BED_OBJECT_WAIT = 3,
    BED_OBJECT_SEQUENCE = 4,
    BED_OBJECT_SEQUENCE_END = 5,
    BED_OBJECT_SEQUENCE_DONE = 6,
    BED_OBJECT_TALK_NEXT = 7,
    BED_OBJECT_TALK = 8,
    BED_OBJECT_TALK_END = 9,
    BED_OBJECT_CHOOSE_ITEM = 10,
    BED_OBJECT_SWAP = 11,
    BED_OBJECT_PLACE = 12,
    BED_OBJECT_VANISH = 13,
    BED_OBJECT_STATE_COUNT = 14
};

/* What BedObject_CheckStep finds one step ahead. */
enum BedObjectStep {
    BED_OBJECT_STEP_BLOCKED = 0,
    BED_OBJECT_STEP_JOINED = 1, /* itself, or another of its kind joined to it */
    BED_OBJECT_STEP_OPEN = 2    /* an object FurnitureInfo_IndoorBit2 accepts, or nothing at all */
};

void BedObject_OnChoice(BedObject *object);
void BedObject_OnTalkStep(BedObject *object);
void BedObject_OnSceneEvent(BedObject *object, int event);
void BedObject_UpdateVanish(BedObject *object);
int BedObject_EnterVanish(BedObject *object);
void BedObject_UpdatePlace(BedObject *object);
int BedObject_EnterPlace(BedObject *object);
void BedObject_UpdateSwap(BedObject *object);
int BedObject_EnterSwap(BedObject *object);
void BedObject_UpdateChooseItem(BedObject *object);
int BedObject_CanTakeItem(u16 *item, int state);
int BedObject_EnterChooseItem(BedObject *object);
void BedObject_UpdateTalkEnd(BedObject *object);
int BedObject_EnterTalkEnd(BedObject *object);
void BedObject_UpdateTalk(BedObject *object);
int BedObject_EnterTalk(BedObject *object);
void BedObject_UpdateTalkNext(BedObject *object);
int BedObject_EnterTalkNext(BedObject *object);
void BedObject_UpdateSequenceDone(BedObject *object);
int BedObject_EnterSequenceDone(BedObject *object);
void BedObject_UpdateSequenceEnd(BedObject *object);
int BedObject_EnterSequenceEnd(BedObject *object);
void BedObject_UpdateSequence(BedObject *object);
int BedObject_EnterSequence(BedObject *object);
void BedObject_UpdateWait(BedObject *object);
int BedObject_EnterWait(BedObject *object);
void BedObject_UpdateMovePlayer(BedObject *object);
int BedObject_EnterMovePlayer(BedObject *object);
void BedObject_UpdateWatch(BedObject *object);
int BedObject_EnterWatch(BedObject *object);
void BedObject_UpdatePushed(BedObject *object);
int BedObject_CellIsFree(const Cell *cell);
int BedObject_EnterPushed(BedObject *object);
void BedObject_UpdateState(BedObject *object);
int BedObject_EnterState(BedObject *object, unsigned int state, int value);
Cell *BedObject_CellsDestruct(Cell *cells);
Cell *BedObject_CellsConstruct(Cell *cells);
Cell *BedObject_PairDestruct(Cell *cells);
Cell *BedObject_PairConstruct(Cell *cells);
Cell *BedObject_CellAt(Cell *cells, int index);
void BedObject_CellsNothing(void);
Cell *BedObject_CellsClear(Cell *cells);
void BedObject_PointAhead(BedObject *object, Vec3 *out, const Vec3 *point, int angle, const Vec3 *offset);
int BedObject_CheckStep(BedObject *object, Vec3 *point, int angle, Vec3 *offset);
unsigned int BedObject_ListCells(BedObject *object, Cell *cells);
int BedObject_FrontCells(BedObject *object, Cell *cells);
int BedObject_Vfunc0C(void);
int BedObject_Vfunc24(void);
int BedObject_Update(BedObject *object);
int BedObject_Start(BedObject *object);
int BedObject_Vfunc48(BedObject *object);
int BedObject_IsPastPushed(BedObject *object);
BedObject *BedObject_Delete(BedObject *object);
BedObject *BedObject_Destroy(BedObject *object);
BedObject *BedObject_Construct(BedObject *object);
void BedObject_Create(void);
BedObject *BedObjectReceiver_Delete(void *receiver);
void BedObjectReceiver_OnChoice(void *receiver);
void BedObjectReceiver_OnTalkStep(void *receiver);
BedObject *BedObjectReceiver_Destroy(void *receiver);

#endif
