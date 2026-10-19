/* The objects of NitroSystem's G3D that the game's model code reads and writes:
 *
 * - the render object a model is drawn through (NNSG3dRenderObj, 0x54 bytes; the model holders
 *   of model_object.h keep one at their 0x08). Its `user` word is what the holder's owner gave
 *   ModelObject_SetInitHook or ModelObject_SetNodeCallback;
 * - the state of a model being drawn (NNSG3dRS), which the hooks the game sets for the model's
 *   commands are handed: the command being run, the render object, the hook of each command
 *   and when it runs, and the results of the material, joint and visibility animations of the
 *   material or node being drawn;
 * - a node's transform (NNSG3dJntAnmResult, 0x58 bytes) and a material's (NNSG3dMatAnmResult,
 *   0x38 bytes), as the animations leave them for the hooks. */
#ifndef CLEAN_MAIN_G3D_RENDER_H
#define CLEAN_MAIN_G3D_RENDER_H

#include "autoload_2/vector.h"
#include "main/model_matrix.h" /* Mtx33 */
#include "types.h"

struct AnimatedModelAnim;

/* The model's commands (NNS_G3D_SBC_*, in the low 5 bits of a command's first byte) the game
 * hooks, and how many there are. */
#define G3D_COMMAND_NODE 2      /* NNS_G3D_SBC_NODE: a node's visibility */
#define G3D_COMMAND_MATERIAL 4  /* NNS_G3D_SBC_MAT */
#define G3D_COMMAND_NODE_DESC 6 /* NNS_G3D_SBC_NODEDESC: a node placed */
#define G3D_COMMAND_COUNT 0x20
#define G3D_COMMAND_MASK 0x1f

/* When a command's hook runs (NNS_G3D_SBC_CALLBACK_TIMING_*): the command's three points, in
 * this order. For a node's description, B is when its transform (G3dRenderState.joint) is
 * computed and not yet applied. */
#define G3D_TIMING_A 1
#define G3D_TIMING_B 2
#define G3D_TIMING_C 3

/* NNSG3dRenderObj. */
typedef struct G3dRenderObject {
    u32 flags;                                  /* 0x00: MODEL_RENDER_* (model_object.h) */
    u8 *model;                                  /* 0x04: the model (NNSG3dResMdl) */
    struct AnimatedModelAnim *material_anims;   /* 0x08 */
    void *blend_materials;                      /* 0x0c */
    struct AnimatedModelAnim *joint_anims;      /* 0x10: a list through AnimatedModelAnim.next */
    void *blend_joints;                         /* 0x14 */
    struct AnimatedModelAnim *visibility_anims; /* 0x18 */
    u8 unk_1c[0x10];                            /* 0x1c */
    void *user;                                 /* 0x2c: the owner's object the hooks act for */
    u32 unk_30;                                 /* 0x30 */
    void *joint_results;                        /* 0x34: kept joint results, one per node */
    u8 unk_38[0x1c];                            /* 0x38 */
} G3dRenderObject;

/* G3dJointResult.flags (NNS_G3D_JNTANM_RESULTFLAG_*). */
#define G3D_JOINT_ROTATION_IDENTITY 0x02 /* the rotation is the identity, not written */
#define G3D_JOINT_TRANSLATION_ZERO 0x04  /* the translation is 0, not written */

/* NNSG3dJntAnmResult. */
typedef struct G3dJointResult {
    u32 flags;        /* 0x00: G3D_JOINT_* */
    u8 scale[0x24];   /* 0x04: the scale and its inverse */
    Mtx33 rotation;   /* 0x28 */
    Vec3 translation; /* 0x4c */
} G3dJointResult;

/* NNSG3dMatAnmResult. */
typedef struct G3dMaterialResult {
    u32 flags;           /* 0x00: the texture matrix's flags (NNS_G3D_MATANM_RESULTFLAG_*) */
    u32 diffuse;         /* 0x04: DIF_AMB, the diffuse colour in bits 0-14 */
    u32 specular;        /* 0x08: SPE_EMI */
    u32 polygon_attr;    /* 0x0c: POLYGON_ATTR, the alpha in bits 16-20 */
    u32 texture_image;   /* 0x10: TEXIMAGE_PARAM */
    u32 texture_palette; /* 0x14 */
    fx32 scale_s;        /* 0x18 */
    fx32 scale_t;        /* 0x1c */
    s16 rotate_sin;      /* 0x20 */
    s16 rotate_cos;      /* 0x22 */
    fx32 translate_s;    /* 0x24 */
    fx32 translate_t;    /* 0x28 */
    u16 width;           /* 0x2c: the texture's size */
    u16 height;          /* 0x2e */
    fx32 magnify_w;      /* 0x30 */
    fx32 magnify_h;      /* 0x34 */
} G3dMaterialResult;

/* NNSG3dRS, up to the model's materials. */
typedef struct G3dRenderState {
    const u8 *command;                  /* 0x00: the command being run; byte 1 its node or material */
    G3dRenderObject *object;            /* 0x04 */
    u32 flags;                          /* 0x08 */
    u32 hooks[G3D_COMMAND_COUNT];       /* 0x0c: each command's hook (a DS address), 0 for none */
    u8 hook_timings[G3D_COMMAND_COUNT]; /* 0x8c: when each runs (G3D_TIMING_*) */
    u8 unk_ac[4];                       /* 0xac */
    G3dMaterialResult *material;        /* 0xb0: the material being drawn's */
    G3dJointResult *joint;              /* 0xb4: the node being placed's */
    u32 *visible;                       /* 0xb8: the node's visibility (NNSG3dVisAnmResult) */
    u8 unk_bc[0x18];                    /* 0xbc */
    const u8 *node_info;                /* 0xd4: the model's node information (NNSG3dResNodeInfo) */
    const u8 *materials;                /* 0xd8: the model's materials (NNSG3dResMat) */
} G3dRenderState;

#endif
