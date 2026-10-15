/* The game's heaps: C++ objects over NitroSystem's expanded and frame heaps (NNS_Fnd), called
 * through a vtable, with a current heap that the allocation functions without a heap use.
 *
 * Each heap object sits at the start of the block it was allocated as from its parent heap,
 * and the NNS heap it manages follows it. */
#ifndef CLEAN_AUTOLOAD_2_HEAP_H
#define CLEAN_AUTOLOAD_2_HEAP_H

#include "types.h"

struct Heap;

/* The slots the functions here use; the others are not named yet. Each takes the heap first. */
typedef struct HeapVtable {
    const void *unk_00[19];
    int (*adjust)(struct Heap *heap); /* shrink to what is allocated: the block's new size */
} HeapVtable;

typedef struct Heap {
    const HeapVtable *vtable;
    void *start;         /* the NNS heap's memory, after this object */
    u32 size;            /* its size */
    struct Heap *parent; /* the heap this one's block came from */
    u32 flags;           /* HeapFlags */
    void *handle;        /* the NNS heap */
} Heap;

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

#endif
