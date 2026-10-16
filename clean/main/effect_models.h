/* The effects drawn as animated models (the effect system's, effect_system.h): four groups, one
 * per model of /spl (0 mp_situren, 1 mp_love, 2 ef_water_col, 3 cra_ribbon1), each holding the
 * model's animation files (.nsbca for the joints, .nsbma for the materials and, for group 0 only,
 * .nsbva for the visibility) and four copies of the model that play them.
 *
 * Loading a group loads its files into the effects' own heap (data_021d52c8, made the first time)
 * and each copy's model; starting an effect takes the group's first copy that is not playing,
 * starts its animations from frame 0 and hands it to a set-up function, which places it (the
 * EffectKindsModelTransform at its start). Each frame the playing copies step their animations,
 * and stop once the joints' animation has run out; drawn, a copy stands at its point bent over
 * the globe, turned and scaled, lit with the scene's emission colour. */
#ifndef CLEAN_MAIN_EFFECT_MODELS_H
#define CLEAN_MAIN_EFFECT_MODELS_H

#include "main/animated_model.h"
#include "main/effect_kinds.h"
#include "main/model_anim.h"
#include "types.h"

#define EFFECT_MODELS_GROUPS 4 /* the models */
#define EFFECT_MODELS_COPIES 4 /* of each model, playing at once */
#define EFFECT_MODELS_ANIMS 3  /* the kinds of animation file: joints, materials, visibility */
#define EFFECT_MODELS_MATERIALS 1
#define EFFECT_MODELS_VISIBILITY 2
#define EFFECT_MODELS_NAME 0x6d656666 /* "meff", plus the group, names a model shared */

/* A copy of a model (0x148 bytes, a C++ class: func_020911dc and func_020902ac build and
 * destroy it). */
typedef struct EffectModel {
    EffectKindsModelTransform transform;  /* 0x00: its unk_00 is nonzero while it plays */
    u8 animated[0xb8];                    /* 0x24: an AnimatedModel (without the blend) */
    u32 anim_used[EFFECT_MODELS_ANIMS];   /* 0xdc: whether anims[i] plays ([0] is never set) */
    ModelAnim anims[EFFECT_MODELS_ANIMS]; /* 0xe8: [1] the materials', [2] the visibility's; [0]
                                           * unused (the AnimatedModel plays the joints) */
} EffectModel;

/* A model's group (0x530 bytes, func_020911b0 and func_0209028c build and destroy it). */
typedef struct EffectModelGroup {
    s32 index;                                /* 0x000: the model's number */
    EffectModel copies[EFFECT_MODELS_COPIES]; /* 0x004 */
    u8 *files[EFFECT_MODELS_ANIMS];           /* 0x524: the animation files, NULL for none */
} EffectModelGroup;

void *EffectModels_DestructGroup(EffectModelGroup *group);
void *EffectModels_DestructCopy(EffectModel *copy);
void EffectModels_StartCopy(EffectModel *copy, EffectModelGroup *group, void (*setup)(void *transform));
void EffectModels_ReleaseCopy(EffectModel *copy);
void EffectModels_DrawCopy(EffectModel *copy);
void EffectModels_StepCopy(EffectModel *copy);
void EffectModels_LoadCopy(EffectModel *copy, EffectModelGroup *group);
int EffectModels_LoadShape(EffectModel *copy, int index);
void EffectModels_FreeFiles(u8 **files);
void EffectModels_LoadFiles(u8 **files, EffectModelGroup *group);
void EffectModels_StartInGroup(EffectModelGroup *group, void (*setup)(void *transform));
void EffectModels_ReleaseGroup(EffectModelGroup *group);
void EffectModels_DrawGroup(EffectModelGroup *group);
void EffectModels_StepGroup(EffectModelGroup *group);
void EffectModels_LoadGroup(EffectModelGroup *group, int index);
void EffectModels_Start(EffectModelGroup *groups, int index, void (*setup)(void *transform));
void EffectModels_ReleaseAll(EffectModelGroup *groups);
void EffectModels_DrawAll(EffectModelGroup *groups);
void EffectModels_StepAll(EffectModelGroup *groups);
void EffectModels_LoadAll(EffectModelGroup *groups);
void *EffectModels_ConstructGroup(EffectModelGroup *group);
void *EffectModels_ConstructCopy(EffectModel *copy);

#endif
