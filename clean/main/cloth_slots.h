/* The slots the clothes' texture files are kept in (data_021c9d1c, a global C++ object): ten
 * buffers of ClothTexture_Size bytes taken from the scene's heap at data_021c9af4 when the
 * scene starts, each with the item (ItemCode) whose texture it holds, CLOTH_SLOTS_NO_ITEM for
 * none.
 *
 * Of the buffers the first four are the players' (data_020c75d0 gives each player its slot),
 * the fifth (CLOTH_SLOTS_SCRATCH) the pool's own, where a design's clothes are loaded to be
 * copied from (ClothSlots_ScratchSlot), the others the scene's other actors'.
 *
 * An actor names its slot with one byte (FIELD_ACTOR_CLOTH), CLOTH_SLOTS_COUNT for none. An
 * item's texture is loaded with ClothTexture_LoadItem, or copied from another slot that holds
 * it; a design is put into a slot's texture with ClothTexture_PutDesign. */
#ifndef CLEAN_MAIN_CLOTH_SLOTS_H
#define CLEAN_MAIN_CLOTH_SLOTS_H

#include "autoload_2/heap.h"
#include "design.h"
#include "design_assets.h" /* DesignModel */
#include "lookups.h"       /* ItemCode */
#include "types.h"

/* The number of slots, also a slot byte's value for none and ClothSlots_Find's "not found". */
#define CLOTH_SLOTS_COUNT 10
/* The slot whose byte the pool keeps itself. */
#define CLOTH_SLOTS_SCRATCH 4
/* The item of a slot that holds none. */
#define CLOTH_SLOTS_NO_ITEM 0xfff1

typedef struct ClothSlots {
    DesignModel *file[CLOTH_SLOTS_COUNT]; /* 0x00: the buffers */
    ItemCode item[CLOTH_SLOTS_COUNT];     /* 0x28: the item each holds */
    u8 scratch;                           /* 0x3c: the pool's own slot byte */
} ClothSlots;

int ClothSlots_SlotFile(unsigned char *slot);
void ClothSlots_CopySlot(unsigned char *slot, int from);
void ClothSlots_PutDesign(unsigned char *slot, Design *design);
void ClothSlots_Load(unsigned char *slot, ItemCode *item, u8 *player, int share, int force);
void ClothSlots_SetSlot(unsigned char *slot, int index);
void ClothSlots_ResetSlot(unsigned char *slot);
void ClothSlots_Assign(unsigned char *slot, int index);
void ClothSlots_DestructSlot(void *slot);
void ClothSlots_ConstructSlot(unsigned char *slot);
int ClothSlots_Find(ClothSlots *slots, ItemCode *item);
void ClothSlots_SetItem(ClothSlots *slots, int index, ItemCode *item);
void ClothSlots_GetItem(ItemCode *item, ClothSlots *slots, int index);
int ClothSlots_ScratchSlotOf(int slots);
unsigned long ClothSlots_File(ClothSlots *slots, int index);
void ClothSlots_Clear(ClothSlots *slots);
void ClothSlots_AllocFiles(ClothSlots *slots);
ClothSlots *ClothSlots_Destruct(ClothSlots *slots);
ClothSlots *ClothSlots_Construct(ClothSlots *slots);
int ClothSlots_ScratchSlot(void);
void ClothSlots_EndScene(void);
void ClothSlots_StartScene(Heap *parent);

#endif
