/* The held items' pool (held_item_pool.h). */
#include "held_item_pool.h"

#include "clean.h"
#include "model_object.h"
#include "resource_pools.h"
#include "scene_heaps.h"
#include "scene_query.h"
#include "scene_tables.h"
#include "session.h"
#include "vram_copy_task.h"
#include "c_library.h"
#include "item_info.h"
#include "rom_file.h"

/* The ModelLoaderTask.state of a task that is queued. */
#define HELD_ITEM_POOL_TASK_QUEUED 1
/* The first entry of the scene's other actors. */
#define HELD_ITEM_POOL_OTHERS 4
/* The sizes of an entry's model file buffer, of its animations' heap and of its texture's
 * VRAM: plain textures, 4x4 compressed textures, palettes. */
#define HELD_ITEM_POOL_MODEL_FILE_SIZE 3876
#define HELD_ITEM_POOL_HEAP_SIZE 2204
#define HELD_ITEM_POOL_TEXTURE_SIZE 1536
#define HELD_ITEM_POOL_TEXTURE_4X4_SIZE 0
#define HELD_ITEM_POOL_PALETTE_SIZE 80
#define HELD_ITEM_POOL_ALIGN 4
/* An animation's speed of 1.0. */
#define HELD_ITEM_POOL_SPEED_ONE 0x1000
/* What the item tables give for an item outside them: no model (the model kind), the
 * holder's animation for none, and model 0x32. */
#define HELD_ITEM_POOL_KIND_NONE 0x2b
#define HELD_ITEM_POOL_ANIM_NONE 0x144
#define HELD_ITEM_POOL_MODEL_NONE 0x32

static_assert(offsetof(HeldItemPool, heap) == 0x024, "HeldItemPool.heap");
static_assert(offsetof(HeldItemPool, joint_anim_size) == 0x06c, "HeldItemPool.joint_anim_size");
static_assert(offsetof(HeldItemPool, texture_anim) == 0x080, "HeldItemPool.texture_anim");
static_assert(offsetof(HeldItemPool, texture_anim_size) == 0x0a4, "HeldItemPool.texture_anim_size");
static_assert(offsetof(HeldItemPool, texture_anim_heap) == 0x0b8, "HeldItemPool.texture_anim_heap");
static_assert(offsetof(HeldItemPool, region) == 0x0dc, "HeldItemPool.region");
static_assert(offsetof(HeldItemPool, task) == 0x190, "HeldItemPool.task");
static_assert(offsetof(HeldItemPool, model) == 0x28c, "HeldItemPool.model");
static_assert(offsetof(HeldItemPool, material_anim) == 0xb20, "HeldItemPool.material_anim");
static_assert(offsetof(HeldItemPool, code) == 0xb44, "HeldItemPool.code");

extern HeldItemPool data_021ca16c; /* the pool */
extern Heap *data_021c9acc;        /* the animation heaps' heap (SceneHeaps_Create021c9acc) */
extern Heap *data_021c9ad8;        /* the model files' heap (SceneHeaps_Create021c9ad8) */
extern NetSession *data_020ccf94;  /* the session */

/* The tables of the items with a model, by their number (func_02062148) below
 * func_02062230: the model kind, the holder's animation and the model number. */
extern const u8 data_020cc900[];
extern const u16 data_020cc940[];
extern const u8 data_020cc8c0[];

/* The path buffers and formats: "/PItm/ItaAnm%d/%d.nsbta", "/PItm/Anm%d/%d.nsbca" and
 * "/PItm/Mdl%d/%d.nsbmd" (the number / 32, then the number). */
extern char data_021ca150[];
extern char data_021ca138[];
extern char data_021ca120[];
extern const char data_020dd768[];
extern const char data_020dd780[];
extern const char data_020dd798[];

extern void *func_021077e8(void *file); /* the file's texture resource */
/* An animation file's set of joint or texture SRT animations, and its animation `index`. */
extern void *NNS_G3dGetJntAnmSet(u8 *file);
extern void *NNS_G3dGetTexSRTAnmSet(u8 *file);
extern u8 *func_02107b44(void *set, u32 index);
extern u8 *func_02107bbc(void *set, u32 index);

/* The members' constructors and destructors, handed to __cxa_vec_ctor and __cxa_vec_cleanup:
 * the VRAM regions' (VramRegion_Construct, VramRegion_Destruct), the models'
 * (AnimatedModel_ConstructBlended, AnimatedModel_DestructBlendedComplete) and the item codes'
 * (RoomInterior_ConstructCode, TrivialObject_DestructItemCode). */
extern void *func_02055cf4(void *region);
extern void func_02055ce8(void *region);
extern void *func_02054e54(void *model);
extern void *func_02054e18(void *model);
extern void func_02034ce0(void *code);
extern void func_020051b0(void *code);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* func_0205f070: the texture of entry `index`'s model file placed in its VRAM region (its keys
 * given to the texture resource). */
void HeldItemPool_PlaceTexture(HeldItemPool *pool, int index)
{
    void *texture = func_021077e8((void *) (uintptr_t) HeldItemPool_ModelFile(pool, index));
    VramRegion_PlaceTexture(HeldItemPool_Region(pool, index), texture);
}
CLEAN_AS(func_0205f070, HeldItemPool_PlaceTexture)

/* func_0205f094: model `model`'s file read into entry `index`'s buffer, at most
 * HeldItemPool_ModelFileSize bytes; its size, 0 on failure. */
int HeldItemPool_LoadModel(HeldItemPool *pool, int index, int model)
{
    char *path = HeldItemPool_ModelPath((unsigned int) model);
    unsigned long file = HeldItemPool_ModelFile(pool, index);
    int size = HeldItemPool_ModelFileSize();
    return RomFile_Read(path, (void *) (uintptr_t) file, size);
}
CLEAN_AS(func_0205f094, HeldItemPool_LoadModel)

/* func_0205f0c0: entry `index`'s task ended when it is queued, else reset. */
void HeldItemPool_StopUpload(HeldItemPool *pool, int index)
{
    VramCopyTask *task = (VramCopyTask *) &pool->task[index];
    if (pool->task[index].state == HELD_ITEM_POOL_TASK_QUEUED) {
        VramCopyTask_End(task);
    } else {
        VramCopyTask_Reset(task);
    }
}
CLEAN_AS(func_0205f0c0, HeldItemPool_StopUpload)

/* func_0205f100 */
ItemCode *HeldItemPool_Code(HeldItemPool *pool, int index)
{
    return &pool->code[index];
}
CLEAN_AS(func_0205f100, HeldItemPool_Code)

/* func_0205f110: the material animation of the item holding entry `index`, as an address. */
int HeldItemPool_MaterialAnim(HeldItemPool *pool, int index)
{
    return (int) (uintptr_t) pool->material_anim[index];
}
CLEAN_AS(func_0205f110, HeldItemPool_MaterialAnim)

/* func_0205f120: the material animation of the item holding entry `index` (NULL when it lets
 * the entry go). The original's source declares `anim` an unsigned char, but its callers
 * (HeldItem_Setup, HeldItem_Clear) pass the item's ModelAnim or NULL and the whole word is
 * kept: it is a pointer here. */
void HeldItemPool_SetMaterialAnim(HeldItemPool *pool, int index, ModelAnim *anim)
{
    pool->material_anim[index] = anim;
}
CLEAN_AS(func_0205f120, HeldItemPool_SetMaterialAnim)

/* func_0205f130: entry `index`'s model, as an address. */
int HeldItemPool_Model(HeldItemPool *pool, int index)
{
    return (int) (uintptr_t) &pool->model[index];
}
CLEAN_AS(func_0205f130, HeldItemPool_Model)

/* func_0205f140 */
ModelLoaderTask *HeldItemPool_Task(HeldItemPool *pool, int index)
{
    return &pool->task[index];
}
CLEAN_AS(func_0205f140, HeldItemPool_Task)

/* func_0205f150 */
VramRegion *HeldItemPool_Region(HeldItemPool *pool, int index)
{
    return &pool->region[index];
}
CLEAN_AS(func_0205f150, HeldItemPool_Region)

/* func_0205f15c: texture SRT animation `number` read into entry `index`'s buffer, and its first
 * animation started (with `flags`, at speed 1.0 from frame 0) as the material animation of the
 * item holding the entry, on the entry's model.
 * QUIRK: the file is read and found in the pool at data_021ca16c, whatever `pool` is; the
 * animation and the model are `pool`'s (the callers pass data_021ca16c). */
void HeldItemPool_StartTextureAnim(HeldItemPool *pool, int index, int number, int flags)
{
    HeldItemPool_LoadTextureAnim(&data_021ca16c, index, number);
    u8 *file = (u8 *) (uintptr_t) HeldItemPool_TextureAnim(&data_021ca16c, index);
    u8 *anim_file = func_02107bbc(NNS_G3dGetTexSRTAnmSet(file), 0);
    ModelAnim *anim = (ModelAnim *) (uintptr_t) HeldItemPool_MaterialAnim(pool, index);
    AnimatedModel *model = (AnimatedModel *) (uintptr_t) HeldItemPool_Model(pool, index);
    ModelAnim_Restart(anim, ModelObject_RenderObject(&model->object), anim_file, flags, HELD_ITEM_POOL_SPEED_ONE, 0);
}
CLEAN_AS(func_0205f15c, HeldItemPool_StartTextureAnim)

/* func_0205f1bc: joint animation `action` read into entry `index`'s buffer, and its first
 * animation played by the entry's model (blended in over `blend` frames, with `flags`, at speed
 * 1.0 from frame 0).
 * QUIRK: `pool` is not used; the entry is always the one of data_021ca16c (the callers pass
 * it). */
void HeldItemPool_PlayJointAnim(HeldItemPool *pool, int index, int action, int blend, unsigned char flags)
{
    (void) pool;
    HeldItemPool_LoadJointAnim(&data_021ca16c, index, action);
    u8 *file = (u8 *) (uintptr_t) HeldItemPool_JointAnim(&data_021ca16c, index);
    u8 *anim_file = func_02107b44(NNS_G3dGetJntAnmSet(file), 0);
    AnimatedModel *model = (AnimatedModel *) (uintptr_t) HeldItemPool_Model(&data_021ca16c, index);
    AnimatedModel_Play(model, anim_file, blend, flags, HELD_ITEM_POOL_SPEED_ONE, 0, 0);
}
CLEAN_AS(func_0205f1bc, HeldItemPool_PlayJointAnim)

/* func_0205f20c: texture SRT animation file `number` read into entry `index`'s buffer, at most
 * its size; returns the room left after it (the size less what was read).
 * QUIRK: `pool` is not used; the entry is the one of data_021ca16c. */
int HeldItemPool_LoadTextureAnim(HeldItemPool *pool, int index, int number)
{
    (void) pool;
    unsigned long buffer = HeldItemPool_TextureAnim(&data_021ca16c, index);
    int size = HeldItemPool_TextureAnimSize(&data_021ca16c, index);
    char *path = HeldItemPool_TextureAnimPath((unsigned int) number);
    int read = RomFile_Read(path, (void *) (uintptr_t) buffer, size);
    return size - read;
}
CLEAN_AS(func_0205f20c, HeldItemPool_LoadTextureAnim)

/* func_0205f240: joint animation file `number` read into entry `index`'s buffer, at most its
 * size; returns the room left after it.
 * QUIRK: `pool` is not used; the entry is the one of data_021ca16c. */
int HeldItemPool_LoadJointAnim(HeldItemPool *pool, int index, int number)
{
    (void) pool;
    int buffer = HeldItemPool_JointAnim(&data_021ca16c, index);
    int size = HeldItemPool_JointAnimSize(&data_021ca16c, index);
    char *path = HeldItemPool_JointAnimPath((unsigned int) number);
    int read = RomFile_Read(path, (void *) (uintptr_t) buffer, size);
    return size - read;
}
CLEAN_AS(func_0205f240, HeldItemPool_LoadJointAnim)

/* func_0205f274: the heap of entry `index`'s material animation. */
void HeldItemPool_SetTextureAnimHeap(HeldItemPool *pool, int index, unsigned long heap)
{
    pool->texture_anim_heap[index] = (Heap *) (uintptr_t) heap;
}
CLEAN_AS(func_0205f274, HeldItemPool_SetTextureAnimHeap)

/* func_0205f280 */
unsigned long HeldItemPool_TextureAnimHeap(HeldItemPool *pool, int index)
{
    return (unsigned long) (uintptr_t) pool->texture_anim_heap[index];
}
CLEAN_AS(func_0205f280, HeldItemPool_TextureAnimHeap)

/* func_0205f28c */
unsigned short HeldItemPool_TextureAnimSize(HeldItemPool *pool, int index)
{
    return pool->texture_anim_size[index];
}
CLEAN_AS(func_0205f28c, HeldItemPool_TextureAnimSize)

/* func_0205f298: entry `index`'s texture SRT animation buffer and its size. */
void HeldItemPool_SetTextureAnim(HeldItemPool *pool, int index, int buffer, short size)
{
    pool->texture_anim[index] = (u8 *) (uintptr_t) buffer;
    pool->texture_anim_size[index] = (u16) size;
}
CLEAN_AS(func_0205f298, HeldItemPool_SetTextureAnim)

/* func_0205f2b0: entry `index`'s texture SRT animation buffer, as an address. */
unsigned long HeldItemPool_TextureAnim(HeldItemPool *pool, int index)
{
    return (unsigned long) (uintptr_t) pool->texture_anim[index];
}
CLEAN_AS(func_0205f2b0, HeldItemPool_TextureAnim)

/* func_0205f2bc */
unsigned short HeldItemPool_JointAnimSize(HeldItemPool *pool, int index)
{
    return pool->joint_anim_size[index];
}
CLEAN_AS(func_0205f2bc, HeldItemPool_JointAnimSize)

/* func_0205f2c8: entry `index`'s joint animation buffer and its size. */
void HeldItemPool_SetJointAnim(HeldItemPool *pool, int index, int buffer, short size)
{
    pool->joint_anim[index] = (u8 *) (uintptr_t) buffer;
    pool->joint_anim_size[index] = (u16) size;
}
CLEAN_AS(func_0205f2c8, HeldItemPool_SetJointAnim)

/* func_0205f2e0: entry `index`'s joint animation buffer, as an address. */
int HeldItemPool_JointAnim(HeldItemPool *pool, int index)
{
    return (int) (uintptr_t) pool->joint_anim[index];
}
CLEAN_AS(func_0205f2e0, HeldItemPool_JointAnim)

/* func_0205f2e8: entry `index`'s heap, as an address. */
int HeldItemPool_Heap(HeldItemPool *pool, int index)
{
    return (int) (uintptr_t) pool->heap[index];
}
CLEAN_AS(func_0205f2e8, HeldItemPool_Heap)

/* func_0205f2f0: entry `index`'s model file buffer, as an address. */
unsigned long HeldItemPool_ModelFile(HeldItemPool *pool, int index)
{
    return (unsigned long) (uintptr_t) pool->model_file[index];
}
CLEAN_AS(func_0205f2f0, HeldItemPool_ModelFile)

/* func_0205f2f8: every entry's model released, its upload stopped, its VRAM region cleared and
 * it holds no item; every heap that was made emptied and forgotten with the entry's animation
 * buffers, their sizes and its material animation; the heaps' heap, if there is one, emptied;
 * every model file buffer forgotten; then the model files' heap, if there is one, emptied. */
void HeldItemPool_Clear(HeldItemPool *pool)
{
    for (int i = 0; i < HELD_ITEM_POOL_COUNT; i++) {
        ModelObject_Release(&pool->model[i].object);
        HeldItemPool_StopUpload(pool, i);
        VramRegion_Clear(&pool->region[i]);
        pool->code[i] = HELD_ITEM_POOL_NO_ITEM;
    }
    for (int i = 0; i < HELD_ITEM_POOL_COUNT; i++) {
        if (pool->heap[i] != NULL) {
            Heap_FreeAll(pool->heap[i]);
            pool->heap[i] = NULL;
            pool->joint_anim[i] = NULL;
            pool->joint_anim_size[i] = 0;
            pool->texture_anim[i] = NULL;
            pool->texture_anim_size[i] = 0;
            pool->material_anim[i] = NULL;
        }
    }
    if (data_021c9acc != NULL) {
        Heap_FreeAll(data_021c9acc);
    }
    for (int i = 0; i < HELD_ITEM_POOL_COUNT; i++) {
        pool->model_file[i] = NULL;
    }
    if (data_021c9ad8 != NULL) {
        Heap_FreeAll(data_021c9ad8);
    }
}
CLEAN_AS(func_0205f2f8, HeldItemPool_Clear)

/* The entries the scene uses: from 0 the smaller of the session's players and the scene's
 * second count; from HELD_ITEM_POOL_OTHERS the scene's first count and heaps less that number
 * (less 1 when it is 0), as the face animation heaps (FaceAnimHeaps_Create). */
static unsigned int held_item_pool_players(void)
{
    unsigned int players = data_020ccf94->player_count;
    unsigned int second = SceneTables_SecondCount(SceneQuery_Current());
    return second < players ? second : players;
}

static unsigned int held_item_pool_others(unsigned int players)
{
    unsigned int at_least_one = players != 0 ? players : 1;
    unsigned int first = SceneTables_FirstCount(SceneQuery_Current());
    return first + (unsigned int) ResourcePools_SceneHeapCount() - at_least_one;
}

/* func_0205f3b4: the animation heaps of the entries the scene uses, frame heaps of
 * HeldItemPool_HeapSize bytes made in the heap at data_021c9acc.
 * REQUIRES: players <= 4 and others <= 5, as the scenes give; no entry's range is checked. */
void HeldItemPool_CreateHeaps(HeldItemPool *pool)
{
    Heap *parent = data_021c9acc;
    unsigned int players = held_item_pool_players();
    for (unsigned int i = 0; i < players; i++) {
        pool->heap[i] = FrameHeap_Create(HeldItemPool_HeapSize(), parent);
    }
    unsigned int others = held_item_pool_others(players);
    for (unsigned int i = HELD_ITEM_POOL_OTHERS; i < others + HELD_ITEM_POOL_OTHERS; i++) {
        pool->heap[i] = FrameHeap_Create(HeldItemPool_HeapSize(), parent);
    }
}
CLEAN_AS(func_0205f3b4, HeldItemPool_CreateHeaps)

/* func_0205f434: for the entries the scene uses, the VRAM regions allocated, then the model
 * file buffers taken from the heap at data_021c9ad8.
 * REQUIRES: players <= 4 and others <= 5, as the scenes give; no entry's range is checked. */
void HeldItemPool_AllocEntries(HeldItemPool *pool)
{
    unsigned int players = held_item_pool_players();
    unsigned int others = held_item_pool_others(players);
    for (unsigned int i = 0; i < players; i++) {
        u32 texture_size = (u32) HeldItemPool_TextureSize();
        u32 texture_4x4_size = (u32) HeldItemPool_Texture4x4Size();
        u32 palette_size = (u32) HeldItemPool_PaletteSize();
        VramRegion_Alloc(&pool->region[i], texture_size, texture_4x4_size, palette_size);
    }
    for (unsigned int i = HELD_ITEM_POOL_OTHERS; i < others + HELD_ITEM_POOL_OTHERS; i++) {
        u32 texture_size = (u32) HeldItemPool_TextureSize();
        u32 texture_4x4_size = (u32) HeldItemPool_Texture4x4Size();
        u32 palette_size = (u32) HeldItemPool_PaletteSize();
        VramRegion_Alloc(&pool->region[i], texture_size, texture_4x4_size, palette_size);
    }
    Heap *heap = data_021c9ad8;
    for (unsigned int i = 0; i < players; i++) {
        pool->model_file[i] = Heap_AllocAligned(heap, HeldItemPool_ModelFileSize(), HELD_ITEM_POOL_ALIGN);
    }
    for (unsigned int i = HELD_ITEM_POOL_OTHERS; i < others + HELD_ITEM_POOL_OTHERS; i++) {
        pool->model_file[i] = Heap_AllocAligned(heap, HeldItemPool_ModelFileSize(), HELD_ITEM_POOL_ALIGN);
    }
}
CLEAN_AS(func_0205f434, HeldItemPool_AllocEntries)

/* func_0205f524: the pool's destructor: the item codes, the models and the VRAM regions
 * destroyed. Returns the pool. */
HeldItemPool *HeldItemPool_Destruct(HeldItemPool *pool)
{
    __cxa_vec_cleanup(pool->code, HELD_ITEM_POOL_COUNT, sizeof(ItemCode), func_020051b0);
    __cxa_vec_cleanup(pool->model, HELD_ITEM_POOL_COUNT, sizeof(AnimatedModel), (void (*)(void *))(uintptr_t) func_02054e18);
    __cxa_vec_cleanup(pool->region, HELD_ITEM_POOL_COUNT, sizeof(VramRegion), func_02055ce8);
    return pool;
}
CLEAN_AS(func_0205f524, HeldItemPool_Destruct)

/* func_0205f570: the pool's constructor: the VRAM regions, the tasks, the models and the item
 * codes. Returns the pool. */
HeldItemPool *HeldItemPool_Construct(HeldItemPool *pool)
{
    __cxa_vec_ctor(pool->region, HELD_ITEM_POOL_COUNT, sizeof(VramRegion), (void (*)(void *))(uintptr_t) func_02055cf4,
                   func_02055ce8);
    for (int i = 0; i < HELD_ITEM_POOL_COUNT; i++) {
        VramCopyTask_Construct((VramCopyTask *) &pool->task[i]);
    }
    __cxa_vec_ctor(pool->model, HELD_ITEM_POOL_COUNT, sizeof(AnimatedModel), (void (*)(void *))(uintptr_t) func_02054e54,
                   (void (*)(void *))(uintptr_t) func_02054e18);
    __cxa_vec_ctor(pool->code, HELD_ITEM_POOL_COUNT, sizeof(ItemCode), func_02034ce0, func_020051b0);
    return pool;
}
CLEAN_AS(func_0205f570, HeldItemPool_Construct)

/* func_0205f5ec: the path of texture SRT animation file `number`, written into one shared
 * buffer (each call overwrites the last one's path). */
char *HeldItemPool_TextureAnimPath(unsigned int number)
{
    CLib_SPrintf(data_021ca150, data_020dd768, number >> 5, number);
    return data_021ca150;
}
CLEAN_AS(func_0205f5ec, HeldItemPool_TextureAnimPath)

/* func_0205f60c: the path of joint animation file `number`, in one shared buffer. */
char *HeldItemPool_JointAnimPath(unsigned int number)
{
    CLib_SPrintf(data_021ca138, data_020dd780, number >> 5, number);
    return data_021ca138;
}
CLEAN_AS(func_0205f60c, HeldItemPool_JointAnimPath)

/* func_0205f62c */
int HeldItemPool_PaletteSize(void)
{
    return HELD_ITEM_POOL_PALETTE_SIZE;
}
CLEAN_AS(func_0205f62c, HeldItemPool_PaletteSize)

/* func_0205f630 */
int HeldItemPool_Texture4x4Size(void)
{
    return HELD_ITEM_POOL_TEXTURE_4X4_SIZE;
}
CLEAN_AS(func_0205f630, HeldItemPool_Texture4x4Size)

/* func_0205f634 */
int HeldItemPool_TextureSize(void)
{
    return HELD_ITEM_POOL_TEXTURE_SIZE;
}
CLEAN_AS(func_0205f634, HeldItemPool_TextureSize)

/* func_0205f63c */
int HeldItemPool_HeapSize(void)
{
    return HELD_ITEM_POOL_HEAP_SIZE;
}
CLEAN_AS(func_0205f63c, HeldItemPool_HeapSize)

/* func_0205f644 */
int HeldItemPool_ModelFileSize(void)
{
    return HELD_ITEM_POOL_MODEL_FILE_SIZE;
}
CLEAN_AS(func_0205f644, HeldItemPool_ModelFileSize)

/* func_0205f64c: the item's model kind (HELD_ITEM_POOL_KIND_NONE for an item without a
 * model). */
int HeldItemPool_ModelKind(ItemCode *item)
{
    unsigned int number = ItemInfo_HeldModelNumber(item);
    if (number < ItemInfo_HeldModelCount()) {
        return data_020cc900[number];
    }
    return HELD_ITEM_POOL_KIND_NONE;
}
CLEAN_AS(func_0205f64c, HeldItemPool_ModelKind)

/* func_0205f670: the animation the holder plays with the item (HELD_ITEM_POOL_ANIM_NONE for
 * none). */
unsigned int HeldItemPool_ItemAnim(ItemCode *item)
{
    unsigned int number = ItemInfo_HeldModelNumber(item);
    if (number < ItemInfo_HeldModelCount()) {
        return data_020cc940[number];
    }
    return HELD_ITEM_POOL_ANIM_NONE;
}
CLEAN_AS(func_0205f670, HeldItemPool_ItemAnim)

/* func_0205f698: the item's model number (HELD_ITEM_POOL_MODEL_NONE outside the table). */
unsigned char HeldItemPool_ModelNumber(ItemCode *item)
{
    unsigned int number = ItemInfo_HeldModelNumber(item);
    if (number < ItemInfo_HeldModelCount()) {
        return data_020cc8c0[number];
    }
    return HELD_ITEM_POOL_MODEL_NONE;
}
CLEAN_AS(func_0205f698, HeldItemPool_ModelNumber)

/* func_0205f6bc: the path of model file `model`, in one shared buffer. */
char *HeldItemPool_ModelPath(unsigned int model)
{
    CLib_SPrintf(data_021ca120, data_020dd798, model >> 5, model);
    return data_021ca120;
}
CLEAN_AS(func_0205f6bc, HeldItemPool_ModelPath)

/* func_0205f6dc: when the scene ends, the pool cleared and its two heaps destroyed. */
void HeldItemPool_EndScene(void)
{
    HeldItemPool_Clear(&data_021ca16c);
    SceneHeaps_Destroy021c9acc();
    SceneHeaps_Destroy021c9ad8();
}
CLEAN_AS(func_0205f6dc, HeldItemPool_EndScene)

/* func_0205f6f8: when the scene starts, the model files' heap made from `parent`, the entries
 * allocated and the heap, if made, shrunk to them; then the animation heaps' heap made, the
 * entries' heaps made in it and it, if made, shrunk to them. */
void HeldItemPool_StartScene(Heap *parent)
{
    SceneHeaps_Create021c9ad8(parent);
    HeldItemPool_AllocEntries(&data_021ca16c);
    Heap *files = data_021c9ad8;
    if (files != NULL) {
        Heap_Adjust(files);
    }
    SceneHeaps_Create021c9acc(parent);
    HeldItemPool_CreateHeaps(&data_021ca16c);
    Heap *heaps = data_021c9acc;
    if (heaps != NULL) {
        Heap_Adjust(heaps);
    }
}
CLEAN_AS(func_0205f6f8, HeldItemPool_StartScene)
