/* The slots of the field actors' face animation files (face_anim_slots.h). */
#include "face_anim_slots.h"

#include "clean.h"
#include "resource_pools.h"
#include "scene_heaps.h"
#include "scene_query.h"
#include "scene_tables.h"
#include "session.h"
#include "c_library.h"
#include "rom_file.h"

/* The first slot of the other actors. */
#define FACE_ANIM_SLOTS_OTHERS 4
/* The blocks' alignment. */
#define FACE_ANIM_SLOTS_ALIGN 4

static_assert(offsetof(FaceAnimSlots, size) == 0x24, "FaceAnimSlots.size");
static_assert(offsetof(FaceAnimSlots, resource) == 0x48, "FaceAnimSlots.resource");

extern FaceAnimSlots data_021c9d7c; /* the slots */
extern Heap *data_021c9aec;         /* their blocks' heap (SceneHeaps_Create021c9aec) */
extern NetSession *data_020ccf94;   /* the session */
extern const u8 data_020cc65c[];    /* each animation number's half */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* func_0205d74c: the slot `slot` names takes animation `a` and animation `b`
 * (FaceAnimSlots_Load with `share` and `force`). FACE_ANIM_SLOTS_NONE or above empties half A
 * for `a`, half B for `b`.
 * QUIRK: an animation other than none goes to the half its number belongs to, whichever of the
 * two it is given as. */
void FaceAnimSlots_LoadPair(unsigned char *slot, int a, int b, int share, int force)
{
    int index = *slot;
    if (a >= FACE_ANIM_SLOTS_NONE) {
        FaceAnimSlots_SetResource(&data_021c9d7c, index, FACE_ANIM_SLOTS_A, FACE_ANIM_SLOTS_NONE);
        FaceAnimSlots_SetSize(&data_021c9d7c, index, FACE_ANIM_SLOTS_A, 0);
    } else {
        FaceAnimSlots_Load(slot, a, share, force);
    }
    if (b >= FACE_ANIM_SLOTS_NONE) {
        FaceAnimSlots_SetResource(&data_021c9d7c, index, FACE_ANIM_SLOTS_B, FACE_ANIM_SLOTS_NONE);
        FaceAnimSlots_SetSize(&data_021c9d7c, index, FACE_ANIM_SLOTS_B, 0);
    } else {
        FaceAnimSlots_Load(slot, b, share, force);
    }
}
CLEAN_AS(func_0205d74c, FaceAnimSlots_LoadPair)

/* func_0205d7b8: puts animation `number` in its half of the slot `slot` names. Nothing happens
 * when the half already holds it, unless `force`. With `share`, a slot that holds it already
 * (and has its file read) is copied into the half, with its number and size. Then its file is
 * read into the half, and the half takes the number and the size read when the read succeeds.
 * QUIRK: the file is read even after a copy, over it. */
void FaceAnimSlots_Load(unsigned char *slot, int number, int share, int force)
{
    int index = *slot;
    int half = FaceAnimSlots_Half((unsigned int) number);
    if (!force && FaceAnimSlots_Resource(&data_021c9d7c, index, half) == number) {
        return;
    }
    int target = FaceAnimSlots_Data(&data_021c9d7c, index, half);
    int limit;
    if (half == FACE_ANIM_SLOTS_A) {
        limit = FaceAnimSlots_HalfASize();
    } else {
        limit = FaceAnimSlots_BlockSize() - FaceAnimSlots_HalfASize();
    }

    if (share) {
        int holder = FaceAnimSlots_Find(&data_021c9d7c, number);
        if (holder != FACE_ANIM_SLOTS_COUNT) {
            int source = FaceAnimSlots_Data(&data_021c9d7c, holder, half);
            int size = FaceAnimSlots_Size(&data_021c9d7c, holder, half);
            if (source != 0 && size != 0) {
                MI_CpuCopy8((const void *) (uintptr_t) source, (void *) (uintptr_t) target, (u32) size);
                FaceAnimSlots_SetResource(&data_021c9d7c, index, half, number);
                FaceAnimSlots_SetSize(&data_021c9d7c, index, half, (short) size);
            }
        }
    }

    int size = RomFile_Read(FaceAnimSlots_Path((unsigned int) number), (void *) (uintptr_t) target, limit);
    if (size != 0) {
        FaceAnimSlots_SetResource(&data_021c9d7c, index, half, number);
        FaceAnimSlots_SetSize(&data_021c9d7c, index, half, (short) size);
    }
}
CLEAN_AS(func_0205d7b8, FaceAnimSlots_Load)

/* func_0205d894: half B of the slot `slot` names, as an address. */
int FaceAnimSlots_SlotDataB(unsigned char *slot)
{
    return FaceAnimSlots_SlotData(slot, FACE_ANIM_SLOTS_B);
}
CLEAN_AS(func_0205d894, FaceAnimSlots_SlotDataB)

/* func_0205d8a0: half A of the slot `slot` names, as an address. */
int FaceAnimSlots_SlotDataA(unsigned char *slot)
{
    return FaceAnimSlots_SlotData(slot, FACE_ANIM_SLOTS_A);
}
CLEAN_AS(func_0205d8a0, FaceAnimSlots_SlotDataA)

/* func_0205d8ac */
int FaceAnimSlots_SlotData(unsigned char *slot, int half)
{
    return FaceAnimSlots_Data(&data_021c9d7c, *slot, half);
}
CLEAN_AS(func_0205d8ac, FaceAnimSlots_SlotData)

/* func_0205d8c0: the slot byte set to name slot `index`. */
void FaceAnimSlots_SetSlot(unsigned char *slot, int index)
{
    *slot = (unsigned char) index;
}
CLEAN_AS(func_0205d8c0, FaceAnimSlots_SetSlot)

/* func_0205d8c4: the slot byte set to name slot `index`, and that slot emptied. */
void FaceAnimSlots_Assign(unsigned char *slot, int index)
{
    FaceAnimSlots_SetSlot(slot, index);
    FaceAnimSlots_LoadPair(slot, FACE_ANIM_SLOTS_NONE, FACE_ANIM_SLOTS_NONE, 0, 0);
}
CLEAN_AS(func_0205d8c4, FaceAnimSlots_Assign)

/* func_0205d8e8: a slot byte's destructor, which does nothing. */
void FaceAnimSlots_DestructSlot(void *slot)
{
    (void) slot;
}
CLEAN_AS(func_0205d8e8, FaceAnimSlots_DestructSlot)

/* func_0205d8ec: a slot byte's constructor: it names none. */
void FaceAnimSlots_ConstructSlot(unsigned char *slot)
{
    *slot = FACE_ANIM_SLOTS_COUNT;
}
CLEAN_AS(func_0205d8ec, FaceAnimSlots_ConstructSlot)

/* func_0205d8f4 */
void FaceAnimSlots_SetSize(FaceAnimSlots *slots, int index, int half, short size)
{
    slots->size[half][index] = (u16) size;
}
CLEAN_AS(func_0205d8f4, FaceAnimSlots_SetSize)

/* func_0205d908 */
unsigned short FaceAnimSlots_Size(FaceAnimSlots *slots, int index, int half)
{
    return slots->size[half][index];
}
CLEAN_AS(func_0205d908, FaceAnimSlots_Size)

/* func_0205d918: the first slot whose half for `number` holds it; FACE_ANIM_SLOTS_COUNT when
 * none does. */
int FaceAnimSlots_Find(FaceAnimSlots *slots, int number)
{
    int half = FaceAnimSlots_Half((unsigned int) number);
    for (int i = 0; i < FACE_ANIM_SLOTS_COUNT; i++) {
        if (FaceAnimSlots_Resource(slots, i, half) == number) {
            return i;
        }
    }
    return FACE_ANIM_SLOTS_COUNT;
}
CLEAN_AS(func_0205d918, FaceAnimSlots_Find)

/* func_0205d950 */
void FaceAnimSlots_SetResource(FaceAnimSlots *slots, int index, int half, int number)
{
    slots->resource[half][index] = (u16) number;
}
CLEAN_AS(func_0205d950, FaceAnimSlots_SetResource)

/* func_0205d968 */
unsigned short FaceAnimSlots_Resource(FaceAnimSlots *slots, int index, int half)
{
    return slots->resource[half][index];
}
CLEAN_AS(func_0205d968, FaceAnimSlots_Resource)

/* func_0205d978: the half of the slot's block, as an address (half B starts func_0205dad0
 * bytes in; any half but B is taken as A). */
int FaceAnimSlots_Data(FaceAnimSlots *slots, int index, int half)
{
    int block = (int) (uintptr_t) slots->data[index];
    if (half == FACE_ANIM_SLOTS_B) {
        return block + FaceAnimSlots_HalfASize();
    }
    return block;
}
CLEAN_AS(func_0205d978, FaceAnimSlots_Data)

/* func_0205d994: every slot without a block, and both its halves without a number or a size;
 * then the blocks' heap, if there is one, emptied. */
void FaceAnimSlots_Clear(FaceAnimSlots *slots)
{
    for (int i = 0; i < FACE_ANIM_SLOTS_COUNT; i++) {
        slots->data[i] = NULL;
        for (int half = 0; half < FACE_ANIM_SLOTS_HALVES; half++) {
            slots->resource[half][i] = FACE_ANIM_SLOTS_NONE;
            slots->size[half][i] = 0;
        }
    }
    Heap *heap = data_021c9aec;
    if (heap != NULL) {
        Heap_FreeAll(heap);
    }
}
CLEAN_AS(func_0205d994, FaceAnimSlots_Clear)

/* func_0205d9ec: the blocks the scene uses, from the heap at data_021c9aec. With `players` the
 * smaller of the session's players and the scene's second count, and `others` the scene's
 * first count and heaps less `players` (less 1 when `players` is 0): slots from 0 for
 * `players` and from 4 for `others`. The same counts sized the heap
 * (SceneHeaps_Create021c9aec).
 * REQUIRES: players <= 4 and others <= 5, as the scenes give; no slot's range is checked. */
void FaceAnimSlots_AllocBlocks(FaceAnimSlots *slots)
{
    Heap *heap = data_021c9aec;
    u32 players = data_020ccf94->player_count;
    u32 second = SceneTables_SecondCount(SceneQuery_Current());
    if (second < players) {
        players = second;
    }
    for (u32 i = 0; i < players; i++) {
        slots->data[i] = Heap_AllocAligned(heap, FaceAnimSlots_BlockSize(), FACE_ANIM_SLOTS_ALIGN);
    }

    u32 at_least_one = players != 0 ? players : 1;
    u32 first = SceneTables_FirstCount(SceneQuery_Current());
    u32 others = first + (u32) ResourcePools_SceneHeapCount() - at_least_one;
    for (u32 i = FACE_ANIM_SLOTS_OTHERS; i < others + FACE_ANIM_SLOTS_OTHERS; i++) {
        slots->data[i] = Heap_AllocAligned(heap, FaceAnimSlots_BlockSize(), FACE_ANIM_SLOTS_ALIGN);
    }
}
CLEAN_AS(func_0205d9ec, FaceAnimSlots_AllocBlocks)

/* func_0205da74: the slots' destructor, which does nothing. */
void FaceAnimSlots_Destruct(void *slots)
{
    (void) slots;
}
CLEAN_AS(func_0205da74, FaceAnimSlots_Destruct)

/* func_0205da78: the slots' constructor: both halves of every slot hold none. */
void FaceAnimSlots_Construct(FaceAnimSlots *slots)
{
    for (int i = 0; i < FACE_ANIM_SLOTS_COUNT; i++) {
        for (int half = 0; half < FACE_ANIM_SLOTS_HALVES; half++) {
            slots->resource[half][i] = FACE_ANIM_SLOTS_NONE;
        }
    }
}
CLEAN_AS(func_0205da78, FaceAnimSlots_Construct)

/* func_0205daac: the half animation `number` belongs to. */
unsigned char FaceAnimSlots_Half(unsigned int number)
{
    return data_020cc65c[number];
}
CLEAN_AS(func_0205daac, FaceAnimSlots_Half)

/* The path buffer of FaceAnimSlots_Path, "/FcAnm/%d/%d.nsbtp" (the animation's number / 32,
 * then the number). */
extern char data_021c9d68[];
extern const char data_020dd6f0[];

/* The size of half A, which is where half B starts. */
#define FACE_ANIM_SLOTS_HALF_A_SIZE 280
/* What a block holds past half A: half B. */
#define FACE_ANIM_SLOTS_HALF_B_SIZE 0x118

/* func_0205dab8: a block's size, both halves. */
int FaceAnimSlots_BlockSize(void)
{
    return FaceAnimSlots_HalfASize() + FACE_ANIM_SLOTS_HALF_B_SIZE;
}
CLEAN_AS(func_0205dab8, FaceAnimSlots_BlockSize)

/* func_0205dad0 */
int FaceAnimSlots_HalfASize(void)
{
    return FACE_ANIM_SLOTS_HALF_A_SIZE;
}
CLEAN_AS(func_0205dad0, FaceAnimSlots_HalfASize)

/* func_0205dad8: the path of animation `number`'s file, written into one shared buffer (each
 * call overwrites the last one's path). */
char *FaceAnimSlots_Path(unsigned int number)
{
    CLib_SPrintf(data_021c9d68, data_020dd6f0, number >> 5, number);
    return data_021c9d68;
}
CLEAN_AS(func_0205dad8, FaceAnimSlots_Path)

/* func_0205daf8: when the scene ends, the slots cleared and the blocks' heap destroyed. */
void FaceAnimSlots_EndScene(void)
{
    FaceAnimSlots_Clear(&data_021c9d7c);
    SceneHeaps_Destroy021c9aec();
}
CLEAN_AS(func_0205daf8, FaceAnimSlots_EndScene)

/* func_0205db10: when the scene starts, the blocks' heap made from `parent`, the blocks
 * allocated, and the heap, if made, shrunk to them. */
void FaceAnimSlots_StartScene(Heap *parent)
{
    SceneHeaps_Create021c9aec(parent);
    FaceAnimSlots_AllocBlocks(&data_021c9d7c);
    Heap *heap = data_021c9aec;
    if (heap != NULL) {
        Heap_Adjust(heap);
    }
}
CLEAN_AS(func_0205db10, FaceAnimSlots_StartScene)
