/* The base class of the post sources (collision_post_source.h). */
#include "collision_post_source.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "itcm/field_units.h"

/* The current map (itcm/field_units.h); its word at 0x120 is its post source, or 0. */
extern FieldBlockMap *data_020da1a8;
/* The class vtable of the base class. */
extern const u8 data_020da1fc[];
/* The default source, its guard (bit 0 once built) and its record for the destructors run at
 * exit. */
extern CollisionPostSource data_021c30f8;
extern int data_021c30dc;
extern u8 data_021c3158[];

extern void __register_global_object(void *object, void *destruct, void *record);
/* The default source's destructor, as the game registers it (CollisionPostSource_Destruct). */
extern void func_02031ea8(void *source);

static void collision_post_source_set_vtable(CollisionPostSource *source)
{
    source->vtable = (const CollisionPostSourceVtable *) (const void *) data_020da1fc;
}

/* func_02031c50: the current map's post source, or the default one when the map has none
 * (built and registered for destruction the first time it is asked for). */
CollisionPostSource *CollisionPostSource_Current(void)
{
    if ((data_021c30dc & 1) == 0) {
        CollisionPostSource_ConstructDefault(&data_021c30f8);
        __register_global_object(&data_021c30f8, (void *) (uintptr_t) func_02031ea8, data_021c3158);
        data_021c30dc |= 1;
    }
    if (data_020da1a8->unk_120 != 0) {
        return (CollisionPostSource *) (uintptr_t) data_020da1a8->unk_120;
    }
    return &data_021c30f8;
}
CLEAN_AS(func_02031c50, CollisionPostSource_Current)

/* func_02031e80: the base class's post_at (slot 2): no unit holds a post. */
int CollisionPostSource_NoPost(void)
{
    return 0;
}
CLEAN_AS(func_02031e80, CollisionPostSource_NoPost)

/* func_02031e84: a destructor of the base class (the derived sources' destructors call it):
 * puts the base vtable back. */
void CollisionPostSource_DestructBase(CollisionPostSource *source)
{
    collision_post_source_set_vtable(source);
}
CLEAN_AS(func_02031e84, CollisionPostSource_DestructBase)

/* func_02031e90: the base class's deleting destructor (slot 1): puts the base vtable back and
 * frees the source. */
CollisionPostSource *CollisionPostSource_Delete(CollisionPostSource *source)
{
    collision_post_source_set_vtable(source);
    Heap_OperatorDeleteB(source);
    return source;
}
CLEAN_AS(func_02031e90, CollisionPostSource_Delete)

/* func_02031ea8: the base class's destructor (slot 0): puts the base vtable back. */
void CollisionPostSource_Destruct(CollisionPostSource *source)
{
    collision_post_source_set_vtable(source);
}
CLEAN_AS(func_02031ea8, CollisionPostSource_Destruct)

/* func_02031eb4: the base class's constructor, as the default source is built. */
void CollisionPostSource_ConstructDefault(CollisionPostSource *source)
{
    collision_post_source_set_vtable(source);
}
CLEAN_AS(func_02031eb4, CollisionPostSource_ConstructDefault)

/* func_02031ec0: the base class's constructor (the derived sources' constructors call it). */
void CollisionPostSource_Construct(CollisionPostSource *source)
{
    collision_post_source_set_vtable(source);
}
CLEAN_AS(func_02031ec0, CollisionPostSource_Construct)
