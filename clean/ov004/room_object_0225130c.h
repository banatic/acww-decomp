/* A class of overlay 4's room objects (vtable 0x0225130c, receiver part 0x022513b8, 0x848
 * bytes) that keeps sound 0x42a playing at its centre and runs through five states, entered
 * through vtable slot 0x70 and dispatched through tables of member pointers (member_pointer.h):
 *
 * - off: the switch off; touching it (a change of the switch pending) requests starting;
 * - starting: the switch on, sound 2 of its row and the animations of variant 0 once; then
 *   running;
 * - running: the switch on and the animations of variant 1 from their end; at frames 0 and
 *   0x14 of the joint animation it sets variable 0 of its sound (to 1, and at 0x14 to 1 and 2
 *   in turn); touching it requests stopping;
 * - stopping: the switch off, sound 4 of its row and the animations of variant 1 once from
 *   where they are, still setting the sound as when running; then settling;
 * - settling: the animations of variant 0 from their end, the sound's variable set to 1 once;
 *   then off.
 *
 * Starting and running show it on (vtable slot 0x74). Once its model is bound it is running
 * when its switch is on (unless func_ov004_0223c10c says otherwise), else off. */
#ifndef CLEAN_OV004_ROOM_OBJECT_0225130C_H
#define CLEAN_OV004_ROOM_OBJECT_0225130C_H

#include "types.h"

#include "room_object.h"

typedef struct RoomObject0225130c {
    RoomObject base;
    u8 unk_844;      /* cleared once its model is bound */
    u8 ticks;        /* times frame 0x14 of the joint animation was reached: odd sets 2 */
    u8 settle_reset; /* set when settling starts, until the sound's variable is set to 1 */
    u8 state;        /* RoomObject0225130cState */
} RoomObject0225130c;

enum RoomObject0225130cState {
    ROOM_OBJECT_0225130C_OFF = 0,
    ROOM_OBJECT_0225130C_STARTING = 1,
    ROOM_OBJECT_0225130C_RUNNING = 2,
    ROOM_OBJECT_0225130C_STOPPING = 3,
    ROOM_OBJECT_0225130C_SETTLING = 4,
    ROOM_OBJECT_0225130C_STATE_COUNT = 5
};

void RoomObject0225130c_UpdateSettling(RoomObject0225130c *object);
int RoomObject0225130c_EnterSettling(RoomObject0225130c *object);
void RoomObject0225130c_UpdateStopping(RoomObject0225130c *object);
int RoomObject0225130c_EnterStopping(RoomObject0225130c *object);
void RoomObject0225130c_UpdateRunning(RoomObject0225130c *object);
int RoomObject0225130c_EnterRunning(RoomObject0225130c *object);
void RoomObject0225130c_UpdateStarting(RoomObject0225130c *object);
int RoomObject0225130c_EnterStarting(RoomObject0225130c *object);
void RoomObject0225130c_UpdateOff(RoomObject0225130c *object);
int RoomObject0225130c_EnterOff(RoomObject0225130c *object);
void RoomObject0225130c_UpdateState(RoomObject0225130c *object);
int RoomObject0225130c_EnterState(RoomObject0225130c *object, unsigned int state, int value);
u8 RoomObject0225130c_StateIsOn(RoomObject0225130c *object, unsigned int state);
int RoomObject0225130c_Vfunc0C(void);
int RoomObject0225130c_UpdateUnsettled(RoomObject0225130c *object);
int RoomObject0225130c_Update(RoomObject0225130c *object);
int RoomObject0225130c_Start(RoomObject0225130c *object);
RoomObject0225130c *RoomObject0225130c_Delete(RoomObject0225130c *object);
RoomObject0225130c *RoomObject0225130c_Destroy(RoomObject0225130c *object);
RoomObject0225130c *RoomObject0225130c_Construct(RoomObject0225130c *object);
void RoomObject0225130c_Create(void);

#endif
