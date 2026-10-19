/* The holder of one 3D model and the model set (model_object.h). */
#include "model_object.h"

#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/design_assets.h"
#include "model_cache.h"
#include "rom_file.h"
#include "scene_lights.h"
#include "vram_region.h"

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

/* The model set of a model file, and the texture resource of a file (NULL without one). */
extern u8 *func_02107828(u8 *file);
extern void *func_021077e8(u8 *file);

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
    u8 *file = RomFile_Load(path, file_heap, -4, NULL);
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
    VramRegion_LoadTexture(texture, NULL);
    void *kept_texture = ModelCache_CopyTexture(texture, heap);
    for (u32 i = 0; i < set->count; i++) {
        u8 *model = ModelCache_CopyModel(model_at(func_02107828(file), i), heap);
        ModelObject_SetModelTexture(&set->models[i], model, kept_texture);
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
    released &= ModelObject_ReleaseRender(object);
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
    ModelObject_SetupRender(object);
}
CLEAN_AS(func_020554b0, ModelObject_UseFileModel)

/* func_020554ec: the first model of the file at `path`, in a copy of its own, its first texture
 * and palette replaced by player `player`'s design `index`. 0 when the file could not be
 * read. */
int ModelObject_LoadWithDesign(ModelObject *object, const char *path, int player, int index)
{
    Heap *file_heap = data_021fbe94;
    u8 *file = RomFile_Load(path, file_heap, -4, NULL);
    if (file == NULL) {
        return 0;
    }
    object->model = ModelCache_KeepModel(model_at(func_02107828(file), 0), MODEL_OBJECT_NO_NAME);
    DesignManager *designs = (DesignManager *) (uintptr_t) DesignManager_Get();
    void *texture = (void *) (uintptr_t) DesignManager_PlayerTexture(designs, player, index);
    NNS_G3dForceBindMdlTex(object->model, texture, 0, 0);
    NNS_G3dForceBindMdlPltt(object->model, texture, 0, 0);
    Heap_Free(file_heap, file);
    ModelObject_SetupRender(object);
    return 1;
}
CLEAN_AS(func_020554ec, ModelObject_LoadWithDesign)

/* func_0205556c: the model kept under `name` when there is one; else the holder takes the name
 * and loads the file at `path` (ModelObject_LoadFrom), which keeps its model under it. 1 when
 * the holder has its model. */
int ModelObject_LoadShared(ModelObject *object, int name, const char *path)
{
    object->model = ModelCache_FindModel(name);
    if (object->model != NULL) {
        ModelObject_SetupRender(object);
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
    u8 *file = RomFile_Load(path, file_heap, -4, NULL);
    if (file == NULL) {
        return 0;
    }
    u8 *model = model_at(func_02107828(file), 0);
    if (heap != NULL) {
        object->model = ModelCache_CopyModel(model, heap);
    } else {
        object->model = ModelCache_KeepModel(model, name);
    }
    if (texture != NULL) {
        NNS_G3dBindMdlTex(object->model, texture);
    } else {
        void *own = func_021077e8(file);
        if (own != NULL) {
            VramRegion_LoadTexture(own, object->vram);
            NNS_G3dBindMdlTex(object->model, own);
        }
    }
    if (palettes != NULL) {
        for (int i = 0; i < materials; i++) {
            NNS_G3dForceBindMdlPltt(object->model, palettes, (u32) i, palette_of_material[i]);
        }
    }
    Heap_Free(file_heap, file);
    ModelObject_SetupRender(object);
    return 1;
}
CLEAN_AS(func_020555dc, ModelObject_LoadNamed)

/* func_02055698: the first model of the file at `path`, copied to `heap`, or without one kept
 * under `name` (func_020561fc), with the file's textures and palettes, placed in VRAM, when it
 * has any. 0 when the file could not be read. */
int ModelObject_LoadFrom(ModelObject *object, const char *path, Heap *heap, int name)
{
    Heap *file_heap = data_021fbe94;
    u8 *file = RomFile_Load(path, file_heap, -4, NULL);
    if (file == NULL) {
        return 0;
    }
    u8 *model = model_at(func_02107828(file), 0);
    void *texture = func_021077e8(file);
    if (heap != NULL) {
        object->model = ModelCache_CopyModel(model, heap);
    } else {
        object->model = ModelCache_KeepModel(model, (u32) name);
    }
    if (texture != NULL) {
        VramRegion_LoadTexture(texture, object->vram);
        NNS_G3dBindMdlTex(object->model, texture);
        NNS_G3dBindMdlPltt(object->model, texture);
    }
    Heap_Free(file_heap, file);
    ModelObject_SetupRender(object);
    return 1;
}
CLEAN_AS(func_02055698, ModelObject_LoadFrom)

/* func_0205572c: the destructor (the derived classes' destructors end with it). */
ModelObject *ModelObject_Destruct(ModelObject *object)
{
    object->vtable = data_020dd03c;
    ModelObject_BaseDestruct(object);
    return object;
}
CLEAN_AS(func_0205572c, ModelObject_Destruct)

/* func_02055744: the deleting destructor. */
ModelObject *ModelObject_Delete(ModelObject *object)
{
    object->vtable = data_020dd03c;
    ModelObject_BaseDestruct(object);
    Heap_OperatorDeleteB(object);
    return object;
}
CLEAN_AS(func_02055744, ModelObject_Delete)

/* func_02055764: the complete destructor, the same as ModelObject_Destruct. */
ModelObject *ModelObject_DestructComplete(ModelObject *object)
{
    object->vtable = data_020dd03c;
    ModelObject_BaseDestruct(object);
    return object;
}
CLEAN_AS(func_02055764, ModelObject_DestructComplete)

/* func_0205577c: the constructor: no name. */
ModelObject *ModelObject_Construct(ModelObject *object)
{
    ModelObject_BaseConstruct(object);
    object->vtable = data_020dd03c;
    object->name = MODEL_OBJECT_NO_NAME;
    return object;
}
CLEAN_AS(func_0205577c, ModelObject_Construct)

/* func_020557a0: the same constructor, the one the derived classes' constructors start with. */
ModelObject *ModelObject_ConstructBase(ModelObject *object)
{
    ModelObject_BaseConstruct(object);
    object->vtable = data_020dd03c;
    object->name = MODEL_OBJECT_NO_NAME;
    return object;
}
CLEAN_AS(func_020557a0, ModelObject_ConstructBase)

/* The render object's parts: the class the holder extends (vtable data_020dd13c) and its own
 * base class (vtable data_020dd11c, constructor func_020563c0, destructor func_02056390). */
extern const u8 data_020dd13c[];

/* NitroSystem's G3D global state (NNS_G3dGlb, data_027e0148): word 0x1f its flags; its base
 * rotation at 0x3c (data_027e0184). */
extern u32 data_027e0148[];
extern u8 data_027e0184[];
/* The flags of NNS_G3dGlb cleared when its base rotation changes (the matrices made from it
 * are out of date). */
#define MODEL_OBJECT_GLB_BASE_CHANGED 0xa4u

/* G3dRenderObject.flags (NitroSystem's NNS_G3D_RENDEROBJ_FLAG_NOGECMD): drawing computes
 * the matrices but sends no geometry commands. */
#define MODEL_RENDER_NO_COMMANDS 0x02

/* The model's shape binary commands (SBC) read by ModelObject_DrawShapes. */
#define MODEL_SBC_OP_MASK 0x1f
#define MODEL_SBC_RET 1 /* the end */
#define MODEL_SBC_MAT 4 /* byte 1: the material of the shapes that follow */
#define MODEL_SBC_SHP 5 /* byte 1: a shape to draw */

/* The materials' polygon attributes (GX's POLYGON_ATTR): the lights used, the alpha and the
 * polygon ID. */
#define MODEL_MATERIAL_LIGHTS 0x0000000fu
#define MODEL_MATERIAL_ALPHA_SHIFT 16
#define MODEL_MATERIAL_ALPHA_KEEP 0xffe0ffffu
#define MODEL_MATERIAL_ID_SHIFT 24
#define MODEL_MATERIAL_ID_KEEP 0xc0ffffffu

/* NitroSystem's material flag that the emission color is sent (NNS_G3D_MATFLAG_EMISSION). */
#define MODEL_MATERIAL_FLAG_EMISSION 0x400

/* The joint results' matrix of node `joint` (NNS_G3dGetResultMtx: no normal matrix wanted). */
extern int NNS_G3dGetResultMtx(G3dRenderObject *render, Mtx43 *out, void *normal, int joint);
extern const Mtx43 *NNS_G3dGlbGetInvV(void);
extern void MTX_Concat43(const Mtx43 *a, const Mtx43 *b, Mtx43 *product);
extern void MTX_Identity43_(Mtx43 *mtx);
extern void MI_Copy36B(const void *src, void *dst);
extern fx32 FX_MulFunc(fx32 a, fx32 b);
/* The render object set up for `model` (NNS_G3dRenderObjInit), its hook run before a draw
 * (NNS_G3dRenderObjSetInitFunc) and drawn (NNS_G3dDraw). */
extern void func_021054e4(G3dRenderObject *render, u8 *model);
extern void func_02105294(G3dRenderObject *render, void *hook);
extern void func_01ff8ad4(G3dRenderObject *render);
extern void NNS_G3dRenderObjSetCallBack(G3dRenderObject *render, void *callback, void *at, int command, int timing);
/* NNS_G3dGlb's base translation and scale (NNS_G3dGlbSetBaseTrans, NNS_G3dGlbSetBaseScale). */
extern void func_0210581c(const Vec3 *translation);
extern void func_021057f4(const Vec3 *scale);
extern void NNS_G3dGlbFlushP(void);
extern void NNS_G3dDraw1Mat1Shp(u8 *model, u32 material, u32 shape, int send_material);
extern u32 NNS_G3dGetSbcCmdLen(const u8 *command);
extern void NNSi_G3dModifyMatFlag(u8 *model, int on, int flag);

/* The render object's pointer handed to its hooks (NNSG3dRenderObj.ptrUser, at 0x2c). */
static void **render_user(ModelObject *object)
{
    return (void **) (void *) (object->render.unk_1c + 0x10);
}

/* The base transform the holder is drawn at: a rotation, then a translation (Mtx43). */
static Mtx43 *base_transform(ModelObject *object)
{
    return (Mtx43 *) (void *) object->unk_64;
}

static const Vec3 *base_translation(ModelObject *object)
{
    return (const Vec3 *) (const void *) (object->unk_64 + 0x24);
}

/* The model's material count, and the polygon attributes of material `index` (its word 0x0c);
 * the materials are a block at the model's word 0x08 with a dictionary at 4. */
static u32 material_count(const u8 *model)
{
    return model[0x18];
}

static u32 *material_attributes(u8 *model, u32 index)
{
    u8 *materials = model + read_u32(model + 0x08);
    const u8 *entries = materials + 4 + read_u16(materials + 0x0a);
    u8 *material = materials + read_u32(entries + read_u16(entries) * index + 4);
    return (u32 *) (void *) (material + 0x0c);
}

/* func_02055d0c: the world matrix of joint `joint` as last drawn (the result matrix times the
 * inverse view), in `out`. 0 when the model keeps no results for it. */
int ModelObject_JointMatrix(ModelObject *object, Mtx43 *out, int joint)
{
    if (!NNS_G3dGetResultMtx(&object->render, out, NULL, joint)) {
        return 0;
    }
    MTX_Concat43(out, NNS_G3dGlbGetInvV(), out);
    return 1;
}
CLEAN_AS(func_02055d0c, ModelObject_JointMatrix)

/* func_02055d38: every material of the model takes `alpha` (0-31).
 * QUIRK: `alpha` is not masked: a larger one sets bits above the alpha. */
void ModelObject_SetAlpha(ModelObject *object, int alpha)
{
    u32 value = (u32) alpha << MODEL_MATERIAL_ALPHA_SHIFT;
    for (u32 i = 0; i < material_count(object->model); i++) {
        u32 *attributes = material_attributes(object->model, i);
        *attributes &= MODEL_MATERIAL_ALPHA_KEEP;
        *attributes |= value;
    }
}
CLEAN_AS(func_02055d38, ModelObject_SetAlpha)

/* func_02055d80: every material of the model takes polygon ID `id` (0-63).
 * QUIRK: `id` is not masked: a larger one sets the top bits. */
void ModelObject_SetPolygonId(ModelObject *object, int id)
{
    u32 value = (u32) id << MODEL_MATERIAL_ID_SHIFT;
    for (u32 i = 0; i < material_count(object->model); i++) {
        u32 *attributes = material_attributes(object->model, i);
        *attributes &= MODEL_MATERIAL_ID_KEEP;
        *attributes |= value;
    }
}
CLEAN_AS(func_02055d80, ModelObject_SetPolygonId)

/* func_02055dc8: `hook` (the game's function) runs before each draw, given `user`. */
void ModelObject_SetInitHook(ModelObject *object, void *hook, void *user)
{
    func_02105294(&object->render, hook);
    *render_user(object) = user;
}
CLEAN_AS(func_02055dc8, ModelObject_SetInitHook)

/* func_02055de0: `callback` (the game's function) runs at `timing` of each shape binary command
 * `command` from `at` (NULL: the start), given `user`. */
void ModelObject_SetNodeCallback(ModelObject *object, void *callback, int command, int timing, void *user, void *at)
{
    NNS_G3dRenderObjSetCallBack(&object->render, callback, at, command, timing);
    *render_user(object) = user;
}
CLEAN_AS(func_02055de0, ModelObject_SetNodeCallback)

/* func_02055e00: the render object. */
G3dRenderObject *ModelObject_RenderObject(ModelObject *object)
{
    return &object->render;
}
CLEAN_AS(func_02055e00, ModelObject_RenderObject)

/* func_02055e04: the render object drawn (at the transform already set). */
void ModelObject_DrawRender(ModelObject *object)
{
    func_01ff8ad4(&object->render);
}
CLEAN_AS(func_02055e04, ModelObject_DrawRender)

/* func_02055e10: the holder's base transform made G3D's base, with `scale` (NULL: 1.0), and
 * sent to the geometry engine. */
void ModelObject_SetBaseTransform(ModelObject *object, const Vec3 *scale)
{
    MI_Copy36B(base_transform(object), data_027e0184);
    data_027e0148[0x1f] &= ~MODEL_OBJECT_GLB_BASE_CHANGED;
    func_0210581c(base_translation(object));
    if (scale == NULL) {
        Vec3 one = {0x1000, 0x1000, 0x1000};
        func_021057f4(&one);
    } else {
        func_021057f4(scale);
    }
    NNS_G3dGlbFlushP();
}
CLEAN_AS(func_02055e10, ModelObject_SetBaseTransform)

/* func_02055e64: the render object drawn without geometry commands (the matrices only); the
 * flag stays set. */
void ModelObject_DrawWithoutCommands(ModelObject *object)
{
    object->render.flags |= MODEL_RENDER_NO_COMMANDS;
    func_01ff8ad4(&object->render);
}
CLEAN_AS(func_02055e64, ModelObject_DrawWithoutCommands)

/* func_02055e7c: the holder drawn at its base transform with `scale` (NULL: 1.0). */
void ModelObject_Draw(ModelObject *object, const Vec3 *scale)
{
    ModelObject_SetBaseTransform(object, scale);
    ModelObject_DrawRender(object);
}
CLEAN_AS(func_02055e7c, ModelObject_Draw)

/* func_02055e90: each shape of the model drawn with its material at the base transform, with
 * `scale` (NULL: 1.0) times the model's position scale, ignoring the nodes' matrices: the shape
 * binary commands are walked for their materials and shapes only.
 * REQUIRES: a material command comes before the first shape command (the original then draws
 * with whatever material number its register held). */
void ModelObject_DrawShapes(ModelObject *object, const Vec3 *scale)
{
    u8 *model = object->model;
    const u8 *command = model + read_u32(model + 0x04);
    fx32 position_scale = (fx32) read_u32(model + 0x1c);

    if (position_scale == 0x1000) {
        ModelObject_SetBaseTransform(object, scale);
    } else {
        Vec3 scaled;
        if (scale == NULL) {
            scaled.x = position_scale;
            scaled.y = position_scale;
            scaled.z = position_scale;
        } else {
            scaled.x = FX_MulFunc(scale->x, position_scale);
            scaled.y = FX_MulFunc(scale->y, position_scale);
            scaled.z = FX_MulFunc(scale->z, position_scale);
        }
        ModelObject_SetBaseTransform(object, &scaled);
    }

    u32 material = 0;
    for (;;) {
        switch (*command & MODEL_SBC_OP_MASK) {
            case MODEL_SBC_RET:
                return;
            case MODEL_SBC_MAT:
                material = command[1];
                break;
            case MODEL_SBC_SHP:
                NNS_G3dDraw1Mat1Shp(object->model, material, command[1], 1);
                break;
            default:
                break;
        }
        command += NNS_G3dGetSbcCmdLen(command);
    }
}
CLEAN_AS(func_02055e90, ModelObject_DrawShapes)

/* func_02055f1c: the render object released (ModelObject_ResetRender). 1. */
int ModelObject_ReleaseRender(ModelObject *object)
{
    ModelObject_ResetRender(object);
    return 1;
}
CLEAN_AS(func_02055f1c, ModelObject_ReleaseRender)

/* func_02055f2c: the holder draws `model`, keeping `texture` with it (not bound). 1. */
int ModelObject_SetModel(ModelObject *object, u8 *model, void *texture)
{
    object->model = model;
    object->texture = texture;
    ModelObject_SetupRender(object);
    return 1;
}
CLEAN_AS(func_02055f2c, ModelObject_SetModel)

/* func_02055f40: the holder draws `model`, with `texture`'s textures and palettes bound to it
 * when there is one. 1. */
int ModelObject_SetModelTexture(ModelObject *object, u8 *model, void *texture)
{
    object->model = model;
    object->texture = texture;
    if (object->texture != NULL) {
        NNS_G3dBindMdlTex(object->model, object->texture);
        NNS_G3dBindMdlPltt(object->model, object->texture);
    }
    ModelObject_SetupRender(object);
    return 1;
}
CLEAN_AS(func_02055f40, ModelObject_SetModelTexture)

/* func_02055f6c: the render object set up for the model; each lit material takes the lights of
 * the current scene (func_020658c4), and no material sends its emission color. */
void ModelObject_SetupRender(ModelObject *object)
{
    func_021054e4(&object->render, object->model);
    for (u32 i = 0; i < material_count(object->model); i++) {
        u32 *attributes = material_attributes(object->model, i);
        if ((*attributes & MODEL_MATERIAL_LIGHTS) != 0) {
            *attributes &= ~MODEL_MATERIAL_LIGHTS;
            *attributes |= SceneLights_MaterialLights();
        }
    }
    NNSi_G3dModifyMatFlag(object->model, 0, MODEL_MATERIAL_FLAG_EMISSION);
}
CLEAN_AS(func_02055f6c, ModelObject_SetupRender)

/* func_02055fcc: no model: the render object emptied, the base transform the identity, the
 * derived classes' flags (layered_model.h) and the VRAM region cleared. */
void ModelObject_ResetRender(ModelObject *object)
{
    func_021054e4(&object->render, NULL);
    object->model = NULL;
    object->texture = NULL;
    MTX_Identity43_(base_transform(object));
    object->flags = 0;
    object->vram = NULL;
}
CLEAN_AS(func_02055fcc, ModelObject_ResetRender)

/* func_02055ff4: the render object part's destructor (the holder's ends with it). */
ModelObject *ModelObject_BaseDestruct(ModelObject *object)
{
    object->vtable = data_020dd13c;
    ModelObject_RootDestruct(object);
    return object;
}
CLEAN_AS(func_02055ff4, ModelObject_BaseDestruct)

/* func_0205600c: its deleting destructor. */
ModelObject *ModelObject_BaseDelete(ModelObject *object)
{
    object->vtable = data_020dd13c;
    ModelObject_RootDestruct(object);
    Heap_OperatorDeleteB(object);
    return object;
}
CLEAN_AS(func_0205600c, ModelObject_BaseDelete)

/* func_0205602c: its complete destructor, the same as ModelObject_BaseDestruct. */
ModelObject *ModelObject_BaseDestructComplete(ModelObject *object)
{
    object->vtable = data_020dd13c;
    ModelObject_RootDestruct(object);
    return object;
}
CLEAN_AS(func_0205602c, ModelObject_BaseDestructComplete)

/* func_02056044: its constructor: no model (ModelObject_ResetRender). */
ModelObject *ModelObject_BaseConstruct(ModelObject *object)
{
    ModelObject_RootConstruct(object);
    object->vtable = data_020dd13c;
    ModelObject_ResetRender(object);
    return object;
}
CLEAN_AS(func_02056044, ModelObject_BaseConstruct)

/* The root of the holder's classes (vtable data_020dd11c): it has nothing but its vtable, and
 * each of its functions only sets that vtable. */
extern const u8 data_020dd11c[];

/* func_02056390: its destructor (the one ModelObject_BaseDestruct ends with). */
void ModelObject_RootDestruct(ModelObject *object)
{
    object->vtable = data_020dd11c;
}
CLEAN_AS(func_02056390, ModelObject_RootDestruct)

/* func_0205639c: its deleting destructor (the vtable's second entry). */
ModelObject *ModelObject_RootDelete(ModelObject *object)
{
    object->vtable = data_020dd11c;
    Heap_OperatorDeleteB(object);
    return object;
}
CLEAN_AS(func_0205639c, ModelObject_RootDelete)

/* func_020563b4: its complete destructor (the vtable's first entry). */
void ModelObject_RootDestructComplete(ModelObject *object)
{
    object->vtable = data_020dd11c;
}
CLEAN_AS(func_020563b4, ModelObject_RootDestructComplete)

/* func_020563c0: its constructor (the one ModelObject_BaseConstruct starts with). */
void ModelObject_RootConstruct(ModelObject *object)
{
    object->vtable = data_020dd11c;
}
CLEAN_AS(func_020563c0, ModelObject_RootConstruct)
