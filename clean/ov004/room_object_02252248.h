/* A class of overlay 4's room objects (vtable 0x02252248, receiver part 0x022522f4, 0x848 bytes)
 * switched on and off by touching it, through four states entered through vtable slot 0x70 and
 * dispatched through tables of member pointers (member_pointer.h):
 *
 * - OFF (0): the animations of variant 0 in mode 3 from the start; touching it (a change of the
 *   switch pending) requests SWITCHING_ON, and unk_76C at 2 enters it at once;
 * - SWITCHING_ON (1): the switch on, the animations of variant 0 once from the start and sound 1
 *   of its row; then ON;
 * - ON (2): the animations of variant 0 once from their end; touching it requests SWITCHING_OFF,
 *   and unk_76C at 2 enters it at once;
 * - SWITCHING_OFF (3): the switch off, the animations of variant 0 from their end in mode 3 and
 *   sound 2 of its row; then OFF.
 *
 * SWITCHING_ON and ON show it on (vtable slot 0x74). Once its model is bound it enters ON when
 * its switch is on and RoomObjects_InNookOrScene0AOr0F says no, else OFF. */
#ifndef CLEAN_OV004_ROOM_OBJECT_02252248_H
#define CLEAN_OV004_ROOM_OBJECT_02252248_H

#include "types.h"

#include "room_object.h"

typedef struct RoomObject02252248 {
    RoomObject base;
    u8 state; /* RoomObject02252248State */
    u8 unk_845[3];
} RoomObject02252248;

enum RoomObject02252248State {
    ROOM_OBJECT_02252248_OFF = 0,
    ROOM_OBJECT_02252248_SWITCHING_ON = 1,
    ROOM_OBJECT_02252248_ON = 2,
    ROOM_OBJECT_02252248_SWITCHING_OFF = 3,
    ROOM_OBJECT_02252248_STATE_COUNT = 4
};

void RoomObject02252248_UpdateSwitchingOff(RoomObject02252248 *object);
int RoomObject02252248_EnterSwitchingOff(RoomObject02252248 *object);
void RoomObject02252248_UpdateOn(RoomObject02252248 *object);
int RoomObject02252248_EnterOn(RoomObject02252248 *object);
void RoomObject02252248_UpdateSwitchingOn(RoomObject02252248 *object);
int RoomObject02252248_EnterSwitchingOn(RoomObject02252248 *object);
void RoomObject02252248_UpdateOff(RoomObject02252248 *object);
int RoomObject02252248_EnterOff(RoomObject02252248 *object);
void RoomObject02252248_UpdateState(RoomObject02252248 *object);
int RoomObject02252248_EnterState(RoomObject02252248 *object, unsigned int state, int value);
u8 RoomObject02252248_StateIsOn(RoomObject02252248 *object, unsigned int state);
int RoomObject02252248_Vfunc0C(void);
int RoomObject02252248_Update(RoomObject02252248 *object);
int RoomObject02252248_Start(RoomObject02252248 *object);
RoomObject02252248 *RoomObject02252248_Delete(RoomObject02252248 *object);
RoomObject02252248 *RoomObject02252248_Destroy(RoomObject02252248 *object);
RoomObject02252248 *RoomObject02252248_Construct(RoomObject02252248 *object);
void RoomObject02252248_Create(void);
RoomObject02252248 *RoomObject02252248Receiver_Delete(void *receiver);
RoomObject02252248 *RoomObject02252248Receiver_Destroy(void *receiver);

#endif
