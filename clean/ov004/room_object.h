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
#include "furniture_mover.h"
#include "main/actor.h"
#include "main/animated_model.h"
#include "main/scene_object_base.h"
#include "main/talk_object.h"
#include "main/talk_receiver.h"
#include "main/touch_pick_shapes.h"
#include "push_box.h"
#include "room_object_parts.h"

struct RoomObject;

/* Four values searched for, and the value that goes with them (at 0x764 in a room object: the
 * indexes of four nodes of its model). */
typedef struct ByteSet {
    s8 values[4];
    u8 value;
} ByteSet;

/* A sound played at a point (RoomSound_PlayAtB and RoomSound_PlayAt play one while
 * `playing`, RoomSound_Stop stops it); the point is the object's centre, kept each frame. */
typedef struct RoomSound {
    u8 unk_00[0x1c];
    u8 playing;
    u8 unk_1d[3];
    Vec3 position;
} RoomSound;

struct NodeHookState;

/* The vtable slots used here; derived classes override them. */
typedef struct RoomObjectVtable {
    const void *unk_00[24];
    /* The model's hooks (room_object_methods.c): for a material, a node, and before and after a
     * node's description; each is given byte 1 of the model's command and the render state. */
    int (*material_hook)(struct RoomObject *object, int material, struct NodeHookState *state);
    int (*node_hook)(struct RoomObject *object, int node, struct NodeHookState *state);
    int (*node_desc_hook)(struct RoomObject *object, int node, struct NodeHookState *state);
    int (*node_desc_after_hook)(struct RoomObject *object, int node, struct NodeHookState *state);
    int (*vfunc_70)(struct RoomObject *object, int a1, int a2); /* RoomObject_SetUnk77C in the base */
    const void *unk_74;
    int (*vfunc_78)(struct RoomObject *object);             /* RoomObject_Unk77C in the base */
    int (*on_model_bound)(struct RoomObject *object);       /* after RoomObject_Init binds the model: whether it is done */
    int (*update_settled)(struct RoomObject *object);       /* each frame, when neither appearing nor vanishing */
    int (*update_unsettled)(struct RoomObject *object);     /* each frame, when appearing or vanishing */
    int (*can_draw)(struct RoomObject *object);             /* RoomObject_Vfunc88 in the base */
    int (*keeps_texture_copy)(struct RoomObject *object);   /* given to FurnitureModel_Load */
    void (*vfunc_90)(struct RoomObject *object);            /* when it starts to vanish */
    void (*vfunc_94)(struct RoomObject *object, int ahead); /* when a move starts: 1 in state 3, 0 in 4 */
    void (*vfunc_98)(struct RoomObject *object, int down);  /* when a turn starts: 1 towards a lower angle */
    void (*vfunc_9c)(struct RoomObject *object, int down);  /* each frame of a turn */
    int (*is_idle)(struct RoomObject *object);              /* RoomObject_IsIdle in the base */
} RoomObjectVtable;

typedef struct RoomObject {
    union {
        SceneObjectBase scene; /* the main program's scene object it extends */
        Actor actor;           /* the same, as the main program's actors see it */
        struct {
            const RoomObjectVtable *vtable;
            u8 unk_004[4];
            u32 placement; /* how it was placed (room_object_body.c) */
            u16 unk_00C;   /* 0x3d: moving it plays no sound */
            u8 unk_00e[0x4e];
            Vec3 position;
            u8 unk_068[0x26];
            s16 angle;
            u8 unk_090[0x5c];
        };
    };
    union {
        TalkReceiver receiver; /* its receiver part, at 0xec */
        struct {
            const void *receiver_vtable;
            u8 unk_0f0[0x1a];
            u8 receiver_state; /* the receiver's state byte */
            u8 unk_10b[0x21];
            /* The conversation the receiver part is attached to (set by the code that opens
             * it): an object that talks waits for its state to become non-zero, then 0 again,
             * and sets its next state to 1 when it starts talking. */
            TalkObject *link;
            u8 unk_130[2];
            u16 slot; /* its entry in the pool data_ov004_02259698 (ModelPool_Take), 0xffff for none */
        };
    };
    u8 unk_134[0x10];
    Vec3 pivot; /* where its model turns about, in its space (PushBox_SettlePivot) */
    union {
        Vec3 scale; /* 20.12 fixed point, as the rest */
        struct {
            int scale_x;
            int scale_y;
            int scale_z;
        };
    };
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
    TouchPickCylinder item_shadows[4]; /* of the items lying on its cells (TouchPick_SetCylinderAndAdd) */
    FurnitureMoveFlag move_flag;       /* given to the move functions FurnitureMover_Step/58/80 */
    u8 unk_251[3];
    Mtx43 base_matrix; /* its place in the world, about its pivot (RoomObject_BuildMatrix) */
    s32 unk_284;       /* the furniture's number (RoomObject_Number), which names its files */
    u8 unk_288;        /* 0: the objects on its cells turn with it; the layer of the town's map it is on */
    u8 is_set_up;      /* func_ov004_0220f52c has run */
    u8 unk_28a[2];
    TouchPickFace shadow[10]; /* its shadow (TouchPick_SetBoxAndAdd) */
    s32 state;                /* RoomObjectState */
    union {
        AnimatedModel model; /* the main program's blended model */
        struct {
            u8 unk_538[0x5c];
            G3dModel *model_resource; /* model.object.model */
            u8 unk_598[4];
            Mtx43 matrix; /* its place in the world, for what it carries */
            u8 unk_5cc[8];
            u8 joint_anim[8]; /* model.frames, the model's joint animation, its frame below */
            u32 joint_frame;
            u8 unk_5e0[0x4c];
        };
    };
    PushBox push_box;
    FurnitureModel model_files;
    Switch light_switch;
    NodePair nodes; /* "kh_j" and "km_j" */
    u8 unk_745[3];
    Glow glow;
    ByteSet node_set; /* the nodes "v", "v1", "v2" and "v3" */
    u8 unk_769[3];
    s32 unk_76C;      /* 2: RoomObject_Unk76CIs2 says so */
    u16 state_frames; /* frames in the state, for the states that count them */
    u8 unk_772[2];
    s32 unk_774;
    s32 unk_778;
    u8 unk_77C; /* what vtable slot 0x78 gives in the base (the map's record gets it) */
    u8 unk_77D; /* set: it neither moves nor switches */
    u8 unk_77E; /* set while the constructor's loading binds its model */
    u8 unk_77f;
    u32 unk_780; /* 0x23 to 0x25: spinning does not turn it */
    u32 unk_784; /* 1: two cells long, its pivot at either end (PushBox_SettlePivot) */
    u32 unk_788; /* 1: the objects on its cells turn with it */
    u8 unk_78C;
    u8 unk_78D; /* 0: its switch starts on when unk_76C is 1 or 2 */
    u8 unk_78e[2];
    fx32 top_height; /* the height of what stands on it, in its own space */
    s32 light_kind;  /* func_02053818 of its number: 0 for no light */
    RoomSound sound;
    FurnitureAnim anims[4]; /* ROOM_ANIM_MATERIAL to ROOM_ANIM_VISIBILITY */
} RoomObject;

/* The animations in RoomObject.anims, with the AnimSet entry each plays. */
enum RoomAnim {
    ROOM_ANIM_MATERIAL = 0,  /* anim_08 */
    ROOM_ANIM_TEXCOORD = 1,  /* anim_18 */
    ROOM_ANIM_PATTERN = 2,   /* anim_20, with the texture */
    ROOM_ANIM_VISIBILITY = 3 /* anim_10 */
};

/* The cells an object covers (RoomObject_ListCells fills them in). */
typedef struct Cell {
    int x;
    int y;
} Cell;

typedef struct CellList {
    u32 count;
    Cell cells[4];
} CellList;

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
