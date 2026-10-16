/* The main program's part of the field actor's class (field_actor.h). */
#include "field_actor.h"

#include <stddef.h>
#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"

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

/* func_02004c24: the deleting destructor (vtable slot 0x44): the members are destroyed in the
 * reverse order of their places, then the message receiver and the base, and the memory is
 * freed. Returns the actor. */
struct FieldActor *FieldActor_DestructDelete(struct FieldActor *actor)
{
    set_vtable(actor, 0x000, data_020d82b4);
    set_vtable(actor, 0x0ec, data_020d832c);
    __cxa_vec_cleanup(at(actor, REQUEST_QUEUE), REQUEST_COUNT, REQUEST_SIZE, (void (*)(void *)) func_0200e91c);
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
    FieldActor_Delete(actor);
    return actor;
}
CLEAN_AS(func_02004c24, FieldActor_DestructDelete)
