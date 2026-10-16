/* Copies of texture and model resources kept on the shared model heap (data_021c9b2c), which
 * a scene makes when it starts (ModelCache_Init) and frees when it ends (ModelCache_FreeHeap).
 *
 * A texture resource (NitroSystem's NNSG3dResTex) is copied up to its texture images, which go
 * to VRAM and are not kept; a model resource (NNSG3dResMdl) whole. A copy can be kept under a
 * 32-bit name, and asking again under the same name gives the copy made the first time; the
 * name MODEL_OBJECT_NO_NAME ("NULL") always makes a new copy. Up to 60 textures and 150 models
 * are recorded, names or not. */
#ifndef CLEAN_MAIN_MODEL_CACHE_H
#define CLEAN_MAIN_MODEL_CACHE_H

#include "autoload_2/heap.h"
#include "types.h"

#define MODEL_CACHE_TEXTURES 60
#define MODEL_CACHE_MODELS 150

/* A copy recorded and the name it was kept under. */
typedef struct ModelCacheEntry {
    void *copy;
    u32 name; /* MODEL_OBJECT_NO_NAME for none */
} ModelCacheEntry;

void *ModelCache_KeepTexture(void *texture, u32 name);
void *ModelCache_CopyTexture(const void *texture, Heap *heap);
u8 *ModelCache_KeepModel(u8 *model, u32 name);
u8 *ModelCache_CopyModel(u8 *model, Heap *heap);
void *ModelCache_FindTexture(u32 name);
u8 *ModelCache_FindModel(u32 name);
void ModelCache_FreeHeap(void);
void ModelCache_Init(void);

#endif
