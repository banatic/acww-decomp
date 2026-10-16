/* The main program's part of the field actor's class (field_actor.h). */
#include "field_actor.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "field_actor_parts.h"
#include "main/item_code.h"
#include "main/session.h"
#include "sound_emitter.h"

/* The heap the field actors are made on. */
extern Heap *data_021c9ab4;

/* The vtables: the class's, the one of its message receiver (at 0xec), and the one of the
 * sound emitter at 0x880, whose destructor callers inline. */
extern const u8 data_020d82b4[];
extern const u8 data_020d832c[];
extern const u8 data_020d8414[];

/* The alignment of the objects (4). */
extern int func_020952e0(void);

extern int func_020051b4(struct FieldActor *actor);
extern void func_02005338(struct FieldActor *actor);
extern void func_020058e4(struct FieldActor *actor);

/* The destructors of the members and bases, in the order the deleting destructor runs them. */
extern int func_0200e91c(void *request);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void func_0201a790(void *member);
extern void func_020f5914(void *emitter);
extern void *func_020f5400(void *emitter);
extern void *func_02032c50(void *member);
extern void func_0205f8d4(void *member);
extern void func_0205d51c(void *member);
extern void func_02064638(void *member);
extern void *func_02056910(void *member);
extern void func_0205db6c(void *member);
extern void func_0205d8e8(void *member);
extern void func_0205dcd4(void *member);
extern void func_0205cce4(void *member);
extern void *func_0205ef90(void *member);
extern void func_0205df18(void *member);
extern void *func_02055764(void *member);
extern void func_0205e4ec(void *member);
extern void func_0205d0bc(void *member);
extern void func_0205f770(void *member);
extern void *func_02054b64(void *member);
extern int func_020b7ed8(void *member);
extern void *func_02089bbc(void *member);
extern void *func_02066994(void *receiver);
extern void *func_0203f080(void *actor);

/* The constructors of the base, the receiver and the members, as FieldActor_Construct runs
 * them; StateRequest_Construct makes an entry of the request queue. */
extern void *func_0203f130(void *actor);
extern void *func_02066a30(void *receiver);
extern void *func_02089bd4(void *member);
extern void *func_020b7ee8(void *member);
extern void *func_02054bac(void *member);
extern void func_0205f774(void *member);
extern void func_0205d0c0(void *member);
extern void *func_0205577c(void *member);
extern void func_0205e4f0(void *member);
extern void func_0205df1c(void *member);
extern void *func_0205efac(void *member);
extern void func_0205cce8(void *member);
extern void func_0205dcd8(void *member);
extern void func_0205d8ec(void *member);
extern void func_0205db70(void *member);
extern void *func_02056928(void *member);
extern void func_0206463c(void *member);
extern void func_0205d520(void *member);
extern void *func_020b9e58(void *member);
extern void func_0205f8d8(void *member);
extern void *func_02032c64(void *member);
extern void *func_020f5430(void *emitter);
extern void *func_020f55cc(void *emitter);
extern void func_0201a794(void *member);
extern u32 func_0200e92c(void *request);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

/* What FieldActor_Shutdown releases. */
extern NetSession *data_020ccf94;
extern void func_0209129c(int effect);
extern void func_020962b8(int player);
extern int func_02073d90(NetSession *session);
extern int func_02073908(void *session, int player);
extern void func_020771cc(int a, void *out, int c, int d);
extern void func_020b9e2c(void *member);
extern void func_0205682c(void *member);
extern int func_02055454(void *model);
extern void func_0205502c(void *model);
extern void func_0205ebb4(void *held);
extern void func_0205defc(void *part);
extern void func_0205e4b0(void *part);
extern void func_0205d4e8(void *member);
extern void func_0205d084(void *member);
extern void func_020961e0(int player);
extern void func_02035638(int a);
extern void func_020b8db4(void);

/* The queue of state requests at 0x934: 30 of 0x1c bytes. */
#define REQUEST_QUEUE 0x934
#define REQUEST_COUNT 30
#define REQUEST_SIZE 0x1c

/* The byte `offset` into the actor. */
static u8 *at(struct FieldActor *actor, u32 offset)
{
    return (u8 *) actor + offset;
}

static void set_vtable(struct FieldActor *actor, u32 offset, const u8 *vtable)
{
    *(const u8 **) at(actor, offset) = vtable;
}

/* func_02004ba8: the class's operator delete. */
void FieldActor_Delete(void *actor)
{
    Heap_Free(data_021c9ab4, actor);
}
CLEAN_AS(func_02004ba8, FieldActor_Delete)

/* func_02004bbc: the class's operator new: `size` bytes, zeroed, or NULL. */
void *FieldActor_New(int size)
{
    Heap *heap = data_021c9ab4;
    void *actor = Heap_AllocAligned(heap, size, func_020952e0());
    if (actor == NULL) {
        return NULL;
    }
    memset(actor, 0, (size_t) size);
    return actor;
}
CLEAN_AS(func_02004bbc, FieldActor_New)

/* func_02004bf4: vtable slot 0x0c, run when the actor goes away (func_020051b4). QUIRK: the
 * original ends in a call to it and so gives back its result; like the matching source, this
 * returns none. */
void FieldActor_Teardown(struct FieldActor *actor)
{
    func_020051b4(actor);
}
CLEAN_AS(func_02004bf4, FieldActor_Teardown)

/* func_02004bfc: vtable slot 0x24 (func_02005338), then 1. */
int FieldActor_Vfunc24(struct FieldActor *actor)
{
    func_02005338(actor);
    return 1;
}
CLEAN_AS(func_02004bfc, FieldActor_Vfunc24)

/* func_02004c0c: vtable slot 0x18, the frame's update with the state machine (func_020058e4),
 * then 1. */
int FieldActor_Update(struct FieldActor *actor)
{
    func_020058e4(actor);
    return 1;
}
CLEAN_AS(func_02004c0c, FieldActor_Update)

/* func_02004c1c: vtable slot 0x00, the set-up once the actor is made (FieldActor_Init). QUIRK:
 * as FieldActor_Teardown, the original gives back the callee's result and this none. */
void FieldActor_Setup(struct FieldActor *actor)
{
    FieldActor_Init(actor);
}
CLEAN_AS(func_02004c1c, FieldActor_Setup)

/* The members are destroyed in the reverse order of their places, then the message receiver
 * and the base. */
static void destroy(struct FieldActor *actor)
{
    set_vtable(actor, 0x000, data_020d82b4);
    set_vtable(actor, 0x0ec, data_020d832c);
    __cxa_vec_cleanup(at(actor, REQUEST_QUEUE), REQUEST_COUNT, REQUEST_SIZE, (void (*)(void *))(uintptr_t) func_0200e91c);
    func_0201a790(at(actor, 0x90c));
    set_vtable(actor, 0x880, data_020d8414);
    func_020f5914(at(actor, 0x880));
    func_020f5400(at(actor, 0x83c));
    func_02032c50(at(actor, 0x7a4));
    func_0205f8d4(at(actor, 0x7a0));
    func_0205d51c(at(actor, 0x774));
    func_02064638(at(actor, 0x768));
    func_02056910(at(actor, 0x73c));
    func_02056910(at(actor, 0x710));
    func_0205db6c(at(actor, 0x70f));
    func_0205d8e8(at(actor, 0x70e));
    func_0205dcd4(at(actor, 0x70d));
    func_0205cce4(at(actor, 0x701));
    func_0205cce4(at(actor, 0x700));
    func_0205ef90(at(actor, 0x5a0));
    func_0205df18(at(actor, 0x59c));
    func_02055764(at(actor, 0x500));
    func_02055764(at(actor, 0x464));
    func_0205e4ec(at(actor, 0x428));
    func_02055764(at(actor, 0x38c));
    func_0205d0bc(at(actor, 0x389));
    func_0205f770(at(actor, 0x388));
    func_02054b64(at(actor, 0x234));
    func_020b7ed8(at(actor, 0x214));
    func_02089bbc(at(actor, 0x1c4));
    func_02089bbc(at(actor, 0x174));
    func_02066994(at(actor, 0x0ec));
    func_0203f080(actor);
}

/* func_02004c24: the deleting destructor (vtable slot 0x44): destroys the actor and frees its
 * memory. Returns the actor. */
struct FieldActor *FieldActor_DestructDelete(struct FieldActor *actor)
{
    destroy(actor);
    FieldActor_Delete(actor);
    return actor;
}
CLEAN_AS(func_02004c24, FieldActor_DestructDelete)

/* func_02004db0: the destructor, without freeing the memory. Returns the actor. */
void *FieldActor_Destruct(struct FieldActor *actor)
{
    destroy(actor);
    return actor;
}
CLEAN_AS(func_02004db0, FieldActor_Destruct)

/* func_02004f34: the constructor: the base and the message receiver, the vtables, the members
 * in the order of their places, then the starting values. The memory comes zeroed from
 * FieldActor_New; what is not set here stays 0. */
struct FieldActor *FieldActor_Construct(struct FieldActor *actor)
{
    func_0203f130(actor);
    func_02066a30(at(actor, 0x0ec));
    set_vtable(actor, 0x000, data_020d82b4);
    set_vtable(actor, 0x0ec, data_020d832c);
    func_02089bd4(at(actor, 0x174));
    func_02089bd4(at(actor, 0x1c4));
    func_020b7ee8(at(actor, 0x214));
    func_02054bac(at(actor, 0x234));
    func_0205f774(at(actor, 0x388));
    func_0205d0c0(at(actor, 0x389));
    func_0205577c(at(actor, 0x38c));
    func_0205e4f0(at(actor, 0x428));
    func_0205577c(at(actor, 0x464));
    func_0205577c(at(actor, 0x500));
    func_0205df1c(at(actor, 0x59c));
    func_0205efac(at(actor, 0x5a0));
    func_0205cce8(at(actor, 0x700));
    func_0205cce8(at(actor, 0x701));
    func_0205dcd8(at(actor, 0x70d));
    func_0205d8ec(at(actor, 0x70e));
    func_0205db70(at(actor, 0x70f));
    func_02056928(at(actor, 0x710));
    func_02056928(at(actor, 0x73c));
    func_0206463c(at(actor, 0x768));
    func_0205d520(at(actor, 0x774));
    func_020b9e58(at(actor, 0x778));
    func_0205f8d8(at(actor, 0x7a0));
    func_02032c64(at(actor, 0x7a4));
    actor->item = ITEM_CODE_NONE;
    actor->unk_822 = ITEM_CODE_NONE;
    func_020f5430(at(actor, 0x83c));
    func_020f55cc(at(actor, 0x880));
    for (int i = 0; i < 2; i++) {
        actor->front_tile[i] = 0;
        actor->tile[i] = 0;
        actor->pending_tile[i] = 0;
    }
    FIELD_ACTOR_PENDING_X(actor) = 0;
    FIELD_ACTOR_PENDING_Z(actor) = 0;
    func_0201a794(at(actor, 0x90c));
    __cxa_vec_ctor(at(actor, REQUEST_QUEUE), REQUEST_COUNT, REQUEST_SIZE, (void (*)(void *))(uintptr_t) func_0200e92c,
                   (void (*)(void *))(uintptr_t) func_0200e91c);
    actor->player = 4; /* none */
    actor->animation = 0xa1;
    FIELD_ACTOR_FIELD(actor, int, 0x708) = 0x144;
    FIELD_ACTOR_FIELD(actor, int, 0x76c) = 0x16f;
    FIELD_ACTOR_FIELD(actor, int, 0x770) = 0x16f;
    actor->aim_mode = 2;
    FIELD_ACTOR_FIELD(actor, int, 0xc80) = -1;
    FIELD_ACTOR_FIELD(actor, int, 0xc8c) = 2;
    FIELD_ACTOR_FIELD(actor, int, 0xc94) = 2;
    FIELD_ACTOR_REMOTE_STATE(actor) = FIELD_ACTOR_STATES;
    actor->unk_C84 = -1;
    FIELD_ACTOR_ENTERED_STATE(actor) = FIELD_ACTOR_STATES;
    return actor;
}
CLEAN_AS(func_02004f34, FieldActor_Construct)

/* func_020051b4: run when the actor goes away (FieldActor_Teardown). In state 0x6d its effect
 * is ended; the session's and the members' resources are released; and flags 0x1a
 * (func_02035638 0x3f), 0xa (the sound emitter that plays: 0x83c with flag 0x19, else 0x880)
 * and 0x1b (func_020b8db4) are undone. Returns 1.
 * QUIRK: the player number plus 8 goes to func_020771cc as its first argument. */
int FieldActor_Shutdown(struct FieldActor *actor)
{
    if (actor->state == 0x6d && actor->work.s6d.effect != -1) {
        func_0209129c(actor->work.s6d.effect);
    }
    func_020962b8(actor->player);
    NetSession *session = data_020ccf94;
    if (func_02073d90(session) && func_02073908(session, actor->player)) {
        func_020771cc(actor->player + 8, NULL, 0, 0);
    }
    func_020b9e2c(at(actor, 0x778));
    func_0205682c(at(actor, 0x710));
    func_0205682c(at(actor, 0x73c));
    func_02055454(at(actor, FIELD_ACTOR_MODEL_C));
    func_02055454(at(actor, FIELD_ACTOR_MODEL_A));
    func_02055454(at(actor, FIELD_ACTOR_MODEL_B));
    func_0205502c(at(actor, FIELD_ACTOR_BODY));
    func_02055454(at(actor, FIELD_ACTOR_BODY));
    func_0205ebb4(actor->held);
    func_0205defc(at(actor, FIELD_ACTOR_PART_C));
    FIELD_ACTOR_FIELD(actor, int, 0xc8c) = 2;
    func_0205e4b0(at(actor, FIELD_ACTOR_PART_B));
    func_0205d4e8(at(actor, 0x774));
    func_0205d084(at(actor, 0x389));
    func_020961e0(actor->player);
    if (FieldActor_TestFlag(actor, 0x1a)) {
        func_02035638(0x3f);
        FieldActor_ClearFlag(actor, 0x1a);
    }
    if (FieldActor_TestFlag(actor, 0xa)) {
        if (FieldActor_TestFlag(actor, 0x19)) {
            SoundEmitter_Vfunc10B((SoundEmitter *) at(actor, FIELD_ACTOR_EMITTER_B));
        } else {
            SoundEmitter_Vfunc10B((SoundEmitter *) at(actor, FIELD_ACTOR_EMITTER));
        }
        FieldActor_ClearFlag(actor, 0xa);
    }
    if (FieldActor_TestFlag(actor, 0x1b)) {
        FieldActor_ClearFlag(actor, 0x1b);
        func_020b8db4();
    }
    return 1;
}
CLEAN_AS(func_020051b4, FieldActor_Shutdown)

/* ---- The set-up once the actor is made (FieldActor_Setup): its player and looks from the
 * word it was made with, its models, and state 0 queued with the state it starts in. */

/* The player's looks by the player's index (func_020961d0): the member at 0x7a0, the parts at
 * 0x70f, 0x70e and 0x70d, the held item, the parts B and C, the looks at 0x389 and 0x774. */
extern const u8 data_020c75c4[];
extern const u8 data_020c75d4[];
extern const u8 data_020c75dc[];
extern const u8 data_020c75cc[];
extern const u8 data_020c75e0[];
extern const u8 data_020c75c8[];
extern const u8 data_020c75e4[];
extern const u8 data_020c75d8[];
extern const u8 data_020c75d0[];
/* Handed by address to func_020100d0 and func_020100b8. */
extern int data_020d83e8;
extern int data_020d83f0;
/* The scene: 0 outdoors (overlay 3), else indoors. */
extern u8 data_020e54a8;

extern int func_02096188(u32 made_with);
extern int func_02096180(u32 made_with);
extern void func_0203efb0(struct FieldActor *actor, u16 player);
extern void func_020962c8(int player, struct FieldActor *actor);
extern int func_020961d0(int player);
extern void func_0205f8cc(void *member, int value);
extern int func_020112d0(struct FieldActor *actor);
extern u8 func_02011150(struct FieldActor *actor, int flag);
extern void func_020106a8(struct FieldActor *actor, int a, int b);
extern void func_0205db4c(void *part, int value);
extern void func_0205d8c4(void *part, int value);
extern void func_0205dccc(void *part, int value);
extern int func_020110e8(struct FieldActor *actor);
extern int func_0205dc94(void *part, int value);
extern void func_020110c4(u16 *item, struct FieldActor *actor);
extern void *func_02011368(struct FieldActor *actor);
extern void func_0205ec50(void *held, int value, struct FieldActor *actor, u16 *item, void *record, int a);
extern void func_02060500(void *line, int player);
extern void func_0205df14(void *part, u8 value);
extern void func_02011138(u16 *item, struct FieldActor *actor);
extern int func_020103c0(struct FieldActor *actor, u16 *item);
extern void func_02010424(struct FieldActor *actor);
extern void func_0205e4e8(void *part, u8 value);
extern void func_020112f8(u16 *item, struct FieldActor *actor);
extern int func_020112e4(struct FieldActor *actor);
extern int func_020100e8(struct FieldActor *actor, u16 *item, int a, int b, int c);
extern void func_0205d0b8(void *look, u8 value);
extern int func_02011340(struct FieldActor *actor);
extern void func_0205d058(void *look, int value);
extern void func_0205d4f0(void *look, u8 value);
extern void func_0201131c(u16 *item, struct FieldActor *actor);
extern void func_02010680(struct FieldActor *actor, u16 *item);
extern int func_0205cfd4(void *look);
extern int func_0205d25c(void *look);
extern int func_0205f8b4(void *member);
extern int func_021077e8(int value);
extern void func_020100d0(struct FieldActor *actor, int a, int b, void *c, void *d);
extern void func_020100b8(struct FieldActor *actor, int a, int b, void *c, void *d);
extern void func_0205d034(void *look);

/* func_0200e42c: the set-up; returns 1. The player is bits 30 and 31 of the word at 8
 * (func_02096188); it is noted at 0xdc (func_0203efb0) and with the session's players
 * (func_020962c8). The looks and models are set up from the player's tables, with the
 * player record's items (FieldActor_SetupLooks, FieldActor_SetupPartB, FieldActor_SetupPartC),
 * and the held item (func_0205ec50). Gravity is -5.0 a step, the vertical speed at least -10.0;
 * state 0 is asked for with the start state (bits 22 to 29, func_02096180; priority 9) and the
 * requests are taken at once. The flags are 1 (and 0 outdoors); the start position is the
 * position; the target and the words at 0x804 and 0x810 are -1, those at 0x808, 0x814 and
 * 0x818 0, and 0x81c 0xf; the byte at 0x8e9 is 0x1f, the counter at 0x8e8 0, and no object is
 * met. */
int FieldActor_Init(struct FieldActor *actor)
{
    Actor *base = FieldActor_Base(actor);
    u32 made_with = FIELD_ACTOR_FIELD(actor, u32, 8);
    actor->player = func_02096188(made_with);
    func_0203efb0(actor, (u16) actor->player);
    func_020962c8(actor->player, actor);
    func_0205f8cc(at(actor, 0x7a0), data_020c75c4[func_020961d0(actor->player)]);
    int index = func_020112d0(actor);
    func_020106a8(actor, index, func_02011150(actor, 1));
    FieldActor_SetupLooks(actor);
    func_0205db4c(at(actor, 0x70f), data_020c75d4[func_020961d0(actor->player)]);
    func_0205d8c4(at(actor, 0x70e), data_020c75dc[func_020961d0(actor->player)]);
    func_0205dccc(at(actor, 0x70d), data_020c75cc[func_020961d0(actor->player)]);
    func_0205dc94(at(actor, 0x70d), func_020110e8(actor));
    FieldActor_SetupPartB(actor);
    FieldActor_SetupPartC(actor);
    index = func_020961d0(actor->player);
    u16 item;
    func_020110c4(&item, actor);
    func_0205ec50(actor->held, data_020c75e0[index], actor, &item, func_02011368(actor), 0);
    func_02060500(at(actor, 0x5c8), actor->player);
    base->gravity = -0x5000;
    base->min_y_velocity = -0xa000;
    FieldActor_RequestState0(actor, func_02096180(made_with), 9, -1);
    FIELD_ACTOR_PENDING_BITS(actor) &= (u8) ~PENDING_ACTION_SET;
    FieldActor_TakeRequests(actor);
    actor->flags = 0;
    FieldActor_SetFlag(actor, 1);
    if (data_020e54a8 == 0) {
        FieldActor_SetFlag(actor, 0);
    }
    actor->start_position = actor->position;
    actor->target = -1;
    actor->unk_810 = -1;
    FIELD_ACTOR_FIELD(actor, int, 0x804) = -1;
    FIELD_ACTOR_FIELD(actor, int, 0x808) = 0;
    actor->unk_814 = 0;
    actor->unk_818 = 0;
    actor->unk_81C = 0xf;
    FIELD_ACTOR_BODY_ARG(actor) = 0x1f;
    actor->unk_8E8 = 0;
    actor->other = NULL;
    actor->other_result = 0;
    return 1;
}
CLEAN_AS(func_0200e42c, FieldActor_Init)

/* func_0200e654: part C (0x59c) from the player's table data_020c75c8, then its item from the
 * player's record (func_02011138) goes to func_020103c0, and func_02010424. */
void FieldActor_SetupPartC(struct FieldActor *actor)
{
    u16 item;
    func_0205df14(at(actor, FIELD_ACTOR_PART_C), data_020c75c8[func_020961d0(actor->player)]);
    func_02011138(&item, actor);
    u16 copy = item;
    func_020103c0(actor, &copy);
    func_02010424(actor);
}
CLEAN_AS(func_0200e654, FieldActor_SetupPartC)

/* func_0200e6a4: part B (0x428) from the player's table data_020c75e4, then its item from the
 * player's record (func_020112f8, 0xfff1 without a record) goes to func_020100e8 with
 * func_020112e4's and func_020112d0's values. */
void FieldActor_SetupPartB(struct FieldActor *actor)
{
    u16 item;
    func_0205e4e8(at(actor, FIELD_ACTOR_PART_B), data_020c75e4[func_020961d0(actor->player)]);
    func_020112f8(&item, actor);
    u16 copy = item;
    int a = func_020112e4(actor);
    int b = func_020112d0(actor);
    func_020100e8(actor, &copy, a, b, 1);
}
CLEAN_AS(func_0200e6a4, FieldActor_SetupPartB)

/* func_0200e704: the looks at 0x389 (from data_020c75d8, then func_02011340's flag) and 0x774
 * (from data_020c75d0), the record's item at func_0201131c to func_02010680, and the pairs of
 * func_021077e8 of the looks handed to func_020100d0 and func_020100b8 (0x774 with 0x389, with
 * data_020d83e8) and to func_020100b8 (0x7a0 with 0x389, with data_020d83f0); then
 * func_0205d034 on 0x389. */
void FieldActor_SetupLooks(struct FieldActor *actor)
{
    u16 item;
    func_0205d0b8(at(actor, 0x389), data_020c75d8[func_020961d0(actor->player)]);
    func_0205d058(at(actor, 0x389), func_02011340(actor) != 0);
    func_0205d4f0(at(actor, 0x774), data_020c75d0[func_020961d0(actor->player)]);
    func_0201131c(&item, actor);
    func_02010680(actor, &item);

    int look_389 = func_021077e8(func_0205cfd4(at(actor, 0x389)));
    int look_774 = func_021077e8(func_0205d25c(at(actor, 0x774)));
    func_020100d0(actor, look_774, look_389, &data_020d83e8, &data_020d83e8);
    func_020100b8(actor, look_774, look_389, &data_020d83e8, &data_020d83e8);
    int look_7a0 = func_021077e8(func_0205f8b4(at(actor, 0x7a0)));
    look_389 = func_021077e8(func_0205cfd4(at(actor, 0x389)));
    func_020100b8(actor, look_7a0, look_389, &data_020d83f0, &data_020d83f0);
    func_0205d034(at(actor, 0x389));
}
CLEAN_AS(func_0200e704, FieldActor_SetupLooks)
