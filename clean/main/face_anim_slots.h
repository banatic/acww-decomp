/* The slots the field actors' face animation files (texture pattern animations,
 * "/FcAnm/<number / 32>/<number>.nsbtp") are read into (data_021c9d7c, a global C++ object):
 * nine blocks taken from the scene's heap at data_021c9aec when the scene starts, each with
 * room for two animations, A in its first half and B in its second, with the number each half
 * holds and that file's size.
 *
 * An animation number belongs to one half (FaceAnimSlots_Half: the numbers below 186 to A, the
 * others to B); FACE_ANIM_SLOTS_NONE is none. Of the slots the first four are the players'
 * (data_020c75dc gives each player its slot), the others the scene's other actors'.
 *
 * An actor names its slot with one byte (FIELD_ACTOR_FACE_ANIM_SET), FACE_ANIM_SLOTS_COUNT for
 * none. An animation is read from its file, after a copy from another slot that holds it. */
#ifndef CLEAN_MAIN_FACE_ANIM_SLOTS_H
#define CLEAN_MAIN_FACE_ANIM_SLOTS_H

#include "autoload_2/heap.h"
#include "types.h"

/* The number of slots, also a slot byte's value for none and FaceAnimSlots_Find's "not
 * found". */
#define FACE_ANIM_SLOTS_COUNT 9
/* A block's halves. */
#define FACE_ANIM_SLOTS_A 0
#define FACE_ANIM_SLOTS_B 1
#define FACE_ANIM_SLOTS_HALVES 2
/* The animation number that is none (FACE_ANIM_NONE). */
#define FACE_ANIM_SLOTS_NONE 0x16f

typedef struct FaceAnimSlots {
    u8 *data[FACE_ANIM_SLOTS_COUNT];                             /* 0x00: the blocks */
    u16 size[FACE_ANIM_SLOTS_HALVES][FACE_ANIM_SLOTS_COUNT];     /* 0x24: each half's file size, 0 for none */
    u16 resource[FACE_ANIM_SLOTS_HALVES][FACE_ANIM_SLOTS_COUNT]; /* 0x48: the number each half holds */
} FaceAnimSlots;

void FaceAnimSlots_LoadPair(unsigned char *slot, int a, int b, int share, int force);
void FaceAnimSlots_Load(unsigned char *slot, int number, int share, int force);
int FaceAnimSlots_SlotDataB(unsigned char *slot);
int FaceAnimSlots_SlotDataA(unsigned char *slot);
int FaceAnimSlots_SlotData(unsigned char *slot, int half);
void FaceAnimSlots_SetSlot(unsigned char *slot, int index);
void FaceAnimSlots_Assign(unsigned char *slot, int index);
void FaceAnimSlots_DestructSlot(void *slot);
void FaceAnimSlots_ConstructSlot(unsigned char *slot);
void FaceAnimSlots_SetSize(FaceAnimSlots *slots, int index, int half, short size);
unsigned short FaceAnimSlots_Size(FaceAnimSlots *slots, int index, int half);
int FaceAnimSlots_Find(FaceAnimSlots *slots, int number);
void FaceAnimSlots_SetResource(FaceAnimSlots *slots, int index, int half, int number);
unsigned short FaceAnimSlots_Resource(FaceAnimSlots *slots, int index, int half);
int FaceAnimSlots_Data(FaceAnimSlots *slots, int index, int half);
void FaceAnimSlots_Clear(FaceAnimSlots *slots);
void FaceAnimSlots_AllocBlocks(FaceAnimSlots *slots);
void FaceAnimSlots_Destruct(void *slots);
void FaceAnimSlots_Construct(FaceAnimSlots *slots);
unsigned char FaceAnimSlots_Half(unsigned int number);
int FaceAnimSlots_BlockSize(void);
int FaceAnimSlots_HalfASize(void);
char *FaceAnimSlots_Path(unsigned int number);
void FaceAnimSlots_EndScene(void);
void FaceAnimSlots_StartScene(Heap *parent);

#endif
