/* The chests (chest.h). */
#include "chest.h"

#include <stdint.h>

#include "autoload_2/vector.h"
#include "cells.h"
#include "clean.h"
#include "furniture_model.h"
#include "main/group_params.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_map.h"
#include "room_object_methods.h"
#include "room_object_parts.h"
#include "ov004/room_player_actor.h"
#include "main/acre_tile.h"
#include "main/collision_map.h"
#include "main/event_queue.h"
#include "main/item_code.h"
#include "main/message_receiver.h"
#include "main/player_actor_ops.h"
#include "main/room_sync.h"
#include "main/scene_kinds.h"
#include "main/scene_object_base.h"
#include "main/scene_query.h"
#include "room_objects.h"
#include "room_pushes.h"

static_assert(offsetof(Chest, lid) == 0x860, "lid");
static_assert(offsetof(Chest, talk_step) == 0x864, "talk step");
static_assert(offsetof(RoomObject, angle) == 0x8e, "angle");
static_assert(offsetof(RoomObject, node_set) == 0x764, "node set");
static_assert(offsetof(Chest, unk_844) == 0x844, "glow");
static_assert(sizeof(Chest) == 0x868, "the size Chest_Create allocates");

#define RECEIVER_OFFSET 0xec
#define CHEST_SIZE 0x868
#define ONE 0x1000         /* normal speed, 20.12 fixed point */
#define ANIM_MODE_ONCE 1   /* stop at the end */
#define ANIM_MODE_3 3      /* the animations' mode 3 */
#define SLOT_70_VALUE 0xff /* the second argument given with a lid state (vtable slot 0x70) */
#define KIND_0B 0xb        /* the chest whose cells in front must be free to open it */
#define KIND_0F 0xf        /* the chest with other animations */
#define CHEST_COUNT 3
#define NO_CHEST (-1)
#define MENU_MODE 0x22 /* the mode group 9 opens its menu in */
#define LINE_COUNT 16  /* the values of the receiver's state byte the talk chooses from */
#define STEP 0x2000    /* one cell, 20.12 fixed point (two units of 0x1000 a cell) */
#define STEP_SHIFT 13  /* a cell from a step */
#define BLOCK_CELLS 16 /* cells along a block of the town's map */

/* "obj_etc_nchest", the receiver's name. */
extern const char data_ov004_02253200[];
/* The kinds (RoomObject.unk_780) of chests 0 to 2. */
extern const s32 data_ov004_022476a4[CHEST_COUNT];

/* Whether each lid state shows the switch on (for vtable slot 0x74). */
extern const u8 data_ov004_02247680[CHEST_LID_STATE_COUNT];

/* The class's vtable, and its receiver part's. */
extern const u8 data_ov004_0225211c[];
extern const u8 data_ov004_022521c8[];

/* The talk's tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02257024;
extern MemberPointer data_ov004_0225766c[CHEST_TALK_STEP_COUNT];
extern const MemberPointer data_ov004_02250588, data_ov004_022501b8, data_ov004_02250048, data_ov004_02250570,
    data_ov004_02250568, data_ov004_02250560, data_ov004_02250558, data_ov004_02250550, data_ov004_02250548,
    data_ov004_02250540, data_ov004_02250538, data_ov004_02250530;
extern u32 data_ov004_02256ff4;
extern MemberPointer data_ov004_0225760c[CHEST_TALK_STEP_COUNT];
extern const MemberPointer data_ov004_02250638, data_ov004_022505f0, data_ov004_022501f0, data_ov004_022505e0,
    data_ov004_022501e8, data_ov004_022505d0, data_ov004_022505c8, data_ov004_022505c0, data_ov004_022501d8,
    data_ov004_022505b0, data_ov004_022505a8, data_ov004_022505a0;

/* The lid's tables. */
extern u32 data_ov004_02257014;
extern MemberPointer data_ov004_022574ec[CHEST_LID_STATE_COUNT];
extern const MemberPointer data_ov004_02250608, data_ov004_02250610, data_ov004_02250618, data_ov004_02250620;
extern u32 data_ov004_02257020;
extern MemberPointer data_ov004_022574cc[CHEST_LID_STATE_COUNT];
extern const MemberPointer data_ov004_022505b8, data_ov004_022505d8, data_ov004_02250650, data_ov004_02250648;

/* The town's map (AcreTile_ItemInAcre finds the item on a cell of it), and whether an item is of the
 * kind ItemCode_HasVariant tells. */
extern void *data_021c80bc;

/* The receiver part as C++ converts a pointer to the chest to it: NULL stays NULL. */
static void *Chest_receiver(Chest *chest)
{
    return chest != NULL ? (u8 *) chest + RECEIVER_OFFSET : NULL;
}

/* An arithmetic shift right, for negative values too. */
static s32 shift_right(s32 value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* Vtable slot 0x70 (Chest_EnterLid): enters lid state `state`. */
static void Chest_switch_to(Chest *chest, int state)
{
    chest->base.vtable->vfunc_70(&chest->base, state, SLOT_70_VALUE);
}

/* Requests lid state `state` for the object's cell (RoomSync_SetState); its answer. */
static int Chest_request(Chest *chest, int state)
{
    return RoomSync_SetState(&chest->base, state, SLOT_70_VALUE, 1);
}

/* Whether the link the receiver is attached to is there and open, or there and closed. */
static int Chest_link_open(Chest *chest)
{
    return chest->base.link != NULL && chest->base.link->state != 0;
}

static int Chest_link_closed(Chest *chest)
{
    return chest->base.link != NULL && chest->base.link->state == 0;
}

/* The common entry of CHEST_MENU_CLOSE and CHEST_TALK_CLOSE: message 0x2f for a chest with an
 * index (refused when it is not sent), then the lid closing requested. */
static int Chest_close(Chest *chest)
{
    int index = Chest_Index(chest);
    if (index != NO_CHEST && RoomPlayerActor_RequestChestClose(&index) == 0) {
        return 0;
    }
    return Chest_request(chest, CHEST_LID_CLOSING);
}

/* The common entry of CHEST_MENU_ANNOUNCE and CHEST_TALK_ANNOUNCE: for a chest with an index,
 * message 0x2d with the index and the values of the chest's entry; whether it was sent (1 for
 * no index).
 * BUG: without an entry for the chest, RoomPushes_Facing and RoomPushes_Destination are handed
 * NULL and the values are read from near address 0; kept. */
static int Chest_announce(Chest *chest)
{
    void *entry = RoomPushes_FindObject(RoomPushes_Records(), &chest->base);
    int index = Chest_Index(chest);
    if (index == NO_CHEST) {
        return 1;
    }
    s16 value = (s16) RoomPushes_Facing(entry);
    Vec3 *destination = RoomPushes_Destination(entry);
    return RoomPlayerActor_RequestChestApproach(&index, &destination->x, &RoomPushes_Destination(entry)->z, &value);
}

/* The common update of CHEST_MENU_ANNOUNCE and CHEST_TALK_ANNOUNCE: `next` for a chest without
 * an index, else once RoomPlayerActor_TestFlag2 says so. */
static void Chest_wait_announce(Chest *chest, int next)
{
    if (Chest_Index(chest) == NO_CHEST) {
        Chest_EnterTalkStep(chest, next);
    } else if (RoomPlayerActor_TestFlag2() != 0) {
        Chest_EnterTalkStep(chest, next);
    }
}

/* _ZN18Obj_ov004_0225211c19func_ov004_02216c60Ev (update of CHEST_TALK_CLOSE): once the lid is
 * closed, hands the receiver back (SceneObjectBase_ReleaseReceiver) and lets the scene go on (EventQueue_FinishObjectEvent). The
 * step stays until the scene sets another. */
void Chest_UpdateTalkClose(Chest *chest)
{
    if (chest->lid == CHEST_LID_CLOSED) {
        SceneObjectBase_ReleaseReceiver(&chest->base.scene, Chest_receiver(chest));
        EventQueue_FinishObjectEvent(chest);
    }
}
CLEAN_AS(_ZN18Obj_ov004_0225211c19func_ov004_02216c60Ev, Chest_UpdateTalkClose)

/* func_ov004_02216c8c (entry of CHEST_TALK_CLOSE): message 0x2f, then the lid closing. */
int Chest_EnterTalkClose(Chest *chest)
{
    return Chest_close(chest);
}
CLEAN_AS(func_ov004_02216c8c, Chest_EnterTalkClose)

/* func_ov004_02216cd0 (update of CHEST_TALK_END): on once the link has closed. */
void Chest_UpdateTalkEnd(Chest *chest)
{
    if (Chest_link_closed(chest)) {
        Chest_EnterTalkStep(chest, CHEST_TALK_CLOSE);
    }
}
CLEAN_AS(func_ov004_02216cd0, Chest_UpdateTalkEnd)

/* func_ov004_02216cf4 (entry of CHEST_TALK_END) */
int Chest_EnterTalkEnd(Chest *chest)
{
    (void) chest;
    return 1;
}
CLEAN_AS(func_ov004_02216cf4, Chest_EnterTalkEnd)

/* func_ov004_02216cf8 (update of CHEST_TALK): on once the link has opened. */
void Chest_UpdateTalk(Chest *chest)
{
    if (Chest_link_open(chest)) {
        Chest_EnterTalkStep(chest, CHEST_TALK_END);
    }
}
CLEAN_AS(func_ov004_02216cf8, Chest_UpdateTalk)

/* The item on cell (x, y) of the town's map, layer 0. */
static u16 *Chest_item_on_cell(void *map, s32 x, s32 y)
{
    return AcreTile_ItemInAcre(map, shift_right(x, 4), shift_right(y, 4), x & (BLOCK_CELLS - 1), y & (BLOCK_CELLS - 1), 0);
}

/* func_ov004_02216d1c (entry of CHEST_TALK): takes the receiver (SceneObjectBase_TakeReceiver), raises the
 * link's request and names the receiver "obj_etc_nchest". Its state byte is set to one of 16
 * values: the furniture's number plus the scene, plus x + 16 y of the first of its cells that
 * holds an item ItemCode_HasVariant tells (on the town's map, when there is one).
 * REQUIRES: the receiver has a link once SceneObjectBase_TakeReceiver has taken it. */
int Chest_EnterTalk(Chest *chest)
{
    RoomObject *base = &chest->base;
    SceneObjectBase_TakeReceiver(&chest->base.scene, Chest_receiver(chest));
    base->link->next_state = 1;
    MessageReceiver_SetName(&base->receiver.base, data_ov004_02253200);
    int number = RoomObject_Number(base);
    int line = (number + SceneQuery_Current()) & (LINE_COUNT - 1);
    CellList cells;
    CellList_Construct(&cells);
    RoomObject_ListCells(base, &cells, NULL, 0);
    void *map = data_021c80bc;
    if (map != NULL) {
        for (unsigned long i = 0; i < CellList_Count(&cells); i++) {
            s32 x = CellList_At(&cells, (int) i)->x;
            s32 y = CellList_At(&cells, (int) i)->y;
            u16 *item = Chest_item_on_cell(map, x, y);
            if (item != NULL && ItemCode_HasVariant(item) != 0) {
                line = (line + x + y * BLOCK_CELLS) & (LINE_COUNT - 1);
                break;
            }
        }
    }
    base->receiver_state = (u8) line;
    CellList_Destruct(&cells);
    return 1;
}
CLEAN_AS(func_ov004_02216d1c, Chest_EnterTalk)

/* func_ov004_02216df0 (update of CHEST_TALK_OPEN): talks once the lid is open. */
void Chest_UpdateTalkOpen(Chest *chest)
{
    if (chest->lid == CHEST_LID_OPEN) {
        Chest_EnterTalkStep(chest, CHEST_TALK);
    }
}
CLEAN_AS(func_ov004_02216df0, Chest_UpdateTalkOpen)

/* func_ov004_02216e0c (entry of CHEST_TALK_OPEN): the lid opening requested; its answer. */
int Chest_EnterTalkOpen(Chest *chest)
{
    return Chest_request(chest, CHEST_LID_OPENING);
}
CLEAN_AS(func_ov004_02216e0c, Chest_EnterTalkOpen)

/* func_ov004_02216e20 (update of CHEST_TALK_ANNOUNCE): opens once the message is through. */
void Chest_UpdateTalkAnnounce(Chest *chest)
{
    Chest_wait_announce(chest, CHEST_TALK_OPEN);
}
CLEAN_AS(func_ov004_02216e20, Chest_UpdateTalkAnnounce)

/* func_ov004_02216e50 (entry of CHEST_TALK_ANNOUNCE): message 0x2d; never refused. */
int Chest_EnterTalkAnnounce(Chest *chest)
{
    Chest_announce(chest);
    return 1;
}
CLEAN_AS(func_ov004_02216e50, Chest_EnterTalkAnnounce)

/* func_ov004_02216ea8 (update of CHEST_TALK_NEXT) */
void Chest_UpdateTalkNext(Chest *chest)
{
    Chest_EnterTalkStep(chest, CHEST_TALK_ANNOUNCE);
}
CLEAN_AS(func_ov004_02216ea8, Chest_UpdateTalkNext)

/* func_ov004_02216eb4 (entry of CHEST_TALK_NEXT) */
int Chest_EnterTalkNext(Chest *chest)
{
    (void) chest;
    return 1;
}
CLEAN_AS(func_ov004_02216eb4, Chest_EnterTalkNext)

/* func_ov004_02216eb8 (update of CHEST_MENU_CLOSE): once the lid is closed, lets the scene go on.
 * The step stays until the scene sets another. */
void Chest_UpdateMenuClose(Chest *chest)
{
    if (chest->lid == CHEST_LID_CLOSED) {
        EventQueue_FinishObjectEvent(chest);
    }
}
CLEAN_AS(func_ov004_02216eb8, Chest_UpdateMenuClose)

/* func_ov004_02216ed4 (entry of CHEST_MENU_CLOSE): message 0x2f, then the lid closing. */
int Chest_EnterMenuClose(Chest *chest)
{
    return Chest_close(chest);
}
CLEAN_AS(func_ov004_02216ed4, Chest_EnterMenuClose)

/* func_ov004_02216f18 (update of CHEST_MENU): once group 9 can be opened again (the menu has
 * closed), closes; whether it did (0 while the menu is open). */
int Chest_UpdateMenu(Chest *chest)
{
    int closed = GroupParams_CanOpen();
    if (closed != 0) {
        return Chest_EnterTalkStep(chest, CHEST_MENU_CLOSE);
    }
    return closed;
}
CLEAN_AS(func_ov004_02216f18, Chest_UpdateMenu)

/* func_ov004_02216f34 (entry of CHEST_MENU): opens group 9 in mode 0x22; refused when it cannot
 * be opened. */
int Chest_EnterMenu(Chest *chest)
{
    (void) chest;
    return GroupParams_Open(MENU_MODE) ? 1 : 0;
}
CLEAN_AS(func_ov004_02216f34, Chest_EnterMenu)

/* func_ov004_02216f50 (update of CHEST_MENU_OPEN): opens the menu once the lid is open. */
void Chest_UpdateMenuOpen(Chest *chest)
{
    if (chest->lid == CHEST_LID_OPEN) {
        Chest_EnterTalkStep(chest, CHEST_MENU);
    }
}
CLEAN_AS(func_ov004_02216f50, Chest_UpdateMenuOpen)

/* func_ov004_02216f6c (entry of CHEST_MENU_OPEN): the lid opening requested; its answer. */
int Chest_EnterMenuOpen(Chest *chest)
{
    return Chest_request(chest, CHEST_LID_OPENING);
}
CLEAN_AS(func_ov004_02216f6c, Chest_EnterMenuOpen)

/* func_ov004_02216f80 (update of CHEST_MENU_ANNOUNCE): opens once the message is through. */
void Chest_UpdateMenuAnnounce(Chest *chest)
{
    Chest_wait_announce(chest, CHEST_MENU_OPEN);
}
CLEAN_AS(func_ov004_02216f80, Chest_UpdateMenuAnnounce)

/* func_ov004_02216fb0 (entry of CHEST_MENU_ANNOUNCE): message 0x2d; refused when it was not
 * sent. */
int Chest_EnterMenuAnnounce(Chest *chest)
{
    return Chest_announce(chest) != 0 ? 1 : 0;
}
CLEAN_AS(func_ov004_02216fb0, Chest_EnterMenuAnnounce)

/* func_ov004_02217010 (update of CHEST_MENU_NEXT) */
void Chest_UpdateMenuNext(Chest *chest)
{
    Chest_EnterTalkStep(chest, CHEST_MENU_ANNOUNCE);
}
CLEAN_AS(func_ov004_02217010, Chest_UpdateMenuNext)

/* func_ov004_0221701c (entry of CHEST_MENU_NEXT) */
int Chest_EnterMenuNext(Chest *chest)
{
    (void) chest;
    return 1;
}
CLEAN_AS(func_ov004_0221701c, Chest_EnterMenuNext)

/* func_ov004_02217020 (update of CHEST_TALK_NONE) */
void Chest_UpdateTalkNone(Chest *chest)
{
    (void) chest;
}
CLEAN_AS(func_ov004_02217020, Chest_UpdateTalkNone)

/* func_ov004_02217024 (entry of CHEST_TALK_NONE) */
int Chest_EnterTalkNone(Chest *chest)
{
    (void) chest;
    return 1;
}
CLEAN_AS(func_ov004_02217024, Chest_EnterTalkNone)

/* _ZN18Obj_ov004_0225211c19func_ov004_02217028Ev: the talk step's update, through its table.
 * REQUIRES: the step is not negative (Chest_EnterTalkStep only sets 0 to 11). */
void Chest_UpdateTalkStep(Chest *chest)
{
    static const MemberPointer *const updates[CHEST_TALK_STEP_COUNT] = {
        &data_ov004_02250588, /* Chest_UpdateTalkNone */
        &data_ov004_022501b8, /* Chest_UpdateMenuNext */
        &data_ov004_02250048, /* Chest_UpdateMenuAnnounce */
        &data_ov004_02250570, /* Chest_UpdateMenuOpen */
        &data_ov004_02250568, /* Chest_UpdateMenu, its result dropped */
        &data_ov004_02250560, /* Chest_UpdateMenuClose */
        &data_ov004_02250558, /* Chest_UpdateTalkNext */
        &data_ov004_02250550, /* Chest_UpdateTalkAnnounce */
        &data_ov004_02250548, /* Chest_UpdateTalkOpen */
        &data_ov004_02250540, /* Chest_UpdateTalk */
        &data_ov004_02250538, /* Chest_UpdateTalkEnd */
        &data_ov004_02250530, /* Chest_UpdateTalkClose */
    };
    MemberTable_InitOnce(&data_ov004_02257024, data_ov004_0225766c, updates, CHEST_TALK_STEP_COUNT);
    int step = chest->talk_step;
    if (step >= 0 && step < CHEST_TALK_STEP_COUNT) {
        MemberPointer_CallVoid(&data_ov004_0225766c[step], chest);
    }
}
CLEAN_AS(_ZN18Obj_ov004_0225211c19func_ov004_02217028Ev, Chest_UpdateTalkStep)

/* func_ov004_02217124: enters talk step `step` if its entry (through a table) agrees; whether it
 * did.
 * REQUIRES: `step` is not negative (the game passes the constants 0 to 11); for a negative step
 * the original reads a member pointer from before its table. */
int Chest_EnterTalkStep(Chest *chest, int step)
{
    static const MemberPointer *const entries[CHEST_TALK_STEP_COUNT] = {
        &data_ov004_02250638, /* Chest_EnterTalkNone */
        &data_ov004_022505f0, /* Chest_EnterMenuNext */
        &data_ov004_022501f0, /* Chest_EnterMenuAnnounce */
        &data_ov004_022505e0, /* Chest_EnterMenuOpen */
        &data_ov004_022501e8, /* Chest_EnterMenu */
        &data_ov004_022505d0, /* Chest_EnterMenuClose */
        &data_ov004_022505c8, /* Chest_EnterTalkNext */
        &data_ov004_022505c0, /* Chest_EnterTalkAnnounce */
        &data_ov004_022501d8, /* Chest_EnterTalkOpen */
        &data_ov004_022505b0, /* Chest_EnterTalk */
        &data_ov004_022505a8, /* Chest_EnterTalkEnd */
        &data_ov004_022505a0, /* Chest_EnterTalkClose */
    };
    MemberTable_InitOnce(&data_ov004_02256ff4, data_ov004_0225760c, entries, CHEST_TALK_STEP_COUNT);
    if (step >= 0 && step < CHEST_TALK_STEP_COUNT && MemberPointer_CallInt(&data_ov004_0225760c[step], chest) != 0) {
        chest->talk_step = step;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02217124, Chest_EnterTalkStep)

/* func_ov004_02217230: which of the chests 0 to 2 it is by its kind, -1 for none. */
int Chest_Index(Chest *chest)
{
    for (unsigned int i = 0; i < CHEST_COUNT; i++) {
        if (chest->base.unk_780 == (u32) data_ov004_022476a4[i]) {
            return (int) i;
        }
    }
    return NO_CHEST;
}
CLEAN_AS(func_ov004_02217230, Chest_Index)

/* func_ov004_02217264 (vtable slot 0x4c): the scene's answer to EventQueue_RequestKind6. Event 1 starts
 * the menu when SceneKinds_CurrentIsHouseRoom and Room_Check0220fed0 allow it, else the talk; event 8 ends
 * either; others do nothing. */
void Chest_OnSceneEvent(Chest *chest, int event)
{
    switch (event) {
        case 1:
            if (SceneKinds_CurrentIsHouseRoom() != 0 && Room_Check0220fed0() != 0) {
                Chest_EnterTalkStep(chest, CHEST_MENU_NEXT);
            } else {
                Chest_EnterTalkStep(chest, CHEST_TALK_NEXT);
            }
            break;
        case 8:
            Chest_EnterTalkStep(chest, CHEST_TALK_NONE);
            break;
    }
}
CLEAN_AS(func_ov004_02217264, Chest_OnSceneEvent)

/* func_ov004_022172ac (update of CHEST_LID_CLOSING): the node set's value 1; closed once the
 * animations have ended. */
void Chest_UpdateLidClosing(Chest *chest)
{
    ByteSet_SetValue(&chest->base.node_set, 1);
    if (RoomObject_AdvanceAnims(&chest->base) != 0) {
        Chest_switch_to(chest, CHEST_LID_CLOSED);
    }
}
CLEAN_AS(func_ov004_022172ac, Chest_UpdateLidClosing)

/* func_ov004_022172dc (entry of CHEST_LID_CLOSING): the switch on (shown at once) and sound 2;
 * kind 0xf plays the animations of variant 1 once from the start, the others those of variant
 * 0 in mode 3 from the end. */
int Chest_EnterLidClosing(Chest *chest)
{
    RoomObject *base = &chest->base;
    Switch_Set(&base->light_switch, 1, 0);
    RoomObject_PlaySound2(base);
    if (base->unk_780 == KIND_0F) {
        RoomObject_PlayAnimsFrom(base, 1, ANIM_MODE_ONCE, ONE, 0);
    } else {
        RoomObject_PlayAnimsFromEnd(base, 0, ANIM_MODE_3, ONE);
    }
    return 1;
}
CLEAN_AS(func_ov004_022172dc, Chest_EnterLidClosing)

/* func_ov004_02217330 (update of CHEST_LID_OPEN): the node set's value 1; in mode 2 (unk_76C) it
 * closes at once. */
void Chest_UpdateLidOpen(Chest *chest)
{
    ByteSet_SetValue(&chest->base.node_set, 1);
    if (RoomObject_Unk76CIs2(&chest->base)) {
        Chest_switch_to(chest, CHEST_LID_CLOSING);
    }
}
CLEAN_AS(func_ov004_02217330, Chest_UpdateLidOpen)

/* func_ov004_02217360 (entry of CHEST_LID_OPEN): the switch off (shown at once); the animations
 * of variant 0 shown at their end.
 * QUIRK: kind 0xf also asks for its joint animation (AnimSet_Anim00) and does not use it. */
int Chest_EnterLidOpen(Chest *chest)
{
    RoomObject *base = &chest->base;
    Switch_Set(&base->light_switch, 0, 0);
    if (base->unk_780 == KIND_0F) {
        AnimSet_Anim00(FurnitureModel_Anims(&base->model_files), 0);
    }
    RoomObject_PlayAnimsFromEnd(base, 0, ANIM_MODE_ONCE, ONE);
    return 1;
}
CLEAN_AS(func_ov004_02217360, Chest_EnterLidOpen)

/* func_ov004_022173b8 (update of CHEST_LID_OPENING): the node set's value 1; open once the
 * animations have ended. */
void Chest_UpdateLidOpening(Chest *chest)
{
    ByteSet_SetValue(&chest->base.node_set, 1);
    if (RoomObject_AdvanceAnims(&chest->base) != 0) {
        Chest_switch_to(chest, CHEST_LID_OPEN);
    }
}
CLEAN_AS(func_ov004_022173b8, Chest_UpdateLidOpening)

/* func_ov004_022173e8 (entry of CHEST_LID_OPENING): the switch off (shown at once), sound 1, and
 * the animations of variant 0 played once from the start. */
int Chest_EnterLidOpening(Chest *chest)
{
    RoomObject *base = &chest->base;
    Switch_Set(&base->light_switch, 0, 0);
    RoomObject_PlaySound1(base);
    RoomObject_PlayAnimsFrom(base, 0, ANIM_MODE_ONCE, ONE, 0);
    return 1;
}
CLEAN_AS(func_ov004_022173e8, Chest_EnterLidOpening)

/* Whether a cell one step in front of each of the chest's cells holds something; it is turned
 * back on when one does. */
static int Chest_front_blocked(Chest *chest)
{
    RoomObject *base = &chest->base;
    CellList cells;
    CellList_Construct(&cells);
    RoomObject_ListCells(base, &cells, NULL, 0);
    Vec3 ahead = {0, 0, STEP};
    Vec_RotateY(&ahead, base->angle);
    s32 dx = shift_right(ahead.x, STEP_SHIFT);
    s32 dy = shift_right(ahead.z, STEP_SHIFT);
    for (unsigned long i = 0; i < CellList_Count(&cells); i++) {
        s32 x = dx + CellList_At(&cells, (int) i)->x;
        s32 y = dy + CellList_At(&cells, (int) i)->y;
        if (RoomObjects_HeightAtCell(x, y) != 0 || CollisionMap_UnclaimedObjectAt(x, y) != -1) {
            Switch_Set(&base->light_switch, 1, 0);
            CellList_Destruct(&cells);
            return 1;
        }
    }
    CellList_Destruct(&cells);
    return 0;
}

/* func_ov004_02217420 (update of CHEST_LID_CLOSED): the node set's value 0. When touched, with an
 * entry that RoomPushes_Side does not hold back, it asks the scene for an event
 * (EventQueue_RequestKind6, then PlayerActorOps_SetOwnFlag17); a chest of kind 0xb only when the cells in front of it
 * are free, else its switch is put back on. Otherwise in mode 2 (unk_76C) it opens at once. */
void Chest_UpdateLidClosed(Chest *chest)
{
    RoomObject *base = &chest->base;
    ByteSet_SetValue(&base->node_set, 0);
    void *entry = RoomPushes_FindObject(RoomPushes_Records(), &chest->base);
    if (Switch_IsPending(&base->light_switch) && entry != NULL && RoomPushes_Side(entry) == 0) {
        if (base->unk_780 == KIND_0B && Chest_front_blocked(chest)) {
            return;
        }
        EventQueue_RequestKind6(chest, 0);
        PlayerActorOps_SetOwnFlag17();
    } else if (RoomObject_Unk76CIs2(base)) {
        Chest_switch_to(chest, CHEST_LID_OPENING);
    }
}
CLEAN_AS(func_ov004_02217420, Chest_UpdateLidClosed)

/* func_ov004_02217534 (entry of CHEST_LID_CLOSED): the switch on (shown at once); kind 0xf shows
 * the animations of variant 1 at their end, the others those of variant 0 in mode 3 from the
 * start. */
int Chest_EnterLidClosed(Chest *chest)
{
    RoomObject *base = &chest->base;
    Switch_Set(&base->light_switch, 1, 0);
    if (base->unk_780 == KIND_0F) {
        RoomObject_PlayAnimsFromEnd(base, 1, ANIM_MODE_ONCE, ONE);
    } else {
        RoomObject_PlayAnimsFrom(base, 0, ANIM_MODE_3, ONE, 0);
    }
    return 1;
}
CLEAN_AS(func_ov004_02217534, Chest_EnterLidClosed)

/* _ZN18Obj_ov004_0225211c19func_ov004_02217580Ev: the lid's update, through its table. */
void Chest_UpdateLid(Chest *chest)
{
    static const MemberPointer *const updates[CHEST_LID_STATE_COUNT] = {
        &data_ov004_02250608, /* Chest_UpdateLidClosed */
        &data_ov004_02250610, /* Chest_UpdateLidOpening */
        &data_ov004_02250618, /* Chest_UpdateLidOpen */
        &data_ov004_02250620, /* Chest_UpdateLidClosing */
    };
    MemberTable_InitOnce(&data_ov004_02257014, data_ov004_022574ec, updates, CHEST_LID_STATE_COUNT);
    if (chest->lid < CHEST_LID_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_022574ec[chest->lid], chest);
    }
}
CLEAN_AS(_ZN18Obj_ov004_0225211c19func_ov004_02217580Ev, Chest_UpdateLid)

/* func_ov004_0221760c (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given `state`
 * and `value`), then enters lid state `state` if its entry (through a table) agrees; whether it
 * did. States 4 and above do not exist. */
int Chest_EnterLid(Chest *chest, unsigned int state, int value)
{
    static const MemberPointer *const entries[CHEST_LID_STATE_COUNT] = {
        &data_ov004_022505b8, /* Chest_EnterLidClosed */
        &data_ov004_022505d8, /* Chest_EnterLidOpening */
        &data_ov004_02250650, /* Chest_EnterLidOpen */
        &data_ov004_02250648, /* Chest_EnterLidClosing */
    };
    RoomObject_SetUnk77C(&chest->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_02257020, data_ov004_022574cc, entries, CHEST_LID_STATE_COUNT);
    if (state < CHEST_LID_STATE_COUNT && MemberPointer_CallInt(&data_ov004_022574cc[state], chest) != 0) {
        chest->lid = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221760c, Chest_EnterLid)

/* func_ov004_022176ac (vtable slot 0x74): whether lid state `state` shows the switch on (closed
 * and closing do); 0 for a state that does not exist. */
u8 Chest_LidStateIsOn(Chest *chest, unsigned int state)
{
    (void) chest;
    if (state < CHEST_LID_STATE_COUNT) {
        return data_ov004_02247680[state];
    }
    return 0;
}
CLEAN_AS(func_ov004_022176ac, Chest_LidStateIsOn)

/* func_ov004_022176c0 (vtable slot 0xa0): idle as the base class tells, and not talking. */
int Chest_IsIdle(Chest *chest)
{
    return RoomObject_IsIdle(&chest->base) && chest->talk_step == CHEST_TALK_NONE;
}
CLEAN_AS(func_ov004_022176c0, Chest_IsIdle)

/* func_ov004_022176e4 (vtable slot 0x0c) */
int Chest_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022176e4, Chest_Vfunc0C)

/* _ZN18Obj_ov004_0225211c19func_ov004_022176e8Ev (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): the talk, then the lid. */
int Chest_Update(Chest *chest)
{
    Chest_UpdateTalkStep(chest);
    Chest_UpdateLid(chest);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_0225211c19func_ov004_022176e8Ev, Chest_Update)

/* func_ov004_02217700 (vtable slot 0x7c, once the model is bound): the node set's value 0; in
 * mode 1 (unk_76C) the switch is set on first. The animations of variant 0 are bound (kind 0xf
 * to play once, the others in mode 3); the lid starts closed when the switch is on or
 * RoomObjects_InNookOrScene0AOr0F says so, else open; and the chest is not talking. Done at once. */
int Chest_Start(Chest *chest)
{
    RoomObject *base = &chest->base;
    ByteSet_SetValue(&base->node_set, 0);
    if (base->unk_76C == 1) {
        Switch_Set(&base->light_switch, 1, 0);
    }
    if (base->unk_780 == KIND_0F) {
        RoomObject_LoadAnims(base, 0, ANIM_MODE_ONCE, ONE, 0);
    } else {
        RoomObject_LoadAnims(base, 0, ANIM_MODE_3, ONE, 0);
    }
    if (Switch_Value(&base->light_switch) != 0 || RoomObjects_InNookOrScene0AOr0F() != 0) {
        Chest_switch_to(chest, CHEST_LID_CLOSED);
    } else {
        Chest_switch_to(chest, CHEST_LID_OPEN);
    }
    Chest_EnterTalkStep(chest, CHEST_TALK_NONE);
    return 1;
}
CLEAN_AS(func_ov004_02217700, Chest_Start)

static void Chest_set_vtables(Chest *chest)
{
    chest->base.vtable = (const RoomObjectVtable *) data_ov004_0225211c;
    chest->base.receiver_vtable = data_ov004_022521c8;
}

/* func_ov004_022177a0 (the deleting destructor, vtable slot 0x44) */
Chest *Chest_Delete(Chest *chest)
{
    Chest_set_vtables(chest);
    Glow_Destruct(&chest->unk_844);
    RoomObject_DestructBase(&chest->base);
    RoomObject_Free(chest);
    return chest;
}
CLEAN_AS(func_ov004_022177a0, Chest_Delete)

/* func_ov004_022177d8 (the destructor, vtable slot 0x40) */
Chest *Chest_Destroy(Chest *chest)
{
    Chest_set_vtables(chest);
    Glow_Destruct(&chest->unk_844);
    RoomObject_DestructBase(&chest->base);
    return chest;
}
CLEAN_AS(func_ov004_022177d8, Chest_Destroy)

/* func_ov004_0221780c (the constructor): the lid closed; the talk step is left as the
 * allocation zeroed it (CHEST_TALK_NONE). */
Chest *Chest_Construct(Chest *chest)
{
    RoomObject_ConstructBase(&chest->base);
    Chest_set_vtables(chest);
    Glow_Construct(&chest->unk_844);
    chest->lid = CHEST_LID_CLOSED;
    return chest;
}
CLEAN_AS(func_ov004_0221780c, Chest_Construct)

/* func_ov004_02217848: a new chest from the room's heap; nothing when it has no room. */
void Chest_Create(void)
{
    Chest *chest = RoomObject_Alloc(CHEST_SIZE);
    if (chest != NULL) {
        Chest_Construct(chest);
    }
}
CLEAN_AS(func_ov004_02217848, Chest_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters Chest's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static Chest *Chest_from_receiver(void *receiver)
{
    return (Chest *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a794: the deleting destructor, entered from the receiver part. */
Chest *ChestReceiver_Delete(void *receiver)
{
    return Chest_Delete(Chest_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_0225211cD0Ev, ChestReceiver_Delete)

/* func_ov004_0221a7b0: the destructor, entered from the receiver part. */
Chest *ChestReceiver_Destroy(void *receiver)
{
    return Chest_Destroy(Chest_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_0225211cD1Ev, ChestReceiver_Destroy)
