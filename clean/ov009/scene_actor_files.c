/* The files of the town's buildings (scene_actor_files.h). */
#include "scene_actor_files.h"

#include <stdint.h>

#include "autoload_2/heap.h" /* Heap_Alloc, Heap_FreeCurrent */
#include "clean.h"
#include "main/animated_model.h"  /* AnimatedModel */
#include "main/building_shapes.h" /* BuildingShapes_Bounds, BuildingShapes_Of */
#include "main/c_library.h"       /* CLib_SPrintf */
#include "main/map_code.h"        /* MapCode_Building */
#include "main/model_cache.h"     /* ModelCache_CopyTexture */
#include "main/model_object.h"    /* ModelObject_SetModel */
#include "main/rom_file.h"        /* RomFile_Exists, RomFile_Load */
#include "main/shadow.h"          /* ObjShadow */
#include "main/vram_region.h"     /* VramRegion_LoadImages, VramRegion_LoadTexture */
#include "ov003/house_files.h"    /* HouseFiles_Palette, HouseFiles_SeasonLetter, HousePalette_Texture */
#include "scene_actor_area.h"     /* SceneActor_MapPoint */

static_assert(sizeof(SceneActorShadowEntry) == 28, "shadow entry");
static_assert(offsetof(SceneActorShadowFile, entries) == 4, "shadow entries");
static_assert(offsetof(SceneActorFiles, lit_texture) == 0x18, "files lit texture");
static_assert(offsetof(SceneActorFiles, srt_anims) == 0x20, "files srt anims");
static_assert(offsetof(SceneActorFiles, pattern_anims) == 0x30, "files pattern anims");
static_assert(offsetof(SceneActorFiles, centre_x) == 0x40, "files bounds");
static_assert(sizeof(SceneActorFiles) == 0x50, "files size");
static_assert(sizeof(ObjShadow) == 0x34, "shadow size");

/* The buildings without a "_lt.nsbtx" texture. */
#define SCENE_ACTOR_NO_LIT_A 0x500a
#define SCENE_ACTOR_NO_LIT_B 0x5011
#define SCENE_ACTOR_NO_LIT_C 0x501c
#define SCENE_ACTOR_NO_LIT_D 0x501d

/* The archive is loaded aligned to 4 words from the start of the heap, the textures from its
 * end (to be freed at once). */
#define SCENE_ACTOR_FILES_ALIGN 4
#define SCENE_ACTOR_FILES_FROM_END (-4)

/* The table of the buildings' records, the record __register_global_object links it with, and
 * the names of what it loads. */
extern SceneActorFiles data_ov009_02265cb4[SCENE_ACTOR_FILES_COUNT];
extern u8 data_ov009_02265b48[];
extern const char data_ov009_02265a28[]; /* "STR", the archive's name once mounted */
extern const char data_ov009_02265a2c[]; /* "STR:a/bca/bca0" */
extern const char data_ov009_02265a3c[]; /* "STR:a/bca/bca1" */
extern const char data_ov009_02265a4c[]; /* "STR:a/bca/bca2" */
extern const char data_ov009_02265a5c[]; /* "STR:a/bta/bta%d" */
extern const char data_ov009_02265a6c[]; /* "STR:a/btp/btp%d" */
extern const char data_ov009_02265a7c[]; /* "STR:a/bmd/bmd0" */
extern const char data_ov009_02265a8c[]; /* "STR:a/bmd/bmd1" */
extern const char data_ov009_02265a9c[]; /* "STR:a/bshadow/bshadow0" */
/* The paths' formats and the buffers they are written to. */
extern const char data_ov009_02265ab4[]; /* "/str/arc/%d/str%d%c_lt.nsbtx" */
extern const char data_ov009_02265ad4[]; /* "/str/arc/%d/str%d%c.nsbtx" */
extern const char data_ov009_02265af0[]; /* "/str/arc/%d/str%d%c.arc" */
extern char data_ov009_02265b94[0x20];
extern char data_ov009_02265b74[0x20];
extern char data_ov009_02265b54[0x20];
/* The six colours of four 5-bit components several source files define for themselves. */
typedef struct SceneActorColour {
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
} SceneActorColour;
extern SceneActorColour data_ov009_02265b3c, data_ov009_02265b20, data_ov009_02265b34, data_ov009_02265b30,
    data_ov009_02265b40, data_ov009_02265b38;
/* The records' constructor and destructor and the table's, as the game is handed them. */
extern void func_ov009_02265634(void *files);
extern void func_ov009_02265630(void *files);
extern void func_ov009_0226569c(void);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __register_global_object(void *object, void *destruct, void *record);

/* The heaps: the scene's (what stays) and the current one (files read for a moment). */
extern Heap *data_021c9b1c;
extern Heap *data_021fbe94;

/* NitroSystem's archives (an NNSFndArchive of 0x6c bytes) and 3D files. */
typedef struct SceneActorArchive {
    u32 words[0x1b];
} SceneActorArchive;
extern int NNS_FndMountArchive(SceneActorArchive *archive, const char *name, void *data);
extern u8 *NNS_FndGetArchiveFileByName(const char *path);
extern int func_0210285c(SceneActorArchive *archive); /* the archive unmounted */
extern void *func_021077e8(void *file);               /* a .nsbtx file's texture resource */
extern u8 *func_02107828(void *file);                 /* a .nsbmd file's model set */
extern void *NNS_G3dGetJntAnmSet(const void *file);
extern void *NNS_G3dGetTexSRTAnmSet(const void *file);
extern void *NNS_G3dGetTexPatAnmSet(const void *file);
extern void *func_02107b44(void *set, int index); /* animation `index` of a joint animation set */
extern void *func_02107bbc(void *set, int index); /* ... of a texture SRT animation set */
extern void *func_02107bf8(void *set, int index); /* ... of a texture pattern animation set */
extern int NNS_G3dBindMdlTex(u8 *model, void *texture);
extern int NNS_G3dBindMdlPltt(u8 *model, void *texture);

/* func_ov009_02264388: shadow `index` of a shadow file. */
const SceneActorShadowEntry *SceneActorShadows_Entry(const SceneActorShadowFile *file, int index)
{
    return &file->entries[index];
}
CLEAN_AS(func_ov009_02264388, SceneActorShadows_Entry)

/* func_ov009_02264394: the number of shadows of a shadow file. */
int SceneActorShadows_Count(const SceneActorShadowFile *file)
{
    return (int) file->count;
}
CLEAN_AS(func_ov009_02264394, SceneActorShadows_Count)

/* func_ov009_02264580: its shadows forgotten, when it has them and its building's record.
 * QUIRK: it walks the shadow file's count (asking for it once per shadow and once more)
 * without doing anything, and frees nothing: the shadows stay on the scene's heap. */
void SceneActor_ReleaseShadows(SceneActor *actor)
{
    SceneActorFiles *files = SceneActorFiles_Of(actor);
    if (files == NULL || actor->shadows == NULL) {
        return;
    }
    for (u32 i = 0; i < (u32) SceneActorShadows_Count(files->shadows); i++) {
    }
    actor->shadows = NULL;
}
CLEAN_AS(func_ov009_02264580, SceneActor_ReleaseShadows)

/* A shadow's point: its x and z on the ground under the actor, moved by `matrix` and taken
 * back to the map. */
static void files_shadow_point(Vec3 *out, const SceneActorShadowEntry *entry, const Mtx43 *matrix)
{
    Vec3 local;
    local.x = entry->x;
    local.y = 0;
    local.z = entry->z;
    SceneActor_MapPoint(out, &local, matrix);
}

/* func_ov009_022645b8: each of its shadows drawn at its point, `matrix` being where the actor
 * is drawn. */
void SceneActor_DrawShadows(SceneActor *actor, const Mtx43 *matrix)
{
    SceneActorFiles *files = SceneActorFiles_Of(actor);
    if (files == NULL) {
        return;
    }
    ObjShadow *shadow = actor->shadows;
    if (shadow == NULL) {
        return;
    }
    for (u32 i = 0; i < (u32) SceneActorShadows_Count(files->shadows); i++, shadow++) {
        const SceneActorShadowEntry *entry = SceneActorShadows_Entry(files->shadows, (int) i);
        Vec3 point;
        files_shadow_point(&point, entry, matrix);
        ObjShadow_Draw(shadow, &point);
    }
}
CLEAN_AS(func_ov009_022645b8, SceneActor_DrawShadows)

/* func_ov009_02264618: a long shadow for each of the building's shadows, on the scene's heap,
 * set up at its point (`matrix` being where the actor is drawn) with its size and texture.
 * REQUIRES: the heap has room for them. */
void SceneActor_InitShadows(SceneActor *actor, const Mtx43 *matrix)
{
    SceneActorFiles *files = SceneActorFiles_Of(actor);
    if (files == NULL || files->shadows == NULL) {
        return;
    }
    Heap *heap = data_021c9b1c;
    u32 count = (u32) SceneActorShadows_Count(files->shadows);
    actor->shadows = Heap_Alloc(heap, (int) (count * sizeof(ObjShadow)));
    ObjShadow *shadow = actor->shadows;
    for (u32 i = 0; i < count; i++, shadow++) {
        if (shadow != NULL) {
            shadow = ObjShadow_Construct(shadow);
        }
        const SceneActorShadowEntry *entry = SceneActorShadows_Entry(files->shadows, (int) i);
        Vec3 point;
        files_shadow_point(&point, entry, matrix);
        ObjShadow_Init(shadow, &point, entry->width, entry->length, entry->texture, entry->s_left, entry->s_right, heap);
    }
}
CLEAN_AS(func_ov009_02264618, SceneActor_InitShadows)

/* func_ov009_02264884: its building's record; NULL for a number of 34 or more. */
SceneActorFiles *SceneActorFiles_Of(SceneActor *actor)
{
    if (actor->index < SCENE_ACTOR_FILES_COUNT) {
        return &data_ov009_02265cb4[actor->index];
    }
    return NULL;
}
CLEAN_AS(func_ov009_02264884, SceneActorFiles_Of)

/* A texture file read from the current heap's end into `*texture`: its texture resource,
 * loaded into VRAM by `load` and kept as a copy on the scene's heap when that worked. The file
 * is freed. `*texture` is left alone when the file could not be read. */
static void files_texture(void **texture, const char *path, int (*load)(void *texture, VramRegion *region))
{
    void *file = RomFile_Load(path, data_021fbe94, SCENE_ACTOR_FILES_FROM_END, NULL);
    if (file == NULL) {
        return;
    }
    *texture = func_021077e8(file);
    if (load(*texture, NULL) != 0) {
        *texture = ModelCache_CopyTexture(*texture, data_021c9b1c);
    }
    Heap_FreeCurrent(file);
}

/* func_ov009_022648e4: its building's files loaded into its record unless something is there
 * already (then 1). The shape's bounds are taken first. The archive `archive` (unless NULL) is
 * read onto the scene's heap and, when it mounts, its animations, models and shadows taken from
 * it; the two textures (unless NULL or missing) are read for a moment and kept. Whether the
 * archive was read.
 * QUIRK: "bmd0" is taken whether or not the archive has it.
 * REQUIRES: the actor's building number is below 34. */
int SceneActorFiles_Load(SceneActor *actor, const char *archive, const char *texture, const char *lit_texture)
{
    int result = 0;
    SceneActorFiles *files = SceneActorFiles_Of(actor);
    if (SceneActorFiles_IsLoaded(files)) {
        return 1;
    }
    BuildingShapeEntry *shape = BuildingShapes_Of(&actor->code);
    if (shape != NULL) {
        BuildingShapes_Bounds(shape, &files->centre_x, &files->centre_z, &files->width, &files->depth);
    }
    if (archive != NULL) {
        void *data = RomFile_Load(archive, data_021c9b1c, SCENE_ACTOR_FILES_ALIGN, NULL);
        if (data != NULL) {
            SceneActorArchive mounted;
            if (NNS_FndMountArchive(&mounted, data_ov009_02265a28, data) != 0) {
                u8 *file;
                if ((file = NNS_FndGetArchiveFileByName(data_ov009_02265a2c)) != NULL) {
                    files->joint_anims[0] = (void *) (uintptr_t) SceneActorFiles_FirstJointAnim(file);
                }
                if ((file = NNS_FndGetArchiveFileByName(data_ov009_02265a3c)) != NULL) {
                    files->joint_anims[1] = (void *) (uintptr_t) SceneActorFiles_FirstJointAnim(file);
                }
                if ((file = NNS_FndGetArchiveFileByName(data_ov009_02265a4c)) != NULL) {
                    files->joint_anims[2] = (void *) (uintptr_t) SceneActorFiles_FirstJointAnim(file);
                }
                char name[0x1c];
                for (u32 i = 0; i < SCENE_ACTOR_FILES_ANIMS; i++) {
                    CLib_SPrintf(name, data_ov009_02265a5c, i);
                    if ((file = NNS_FndGetArchiveFileByName(name)) != NULL) {
                        files->srt_anims[i] = func_02107bbc(NNS_G3dGetTexSRTAnmSet(file), 0);
                    }
                }
                for (u32 i = 0; i < SCENE_ACTOR_FILES_ANIMS; i++) {
                    CLib_SPrintf(name, data_ov009_02265a6c, i);
                    if ((file = NNS_FndGetArchiveFileByName(name)) != NULL) {
                        files->pattern_anims[i] = func_02107bf8(NNS_G3dGetTexPatAnmSet(file), 0);
                    }
                }
                files->model = SceneActorFiles_FirstModel(NNS_FndGetArchiveFileByName(data_ov009_02265a7c));
                if ((file = NNS_FndGetArchiveFileByName(data_ov009_02265a8c)) != NULL) {
                    files->model_1 = SceneActorFiles_FirstModel(file);
                }
                files->shadows = (SceneActorShadowFile *) NNS_FndGetArchiveFileByName(data_ov009_02265a9c);
                func_0210285c(&mounted);
            }
            result = 1;
        }
    }
    if (texture != NULL && RomFile_Exists(texture)) {
        files_texture(&files->texture, texture, VramRegion_LoadImages);
    }
    if (lit_texture != NULL && RomFile_Exists(lit_texture)) {
        files_texture(&files->lit_texture, lit_texture, VramRegion_LoadTexture);
    }
    return result;
}
CLEAN_AS(func_ov009_022648e4, SceneActorFiles_Load)

/* func_ov009_02264ad8: unless it has its shadows or a model already (then 1), its building's
 * files loaded and its model object given the first model, with the palettes of overlay 3's
 * house palette file, then the texture and the second texture (with its palettes) bound to it.
 * 0 only when the model object refused the model. */
int SceneActor_LoadModel(SceneActor *actor, const char *archive, const char *texture, const char *lit_texture)
{
    if (actor->shadows != NULL || actor->model != NULL) {
        return 1;
    }
    SceneActorFiles_Load(actor, archive, texture, lit_texture);
    SceneActorFiles *files = SceneActorFiles_Of(actor);
    if (files == NULL || files->model == NULL) {
        return 1;
    }
    if (ModelObject_SetModel(&((AnimatedModel *) (void *) actor->model_object)->object, files->model, NULL) == 0) {
        return 0;
    }
    NNS_G3dBindMdlPltt(files->model, (void *) (uintptr_t) HousePalette_Texture(HouseFiles_Palette()));
    if (files->texture != NULL) {
        NNS_G3dBindMdlTex(files->model, files->texture);
    }
    if (files->lit_texture != NULL) {
        NNS_G3dBindMdlTex(files->model, files->lit_texture);
        NNS_G3dBindMdlPltt(files->model, files->lit_texture);
    }
    return 1;
}
CLEAN_AS(func_ov009_02264ad8, SceneActor_LoadModel)

/* func_ov009_02264b64 (vtable slot 0xac): the path of its "_lt.nsbtx" texture, in a buffer of
 * the overlay's; NULL for the four buildings without one. */
char *SceneActor_LitTexturePath(SceneActor *actor)
{
    switch (MapCode_Building(actor->index)) {
        case SCENE_ACTOR_NO_LIT_A:
        case SCENE_ACTOR_NO_LIT_B:
        case SCENE_ACTOR_NO_LIT_C:
        case SCENE_ACTOR_NO_LIT_D:
            return NULL;
        default:
            break;
    }
    int number = (int) actor->index;
    CLib_SPrintf(data_ov009_02265b94, data_ov009_02265ab4, number, number, HouseFiles_SeasonLetter());
    return data_ov009_02265b94;
}
CLEAN_AS(func_ov009_02264b64, SceneActor_LitTexturePath)

/* func_ov009_02264be0 (vtable slot 0xa8): the path of its texture, in a buffer of the
 * overlay's. */
char *SceneActor_TexturePath(SceneActor *actor)
{
    int number = (int) actor->index;
    CLib_SPrintf(data_ov009_02265b74, data_ov009_02265ad4, number, number, HouseFiles_SeasonLetter());
    return data_ov009_02265b74;
}
CLEAN_AS(func_ov009_02264be0, SceneActor_TexturePath)

/* func_ov009_02264c10 (vtable slot 0xa4): the path of its archive, in a buffer of the
 * overlay's. */
char *SceneActor_ArchivePath(SceneActor *actor)
{
    int number = (int) actor->index;
    int letter = HouseFiles_SeasonLetter();
    CLib_SPrintf(data_ov009_02265b54, data_ov009_02265af0, number, number, letter);
    return data_ov009_02265b54;
}
CLEAN_AS(func_ov009_02264c10, SceneActor_ArchivePath)

/* func_ov009_02264cf8: its building's texture SRT animation `index` ("bta<index>"); 0 for an
 * index of 4 or more or without a record. */
unsigned int SceneActor_SrtAnim(SceneActor *actor, unsigned int index)
{
    if (index >= SCENE_ACTOR_FILES_ANIMS) {
        return 0;
    }
    SceneActorFiles *files = SceneActorFiles_Of(actor);
    if (files == NULL) {
        return 0;
    }
    return (unsigned int) (uintptr_t) files->srt_anims[index];
}
CLEAN_AS(func_ov009_02264cf8, SceneActor_SrtAnim)

/* Joint animation `index` of its building ("bca<index>"); 0 without a record. */
static int files_joint_anim(SceneActor *actor, int index)
{
    SceneActorFiles *files = SceneActorFiles_Of(actor);
    if (files == NULL) {
        return 0;
    }
    return (int) (uintptr_t) files->joint_anims[index];
}

/* func_ov009_02264d18: "bca2". */
int SceneActor_JointAnim2(SceneActor *actor)
{
    return files_joint_anim(actor, 2);
}
CLEAN_AS(func_ov009_02264d18, SceneActor_JointAnim2)

/* func_ov009_02264d30 (vtable slot 0x68): "bca1". */
int SceneActor_JointAnim1(SceneActor *actor)
{
    return files_joint_anim(actor, 1);
}
CLEAN_AS(func_ov009_02264d30, SceneActor_JointAnim1)

/* func_ov009_02264d48 (vtable slot 0x64): "bca0". */
int SceneActor_JointAnim0(SceneActor *actor)
{
    return files_joint_anim(actor, 0);
}
CLEAN_AS(func_ov009_02264d48, SceneActor_JointAnim0)

/* func_ov009_02265598: the first animation of a joint animation file. */
int SceneActorFiles_FirstJointAnim(const void *file)
{
    return (int) (uintptr_t) func_02107b44(NNS_G3dGetJntAnmSet(file), 0);
}
CLEAN_AS(func_ov009_02265598, SceneActorFiles_FirstJointAnim)

/* func_ov009_022655ac: the first model of a model file: its set's dictionary (whose offset is
 * the halfword at 0x0e) gives the model's offset in its first entry's data (at 0x0c). */
void *SceneActorFiles_FirstModel(void *file)
{
    u8 *set = func_02107828(file);
    u16 dictionary = *(const u16 *) (const void *) (set + 0x0e);
    s32 offset = *(const s32 *) (const void *) (set + dictionary + 0x0c);
    return set + offset;
}
CLEAN_AS(func_ov009_022655ac, SceneActorFiles_FirstModel)

/* func_ov009_022655f8: whether anything of a record is loaded: a model, a joint animation, a
 * texture or the shadows. */
int SceneActorFiles_IsLoaded(const SceneActorFiles *files)
{
    return files->model != NULL || files->model_1 != NULL || files->texture != NULL || files->lit_texture != NULL ||
           files->shadows != NULL || files->joint_anims[0] != NULL || files->joint_anims[1] != NULL ||
           files->joint_anims[2] != NULL;
}
CLEAN_AS(func_ov009_022655f8, SceneActorFiles_IsLoaded)

/* func_ov009_02265630: a record's destructor: nothing. */
void SceneActorFiles_Destruct(SceneActorFiles *files)
{
    (void) files;
}
CLEAN_AS(func_ov009_02265630, SceneActorFiles_Destruct)

/* func_ov009_02265634: a record's constructor: everything cleared but the pattern animations. */
void SceneActorFiles_Construct(SceneActorFiles *files)
{
    files->model = NULL;
    files->model_1 = NULL;
    files->texture = NULL;
    files->lit_texture = NULL;
    files->shadows = NULL;
    for (int i = 0; i < 3; i++) {
        files->joint_anims[i] = NULL;
    }
    files->centre_x = 0;
    files->centre_z = 0;
    files->width = 0;
    files->depth = 0;
    for (int i = 0; i < SCENE_ACTOR_FILES_ANIMS; i++) {
        files->srt_anims[i] = NULL;
    }
}
CLEAN_AS(func_ov009_02265634, SceneActorFiles_Construct)

/* func_ov009_0226569c: the table's destructor, run when the overlay goes: each record's. */
void SceneActorFiles_DestroyAll(void)
{
    __cxa_vec_cleanup(data_ov009_02265cb4, SCENE_ACTOR_FILES_COUNT, sizeof(SceneActorFiles), func_ov009_02265630);
}
CLEAN_AS(func_ov009_0226569c, SceneActorFiles_DestroyAll)

static void files_colour(SceneActorColour *colour, u8 c0, u8 c1, u8 c2, u8 c3)
{
    colour->c0 = c0;
    colour->c1 = c1;
    colour->c2 = c2;
    colour->c3 = c3;
}

/* __sinit_ov009_022656f4: overlay 9's static initialiser: the six colours (red, blue, yellow,
 * green, cyan and grey, which nothing here reads), then the table of records built and its
 * destructor registered for when the overlay goes. */
void SceneActorFiles_StaticInit(void)
{
    files_colour(&data_ov009_02265b3c, 31, 20, 20, 31);
    files_colour(&data_ov009_02265b20, 20, 20, 31, 31);
    files_colour(&data_ov009_02265b34, 31, 31, 20, 31);
    files_colour(&data_ov009_02265b30, 20, 31, 20, 31);
    files_colour(&data_ov009_02265b40, 20, 31, 31, 31);
    files_colour(&data_ov009_02265b38, 20, 24, 24, 31);
    __cxa_vec_ctor(data_ov009_02265cb4, SCENE_ACTOR_FILES_COUNT, sizeof(SceneActorFiles), func_ov009_02265634,
                   func_ov009_02265630);
    __register_global_object(NULL, (void *) (uintptr_t) func_ov009_0226569c, data_ov009_02265b48);
}
CLEAN_AS(__sinit_ov009_022656f4, SceneActorFiles_StaticInit)
