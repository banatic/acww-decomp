/* The scene object class with vtable 0x020d8c64 (obj_020d8c64.h). */
#include "obj_020d8c64.h"

#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "clean.h"

/* The class's vtable and that of the sound emitter at 0x514, whose destructor is inlined. */
extern const u8 data_020d8c64[];
extern const u8 data_020d8414[];

/* The destructors of the members and the base, in the order they run. */
extern void func_02014898(void *member);
extern void func_02019eac(void *member);
extern void func_02013c28(void *member);
extern void *func_02089c70(void *member);
extern void *func_02032c50(void *member);
extern void func_0201a790(void *member);
extern void func_0201a7e8(void *member);
extern void func_0201ade4(void *member);
extern void func_0201b320(void *member);
extern int func_02016998(void *member);
extern void *func_0201a3f8(void *member);
extern void func_0201b390(void *member);
extern void *func_02054630(void *member);
extern void *func_0203f080(void *object);

#define SOUND_EMITTER 0x514

static u8 *at(void *object, u32 offset)
{
    return (u8 *) object + offset;
}

/* func_020120e0: the destructor: as Obj020d8c64_DestructDelete without freeing the memory.
 * Returns the object. */
void *Obj020d8c64_Destruct(void *object)
{
    *(const u8 **) object = data_020d8c64;
    func_02014898(at(object, 0x618));
    func_02019eac(at(object, 0x564));
    func_02013c28(at(object, 0x558));
    *(const u8 **) at(object, SOUND_EMITTER) = data_020d8414;
    SoundEmitterClass_DestructBase((SoundEmitterObject *) at(object, SOUND_EMITTER));
    func_02089c70(at(object, 0x4cc));
    func_02032c50(at(object, 0x49c));
    func_0201a790(at(object, 0x420));
    func_0201a7e8(at(object, 0x418));
    func_0201ade4(at(object, 0x3b0));
    func_0201b320(at(object, 0x350));
    func_02016998(at(object, 0x334));
    func_0201a3f8(at(object, 0x2ac));
    func_0201b390(at(object, 0x2a0));
    func_02054630(at(object, 0x0ec));
    func_0203f080(object);
    return object;
}
CLEAN_AS(func_020120e0, Obj020d8c64_Destruct)

/* func_02012014: the deleting destructor (vtable slot 0x44): the class's vtable, the members in
 * the reverse order of their places (the emitter at 0x514 gets its own vtable first), the
 * base, then the memory freed to the auxiliary heap. Returns the object. */
void *Obj020d8c64_DestructDelete(void *object)
{
    *(const u8 **) object = data_020d8c64;
    func_02014898(at(object, 0x618));
    func_02019eac(at(object, 0x564));
    func_02013c28(at(object, 0x558));
    *(const u8 **) at(object, SOUND_EMITTER) = data_020d8414;
    SoundEmitterClass_DestructBase((SoundEmitterObject *) at(object, SOUND_EMITTER));
    func_02089c70(at(object, 0x4cc));
    func_02032c50(at(object, 0x49c));
    func_0201a790(at(object, 0x420));
    func_0201a7e8(at(object, 0x418));
    func_0201ade4(at(object, 0x3b0));
    func_0201b320(at(object, 0x350));
    func_02016998(at(object, 0x334));
    func_0201a3f8(at(object, 0x2ac));
    func_0201b390(at(object, 0x2a0));
    func_02054630(at(object, 0x0ec));
    func_0203f080(object);
    Heap_FreeAux(object);
    return object;
}
CLEAN_AS(func_02012014, Obj020d8c64_DestructDelete)
