/* A room object's body (room_object.h): setting it up from the word it was placed with, its
 * matrices, size, corners and centre, the box it pushes back with and its shadows, binding its
 * model, and the base class's small virtual functions.
 *
 * The placement word (RoomObject.placement): the cell within its block (bits 0-3 and 4-7), the
 * furniture's number (8-23), the side it faces (24-25, a quarter turn each), its mode (26-27,
 * RoomObject.unk_76C: 2 for a preview shown in front of the camera) and whether it stands on
 * another object (28, RoomObject.unk_288). */
#ifndef CLEAN_OV004_ROOM_OBJECT_BODY_H
#define CLEAN_OV004_ROOM_OBJECT_BODY_H

#include "types.h"

#include "room_object.h"

void RoomObject_SetModelByIndex(RoomObject *object);
void RoomObject_BindModel(RoomObject *object);
void RoomObject_SetUp(RoomObject *object);
int RoomObject_EnterFirstState(RoomObject *object);
void RoomObject_ShadowItemsOnTop(RoomObject *object);
void RoomObject_UpdateBoxAndShadow(RoomObject *object);
void RoomObject_RemoveBox(RoomObject *object);
void RoomObject_SetUpBoxAndShadow(RoomObject *object);
void RoomObject_Size(RoomObject *object, Vec3 *size);
void RoomObject_UpdateMatrices(RoomObject *object);
void RoomObject_BuildMatrix(RoomObject *object, Vec3 *offset, int turn);
int RoomObject_Layer(RoomObject *object);
int RoomObject_ToggleSwitch(RoomObject *object);
int RoomObject_Vfunc74(void);
int RoomObject_SetUnk77C(RoomObject *object, int unused, int value);
int RoomObject_Number(RoomObject *object);
void RoomObject_Centre(RoomObject *object, Vec3 *centre);
void RoomObject_Corner(RoomObject *object, Vec3 *corner, int index);
void RoomObject_ToWorld(RoomObject *object, Vec3 *out, const Vec3 *point);
int RoomObject_Lookup020537a8(RoomObject *object);
int RoomObject_Unk77C(RoomObject *object);
Vec3 *RoomObject_PointBeforePlayer(RoomObject *object);
void RoomObject_OnTurnFrame(void);
void RoomObject_OnTurnStart(void);
void RoomObject_OnMoveStart(void);
void RoomObject_OnVanish(void);
int RoomObject_Vfunc88(void);
int RoomObject_Vfunc8C(void);
void RoomObject_Vfunc14(RoomObject *object, int mode);
int RoomObject_Vfunc10(RoomObject *object);
unsigned int Placement_Mode(unsigned int placement);
unsigned int Placement_Number(unsigned int placement);
int Placement_Make(int x, int y, int number, int side, u8 on_top, int mode);

#endif
