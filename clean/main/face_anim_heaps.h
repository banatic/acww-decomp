/* The small frame heaps the field actors' face animations are bound on (data_021c9df4, a global
 * C++ object): nine heaps of FaceAnimHeaps_HeapSize bytes made in the scene's heap at
 * data_021c9ad4 when the scene starts. As with the face animation slots (face_anim_slots.h)
 * the first four are the players', the others the scene's other actors'.
 *
 * An actor names its heap with one byte (FIELD_ACTOR_FACE_ANIM_HEAP), FACE_ANIM_HEAPS_COUNT
 * for none; a heap is emptied when an actor takes it. */
#ifndef CLEAN_MAIN_FACE_ANIM_HEAPS_H
#define CLEAN_MAIN_FACE_ANIM_HEAPS_H

#include "autoload_2/heap.h"
#include "types.h"

/* The number of heaps, also a heap byte's value for none. */
#define FACE_ANIM_HEAPS_COUNT 9

typedef struct FaceAnimHeaps {
    Heap *heap[FACE_ANIM_HEAPS_COUNT]; /* 0x00 */
} FaceAnimHeaps;

unsigned long FaceAnimHeaps_SlotHeap(unsigned char *slot);
void FaceAnimHeaps_Assign(unsigned char *slot, unsigned char index);
void FaceAnimHeaps_DestructSlot(void *slot);
void FaceAnimHeaps_ConstructSlot(unsigned char *slot);
unsigned long FaceAnimHeaps_Heap(FaceAnimHeaps *heaps, int index);
void FaceAnimHeaps_Clear(FaceAnimHeaps *heaps);
void FaceAnimHeaps_Create(FaceAnimHeaps *heaps);
void FaceAnimHeaps_Destruct(void *heaps);
void FaceAnimHeaps_Construct(void *heaps);
int FaceAnimHeaps_HeapSize(void);
void FaceAnimHeaps_EndScene(void);
void FaceAnimHeaps_StartScene(Heap *parent);

#endif
