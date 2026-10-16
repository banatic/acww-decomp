/* The process class with vtable 0x020e2fe8 (obj_020e2fe8.h). */
#include "obj_020e2fe8.h"

#include "autoload_2/heap.h"
#include "clean.h"

extern const u8 data_020da13c[]; /* the base class's vtable */
extern const u8 data_020e2fe8[]; /* this class's */

/* func_02096c50: the constructor. The vtable is the base class's while its constructor runs,
 * then this class's. Returns the object. */
Process *Obj020e2fe8_Construct(Process *self)
{
    Process_Construct(self);
    self->vtable = (const u32 *) data_020da13c;
    self->vtable = (const u32 *) data_020e2fe8;
    return self;
}
CLEAN_AS(func_02096c50, Obj020e2fe8_Construct)

/* func_02096c70: a new object, constructed (the profile's create function). QUIRK: it is
 * declared without a result, but the ROM's code leaves the object, or 0 when there was no
 * memory for it, in the result register, which is what its caller reads. */
void Obj020e2fe8_New(void)
{
    Process *self = Heap_AllocAuxZeroed(sizeof(Process));
    if (self != NULL) {
        Obj020e2fe8_Construct(self);
    }
}
CLEAN_AS(func_02096c70, Obj020e2fe8_New)
