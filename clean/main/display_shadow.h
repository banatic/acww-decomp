/* The game's copy of the 2D display registers of both screens: the visible backgrounds, the
 * windows, the blending, the background modes and scrolling. The setters change the copy and
 * mark what changed; func_02001ecc writes the marked parts to the hardware (on VBlank) and
 * func_02002354 writes the rest.
 *
 * Plane masks are DISPCNT's and the windows' bits: 0x01-0x08 backgrounds 0-3, 0x10 the OBJ.
 * Window rectangles are given as left, top, right, bottom. */
#ifndef CLEAN_MAIN_DISPLAY_SHADOW_H
#define CLEAN_MAIN_DISPLAY_SHADOW_H

#include "types.h"

/* A text background's scrolling, in pixels (BGxHOFS, BGxVOFS). */
typedef struct ScrollShadow {
    u16 x;
    u16 y;
} ScrollShadow;

/* An affine background's matrix (NitroSDK's MtxFx22, 20.12 fixed point). */
typedef struct BgAffineMtx {
    fx32 m00, m01, m10, m11;
} BgAffineMtx;

/* An affine background's parameters, as G2x_SetBGyAffine_ takes them. A background the mode
 * makes a text one uses only x and y, as its scrolling. */
typedef struct BgAffineShadow {
    BgAffineMtx mtx;
    s32 center_x; /* 0x10 */
    s32 center_y; /* 0x14 */
    s32 x;        /* 0x18 */
    s32 y;        /* 0x1c */
} BgAffineShadow;

/* data_0213fdf4: the scrolling of every background but the sub screen's background 3, whose
 * BgAffineShadow (data_0213fe64) follows and runs on into DisplayShadow. */
typedef struct ScrollBlockShadow {
    ScrollShadow main_bg0;   /* 0x00: written to BG0HOFS, or to the 3D's offset */
    ScrollShadow main_bg1;   /* 0x04 */
    BgAffineShadow main_bg2; /* 0x08 */
    BgAffineShadow main_bg3; /* 0x28 */
    ScrollShadow sub_bg0;    /* 0x48 */
    ScrollShadow sub_bg1;    /* 0x4c */
    BgAffineShadow sub_bg2;  /* 0x50 */
} ScrollBlockShadow;

/* A window's rectangle and the planes shown inside it. Only the reset (func_02001e94) sees one
 * this way: the main screen's window 0 straddles DisplayShadow and WindowBlendShadow. */
typedef struct WindowShadow {
    u8 left;
    u8 top;
    u8 right;
    u8 bottom;
    u8 planes;
} WindowShadow;

/* data_0213fe74 */
typedef struct DisplayShadow {
    u32 sub_bg3_affine[4];  /* the end of data_0213fe64, the sub screen's background 3's
                               BgAffineShadow: its centre x, y and its x, y */
    u8 affine_bgs;          /* 0x10: AffineBgs: which backgrounds the modes make affine */
    u8 scroll_dirty;        /* 0x11: scrolling and affine parameters to write */
    u16 window_dirty;       /* 0x12: WindowDirty */
    u8 main_planes;         /* 0x14: the main screen's visible planes */
    u8 sub_planes;          /* 0x15 */
    u8 main_bg_mode;        /* 0x16 */
    u8 sub_bg_mode;         /* 0x17 */
    u8 main_windows;        /* 0x18: Windows enabled on the main screen */
    u8 sub_windows;         /* 0x19 */
    u8 main_outside_planes; /* 0x1a: the planes shown outside the windows (with effects) */
    u8 sub_outside_planes;  /* 0x1b */
    u8 main_objwin_planes;  /* 0x1c: the planes shown in the OBJ window */
    u8 sub_objwin_planes;   /* 0x1d */
    u8 main_win0_left;      /* 0x1e */
    u8 main_win0_top;       /* 0x1f */
} DisplayShadow;

/* data_0213fe94, which follows it */
typedef struct WindowBlendShadow {
    u8 main_win0_right;  /* 0x00 */
    u8 main_win0_bottom; /* 0x01 */
    u8 main_win0_planes; /* 0x02 */
    u8 main_win1_left;   /* 0x03 */
    u8 main_win1_top;    /* 0x04 */
    u8 main_win1_right;  /* 0x05 */
    u8 main_win1_bottom; /* 0x06 */
    u8 main_win1_planes; /* 0x07 */
    u8 sub_win0_left;    /* 0x08 */
    u8 sub_win0_top;     /* 0x09 */
    u8 sub_win0_right;   /* 0x0a */
    u8 sub_win0_bottom;  /* 0x0b */
    u8 sub_win0_planes;  /* 0x0c */
    u8 sub_win1_left;    /* 0x0d */
    u8 sub_win1_top;     /* 0x0e */
    u8 sub_win1_right;   /* 0x0f */
    u8 sub_win1_bottom;  /* 0x10 */
    u8 sub_win1_planes;  /* 0x11 */
    u8 blend_request;    /* 0x12: BlendRequest; one is applied, then all are dropped */
    u8 blend_planes;     /* 0x13: the first target planes */
    u8 blend_value;      /* 0x14: the second target planes (alpha), or the brightness */
    u8 blend_ev;         /* 0x15: the first target's weight of 16 (alpha) */
} WindowBlendShadow;

enum AffineBgs { AFFINE_MAIN_BG2 = 1 << 0, AFFINE_MAIN_BG3 = 1 << 1, AFFINE_SUB_BG2 = 1 << 2, AFFINE_SUB_BG3 = 1 << 3 };

enum Windows { WINDOW_0 = 1 << 0, WINDOW_1 = 1 << 1, WINDOW_OBJ = 1 << 2 };

/* The PLANES bits write a window's planes with the colour effects enabled inside it, the
 * PLANES_PLAIN ones without; the RECT bits its rectangle. */
enum WindowDirty {
    DIRTY_MAIN_WIN0_PLANES = 1 << 0,
    DIRTY_MAIN_WIN1_PLANES = 1 << 1,
    DIRTY_SUB_WIN0_PLANES = 1 << 2,
    DIRTY_SUB_WIN1_PLANES = 1 << 3,
    DIRTY_MAIN_WIN0_RECT = 1 << 4,
    DIRTY_MAIN_WIN1_RECT = 1 << 5,
    DIRTY_SUB_WIN0_RECT = 1 << 6,
    DIRTY_SUB_WIN1_RECT = 1 << 7,
    DIRTY_SUB_WIN0_PLANES_PLAIN = 1 << 8,
    DIRTY_SUB_WIN1_PLANES_PLAIN = 1 << 9
};

/* DisplayShadow.scroll_dirty: the backgrounds whose scrolling (and affine parameters) to write. */
enum ScrollDirty {
    DIRTY_MAIN_BG0 = 1 << 0,
    DIRTY_MAIN_BG1 = 1 << 1,
    DIRTY_MAIN_BG2 = 1 << 2,
    DIRTY_MAIN_BG3 = 1 << 3,
    DIRTY_SUB_BG0 = 1 << 4,
    DIRTY_SUB_BG1 = 1 << 5,
    DIRTY_SUB_BG2 = 1 << 6,
    DIRTY_SUB_BG3 = 1 << 7
};

/* In the order func_02001ecc tries them: the first one set is applied. */
enum BlendRequest {
    BLEND_MAIN_OFF = 1 << 5,          /* no effect on the main screen */
    BLEND_MAIN_ALPHA = 1 << 4,        /* alpha blending on the main screen */
    BLEND_SUB_OFF = 1 << 1,           /* no effect on the sub screen */
    BLEND_SUB_ALPHA = 1 << 3,         /* alpha blending on the sub screen */
    BLEND_SUB_BRIGHTNESS = 1 << 2,    /* brightness change on the sub screen */
    BLEND_SUB_BRIGHTNESS_OBJ = 1 << 0 /* the same, set with the sub screen's OBJ window */
};

void DisplayShadow_MainBlendOff(void);
void DisplayShadow_SetMainAlpha(u8 planes, u8 second_planes, u8 ev);
void DisplayShadow_SubBlendOff(void);
void DisplayShadow_SetSubAlpha(u8 planes, u8 second_planes, u8 ev);
void DisplayShadow_SetSubBrightness(u8 brightness);
u8 DisplayShadow_ExcludeSubBrightnessPlanes(u8 planes);
void DisplayShadow_SubBrightnessAllPlanes(void);
void DisplayShadow_EndSubObjWindowBrightness(void);
void DisplayShadow_BeginSubObjWindowBrightness(void);
void Display_SetBrightnessNow(unsigned int brightness);
void DisplayShadow_HideSubPlanes(u8 planes);
void DisplayShadow_ShowSubPlanes(int planes);
void DisplayShadow_SetSubPlanes(u8 planes);
u8 DisplayShadow_GetSubPlanes(void);
void DisplayShadow_HideMainPlanes(u8 planes);
void DisplayShadow_ShowMainPlanes(u8 planes);
void DisplayShadow_SetMainPlanes(u8 planes);
u8 DisplayShadow_GetMainPlanes(void);
void DisplayShadow_DisableSubWindows(u8 windows);
void DisplayShadow_EnableSubWindows(u8 windows);
void DisplayShadow_SetSubWindows(u8 windows);
u8 DisplayShadow_GetSubWindows(void);
void DisplayShadow_DisableMainWindows(u8 windows);
void DisplayShadow_EnableMainWindows(u8 windows);
void DisplayShadow_SetMainWindows(u8 windows);
u8 DisplayShadow_GetMainWindows(void);
void Display_SetSubBgModeNow(int mode);
void Display_SetMainBgModeNow(int mode);
void DisplayShadow_SetSubBgMode(u8 mode);
void DisplayShadow_SetMainBgMode(u8 mode);
void DisplayShadow_SetSubWindow1(u8 left, u8 top, u8 right, u8 bottom);
void DisplayShadow_SetSubWindow0(u8 left, u8 top, u8 right, u8 bottom);
void DisplayShadow_SetMainWindow1(u8 left, u8 top, u8 right, u8 bottom);
void DisplayShadow_SetMainWindow0(u8 left, u8 top, u8 right, u8 bottom);
void DisplayShadow_SetSubObjWindowPlanes(u8 planes);
void DisplayShadow_SetMainObjWindowPlanes(u8 planes);
void DisplayShadow_SetSubOutsidePlanes(u8 planes);
void DisplayShadow_HideMainOutsidePlanes(u8 planes);
void DisplayShadow_SetMainOutsidePlanes(u8 planes);
void DisplayShadow_MarkSubWindow1Planes(unsigned int effects);
void DisplayShadow_MarkSubWindow0Planes(int effects);
void DisplayShadow_SetSubWindow1Planes(u8 planes, int effects);
void DisplayShadow_SetSubWindow0Planes(s8 planes, int effects);
void DisplayShadow_SetMainWindow1Planes(u8 planes);
void DisplayShadow_SetMainWindow0Planes(u8 planes);
void DisplayShadow_SetSubBg3Scroll(int x, int y);
void DisplayShadow_SetSubBg2Scroll(int x, int y);
void DisplayShadow_SetSubBg1Scroll(u16 x, u16 y);
void DisplayShadow_SetSubBg0Scroll(u16 x, u16 y);
void DisplayShadow_SetMainBg3Scroll(unsigned int x, unsigned int y);
void DisplayShadow_SetMainBg2Scroll(unsigned int x, unsigned int y);
void DisplayShadow_SetMainBg1Scroll(u16 x, u16 y);
void DisplayShadow_ResetWindow(WindowShadow *window);
void DisplayShadow_ResetAffine(BgAffineShadow *affine);
void DisplayShadow_ResetScroll(ScrollShadow *scroll);
void DisplayShadow_Flush(void);
void DisplayShadow_WriteModes(void);
void Display_EmptyHook(void);
void DisplayShadow_Reset(void);
void Display_LoadBackdropColor(void);
void DisplayShadow_SetWindow(unsigned int window, int left, int top, int right, int bottom);

#endif
