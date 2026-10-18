/* The room objects of vtable 0x02253058 (room_object_02253058.h).
 *
 * REQUIRES: the object at a word-aligned address, as every object the room's heap gives is;
 * the ROM reads and writes its 16-bit fields with halfword accesses, which at an odd address
 * the DS's ARM9 aligns down. */
#include "room_object_02253058.h"

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

static_assert(offsetof(RoomObject, unk_00C) == 0xc, "kind");
static_assert(offsetof(RoomObject, position) == 0x5c, "position");
static_assert(offsetof(RoomObject, angle) == 0x8e, "angle");
static_assert(offsetof(RoomObject, receiver_state) == 0x10a, "receiver state byte");
static_assert(offsetof(RoomObject, link) == 0x12c, "link");
static_assert(offsetof(RoomObject, unk_784) == 0x784, "unk_784");
static_assert(offsetof(RoomObject02253058, push_frames) == 0x844, "push frames");
static_assert(offsetof(RoomObject02253058, quarter) == 0x848, "quarter");
static_assert(offsetof(RoomObject02253058, wait) == 0x84a, "wait");
static_assert(offsetof(RoomObject02253058, wait_gone) == 0x84c, "wait gone");
static_assert(offsetof(RoomObject02253058, cell_x) == 0x850, "cell");
static_assert(offsetof(RoomObject02253058, mode) == 0x858, "mode");
static_assert(offsetof(RoomObject02253058, item) == 0x85c, "item");
static_assert(offsetof(RoomObject02253058, state) == 0x85e, "state");
static_assert(offsetof(RoomObject02253058, glows) == 0x860, "glows");
static_assert(sizeof(RoomObject02253058) == 0x8b8, "the size RoomObject02253058_Create allocates");

#define RECEIVER_OFFSET 0xec
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */
#define ONE 0x1000         /* normal speed, 20.12 fixed point */
#define PLAYER 4           /* the actor SessionPlayers_ActorOf is asked for: this console's player */
#define PLAYER_COUNT 4     /* the actors RoomPlayerActor_PointAtPlace is asked for */
#define PUSH_FRAMES 7      /* frames of pushing before it counts */
#define MOVED_ENOUGH 0x200 /* how far the entry must have moved (RoomPushes_Moved) */
#define WAIT_FRAMES 0x18
#define VANISH_FRAMES 0x16
#define KIND_2A 0x2a       /* RoomObject.unk_780 of the kind with glows */
#define KIND_37 0x37       /* RoomObject.unk_00C of this class */
#define LONG_SHAPE 2       /* RoomObject.unk_784 of the shape two cells wide */
#define BACK_Z 0x16000     /* the z from which on it is in the back of the room */
#define STEP 0x2000        /* one cell, 20.12 fixed point */
#define HALF_STEP 0x1000   /* RoomObject02253058_PointAhead's step */
#define PLAYER_REACH 0x800 /* what Actors_NoneNear is given */
#define NPC_REACH 0x2000
#define PLAYER_RADIUS 0x800
#define NO_ITEM_KIND_SLOT 0 /* the pockets' slot state RoomObject02253058_CanTakeItem accepts */
#define ITEM_CATEGORY 5     /* what FurnitureInfo_ItemCategory says of the items it accepts */
#define ITEM_PLACE_SIDE 3   /* the side the kept item is placed facing */
#define ITEM_PLACE_MODE 1
#define POCKETS_ARG 0x28 /* what GroupParams_OpenWithMask is given */
#define CHOICE_FIRST 0xc /* the messages of the two choices */
#define CHOICE_SECOND 0xd
#define SEQUENCE_4 0x19 /* the receiver's state byte with "sp_etc_sequence4" */
#define TALK_STATE 4    /* the receiver's state byte with "obj_etc_player" */
#define DONE_EVENT 0x2e /* queued in SceneTables_EntryRecord's object when the sequence is done */
#define DONE_EVENT_ARG 2
#define NO_ITEM 0xfff1 /* RoomObject02253058.item when none is kept */
#define ROOM_OBJECT_02253058_SIZE 0x8b8

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02253058[];
extern const u8 data_ov004_02253104[];

/* The receiver's names: "obj_etc_player", "sp_etc_sequence4" and "sp_etc_sequence2". */
extern const char data_ov004_022531f0[];
extern const char data_ov004_02253210[];
extern const char data_ov004_02253224[];

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02257064;
extern MemberPointer data_ov004_0225773c[ROOM_OBJECT_02253058_STATE_COUNT];
extern const MemberPointer data_ov004_022500d0, data_ov004_022500e0, data_ov004_02250118, data_ov004_022500a8,
    data_ov004_022500c8, data_ov004_02250138, data_ov004_022504c0, data_ov004_022504f8, data_ov004_02250360,
    data_ov004_02250508, data_ov004_02250510, data_ov004_02250518, data_ov004_022502e8, data_ov004_02250368;
extern u32 data_ov004_02257070;
extern MemberPointer data_ov004_022576cc[ROOM_OBJECT_02253058_STATE_COUNT];
extern const MemberPointer data_ov004_02250058, data_ov004_02250090, data_ov004_02250110, data_ov004_02250398,
    data_ov004_02250590, data_ov004_022503f0, data_ov004_02250358, data_ov004_022502f0, data_ov004_02250660,
    data_ov004_02250180, data_ov004_02250210, data_ov004_02250418, data_ov004_022502c8, data_ov004_02250440;

/* The points, in the object's space, of its cells (for each RoomObject.unk_784) and of the
 * two cells in front of it (NULL for none). */
typedef struct RoomObject02253058Shape {
    const Vec3 *points;
    u32 count;
} RoomObject02253058Shape;
extern const RoomObject02253058Shape data_ov004_022476b0[];
extern const Vec3 *const data_ov004_02250668[];

/* The players: actor 4 (SessionPlayers_ActorOf), this console's player's number (PlayerRecords_CurrentNumber) and
 * record (PlayerRecords_Current). */
extern NetSession *data_020ccf94;
/* The width the room's halves are taken from. */
extern s32 data_020ca0ec;

/* The town's map: a cell's point and a point's cell, whether a cell holds something
 * (RoomObjects_HeightAtCell, CollisionMap_UnclaimedObjectAt gives -1 for nothing), the same for the cell of a point,
 * and the grid of the room's objects. */
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);

/* The conversation: its choices (at 0x31c), the one taken, and its message. */
extern u8 data_021f43e8;

/* RoomObject02253058_CanTakeItem by the game's symbol, the predicate the pockets are given. */
extern int func_ov004_02217bb0(u16 *item, int state);

/* The receiver part as C++ converts a pointer to the object to it: NULL stays NULL. */
static void *receiver_of(RoomObject02253058 *object)
{
    return object != NULL ? (u8 *) object + RECEIVER_OFFSET : NULL;
}

/* Vtable slot 0x70 (RoomObject02253058_EnterState): enters `state`. */
static void switch_to(RoomObject02253058 *object, int state)
{
    object->base.vtable->vfunc_70(&object->base, state, SLOT_70_VALUE);
}

static void *entry_of(RoomObject02253058 *object)
{
    return RoomPushes_FindObject(RoomPushes_Records(), &object->base);
}

/* Whether the entry is in state 2 or 0. */
static int entry_ready(void *entry)
{
    return RoomPushes_Side(entry) == 2 || RoomPushes_Side(entry) == 0;
}

/* The angle the player faces it with. */
static s16 facing(RoomObject02253058 *object)
{
    return (s16) (object->base.angle - 0x4000);
}

/* Whether the link the receiver is attached to is there and closed. */
static int link_closed(RoomObject02253058 *object)
{
    return object->base.link != NULL && object->base.link->state == 0;
}

/* Hands the receiver back and lets the scene go on. */
static void end_talk(RoomObject02253058 *object)
{
    SceneObjectBase_ReleaseReceiver(&object->base.scene, receiver_of(object));
    EventQueue_FinishObjectEvent(object);
}

/* Takes the receiver, raises the link's request and names the receiver.
 * REQUIRES: the receiver has a link once SceneObjectBase_TakeReceiver has taken it. */
static void take_receiver(RoomObject02253058 *object, const char *name)
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
void RoomObject02253058_OnChoice(RoomObject02253058 *object)
{
    unsigned int choice = TalkAnswers_Picked(TalkObject_Answers(object->base.link));
    if (object->mode == ROOM_OBJECT_02253058_MODE_PUSH) {
        switch (choice) {
            case 0:
                TalkObject_SetMessage(object->base.link, &data_021f43e8, NULL);
                switch_to(object, ROOM_OBJECT_02253058_SEQUENCE_DONE);
                break;
            case 1:
                switch_to(object, ROOM_OBJECT_02253058_SEQUENCE_END);
                break;
        }
    } else {
        switch (choice) {
            case 0:
                TalkObject_SetMessage(object->base.link, &data_021f43e8, NULL);
                switch_to(object, ROOM_OBJECT_02253058_CHOOSE_ITEM);
                break;
            case 1:
                TalkObject_SetMessage(object->base.link, &data_021f43e8, NULL);
                switch_to(object, ROOM_OBJECT_02253058_TALK_END);
                break;
        }
    }
}
CLEAN_AS(func_ov004_02217864, RoomObject02253058_OnChoice)

/* func_ov004_022178fc (the receiver's slot 0x14): at state byte 0 the conversation offers two
 * choices (messages 0xc and 0xd, each with message data_021f43e8 as it is then) and shows them;
 * at state byte 0x19 the sequence ends. */
void RoomObject02253058_OnTalkStep(RoomObject02253058 *object)
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
        switch_to(object, ROOM_OBJECT_02253058_SEQUENCE_END);
    }
}
CLEAN_AS(func_ov004_022178fc, RoomObject02253058_OnTalkStep)

/* func_ov004_022179a0 (vtable slot 0x4c): the scene's answer to EventQueue_RequestKind6. Events 0 and 1
 * move the player in mode 1, else start the talk; event 8 watches again; others do nothing. */
void RoomObject02253058_OnSceneEvent(RoomObject02253058 *object, int event)
{
    switch (event) {
        case 0:
        case 1:
            if (object->mode == ROOM_OBJECT_02253058_MODE_PUSH) {
                switch_to(object, ROOM_OBJECT_02253058_MOVE_PLAYER);
            } else {
                switch_to(object, ROOM_OBJECT_02253058_TALK_NEXT);
            }
            break;
        case 8:
            switch_to(object, ROOM_OBJECT_02253058_WATCH);
            break;
    }
}
CLEAN_AS(func_ov004_022179a0, RoomObject02253058_OnSceneEvent)

/* func_ov004_022179e8 (update of VANISH): after 22 frames hands the receiver back, lets the
 * scene go on and asks for the object's deletion. The count stays at 22, so this repeats each
 * frame until it is gone. */
void RoomObject02253058_UpdateVanish(RoomObject02253058 *object)
{
    if (object->wait_gone < VANISH_FRAMES) {
        object->wait_gone++;
    }
    if (object->wait_gone == VANISH_FRAMES) {
        end_talk(object);
        Process_RequestDelete((Process *) (void *) object);
    }
}
CLEAN_AS(func_ov004_022179e8, RoomObject02253058_UpdateVanish)

/* func_ov004_02217a28 (entry of VANISH) */
int RoomObject02253058_EnterVanish(RoomObject02253058 *object)
{
    object->wait_gone = 0;
    return 1;
}
CLEAN_AS(func_ov004_02217a28, RoomObject02253058_EnterVanish)

/* func_ov004_02217a38 (update of PLACE): once shrunk away, places the kept item at its cell
 * facing side 3 (a cell to the right for the two-cell shape on the left half, a cell back to the
 * left for an item FurnitureInfo_ItemShape tells 2 of on the left half); vanishes once RoomObjects_Spawn
 * has placed it. */
void RoomObject02253058_UpdatePlace(RoomObject02253058 *object)
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
    int number = ItemCode_VariantItem(&object->item);
    if (RoomObjects_Spawn(Placement_Make(x, y, number, ITEM_PLACE_SIDE, 0, ITEM_PLACE_MODE)) != 0) {
        switch_to(object, ROOM_OBJECT_02253058_VANISH);
    }
}
CLEAN_AS(func_ov004_02217a38, RoomObject02253058_UpdatePlace)

/* func_ov004_02217ac4 (entry of PLACE): the cell for the item (RoomObject_FindVariantCell, its
 * answer dropped), then it shrinks away. */
int RoomObject02253058_EnterPlace(RoomObject02253058 *object)
{
    RoomObject_FindVariantCell(&object->base, &object->cell_x, &object->cell_y, NULL, 0);
    RoomObject_Shrink(&object->base);
    return 1;
}
CLEAN_AS(func_ov004_02217ac4, RoomObject02253058_EnterPlace)

/* func_ov004_02217af4 (update of SWAP): once group 9 can open again, without an item chosen it
 * ends the talk; with one, keeps the item of the chosen slot (and gives it to the player's
 * record), puts this object's item code in that slot and places the kept item. */
void RoomObject02253058_UpdateSwap(RoomObject02253058 *object)
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
        PlayerRecord_SetItem240E(record, &object->item);
    }
    u16 code = ItemCode_MakeVariant(RoomObject_Number(&object->base), 0);
    CurrentPockets_Set(&code, 0, slot);
    switch_to(object, ROOM_OBJECT_02253058_PLACE);
}
CLEAN_AS(func_ov004_02217af4, RoomObject02253058_UpdateSwap)

/* func_ov004_02217b70 (entry of SWAP) */
int RoomObject02253058_EnterSwap(RoomObject02253058 *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov004_02217b70, RoomObject02253058_EnterSwap)

/* func_ov004_02217b74 (update of CHOOSE_ITEM): once the link has closed, opens the pockets on
 * the slots RoomObject02253058_CanTakeItem accepts; swaps once they are open. */
void RoomObject02253058_UpdateChooseItem(RoomObject02253058 *object)
{
    if (link_closed(object) && GroupParams_OpenWithMask(Pockets_Select(func_ov004_02217bb0), POCKETS_ARG) != 0) {
        switch_to(object, ROOM_OBJECT_02253058_SWAP);
    }
}
CLEAN_AS(func_ov004_02217b74, RoomObject02253058_UpdateChooseItem)

/* func_ov004_02217bb0: whether a pockets' slot may be chosen: in state 0, holding an item
 * ItemCode_HasVariant tells that FurnitureInfo_ItemCategory puts in category 5. */
int RoomObject02253058_CanTakeItem(u16 *item, int state)
{
    return state == NO_ITEM_KIND_SLOT && ItemCode_HasVariant(item) != 0 && FurnitureInfo_ItemCategory(item) == ITEM_CATEGORY;
}
CLEAN_AS(func_ov004_02217bb0, RoomObject02253058_CanTakeItem)

/* func_ov004_02217bd8 (entry of CHOOSE_ITEM) */
int RoomObject02253058_EnterChooseItem(RoomObject02253058 *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov004_02217bd8, RoomObject02253058_EnterChooseItem)

/* func_ov004_02217bdc (update of TALK_END): ends the talk once the link has closed. */
void RoomObject02253058_UpdateTalkEnd(RoomObject02253058 *object)
{
    if (link_closed(object)) {
        end_talk(object);
    }
}
CLEAN_AS(func_ov004_02217bdc, RoomObject02253058_UpdateTalkEnd)

/* func_ov004_02217c0c (entry of TALK_END) */
int RoomObject02253058_EnterTalkEnd(RoomObject02253058 *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov004_02217c0c, RoomObject02253058_EnterTalkEnd)

/* func_ov004_02217c10 (update of TALK): the receiver leads. */
void RoomObject02253058_UpdateTalk(RoomObject02253058 *object)
{
    (void) object;
}
CLEAN_AS(func_ov004_02217c10, RoomObject02253058_UpdateTalk)

/* func_ov004_02217c14 (entry of TALK): takes the receiver, named "obj_etc_player", in state 4. */
int RoomObject02253058_EnterTalk(RoomObject02253058 *object)
{
    take_receiver(object, data_ov004_022531f0);
    object->base.receiver_state = TALK_STATE;
    return 1;
}
CLEAN_AS(func_ov004_02217c14, RoomObject02253058_EnterTalk)

/* func_ov004_02217c58 (update of TALK_NEXT) */
void RoomObject02253058_UpdateTalkNext(RoomObject02253058 *object)
{
    switch_to(object, ROOM_OBJECT_02253058_TALK);
}
CLEAN_AS(func_ov004_02217c58, RoomObject02253058_UpdateTalkNext)

/* func_ov004_02217c6c (entry of TALK_NEXT) */
int RoomObject02253058_EnterTalkNext(RoomObject02253058 *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov004_02217c6c, RoomObject02253058_EnterTalkNext)

/* func_ov004_02217c70 (update of SEQUENCE_DONE): once the link has closed, ends the talk, queues
 * event 0x2e in SceneTables_EntryRecord's object and sets the flag of ActivityJob_Ask1. */
void RoomObject02253058_UpdateSequenceDone(RoomObject02253058 *object)
{
    if (link_closed(object)) {
        end_talk(object);
        SceneExit_SetToScene((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), DONE_EVENT, DONE_EVENT_ARG, 0);
        ActivityJob_Ask1();
    }
}
CLEAN_AS(func_ov004_02217c70, RoomObject02253058_UpdateSequenceDone)

/* func_ov004_02217cb4 (entry of SEQUENCE_DONE) */
int RoomObject02253058_EnterSequenceDone(RoomObject02253058 *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov004_02217cb4, RoomObject02253058_EnterSequenceDone)

/* func_ov004_02217cb8 (update of SEQUENCE_END): once the link has closed, tells the player the
 * half it stands in (RoomPlayerActor_RequestPlaceOff) and ends the talk. */
void RoomObject02253058_UpdateSequenceEnd(RoomObject02253058 *object)
{
    if (link_closed(object)) {
        RoomPlayerActor_RequestPlaceOff(object->left_half, 0);
        end_talk(object);
    }
}
CLEAN_AS(func_ov004_02217cb8, RoomObject02253058_UpdateSequenceEnd)

/* func_ov004_02217cf8 (entry of SEQUENCE_END) */
int RoomObject02253058_EnterSequenceEnd(RoomObject02253058 *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov004_02217cf8, RoomObject02253058_EnterSequenceEnd)

/* func_ov004_02217cfc (update of SEQUENCE): the receiver leads. */
void RoomObject02253058_UpdateSequence(RoomObject02253058 *object)
{
    (void) object;
}
CLEAN_AS(func_ov004_02217cfc, RoomObject02253058_UpdateSequence)

/* func_ov004_02217d00 (entry of SEQUENCE): takes the receiver, named "sp_etc_sequence4" in state
 * 0x19 when StartKind_IsNewTown or StartKind_IsNewPlayer says so, else "sp_etc_sequence2" in state 0. */
int RoomObject02253058_EnterSequence(RoomObject02253058 *object)
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
CLEAN_AS(func_ov004_02217d00, RoomObject02253058_EnterSequence)

/* func_ov004_02217d68 (update of WAIT): the sequence after 24 frames. */
void RoomObject02253058_UpdateWait(RoomObject02253058 *object)
{
    if (object->wait < WAIT_FRAMES) {
        object->wait++;
    }
    if (object->wait == WAIT_FRAMES) {
        switch_to(object, ROOM_OBJECT_02253058_SEQUENCE);
    }
}
CLEAN_AS(func_ov004_02217d68, RoomObject02253058_UpdateWait)

/* func_ov004_02217d98 (entry of WAIT) */
int RoomObject02253058_EnterWait(RoomObject02253058 *object)
{
    object->wait = 0;
    return 1;
}
CLEAN_AS(func_ov004_02217d98, RoomObject02253058_EnterWait)

/* func_ov004_02217da8 (update of MOVE_PLAYER): sends the player to the entry's point with the
 * entry's angle, facing the object; waits once the player goes.
 * BUG: without an entry for the object, RoomPushes_Facing and RoomPushes_Centre are handed
 * NULL and the point is read from near address 0; kept. */
void RoomObject02253058_UpdateMovePlayer(RoomObject02253058 *object)
{
    void *entry = entry_of(object);
    s16 angle = (s16) RoomPushes_Facing(entry);
    Vec3 *point = RoomPushes_Centre(entry);
    if (RoomPlayerActor_RequestPlaceApproach(&point->x, &RoomPushes_Centre(entry)->z, &angle, facing(object), 1) != 0) {
        switch_to(object, ROOM_OBJECT_02253058_WAIT);
    }
}
CLEAN_AS(func_ov004_02217da8, RoomObject02253058_UpdateMovePlayer)

/* func_ov004_02217e08 (entry of MOVE_PLAYER) */
int RoomObject02253058_EnterMovePlayer(RoomObject02253058 *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov004_02217e08, RoomObject02253058_EnterMovePlayer)

/* func_ov004_02217e0c (update of WATCH): with an entry, in the quarter of this console's player:
 * with the entry in state 0 or 2 it is pushed (mode 1), counts up to 7 frames and, once the
 * entry has moved more than 0x200 after those, asks the scene for an event unless the session
 * is linked; with the entry in another state it is for talking (mode 2) when TownObjects_VisitorsHere is at
 * most 1. The count restarts on any frame it did not go up. */
void RoomObject02253058_UpdateWatch(RoomObject02253058 *object)
{
    int counted = 0;
    object->mode = ROOM_OBJECT_02253058_MODE_NONE;
    void *entry = entry_of(object);
    if (entry != NULL && (int) object->quarter == PlayerRecords_CurrentNumber()) {
        if (entry_ready(entry)) {
            object->mode = ROOM_OBJECT_02253058_MODE_PUSH;
            if (object->push_frames < PUSH_FRAMES) {
                counted = 1;
                object->push_frames++;
            }
            if (RoomPushes_Moved(entry) > MOVED_ENOUGH && object->push_frames >= PUSH_FRAMES &&
                Session_IsLinked(data_020ccf94) == 0) {
                EventQueue_RequestKind6(object, 0);
            }
        } else if ((unsigned int) TownObjects_VisitorsHere() <= 1) {
            object->mode = ROOM_OBJECT_02253058_MODE_TALK;
        }
    }
    if (!counted) {
        object->push_frames = 0;
    }
}
CLEAN_AS(func_ov004_02217e0c, RoomObject02253058_UpdateWatch)

/* func_ov004_02217eb8 (entry of WATCH): the quarter of the room it stands in, by its x against
 * half of data_020ca0ec and its z against 0x16000. */
int RoomObject02253058_EnterWatch(RoomObject02253058 *object)
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
CLEAN_AS(func_ov004_02217eb8, RoomObject02253058_EnterWatch)

/* func_ov004_02217f2c (update of PUSHED): with an entry in state 0 or 2, the player there and
 * RoomPushes_Allowed allowing it, the one of its two front cells nearer the player (the second
 * when as near); when that cell is free and nobody is one cell ahead of the entry (along its
 * angle) it counts up to 7 frames, and once the entry has moved more than 0x200 after those it
 * sends the player to the entry's point and counts again. The count restarts on any frame it
 * did not go up. */
void RoomObject02253058_UpdatePushed(RoomObject02253058 *object)
{
    int counted = 0;
    void *entry = entry_of(object);
    MapActor *player = SessionPlayers_ActorOf(PLAYER);
    if (entry != NULL && player != NULL && RoomPushes_Allowed() != 0 && entry_ready(entry)) {
        Cell cells[2];
        RoomObject02253058_PairConstruct(cells);
        RoomObject02253058_FrontCells(object, cells);
        Vec3 first;
        Vec3 second;
        Cell *cell = RoomObject02253058_CellAt(cells, 0);
        AcreTile_TileCentre(&first, cell->x, cell->y);
        cell = RoomObject02253058_CellAt(cells, 1);
        AcreTile_TileCentre(&second, cell->x, cell->y);
        Vec3 at = player->position;
        fx32 to_first = Vec_DistanceXZ(&at, &first);
        fx32 to_second = Vec_DistanceXZ(&at, &second);
        Cell chosen = *RoomObject02253058_CellAt(cells, to_first < to_second ? 0 : 1);
        if (RoomObject02253058_CellIsFree(&chosen)) {
            Vec3 ahead = {0, 0, STEP};
            Vec_RotateY(&ahead, RoomPushes_Facing(entry));
            fx32 z = ahead.z + RoomPushes_Centre(entry)->z;
            Vec3 probe = {ahead.x + RoomPushes_Centre(entry)->x, 0, z};
            if (Actors_NoneNear(&probe, PLAYER_REACH, NPC_REACH, PLAYER_RADIUS, 0)) {
                if (object->push_frames < PUSH_FRAMES) {
                    counted = 1;
                    object->push_frames++;
                }
                if (RoomPushes_Moved(entry) > MOVED_ENOUGH && object->push_frames >= PUSH_FRAMES) {
                    s16 angle = (s16) RoomPushes_Facing(entry);
                    Vec3 *point = RoomPushes_Centre(entry);
                    RoomPlayerActor_RequestPlaceApproach(&point->x, &RoomPushes_Centre(entry)->z, &angle, facing(object), 0);
                    object->push_frames = 0;
                }
            }
        }
        RoomObject02253058_PairDestruct(cells);
    }
    if (!counted) {
        object->push_frames = 0;
    }
}
CLEAN_AS(func_ov004_02217f2c, RoomObject02253058_UpdatePushed)

/* func_ov004_022180d4: whether a cell holds nothing. */
int RoomObject02253058_CellIsFree(const Cell *cell)
{
    return RoomObjects_HeightAtCell(cell->x, cell->y) == 0 && CollisionMap_UnclaimedObjectAt(cell->x, cell->y) == -1;
}
CLEAN_AS(func_ov004_022180d4, RoomObject02253058_CellIsFree)

/* func_ov004_02218100 (entry of PUSHED) */
int RoomObject02253058_EnterPushed(RoomObject02253058 *object)
{
    object->push_frames = 0;
    return 1;
}
CLEAN_AS(func_ov004_02218100, RoomObject02253058_EnterPushed)

/* _ZN18Obj_ov004_0225305819func_ov004_02218110Ev: the state's update, through its table. */
void RoomObject02253058_UpdateState(RoomObject02253058 *object)
{
    static const MemberPointer *const updates[ROOM_OBJECT_02253058_STATE_COUNT] = {
        &data_ov004_022500d0, /* RoomObject02253058_UpdatePushed */
        &data_ov004_022500e0, /* RoomObject02253058_UpdateWatch */
        &data_ov004_02250118, /* RoomObject02253058_UpdateMovePlayer */
        &data_ov004_022500a8, /* RoomObject02253058_UpdateWait */
        &data_ov004_022500c8, /* RoomObject02253058_UpdateSequence */
        &data_ov004_02250138, /* RoomObject02253058_UpdateSequenceEnd */
        &data_ov004_022504c0, /* RoomObject02253058_UpdateSequenceDone */
        &data_ov004_022504f8, /* RoomObject02253058_UpdateTalkNext */
        &data_ov004_02250360, /* RoomObject02253058_UpdateTalk */
        &data_ov004_02250508, /* RoomObject02253058_UpdateTalkEnd */
        &data_ov004_02250510, /* RoomObject02253058_UpdateChooseItem */
        &data_ov004_02250518, /* RoomObject02253058_UpdateSwap */
        &data_ov004_022502e8, /* RoomObject02253058_UpdatePlace */
        &data_ov004_02250368, /* RoomObject02253058_UpdateVanish */
    };
    MemberTable_InitOnce(&data_ov004_02257064, data_ov004_0225773c, updates, ROOM_OBJECT_02253058_STATE_COUNT);
    if (object->state < ROOM_OBJECT_02253058_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_0225773c[object->state], object);
    }
}
CLEAN_AS(_ZN18Obj_ov004_0225305819func_ov004_02218110Ev, RoomObject02253058_UpdateState)

/* func_ov004_02218228 (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given `state`
 * and `value`), then enters `state` if its entry (through a table) agrees; whether it did.
 * States 14 and above do not exist. */
int RoomObject02253058_EnterState(RoomObject02253058 *object, unsigned int state, int value)
{
    static const MemberPointer *const entries[ROOM_OBJECT_02253058_STATE_COUNT] = {
        &data_ov004_02250058, /* RoomObject02253058_EnterPushed */
        &data_ov004_02250090, /* RoomObject02253058_EnterWatch */
        &data_ov004_02250110, /* RoomObject02253058_EnterMovePlayer */
        &data_ov004_02250398, /* RoomObject02253058_EnterWait */
        &data_ov004_02250590, /* RoomObject02253058_EnterSequence */
        &data_ov004_022503f0, /* RoomObject02253058_EnterSequenceEnd */
        &data_ov004_02250358, /* RoomObject02253058_EnterSequenceDone */
        &data_ov004_022502f0, /* RoomObject02253058_EnterTalkNext */
        &data_ov004_02250660, /* RoomObject02253058_EnterTalk */
        &data_ov004_02250180, /* RoomObject02253058_EnterTalkEnd */
        &data_ov004_02250210, /* RoomObject02253058_EnterChooseItem */
        &data_ov004_02250418, /* RoomObject02253058_EnterSwap */
        &data_ov004_022502c8, /* RoomObject02253058_EnterPlace */
        &data_ov004_02250440, /* RoomObject02253058_EnterVanish */
    };
    RoomObject_SetUnk77C(&object->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_02257070, data_ov004_022576cc, entries, ROOM_OBJECT_02253058_STATE_COUNT);
    if (state < ROOM_OBJECT_02253058_STATE_COUNT && MemberPointer_CallInt(&data_ov004_022576cc[state], object) != 0) {
        object->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02218228, RoomObject02253058_EnterState)

/* The two kinds of local pairs of cells the functions below use: each is cleared when built
 * (RoomObject02253058_CellsClear) and needs nothing to be taken down. */

/* func_ov004_02218354 */
Cell *RoomObject02253058_CellsDestruct(Cell *cells)
{
    RoomObject02253058_CellsNothing();
    return cells;
}
CLEAN_AS(func_ov004_02218354, RoomObject02253058_CellsDestruct)

/* func_ov004_02218364 */
Cell *RoomObject02253058_CellsConstruct(Cell *cells)
{
    RoomObject02253058_CellsClear(cells);
    return cells;
}
CLEAN_AS(func_ov004_02218364, RoomObject02253058_CellsConstruct)

/* func_ov004_02218374 */
Cell *RoomObject02253058_PairDestruct(Cell *cells)
{
    RoomObject02253058_CellsNothing();
    return cells;
}
CLEAN_AS(func_ov004_02218374, RoomObject02253058_PairDestruct)

/* func_ov004_02218384 */
Cell *RoomObject02253058_PairConstruct(Cell *cells)
{
    RoomObject02253058_CellsClear(cells);
    return cells;
}
CLEAN_AS(func_ov004_02218384, RoomObject02253058_PairConstruct)

/* func_ov004_02218394: cell `index` of a pair (only its lowest bit counts). */
Cell *RoomObject02253058_CellAt(Cell *cells, int index)
{
    return &cells[index & 1];
}
CLEAN_AS(func_ov004_02218394, RoomObject02253058_CellAt)

/* func_ov004_022183a0 */
void RoomObject02253058_CellsNothing(void) {}
CLEAN_AS(func_ov004_022183a0, RoomObject02253058_CellsNothing)

/* func_ov004_022183a4: both cells of a pair at (0, 0). */
Cell *RoomObject02253058_CellsClear(Cell *cells)
{
    for (int i = 0; i < 2; i++) {
        cells[i].x = 0;
        cells[i].y = 0;
    }
    return cells;
}
CLEAN_AS(func_ov004_022183a4, RoomObject02253058_CellsClear)

/* func_ov004_022183b8: `point` plus `offset` (none when NULL) moved half a cell forward and
 * turned by `angle`. `object` is not used. */
void RoomObject02253058_PointAhead(RoomObject02253058 *object, Vec3 *out, const Vec3 *point, int angle, const Vec3 *offset)
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
CLEAN_AS(func_ov004_022183b8, RoomObject02253058_PointAhead)

/* func_ov004_02218414 (RoomObjects_CheckStep asks it of an object of this kind): what is half a
 * cell ahead of `point` along `angle` (RoomObject02253058_PointAhead): blocked when someone is
 * near; else the object of the room on that cell: itself (joined), one FurnitureInfo_IndoorBit2 accepts by
 * its number (open), or one of this kind facing the same way with a cell next to one of this
 * object's (joined); with no object there, open when the cell holds nothing. */
int RoomObject02253058_CheckStep(RoomObject02253058 *object, Vec3 *point, int angle, Vec3 *offset)
{
    Vec3 moved;
    int x;
    int y;
    RoomObject02253058_PointAhead(object, &moved, point, angle, offset);
    Position_Tile(&x, &y, (const Position *) (const void *) &moved);
    RoomObject *other = RoomObjects_GridObjectAt(RoomObjects_Grid(), x, y, 0);
    if (!Actors_NoneNear(&moved, PLAYER_REACH, NPC_REACH, PLAYER_RADIUS, 0)) {
        return ROOM_OBJECT_02253058_STEP_BLOCKED;
    }
    if (other == NULL) {
        if (RoomObjects_HeightAtPoint(&moved) == 0 && CollisionMap_UnclaimedObjectAtPoint(&moved) == -1) {
            return ROOM_OBJECT_02253058_STEP_OPEN;
        }
        return ROOM_OBJECT_02253058_STEP_BLOCKED;
    }
    if (other == &object->base) {
        return ROOM_OBJECT_02253058_STEP_JOINED;
    }
    if (FurnitureInfo_IndoorBit2(RoomObject_Number(other)) != 0) {
        return ROOM_OBJECT_02253058_STEP_OPEN;
    }
    if (object->base.angle == other->angle && other->unk_00C == KIND_37) {
        Cell mine[2];
        Cell theirs[2];
        RoomObject02253058_CellsConstruct(mine);
        RoomObject02253058_CellsConstruct(theirs);
        unsigned int my_count = RoomObject02253058_ListCells(object, mine);
        unsigned int their_count = RoomObject02253058_ListCells((RoomObject02253058 *) other, theirs);
        for (unsigned int i = 0; i < my_count; i++) {
            Cell *a = RoomObject02253058_CellAt(mine, (int) i);
            s32 ax = a->x;
            s32 ay = a->y;
            for (unsigned int j = 0; j < their_count; j++) {
                Cell *b = RoomObject02253058_CellAt(theirs, (int) j);
                s32 dx = ax - b->x;
                s32 dy = ay - b->y;
                if (dx < 0) {
                    dx = -dx;
                }
                if (dy < 0) {
                    dy = -dy;
                }
                if (dx + dy == 1) {
                    RoomObject02253058_CellsDestruct(theirs);
                    RoomObject02253058_CellsDestruct(mine);
                    return ROOM_OBJECT_02253058_STEP_JOINED;
                }
            }
        }
        RoomObject02253058_CellsDestruct(theirs);
        RoomObject02253058_CellsDestruct(mine);
    }
    return ROOM_OBJECT_02253058_STEP_BLOCKED;
}
CLEAN_AS(func_ov004_02218414, RoomObject02253058_CheckStep)

/* func_ov004_02218548: the cells the object covers by its shape (RoomObject.unk_784), its points
 * in the world; how many (0 for a shape without points). */
unsigned int RoomObject02253058_ListCells(RoomObject02253058 *object, Cell *cells)
{
    const Vec3 *points = data_ov004_022476b0[object->base.unk_784].points;
    if (points == NULL) {
        return 0;
    }
    for (u32 i = 0; i < data_ov004_022476b0[object->base.unk_784].count; i++) {
        Vec3 world;
        RoomObject_ToWorld(&object->base, &world, &points[i]);
        Cell *cell = RoomObject02253058_CellAt(cells, (int) i);
        Position_Tile(&cell->x, &cell->y, (const Position *) (const void *) &world);
    }
    return data_ov004_022476b0[object->base.unk_784].count;
}
CLEAN_AS(func_ov004_02218548, RoomObject02253058_ListCells)

/* func_ov004_022185b0: the two cells in front of the object by its shape (RoomObject.unk_784);
 * 2, or 0 for a shape without them. */
int RoomObject02253058_FrontCells(RoomObject02253058 *object, Cell *cells)
{
    const Vec3 *points = data_ov004_02250668[object->base.unk_784];
    if (points == NULL) {
        return 0;
    }
    for (unsigned int i = 0; i < 2; i++) {
        Vec3 world;
        RoomObject_ToWorld(&object->base, &world, &points[i]);
        Cell *cell = RoomObject02253058_CellAt(cells, (int) i);
        Position_Tile(&cell->x, &cell->y, (const Position *) (const void *) &world);
    }
    return 2;
}
CLEAN_AS(func_ov004_022185b0, RoomObject02253058_FrontCells)

/* func_ov004_02218604 (vtable slot 0x0c) */
int RoomObject02253058_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02218604, RoomObject02253058_Vfunc0C)

/* func_ov004_02218608 (vtable slot 0x24) */
int RoomObject02253058_Vfunc24(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02218608, RoomObject02253058_Vfunc24)

/* _ZN18Obj_ov004_0225305819func_ov004_0221860cEv (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): for kind 0x2a, the node set's value 0, or 1 while a player (actors 0
 * to 3, in state 8) stands on one of its cells, which also runs the glows and the animations and
 * plays sound 0 for each such player; then the state. */
int RoomObject02253058_Update(RoomObject02253058 *object)
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
    RoomObject02253058_UpdateState(object);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_0225305819func_ov004_0221860cEv, RoomObject02253058_Update)

/* func_ov004_022186cc (vtable slot 0x7c, once the model is bound): the node set's value 0; kind
 * 0x2a binds the animations of variant 0 and its glows (on); it watches at once when
 * SceneKinds_CurrentIn6To8 says so. Done at once. */
int RoomObject02253058_Start(RoomObject02253058 *object)
{
    RoomObject *base = &object->base;
    ByteSet_SetValue(&base->node_set, 0);
    if (base->unk_780 == KIND_2A) {
        RoomObject_LoadAnims(base, 0, 0, ONE, 0);
        GlowSet_Bind(&object->glows, base->model_resource, 1);
    }
    if (SceneKinds_CurrentIn6To8() != 0) {
        switch_to(object, ROOM_OBJECT_02253058_WATCH);
    }
    return 1;
}
CLEAN_AS(func_ov004_022186cc, RoomObject02253058_Start)

/* func_ov004_02218734 (vtable slot 0x48): whether it is busy for the scene: the session not
 * linked, past PUSHED (RoomObject02253058_IsPastPushed) and marked to be pushed or talked to. */
int RoomObject02253058_Vfunc48(RoomObject02253058 *object)
{
    return Session_IsLinked(data_020ccf94) == 0 && RoomObject02253058_IsPastPushed(object) != 0 &&
           object->mode != ROOM_OBJECT_02253058_MODE_NONE;
}
CLEAN_AS(func_ov004_02218734, RoomObject02253058_Vfunc48)

/* func_ov004_0221876c: whether it has left PUSHED (any state from WATCH on). */
int RoomObject02253058_IsPastPushed(RoomObject02253058 *object)
{
    return object->state >= ROOM_OBJECT_02253058_WATCH;
}
CLEAN_AS(func_ov004_0221876c, RoomObject02253058_IsPastPushed)

static void RoomObject02253058_set_vtables(RoomObject02253058 *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02253058;
    object->base.receiver_vtable = data_ov004_02253104;
}

/* func_ov004_02218780 (the deleting destructor, vtable slot 0x44): the glows taken down, then
 * the base class's, and the memory given back. */
RoomObject02253058 *RoomObject02253058_Delete(RoomObject02253058 *object)
{
    RoomObject02253058_set_vtables(object);
    GlowSet_Destruct(&object->glows);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02218780, RoomObject02253058_Delete)

/* func_ov004_022187b8 (the destructor, vtable slot 0x40): the glows taken down, then the base
 * class's. */
RoomObject02253058 *RoomObject02253058_Destroy(RoomObject02253058 *object)
{
    RoomObject02253058_set_vtables(object);
    GlowSet_Destruct(&object->glows);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_022187b8, RoomObject02253058_Destroy)

/* func_ov004_022187ec (the constructor): no item kept and the glows built. Its other fields are
 * left as the allocation zeroed them. */
RoomObject02253058 *RoomObject02253058_Construct(RoomObject02253058 *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject02253058_set_vtables(object);
    object->item = NO_ITEM;
    GlowSet_Construct(&object->glows);
    return object;
}
CLEAN_AS(func_ov004_022187ec, RoomObject02253058_Construct)

/* func_ov004_0221882c: a new one from the room's heap; nothing when it has no room. */
void RoomObject02253058_Create(void)
{
    RoomObject02253058 *object = RoomObject_Alloc(ROOM_OBJECT_02253058_SIZE);
    if (object != NULL) {
        RoomObject02253058_Construct(object);
    }
}
CLEAN_AS(func_ov004_0221882c, RoomObject02253058_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters RoomObject02253058's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static RoomObject02253058 *RoomObject02253058_from_receiver(void *receiver)
{
    return (RoomObject02253058 *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a724: the deleting destructor, entered from the receiver part. */
RoomObject02253058 *RoomObject02253058Receiver_Delete(void *receiver)
{
    return RoomObject02253058_Delete(RoomObject02253058_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02253058D0Ev, RoomObject02253058Receiver_Delete)

/* func_ov004_0221a740: RoomObject02253058_OnChoice, entered from the receiver part. */
void RoomObject02253058Receiver_OnChoice(void *receiver)
{
    RoomObject02253058_OnChoice(RoomObject02253058_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_0225305817vfunc_02066994_18Ev, RoomObject02253058Receiver_OnChoice)

/* func_ov004_0221a75c: RoomObject02253058_OnTalkStep, entered from the receiver part. */
void RoomObject02253058Receiver_OnTalkStep(void *receiver)
{
    RoomObject02253058_OnTalkStep(RoomObject02253058_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_0225305817vfunc_02066994_14Ev, RoomObject02253058Receiver_OnTalkStep)

/* func_ov004_0221a778: the destructor, entered from the receiver part. */
RoomObject02253058 *RoomObject02253058Receiver_Destroy(void *receiver)
{
    return RoomObject02253058_Destroy(RoomObject02253058_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02253058D1Ev, RoomObject02253058Receiver_Destroy)
