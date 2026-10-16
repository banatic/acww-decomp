/* The holder of one 3D model and the model set (model_object.h). */
#include "model_object.h"

#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/design_assets.h"

static_assert(sizeof(ModelRenderObject) == 0x54, "ModelRenderObject size");
static_assert(offsetof(ModelRenderObject, joint_results) == 0x34, "ModelRenderObject joint_results");
static_assert(offsetof(ModelObject, render) == 0x08, "ModelObject render");
static_assert(offsetof(ModelObject, model) == 0x5c, "ModelObject model");
static_assert(offsetof(ModelObject, vram) == 0x94, "ModelObject vram");
static_assert(sizeof(ModelObject) == 0x9c, "ModelObject size");
static_assert(sizeof(ModelSet) == 0x10, "ModelSet size");

/* The vtables of the holder and of the model set. */
extern const u8 data_020dd03c[];
extern const u8 data_020dd04c[];

extern Heap *data_021fbe94; /* the current heap, which files are read into */
extern Heap *data_021c9b2c; /* the heap a model set is kept on when none is given */

/* A file read whole into `heap` (from its end when `align` is negative). */
extern u8 *func_02064b2c(const char *path, Heap *heap, int align, u32 *size);
/* The model set of a model file, and the texture resource of a file (NULL without one). */
extern u8 *func_02107828(u8 *file);
extern void *func_021077e8(u8 *file);
/* A texture resource given its place in VRAM (`vram` NULL: anywhere), then copied to `heap`. */
extern int func_02056064(void *texture, void *vram);
extern void *func_020561cc(void *texture, Heap *heap);
/* A model resource copied to `heap`; one copied to the shared heap and kept under `name`, or the
 * one already kept under it (MODEL_OBJECT_NO_NAME: always a new copy); the one kept under
 * `name`, or NULL. */
extern u8 *func_02056268(u8 *model, Heap *heap);
extern u8 *func_020561fc(u8 *model, u32 name);
extern u8 *func_020562cc(int name);
/* The holder's render object set up for its model; the holder given a model and a texture
 * resource bound to it; the holder's render object released (1). */
extern void func_02055f6c(ModelObject *object);
extern int func_02055f40(ModelObject *object, u8 *model, void *texture);
extern int func_02055f1c(ModelObject *object);
/* The constructor and destructor of the class the holder extends (vtable data_020dd13c). */
extern ModelObject *func_02056044(ModelObject *object);
extern void func_02055ff4(ModelObject *object);

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern int NNS_G3dBindMdlTex(u8 *model, void *texture);
extern int NNS_G3dBindMdlPltt(u8 *model, void *texture);
extern int NNS_G3dForceBindMdlTex(u8 *model, void *texture, u32 material_list, u32 texture_index);
extern int NNS_G3dForceBindMdlPltt(u8 *model, void *texture, u32 material, u32 palette);

static u16 read_u16(const u8 *p)
{
    return *(const u16 *) (const void *) p;
}

static u32 read_u32(const u8 *p)
{
    return *(const u32 *) (const void *) p;
}

/* The entries of a model set's dictionary (each a word: the model's offset in the set), after
 * the dictionary's header at 8. */
static const u8 *model_entries(const u8 *models)
{
    return models + 8 + read_u16(models + 0x0e);
}

/* The model `index` of a model set. */
static u8 *model_at(u8 *models, u32 index)
{
    const u8 *entries = model_entries(models);
    return models + read_u32(entries + read_u16(entries) * index + 4);
}

/* func_020552b0: every holder of the set released; the set then holds none. 1.
 * QUIRK: whether every holder released is computed and dropped. */
int ModelSet_Release(ModelSet *set)
{
    if (set->count == 0) {
        return 1;
    }
    int all = 1;
    for (u32 i = 0; i < set->count; i++) {
        all &= ModelObject_Release(&set->models[i]);
    }
    (void) all;
    set->count = 0;
    return 1;
}
CLEAN_AS(func_020552b0, ModelSet_Release)

/* func_020552ec: the holder of the model named `name`, or NULL.
 * QUIRK: a name of all 16 characters has no 0 and is compared on into the next one. */
ModelObject *ModelSet_Find(ModelSet *set, const char *name)
{
    u32 count = set->count;
    for (u32 i = 0; i < count; i++) {
        if (strcmp(name, set->names[i]) == 0) {
            return &set->models[i];
        }
    }
    return NULL;
}
CLEAN_AS(func_020552ec, ModelSet_Find)

/* func_02055324: every model of the model file at `path`, each copied to `heap` (NULL:
 * data_021c9b2c) in a holder of its own, with the file's texture resource placed in VRAM and
 * copied there too, and their names. 0 when the file could not be read.
 * QUIRK: allocations are not checked; holders are constructed only where the array's address
 * is not NULL, so only the first of an array that failed is skipped. */
int ModelSet_Load(ModelSet *set, const char *path, Heap *heap)
{
    if (heap == NULL) {
        heap = data_021c9b2c;
    }
    Heap *file_heap = data_021fbe94;
    u8 *file = func_02064b2c(path, file_heap, -4, NULL);
    if (file == NULL) {
        return 0;
    }
    u8 *models = func_02107828(file);
    set->count = models[9];
    u32 size = set->count * 16;
    set->names = Heap_Alloc(heap, (int) size);
    const u8 *entries = model_entries(models);
    MI_CpuCopy8(entries + read_u16(entries + 2), set->names, size);

    set->models = Heap_Alloc(heap, (int) (set->count * sizeof(ModelObject)));
    for (u32 i = 0; i < set->count; i++) {
        ModelObject *object = (ModelObject *) ((uintptr_t) set->models + i * sizeof(ModelObject));
        if (object != NULL) {
            ModelObject_Construct(object);
        }
    }

    void *texture = func_021077e8(file);
    func_02056064(texture, NULL);
    void *kept_texture = func_020561cc(texture, heap);
    for (u32 i = 0; i < set->count; i++) {
        u8 *model = func_02056268(model_at(func_02107828(file), i), heap);
        func_02055f40(&set->models[i], model, kept_texture);
    }
    Heap_Free(file_heap, file);
    return 1;
}
CLEAN_AS(func_02055324, ModelSet_Load)

/* func_02055420: the deleting destructor. */
ModelSet *ModelSet_Delete(ModelSet *set)
{
    set->vtable = data_020dd04c;
    Heap_OperatorDeleteB(set);
    return set;
}
CLEAN_AS(func_02055420, ModelSet_Delete)

/* func_02055438: the destructor. */
void ModelSet_Destruct(ModelSet *set)
{
    set->vtable = data_020dd04c;
}
CLEAN_AS(func_02055438, ModelSet_Destruct)

/* func_02055444: the constructor: no holder. */
void ModelSet_Construct(ModelSet *set)
{
    set->vtable = data_020dd04c;
    set->count = 0;
    set->models = NULL;
}
CLEAN_AS(func_02055444, ModelSet_Construct)

/* func_02055454: the render object released and the name forgotten; 1 when it was released. */
int ModelObject_Release(ModelObject *object)
{
    int released = 1;
    released &= func_02055f1c(object);
    object->name = MODEL_OBJECT_NO_NAME;
    return released;
}
CLEAN_AS(func_02055454, ModelObject_Release)

/* func_02055478: room on `heap` (NULL: the current one) for the joints' results of every node
 * (NNSG3dJntAnmResult, 0x58 bytes), which the next draw computes and keeps. 0 without room. */
int ModelObject_AllocJointResults(ModelObject *object, Heap *heap)
{
    int size = object->render.model[0x17] * 0x58; /* the model's node count */
    if (heap == NULL) {
        heap = data_021fbe94;
    }
    void *results = Heap_Alloc(heap, size);
    if (results == NULL) {
        return 0;
    }
    object->render.joint_results = results;
    object->render.flags |= MODEL_RENDER_RECORD;
    return 1;
}
CLEAN_AS(func_02055478, ModelObject_AllocJointResults)

/* func_020554b0: the holder draws the first model of a model file read already, in place, with
 * that file's textures and palettes.
 * QUIRK: unlike the loading functions, it does not check that the file has textures. */
void ModelObject_UseFileModel(ModelObject *object, u8 *file)
{
    u8 *model = model_at(func_02107828(file), 0);
    void *texture = func_021077e8(file);
    object->model = model;
    NNS_G3dBindMdlTex(object->model, texture);
    NNS_G3dBindMdlPltt(object->model, texture);
    func_02055f6c(object);
}
CLEAN_AS(func_020554b0, ModelObject_UseFileModel)

/* func_020554ec: the first model of the file at `path`, in a copy of its own, its first texture
 * and palette replaced by player `player`'s design `index`. 0 when the file could not be
 * read. */
int ModelObject_LoadWithDesign(ModelObject *object, const char *path, int player, int index)
{
    Heap *file_heap = data_021fbe94;
    u8 *file = func_02064b2c(path, file_heap, -4, NULL);
    if (file == NULL) {
        return 0;
    }
    object->model = func_020561fc(model_at(func_02107828(file), 0), MODEL_OBJECT_NO_NAME);
    DesignManager *designs = (DesignManager *) (uintptr_t) DesignManager_Get();
    void *texture = (void *) (uintptr_t) DesignManager_PlayerTexture(designs, player, index);
    NNS_G3dForceBindMdlTex(object->model, texture, 0, 0);
    NNS_G3dForceBindMdlPltt(object->model, texture, 0, 0);
    Heap_Free(file_heap, file);
    func_02055f6c(object);
    return 1;
}
CLEAN_AS(func_020554ec, ModelObject_LoadWithDesign)

/* func_0205556c: the model kept under `name` when there is one; else the holder takes the name
 * and loads the file at `path` (ModelObject_LoadFrom), which keeps its model under it. 1 when
 * the holder has its model. */
int ModelObject_LoadShared(ModelObject *object, int name, const char *path)
{
    object->model = func_020562cc(name);
    if (object->model != NULL) {
        func_02055f6c(object);
        return 1;
    }
    object->name = (u32) name;
    return ModelObject_LoadFrom(object, path, NULL, name);
}
CLEAN_AS(func_0205556c, ModelObject_LoadShared)

/* func_020555a4: ModelObject_LoadNamed without a name. */
int ModelObject_LoadWithPalettes(ModelObject *object, const char *path, Heap *heap, void *texture, void *palettes,
                                 const u32 *palette_of_material, int materials)
{
    return ModelObject_LoadNamed(object, path, heap, texture, palettes, palette_of_material, materials, MODEL_OBJECT_NO_NAME);
}
CLEAN_AS(func_020555a4, ModelObject_LoadWithPalettes)

/* func_020555c8: ModelObject_LoadFrom without a name. */
int ModelObject_Load(ModelObject *object, const char *path, Heap *heap)
{
    return ModelObject_LoadFrom(object, path, heap, MODEL_OBJECT_NO_NAME);
}
CLEAN_AS(func_020555c8, ModelObject_Load)

/* func_020555dc: the first model of the file at `path`, copied to `heap`, or without one kept
 * under `name` (func_020561fc). Its textures are `texture`'s, or else the file's own placed in
 * VRAM, if it has any; with `palettes`, material i of the first `materials` takes palette
 * palette_of_material[i] of them. 0 when the file could not be read.
 * QUIRK: without `palettes` the model's palettes are bound to nothing, not even the file's. */
int ModelObject_LoadNamed(ModelObject *object, const char *path, Heap *heap, void *texture, void *palettes,
                          const u32 *palette_of_material, int materials, u32 name)
{
    Heap *file_heap = data_021fbe94;
    u8 *file = func_02064b2c(path, file_heap, -4, NULL);
    if (file == NULL) {
        return 0;
    }
    u8 *model = model_at(func_02107828(file), 0);
    if (heap != NULL) {
        object->model = func_02056268(model, heap);
    } else {
        object->model = func_020561fc(model, name);
    }
    if (texture != NULL) {
        NNS_G3dBindMdlTex(object->model, texture);
    } else {
        void *own = func_021077e8(file);
        if (own != NULL) {
            func_02056064(own, object->vram);
            NNS_G3dBindMdlTex(object->model, own);
        }
    }
    if (palettes != NULL) {
        for (int i = 0; i < materials; i++) {
            NNS_G3dForceBindMdlPltt(object->model, palettes, (u32) i, palette_of_material[i]);
        }
    }
    Heap_Free(file_heap, file);
    func_02055f6c(object);
    return 1;
}
CLEAN_AS(func_020555dc, ModelObject_LoadNamed)

/* func_02055698: the first model of the file at `path`, copied to `heap`, or without one kept
 * under `name` (func_020561fc), with the file's textures and palettes, placed in VRAM, when it
 * has any. 0 when the file could not be read. */
int ModelObject_LoadFrom(ModelObject *object, const char *path, Heap *heap, int name)
{
    Heap *file_heap = data_021fbe94;
    u8 *file = func_02064b2c(path, file_heap, -4, NULL);
    if (file == NULL) {
        return 0;
    }
    u8 *model = model_at(func_02107828(file), 0);
    void *texture = func_021077e8(file);
    if (heap != NULL) {
        object->model = func_02056268(model, heap);
    } else {
        object->model = func_020561fc(model, (u32) name);
    }
    if (texture != NULL) {
        func_02056064(texture, object->vram);
        NNS_G3dBindMdlTex(object->model, texture);
        NNS_G3dBindMdlPltt(object->model, texture);
    }
    Heap_Free(file_heap, file);
    func_02055f6c(object);
    return 1;
}
CLEAN_AS(func_02055698, ModelObject_LoadFrom)

/* func_0205572c: the destructor (the derived classes' destructors end with it). */
ModelObject *ModelObject_Destruct(ModelObject *object)
{
    object->vtable = data_020dd03c;
    func_02055ff4(object);
    return object;
}
CLEAN_AS(func_0205572c, ModelObject_Destruct)

/* func_02055744: the deleting destructor. */
ModelObject *ModelObject_Delete(ModelObject *object)
{
    object->vtable = data_020dd03c;
    func_02055ff4(object);
    Heap_OperatorDeleteB(object);
    return object;
}
CLEAN_AS(func_02055744, ModelObject_Delete)

/* func_02055764: the complete destructor, the same as ModelObject_Destruct. */
ModelObject *ModelObject_DestructComplete(ModelObject *object)
{
    object->vtable = data_020dd03c;
    func_02055ff4(object);
    return object;
}
CLEAN_AS(func_02055764, ModelObject_DestructComplete)

/* func_0205577c: the constructor: no name. */
ModelObject *ModelObject_Construct(ModelObject *object)
{
    func_02056044(object);
    object->vtable = data_020dd03c;
    object->name = MODEL_OBJECT_NO_NAME;
    return object;
}
CLEAN_AS(func_0205577c, ModelObject_Construct)

/* func_020557a0: the same constructor, the one the derived classes' constructors start with. */
ModelObject *ModelObject_ConstructBase(ModelObject *object)
{
    func_02056044(object);
    object->vtable = data_020dd03c;
    object->name = MODEL_OBJECT_NO_NAME;
    return object;
}
CLEAN_AS(func_020557a0, ModelObject_ConstructBase)
