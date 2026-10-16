/* A class of overlay 4's room objects (vtable 0x022518e8, receiver part 0x02251994, 0x848 bytes)
 * switched on and off by touching it, through four states entered through vtable slot 0x70 and
 * dispatched through tables of member pointers (member_pointer.h). The node set's value
 * (RoomObject.node_set) is 0 when off and 1 in the other states.
 *
 * - OFF (0): the animations of variant 1 once from their end; touching it (a change of the
 *   switch pending) requests SWITCHING_ON, and unk_76C at 2 enters it at once;
 * - SWITCHING_ON (1): the switch on, the animations of variant 0 once from the start and sound 1
 *   of its row; sound 0 each frame; then ON;
 * - ON (2): the animations of variant 0 once from their end; sound 0 each frame; touching it
 *   requests SWITCHING_OFF, and unk_76C at 2 enters it at once;
 * - SWITCHING_OFF (3): the switch off, the animations of variant 1 once from the start and sound
 *   2 of its row; sound 0 each frame; then OFF.
 *
 * SWITCHING_ON and ON show it on (vtable slot 0x74). Once its model is bound it is ON when its
 * switch is on (unless func_ov004_0223c10c says otherwise), else OFF. */
#ifndef CLEAN_OV004_ROOM_OBJECT_022518E8_H
#define CLEAN_OV004_ROOM_OBJECT_022518E8_H

#include "types.h"

#include "room_object.h"

typedef struct RoomObject022518e8 {
    RoomObject base;
    u8 unk_844;
    u8 state; /* RoomObject022518e8State */
    u8 unk_846[2];
} RoomObject022518e8;

enum RoomObject022518e8State {
    ROOM_OBJECT_022518E8_OFF = 0,
    ROOM_OBJECT_022518E8_SWITCHING_ON = 1,
    ROOM_OBJECT_022518E8_ON = 2,
    ROOM_OBJECT_022518E8_SWITCHING_OFF = 3,
    ROOM_OBJECT_022518E8_STATE_COUNT = 4
};

void RoomObject022518e8_UpdateSwitchingOff(RoomObject022518e8 *object);
int RoomObject022518e8_EnterSwitchingOff(RoomObject022518e8 *object);
void RoomObject022518e8_UpdateOn(RoomObject022518e8 *object);
int RoomObject022518e8_EnterOn(RoomObject022518e8 *object);
void RoomObject022518e8_UpdateSwitchingOn(RoomObject022518e8 *object);
int RoomObject022518e8_EnterSwitchingOn(RoomObject022518e8 *object);
void RoomObject022518e8_UpdateOff(RoomObject022518e8 *object);
int RoomObject022518e8_EnterOff(RoomObject022518e8 *object);
void RoomObject022518e8_UpdateState(RoomObject022518e8 *object);
int RoomObject022518e8_EnterState(RoomObject022518e8 *object, unsigned int state, int value);
u8 RoomObject022518e8_StateIsOn(RoomObject022518e8 *object, unsigned int state);
int RoomObject022518e8_Vfunc0C(void);
int RoomObject022518e8_Update(RoomObject022518e8 *object);
int RoomObject022518e8_Start(RoomObject022518e8 *object);
RoomObject022518e8 *RoomObject022518e8_Delete(RoomObject022518e8 *object);
RoomObject022518e8 *RoomObject022518e8_Destroy(RoomObject022518e8 *object);
RoomObject022518e8 *RoomObject022518e8_Construct(RoomObject022518e8 *object);
void RoomObject022518e8_Create(void);

#endif
