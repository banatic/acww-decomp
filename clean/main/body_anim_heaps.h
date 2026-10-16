/* The frame heaps the players' body models (a field actor's LayeredModel at FIELD_ACTOR_BODY)
 * take their animation objects and joint results from (data_021cacd0, a global C++ object):
 * one heap of BodyAnimHeaps_HeapSize bytes for each of the session's players, made in the
 * scene's heap at data_021c9ad0 when the scene starts.
 *
 * A field actor names its heap with one byte at 0x388 (the player's, data_020c75c0),
 * BODY_ANIM_HEAPS_COUNT for none; a heap is emptied when an actor takes it. */
#ifndef CLEAN_MAIN_BODY_ANIM_HEAPS_H
#define CLEAN_MAIN_BODY_ANIM_HEAPS_H

#include "autoload_2/heap.h"
#include "types.h"

/* The number of heaps, also a heap byte's value for none. */
#define BODY_ANIM_HEAPS_COUNT 4

typedef struct BodyAnimHeaps {
    Heap *heap[BODY_ANIM_HEAPS_COUNT]; /* 0x00 */
} BodyAnimHeaps;

unsigned long BodyAnimHeaps_SlotHeap(unsigned char *slot);
void BodyAnimHeaps_Assign(char *slot, char index);
void BodyAnimHeaps_DestructSlot(void *slot);
void BodyAnimHeaps_ConstructSlot(unsigned char *slot);
unsigned long BodyAnimHeaps_Heap(BodyAnimHeaps *heaps, int index);
void BodyAnimHeaps_Clear(BodyAnimHeaps *heaps);
void BodyAnimHeaps_Create(BodyAnimHeaps *heaps);
void BodyAnimHeaps_Destruct(void *heaps);
void BodyAnimHeaps_Construct(void *heaps);
int BodyAnimHeaps_HeapSize(void);
void BodyAnimHeaps_EndScene(void);
void BodyAnimHeaps_StartScene(Heap *parent);

#endif
