/* The walkers' base class (message_walker.h). */
#include "message_walker.h"

#include "autoload_2/heap.h"
#include "clean.h"

extern const u8 data_020e3e68[]; /* the walkers' base class's vtable */

/* The walkers' base destructor. */
extern void *func_020a941c(void *walker);

/* func_020a794c (slot 0): the destructor: its vtable, then the base destructor. */
MessageWalker *MessageWalker_Destruct(MessageWalker *walker)
{
    walker->vtable = data_020e3e68;
    func_020a941c(walker);
    return walker;
}
CLEAN_AS(func_020a794c, MessageWalker_Destruct)

/* func_020a7964 (slot 1): the walker destroyed (as MessageWalker_Destruct) and freed. */
MessageWalker *MessageWalker_Delete(MessageWalker *walker)
{
    walker->vtable = data_020e3e68;
    func_020a941c(walker);
    Heap_OperatorDeleteB(walker);
    return walker;
}
CLEAN_AS(func_020a7964, MessageWalker_Delete)
