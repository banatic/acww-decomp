/* The effects drawn as animated models (effect_models.h). */
#include "effect_models.h"

#include <string.h>

#include "autoload_2/heap.h"
#include "autoload_2/matrix.h"
#include "clean.h"
#include "main/frame_ctrl.h"
#include "main/globe.h"
#include "main/model_object.h"
#include "main/rom_file.h"
#include "main/scene_lights.h"

static_assert(sizeof(EffectKindsModelTransform) == 0x24, "EffectKindsModelTransform");
static_assert(offsetof(EffectModel, animated) == 0x24, "EffectModel.animated");
static_assert(offsetof(EffectModel, anim_used) == 0xdc, "EffectModel.anim_used");
static_assert(offsetof(EffectModel, anims) == 0xe8, "EffectModel.anims");
static_assert(sizeof(EffectModel) == 0x148, "EffectModel");
static_assert(offsetof(EffectModelGroup, files) == 0x524, "EffectModelGroup.files");
static_assert(sizeof(EffectModelGroup) == 0x530, "EffectModelGroup");
static_assert(offsetof(AnimatedModel, frames) == 0x9c && offsetof(AnimatedModel, anim) == 0xb4, "AnimatedModel");
static_assert(offsetof(ModelObject, model) == 0x5c && offsetof(ModelObject, unk_64) == 0x64, "ModelObject");
static_assert(sizeof(ModelAnim) == 0x20, "ModelAnim");

/* The effects' heap (made by EffectModels_LoadAll) and the current heap it is made in. */
extern Heap *data_021d52c8;
extern Heap *data_021fbe94;
/* Each model's file, and its animation files (NULL for none). */
extern const char *const data_020e2498[EFFECT_MODELS_GROUPS];
extern const char *const data_020e26ec[EFFECT_MODELS_GROUPS][EFFECT_MODELS_ANIMS];
/* The matrix being built for a copy. */
extern Mtx43 data_021fbe48;

/* NitroSystem's G3D: an animation file's set of joint, material or visibility animations, and
 * the animation of a set by its number. */
extern int NNS_G3dGetJntAnmSet(u32 file);
extern int NNS_G3dGetMatCAnmSet(u32 file);
extern int NNS_G3dGetVisAnmSet(u32 file);
extern int func_02107b44(int set, int index);
extern int func_02107b80(int set, int index);
extern int func_02107cf0(int set, int index);
extern void NNS_G3dMdlSetMdlEmi(int model, int material, unsigned short colour);

/* The C++ runtime's array helpers, and the classes' constructors and destructors given to them. */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void *func_020911dc(void *copy);
extern void *func_020902ac(void *copy);
extern void func_020565c8(void *anim);
extern void *func_020565b0(void *anim);

#define EFFECT_MODELS_HEAP_SIZE 0x2800
#define EFFECT_MODELS_FILE_ALIGN 4
#define EFFECT_MODELS_SPEED 0x1000

static AnimatedModel *effect_models_animated(EffectModel *copy)
{
    return (AnimatedModel *) (void *) copy->animated;
}

static const u8 *effect_models_joint_anim(const u8 *file)
{
    return (const u8 *) (uintptr_t) func_02107b44(NNS_G3dGetJntAnmSet((u32) (uintptr_t) file), 0);
}

static const u8 *effect_models_material_anim(const u8 *file)
{
    return (const u8 *) (uintptr_t) func_02107b80(NNS_G3dGetMatCAnmSet((u32) (uintptr_t) file), 0);
}

static const u8 *effect_models_visibility_anim(const u8 *file)
{
    return (const u8 *) (uintptr_t) func_02107cf0(NNS_G3dGetVisAnmSet((u32) (uintptr_t) file), 0);
}

/* func_0209028c: a group's destructor. */
void *EffectModels_DestructGroup(EffectModelGroup *group)
{
    __cxa_vec_cleanup(group->copies, EFFECT_MODELS_COPIES, sizeof(EffectModel), (void (*)(void *))(uintptr_t) func_020902ac);
    return group;
}
CLEAN_AS(func_0209028c, EffectModels_DestructGroup)

/* func_020902ac: a copy's destructor. */
void *EffectModels_DestructCopy(EffectModel *copy)
{
    __cxa_vec_cleanup(copy->anims, EFFECT_MODELS_ANIMS, sizeof(ModelAnim), (void (*)(void *))(uintptr_t) func_020565b0);
    AnimatedModel_DestructComplete(effect_models_animated(copy));
    return copy;
}
CLEAN_AS(func_020902ac, EffectModels_DestructCopy)

/* func_0209036c: the copy started: unturned at scale 1, its animations from frame 0, then
 * handed to `setup` to be placed. */
void EffectModels_StartCopy(EffectModel *copy, EffectModelGroup *group, void (*setup)(void *transform))
{
    EffectKindsModelTransform *transform = &copy->transform;

    transform->unk_00 = 1;
    transform->scale.x = 0x1000;
    transform->scale.y = 0x1000;
    transform->scale.z = 0x1000;
    transform->rotation[0] = 0;
    transform->rotation[1] = 0;
    transform->rotation[2] = 0;

    AnimatedModel_Start(effect_models_animated(copy), effect_models_joint_anim(group->files[0]), FRAME_CTRL_ONCE,
                        EFFECT_MODELS_SPEED, 0, 0);
    if (copy->anim_used[EFFECT_MODELS_MATERIALS] != 0) {
        ModelAnim_Start(&copy->anims[EFFECT_MODELS_MATERIALS], effect_models_material_anim(group->files[1]), FRAME_CTRL_ONCE,
                        EFFECT_MODELS_SPEED, 0);
    }
    if (copy->anim_used[EFFECT_MODELS_VISIBILITY] != 0) {
        ModelAnim_Start(&copy->anims[EFFECT_MODELS_VISIBILITY], effect_models_visibility_anim(group->files[2]),
                        FRAME_CTRL_ONCE, EFFECT_MODELS_SPEED, 0);
    }
    setup(copy);
}
CLEAN_AS(func_0209036c, EffectModels_StartCopy)

/* func_02090418: the copy's model let go. */
void EffectModels_ReleaseCopy(EffectModel *copy)
{
    ModelObject_Release(&effect_models_animated(copy)->object);
}
CLEAN_AS(func_02090418, EffectModels_ReleaseCopy)

/* func_02090424: a playing copy drawn: its point bent over the globe, turned by the bend about
 * X, then by its own angles (Z, Y, X order) and scaled; lit by the scene's emission colour. */
void EffectModels_DrawCopy(EffectModel *copy)
{
    EffectKindsModelTransform *transform = &copy->transform;
    AnimatedModel *animated = effect_models_animated(copy);
    Vec3 bent;
    int tilt;

    if (transform->unk_00 == 0) {
        return;
    }
    tilt = Globe_BendFar(&bent, &transform->position);
    Mtx43_Translation(&data_021fbe48, bent.x, bent.y, bent.z);
    Mtx43_RotateX(&data_021fbe48, tilt);
    Mtx43_RotateZYX(&data_021fbe48, transform->rotation[0], transform->rotation[1], transform->rotation[2]);
    Mtx43_Scale(&data_021fbe48, transform->scale.x, transform->scale.y, transform->scale.z);
    memcpy(animated->object.unk_64, &data_021fbe48, sizeof(Mtx43));
    AnimatedModel_Draw(animated, NULL);
    NNS_G3dMdlSetMdlEmi((int) (uintptr_t) animated->object.model, 0, (unsigned short) SceneLights_EmissionColour());
}
CLEAN_AS(func_02090424, EffectModels_DrawCopy)

/* func_020904ac: a playing copy's animations stepped a frame (each ModelAnim's frame copied into
 * its animation object); it stops once the joints' animation is done. */
void EffectModels_StepCopy(EffectModel *copy)
{
    AnimatedModel *animated = effect_models_animated(copy);
    int i;

    if (copy->transform.unk_00 == 0) {
        return;
    }
    AnimatedModel_StepFrames(animated);
    for (i = EFFECT_MODELS_MATERIALS; i < EFFECT_MODELS_ANIMS; i++) {
        if (copy->anim_used[i] != 0) {
            FrameCtrl_Step(&copy->anims[i].ctrl);
            copy->anims[i].anim->frame = copy->anims[i].ctrl.frame;
        }
    }
    if (FrameCtrl_IsDone(&animated->frames)) {
        copy->transform.unk_00 = 0;
    }
}
CLEAN_AS(func_020904ac, EffectModels_StepCopy)

/* func_0209050c: a copy of the group's model loaded, not playing, with an animation object for
 * each of the group's animation files. */
void EffectModels_LoadCopy(EffectModel *copy, EffectModelGroup *group)
{
    AnimatedModel *animated = effect_models_animated(copy);
    int index = group->index;
    u8 *const *files = group->files;

    copy->transform.unk_00 = 0;
    if (EffectModels_LoadShape(copy, index) == 0) {
        return;
    }

    if (files[0] != NULL) {
        ModelObject_AllocJointResults(&animated->object, data_021d52c8);
        AnimatedModel_LoadAnim(animated, data_021d52c8);
        AnimatedModel_Start(animated, effect_models_joint_anim(files[0]), FRAME_CTRL_ONCE, EFFECT_MODELS_SPEED, 0, 0);
        AnimatedModel_Attach(animated);
    }

    if (files[1] != NULL) {
        ModelAnim *anim = &copy->anims[EFFECT_MODELS_MATERIALS];
        copy->anim_used[EFFECT_MODELS_MATERIALS] = 1;
        ModelAnim_AllocMaterialAnim(anim, animated->object.model, data_021d52c8);
        ModelAnim_Start(anim, effect_models_material_anim(files[1]), FRAME_CTRL_ONCE, EFFECT_MODELS_SPEED, 0);
        ModelAnim_Attach(anim, ModelObject_RenderObject(&animated->object));
    } else {
        copy->anim_used[EFFECT_MODELS_MATERIALS] = 0;
    }

    if (files[2] != NULL) {
        ModelAnim *anim = &copy->anims[EFFECT_MODELS_VISIBILITY];
        copy->anim_used[EFFECT_MODELS_VISIBILITY] = 1;
        ModelAnim_AllocJointAnim(anim, animated->object.model, data_021d52c8);
        ModelAnim_Start(anim, effect_models_visibility_anim(files[2]), FRAME_CTRL_ONCE, EFFECT_MODELS_SPEED, 0);
        ModelAnim_Attach(anim, ModelObject_RenderObject(&animated->object));
    } else {
        copy->anim_used[EFFECT_MODELS_VISIBILITY] = 0;
    }
}
CLEAN_AS(func_0209050c, EffectModels_LoadCopy)

/* func_02090638: the copy's model `index` loaded, shared by the name "meff" + index; 1 when it
 * loaded, else 0. */
int EffectModels_LoadShape(EffectModel *copy, int index)
{
    if (ModelObject_LoadShared(&effect_models_animated(copy)->object, index + EFFECT_MODELS_NAME, data_020e2498[index]) == 0) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_02090638, EffectModels_LoadShape)

/* func_02090664: the animation files given back to the effects' heap. */
void EffectModels_FreeFiles(u8 **files)
{
    int i;
    for (i = 0; i < EFFECT_MODELS_ANIMS; i++) {
        if (files[i] != NULL) {
            Heap_Free(data_021d52c8, files[i]);
            files[i] = NULL;
        }
    }
}
CLEAN_AS(func_02090664, EffectModels_FreeFiles)

/* func_02090694: the group's animation files loaded into the effects' heap. */
void EffectModels_LoadFiles(u8 **files, EffectModelGroup *group)
{
    const char *const *paths = data_020e26ec[group->index];
    int i;
    for (i = 0; i < EFFECT_MODELS_ANIMS; i++) {
        if (paths[i] != NULL) {
            files[i] = RomFile_Load(paths[i], data_021d52c8, EFFECT_MODELS_FILE_ALIGN, NULL);
        } else {
            files[i] = NULL;
        }
    }
}
CLEAN_AS(func_02090694, EffectModels_LoadFiles)

/* func_020906dc: the group's first copy that is not playing started; none when all play. */
void EffectModels_StartInGroup(EffectModelGroup *group, void (*setup)(void *transform))
{
    int i;
    for (i = 0; i < EFFECT_MODELS_COPIES; i++) {
        if (group->copies[i].transform.unk_00 == 0) {
            EffectModels_StartCopy(&group->copies[i], group, setup);
            return;
        }
    }
}
CLEAN_AS(func_020906dc, EffectModels_StartInGroup)

/* func_02090710 */
void EffectModels_ReleaseGroup(EffectModelGroup *group)
{
    int i;
    EffectModels_FreeFiles(group->files);
    for (i = 0; i < EFFECT_MODELS_COPIES; i++) {
        EffectModels_ReleaseCopy(&group->copies[i]);
    }
}
CLEAN_AS(func_02090710, EffectModels_ReleaseGroup)

/* func_02090740 */
void EffectModels_DrawGroup(EffectModelGroup *group)
{
    int i;
    for (i = 0; i < EFFECT_MODELS_COPIES; i++) {
        EffectModels_DrawCopy(&group->copies[i]);
    }
}
CLEAN_AS(func_02090740, EffectModels_DrawGroup)

/* func_02090764 */
void EffectModels_StepGroup(EffectModelGroup *group)
{
    int i;
    for (i = 0; i < EFFECT_MODELS_COPIES; i++) {
        EffectModels_StepCopy(&group->copies[i]);
    }
}
CLEAN_AS(func_02090764, EffectModels_StepGroup)

/* func_02090788: the group of model `index` loaded. */
void EffectModels_LoadGroup(EffectModelGroup *group, int index)
{
    int i;
    group->index = index;
    EffectModels_LoadFiles(group->files, group);
    for (i = 0; i < EFFECT_MODELS_COPIES; i++) {
        EffectModels_LoadCopy(&group->copies[i], group);
    }
}
CLEAN_AS(func_02090788, EffectModels_LoadGroup)

/* func_020907c4: model `index` started (not checked against the groups' count). */
void EffectModels_Start(EffectModelGroup *groups, int index, void (*setup)(void *transform))
{
    EffectModels_StartInGroup(&groups[index], setup);
}
CLEAN_AS(func_020907c4, EffectModels_Start)

/* func_020907d8: every group released, then the effects' heap destroyed. */
void EffectModels_ReleaseAll(EffectModelGroup *groups)
{
    int i;
    for (i = 0; i < EFFECT_MODELS_GROUPS; i++) {
        EffectModels_ReleaseGroup(&groups[i]);
    }
    if (data_021d52c8 != NULL) {
        Heap_Destroy(data_021d52c8);
        data_021d52c8 = NULL;
    }
}
CLEAN_AS(func_020907d8, EffectModels_ReleaseAll)

/* func_02090810 */
void EffectModels_DrawAll(EffectModelGroup *groups)
{
    int i;
    for (i = 0; i < EFFECT_MODELS_GROUPS; i++) {
        EffectModels_DrawGroup(&groups[i]);
    }
}
CLEAN_AS(func_02090810, EffectModels_DrawAll)

/* func_02090834 */
void EffectModels_StepAll(EffectModelGroup *groups)
{
    int i;
    for (i = 0; i < EFFECT_MODELS_GROUPS; i++) {
        EffectModels_StepGroup(&groups[i]);
    }
}
CLEAN_AS(func_02090834, EffectModels_StepAll)

/* func_02090858: the effects' heap made in the current heap if there is none, then each group
 * loaded. */
void EffectModels_LoadAll(EffectModelGroup *groups)
{
    int i;
    if (data_021d52c8 == NULL) {
        data_021d52c8 = ExpHeap_Create(EFFECT_MODELS_HEAP_SIZE, data_021fbe94);
    }
    for (i = 0; i < EFFECT_MODELS_GROUPS; i++) {
        EffectModels_LoadGroup(&groups[i], i);
    }
}
CLEAN_AS(func_02090858, EffectModels_LoadAll)

/* func_020911b0: a group's constructor. */
void *EffectModels_ConstructGroup(EffectModelGroup *group)
{
    __cxa_vec_ctor(group->copies, EFFECT_MODELS_COPIES, sizeof(EffectModel), (void (*)(void *))(uintptr_t) func_020911dc,
                   (void (*)(void *))(uintptr_t) func_020902ac);
    return group;
}
CLEAN_AS(func_020911b0, EffectModels_ConstructGroup)

/* func_020911dc: a copy's constructor. */
void *EffectModels_ConstructCopy(EffectModel *copy)
{
    AnimatedModel_Construct(effect_models_animated(copy));
    __cxa_vec_ctor(copy->anims, EFFECT_MODELS_ANIMS, sizeof(ModelAnim), (void (*)(void *))(uintptr_t) func_020565c8,
                   (void (*)(void *))(uintptr_t) func_020565b0);
    return copy;
}
CLEAN_AS(func_020911dc, EffectModels_ConstructCopy)
