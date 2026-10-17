/* The room object of /roomObj/obj_b_machine (barber_machine.h). */
#include "barber_machine.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/animated_model.h"
#include "main/frame_ctrl.h"
#include "main/room_object_state.h"
#include "member_pointer.h"
#include "rmo_object_base.h"

static_assert(sizeof(RmoObject) == 0x290, "RmoObject size");
static_assert(offsetof(BarberMachine, receiver) == 0x290, "receiver");
static_assert(offsetof(BarberMachine, box) == 0x2d8, "box");
static_assert(offsetof(BarberMachine, shared_run) == 0x374, "shared run");
static_assert(sizeof(BarberMachine) == 0x378, "the size BarberMachine_Create allocates");

#define BARBER_MACHINE_ONE 0x1000 /* normal speed, 20.12 fixed point */
#define BARBER_MACHINE_PLAY_ONCE FRAME_CTRL_ONCE

/* The joint animation of each part of a run. */
#define BARBER_MACHINE_ANIM_STARTING 0
#define BARBER_MACHINE_ANIM_RUNNING 1
#define BARBER_MACHINE_ANIM_STOPPING 2
#define BARBER_MACHINE_SOUND_STARTING 0x4d8
#define BARBER_MACHINE_SOUND_STOPPING 0x4d9

/* Its collision box. */
#define BARBER_MACHINE_WIDTH 0x2000
#define BARBER_MACHINE_DEPTH 0x4000
#define BARBER_MACHINE_HEIGHT 0x2000

/* The point it gives for its position (vtable slot 0x64). */
#define BARBER_MACHINE_POINT_X 0xc000
#define BARBER_MACHINE_POINT_Z 0x17000

/* The vtable slot that enters a state (BarberMachine_SetState). */
#define BARBER_MACHINE_SLOT_SET_STATE 0x60

/* The one that exists, NULL for none. */
extern BarberMachine *data_ov004_02258224;

/* The class's vtable and its receiver part's. */
extern const u8 data_ov004_02254c58[];
extern const u8 data_ov004_02254cc8[];

/* "/roomObj/obj_b_machine.arc" and "/roomObj/obj_b_machine.nsbtx". */
extern const char data_ov004_02254d40[];
extern const char data_ov004_02254d5c[];

extern Heap *data_021c9b24;

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_0225822c;
extern MemberPointer data_ov004_02258230[BARBER_MACHINE_STATE_COUNT];
extern const MemberPointer data_ov004_02254c18, data_ov004_02254c00, data_ov004_02254c08, data_ov004_02254c10;
extern u32 data_ov004_02258228;
extern MemberPointer data_ov004_02258250[BARBER_MACHINE_STATE_COUNT];
extern const MemberPointer data_ov004_02254bf8, data_ov004_02254c30, data_ov004_02254c28, data_ov004_02254c20;

/* The RMO family's base class (rmo_object.h). */
extern int func_ov004_0222c600(RmoObject *object, const char *archive, const char *texture);
extern void func_ov004_0222c598(RmoObject *object);
extern const u8 *func_ov004_0222c3c4(RmoModel *model, int index);
extern RmoObject *func_ov004_0222c7a0(RmoObject *object);
/* Plays a sound at the object's sound source (at 0x250). */
extern int func_ov004_0222c2dc(void *source, int sound);

static AnimatedModel *BarberMachine_body(BarberMachine *self)
{
    return (AnimatedModel *) (void *) &self->base.body;
}

/* The state byte, and the sound source after it. */
static u8 *BarberMachine_state(BarberMachine *self)
{
    return &self->base.unk_24c[0];
}

static void *BarberMachine_sound_source(BarberMachine *self)
{
    return &self->base.unk_24c[4];
}

/* Vtable slot 0x60 (BarberMachine_SetState for this class), called through the vtable. */
static int BarberMachine_call_set_state(BarberMachine *self, unsigned int state)
{
    const u32 *vtable = self->base.actor.vtable;
    return ((int (*)(BarberMachine *, unsigned int))(uintptr_t) vtable[BARBER_MACHINE_SLOT_SET_STATE / 4])(self, state);
}

/* Joint animation `index` played once from its start. */
static void BarberMachine_play(BarberMachine *self, int index)
{
    AnimatedModel_Start(BarberMachine_body(self), func_ov004_0222c3c4(&self->base.body_model, index), BARBER_MACHINE_PLAY_ONCE,
                        BARBER_MACHINE_ONE, 0, 0);
}

/* Once the animation has run out, `next`: directly, or through the shared values while the run
 * is BarberMachine_Run's; until then the animation steps. */
static void BarberMachine_play_on(BarberMachine *self, unsigned char next)
{
    if (FrameCtrl_IsDone(&self->base.body.frames)) {
        if (self->shared_run == 0) {
            BarberMachine_call_set_state(self, next);
            return;
        }
        RoomObjectState_Change((RoomObject *) (void *) self, next);
    } else {
        AnimatedModel_StepFrames(BarberMachine_body(self));
    }
}

/* func_ov004_0222c8c8: the one that exists set running through the shared values (which call
 * vtable slot 0x60 with BARBER_MACHINE_STARTING); when that was done, the run is marked as
 * this one's.
 * QUIRK: answers 0x374 (the flag's offset, left in the register) when it was done, else 0.
 * REQUIRES: one exists (data_ov004_02258224 is not NULL). */
int BarberMachine_Run(void)
{
    int changed = RoomObjectState_Change((RoomObject *) (void *) data_ov004_02258224, BARBER_MACHINE_STARTING);
    if (changed != 0) {
        data_ov004_02258224->shared_run = 1;
        return (int) offsetof(BarberMachine, shared_run);
    }
    return changed;
}
CLEAN_AS(func_ov004_0222c8c8, BarberMachine_Run)

/* func_ov004_0222c8f4: the collision box taken off the field. */
int BarberMachine_RemoveBox(BarberMachine *self)
{
    return CollisionBox_Remove(&self->box);
}
CLEAN_AS(func_ov004_0222c8f4, BarberMachine_RemoveBox)

/* func_ov004_0222c904: the collision box put on the field at its position. */
int BarberMachine_AddBox(BarberMachine *self)
{
    return CollisionBox_Add(&self->box, BARBER_MACHINE_WIDTH, BARBER_MACHINE_DEPTH, BARBER_MACHINE_HEIGHT,
                            &self->base.actor.position, 0, NULL);
}
CLEAN_AS(func_ov004_0222c904, BarberMachine_AddBox)

/* func_ov004_0222c934 (update of BARBER_MACHINE_STOPPING): at rest once the animation has run
 * out, else the animation steps. */
void BarberMachine_UpdateStopping(BarberMachine *self)
{
    if (FrameCtrl_IsDone(&self->base.body.frames)) {
        BarberMachine_call_set_state(self, BARBER_MACHINE_REST);
    } else {
        AnimatedModel_StepFrames(BarberMachine_body(self));
    }
}
CLEAN_AS(func_ov004_0222c934, BarberMachine_UpdateStopping)

/* func_ov004_0222c964 (entry of BARBER_MACHINE_STOPPING): the last animation with its sound;
 * the run is no longer BarberMachine_Run's. */
int BarberMachine_EnterStopping(BarberMachine *self)
{
    BarberMachine_play(self, BARBER_MACHINE_ANIM_STOPPING);
    func_ov004_0222c2dc(BarberMachine_sound_source(self), BARBER_MACHINE_SOUND_STOPPING);
    self->shared_run = 0;
    return 1;
}
CLEAN_AS(func_ov004_0222c964, BarberMachine_EnterStopping)

/* func_ov004_0222c9b8 (update of BARBER_MACHINE_RUNNING) */
void BarberMachine_UpdateRunning(BarberMachine *self)
{
    BarberMachine_play_on(self, BARBER_MACHINE_STOPPING);
}
CLEAN_AS(func_ov004_0222c9b8, BarberMachine_UpdateRunning)

/* func_ov004_0222c9fc (entry of BARBER_MACHINE_RUNNING) */
int BarberMachine_EnterRunning(BarberMachine *self)
{
    BarberMachine_play(self, BARBER_MACHINE_ANIM_RUNNING);
    return 1;
}
CLEAN_AS(func_ov004_0222c9fc, BarberMachine_EnterRunning)

/* func_ov004_0222ca34 (update of BARBER_MACHINE_STARTING) */
void BarberMachine_UpdateStarting(BarberMachine *self)
{
    BarberMachine_play_on(self, BARBER_MACHINE_RUNNING);
}
CLEAN_AS(func_ov004_0222ca34, BarberMachine_UpdateStarting)

/* func_ov004_0222ca78 (entry of BARBER_MACHINE_STARTING): the first animation with its sound. */
int BarberMachine_EnterStarting(BarberMachine *self)
{
    BarberMachine_play(self, BARBER_MACHINE_ANIM_STARTING);
    func_ov004_0222c2dc(BarberMachine_sound_source(self), BARBER_MACHINE_SOUND_STARTING);
    return 1;
}
CLEAN_AS(func_ov004_0222ca78, BarberMachine_EnterStarting)

/* func_ov004_0222cac0 (update of BARBER_MACHINE_REST): nothing. */
void BarberMachine_UpdateRest(BarberMachine *self)
{
    (void) self;
}
CLEAN_AS(func_ov004_0222cac0, BarberMachine_UpdateRest)

/* func_ov004_0222cac4 (entry of BARBER_MACHINE_REST): the first animation started from its
 * first frame, without sound; nothing steps it in this state. */
int BarberMachine_EnterRest(BarberMachine *self)
{
    BarberMachine_play(self, BARBER_MACHINE_ANIM_STARTING);
    return 1;
}
CLEAN_AS(func_ov004_0222cac4, BarberMachine_EnterRest)

/* _ZN18Obj_ov004_02254c5819func_ov004_0222cafcEv: the state's update, through its table; a
 * state byte of 4 or more runs none. */
void BarberMachine_UpdateState(BarberMachine *self)
{
    static const MemberPointer *const updates[BARBER_MACHINE_STATE_COUNT] = {
        &data_ov004_02254c18, /* BarberMachine_UpdateRest */
        &data_ov004_02254c00, /* BarberMachine_UpdateStarting */
        &data_ov004_02254c08, /* BarberMachine_UpdateRunning */
        &data_ov004_02254c10, /* BarberMachine_UpdateStopping */
    };
    MemberTable_InitOnce(&data_ov004_0225822c, data_ov004_02258230, updates, BARBER_MACHINE_STATE_COUNT);
    u8 state = *BarberMachine_state(self);
    if (state < BARBER_MACHINE_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_02258230[state], self);
    }
}
CLEAN_AS(_ZN18Obj_ov004_02254c5819func_ov004_0222cafcEv, BarberMachine_UpdateState)

/* func_ov004_0222cb88 (vtable slot 0x60): enters `state` if its entry (through a table)
 * agrees; whether it did. */
int BarberMachine_SetState(BarberMachine *self, unsigned int state)
{
    static const MemberPointer *const entries[BARBER_MACHINE_STATE_COUNT] = {
        &data_ov004_02254bf8, /* BarberMachine_EnterRest */
        &data_ov004_02254c30, /* BarberMachine_EnterStarting */
        &data_ov004_02254c28, /* BarberMachine_EnterRunning */
        &data_ov004_02254c20, /* BarberMachine_EnterStopping */
    };
    MemberTable_InitOnce(&data_ov004_02258228, data_ov004_02258250, entries, BARBER_MACHINE_STATE_COUNT);
    if (state < BARBER_MACHINE_STATE_COUNT && MemberPointer_CallInt(&data_ov004_02258250[state], self) != 0) {
        *BarberMachine_state(self) = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0222cb88, BarberMachine_SetState)

/* func_ov004_0222cc24 (vtable slot 0x64; the base class gives its position): the fixed point
 * (0xc000, 0, 0x17000). */
void BarberMachine_GetPosition(BarberMachine *self, Vec3 *out)
{
    (void) self;
    out->x = BARBER_MACHINE_POINT_X;
    out->y = 0;
    out->z = BARBER_MACHINE_POINT_Z;
}
CLEAN_AS(func_ov004_0222cc24, BarberMachine_GetPosition)

/* func_ov004_0222cc40 (vtable slot 0x0c): off the field, the archive released and no longer the
 * one that exists. */
int BarberMachine_Release(BarberMachine *self)
{
    BarberMachine_RemoveBox(self);
    func_ov004_0222c598(&self->base);
    data_ov004_02258224 = NULL;
    return 1;
}
CLEAN_AS(func_ov004_0222cc40, BarberMachine_Release)

/* func_ov004_0222cc60 (vtable slot 0x24) */
int BarberMachine_Draw(BarberMachine *self)
{
    AnimatedModel_Draw(BarberMachine_body(self), NULL);
    return 1;
}
CLEAN_AS(func_ov004_0222cc60, BarberMachine_Draw)

/* _ZN18Obj_ov004_02254c5819func_ov004_0222cc74Ev (vtable slot 0x18) */
int BarberMachine_Update(BarberMachine *self)
{
    BarberMachine_UpdateState(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_02254c5819func_ov004_0222cc74Ev, BarberMachine_Update)

/* func_ov004_0222cc84 (vtable slot 0x00): becomes the one that exists with no run of
 * BarberMachine_Run's, loads its archive and texture, goes on the field and, when it has a
 * first joint animation that the model can take, starts it once and attaches it. Its state
 * stays at rest as the allocation zeroed it. */
int BarberMachine_Start(BarberMachine *self)
{
    data_ov004_02258224 = self;
    self->shared_run = 0;
    func_ov004_0222c600(&self->base, data_ov004_02254d40, data_ov004_02254d5c);
    BarberMachine_AddBox(self);
    if (func_ov004_0222c3c4(&self->base.body_model, BARBER_MACHINE_ANIM_STARTING) != NULL &&
        AnimatedModel_LoadAnim(BarberMachine_body(self), data_021c9b24) != 0) {
        BarberMachine_play(self, BARBER_MACHINE_ANIM_STARTING);
        AnimatedModel_Attach(BarberMachine_body(self));
    }
    return 1;
}
CLEAN_AS(func_ov004_0222cc84, BarberMachine_Start)

static void BarberMachine_set_vtables(BarberMachine *self)
{
    self->base.actor.vtable = data_ov004_02254c58;
    self->receiver.base.vtable = data_ov004_02254cc8;
}

/* func_ov004_0222cd0c (the deleting destructor, vtable slot 0x44) */
BarberMachine *BarberMachine_Delete(BarberMachine *self)
{
    BarberMachine_set_vtables(self);
    CollisionBox_Destruct(&self->box);
    TalkReceiver_Destruct(&self->receiver);
    func_ov004_0222c7a0(&self->base);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_0222cd0c, BarberMachine_Delete)

/* func_ov004_0222cd50 (the destructor, vtable slot 0x40) */
BarberMachine *BarberMachine_Destruct(BarberMachine *self)
{
    BarberMachine_set_vtables(self);
    CollisionBox_Destruct(&self->box);
    TalkReceiver_Destruct(&self->receiver);
    func_ov004_0222c7a0(&self->base);
    return self;
}
CLEAN_AS(func_ov004_0222cd50, BarberMachine_Destruct)

/* func_ov004_0222cd8c (the constructor) */
BarberMachine *BarberMachine_Construct(BarberMachine *self)
{
    RmoObjectBase_Construct(&self->base);
    TalkReceiver_ConstructBase(&self->receiver);
    BarberMachine_set_vtables(self);
    CollisionBox_Construct(&self->box);
    return self;
}
CLEAN_AS(func_ov004_0222cd8c, BarberMachine_Construct)

/* func_ov004_0222cdc8: a new one from the room's heap; nothing when it has no room. */
void BarberMachine_Create(void)
{
    BarberMachine *self = Heap_AllocAuxZeroed(sizeof(BarberMachine));
    if (self != NULL) {
        BarberMachine_Construct(self);
    }
}
CLEAN_AS(func_ov004_0222cdc8, BarberMachine_Create)

/* The receiver part (at 0x290) enters the destructors through its vtable with these: each
 * moves the pointer back to the object and goes on with the object's destructor. */
static BarberMachine *BarberMachine_from_receiver(void *receiver)
{
    return (BarberMachine *) (void *) ((u8 *) receiver - offsetof(BarberMachine, receiver));
}

/* func_ov004_0222cde4: the deleting destructor, entered from the receiver part. */
BarberMachine *BarberMachineReceiver_Delete(void *receiver)
{
    return BarberMachine_Delete(BarberMachine_from_receiver(receiver));
}
CLEAN_AS(_ZThn656_N18Obj_ov004_02254c58D0Ev, BarberMachineReceiver_Delete)

/* func_ov004_0222ce00: the destructor, entered from the receiver part. */
BarberMachine *BarberMachineReceiver_Destruct(void *receiver)
{
    return BarberMachine_Destruct(BarberMachine_from_receiver(receiver));
}
CLEAN_AS(_ZThn656_N18Obj_ov004_02254c58D1Ev, BarberMachineReceiver_Destruct)
