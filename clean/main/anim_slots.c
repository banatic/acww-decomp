/* The slots of the field actors' joint animation files (anim_slots.h). */
#include "anim_slots.h"

#include "clean.h"
#include "resource_pools.h"
#include "scene_heaps.h"
#include "scene_query.h"
#include "scene_tables.h"
#include "session.h"
#include "c_library.h"
#include "rom_file.h"

/* The sizes of a body slot's block and of a held slot's (both ranges of the held slots). */
#define ANIM_SLOTS_BODY_BLOCK_SIZE 5568
#define ANIM_SLOTS_HELD_BLOCK_SIZE 624
/* The players' slots come first in each range: body slots 0 to 3, held slots 9 to 12; the
 * other actors' start at 4, 13 and 18. */
#define ANIM_SLOTS_OTHER_BODY 4
#define ANIM_SLOTS_OTHER_HELD 13
#define ANIM_SLOTS_OTHER_LAST 18
/* The blocks' alignment. */
#define ANIM_SLOTS_ALIGN 4

extern AnimSlots data_021c9b58;    /* the slots */
extern Heap *data_021c9af8;        /* their blocks' heap (SceneHeaps_Create021c9af8) */
extern NetSession *data_020ccf94;  /* the session */
extern char data_021c9b44[20];     /* the path AnimSlots_FilePath makes */
extern const char data_020dd6ac[]; /* "/anm/%d/%d.nsbca" */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* func_0205cb80: the resource the slot `slot` names holds. */
unsigned short AnimSlots_SlotResource(u8 *slot)
{
    return AnimSlots_Resource(&data_021c9b58, *slot);
}
CLEAN_AS(func_0205cb80, AnimSlots_SlotResource)

/* func_0205cb94: the block of the slot `slot` names, as an address. */
int AnimSlots_SlotData(u8 *slot)
{
    return (int) (uintptr_t) AnimSlots_Data(&data_021c9b58, *slot);
}
CLEAN_AS(func_0205cb94, AnimSlots_SlotData)

/* func_0205cba8: the file slot `from` holds copied into the slot `slot` names, with its
 * resource and size, unless they are the same slot, already hold the same resource, `from`
 * has no file read, or either has no block. */
void AnimSlots_CopySlot(u8 *slot, int from)
{
    int to = *slot;
    if (from == to) {
        return;
    }
    unsigned short resource = AnimSlots_Resource(&data_021c9b58, from);
    if (resource == AnimSlots_Resource(&data_021c9b58, to)) {
        return;
    }
    unsigned short size = AnimSlots_Size(&data_021c9b58, from);
    if (size == 0) {
        return;
    }
    u8 *source = AnimSlots_Data(&data_021c9b58, from);
    u8 *target = AnimSlots_Data(&data_021c9b58, to);
    if (source == NULL || target == NULL) {
        return;
    }
    MI_CpuCopy8(source, target, size);
    AnimSlots_SetResource(&data_021c9b58, to, resource);
    AnimSlots_SetSize(&data_021c9b58, to, size);
}
CLEAN_AS(func_0205cba8, AnimSlots_CopySlot)

/* func_0205cc1c: puts `resource` in the slot `slot` names. ANIM_SLOTS_NO_RESOURCE or above
 * empties the slot (its resource none, its size 0). Otherwise nothing happens when the slot
 * already holds it, unless `force`; with `share`, a slot of its range that holds it already is
 * copied (AnimSlots_CopySlot); else its file is read into the slot's block, and the slot takes
 * the resource and the size read when the read succeeds.
 *
 * QUIRK: the slots 18 to 24 are read with AnimSlots_HeldBlockSize as the limit, not
 * AnimSlots_LastBlockSize that their blocks were allocated with; the two are equal. */
void AnimSlots_Load(u8 *slot, int resource, int share, int force)
{
    int index = *slot;
    if (resource >= ANIM_SLOTS_NO_RESOURCE) {
        AnimSlots_SetResource(&data_021c9b58, index, ANIM_SLOTS_NO_RESOURCE);
        AnimSlots_SetSize(&data_021c9b58, index, 0);
        return;
    }
    if (!force && resource == AnimSlots_Resource(&data_021c9b58, index)) {
        return;
    }
    if (share) {
        int holder = AnimSlots_Find(&data_021c9b58, resource);
        if (holder != ANIM_SLOTS_COUNT) {
            AnimSlots_CopySlot(slot, holder);
            return;
        }
    }

    u8 *block = AnimSlots_Data(&data_021c9b58, index);
    int limit = index > ANIM_SLOTS_LAST_BODY ? AnimSlots_HeldBlockSize() : AnimSlots_BodyBlockSize();
    int size = RomFile_Read(AnimSlots_FilePath((unsigned int) resource), block, limit);
    if (size == 0) {
        return;
    }
    AnimSlots_SetResource(&data_021c9b58, index, (unsigned short) resource);
    AnimSlots_SetSize(&data_021c9b58, index, (unsigned short) size);
}
CLEAN_AS(func_0205cc1c, AnimSlots_Load)

/* func_0205ccc0: the slot byte set to name slot `index`. */
void AnimSlots_SetSlot(u8 *slot, int index)
{
    *slot = (u8) index;
}
CLEAN_AS(func_0205ccc0, AnimSlots_SetSlot)

/* func_0205ccc4: the slot byte set to name slot `index`, and that slot emptied. */
void AnimSlots_Assign(u8 *slot, int index)
{
    AnimSlots_SetSlot(slot, index);
    AnimSlots_Load(slot, ANIM_SLOTS_NO_RESOURCE, 0, 0);
}
CLEAN_AS(func_0205ccc4, AnimSlots_Assign)

/* func_0205cce4: a slot byte's destructor, which does nothing. */
void AnimSlots_DestructSlot(void *slot)
{
    (void) slot;
}
CLEAN_AS(func_0205cce4, AnimSlots_DestructSlot)

/* func_0205cce8: a slot byte's constructor: it names none. */
void AnimSlots_ConstructSlot(u8 *slot)
{
    *slot = ANIM_SLOTS_COUNT;
}
CLEAN_AS(func_0205cce8, AnimSlots_ConstructSlot)

/* func_0205ccf0 */
void AnimSlots_SetSize(AnimSlots *slots, int index, unsigned short size)
{
    slots->size[index] = size;
}
CLEAN_AS(func_0205ccf0, AnimSlots_SetSize)

/* func_0205ccfc */
unsigned short AnimSlots_Size(AnimSlots *slots, int index)
{
    return slots->size[index];
}
CLEAN_AS(func_0205ccfc, AnimSlots_Size)

/* func_0205cd08: the first slot of the resource's range (the body slots for a body animation,
 * the held slots else) that holds `resource`; ANIM_SLOTS_COUNT when none does. */
int AnimSlots_Find(AnimSlots *slots, int resource)
{
    int first = 0;
    int end = ANIM_SLOTS_LAST_BODY + 1;
    if (resource >= ANIM_SLOTS_FIRST_HELD_RESOURCE) {
        first = ANIM_SLOTS_FIRST_HELD;
        end = ANIM_SLOTS_COUNT;
    }
    for (int i = first; i < end; i++) {
        if (slots->resource[i] == resource) {
            return i;
        }
    }
    return ANIM_SLOTS_COUNT;
}
CLEAN_AS(func_0205cd08, AnimSlots_Find)

/* func_0205cd40 */
void AnimSlots_SetResource(AnimSlots *slots, int index, unsigned short resource)
{
    slots->resource[index] = resource;
}
CLEAN_AS(func_0205cd40, AnimSlots_SetResource)

/* func_0205cd4c */
unsigned short AnimSlots_Resource(AnimSlots *slots, int index)
{
    return slots->resource[index];
}
CLEAN_AS(func_0205cd4c, AnimSlots_Resource)

/* func_0205cd58 */
u8 *AnimSlots_Data(AnimSlots *slots, int index)
{
    return slots->data[index];
}
CLEAN_AS(func_0205cd58, AnimSlots_Data)

/* func_0205cd60: every slot without a block, a resource or a size; then the blocks' heap, if
 * there is one, emptied. */
void AnimSlots_Clear(AnimSlots *slots)
{
    for (int i = 0; i < ANIM_SLOTS_COUNT; i++) {
        slots->data[i] = NULL;
        slots->resource[i] = ANIM_SLOTS_NO_RESOURCE;
        slots->size[i] = 0;
    }
    Heap *heap = data_021c9af8;
    if (heap != NULL) {
        Heap_FreeAll(heap);
    }
}
CLEAN_AS(func_0205cd60, AnimSlots_Clear)

/* func_0205cda0: the blocks the scene uses, from the heap at data_021c9af8. With `players` the
 * smaller of the session's players and the scene's second count, and `others` the scene's
 * first count and heaps less `players` (less 1 when `players` is 0): body slots and held slots
 * for `players` from 0 and from 9, and for `others` from 4, from 13 and from 18 (the last of
 * AnimSlots_LastBlockSize bytes). The same counts sized the heap (SceneHeaps_Create021c9af8).
 * REQUIRES: players <= 4 and others <= 5, as the scenes give; no slot's range is checked. */
void AnimSlots_AllocBlocks(AnimSlots *slots)
{
    Heap *heap = data_021c9af8;
    u32 players = data_020ccf94->player_count;
    u32 second = SceneTables_SecondCount(SceneQuery_Current());
    if (second < players) {
        players = second;
    }
    u32 at_least_one = players != 0 ? players : 1;
    u32 first = SceneTables_FirstCount(SceneQuery_Current());
    u32 others = first + (u32) ResourcePools_SceneHeapCount() - at_least_one;
    int body_size = AnimSlots_BodyBlockSize();
    int held_size = AnimSlots_HeldBlockSize();
    int last_size = AnimSlots_LastBlockSize();

    for (u32 i = 0; i < players; i++) {
        slots->data[i] = Heap_AllocAligned(heap, body_size, ANIM_SLOTS_ALIGN);
    }
    for (u32 i = ANIM_SLOTS_OTHER_BODY; i < others + ANIM_SLOTS_OTHER_BODY; i++) {
        slots->data[i] = Heap_AllocAligned(heap, body_size, ANIM_SLOTS_ALIGN);
    }
    for (u32 i = ANIM_SLOTS_FIRST_HELD; i < players + ANIM_SLOTS_FIRST_HELD; i++) {
        slots->data[i] = Heap_AllocAligned(heap, held_size, ANIM_SLOTS_ALIGN);
    }
    for (u32 i = ANIM_SLOTS_OTHER_HELD; i < others + ANIM_SLOTS_OTHER_HELD; i++) {
        slots->data[i] = Heap_AllocAligned(heap, held_size, ANIM_SLOTS_ALIGN);
    }
    for (u32 i = ANIM_SLOTS_OTHER_LAST; i < others + ANIM_SLOTS_OTHER_LAST; i++) {
        slots->data[i] = Heap_AllocAligned(heap, last_size, ANIM_SLOTS_ALIGN);
    }
}
CLEAN_AS(func_0205cda0, AnimSlots_AllocBlocks)

/* func_0205ce94: the slots' destructor (registered by __sinit_020c5808), which does nothing. */
void AnimSlots_Destruct(void *slots)
{
    (void) slots;
}
CLEAN_AS(func_0205ce94, AnimSlots_Destruct)

/* func_0205ce98: the slots' constructor (__sinit_020c5808): every slot's resource none. */
void AnimSlots_Construct(AnimSlots *slots)
{
    for (int i = 0; i < ANIM_SLOTS_COUNT; i++) {
        slots->resource[i] = ANIM_SLOTS_NO_RESOURCE;
    }
}
CLEAN_AS(func_0205ce98, AnimSlots_Construct)

/* func_0205cf34: the block size of the slots 18 to 24. */
int AnimSlots_LastBlockSize(void)
{
    return ANIM_SLOTS_HELD_BLOCK_SIZE;
}
CLEAN_AS(func_0205cf34, AnimSlots_LastBlockSize)

/* func_0205cf3c: the block size of the held slots. */
int AnimSlots_HeldBlockSize(void)
{
    return ANIM_SLOTS_HELD_BLOCK_SIZE;
}
CLEAN_AS(func_0205cf3c, AnimSlots_HeldBlockSize)

/* func_0205cf44: the block size of the body slots. */
int AnimSlots_BodyBlockSize(void)
{
    return ANIM_SLOTS_BODY_BLOCK_SIZE;
}
CLEAN_AS(func_0205cf44, AnimSlots_BodyBlockSize)

/* func_0205cf4c: the path of the resource's file, in the buffer at data_021c9b44. */
char *AnimSlots_FilePath(unsigned int resource)
{
    CLib_SPrintf(data_021c9b44, data_020dd6ac, resource >> 5, resource);
    return data_021c9b44;
}
CLEAN_AS(func_0205cf4c, AnimSlots_FilePath)

/* func_0205cf6c: when the scene ends, the slots emptied and their heap destroyed. */
void AnimSlots_EndScene(void)
{
    AnimSlots_Clear(&data_021c9b58);
    SceneHeaps_Destroy021c9af8();
}
CLEAN_AS(func_0205cf6c, AnimSlots_EndScene)

/* func_0205cf84: when the scene starts, the slots' heap made from `parent`, their blocks
 * allocated, and the heap, if made, shrunk to them. */
void AnimSlots_StartScene(Heap *parent)
{
    SceneHeaps_Create021c9af8(parent);
    AnimSlots_AllocBlocks(&data_021c9b58);
    Heap *heap = data_021c9af8;
    if (heap != NULL) {
        Heap_Adjust(heap);
    }
}
CLEAN_AS(func_0205cf84, AnimSlots_StartScene)
