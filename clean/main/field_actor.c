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

extern int func_0200e42c(struct FieldActor *actor);
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
 * them; func_0200e92c makes an entry of the request queue. */
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
extern int func_0200f290(FieldActor *actor, int bit);
extern void func_0200f268(FieldActor *actor, int bit);
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

/* func_02004c1c: vtable slot 0x00, the set-up once the actor is made (func_0200e42c). QUIRK:
 * as FieldActor_Teardown, the original gives back the callee's result and this none. */
void FieldActor_Setup(struct FieldActor *actor)
{
    func_0200e42c(actor);
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
    if (func_0200f290(actor, 0x1a)) {
        func_02035638(0x3f);
        func_0200f268(actor, 0x1a);
    }
    if (func_0200f290(actor, 0xa)) {
        if (func_0200f290(actor, 0x19)) {
            SoundEmitter_Vfunc10B((SoundEmitter *) at(actor, FIELD_ACTOR_EMITTER_B));
        } else {
            SoundEmitter_Vfunc10B((SoundEmitter *) at(actor, FIELD_ACTOR_EMITTER));
        }
        func_0200f268(actor, 0xa);
    }
    if (func_0200f290(actor, 0x1b)) {
        func_0200f268(actor, 0x1b);
        func_020b8db4();
    }
    return 1;
}
CLEAN_AS(func_020051b4, FieldActor_Shutdown)
