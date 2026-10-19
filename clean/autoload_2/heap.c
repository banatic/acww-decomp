/* The game's heaps (heap.h).
 *
 * Allocations take an alignment as NNS does: a positive one allocates from the front of the
 * heap, a negative one from the back. A size of -1 asks for all that can be allocated. */
#include "heap.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"
#include "main/game_halt.h"

static_assert(offsetof(HeapVtable, adjust) == 0x4c, "vtable slot 19");
static_assert(sizeof(Heap) == 0x18, "the heap object before its NNS heap");
static_assert(sizeof(ExpHeap) == 0x30, "the expanded heap object before its NNS heap");
static_assert(offsetof(HeapVtable, alloc) == 0x18, "vtable slot 6");
static_assert(offsetof(HeapVtable, resize) == 0x2c, "vtable slot 11");

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

/* The heaps' vtables: the expanded heap's, the frame heap's and the base class's. */
extern const HeapVtable data_0213e5b0;
extern const HeapVtable data_0213e608;
extern const HeapVtable data_0213e660;
/* The NNS options every heap is created with: 3, zero new blocks and fill freed ones (the
 * fill only exists in NNS's debug builds). */
extern u16 data_0213e5a4;
/* The hooks the game can install, called for a heap with HEAP_CALL_ALLOC_HOOK or
 * HEAP_CALL_FREE_HOOK: an allocation with its result and request, and a free (NULL: all). */
extern void (*data_021fbe84)(Heap *heap, void *block, int size, int align);
extern void (*data_021fbe7c)(Heap *heap, void *block);
/* The heap made at start-up from the arena (Heap_InitRoot), the size it is given there (0: all
 * of the arena), the arena it comes from, and whether the start-up has made it. */
extern Heap *data_021fbe8c;
extern u32 data_021fbe90;
extern u32 data_021fbe98;
extern u8 data_021fbe78;

extern u32 OS_DisableInterrupts(void);
extern u32 OS_RestoreInterrupts(u32 state);
extern u32 NNS_FndAdjustFrmHeap(void *heap);
extern u32 NNS_FndGetGroupIDForExpHeap(void *heap);
extern u16 NNS_FndSetGroupIDForExpHeap(void *heap, u16 group_id);
extern u32 NNS_FndGetSizeForMBlockExpHeap(const void *block);
extern void NNS_FndFreeToFrmHeap(void *heap, int mode);
extern void NNS_FndVisitAllocatedForExpHeap(void *heap, void (*visitor)(void *block, void *heap, u32 param), u32 param);
extern void NNS_FndFreeToExpHeap(void *heap, void *block);
extern u32 NNS_FndGetAllocatableSizeForFrmHeapEx(void *heap, int align);
extern u32 NNS_FndGetAllocatableSizeForExpHeapEx(void *heap, int align);
extern u32 NNS_FndGetTotalFreeSizeForExpHeap(void *heap);
extern void *NNS_FndAllocFromFrmHeapEx(void *heap, u32 size, int align);
extern void *NNS_FndAllocFromExpHeapEx(void *heap, u32 size, int align);
extern void NNS_FndDestroyFrmHeap(void *heap);
extern void *NNS_FndCreateFrmHeapEx(void *start, u32 size, u16 options);
extern void *NNS_FndCreateExpHeapEx(void *start, u32 size, u16 options);
/* NNS_FndResizeForMBlockFrmHeap, NNS_FndResizeForMBlockExpHeap and NNS_FndDestroyExpHeap by
 * where they sit among NNS's heap functions; the block's new size, 0 when it cannot change. */
extern u32 func_021023c8(void *heap, void *block, u32 size);
extern u32 func_02101c54(void *heap, void *block, u32 size);
extern void func_02101e20(void *heap);
/* The address the expanded heap's free_all hands NNS (ExpHeap_FreeVisitedBlock). */
extern void func_020e9b84(void *block, void *heap, u32 param);
/* The thread-switch callback that was installed before Heap_InstallThreadHook's; it is
 * still called after each switch. */
extern void (*data_021fbe88)(OSThread *from, OSThread *to);
/* NitroSDK's thread parameter: a word each thread keeps for its owner. The heaps keep in it
 * the current heap of every thread that is not running. */
extern void OS_SetThreadParameter(OSThread *thread, void *parameter);
extern void *OS_GetThreadParameter(const OSThread *thread);
extern void (*OS_SetSwitchThreadCallback(void (*callback)(OSThread *from, OSThread *to)))(OSThread *from, OSThread *to);
/* Heap_SwitchThreads by the game's own symbol: the callback NitroSDK keeps is the game's
 * address, not the Clean function's. */
extern void func_020ea5c4(OSThread *from, OSThread *to);
extern BOOL OS_TryLockMutex(OSMutex *mutex);
extern void OS_UnlockMutex(OSMutex *mutex);
extern void OS_LockMutex(OSMutex *mutex);
extern void OS_InitMutex(OSMutex *mutex);
extern u32 OS_GetProcMode(void);
extern void *OS_GetArenaLo(u32 id);
extern void *OS_GetArenaHi(u32 id);
extern void *OS_AllocFromArenaLo(u32 id, u32 size, u32 align);

#define CPU_MODE_SYSTEM 0x1f
#define NNS_FRMHEAP_FREE_ALL 3 /* NNS_FND_FRMHEAP_FREE_HEAD | NNS_FND_FRMHEAP_FREE_TAIL */
/* The smallest heaps the size -1 makes: the object, NNS's header and 4 bytes. */
#define FRAME_HEAP_HEADER 0x30 /* NNS's frame heap header */
#define EXP_HEAP_HEADER 0x4c   /* NNS's expanded heap header */

#define ALIGN_FRONT 4
#define ALIGN_BACK -4

/* func_020e9898 */
void Heap_FreeCurrent(void *block)
{
    Heap_FreeBlock(data_021fbe94, block);
}
CLEAN_AS(func_020e9898, Heap_FreeCurrent)

/* func_020e98b4 */
void *Heap_AllocCurrent(int size)
{
    return Heap_AllocBlock(data_021fbe94, size, ALIGN_FRONT);
}
CLEAN_AS(func_020e98b4, Heap_AllocCurrent)

/* func_020e98d4 */
void *Heap_AllocCurrentBack(int size)
{
    return Heap_AllocBlock(data_021fbe94, size, ALIGN_BACK);
}
CLEAN_AS(func_020e98d4, Heap_AllocCurrentBack)

/* func_020e98f4 */
void *Heap_AllocCurrentAligned(int size, int align)
{
    return Heap_AllocBlock(data_021fbe94, size, align);
}
CLEAN_AS(func_020e98f4, Heap_AllocCurrentAligned)

/* GXS_BeginLoadOBJExtPltt: the start-up (func_020b1b84) makes the expanded heap at
 * sSubOBJExtPltt, 0x13fc8 bytes from the current heap. */
void Heap_CreateAuxHeap(int size, Heap *parent)
{
    sSubOBJExtPltt = ExpHeap_Create(size, parent);
}
CLEAN_AS(GXS_BeginLoadOBJExtPltt, Heap_CreateAuxHeap)

/* func_020e993c */
void Heap_Free(Heap *heap, void *block)
{
    Heap_FreeBlock(heap, block);
}
CLEAN_AS(func_020e993c, Heap_Free)

/* func_020e9948 */
void *Heap_Alloc(Heap *heap, int size)
{
    return Heap_AllocBlock(heap, size, ALIGN_FRONT);
}
CLEAN_AS(func_020e9948, Heap_Alloc)

/* func_020e9958 */
void *Heap_AllocBack(Heap *heap, int size)
{
    return Heap_AllocBlock(heap, size, ALIGN_BACK);
}
CLEAN_AS(func_020e9958, Heap_AllocBack)

/* func_020e9968 */
void *Heap_AllocAligned(Heap *heap, int size, int align)
{
    return Heap_AllocBlock(heap, size, align);
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
    Heap *heap = FrameHeap_Create(size, parent);
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
    if (Heap_Resize(heap->parent, heap, block_size) < 0) {
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
    Heap_Lock(heap);
    int size = heap->vtable->adjust(heap);
    if (size == 0 && (heap->flags & HEAP_STOP_ON_FAILURE) != 0) {
        GameHalt_Terminate();
    }
    Heap_Unlock(heap);
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

/* func_020e9b24 (vtable slot 17 of the frame heap): frame heaps have no group ids; 0. */
int FrameHeap_SetGroupId(void)
{
    return 0;
}
CLEAN_AS(func_020e9b24, FrameHeap_SetGroupId)

/* func_020e9b2c (vtable slot 17 of the expanded heap): the group id new blocks get set; the one
 * before. */
int ExpHeap_SetGroupId(Heap *heap, u16 group_id)
{
    return NNS_FndSetGroupIDForExpHeap(heap->handle, group_id);
}
CLEAN_AS(func_020e9b2c, ExpHeap_SetGroupId)

/* func_020e9b3c (vtable slot 12 of the frame heap): a frame heap does not know its blocks'
 * sizes; -1. */
int FrameHeap_BlockSize(void)
{
    return -1;
}
CLEAN_AS(func_020e9b3c, FrameHeap_BlockSize)

/* func_020e9b44 (vtable slot 12 of the expanded heap): the size of one of its blocks. */
int ExpHeap_BlockSize(Heap *heap, void *block)
{
    (void) heap;
    return (int) NNS_FndGetSizeForMBlockExpHeap(block);
}
CLEAN_AS(func_020e9b44, ExpHeap_BlockSize)

/* func_020e9b54 (vtable slot 8 of the frame heap): everything allocated freed, from both ends. */
void FrameHeap_FreeAll(Heap *heap)
{
    NNS_FndFreeToFrmHeap(heap->handle, NNS_FRMHEAP_FREE_ALL);
}
CLEAN_AS(func_020e9b54, FrameHeap_FreeAll)

/* func_020e9b68 (vtable slot 8 of the expanded heap): every allocated block freed, one by one. */
void ExpHeap_FreeAll(Heap *heap)
{
    NNS_FndVisitAllocatedForExpHeap(heap->handle, func_020e9b84, 0);
}
CLEAN_AS(func_020e9b68, ExpHeap_FreeAll)

/* func_020e9b84: ExpHeap_FreeAll's visitor; frees the block it is shown. */
void ExpHeap_FreeVisitedBlock(void *block, void *handle, u32 unused)
{
    (void) unused;
    NNS_FndFreeToExpHeap(handle, block);
}
CLEAN_AS(func_020e9b84, ExpHeap_FreeVisitedBlock)

/* func_020e9b9c: everything allocated in the heap freed (its vtable's free_all), reported to
 * the free hook as a free of NULL. */
void Heap_FreeAll(Heap *heap)
{
    Heap_Lock(heap);
    if (data_021fbe7c != NULL && (heap->flags & HEAP_CALL_FREE_HOOK) != 0) {
        data_021fbe7c(heap, NULL);
    }
    heap->vtable->free_all(heap);
    Heap_Unlock(heap);
}
CLEAN_AS(func_020e9b9c, Heap_FreeAll)

/* func_020e9bf4 (vtable slot 7 of the frame heap): a frame heap cannot free one block; asked to,
 * it stops the game. NULL is ignored. */
void FrameHeap_Free(Heap *heap, void *block)
{
    (void) heap;
    if (block == NULL) {
        return;
    }
    GameHalt_Terminate();
}
CLEAN_AS(func_020e9bf4, FrameHeap_Free)

/* func_020e9c1c (vtable slot 7 of the expanded heap); NULL is ignored. */
void ExpHeap_Free(Heap *heap, void *block)
{
    if (block == NULL) {
        return;
    }
    NNS_FndFreeToExpHeap(heap->handle, block);
}
CLEAN_AS(func_020e9c1c, ExpHeap_Free)

/* func_020e9c48: a block freed (its vtable's free), reported to the free hook first. NULL is
 * ignored. */
void Heap_FreeBlock(Heap *heap, void *block)
{
    if (block == NULL) {
        return;
    }
    Heap_Lock(heap);
    if (data_021fbe7c != NULL && (heap->flags & HEAP_CALL_FREE_HOOK) != 0) {
        data_021fbe7c(heap, block);
    }
    heap->vtable->free(heap, block);
    Heap_Unlock(heap);
}
CLEAN_AS(func_020e9c48, Heap_FreeBlock)

/* func_020e9cbc (vtable slot 11 of the frame heap): the block resized in place; its new size, 0
 * when it cannot change. */
int FrameHeap_Resize(Heap *heap, void *block, u32 size)
{
    return (int) func_021023c8(heap->handle, block, size);
}
CLEAN_AS(func_020e9cbc, FrameHeap_Resize)

/* func_020e9ccc (vtable slot 11 of the expanded heap): the same for an expanded heap. */
int ExpHeap_Resize(Heap *heap, void *block, u32 size)
{
    return (int) func_02101c54(heap->handle, block, size);
}
CLEAN_AS(func_020e9ccc, ExpHeap_Resize)

/* func_020e9cdc: a block resized in place (its vtable's resize); its new size, 0 when it cannot
 * change. */
int Heap_Resize(Heap *heap, void *block, int size)
{
    Heap_Lock(heap);
    int result = heap->vtable->resize(heap, block, (u32) size);
    Heap_Unlock(heap);
    return result;
}
CLEAN_AS(func_020e9cdc, Heap_Resize)

/* func_020e9d20 (vtable slot 16 of the frame heap): its free memory is what can be allocated at
 * 4-byte alignment.
 * QUIRK: the ROM's code ends in a jump to NNS, so its caller receives NNS's answer, which the
 * slot's callers read as the result; this version, like its matching source, has none. */
void FrameHeap_TotalFree(Heap *heap)
{
    NNS_FndGetAllocatableSizeForFrmHeapEx(heap->handle, 4);
}
CLEAN_AS(func_020e9d20, FrameHeap_TotalFree)

/* func_020e9d34 (vtable slot 16 of the expanded heap): all of its free memory, in however many
 * pieces. */
int ExpHeap_TotalFree(Heap *heap)
{
    return (int) NNS_FndGetTotalFreeSizeForExpHeap(heap->handle);
}
CLEAN_AS(func_020e9d34, ExpHeap_TotalFree)

/* func_020e9d44 (vtable slot 15 of the frame heap): the largest block it can allocate at the
 * alignment (negative: from the back). */
int FrameHeap_Allocatable(Heap *heap, int align)
{
    return (int) NNS_FndGetAllocatableSizeForFrmHeapEx(heap->handle, align);
}
CLEAN_AS(func_020e9d44, FrameHeap_Allocatable)

/* func_020e9d54 (vtable slot 15 of the expanded heap). */
int ExpHeap_Allocatable(Heap *heap, int align)
{
    return (int) NNS_FndGetAllocatableSizeForExpHeapEx(heap->handle, align);
}
CLEAN_AS(func_020e9d54, ExpHeap_Allocatable)

/* func_020e9d64: the largest block the heap can allocate at the alignment (its vtable's
 * allocatable); what an allocation of size -1 gets. */
int Heap_GetAllocatableSize(Heap *heap, int align)
{
    Heap_Lock(heap);
    int size = heap->vtable->allocatable(heap, align);
    Heap_Unlock(heap);
    return size;
}
CLEAN_AS(func_020e9d64, Heap_GetAllocatableSize)

/* func_020e9da8 (vtable slot 14 of the frame heap): the largest block at 4-byte alignment. */
int FrameHeap_LargestBlock(Heap *heap)
{
    return (int) NNS_FndGetAllocatableSizeForFrmHeapEx(heap->handle, 4);
}
CLEAN_AS(func_020e9da8, FrameHeap_LargestBlock)

/* func_020e9dbc (vtable slot 14 of the expanded heap). */
int ExpHeap_LargestBlock(Heap *heap)
{
    return (int) NNS_FndGetAllocatableSizeForExpHeapEx(heap->handle, 4);
}
CLEAN_AS(func_020e9dbc, ExpHeap_LargestBlock)

/* func_020e9dd0: the largest block the heap can allocate (its vtable's largest_block); the
 * archive reader (func_020649ac) sizes its streaming buffer with it. */
int Heap_GetLargestBlock(Heap *heap)
{
    Heap_Lock(heap);
    int size = heap->vtable->largest_block(heap);
    Heap_Unlock(heap);
    return size;
}
CLEAN_AS(func_020e9dd0, Heap_GetLargestBlock)

/* func_020e9e0c (vtable slot 13 of the frame heap): the largest block at 4-byte alignment.
 * QUIRK: as FrameHeap_TotalFree, the ROM's caller receives NNS's answer; this version, like its
 * matching source, has no result. */
void FrameHeap_FreeSize(Heap *heap)
{
    NNS_FndGetAllocatableSizeForFrmHeapEx(heap->handle, 4);
}
CLEAN_AS(func_020e9e0c, FrameHeap_FreeSize)

/* func_020e9e20 (vtable slot 13 of the expanded heap): the largest block at 4-byte alignment,
 * not the total free (ExpHeap_TotalFree). */
int ExpHeap_FreeSize(Heap *heap)
{
    return (int) NNS_FndGetAllocatableSizeForExpHeapEx(heap->handle, 4);
}
CLEAN_AS(func_020e9e20, ExpHeap_FreeSize)

/* func_020e9e34: the heap's free memory (its vtable's free_size); callers take it from the
 * heap's size to get what is in use (func_020ee0a4). */
int Heap_GetFreeSize(Heap *heap)
{
    Heap_Lock(heap);
    int size = heap->vtable->free_size(heap);
    Heap_Unlock(heap);
    return size;
}
CLEAN_AS(func_020e9e34, Heap_GetFreeSize)

/* func_020e9e70 (vtable slot 10 of the frame heap): empty. */
void FrameHeap_Report(void) {}
CLEAN_AS(func_020e9e70, FrameHeap_Report)

/* func_020e9e74 (vtable slot 10 of the expanded heap): empty. */
void ExpHeap_Report(void) {}
CLEAN_AS(func_020e9e74, ExpHeap_Report)

/* func_020e9e78: the heap's vtable slot 10, empty for both kinds of heap. A hidden button
 * sequence (func_02001324) calls it for the root, current and auxiliary heaps, which suggests a
 * report of the heap's contents left out of this build. */
void Heap_Report(Heap *heap)
{
    Heap_Lock(heap);
    heap->vtable->report(heap);
    Heap_Unlock(heap);
}
CLEAN_AS(func_020e9e78, Heap_Report)

/* func_020e9ea4 (vtable slot 9 of the frame heap): 1; its use is not known. */
int FrameHeap_Unk24(void)
{
    return 1;
}
CLEAN_AS(func_020e9ea4, FrameHeap_Unk24)

/* func_020e9eac (vtable slot 9 of the expanded heap): 1, as the frame heap's. */
int ExpHeap_Unk24(void)
{
    return 1;
}
CLEAN_AS(func_020e9eac, ExpHeap_Unk24)

/* func_020e9eb4 (vtable slot 6 of the frame heap). */
void *FrameHeap_Alloc(Heap *heap, u32 size, int align)
{
    return NNS_FndAllocFromFrmHeapEx(heap->handle, size, align);
}
CLEAN_AS(func_020e9eb4, FrameHeap_Alloc)

/* func_020e9ec4 (vtable slot 6 of the expanded heap). */
void *ExpHeap_Alloc(Heap *heap, u32 size, int align)
{
    return NNS_FndAllocFromExpHeapEx(heap->handle, size, align);
}
CLEAN_AS(func_020e9ec4, ExpHeap_Alloc)

/* func_020e9ed4: a block of `size` bytes (-1: the largest there is) at the alignment (negative:
 * from the back), through the heap's vtable; NULL when there is no room, which stops the game
 * for a heap with HEAP_STOP_ON_FAILURE. The alloc hook sees the result and the size asked. */
void *Heap_AllocBlock(Heap *heap, int size, int align)
{
    Heap_Lock(heap);
    if (size == -1) {
        size = Heap_GetAllocatableSize(heap, align);
    }
    void *block = heap->vtable->alloc(heap, size, align);
    if (data_021fbe84 != NULL && (heap->flags & HEAP_CALL_ALLOC_HOOK) != 0) {
        data_021fbe84(heap, block, size, align);
    }
    if (block == NULL && (heap->flags & HEAP_STOP_ON_FAILURE) != 0) {
        GameHalt_Terminate();
    }
    Heap_Unlock(heap);
    return block;
}
CLEAN_AS(func_020e9ed4, Heap_AllocBlock)

/* func_020e9f88 (vtable slot 5 of the frame heap): the NNS heap destroyed and forgotten. */
void FrameHeap_Destroy(Heap *heap)
{
    NNS_FndDestroyFrmHeap(heap->handle);
    heap->handle = NULL;
}
CLEAN_AS(func_020e9f88, FrameHeap_Destroy)

/* func_020e9fa8 (vtable slot 5 of the expanded heap). */
void ExpHeap_Destroy(Heap *heap)
{
    func_02101e20(heap->handle);
    heap->handle = NULL;
}
CLEAN_AS(func_020e9fa8, ExpHeap_Destroy)

/* func_020e9fc8: Heap_Destroy, the entry most of the game calls. */
void Heap_Delete(Heap *heap)
{
    Heap_Destroy(heap);
}
CLEAN_AS(func_020e9fc8, Heap_Delete)

/* func_020e9fd4: the heap destroyed: its NNS heap (the vtable's destroy) and the object (its
 * destructor), and its block given back to the parent heap. A heap without a parent (one made
 * in memory of its own) only loses its NNS heap and object. */
void Heap_Destroy(Heap *heap)
{
    Heap_Lock(heap);
    heap->vtable->destroy(heap);
    heap->start = NULL;
    heap->size = 0;
    Heap_Unlock(heap);
    Heap *parent = heap->parent;
    heap->vtable->destruct(heap);
    if (parent == NULL) {
        return;
    }
    Heap_FreeBlock(parent, heap);
}
CLEAN_AS(func_020e9fd4, Heap_Destroy)

/* func_020ea044 (vtable slot 4 of the expanded heap): its mutex taken if it is free.
 * QUIRK: the ROM's caller receives OS_TryLockMutex's answer, as the jump to it ends the
 * function; this version, like its matching source, has no result. */
void ExpHeap_TryLock(ExpHeap *heap)
{
    OS_TryLockMutex(&heap->mutex);
}
CLEAN_AS(func_020ea044, ExpHeap_TryLock)

/* func_020ea054 (vtable slot 3 of the expanded heap). */
void ExpHeap_Unlock(ExpHeap *heap)
{
    OS_UnlockMutex(&heap->mutex);
}
CLEAN_AS(func_020ea054, ExpHeap_Unlock)

/* func_020ea064 (vtable slot 2 of the expanded heap). */
void ExpHeap_Lock(ExpHeap *heap)
{
    OS_LockMutex(&heap->mutex);
}
CLEAN_AS(func_020ea064, ExpHeap_Lock)

/* func_020ea074 (vtable slot 4 of the frame heap and of the base class): a heap without a mutex
 * can always be locked; 1. */
int Heap_TryLockNothing(void)
{
    return 1;
}
CLEAN_AS(func_020ea074, Heap_TryLockNothing)

/* func_020ea07c (vtable slot 3 of the frame heap and of the base class). */
void Heap_UnlockNothing(void) {}
CLEAN_AS(func_020ea07c, Heap_UnlockNothing)

/* func_020ea080 (vtable slot 2 of the frame heap and of the base class). */
void Heap_LockNothing(void) {}
CLEAN_AS(func_020ea080, Heap_LockNothing)

/* func_020ea084: the heap unlocked (its vtable's unlock). */
void Heap_Unlock(Heap *heap)
{
    heap->vtable->unlock(heap);
}
CLEAN_AS(func_020ea084, Heap_Unlock)

/* func_020ea0a4: the heap locked (its vtable's lock). Outside the CPU's system mode, as in an
 * interrupt handler, that stops the game unless the heap has HEAP_ANY_MODE. */
void Heap_Lock(Heap *heap)
{
    if (OS_GetProcMode() != CPU_MODE_SYSTEM && (heap->flags & HEAP_ANY_MODE) == 0) {
        GameHalt_Terminate();
    }
    heap->vtable->lock(heap);
}
CLEAN_AS(func_020ea0a4, Heap_Lock)

/* func_020ea0e0: a new frame heap with `size` bytes of its own (-1: all that `parent` can give),
 * in a block of `parent` (NULL: the current heap); NULL when there is no room. */
Heap *FrameHeap_Create(int size, Heap *parent)
{
    u32 block_size;
    u32 nns_size;

    if (parent == NULL) {
        parent = data_021fbe94;
    }
    if (size == -1) {
        block_size = (u32) Heap_GetAllocatableSize(parent, 4);
        if (block_size < sizeof(Heap) + FRAME_HEAP_HEADER) {
            return NULL;
        }
        nns_size = block_size - sizeof(Heap);
    } else {
        nns_size = (((u32) size + 3) & ~3u) + FRAME_HEAP_HEADER;
        block_size = nns_size + sizeof(Heap);
    }
    Heap *heap = Heap_AllocBlock(parent, (int) block_size, 4);
    if (heap == NULL) {
        return NULL;
    }
    void *start = heap + 1;
    void *handle = NNS_FndCreateFrmHeapEx(start, nns_size, data_0213e5a4);
    if (handle == NULL) {
        Heap_FreeBlock(parent, heap);
        return NULL;
    }
    FrameHeap_Construct(heap, start, (int) nns_size, parent, handle);
    return heap;
}
CLEAN_AS(func_020ea0e0, FrameHeap_Create)

/* GX_ResetBankForSubOBJExtPltt: a new expanded heap, as FrameHeap_Create makes a frame heap.
 * Its symbol carries a NitroSDK name that does not fit what it does. */
Heap *ExpHeap_Create(int size, Heap *parent)
{
    u32 block_size;
    u32 nns_size;

    if (parent == NULL) {
        parent = data_021fbe94;
    }
    if (size == -1) {
        block_size = (u32) Heap_GetAllocatableSize(parent, 4);
        if (block_size < sizeof(ExpHeap) + EXP_HEAP_HEADER) {
            return NULL;
        }
        nns_size = block_size - sizeof(ExpHeap);
    } else {
        nns_size = (((u32) size + 3) & ~3u) + EXP_HEAP_HEADER;
        block_size = nns_size + sizeof(ExpHeap);
    }
    ExpHeap *heap = Heap_AllocBlock(parent, (int) block_size, 4);
    if (heap == NULL) {
        return NULL;
    }
    void *start = heap + 1;
    void *handle = NNS_FndCreateExpHeapEx(start, nns_size, data_0213e5a4);
    if (handle == NULL) {
        Heap_FreeBlock(parent, heap);
        return NULL;
    }
    ExpHeap_Construct(heap, start, (int) nns_size, parent, handle);
    return &heap->heap;
}
CLEAN_AS(GX_ResetBankForSubOBJExtPltt, ExpHeap_Create)

/* func_020ea298: an expanded heap without a parent, made in the `size` bytes at `memory` (the
 * root heap in the arena, and a heap of overlay 3 in memory of its own); NULL when NNS cannot.
 * REQUIRES: `memory` is not NULL. With NULL the ROM still has NNS make a heap at 0x30, and
 * returns NULL; this version does the same, without forming the address from a null pointer. */
Heap *ExpHeap_CreateAt(void *memory, u32 size)
{
    void *start = (void *) ((uintptr_t) memory + sizeof(ExpHeap));
    u32 nns_size = size - sizeof(ExpHeap);
    void *handle = NNS_FndCreateExpHeapEx(start, nns_size, data_0213e5a4);
    if (handle == NULL) {
        return NULL;
    }
    if (memory != NULL) {
        ExpHeap_Construct(memory, start, (int) nns_size, NULL, handle);
    }
    return memory;
}
CLEAN_AS(func_020ea298, ExpHeap_CreateAt)

/* func_020ea30c (vtable slot 1 of the frame heap): destructed and freed to the current heap. */
Heap *FrameHeap_DestructFree(Heap *heap)
{
    heap->vtable = &data_0213e608;
    Heap_DestructBase(heap);
    Heap_OperatorDeleteB(heap);
    return heap;
}
CLEAN_AS(func_020ea30c, FrameHeap_DestructFree)

/* func_020ea338 (vtable slot 0 of the frame heap): back to the base class; the NNS heap is
 * left to Heap_Destroy. */
Heap *FrameHeap_Destruct(Heap *heap)
{
    heap->vtable = &data_0213e608;
    Heap_DestructBase(heap);
    return heap;
}
CLEAN_AS(func_020ea338, FrameHeap_Destruct)

/* func_020ea35c (vtable slot 1 of the expanded heap). */
Heap *ExpHeap_DestructFree(Heap *heap)
{
    heap->vtable = &data_0213e5b0;
    Heap_DestructBase(heap);
    Heap_OperatorDeleteB(heap);
    return heap;
}
CLEAN_AS(func_020ea35c, ExpHeap_DestructFree)

/* func_020ea388 (vtable slot 0 of the expanded heap). */
Heap *ExpHeap_Destruct(Heap *heap)
{
    heap->vtable = &data_0213e5b0;
    Heap_DestructBase(heap);
    return heap;
}
CLEAN_AS(func_020ea388, ExpHeap_Destruct)

/* func_020ea3ac: the base class's destructor as the derived ones call it. */
void Heap_DestructBase(Heap *heap)
{
    heap->vtable = &data_0213e660;
}
CLEAN_AS(func_020ea3ac, Heap_DestructBase)

/* func_020ea3bc (vtable slot 1 of the base class). */
Heap *Heap_DestructFree(Heap *heap)
{
    heap->vtable = &data_0213e660;
    Heap_OperatorDeleteB(heap);
    return heap;
}
CLEAN_AS(func_020ea3bc, Heap_DestructFree)

/* func_020ea3e0 (vtable slot 0 of the base class): the same as Heap_DestructBase. */
void Heap_Destruct(Heap *heap)
{
    heap->vtable = &data_0213e660;
}
CLEAN_AS(func_020ea3e0, Heap_Destruct)

/* func_020ea3f0: the frame heap object for an NNS heap made at `start`. */
Heap *FrameHeap_Construct(Heap *heap, void *start, int size, Heap *parent, void *handle)
{
    Heap_Construct(heap, start, (u32) size, parent);
    heap->vtable = &data_0213e608;
    heap->handle = handle;
    return heap;
}
CLEAN_AS(func_020ea3f0, FrameHeap_Construct)

/* func_020ea41c: the expanded heap object for an NNS heap made at `start`, with its mutex. */
Heap *ExpHeap_Construct(ExpHeap *heap, void *start, int size, Heap *parent, void *handle)
{
    Heap_Construct(&heap->heap, start, (u32) size, parent);
    heap->heap.vtable = &data_0213e5b0;
    heap->heap.handle = handle;
    OS_InitMutex(&heap->mutex);
    return &heap->heap;
}
CLEAN_AS(func_020ea41c, ExpHeap_Construct)

/* func_020ea450: the base class's constructor. A heap starts with HEAP_STOP_ON_FAILURE only.
 * QUIRK: the ROM stores 0 to the flags before HEAP_STOP_ON_FAILURE; nothing runs in between. */
void Heap_Construct(Heap *heap, void *start, u32 size, Heap *parent)
{
    heap->vtable = &data_0213e660;
    heap->start = start;
    heap->size = size;
    heap->parent = parent;
    heap->flags = HEAP_STOP_ON_FAILURE;
}
CLEAN_AS(func_020ea450, Heap_Construct)

/* func_020ea48c: the root heap made at start-up (NitroStartUp) from the main arena, of
 * data_021fbe90 bytes or, when that is 0, all of the arena from its 32-byte aligned start; once
 * made, each thread keeps its own current heap (Heap_InstallThreadHook). */
void Heap_InitRoot(void)
{
    u32 size = data_021fbe90;
    data_021fbe98 = 0;
    if (size == 0) {
        uintptr_t lo = (uintptr_t) OS_GetArenaLo(0);
        uintptr_t hi = (uintptr_t) OS_GetArenaHi(data_021fbe98);
        size = (u32) (hi - ((lo + 0x1f) & ~(uintptr_t) 0x1f));
    }
    void *memory = OS_AllocFromArenaLo(data_021fbe98, size, 0x20);
    if (Heap_CreateRoot(memory, size) != 0) {
        Heap_InstallThreadHook();
    }
}
CLEAN_AS(func_020ea48c, Heap_InitRoot)

/* func_020ea50c: the root heap made at `memory` and made the current heap; the heap, 0 when it
 * could not be made. The start-up is marked done either way. */
int Heap_CreateRoot(void *memory, u32 size)
{
    Heap *heap = ExpHeap_CreateAt(memory, size);
    if (heap != NULL) {
        data_021fbe8c = heap;
        data_021fbe94 = heap;
    }
    data_021fbe78 = 1;
    return (int) (uintptr_t) heap;
}
CLEAN_AS(func_020ea50c, Heap_CreateRoot)

/* func_020ea550: from now on each thread keeps its own current heap: the thread-switch callback
 * swaps it (Heap_SwitchThreads), and the callback installed before is kept to be called after.
 * Returns what OS_RestoreInterrupts returns, the interrupt state before. */
u32 Heap_InstallThreadHook(void)
{
    u32 interrupts = OS_DisableInterrupts();
    data_021fbe88 = OS_SetSwitchThreadCallback(func_020ea5c4);
    return OS_RestoreInterrupts(interrupts);
}
CLEAN_AS(func_020ea550, Heap_InstallThreadHook)

/* func_020ea584: `heap` made the current heap of `thread`: at once when it is the running
 * thread, else when it next runs (Heap_SwitchThreads). */
void Heap_SetThreadHeap(OSThread *thread, Heap *heap)
{
    if (thread == OSi_ThreadInfo.current) {
        Heap_SetCurrent(heap);
    } else {
        OS_SetThreadParameter(thread, heap);
    }
}
CLEAN_AS(func_020ea584, Heap_SetThreadHeap)

/* func_020ea5c4: the thread-switch callback. The current heap is kept in the parameter of the
 * thread that stops, and the one kept by the thread that starts becomes the current heap; its
 * parameter is cleared. Then the callback installed before, if any. */
void Heap_SwitchThreads(OSThread *from, OSThread *to)
{
    OS_SetThreadParameter(from, data_021fbe94);
    data_021fbe94 = OS_GetThreadParameter(to);
    OS_SetThreadParameter(to, NULL);
    if (data_021fbe88 != NULL) {
        data_021fbe88(from, to);
    }
}
CLEAN_AS(func_020ea5c4, Heap_SwitchThreads)

/* ---- Allocation for objects ---- */

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* func_020edb60: a block freed to the current heap. */
void Heap_OperatorFree(void *block)
{
    Heap_Free(data_021fbe94, block);
}
CLEAN_AS(func_020edb60, Heap_OperatorFree)

/* func_020edb7c: a block from the front of the current heap. */
void *Heap_OperatorAlloc(u32 size)
{
    return Heap_Alloc(data_021fbe94, (int) size);
}
CLEAN_AS(func_020edb7c, Heap_OperatorAlloc)

/* func_020edb30 and func_020edb3c free through the current heap, func_020edb48 and
 * func_020edb54 allocate from it: by their shape C++'s operator delete and delete[], new and
 * new[] (which of each pair is the array form is not known). */

/* func_020edb30 */
void Heap_OperatorDelete(void *block)
{
    Heap_OperatorFree(block);
}
CLEAN_AS(func_020edb30, Heap_OperatorDelete)

/* func_020edb3c: what most of the game frees with. */
void Heap_OperatorDeleteB(void *block)
{
    Heap_OperatorFree(block);
}
CLEAN_AS(func_020edb3c, Heap_OperatorDeleteB)

/* func_020edb48. QUIRK: it jumps to Heap_OperatorAlloc, so the block is left in the result
 * register, but it is declared without a result. */
void Heap_OperatorNew(u32 size)
{
    Heap_OperatorAlloc(size);
}
CLEAN_AS(func_020edb48, Heap_OperatorNew)

/* func_020edb54 */
void *Heap_OperatorNewB(u32 size)
{
    return Heap_OperatorAlloc(size);
}
CLEAN_AS(func_020edb54, Heap_OperatorNewB)

/* func_020edf54: a block freed to the auxiliary heap (processes are freed with it). */
void Heap_FreeAux(void *block)
{
    Heap_FreeBlock(sSubOBJExtPltt, block);
}
CLEAN_AS(func_020edf54, Heap_FreeAux)

/* func_020edf70: a zeroed block of `size` bytes from the back of the auxiliary heap; NULL when
 * there is no room. The game allocates its processes with it. */
void *Heap_AllocAuxZeroed(int size)
{
    void *block = Heap_AllocBlock(sSubOBJExtPltt, size, ALIGN_BACK);
    if (block == NULL) {
        return NULL;
    }
    MI_CpuFill8(block, 0, (u32) size);
    return block;
}
CLEAN_AS(func_020edf70, Heap_AllocAuxZeroed)
