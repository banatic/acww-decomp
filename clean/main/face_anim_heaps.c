/* The frame heaps of the field actors' face animations (face_anim_heaps.h). */
#include "face_anim_heaps.h"

#include "clean.h"
#include "resource_pools.h"
#include "scene_heaps.h"
#include "scene_query.h"
#include "scene_tables.h"
#include "session.h"

/* The first heap of the other actors. */
#define FACE_ANIM_HEAPS_OTHERS 4
/* Each heap's size. */
#define FACE_ANIM_HEAPS_SIZE 80

static_assert(sizeof(FaceAnimHeaps) == 0x24, "FaceAnimHeaps");

extern FaceAnimHeaps data_021c9df4; /* the heaps */
extern Heap *data_021c9ad4;         /* the heap they are made in (SceneHeaps_Create021c9ad4) */
extern NetSession *data_020ccf94;   /* the session */

/* func_0205db38: the heap the byte `slot` names, as an address. */
unsigned long FaceAnimHeaps_SlotHeap(unsigned char *slot)
{
    return FaceAnimHeaps_Heap(&data_021c9df4, *slot);
}
CLEAN_AS(func_0205db38, FaceAnimHeaps_SlotHeap)

/* func_0205db4c: heap `index` emptied, then the byte `slot` set to name it (the callers give
 * each player its own, data_020c75d4). */
void FaceAnimHeaps_Assign(unsigned char *slot, unsigned char index)
{
    Heap_FreeAll((Heap *) (uintptr_t) FaceAnimHeaps_Heap(&data_021c9df4, index));
    *slot = index;
}
CLEAN_AS(func_0205db4c, FaceAnimHeaps_Assign)

/* func_0205db6c: a heap byte's destructor, which does nothing. */
void FaceAnimHeaps_DestructSlot(void *slot)
{
    (void) slot;
}
CLEAN_AS(func_0205db6c, FaceAnimHeaps_DestructSlot)

/* func_0205db70: a heap byte's constructor: it names none. */
void FaceAnimHeaps_ConstructSlot(unsigned char *slot)
{
    *slot = FACE_ANIM_HEAPS_COUNT;
}
CLEAN_AS(func_0205db70, FaceAnimHeaps_ConstructSlot)

/* func_0205db78: heap `index`, as an address. */
unsigned long FaceAnimHeaps_Heap(FaceAnimHeaps *heaps, int index)
{
    return (unsigned long) (uintptr_t) heaps->heap[index];
}
CLEAN_AS(func_0205db78, FaceAnimHeaps_Heap)

/* func_0205db80: every heap that was made emptied and forgotten; then the heap they were made
 * in, if there is one, emptied. */
void FaceAnimHeaps_Clear(FaceAnimHeaps *heaps)
{
    for (int i = 0; i < FACE_ANIM_HEAPS_COUNT; i++) {
        if (heaps->heap[i] != NULL) {
            Heap_FreeAll(heaps->heap[i]);
            heaps->heap[i] = NULL;
        }
    }
    Heap *parent = data_021c9ad4;
    if (parent != NULL) {
        Heap_FreeAll(parent);
    }
}
CLEAN_AS(func_0205db80, FaceAnimHeaps_Clear)

/* func_0205dbb8: the heaps the scene uses, made in the heap at data_021c9ad4. With `players`
 * the smaller of the session's players and the scene's second count, and `others` the scene's
 * first count and heaps less `players` (less 1 when `players` is 0): heaps from 0 for
 * `players` and from 4 for `others`, as the face animation slots (FaceAnimSlots_AllocBlocks).
 * REQUIRES: players <= 4 and others <= 5, as the scenes give; no heap's range is checked. */
void FaceAnimHeaps_Create(FaceAnimHeaps *heaps)
{
    Heap *parent = data_021c9ad4;
    u32 players = data_020ccf94->player_count;
    u32 second = SceneTables_SecondCount(SceneQuery_Current());
    if (second < players) {
        players = second;
    }
    for (u32 i = 0; i < players; i++) {
        heaps->heap[i] = FrameHeap_Create(FaceAnimHeaps_HeapSize(), parent);
    }

    u32 at_least_one = players != 0 ? players : 1;
    u32 first = SceneTables_FirstCount(SceneQuery_Current());
    u32 others = first + (u32) ResourcePools_SceneHeapCount() - at_least_one;
    for (u32 i = FACE_ANIM_HEAPS_OTHERS; i < others + FACE_ANIM_HEAPS_OTHERS; i++) {
        heaps->heap[i] = FrameHeap_Create(FaceAnimHeaps_HeapSize(), parent);
    }
}
CLEAN_AS(func_0205dbb8, FaceAnimHeaps_Create)

/* func_0205dc34: the heaps' destructor (registered by __sinit_020c58a8), which does nothing. */
void FaceAnimHeaps_Destruct(void *heaps)
{
    (void) heaps;
}
CLEAN_AS(func_0205dc34, FaceAnimHeaps_Destruct)

/* func_0205dc38: the heaps' constructor (__sinit_020c58a8), which does nothing: the object
 * starts zeroed, every heap not made. */
void FaceAnimHeaps_Construct(void *heaps)
{
    (void) heaps;
}
CLEAN_AS(func_0205dc38, FaceAnimHeaps_Construct)

/* func_0205dc3c */
int FaceAnimHeaps_HeapSize(void)
{
    return FACE_ANIM_HEAPS_SIZE;
}
CLEAN_AS(func_0205dc3c, FaceAnimHeaps_HeapSize)

/* func_0205dc40: when the scene ends, the heaps cleared and the heap they are made in
 * destroyed. */
void FaceAnimHeaps_EndScene(void)
{
    FaceAnimHeaps_Clear(&data_021c9df4);
    SceneHeaps_Destroy021c9ad4();
}
CLEAN_AS(func_0205dc40, FaceAnimHeaps_EndScene)

/* func_0205dc58: when the scene starts, the heap at data_021c9ad4 made from `parent`, the
 * heaps made in it, and it, if made, shrunk to them. */
void FaceAnimHeaps_StartScene(Heap *parent)
{
    SceneHeaps_Create021c9ad4(parent);
    FaceAnimHeaps_Create(&data_021c9df4);
    Heap *heap = data_021c9ad4;
    if (heap != NULL) {
        Heap_Adjust(heap);
    }
}
CLEAN_AS(func_0205dc58, FaceAnimHeaps_StartScene)
