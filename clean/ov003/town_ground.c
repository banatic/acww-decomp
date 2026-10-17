/* The town's ground (town_ground.h). */
#include "town_ground.h"

#include "autoload_2/heap.h"   /* Heap, Heap_Alloc, Heap_FreeAux, Heap_AllocAuxZeroed */
#include "autoload_2/matrix.h" /* Mtx43, Mtx43_Translation, Mtx43_RotateX */
#include "clean.h"
#include "main/acre_kind.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/bg_models.h"
#include "main/camera_control.h"
#include "main/camera_view.h" /* CameraControl_GroundAngle, CameraControl_TargetAcre */
#include "main/collision_map.h"
#include "main/frame_ctrl.h"
#include "main/g3d_resource.h"
#include "main/globe.h"
#include "main/shadow.h"
#include "main/unit_type_info.h"
#include "sound_mark.h"
#include "sound_source_member.h"

static_assert(sizeof(Process) == 0x50, "process");
static_assert(sizeof(ModelObject) == 0x9c, "model object");
static_assert(sizeof(ModelAnim) == 0x20, "model animation");
static_assert(sizeof(TexSlotAnim) == 0x90, "texture slot animation");
static_assert(sizeof(SoundSource) == 0x0c, "sound source");
static_assert(offsetof(TownGroundAcre, model) == 0x04, "acre model");
static_assert(offsetof(TownGroundAcre, x) == 0xa0, "acre x");
static_assert(offsetof(TownGroundAcre, anims) == 0xa8, "acre animations");
static_assert(offsetof(TownGroundAcre, beach_material) == 0xe8, "acre beach material");
static_assert(sizeof(TownGroundAcre) == 0xec, "acre");
static_assert(offsetof(TownGroundUnit, position) == 0x9c, "unit position");
static_assert(offsetof(TownGroundUnit, angle) == 0xa8, "unit angle");
static_assert(offsetof(TownGroundUnit, acre_x) == 0xac, "unit acre x");
static_assert(offsetof(TownGroundUnit, acre_z) == 0xb0, "unit acre z");
static_assert(offsetof(TownGroundUnit, anims) == 0xb4, "unit animations");
static_assert(sizeof(TownGroundUnit) == 0xf4, "unit");
static_assert(offsetof(TownGroundFollow, resource) == 0x9c, "follow resource");
static_assert(sizeof(TownGroundFollow) == 0xa0, "follow");
static_assert(offsetof(TownGround, acres) == 0x050, "acres");
static_assert(offsetof(TownGround, unit) == 0x054, "unit");
static_assert(offsetof(TownGround, acres_wide) == 0x148, "acres wide");
static_assert(offsetof(TownGround, acres_high) == 0x14c, "acres high");
static_assert(offsetof(TownGround, follow) == 0x150, "follow");
static_assert(offsetof(TownGround, river) == 0x1f0, "river");
static_assert(offsetof(TownGround, beach) == 0x280, "beach");
static_assert(offsetof(TownGround, sound) == 0x310, "sound");
static_assert(sizeof(TownGround) == 0x31c, "the size TownGround_New allocates");
static_assert(offsetof(TownGroundRenderObject, acre) == 0x2c, "render object user");
static_assert(offsetof(TownGroundRenderState, hooks) == 0x0c, "hooks");
static_assert(offsetof(TownGroundRenderState, hook_timings) == 0x8c, "hook timings");
static_assert(offsetof(TownGroundRenderState, material_result) == 0xb0, "material result");
static_assert(offsetof(TownGroundMaterialResult, translate_s) == 0x28, "scroll along S");

/* The background models: model 0x83 (TownGroundFollow), and the units' models by kind
 * (data_ov003_02236664: 0x84 and 0x85). */
#define TOWN_GROUND_FOLLOW_MODEL 0x83
extern const int data_ov003_02236664[];

/* Positions >> 17 give an acre's coordinates. */
#define TOWN_GROUND_ACRE_SHIFT 17
/* The tiles to an acre's side. */
#define TOWN_GROUND_ACRE_TILES 16
/* The ground's animations' speed: one frame a frame. */
#define TOWN_GROUND_ANIM_SPEED 0x1000
/* An acre's kind flag: the acre has a beach (its "m_grd_beA" gets the hook). */
#define TOWN_GROUND_KIND_BEACH 8
/* The render state's command whose hook the acre sets: materials, after the material. */
#define TOWN_GROUND_COMMAND_MATERIAL 4
#define TOWN_GROUND_TIMING_AFTER 2
/* The beach's texture scroll goes to the collision map in steps of this. */
#define TOWN_GROUND_BEACH_STEP 0xda2
/* NNSG3dResMatData's polygon attribute bit 11: translucent pixels update the depth buffer. */
#define TOWN_GROUND_DEPTH_UPDATE 0x800
#define TOWN_GROUND_WATER_MATERIALS 2

/* The sounds played at the nearest mark, by its kind. */
#define TOWN_GROUND_SOUND_KIND_11 0x80b
#define TOWN_GROUND_SOUND_KIND_F 0x80c
#define TOWN_GROUND_SOUND_OTHER 0x80d /* kind 0x12 too */
#define TOWN_GROUND_SOUND_KIND_5 0x80e

/* The band of acres drawn round the acre the camera looks at. */
#define TOWN_GROUND_DRAW_LEFT 1
#define TOWN_GROUND_DRAW_RIGHT 1
#define TOWN_GROUND_DRAW_BEHIND 2
#define TOWN_GROUND_DRAW_FRONT 1

/* The camera and the point it looks at. */
extern CameraControl *data_021c67a4;
extern Vec3 data_021c67d0;
/* An acre's width in world units (32.0), and half of it. */
extern int data_020ca0ec;
extern int data_020ca0e4;
/* Main's matrix the placements are built in. */
extern Mtx43 data_021fbe48;
/* The scene's map, and the background heap. */
extern AcreMap *data_021c80bc;
extern Heap *data_021c9b24;
/* The list of catch spheres (main/catch_sphere.h), emptied each frame. */
extern void *data_021d3124;
/* Set while the nearest sound mark is of kind 0x12; nothing in this file reads it. */
extern u8 data_ov003_0223cad0;
/* Set once the beach's scroll went to the collision map this frame. */
extern int data_ov003_0223cad4;
/* The water's materials, "m_grd_riv" and "m_grd_sea085". */
extern const char *const data_ov003_02239a24[TOWN_GROUND_WATER_MATERIALS];
/* "m_grd_beA", and the slots' names: "grd_riv.0", "grd_riv_pl", "grd_beB", "grd_beB_pl". */
extern const char data_ov003_02239aa0[];
extern const char data_ov003_02239aac[];
extern const char data_ov003_02239ab8[];
extern const char data_ov003_02239ac4[];
extern const char data_ov003_02239acc[];
/* The vtables: the process class's and the ground's. */
extern const u32 data_020da13c[];
extern const u32 data_ov003_02239a58[];

/* The hooks are the game's functions: their addresses go to the model and its render state. */
extern void func_ov003_0221fdb8(TownGroundRenderState *state);
extern void func_ov003_0221fdc8(TownGroundRenderState *state);
/* The array helpers and what they are handed: the game's own animation constructor and
 * destructor. */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void func_020565c8(void *anim);
extern void func_020565b0(void *anim); /* returns `anim`, unused here */

extern fx32 FX_Div(fx32 numerator, fx32 denominator);

static BgModels *town_ground_bg_models(void)
{
    return (BgModels *) (uintptr_t) (u32) BgModels_Get();
}

/* A model object's placement: its matrix, 0x64 bytes in. */
static Mtx43 *town_ground_matrix(ModelObject *model)
{
    return (Mtx43 *) (void *) model->unk_64;
}

/* Gives `anims` the ground's two animations for `model`, those it can allocate, and puts them on
 * `object`'s render object. */
static void town_ground_start_anims(ModelAnim *anims, u8 *model, ModelObject *object)
{
    if (ModelAnim_AllocMaterialAnim(&anims[0], model, data_021c9b24)) {
        const u8 *file = (const u8 *) (uintptr_t) BgModels_GroundColourAnim(town_ground_bg_models());
        ModelAnim_Start(&anims[0], file, 0, TOWN_GROUND_ANIM_SPEED, 0);
        ModelAnim_Attach(&anims[0], ModelObject_RenderObject(object));
    }
    if (ModelAnim_AllocMaterialAnim(&anims[1], model, data_021c9b24)) {
        const u8 *file = (const u8 *) (uintptr_t) BgModels_GroundTextureAnim(town_ground_bg_models());
        ModelAnim_Start(&anims[1], file, 0, TOWN_GROUND_ANIM_SPEED, 0);
        ModelAnim_Attach(&anims[1], ModelObject_RenderObject(object));
    }
}

/* Steps both animations and copies their frames to their animation objects.
 * REQUIRES: both animations were allocated (their objects are written without a check). */
static void town_ground_step_anims(ModelAnim *anims)
{
    for (int i = 0; i < TOWN_GROUND_ANIMS; i++) {
        FrameCtrl_Step(&anims[i].ctrl);
        anims[i].anim->frame = anims[i].ctrl.frame;
    }
}

/* func_ov003_0221f110 (TownGroundFollow, released): its render object let go; 1. */
int TownGroundFollow_Release(TownGroundFollow *follow)
{
    ModelObject_ReleaseRender(&follow->model);
    return 1;
}
CLEAN_AS(func_ov003_0221f110, TownGroundFollow_Release)

/* func_ov003_0221f120 (TownGroundFollow, drawn): drawn while there is a camera (1), else 0. */
int TownGroundFollow_Draw(TownGroundFollow *follow)
{
    if (data_021c67a4 != NULL) {
        ModelObject_Draw(&follow->model, NULL);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0221f120, TownGroundFollow_Draw)

/* func_ov003_0221f144 (TownGroundFollow, each frame): placed at the x of the point the camera
 * looks at less half an acre, turned by the camera's turn round the drum (1); 0 without a
 * camera. */
int TownGroundFollow_Place(TownGroundFollow *follow)
{
    CameraControl *camera = data_021c67a4;
    if (camera != NULL) {
        Mtx43_Translation(&data_021fbe48, data_021c67d0.x - data_020ca0e4, 0, 0);
        Mtx43_RotateX(&data_021fbe48, CameraControl_GroundAngle(camera));
        *town_ground_matrix(&follow->model) = data_021fbe48;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0221f144, TownGroundFollow_Place)

/* func_ov003_0221f1ac (TownGroundFollow, set up): background model 0x83 with the ground's
 * texture, then placed; 1.
 * REQUIRES: the background model loads (its slot is read without a check). */
int TownGroundFollow_SetUp(TownGroundFollow *follow)
{
    BgModel *bg_model = BgModels_Load(town_ground_bg_models(), TOWN_GROUND_FOLLOW_MODEL);
    void *texture = (void *) (uintptr_t) BgModels_GroundTexture(town_ground_bg_models());
    follow->resource = bg_model->model;
    ModelObject_SetModelTexture(&follow->model, follow->resource, texture);
    TownGroundFollow_Place(follow);
    return 1;
}
CLEAN_AS(func_ov003_0221f1ac, TownGroundFollow_SetUp)

/* func_ov003_0221f1ec: forgets the model resource. */
void TownGroundFollow_Clear(TownGroundFollow *follow)
{
    follow->resource = NULL;
}
CLEAN_AS(func_ov003_0221f1ec, TownGroundFollow_Clear)

/* func_ov003_0221f1f4: TownGroundFollow's destructor; returns `follow`. */
int TownGroundFollow_Destruct(TownGroundFollow *follow)
{
    ModelObject_DestructComplete(&follow->model);
    return (int) (uintptr_t) follow;
}
CLEAN_AS(func_ov003_0221f1f4, TownGroundFollow_Destruct)

/* func_ov003_0221f204: TownGroundFollow's constructor; returns `follow`. */
int TownGroundFollow_Construct(TownGroundFollow *follow)
{
    ModelObject_Construct(&follow->model);
    TownGroundFollow_Clear(follow);
    return (int) (uintptr_t) follow;
}
CLEAN_AS(func_ov003_0221f204, TownGroundFollow_Construct)

/* func_ov003_0221f21c (an acre, released): its render object let go; 1. */
int TownGroundAcre_Release(TownGroundAcre *acre)
{
    ModelObject_ReleaseRender(&acre->model);
    return 1;
}
CLEAN_AS(func_ov003_0221f21c, TownGroundAcre_Release)

/* func_ov003_0221f230 (an acre, drawn): 1. */
int TownGroundAcre_Draw(TownGroundAcre *acre)
{
    ModelObject_Draw(&acre->model, NULL);
    return 1;
}
CLEAN_AS(func_ov003_0221f230, TownGroundAcre_Draw)

/* func_ov003_0221f244 (an acre, each frame): its animations stepped; 1. */
int TownGroundAcre_Update(TownGroundAcre *acre)
{
    town_ground_step_anims(acre->anims);
    return 1;
}
CLEAN_AS(func_ov003_0221f244, TownGroundAcre_Update)

/* func_ov003_0221f270 (an acre, set up from its record at (x, z)): its background model with
 * the model's own texture when it has one, else the ground's; the ground's animations; placed
 * at x acres' width and turned round the drum by z arcs; the hook on "m_grd_beA" in an acre of
 * a beach kind; the water's materials updating the depth. 1.
 * REQUIRES: the record and its background model exist (both are read without a check). */
int TownGroundAcre_SetUp(TownGroundAcre *acre, const AcreRecord *record, int x, int z)
{
    acre->x = x;
    acre->z = z;
    acre->model_number = AcreRecord_Model(record);

    void *texture = (void *) (uintptr_t) BgModels_GroundTexture(town_ground_bg_models());
    BgModel *bg_model = record->bg_model;
    if (bg_model->texture != NULL) {
        texture = bg_model->texture;
    }
    u8 *model = bg_model->model;
    ModelObject_SetModelTexture(&acre->model, model, texture);
    town_ground_start_anims(acre->anims, model, &acre->model);

    Mtx43_Translation(&data_021fbe48, (fx32) ((u32) x * (u32) data_020ca0ec), 0, 0);
    s16 angle = (s16) ((u32) z * (u32) Globe_ArcAngle());
    Mtx43_RotateX(&data_021fbe48, angle);
    *town_ground_matrix(&acre->model) = data_021fbe48;

    if (AcreKind_ModelFlags((unsigned int) acre->model_number) & TOWN_GROUND_KIND_BEACH) {
        acre->beach_material = (s8) G3dRes_MaterialIndex(model, data_ov003_02239aa0);
        if (acre->beach_material != -1) {
            ModelObject_SetInitHook(&acre->model, (void *) func_ov003_0221fdb8, acre);
        }
    }

    TownGround_SetWaterDepthUpdate(&acre->model, 1);
    return 1;
}
CLEAN_AS(func_ov003_0221f270, TownGroundAcre_SetUp)

/* func_ov003_0221f3b0: an acre's constructor; returns `acre`.
 * QUIRK: the beach material is left as it is (0 in the ground's zeroed allocation). */
TownGroundAcre *TownGroundAcre_Construct(TownGroundAcre *acre)
{
    ModelObject_Construct(&acre->model);
    __cxa_vec_ctor(acre->anims, TOWN_GROUND_ANIMS, sizeof(ModelAnim), func_020565c8, func_020565b0);
    acre->model_number = 0;
    acre->x = 0;
    acre->z = 0;
    return acre;
}
CLEAN_AS(func_ov003_0221f3b0, TownGroundAcre_Construct)

/* func_ov003_0221f3f0 (the unit's model, released): with a model, its render object let go and
 * the acre forgotten (1); else 0. */
int TownGroundUnit_Release(TownGroundUnit *unit)
{
    if (TownGroundUnit_IsSetUp(unit)) {
        ModelObject_ReleaseRender(&unit->model);
        unit->acre_z = TOWN_GROUND_UNIT_NONE;
        unit->acre_x = unit->acre_z;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0221f3f0, TownGroundUnit_Release)

/* func_ov003_0221f424 (the unit's model, drawn): with a model, drawn (1); else 0. */
int TownGroundUnit_Draw(TownGroundUnit *unit)
{
    if (TownGroundUnit_IsSetUp(unit)) {
        ModelObject_Draw(&unit->model, NULL);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0221f424, TownGroundUnit_Draw)

/* func_ov003_0221f444 (the unit's model, each frame): with a model, its animations stepped (1);
 * else 0. */
int TownGroundUnit_Update(TownGroundUnit *unit)
{
    if (TownGroundUnit_IsSetUp(unit)) {
        town_ground_step_anims(unit->anims);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0221f444, TownGroundUnit_Update)

/* func_ov003_0221f47c (the unit's model, set up at `position` for unit kind `kind`, 0 or 1):
 * only when it has no model yet (else 0). Background model 0x84 or 0x85 with the ground's
 * texture and animations, placed at the position's x and turned round the drum to where the
 * position bends (Globe_BendFar); its acre kept. 1.
 * REQUIRES: the background model loads (its slot is read without a check). */
int TownGroundUnit_SetUp(TownGroundUnit *unit, const Vec3 *position, int kind)
{
    if (TownGroundUnit_IsSetUp(unit)) {
        return 0;
    }
    unit->position.x = position->x;
    unit->position.y = position->y;
    unit->position.z = position->z;

    BgModel *bg_model = BgModels_Load(town_ground_bg_models(), data_ov003_02236664[kind]);
    void *texture = (void *) (uintptr_t) BgModels_GroundTexture(town_ground_bg_models());
    u8 *model = bg_model->model;
    ModelObject_SetModelTexture(&unit->model, model, texture);
    town_ground_start_anims(unit->anims, model, &unit->model);

    Vec3 bent;
    unit->angle = (s16) Globe_BendFar(&bent, &unit->position);
    Mtx43_Translation(&data_021fbe48, unit->position.x, 0, 0);
    Mtx43_RotateX(&data_021fbe48, unit->angle);
    *town_ground_matrix(&unit->model) = data_021fbe48;

    unit->acre_x = position->x >> TOWN_GROUND_ACRE_SHIFT;
    unit->acre_z = position->z >> TOWN_GROUND_ACRE_SHIFT;
    return 1;
}
CLEAN_AS(func_ov003_0221f47c, TownGroundUnit_SetUp)

/* func_ov003_0221f5ac: whether the unit's model is set up (both acre coordinates kept). */
int TownGroundUnit_IsSetUp(TownGroundUnit *unit)
{
    return (int) TownGroundUnit_AcreX(unit) != TOWN_GROUND_UNIT_NONE &&
           (int) TownGroundUnit_AcreZ(unit) != TOWN_GROUND_UNIT_NONE;
}
CLEAN_AS(func_ov003_0221f5ac, TownGroundUnit_IsSetUp)

/* func_ov003_0221f5d8 */
u32 TownGroundUnit_AcreZ(TownGroundUnit *unit)
{
    return (u32) unit->acre_z;
}
CLEAN_AS(func_ov003_0221f5d8, TownGroundUnit_AcreZ)

/* func_ov003_0221f5e0 */
u32 TownGroundUnit_AcreX(TownGroundUnit *unit)
{
    return (u32) unit->acre_x;
}
CLEAN_AS(func_ov003_0221f5e0, TownGroundUnit_AcreX)

/* func_ov003_0221f5e8: the address of the unit's position. */
int TownGroundUnit_Position(TownGroundUnit *unit)
{
    return (int) (uintptr_t) &unit->position;
}
CLEAN_AS(func_ov003_0221f5e8, TownGroundUnit_Position)

/* func_ov003_0221f5ec */
s16 TownGroundUnit_Angle(TownGroundUnit *unit)
{
    return unit->angle;
}
CLEAN_AS(func_ov003_0221f5ec, TownGroundUnit_Angle)

/* func_ov003_0221f5f4: the unit's model's destructor; returns `unit`. */
TownGroundUnit *TownGroundUnit_Destruct(TownGroundUnit *unit)
{
    __cxa_vec_cleanup(unit->anims, TOWN_GROUND_ANIMS, sizeof(ModelAnim), func_020565b0);
    ModelObject_DestructComplete(&unit->model);
    return unit;
}
CLEAN_AS(func_ov003_0221f5f4, TownGroundUnit_Destruct)

/* func_ov003_0221f618: the unit's model's constructor, without a model; returns `unit`. */
TownGroundUnit *TownGroundUnit_Construct(TownGroundUnit *unit)
{
    ModelObject_Construct(&unit->model);
    __cxa_vec_ctor(unit->anims, TOWN_GROUND_ANIMS, sizeof(ModelAnim), func_020565c8, func_020565b0);
    unit->acre_x = TOWN_GROUND_UNIT_NONE;
    unit->acre_z = TOWN_GROUND_UNIT_NONE;
    unit->position.x = 0;
    unit->position.y = 0;
    unit->position.z = 0;
    return unit;
}
CLEAN_AS(func_ov003_0221f618, TownGroundUnit_Construct)

/* The data of material `index` of a model resource (NNSG3dResMdl): its materials' block, the
 * block's dictionary (at 4), and the entry's offset of the material in the block. */
static G3dResMaterial *town_ground_material(u8 *model, int index)
{
    u8 *materials = model + *(const u32 *) (const void *) (model + 8);
    u8 *dict = materials + 4;
    u8 *entries = dict + *(const u16 *) (const void *) (dict + 6);
    u16 entry_size = *(const u16 *) (const void *) entries;
    u8 *entry = entries + entry_size * index;
    return (G3dResMaterial *) (void *) (materials + *(const u32 *) (const void *) (entry + 4));
}

/* func_ov003_0221f668: the water's materials of the model ("m_grd_riv" and "m_grd_sea085",
 * those it has) set to update the depth with their translucent pixels (`on`) or not, in the
 * model resource itself. */
void TownGround_SetWaterDepthUpdate(ModelObject *model, int on)
{
    for (unsigned int i = 0; i < TOWN_GROUND_WATER_MATERIALS; i++) {
        int index = G3dRes_MaterialIndex(model->model, data_ov003_02239a24[i]);
        if (index == -1) {
            continue;
        }
        G3dResMaterial *material = town_ground_material(model->model, index);
        if (material != NULL) {
            material->poly_attr_mask |= TOWN_GROUND_DEPTH_UPDATE;
            if (on) {
                material->poly_attr |= TOWN_GROUND_DEPTH_UPDATE;
            } else {
                material->poly_attr &= ~TOWN_GROUND_DEPTH_UPDATE;
            }
        }
    }
}
CLEAN_AS(func_ov003_0221f668, TownGround_SetWaterDepthUpdate)

/* func_ov003_0221f6dc: with a camera, the ground's sound plays at the sound mark nearest the
 * point the camera looks at, chosen by its kind (0x11: 0x80b, 0xf: 0x80c, 5: 0x80e, else 0x80d);
 * data_ov003_0223cad0 says whether that mark is of kind 0x12. Without a mark nothing plays. */
void TownGround_UpdateSound(TownGround *ground)
{
    data_ov003_0223cad0 = 0;
    if (data_021c67a4 == NULL) {
        return;
    }
    Vec3 point = data_021c67d0;
    SoundMarkSearch search;
    SoundMark_FindNearest(&search, &point);
    Vec3 *at = SoundMark_Position(&search);
    if (at != NULL) {
        int number = TOWN_GROUND_SOUND_OTHER;
        switch (SoundMark_Kind(&search)) {
            case SOUND_MARK_KIND_11:
                number = TOWN_GROUND_SOUND_KIND_11;
                break;
            case SOUND_MARK_KIND_12:
                data_ov003_0223cad0 = 1;
                break;
            case SOUND_MARK_KIND_5:
                number = TOWN_GROUND_SOUND_KIND_5;
                break;
            case SOUND_MARK_KIND_F:
                number = TOWN_GROUND_SOUND_KIND_F;
                break;
            default:
                break;
        }
        SoundSourceMember_PlayAt(&ground->sound, at, number);
    }
    SoundMark_Destruct(&search);
}
CLEAN_AS(func_ov003_0221f6dc, TownGround_UpdateSound)

/* func_ov003_0221f788 (vtable slot 3, released): the unit's model, every acre's, the model
 * under the camera and the sound let go; 1. */
int TownGround_Release(TownGround *ground)
{
    TownGroundUnit_Release(&ground->unit);
    int n = 0;
    for (int z = 0; z < ground->acres_high; z++) {
        for (int x = 0; x < ground->acres_wide; x++) {
            TownGroundAcre_Release(&ground->acres[n++]);
        }
    }
    TownGroundFollow_Release(&ground->follow);
    SoundSourceMember_Release(&ground->sound);
    return 1;
}
CLEAN_AS(func_ov003_0221f788, TownGround_Release)

/* Whether acre (x, z) is in the band drawn round acre (at_x, at_z). */
static int town_ground_is_drawn(int x, int z, int at_x, int at_z)
{
    return x >= at_x - TOWN_GROUND_DRAW_LEFT && x <= at_x + TOWN_GROUND_DRAW_RIGHT && z >= at_z - TOWN_GROUND_DRAW_BEHIND &&
           z <= at_z + TOWN_GROUND_DRAW_FRONT;
}

/* Draws the acres in the band round acre (at_x, at_z), row by row. */
static void town_ground_draw_acres(TownGround *ground, int at_x, int at_z)
{
    int n = 0;
    for (int z = 0; z < ground->acres_high; z++) {
        for (int x = 0; x < ground->acres_wide; x++) {
            if (town_ground_is_drawn(x, z, at_x, at_z)) {
                TownGroundAcre_Draw(&ground->acres[n]);
            }
            n++;
        }
    }
}

/* func_ov003_0221f7f0 (vtable slot 9, drawn): the shadows' frame begins; then the model under
 * the camera, the acres in the band round the acre the camera looks at, and the unit's model
 * when its acre is in the band. Their order: when the unit's turn round the drum is less than
 * the camera's, the unit's model first if its z is less than the arc of the camera's turn, then
 * the model under the camera, then the acres; else the model under the camera, the acres and
 * the unit's model last. 1. Without a camera the band is round acre (0, 0). */
int TownGround_Draw(TownGround *ground)
{
    data_ov003_0223cad4 = 0;
    ShadowLight_Update();
    CharaShadow_BeginFrame();

    int arc = 0;
    int at_x = 0;
    int at_z = 0;
    int unit_z = ((const Vec3 *) (uintptr_t) (u32) TownGroundUnit_Position(&ground->unit))->z;
    int angle = 0;
    CameraControl *camera = data_021c67a4;
    if (camera != NULL) {
        angle = CameraControl_GroundAngle(camera);
        CameraControl_TargetAcre(camera, &at_x, &at_z);
        arc = Globe_ArcLength(angle);
    }

    int unit_drawn = 0;
    for (int z = 0; z < ground->acres_high; z++) {
        for (int x = 0; x < ground->acres_wide; x++) {
            if (town_ground_is_drawn(x, z, at_x, at_z) && x == (int) TownGroundUnit_AcreX(&ground->unit) &&
                z == (int) TownGroundUnit_AcreZ(&ground->unit)) {
                unit_drawn = 1;
            }
        }
    }

    if (!unit_drawn) {
        TownGroundFollow_Draw(&ground->follow);
        town_ground_draw_acres(ground, at_x, at_z);
    } else if (TownGroundUnit_Angle(&ground->unit) < angle) {
        if (unit_z < arc) {
            TownGroundUnit_Draw(&ground->unit);
            TownGroundFollow_Draw(&ground->follow);
        } else {
            TownGroundFollow_Draw(&ground->follow);
            TownGroundUnit_Draw(&ground->unit);
        }
        town_ground_draw_acres(ground, at_x, at_z);
    } else {
        TownGroundFollow_Draw(&ground->follow);
        town_ground_draw_acres(ground, at_x, at_z);
        TownGroundUnit_Draw(&ground->unit);
    }
    return 1;
}
CLEAN_AS(func_ov003_0221f7f0, TownGround_Draw)

/* func_ov003_0221fa28 (vtable slot 6, each frame): the model under the camera placed, the
 * animations of the unit's model, of every acre and of the river's and the beach's slots
 * stepped, the sound updated and the list of catch spheres emptied; 1. */
int TownGround_Update(TownGround *ground)
{
    TownGroundFollow_Place(&ground->follow);
    TownGroundUnit_Update(&ground->unit);
    TownGroundAcre *acre = ground->acres;
    for (int z = 0; z < ground->acres_high; z++) {
        for (int x = 0; x < ground->acres_wide; x++) {
            TownGroundAcre_Update(acre);
            acre++;
        }
    }
    TexSlotAnim_Update(&ground->river);
    TexSlotAnim_Update(&ground->beach);
    TownGround_UpdateSound(ground);
    data_021d3124 = NULL;
    return 1;
}
CLEAN_AS(func_ov003_0221fa28, TownGround_Update)

/* func_ov003_0221faac (vtable slot 0, set up): the model under the camera; the river's slot
 * (the ground texture's "grd_riv.0" and palette "grd_riv_pl" from the river's texture) and the
 * beach's (palettes only, "grd_beB" and "grd_beB_pl"); one acre model for each acre of the
 * scene's map, from the background heap; the unit's model at the first tile, acre by acre and
 * row by row, of unit type 0x6f or 0x70; every acre set up from its record; the sound. 1.
 * REQUIRES: the scene's map exists and the allocation succeeds. */
int TownGround_SetUp(TownGround *ground)
{
    TownGroundFollow_Clear(&ground->follow);
    TownGroundFollow_SetUp(&ground->follow);

    G3dResTex *target = (G3dResTex *) (uintptr_t) BgModels_GroundTexture(town_ground_bg_models());
    G3dResTex *source = (G3dResTex *) (uintptr_t) BgModels_RiverTexture(town_ground_bg_models());
    const u8 *anim = (const u8 *) (uintptr_t) (u32) BgModels_RiverPatternAnim(town_ground_bg_models());
    TexSlotAnim_Start(&ground->river, target, data_ov003_02239aac, data_ov003_02239ab8, source, anim, 0);

    target = (G3dResTex *) (uintptr_t) BgModels_GroundTexture(town_ground_bg_models());
    source = (G3dResTex *) (uintptr_t) BgModels_BebTexture(town_ground_bg_models());
    anim = (const u8 *) (uintptr_t) BgModels_BebPatternAnim(town_ground_bg_models());
    TexSlotAnim_Start(&ground->beach, target, data_ov003_02239ac4, data_ov003_02239acc, source, anim, 1);

    const AcreMap *map = data_021c80bc;
    ground->acres_wide = map->acres_wide;
    ground->acres_high = map->acres_high;
    u32 count = (u32) ground->acres_wide * (u32) ground->acres_high;
    ground->acres = Heap_Alloc(data_021c9b24, (int) (sizeof(TownGroundAcre) * count));
    for (u32 i = 0; i < count; i++) {
        TownGroundAcre_Construct(&ground->acres[i]);
    }

    for (u32 z = 0; z < (u32) ground->acres_high; z++) {
        for (u32 x = 0; x < (u32) ground->acres_wide; x++) {
            for (int tile_z = 0; tile_z < TOWN_GROUND_ACRE_TILES; tile_z++) {
                for (int tile_x = 0; tile_x < TOWN_GROUND_ACRE_TILES; tile_x++) {
                    int map_x;
                    int map_z;
                    AcreTile_TileOfAcre(&map_x, &map_z, (int) x, (int) z, tile_x, tile_z);
                    int kind = UnitTypeInfo_Kind6fAt(map_x, map_z);
                    if (kind != UNIT_TYPE_INFO_NO_KIND) {
                        Vec3 centre = {0, 0, 0};
                        AcreTile_TileCentreInAcre(&centre, (int) x, (int) z, tile_x, tile_z);
                        TownGroundUnit_SetUp(&ground->unit, &centre, kind);
                    }
                }
            }
        }
    }

    u32 n = 0;
    for (u32 z = 0; z < (u32) ground->acres_high; z++) {
        for (u32 x = 0; x < (u32) ground->acres_wide; x++) {
            const AcreRecord *record = NULL;
            if (x < (u32) map->acres_wide && z < (u32) map->acres_high && map->acres != NULL) {
                record =
                    (const AcreRecord *) (const void *) (map->acres + (x + z * (u32) map->acres_wide) * ACRE_MAP_ACRE_SIZE);
            }
            TownGroundAcre_SetUp(&ground->acres[n++], record, (int) x, (int) z);
        }
    }

    SoundSourceMember_Init(&ground->sound);
    return 1;
}
CLEAN_AS(func_ov003_0221faac, TownGround_SetUp)

/* The members' destructors, last to first, and the process's. */
static void town_ground_destroy(TownGround *ground)
{
    ground->process.vtable = data_ov003_02239a58;
    SoundSourceMember_Destruct(&ground->sound);
    TexSlotAnim_Destruct(&ground->beach);
    TexSlotAnim_Destruct(&ground->river);
    TownGroundFollow_Destruct(&ground->follow);
    TownGroundUnit_Destruct(&ground->unit);
    ground->process.vtable = data_020da13c;
    Process_Destruct(&ground->process);
}

/* func_ov003_0221fca4 (vtable slot 17): destroys the ground and frees it; returns `ground`. */
TownGround *TownGround_DestroyAndFree(TownGround *ground)
{
    town_ground_destroy(ground);
    Heap_FreeAux(ground);
    return ground;
}
CLEAN_AS(func_ov003_0221fca4, TownGround_DestroyAndFree)

/* func_ov003_0221fd04 (vtable slot 16): destroys the ground; returns it. */
TownGround *TownGround_Destroy(TownGround *ground)
{
    town_ground_destroy(ground);
    return ground;
}
CLEAN_AS(func_ov003_0221fd04, TownGround_Destroy)

/* func_ov003_0221fd60: the ground's constructor; returns `ground`. */
TownGround *TownGround_Construct(TownGround *ground)
{
    Process_Construct(&ground->process);
    ground->process.vtable = data_020da13c;
    ground->process.vtable = data_ov003_02239a58;
    TownGroundUnit_Construct(&ground->unit);
    TownGroundFollow_Construct(&ground->follow);
    TexSlotAnim_Construct(&ground->river);
    TexSlotAnim_Construct(&ground->beach);
    SoundSourceMember_Construct(&ground->sound);
    return ground;
}
CLEAN_AS(func_ov003_0221fd60, TownGround_Construct)

/* func_ov003_0221fdb8 (the hook ModelObject_SetInitHook is given, run before an acre's model is
 * drawn): sets the materials' hook (after each material) to func_ov003_0221fdc8. */
void TownGroundAcre_SetModelHooks(TownGroundRenderState *state)
{
    state->hooks[TOWN_GROUND_COMMAND_MATERIAL] = (u32) (uintptr_t) func_ov003_0221fdc8;
    state->hook_timings[TOWN_GROUND_COMMAND_MATERIAL] = TOWN_GROUND_TIMING_AFTER;
}
CLEAN_AS(func_ov003_0221fdb8, TownGroundAcre_SetModelHooks)

/* func_ov003_0221fdc8 (a material's hook): at the acre's "m_grd_beA", the first time in the
 * frame, the collision map's value 0x134 becomes the material's scroll along S plus 0xda2, in
 * steps of 0xda2. */
void TownGroundAcre_BeachHook(TownGroundRenderState *state)
{
    if (data_ov003_0223cad4 == 0) {
        TownGroundAcre *acre = state->render_object->acre;
        u8 material = state->command[1];
        if (acre != NULL && acre->beach_material == material) {
            fx32 scroll = state->material_result->translate_s;
            CollisionMap_SetValue134((s16) FX_Div(scroll + TOWN_GROUND_BEACH_STEP, TOWN_GROUND_BEACH_STEP));
            data_ov003_0223cad4 = 1;
        }
    }
}
CLEAN_AS(func_ov003_0221fdc8, TownGroundAcre_BeachHook)

/* func_ov003_0221fe10 (the ground's entry in the overlay's table of profiles): allocates and
 * constructs one; nothing keeps the pointer here. */
void TownGround_New(void)
{
    TownGround *ground = Heap_AllocAuxZeroed(sizeof(TownGround));
    if (ground != NULL) {
        TownGround_Construct(ground);
    }
}
CLEAN_AS(func_ov003_0221fe10, TownGround_New)
