/* Methods of overlay 4's room objects (room_object.h) outside their states: the hooks the
 * model calls for its nodes (vtable slots 0x60 to 0x6c), questions about the object's kind,
 * the effects shown at its corners and cells, and the 16-bit reference the game keeps for an
 * object (its index among the room's objects, or the cell of the town's map it is on). */
#ifndef CLEAN_OV004_ROOM_OBJECT_METHODS_H
#define CLEAN_OV004_ROOM_OBJECT_METHODS_H

#include "types.h"

#include "room_object.h"

/* The object a model is drawn through (NitroSystem's NNSG3dRenderObj): the room object it
 * belongs to is kept at 0x2c (func_02055dc8 puts it there). */
typedef struct G3dRenderObject {
    u8 unk_00[0x2c];
    struct RoomObject *user;
} G3dRenderObject;

/* The model's commands with hooks here (NitroSystem's NNS_G3D_SBC_*), and when the hook runs
 * (NNS_G3D_SBC_CALLBACK_TIMING_*). */
enum { G3D_COMMAND_NODE = 2, G3D_COMMAND_MATERIAL = 4, G3D_COMMAND_NODE_DESC = 6, G3D_COMMAND_COUNT = 0x20 };
enum {
    G3D_TIMING_BEFORE = 1, /* timing A */
    G3D_TIMING_AFTER = 2   /* timing B */
};

/* What the model's hooks get: the state of the model being drawn (NitroSystem's NNSG3dRS).
 * The main program's func_020b3188 and func_020b3220 turn the node at 0xb4; 0xb8 points to the
 * word the node set's value goes to. */
typedef struct NodeHookState {
    const u8 *command; /* the command being run: byte 1 is its node or material */
    G3dRenderObject *render_object;
    u32 flags;
    u32 hooks[G3D_COMMAND_COUNT]; /* the address of each command's hook, 0 for none */
    u8 hook_timings[G3D_COMMAND_COUNT];
    u8 unk_ac[8];
    void *unk_B4;
    u32 *unk_B8;
} NodeHookState;

int RoomObject_NodeSetHook(RoomObject *object, int node, NodeHookState *state);
void RoomObject_ClockHandsHook(RoomObject *object, int node, NodeHookState *state);
void RoomObject_IgnoreHook68(void);
void RoomObject_IgnoreHook60(void);
void RoomObject_ItemCode(ItemCode *code, RoomObject *object);
int RoomObject_Unk780Is18(RoomObject *object);
int RoomObject_Unk00CIs36Or37(RoomObject *object);
int RoomObject_Unk00CIs3A(RoomObject *object);
int RoomObject_Check0221134c(RoomObject *object);
int RoomObject_Unk76CIs2(const RoomObject *object);
void RoomObject_EffectNearCorner(RoomObject *object, int corner);
int RoomObject_Effect3dAt(RoomObject *object, const Vec3 *point);
int RoomObject_EffectTowardsPlayer(RoomObject *object);
void RoomObject_EffectAtCellTowardsPlayer(RoomObject *object, int farthest);
int RoomEffect_SpawnC0(Vec3 *point, int angle);
int RoomObject_FindVariantCell(RoomObject *object, int *x, int *y, Vec3 *offset, s16 turn);
u16 RoomObject_Reference(RoomObject *object, Vec3 *offset, int turn);
int RoomObject_Check022111f0(RoomObject *object);
int RoomObject_SettledUnk780Is10(RoomObject *object);
int RoomObject_TestUnk780Is18(const RoomObject *object);
int RoomObject_TestUnk00CIs36Or37(const RoomObject *object);
int RoomObject_Unk00CIs3BOr3CAndOn(RoomObject *object);
int RoomObject_Unk00CIs3AAndOn(RoomObject *object);
int RoomObject_TestUnk00CIs3A(const RoomObject *object);
int RoomObject_IsLight(RoomObject *object);
void RoomObject_SetModelHooks(NodeHookState *state);
int RoomObject_RunNodeHook(NodeHookState *state);
void RoomObject_RunNodeDescAfterHook(NodeHookState *state);
void RoomObject_RunNodeDescHook(NodeHookState *state);
int RoomObject_RunMaterialHook(NodeHookState *state);

#endif
