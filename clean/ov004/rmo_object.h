/* Overlay 4's room objects built from an "RMO" archive (a C++ base class with vtable
 * 0x02254b28, built by RmoObjectBase_Construct and taken down by RmoObjectSlots_Destruct): a scene
 * object (actor.h) with one animated model whose model, animations and textures come from a
 * /roomObj/ archive (RmoObjectSlots_Load loads it, RmoObjectSlots_ReleaseBody releases it).
 *
 * An archive is held by an RmoModel: the archive file, its model ("RMO:a/bmd/bmd0") and up to
 * 13 animations of each kind ("RMO:a/bca/bca%d" for the joints, "bma" for the materials, "bta"
 * for the texture coordinates), loaded by RmoModel_Load; RmoModel_JointAnim gives the
 * joint animation of an index, NULL for none. The textures come from a separate .nsbtx file,
 * held by an RmoTexture (RmoTexture_Load). */
#ifndef CLEAN_OV004_RMO_OBJECT_H
#define CLEAN_OV004_RMO_OBJECT_H

#include "main/actor.h"
#include "main/animated_model.h"
#include "types.h"

#define RMO_ANIMS 13 /* the animations of each kind an archive may hold */

typedef struct RmoModel {
    u8 *file;                            /* 0x00: the archive, NULL until loaded */
    u8 *model;                           /* 0x04 */
    const u8 *joint_anims[RMO_ANIMS];    /* 0x08 */
    const u8 *material_anims[RMO_ANIMS]; /* 0x3c */
    const u8 *texture_anims[RMO_ANIMS];  /* 0x70 */
} RmoModel;

typedef struct RmoTexture {
    void *texture; /* the texture file, NULL until loaded */
} RmoTexture;

/* The animated model (animated_model.h) without the blend that only its blended class has: the
 * size these objects embed it with. */
typedef struct RmoAnimatedModel {
    ModelObject object;      /* 0x00: object.unk_64 is the model's base matrix (a Mtx43) */
    FrameCtrl frames;        /* 0x9c */
    AnimatedModelAnim *anim; /* 0xb4 */
} RmoAnimatedModel;

typedef struct RmoObject {
    Actor actor;             /* 0x000: actor.unk_08 is a word its class reads as a parameter */
    u8 unk_d4[0x18];         /* 0x0d4 */
    RmoAnimatedModel body;   /* 0x0ec */
    RmoModel body_model;     /* 0x1a4 */
    RmoTexture body_texture; /* 0x248 */
    u8 unk_24c[0x44];        /* 0x24c */
} RmoObject;

#endif
