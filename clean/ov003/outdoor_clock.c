/* The clock whose model's joints turn by the time of day (outdoor_clock.h). */
#include "outdoor_clock.h"

#include <stdint.h>

#include "autoload_2/heap.h" /* Heap_FreeAux, Heap_AllocAuxZeroed */
#include "clean.h"

static_assert(offsetof(OutdoorClock, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(OutdoorClock, model_object) == 0x13c, "model object");
static_assert(offsetof(OutdoorClock, model) == 0x198, "model");
static_assert(offsetof(OutdoorClock, hour_node) == 0x2b4, "hour node");
static_assert(offsetof(OutdoorClock, minute_node) == 0x2b5, "minute node");
static_assert(sizeof(OutdoorClock) == 0x2b8, "the size OutdoorClock_New allocates");
static_assert(offsetof(OutdoorClockRenderObject, clock) == 0x2c, "render object user");

#define OUTDOOR_CLOCK_RECEIVER_OFFSET 0xec
#define OUTDOOR_CLOCK_NO_NODE (-1)
/* The render state's command whose hook the clock sets: a joint's description, after it. */
#define OUTDOOR_CLOCK_COMMAND_NODE_DESC 6
#define OUTDOOR_CLOCK_TIMING_AFTER 2
/* The vtable slot the hook hands each joint to (OutdoorClock_TurnHand). */
#define OUTDOOR_CLOCK_SLOT_TURN_HAND 0x60

/* "kh_j" and "km_j": the joints of the hour hand and the minute hand. */
extern const char data_ov003_02239224[];
extern const char data_ov003_0223922c[];
/* The vtables: the class's and its receiver part's. */
extern const u8 data_ov003_022390e8[];
extern const u8 data_ov003_022391ac[];

/* The index of the model's joint named `name`, -1 for none. */
extern int func_0205790c(void *model, const char *name);
/* Sets the hook the model object's render state runs for `command` at `timing`, and the object
 * it is given. */
extern void func_02055de0(void *model_object, int hook, int command, int timing, OutdoorClock *user, int a5);
/* Turn the joint being described by the clock's time: as an hour hand, as a minute hand. */
extern void func_020b3220(OutdoorClockRenderState *state);
extern void func_020b3188(OutdoorClockRenderState *state);
/* Overlay 9's scene actor: its destructor and its constructor. */
extern void *func_ov009_0226539c(OutdoorClock *clock);
extern void *func_ov009_0226552c(OutdoorClock *clock);
/* The hook is the game's function: its address goes to the model object. */
extern void func_ov003_0221db90(OutdoorClockRenderState *state);

/* func_ov003_0221da64 (vtable slot 0x98): always 1. */
int OutdoorClock_Slot98(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221da64, OutdoorClock_Slot98)

/* func_ov003_0221da68 (vtable slot 0x60, a joint being described): turns the hour hand's joint
 * and the minute hand's joint; other joints are left alone. */
void OutdoorClock_TurnHand(OutdoorClock *clock, int node, OutdoorClockRenderState *state)
{
    if (node == clock->hour_node) {
        func_020b3220(state);
    } else if (node == clock->minute_node) {
        func_020b3188(state);
    }
}
CLEAN_AS(func_ov003_0221da68, OutdoorClock_TurnHand)

/* func_ov003_0221da98 (vtable slot 0x70, setting it up): finds the joints "kh_j" and "km_j" of
 * its model and, when both are there, hooks each joint's description (func_ov003_0221db90);
 * always 1. */
int OutdoorClock_Init(OutdoorClock *clock)
{
    clock->hour_node = (s8) func_0205790c(clock->model, data_ov003_02239224);
    clock->minute_node = (s8) func_0205790c(clock->model, data_ov003_0223922c);
    if (clock->hour_node != OUTDOOR_CLOCK_NO_NODE && clock->minute_node != OUTDOOR_CLOCK_NO_NODE) {
        func_02055de0(clock->model_object, (int) (uintptr_t) func_ov003_0221db90, OUTDOOR_CLOCK_COMMAND_NODE_DESC,
                      OUTDOOR_CLOCK_TIMING_AFTER, clock, 0);
    }
    return 1;
}
CLEAN_AS(func_ov003_0221da98, OutdoorClock_Init)

/* The vtables set back, then overlay 9's destructor. */
static void outdoor_clock_destroy_parts(OutdoorClock *clock)
{
    clock->vtable = data_ov003_022390e8;
    clock->receiver_vtable = data_ov003_022391ac;
    func_ov009_0226539c(clock);
}

/* func_ov003_0221db04 (vtable slot 0x44, the deleting destructor): the destructor's work, then
 * the memory freed. */
OutdoorClock *OutdoorClock_DestroyAndFree(OutdoorClock *clock)
{
    outdoor_clock_destroy_parts(clock);
    Heap_FreeAux(clock);
    return clock;
}
CLEAN_AS(func_ov003_0221db04, OutdoorClock_DestroyAndFree)

/* func_ov003_0221db30 (vtable slot 0x40): the destructor. */
OutdoorClock *OutdoorClock_Destroy(OutdoorClock *clock)
{
    outdoor_clock_destroy_parts(clock);
    return clock;
}
CLEAN_AS(func_ov003_0221db30, OutdoorClock_Destroy)

/* func_ov003_0221db54: the constructor: overlay 9's, the vtables; no joints yet. */
OutdoorClock *OutdoorClock_Construct(OutdoorClock *clock)
{
    func_ov009_0226552c(clock);
    clock->vtable = data_ov003_022390e8;
    clock->receiver_vtable = data_ov003_022391ac;
    clock->minute_node = OUTDOOR_CLOCK_NO_NODE;
    clock->hour_node = clock->minute_node;
    return clock;
}
CLEAN_AS(func_ov003_0221db54, OutdoorClock_Construct)

/* func_ov003_0221db90 (the hook func_02055de0 is given, run after each joint's description):
 * hands the joint (byte 1 of the command) and the state to vtable slot 0x60 of the clock, when
 * the render object has one. */
void OutdoorClock_RunNodeHook(OutdoorClockRenderState *state)
{
    typedef void (*OutdoorClockTurnSlot)(OutdoorClock *clock, int node, OutdoorClockRenderState *state);

    OutdoorClock *clock = state->render_object->clock;
    if (clock != NULL) {
        u32 slot = *(const u32 *) ((const u8 *) clock->vtable + OUTDOOR_CLOCK_SLOT_TURN_HAND);
        ((OutdoorClockTurnSlot) (uintptr_t) slot)(clock, state->command[1], state);
    }
}
CLEAN_AS(func_ov003_0221db90, OutdoorClock_RunNodeHook)

/* func_ov003_0221dbb0 (the clock's entry in the overlay's table of profiles): allocates and
 * constructs one; nothing keeps the pointer here. */
void OutdoorClock_New(void)
{
    OutdoorClock *clock = Heap_AllocAuxZeroed(sizeof(OutdoorClock));
    if (clock != NULL) {
        OutdoorClock_Construct(clock);
    }
}
CLEAN_AS(func_ov003_0221dbb0, OutdoorClock_New)

/* ---- The receiver vtable's thunks: each finds the clock around `receiver`. */

static OutdoorClock *outdoor_clock_from_receiver(void *receiver)
{
    return (OutdoorClock *) (void *) ((u8 *) receiver - OUTDOOR_CLOCK_RECEIVER_OFFSET);
}

/* _ZThn236_N18Obj_ov003_022390e8D0Ev: OutdoorClock_DestroyAndFree. */
OutdoorClock *OutdoorClock_ReceiverDestroyAndFree(void *receiver)
{
    return OutdoorClock_DestroyAndFree(outdoor_clock_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_022390e8D0Ev, OutdoorClock_ReceiverDestroyAndFree)

/* _ZThn236_N18Obj_ov003_022390e8D1Ev: OutdoorClock_Destroy. */
OutdoorClock *OutdoorClock_ReceiverDestroy(void *receiver)
{
    return OutdoorClock_Destroy(outdoor_clock_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_022390e8D1Ev, OutdoorClock_ReceiverDestroy)
