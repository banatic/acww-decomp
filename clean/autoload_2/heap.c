/* The game's heaps (heap.h).
 *
 * Allocations take an alignment as NNS does: a positive one allocates from the front of the
 * heap, a negative one from the back. A size of -1 asks for all that can be allocated. */
#include "heap.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"

static_assert(offsetof(HeapVtable, adjust) == 0x4c, "vtable slot 19");
static_assert(sizeof(Heap) == 0x18, "the heap object before its NNS heap");

/* The heap the functions without one use. */
extern Heap *data_021fbe94;
/* The heap Heap_CreateAuxHeap makes at start-up; func_020edf70 allocates zeroed blocks from
 * its back. Its symbol carries a NitroSDK name that does not fit what it holds. */
extern Heap *sSubOBJExtPltt;
/* The current heap each thread had before Heap_PushFrameHeap, by thread id. */
extern Heap *data_021fbe9c[16];

typedef struct OSThread {
    u8 unk_00[0x6c];
    u32 id;
} OSThread;

typedef struct OSThreadInfo {
    u16 is_need_rescheduling;
    u16 irq_depth;
    OSThread *current;
} OSThreadInfo;

extern OSThreadInfo OSi_ThreadInfo;

/* The heap's own calls, through its vtable; each checks the CPU mode and locks the heap. */
extern void *func_020e9ed4(Heap *heap, int size, int align);
extern void func_020e9c48(Heap *heap, void *block);
extern int func_020e9cdc(Heap *heap, void *block, int size);
/* Lock and unlock (the vtable's slots 2 and 3); locking outside the CPU's system mode stops
 * the game unless the heap has HEAP_ANY_MODE. */
extern void func_020ea0a4(Heap *heap);
extern void func_020ea084(Heap *heap);
/* A new frame heap, and an expanded heap, of `size` bytes (-1: all there is) in a block of
 * `parent` (NULL: the current heap). The second's symbol carries a NitroSDK name that does not
 * fit what it does. */
extern Heap *func_020ea0e0(int size, Heap *parent);
extern Heap *GX_ResetBankForSubOBJExtPltt(int size, Heap *parent);

extern u32 OS_DisableInterrupts(void);
extern u32 OS_RestoreInterrupts(u32 state);
extern void OS_Terminate(void);
extern u32 NNS_FndAdjustFrmHeap(void *heap);
extern u32 NNS_FndGetGroupIDForExpHeap(void *heap);

#define ALIGN_FRONT 4
#define ALIGN_BACK -4

/* func_020e9898 */
void Heap_FreeCurrent(void *block)
{
    func_020e9c48(data_021fbe94, block);
}
CLEAN_AS(func_020e9898, Heap_FreeCurrent)

/* func_020e98b4 */
void *Heap_AllocCurrent(int size)
{
    return func_020e9ed4(data_021fbe94, size, ALIGN_FRONT);
}
CLEAN_AS(func_020e98b4, Heap_AllocCurrent)

/* func_020e98d4 */
void *Heap_AllocCurrentBack(int size)
{
    return func_020e9ed4(data_021fbe94, size, ALIGN_BACK);
}
CLEAN_AS(func_020e98d4, Heap_AllocCurrentBack)

/* func_020e98f4 */
void *Heap_AllocCurrentAligned(int size, int align)
{
    return func_020e9ed4(data_021fbe94, size, align);
}
CLEAN_AS(func_020e98f4, Heap_AllocCurrentAligned)

/* GXS_BeginLoadOBJExtPltt: the start-up (func_020b1b84) makes the expanded heap at
 * sSubOBJExtPltt, 0x13fc8 bytes from the current heap. */
void Heap_CreateAuxHeap(int size, Heap *parent)
{
    sSubOBJExtPltt = GX_ResetBankForSubOBJExtPltt(size, parent);
}
CLEAN_AS(GXS_BeginLoadOBJExtPltt, Heap_CreateAuxHeap)

/* func_020e993c */
void Heap_Free(Heap *heap, void *block)
{
    func_020e9c48(heap, block);
}
CLEAN_AS(func_020e993c, Heap_Free)

/* func_020e9948 */
void *Heap_Alloc(Heap *heap, int size)
{
    return func_020e9ed4(heap, size, ALIGN_FRONT);
}
CLEAN_AS(func_020e9948, Heap_Alloc)

/* func_020e9958 */
void *Heap_AllocBack(Heap *heap, int size)
{
    return func_020e9ed4(heap, size, ALIGN_BACK);
}
CLEAN_AS(func_020e9958, Heap_AllocBack)

/* func_020e9968 */
void *Heap_AllocAligned(Heap *heap, int size, int align)
{
    return func_020e9ed4(heap, size, align);
}
CLEAN_AS(func_020e9968, Heap_AllocAligned)

/* func_020e9974: the running thread's current heap back to the one Heap_PushFrameHeap saved.
 * The frame heap itself stays. */
void Heap_PopThreadHeap(void)
{
    u32 thread = OSi_ThreadInfo.current->id;
    Heap_SetCurrent(data_021fbe9c[thread]);
    data_021fbe9c[thread] = NULL;
}
CLEAN_AS(func_020e9974, Heap_PopThreadHeap)

/* func_020e99ac: the current heap saved for the running thread. */
void Heap_SaveThreadHeap(void)
{
    data_021fbe9c[OSi_ThreadInfo.current->id] = data_021fbe94;
}
CLEAN_AS(func_020e99ac, Heap_SaveThreadHeap)

/* func_020e99d8: a new frame heap of `size` bytes in `parent` (NULL: the current heap) made the
 * current heap, the previous one saved for the running thread (Heap_PopThreadHeap). NULL, with
 * nothing changed, when there is no room. */
Heap *Heap_PushFrameHeap(int size, Heap *parent)
{
    Heap *heap = func_020ea0e0(size, parent);
    if (heap == NULL) {
        return NULL;
    }
    Heap_SaveThreadHeap();
    Heap_SetCurrent(heap);
    return heap;
}
CLEAN_AS(func_020e99d8, Heap_PushFrameHeap)

/* func_020e9a08: `heap` made the current heap; the one before. */
Heap *Heap_SetCurrent(Heap *heap)
{
    u32 interrupts = OS_DisableInterrupts();
    Heap *before = data_021fbe94;
    data_021fbe94 = heap;
    OS_RestoreInterrupts(interrupts);
    return before;
}
CLEAN_AS(func_020e9a08, Heap_SetCurrent)

/* func_020e9a3c: the heap's flags set to `flags`, unless they have HEAP_FLAGS_READ_ONLY; the
 * flags before. */
int Heap_SetFlags(Heap *heap, int flags)
{
    u32 interrupts = OS_DisableInterrupts();
    int before = (int) heap->flags;
    if ((flags & HEAP_FLAGS_READ_ONLY) == 0) {
        heap->flags = (u32) flags;
    }
    OS_RestoreInterrupts(interrupts);
    return before;
}
CLEAN_AS(func_020e9a3c, Heap_SetFlags)

/* func_020e9a68 (vtable slot 19 of the frame heap): the frame heap shrunk to what is allocated
 * in it, and its block in the parent heap with it; the block's new size, or 0 when either
 * fails. */
int FrameHeap_Adjust(Heap *heap)
{
    u32 size = NNS_FndAdjustFrmHeap(heap->handle);
    if (size == 0) {
        return 0;
    }
    int block_size = (int) (size + sizeof(Heap));
    if (func_020e9cdc(heap->parent, heap, block_size) < 0) {
        return 0;
    }
    heap->size = size;
    return block_size;
}
CLEAN_AS(func_020e9a68, FrameHeap_Adjust)

/* func_020e9ab4 (vtable slot 19 of the expanded heap): an expanded heap does not shrink. */
int ExpHeap_Adjust(void)
{
    return 0;
}
CLEAN_AS(func_020e9ab4, ExpHeap_Adjust)

/* func_020e9abc: the heap shrunk to what is allocated in it (its vtable's adjust); the block's
 * new size, or 0 when it does not shrink, which stops the game for a heap with
 * HEAP_STOP_ON_FAILURE. */
int Heap_Adjust(Heap *heap)
{
    func_020ea0a4(heap);
    int size = heap->vtable->adjust(heap);
    if (size == 0 && (heap->flags & HEAP_STOP_ON_FAILURE) != 0) {
        OS_Terminate();
    }
    func_020ea084(heap);
    return size;
}
CLEAN_AS(func_020e9abc, Heap_Adjust)

/* func_020e9b0c (vtable slot 18 of the frame heap): frame heaps have no group ids. */
int FrameHeap_GroupId(void)
{
    return 0;
}
CLEAN_AS(func_020e9b0c, FrameHeap_GroupId)

/* func_020e9b14 (vtable slot 18 of the expanded heap): the group id new blocks get. */
int ExpHeap_GroupId(Heap *heap)
{
    return (int) NNS_FndGetGroupIDForExpHeap(heap->handle);
}
CLEAN_AS(func_020e9b14, ExpHeap_GroupId)
