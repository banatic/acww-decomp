/* A loader that takes a texture resource, or a model file's first model with its textures,
 * over several frames (a C++ class of main, vtable data_020dd10c, 0x34 bytes). The texture is
 * given keys in a VRAM region (vram_region.h), then handed to a queued task (func_020ba01c's
 * class, run in 2 KB pieces) that takes it there; once the task is done the loader keeps a
 * copy of the texture resource, or of the model bound to the texture. Each step function is
 * called once a frame until it returns MODEL_LOADER_DONE.
 *
 * The furniture models of the rooms (ov004 furniture_model.h) and the pools of model files
 * (model_pool.h) use one. */
#ifndef CLEAN_MAIN_MODEL_LOADER_H
#define CLEAN_MAIN_MODEL_LOADER_H

#include "autoload_2/heap.h"
#include "main/vram_region.h"
#include "types.h"

/* ModelLoader.step */
#define MODEL_LOADER_START 0   /* nothing started */
#define MODEL_LOADER_SENDING 1 /* the task is taking the texture to VRAM */
#define MODEL_LOADER_SENT 2    /* the task is done */
#define MODEL_LOADER_DONE 3    /* the copy is made */

/* ModelLoaderTask.state once the task is done. */
#define MODEL_LOADER_TASK_DONE 2

/* The queued task (func_020ba01c constructs it, func_020b9eec queues it, func_020b9ec4 ends
 * it), the part read here. */
typedef struct ModelLoaderTask {
    u8 unk_00[0x0d];
    u8 state; /* 0x0d: MODEL_LOADER_TASK_DONE once done */
    u8 unk_0e[0x0e];
} ModelLoaderTask;

typedef struct ModelLoader {
    const void *vtable;   /* 0x00 */
    u8 *file;             /* 0x04: the model file while it is loaded (ModelLoader_StepModel) */
    Heap *file_heap;      /* 0x08: the heap it was read into */
    u8 *model;            /* 0x0c: the copy of the model, bound to the file's textures */
    void *texture;        /* 0x10: the copy of the texture resource (ModelLoader_StepTexture) */
    ModelLoaderTask task; /* 0x14 */
    u8 step;              /* 0x30: MODEL_LOADER_* */
    u8 unk_31;            /* 0x31: cleared by the constructor */
    u8 pad_32[2];
} ModelLoader;

void *ModelLoader_Texture(ModelLoader *loader);
u8 *ModelLoader_Model(ModelLoader *loader);
int ModelLoader_StepTexture(ModelLoader *loader, void *texture, VramRegion *region, Heap *heap);
u8 ModelLoader_StepModel(ModelLoader *loader, const char *path, VramRegion *region, Heap *heap, Heap *file_heap);
void ModelLoader_Release(ModelLoader *loader);
ModelLoader *ModelLoader_Delete(ModelLoader *loader);
void ModelLoader_Destruct(ModelLoader *loader);
ModelLoader *ModelLoader_Construct(ModelLoader *loader);

#endif
