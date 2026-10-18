/* The screen's transition between scenes (screen_transition.h). */
#include "screen_transition.h"

#include "autoload_2/approach.h"
#include "caution_window.h"
#include "clean.h"
#include "display_shadow.h"
#include "empty_0203de64.h"
#include "line_handlers.h"
#include "music_queue.h"
#include "scene_sound.h"
#include "transition_mark.h"

static_assert(offsetof(ScreenTransition, cover) == 0x04, "ScreenTransition.cover");
static_assert(offsetof(ScreenTransition, brightness) == 0x0c, "ScreenTransition.brightness");
static_assert(sizeof(ScreenTransitionFunctions) == 0x10, "ScreenTransitionFunctions");

#define REG16(address) (*(volatile u16 *) (address))
#define REG_DISPSTAT REG16(0x04000004)
#define REG_VCOUNT REG16(0x04000006)
#define REG_BG2CNT REG16(0x0400000c)
#define REG_WIN0H REG16(0x04000040)
#define REG_WIN0V REG16(0x04000044)
#define REG_DB_BG2CNT REG16(0x0400100c)
#define REG_DB_WIN0H REG16(0x04001040)
#define REG_DB_WIN0V REG16(0x04001044)
#define PALETTE_MAIN 0x05000000u
#define PALETTE_SUB 0x05000400u

#define DISPSTAT_IN_HBLANK 0x0002
#define BGCNT_PRIORITY 0x0003
#define BGCNT_KEEP 0x0043  /* the character base and the mosaic */
#define BG2CNT_MAIN 0x0600 /* screen base 6, priority 0 */
#define BG2CNT_SUB 0x0e04  /* screen base 0xe, character base 1, priority 0 */
#define BLACK 0x8000       /* a colour of the clear backgrounds */
#define TILE_COLOUR_1 0x1111

#define PLANE_BG2 0x04
#define PLANE_OBJ 0x10
#define WINDOW_0 0x01
#define WINDOW_0_PLANES 0x1b /* BG0, BG1, BG3 and OBJ inside the circle */
#define BRIGHTNESS_BLACK (-16)
#define BRIGHTNESS_WHITE 16
#define FULL_SPEED 0x1000 /* a transition done in one frame */

#define SCREEN_HEIGHT 192
#define CIRCLE_MAX_RADIUS 160     /* the half diagonal of the screen, near enough */
#define WINDOW_SPAN_ALL 0x00ff    /* window 0 from x 0 to 255 */
#define WINDOW_SPAN_NONE 0x8080   /* an empty window at the centre */
#define CIRCLE_HALF_WIDTH 0x80000 /* 128 in fixed point: wider than half the screen */

extern void MIi_CpuClear16(u16 value, void *destination, u32 size);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG2CharPtr(void);
extern void *G2S_GetBG2ScrPtr(void);
extern void *G2S_GetBG2CharPtr(void);
extern int FX_Div(int numerator, int denominator);
extern int FX_Sqrt(int value);
/* The circle's HBlank and VBlank functions, as the game's line handler gets them. */
extern void func_02042154(void);
extern void func_02042120(void);

extern ScreenTransition data_021c75b8;
extern u8 data_021c75b0;   /* closing is allowed when the screen is not shown */
extern u8 data_021c75ac;   /* the circle's flags (SCREEN_TRANSITION_HANDLER, ...) */
extern u16 *data_021c75b4; /* the circle's table of lines shown */
extern LineHandler data_021c75cc;
extern u16 data_021c75e8[SCREEN_TRANSITION_LINES]; /* the two tables of lines, one after the other */
extern u16 data_021c76a8[SCREEN_TRANSITION_LINES];
extern const ScreenTransitionFunctions data_020ca514[];
extern Obj021c526c *data_021c526c;

static Music2d0 *music_2d0(void)
{
    return (Music2d0 *) (void *) data_021c526c->unk_2d0;
}

/* `value` shifted right as the ARM's ASR does. */
static s32 asr(s32 value, int bits)
{
    return value >> bits;
}

/* Background 2 of both engines made a clear black layer: its control set, its map cleared,
 * its first tile all colour 1 and the palette's colours 0 and 1 black; then shown.
 * HW: each control register read, written, read and written again. */
static void clear_bg2(void)
{
    REG_BG2CNT &= (u16) ~BGCNT_PRIORITY;
    REG_BG2CNT = (u16) ((REG_BG2CNT & BGCNT_KEEP) | BG2CNT_MAIN);
    MIi_CpuClear16(0, G2_GetBG2ScrPtr(), 0x800);
    MIi_CpuClear16(TILE_COLOUR_1, G2_GetBG2CharPtr(), 0x20);
    MIi_CpuClear16(BLACK, (void *) (uintptr_t) PALETTE_MAIN, 4);
    DisplayShadow_ShowMainPlanes(PLANE_BG2);

    REG_DB_BG2CNT &= (u16) ~BGCNT_PRIORITY;
    REG_DB_BG2CNT = (u16) ((REG_DB_BG2CNT & BGCNT_KEEP) | BG2CNT_SUB);
    MIi_CpuClear16(0, G2S_GetBG2ScrPtr(), 0x800);
    MIi_CpuClear16(TILE_COLOUR_1, G2S_GetBG2CharPtr(), 0x20);
    MIi_CpuClear16(BLACK, (void *) (uintptr_t) PALETTE_SUB, 4);
    DisplayShadow_ShowSubPlanes(PLANE_BG2);
}

/* func_02041a9c: background 2 of both engines made a clear black layer and shown. */
void ScreenTransition_ClearBg2(void)
{
    clear_bg2();
}
CLEAN_AS(func_02041a9c, ScreenTransition_ClearBg2)

/* func_02041b74: background 2 of both engines hidden (before the screen opens). */
void ScreenTransition_HideBg2(void)
{
    DisplayShadow_HideMainPlanes(PLANE_BG2);
    DisplayShadow_HideSubPlanes(PLANE_BG2);
    Empty0203de64_NothingValue68(0);
}
CLEAN_AS(func_02041b74, ScreenTransition_HideBg2)

/* func_02041b90: the closed screen: only the main engine's OBJ shown, background 2 cleared,
 * and the brightness black. */
void ScreenTransition_ShowClosed(void)
{
    Empty0203de64_NothingValue6c(0);
    DisplayShadow_SetMainPlanes(PLANE_OBJ);
    DisplayShadow_SetSubPlanes(0);
    ScreenTransition_ClearBg2();
    Display_SetBrightnessNow((unsigned int) BRIGHTNESS_BLACK);
}
CLEAN_AS(func_02041b90, ScreenTransition_ShowClosed)

/* func_02041bb8: after the VBlank, unless the caution window hides the planes: an opening or
 * closing transition applied (its kind's apply), then ended once `cover` got there (`speed` 0):
 * shown, or closed and the closed screen set up, each after its kind's finish. */
void ScreenTransition_AfterVBlank(void)
{
    ScreenTransition *transition = &data_021c75b8;

    if (CautionWindow_ArePlanesHidden()) {
        return;
    }
    u8 kind = transition->kind;
    u8 state = transition->state;
    if (state == SCREEN_TRANSITION_SHOWN || state == SCREEN_TRANSITION_CLOSED) {
        return;
    }
    if (data_020ca514[kind].apply != NULL) {
        data_020ca514[kind].apply();
    }

    if (transition->state == SCREEN_TRANSITION_OPENING) {
        if (transition->speed != 0) {
            return;
        }
        transition->state = SCREEN_TRANSITION_SHOWN;
        if (data_020ca514[kind].finish != NULL) {
            data_020ca514[kind].finish();
        }
    } else if (transition->state == SCREEN_TRANSITION_CLOSING) {
        if (transition->speed != 0) {
            return;
        }
        transition->state = SCREEN_TRANSITION_CLOSED;
        if (data_020ca514[kind].finish != NULL) {
            data_020ca514[kind].finish();
        }
        ScreenTransition_ShowClosed();
    }
}
CLEAN_AS(func_02041bb8, ScreenTransition_AfterVBlank)

/* func_02041c28: after the drawing, unless the caution window hides the planes: an opening or
 * closing transition's `cover` moved by `speed` towards 0x1000 (speed above 0) or 0 (below),
 * `speed` cleared once there; then its kind's update. */
void ScreenTransition_AfterDraw(void)
{
    ScreenTransition *transition = &data_021c75b8;

    if (CautionWindow_ArePlanesHidden()) {
        return;
    }
    u8 kind = transition->kind;
    u8 state = transition->state;
    if (state == SCREEN_TRANSITION_CLOSED || state == SCREEN_TRANSITION_SHOWN) {
        return;
    }
    s32 speed = transition->speed;
    if (speed != 0) {
        int target = speed >= 0 ? SCREEN_TRANSITION_COVERED : 0;
        int step = speed < 0 ? (int) (0u - (u32) speed) : speed;
        if (Approach_S32(&transition->cover, target, step)) {
            transition->speed = 0;
        }
    }
    if (data_020ca514[kind].update != NULL) {
        data_020ca514[kind].update();
    }
}
CLEAN_AS(func_02041c28, ScreenTransition_AfterDraw)

/* `numerator` over `frames` frames, as a speed per frame. */
static s32 speed_over(s32 numerator, int frames)
{
    return FX_Div(numerator, (int) ((u32) frames << 12));
}

/* func_02041c88: the closed screen opened by transition `kind` over `frames` frames (at once
 * for 0 frames and kind 3); unless `keep_music`, the music told. 0 when the screen is not
 * closed, else 1. */
int ScreenTransition_Open(int kind, int frames, int keep_music)
{
    ScreenTransition *transition = &data_021c75b8;

    if (transition->state != SCREEN_TRANSITION_CLOSED) {
        return 0;
    }
    ScreenTransition_HideBg2();
    transition->state = SCREEN_TRANSITION_OPENING;
    transition->kind = (u8) kind;
    transition->cover = SCREEN_TRANSITION_COVERED;
    if (data_020ca514[kind].begin != NULL) {
        data_020ca514[kind].begin();
    }
    if (frames == 0 || kind == SCREEN_TRANSITION_NONE) {
        transition->speed = -FULL_SPEED;
    } else {
        transition->speed = speed_over(-FULL_SPEED, frames);
    }
    if (keep_music == 0) {
        Music2d0_Finish(music_2d0());
        TransitionMark_SetBlinkFrames(kind);
    }
    return 1;
}
CLEAN_AS(func_02041c88, ScreenTransition_Open)

/* func_02041d14: the shown screen (or any, while data_021c75b0 is set, which is cleared)
 * closed by transition `kind` over `frames` frames: the running kind finished, the new one
 * begun and, when it has a begin, the music told (and the scene's sound stopped for the
 * circle). 0 when it cannot be closed now, else 1. */
int ScreenTransition_Close(int kind, int frames)
{
    ScreenTransition *transition = &data_021c75b8;
    u8 old = transition->kind;

    if (transition->state != SCREEN_TRANSITION_SHOWN && data_021c75b0 == 0) {
        return 0;
    }
    transition->state = SCREEN_TRANSITION_CLOSING;
    data_021c75b0 = 0;
    if (data_020ca514[old].finish != NULL) {
        data_020ca514[old].finish();
    }
    transition->kind = (u8) kind;
    transition->cover = 0;
    if (data_020ca514[kind].begin != NULL) {
        data_020ca514[kind].begin();
        Music2d0_Start(music_2d0());
        TransitionMark_SetDelay(kind);
        if (kind == SCREEN_TRANSITION_CIRCLE) {
            SceneSound_Stop();
        }
    }
    if (frames == 0 || kind == SCREEN_TRANSITION_NONE) {
        transition->speed = FULL_SPEED;
    } else {
        transition->speed = speed_over(FULL_SPEED, frames);
    }
    return 1;
}
CLEAN_AS(func_02041d14, ScreenTransition_Close)

/* func_02041dc4: closed, black, still; no table of lines and no flags. */
void ScreenTransition_Reset(void)
{
    data_021c75b8.state = SCREEN_TRANSITION_CLOSED;
    data_021c75b8.kind = SCREEN_TRANSITION_BLACK;
    data_021c75b8.brightness = BRIGHTNESS_BLACK;
    data_021c75b8.cover = SCREEN_TRANSITION_COVERED;
    data_021c75b8.speed = 0;
    data_021c75b4 = NULL;
    data_021c75ac = 0;
}
CLEAN_AS(func_02041dc4, ScreenTransition_Reset)

/* func_02041df4, func_02041df8, func_02041dfc: kind 3 applies, updates and finishes nothing. */
void ScreenTransitionNone_Apply(void) {}
CLEAN_AS(func_02041df4, ScreenTransitionNone_Apply)

void ScreenTransitionNone_Update(void) {}
CLEAN_AS(func_02041df8, ScreenTransitionNone_Update)

void ScreenTransitionNone_Finish(void) {}
CLEAN_AS(func_02041dfc, ScreenTransitionNone_Finish)

/* func_02041e00: kind 3 begins with the brightness normal. */
void ScreenTransitionNone_Begin(void)
{
    Display_SetBrightnessNow(0);
}
CLEAN_AS(func_02041e00, ScreenTransitionNone_Begin)

/* func_02041e0c: the circle's tables swapped: the one just written shown. */
void ScreenTransitionCircle_Apply(void)
{
    u8 flags = data_021c75ac;
    if (flags & SCREEN_TRANSITION_WRITE_FIRST) {
        data_021c75b4 = data_021c75e8;
        data_021c75ac = (u8) (flags & ~SCREEN_TRANSITION_WRITE_FIRST);
    } else {
        data_021c75b4 = data_021c76a8;
        data_021c75ac = (u8) (flags | SCREEN_TRANSITION_WRITE_FIRST);
    }
}
CLEAN_AS(func_02041e0c, ScreenTransitionCircle_Apply)

/* func_02041e48: the circle's lines written: for each line of the top half the span of window 0
 * across the circle of radius (0x1000 - cover) * 160 >> 12 around the screen's centre (an
 * empty span above it, the whole line where the circle is wider than the screen). Shown
 * (cover 0) the table written spans every line; closed (0x1000) both tables are empty. */
void ScreenTransitionCircle_Update(void)
{
    u16 *line = (data_021c75ac & SCREEN_TRANSITION_WRITE_FIRST) ? data_021c75e8 : data_021c76a8;
    s32 cover = data_021c75b8.cover;

    if (cover == 0) {
        MIi_CpuClear16(WINDOW_SPAN_ALL, line, SCREEN_TRANSITION_LINES * 2);
        return;
    }
    if (cover == SCREEN_TRANSITION_COVERED) {
        MIi_CpuClear16(WINDOW_SPAN_NONE, data_021c75e8, SCREEN_TRANSITION_LINES * 4);
        return;
    }

    s32 radius = asr((s32) ((u32) (SCREEN_TRANSITION_COVERED - cover) * CIRCLE_MAX_RADIUS), 12);
    s32 radius_squared = (s32) ((u32) radius * (u32) radius << 12);
    for (int i = 0; i < SCREEN_TRANSITION_LINES; i++) {
        int above = SCREEN_TRANSITION_LINES - i; /* the lines above the centre */
        if (above > radius) {
            *line = WINDOW_SPAN_NONE;
        } else {
            s32 half_width = FX_Sqrt((s32) ((u32) radius_squared - ((u32) (above * above) << 12)));
            if (half_width < CIRCLE_HALF_WIDTH) {
                u32 left = (u32) (0x80 - asr(half_width, 12)) & 0xffff;
                *line = (u16) (((left << 8) & 0xff00) | ((0x100 - left) & 0xff));
            } else {
                *line = WINDOW_SPAN_ALL;
            }
        }
        line++;
    }
}
CLEAN_AS(func_02041e48, ScreenTransitionCircle_Update)

/* func_02041f20: the circle finished: window 0 off on both engines, its line handler taken out,
 * background 2 hidden. */
void ScreenTransitionCircle_Finish(void)
{
    DisplayShadow_DisableMainWindows(WINDOW_0);
    DisplayShadow_DisableSubWindows(WINDOW_0);
    if (data_021c75ac & SCREEN_TRANSITION_HANDLER) {
        LineHandlers_Remove(&data_021c75cc);
        data_021c75ac &= (u8) ~SCREEN_TRANSITION_HANDLER;
    }
    DisplayShadow_HideMainPlanes(PLANE_BG2);
    DisplayShadow_HideSubPlanes(PLANE_BG2);
    Empty0203de64_NothingValue68(0);
}
CLEAN_AS(func_02041f20, ScreenTransitionCircle_Finish)

/* func_02041f6c: the circle begun: both tables cleared and the first shown, the windows and
 * background 2 set up, the line handler added (the HBlank function func_02042154, the VBlank
 * one func_02042120); a closed screen's brightness made normal, the window hiding it now. */
void ScreenTransitionCircle_Begin(void)
{
    MIi_CpuClear16(0, data_021c75e8, SCREEN_TRANSITION_LINES * 4);
    data_021c75b4 = data_021c75e8;
    ScreenTransitionCircle_SetUp();
    if (LineHandlers_Add(&data_021c75cc, (int) (uintptr_t) func_02042154, (int) (uintptr_t) func_02042120, 0)) {
        data_021c75ac |= SCREEN_TRANSITION_HANDLER;
    }
    if (data_021c75b8.cover == SCREEN_TRANSITION_COVERED) {
        Display_SetBrightnessNow(0);
    }
}
CLEAN_AS(func_02041f6c, ScreenTransitionCircle_Begin)

/* func_02041fe0: window 0 on for both engines with BG0, BG1, BG3 and OBJ inside and BG2
 * outside, the whole screen (shown) or nothing (otherwise) to begin with; background 2 made a
 * clear black layer and shown. */
void ScreenTransitionCircle_SetUp(void)
{
    Empty0203de64_NothingValue6c(0);
    DisplayShadow_EnableMainWindows(WINDOW_0);
    DisplayShadow_EnableSubWindows(WINDOW_0);
    DisplayShadow_SetMainWindow0Planes(WINDOW_0_PLANES);
    DisplayShadow_SetSubWindow0Planes(WINDOW_0_PLANES, 1);
    DisplayShadow_SetMainOutsidePlanes(PLANE_BG2);
    DisplayShadow_SetSubOutsidePlanes(PLANE_BG2);
    if (data_021c75b8.cover == 0) {
        DisplayShadow_SetMainWindow0(0, 0, 0xff, SCREEN_HEIGHT);
        DisplayShadow_SetSubWindow0(0, 0, 0xff, SCREEN_HEIGHT);
    } else {
        DisplayShadow_SetMainWindow0(0, 0, 0, 0);
        DisplayShadow_SetSubWindow0(0, 0, 0, 0);
    }
    clear_bg2();
}
CLEAN_AS(func_02041fe0, ScreenTransitionCircle_SetUp)

/* func_02042120 (the line handler's VBlank function): window 0 of both engines spans the
 * table's first line, over the whole height.
 * HW: in this order. */
void ScreenTransitionCircle_VBlank(void)
{
    REG_WIN0H = *data_021c75b4;
    REG_DB_WIN0H = *data_021c75b4;
    REG_WIN0V = SCREEN_HEIGHT;
    REG_DB_WIN0V = SCREEN_HEIGHT;
}
CLEAN_AS(func_02042120, ScreenTransitionCircle_VBlank)

/* func_02042154 (the line handler's HBlank function): on a visible line, the line's span (the
 * bottom half mirrors the top) written to window 0 of both engines while still in the HBlank.
 * HW: VCOUNT read, then DISPSTAT, then the two writes. */
void ScreenTransitionCircle_HBlank(void)
{
    int y = REG_VCOUNT;
    if (y >= SCREEN_HEIGHT) {
        return;
    }
    if (y >= SCREEN_TRANSITION_LINES) {
        y = SCREEN_HEIGHT - 1 - y;
    }
    u16 span = data_021c75b4[y];
    if (REG_DISPSTAT & DISPSTAT_IN_HBLANK) {
        REG_WIN0H = span;
        REG_DB_WIN0H = span;
    }
}
CLEAN_AS(func_02042154, ScreenTransitionCircle_HBlank)

/* func_02042198: a fade applies its brightness. */
void ScreenTransitionFade_Apply(void)
{
    Display_SetBrightnessNow((unsigned int) data_021c75b8.brightness);
}
CLEAN_AS(func_02042198, ScreenTransitionFade_Apply)

/* func_020421a8: a fade's brightness from `cover`: 0 shown, -16 (black) or 16 (white)
 * closed. */
void ScreenTransitionFade_Update(void)
{
    u32 scaled = (u32) data_021c75b8.cover << 4;
    if (data_021c75b8.kind == SCREEN_TRANSITION_BLACK) {
        scaled = 0u - scaled;
    }
    data_021c75b8.brightness = asr((s32) scaled, 12);
}
CLEAN_AS(func_020421a8, ScreenTransitionFade_Update)

/* func_020421cc: a fade finishes with nothing to undo. */
void ScreenTransitionFade_Finish(void) {}
CLEAN_AS(func_020421cc, ScreenTransitionFade_Finish)

/* func_020421d0: a fade begun at its start: normal when closing, else black or white. */
void ScreenTransitionFade_Begin(void)
{
    ScreenTransition *transition = &data_021c75b8;
    if (transition->state == SCREEN_TRANSITION_CLOSING) {
        transition->brightness = 0;
    } else if (transition->kind == SCREEN_TRANSITION_BLACK) {
        transition->brightness = BRIGHTNESS_BLACK;
    } else {
        transition->brightness = BRIGHTNESS_WHITE;
    }
    Display_SetBrightnessNow((unsigned int) transition->brightness);
}
CLEAN_AS(func_020421d0, ScreenTransitionFade_Begin)
