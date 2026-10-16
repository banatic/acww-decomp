/* A scene object of overlay 3 (class Obj_ov003_022387a8, vtable 0x022387a8, receiver part
 * 0x0223886c, 0x2b4 bytes) that sends the player elsewhere: when vtable slot 0x70 runs while
 * event 0x40 is on for the clock's date and time (func_0203fc78), it requests a scene
 * change to place 0x6c (the halfword at data_ov003_02238784) from where it stands. It is
 * derived from overlay 9's scene actor (Obj_ov009_022658dc), which runs the rest. What place
 * 0x6c and event 0x40 are is not known yet.
 *
 * Its receiver keeps overlay 9's slot 0x14, entered through a thunk this overlay also gives
 * the checkpoint (WarpObject_ReceiverSlot14). */
#ifndef CLEAN_OV003_WARP_OBJECT_H
#define CLEAN_OV003_WARP_OBJECT_H

#include "autoload_2/vector.h" /* Vec3 */
#include "types.h"

typedef struct WarpObject {
    const void *vtable; /* data_ov003_022387a8 */
    u8 unk_04[0x5c - 0x04];
    Vec3 position;
    u8 unk_68[0xec - 0x68];
    const void *receiver_vtable; /* data_ov003_0223886c */
    u8 unk_F0[0x2b4 - 0xf0];
} WarpObject;

void WarpObject_ReceiverSlot14(void *receiver);
int WarpObject_Enter(WarpObject *object);
WarpObject *WarpObject_DestroyAndFree(WarpObject *object);
WarpObject *WarpObject_Destroy(WarpObject *object);
WarpObject *WarpObject_Construct(WarpObject *object);
void WarpObject_New(void);
WarpObject *WarpObject_ReceiverDestroyAndFree(void *receiver);
WarpObject *WarpObject_ReceiverDestroy(void *receiver);

#endif
