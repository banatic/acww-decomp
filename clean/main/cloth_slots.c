/* The slots of the clothes' texture files (cloth_slots.h). */
#include "cloth_slots.h"

#include "clean.h"
#include "item_code.h"
#include "item_texture.h"
#include "resource_pools.h"
#include "scene_heaps.h"
#include "scene_query.h"
#include "scene_tables.h"
#include "session.h"

/* The items made from a design, in three ranges (item_texture.h). */
#define CLOTH_SLOTS_DESIGN_A_FIRST 0x12a8
#define CLOTH_SLOTS_DESIGN_A_LAST 0x12af
#define CLOTH_SLOTS_DESIGN_B_FIRST 0x1429
#define CLOTH_SLOTS_DESIGN_B_LAST 0x1430
#define CLOTH_SLOTS_DESIGN_C_FIRST 0x13a0
#define CLOTH_SLOTS_DESIGN_C_LAST 0x13a7
/* The item a slot takes when a design is put into it. */
#define CLOTH_SLOTS_DESIGN_ITEM 0xffff
/* The buffers' alignment. */
#define CLOTH_SLOTS_ALIGN 4

static_assert(offsetof(ClothSlots, item) == 0x28, "ClothSlots.item");
static_assert(offsetof(ClothSlots, scratch) == 0x3c, "ClothSlots.scratch");

extern ClothSlots data_021c9d1c;  /* the slots */
extern Heap *data_021c9af4;       /* their buffers' heap (SceneHeaps_CreateClothTextures) */
extern NetSession *data_020ccf94; /* the session */
/* ClothSlots_PutDesign's item: a function-level static object, made on first use (bit 0 of
 * its guard word), its destructor registered with the record at data_021c9d04. */
extern ItemCode data_021c9cfc;
extern u32 data_021c9d00;
extern u8 data_021c9d04[];

/* The item codes' constructor and destructor, handed to __cxa_vec_ctor, __cxa_vec_cleanup and
 * __register_global_object (RoomInterior_ConstructCode, TrivialObject_DestructItemCode). */
extern void func_02034ce0(void *item);
extern void func_020051b0(void *item);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __register_global_object(void *object, void *destruct, void *record);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

static int cloth_slots_in(ItemCode item, ItemCode first, ItemCode last)
{
    return item >= first && item <= last;
}

/* Whether the slot holding `held` already holds `item`: the same item for an item with
 * variants (ItemCode_VariantItem), else the same code. */
static int cloth_slots_same(ItemCode *item, ItemCode *held)
{
    if (ItemCode_HasVariant(item)) {
        return ItemCode_VariantItem(item) == ItemCode_VariantItem(held);
    }
    return *item == *held;
}

static DesignModel *cloth_slots_file(int index)
{
    return (DesignModel *) (uintptr_t) ClothSlots_File(&data_021c9d1c, index);
}

/* func_0205d25c: the buffer of the slot `slot` names, as an address. */
int ClothSlots_SlotFile(unsigned char *slot)
{
    return (int) ClothSlots_File(&data_021c9d1c, *slot);
}
CLEAN_AS(func_0205d25c, ClothSlots_SlotFile)

/* func_0205d270: the texture slot `from` holds copied into the slot `slot` names, with its
 * item, unless they are the same slot, already hold the same item, or either has no buffer.
 *
 * BUG: a design's clothes were meant to be copied even when the slot holds the same item (the
 * item does not say which design it shows, as ClothSlots_Load knows), but the test asks for
 * the item to be in all three design ranges at once, which none is: the same item is never
 * copied. BUGFIX: an item of any one range is copied. */
void ClothSlots_CopySlot(unsigned char *slot, int from)
{
    int to = *slot;
    if (from == to) {
        return;
    }
    ItemCode from_item;
    ItemCode to_item;
    ClothSlots_GetItem(&from_item, &data_021c9d1c, from);
    ClothSlots_GetItem(&to_item, &data_021c9d1c, to);

#ifdef BUGFIX
    int design = cloth_slots_in(from_item, CLOTH_SLOTS_DESIGN_A_FIRST, CLOTH_SLOTS_DESIGN_A_LAST) ||
                 cloth_slots_in(from_item, CLOTH_SLOTS_DESIGN_B_FIRST, CLOTH_SLOTS_DESIGN_B_LAST) ||
                 cloth_slots_in(from_item, CLOTH_SLOTS_DESIGN_C_FIRST, CLOTH_SLOTS_DESIGN_C_LAST);
#else
    int design = cloth_slots_in(from_item, CLOTH_SLOTS_DESIGN_A_FIRST, CLOTH_SLOTS_DESIGN_A_LAST) &&
                 cloth_slots_in(from_item, CLOTH_SLOTS_DESIGN_B_FIRST, CLOTH_SLOTS_DESIGN_B_LAST) &&
                 cloth_slots_in(from_item, CLOTH_SLOTS_DESIGN_C_FIRST, CLOTH_SLOTS_DESIGN_C_LAST);
#endif
    if (!design && cloth_slots_same(&from_item, &to_item)) {
        return;
    }

    DesignModel *source = cloth_slots_file(from);
    DesignModel *target = cloth_slots_file(to);
    if (source == NULL || target == NULL) {
        return;
    }
    MI_CpuCopy8(source, target, (u32) ClothTexture_Size());
    ClothSlots_SetItem(&data_021c9d1c, to, &from_item);
}
CLEAN_AS(func_0205d270, ClothSlots_CopySlot)

/* func_0205d36c: `design` put into the texture of the slot `slot` names; when it is, the
 * slot's item becomes CLOTH_SLOTS_DESIGN_ITEM, which no item equals, so the slot is not taken
 * for another's clothes. */
void ClothSlots_PutDesign(unsigned char *slot, Design *design)
{
    int index = *slot;
    if (ClothTexture_PutDesign(cloth_slots_file(index), design)) {
        if ((data_021c9d00 & 1) == 0) {
            data_021c9cfc = CLOTH_SLOTS_DESIGN_ITEM;
            __register_global_object(&data_021c9cfc, (void *) (uintptr_t) func_020051b0, data_021c9d04);
            data_021c9d00 |= 1;
        }
        ClothSlots_SetItem(&data_021c9d1c, index, &data_021c9cfc);
    }
}
CLEAN_AS(func_0205d36c, ClothSlots_PutDesign)

/* func_0205d3d4: puts the texture of `*item` in the slot `slot` names, taking a design item's
 * design from `player`'s record (the shop's designs when NULL). CLOTH_SLOTS_NO_ITEM first
 * empties the slot's item. For an item that is not a design's: nothing happens when the slot
 * already holds it, unless `force`; with `share` a slot that holds it already is copied
 * (ClothSlots_CopySlot). Otherwise the texture is loaded into the slot's buffer, and the slot
 * takes the item when that succeeds. */
void ClothSlots_Load(unsigned char *slot, ItemCode *item, u8 *player, int share, int force)
{
    int index = *slot;
    if (*item == CLOTH_SLOTS_NO_ITEM) {
        ClothSlots_SetItem(&data_021c9d1c, index, item);
    }
    int design = cloth_slots_in(*item, CLOTH_SLOTS_DESIGN_A_FIRST, CLOTH_SLOTS_DESIGN_A_LAST) ||
                 cloth_slots_in(*item, CLOTH_SLOTS_DESIGN_B_FIRST, CLOTH_SLOTS_DESIGN_B_LAST) ||
                 cloth_slots_in(*item, CLOTH_SLOTS_DESIGN_C_FIRST, CLOTH_SLOTS_DESIGN_C_LAST);

    if (!force && !design) {
        ItemCode held;
        ClothSlots_GetItem(&held, &data_021c9d1c, index);
        if (cloth_slots_same(item, &held)) {
            return;
        }
    }
    if (share && !design) {
        int holder = ClothSlots_Find(&data_021c9d1c, item);
        if (holder != CLOTH_SLOTS_COUNT) {
            ClothSlots_CopySlot(slot, holder);
            return;
        }
    }
    if (ClothTexture_LoadItem(cloth_slots_file(index), item, player)) {
        ClothSlots_SetItem(&data_021c9d1c, index, item);
    }
}
CLEAN_AS(func_0205d3d4, ClothSlots_Load)

/* func_0205d4e4: the slot byte set to name slot `index`. */
void ClothSlots_SetSlot(unsigned char *slot, int index)
{
    *slot = (unsigned char) index;
}
CLEAN_AS(func_0205d4e4, ClothSlots_SetSlot)

/* func_0205d4e8: the slot byte set to name none. */
void ClothSlots_ResetSlot(unsigned char *slot)
{
    *slot = CLOTH_SLOTS_COUNT;
}
CLEAN_AS(func_0205d4e8, ClothSlots_ResetSlot)

/* func_0205d4f0: the slot byte set to name slot `index`, and that slot's item emptied. */
void ClothSlots_Assign(unsigned char *slot, int index)
{
    ClothSlots_SetSlot(slot, index);
    ItemCode none = CLOTH_SLOTS_NO_ITEM;
    ClothSlots_Load(slot, &none, NULL, 0, 0);
}
CLEAN_AS(func_0205d4f0, ClothSlots_Assign)

/* func_0205d51c: a slot byte's destructor, which does nothing. */
void ClothSlots_DestructSlot(void *slot)
{
    (void) slot;
}
CLEAN_AS(func_0205d51c, ClothSlots_DestructSlot)

/* func_0205d520: a slot byte's constructor: it names none. */
void ClothSlots_ConstructSlot(unsigned char *slot)
{
    *slot = CLOTH_SLOTS_COUNT;
}
CLEAN_AS(func_0205d520, ClothSlots_ConstructSlot)

/* func_0205d528: the first slot that holds `*item` (for an item with variants, the same item
 * in any variant); CLOTH_SLOTS_COUNT when none does. */
int ClothSlots_Find(ClothSlots *slots, ItemCode *item)
{
    for (int i = 0; i < CLOTH_SLOTS_COUNT; i++) {
        if (cloth_slots_same(&slots->item[i], item)) {
            return i;
        }
    }
    return CLOTH_SLOTS_COUNT;
}
CLEAN_AS(func_0205d528, ClothSlots_Find)

/* func_0205d58c */
void ClothSlots_SetItem(ClothSlots *slots, int index, ItemCode *item)
{
    slots->item[index] = *item;
}
CLEAN_AS(func_0205d58c, ClothSlots_SetItem)

/* func_0205d598 */
void ClothSlots_GetItem(ItemCode *item, ClothSlots *slots, int index)
{
    *item = slots->item[index];
}
CLEAN_AS(func_0205d598, ClothSlots_GetItem)

/* func_0205d5a4: the address of the pool's own slot byte, from the pool's address. */
int ClothSlots_ScratchSlotOf(int slots)
{
    return slots + (int) offsetof(ClothSlots, scratch);
}
CLEAN_AS(func_0205d5a4, ClothSlots_ScratchSlotOf)

/* func_0205d5a8: the slot's buffer, as an address. */
unsigned long ClothSlots_File(ClothSlots *slots, int index)
{
    return (unsigned long) (uintptr_t) slots->file[index];
}
CLEAN_AS(func_0205d5a8, ClothSlots_File)

/* func_0205d5b0: the pool's own slot byte names none, and every slot is without a buffer and
 * an item; then the buffers' heap, if there is one, emptied. */
void ClothSlots_Clear(ClothSlots *slots)
{
    ClothSlots_ResetSlot(&slots->scratch);
    for (int i = 0; i < CLOTH_SLOTS_COUNT; i++) {
        slots->file[i] = NULL;
        slots->item[i] = CLOTH_SLOTS_NO_ITEM;
    }
    Heap *heap = data_021c9af4;
    if (heap != NULL) {
        Heap_FreeAll(heap);
    }
}
CLEAN_AS(func_0205d5b0, ClothSlots_Clear)

/* func_0205d5f0: the buffers the scene uses, from the heap at data_021c9af4. With `players`
 * the smaller of the session's players and the scene's second count, and `others` the scene's
 * first count and heaps less `players` (less 1 when `players` is 0): slots from 0 for
 * `players`, the scratch slot, and slots from 5 for `others`. The same counts sized the heap
 * (SceneHeaps_CreateClothTextures). Then the pool's own byte names the scratch slot, emptied.
 * REQUIRES: players <= 4 and others <= 5, as the scenes give; no slot's range is checked. */
void ClothSlots_AllocFiles(ClothSlots *slots)
{
    Heap *heap = data_021c9af4;
    u32 players = data_020ccf94->player_count;
    u32 second = SceneTables_SecondCount(SceneQuery_Current());
    if (second < players) {
        players = second;
    }

    for (u32 i = 0; i < players; i++) {
        slots->file[i] = Heap_AllocAligned(heap, ClothTexture_Size(), CLOTH_SLOTS_ALIGN);
    }
    slots->file[CLOTH_SLOTS_SCRATCH] = Heap_AllocAligned(heap, ClothTexture_Size(), CLOTH_SLOTS_ALIGN);

    u32 at_least_one = players != 0 ? players : 1;
    u32 first = SceneTables_FirstCount(SceneQuery_Current());
    u32 others = first + (u32) ResourcePools_SceneHeapCount() - at_least_one;
    for (u32 i = CLOTH_SLOTS_SCRATCH + 1; i < others + CLOTH_SLOTS_SCRATCH + 1; i++) {
        slots->file[i] = Heap_AllocAligned(heap, ClothTexture_Size(), CLOTH_SLOTS_ALIGN);
    }

    ClothSlots_Assign(&slots->scratch, CLOTH_SLOTS_SCRATCH);
}
CLEAN_AS(func_0205d5f0, ClothSlots_AllocFiles)

/* func_0205d690: the pool's destructor (registered by its static initialiser): the pool's own
 * slot byte, then the items. Returns the pool. */
ClothSlots *ClothSlots_Destruct(ClothSlots *slots)
{
    ClothSlots_DestructSlot(&slots->scratch);
    __cxa_vec_cleanup(slots->item, CLOTH_SLOTS_COUNT, sizeof(ItemCode), func_020051b0);
    return slots;
}
CLEAN_AS(func_0205d690, ClothSlots_Destruct)

/* func_0205d6b4: the pool's constructor: the items, the pool's own slot byte (none), then
 * every slot's item none. Returns the pool. */
ClothSlots *ClothSlots_Construct(ClothSlots *slots)
{
    __cxa_vec_ctor(slots->item, CLOTH_SLOTS_COUNT, sizeof(ItemCode), func_02034ce0, func_020051b0);
    ClothSlots_ConstructSlot(&slots->scratch);
    for (int i = 0; i < CLOTH_SLOTS_COUNT; i++) {
        slots->item[i] = CLOTH_SLOTS_NO_ITEM;
    }
    return slots;
}
CLEAN_AS(func_0205d6b4, ClothSlots_Construct)

/* func_0205d6fc: the pool's own slot byte, as an address. */
int ClothSlots_ScratchSlot(void)
{
    return ClothSlots_ScratchSlotOf((int) (uintptr_t) &data_021c9d1c);
}
CLEAN_AS(func_0205d6fc, ClothSlots_ScratchSlot)

/* func_0205d70c: when the scene ends, the pool cleared and the buffers' heap destroyed. */
void ClothSlots_EndScene(void)
{
    ClothSlots_Clear(&data_021c9d1c);
    SceneHeaps_DestroyClothTextures();
}
CLEAN_AS(func_0205d70c, ClothSlots_EndScene)

/* func_0205d724: when the scene starts, the buffers' heap made from `parent`, the buffers
 * allocated, and the heap, if made, shrunk to them. */
void ClothSlots_StartScene(Heap *parent)
{
    SceneHeaps_CreateClothTextures(parent);
    ClothSlots_AllocFiles(&data_021c9d1c);
    Heap *heap = data_021c9af4;
    if (heap != NULL) {
        Heap_Adjust(heap);
    }
}
CLEAN_AS(func_0205d724, ClothSlots_StartScene)
