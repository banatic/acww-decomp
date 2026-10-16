/* The state machine of overlay 4's room objects (the C++ base with vtable 0x0224fe6c and its
 * derived classes): each state has an entry, which may refuse, and an update run every frame,
 * both reached through tables of member pointers (member_pointer.h).
 *
 * What the states do, from their code: an object appears with a wobble of its scale (0),
 * stands still (1), turns to a target angle (2), moves one 0x2000 step (3, and 4 the opposite
 * way), shrinks away and asks to be removed (5), shrinks away and stays (6, then 7), or spins
 * (8). Turning also turns the objects found on the cells it covers. */
#ifndef CLEAN_OV004_ROOM_OBJECT_H
#define CLEAN_OV004_ROOM_OBJECT_H

#include "types.h"

#include "autoload_2/approach.h"
#include "autoload_2/matrix.h" /* Mtx43 */
#include "carried_items.h"
#include "furniture_model.h"
#include "push_box.h"
#include "room_object_parts.h"

struct RoomObject;

/* Four values searched for, and the value that goes with them (at 0x764 in a room object: the
 * indexes of four nodes of its model). */
typedef struct ByteSet {
    s8 values[4];
    u8 value;
} ByteSet;

/* The vtable slots used here; derived classes override them. */
typedef struct RoomObjectVtable {
    const void *unk_00[36];
    void (*vfunc_90)(struct RoomObject *object);            /* when it starts to vanish */
    void (*vfunc_94)(struct RoomObject *object, int ahead); /* when a move starts: 1 in state 3, 0 in 4 */
    void (*vfunc_98)(struct RoomObject *object, int down);  /* when a turn starts: 1 towards a lower angle */
    void (*vfunc_9c)(struct RoomObject *object, int down);  /* each frame of a turn */
    int (*is_idle)(struct RoomObject *object);              /* RoomObject_IsIdle in the base */
} RoomObjectVtable;

typedef struct RoomObject {
    const RoomObjectVtable *vtable;
    u8 unk_004[8];
    u16 unk_00C; /* 0x3d: moving it plays no sound */
    u8 unk_00e[0x4e];
    Vec3 position;
    u8 unk_068[0x26];
    s16 angle;
    u8 unk_090[0xb4];
    Vec3 pivot;  /* where its model turns about, in its space (func_ov004_0220dbac) */
    int scale_x; /* 20.12 fixed point, as the rest */
    int scale_y;
    int scale_z;
    int unk_15C;      /* rises to 0x1000 while appearing; the wobble ends only once it is there */
    u16 timer;        /* frames since it started to appear */
    u16 wobble_phase; /* an angle */
    s16 wobble_speed;
    u8 unk_166[2];
    fx32 wobble_amplitude;
    s16 target_angle;
    u8 unk_16e[2];
    Vec3 target_position;
    Mount mount;
    CarriedItems carried;
    u8 unk_1d0[0x80];
    u8 unk_250[0x34]; /* given to the move functions func_ov004_0223b004/58/80 */
    s32 unk_284;      /* the furniture's number (func_ov004_0220fde0), which names its files */
    u8 unk_288;       /* 0: the objects on its cells turn with it; the layer of the town's map it is on */
    u8 unk_289[0x2ab];
    s32 state; /* RoomObjectState */
    u8 unk_538[0x64];
    Mtx43 matrix; /* its place in the world, for what it carries */
    u8 unk_5cc[0x60];
    PushBox push_box;
    FurnitureModel model_files;
    Switch light_switch;
    NodePair nodes; /* "kh_j" and "km_j" */
    u8 unk_745[3];
    Glow glow;
    ByteSet node_set; /* the nodes "v", "v1", "v2" and "v3" */
    u8 unk_769[3];
    s32 unk_76C;      /* 2: func_ov004_0220e5c8 says so */
    u16 state_frames; /* frames in the state, for the states that count them */
    u8 unk_772[0xe];
    u32 unk_780; /* 0x23 to 0x25: spinning does not turn it */
    u32 unk_784; /* 1: two cells long, its pivot at either end (func_ov004_0220dbac) */
    u32 unk_788; /* 1: the objects on its cells turn with it */
    u8 unk_78C;
    u8 unk_78D; /* 0: its switch starts on when unk_76C is 1 or 2 */
    u8 unk_78e[2];
    fx32 top_height; /* the height of what stands on it, in its own space */
} RoomObject;

/* The cells an object covers (func_ov004_0220f27c fills them in). */
typedef struct Cell {
    s32 x;
    s32 y;
} Cell;

typedef struct CellList {
    u32 count;
    Cell cells[4];
} CellList;

extern CellList *func_ov004_0220db94(CellList *list);
extern void func_ov004_0220f27c(RoomObject *object, CellList *list, void *a2, int a3);
extern unsigned long func_ov004_0220db68(CellList *list);
extern Cell *func_ov004_0220db5c(CellList *list, int index);
extern void func_ov004_0220db90(CellList *list);

enum RoomObjectState {
    ROOM_OBJECT_APPEAR = 0,
    ROOM_OBJECT_IDLE = 1,
    ROOM_OBJECT_TURN = 2,
    ROOM_OBJECT_MOVE = 3,
    ROOM_OBJECT_MOVE_BACK = 4,
    ROOM_OBJECT_VANISH = 5,
    ROOM_OBJECT_SHRINK = 6,
    ROOM_OBJECT_SHRUNK = 7,
    ROOM_OBJECT_SPIN = 8,
    ROOM_OBJECT_STATE_COUNT = 9
};

void RoomObject_UpdateSpin(RoomObject *object);
int RoomObject_EnterSpin(RoomObject *object);
void RoomObject_UpdateShrink(RoomObject *object);
int RoomObject_EnterShrink(RoomObject *object);
void RoomObject_UpdateVanish(RoomObject *object);
int RoomObject_EnterVanish(RoomObject *object);
void RoomObject_UpdateMoveBack(RoomObject *object);
int RoomObject_EnterMoveBack(RoomObject *object);
void RoomObject_UpdateMove(RoomObject *object);
int RoomObject_EnterMove(RoomObject *object);
void RoomObject_UpdateTurn(RoomObject *object);
int RoomObject_EnterTurn(RoomObject *object);
void RoomObject_UpdateIdle(RoomObject *object);
int RoomObject_EnterIdle(RoomObject *object);
void RoomObject_UpdateAppear(RoomObject *object);
int RoomObject_EnterAppear(RoomObject *object);
void RoomObject_UpdateState(RoomObject *object);
int RoomObject_EnterState(RoomObject *object, int state);
int RoomObject_IsInState(const RoomObject *object, int state);
int RoomObject_IsShrunk(const RoomObject *object);
int RoomObject_IsVanishing(const RoomObject *object);
int RoomObject_IsBusy(RoomObject *object);
int RoomObject_IsIdle(const RoomObject *object);
int RoomObject_IsNotIdle(const RoomObject *object);
int RoomObject_IsIdleAgain(const RoomObject *object);
void RoomObject_Shrink(RoomObject *object);
int RoomObject_TryMoveBack(RoomObject *object, u16 angle);
int RoomObject_TryMove(RoomObject *object, u16 angle);
int RoomObject_TryTurn(RoomObject *object, int turn);
int ByteSet_Value(const ByteSet *set);
int ByteSet_Contains(const ByteSet *set, int value);
void ByteSet_SetValue(ByteSet *set, u8 value);
void ByteSet_Bind(ByteSet *set, void *model, int value);
void ByteSet_Destruct(ByteSet *set);
void ByteSet_Construct(ByteSet *set);

#endif
