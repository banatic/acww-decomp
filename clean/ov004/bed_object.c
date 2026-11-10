/* The beds of the house's attic: the room objects of vtable 0x02253058 (bed_object.h).
 *
 * REQUIRES: the object at a word-aligned address, as every object the room's heap gives is;
 * the ROM reads and writes its 16-bit fields with halfword accesses, which at an odd address
 * the DS's ARM9 aligns down. */
#include "bed_object.h"

#include <stdint.h>

#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "cells.h"
#include "clean.h"
#include "main/group_params.h"
#include "main/pockets.h"
#include "main/session.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_map.h"
#include "room_object_methods.h"
#include "room_object_parts.h"
#include "ov004/room_player_actor.h"
#include "main/acre_tile.h"
#include "main/activity_job.h"
#include "main/actor_table.h"
#include "main/collision_map.h"
#include "main/current_pockets.h"
#include "main/event_queue.h"
#include "main/furniture_info.h"
#include "main/item_code.h"
#include "main/message_receiver.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_exit.h"
#include "main/scene_kinds.h"
#include "main/scene_object_base.h"
#include "main/scene_tables.h"
#include "main/session_players.h"
#include "main/start_kind.h"
#include "main/talk_answers.h"
#include "main/talk_object.h"
#include "main/town_objects.h"
#include "room_objects.h"
#include "room_pushes.h"

static_assert(offsetof(RoomObject, unk_00c) == 0xc, "kind");
static_assert(offsetof(RoomObject, position) == 0x5c, "position");
static_assert(offsetof(RoomObject, angle) == 0x8e, "angle");
static_assert(offsetof(RoomObject, receiver_state) == 0x10a, "receiver state byte");
static_assert(offsetof(RoomObject, link) == 0x12c, "link");
static_assert(offsetof(RoomObject, unk_784) == 0x784, "unk_784");
static_assert(offsetof(BedObject, push_frames) == 0x844, "push frames");
static_assert(offsetof(BedObject, quarter) == 0x848, "quarter");
static_assert(offsetof(BedObject, wait) == 0x84a, "wait");
static_assert(offsetof(BedObject, wait_gone) == 0x84c, "wait gone");
static_assert(offsetof(BedObject, cell_x) == 0x850, "cell");
static_assert(offsetof(BedObject, mode) == 0x858, "mode");
static_assert(offsetof(BedObject, item) == 0x85c, "item");
static_assert(offsetof(BedObject, state) == 0x85e, "state");
static_assert(offsetof(BedObject, glows) == 0x860, "glows");
static_assert(sizeof(BedObject) == 0x8b8, "the size BedObject_Create allocates");

#define RECEIVER_OFFSET 0xec
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */
#define PLAYER_COUNT 4     /* the actors RoomPlayerActor_PointAtPlace is asked for */
#define PUSH_FRAMES 7      /* frames of pushing before it counts */
#define MOVED_ENOUGH 0x200 /* how far the entry must have moved (RoomPushes_Moved) */
#define WAIT_FRAMES 0x18
#define VANISH_FRAMES 0x16
#define KIND_2A 0x2a       /* RoomObject.unk_780 of the kind with glows */
#define KIND_BED 0x37      /* RoomObject.unk_00c of this class */
#define LONG_SHAPE 2       /* RoomObject.unk_784 of the shape two cells wide */
#define BACK_Z 0x16000     /* the z from which on it is in the back of the room */
#define STEP 0x2000        /* one cell, 20.12 fixed point */
#define HALF_STEP 0x1000   /* BedObject_PointAhead's step */
#define PLAYER_REACH 0x800 /* what Actors_NoneNear is given */
#define NPC_REACH 0x2000
#define PLAYER_RADIUS 0x800
#define NO_ITEM_KIND_SLOT 0 /* the pockets' slot state BedObject_CanTakeItem accepts */
#define ITEM_CATEGORY 5     /* what FurnitureInfo_ItemCategory says of the items it accepts */
#define ITEM_PLACE_SIDE 3   /* the side the kept item is placed facing */
#define ITEM_PLACE_MODE 1
#define POCKETS_ARG 0x28 /* what GroupParams_OpenWithMask is given */
#define CHOICE_FIRST 0xc /* the messages of the two choices */
#define CHOICE_SECOND 0xd
#define SEQUENCE_4 0x19 /* the receiver's state byte with "sp_etc_sequence4" */
#define TALK_STATE 4    /* the receiver's state byte with "obj_etc_player" */
#define DONE_SCENE 0x2e /* the entry record's exit set to it when the sequence is done */
#define DONE_CHANGE_ARG 2
#define BED_OBJECT_SIZE 0x8b8

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02253058[];
extern const u8 data_ov004_02253104[];

/* The receiver's names: "obj_etc_player", "sp_etc_sequence4" and "sp_etc_sequence2". */
extern const char data_ov004_022531f0[];
extern const char data_ov004_02253210[];
extern const char data_ov004_02253224[];

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02257064;
extern MemberPointer data_ov004_0225773c[BED_OBJECT_STATE_COUNT];
extern const MemberPointer data_ov004_022500d0, data_ov004_022500e0, data_ov004_02250118, data_ov004_022500a8,
    data_ov004_022500c8, data_ov004_02250138, data_ov004_022504c0, data_ov004_022504f8, data_ov004_02250360,
    data_ov004_02250508, data_ov004_02250510, data_ov004_02250518, data_ov004_022502e8, data_ov004_02250368;
extern u32 data_ov004_02257070;
extern MemberPointer data_ov004_022576cc[BED_OBJECT_STATE_COUNT];
extern const MemberPointer data_ov004_02250058, data_ov004_02250090, data_ov004_02250110, data_ov004_02250398,
    data_ov004_02250590, data_ov004_022503f0, data_ov004_02250358, data_ov004_022502f0, data_ov004_02250660,
    data_ov004_02250180, data_ov004_02250210, data_ov004_02250418, data_ov004_022502c8, data_ov004_02250440;

/* The points, in the object's space, of its cells (for each RoomObject.unk_784) and of the
 * two cells in front of it (NULL for none). */
typedef struct BedObjectShape {
    const Vec3 *points;
    u32 count;
} BedObjectShape;
extern const BedObjectShape data_ov004_022476b0[];
extern const Vec3 *const data_ov004_02250668[];

/* The players: actor 4 (SessionPlayers_ActorOf), this console's player's number (PlayerRecords_CurrentNumber) and
 * record (PlayerRecords_Current). */
extern NetSession *data_020ccf94;
/* The width the room's halves are taken from. */
extern s32 data_020ca0ec;

/* The scene's map: a cell's point and a point's cell, whether a cell holds something
 * (RoomObjects_HeightAtCell, CollisionMap_UnclaimedObjectAt gives -1 for nothing), the same for the cell of a point,
 * and the grid of the room's objects. */
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);

/* The conversation: its choices (at 0x31c), the one taken, and its message. */
extern u8 data_021f43e8;

/* BedObject_CanTakeItem by the game's symbol, the predicate the pockets are given. */
extern int func_ov004_02217bb0(u16 *item, int state);

/* The receiver part as C++ converts a pointer to the object to it: NULL stays NULL. */
static void *receiver_of(BedObject *object)
{
    return object != NULL ? (u8 *) object + RECEIVER_OFFSET : NULL;
}

/* Vtable slot 0x70 (BedObject_EnterState): enters `state`. */
static void switch_to(BedObject *object, int state)
{
    object->base.vtable->vfunc_70(&object->base, state, SLOT_70_VALUE);
}

static void *entry_of(BedObject *object)
{
    return RoomPushes_FindObject(RoomPushes_Records(), &object->base);
}

/* Whether the entry is in state 2 or 0. */
static int entry_ready(void *entry)
{
    return RoomPushes_Side(entry) == 2 || RoomPushes_Side(entry) == 0;
}

/* The angle the player faces it with. */
static s16 facing(BedObject *object)
{
    return (s16) (object->base.angle - 0x4000);
}

/* Whether the link the receiver is attached to is there and closed. */
static int link_closed(BedObject *object)
{
    return object->base.link != NULL && object->base.link->state == 0;
}

/* Hands the receiver back and lets the scene go on. */
static void end_talk(BedObject *object)
{
    SceneObjectBase_ReleaseReceiver(&object->base.scene, receiver_of(object));
    EventQueue_FinishObjectEvent(object);
}

/* Takes the receiver, raises the link's request and names the receiver.
 * REQUIRES: the receiver has a link once SceneObjectBase_TakeReceiver has taken it. */
static void take_receiver(BedObject *object, const char *name)
{
    SceneObjectBase_TakeReceiver(&object->base.scene, receiver_of(object));
    object->base.link->next_state = 1;
    MessageReceiver_SetName(&object->base.receiver.base, name);
}

/* An arithmetic shift right, for negative values too. */
static s32 shift_right(s32 value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* func_ov004_02217864 (the receiver's slot 0x18, after the player chose in the conversation):
 * in mode 1 the first choice ends the sequence done (with message data_021f43e8) and the second
 * ends it; otherwise the first chooses an item and the second ends the talk, both with the
 * message. Other answers do nothing. */
void BedObject_OnChoice(BedObject *object)
{
    unsigned int choice = TalkAnswers_Picked(TalkObject_Answers(object->base.link));
    if (object->mode == BED_OBJECT_MODE_PUSH) {
        switch (choice) {
            case 0:
                TalkObject_SetMessage(object->base.link, &data_021f43e8, NULL);
                switch_to(object, BED_OBJECT_SEQUENCE_DONE);
                break;
            case 1:
                switch_to(object, BED_OBJECT_SEQUENCE_END);
                break;
        }
    } else {
        switch (choice) {
            case 0:
                TalkObject_SetMessage(object->base.link, &data_021f43e8, NULL);
                switch_to(object, BED_OBJECT_CHOOSE_ITEM);
                break;
            case 1:
                TalkObject_SetMessage(object->base.link, &data_021f43e8, NULL);
                switch_to(object, BED_OBJECT_TALK_END);
                break;
        }
    }
}
CLEAN_AS(func_ov004_02217864, BedObject_OnChoice)

/* func_ov004_022178fc (the receiver's slot 0x14): at state byte 0 the conversation offers two
 * choices (messages 0xc and 0xd, each with message data_021f43e8 as it is then) and shows them;
 * at state byte 0x19 the sequence ends. */
void BedObject_OnTalkStep(BedObject *object)
{
    if (object->base.receiver_state == 0) {
        void *talk = object->base.link;
        void *choices = TalkObject_Answers(talk);
        TalkAnswers_Reset(choices, 2, 1);
        u8 first[2] = {CHOICE_FIRST, data_021f43e8};
        TalkAnswers_Set(choices, 0, &first[0], 1, &first[1], 0, 2);
        u8 second[2] = {CHOICE_SECOND, data_021f43e8};
        TalkAnswers_Set(choices, 1, &second[0], 1, &second[1], 0, 0);
        TalkAnswers_LoadTexts(choices);
        TalkObject_OpenChoices(talk, 1);
    }
    if (object->base.receiver_state == SEQUENCE_4) {
        switch_to(object, BED_OBJECT_SEQUENCE_END);
    }
}
CLEAN_AS(func_ov004_022178fc, BedObject_OnTalkStep)

/* func_ov004_022179a0 (vtable slot 0x4c): the scene's answer to EventQueue_RequestKind6. Events 0 and 1
 * move the player in mode 1, else start the talk; event 8 watches again; others do nothing. */
void BedObject_OnSceneEvent(BedObject *object, int event)
{
    switch (event) {
        case 0:
        case 1:
            if (object->mode == BED_OBJECT_MODE_PUSH) {
                switch_to(object, BED_OBJECT_MOVE_PLAYER);
            } else {
                switch_to(object, BED_OBJECT_TALK_NEXT);
            }
            break;
        case 8:
            switch_to(object, BED_OBJECT_WATCH);
            break;
    }
}
CLEAN_AS(func_ov004_022179a0, BedObject_OnSceneEvent)

/* func_ov004_022179e8 (update of VANISH): after 22 frames hands the receiver back, lets the
 * scene go on and asks for the object's deletion. The count stays at 22, so this repeats each
 * frame until it is gone. */
void BedObject_UpdateVanish(BedObject *object)
{
    if (object->wait_gone < VANISH_FRAMES) {
        object->wait_gone++;
    }
    if (object->wait_gone == VANISH_FRAMES) {
        end_talk(object);
        Process_RequestDelete((Process *) (void *) object);
    }
}
CLEAN_AS(func_ov004_022179e8, BedObject_UpdateVanish)

/* func_ov004_02217a28 (entry of VANISH) */
int BedObject_EnterVanish(BedObject *object)
{
    object->wait_gone = 0;
    return 1;
}
CLEAN_AS(func_ov004_02217a28, BedObject_EnterVanish)

/* func_ov004_02217a38 (update of PLACE): once shrunk away, places the kept item at its cell
 * facing side 3 (a cell to the right for the two-cell shape on the left half, a cell back to the
 * left for an item FurnitureInfo_ItemShape tells 2 of on the left half); vanishes once RoomObjects_Spawn
 * has placed it. */
void BedObject_UpdatePlace(BedObject *object)
{
    if (RoomObject_IsShrunk(&object->base) == 0) {
        return;
    }
    int x = object->cell_x;
    int y = object->cell_y;
    if (object->base.unk_784 == LONG_SHAPE && object->left_half != 0) {
        x++;
    }
    int kind = FurnitureInfo_ItemShape(&object->item);
    if (object->left_half != 0 && kind == 2) {
        x--;
    }
    int number = ItemCode_FurnitureNumber(&object->item);
    if (RoomObjects_Spawn(Placement_Make(x, y, number, ITEM_PLACE_SIDE, 0, ITEM_PLACE_MODE)) != 0) {
        switch_to(object, BED_OBJECT_VANISH);
    }
}
CLEAN_AS(func_ov004_02217a38, BedObject_UpdatePlace)

/* func_ov004_02217ac4 (entry of PLACE): the cell for the item (RoomObject_FindFurnitureCell, its
 * answer dropped), then it shrinks away. */
int BedObject_EnterPlace(BedObject *object)
{
    RoomObject_FindFurnitureCell(&object->base, &object->cell_x, &object->cell_y, NULL, 0);
    RoomObject_Shrink(&object->base);
    return 1;
}
CLEAN_AS(func_ov004_02217ac4, BedObject_EnterPlace)

/* func_ov004_02217af4 (update of SWAP): once group 9 can open again, without an item chosen it
 * ends the talk; with one, keeps the item of the chosen slot (and gives it to the player's
 * record), puts this object's item code in that slot and places the kept item. */
void BedObject_UpdateSwap(BedObject *object)
{
    if (!GroupParams_CanOpen()) {
        return;
    }
    if (!GroupParams_C4CIs1()) {
        end_talk(object);
        return;
    }
    int slot = GroupParams_Arg();
    object->item = CurrentPockets_Item((unsigned int) slot);
    void *record = PlayerRecords_Current();
    if (record != NULL) {
        PlayerRecord_SetBed(record, &object->item);
    }
    u16 code = ItemCode_MakeFurniture(RoomObject_Number(&object->base), 0);
    CurrentPockets_Set(&code, 0, slot);
    switch_to(object, BED_OBJECT_PLACE);
}
CLEAN_AS(func_ov004_02217af4, BedObject_UpdateSwap)

/* func_ov004_02217b70 (entry of SWAP) */
int BedObject_EnterSwap(BedObject *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov004_02217b70, BedObject_EnterSwap)

/* func_ov004_02217b74 (update of CHOOSE_ITEM): once the link has closed, opens the pockets on
 * the slots BedObject_CanTakeItem accepts; swaps once they are open. */
void BedObject_UpdateChooseItem(BedObject *object)
{
    if (link_closed(object) && GroupParams_OpenWithMask(Pockets_Select(func_ov004_02217bb0), POCKETS_ARG) != 0) {
        switch_to(object, BED_OBJECT_SWAP);
    }
}
CLEAN_AS(func_ov004_02217b74, BedObject_UpdateChooseItem)

/* func_ov004_02217bb0: whether a pockets' slot may be chosen: in state 0, holding an item
 * ItemCode_IsFurniture tells that FurnitureInfo_ItemCategory puts in category 5. */
int BedObject_CanTakeItem(u16 *item, int state)
{
    return state == NO_ITEM_KIND_SLOT && ItemCode_IsFurniture(item) != 0 && FurnitureInfo_ItemCategory(item) == ITEM_CATEGORY;
}
CLEAN_AS(func_ov004_02217bb0, BedObject_CanTakeItem)

/* func_ov004_02217bd8 (entry of CHOOSE_ITEM) */
int BedObject_EnterChooseItem(BedObject *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov004_02217bd8, BedObject_EnterChooseItem)

/* func_ov004_02217bdc (update of TALK_END): ends the talk once the link has closed. */
void BedObject_UpdateTalkEnd(BedObject *object)
{
    if (link_closed(object)) {
        end_talk(object);
    }
}
CLEAN_AS(func_ov004_02217bdc, BedObject_UpdateTalkEnd)

/* func_ov004_02217c0c (entry of TALK_END) */
int BedObject_EnterTalkEnd(BedObject *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov004_02217c0c, BedObject_EnterTalkEnd)

/* func_ov004_02217c10 (update of TALK): the receiver leads. */
void BedObject_UpdateTalk(BedObject *object)
{
    (void) object;
}
CLEAN_AS(func_ov004_02217c10, BedObject_UpdateTalk)

/* func_ov004_02217c14 (entry of TALK): takes the receiver, named "obj_etc_player", in state 4. */
int BedObject_EnterTalk(BedObject *object)
{
    take_receiver(object, data_ov004_022531f0);
    object->base.receiver_state = TALK_STATE;
    return 1;
}
CLEAN_AS(func_ov004_02217c14, BedObject_EnterTalk)

/* func_ov004_02217c58 (update of TALK_NEXT) */
void BedObject_UpdateTalkNext(BedObject *object)
{
    switch_to(object, BED_OBJECT_TALK);
}
CLEAN_AS(func_ov004_02217c58, BedObject_UpdateTalkNext)

/* func_ov004_02217c6c (entry of TALK_NEXT) */
int BedObject_EnterTalkNext(BedObject *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov004_02217c6c, BedObject_EnterTalkNext)

/* func_ov004_02217c70 (update of SEQUENCE_DONE): once the link has closed, ends the talk, sets
 * the entry record's exit to scene 0x2e (SceneExit_SetToScene, change arg 2) and sets the flag of ActivityJob_Ask1. */
void BedObject_UpdateSequenceDone(BedObject *object)
{
    if (link_closed(object)) {
        end_talk(object);
        SceneExit_SetToScene((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), DONE_SCENE, DONE_CHANGE_ARG, 0);
        ActivityJob_Ask1();
    }
}
CLEAN_AS(func_ov004_02217c70, BedObject_UpdateSequenceDone)

/* func_ov004_02217cb4 (entry of SEQUENCE_DONE) */
int BedObject_EnterSequenceDone(BedObject *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov004_02217cb4, BedObject_EnterSequenceDone)

/* func_ov004_02217cb8 (update of SEQUENCE_END): once the link has closed, tells the player the
 * half it stands in (RoomPlayerActor_RequestPlaceOff) and ends the talk. */
void BedObject_UpdateSequenceEnd(BedObject *object)
{
    if (link_closed(object)) {
        RoomPlayerActor_RequestPlaceOff(object->left_half, 0);
        end_talk(object);
    }
}
CLEAN_AS(func_ov004_02217cb8, BedObject_UpdateSequenceEnd)

/* func_ov004_02217cf8 (entry of SEQUENCE_END) */
int BedObject_EnterSequenceEnd(BedObject *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov004_02217cf8, BedObject_EnterSequenceEnd)

/* func_ov004_02217cfc (update of SEQUENCE): the receiver leads. */
void BedObject_UpdateSequence(BedObject *object)
{
    (void) object;
}
CLEAN_AS(func_ov004_02217cfc, BedObject_UpdateSequence)

/* func_ov004_02217d00 (entry of SEQUENCE): takes the receiver, named "sp_etc_sequence4" in state
 * 0x19 when StartKind_IsNewTown or StartKind_IsNewPlayer says so, else "sp_etc_sequence2" in state 0. */
int BedObject_EnterSequence(BedObject *object)
{
    SceneObjectBase_TakeReceiver(&object->base.scene, receiver_of(object));
    object->base.link->next_state = 1;
    if (StartKind_IsNewTown() != 0 || StartKind_IsNewPlayer() != 0) {
        MessageReceiver_SetName(&object->base.receiver.base, data_ov004_02253210);
        object->base.receiver_state = SEQUENCE_4;
    } else {
        MessageReceiver_SetName(&object->base.receiver.base, data_ov004_02253224);
        object->base.receiver_state = 0;
    }
    return 1;
}
CLEAN_AS(func_ov004_02217d00, BedObject_EnterSequence)

/* func_ov004_02217d68 (update of WAIT): the sequence after 24 frames. */
void BedObject_UpdateWait(BedObject *object)
{
    if (object->wait < WAIT_FRAMES) {
        object->wait++;
    }
    if (object->wait == WAIT_FRAMES) {
        switch_to(object, BED_OBJECT_SEQUENCE);
    }
}
CLEAN_AS(func_ov004_02217d68, BedObject_UpdateWait)

/* func_ov004_02217d98 (entry of WAIT) */
int BedObject_EnterWait(BedObject *object)
{
    object->wait = 0;
    return 1;
}
CLEAN_AS(func_ov004_02217d98, BedObject_EnterWait)

/* func_ov004_02217da8 (update of MOVE_PLAYER): sends the player to the entry's point with the
 * entry's angle, facing the object; waits once the player goes.
 * BUG: without an entry for the object, RoomPushes_Facing and RoomPushes_Center are handed
 * NULL and the point is read from near address 0; kept. */
void BedObject_UpdateMovePlayer(BedObject *object)
{
    void *entry = entry_of(object);
    s16 angle = (s16) RoomPushes_Facing(entry);
    Vec3 *point = RoomPushes_Center(entry);
    if (RoomPlayerActor_RequestPlaceApproach(&point->x, &RoomPushes_Center(entry)->z, &angle, facing(object), 1) != 0) {
        switch_to(object, BED_OBJECT_WAIT);
    }
}
CLEAN_AS(func_ov004_02217da8, BedObject_UpdateMovePlayer)

/* func_ov004_02217e08 (entry of MOVE_PLAYER) */
int BedObject_EnterMovePlayer(BedObject *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov004_02217e08, BedObject_EnterMovePlayer)

/* func_ov004_02217e0c (update of WATCH): with an entry, in the quarter of this console's player:
 * with the entry in state 0 or 2 it is pushed (mode 1), counts up to 7 frames and, once the
 * entry has moved more than 0x200 after those, asks the scene for an event unless the session
 * is linked; with the entry in another state it is for talking (mode 2) when TownObjects_VisitorsHere is at
 * most 1. The count restarts on any frame it did not go up. */
void BedObject_UpdateWatch(BedObject *object)
{
    int counted = 0;
    object->mode = BED_OBJECT_MODE_NONE;
    void *entry = entry_of(object);
    if (entry != NULL && (int) object->quarter == PlayerRecords_CurrentNumber()) {
        if (entry_ready(entry)) {
            object->mode = BED_OBJECT_MODE_PUSH;
            if (object->push_frames < PUSH_FRAMES) {
                counted = 1;
                object->push_frames++;
            }
            if (RoomPushes_Moved(entry) > MOVED_ENOUGH && object->push_frames >= PUSH_FRAMES &&
                Session_IsLinked(data_020ccf94) == 0) {
                EventQueue_RequestKind6(object, 0);
            }
        } else if ((unsigned int) TownObjects_VisitorsHere() <= 1) {
            object->mode = BED_OBJECT_MODE_TALK;
        }
    }
    if (!counted) {
        object->push_frames = 0;
    }
}
CLEAN_AS(func_ov004_02217e0c, BedObject_UpdateWatch)

/* func_ov004_02217eb8 (entry of WATCH): the quarter of the room it stands in, by its x against
 * half of data_020ca0ec and its z against 0x16000. */
int BedObject_EnterWatch(BedObject *object)
{
    object->left_half = object->base.position.x < shift_right(data_020ca0ec, 1) ? 1 : 0;
    object->front_half = object->base.position.z < BACK_Z ? 1 : 0;
    if (object->left_half != 0) {
        object->quarter = object->front_half != 0 ? 0 : 2;
    } else {
        object->quarter = object->front_half != 0 ? 1 : 3;
    }
    return 1;
}
CLEAN_AS(func_ov004_02217eb8, BedObject_EnterWatch)

/* func_ov004_02217f2c (update of PUSHED): with an entry in state 0 or 2, the player there and
 * RoomPushes_Allowed allowing it, the one of its two front cells nearer the player (the second
 * when as near); when that cell is free and nobody is one cell ahead of the entry (along its
 * angle) it counts up to 7 frames, and once the entry has moved more than 0x200 after those it
 * sends the player to the entry's point and counts again. The count restarts on any frame it
 * did not go up. */
void BedObject_UpdatePushed(BedObject *object)
{
    int counted = 0;
    void *entry = entry_of(object);
    MapActor *player = SessionPlayers_ActorOf(SESSION_PLAYERS_OWN);
    if (entry != NULL && player != NULL && RoomPushes_Allowed() != 0 && entry_ready(entry)) {
        Cell cells[2];
        BedObject_PairConstruct(cells);
        BedObject_FrontCells(object, cells);
        Vec3 first;
        Vec3 second;
        Cell *cell = BedObject_CellAt(cells, 0);
        AcreTile_TileCenter(&first, cell->x, cell->y);
        cell = BedObject_CellAt(cells, 1);
        AcreTile_TileCenter(&second, cell->x, cell->y);
        Vec3 at = player->position;
        fx32 to_first = Vec_DistanceXZ(&at, &first);
        fx32 to_second = Vec_DistanceXZ(&at, &second);
        Cell chosen = *BedObject_CellAt(cells, to_first < to_second ? 0 : 1);
        if (BedObject_CellIsFree(&chosen)) {
            Vec3 ahead = {0, 0, STEP};
            Vec_RotateY(&ahead, RoomPushes_Facing(entry));
            fx32 z = ahead.z + RoomPushes_Center(entry)->z;
            Vec3 probe = {ahead.x + RoomPushes_Center(entry)->x, 0, z};
            if (Actors_NoneNear(&probe, PLAYER_REACH, NPC_REACH, PLAYER_RADIUS, 0)) {
                if (object->push_frames < PUSH_FRAMES) {
                    counted = 1;
                    object->push_frames++;
                }
                if (RoomPushes_Moved(entry) > MOVED_ENOUGH && object->push_frames >= PUSH_FRAMES) {
                    s16 angle = (s16) RoomPushes_Facing(entry);
                    Vec3 *point = RoomPushes_Center(entry);
                    RoomPlayerActor_RequestPlaceApproach(&point->x, &RoomPushes_Center(entry)->z, &angle, facing(object), 0);
                    object->push_frames = 0;
                }
            }
        }
        BedObject_PairDestruct(cells);
    }
    if (!counted) {
        object->push_frames = 0;
    }
}
CLEAN_AS(func_ov004_02217f2c, BedObject_UpdatePushed)

/* func_ov004_022180d4: whether a cell holds nothing. */
int BedObject_CellIsFree(const Cell *cell)
{
    return RoomObjects_HeightAtCell(cell->x, cell->y) == 0 && CollisionMap_UnclaimedObjectAt(cell->x, cell->y) == -1;
}
CLEAN_AS(func_ov004_022180d4, BedObject_CellIsFree)

/* func_ov004_02218100 (entry of PUSHED) */
int BedObject_EnterPushed(BedObject *object)
{
    object->push_frames = 0;
    return 1;
}
CLEAN_AS(func_ov004_02218100, BedObject_EnterPushed)

/* _ZN18Obj_ov004_0225305819func_ov004_02218110Ev: the state's update, through its table. */
void BedObject_UpdateState(BedObject *object)
{
    static const MemberPointer *const updates[BED_OBJECT_STATE_COUNT] = {
        &data_ov004_022500d0, /* BedObject_UpdatePushed */
        &data_ov004_022500e0, /* BedObject_UpdateWatch */
        &data_ov004_02250118, /* BedObject_UpdateMovePlayer */
        &data_ov004_022500a8, /* BedObject_UpdateWait */
        &data_ov004_022500c8, /* BedObject_UpdateSequence */
        &data_ov004_02250138, /* BedObject_UpdateSequenceEnd */
        &data_ov004_022504c0, /* BedObject_UpdateSequenceDone */
        &data_ov004_022504f8, /* BedObject_UpdateTalkNext */
        &data_ov004_02250360, /* BedObject_UpdateTalk */
        &data_ov004_02250508, /* BedObject_UpdateTalkEnd */
        &data_ov004_02250510, /* BedObject_UpdateChooseItem */
        &data_ov004_02250518, /* BedObject_UpdateSwap */
        &data_ov004_022502e8, /* BedObject_UpdatePlace */
        &data_ov004_02250368, /* BedObject_UpdateVanish */
    };
    MemberTable_InitOnce(&data_ov004_02257064, data_ov004_0225773c, updates, BED_OBJECT_STATE_COUNT);
    if (object->state < BED_OBJECT_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_0225773c[object->state], object);
    }
}
CLEAN_AS(_ZN18Obj_ov004_0225305819func_ov004_02218110Ev, BedObject_UpdateState)

/* func_ov004_02218228 (vtable slot 0x70): the base class's (RoomObject_SetUnk77c, given `state`
 * and `value`), then enters `state` if its entry (through a table) agrees; whether it did.
 * States 14 and above do not exist. */
int BedObject_EnterState(BedObject *object, unsigned int state, int value)
{
    static const MemberPointer *const entries[BED_OBJECT_STATE_COUNT] = {
        &data_ov004_02250058, /* BedObject_EnterPushed */
        &data_ov004_02250090, /* BedObject_EnterWatch */
        &data_ov004_02250110, /* BedObject_EnterMovePlayer */
        &data_ov004_02250398, /* BedObject_EnterWait */
        &data_ov004_02250590, /* BedObject_EnterSequence */
        &data_ov004_022503f0, /* BedObject_EnterSequenceEnd */
        &data_ov004_02250358, /* BedObject_EnterSequenceDone */
        &data_ov004_022502f0, /* BedObject_EnterTalkNext */
        &data_ov004_02250660, /* BedObject_EnterTalk */
        &data_ov004_02250180, /* BedObject_EnterTalkEnd */
        &data_ov004_02250210, /* BedObject_EnterChooseItem */
        &data_ov004_02250418, /* BedObject_EnterSwap */
        &data_ov004_022502c8, /* BedObject_EnterPlace */
        &data_ov004_02250440, /* BedObject_EnterVanish */
    };
    RoomObject_SetUnk77c(&object->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_02257070, data_ov004_022576cc, entries, BED_OBJECT_STATE_COUNT);
    if (state < BED_OBJECT_STATE_COUNT && MemberPointer_CallInt(&data_ov004_022576cc[state], object) != 0) {
        object->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02218228, BedObject_EnterState)

/* The two kinds of local pairs of cells the functions below use: each is cleared when built
 * (BedObject_CellsClear) and needs nothing to be taken down. */

/* func_ov004_02218354 */
Cell *BedObject_CellsDestruct(Cell *cells)
{
    BedObject_CellsNothing();
    return cells;
}
CLEAN_AS(func_ov004_02218354, BedObject_CellsDestruct)

/* func_ov004_02218364 */
Cell *BedObject_CellsConstruct(Cell *cells)
{
    BedObject_CellsClear(cells);
    return cells;
}
CLEAN_AS(func_ov004_02218364, BedObject_CellsConstruct)

/* func_ov004_02218374 */
Cell *BedObject_PairDestruct(Cell *cells)
{
    BedObject_CellsNothing();
    return cells;
}
CLEAN_AS(func_ov004_02218374, BedObject_PairDestruct)

/* func_ov004_02218384 */
Cell *BedObject_PairConstruct(Cell *cells)
{
    BedObject_CellsClear(cells);
    return cells;
}
CLEAN_AS(func_ov004_02218384, BedObject_PairConstruct)

/* func_ov004_02218394: cell `index` of a pair (only its lowest bit counts). */
Cell *BedObject_CellAt(Cell *cells, int index)
{
    return &cells[index & 1];
}
CLEAN_AS(func_ov004_02218394, BedObject_CellAt)

/* func_ov004_022183a0 */
void BedObject_CellsNothing(void) {}
CLEAN_AS(func_ov004_022183a0, BedObject_CellsNothing)

/* func_ov004_022183a4: both cells of a pair at (0, 0). */
Cell *BedObject_CellsClear(Cell *cells)
{
    for (int i = 0; i < 2; i++) {
        cells[i].x = 0;
        cells[i].y = 0;
    }
    return cells;
}
CLEAN_AS(func_ov004_022183a4, BedObject_CellsClear)

/* func_ov004_022183b8: `point` plus `offset` (none when NULL) moved half a cell forward and
 * turned by `angle`. `object` is not used. */
void BedObject_PointAhead(BedObject *object, Vec3 *out, const Vec3 *point, int angle, const Vec3 *offset)
{
    (void) object;
    *out = *point;
    Vec3 base = {0, 0, 0};
    if (offset != NULL) {
        base = *offset;
    }
    Vec3 step = {base.x, base.y, base.z + HALF_STEP};
    Vec_RotateY(&step, angle);
    VEC_Add(out, &step, out);
}
CLEAN_AS(func_ov004_022183b8, BedObject_PointAhead)

/* func_ov004_02218414 (RoomObjects_CheckStep asks it of an object of this kind): what is half a
 * cell ahead of `point` along `angle` (BedObject_PointAhead): blocked when someone is
 * near; else the object of the room on that cell: itself (joined), one FurnitureInfo_IndoorBit2 accepts by
 * its number (open), or one of this kind facing the same way with a cell next to one of this
 * object's (joined); with no object there, open when the cell holds nothing. */
int BedObject_CheckStep(BedObject *object, Vec3 *point, int angle, Vec3 *offset)
{
    Vec3 moved;
    int x;
    int y;
    BedObject_PointAhead(object, &moved, point, angle, offset);
    Position_Tile(&x, &y, (const Position *) (const void *) &moved);
    RoomObject *other = RoomObjects_GridObjectAt(RoomObjects_Grid(), x, y, 0);
    if (!Actors_NoneNear(&moved, PLAYER_REACH, NPC_REACH, PLAYER_RADIUS, 0)) {
        return BED_OBJECT_STEP_BLOCKED;
    }
    if (other == NULL) {
        if (RoomObjects_HeightAtPoint(&moved) == 0 && CollisionMap_UnclaimedObjectAtPoint(&moved) == -1) {
            return BED_OBJECT_STEP_OPEN;
        }
        return BED_OBJECT_STEP_BLOCKED;
    }
    if (other == &object->base) {
        return BED_OBJECT_STEP_JOINED;
    }
    if (FurnitureInfo_IndoorBit2(RoomObject_Number(other)) != 0) {
        return BED_OBJECT_STEP_OPEN;
    }
    if (object->base.angle == other->angle && other->unk_00c == KIND_BED) {
        Cell mine[2];
        Cell theirs[2];
        BedObject_CellsConstruct(mine);
        BedObject_CellsConstruct(theirs);
        unsigned int my_count = BedObject_ListCells(object, mine);
        unsigned int their_count = BedObject_ListCells((BedObject *) other, theirs);
        for (unsigned int i = 0; i < my_count; i++) {
            Cell *a = BedObject_CellAt(mine, (int) i);
            s32 ax = a->x;
            s32 ay = a->y;
            for (unsigned int j = 0; j < their_count; j++) {
                Cell *b = BedObject_CellAt(theirs, (int) j);
                s32 dx = ax - b->x;
                s32 dy = ay - b->y;
                if (dx < 0) {
                    dx = -dx;
                }
                if (dy < 0) {
                    dy = -dy;
                }
                if (dx + dy == 1) {
                    BedObject_CellsDestruct(theirs);
                    BedObject_CellsDestruct(mine);
                    return BED_OBJECT_STEP_JOINED;
                }
            }
        }
        BedObject_CellsDestruct(theirs);
        BedObject_CellsDestruct(mine);
    }
    return BED_OBJECT_STEP_BLOCKED;
}
CLEAN_AS(func_ov004_02218414, BedObject_CheckStep)

/* func_ov004_02218548: the cells the object covers by its shape (RoomObject.unk_784), its points
 * in the world; how many (0 for a shape without points). */
unsigned int BedObject_ListCells(BedObject *object, Cell *cells)
{
    const Vec3 *points = data_ov004_022476b0[object->base.unk_784].points;
    if (points == NULL) {
        return 0;
    }
    for (u32 i = 0; i < data_ov004_022476b0[object->base.unk_784].count; i++) {
        Vec3 world;
        RoomObject_ToWorld(&object->base, &world, &points[i]);
        Cell *cell = BedObject_CellAt(cells, (int) i);
        Position_Tile(&cell->x, &cell->y, (const Position *) (const void *) &world);
    }
    return data_ov004_022476b0[object->base.unk_784].count;
}
CLEAN_AS(func_ov004_02218548, BedObject_ListCells)

/* func_ov004_022185b0: the two cells in front of the object by its shape (RoomObject.unk_784);
 * 2, or 0 for a shape without them. */
int BedObject_FrontCells(BedObject *object, Cell *cells)
{
    const Vec3 *points = data_ov004_02250668[object->base.unk_784];
    if (points == NULL) {
        return 0;
    }
    for (unsigned int i = 0; i < 2; i++) {
        Vec3 world;
        RoomObject_ToWorld(&object->base, &world, &points[i]);
        Cell *cell = BedObject_CellAt(cells, (int) i);
        Position_Tile(&cell->x, &cell->y, (const Position *) (const void *) &world);
    }
    return 2;
}
CLEAN_AS(func_ov004_022185b0, BedObject_FrontCells)

/* func_ov004_02218604 (vtable slot 0x0c) */
int BedObject_Vfunc0c(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02218604, BedObject_Vfunc0c)

/* func_ov004_02218608 (vtable slot 0x24) */
int BedObject_Vfunc24(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02218608, BedObject_Vfunc24)

/* _ZN18Obj_ov004_0225305819func_ov004_0221860cEv (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): for kind 0x2a, the node set's value 0, or 1 while a player (actors 0
 * to 3, in state 8) stands on one of its cells, which also runs the glows and the animations and
 * plays sound 0 for each such player; then the state. */
int BedObject_Update(BedObject *object)
{
    RoomObject *base = &object->base;
    if (base->unk_780 == KIND_2A) {
        ByteSet_SetValue(&base->node_set, 0);
        for (int i = 0; i < PLAYER_COUNT; i++) {
            Vec3 point;
            if (RoomPlayerActor_PointAtPlace(&point, i) == 0) {
                continue;
            }
            int x;
            int y;
            Position_Tile(&x, &y, (const Position *) (const void *) &point);
            CellList cells;
            CellList_Construct(&cells);
            RoomObject_ListCells(base, &cells, NULL, 0);
            for (unsigned long j = 0; j < CellList_Count(&cells); j++) {
                if (x == CellList_At(&cells, (int) j)->x && y == CellList_At(&cells, (int) j)->y) {
                    ByteSet_SetValue(&base->node_set, 1);
                    GlowSet_Update(&object->glows);
                    RoomObject_AdvanceAnims(base);
                    RoomObject_PlaySound0(base);
                    break;
                }
            }
            CellList_Destruct(&cells);
        }
    }
    BedObject_UpdateState(object);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_0225305819func_ov004_0221860cEv, BedObject_Update)

/* func_ov004_022186cc (vtable slot 0x7c, once the model is bound): the node set's value 0; kind
 * 0x2a binds the animations of variant 0 and its glows (on); it watches at once when
 * SceneKinds_CurrentIn6To8 says so. Done at once. */
int BedObject_Start(BedObject *object)
{
    RoomObject *base = &object->base;
    ByteSet_SetValue(&base->node_set, 0);
    if (base->unk_780 == KIND_2A) {
        RoomObject_LoadAnims(base, 0, 0, FX32_ONE, 0);
        GlowSet_Bind(&object->glows, base->model_resource, 1);
    }
    if (SceneKinds_CurrentIn6To8() != 0) {
        switch_to(object, BED_OBJECT_WATCH);
    }
    return 1;
}
CLEAN_AS(func_ov004_022186cc, BedObject_Start)

/* func_ov004_02218734 (vtable slot 0x48): whether it is busy for the scene: the session not
 * linked, past PUSHED (BedObject_IsPastPushed) and marked to be pushed or talked to. */
int BedObject_Vfunc48(BedObject *object)
{
    return Session_IsLinked(data_020ccf94) == 0 && BedObject_IsPastPushed(object) != 0 && object->mode != BED_OBJECT_MODE_NONE;
}
CLEAN_AS(func_ov004_02218734, BedObject_Vfunc48)

/* func_ov004_0221876c: whether it has left PUSHED (any state from WATCH on). */
int BedObject_IsPastPushed(BedObject *object)
{
    return object->state >= BED_OBJECT_WATCH;
}
CLEAN_AS(func_ov004_0221876c, BedObject_IsPastPushed)

static void bed_object_set_vtables(BedObject *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02253058;
    object->base.receiver_vtable = data_ov004_02253104;
}

/* func_ov004_02218780 (the deleting destructor, vtable slot 0x44): the glows taken down, then
 * the base class's, and the memory given back. */
BedObject *BedObject_Delete(BedObject *object)
{
    bed_object_set_vtables(object);
    GlowSet_Destruct(&object->glows);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02218780, BedObject_Delete)

/* func_ov004_022187b8 (the destructor, vtable slot 0x40): the glows taken down, then the base
 * class's. */
BedObject *BedObject_Destroy(BedObject *object)
{
    bed_object_set_vtables(object);
    GlowSet_Destruct(&object->glows);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_022187b8, BedObject_Destroy)

/* func_ov004_022187ec (the constructor): no item kept and the glows built. Its other fields are
 * left as the allocation zeroed them. */
BedObject *BedObject_Construct(BedObject *object)
{
    RoomObject_ConstructBase(&object->base);
    bed_object_set_vtables(object);
    object->item = ITEM_CODE_NONE;
    GlowSet_Construct(&object->glows);
    return object;
}
CLEAN_AS(func_ov004_022187ec, BedObject_Construct)

/* func_ov004_0221882c: a new one from the room's heap; nothing when it has no room. */
void BedObject_Create(void)
{
    BedObject *object = RoomObject_Alloc(BED_OBJECT_SIZE);
    if (object != NULL) {
        BedObject_Construct(object);
    }
}
CLEAN_AS(func_ov004_0221882c, BedObject_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters BedObject's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static BedObject *bed_object_from_receiver(void *receiver)
{
    return (BedObject *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a724: the deleting destructor, entered from the receiver part. */
BedObject *BedObjectReceiver_Delete(void *receiver)
{
    return BedObject_Delete(bed_object_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02253058D0Ev, BedObjectReceiver_Delete)

/* func_ov004_0221a740: BedObject_OnChoice, entered from the receiver part. */
void BedObjectReceiver_OnChoice(void *receiver)
{
    BedObject_OnChoice(bed_object_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_0225305817vfunc_02066994_18Ev, BedObjectReceiver_OnChoice)

/* func_ov004_0221a75c: BedObject_OnTalkStep, entered from the receiver part. */
void BedObjectReceiver_OnTalkStep(void *receiver)
{
    BedObject_OnTalkStep(bed_object_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_0225305817vfunc_02066994_14Ev, BedObjectReceiver_OnTalkStep)

/* func_ov004_0221a778: the destructor, entered from the receiver part. */
BedObject *BedObjectReceiver_Destroy(void *receiver)
{
    return BedObject_Destroy(bed_object_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02253058D1Ev, BedObjectReceiver_Destroy)
