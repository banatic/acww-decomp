/* The scene of overlay 128 (vtable 0x0229cbc0, include/cpp/ov128/Obj_ov128_0229cbc0.h;
 * constructor StarView_New, 0x2d74 bytes): the telescope's view of the night sky with the
 * town's constellations. Overlay 92's dispatcher (ov092/menu_dispatch.h) opens it as overlay
 * group 0x19 (overlays 128 and 127) for GroupParams mode 0x2d; it is a menu scene
 * (ov002/menu_scene.h) on the sub screen.
 *
 * Overlay 127's sky view (ov127/star_scope.h, at 0x4a4) scrolls the sky by four arrows round
 * the screen's middle, held with the pen (sub states 0-2) or the d-pad (4-6); the sky's
 * palettes twinkle (main/star_palette.h). The constellation under the screen's middle is named
 * in a panel that slides up from the bottom ("<name>" and the Hangul suffix for
 * "constellation"), and slides away a while after none is there. A button at the bottom right
 * (ov002/panel_sprite.h, menu message 0x69), touched, or B or START, closes the scene.
 *
 * QUIRK: as the overlay is, nothing sets STAR_VIEW_FLAG_FREE, so the pointer never leaves its
 * spot by an arrow and the free pointer's sub states (3, 8 and the Y key's way back) are not
 * reached; nothing changes `pointer_spot` from 1 either. */
#ifndef CLEAN_OV128_STAR_VIEW_H
#define CLEAN_OV128_STAR_VIEW_H

#include "main/star_palette.h"
#include "main/text_label.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov002/panel_sprite.h"
#include "ov127/star_scope.h"
#include "types.h"

/* In `flags`. */
enum StarViewFlag {
    STAR_VIEW_FLAG_DRAWN = 0x1,      /* the button, the arrows and the grid are drawn */
    STAR_VIEW_FLAG_FREE = 0x2,       /* the pointer moves freely with the d-pad (nothing sets it) */
    STAR_VIEW_FLAG_INTERACTIVE = 0x4 /* set when the wipe in ends, cleared on closing (not read) */
};

/* The scene's states (MenuScene.state, phase 1) and sub states (MenuScene.sub_state, phase 2),
 * in the order of their tables. */
enum StarViewState {
    STAR_VIEW_STATE_OPEN = 0,           /* StarView_StateOpen */
    STAR_VIEW_STATE_WIPE_IN = 1,        /* StarView_StateWipeIn */
    STAR_VIEW_STATE_START_WIPE_OUT = 2, /* StarView_StateStartWipeOut */
    STAR_VIEW_STATE_WIPE_OUT = 3,       /* StarView_StateWipeOut */
    STAR_VIEW_STATES = 4
};

enum StarViewSubState {
    STAR_VIEW_SUB_TOUCH = 0,     /* StarView_SubTouch: the pen picks an arrow or the button */
    STAR_VIEW_SUB_PEN_HOLD = 1,  /* StarView_SubPenHold: an arrow held with the pen */
    STAR_VIEW_SUB_PEN_NUDGE = 2, /* StarView_SubPenNudge: the nudge after the pen let go */
    STAR_VIEW_SUB_FREE = 3,      /* StarView_SubFree: the free pointer */
    STAR_VIEW_SUB_KEYS = 4,      /* StarView_SubKeys: the d-pad picks an arrow */
    STAR_VIEW_SUB_KEY_HOLD = 5,  /* StarView_SubKeyHold: an arrow held with the d-pad */
    STAR_VIEW_SUB_KEY_NUDGE = 6, /* StarView_SubKeyNudge: the nudge after the d-pad let go */
    STAR_VIEW_SUB_GLIDE = 7,     /* StarView_SubGlide: the pointer glides */
    STAR_VIEW_SUB_PRESS = 8,     /* StarView_SubPress: the pointer's press plays */
    STAR_VIEW_SUB_RELEASE = 9,   /* StarView_SubRelease: the pointer's release plays */
    STAR_VIEW_SUB_BUTTON = 10,   /* StarView_SubButton: the button's press, then the close */
    STAR_VIEW_SUB_STATES = 11
};

/* The phases the scene sets (MenuScene_Update runs phase 0 by the vtable's slot 0x48, 1 by
 * 0x4c, 2 by 0x50, 3 by 0x54, 4 by 0x58 and 5 by 0x5c). */
enum StarViewPhase {
    STAR_VIEW_PHASE_WAIT = 0,        /* the base's MenuScene_Wait, on to phase 1 */
    STAR_VIEW_PHASE_STATES = 1,      /* StarView_RunState */
    STAR_VIEW_PHASE_INTERACTIVE = 2, /* StarView_RunInteractive */
    STAR_VIEW_PHASE_DELETE = 5       /* StarView_RequestDelete */
};

/* The name panel (`name_state`). */
enum StarViewNameState {
    STAR_VIEW_NAME_HIDDEN = 0,
    STAR_VIEW_NAME_RISING = 1,  /* `name_slide` up to 3 */
    STAR_VIEW_NAME_SHOWN = 2,   /* held while a constellation is pointed at, else for 20 frames */
    STAR_VIEW_NAME_SINKING = 3, /* `name_slide` down to 0, then the wanted name shown */
    STAR_VIEW_NAME_SLIDE_TOP = 3
};

#define STAR_VIEW_NONE (-1) /* no constellation */
#define STAR_VIEW_NAME_HOLD 20
#define STAR_VIEW_NAME_MIN_CELLS 2

typedef struct StarView {
    MenuScene base;       /* 0x0000 */
    PanelSprite button;   /* 0x0094: the closing button */
    Glider pointer;       /* 0x0110: the pointing hand */
    StarPalette twinkle;  /* 0x0174 */
    StarScope scope;      /* 0x04a4 */
    TextLabel name_label; /* 0x2cdc: the constellation's name */
    s32 cursor_x;         /* 0x2d48: the free pointer's place */
    s32 cursor_y;         /* 0x2d4c */
    s32 wipe_y;           /* 0x2d50: MenuScene_WipeOffsetY's */
    s32 fine_x;           /* 0x2d54: the view's scroll within a 16-pixel step */
    s32 fine_y;           /* 0x2d58 */
    s32 pointed;          /* 0x2d5c: the constellation last found under the middle */
    s32 wanted;           /* 0x2d60: the constellation the panel is to name */
    s32 named;            /* 0x2d64: the constellation `name_label` holds */
    u16 flags;            /* 0x2d68: StarViewFlag */
    u8 return_sub_state;  /* 0x2d6a: where a glide or a release goes back to */
    u8 arrow;             /* 0x2d6b: the arrow held, STAR_SCOPE_ARROWS for none */
    u8 pointer_spot;      /* 0x2d6c: the arrow the pointer rests by (always 1) */
    u8 name_slide;        /* 0x2d6d: 0-3 */
    u8 name_state;        /* 0x2d6e: StarViewNameState */
    u8 name_timer;        /* 0x2d6f */
    u8 name_cells;        /* 0x2d70: the name's width in 8-pixel cells, from 2 */
    u8 pad_2d71[3];
} StarView;

/* star_view.c: the scene */
StarView *StarView_Destroy(StarView *self);
StarView *StarView_Delete(StarView *self);
void StarView_ClearFlags(StarView *self, unsigned short mask);
void StarView_SetFlags(StarView *self, unsigned short mask);
int StarView_TestFlags(StarView *self, unsigned short mask);
void StarView_LoadGraphics(StarView *self);
void StarView_SetUpLayers(void);
void StarView_EndFrame(StarView *self);
void StarView_BeginFrame(StarView *self);
void StarView_EndInteractive(StarView *self);
void StarView_BeginInteractive(StarView *self);
void StarView_Teardown(StarView *self);
void StarView_ResetName(StarView *self);
void StarView_Setup(StarView *self);
void StarView_SetWipeWindow(StarView *self);
void StarView_FollowWipe(StarView *self);
void StarView_StateWipeOut(StarView *self);
void StarView_StateStartWipeOut(StarView *self);
void StarView_StateWipeIn(StarView *self);
void StarView_StateOpen(StarView *self);
int StarView_RequestDelete(StarView *self);
int StarView_Phase4(void);
int StarView_Phase3(void);
int StarView_RunInteractive(StarView *self);
void StarView_RunSubState(StarView *self);
int StarView_RunState(StarView *self);
int StarView_Draw(StarView *self);
int StarView_End(StarView *self);
int StarView_Start(StarView *self);
StarView *StarView_New(void);

/* star_view_input.c: the name panel, the pointer and the sub states */
void StarView_StepName(StarView *self);
void StarView_FollowPointed(StarView *self);
void StarView_HideName(StarView *self);
void StarView_ChangeName(StarView *self);
void StarView_ApplyName(StarView *self);
void StarView_DrawName(StarView *self);
void StarView_FindPointed(StarView *self);
int StarView_HeldArrow(StarView *self);
void StarView_UpdateView(StarView *self);
void StarView_DrawGrid(StarView *self, int y);
void StarView_ReleasePointer(StarView *self);
void StarView_PressPointer(StarView *self);
void StarView_ShowPointer(StarView *self);
void StarView_GlideTo(StarView *self, int x, int y);
void StarView_GlideToCursor(StarView *self);
void StarView_HidePointer(StarView *self);
int StarView_CursorY(StarView *self);
int StarView_CursorX(StarView *self);
void StarView_PlacePointer(StarView *self);
void StarView_Close(StarView *self);
void StarView_EnterInput(StarView *self);
void StarView_EnterKeys(StarView *self);
void StarView_EnterTouch(StarView *self);
void StarView_SubButton(StarView *self);
void StarView_SubRelease(StarView *self);
void StarView_SubPress(StarView *self);
void StarView_SubGlide(StarView *self);
void StarView_SubKeyNudge(StarView *self);
void StarView_SubKeyHold(StarView *self);
void StarView_SubKeys(StarView *self);
void StarView_SubFree(StarView *self);
void StarView_SubPenNudge(StarView *self);
void StarView_SubPenHold(StarView *self);
void StarView_SubTouch(StarView *self);

#endif
