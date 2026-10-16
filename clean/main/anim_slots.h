/* The slots the field actors' joint animation files are read into (data_021c9b58, a global
 * C++ object): 25 blocks taken from the scene's heap at data_021c9af8 when the scene starts,
 * each with the animation resource it holds and that file's size.
 *
 * Slots 0 to 8 hold body animations (resources below ANIM_SLOTS_FIRST_HELD) in blocks of
 * AnimSlots_BodyBlockSize bytes; slots 9 to 24 hold the held items' animations in smaller
 * blocks. Of each range the first four slots are the players' (data_020c75e8 gives each player
 * its body slot and its held slot), the others the scene's other actors'.
 *
 * An actor names its slots with one byte each (FIELD_ACTOR_BODY_ANIM_SET and
 * FIELD_ACTOR_HELD_ANIM_SET), ANIM_SLOTS_COUNT for none. A resource is read from
 * "/anm/<resource / 32>/<resource>.nsbca", or copied from another slot that holds it. */
#ifndef CLEAN_MAIN_ANIM_SLOTS_H
#define CLEAN_MAIN_ANIM_SLOTS_H

#include "autoload_2/heap.h"
#include "types.h"

/* The number of slots, also a slot byte's value for none and AnimSlots_Find's "not found". */
#define ANIM_SLOTS_COUNT 25
/* The body slots are 0 to ANIM_SLOTS_LAST_BODY. */
#define ANIM_SLOTS_LAST_BODY 8
#define ANIM_SLOTS_FIRST_HELD 9
/* The first resource of the held items' animations, and the resource that is none. */
#define ANIM_SLOTS_FIRST_HELD_RESOURCE 0x137
#define ANIM_SLOTS_NO_RESOURCE 0x144

typedef struct AnimSlots {
    u8 *data[ANIM_SLOTS_COUNT];     /* 0x00: the blocks */
    u16 resource[ANIM_SLOTS_COUNT]; /* 0x64: the resource each holds, ANIM_SLOTS_NO_RESOURCE */
    u16 size[ANIM_SLOTS_COUNT];     /* 0x96: its file's size, 0 when none was read */
} AnimSlots;

unsigned short AnimSlots_SlotResource(u8 *slot);
int AnimSlots_SlotData(u8 *slot);
void AnimSlots_CopySlot(u8 *slot, int from);
void AnimSlots_Load(u8 *slot, int resource, int share, int force);
void AnimSlots_SetSlot(u8 *slot, int index);
void AnimSlots_Assign(u8 *slot, int index);
void AnimSlots_DestructSlot(void *slot);
void AnimSlots_ConstructSlot(u8 *slot);
void AnimSlots_SetSize(AnimSlots *slots, int index, unsigned short size);
unsigned short AnimSlots_Size(AnimSlots *slots, int index);
int AnimSlots_Find(AnimSlots *slots, int resource);
void AnimSlots_SetResource(AnimSlots *slots, int index, unsigned short resource);
unsigned short AnimSlots_Resource(AnimSlots *slots, int index);
u8 *AnimSlots_Data(AnimSlots *slots, int index);
void AnimSlots_Clear(AnimSlots *slots);
void AnimSlots_AllocBlocks(AnimSlots *slots);
void AnimSlots_Destruct(void *slots);
void AnimSlots_Construct(AnimSlots *slots);
int AnimSlots_LastBlockSize(void);
int AnimSlots_HeldBlockSize(void);
int AnimSlots_BodyBlockSize(void);
char *AnimSlots_FilePath(unsigned int resource);
void AnimSlots_EndScene(void);
void AnimSlots_StartScene(Heap *parent);

#endif
