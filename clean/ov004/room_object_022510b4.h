/* A class of overlay 4's room objects (vtable 0x022510b4, receiver part 0x02251160, 0x848 bytes)
 * switched on and off by touching it, through four states entered through vtable slot 0x70 and
 * dispatched through tables of member pointers (member_pointer.h):
 *
 * - OFF (0): the animations of variant 0 in mode 3 from the start; touching it (a change of the
 *   switch pending) requests SWITCHING_ON, and unk_76C at 2 enters it at once;
 * - SWITCHING_ON (1): the switch on, sound 1 of its row and the animations of variant 0 once;
 *   then ON;
 * - ON (2): the animations of variant 1 in a loop from their end, advanced each frame with
 *   sound 0 and func_020537a8 of its number; touching it requests SWITCHING_OFF, and unk_76C at
 *   2 enters it at once;
 * - SWITCHING_OFF (3): the switch off, sound 2 of its row and the animations of variant 0 from
 *   their end in mode 3; then OFF.
 *
 * SWITCHING_ON and ON show it on (vtable slot 0x74). Once its model is bound it is ON when its
 * switch is on (unless func_ov004_0223c10c says otherwise), else OFF. */
#ifndef CLEAN_OV004_ROOM_OBJECT_022510B4_H
#define CLEAN_OV004_ROOM_OBJECT_022510B4_H

#include "types.h"

#include "room_object.h"

typedef struct RoomObject022510b4 {
    RoomObject base;
    u8 unk_844; /* cleared once its model is bound */
    u8 state;   /* RoomObject022510b4State */
    u8 unk_846[2];
} RoomObject022510b4;

enum RoomObject022510b4State {
    ROOM_OBJECT_022510B4_OFF = 0,
    ROOM_OBJECT_022510B4_SWITCHING_ON = 1,
    ROOM_OBJECT_022510B4_ON = 2,
    ROOM_OBJECT_022510B4_SWITCHING_OFF = 3,
    ROOM_OBJECT_022510B4_STATE_COUNT = 4
};

void RoomObject022510b4_UpdateSwitchingOff(RoomObject022510b4 *object);
int RoomObject022510b4_EnterSwitchingOff(RoomObject022510b4 *object);
void RoomObject022510b4_UpdateOn(RoomObject022510b4 *object);
int RoomObject022510b4_EnterOn(RoomObject022510b4 *object);
void RoomObject022510b4_UpdateSwitchingOn(RoomObject022510b4 *object);
int RoomObject022510b4_EnterSwitchingOn(RoomObject022510b4 *object);
void RoomObject022510b4_UpdateOff(RoomObject022510b4 *object);
int RoomObject022510b4_EnterOff(RoomObject022510b4 *object);
void RoomObject022510b4_UpdateState(RoomObject022510b4 *object);
int RoomObject022510b4_EnterState(RoomObject022510b4 *object, unsigned int state, int value);
u8 RoomObject022510b4_StateIsOn(RoomObject022510b4 *object, unsigned int state);
int RoomObject022510b4_Vfunc0C(void);
int RoomObject022510b4_Update(RoomObject022510b4 *object);
int RoomObject022510b4_Start(RoomObject022510b4 *object);
RoomObject022510b4 *RoomObject022510b4_Delete(RoomObject022510b4 *object);
RoomObject022510b4 *RoomObject022510b4_Destroy(RoomObject022510b4 *object);
RoomObject022510b4 *RoomObject022510b4_Construct(RoomObject022510b4 *object);
void RoomObject022510b4_Create(void);

#endif
