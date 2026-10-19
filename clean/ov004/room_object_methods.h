/* Methods of overlay 4's room objects (room_object.h) outside their states: the hooks the
 * model calls for its nodes (vtable slots 0x60 to 0x6c), questions about the object's kind,
 * the effects shown at its corners and cells, and the 16-bit reference the game keeps for an
 * object (its index among the room's objects, or the cell of the town's map it is on). */
#ifndef CLEAN_OV004_ROOM_OBJECT_METHODS_H
#define CLEAN_OV004_ROOM_OBJECT_METHODS_H

#include "main/g3d_render.h"
#include "types.h"

#include "room_object.h"

int RoomObject_NodeSetHook(RoomObject *object, int node, G3dRenderState *state);
void RoomObject_ClockHandsHook(RoomObject *object, int node, G3dRenderState *state);
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
void RoomObject_SetModelHooks(G3dRenderState *state);
int RoomObject_RunNodeHook(G3dRenderState *state);
void RoomObject_RunNodeDescAfterHook(G3dRenderState *state);
void RoomObject_RunNodeDescHook(G3dRenderState *state);
int RoomObject_RunMaterialHook(G3dRenderState *state);

#endif
