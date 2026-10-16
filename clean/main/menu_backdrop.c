/* The backdrop behind the menus (menu_backdrop.h). */
#include "menu_backdrop.h"

#include "a_mes_obj.h"
#include "autoload_2/heap.h"
#include "c_library.h"
#include "camera_control.h"
#include "camera_modes.h"
#include "clean.h"
#include "display_layers.h"
#include "display_shadow.h"
#include "empty_0203de64.h"
#include "item_texture.h"
#include "itcm/interrupts.h"
#include "itcm/line_effects.h"
#include "line_handlers.h"
#include "player_record.h"
#include "player_records.h"
#include "sky.h"
#include "state_flags.h"
#include "tile_convert.h"

/* The steps' handlers, by MenuBackdropState (the game's functions). */
extern const u32 data_020df2a4[MENU_BACKDROP_STATES];

extern u8 data_021cfc0c;          /* the holds */
extern u8 data_021cfc10;          /* the picture's style */
extern u8 data_021cfc14;          /* WIPE_HANDLER_ADDED */
extern u16 data_021cfc18;         /* the scroll, 0 to 0x1ff */
extern s16 data_021cfc1c;         /* the sweep's edge: window 1's left edge on the pattern's first line */
extern u16 data_021cfc20;         /* the step, MenuBackdropState */
extern s32 data_021cfc24;         /* the ease's step */
extern s32 data_021cfc28;         /* the ease's time left, 0x1000 (1.0) down to 0 */
extern LineHandler data_021cfc2c; /* the sweep's line handler */

/* Window 1's left edge on each line of the first half of the pattern, and the pattern's line
 * (itcm/line_effects.c); in the DTCM. */
#define EDGE_LINES 24
extern u8 data_027e0438[EDGE_LINES];
extern u8 data_027e0434;

extern int data_021c8c9c; /* POWCNT1's swap bit (display_frame.c) */
extern u8 data_020e54a8;  /* 0 outdoors, 1 in a room */
extern Heap *data_021fbe94;

/* "menu/inventory/b_itm_back.bsc", "menu/bas/b_bas_%d.bpl", "menu/bas/b_bas_%d.bch" */
extern const char data_020df2d8[];
extern const char data_020df2f8[];
extern const char data_020df310[];

extern s32 FX_MulFunc(s32 a, s32 b);

/* The sweep's functions: window 1's edge each line (LineFx_Window1Edge), and the VBlank
 * functions of the sweep in (func_0206f408) and out (MenuBackdrop_WipeOutFrame). */
extern void func_01ffccf4(void);
extern void func_0206f408(void);
extern void func_0206f38c(void);

#define REG_WIN1H (*(volatile u16 *) 0x04000042)

#define WIPE_HANDLER_ADDED 0x01

/* The layers of the picture: background 2 of the main and of the sub engine. */
#define LAYER_MAIN LAYER_MAIN_BG2
#define LAYER_SUB LAYER_SUB_BG2

#define WINDOW_0 0x01
#define WINDOW_1 0x02
#define PLANE_BG1 0x02
#define PLANE_BG2 0x04
#define PLANE_BG3 0x08
#define PLANES_ALL 0x1f     /* BG0 to BG3 and OBJ */
#define PLANES_BUT_BG2 0x1b /* BG0, BG1, BG3 and OBJ */
#define SUB_PLANES_BG 0x0f  /* BG0 to BG3 */

#define EASE_ONE 0x1000
#define EASE_STEP 0x200
#define SCROLL_MASK 0x1ff

/* The sweep: the edge moves 20 pixels a frame, from 0x117 down to 0 in and from 0 up past
 * 0x102 out; window 1 then ends at the screen's right edge (0xff) and is empty from 0xfe. */
#define WIPE_SPEED 20
#define WIPE_IN_START 0x117
#define WIPE_OUT_END 0x103
#define EDGE_EMPTY 0xfe
#define WIN1H_EMPTY ((EDGE_EMPTY << 8) | 0xff)

#define SCREEN_RIGHT 0xff
#define SCREEN_BOTTOM 0xc0

/* The clothing's picture: 4 by 4 characters of 4 bits, and its 16 colours. */
#define CLOTHING_CHARS_SIZE 0x200
#define CLOTHING_PALETTE_SIZE 0x20
#define CLOTHING_MODEL_SIZE 0x2c4
#define CLOTHING_FIRST 0x11a8
#define CLOTHING_LAST 0x12af
#define PALETTE_COLOURS 16

static BOOL outdoors(void)
{
    return data_020e54a8 == 0;
}

/* The ease's time counted down by its step, at 0 at most. */
static void ease_count_down(void)
{
    if (data_021cfc28 > data_021cfc24) {
        data_021cfc28 -= data_021cfc24;
    } else {
        data_021cfc28 = 0;
    }
}

/* func_0206ead8 */
void MenuBackdrop_SetStyle(char style)
{
    data_021cfc10 = (u8) style;
}
CLEAN_AS(func_0206ead8, MenuBackdrop_SetStyle)

/* func_0206eae4: whether every hold of `mask` is set. */
int MenuBackdrop_IsHeld(int mask)
{
    return (mask & data_021cfc0c) == mask;
}
CLEAN_AS(func_0206eae4, MenuBackdrop_IsHeld)

/* func_0206eafc */
void MenuBackdrop_Release(unsigned int mask)
{
    data_021cfc0c = (u8) (data_021cfc0c & ~mask);
}
CLEAN_AS(func_0206eafc, MenuBackdrop_Release)

/* func_0206eb0c */
void MenuBackdrop_Hold(unsigned char mask)
{
    data_021cfc0c |= mask;
}
CLEAN_AS(func_0206eb0c, MenuBackdrop_Hold)

/* func_0206eb1c: colours 1 to 15 of `source` made halfway to white in `lightened` (each
 * component (c + 31) / 2).
 * QUIRK: colour 0 of the source is cleared, and that of `lightened` is left as it was; bit 15
 * of a colour is dropped. */
void MenuBackdrop_LightenPalette(u16 *source, u16 *lightened)
{
    source[0] = 0;
    for (int i = 1; i < PALETTE_COLOURS; i++) {
        u16 colour = source[i];
        u16 red = (u16) (((colour & 0x1f) + 0x1f) >> 1);
        u16 green = (u16) ((((colour >> 5) & 0x1f) + 0x1f) >> 1);
        u16 blue = (u16) ((((colour >> 10) & 0x1f) + 0x1f) >> 1);
        lightened[i] = (u16) (red | (green << 5) | (blue << 10));
    }
}
CLEAN_AS(func_0206eb1c, MenuBackdrop_LightenPalette)

/* func_0206eb7c (step 11): once the sweep out is over, closed: window 1 off, the main
 * picture hidden, state flag 0x10 cleared. Always 1. */
int MenuBackdrop_StepWipeOut(void)
{
    if (!MenuBackdrop_IsWiping()) {
        data_021cfc20 = MENU_BACKDROP_CLOSED;
        DisplayShadow_DisableMainWindows(WINDOW_1);
        DisplayLayer_HideAndResetScroll(LAYER_MAIN);
        StateFlags_Clear10();
    }
    return 1;
}
CLEAN_AS(func_0206eb7c, MenuBackdrop_StepWipeOut)

/* func_0206ebac (step 10): window 1 on (window 0 off) with every plane inside and all but
 * background 2 outside, backgrounds 1 and 3 hidden and the sweep out begun; step 11 once the
 * camera takes its previous mode. Always 1.
 * QUIRK: until then all of it is done again each frame, the sweep begun anew. */
int MenuBackdrop_StepRestore(void)
{
    DisplayShadow_EnableMainWindows(WINDOW_1);
    DisplayShadow_DisableMainWindows(WINDOW_0);
    DisplayShadow_SetMainWindow1Planes(PLANES_ALL);
    DisplayShadow_SetMainOutsidePlanes(PLANES_BUT_BG2);
    DisplayShadow_HideMainPlanes(PLANE_BG1 | PLANE_BG3);
    MenuBackdrop_BeginWipeOut();
    if (CameraControl_SetPreviousMode()) {
        data_021cfc20 = MENU_BACKDROP_WIPE_OUT;
    }
    return 1;
}
CLEAN_AS(func_0206ebac, MenuBackdrop_StepRestore)

/* func_0206ebec (step 9): the value eased from 1 to 0 (the time left squared). Once it is 0
 * and hold 1 is let go: the main picture loaded again and shown in front (priority 1 of the
 * sub engine's layer), state flag 4 cleared, the screens swapped back, backgrounds 1 to 3 of
 * the main engine hidden, the sub picture hidden, the sheet moved to the sub screen and,
 * outdoors, the sky shown on screen 0; state flag 1 cleared, and step 10. Always 1. */
int MenuBackdrop_StepEaseOut(void)
{
    if (data_021cfc28 == 0 && !MenuBackdrop_IsHeld(MENU_BACKDROP_HOLD_CLOSE)) {
        DisplayLayer_SetPriority(LAYER_SUB, 1);
        MenuBackdrop_LoadLayer(LAYER_MAIN);
        StateFlags_Clear4();
        data_021cfc20 = MENU_BACKDROP_RESTORE;
        data_021c8c9c = 0;
        DisplayShadow_HideMainPlanes(PLANE_BG1 | PLANE_BG2 | PLANE_BG3);
        DisplayLayer_Show(LAYER_MAIN);
        DisplayLayer_HideAndResetScroll(LAYER_SUB);
        AMesObj_SetSheetSub();
        if (outdoors()) {
            Sky_ShowOn(0);
        }
        StateFlags_Clear1();
        Empty0203de64_NothingValue68(0);
    }
    ease_count_down();
    StateFlags_SetValue((u32) FX_MulFunc(data_021cfc28, data_021cfc28));
    return 1;
}
CLEAN_AS(func_0206ebec, MenuBackdrop_StepEaseOut)

/* func_0206ec98 (step 8): the camera's saved view restored, if there is one; outdoors the sky
 * shown on screen 1 with background 3 of the main engine hidden; the ease begun and hold 1
 * set, and step 9. Always 1. */
int MenuBackdrop_StepClose(void)
{
    if (CameraControl_IsViewSaved()) {
        CameraControl_RestoreView();
    }
    if (outdoors()) {
        Empty0203de64_NothingValue6c(0);
        Sky_ShowOn(1);
        DisplayShadow_HideMainPlanes(PLANE_BG3);
    }
    data_021cfc20 = MENU_BACKDROP_EASE_OUT;
    data_021cfc28 = EASE_ONE;
    data_021cfc24 = EASE_STEP;
    MenuBackdrop_Hold(MENU_BACKDROP_HOLD_CLOSE);
    return 1;
}
CLEAN_AS(func_0206ec98, MenuBackdrop_StepClose)

/* func_0206ed04 (step 6): both windows off, backgrounds 1 to 3 of the main engine hidden, and
 * step 7. Always 1. */
int MenuBackdrop_StepShow(void)
{
    DisplayShadow_DisableMainWindows(WINDOW_0);
    DisplayShadow_DisableMainWindows(WINDOW_1);
    DisplayShadow_HideMainPlanes(PLANE_BG1 | PLANE_BG2 | PLANE_BG3);
    data_021cfc20 = MENU_BACKDROP_OPEN;
    return 1;
}
CLEAN_AS(func_0206ed04, MenuBackdrop_StepShow)

/* func_0206ed2c (step 5): the value eased from 0 to 1 (1 less the time left squared); once
 * the time is over, step 6 with the sky hidden outdoors and the main engine in mode 0.
 * Always 1. */
int MenuBackdrop_StepEaseIn(void)
{
    if (data_021cfc28 == 0) {
        data_021cfc20 = MENU_BACKDROP_SHOW;
        if (outdoors()) {
            Sky_HideOnMain();
        }
        DisplayShadow_SetMainBgMode(0);
        return 1;
    }
    ease_count_down();
    StateFlags_SetValue((u32) (EASE_ONE - FX_MulFunc(data_021cfc28, data_021cfc28)));
    return 1;
}
CLEAN_AS(func_0206ed2c, MenuBackdrop_StepEaseIn)

/* func_0206eda0 (step 4): once the sub engine's picture is loaded: window 1 off, the sub
 * engine's backgrounds hidden but the picture's, the screens swapped, state flag 0x10
 * cleared and 1 set, the main picture hidden, step 5 and, outdoors, the sky shown on screen 1.
 * Always 1. */
int MenuBackdrop_StepLoadSub(void)
{
    if (MenuBackdrop_LoadLayer(LAYER_SUB)) {
        DisplayShadow_DisableMainWindows(WINDOW_1);
        DisplayShadow_HideSubPlanes(SUB_PLANES_BG);
        DisplayLayer_Show(LAYER_SUB);
        data_021c8c9c = 1;
        StateFlags_Clear10();
        StateFlags_Set1();
        DisplayLayer_HideAndResetScroll(LAYER_MAIN);
        data_021cfc20 = MENU_BACKDROP_EASE_IN;
        if (outdoors()) {
            Sky_ShowOn(1);
        }
    }
    return 1;
}
CLEAN_AS(func_0206eda0, MenuBackdrop_StepLoadSub)

/* func_0206ee08 (step 3): once the camera stands still, state flag 4 set with the value 0,
 * the ease begun, and step 4. Always 1. */
int MenuBackdrop_StepStill(void)
{
    if (CameraControl_SetModeStill()) {
        StateFlags_Set4();
        StateFlags_SetValue(0);
        data_021cfc28 = EASE_ONE;
        data_021cfc24 = EASE_STEP;
        data_021cfc20 = MENU_BACKDROP_LOAD_SUB;
    }
    return 1;
}
CLEAN_AS(func_0206ee08, MenuBackdrop_StepStill)

/* func_0206ee4c (step 2): once the sweep in is over, window 1 the whole screen from x 1, step
 * 3 and the sub engine's layer set up. Always 1. */
int MenuBackdrop_StepWipeIn(void)
{
    if (!MenuBackdrop_IsWiping()) {
        DisplayShadow_SetMainWindow1(1, 0, SCREEN_RIGHT, SCREEN_BOTTOM);
        data_021cfc20 = MENU_BACKDROP_STILL;
        MenuBackdrop_SetUpSubLayer();
    }
    return 1;
}
CLEAN_AS(func_0206ee4c, MenuBackdrop_StepWipeIn)

/* func_0206ee7c (step 1): once the main engine's picture is loaded: step 2, the picture shown
 * through window 1 (every plane inside, all but background 2 outside), the sweep in begun and
 * step 2 run at once. Always 1. */
int MenuBackdrop_StepLoadMain(void)
{
    if (!MenuBackdrop_LoadLayer(LAYER_MAIN)) {
        return 1;
    }
    data_021cfc20 = MENU_BACKDROP_WIPE_IN;
    DisplayLayer_Show(LAYER_MAIN);
    DisplayShadow_EnableMainWindows(WINDOW_1);
    DisplayShadow_SetMainWindow1Planes(PLANES_ALL);
    DisplayShadow_SetMainOutsidePlanes(PLANES_BUT_BG2);
    MenuBackdrop_BeginWipeIn();
    return MenuBackdrop_StepWipeIn();
}
CLEAN_AS(func_0206ee7c, MenuBackdrop_StepLoadMain)

/* func_0206eec0 (steps 7 and 12): nothing to do but scroll. */
int MenuBackdrop_StepStay(void)
{
    return 1;
}
CLEAN_AS(func_0206eec0, MenuBackdrop_StepStay)

/* func_0206eec4 (step 0): nothing, not even the scroll. */
int MenuBackdrop_StepIdle(void)
{
    return 0;
}
CLEAN_AS(func_0206eec4, MenuBackdrop_StepIdle)

/* func_0206eec8: the frame's step; unless idle, the picture scrolled one pixel right and down
 * (on the main engine's layer in steps 2, 4, 10 and 11 as the step leaves it, else on the
 * sub engine's).
 * QUIRK: the step is not checked against the table's size. */
void MenuBackdrop_Update(void)
{
    typedef int (*MenuBackdropStep)(void);

    MenuBackdropStep step = (MenuBackdropStep) (uintptr_t) data_020df2a4[data_021cfc20];
    if (!step()) {
        return;
    }
    data_021cfc18 = (u16) ((data_021cfc18 + 1) & SCROLL_MASK);
    u16 state = data_021cfc20;
    if (state == MENU_BACKDROP_WIPE_IN || state == MENU_BACKDROP_LOAD_SUB || state == MENU_BACKDROP_RESTORE ||
        state == MENU_BACKDROP_WIPE_OUT) {
        DisplayLayer_SetScroll(LAYER_MAIN, data_021cfc18, data_021cfc18);
    } else {
        DisplayLayer_SetScroll(LAYER_SUB, data_021cfc18, data_021cfc18);
    }
}
CLEAN_AS(func_0206eec8, MenuBackdrop_Update)

/* func_0206ef34: the backdrop put away at once: both pictures hidden (always, since
 * func_0203de78 is 0), window 1 off, the screens not swapped, state flag 0x10 cleared, the
 * steps reset and the sweep stopped. */
void MenuBackdrop_End(void)
{
    if (!Empty0203de64_No78()) {
        DisplayLayer_HideAndResetScroll(LAYER_MAIN);
        DisplayLayer_HideAndResetScroll(LAYER_SUB);
    }
    DisplayShadow_DisableMainWindows(WINDOW_1);
    data_021c8c9c = 0;
    StateFlags_Clear10();
    MenuBackdrop_Reset();
    MenuBackdrop_StopWipe();
}
CLEAN_AS(func_0206ef34, MenuBackdrop_End)

/* func_0206ef70: idle, with the scroll and the sweep's edge at 0. */
void MenuBackdrop_Reset(void)
{
    data_021cfc18 = 0;
    data_021cfc20 = MENU_BACKDROP_IDLE;
    data_021cfc1c = 0;
}
CLEAN_AS(func_0206ef70, MenuBackdrop_Reset)

/* func_0206ef8c: hold 1 let go, so closing can go on. */
void MenuBackdrop_ReleaseClose(void)
{
    MenuBackdrop_Release(MENU_BACKDROP_HOLD_CLOSE);
}
CLEAN_AS(func_0206ef8c, MenuBackdrop_ReleaseClose)

/* func_0206ef98: opening begun: the main engine's layer set up, step 1, the clothing's style
 * and state flag 0x10 set. */
void MenuBackdrop_Open(void)
{
    MenuBackdrop_SetUpMainLayer();
    data_021cfc20 = MENU_BACKDROP_LOAD_MAIN;
    data_021cfc10 = MENU_BACKDROP_STYLE_CLOTHING;
    StateFlags_Set10();
}
CLEAN_AS(func_0206ef98, MenuBackdrop_Open)

/* func_0206efc0: closing begun: step 8 and state flag 0x10 set. */
void MenuBackdrop_Close(void)
{
    data_021cfc20 = MENU_BACKDROP_CLOSE;
    StateFlags_Set10();
}
CLEAN_AS(func_0206efc0, MenuBackdrop_Close)

/* func_0206efd4: the picture loaded on `layer`; whether all of it was (the answers ANDed).
 * In the clothing's style: the player's clothing (the record's item at 0x2410) read into
 * blocks from the back of the current heap, its palette lightened and its image made
 * characters, both loaded, the blocks freed, then the screen file loaded. With no room for a
 * block, nothing is loaded and the answer is 0. Other styles load the style's files. */
int MenuBackdrop_LoadLayer(int layer)
{
    if (data_021cfc10 != MENU_BACKDROP_STYLE_CLOTHING) {
        return MenuBackdrop_LoadFiles(layer);
    }
    Heap *heap = data_021fbe94;
    u8 *player = PlayerRecords_Current();
    ItemCode clothing = *PlayerRecord_Item2410(player);

    u8 *chars = Heap_AllocBack(heap, CLOTHING_CHARS_SIZE);
    if (chars == NULL) {
        return 0;
    }
    u16 *palette = Heap_AllocBack(heap, CLOTHING_PALETTE_SIZE);
    if (palette == NULL) {
        Heap_Free(heap, chars);
        return 0;
    }
    DesignModel *model = Heap_AllocBack(heap, CLOTHING_MODEL_SIZE);
    if (model == NULL) {
        Heap_Free(heap, chars);
        Heap_Free(heap, palette);
        return 0;
    }
    ClothTexture_Load(model, &clothing, player);
    MenuBackdrop_LightenPalette((u16 *) (void *) ClothTexture_Palette(model), palette);
    int loaded = DisplayLayer_LoadPalettes((u8 *) palette, (unsigned int) layer, 0, 0, 0);
    TileConvert_BitmapToCharsBytes(ClothTexture_Image(model), chars, 4, 4);
    loaded &= DisplayLayer_LoadChars((u32) (uintptr_t) chars, layer, 0, 0, 0xf);
    Heap_Free(heap, chars);
    Heap_Free(heap, palette);
    Heap_Free(heap, model);
    loaded &= DisplayLayer_LoadScreenFromFile(data_020df2d8, heap, layer);
    return loaded;
}
CLEAN_AS(func_0206efd4, MenuBackdrop_LoadLayer)

/* func_0206f0d4: the picture's screen, then the style's palette and characters, loaded on
 * `layer` from their files; 0 when the screen or the palette could not be. Then 1.
 * QUIRK: whether the characters loaded is not looked at. */
int MenuBackdrop_LoadFiles(int layer)
{
    Heap *heap = data_021fbe94;
    char path[36];

    if (!DisplayLayer_LoadScreenFromFile(data_020df2d8, heap, layer)) {
        return 0;
    }
    CLib_SPrintf(path, data_020df2f8, data_021cfc10);
    if (!DisplayLayer_LoadPalettesFromFile(path, heap, layer, 0, 0, 0)) {
        return 0;
    }
    CLib_SPrintf(path, data_020df310, data_021cfc10);
    DisplayLayer_LoadCharsFromFile(path, heap, layer, 0, 0, 0xf);
    return 1;
}
CLEAN_AS(func_0206f0d4, MenuBackdrop_LoadFiles)

/* func_0206f150: the sub engine's layer at priority 3, with background control 0. */
void MenuBackdrop_SetUpSubLayer(void)
{
    DisplayLayer_SetPriority(LAYER_SUB, 3);
    DisplayLayer_SetBgControl(LAYER_SUB, 0, 0, 0);
}
CLEAN_AS(func_0206f150, MenuBackdrop_SetUpSubLayer)

/* func_0206f170: the main engine's layer at priority 1, with background control 0. */
void MenuBackdrop_SetUpMainLayer(void)
{
    DisplayLayer_SetPriority(LAYER_MAIN, 1);
    DisplayLayer_SetBgControl(LAYER_MAIN, 0, 0, 0);
}
CLEAN_AS(func_0206f170, MenuBackdrop_SetUpMainLayer)

/* func_0206f190: for a piece of clothing (0x11a8-0x12af), its image made characters in
 * `chars` and its palette lightened in `palette`, both queued on `task` for the sub engine's
 * layer, and if that was taken, the item made the player's backdrop clothing (the record's
 * item at 0x2410). Nothing for another item or without room for the clothing's model. */
void MenuBackdrop_QueueDesign(u16 *item, LayerTaskPair *task, u8 *chars, u16 *palette)
{
    u8 *player = PlayerRecords_Current();
    if (*item < CLOTHING_FIRST || *item > CLOTHING_LAST) {
        return;
    }
    Heap *heap = data_021fbe94;
    DesignModel *model = Heap_AllocBack(heap, CLOTHING_MODEL_SIZE);
    if (model == NULL) {
        return;
    }
    ClothTexture_Load(model, item, player);
    MenuBackdrop_LightenPalette((u16 *) (void *) ClothTexture_Palette(model), palette);
    TileConvert_BitmapToCharsBytes(ClothTexture_Image(model), chars, 4, 4);
    Heap_Free(heap, model);
    if (LayerTask_QueueCharsAndPalette(task, (int) (uintptr_t) chars, LAYER_SUB, 0, 0, 0xf, (int) (uintptr_t) palette, 0)) {
        PlayerRecord_SetItem2410(player, item);
    }
}
CLEAN_AS(func_0206f190, MenuBackdrop_QueueDesign)

/* func_0206f244 */
int MenuBackdrop_IsClosed(void)
{
    return data_021cfc20 == MENU_BACKDROP_CLOSED;
}
CLEAN_AS(func_0206f244, MenuBackdrop_IsClosed)

/* func_0206f258: whether the step is 5, 6 or 7 (easing in or open). */
int MenuBackdrop_IsUp(void)
{
    return data_021cfc20 >= MENU_BACKDROP_EASE_IN && data_021cfc20 <= MENU_BACKDROP_OPEN;
}
CLEAN_AS(func_0206f258, MenuBackdrop_IsUp)

/* func_0206f278: whether the sweep's line handler is in. */
int MenuBackdrop_IsWiping(void)
{
    return (data_021cfc14 & WIPE_HANDLER_ADDED) != 0;
}
CLEAN_AS(func_0206f278, MenuBackdrop_IsWiping)

/* Window 1's left edge on the pattern's first lines: `edge` less the line, from 0 to
 * EDGE_EMPTY, so the edge slants. */
static void set_edges(int edge)
{
    for (int i = 0; i < EDGE_LINES; i++) {
        int left = edge - i;
        if (left < 0) {
            data_027e0438[i] = 0;
        } else if (left > EDGE_EMPTY) {
            data_027e0438[i] = EDGE_EMPTY;
        } else {
            data_027e0438[i] = (u8) left;
        }
    }
}

/* func_0206f28c: the sweep out begun from the left edge: the line handler added (window 1's
 * edge each line, func_0206f38c each VBlank), the window from x 1 over the whole screen and
 * the pattern at its first line. */
void MenuBackdrop_BeginWipeOut(void)
{
    data_021cfc1c = 0;
    if (LineHandlers_Add(&data_021cfc2c, (int) (uintptr_t) func_01ffccf4, (int) (uintptr_t) func_0206f38c, 0)) {
        data_021cfc14 |= WIPE_HANDLER_ADDED;
    }
    for (int i = 0; i < EDGE_LINES; i++) {
        data_027e0438[i] = 0;
    }
    DisplayShadow_SetMainWindow1(1, 0, SCREEN_RIGHT, SCREEN_BOTTOM);
    data_027e0434 = 0;
}
CLEAN_AS(func_0206f28c, MenuBackdrop_BeginWipeOut)

/* func_0206f2f0: the sweep in begun from beyond the right edge: the line handler added
 * (window 1's edge each line, func_0206f408 each VBlank), the window empty on every line of
 * the pattern and set over the whole screen, and the pattern at its first line.
 * QUIRK: the window's left edge is given as the sweep's edge, 0x117, which its 8-bit
 * parameter makes 0x17; the line handler sets the edge of each line anyway. */
void MenuBackdrop_BeginWipeIn(void)
{
    data_021cfc1c = WIPE_IN_START;
    if (LineHandlers_Add(&data_021cfc2c, (int) (uintptr_t) func_01ffccf4, (int) (uintptr_t) func_0206f408, 0)) {
        data_021cfc14 |= WIPE_HANDLER_ADDED;
    }
    for (int i = 0; i < EDGE_LINES; i++) {
        data_027e0438[i] = EDGE_EMPTY;
    }
    DisplayShadow_SetMainWindow1((u8) data_021cfc1c, 0, SCREEN_RIGHT, SCREEN_BOTTOM);
    data_027e0434 = 0;
}
CLEAN_AS(func_0206f2f0, MenuBackdrop_BeginWipeIn)

/* func_0206f35c: the sweep's line handler taken out, if it is in. */
void MenuBackdrop_StopWipe(void)
{
    if (data_021cfc14 & WIPE_HANDLER_ADDED) {
        LineHandlers_Remove(&data_021cfc2c);
        data_021cfc14 &= (u8) ~WIPE_HANDLER_ADDED;
    }
}
CLEAN_AS(func_0206f35c, MenuBackdrop_StopWipe)

/* func_0206f38c: the sweep out's VBlank function: the edge moved right; once it has passed
 * the screen, the line handler taken out and the window left empty. Then the pattern's edges
 * set from it.
 * HW: WIN1H is written at once, the line handler no longer setting it. */
void MenuBackdrop_WipeOutFrame(void)
{
    if (data_021cfc1c < WIPE_OUT_END) {
        data_021cfc1c = (s16) (data_021cfc1c + WIPE_SPEED);
    } else {
        LineHandlers_Remove(&data_021cfc2c);
        data_021cfc14 &= (u8) ~WIPE_HANDLER_ADDED;
        data_021cfc1c = EDGE_EMPTY;
        REG_WIN1H = WIN1H_EMPTY;
    }
    set_edges(data_021cfc1c);
}
CLEAN_AS(func_0206f38c, MenuBackdrop_WipeOutFrame)
