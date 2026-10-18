/* The room objects' states (room_object.h). */
#include "room_object.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"
#include "member_pointer.h"
#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "cells.h"
#include "dropped_items.h"
#include "furniture_mover.h"
#include "itcm/vector.h"
#include "main/furniture_info.h"
#include "main/g3d_resource.h"
#include "main/item_code.h"
#include "main/player_actors.h"
#include "main/session_players.h"
#include "room_manager.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_map.h"
#include "room_object_methods.h"
#include "room_objects.h"

static_assert(offsetof(RoomObjectVtable, vfunc_90) == 0x90, "vtable slot 0x90");
static_assert(offsetof(RoomObjectVtable, is_idle) == 0xa0, "vtable slot 0xa0");
static_assert(offsetof(RoomObject, unk_00C) == 0x0c, "unk_00C");
static_assert(offsetof(RoomObject, position) == 0x5c, "position");
static_assert(offsetof(RoomObject, angle) == 0x8e, "angle");
static_assert(offsetof(RoomObject, scale_x) == 0x150, "scale");
static_assert(offsetof(RoomObject, unk_15C) == 0x15c, "unk_15C");
static_assert(offsetof(RoomObject, timer) == 0x160, "timer");
static_assert(offsetof(RoomObject, wobble_amplitude) == 0x168, "wobble");
static_assert(offsetof(RoomObject, target_angle) == 0x16c, "target angle");
static_assert(offsetof(RoomObject, target_position) == 0x170, "target position");
static_assert(offsetof(RoomObject, mount) == 0x17c, "mount");
static_assert(offsetof(RoomObject, carried) == 0x18c, "carried items");
static_assert(offsetof(RoomObject, matrix) == 0x59c, "matrix");
static_assert(offsetof(RoomObject, light_switch) == 0x740, "switch");
static_assert(offsetof(RoomObject, nodes) == 0x742, "nodes");
static_assert(offsetof(RoomObject, glow) == 0x748, "glow");
static_assert(offsetof(RoomObject, node_set) == 0x764, "node set");
static_assert(offsetof(RoomObject, unk_76C) == 0x76c, "unk_76C");
static_assert(offsetof(RoomObject, unk_78D) == 0x78d, "unk_78D");
static_assert(offsetof(RoomObject, top_height) == 0x790, "top height");
static_assert(offsetof(RoomObject, move_flag) == 0x250, "move flag");
static_assert(offsetof(RoomObject, unk_284) == 0x284, "unk_284");
static_assert(offsetof(RoomObject, state) == 0x534, "state");
static_assert(offsetof(RoomObject, state_frames) == 0x770, "state frames");
static_assert(offsetof(RoomObject, unk_780) == 0x780, "unk_780");
static_assert(offsetof(RoomObject, unk_788) == 0x788, "unk_788");
static_assert(offsetof(RoomObject, pivot) == 0x144, "pivot");
static_assert(offsetof(RoomObject, push_box) == 0x62c, "push box");
static_assert(offsetof(RoomObject, model_files) == 0x6cc, "model files");
static_assert(offsetof(RoomObject, unk_784) == 0x784, "unk_784");

#define ONE 0x1000         /* 1 in 20.12 fixed point */
#define STEP 0x2000        /* one move */
#define HALF_TURN 0x8000   /* an angle (fx_math.h) */
#define TURN_SPEED 0x700   /* per frame */
#define SPIN_SPEED 0x400   /* per frame */
#define SHRINK_SPEED 0x400 /* of the scale, per frame */
#define NO_SOUND 0xffff    /* from RoomObject_MoveSound */
#define KIND_SILENT_MOVE 0x3d

/* The sounds (PlayerActors_OwnPlaySound). */
#define SOUND_TURN 0x4c4
#define SOUND_APPEAR 0x4c7
#define SOUND_VANISH 0x4c8

/* The state tables (member_pointer.h): guards, tables and their constants. */
extern u32 data_ov004_02256c74;
extern MemberPointer data_ov004_02256f5c[ROOM_OBJECT_STATE_COUNT];
extern const MemberPointer data_ov004_0224fd90, data_ov004_0224fd78, data_ov004_0224fd98, data_ov004_0224fda0,
    data_ov004_0224fdc0, data_ov004_0224fdb8, data_ov004_0224fde0, data_ov004_0224fd68, data_ov004_0224fd80;
extern u32 data_ov004_02256c60;
extern MemberPointer data_ov004_02256fa4[ROOM_OBJECT_STATE_COUNT];
extern const MemberPointer data_ov004_0224fd70, data_ov004_0224fd88, data_ov004_0224fde8, data_ov004_0224fdf0,
    data_ov004_0224fdd8, data_ov004_0224fda8, data_ov004_0224fdb0, data_ov004_0224fdc8, data_ov004_0224fdd0;

/* NitroSDK's table of sines and cosines, interleaved, for 4096 angles. */
extern const s16 FX_SinCosTable_[];

static_assert(sizeof(CellList) == 0x24, "the list func_ov004_0220db94 clears");

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

extern int func_ov004_0223b058(void *mover, void *member, Vec3 *position, int angle);
extern int func_ov004_0223b080(void *mover, void *member, Vec3 *position, int angle);

/* An arithmetic shift right, for negative values too. */
static s32 shift_right(s32 value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* |value|, where the most negative value stays itself (it wraps, as the ROM's negation). */
static s32 magnitude(s32 value)
{
    return value < 0 ? (s32) (0u - (u32) value) : value;
}

static s16 sine(u16 angle)
{
    return FX_SinCosTable_[(angle >> 4) * 2];
}

static void set_scale(RoomObject *object, fx32 scale)
{
    object->scale_z = scale;
    object->scale_y = object->scale_z;
    object->scale_x = object->scale_y;
}

/* func_ov004_0220c560 (update of ROOM_OBJECT_SPIN): turns by 0x400 a frame (unless unk_780 is
 * 0x23 to 0x25) and takes its scale from RoomObject_Number through FurnitureInfo_Scale, over
 * 100 and a quarter of that. */
void RoomObject_UpdateSpin(RoomObject *object)
{
    if (object->unk_780 != 0x23 && object->unk_780 != 0x24 && object->unk_780 != 0x25) {
        object->angle = (s16) (object->angle + SPIN_SPEED);
    }
    set_scale(object, shift_right(FX_Div(FurnitureInfo_Scale(RoomObject_Number(object)), 100 * ONE), 2));
}
CLEAN_AS(func_ov004_0220c560, RoomObject_UpdateSpin)

/* func_ov004_0220c5c8 (entry of ROOM_OBJECT_SPIN) */
int RoomObject_EnterSpin(RoomObject *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov004_0220c5c8, RoomObject_EnterSpin)

/* The shrinking of ROOM_OBJECT_VANISH and ROOM_OBJECT_SHRINK: the scale towards 0 (only its x
 * is moved, then copied); whether it is there. */
static int shrink(RoomObject *object)
{
    Approach_S32Again(&object->scale_x, 0, SHRINK_SPEED);
    object->scale_z = object->scale_x;
    object->scale_y = object->scale_z;
    return object->scale_x == 0;
}

/* The effect at the object's centre, in the second frame of shrinking. */
static void shrink_effect(RoomObject *object)
{
    Vec3 centre;
    RoomObject_Centre(object, &centre);
    RoomObject_Effect3dAt(object, &centre);
}

/* func_ov004_0220c5cc (update of ROOM_OBJECT_SHRINK): once shrunk, ROOM_OBJECT_SHRUNK. */
void RoomObject_UpdateShrink(RoomObject *object)
{
    if (shrink(object)) {
        RoomObject_EnterState(object, ROOM_OBJECT_SHRUNK);
    } else if (object->state_frames == 1) {
        shrink_effect(object);
    }
    object->state_frames++;
}
CLEAN_AS(func_ov004_0220c5cc, RoomObject_UpdateShrink)

/* func_ov004_0220c640 (entry of ROOM_OBJECT_SHRINK): as vanishing. */
int RoomObject_EnterShrink(RoomObject *object)
{
    return RoomObject_EnterVanish(object);
}
CLEAN_AS(func_ov004_0220c640, RoomObject_EnterShrink)

/* func_ov004_0220c648 (update of ROOM_OBJECT_VANISH): once shrunk, asks for the object's
 * removal (Process_RequestDelete) and goes on with the frame. */
void RoomObject_UpdateVanish(RoomObject *object)
{
    if (shrink(object)) {
        Process_RequestDelete(&object->scene.process);
    }
    if (object->state_frames == 1) {
        shrink_effect(object);
    }
    object->state_frames++;
}
CLEAN_AS(func_ov004_0220c648, RoomObject_UpdateVanish)

/* func_ov004_0220c6b8 (entry of ROOM_OBJECT_VANISH): tells the object, then an effect at its
 * centre and a sound. */
int RoomObject_EnterVanish(RoomObject *object)
{
    Vec3 centre;

    object->vtable->vfunc_90(object);
    object->state_frames = 0;
    RoomObject_Centre(object, &centre);
    RoomObjects_SetVanishPoint(&centre);
    PlayerActors_OwnPlaySound(SOUND_VANISH);
    return 1;
}
CLEAN_AS(func_ov004_0220c6b8, RoomObject_EnterVanish)

/* func_ov004_0220c6f4 (update of ROOM_OBJECT_MOVE_BACK): as a move. */
void RoomObject_UpdateMoveBack(RoomObject *object)
{
    RoomObject_UpdateMove(object);
}
CLEAN_AS(func_ov004_0220c6f4, RoomObject_UpdateMoveBack)

/* The start of a move to the target position: the offset to it, then whether the mover
 * (RoomManager_Mover) takes it on with `start`. */
static int start_move(RoomObject *object, int (*start)(void *, void *, Vec3 *, int), int ahead)
{
    Vec3 offset;

    Vec_Subtract(&offset, &object->target_position, &object->position);
    CarriedItems_PickUp(&object->carried, object);
    RoomObject_MoveOnMap(object, &offset, 0);
    void *mover = RoomManager_Mover();
    if (mover != NULL && start(mover, &object->move_flag, &object->position, object->target_angle) != 0) {
        object->vtable->vfunc_94(object, ahead);
        RoomObject_EffectAtCellTowardsPlayer(object, !ahead);
        return 1;
    }
    return 0;
}

/* func_ov004_0220c6fc (entry of ROOM_OBJECT_MOVE_BACK) */
int RoomObject_EnterMoveBack(RoomObject *object)
{
    return start_move(object, func_ov004_0223b058, 0);
}
CLEAN_AS(func_ov004_0220c6fc, RoomObject_EnterMoveBack)

/* func_ov004_0220c774 (update of ROOM_OBJECT_MOVE): the position the mover gives, until it
 * says the move is over; then the object is at the target and idle. Without a mover, nothing. */
void RoomObject_UpdateMove(RoomObject *object)
{
    void *mover = RoomManager_Mover();
    if (mover != NULL) {
        Vec3 position;
        if (FurnitureMover_Step(mover, &object->move_flag, &position)) {
            object->position = object->target_position;
            RoomObject_EnterState(object, ROOM_OBJECT_IDLE);
            CarriedItems_PutDown(&object->carried, object);
        } else {
            object->position = position;
        }
    }
}
CLEAN_AS(func_ov004_0220c774, RoomObject_UpdateMove)

/* func_ov004_0220c7e0 (entry of ROOM_OBJECT_MOVE) */
int RoomObject_EnterMove(RoomObject *object)
{
    return start_move(object, func_ov004_0223b080, 1);
}
CLEAN_AS(func_ov004_0220c7e0, RoomObject_EnterMove)

/* The vtable slots a turn calls, on the object and the objects on its cells. */
enum TurnSlot { TURN_START, TURN_FRAME };

static void call_turn(RoomObject *object, enum TurnSlot slot, int down)
{
    if (slot == TURN_START) {
        object->vtable->vfunc_98(object, down);
    } else {
        object->vtable->vfunc_9c(object, down);
    }
}

/* The object's turn, and when it carries them (unk_288 0 and unk_788 1), the turn of the
 * objects on its cells (layer 1).
 * QUIRK: each cell is asked for twice, once for its x and once for its y. */
static void turn_with_cells(RoomObject *object, enum TurnSlot slot, int down)
{
    call_turn(object, slot, down);
    if (object->unk_288 != 0 || object->unk_788 != 1) {
        return;
    }
    CellList cells;
    CellList_Construct(&cells);
    RoomObject_ListCells(object, &cells, NULL, 0);
    for (unsigned long i = 0; i < CellList_Count(&cells); i++) {
        void *grid = RoomObjects_Grid();
        Cell *for_x = CellList_At(&cells, (int) i);
        Cell *for_y = CellList_At(&cells, (int) i);
        RoomObject *above = RoomObjects_GridObjectAt(grid, for_x->x, for_y->y, 1);
        if (above != NULL) {
            call_turn(above, slot, down);
        }
    }
    CellList_Destruct(&cells);
}

/* func_ov004_0220c858 (update of ROOM_OBJECT_TURN): towards the target angle by 0x700 a
 * frame; there, idle. */
void RoomObject_UpdateTurn(RoomObject *object)
{
    int down = (s16) (object->target_angle - object->angle) < 0;
    turn_with_cells(object, TURN_FRAME, down);
    if (Approach_S16Wrapped(&object->angle, object->target_angle, TURN_SPEED)) {
        RoomObject_EnterState(object, ROOM_OBJECT_IDLE);
        CarriedItems_PutDown(&object->carried, object);
    }
}
CLEAN_AS(func_ov004_0220c858, RoomObject_UpdateTurn)

/* func_ov004_0220c930 (entry of ROOM_OBJECT_TURN) */
int RoomObject_EnterTurn(RoomObject *object)
{
    CarriedItems_PickUp(&object->carried, object);
    s16 turn = (s16) (object->target_angle - object->angle);
    RoomObject_MoveOnMap(object, NULL, turn);
    turn_with_cells(object, TURN_START, turn < 0);
    return 1;
}
CLEAN_AS(func_ov004_0220c930, RoomObject_EnterTurn)

/* func_ov004_0220c9f4 (update of ROOM_OBJECT_IDLE and ROOM_OBJECT_SHRUNK) */
void RoomObject_UpdateIdle(RoomObject *object)
{
    (void) object;
}
CLEAN_AS(func_ov004_0220c9f4, RoomObject_UpdateIdle)

/* func_ov004_0220c9f8 (entry of ROOM_OBJECT_IDLE and ROOM_OBJECT_SHRUNK) */
int RoomObject_EnterIdle(RoomObject *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov004_0220c9f8, RoomObject_EnterIdle)

/* func_ov004_0220c9fc (update of ROOM_OBJECT_APPEAR): unk_15C rises towards 0x1000 by 0x88.
 * For 15 frames the object stays at scale 0 (a sound at frame 12, an effect at frame 15), two
 * more frames pass, then its scale wobbles: x and y around 1 in opposite directions by the
 * sine of the phase times the amplitude, z as x. Each time the sine changes sign the
 * amplitude drops to 0.3 of itself and the phase speeds up by 0x960. Once unk_15C is 0x1000
 * and the amplitude below 0x52, the object is idle. While wobbling, it calls
 * RoomObject_EffectNearCorner with 0 and 2 in its first frame and with 1 and 3 in its third. */
void RoomObject_UpdateAppear(RoomObject *object)
{
    Approach_S32Again(&object->unk_15C, ONE, 0x88);

    if (object->timer < 15) {
        object->timer++;
        object->state_frames = 0;
        if (object->timer == 12) {
            PlayerActors_OwnPlaySound(SOUND_APPEAR);
        }
        if (object->timer == 15) {
            Vec3 centre;
            RoomObject_Centre(object, &centre);
            RoomObject_Effect3dAt(object, &centre);
        }
        return;
    }
    if (object->timer < 17) {
        object->timer++;
        return;
    }

    u16 previous_phase = object->wobble_phase;
    object->wobble_phase = (u16) (object->wobble_phase + object->wobble_speed);
    u16 phase = object->wobble_phase;

    fx32 swing = FX_MulFunc(object->wobble_amplitude, sine(phase));
    object->scale_y = swing + ONE;
    object->scale_x = ONE - swing;
    object->scale_z = object->scale_x;

    if (FX_MulFunc(sine(previous_phase), sine(phase)) < 0) {
        object->wobble_amplitude = FX_MulFunc(object->wobble_amplitude, 0x4cd);
        object->wobble_speed = (s16) (object->wobble_speed + 0x960);
    }
    if (object->unk_15C == ONE && magnitude(object->wobble_amplitude) < 0x52) {
        RoomObject_EnterState(object, ROOM_OBJECT_IDLE);
    }

    switch (object->state_frames) {
        case 0:
            RoomObject_EffectNearCorner(object, 0);
            RoomObject_EffectNearCorner(object, 2);
            break;
        case 2:
            RoomObject_EffectNearCorner(object, 1);
            RoomObject_EffectNearCorner(object, 3);
            break;
    }
    object->state_frames++;
}
CLEAN_AS(func_ov004_0220c9fc, RoomObject_UpdateAppear)

/* func_ov004_0220cb68 (entry of ROOM_OBJECT_APPEAR): scale 0, the wobble's start, and when
 * SessionPlayers_ActorOf(4) says so, whatever DroppedItems_DropFromLocalPlayer does at 0x800 above the object's
 * centre (on the floor when unk_288 is 0, else at the height RoomObjects_HeightAtPoint gives) with
 * the value ItemCode_MakeVariant makes of unk_284; its result decides. */
int RoomObject_EnterAppear(RoomObject *object)
{
    object->unk_15C = 0x555;
    object->scale_x = 0;
    object->scale_y = 0;
    object->scale_z = 0;
    object->timer = 0;
    object->wobble_phase = 0;
    object->wobble_speed = 0x2710;
    object->wobble_amplitude = 0x800;

    if (SessionPlayers_ActorOf(4)) {
        Vec3 centre;
        RoomObject_Centre(object, &centre);
        if (object->unk_288 == 0) {
            centre.y = 0;
        } else {
            centre.y = RoomObjects_HeightAtPoint(&centre);
        }
        centre.y += 0x800;
        u16 code = ItemCode_MakeVariant(object->unk_284, 0);
        return DroppedItems_DropFromLocalPlayer(&code, &centre);
    }
    return 1;
}
CLEAN_AS(func_ov004_0220cb68, RoomObject_EnterAppear)

/* _ZN10RoomObject19func_ov004_0220cc28Ev: the current state's update, through its table.
 * REQUIRES: the state is not negative (RoomObject_EnterState only sets 0 to 8). */
void RoomObject_UpdateState(RoomObject *object)
{
    static const MemberPointer *const updates[ROOM_OBJECT_STATE_COUNT] = {
        &data_ov004_0224fd90, /* RoomObject_UpdateAppear */
        &data_ov004_0224fd78, /* RoomObject_UpdateIdle */
        &data_ov004_0224fd98, /* RoomObject_UpdateTurn */
        &data_ov004_0224fda0, /* RoomObject_UpdateMove */
        &data_ov004_0224fdc0, /* RoomObject_UpdateMoveBack */
        &data_ov004_0224fdb8, /* RoomObject_UpdateVanish */
        &data_ov004_0224fde0, /* RoomObject_UpdateShrink */
        &data_ov004_0224fd68, /* RoomObject_UpdateIdle */
        &data_ov004_0224fd80, /* RoomObject_UpdateSpin */
    };
    MemberTable_InitOnce(&data_ov004_02256c74, data_ov004_02256f5c, updates, ROOM_OBJECT_STATE_COUNT);
    if (object->state < ROOM_OBJECT_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_02256f5c[object->state], object);
    }
}
CLEAN_AS(_ZN10RoomObject19func_ov004_0220cc28Ev, RoomObject_UpdateState)

/* func_ov004_0220ccf8: enters `state` if its entry (through a table) agrees; whether it did.
 * States 9 and above do not exist.
 * REQUIRES: `state` is not negative. */
int RoomObject_EnterState(RoomObject *object, int state)
{
    static const MemberPointer *const entries[ROOM_OBJECT_STATE_COUNT] = {
        &data_ov004_0224fd70, /* RoomObject_EnterAppear */
        &data_ov004_0224fd88, /* RoomObject_EnterIdle */
        &data_ov004_0224fde8, /* RoomObject_EnterTurn */
        &data_ov004_0224fdf0, /* RoomObject_EnterMove */
        &data_ov004_0224fdd8, /* RoomObject_EnterMoveBack */
        &data_ov004_0224fda8, /* RoomObject_EnterVanish */
        &data_ov004_0224fdb0, /* RoomObject_EnterShrink */
        &data_ov004_0224fdc8, /* RoomObject_EnterIdle */
        &data_ov004_0224fdd0, /* RoomObject_EnterSpin */
    };
    MemberTable_InitOnce(&data_ov004_02256c60, data_ov004_02256fa4, entries, ROOM_OBJECT_STATE_COUNT);
    if (state < ROOM_OBJECT_STATE_COUNT && MemberPointer_CallInt(&data_ov004_02256fa4[state], object) != 0) {
        object->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0220ccf8, RoomObject_EnterState)

/* func_ov004_0220cdd8 */
int RoomObject_IsInState(const RoomObject *object, int state)
{
    return object->state == state;
}
CLEAN_AS(func_ov004_0220cdd8, RoomObject_IsInState)

/* func_ov004_0220cdec */
int RoomObject_IsShrunk(const RoomObject *object)
{
    return RoomObject_IsInState(object, ROOM_OBJECT_SHRUNK);
}
CLEAN_AS(func_ov004_0220cdec, RoomObject_IsShrunk)

/* func_ov004_0220cdf8 */
int RoomObject_IsVanishing(const RoomObject *object)
{
    return RoomObject_IsInState(object, ROOM_OBJECT_VANISH);
}
CLEAN_AS(func_ov004_0220cdf8, RoomObject_IsVanishing)

/* func_ov004_0220ce04: not idle, as the object's class tells (vtable slot 0xa0). */
int RoomObject_IsBusy(RoomObject *object)
{
    return object->vtable->is_idle(object) == 0;
}
CLEAN_AS(func_ov004_0220ce04, RoomObject_IsBusy)

/* func_ov004_0220ce20 (the base's vtable slot 0xa0) */
int RoomObject_IsIdle(const RoomObject *object)
{
    return RoomObject_IsInState(object, ROOM_OBJECT_IDLE);
}
CLEAN_AS(func_ov004_0220ce20, RoomObject_IsIdle)

/* func_ov004_0220ce2c */
int RoomObject_IsNotIdle(const RoomObject *object)
{
    return RoomObject_IsIdleAgain(object) == 0;
}
CLEAN_AS(func_ov004_0220ce2c, RoomObject_IsNotIdle)

/* func_ov004_0220ce44: the same as RoomObject_IsIdle; the game has both. */
int RoomObject_IsIdleAgain(const RoomObject *object)
{
    return RoomObject_IsInState(object, ROOM_OBJECT_IDLE);
}
CLEAN_AS(func_ov004_0220ce44, RoomObject_IsIdleAgain)

/* func_ov004_0220ce50 */
void RoomObject_Shrink(RoomObject *object)
{
    RoomObject_EnterState(object, ROOM_OBJECT_SHRINK);
}
CLEAN_AS(func_ov004_0220ce50, RoomObject_Shrink)

/* A move one step along `step_angle` (if RoomObject_CanMove allows it), keeping `angle` as
 * the target angle, in `state`; the object's move sound unless its unk_00C is 0x3d. Whether
 * it moves. The state's entry is not asked whether it agrees here. */
static int try_move(RoomObject *object, u16 angle, int step_angle, int state)
{
    Vec3 step = {0, 0, STEP};
    Vec_RotateY(&step, step_angle);
    if (!RoomObject_CanMove(object, &step)) {
        return 0;
    }
    Vec3 target;
    Vec_Add(&target, &object->position, &step);
    object->target_position = target;
    object->target_angle = (s16) angle;
    RoomObject_EnterState(object, state);
    if (object->unk_00C != KIND_SILENT_MOVE) {
        int sound = RoomObject_MoveSound(object);
        if (sound != NO_SOUND) {
            PlayerActors_OwnPlaySound(sound);
        }
    }
    return 1;
}

/* func_ov004_0220ce5c: a move against `angle` (the step half a turn round from it). */
int RoomObject_TryMoveBack(RoomObject *object, u16 angle)
{
    return try_move(object, angle, (s16) (angle + HALF_TURN), ROOM_OBJECT_MOVE_BACK);
}
CLEAN_AS(func_ov004_0220ce5c, RoomObject_TryMoveBack)

/* func_ov004_0220cefc: a move along `angle`. */
int RoomObject_TryMove(RoomObject *object, u16 angle)
{
    return try_move(object, angle, angle, ROOM_OBJECT_MOVE);
}
CLEAN_AS(func_ov004_0220cefc, RoomObject_TryMove)

/* func_ov004_0220cf90: a turn by `turn` from the object's angle, if RoomObject_CanTurn allows
 * it; whether it turns. */
int RoomObject_TryTurn(RoomObject *object, int turn)
{
    if (!RoomObject_CanTurn(object, turn)) {
        return 0;
    }
    object->target_angle = (s16) (object->angle + turn);
    RoomObject_EnterState(object, ROOM_OBJECT_TURN);
    PlayerActors_OwnPlaySound(SOUND_TURN);
    return 1;
}
CLEAN_AS(func_ov004_0220cf90, RoomObject_TryTurn)

/* func_ov004_0220cfd0 */
int ByteSet_Value(const ByteSet *set)
{
    return set->value;
}
CLEAN_AS(func_ov004_0220cfd0, ByteSet_Value)

/* func_ov004_0220cfd4: whether `value` is one of the four. */
int ByteSet_Contains(const ByteSet *set, int value)
{
    for (unsigned int i = 0; i < 4; i++) {
        if (value == set->values[i]) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0220cfd4, ByteSet_Contains)

/* func_ov004_0220cfec */
void ByteSet_SetValue(ByteSet *set, u8 value)
{
    set->value = value;
}
CLEAN_AS(func_ov004_0220cfec, ByteSet_SetValue)

/* The names of the four nodes (the strings "v", "v1", "v2" and "v3"). */
extern const char *const data_ov004_0224fe2c[4];

/* func_ov004_0220cff0: the indexes of the model's nodes "v", "v1", "v2" and "v3", and `value`
 * with them; nothing without a model.
 * QUIRK: the value is kept in a byte. */
void ByteSet_Bind(ByteSet *set, void *model, int value)
{
    if (model != NULL) {
        for (unsigned int i = 0; i < 4; i++) {
            set->values[i] = (s8) G3dRes_NodeIndex(model, data_ov004_0224fe2c[i]);
        }
        ByteSet_SetValue(set, (u8) value);
    }
}
CLEAN_AS(func_ov004_0220cff0, ByteSet_Bind)

/* func_ov004_0220d028 */
void ByteSet_Destruct(ByteSet *set)
{
    (void) set;
}
CLEAN_AS(func_ov004_0220d028, ByteSet_Destruct)

/* func_ov004_0220d02c: leaves the set as it is. */
void ByteSet_Construct(ByteSet *set)
{
    (void) set;
}
CLEAN_AS(func_ov004_0220d02c, ByteSet_Construct)
