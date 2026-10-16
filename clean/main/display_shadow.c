/* The copy of the 2D display registers (display_shadow.h). */
#include "display_shadow.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"

static_assert(offsetof(DisplayShadow, window_dirty) == 0x12, "DisplayShadow layout");
static_assert(offsetof(DisplayShadow, main_win0_top) == 0x1f, "DisplayShadow layout");
static_assert(offsetof(WindowBlendShadow, blend_ev) == 0x15, "WindowBlendShadow layout");
static_assert(offsetof(ScrollBlockShadow, main_bg2) == 0x08, "ScrollBlockShadow layout");
static_assert(offsetof(ScrollBlockShadow, sub_bg0) == 0x48, "ScrollBlockShadow layout");
static_assert(sizeof(ScrollBlockShadow) == 0x70, "ScrollBlockShadow layout");
static_assert(sizeof(BgAffineShadow) == 0x20, "BgAffineShadow layout");
static_assert(sizeof(WindowShadow) == 5, "WindowShadow layout");

#define REG_BLDCNT 0x04000050u
#define REG_DB_BLDCNT 0x04001050u
#define PLANES_ALL 0x1f /* backgrounds 0-3 and the OBJ */
#define PLANES_ALL_BACKDROP 0x3f
#define PLANE_OBJ 0x10
#define PLANE_BACKDROP 0x20

#define GX_DISPMODE_GRAPHICS 1
#define GX_BG0_AS_3D 1

extern DisplayShadow data_0213fe74;
extern WindowBlendShadow data_0213fe94;
extern ScrollBlockShadow data_0213fdf4;
extern BgAffineShadow data_0213fe64; /* the sub screen's background 3; its last 16 bytes are DisplayShadow's first */
extern u16 data_0213fdf0;            /* the backdrop colour of both screens */

extern void G2x_SetBGyAffine_(u32 reg, const BgAffineMtx *mtx, s32 center_x, s32 center_y, s32 x, s32 y);
extern void G2x_SetBlendAlpha_(u32 reg, int planes, int second_planes, int ev, int second_ev);
extern void G3X_SetHOffset(u32 offset);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GXS_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void G2x_SetBlendBrightness_(u32 reg, u32 planes, u32 brightness);
extern void G2x_SetBlendBrightnessExt_(u32 reg, u32 planes, u32 second_planes, u32 ev, u32 second_ev, u32 brightness);
extern void GX_SetGraphicsMode(int display_mode, int bg_mode, int bg0_2d3d);
extern void GXS_SetGraphicsMode(int bg_mode);

/* func_020019cc */
void DisplayShadow_MainBlendOff(void)
{
    data_0213fe94.blend_request |= BLEND_MAIN_OFF;
}
CLEAN_AS(func_020019cc, DisplayShadow_MainBlendOff)

/* func_020019dc: blend `planes` over `second_planes` on the main screen, `ev` of 16 for the
 * first. */
void DisplayShadow_SetMainAlpha(u8 planes, u8 second_planes, u8 ev)
{
    data_0213fe94.blend_planes = planes;
    data_0213fe94.blend_value = second_planes;
    data_0213fe94.blend_ev = ev;
    data_0213fe94.blend_request |= BLEND_MAIN_ALPHA;
}
CLEAN_AS(func_020019dc, DisplayShadow_SetMainAlpha)

/* func_020019f4 */
void DisplayShadow_SubBlendOff(void)
{
    data_0213fe94.blend_request |= BLEND_SUB_OFF;
}
CLEAN_AS(func_020019f4, DisplayShadow_SubBlendOff)

/* func_02001a04: as DisplayShadow_SetMainAlpha, on the sub screen. */
void DisplayShadow_SetSubAlpha(u8 planes, u8 second_planes, u8 ev)
{
    data_0213fe94.blend_planes = planes;
    data_0213fe94.blend_value = second_planes;
    data_0213fe94.blend_ev = ev;
    data_0213fe94.blend_request |= BLEND_SUB_ALPHA;
}
CLEAN_AS(func_02001a04, DisplayShadow_SetSubAlpha)

/* func_02001a1c: the sub screen's brightness (signed: negative darkens). */
void DisplayShadow_SetSubBrightness(u8 brightness)
{
    data_0213fe94.blend_value = brightness;
    data_0213fe94.blend_request |= BLEND_SUB_BRIGHTNESS;
}
CLEAN_AS(func_02001a1c, DisplayShadow_SetSubBrightness)

/* func_02001a30: take `planes` out of those the sub screen's brightness changes.
 * QUIRK: returns 4, the request bit it set. */
u8 DisplayShadow_ExcludeSubBrightnessPlanes(u8 planes)
{
    data_0213fe94.blend_planes &= (u8) ~planes;
    data_0213fe94.blend_request |= BLEND_SUB_BRIGHTNESS;
    return BLEND_SUB_BRIGHTNESS;
}
CLEAN_AS(func_02001a30, DisplayShadow_ExcludeSubBrightnessPlanes)

/* func_02001a48: the sub screen's brightness changes every background and the OBJ. */
void DisplayShadow_SubBrightnessAllPlanes(void)
{
    data_0213fe94.blend_planes = PLANES_ALL;
    data_0213fe94.blend_request |= BLEND_SUB_BRIGHTNESS;
}
CLEAN_AS(func_02001a48, DisplayShadow_SubBrightnessAllPlanes)

/* func_02001a5c: undo DisplayShadow_BeginSubObjWindowBrightness: the sub screen's OBJ
 * window off and no effect. */
void DisplayShadow_EndSubObjWindowBrightness(void)
{
    DisplayShadow_DisableSubWindows(WINDOW_OBJ);
    data_0213fe94.blend_request |= BLEND_SUB_OFF;
}
CLEAN_AS(func_02001a5c, DisplayShadow_EndSubObjWindowBrightness)

/* func_02001a7c: change the brightness of the whole sub screen except inside its OBJ window,
 * where only the OBJ show, without effects. */
void DisplayShadow_BeginSubObjWindowBrightness(void)
{
    DisplayShadow_SubBrightnessAllPlanes();
    DisplayShadow_SetSubOutsidePlanes(PLANES_ALL);
    DisplayShadow_SetSubObjWindowPlanes(PLANE_OBJ);
    DisplayShadow_EnableSubWindows(WINDOW_OBJ);
    data_0213fe94.blend_request |= BLEND_SUB_BRIGHTNESS_OBJ;
}
CLEAN_AS(func_02001a7c, DisplayShadow_BeginSubObjWindowBrightness)

/* func_02001aac: set the brightness of both screens at once, on every plane and the
 * backdrop; 0 turns the effect off (brightness 0, weights 16/16, the backdrop second). */
void Display_SetBrightnessNow(unsigned int brightness)
{
    if (brightness != 0) {
        G2x_SetBlendBrightness_(REG_BLDCNT, PLANES_ALL_BACKDROP, brightness);
        G2x_SetBlendBrightness_(REG_DB_BLDCNT, PLANES_ALL_BACKDROP, brightness);
    } else {
        G2x_SetBlendBrightnessExt_(REG_BLDCNT, PLANES_ALL, PLANE_BACKDROP, 16, 16, brightness);
        G2x_SetBlendBrightnessExt_(REG_DB_BLDCNT, PLANES_ALL, PLANE_BACKDROP, 16, 16, brightness);
    }
}
CLEAN_AS(func_02001aac, Display_SetBrightnessNow)

/* func_02001afc */
void DisplayShadow_HideSubPlanes(u8 planes)
{
    data_0213fe74.sub_planes &= (u8) ~planes;
}
CLEAN_AS(func_02001afc, DisplayShadow_HideSubPlanes)

/* func_02001b0c */
void DisplayShadow_ShowSubPlanes(int planes)
{
    data_0213fe74.sub_planes |= (u8) planes;
}
CLEAN_AS(func_02001b0c, DisplayShadow_ShowSubPlanes)

/* func_02001b1c */
void DisplayShadow_SetSubPlanes(u8 planes)
{
    data_0213fe74.sub_planes = planes;
}
CLEAN_AS(func_02001b1c, DisplayShadow_SetSubPlanes)

/* func_02001b28 */
u8 DisplayShadow_GetSubPlanes(void)
{
    return data_0213fe74.sub_planes;
}
CLEAN_AS(func_02001b28, DisplayShadow_GetSubPlanes)

/* func_02001b34 */
void DisplayShadow_HideMainPlanes(u8 planes)
{
    data_0213fe74.main_planes &= (u8) ~planes;
}
CLEAN_AS(func_02001b34, DisplayShadow_HideMainPlanes)

/* func_02001b44 */
void DisplayShadow_ShowMainPlanes(u8 planes)
{
    data_0213fe74.main_planes |= planes;
}
CLEAN_AS(func_02001b44, DisplayShadow_ShowMainPlanes)

/* func_02001b54 */
void DisplayShadow_SetMainPlanes(u8 planes)
{
    data_0213fe74.main_planes = planes;
}
CLEAN_AS(func_02001b54, DisplayShadow_SetMainPlanes)

/* func_02001b60 */
u8 DisplayShadow_GetMainPlanes(void)
{
    return data_0213fe74.main_planes;
}
CLEAN_AS(func_02001b60, DisplayShadow_GetMainPlanes)

/* func_02001b6c */
void DisplayShadow_DisableSubWindows(u8 windows)
{
    data_0213fe74.sub_windows &= (u8) ~windows;
}
CLEAN_AS(func_02001b6c, DisplayShadow_DisableSubWindows)

/* func_02001b7c */
void DisplayShadow_EnableSubWindows(u8 windows)
{
    data_0213fe74.sub_windows |= windows;
}
CLEAN_AS(func_02001b7c, DisplayShadow_EnableSubWindows)

/* func_02001b8c */
void DisplayShadow_SetSubWindows(u8 windows)
{
    data_0213fe74.sub_windows = windows;
}
CLEAN_AS(func_02001b8c, DisplayShadow_SetSubWindows)

/* func_02001b98 */
u8 DisplayShadow_GetSubWindows(void)
{
    return data_0213fe74.sub_windows;
}
CLEAN_AS(func_02001b98, DisplayShadow_GetSubWindows)

/* func_02001ba4 */
void DisplayShadow_DisableMainWindows(u8 windows)
{
    data_0213fe74.main_windows &= (u8) ~windows;
}
CLEAN_AS(func_02001ba4, DisplayShadow_DisableMainWindows)

/* func_02001bb4 */
void DisplayShadow_EnableMainWindows(u8 windows)
{
    data_0213fe74.main_windows |= windows;
}
CLEAN_AS(func_02001bb4, DisplayShadow_EnableMainWindows)

/* func_02001bc4 */
void DisplayShadow_SetMainWindows(u8 windows)
{
    data_0213fe74.main_windows = windows;
}
CLEAN_AS(func_02001bc4, DisplayShadow_SetMainWindows)

/* func_02001bd0 */
u8 DisplayShadow_GetMainWindows(void)
{
    return data_0213fe74.main_windows;
}
CLEAN_AS(func_02001bd0, DisplayShadow_GetMainWindows)

/* func_02001bdc: the sub screen's background mode, in the copy and in the hardware. */
void Display_SetSubBgModeNow(int mode)
{
    DisplayShadow_SetSubBgMode((u8) mode);
    GXS_SetGraphicsMode(mode);
}
CLEAN_AS(func_02001bdc, Display_SetSubBgModeNow)

/* func_02001bf0: the main screen's background mode, in the copy and in the hardware, with
 * background 0 showing the 3D. */
void Display_SetMainBgModeNow(int mode)
{
    DisplayShadow_SetMainBgMode((u8) mode);
    GX_SetGraphicsMode(GX_DISPMODE_GRAPHICS, mode, GX_BG0_AS_3D);
}
CLEAN_AS(func_02001bf0, Display_SetMainBgModeNow)

/* Which of backgrounds 2 and 3 the copy treats as affine in each background mode, two bits
 * per mode from the low bits up (bit 0 background 2, bit 1 background 3): mode 0 neither,
 * 1 background 3, 2 both, 3 background 2, 4 both, 5 both, 6 and 7 neither.
 * QUIRK: mode 3 marks background 2, a text background in that mode, rather than background 3,
 * and mode 6 marks neither. */
#define AFFINE_BY_MODE 0xf78u

/* The table's entry as the ARM reads it: the shift amount is the low byte of mode * 2, and
 * amounts of 32 and more give 0 (so modes 128 and up read as mode - 128). */
static u32 affine_for_mode(u8 mode)
{
    u32 amount = ((u32) mode << 1) & 0xff;
    return amount < 32 ? (AFFINE_BY_MODE >> amount) & 3 : 0;
}

/* func_02001c08 */
void DisplayShadow_SetSubBgMode(u8 mode)
{
    data_0213fe74.sub_bg_mode = mode;
    data_0213fe74.affine_bgs =
        (u8) ((data_0213fe74.affine_bgs & ~(AFFINE_SUB_BG2 | AFFINE_SUB_BG3)) | affine_for_mode(mode) << 2);
}
CLEAN_AS(func_02001c08, DisplayShadow_SetSubBgMode)

/* func_02001c30 */
void DisplayShadow_SetMainBgMode(u8 mode)
{
    data_0213fe74.main_bg_mode = mode;
    data_0213fe74.affine_bgs =
        (u8) ((data_0213fe74.affine_bgs & ~(AFFINE_MAIN_BG2 | AFFINE_MAIN_BG3)) | affine_for_mode(mode));
}
CLEAN_AS(func_02001c30, DisplayShadow_SetMainBgMode)

/* func_02001c58 */
void DisplayShadow_SetSubWindow1(u8 left, u8 top, u8 right, u8 bottom)
{
    data_0213fe94.sub_win1_left = left;
    data_0213fe94.sub_win1_top = top;
    data_0213fe94.sub_win1_right = right;
    data_0213fe94.sub_win1_bottom = bottom;
    data_0213fe74.window_dirty |= DIRTY_SUB_WIN1_RECT;
}
CLEAN_AS(func_02001c58, DisplayShadow_SetSubWindow1)

/* func_02001c7c */
void DisplayShadow_SetSubWindow0(u8 left, u8 top, u8 right, u8 bottom)
{
    data_0213fe94.sub_win0_left = left;
    data_0213fe94.sub_win0_top = top;
    data_0213fe94.sub_win0_right = right;
    data_0213fe94.sub_win0_bottom = bottom;
    data_0213fe74.window_dirty |= DIRTY_SUB_WIN0_RECT;
}
CLEAN_AS(func_02001c7c, DisplayShadow_SetSubWindow0)

/* func_02001ca0 */
void DisplayShadow_SetMainWindow1(u8 left, u8 top, u8 right, u8 bottom)
{
    data_0213fe94.main_win1_left = left;
    data_0213fe94.main_win1_top = top;
    data_0213fe94.main_win1_right = right;
    data_0213fe94.main_win1_bottom = bottom;
    data_0213fe74.window_dirty |= DIRTY_MAIN_WIN1_RECT;
}
CLEAN_AS(func_02001ca0, DisplayShadow_SetMainWindow1)

/* func_02001cc4 */
void DisplayShadow_SetMainWindow0(u8 left, u8 top, u8 right, u8 bottom)
{
    data_0213fe74.main_win0_left = left;
    data_0213fe74.main_win0_top = top;
    data_0213fe94.main_win0_right = right;
    data_0213fe94.main_win0_bottom = bottom;
    data_0213fe74.window_dirty |= DIRTY_MAIN_WIN0_RECT;
}
CLEAN_AS(func_02001cc4, DisplayShadow_SetMainWindow0)

/* func_02001ce8 */
void DisplayShadow_SetSubObjWindowPlanes(u8 planes)
{
    data_0213fe74.sub_objwin_planes = planes;
}
CLEAN_AS(func_02001ce8, DisplayShadow_SetSubObjWindowPlanes)

/* func_02001cf4 */
void DisplayShadow_SetMainObjWindowPlanes(u8 planes)
{
    data_0213fe74.main_objwin_planes = planes;
}
CLEAN_AS(func_02001cf4, DisplayShadow_SetMainObjWindowPlanes)

/* func_02001d00 */
void DisplayShadow_SetSubOutsidePlanes(u8 planes)
{
    data_0213fe74.sub_outside_planes = planes;
}
CLEAN_AS(func_02001d00, DisplayShadow_SetSubOutsidePlanes)

/* func_02001d0c */
void DisplayShadow_HideMainOutsidePlanes(u8 planes)
{
    data_0213fe74.main_outside_planes &= (u8) ~planes;
}
CLEAN_AS(func_02001d0c, DisplayShadow_HideMainOutsidePlanes)

/* func_02001d1c */
void DisplayShadow_SetMainOutsidePlanes(u8 planes)
{
    data_0213fe74.main_outside_planes = planes;
}
CLEAN_AS(func_02001d1c, DisplayShadow_SetMainOutsidePlanes)

/* func_02001d28: write the sub screen's window 1 planes on the next flush, with the colour
 * effects enabled inside the window when `effects` is nonzero. */
void DisplayShadow_MarkSubWindow1Planes(unsigned int effects)
{
    data_0213fe74.window_dirty |= effects != 0 ? DIRTY_SUB_WIN1_PLANES : DIRTY_SUB_WIN1_PLANES_PLAIN;
}
CLEAN_AS(func_02001d28, DisplayShadow_MarkSubWindow1Planes)

/* func_02001d44: as DisplayShadow_MarkSubWindow1Planes, for window 0. */
void DisplayShadow_MarkSubWindow0Planes(int effects)
{
    data_0213fe74.window_dirty |= effects != 0 ? DIRTY_SUB_WIN0_PLANES : DIRTY_SUB_WIN0_PLANES_PLAIN;
}
CLEAN_AS(func_02001d44, DisplayShadow_MarkSubWindow0Planes)

/* func_02001d60 */
void DisplayShadow_SetSubWindow1Planes(u8 planes, int effects)
{
    data_0213fe94.sub_win1_planes = planes;
    DisplayShadow_MarkSubWindow1Planes((unsigned int) effects);
}
CLEAN_AS(func_02001d60, DisplayShadow_SetSubWindow1Planes)

/* func_02001d74 */
void DisplayShadow_SetSubWindow0Planes(s8 planes, int effects)
{
    data_0213fe94.sub_win0_planes = (u8) planes;
    DisplayShadow_MarkSubWindow0Planes(effects);
}
CLEAN_AS(func_02001d74, DisplayShadow_SetSubWindow0Planes)

/* func_02001d88: the main screen's window 1 planes, always with the colour effects. */
void DisplayShadow_SetMainWindow1Planes(u8 planes)
{
    data_0213fe94.main_win1_planes = planes;
    data_0213fe74.window_dirty |= DIRTY_MAIN_WIN1_PLANES;
}
CLEAN_AS(func_02001d88, DisplayShadow_SetMainWindow1Planes)

/* func_02001da0 */
void DisplayShadow_SetMainWindow0Planes(u8 planes)
{
    data_0213fe94.main_win0_planes = planes;
    data_0213fe74.window_dirty |= DIRTY_MAIN_WIN0_PLANES;
}
CLEAN_AS(func_02001da0, DisplayShadow_SetMainWindow0Planes)

/* func_02001db8 */
void DisplayShadow_SetSubBg3Scroll(int x, int y)
{
    data_0213fe74.scroll_dirty |= DIRTY_SUB_BG3;
    data_0213fe64.x = x;
    data_0213fe64.y = y;
}
CLEAN_AS(func_02001db8, DisplayShadow_SetSubBg3Scroll)

/* func_02001dd4 */
void DisplayShadow_SetSubBg2Scroll(int x, int y)
{
    data_0213fe74.scroll_dirty |= DIRTY_SUB_BG2;
    data_0213fdf4.sub_bg2.x = x;
    data_0213fdf4.sub_bg2.y = y;
}
CLEAN_AS(func_02001dd4, DisplayShadow_SetSubBg2Scroll)

/* func_02001df4 */
void DisplayShadow_SetSubBg1Scroll(u16 x, u16 y)
{
    data_0213fe74.scroll_dirty |= DIRTY_SUB_BG1;
    data_0213fdf4.sub_bg1.x = x;
    data_0213fdf4.sub_bg1.y = y;
}
CLEAN_AS(func_02001df4, DisplayShadow_SetSubBg1Scroll)

/* func_02001e14 */
void DisplayShadow_SetSubBg0Scroll(u16 x, u16 y)
{
    data_0213fe74.scroll_dirty |= DIRTY_SUB_BG0;
    data_0213fdf4.sub_bg0.x = x;
    data_0213fdf4.sub_bg0.y = y;
}
CLEAN_AS(func_02001e14, DisplayShadow_SetSubBg0Scroll)

/* func_02001e34 */
void DisplayShadow_SetMainBg3Scroll(unsigned int x, unsigned int y)
{
    data_0213fe74.scroll_dirty |= DIRTY_MAIN_BG3;
    data_0213fdf4.main_bg3.x = (s32) x;
    data_0213fdf4.main_bg3.y = (s32) y;
}
CLEAN_AS(func_02001e34, DisplayShadow_SetMainBg3Scroll)

/* func_02001e54 */
void DisplayShadow_SetMainBg2Scroll(unsigned int x, unsigned int y)
{
    data_0213fe74.scroll_dirty |= DIRTY_MAIN_BG2;
    data_0213fdf4.main_bg2.x = (s32) x;
    data_0213fdf4.main_bg2.y = (s32) y;
}
CLEAN_AS(func_02001e54, DisplayShadow_SetMainBg2Scroll)

/* func_02001e74 */
void DisplayShadow_SetMainBg1Scroll(u16 x, u16 y)
{
    data_0213fe74.scroll_dirty |= DIRTY_MAIN_BG1;
    data_0213fdf4.main_bg1.x = x;
    data_0213fdf4.main_bg1.y = y;
}
CLEAN_AS(func_02001e74, DisplayShadow_SetMainBg1Scroll)

/* func_02001e94: the whole screen (0-255 by 0-192), showing nothing. */
void DisplayShadow_ResetWindow(WindowShadow *window)
{
    window->left = 0;
    window->top = 0;
    window->right = 255;
    window->bottom = 192;
    window->planes = 0;
}
CLEAN_AS(func_02001e94, DisplayShadow_ResetWindow)

#define FX32_ONE 0x1000

/* func_02001ea8: the identity matrix, centre and position 0. */
void DisplayShadow_ResetAffine(BgAffineShadow *affine)
{
    affine->mtx.m00 = FX32_ONE;
    affine->mtx.m01 = 0;
    affine->mtx.m10 = 0;
    affine->mtx.m11 = FX32_ONE;
    affine->center_x = 0;
    affine->center_y = 0;
    affine->x = 0;
    affine->y = 0;
}
CLEAN_AS(func_02001ea8, DisplayShadow_ResetAffine)

/* func_02001ec4 */
void DisplayShadow_ResetScroll(ScrollShadow *scroll)
{
    scroll->x = 0;
    scroll->y = 0;
}
CLEAN_AS(func_02001ec4, DisplayShadow_ResetScroll)

#define REG16(addr) (*(volatile u16 *) (addr))
#define REG32(addr) (*(volatile u32 *) (addr))

#define REG_DISPCNT 0x04000000u
#define REG_DB_DISPCNT 0x04001000u
#define DISPCNT_BG0_3D 0x8u
#define DISPCNT_PLANES_SHIFT 8
#define DISPCNT_PLANES_MASK 0x1f00u
#define DISPCNT_WINDOWS_SHIFT 13
#define DISPCNT_WINDOWS_MASK 0xe000u

#define SUB_SCREEN 0x1000u /* the sub screen's registers follow the main screen's at this distance */
#define REG_BG0OFS 0x04000010u
#define REG_BG1OFS 0x04000014u
#define REG_BG2OFS 0x04000018u
#define REG_BG3OFS 0x0400001cu
#define REG_BG2PA 0x04000020u
#define REG_BG3PA 0x04000030u
#define REG_WIN0H 0x04000040u
#define REG_WIN1H 0x04000042u
#define REG_WIN0V 0x04000044u
#define REG_WIN1V 0x04000046u
#define REG_WININ 0x04000048u
#define REG_WINOUT 0x0400004au
#define WIN_LOW 0  /* WININ: window 0; WINOUT: outside the windows */
#define WIN_HIGH 8 /* WININ: window 1; WINOUT: inside the OBJ window */

/* A text background's BGxHOFS and BGxVOFS in one write, 9 bits each. */
static void write_bg_offset(u32 reg, u32 x, u32 y)
{
    REG32(reg) = (x & 0x1ff) | ((y << 16) & 0x01ff0000);
}

/* A background that may be affine: its parameters when it is, else x and y as its scrolling. */
static void write_bg_affine(int affine, u32 affine_reg, u32 offset_reg, const BgAffineShadow *bg)
{
    if (affine) {
        G2x_SetBGyAffine_(affine_reg, &bg->mtx, bg->center_x, bg->center_y, bg->x, bg->y);
    } else {
        write_bg_offset(offset_reg, (u32) bg->x, (u32) bg->y);
    }
}

/* One half of WININ or WINOUT: the planes, and the colour effects bit when `effects`.
 * QUIRK: the planes are not masked to their 6 bits. */
static void write_window_planes(u32 reg, int shift, u8 planes, int effects)
{
    u16 value = REG16(reg) & (u16) ~(0x3f << shift);
    REG16(reg) = (u16) (value | planes << shift | (effects ? 0x20 << shift : 0));
}

/* HW: the horizontal extent is written before the vertical one, as the ROM does. */
static void write_window_rect(u32 h_reg, u32 v_reg, u8 left, u8 top, u8 right, u8 bottom)
{
    REG16(h_reg) = (u16) (left << 8 | right);
    REG16(v_reg) = (u16) (top << 8 | bottom);
}

/* func_02001ecc: write what the setters marked to the hardware, then forget the marks, and
 * apply the first blend request (BlendRequest) and drop the others.
 * HW: the registers are written in this order: scrolling, the windows' planes, their
 * rectangles, the blending. */
void DisplayShadow_Flush(void)
{
    DisplayShadow *shadow = &data_0213fe74;
    WindowBlendShadow *win = &data_0213fe94;
    ScrollBlockShadow *scroll = &data_0213fdf4;
    u8 affine = shadow->affine_bgs;
    u8 request;

    if (shadow->scroll_dirty != 0) {
        u8 dirty = shadow->scroll_dirty;
        if (dirty & DIRTY_MAIN_BG0) {
            /* background 0 showing the 3D scrolls the 3D instead */
            if ((REG32(REG_DISPCNT) & DISPCNT_BG0_3D) == 0) {
                write_bg_offset(REG_BG0OFS, scroll->main_bg0.x, scroll->main_bg0.y);
            } else {
                G3X_SetHOffset(scroll->main_bg0.x);
            }
        }
        if (dirty & DIRTY_MAIN_BG1) {
            write_bg_offset(REG_BG1OFS, scroll->main_bg1.x, scroll->main_bg1.y);
        }
        if (dirty & DIRTY_MAIN_BG2) {
            write_bg_affine(affine & AFFINE_MAIN_BG2, REG_BG2PA, REG_BG2OFS, &scroll->main_bg2);
        }
        if (dirty & DIRTY_MAIN_BG3) {
            write_bg_affine(affine & AFFINE_MAIN_BG3, REG_BG3PA, REG_BG3OFS, &scroll->main_bg3);
        }
        if (dirty & DIRTY_SUB_BG0) {
            write_bg_offset(SUB_SCREEN + REG_BG0OFS, scroll->sub_bg0.x, scroll->sub_bg0.y);
        }
        if (dirty & DIRTY_SUB_BG1) {
            write_bg_offset(SUB_SCREEN + REG_BG1OFS, scroll->sub_bg1.x, scroll->sub_bg1.y);
        }
        if (dirty & DIRTY_SUB_BG2) {
            write_bg_affine(affine & AFFINE_SUB_BG2, SUB_SCREEN + REG_BG2PA, SUB_SCREEN + REG_BG2OFS, &scroll->sub_bg2);
        }
        if (dirty & DIRTY_SUB_BG3) {
            write_bg_affine(affine & AFFINE_SUB_BG3, SUB_SCREEN + REG_BG3PA, SUB_SCREEN + REG_BG3OFS, &data_0213fe64);
        }
        shadow->scroll_dirty = 0;
    }

    if (shadow->window_dirty != 0) {
        u16 dirty = shadow->window_dirty;
        if (dirty & DIRTY_MAIN_WIN0_PLANES) {
            write_window_planes(REG_WININ, WIN_LOW, win->main_win0_planes, 1);
        }
        if (dirty & DIRTY_MAIN_WIN1_PLANES) {
            write_window_planes(REG_WININ, WIN_HIGH, win->main_win1_planes, 1);
        }
        if (dirty & DIRTY_SUB_WIN0_PLANES) {
            write_window_planes(SUB_SCREEN + REG_WININ, WIN_LOW, win->sub_win0_planes, 1);
        }
        if (dirty & DIRTY_SUB_WIN0_PLANES_PLAIN) {
            write_window_planes(SUB_SCREEN + REG_WININ, WIN_LOW, win->sub_win0_planes, 0);
        }
        if (dirty & DIRTY_SUB_WIN1_PLANES) {
            write_window_planes(SUB_SCREEN + REG_WININ, WIN_HIGH, win->sub_win1_planes, 1);
        }
        if (dirty & DIRTY_SUB_WIN1_PLANES_PLAIN) {
            write_window_planes(SUB_SCREEN + REG_WININ, WIN_HIGH, win->sub_win1_planes, 0);
        }
        if (dirty & DIRTY_MAIN_WIN0_RECT) {
            write_window_rect(REG_WIN0H, REG_WIN0V, shadow->main_win0_left, shadow->main_win0_top, win->main_win0_right,
                              win->main_win0_bottom);
        }
        if (dirty & DIRTY_MAIN_WIN1_RECT) {
            write_window_rect(REG_WIN1H, REG_WIN1V, win->main_win1_left, win->main_win1_top, win->main_win1_right,
                              win->main_win1_bottom);
        }
        if (dirty & DIRTY_SUB_WIN0_RECT) {
            write_window_rect(SUB_SCREEN + REG_WIN0H, SUB_SCREEN + REG_WIN0V, win->sub_win0_left, win->sub_win0_top,
                              win->sub_win0_right, win->sub_win0_bottom);
        }
        if (dirty & DIRTY_SUB_WIN1_RECT) {
            write_window_rect(SUB_SCREEN + REG_WIN1H, SUB_SCREEN + REG_WIN1V, win->sub_win1_left, win->sub_win1_top,
                              win->sub_win1_right, win->sub_win1_bottom);
        }
        shadow->window_dirty = 0;
    }

    /* QUIRK: blend_value is read as signed, which suits the brightness (negative darkens) but
     * also sign-extends the alpha's second planes; they never reach 0x80. */
    request = win->blend_request;
    if (request & BLEND_MAIN_OFF) {
        G2x_SetBlendBrightnessExt_(REG_BLDCNT, PLANES_ALL, PLANE_BACKDROP, 16, 16, 0);
    } else if (request & BLEND_MAIN_ALPHA) {
        G2x_SetBlendAlpha_(REG_BLDCNT, win->blend_planes, (s8) win->blend_value, win->blend_ev, 16 - win->blend_ev);
    } else if (request & BLEND_SUB_OFF) {
        G2x_SetBlendBrightnessExt_(REG_DB_BLDCNT, PLANES_ALL, PLANE_BACKDROP, 16, 16, 0);
    } else if (request & BLEND_SUB_ALPHA) {
        G2x_SetBlendAlpha_(REG_DB_BLDCNT, win->blend_planes, (s8) win->blend_value, win->blend_ev, 16 - win->blend_ev);
    } else if (request != 0) {
        /* BLEND_SUB_BRIGHTNESS, BLEND_SUB_BRIGHTNESS_OBJ, or any other bit */
        G2x_SetBlendBrightness_(REG_DB_BLDCNT, win->blend_planes, (u32) (s8) win->blend_value);
    }
    win->blend_request = 0;
}
CLEAN_AS(func_02001ecc, DisplayShadow_Flush)

/* func_02002354: write the parts of the copy that have no marks, every frame: both screens'
 * background modes (the main screen's background 0 showing the 3D), visible planes, enabled
 * windows, the planes outside the windows (with the colour effects) and inside the OBJ window
 * (without).
 * QUIRK: no value is masked to its field: planes above 0x1f reach the windows' bits until
 * those are written, and windows above 7 reach DISPCNT's bits 16 and up.
 * HW: in this order. */
void DisplayShadow_WriteModes(void)
{
    DisplayShadow *shadow = &data_0213fe74;

    GX_SetGraphicsMode(GX_DISPMODE_GRAPHICS, shadow->main_bg_mode, GX_BG0_AS_3D);
    GXS_SetGraphicsMode(shadow->sub_bg_mode);
    REG32(REG_DISPCNT) = (REG32(REG_DISPCNT) & ~DISPCNT_PLANES_MASK) | (u32) shadow->main_planes << DISPCNT_PLANES_SHIFT;
    REG32(REG_DB_DISPCNT) = (REG32(REG_DB_DISPCNT) & ~DISPCNT_PLANES_MASK) | (u32) shadow->sub_planes << DISPCNT_PLANES_SHIFT;
    REG32(REG_DISPCNT) = (REG32(REG_DISPCNT) & ~DISPCNT_WINDOWS_MASK) | (u32) shadow->main_windows << DISPCNT_WINDOWS_SHIFT;
    REG32(REG_DB_DISPCNT) = (REG32(REG_DB_DISPCNT) & ~DISPCNT_WINDOWS_MASK) | (u32) shadow->sub_windows
                                                                                  << DISPCNT_WINDOWS_SHIFT;
    write_window_planes(REG_WINOUT, WIN_LOW, shadow->main_outside_planes, 1);
    write_window_planes(SUB_SCREEN + REG_WINOUT, WIN_LOW, shadow->sub_outside_planes, 1);
    write_window_planes(REG_WINOUT, WIN_HIGH, shadow->main_objwin_planes, 0);
    write_window_planes(SUB_SCREEN + REG_WINOUT, WIN_HIGH, shadow->sub_objwin_planes, 0);
}
CLEAN_AS(func_02002354, DisplayShadow_WriteModes)

/* func_02002408: does nothing; func_02054094 calls it after resetting the 3D. */
void Display_EmptyHook(void) {}
CLEAN_AS(func_02002408, Display_EmptyHook)

/* The windows seen as WindowShadow (see there). */
extern WindowShadow data_0213fe92; /* the main screen's window 0 */
extern WindowShadow data_0213fe97; /* the main screen's window 1 */
extern WindowShadow data_0213fe9c; /* the sub screen's window 0 */
extern WindowShadow data_0213fea1; /* the sub screen's window 1 */

/* func_0200240c: nothing visible and no windows, no scrolling, identity affine parameters,
 * windows covering the screen and showing nothing; every scrolling and window marked to be
 * written, no blend request; the main screen in background mode 1, the sub screen in mode 0.
 * QUIRK: the modes are first stored the other way round (main 0, sub 1), then set right by
 * DisplayShadow_SetSubBgMode and DisplayShadow_SetMainBgMode, which also set affine_bgs. */
void DisplayShadow_Reset(void)
{
    DisplayShadow *shadow = &data_0213fe74;

    shadow->main_planes = 0;
    shadow->sub_planes = 0;
    shadow->main_windows = 0;
    shadow->sub_windows = 0;
    shadow->main_outside_planes = 0;
    shadow->sub_outside_planes = 0;
    shadow->main_objwin_planes = 0;
    shadow->sub_objwin_planes = 0;
    shadow->main_bg_mode = 0;
    shadow->sub_bg_mode = 1;

    DisplayShadow_ResetScroll(&data_0213fdf4.main_bg0);
    DisplayShadow_ResetScroll(&data_0213fdf4.main_bg1);
    DisplayShadow_ResetAffine(&data_0213fdf4.main_bg2);
    DisplayShadow_ResetAffine(&data_0213fdf4.main_bg3);
    DisplayShadow_ResetScroll(&data_0213fdf4.sub_bg0);
    DisplayShadow_ResetScroll(&data_0213fdf4.sub_bg1);
    DisplayShadow_ResetAffine(&data_0213fdf4.sub_bg2);
    DisplayShadow_ResetAffine(&data_0213fe64);
    DisplayShadow_ResetWindow(&data_0213fe92);
    DisplayShadow_ResetWindow(&data_0213fe97);
    DisplayShadow_ResetWindow(&data_0213fe9c);
    DisplayShadow_ResetWindow(&data_0213fea1);

    shadow->affine_bgs = 0;
    shadow->scroll_dirty = 0xff;
    shadow->window_dirty = 0xff; /* every bit but the PLANES_PLAIN ones */
    data_0213fe94.blend_request = 0;
    data_0213fe94.blend_value = 0;

    DisplayShadow_SetSubBgMode(0);
    DisplayShadow_SetMainBgMode(1);
}
CLEAN_AS(func_0200240c, DisplayShadow_Reset)

/* func_020024cc: colour 0 of both screens' background palettes, the backdrop. */
void Display_LoadBackdropColor(void)
{
    GX_LoadBGPltt(&data_0213fdf0, 0, sizeof(u16));
    GXS_LoadBGPltt(&data_0213fdf0, 0, sizeof(u16));
}
CLEAN_AS(func_020024cc, Display_LoadBackdropColor)

/* func_02002808: set window `window` (0 and 1 the main screen's, 2 and 3 the sub screen's)
 * to a rectangle; other numbers do nothing. */
void DisplayShadow_SetWindow(unsigned int window, int left, int top, int right, int bottom)
{
    switch (window) {
        case 0:
            DisplayShadow_SetMainWindow0((u8) left, (u8) top, (u8) right, (u8) bottom);
            break;
        case 1:
            DisplayShadow_SetMainWindow1((u8) left, (u8) top, (u8) right, (u8) bottom);
            break;
        case 2:
            DisplayShadow_SetSubWindow0((u8) left, (u8) top, (u8) right, (u8) bottom);
            break;
        case 3:
            DisplayShadow_SetSubWindow1((u8) left, (u8) top, (u8) right, (u8) bottom);
            break;
    }
}
CLEAN_AS(func_02002808, DisplayShadow_SetWindow)
