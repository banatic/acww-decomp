/* The nameplate of a villager's house (villager_nameplate.h). */
#include "villager_nameplate.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"
#include "autoload_2/heap.h"
#include "autoload_2/vector.h"
#include "main/event_queue.h"
#include "main/message_receiver.h"
#include "main/npc_id.h"
#include "main/player_id.h"
#include "main/scene_object_base.h"
#include "main/scene_query.h"
#include "main/talk_object.h"
#include "main/talk_receiver.h"
#include "main/touch_pick_shapes.h"
#include "main/town_villager.h"
#include "main/villager_roster.h"

static_assert(offsetof(VillagerNameplate, index) == 0x08, "index");
static_assert(offsetof(VillagerNameplate, position) == 0x5c, "position");
static_assert(offsetof(VillagerNameplate, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(VillagerNameplate, receiver_name) == 0xf0, "receiver name");
static_assert(offsetof(VillagerNameplate, receiver_unk_1e) == 0x10a, "receiver byte 0x1e");
static_assert(offsetof(VillagerNameplate, link) == 0x12c, "link");
static_assert(offsetof(VillagerNameplate, state) == 0x134, "state");
static_assert(offsetof(VillagerNameplate, member_138) == 0x138, "member");
static_assert(sizeof(VillagerNameplate) == 0x154, "size");
static_assert(offsetof(VillagerNameplateViewer, yaw) == 0x8e, "yaw");

/* The boards by index, and how many there are. */
extern VillagerNameplate *data_ov003_0223c5f4[VILLAGER_NAMEPLATE_MAX];
extern u8 data_ov003_0223c5a0;

/* The vtables: the class's, and its receiver part's. */
extern const u8 data_ov003_02238010[];
extern const u8 data_ov003_02238078[];
/* "obj_etc_board" */
extern const char data_ov003_022380f0[];
/* The table whose entry `index` the board shows (eight entries of 0x7ec bytes). */
extern u8 data_021e5a2c[];

/* The receiver part of a board, as a C++ conversion makes it: null stays null. */
static void *receiver_of(VillagerNameplate *board)
{
    return board != NULL ? (void *) &board->receiver_vtable : NULL;
}

/* func_ov003_0220bf00: the board with `index`, or null when there is none or `index` is out of
 * 0-7. */
VillagerNameplate *VillagerNameplate_Get(int index)
{
    if (index >= 0 && index < VILLAGER_NAMEPLATE_MAX) {
        return data_ov003_0223c5f4[index];
    }
    return NULL;
}
CLEAN_AS(func_ov003_0220bf00, VillagerNameplate_Get)

/* func_ov003_0220bf18: state 2's update. Once the link has closed, the receiver is released. */
void VillagerNameplate_UpdateOpen(VillagerNameplate *board)
{
    if (board->link != NULL && board->link->open == 0) {
        SceneObjectBase_ReleaseReceiver((SceneObjectBase *) board, receiver_of(board));
        EventQueue_FinishObjectEvent(board);
    }
}
CLEAN_AS(func_ov003_0220bf18, VillagerNameplate_UpdateOpen)

/* func_ov003_0220bf48: entering state 2 always succeeds. */
int VillagerNameplate_EnterOpen(VillagerNameplate *board)
{
    (void) board;
    return 1;
}
CLEAN_AS(func_ov003_0220bf48, VillagerNameplate_EnterOpen)

/* func_ov003_0220bf4c: state 1's update: on to state 2 once the link has opened. */
void VillagerNameplate_UpdateWaiting(VillagerNameplate *board)
{
    if (board->link != NULL && board->link->open != 0) {
        VillagerNameplate_SetState(board, VILLAGER_NAMEPLATE_OPEN);
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223801019func_ov003_0220bf4cEv, VillagerNameplate_UpdateWaiting)

/* func_ov003_0220bf70: entering state 1 (always succeeds). The receiver is taken and named,
 * and the link gets the text of the board's table entry with its request raised. */
int VillagerNameplate_EnterWaiting(VillagerNameplate *board)
{
    u8 text[0x24];

    SceneObjectBase_TakeReceiver((SceneObjectBase *) board, receiver_of(board));
    MessageReceiver_SetName((MessageReceiver *) &board->receiver_vtable, data_ov003_022380f0);
    board->receiver_unk_1e = 0;
    board->link->requested = 1;

    PlayerIdText_Construct((PlayerIdText *) text);
    NpcId_FormatName(TownVillager_NpcId(VillagerRoster_At((VillagerTown *) data_021e5a2c, (int) board->index)), (char *) text);
    TalkObject_SetPart((TalkObject *) board->link, 0, (TextBase *) text);
    PlayerIdText_Destruct((PlayerIdText *) text);
    return 1;
}
CLEAN_AS(func_ov003_0220bf70, VillagerNameplate_EnterWaiting)

/* func_ov003_0220bfe0: state 0's update does nothing. */
void VillagerNameplate_UpdateIdle(VillagerNameplate *board)
{
    (void) board;
}
CLEAN_AS(func_ov003_0220bfe0, VillagerNameplate_UpdateIdle)

/* func_ov003_0220bfe4: entering state 0 always succeeds. */
int VillagerNameplate_EnterIdle(VillagerNameplate *board)
{
    (void) board;
    return 1;
}
CLEAN_AS(func_ov003_0220bfe4, VillagerNameplate_EnterIdle)

/* func_ov003_0220bfe8: the update of the current state (the ROM picks it from a table of member
 * function pointers). REQUIRES: the state is 0-2, as VillagerNameplate_SetState leaves it; the ROM
 * reads before its table for a negative one, while this does nothing. */
void VillagerNameplate_Update(VillagerNameplate *board)
{
    switch (board->state) {
        case VILLAGER_NAMEPLATE_IDLE:
            VillagerNameplate_UpdateIdle(board);
            break;
        case VILLAGER_NAMEPLATE_WAITING:
            VillagerNameplate_UpdateWaiting(board);
            break;
        case VILLAGER_NAMEPLATE_OPEN:
            VillagerNameplate_UpdateOpen(board);
            break;
        default:
            break;
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223801019func_ov003_0220bfe8Ev, VillagerNameplate_Update)

/* func_ov003_0220c064: moves to `state` when entering it succeeds; whether it did.
 * REQUIRES: `state` is not negative (the callers pass 0-2); the ROM reads before its table of
 * entry functions for a negative one, while this refuses it. */
int VillagerNameplate_SetState(VillagerNameplate *board, int state)
{
    int entered;

    switch (state) {
        case VILLAGER_NAMEPLATE_IDLE:
            entered = VillagerNameplate_EnterIdle(board);
            break;
        case VILLAGER_NAMEPLATE_WAITING:
            entered = VillagerNameplate_EnterWaiting(board);
            break;
        case VILLAGER_NAMEPLATE_OPEN:
            entered = VillagerNameplate_EnterOpen(board);
            break;
        default:
            return 0;
    }
    if (entered) {
        board->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(_ZN18Obj_ov003_0223801019func_ov003_0220c064Ei, VillagerNameplate_SetState)

/* func_ov003_0220c0f0 (vtable slot 0x4c): event 0 starts the board (state 1), event 8 stops it
 * (state 0); other events are ignored. */
void VillagerNameplate_HandleEvent(VillagerNameplate *board, int event)
{
    switch (event) {
        case 0:
            VillagerNameplate_SetState(board, VILLAGER_NAMEPLATE_WAITING);
            break;
        case 8:
            VillagerNameplate_SetState(board, VILLAGER_NAMEPLATE_IDLE);
            break;
        default:
            break;
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223801019func_ov003_0220c0f0Ei, VillagerNameplate_HandleEvent)

/* func_ov003_0220c114 (vtable slot 0x48): whether `viewer` stands within 0x2333 of the board
 * facing within 0x1100 of angle 0x8000. func_0203edd0 runs on the board first in any case. */
int VillagerNameplate_IsFacedBy(VillagerNameplate *board, const VillagerNameplateViewer *viewer)
{
    SceneObjectBase_ClearApproach((SceneObjectBase *) board);
    return viewer != NULL && Vec_DistanceXZ(&viewer->position, &board->position) < 0x2333 &&
           Math_AbsDiff16(-0x8000, viewer->yaw) <= 0x1100;
}
CLEAN_AS(func_ov003_0220c114, VillagerNameplate_IsFacedBy)

/* func_ov003_0220c160: empties the table when no board is counted in it. */
void VillagerNameplate_ClearTableIfEmpty(void)
{
    if (data_ov003_0223c5a0 == 0) {
        for (int i = 0; i < VILLAGER_NAMEPLATE_MAX; i++) {
            data_ov003_0223c5f4[i] = NULL;
        }
    }
}
CLEAN_AS(func_ov003_0220c160, VillagerNameplate_ClearTableIfEmpty)

/* func_ov003_0220c184 (vtable slot 0x0c): takes the board out of the table; always 1.
 * REQUIRES: the board's index is 0-7, as VillagerNameplate_Init entered it. QUIRK: the count is a byte
 * and wraps below 0. */
int VillagerNameplate_Unregister(VillagerNameplate *board)
{
    data_ov003_0223c5f4[board->index] = NULL;
    data_ov003_0223c5a0--;
    return 1;
}
CLEAN_AS(func_ov003_0220c184, VillagerNameplate_Unregister)

/* func_ov003_0220c1a4 (vtable slot 0x24): always 1. */
int VillagerNameplate_Slot24(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0220c1a4, VillagerNameplate_Slot24)

/* func_ov003_0220c1a8 (vtable slot 0x18): the state's update, then the member at 0x138 handed
 * to func_020b7d84 at the board's position, with 0xc00, 9 and the index's low byte; always 1. */
int VillagerNameplate_Run(VillagerNameplate *board)
{
    VillagerNameplate_Update(board);
    TouchPick_SetSphereAndAdd((TouchPick *) (uintptr_t) SceneQuery_FieldObject(), (TouchPickSphere *) board->member_138,
                              &board->position, 0xc00, 9, (u8) board->index);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov003_0223801019func_ov003_0220c1a8Ev, VillagerNameplate_Run)

/* func_ov003_0220c1e4 (vtable slot 0x00): starts the board idle and enters it in the table
 * under its index (emptying the table first when it holds none); always 1.
 * REQUIRES: the index is 0-7. */
int VillagerNameplate_Init(VillagerNameplate *board)
{
    VillagerNameplate_ClearTableIfEmpty();
    SceneObjectBase_SetId((SceneObjectBase *) board, (u16) board->index);
    VillagerNameplate_SetState(board, VILLAGER_NAMEPLATE_IDLE);
    data_ov003_0223c5f4[board->index] = board;
    data_ov003_0223c5a0++;
    return 1;
}
CLEAN_AS(_ZN18Obj_ov003_0223801019func_ov003_0220c1e4Ev, VillagerNameplate_Init)

/* func_ov003_0220c220: the deleting destructor: the member, the receiver part and the base
 * destroyed in turn, then the memory freed. */
VillagerNameplate *VillagerNameplate_Delete(VillagerNameplate *board)
{
    board->vtable = data_ov003_02238010;
    board->receiver_vtable = data_ov003_02238078;
    TouchPickSphere_Destruct2((TouchPickSphere *) board->member_138);
    TalkReceiver_Destruct((TalkReceiver *) &board->receiver_vtable);
    SceneObjectBase_DestructBase((SceneObjectBase *) board);
    Heap_FreeAux(board);
    return board;
}
CLEAN_AS(func_ov003_0220c220, VillagerNameplate_Delete)

/* func_ov003_0220c260: the destructor, without freeing. */
VillagerNameplate *VillagerNameplate_Destruct(VillagerNameplate *board)
{
    board->vtable = data_ov003_02238010;
    board->receiver_vtable = data_ov003_02238078;
    TouchPickSphere_Destruct2((TouchPickSphere *) board->member_138);
    TalkReceiver_Destruct((TalkReceiver *) &board->receiver_vtable);
    SceneObjectBase_DestructBase((SceneObjectBase *) board);
    return board;
}
CLEAN_AS(func_ov003_0220c260, VillagerNameplate_Destruct)

/* func_ov003_0220c29c: the constructor: the base and the receiver part, then the vtables and
 * the member at 0x138. */
VillagerNameplate *VillagerNameplate_Construct(VillagerNameplate *board)
{
    SceneObjectBase_Construct((SceneObjectBase *) board);
    TalkReceiver_ConstructBase((TalkReceiver *) &board->receiver_vtable);
    board->vtable = data_ov003_02238010;
    board->receiver_vtable = data_ov003_02238078;
    TouchPickSphere_Construct((TouchPickSphere *) board->member_138);
    return board;
}
CLEAN_AS(func_ov003_0220c29c, VillagerNameplate_Construct)

/* func_ov003_0220c2d4: allocates and constructs a board; nothing keeps the pointer here. */
void VillagerNameplate_New(void)
{
    VillagerNameplate *board = Heap_AllocAuxZeroed(sizeof(VillagerNameplate));
    if (board != NULL) {
        VillagerNameplate_Construct(board);
    }
}
CLEAN_AS(func_ov003_0220c2d4, VillagerNameplate_New)

/* The board a pointer to its receiver part belongs to. */
static VillagerNameplate *board_of(void *receiver)
{
    return (VillagerNameplate *) ((u8 *) receiver - offsetof(VillagerNameplate, receiver_vtable));
}

/* func_ov003_0220c2f0 (the receiver vtable's deleting destructor): VillagerNameplate_Delete on
 * the board around `receiver`. */
VillagerNameplate *VillagerNameplate_ReceiverDelete(void *receiver)
{
    return VillagerNameplate_Delete(board_of(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238010D0Ev, VillagerNameplate_ReceiverDelete)

/* func_ov003_0220c30c (the receiver vtable's destructor): VillagerNameplate_Destruct on the board
 * around `receiver`. */
VillagerNameplate *VillagerNameplate_ReceiverDestruct(void *receiver)
{
    return VillagerNameplate_Destruct(board_of(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238010D1Ev, VillagerNameplate_ReceiverDestruct)
