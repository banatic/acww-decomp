/* A room object of the RMO family (rmo_object.h; vtable 0x02254c58, receiver part 0x02254cc8
 * at 0x290, 0x378 bytes) built from /roomObj/obj_b_machine.arc and its .nsbtx: a machine that
 * overlay 53 (the barber's, "sp_npc_barber") sets running with BarberMachine_Run. Only one
 * exists at a time: data_ov004_02258224 points to it from its start to its release.
 *
 * It stands in a collision box 0x2000 wide, 0x4000 deep and 0x2000 high at its position, and
 * gives the point (0xc000, 0, 0x17000) for its position (vtable slot 0x64).
 *
 * Its state (RmoObject byte 0x24c) is entered through vtable slot 0x60 and stepped by its
 * update, through tables of member pointers (member_pointer.h). At rest it shows the first
 * frame of joint animation 0; a run plays joint animations 0, 1 and 2 once each, with sound
 * 0x4d8 at the start and 0x4d9 at the last, and comes back to rest. A run that
 * BarberMachine_Run started goes from its first to its second and third animation through the
 * room objects' shared values (main/room_object_state.h), one started otherwise directly. */
#ifndef CLEAN_OV004_BARBER_MACHINE_H
#define CLEAN_OV004_BARBER_MACHINE_H

#include "autoload_2/vector.h"
#include "main/collision_box.h"
#include "main/talk_receiver.h"
#include "rmo_object.h"
#include "types.h"

typedef struct BarberMachine {
    RmoObject base;        /* 0x000: base.unk_24c[0] is the state */
    TalkReceiver receiver; /* 0x290: vtable data_ov004_02254cc8 */
    CollisionBox box;      /* 0x2d8 */
    u8 shared_run;         /* 0x374: set by BarberMachine_Run, cleared by the last animation */
    u8 pad_375[3];
} BarberMachine;

/* Its states (BarberMachine.base.unk_24c[0]). */
enum BarberMachineState {
    BARBER_MACHINE_REST = 0,
    BARBER_MACHINE_STARTING = 1, /* joint animation 0 */
    BARBER_MACHINE_RUNNING = 2,  /* joint animation 1 */
    BARBER_MACHINE_STOPPING = 3, /* joint animation 2 */
    BARBER_MACHINE_STATE_COUNT = 4
};

int BarberMachine_Run(void);
int BarberMachine_RemoveBox(BarberMachine *self);
int BarberMachine_AddBox(BarberMachine *self);
void BarberMachine_UpdateStopping(BarberMachine *self);
int BarberMachine_EnterStopping(BarberMachine *self);
void BarberMachine_UpdateRunning(BarberMachine *self);
int BarberMachine_EnterRunning(BarberMachine *self);
void BarberMachine_UpdateStarting(BarberMachine *self);
int BarberMachine_EnterStarting(BarberMachine *self);
void BarberMachine_UpdateRest(BarberMachine *self);
int BarberMachine_EnterRest(BarberMachine *self);
void BarberMachine_UpdateState(BarberMachine *self);
int BarberMachine_SetState(BarberMachine *self, unsigned int state);
void BarberMachine_GetPosition(BarberMachine *self, Vec3 *out);
int BarberMachine_Release(BarberMachine *self);
int BarberMachine_Draw(BarberMachine *self);
int BarberMachine_Update(BarberMachine *self);
int BarberMachine_Start(BarberMachine *self);
BarberMachine *BarberMachine_Delete(BarberMachine *self);
BarberMachine *BarberMachine_Destruct(BarberMachine *self);
BarberMachine *BarberMachine_Construct(BarberMachine *self);
void BarberMachine_Create(void);
BarberMachine *BarberMachineReceiver_Delete(void *receiver);
BarberMachine *BarberMachineReceiver_Destruct(void *receiver);

#endif
