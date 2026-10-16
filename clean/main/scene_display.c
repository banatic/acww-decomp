/* The display of a scene on the field (scene_display.h). */
#include "scene_display.h"

#include "clean.h"
#include "main/caution_window.h"
#include "main/display_frame.h"
#include "main/display_shadow.h"
#include "main/model_cache.h"

static_assert(offsetof(SceneFog, enabled) == 0x20, "enabled");
static_assert(offsetof(SceneFog, offset) == 0x22, "offset");
static_assert(offsetof(SceneFog, color) == 0x24, "color");
static_assert(offsetof(SceneFog, alpha) == 0x26, "alpha");

#define REG32(addr) (*(volatile u32 *) (uintptr_t) (addr))
#define REG_DISPCNT 0x04000000u
#define REG_DB_DISPCNT 0x04001000u
#define REG_FOG_COLOR 0x04000358u
/* DISPCNT: the OBJ characters' 1D mapping and its boundary; the main engine's character base. */
#define DISPCNT_OBJ_1D_MAPPING 0x00300010u
#define DISPCNT_CHAR_BASE 0x38000000u
/* FOG_COLOR: the alpha above the color. */
#define FOG_COLOR_ALPHA_SHIFT 16
#define FOG_ALPHA_MASK 0x1f

/* The VRAM banks (GX_VRAM_*): A-C for textures, E for their palettes, F and G for the main
 * engine's backgrounds and OBJ, H and I for the sub engine's. */
#define SCENE_DISPLAY_BANKS_TEX 0x07
#define SCENE_DISPLAY_BANK_TEX_PLTT 0x10
#define SCENE_DISPLAY_BANK_BG 0x20
#define SCENE_DISPLAY_BANK_OBJ 0x40
#define SCENE_DISPLAY_BANK_SUB_BG 0x80
#define SCENE_DISPLAY_BANK_SUB_OBJ 0x100
/* The BG modes, and the planes shown: BG0 and OBJ on the main engine, OBJ on the sub one. */
#define SCENE_DISPLAY_MAIN_BG_MODE 0
#define SCENE_DISPLAY_SUB_BG_MODE 1
#define SCENE_DISPLAY_MAIN_PLANES 0x11
#define SCENE_DISPLAY_SUB_PLANES 0x10

/* The fog a scene starts with: alpha blending only, slope 8 (GX_FOGSLOPE_0x0800), from depth
 * 0xd2, in white with alpha 0; on outdoors, off in the rooms. */
#define SCENE_FOG_BLEND_ALPHA 1
#define SCENE_FOG_START_SLOPE 8
#define SCENE_FOG_START_OFFSET 0xd2
#define SCENE_FOG_START_COLOR 0x7fff
#define SCENE_FOG_START_ALPHA 0
/* The mode of data_020e54a8 that is a room. */
#define SCENE_DISPLAY_MODE_ROOM 1

/* The fog's settings. */
extern SceneFog data_021f69ec;
/* The density table a scene starts with. */
extern const u8 data_020e5518[SCENE_FOG_TABLE_SIZE];
/* The mode: 0 outdoors, 1 in a room. */
extern u8 data_020e54a8;

extern void GX_SetBankForTex(int banks);
extern void GX_SetBankForTexPltt(int banks);
extern void GX_SetBankForBG(int banks);
extern void GX_SetBankForOBJ(int banks);
extern void GX_SetBankForSubBG(int banks);
extern void GX_SetBankForSubOBJ(int banks);
extern void G3X_SetFog(int enable, int blend, int slope, int offset);
extern void G3X_SetFogTable(const u32 *table);
/* Two resets of display state (also at the boot screen's set-up). */
extern void func_020b98dc(void);
extern void func_020b9990(void);
/* The texture and palette VRAM managers set up on the banks. */
extern void func_020b947c(void);

/* func_020b68ac: the scene's display hook after the VBlank: nothing. */
void SceneDisplay_AfterVBlank(void) {}
CLEAN_AS(func_020b68ac, SceneDisplay_AfterVBlank)

/* func_020b68b0: the fog's density table copied from `table`. */
void SceneDisplay_SetFogTable(int unused, const u8 *table)
{
    (void) unused;
    for (int i = 0; i < SCENE_FOG_TABLE_SIZE; i++) {
        data_021f69ec.table[i] = table[i];
    }
}
CLEAN_AS(func_020b68b0, SceneDisplay_SetFogTable)

/* func_020b68c8: the depth the fog starts at (its low 16 bits). */
void SceneDisplay_SetFogOffset(unsigned int offset)
{
    data_021f69ec.offset = (u16) offset;
}
CLEAN_AS(func_020b68c8, SceneDisplay_SetFogOffset)

/* func_020b68d4: the fog's alpha (its low five bits). */
void SceneDisplay_SetFogAlpha(int alpha)
{
    data_021f69ec.alpha = (u8) (alpha & FOG_ALPHA_MASK);
}
CLEAN_AS(func_020b68d4, SceneDisplay_SetFogAlpha)

/* func_020b68e4: the caution window closed and the model cache's heap freed. */
void SceneDisplay_TearDown(void)
{
    CautionWindow_CloseGlobal();
    ModelCache_FreeHeap();
}
CLEAN_AS(func_020b68e4, SceneDisplay_TearDown)

/* func_020b68f8: the display reset and set up for a scene: the VRAM banks, the BG modes, the
 * texture managers, the planes shown, the model cache and the caution window.
 * HW: DISPCNT of both engines loses the OBJ 1D mapping bits, then the main one its character
 * base, at these points between the calls. */
void SceneDisplay_SetUp(void)
{
    DisplayFrame_ResetState();
    func_020b98dc();
    func_020b9990();
    DisplayFrame_ReleaseVram();
    GX_SetBankForTex(SCENE_DISPLAY_BANKS_TEX);
    GX_SetBankForTexPltt(SCENE_DISPLAY_BANK_TEX_PLTT);
    GX_SetBankForBG(SCENE_DISPLAY_BANK_BG);
    GX_SetBankForOBJ(SCENE_DISPLAY_BANK_OBJ);
    GX_SetBankForSubBG(SCENE_DISPLAY_BANK_SUB_BG);
    GX_SetBankForSubOBJ(SCENE_DISPLAY_BANK_SUB_OBJ);
    REG32(REG_DISPCNT) &= ~DISPCNT_OBJ_1D_MAPPING;
    REG32(REG_DB_DISPCNT) &= ~DISPCNT_OBJ_1D_MAPPING;
    Display_SetMainBgModeNow(SCENE_DISPLAY_MAIN_BG_MODE);
    Display_SetSubBgModeNow(SCENE_DISPLAY_SUB_BG_MODE);
    REG32(REG_DISPCNT) &= ~DISPCNT_CHAR_BASE;
    func_020b947c();
    DisplayShadow_ShowMainPlanes(SCENE_DISPLAY_MAIN_PLANES);
    DisplayShadow_ShowSubPlanes(SCENE_DISPLAY_SUB_PLANES);
    ModelCache_Init();
    CautionWindow_StartGlobal();
}
CLEAN_AS(func_020b68f8, SceneDisplay_SetUp)

/* func_020b698c: the fog's settings given to the 3D engine.
 * HW: G3X_SetFog, then FOG_COLOR written, then the density table. */
void SceneDisplay_ApplyFog(void *unused)
{
    (void) unused;
    G3X_SetFog(data_021f69ec.enabled, SCENE_FOG_BLEND_ALPHA, data_021f69ec.slope, data_021f69ec.offset);
    REG32(REG_FOG_COLOR) = data_021f69ec.color | ((u32) data_021f69ec.alpha << FOG_COLOR_ALPHA_SHIFT);
    G3X_SetFogTable((const u32 *) (const void *) data_021f69ec.table);
}
CLEAN_AS(func_020b698c, SceneDisplay_ApplyFog)

/* func_020b69c8: the fog a scene starts with (on outdoors, off in a room), applied at once. */
void SceneDisplay_ResetFog(void *unused)
{
    SceneDisplay_SetFogTable((int) (uintptr_t) unused, data_020e5518);
    data_021f69ec.enabled = data_020e54a8 != SCENE_DISPLAY_MODE_ROOM;
    data_021f69ec.slope = SCENE_FOG_START_SLOPE;
    data_021f69ec.offset = SCENE_FOG_START_OFFSET;
    data_021f69ec.color = SCENE_FOG_START_COLOR;
    data_021f69ec.alpha = SCENE_FOG_START_ALPHA;
    SceneDisplay_ApplyFog(unused);
}
CLEAN_AS(func_020b69c8, SceneDisplay_ResetFog)
