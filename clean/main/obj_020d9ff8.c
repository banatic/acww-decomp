/* The scene class with vtable 0x020d9ff8 (obj_020d9ff8.h). */
#include "obj_020d9ff8.h"

#include "autoload_2/heap.h"
#include "clean.h"

/* The class's vtable. */
extern const u8 data_020d9ff8[];

/* func_0202eb20: the destructor the derived classes' destructors run: the class's vtable,
 * then the scene base's destructor (SceneBase_DestructBody). Returns the scene. */
void *Obj020d9ff8_DestructBody(void *scene)
{
    *(const u8 **) scene = data_020d9ff8;
    SceneBase_DestructBody(scene);
    return scene;
}
CLEAN_AS(func_0202eb20, Obj020d9ff8_DestructBody)

/* func_0202eb38 (slot 0x04): destructed, then freed (Heap_OperatorDeleteB). */
void *Obj020d9ff8_DestructDelete(void *scene)
{
    *(const u8 **) scene = data_020d9ff8;
    SceneBase_DestructBody(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_0202eb38, Obj020d9ff8_DestructDelete)

/* func_0202eb58 (slot 0x00): the destructor. */
void *Obj020d9ff8_Destruct(void *scene)
{
    *(const u8 **) scene = data_020d9ff8;
    SceneBase_DestructBody(scene);
    return scene;
}
CLEAN_AS(func_0202eb58, Obj020d9ff8_Destruct)

/* func_0202eb70: the constructor: a scene base (SceneBase_Construct) given the class's vtable.
 * Returns the scene. */
void *Obj020d9ff8_Construct(void *scene)
{
    SceneBase_Construct((SceneBase *) scene);
    *(const u8 **) scene = data_020d9ff8;
    return scene;
}
CLEAN_AS(func_0202eb70, Obj020d9ff8_Construct)
