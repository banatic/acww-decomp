/* The game's heaps: C++ objects over NitroSystem's expanded and frame heaps (NNS_Fnd), called
 * through a vtable, with a current heap that the allocation functions without a heap use.
 *
 * Each heap object sits at the start of the block it was allocated as from its parent heap,
 * and the NNS heap it manages follows it. Three classes share the layout: a base class whose
 * vtable (data_0213e660) has only the destructors and a lock that does nothing, the frame heap
 * (data_0213e608) and the expanded heap (data_0213e5b0), which adds a mutex. */
#ifndef CLEAN_AUTOLOAD_2_HEAP_H
#define CLEAN_AUTOLOAD_2_HEAP_H

#include "types.h"

struct Heap;
struct OSThread;

/* The heap's virtual functions; each takes the heap first. The comments give what the frame
 * heap's and the expanded heap's versions do where they differ. */
typedef struct HeapVtable {
    void (*destruct)(struct Heap *heap);                     /* 0x00 */
    void *(*destruct_free)(struct Heap *heap);               /* 0x04: destruct, then free the object */
    void (*lock)(struct Heap *heap);                         /* 0x08: frame: nothing; expanded: its mutex */
    void (*unlock)(struct Heap *heap);                       /* 0x0c */
    int (*try_lock)(struct Heap *heap);                      /* 0x10: frame: 1; expanded: OS_TryLockMutex */
    void (*destroy)(struct Heap *heap);                      /* 0x14: destroy the NNS heap */
    void *(*alloc)(struct Heap *heap, int size, int align);  /* 0x18 */
    void (*free)(struct Heap *heap, void *block);            /* 0x1c: frame: stops the game unless NULL */
    void (*free_all)(struct Heap *heap);                     /* 0x20 */
    int (*unk_24)(struct Heap *heap);                        /* 0x24: 1 in both */
    void (*report)(struct Heap *heap);                       /* 0x28: empty in both */
    int (*resize)(struct Heap *heap, void *block, u32 size); /* 0x2c: the block's new size */
    int (*block_size)(struct Heap *heap, void *block);       /* 0x30: frame: -1 */
    int (*free_size)(struct Heap *heap);                     /* 0x34: allocatable at 4 bytes */
    int (*largest_block)(struct Heap *heap);                 /* 0x38: allocatable at 4 bytes */
    int (*allocatable)(struct Heap *heap, int align);        /* 0x3c */
    int (*total_free)(struct Heap *heap);                    /* 0x40: frame: allocatable */
    int (*set_group_id)(struct Heap *heap, u16 group_id);    /* 0x44: frame: 0 */
    int (*group_id)(struct Heap *heap);                      /* 0x48: frame: 0 */
    int (*adjust)(struct Heap *heap);                        /* 0x4c: shrink to what is allocated: the block's new size */
} HeapVtable;

typedef struct Heap {
    const HeapVtable *vtable;
    void *start;         /* the NNS heap's memory, after this object */
    u32 size;            /* its size */
    struct Heap *parent; /* the heap this one's block came from */
    u32 flags;           /* HeapFlags */
    void *handle;        /* the NNS heap */
} Heap;

/* NitroSDK's OSMutex, used here only through OS_*Mutex. */
typedef struct OSMutex {
    u8 unk_00[0x18];
} OSMutex;

/* An expanded heap: the heap and the mutex its lock takes. */
typedef struct ExpHeap {
    Heap heap;
    OSMutex mutex;
} ExpHeap;

enum HeapFlags {
    HEAP_CALL_ALLOC_HOOK = 1 << 10, /* report allocations to the hook the game can install */
    HEAP_CALL_FREE_HOOK = 1 << 11,  /* report frees to the hook */
    HEAP_ANY_MODE = 1 << 13,        /* usable outside the CPU's system mode (from interrupts) */
    HEAP_STOP_ON_FAILURE = 1 << 14, /* a failed allocation or adjustment stops the game */
    HEAP_FLAGS_READ_ONLY = 1 << 15  /* given to Heap_SetFlags: only read the flags */
};

void Heap_FreeCurrent(void *block);
void *Heap_AllocCurrent(int size);
void *Heap_AllocCurrentBack(int size);
void *Heap_AllocCurrentAligned(int size, int align);
void Heap_CreateAuxHeap(int size, Heap *parent);
void Heap_Free(Heap *heap, void *block);
void *Heap_Alloc(Heap *heap, int size);
void *Heap_AllocBack(Heap *heap, int size);
void *Heap_AllocAligned(Heap *heap, int size, int align);
void Heap_PopThreadHeap(void);
void Heap_SaveThreadHeap(void);
Heap *Heap_PushFrameHeap(int size, Heap *parent);
Heap *Heap_SetCurrent(Heap *heap);
int Heap_SetFlags(Heap *heap, int flags);
int FrameHeap_Adjust(Heap *heap);
int ExpHeap_Adjust(void);
int Heap_Adjust(Heap *heap);
int FrameHeap_GroupId(void);
int ExpHeap_GroupId(Heap *heap);

int FrameHeap_SetGroupId(void);
int ExpHeap_SetGroupId(Heap *heap, u16 group_id);
int FrameHeap_BlockSize(void);
int ExpHeap_BlockSize(Heap *heap, void *block);
void FrameHeap_FreeAll(Heap *heap);
void ExpHeap_FreeAll(Heap *heap);
void ExpHeap_FreeVisitedBlock(void *block, void *handle, u32 unused);
void Heap_FreeAll(Heap *heap);
void FrameHeap_Free(Heap *heap, void *block);
void ExpHeap_Free(Heap *heap, void *block);
void Heap_FreeBlock(Heap *heap, void *block);
int FrameHeap_Resize(Heap *heap, void *block, u32 size);
int ExpHeap_Resize(Heap *heap, void *block, u32 size);
int Heap_Resize(Heap *heap, void *block, int size);
void FrameHeap_TotalFree(Heap *heap);
int ExpHeap_TotalFree(Heap *heap);
int FrameHeap_Allocatable(Heap *heap, int align);
int ExpHeap_Allocatable(Heap *heap, int align);
int Heap_GetAllocatableSize(Heap *heap, int align);
int FrameHeap_LargestBlock(Heap *heap);
int ExpHeap_LargestBlock(Heap *heap);
int Heap_GetLargestBlock(Heap *heap);
void FrameHeap_FreeSize(Heap *heap);
int ExpHeap_FreeSize(Heap *heap);
int Heap_GetFreeSize(Heap *heap);
void FrameHeap_Report(void);
void ExpHeap_Report(void);
void Heap_Report(Heap *heap);
int FrameHeap_Unk24(void);
int ExpHeap_Unk24(void);
void *FrameHeap_Alloc(Heap *heap, u32 size, int align);
void *ExpHeap_Alloc(Heap *heap, u32 size, int align);
void *Heap_AllocBlock(Heap *heap, int size, int align);
void FrameHeap_Destroy(Heap *heap);
void ExpHeap_Destroy(Heap *heap);
void Heap_Delete(Heap *heap);
void Heap_Destroy(Heap *heap);
void ExpHeap_TryLock(ExpHeap *heap);
void ExpHeap_Unlock(ExpHeap *heap);
void ExpHeap_Lock(ExpHeap *heap);
int Heap_TryLockNothing(void);
void Heap_UnlockNothing(void);
void Heap_LockNothing(void);
void Heap_Unlock(Heap *heap);
void Heap_Lock(Heap *heap);
Heap *FrameHeap_Create(int size, Heap *parent);
Heap *ExpHeap_Create(int size, Heap *parent);
Heap *ExpHeap_CreateAt(void *memory, u32 size);
Heap *FrameHeap_DestructFree(Heap *heap);
Heap *FrameHeap_Destruct(Heap *heap);
Heap *ExpHeap_DestructFree(Heap *heap);
Heap *ExpHeap_Destruct(Heap *heap);
void Heap_DestructBase(Heap *heap);
Heap *Heap_DestructFree(Heap *heap);
void Heap_Destruct(Heap *heap);
Heap *FrameHeap_Construct(Heap *heap, void *start, int size, Heap *parent, void *handle);
Heap *ExpHeap_Construct(ExpHeap *heap, void *start, int size, Heap *parent, void *handle);
void Heap_Construct(Heap *heap, void *start, u32 size, Heap *parent);
void Heap_InitRoot(void);
int Heap_CreateRoot(void *memory, u32 size);
u32 Heap_InstallThreadHook(void);
void Heap_SetThreadHeap(struct OSThread *thread, Heap *heap);
void Heap_SwitchThreads(struct OSThread *from, struct OSThread *to);
void Heap_OperatorFree(void *block);
void *Heap_OperatorAlloc(u32 size);
void Heap_OperatorDelete(void *block);
void Heap_OperatorDeleteB(void *block);
void Heap_OperatorNew(u32 size);
void *Heap_OperatorNewB(u32 size);
void Heap_FreeAux(void *block);
void *Heap_AllocAuxZeroed(int size);

#endif
