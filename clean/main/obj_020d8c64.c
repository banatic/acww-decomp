/* The scene object class with vtable 0x020d8c64 (obj_020d8c64.h). */
#include "obj_020d8c64.h"

#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "clean.h"
#include "scene_action.h"

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

/* ---- The motion number kept at 0x63e */

#define OBJ_020D8C64_MOTION 0x564
#define OBJ_020D8C64_ACTION 0x618
#define OBJ_020D8C64_MOTION_NUMBER 0x63e
#define OBJ_020D8C64_NO_NUMBER (-1)
/* The kind of motion of a talk, and the numbers its byte 0xa9 may give. */
#define OBJ_020D8C64_MOTION_TALK 8
#define OBJ_020D8C64_NUMBER_LAST 59

extern int func_02019e00(void *motion);
extern u8 func_02019df8(void *motion);
extern u32 func_0201c274(void *object);
extern void *func_020160d4(void *scene);
/* The slot (0 to 3) of `number` among the four bytes at 0x23e8 of the player's record, or -1. */
extern int func_0203f9e0(int number);

/* func_02013a0c (vtable slot 0xa0 of the class): no number (-1). */
int Obj020d8c64_NoMotionNumber(void *object)
{
    (void) object;
    return OBJ_020D8C64_NO_NUMBER;
}
CLEAN_AS(func_02013a0c, Obj020d8c64_NoMotionNumber)

/* func_02013a14: while an action runs or is requested (SceneAction_IsBusy), the motion is the
 * talk's (kind 8), and the object is in a scene (func_0201c274) without another speaker
 * (func_020160d4): the number its motion shows (byte 0xa9, func_02019df8) when it is 1 to 59,
 * not the one kept, and none of the four bytes of the player's record (func_0203f9e0); it is
 * then kept. Else -1. */
int Obj020d8c64_TakeNewMotionNumber(void *object)
{
    void *motion = at(object, OBJ_020D8C64_MOTION);
    if (SceneAction_IsBusy((const SceneAction *) at(object, OBJ_020D8C64_ACTION)) == 0 ||
        func_02019e00(motion) != OBJ_020D8C64_MOTION_TALK) {
        return OBJ_020D8C64_NO_NUMBER;
    }
    u32 scene = func_0201c274(object);
    if (scene == 0 || func_020160d4((void *) (uintptr_t) scene) != NULL) {
        return OBJ_020D8C64_NO_NUMBER;
    }
    int number = func_02019df8(motion);
    if (number > 0 && number <= OBJ_020D8C64_NUMBER_LAST && number != Obj020d8c64_LastMotionNumber((s16 *) object) &&
        func_0203f9e0((u8) number) == -1) {
        Obj020d8c64_SetLastMotionNumber(object, (u8) number);
        return number;
    }
    return OBJ_020D8C64_NO_NUMBER;
}
CLEAN_AS(func_02013a14, Obj020d8c64_TakeNewMotionNumber)

/* func_02013a94 */
s16 Obj020d8c64_LastMotionNumber(s16 *object)
{
    return *(const s16 *) at(object, OBJ_020D8C64_MOTION_NUMBER);
}
CLEAN_AS(func_02013a94, Obj020d8c64_LastMotionNumber)

/* func_02013aa0 */
void Obj020d8c64_SetLastMotionNumber(void *object, u16 number)
{
    *(u16 *) at(object, OBJ_020D8C64_MOTION_NUMBER) = number;
}
CLEAN_AS(func_02013aa0, Obj020d8c64_SetLastMotionNumber)

/* func_02013aac: none kept (0xffff). */
void Obj020d8c64_ClearLastMotionNumber(void *object)
{
    *(u16 *) at(object, OBJ_020D8C64_MOTION_NUMBER) = 0xffff;
}
CLEAN_AS(func_02013aac, Obj020d8c64_ClearLastMotionNumber)
