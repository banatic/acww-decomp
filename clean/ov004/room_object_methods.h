/* Methods of overlay 4's room objects (room_object.h) outside their states: the hooks the
 * model calls for its nodes (vtable slots 0x60 to 0x6c), questions about the object's kind,
 * the effects shown at its corners and cells, and the 16-bit reference the game keeps for an
 * object (its index among the room's objects, or the cell of the town's map it is on). */
#ifndef CLEAN_OV004_ROOM_OBJECT_METHODS_H
#define CLEAN_OV004_ROOM_OBJECT_METHODS_H

#include "types.h"

#include "room_object.h"

/* What the model's node hooks get (the main program's func_020b3188 and func_020b3220 turn
 * the node at 0xb4; 0xb8 points to the word the node set's value goes to). */
typedef struct NodeHookState {
    u8 unk_00[0xb4];
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

#endif
