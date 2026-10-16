/* The sound objects of overlay 4's field (sound_object.h). */
#include "sound_object.h"

#include <assert.h>
#include <stddef.h>

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(offsetof(SoundObject, param) == 0x0c, "SoundObject layout");
static_assert(offsetof(SoundObjectVtable, silence) == 0x10, "SoundObjectVtable layout");

/* Positions handed to the sound objects are taken relative to this point, and only while the
 * camera (data_021c67a4) exists. */
extern void *data_021c67a4;
extern Vec3 data_021c67b8;

/* The size of each kind, in the order of SoundObject_New's kinds (0 to 10, then 255). */
extern const u32 data_020c7590[SOUND_OBJECT_KINDS];

/* The base class, then each kind's class. */
extern const SoundObjectVtable data_0213f190;
extern const SoundObjectVtable data_0213f0b0, data_0213f0d0, data_0213f0f0, data_0213f110, data_0213f130, data_0213f150,
    data_0213f170, data_0213f1b0, data_0213f1d0, data_0213f1f0, data_0213f210, data_0213f230;

/* func_02003e00: slot 4, both handles to silence. QUIRK: the base class's slot returns nothing;
 * the result is whatever it leaves behind, and the only caller ignores it. */
int SoundObject_Silence(SoundObject *obj)
{
    return obj->vtable->silence(obj);
}
CLEAN_AS(func_02003e00, SoundObject_Silence)

/* func_02003e10: slot 3, both handles to full volume. */
void SoundObject_Raise(SoundObject *obj, int param)
{
    obj->vtable->raise(obj, param);
}
CLEAN_AS(func_02003e10, SoundObject_Raise)

/* func_02003e20: slot 2 with the position relative to data_021c67b8, or with none. With a
 * position but no camera, nothing is updated. */
void SoundObject_UpdateAt(SoundObject *obj, int param, const Vec3 *pos)
{
    if (pos == NULL) {
        obj->vtable->update(obj, param, NULL);
        return;
    }
    if (data_021c67a4 == NULL) {
        return;
    }
    Vec3 rel = {pos->x - data_021c67b8.x, pos->y - data_021c67b8.y, pos->z - data_021c67b8.z};
    obj->vtable->update(obj, param, &rel);
}
CLEAN_AS(func_02003e20, SoundObject_UpdateAt)

/* func_02003e80: slot 1, stop and release both handles. */
void *SoundObject_Release(SoundObject *obj)
{
    return obj->vtable->release(obj);
}
CLEAN_AS(func_02003e80, SoundObject_Release)

/* func_02003e90: slot 0, start. */
void SoundObject_Start(SoundObject *obj)
{
    obj->vtable->start(obj);
}
CLEAN_AS(func_02003e90, SoundObject_Start)

/* func_02003ea0: the size of the largest kind, rounded up to a multiple of 4; overlay 4 makes
 * the objects' heap that size plus 0x60. */
u32 SoundObject_MaxSize(void)
{
    u32 max = 0;
    for (int i = 0; i < SOUND_OBJECT_KINDS; i++) {
        if (data_020c7590[i] > max) {
            max = data_020c7590[i];
        }
    }
    return (max + 3) & ~3u;
}
CLEAN_AS(func_02003ea0, SoundObject_MaxSize)

/* func_02003ec8: a new object of `kind` (0 to 10 or 255; any other kind makes kind 0) on
 * `heap`, or NULL when the heap is full. The constructors only set the vtable: the base
 * class's, then the kind's. */
SoundObject *SoundObject_New(void *heap, int kind)
{
    int size = 0x10;
    const SoundObjectVtable *vtable;

    switch (kind) {
        case 1:
            vtable = &data_0213f0d0;
            break;
        case 2:
            vtable = &data_0213f0f0;
            break;
        case 3:
            vtable = &data_0213f110;
            break;
        case 4:
            size = 0x14;
            vtable = &data_0213f230;
            break;
        case 5:
            vtable = &data_0213f130;
            break;
        case 6:
            vtable = &data_0213f1b0;
            break;
        case 7:
            size = 0x18;
            vtable = &data_0213f1d0;
            break;
        case 8:
            size = 0x14;
            vtable = &data_0213f1f0;
            break;
        case 9:
            vtable = &data_0213f150;
            break;
        case 10:
            size = 0x14;
            vtable = &data_0213f210;
            break;
        case SOUND_OBJECT_KIND_LAST:
            vtable = &data_0213f170;
            break;
        case 0:
        default:
            vtable = &data_0213f0b0;
            break;
    }

    SoundObject *obj = Heap_Alloc(heap, size);
    if (obj != NULL) {
        obj->vtable = &data_0213f190;
        obj->vtable = vtable;
    }
    return obj;
}
CLEAN_AS(func_02003ec8, SoundObject_New)
