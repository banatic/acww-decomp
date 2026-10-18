/* Copies of texture and model resources on the shared model heap (model_cache.h). */
#include "model_cache.h"

#include "clean.h"
#include "main/model_object.h"
#include "scene_heaps.h"

static_assert(sizeof(ModelCacheEntry) == 8, "ModelCacheEntry size");

/* The shared model heap. */
extern Heap *data_021c9b2c;

/* The textures and the models recorded, and how many of each. */
extern int data_021c8ca4;
extern ModelCacheEntry data_021c8cac[MODEL_CACHE_TEXTURES];
extern int data_021c8ca8;
extern ModelCacheEntry data_021c8e8c[MODEL_CACHE_MODELS];

/* 0 while the player is in town, else in a building (the pockets scene, ov096, reads it the
 * same way). */
extern u8 data_020e54a8;

extern void OS_Terminate(void);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The shared model heap's size in town and in a building. */
#define MODEL_CACHE_HEAP_TOWN 0x7800
#define MODEL_CACHE_HEAP_INDOORS 0x10400

/* The bytes of a texture resource that precede its texture images (NNSG3dResTex's
 * texInfo.ofsTex). */
static u32 texture_header_size(const void *texture)
{
    return ((const u32 *) texture)[5];
}

/* The size of a model resource, its first word (NNSG3dResMdl's size). */
static u32 model_size(const u8 *model)
{
    return *(const u32 *) (const void *) model;
}

/* func_02056160: the copy of `texture` kept under `name`; when there is none yet (or `name` is
 * MODEL_OBJECT_NO_NAME) a new copy on the shared model heap, recorded under it. The game stops
 * (OS_Terminate) when 60 textures are recorded or the heap is full. */
void *ModelCache_KeepTexture(void *texture, u32 name)
{
    Heap *heap = data_021c9b2c;
    void *copy;

    if (name != MODEL_OBJECT_NO_NAME) {
        copy = ModelCache_FindTexture(name);
        if (copy != NULL) {
            return copy;
        }
    }
    if (data_021c8ca4 >= MODEL_CACHE_TEXTURES) {
        OS_Terminate();
        return NULL;
    }
    copy = ModelCache_CopyTexture(texture, heap);
    if (copy == NULL) {
        OS_Terminate();
        return NULL;
    }
    data_021c8cac[data_021c8ca4].copy = copy;
    data_021c8cac[data_021c8ca4].name = name;
    data_021c8ca4++;
    return copy;
}
CLEAN_AS(func_02056160, ModelCache_KeepTexture)

/* func_020561cc: a copy of `texture` up to its texture images on `heap`, or NULL when the heap
 * is full. */
void *ModelCache_CopyTexture(const void *texture, Heap *heap)
{
    u32 size = texture_header_size(texture);
    void *copy = Heap_Alloc(heap, (int) size);
    if (copy == NULL) {
        return NULL;
    }
    MI_CpuCopy8(texture, copy, size);
    return copy;
}
CLEAN_AS(func_020561cc, ModelCache_CopyTexture)

/* func_020561fc: the copy of `model` kept under `name`; when there is none yet (or `name` is
 * MODEL_OBJECT_NO_NAME) a new copy on the shared model heap, recorded under it. The game stops
 * (OS_Terminate) when 150 models are recorded or the heap is full. */
u8 *ModelCache_KeepModel(u8 *model, u32 name)
{
    Heap *heap = data_021c9b2c;
    u8 *copy;

    if (name != MODEL_OBJECT_NO_NAME) {
        copy = ModelCache_FindModel(name);
        if (copy != NULL) {
            return copy;
        }
    }
    if (data_021c8ca8 >= MODEL_CACHE_MODELS) {
        OS_Terminate();
        return NULL;
    }
    copy = ModelCache_CopyModel(model, heap);
    if (copy == NULL) {
        OS_Terminate();
        return NULL;
    }
    data_021c8e8c[data_021c8ca8].copy = copy;
    data_021c8e8c[data_021c8ca8].name = name;
    data_021c8ca8++;
    return copy;
}
CLEAN_AS(func_020561fc, ModelCache_KeepModel)

/* func_02056268: a copy of the whole `model` on `heap`, or NULL when the heap is full. */
u8 *ModelCache_CopyModel(u8 *model, Heap *heap)
{
    u8 *copy = Heap_Alloc(heap, (int) model_size(model));
    if (copy == NULL) {
        return NULL;
    }
    MI_CpuCopy8(model, copy, model_size(model));
    return copy;
}
CLEAN_AS(func_02056268, ModelCache_CopyModel)

/* func_02056294: the texture copy kept under `name`, or NULL (always for
 * MODEL_OBJECT_NO_NAME). All 60 entries are searched; the unused ones have no name. */
void *ModelCache_FindTexture(u32 name)
{
    if (name == MODEL_OBJECT_NO_NAME) {
        return NULL;
    }
    for (int i = 0; i < MODEL_CACHE_TEXTURES; i++) {
        if (data_021c8cac[i].name == name) {
            return data_021c8cac[i].copy;
        }
    }
    return NULL;
}
CLEAN_AS(func_02056294, ModelCache_FindTexture)

/* func_020562cc: the model copy kept under `name`, or NULL (always for MODEL_OBJECT_NO_NAME).
 * Only the models recorded are searched. */
u8 *ModelCache_FindModel(u32 name)
{
    if (name == MODEL_OBJECT_NO_NAME) {
        return NULL;
    }
    for (int i = 0; i < data_021c8ca8; i++) {
        if (data_021c8e8c[i].name == name) {
            return data_021c8e8c[i].copy;
        }
    }
    return NULL;
}
CLEAN_AS(func_020562cc, ModelCache_FindModel)

/* func_02056310: the shared model heap freed, with every copy on it. The records are left as
 * they are; ModelCache_Init clears them. */
void ModelCache_FreeHeap(void)
{
    SceneHeaps_DestroyModelCache();
}
CLEAN_AS(func_02056310, ModelCache_FreeHeap)

/* func_02056318: every record cleared, then a new shared model heap made in the current heap:
 * 30 KB in town, 65 KB in a building. */
void ModelCache_Init(void)
{
    for (int i = 0; i < MODEL_CACHE_MODELS; i++) {
        data_021c8e8c[i].copy = NULL;
        data_021c8e8c[i].name = MODEL_OBJECT_NO_NAME;
    }
    for (int i = 0; i < MODEL_CACHE_TEXTURES; i++) {
        data_021c8cac[i].copy = NULL;
        data_021c8cac[i].name = MODEL_OBJECT_NO_NAME;
    }
    data_021c8ca8 = 0;
    data_021c8ca4 = 0;
    SceneHeaps_CreateModelCache(data_020e54a8 == 0 ? MODEL_CACHE_HEAP_TOWN : MODEL_CACHE_HEAP_INDOORS, NULL);
}
CLEAN_AS(func_02056318, ModelCache_Init)
