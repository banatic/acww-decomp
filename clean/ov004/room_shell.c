/* The model of the room itself (room_shell.h). */
#include "room_shell.h"

#include <stdint.h>

#include "clean.h"
#include "main/acre_map.h"
#include "main/clock_hands.h"
#include "main/sky.h"
#include "room_etc_board.h"

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
    u8 unk_00[0x28];
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
