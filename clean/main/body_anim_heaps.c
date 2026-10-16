/* The frame heaps of the players' body animations (body_anim_heaps.h). */
#include "body_anim_heaps.h"

#include "clean.h"
#include "scene_heaps.h"
#include "session.h"

/* Each heap's size. */
#define BODY_ANIM_HEAPS_SIZE 1896

static_assert(sizeof(BodyAnimHeaps) == 0x10, "BodyAnimHeaps");

extern BodyAnimHeaps data_021cacd0; /* the heaps */
extern Heap *data_021c9ad0;         /* the heap they are made in (SceneHeaps_Create021c9ad0) */
extern NetSession *data_020ccf94;   /* the session */

/* func_0205f73c: the heap the byte `slot` names, as an address. */
unsigned long BodyAnimHeaps_SlotHeap(unsigned char *slot)
{
    return BodyAnimHeaps_Heap(&data_021cacd0, *slot);
}
CLEAN_AS(func_0205f73c, BodyAnimHeaps_SlotHeap)

/* func_0205f750: heap `index` emptied, then the byte `slot` set to name it (the callers give
 * each player its own, data_020c75c0). */
void BodyAnimHeaps_Assign(char *slot, char index)
{
    Heap_FreeAll((Heap *) (uintptr_t) BodyAnimHeaps_Heap(&data_021cacd0, (unsigned char) index));
    *slot = index;
}
CLEAN_AS(func_0205f750, BodyAnimHeaps_Assign)

/* func_0205f770: a heap byte's destructor, which does nothing. */
void BodyAnimHeaps_DestructSlot(void *slot)
{
    (void) slot;
}
CLEAN_AS(func_0205f770, BodyAnimHeaps_DestructSlot)

/* func_0205f774: a heap byte's constructor: it names none. */
void BodyAnimHeaps_ConstructSlot(unsigned char *slot)
{
    *slot = BODY_ANIM_HEAPS_COUNT;
}
CLEAN_AS(func_0205f774, BodyAnimHeaps_ConstructSlot)

/* func_0205f77c: heap `index`, as an address. */
unsigned long BodyAnimHeaps_Heap(BodyAnimHeaps *heaps, int index)
{
    return (unsigned long) (uintptr_t) heaps->heap[index];
}
CLEAN_AS(func_0205f77c, BodyAnimHeaps_Heap)

/* func_0205f784: every heap that was made emptied and forgotten; then the heap they were made
 * in, if there is one, emptied. */
void BodyAnimHeaps_Clear(BodyAnimHeaps *heaps)
{
    for (int i = 0; i < BODY_ANIM_HEAPS_COUNT; i++) {
        if (heaps->heap[i] != NULL) {
            Heap_FreeAll(heaps->heap[i]);
            heaps->heap[i] = NULL;
        }
    }
    Heap *parent = data_021c9ad0;
    if (parent != NULL) {
        Heap_FreeAll(parent);
    }
}
CLEAN_AS(func_0205f784, BodyAnimHeaps_Clear)

/* func_0205f7bc: a heap for each of the session's players, made in the heap at data_021c9ad0.
 * REQUIRES: the session has at most BODY_ANIM_HEAPS_COUNT players (its count is 0-4). */
void BodyAnimHeaps_Create(BodyAnimHeaps *heaps)
{
    Heap *parent = data_021c9ad0;
    unsigned int count = data_020ccf94->player_count;
    for (unsigned int i = 0; i < count; i++) {
        heaps->heap[i] = FrameHeap_Create(BodyAnimHeaps_HeapSize(), parent);
    }
}
CLEAN_AS(func_0205f7bc, BodyAnimHeaps_Create)

/* func_0205f7f8: the heaps' destructor (registered by __sinit_020c5970), which does nothing. */
void BodyAnimHeaps_Destruct(void *heaps)
{
    (void) heaps;
}
CLEAN_AS(func_0205f7f8, BodyAnimHeaps_Destruct)

/* func_0205f7fc: the heaps' constructor (__sinit_020c5970), which does nothing: the object
 * starts zeroed, every heap not made. */
void BodyAnimHeaps_Construct(void *heaps)
{
    (void) heaps;
}
CLEAN_AS(func_0205f7fc, BodyAnimHeaps_Construct)

/* func_0205f800 */
int BodyAnimHeaps_HeapSize(void)
{
    return BODY_ANIM_HEAPS_SIZE;
}
CLEAN_AS(func_0205f800, BodyAnimHeaps_HeapSize)

/* func_0205f808: when the scene ends, the heaps cleared and the heap they are made in
 * destroyed. */
void BodyAnimHeaps_EndScene(void)
{
    BodyAnimHeaps_Clear(&data_021cacd0);
    SceneHeaps_Destroy021c9ad0();
}
CLEAN_AS(func_0205f808, BodyAnimHeaps_EndScene)

/* func_0205f820: when the scene starts, the heap at data_021c9ad0 made from `parent`, the
 * heaps made in it, and it, if made, shrunk to them. */
void BodyAnimHeaps_StartScene(Heap *parent)
{
    SceneHeaps_Create021c9ad0(parent);
    BodyAnimHeaps_Create(&data_021cacd0);
    Heap *heap = data_021c9ad0;
    if (heap != NULL) {
        Heap_Adjust(heap);
    }
}
CLEAN_AS(func_0205f820, BodyAnimHeaps_StartScene)
