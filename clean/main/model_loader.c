/* The loader of a texture or a model over several frames (model_loader.h). */
#include "model_loader.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "model_cache.h"
#include "rom_file.h"
#include "vram_copy_task.h"

static_assert(offsetof(ModelLoaderTask, state) == 0x0d, "ModelLoaderTask state");
static_assert(sizeof(ModelLoaderTask) == 0x1c, "ModelLoaderTask size");
static_assert(offsetof(ModelLoader, texture) == 0x10, "ModelLoader texture");
static_assert(offsetof(ModelLoader, task) == 0x14, "ModelLoader task");
static_assert(offsetof(ModelLoader, step) == 0x30, "ModelLoader step");
static_assert(sizeof(ModelLoader) == 0x34, "ModelLoader size");

/* The loader's vtable. */
extern const u8 data_020dd10c[];

extern Heap *data_021fbe94; /* the current heap, which files are read into */

/* The model set of a model file, and the texture resource of a file. */
extern u8 *func_02107828(u8 *file);
extern void *func_021077e8(u8 *file);

extern int NNS_G3dBindMdlTex(u8 *model, void *texture);
extern int NNS_G3dBindMdlPltt(u8 *model, void *texture);

static u16 read_u16(const u8 *p)
{
    return *(const u16 *) (const void *) p;
}

static u32 read_u32(const u8 *p)
{
    return *(const u32 *) (const void *) p;
}

/* The first model of a model set: the first word of the entries of its dictionary (after the
 * dictionary's header at 8) is its offset in the set. */
static u8 *first_model(u8 *models)
{
    const u8 *entries = models + 8 + read_u16(models + 0x0e);
    return models + read_u32(entries + 4);
}

/* func_0205594c: the copy of the texture resource, once ModelLoader_StepTexture is done. */
void *ModelLoader_Texture(ModelLoader *loader)
{
    return loader->texture;
}
CLEAN_AS(func_0205594c, ModelLoader_Texture)

/* func_02055950: the copy of the model, once ModelLoader_StepModel is done. */
u8 *ModelLoader_Model(ModelLoader *loader)
{
    return loader->model;
}
CLEAN_AS(func_02055950, ModelLoader_Model)

/* func_02055954: one step of loading `texture` into `region`: first the texture is given keys
 * there and handed to the task; once the task is done, a copy of the resource is made on
 * `heap`. The step reached (MODEL_LOADER_*). */
int ModelLoader_StepTexture(ModelLoader *loader, void *texture, VramRegion *region, Heap *heap)
{
    u8 step = loader->step;
    if (step == MODEL_LOADER_DONE) {
        return step;
    }
    if (step == MODEL_LOADER_START) {
        VramRegion_PlaceTexture(region, texture);
        VramCopyTask_QueueTexture((VramCopyTask *) &loader->task, texture, 1);
        loader->step = MODEL_LOADER_SENDING;
        return loader->step;
    }
    if (step == MODEL_LOADER_SENDING) {
        if (loader->task.state != MODEL_LOADER_TASK_DONE) {
            return step;
        }
        loader->step = MODEL_LOADER_SENT;
    }
    if (loader->step == MODEL_LOADER_SENT) {
        loader->texture = ModelCache_CopyTexture(texture, heap);
        loader->step = MODEL_LOADER_DONE;
    }
    return loader->step;
}
CLEAN_AS(func_02055954, ModelLoader_StepTexture)

/* func_020559d0: one step of loading the model file at `path`: first the file is read into
 * `file_heap` (NULL: the current heap), and its texture resource is given keys in `region` and
 * handed to the task; once the task is done, the file's first model is copied to `heap`, bound
 * to the file's textures and palettes, and the file is freed. The step reached
 * (MODEL_LOADER_*).
 * QUIRK: a file that could not be read is not noticed. */
u8 ModelLoader_StepModel(ModelLoader *loader, const char *path, VramRegion *region, Heap *heap, Heap *file_heap)
{
    u8 step = loader->step;
    if (step == MODEL_LOADER_DONE) {
        return step;
    }
    if (file_heap == NULL) {
        file_heap = data_021fbe94;
    }
    if (step == MODEL_LOADER_START) {
        loader->file = RomFile_Load(path, file_heap, -4, NULL);
        loader->file_heap = file_heap;
        void *texture = func_021077e8(loader->file);
        VramRegion_PlaceTexture(region, texture);
        VramCopyTask_QueueTexture((VramCopyTask *) &loader->task, texture, 1);
        loader->step = MODEL_LOADER_SENDING;
        return loader->step;
    }
    if (step == MODEL_LOADER_SENDING) {
        if (loader->task.state != MODEL_LOADER_TASK_DONE) {
            return step;
        }
        loader->step = MODEL_LOADER_SENT;
    }
    if (loader->step == MODEL_LOADER_SENT) {
        u8 *model = first_model(func_02107828(loader->file));
        loader->model = ModelCache_CopyModel(model, heap);
        void *texture = func_021077e8(loader->file);
        NNS_G3dBindMdlTex(loader->model, texture);
        NNS_G3dBindMdlPltt(loader->model, texture);
        Heap_Free(loader->file_heap, loader->file);
        loader->file_heap = NULL;
        loader->file = NULL;
        loader->step = MODEL_LOADER_DONE;
    }
    return loader->step;
}
CLEAN_AS(func_020559d0, ModelLoader_StepModel)

/* func_02055aac: the file freed if one is held, everything forgotten (the copies are not
 * freed) and the task ended: the loader can start again. */
void ModelLoader_Release(ModelLoader *loader)
{
    if (loader->file != NULL) {
        Heap_Free(loader->file_heap, loader->file);
    }
    loader->file = NULL;
    loader->file_heap = NULL;
    loader->model = NULL;
    loader->texture = NULL;
    loader->step = MODEL_LOADER_START;
    VramCopyTask_End((VramCopyTask *) &loader->task);
}
CLEAN_AS(func_02055aac, ModelLoader_Release)

/* func_02055adc: the deleting destructor. */
ModelLoader *ModelLoader_Delete(ModelLoader *loader)
{
    loader->vtable = data_020dd10c;
    Heap_OperatorDeleteB(loader);
    return loader;
}
CLEAN_AS(func_02055adc, ModelLoader_Delete)

/* func_02055af4: the destructor. */
void ModelLoader_Destruct(ModelLoader *loader)
{
    loader->vtable = data_020dd10c;
}
CLEAN_AS(func_02055af4, ModelLoader_Destruct)

/* func_02055b00: the constructor: nothing loaded. */
ModelLoader *ModelLoader_Construct(ModelLoader *loader)
{
    loader->vtable = data_020dd10c;
    VramCopyTask_Construct((VramCopyTask *) &loader->task);
    loader->file = NULL;
    loader->file_heap = NULL;
    loader->model = NULL;
    loader->texture = NULL;
    loader->step = MODEL_LOADER_START;
    loader->unk_31 = 0;
    return loader;
}
CLEAN_AS(func_02055b00, ModelLoader_Construct)
