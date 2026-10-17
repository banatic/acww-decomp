/* The town's ground: a process of overlay 3 (vtable 0x02239a58, 0x31c bytes, derived from the
 * process class of autoload_2/process.h) that draws the background models of the acres of the
 * scene's map (data_021c80bc) bent round the globe (main/globe.h), with what goes with them:
 *
 *   - one ground model per acre (TownGroundAcre): the acre's background model with the ground's
 *     texture (or the model's own), the ground's material colour and texture coordinate
 *     animations, placed at the acre's x and turned round the drum by its z. In an acre whose
 *     kind has flag 8, the material "m_grd_beA" gets a hook that hands its texture's scroll to
 *     the collision map (CollisionMap_SetValue134) once a frame;
 *   - one model for the first tile of unit type 0x6f or 0x70 found (TownGroundUnit): background
 *     model 0x84 or 0x85, with the same animations;
 *   - background model 0x83 kept under the camera (TownGroundFollow): at the x of the point the
 *     camera looks at less half an acre, turned by the camera's turn round the drum;
 *   - the river's and the beach's texture pattern animations, played into slots of the ground's
 *     texture ("grd_riv.0"/"grd_riv_pl" and "grd_beB"/"grd_beB_pl", main/tex_slot_anim.h);
 *   - a sound at the nearest sound mark of the acres around the camera (sound_mark.h).
 *
 * Only the acres in a band round the acre the camera looks at are drawn: one acre either side
 * along x, two behind and one in front along z. Its vtable's slots 0 (set up), 3 (release), 6
 * (each frame), 9 (draw), 16 and 17 (destructors) are here; func_ov003_0221fe10 makes one. */
#ifndef CLEAN_OV003_TOWN_GROUND_H
#define CLEAN_OV003_TOWN_GROUND_H

#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "main/acre_record.h"
#include "main/model_anim.h"
#include "main/model_object.h"
#include "main/sound_emitter.h"
#include "main/tex_slot_anim.h"
#include "types.h"

/* The ground's two animations of a model: material colours ("grd_set.nsbma") and texture
 * coordinates ("grd_set.nsbta"). */
#define TOWN_GROUND_ANIMS 2

/* TownGroundUnit's acre coordinates while it has no model. */
#define TOWN_GROUND_UNIT_NONE (-1)

/* An acre's ground model (0xec bytes). */
typedef struct TownGroundAcre {
    int model_number;                   /* 0x00: the acre's model number (AcreRecord_Model) */
    ModelObject model;                  /* 0x04: its placement is its matrix at 0x64 */
    int x;                              /* 0xa0: the acre's coordinates in the map */
    int z;                              /* 0xa4 */
    ModelAnim anims[TOWN_GROUND_ANIMS]; /* 0xa8 */
    s8 beach_material;                  /* 0xe8: the index of "m_grd_beA", -1 for none */
    u8 pad_e9[3];
} TownGroundAcre;

/* The model of unit type 0x6f or 0x70 (0xf4 bytes). */
typedef struct TownGroundUnit {
    ModelObject model; /* 0x00 */
    Vec3 position;     /* 0x9c: the tile's centre */
    s16 angle;         /* 0xa8: its turn round the drum (Globe_BendFar) */
    u8 pad_aa[2];
    int acre_x;                         /* 0xac: TOWN_GROUND_UNIT_NONE without a model */
    int acre_z;                         /* 0xb0 */
    ModelAnim anims[TOWN_GROUND_ANIMS]; /* 0xb4 */
} TownGroundUnit;

/* Background model 0x83, kept under the camera (0xa0 bytes). */
typedef struct TownGroundFollow {
    ModelObject model; /* 0x00 */
    u8 *resource;      /* 0x9c: the model resource it was given */
} TownGroundFollow;

typedef struct TownGround {
    Process process;         /* 0x000 */
    TownGroundAcre *acres;   /* 0x050: acres_wide x acres_high, row by row */
    TownGroundUnit unit;     /* 0x054 */
    int acres_wide;          /* 0x148: the map's size in acres */
    int acres_high;          /* 0x14c */
    TownGroundFollow follow; /* 0x150 */
    TexSlotAnim river;       /* 0x1f0 */
    TexSlotAnim beach;       /* 0x280 */
    SoundSource sound;       /* 0x310 (sound_source_member.h) */
} TownGround;

/* What the model's hooks get: the state of the model being drawn (NitroSystem's NNSG3dRS). */
typedef struct TownGroundRenderObject {
    u8 unk_00[0x2c];
    TownGroundAcre *acre; /* the object ModelObject_SetInitHook was given */
} TownGroundRenderObject;

/* NitroSystem's NNSG3dMatAnmResult, up to the texture's scroll along S. */
typedef struct TownGroundMaterialResult {
    u32 flags;        /* 0x00 */
    u32 color0;       /* 0x04 */
    u32 color1;       /* 0x08 */
    u32 polygon_attr; /* 0x0c */
    u32 tex_image;    /* 0x10 */
    u32 tex_palette;  /* 0x14 */
    fx32 scale_s;     /* 0x18 */
    fx32 scale_t;     /* 0x1c */
    fx32 rotate_sin;  /* 0x20 */
    fx32 rotate_cos;  /* 0x24 */
    fx32 translate_s; /* 0x28 */
    fx32 translate_t; /* 0x2c */
} TownGroundMaterialResult;

typedef struct TownGroundRenderState {
    const u8 *command; /* the command being run: byte 1 is its material */
    TownGroundRenderObject *render_object;
    u32 flags;
    u32 hooks[0x20]; /* the address of each command's hook, 0 for none */
    u8 hook_timings[0x20];
    u8 unk_AC[4];
    TownGroundMaterialResult *material_result;
} TownGroundRenderState;

int TownGroundFollow_Release(TownGroundFollow *follow);
int TownGroundFollow_Draw(TownGroundFollow *follow);
int TownGroundFollow_Place(TownGroundFollow *follow);
int TownGroundFollow_SetUp(TownGroundFollow *follow);
void TownGroundFollow_Clear(TownGroundFollow *follow);
int TownGroundFollow_Destruct(TownGroundFollow *follow);
int TownGroundFollow_Construct(TownGroundFollow *follow);
int TownGroundAcre_Release(TownGroundAcre *acre);
int TownGroundAcre_Draw(TownGroundAcre *acre);
int TownGroundAcre_Update(TownGroundAcre *acre);
int TownGroundAcre_SetUp(TownGroundAcre *acre, const AcreRecord *record, int x, int z);
TownGroundAcre *TownGroundAcre_Construct(TownGroundAcre *acre);
int TownGroundUnit_Release(TownGroundUnit *unit);
int TownGroundUnit_Draw(TownGroundUnit *unit);
int TownGroundUnit_Update(TownGroundUnit *unit);
int TownGroundUnit_SetUp(TownGroundUnit *unit, const Vec3 *position, int kind);
int TownGroundUnit_IsSetUp(TownGroundUnit *unit);
u32 TownGroundUnit_AcreZ(TownGroundUnit *unit);
u32 TownGroundUnit_AcreX(TownGroundUnit *unit);
int TownGroundUnit_Position(TownGroundUnit *unit);
s16 TownGroundUnit_Angle(TownGroundUnit *unit);
TownGroundUnit *TownGroundUnit_Destruct(TownGroundUnit *unit);
TownGroundUnit *TownGroundUnit_Construct(TownGroundUnit *unit);
void TownGround_SetWaterDepthUpdate(ModelObject *model, int on);
void TownGround_UpdateSound(TownGround *ground);
int TownGround_Release(TownGround *ground);
int TownGround_Draw(TownGround *ground);
int TownGround_Update(TownGround *ground);
int TownGround_SetUp(TownGround *ground);
TownGround *TownGround_DestroyAndFree(TownGround *ground);
TownGround *TownGround_Destroy(TownGround *ground);
TownGround *TownGround_Construct(TownGround *ground);
void TownGroundAcre_SetModelHooks(TownGroundRenderState *state);
void TownGroundAcre_BeachHook(TownGroundRenderState *state);
void TownGround_New(void);

#endif
