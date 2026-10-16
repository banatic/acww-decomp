/* An outdoor scene object of overlay 3 (class Obj_ov003_02238434, vtable 0x02238434, receiver
 * part 0x022384f8, 0x2b8 bytes) that opens a screen when it is checked: its own state machine
 * (the word at 0x2b4) runs through tables of member pointers (ov004/member_pointer.h):
 *
 *   0 idle:    nothing happens; scene event 0 or 1 opens the screen (state 1).
 *   1 opening: entering it asks main to open group 9 in mode 0 (GroupParams_Open), and fails
 *              when main refuses; the next frame moves to state 2.
 *   2 open:    once main can open a screen again (GroupParams_CanOpen) it lets the scene go on
 *              (func_0203e020).
 *
 * Scene event 8 and vtable slot 0x70 make it idle. It is derived from overlay 9's scene actor
 * (Obj_ov009_022658dc), which runs the rest. Which screen mode 0 of group 9 is, and so what the
 * object is, is not known yet. */
#ifndef CLEAN_OV003_SCREEN_OBJECT_H
#define CLEAN_OV003_SCREEN_OBJECT_H

#include "types.h"

enum ScreenObjectState { SCREEN_OBJECT_IDLE, SCREEN_OBJECT_OPENING, SCREEN_OBJECT_OPEN, SCREEN_OBJECT_STATES };

typedef struct ScreenObject {
    const void *vtable; /* data_ov003_02238434 */
    u8 unk_04[0x8e - 0x04];
    s16 yaw; /* the direction it faces */
    u8 unk_90[0xec - 0x90];
    const void *receiver_vtable; /* data_ov003_022384f8 */
    u8 unk_F0[0x235 - 0xf0];
    u8 flags_235; /* ScreenObject_IsFacedBy needs bit 3 */
    u8 unk_236[0x2b4 - 0x236];
    int state; /* enum ScreenObjectState */
} ScreenObject;

/* What ScreenObject_IsFacedBy reads of the other actor. */
typedef struct ScreenObjectViewer {
    u8 unk_00[0x8e];
    s16 yaw;
} ScreenObjectViewer;

void ScreenObject_UpdateOpen(ScreenObject *object);
int ScreenObject_EnterOpen(ScreenObject *object);
void ScreenObject_UpdateOpening(ScreenObject *object);
int ScreenObject_EnterOpening(ScreenObject *object);
void ScreenObject_UpdateIdle(void);
int ScreenObject_EnterIdle(ScreenObject *object);
void ScreenObject_UpdateState(ScreenObject *object);
int ScreenObject_SetState(ScreenObject *object, int state);
void ScreenObject_OnSceneEvent(ScreenObject *object, int event);
int ScreenObject_IsFacedBy(ScreenObject *object, ScreenObjectViewer *viewer);
int ScreenObject_Slot0C(void);
int ScreenObject_Slot24(void);
int ScreenObject_Update(ScreenObject *object);
int ScreenObject_Reset(ScreenObject *object);
ScreenObject *ScreenObject_DestroyAndFree(ScreenObject *object);
ScreenObject *ScreenObject_Destroy(ScreenObject *object);
ScreenObject *ScreenObject_Construct(ScreenObject *object);
void ScreenObject_New(void);
ScreenObject *ScreenObject_ReceiverDestroyAndFree(void *receiver);
ScreenObject *ScreenObject_ReceiverDestroy(void *receiver);

#endif
