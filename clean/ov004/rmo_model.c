/* The archive, texture and sound parts of the RMO room objects (rmo_model.h). */
#include "rmo_model.h"

#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/c_library.h"
#include "main/model_cache.h"
#include "main/model_object.h"
#include "main/rom_file.h"
#include "main/sound_emitter.h"
#include "main/vram_region.h"
#include "ov004/rmo_object.h"

static_assert(offsetof(RmoModel, model) == 0x04, "model");
static_assert(offsetof(RmoModel, joint_anims) == 0x08, "joint animations");
static_assert(offsetof(RmoModel, material_anims) == 0x3c, "material animations");
static_assert(offsetof(RmoModel, texture_anims) == 0x70, "texture animations");
static_assert(sizeof(RmoModel) == 0xa4, "an archive holder");

/* The sounds are played at full volume. */
#define RMO_SOUND_VOLUME 0x7f

/* The heaps: the room's (what stays) and the current one (files read for a moment). */
extern Heap *data_021c9b24;
extern Heap *data_021fbe94;

/* The archive's mount name, its model, the formats of its animations' names and of the two
 * files' paths. */
extern const char data_ov004_02254b90[]; /* "RMO" */
extern const char data_ov004_02254b94[]; /* "RMO:a/bmd/bmd0" */
extern const char data_ov004_02254ba4[]; /* "RMO:a/bca/bca%d" */
extern const char data_ov004_02254bb4[]; /* "RMO:a/bma/bma%d" */
extern const char data_ov004_02254bc4[]; /* "RMO:a/bta/bta%d" */
extern const char data_ov004_02254bd4[]; /* "/roomObj/%s.arc" */
extern const char data_ov004_02254be4[]; /* "/roomObj/%s.nsbtx" */

/* NitroSystem's archives (an NNSFndArchive) and 3D files. */
typedef struct RmoArchive {
    u32 words[0x1b];
} RmoArchive;
extern int NNS_FndMountArchive(RmoArchive *archive, const char *name, void *data);
extern u8 *NNS_FndGetArchiveFileByName(const char *path);
extern int func_0210285c(RmoArchive *archive); /* the archive unmounted */
extern void *func_021077e8(void *file);        /* a .nsbtx file's texture resource */
extern u8 *func_02107828(void *file);          /* a .nsbmd file's model set */
extern void *NNS_G3dGetJntAnmSet(void *file);
extern void *NNS_G3dGetMatCAnmSet(void *file);
extern void *NNS_G3dGetTexSRTAnmSet(void *file);
extern void *func_02107b44(void *set, int index); /* animation `index` of a joint animation set */
extern void *func_02107b80(void *set, int index); /* ... of a material colour animation set */
extern void *func_02107bbc(void *set, int index); /* ... of a texture SRT animation set */
extern int NNS_G3dBindMdlTex(u8 *model, void *texture);
extern int NNS_G3dBindMdlPltt(u8 *model, void *texture);

/* The paths are built in buffers of this size. */
#define RMO_PATH_SIZE 0x28

/* ---- The sound emitter */

/* func_ov004_0222c2c8: sound `number` played at full volume through the sound layer's other
 * entry (SoundEmitter_PlayEx). */
int RmoSound_PlayEx(SoundEmitter *emitter, int number)
{
    return SoundEmitter_PlayEx(emitter, number, RMO_SOUND_VOLUME, 0);
}
CLEAN_AS(func_ov004_0222c2c8, RmoSound_PlayEx)

/* func_ov004_0222c2dc: sound `number` played at full volume. */
int RmoSound_Play(SoundEmitter *emitter, int number)
{
    return SoundEmitter_PlayB(emitter, number, RMO_SOUND_VOLUME, 0);
}
CLEAN_AS(func_ov004_0222c2dc, RmoSound_Play)

/* func_ov004_0222c2f0: the emitter's vtable slot 0x10 (its answer dropped). */
void RmoSound_Vfunc10(SoundEmitter *emitter)
{
    SoundEmitter_Vfunc10B(emitter);
}
CLEAN_AS(func_ov004_0222c2f0, RmoSound_Vfunc10)

/* func_ov004_0222c2f8: the emitter's sounds follow a copy of `position`. */
void RmoSound_UpdateAt(SoundEmitter *emitter, const Vec3 *position)
{
    Vec3 copy;
    copy.x = position->x;
    copy.y = position->y;
    copy.z = position->z;
    SoundEmitter_UpdateAtB(emitter, &copy);
}
CLEAN_AS(func_ov004_0222c2f8, RmoSound_UpdateAt)

/* func_ov004_0222c314: the emitter's sounds stopped. */
void RmoSound_Stop(SoundEmitter *emitter)
{
    SoundEmitter_StopB(emitter);
}
CLEAN_AS(func_ov004_0222c314, RmoSound_Stop)

/* func_ov004_0222c31c: the emitter's destructor (the base class's); returns it. */
SoundEmitterObject *RmoSound_Destruct(SoundEmitterObject *emitter)
{
    SoundEmitterClass_DestructBaseB(emitter);
    return emitter;
}
CLEAN_AS(func_ov004_0222c31c, RmoSound_Destruct)

/* func_ov004_0222c32c: the emitter's constructor (the base class's); returns it. */
SoundEmitterObject *RmoSound_Construct(SoundEmitterObject *emitter)
{
    SoundEmitterClass_ConstructBaseB(emitter);
    return emitter;
}
CLEAN_AS(func_ov004_0222c32c, RmoSound_Construct)

/* ---- The texture holder */

/* func_ov004_0222c33c: the texture resource held, NULL for none. */
void *RmoTexture_Texture(RmoTexture *texture)
{
    return texture->texture;
}
CLEAN_AS(func_ov004_0222c33c, RmoTexture_Texture)

/* func_ov004_0222c340: the texture let go of.
 * QUIRK: the copy in the room's heap is not freed (it goes with the heap). */
void RmoTexture_Release(RmoTexture *texture)
{
    texture->texture = NULL;
}
CLEAN_AS(func_ov004_0222c340, RmoTexture_Release)

/* func_ov004_0222c348: the .nsbtx file at `path` read into the current heap (from its end), its
 * textures put in VRAM anywhere and a copy of its texture resource made in the room's heap and
 * held; the file is freed again. Whether the file was read (else nothing is held anew). */
int RmoTexture_Load(RmoTexture *texture, const char *path)
{
    void *file = RomFile_Load(path, data_021fbe94, -4, NULL);
    if (file == NULL) {
        return 0;
    }
    void *resource = func_021077e8(file);
    VramRegion_LoadTexture(resource, NULL);
    texture->texture = ModelCache_CopyTexture(resource, data_021c9b24);
    Heap_FreeCurrent(file);
    return 1;
}
CLEAN_AS(func_ov004_0222c348, RmoTexture_Load)

/* func_ov004_0222c394: the texture holder's destructor: nothing to do. */
void RmoTexture_Destruct(RmoTexture *texture)
{
    (void) texture;
}
CLEAN_AS(func_ov004_0222c394, RmoTexture_Destruct)

/* func_ov004_0222c398: the texture holder's constructor: nothing held. */
void RmoTexture_Construct(RmoTexture *texture)
{
    texture->texture = NULL;
}
CLEAN_AS(func_ov004_0222c398, RmoTexture_Construct)

/* ---- The archive holder */

/* func_ov004_0222c3a0: the model held (an NNSG3dResMdl), NULL for none. */
u8 *RmoModel_Model(RmoModel *model)
{
    return model->model;
}
CLEAN_AS(func_ov004_0222c3a0, RmoModel_Model)

/* func_ov004_0222c3a4: texture coordinate animation `index` (NULL past the 13th or for none). */
const u8 *RmoModel_TextureAnim(RmoModel *model, int index)
{
    if ((u32) index >= RMO_ANIMS) {
        return NULL;
    }
    return model->texture_anims[index];
}
CLEAN_AS(func_ov004_0222c3a4, RmoModel_TextureAnim)

/* func_ov004_0222c3b4: material animation `index` (NULL past the 13th or for none). */
const u8 *RmoModel_MaterialAnim(RmoModel *model, int index)
{
    if ((u32) index >= RMO_ANIMS) {
        return NULL;
    }
    return model->material_anims[index];
}
CLEAN_AS(func_ov004_0222c3b4, RmoModel_MaterialAnim)

/* func_ov004_0222c3c4: joint animation `index` (NULL past the 13th or for none). */
const u8 *RmoModel_JointAnim(RmoModel *model, int index)
{
    if ((u32) index >= RMO_ANIMS) {
        return NULL;
    }
    return model->joint_anims[index];
}
CLEAN_AS(func_ov004_0222c3c4, RmoModel_JointAnim)

/* func_ov004_0222c3d4: the archive freed from the room's heap, if one is held.
 * QUIRK: the model and animation pointers into it are left as they were. */
void RmoModel_Release(RmoModel *model)
{
    if (model->file != NULL) {
        Heap_Free(data_021c9b24, model->file);
        model->file = NULL;
    }
}
CLEAN_AS(func_ov004_0222c3d4, RmoModel_Release)

/* The first model of a .nsbmd model set: its dictionary (at the offset in its halfword 0x0e)
 * holds the model's offset from the set in its word 0x0c. */
static u8 *rmo_first_model(u8 *set)
{
    u16 dictionary = *(const u16 *) (const void *) (set + 0x0e);
    u32 offset = *(const u32 *) (const void *) (set + dictionary + 0x0c);
    return set + offset;
}

/* The animations of one kind: from index 0, each found in the archive is the first animation
 * of its set; a missing one leaves its entry as it was, and the first empty entry ends the
 * list. */
static void rmo_load_anims(const u8 **anims, const char *format, void *(*get_set)(void *file),
                           void *(*get_anim)(void *set, int index))
{
    char name[RMO_PATH_SIZE + 0x0c];
    for (u32 i = 0; i < RMO_ANIMS; i++) {
        CLib_SPrintf(name, format, i);
        u8 *file = NNS_FndGetArchiveFileByName(name);
        if (file != NULL) {
            anims[i] = get_anim(get_set(file), 0);
        }
        if (anims[i] == NULL) {
            break;
        }
    }
}

/* func_ov004_0222c3f4: the archive at `path` read into the room's heap and held, mounted as
 * "RMO" while its model (when it has one) and its joint, material and texture animations are
 * found, then unmounted. 1 when it was read; 0 when an archive is held already, it could not
 * be read or not be mounted (then it is still held). */
int RmoModel_Load(RmoModel *model, const char *path)
{
    RmoArchive archive;
    if (model->file != NULL) {
        return 0;
    }
    model->file = RomFile_Load(path, data_021c9b24, 4, NULL);
    if (model->file == NULL) {
        return 0;
    }
    if (NNS_FndMountArchive(&archive, data_ov004_02254b90, model->file) == 0) {
        return 0;
    }
    u8 *file = NNS_FndGetArchiveFileByName(data_ov004_02254b94);
    if (file != NULL) {
        model->model = rmo_first_model(func_02107828(file));
    }
    rmo_load_anims(model->joint_anims, data_ov004_02254ba4, NNS_G3dGetJntAnmSet, func_02107b44);
    rmo_load_anims(model->material_anims, data_ov004_02254bb4, NNS_G3dGetMatCAnmSet, func_02107b80);
    rmo_load_anims(model->texture_anims, data_ov004_02254bc4, NNS_G3dGetTexSRTAnmSet, func_02107bbc);
    func_0210285c(&archive);
    return 1;
}
CLEAN_AS(func_ov004_0222c3f4, RmoModel_Load)

/* func_ov004_0222c51c: nothing held: no archive, no model, no animations. */
void RmoModel_Clear(RmoModel *model)
{
    model->file = NULL;
    model->model = NULL;
    for (u32 i = 0; i < RMO_ANIMS; i++) {
        model->material_anims[i] = NULL;
        model->joint_anims[i] = NULL;
        model->texture_anims[i] = NULL;
    }
}
CLEAN_AS(func_ov004_0222c51c, RmoModel_Clear)

/* func_ov004_0222c538: the archive holder's destructor: it is cleared (the archive is not
 * freed); returns it. */
RmoModel *RmoModel_Destruct(RmoModel *model)
{
    RmoModel_Clear(model);
    return model;
}
CLEAN_AS(func_ov004_0222c538, RmoModel_Destruct)

/* func_ov004_0222c548: the archive holder's constructor: nothing held; returns it. */
RmoModel *RmoModel_Construct(RmoModel *model)
{
    RmoModel_Clear(model);
    return model;
}
CLEAN_AS(func_ov004_0222c548, RmoModel_Construct)

/* ---- Both together */

/* func_ov004_0222c5b4: the archive freed and the texture let go of. */
void RmoModel_ReleaseWithTexture(RmoModel *model, RmoTexture *texture)
{
    RmoModel_Release(model);
    RmoTexture_Release(texture);
}
CLEAN_AS(func_ov004_0222c5b4, RmoModel_ReleaseWithTexture)

/* func_ov004_0222c62c: "/roomObj/<name>.arc" and "/roomObj/<name>.nsbtx" loaded into `model` and
 * `texture` and put on `object` (RmoModel_LoadWithTexture).
 * QUIRK: the first path's formatting is handed `texture` as a second, unused argument. */
int RmoModel_LoadNamed(const char *name, ModelObject *object, RmoModel *model, RmoTexture *texture)
{
    char archive[RMO_PATH_SIZE];
    char texture_path[RMO_PATH_SIZE];
    CLib_SPrintf(archive, data_ov004_02254bd4, name, texture);
    CLib_SPrintf(texture_path, data_ov004_02254be4, name);
    return RmoModel_LoadWithTexture(archive, texture_path, object, model, texture);
}
CLEAN_AS(func_ov004_0222c62c, RmoModel_LoadNamed)

/* func_ov004_0222c66c: the archive at `archive` loaded into `model` and the textures at
 * `texture_path` into `texture`; the model is given to `object` and bound to the textures and
 * their palettes. The palettes' binding's answer. */
int RmoModel_LoadWithTexture(const char *archive, const char *texture_path, ModelObject *object, RmoModel *model,
                             RmoTexture *texture)
{
    RmoModel_Load(model, archive);
    RmoTexture_Load(texture, texture_path);
    ModelObject_SetModel(object, RmoModel_Model(model), NULL);
    u8 *mdl = RmoModel_Model(model);
    NNS_G3dBindMdlTex(mdl, RmoTexture_Texture(texture));
    mdl = RmoModel_Model(model);
    return NNS_G3dBindMdlPltt(mdl, RmoTexture_Texture(texture));
}
CLEAN_AS(func_ov004_0222c66c, RmoModel_LoadWithTexture)
