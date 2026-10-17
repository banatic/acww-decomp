/* The model of the room itself (room_shell.h). */
#include "room_shell.h"

#include <stdint.h>

#include "clean.h"
#include "main/acre_map.h"
#include "main/clock_hands.h"
#include "main/sky.h"
#include "room_etc_board.h"
#include <string.h>

#include "autoload_2/heap.h"
#include "autoload_2/matrix.h"
#include "main/field_collision.h"
#include "main/g3d_resource.h"
#include "main/house_record.h"
#include "main/item_code.h"
#include "main/model_object.h"
#include "main/room_interior.h"
#include "main/scene_kinds.h"
#include "main/scene_lights.h"
#include "main/scene_query.h"
#include "main/shadow.h"
#include "main/sound.h"
#include "main/trivial_object.h"
#include "main/villager_furniture.h"
#include "main/villager_roster.h"
#include "room_surface.h"

static_assert(offsetof(RoomShell, wallpaper) == 0x128, "wallpaper");
static_assert(offsetof(RoomShell, wallpaper_material) == 0x121c, "wallpaper material");
static_assert(offsetof(RoomShell, carpet) == 0x1228, "carpet");
static_assert(offsetof(RoomShell, carpet_material) == 0x331c, "carpet material");
static_assert(offsetof(RoomShell, hour_hand_node) == 0x3520, "hour hand node");
static_assert(offsetof(RoomShell, size) == 0x3522, "size");
static_assert(offsetof(RoomShell, hour_hand_position) == 0x3528, "hour hand position");
static_assert(offsetof(RoomShellMaterialResult, texture_image) == 0x10, "texture image");
static_assert(offsetof(RoomShellMaterialResult, width) == 0x2c, "width");
static_assert(offsetof(RoomShellMaterialResult, magnify_h) == 0x34, "magnify h");
static_assert(offsetof(RoomShellRenderState, material) == 0xb0, "material result");
static_assert(offsetof(RoomShellRenderState, materials) == 0xd8, "materials");
static_assert(offsetof(NodeHookState, hooks) == 0x0c, "hooks");
static_assert(offsetof(NodeHookState, hook_timings) == 0x8c, "hook timings");

/* The vtable slots the hooks are sent to. */
#define ROOM_SHELL_SLOT_NODE_DESC_HOOK 0x48
#define ROOM_SHELL_SLOT_MATERIAL_HOOK 0x4c

/* The codes whose wallpaper or carpet the material hook sets up. */
#define ROOM_SHELL_CODE_FIRST 0x1188
#define ROOM_SHELL_CODE_LAST 0x11a7

/* The material animation result's flags (NNS_G3D_MATANM_RESULTFLAG_TEXMTX_*). */
#define ROOM_SHELL_TEXTURE_MATRIX_SCALE_ONE 0x1
#define ROOM_SHELL_TEXTURE_MATRIX_ROTATION_ZERO 0x2
#define ROOM_SHELL_TEXTURE_MATRIX_TRANSLATION_ZERO 0x4
#define ROOM_SHELL_TEXTURE_MATRIX_SET 0x8

/* TEXIMAGE_PARAM's bits: repeat and flip in S and T, the texture coordinates' source (bits
 * 30-31, 1: from the texture coordinates). */
#define ROOM_SHELL_TEXTURE_REPEAT_S (1u << 16)
#define ROOM_SHELL_TEXTURE_REPEAT_T (1u << 17)
#define ROOM_SHELL_TEXTURE_FLIP_S (1u << 18)
#define ROOM_SHELL_TEXTURE_FLIP_T (1u << 19)
#define ROOM_SHELL_TEXTURE_SOURCE_MASK 0xc0000000u
#define ROOM_SHELL_TEXTURE_SOURCE_TEXCOORD 0x40000000u

/* The mode of the wallpaper's or carpet's part that flips its texture. */
#define ROOM_SHELL_MODE_FLIP 1

/* The room's sizes, and what the texture's scale adds up from. */
#define ROOM_SHELL_SIZE_4 4
#define ROOM_SHELL_SIZE_6 6
#define ROOM_SHELL_SIZE_8 8
#define ROOM_SHELL_SCALE_DIVISOR 0x64000

/* The render state's flag the material hook clears (bit 8 of NNSG3dRS's flag). */
#define ROOM_SHELL_RENDER_FLAG_8 0x100u

/* The height given to node "hasu1"'s point. */
#define ROOM_SHELL_HASU1_HEIGHT 0x3700

/* The one that exists, NULL for none. */
extern RoomShell *data_ov004_022589fc;
/* The code the getters answer while none exists. */
extern u16 data_ov004_022589ec[];
/* Where node "hasu1" was last drawn (its X and Z, height 0x3700). */
extern Vec3 data_ov004_02258a30;

extern AcreMap *data_021c80bc; /* the map of the scene shown */

/* The wallpaper's and carpet's parts: their first and second code and their mode. */
extern u16 *func_ov004_022329c0(u8 *wallpaper);
extern u16 *func_ov004_022329c4(u8 *wallpaper);
extern int func_ov004_022329b4(u8 *wallpaper);
extern u16 *func_ov004_02232734(u8 *carpet);
extern u16 *func_ov004_02232738(u8 *carpet);
extern int func_ov004_02232728(u8 *carpet);

extern fx32 FX_Div(fx32 numerator, fx32 denominator);

/* The hooks are the game's functions: their addresses go into the render state. */
extern int func_ov004_02231b58(NodeHookState *state);
extern int func_ov004_02231b78(NodeHookState *state);

static void RoomShell_set_hook(NodeHookState *state, int command, u32 hook, u8 timing)
{
    state->hooks[command] = hook;
    state->hook_timings[command] = timing;
}

/* func_ov004_02231b38 (the model's init hook, given by func_02055dc8): the hooks for materials
 * and after nodes' descriptions. */
void RoomShell_SetModelHooks(NodeHookState *state)
{
    RoomShell_set_hook(state, G3D_COMMAND_MATERIAL, (u32) (uintptr_t) func_ov004_02231b78, G3D_TIMING_AFTER);
    RoomShell_set_hook(state, G3D_COMMAND_NODE_DESC, (u32) (uintptr_t) func_ov004_02231b58, G3D_TIMING_AFTER);
}
CLEAN_AS(func_ov004_02231b38, RoomShell_SetModelHooks)

/* Sends the hook to vtable slot `slot` of the model's object with byte 1 of the command (its
 * node or material) and the state; its answer, or 0 without an object. */
static int RoomShell_run_hook(NodeHookState *state, int slot)
{
    void *user = state->render_object->user;
    if (user == NULL) {
        return 0;
    }
    const u32 *vtable = *(const u32 *const *) user;
    return ((int (*)(void *, int, NodeHookState *))(uintptr_t) vtable[slot / 4])(user, state->command[1], state);
}

/* func_ov004_02231b58: after a node's description, vtable slot 0x48 (RoomShell_NodeDescHook). */
int RoomShell_RunNodeDescHook(NodeHookState *state)
{
    return RoomShell_run_hook(state, ROOM_SHELL_SLOT_NODE_DESC_HOOK);
}
CLEAN_AS(func_ov004_02231b58, RoomShell_RunNodeDescHook)

/* func_ov004_02231b78: a material's hook, vtable slot 0x4c (RoomShell_MaterialHook). */
int RoomShell_RunMaterialHook(NodeHookState *state)
{
    return RoomShell_run_hook(state, ROOM_SHELL_SLOT_MATERIAL_HOOK);
}
CLEAN_AS(func_ov004_02231b78, RoomShell_RunMaterialHook)

/* A 15-bit colour's channel: 5 bits at `shift`. */
static int RoomShell_channel(u16 colour, int shift)
{
    return (colour >> shift) & 0x1f;
}

static int RoomShell_clamp_channel(int value)
{
    if (value > 0x1f) {
        return 0x1f;
    }
    if (value < 0) {
        return 0;
    }
    return value;
}

/* func_ov004_02231b98: material "wd"'s diffuse colour: the shown sky palette's lower gradient
 * colour with a third of the sky's light colour 0 added to each channel (at most 31), its top
 * bit kept; 0xffff (as a short, -1) without a palette. */
short RoomShell_WdDiffuse(RoomShell *self)
{
    (void) self;
    SkyPalette *palette = Sky_ShownPalette();
    if (palette == NULL) {
        return -1;
    }
    u16 light = (u16) Sky_LightColor(0);
    u16 colour = palette->gradient_bottom;
    int r = RoomShell_channel(colour, 0) + RoomShell_channel(light, 0) / 3;
    int g = RoomShell_channel(colour, 5) + RoomShell_channel(light, 5) / 3;
    int b = RoomShell_channel(colour, 10) + RoomShell_channel(light, 10) / 3;
    u16 result = (u16) ((colour & 0x8000) | (RoomShell_clamp_channel(b) << 10) | (RoomShell_clamp_channel(g) << 5) |
                        RoomShell_clamp_channel(r));
    return (short) result;
}
CLEAN_AS(func_ov004_02231b98, RoomShell_WdDiffuse)

/* A board of the room as the map's data lists it (10 bytes): its point and reach in whole
 * units of 0x100, its turn in quarter turns (the low two bits) and its message. */
typedef struct RoomShellBoard {
    s16 x;
    s16 y;
    s16 z;
    s16 reach;
    u8 turn;
    u8 message;
} RoomShellBoard;

/* The data of the room an acre of the map points to (at 0x20 of the acre's record), as far as
 * its boards. */
typedef struct RoomShellLayout {
    u8 unk_00[8];
    u8 *model; /* 0x08: the room's model (RoomShell_LoadModel) */
    u8 unk_0c[8];
    const u8 *animation; /* 0x14: its joint animation, NULL for none */
    u8 unk_18[4];
    const u8 *material_anim; /* 0x1c: its material animation, NULL for none */
    G3dResTex *texture;      /* 0x20: its texture resource */
    u8 unk_24[4];
    const RoomShellBoard *boards; /* 0x28 */
    u32 board_count;              /* 0x2c */
} RoomShellLayout;

#define ROOM_SHELL_ACRE_LAYOUT 0x20
#define ROOM_SHELL_UNIT 0x100
#define ROOM_SHELL_QUARTER_TURN 0x4000

static_assert(sizeof(RoomShellBoard) == 10, "board");
static_assert(offsetof(RoomShellLayout, boards) == 0x28, "boards");

/* func_ov004_02231c7c (from the room's start): an obj_etc_board made for each board the map's
 * first acre lists (RoomEtcBoard_Spawn), when the acre has that data.
 * REQUIRES: the map has an acre (both its counts are not 0 and it has records): the ROM reads
 * address 0x20 otherwise; Clean then makes none. */
void RoomShell_SpawnBoards(RoomShell *self)
{
    (void) self;
    AcreMap *map = data_021c80bc;
    if (map->acres_wide == 0 || map->acres_high == 0 || map->acres == NULL) {
        return;
    }
    const RoomShellLayout *layout = *(RoomShellLayout *const *) (void *) (map->acres + ROOM_SHELL_ACRE_LAYOUT);
    if (layout == NULL) {
        return;
    }
    const RoomShellBoard *board = layout->boards;
    if (board == NULL) {
        return;
    }
    for (u32 i = 0; i < layout->board_count; i++, board++) {
        Vec3 position;
        position.x = board->x * ROOM_SHELL_UNIT;
        position.y = board->y * ROOM_SHELL_UNIT;
        position.z = board->z * ROOM_SHELL_UNIT;
        RoomEtcBoard_Spawn(&position, board->reach * ROOM_SHELL_UNIT, (u16) ((board->turn & 3) * ROOM_SHELL_QUARTER_TURN),
                           board->message);
    }
}
CLEAN_AS(func_ov004_02231c7c, RoomShell_SpawnBoards)

/* Whether the code is one the material hook sets up. */
static int RoomShell_code_set_up(const u16 *code)
{
    return *code >= ROOM_SHELL_CODE_FIRST && *code <= ROOM_SHELL_CODE_LAST;
}

/* The material record of `material` in the model's materials (NNSG3dResMat): the data word of
 * the dictionary's entry, an offset from the materials' start. */
static const u8 *RoomShell_material_record(const u8 *materials, u32 material)
{
    const u8 *dict = materials + 4;
    u16 entries = *(const u16 *) (const void *) (materials + 0x0a);
    const u8 *entry = dict + entries;
    u16 unit = *(const u16 *) (const void *) entry;
    const u8 *row = (const u8 *) (uintptr_t) ((uintptr_t) entry + (u32) unit * material);
    return materials + *(const u32 *) (const void *) (row + 4);
}

/* func_ov004_02231cf8 (vtable slot 0x4c, a material's hook): for the wallpaper's material while
 * its second code is from 0x1188 to 0x11a7, or else the carpet's under the same rule, the
 * material's texture is set up for its pattern: taken from the texture coordinates, repeated
 * in S and T and flipped in both when its part's mode is 1, with the texture matrix set
 * (scale given, no rotation, no translation), the material's own size and magnification, and
 * a scale by the room's size: the wallpaper 0x2000 by 0x4000, the carpet 0x2000, 0x3000 or
 * 0x4000 both ways for a room of 4, 6 or 8 (each worked out as FX_Div(0, 0x64000) plus that,
 * so FX_Div is called once or twice). Then bit 8 of the render state's flags is cleared.
 * BUG: a size other than 4, 6 or 8 writes the ROM's stack words that were never set as the
 * scale; Clean writes 0.
 * REQUIRES: the room's size is 4, 6 or 8. */
void RoomShell_MaterialHook(RoomShell *self, u32 material, RoomShellRenderState *state)
{
    const u8 *record = RoomShell_material_record(state->materials, material);
    int wallpaper = material == (u32) (int) MaterialBind_Material(&self->wallpaper_material);
    int carpet = material == (u32) (int) MaterialBind_Material(&self->carpet_material);
    if (!((wallpaper && RoomShell_code_set_up(func_ov004_022329c4(self->wallpaper))) ||
          (carpet && RoomShell_code_set_up(func_ov004_02232738(self->carpet))))) {
        return;
    }

    RoomShellMaterialResult *result = state->material;
    result->texture_image &= ~(ROOM_SHELL_TEXTURE_SOURCE_MASK | ROOM_SHELL_TEXTURE_FLIP_S | ROOM_SHELL_TEXTURE_FLIP_T |
                               ROOM_SHELL_TEXTURE_REPEAT_S | ROOM_SHELL_TEXTURE_REPEAT_T);
    result->texture_image |= ROOM_SHELL_TEXTURE_SOURCE_TEXCOORD;
    int mode = wallpaper ? func_ov004_022329b4(self->wallpaper) : func_ov004_02232728(self->carpet);
    result = state->material;
    result->texture_image |= ROOM_SHELL_TEXTURE_REPEAT_S | ROOM_SHELL_TEXTURE_REPEAT_T;
    if (mode == ROOM_SHELL_MODE_FLIP) {
        result->texture_image |= ROOM_SHELL_TEXTURE_FLIP_S | ROOM_SHELL_TEXTURE_FLIP_T;
    }
    result->flags |= ROOM_SHELL_TEXTURE_MATRIX_SET;
    result->width = *(const u16 *) (const void *) (record + 0x20);
    result->height = *(const u16 *) (const void *) (record + 0x22);
    result->magnify_w = *(const fx32 *) (const void *) (record + 0x24);
    result->magnify_h = *(const fx32 *) (const void *) (record + 0x28);
    result->flags &= ~(u32) ROOM_SHELL_TEXTURE_MATRIX_SCALE_ONE;
    result->flags |= ROOM_SHELL_TEXTURE_MATRIX_ROTATION_ZERO | ROOM_SHELL_TEXTURE_MATRIX_TRANSLATION_ZERO;

    fx32 scale_s = 0;
    fx32 scale_t = 0;
    if (wallpaper) {
        switch (self->size) {
            case ROOM_SHELL_SIZE_4:
            case ROOM_SHELL_SIZE_6:
            case ROOM_SHELL_SIZE_8:
                scale_s = FX_Div(0, ROOM_SHELL_SCALE_DIVISOR) + 0x2000;
                scale_t = FX_Div(0, ROOM_SHELL_SCALE_DIVISOR) + 0x4000;
                break;
        }
    } else {
        switch (self->size) {
            case ROOM_SHELL_SIZE_4:
                scale_s = FX_Div(0, ROOM_SHELL_SCALE_DIVISOR) + 0x2000;
                break;
            case ROOM_SHELL_SIZE_6:
                scale_s = FX_Div(0, ROOM_SHELL_SCALE_DIVISOR) + 0x3000;
                break;
            case ROOM_SHELL_SIZE_8:
                scale_s = FX_Div(0, ROOM_SHELL_SCALE_DIVISOR) + 0x4000;
                break;
        }
        scale_t = scale_s;
    }
    result->scale_s = scale_s;
    result->scale_t = scale_t;
    state->flags &= ~ROOM_SHELL_RENDER_FLAG_8;
}
CLEAN_AS(func_ov004_02231cf8, RoomShell_MaterialHook)

/* func_ov004_02231fcc (vtable slot 0x48, after a node's description): the hour hand's node
 * turned and its translation kept; the minute hand's turned; for node "hasu1" (when there is a
 * state) its X and Z kept at height 0x3700 in data_ov004_02258a30.
 * QUIRK: only the "hasu1" case checks that there is a state. */
void RoomShell_NodeDescHook(RoomShell *self, int node, RoomShellRenderState *state)
{
    if (self->hour_hand_node == node) {
        ClockHands_TurnHourHand((ClockHandsRenderState *) (void *) state);
        self->hour_hand_position = state->joint->translation;
    } else if (self->minute_hand_node == node) {
        ClockHands_TurnMinuteHand((ClockHandsRenderState *) (void *) state);
    } else if (self->hasu1_node == node) {
        if (state != NULL) {
            const RoomShellJoint *joint = state->joint;
            fx32 z = joint->translation.z;
            fx32 x = joint->translation.x;
            data_ov004_02258a30.x = x;
            data_ov004_02258a30.y = ROOM_SHELL_HASU1_HEIGHT;
            data_ov004_02258a30.z = z;
        }
    }
}
CLEAN_AS(func_ov004_02231fcc, RoomShell_NodeDescHook)

/* func_ov004_02232054: the wallpaper's first code (main/room_interior.c changes it). */
u16 *RoomShell_WallpaperCode(void)
{
    RoomShell *self = data_ov004_022589fc;
    if (self != NULL) {
        return func_ov004_022329c0(self->wallpaper);
    }
    return data_ov004_022589ec;
}
CLEAN_AS(func_ov004_02232054, RoomShell_WallpaperCode)

/* func_ov004_02232080: the wallpaper's second code. */
u16 *RoomShell_WallpaperCode2(void)
{
    RoomShell *self = data_ov004_022589fc;
    if (self != NULL) {
        return func_ov004_022329c4(self->wallpaper);
    }
    return data_ov004_022589ec;
}
CLEAN_AS(func_ov004_02232080, RoomShell_WallpaperCode2)

/* func_ov004_022320ac: the carpet's first code (main/room_interior.c changes it). */
u16 *RoomShell_CarpetCode(void)
{
    RoomShell *self = data_ov004_022589fc;
    if (self != NULL) {
        return func_ov004_02232734(self->carpet);
    }
    return data_ov004_022589ec;
}
CLEAN_AS(func_ov004_022320ac, RoomShell_CarpetCode)

/* func_ov004_022320d8: the carpet's second code (the floor's item for its sounds,
 * main/ground_sound.c). */
u16 *RoomShell_CarpetCode2(void)
{
    RoomShell *self = data_ov004_022589fc;
    if (self != NULL) {
        return func_ov004_02232738(self->carpet);
    }
    return data_ov004_022589ec;
}
CLEAN_AS(func_ov004_022320d8, RoomShell_CarpetCode2)

/* The room's process (vtable 0x02255ac8): its creation (slot 0), release (slot 3), each
 * frame's work (slot 6) and drawing (slot 9), its destructors (slots 0x40 and 0x44), its
 * constructor and its profile's maker. */

static_assert(offsetof(RoomShell, model) == 0x50, "model");
static_assert(offsetof(RoomShell, material_anim) == 0x108, "material anim");
static_assert(offsetof(RoomShell, boxes) == 0x3328, "boxes");
static_assert(offsetof(RoomShell, box) == 0x3460, "box");
static_assert(offsetof(RoomShell, touch) == 0x34fc, "touch");
static_assert(offsetof(RoomShell, sound) == 0x3534, "sound");
static_assert(offsetof(RoomShell, wd_material) == 0x3540, "wd material");
static_assert(sizeof(RoomShell) == 0x3544, "room shell");
static_assert(sizeof(RoomWallpaper) == offsetof(RoomShell, carpet) - offsetof(RoomShell, wallpaper), "wallpaper part");
static_assert(sizeof(RoomCarpet) == offsetof(RoomShell, boxes) - offsetof(RoomShell, carpet), "carpet part");
static_assert(offsetof(RoomShellLayout, model) == 0x08, "layout model");
static_assert(offsetof(RoomShellLayout, animation) == 0x14, "layout animation");
static_assert(offsetof(RoomShellLayout, material_anim) == 0x1c, "layout material anim");
static_assert(offsetof(RoomShellLayout, texture) == 0x20, "layout texture");

/* The classes: the room's and the process base's. */
extern const u32 data_ov004_02255ac8[];
extern const u32 data_020da13c[];
/* The sound source's class (sound_emitter.h). */
extern const u32 data_0213efe8[];

/* The heap the room's animations are allocated from. */
extern Heap *data_021c9b24;
/* The rooms' records (house_record.h) and the town's villagers (villager_town.h). */
extern HouseRecord data_021ebcd4;
extern u8 data_021e5a2c[];
/* The scratch matrix of main. */
extern Mtx43 data_021fbe48;
/* The spheres a swing of the net is tested against (catch_sphere.h), cleared each frame. */
extern void *data_021d3124;

/* The nodes and the material the creation looks for. */
extern const char data_ov004_02255b50[]; /* "kh_j" */
extern const char data_ov004_02255b58[]; /* "km_j" */
extern const char data_ov004_02255b60[]; /* "hasu1" */
extern const char data_ov004_02255b68[]; /* "wd" */

/* Nook's shops' own wallpaper and carpet for each of their six scenes, used while the scene's
 * own is not one: function-local statics built on first use (their guards, bit 0 of each),
 * each item registered for destruction with its record. */
extern u32 data_ov004_022589f4;
extern u32 data_ov004_022589f8;
extern ItemCode data_ov004_02258a6c[];
extern ItemCode data_ov004_02258a18[];
extern u8 data_ov004_02258ac0[], data_ov004_02258ab4[], data_ov004_02258a0c[], data_ov004_02258a9c[], data_ov004_02258a90[],
    data_ov004_02258a60[];
extern u8 data_ov004_02258a78[], data_ov004_02258aa8[], data_ov004_02258acc[], data_ov004_02258a3c[], data_ov004_02258a00[],
    data_ov004_02258a24[];

/* The frame of the room's shared frame counter (clock.h). */
extern u16 func_ov004_0223c1e0(void);
extern void NNS_G3dMdlSetMdlDiff(u8 *model, int material, u16 diffuse);
extern void __register_global_object(void *object, void *destruct, void *record);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

/* The animated model's and ModelAnim's functions (animated_model.h, model_anim.h), declared
 * here on their structures' tags: animated_model.h cannot be included next to
 * room_object_methods.h (both define G3dRenderObject). */
struct AnimatedModel;
struct AnimatedModelAnim;
struct ModelAnim;
struct AnimatedModelAnim *AnimatedModel_Anim(struct AnimatedModel *model);
void AnimatedModel_Attach(struct AnimatedModel *model);
void AnimatedModel_Start(struct AnimatedModel *model, const u8 *file, int flags, fx32 speed, u16 start, u16 frames);
void AnimatedModel_Draw(struct AnimatedModel *model, const Vec3 *scale);
void AnimatedModel_StepFrames(struct AnimatedModel *model);
int AnimatedModel_LoadAnim(struct AnimatedModel *model, Heap *heap);
struct AnimatedModel *AnimatedModel_DestructComplete(struct AnimatedModel *model);
struct AnimatedModel *AnimatedModel_Construct(struct AnimatedModel *model);
void ModelAnim_Attach(struct ModelAnim *anim, ModelRenderObject *render);
void ModelAnim_Start(struct ModelAnim *anim, const u8 *file, int flags, fx32 speed, u16 start);
int ModelAnim_AllocMaterialAnim(struct ModelAnim *anim, u8 *model, Heap *heap);

/* Functions handed to the game: its symbols. */
extern void func_ov004_02231b38(NodeHookState *state);
extern RoomShellMaterialAnim *func_ov004_022324d8(RoomShellMaterialAnim *anim);
extern RoomShellMaterialAnim *func_ov004_022324f0(RoomShellMaterialAnim *anim);
extern void func_020051b0(void *item);

/* The item ranges of wallpaper and carpets, and their counts. */
#define ROOM_SHELL_WALLPAPER_FIRST 0x1100
#define ROOM_SHELL_WALLPAPER_LAST 0x1143
#define ROOM_SHELL_CARPET_FIRST 0x1144
#define ROOM_SHELL_CARPET_LAST 0x1187
#define ROOM_SHELL_WALLPAPER_COUNT 0x44
#define ROOM_SHELL_CARPET_COUNT 0x44

/* The wallpaper and carpet put up under a player's design. */
#define ROOM_SHELL_WALLPAPER_UNDER_DESIGN 0x1124
#define ROOM_SHELL_CARPET_UNDER_DESIGN 0x1182

/* The animations' speed, 1.0. */
#define ROOM_SHELL_SPEED_ONE 0x1000

/* The sound played on a change in Nook's shop. */
#define ROOM_SHELL_SE_CHANGE 0x50
/* The clock's tick, at frames 9 and 0x1d of the shared counter. */
#define ROOM_SHELL_SE_TICK 0x4d1
#define ROOM_SHELL_TICK_FRAME_1 9
#define ROOM_SHELL_TICK_FRAME_2 0x1d

/* The model's materials' polygon attributes: the lights they are lit by (bits 0-3). */
#define ROOM_SHELL_MATERIAL_LIGHTS 0xfu

/* The units RoomShell_MeasureSize looks at: x 0 to 15 on the row z 10. */
#define ROOM_SHELL_MEASURE_UNITS 16
#define ROOM_SHELL_MEASURE_ROW 10

#define ROOM_SHELL_NOOK_SCENES 6

static RoomWallpaper *RoomShell_wallpaper(RoomShell *self)
{
    return (RoomWallpaper *) (void *) self->wallpaper;
}

static RoomCarpet *RoomShell_carpet(RoomShell *self)
{
    return (RoomCarpet *) (void *) self->carpet;
}

static struct AnimatedModel *RoomShell_animated(RoomShell *self)
{
    return (struct AnimatedModel *) (void *) &self->model;
}

static struct ModelAnim *RoomShell_material_anim(RoomShell *self)
{
    return (struct ModelAnim *) (void *) &self->material_anim;
}

static int RoomShell_in(ItemCode code, ItemCode first, ItemCode last)
{
    return code >= first && code <= last;
}

static int RoomShell_is_design(ItemCode code)
{
    return RoomShell_in(code, ROOM_SHELL_CODE_FIRST, ROOM_SHELL_CODE_LAST);
}

/* func_ov004_02232104 (main/room_interior.c): the room's carpet changed to `*item` (a carpet or
 * a player's design) with `mode`, and sound 0x50 in Nook's shop when `with_sound`; the carpet
 * it replaced when that is a carpet, else data_ov004_022589ec (also when nothing changed). */
u16 *RoomShell_SetCarpet(u16 *item, int mode, int with_sound)
{
    ItemCode code = *item;
    if (!RoomShell_in(code, ROOM_SHELL_CARPET_FIRST, ROOM_SHELL_CARPET_LAST) && !RoomShell_is_design(code)) {
        return data_ov004_022589ec;
    }
    RoomShell *self = data_ov004_022589fc;
    if (self == NULL || !RoomCarpet_Set(RoomShell_carpet(self), item, self->model.object.model, mode)) {
        return data_ov004_022589ec;
    }
    if (with_sound != 0 && SceneQuery_CurrentInNook()) {
        SoundSys_PlaySe(ROOM_SHELL_SE_CHANGE);
    }
    ItemCode replaced = *RoomCarpet_Replaced(RoomShell_carpet(data_ov004_022589fc));
    if (RoomShell_in(replaced, ROOM_SHELL_CARPET_FIRST, ROOM_SHELL_CARPET_LAST)) {
        return RoomCarpet_Replaced(RoomShell_carpet(data_ov004_022589fc));
    }
    return data_ov004_022589ec;
}
CLEAN_AS(func_ov004_02232104, RoomShell_SetCarpet)

/* func_ov004_022321b8 (main/room_interior.c): RoomShell_SetCarpet for the wallpaper. */
u16 *RoomShell_SetWallpaper(u16 *item, int mode, int with_sound)
{
    ItemCode code = *item;
    if (!RoomShell_in(code, ROOM_SHELL_WALLPAPER_FIRST, ROOM_SHELL_WALLPAPER_LAST) && !RoomShell_is_design(code)) {
        return data_ov004_022589ec;
    }
    RoomShell *self = data_ov004_022589fc;
    if (self == NULL || !RoomWallpaper_Set(RoomShell_wallpaper(self), item, self->model.object.model, mode)) {
        return data_ov004_022589ec;
    }
    if (with_sound != 0 && SceneQuery_CurrentInNook()) {
        SoundSys_PlaySe(ROOM_SHELL_SE_CHANGE);
    }
    ItemCode replaced = *RoomWallpaper_Replaced(RoomShell_wallpaper(data_ov004_022589fc));
    if (RoomShell_in(replaced, ROOM_SHELL_WALLPAPER_FIRST, ROOM_SHELL_WALLPAPER_LAST)) {
        return RoomWallpaper_Replaced(RoomShell_wallpaper(data_ov004_022589fc));
    }
    return data_ov004_022589ec;
}
CLEAN_AS(func_ov004_022321b8, RoomShell_SetWallpaper)

/* func_ov004_02232a20 (at the start): each of the model's materials lit by any light is lit by
 * the room's lights instead (SceneLights_RoomMaterialLights). */
void RoomShell_LightMaterials(RoomShell *self, u8 *model)
{
    (void) self;
    u32 count = model[0x18];
    const u8 *materials = (const u8 *) (uintptr_t) ((uintptr_t) model + *(const u32 *) (const void *) (model + 8));
    for (u32 i = 0; i < count; i++) {
        u32 *attributes = (u32 *) (uintptr_t) (RoomShell_material_record(materials, i) + 0xc);
        if ((*attributes & ROOM_SHELL_MATERIAL_LIGHTS) != 0) {
            *attributes &= ~ROOM_SHELL_MATERIAL_LIGHTS;
            *attributes |= (u32) SceneLights_RoomMaterialLights();
        }
    }
}
CLEAN_AS(func_ov004_02232a20, RoomShell_LightMaterials)

/* func_ov004_02232a68 (at the start): the model's base matrix made the identity. */
void RoomShell_ResetMatrix(RoomShell *self)
{
    Mtx43_Translation(&data_021fbe48, 0, 0, 0);
    memcpy(self->model.object.unk_64, &data_021fbe48, sizeof(Mtx43));
}
CLEAN_AS(func_ov004_02232a68, RoomShell_ResetMatrix)

/* The room's data of the map's first acre, NULL when the map has no acre. */
static const RoomShellLayout *RoomShell_layout(void)
{
    AcreMap *map = data_021c80bc;
    if (map->acres_wide == 0 || map->acres_high == 0 || map->acres == NULL) {
        return NULL;
    }
    return *(RoomShellLayout *const *) (void *) (map->acres + ROOM_SHELL_ACRE_LAYOUT);
}

/* func_ov004_02232a94 (at the start): the room's model and texture resource from the map's
 * room data, then its joint animation and its material animation (each when there is one and
 * the heap has room for it) started at frame 0 at speed 1.0 and attached.
 * REQUIRES: the map has an acre (the ROM reads address 0x20 otherwise; Clean does nothing). */
void RoomShell_LoadModel(RoomShell *self)
{
    const RoomShellLayout *layout = RoomShell_layout();
    if (layout == NULL) {
        return;
    }
    struct AnimatedModel *animated = RoomShell_animated(self);
    ModelObject_SetModelTexture(&self->model.object, layout->model, layout->texture);
    if (layout->animation != NULL && AnimatedModel_LoadAnim(animated, data_021c9b24)) {
        AnimatedModel_Start(animated, layout->animation, 0, ROOM_SHELL_SPEED_ONE, 0, 0);
        AnimatedModel_Attach(animated);
    }
    if (layout->material_anim != NULL &&
        ModelAnim_AllocMaterialAnim(RoomShell_material_anim(self), self->model.object.model, data_021c9b24)) {
        ModelAnim_Start(RoomShell_material_anim(self), layout->material_anim, 0, ROOM_SHELL_SPEED_ONE, 0);
        ModelAnim_Attach(RoomShell_material_anim(self), ModelObject_RenderObject(&self->model.object));
    }
}
CLEAN_AS(func_ov004_02232a94, RoomShell_LoadModel)

/* func_ov004_02232b48 (at the start): the wallpaper's and carpet's materials picked (with the
 * room's texture resource), then the scene's wallpaper and carpet put up; a player's design
 * goes over wallpaper 0x1124 or carpet 0x1182, put up first.
 * REQUIRES: the map has an acre (as RoomShell_LoadModel). */
void RoomShell_LoadSurfaces(RoomShell *self)
{
    const RoomShellLayout *layout = RoomShell_layout();
    if (layout == NULL) {
        return;
    }
    RoomWallpaper *wallpaper = RoomShell_wallpaper(self);
    RoomCarpet *carpet = RoomShell_carpet(self);
    RoomWallpaper_PickMaterial(wallpaper, self->model.object.model, layout->texture);
    RoomCarpet_PickMaterial(carpet, self->model.object.model, layout->texture);

    ItemCode wallpaper_code = ITEM_CODE_NONE;
    ItemCode carpet_code = ITEM_CODE_NONE;
    int wallpaper_mode;
    int carpet_mode;
    RoomShell_SceneSurfaces(self, &wallpaper_code, &wallpaper_mode, &carpet_code, &carpet_mode);
    if (RoomShell_is_design(wallpaper_code)) {
        RoomWallpaper_SetCode(wallpaper, ROOM_SHELL_WALLPAPER_UNDER_DESIGN, self->model.object.model, wallpaper_mode);
    }
    if (RoomShell_is_design(carpet_code)) {
        RoomCarpet_SetCode(carpet, ROOM_SHELL_CARPET_UNDER_DESIGN, self->model.object.model, carpet_mode);
    }
    RoomWallpaper_Set(wallpaper, &wallpaper_code, self->model.object.model, wallpaper_mode);
    RoomCarpet_Set(carpet, &carpet_code, self->model.object.model, carpet_mode);
}
CLEAN_AS(func_ov004_02232b48, RoomShell_LoadSurfaces)

/* Nook's shops' own wallpaper and carpet of scene `slot`, the table built on first use. */
static ItemCode RoomShell_nook_wallpaper(int slot)
{
    static const ItemCode codes[ROOM_SHELL_NOOK_SCENES] = {0x1140, 0x1141, 0x1142, 0x1143, 0x1143, 0x1143};
    u8 *const records[ROOM_SHELL_NOOK_SCENES] = {data_ov004_02258ac0, data_ov004_02258ab4, data_ov004_02258a0c,
                                                 data_ov004_02258a9c, data_ov004_02258a90, data_ov004_02258a60};
    if ((data_ov004_022589f4 & 1) == 0) {
        for (int i = 0; i < ROOM_SHELL_NOOK_SCENES; i++) {
            data_ov004_02258a6c[i] = codes[i];
            __register_global_object(&data_ov004_02258a6c[i], (void *) (uintptr_t) func_020051b0, records[i]);
        }
        data_ov004_022589f4 |= 1;
    }
    return data_ov004_02258a6c[slot];
}

static ItemCode RoomShell_nook_carpet(int slot)
{
    static const ItemCode codes[ROOM_SHELL_NOOK_SCENES] = {0x1184, 0x1185, 0x1186, 0x1187, 0x1187, 0x1187};
    u8 *const records[ROOM_SHELL_NOOK_SCENES] = {data_ov004_02258a78, data_ov004_02258aa8, data_ov004_02258acc,
                                                 data_ov004_02258a3c, data_ov004_02258a00, data_ov004_02258a24};
    if ((data_ov004_022589f8 & 1) == 0) {
        for (int i = 0; i < ROOM_SHELL_NOOK_SCENES; i++) {
            data_ov004_02258a18[i] = codes[i];
            __register_global_object(&data_ov004_02258a18[i], (void *) (uintptr_t) func_020051b0, records[i]);
        }
        data_ov004_022589f8 |= 1;
    }
    return data_ov004_02258a18[slot];
}

/* func_ov004_02232c48: the current scene's wallpaper and carpet with their modes (the modes are
 * 0 unless a house room's record gives them; the codes are left as they were when there is
 * nothing to read):
 * - a room of the player's house: from the room's record;
 * - scenes 0x11-0x18 (the villagers' houses): the villager's wallpaper and carpet (the first
 *   for an index of 0x44 or more);
 * - Nook's scenes: the scene's own (room_interior.h), or while that is not a wallpaper (a
 *   carpet) the shop's: wallpaper 0x1140, 0x1141, 0x1142, 0x1143, 0x1143, 0x1143 (carpet
 *   0x1184 to 0x1187 alike) for its six scenes. */
void RoomShell_SceneSurfaces(RoomShell *self, u16 *wallpaper, int *wallpaper_mode, u16 *carpet, int *carpet_mode)
{
    (void) self;
    unsigned int scene = SceneQuery_Current();
    *carpet_mode = 0;
    *wallpaper_mode = *carpet_mode;

    if (SceneKinds_IsHouseRoom(scene)) {
        HouseRoom *room = HouseRecord_Room(&data_021ebcd4, SceneKinds_HouseRoomIndex(scene));
        if (room == NULL) {
            return;
        }
        *wallpaper = *HouseRecord_RoomWallpaper(room, wallpaper_mode);
        *carpet = *HouseRecord_RoomCarpet(room, (unsigned int *) carpet_mode);
        return;
    }
    if (SceneQuery_In11((int) scene)) {
        u8 *villager = VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, SceneQuery_IndexIn11(scene));
        if (villager == NULL) {
            return;
        }
        u8 index = VillagerFurniture_Wallpaper(villager);
        *wallpaper =
            (u16) (index < ROOM_SHELL_WALLPAPER_COUNT ? ROOM_SHELL_WALLPAPER_FIRST + index : ROOM_SHELL_WALLPAPER_FIRST);
        index = VillagerFurniture_Carpet(villager);
        *carpet = (u16) (index < ROOM_SHELL_CARPET_COUNT ? ROOM_SHELL_CARPET_FIRST + index : ROOM_SHELL_CARPET_FIRST);
        return;
    }
    if (!SceneQuery_InNook(scene)) {
        return;
    }
    int slot = SceneQuery_IndexInNook(scene);
    ItemCode code = *RoomInterior_SceneWallpaper(scene);
    if (RoomShell_in(code, ROOM_SHELL_WALLPAPER_FIRST, ROOM_SHELL_WALLPAPER_LAST)) {
        *wallpaper = code;
    } else {
        *wallpaper = RoomShell_nook_wallpaper(slot);
    }
    code = *RoomInterior_SceneCarpet(scene);
    if (RoomShell_in(code, ROOM_SHELL_CARPET_FIRST, ROOM_SHELL_CARPET_LAST)) {
        *carpet = code;
    } else {
        *carpet = RoomShell_nook_carpet(slot);
    }
}
CLEAN_AS(func_ov004_02232c48, RoomShell_SceneSurfaces)

/* func_ov004_02232edc (at the start): the room's size, the number of the field's units x 0 to
 * 15 on row z 10 whose ground is at height 0. */
void RoomShell_MeasureSize(RoomShell *self)
{
    int count = 0;
    for (int x = 0; x < ROOM_SHELL_MEASURE_UNITS; x++) {
        CollisionGround ground;
        CollisionGround_InitAtUnit(&ground, x, ROOM_SHELL_MEASURE_ROW, 0, 0);
        if (CollisionGround_GetHeight(&ground, 0) == 0) {
            count++;
        }
        CollisionGround_Destroy(&ground);
    }
    self->size = (s8) count;
}
CLEAN_AS(func_ov004_02232edc, RoomShell_MeasureSize)

/* func_ov004_02232f24 (vtable slot 3, the release): the copies ended, the boxes taken off the
 * field, the render object released, the sound released; no room any more. Done. */
int RoomShell_Release(RoomShell *self)
{
    RoomWallpaper_End(RoomShell_wallpaper(self));
    RoomShellTouch_Remove(&self->touch);
    RoomShellBox_Remove(&self->box);
    RoomCarpet_End(RoomShell_carpet(self));
    RoomShellBoxes_Remove(self->boxes);
    ModelObject_ReleaseRender(&self->model.object);
    data_ov004_022589fc = NULL;
    SoundSource_Release(&self->sound);
    return 1;
}
CLEAN_AS(func_ov004_02232f24, RoomShell_Release)

/* func_ov004_02232f8c (vtable slot 9, the drawing): the shadows' light and frame begun,
 * material "wd" given its colour from the sky (RoomShell_WdDiffuse), the model drawn. */
int RoomShell_Draw(RoomShell *self)
{
    ShadowLight_Update();
    CharaShadow_BeginFrame();
    if (self->wd_material != -1) {
        u16 colour = (u16) RoomShell_WdDiffuse(self);
        NNS_G3dMdlSetMdlDiff(self->model.object.model, self->wd_material, colour);
    }
    AnimatedModel_Draw(RoomShell_animated(self), NULL);
    return 1;
}
CLEAN_AS(func_ov004_02232f8c, RoomShell_Draw)

/* func_ov004_02232fdc (vtable slot 6, each frame): the animations stepped (the material
 * animation's frame copied into its animation object); with a clock's hour hand (its X not 0),
 * its tick at frames 9 and 0x1d of the shared counter; the sound kept at the hour hand; the
 * touch cylinder offered; the net's spheres cleared. Done. */
int RoomShell_Execute(RoomShell *self)
{
    struct AnimatedModel *animated = RoomShell_animated(self);
    if (AnimatedModel_Anim(animated) != NULL) {
        AnimatedModel_StepFrames(animated);
    }
    RoomShellMaterialAnim *anim = &self->material_anim;
    if (RoomShellMaterialAnim_Anim(anim) != 0) {
        FrameCtrl_Step(&anim->ctrl);
        anim->anim->frame = anim->ctrl.frame;
    }
    if (self->hour_hand_position.x != 0) {
        u16 frame = func_ov004_0223c1e0();
        if (frame == ROOM_SHELL_TICK_FRAME_1 || frame == ROOM_SHELL_TICK_FRAME_2) {
            SoundSource_PlayHeld(&self->sound, ROOM_SHELL_SE_TICK);
        }
    }
    Vec3 at = self->hour_hand_position;
    SoundSource_UpdateAt(&self->sound, &at);
    RoomShellTouch_Offer(&self->touch);
    data_021d3124 = NULL;
    return 1;
}
CLEAN_AS(func_ov004_02232fdc, RoomShell_Execute)

/* func_ov004_02233084 (vtable slot 0, the creation): this is the room from now on; its boxes,
 * touch cylinder, size, model, lights, base matrix, wallpaper and carpet set up, the clock's
 * hands' and "hasu1"'s nodes and material "wd" found, the model's init hook set (which sets
 * its draw hooks, RoomShell_SetModelHooks), the boards made and the sound started. Done. */
int RoomShell_Create(RoomShell *self)
{
    data_ov004_022589fc = self;
    RoomShellBoxes_Add(self->boxes);
    RoomShellBox_Add(&self->box);
    RoomShellTouch_Init(&self->touch);
    RoomShell_MeasureSize(self);
    RoomShell_LoadModel(self);
    RoomShell_LightMaterials(self, self->model.object.model);
    RoomShell_ResetMatrix(self);
    RoomShell_LoadSurfaces(self);
    self->hour_hand_node = (s8) G3dRes_NodeIndex(self->model.object.model, data_ov004_02255b50);
    self->minute_hand_node = (s8) G3dRes_NodeIndex(self->model.object.model, data_ov004_02255b58);
    self->hasu1_node = (s8) G3dRes_NodeIndex(self->model.object.model, data_ov004_02255b60);
    self->wd_material = (s8) G3dRes_MaterialIndex(self->model.object.model, data_ov004_02255b68);
    ModelObject_SetInitHook(&self->model.object, (void *) (uintptr_t) func_ov004_02231b38, self);
    RoomShell_SpawnBoards(self);
    SoundSource_Init(&self->sound);
    return 1;
}
CLEAN_AS(func_ov004_02233084, RoomShell_Create)

/* The members taken down, in reverse order of their construction, then the base.
 * QUIRK: the sound source is not taken down. */
static void RoomShell_destruct_members(RoomShell *self)
{
    self->base.vtable = data_ov004_02255ac8;
    RoomShellTouch_Destruct(&self->touch);
    CollisionBox_Destruct(&self->box);
    RoomShellBoxes_Destruct(self->boxes);
    RoomCarpet_Destruct(RoomShell_carpet(self));
    RoomWallpaper_Destruct(RoomShell_wallpaper(self));
    __cxa_vec_cleanup(&self->material_anim, 1, sizeof(RoomShellMaterialAnim),
                      (void (*)(void *))(uintptr_t) func_ov004_022324d8);
    AnimatedModel_DestructComplete(RoomShell_animated(self));
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
}

/* func_ov004_02233164 (the deleting destructor, vtable slot 0x44) */
RoomShell *RoomShell_Delete(RoomShell *self)
{
    RoomShell_destruct_members(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_02233164, RoomShell_Delete)

/* func_ov004_022331e8 (the destructor, vtable slot 0x40) */
RoomShell *RoomShell_Destruct(RoomShell *self)
{
    RoomShell_destruct_members(self);
    return self;
}
CLEAN_AS(func_ov004_022331e8, RoomShell_Destruct)

/* func_ov004_02233264 (the constructor): the base's vtable set before the class's; no clock
 * hands and no material "wd" until the creation finds them. */
RoomShell *RoomShell_Construct(RoomShell *self)
{
    Process_Construct(&self->base);
    self->base.vtable = data_020da13c;
    self->base.vtable = data_ov004_02255ac8;
    AnimatedModel_Construct(RoomShell_animated(self));
    __cxa_vec_ctor(&self->material_anim, 1, sizeof(RoomShellMaterialAnim), (void (*)(void *))(uintptr_t) func_ov004_022324f0,
                   (void (*)(void *))(uintptr_t) func_ov004_022324d8);
    RoomWallpaper_Construct(RoomShell_wallpaper(self));
    RoomCarpet_Construct(RoomShell_carpet(self));
    RoomShellBoxes_Construct(self->boxes);
    CollisionBox_Construct(&self->box);
    RoomShellTouch_Construct(&self->touch);
    self->sound.vtable = (const SoundSourceVtable *) (const void *) data_0213efe8;
    self->wd_material = -1;
    self->minute_hand_node = -1;
    self->hour_hand_node = -1;
    return self;
}
CLEAN_AS(func_ov004_02233264, RoomShell_Construct)

/* func_ov004_02233318 (the profile's maker): a new one from the room's heap; nothing when it
 * has no room. */
void RoomShell_New(void)
{
    RoomShell *self = Heap_AllocAuxZeroed(sizeof(RoomShell));
    if (self != NULL) {
        RoomShell_Construct(self);
    }
}
CLEAN_AS(func_ov004_02233318, RoomShell_New)
