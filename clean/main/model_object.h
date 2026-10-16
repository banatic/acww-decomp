/* The game's holder of one 3D model (a C++ class, vtable data_020dd03c, 0x9c bytes): a
 * NitroSystem render object over a model resource, loaded from a model file (the first model
 * of its model set) or shared by a 32-bit name with every holder loaded under that name, its
 * textures bound from the same file, from a texture given, or from the player's designs.
 * Classes with animations extend it (animated_model.h, layered_model.h).
 *
 * A model set (vtable data_020dd04c) holds all the models of one model file, each in its own
 * holder, with their 16-byte names to find them by. */
#ifndef CLEAN_MAIN_MODEL_OBJECT_H
#define CLEAN_MAIN_MODEL_OBJECT_H

#include "autoload_2/heap.h"
#include "types.h"

/* The name of a holder that shares its model with no other ("NULL"). */
#define MODEL_OBJECT_NO_NAME 0x4e554c4c

/* ModelRenderObject.flags (NitroSystem's NNS_G3D_RENDEROBJ_FLAG_RECORD): the joints'
 * animation results are computed and kept in joint_results on the next draw. */
#define MODEL_RENDER_RECORD 0x01

struct AnimatedModelAnim;

/* NitroSystem's NNSG3dRenderObj. */
typedef struct ModelRenderObject {
    u32 flags;                                  /* 0x00: MODEL_RENDER_* */
    u8 *model;                                  /* 0x04: the model (NNSG3dResMdl) */
    struct AnimatedModelAnim *material_anims;   /* 0x08 */
    void *blend_materials;                      /* 0x0c */
    struct AnimatedModelAnim *joint_anims;      /* 0x10: a list through AnimatedModelAnim.next */
    void *blend_joints;                         /* 0x14 */
    struct AnimatedModelAnim *visibility_anims; /* 0x18 */
    u8 unk_1c[0x18];                            /* 0x1c */
    void *joint_results;                        /* 0x34: kept joint results, one per node */
    u8 unk_38[0x1c];                            /* 0x38 */
} ModelRenderObject;

typedef struct ModelObject {
    const void *vtable;       /* 0x00 */
    u8 unk_04[4];             /* 0x04 */
    ModelRenderObject render; /* 0x08 */
    u8 *model;                /* 0x5c: the model resource drawn (NNSG3dResMdl) */
    void *texture;            /* 0x60: the texture resource kept with it, by func_02055f40 */
    u8 unk_64[0x30];          /* 0x64 */
    void *vram;               /* 0x94: where its textures go in VRAM (func_02056064; NULL: anywhere) */
    u32 name;                 /* 0x98: the name it is shared by, MODEL_OBJECT_NO_NAME for none */
} ModelObject;

typedef struct ModelSet {
    const void *vtable;  /* 0x00 */
    u32 count;           /* 0x04 */
    ModelObject *models; /* 0x08: `count` holders */
    char (*names)[16];   /* 0x0c: their names, not always 0-terminated */
} ModelSet;

int ModelSet_Release(ModelSet *set);
ModelObject *ModelSet_Find(ModelSet *set, const char *name);
int ModelSet_Load(ModelSet *set, const char *path, Heap *heap);
ModelSet *ModelSet_Delete(ModelSet *set);
void ModelSet_Destruct(ModelSet *set);
void ModelSet_Construct(ModelSet *set);
int ModelObject_Release(ModelObject *object);
int ModelObject_AllocJointResults(ModelObject *object, Heap *heap);
void ModelObject_UseFileModel(ModelObject *object, u8 *file);
int ModelObject_LoadWithDesign(ModelObject *object, const char *path, int player, int index);
int ModelObject_LoadShared(ModelObject *object, int name, const char *path);
int ModelObject_LoadWithPalettes(ModelObject *object, const char *path, Heap *heap, void *texture, void *palettes,
                                 const u32 *palette_of_material, int materials);
int ModelObject_Load(ModelObject *object, const char *path, Heap *heap);
int ModelObject_LoadNamed(ModelObject *object, const char *path, Heap *heap, void *texture, void *palettes,
                          const u32 *palette_of_material, int materials, u32 name);
int ModelObject_LoadFrom(ModelObject *object, const char *path, Heap *heap, int name);
ModelObject *ModelObject_Destruct(ModelObject *object);
ModelObject *ModelObject_Delete(ModelObject *object);
ModelObject *ModelObject_DestructComplete(ModelObject *object);
ModelObject *ModelObject_Construct(ModelObject *object);
ModelObject *ModelObject_ConstructBase(ModelObject *object);

/* The render object's parts (vtable data_020dd13c, the class the holder extends): drawing,
 * the base transform, the materials' alpha and polygon ID, node callbacks and joint
 * matrices. */
#include "autoload_2/matrix.h"
#include "autoload_2/vector.h"

int ModelObject_JointMatrix(ModelObject *object, Mtx43 *out, int joint);
void ModelObject_SetAlpha(ModelObject *object, int alpha);
void ModelObject_SetPolygonId(ModelObject *object, int id);
void ModelObject_SetInitHook(ModelObject *object, void *hook, void *user);
void ModelObject_SetNodeCallback(ModelObject *object, void *callback, int command, int timing, void *user, void *at);
ModelRenderObject *ModelObject_RenderObject(ModelObject *object);
void ModelObject_DrawRender(ModelObject *object);
void ModelObject_SetBaseTransform(ModelObject *object, const Vec3 *scale);
void ModelObject_DrawWithoutCommands(ModelObject *object);
void ModelObject_Draw(ModelObject *object, const Vec3 *scale);
void ModelObject_DrawShapes(ModelObject *object, const Vec3 *scale);
int ModelObject_ReleaseRender(ModelObject *object);
int ModelObject_SetModel(ModelObject *object, u8 *model, void *texture);
int ModelObject_SetModelTexture(ModelObject *object, u8 *model, void *texture);
void ModelObject_SetupRender(ModelObject *object);
void ModelObject_ResetRender(ModelObject *object);
ModelObject *ModelObject_BaseDestruct(ModelObject *object);
ModelObject *ModelObject_BaseDelete(ModelObject *object);
ModelObject *ModelObject_BaseDestructComplete(ModelObject *object);
ModelObject *ModelObject_BaseConstruct(ModelObject *object);
void ModelObject_RootDestruct(ModelObject *object);
ModelObject *ModelObject_RootDelete(ModelObject *object);
void ModelObject_RootDestructComplete(ModelObject *object);
void ModelObject_RootConstruct(ModelObject *object);

#endif
