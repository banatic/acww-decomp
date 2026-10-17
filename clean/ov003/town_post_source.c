/* Overlay 3's post source (town_post_source.h). */
#include "town_post_source.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "clean.h"
#include "main/collision_post_source.h"

/* The source's vtable. */
extern const CollisionPostSourceVtable data_ov003_0223a248;

/* func_ov003_022208cc (vtable slot 1): the source's vtable, the base class's destructor, and
 * the source is freed (operator delete); returns `source`. */
CollisionPostSource *TownPostSource_Delete(CollisionPostSource *source)
{
    source->vtable = &data_ov003_0223a248;
    CollisionPostSource_DestructBase(source);
    Heap_OperatorDeleteB(source);
    return source;
}
CLEAN_AS(func_ov003_022208cc, TownPostSource_Delete)
