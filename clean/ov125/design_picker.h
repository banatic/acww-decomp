/* The scene of overlay 125 (vtable 0x022a0ab8, include/cpp/ov125/Obj_ov125_022a0ab8.h;
 * constructor DesignPicker_New, 0x880 bytes): a menu scene (ov002/menu_scene.h) that shows the
 * current player's eight designs and lets one be picked, as the evidence says:
 *
 * - overlay 92's dispatcher opens it with overlay 124 as overlay group 0x0e for GroupParams'
 *   modes 4-10 (ov092/menu_dispatch.c); the mode chooses the confirm row's text
 *   (DesignPicker_FillEntries) and, in overlay 124, the title's;
 * - its setup loads the characters and palettes of the player's designs, in their order
 *   (PlayerDesigns_InOrder), into the OBJ characters 0xc0-0x13f and OBJ palettes 5-12
 *   (DesignPicker_LoadDesigns), and draws each design as a 32 x 32 OBJ (DesignPicker_Draw);
 * - the popup shows the title of the design under the cursor (DesignPicker_SetPopupText);
 * - the design picked is handed back through GroupParams_SetArg (DesignPicker_RunAction).
 *
 * The eight designs sit in two rows of four (places 0-3 and 4-7, DesignPicker_DesignX and
 * DesignPicker_DesignY); place 8 is the panel's button 9, which quits. Picking a design opens a
 * choice (ov002/paged_choice.h) of two rows: confirm (value 0) and the other row (value 1). The
 * object at 0x94 is overlay 124's (its functions are called by symbol). */
#ifndef CLEAN_OV125_DESIGN_PICKER_H
#define CLEAN_OV125_DESIGN_PICKER_H

#include "ov002/button_panel.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov002/paged_choice.h"
#include "ov002/popup.h"
#include "ov124/han_panel.h"
#include "types.h"

#define DESIGN_PICKER_DESIGNS 8

/* The places of the cursor (`cursor`). */
enum DesignPickerPlace {
    DESIGN_PICKER_TOP_FIRST = 0, /* 0-3: the top row of designs */
    DESIGN_PICKER_TOP_LAST = 3,
    DESIGN_PICKER_BOTTOM_FIRST = 4, /* 4-7: the bottom row */
    DESIGN_PICKER_BOTTOM_LAST = 7,
    DESIGN_PICKER_QUIT = 8,    /* the panel's button 9 */
    DESIGN_PICKER_NO_PLACE = 9 /* `popup_design` and `picked` before any */
};

/* In `flags`. */
enum DesignPickerFlag {
    DESIGN_PICKER_FLAG_DRAWN = 0x01,         /* the scene is drawn (DesignPicker_Draw) */
    DESIGN_PICKER_FLAG_JUMP = 0x02,          /* the cursor sprite jumps to the cursor instead of easing,
                                              * once (DesignPicker_GlideToCursor); never set here */
    DESIGN_PICKER_FLAG_WRAPPED_LEFT = 0x04,  /* this move wrapped the cursor from a row's first design to
                                              * its last: the sprite eases on to the left */
    DESIGN_PICKER_FLAG_WRAPPED_RIGHT = 0x08, /* ... from a row's last design to its first */
    DESIGN_PICKER_FLAG_QUIT = 0x10           /* the scene was quit (DesignPicker_Quit) */
};

#define DESIGN_PICKER_FLAGS_WRAPPED (DESIGN_PICKER_FLAG_WRAPPED_LEFT | DESIGN_PICKER_FLAG_WRAPPED_RIGHT)

/* The values of the choice rows (`action`, DesignPicker_RunAction). */
enum DesignPickerAction {
    DESIGN_PICKER_ACTION_CONFIRM = 0, /* the design is picked and the scene closes */
    DESIGN_PICKER_ACTION_BACK = 1     /* back to the designs */
};

/* The states, run from the table of DesignPicker_RunState (MenuScene_SetState). */
enum DesignPickerState {
    DESIGN_PICKER_STATE_START_SETUP = 0,    /* DesignPicker_StartSetup */
    DESIGN_PICKER_STATE_START_WIPE_IN = 1,  /* DesignPicker_StartWipeIn */
    DESIGN_PICKER_STATE_WIPE_IN = 2,        /* DesignPicker_WipeIn */
    DESIGN_PICKER_STATE_START_WIPE_OUT = 3, /* DesignPicker_StartWipeOut */
    DESIGN_PICKER_STATE_WIPE_OUT = 4,       /* DesignPicker_WipeOut */
    DESIGN_PICKER_STATES = 5
};

/* The sub states, run from the table of DesignPicker_RunSubState (MenuScene_SetSubState). */
enum DesignPickerSubState {
    DESIGN_PICKER_SUB_TOUCH_BROWSE = 0,   /* DesignPicker_BrowseByTouch */
    DESIGN_PICKER_SUB_TOUCH_CHOICE = 1,   /* DesignPicker_ChooseByTouch */
    DESIGN_PICKER_SUB_BROWSE = 2,         /* DesignPicker_BrowseByKeys */
    DESIGN_PICKER_SUB_CHOICE = 3,         /* DesignPicker_ChooseByKeys */
    DESIGN_PICKER_SUB_CHOICE_PICK = 4,    /* DesignPicker_PickChoiceRow */
    DESIGN_PICKER_SUB_SPRITE_MOVE = 5,    /* DesignPicker_WaitCursorSprite */
    DESIGN_PICKER_SUB_QUIT_PRESS = 6,     /* DesignPicker_WaitQuitSprite */
    DESIGN_PICKER_SUB_CHOICE_OPEN = 7,    /* DesignPicker_WaitChoiceShown */
    DESIGN_PICKER_SUB_CHOICE_CLOSE = 8,   /* DesignPicker_CloseChoice */
    DESIGN_PICKER_SUB_CHOICE_RUN = 9,     /* DesignPicker_RunActionWhenIdle */
    DESIGN_PICKER_SUB_PANEL_PRESSED = 10, /* DesignPicker_FollowQuitPress */
    DESIGN_PICKER_SUB_STATES = 11
};

typedef struct DesignPicker {
    MenuScene base;        /* 0x000 */
    HanPanel title;        /* 0x094: overlay 124's panel (ov124/han_panel.h) */
    u8 choice[0x3e8];      /* 0x180: a PagedChoice */
    ChoiceEntries entries; /* 0x568 */
    u8 pad_573;            /* 0x573 */
    Popup popup;           /* 0x574: the title of the design under the cursor */
    Glider cursor_sprite;  /* 0x644: a Glider0 */
    ButtonPanel panel;     /* 0x6a8 */
    s32 wipe_y;            /* 0x874: MenuScene_WipeOffsetY's, the designs and the title drawn there */
    u16 flags;             /* 0x878: DesignPickerFlag */
    u8 popup_design;       /* 0x87a: the design whose title the popup shows */
    u8 picked;             /* 0x87b: the design whose choice is open, then handed back */
    u8 cursor;             /* 0x87c: DesignPickerPlace */
    u8 action;             /* 0x87d: DesignPickerAction */
    u8 choice_row;         /* 0x87e: the choice row the cursor sprite points at */
    u8 return_sub_state;   /* 0x87f: the sub state to go back to once the sprite stops */
} DesignPicker;

DesignPicker *DesignPicker_Destroy(DesignPicker *self);
DesignPicker *DesignPicker_Delete(DesignPicker *self);
void DesignPicker_ClearFlags(DesignPicker *self, u16 flags);
void DesignPicker_SetFlags(DesignPicker *self, u16 flags);
int DesignPicker_TestFlags(DesignPicker *self, u16 flags);
int DesignPicker_MoveCursor(DesignPicker *self, int keys);
u8 DesignPicker_RowDown(DesignPicker *self, u8 first, u8 last, u8 to);
int DesignPicker_RowUp(DesignPicker *self, u8 first, u8 last, u8 to);
int DesignPicker_StepLeft(DesignPicker *self, unsigned int first, unsigned int last);
int DesignPicker_StepRight(DesignPicker *self, u32 first, u32 last);
void DesignPicker_ShowCursorSprite(DesignPicker *self);
void DesignPicker_PointAtFirstRow(DesignPicker *self);
void DesignPicker_PlaceSpriteAtCursor(DesignPicker *self);
void DesignPicker_CancelChoice(DesignPicker *self);
void DesignPicker_GlideToRow(DesignPicker *self);
void DesignPicker_GlideToCursor(DesignPicker *self);
void DesignPicker_HideCursorSprite(DesignPicker *self);
int DesignPicker_CursorSpriteY(DesignPicker *self);
int DesignPicker_CursorSpriteX(DesignPicker *self);
void DesignPicker_ShowCursorAtCursor(DesignPicker *self);
void DesignPicker_RunAction(DesignPicker *self);
void DesignPicker_ShowChoice(DesignPicker *self);
u8 DesignPicker_EntryValue(DesignPicker *self, int row);
void DesignPicker_FillEntries(DesignPicker *self);
void DesignPicker_QueuePopup(DesignPicker *self);
void DesignPicker_SetPopupText(DesignPicker *self);
int DesignPicker_TouchedPlace(DesignPicker *self);
int DesignPicker_DesignY(DesignPicker *self, int place);
u8 DesignPicker_DesignX(DesignPicker *self, int place);
void DesignPicker_Quit(DesignPicker *self);
void DesignPicker_Resume(DesignPicker *self);
void DesignPicker_ResumeByKeys(DesignPicker *self);
void DesignPicker_ResumeByTouch(DesignPicker *self);
void DesignPicker_FollowQuitPress(DesignPicker *self);
void DesignPicker_RunActionWhenIdle(DesignPicker *self);
void DesignPicker_CloseChoice(DesignPicker *self);
void DesignPicker_WaitChoiceShown(DesignPicker *self);
void DesignPicker_WaitQuitSprite(DesignPicker *self);
void DesignPicker_WaitCursorSprite(DesignPicker *self);
void DesignPicker_PickChoiceRow(DesignPicker *self);
void DesignPicker_ChooseByKeys(DesignPicker *self);
void DesignPicker_BrowseByKeys(DesignPicker *self);
void DesignPicker_ChooseByTouch(DesignPicker *self);
void DesignPicker_BrowseByTouch(DesignPicker *self);
void DesignPicker_LoadGraphics(DesignPicker *self);
void DesignPicker_LoadDesigns(void);
void DesignPicker_OpenTitle(DesignPicker *self);
void DesignPicker_SetUpLayers(void);
void DesignPicker_EndFrame(DesignPicker *self);
void DesignPicker_BeginFrame(DesignPicker *self);
void DesignPicker_EndInteractiveFrame(DesignPicker *self);
void DesignPicker_BeginInteractiveFrame(DesignPicker *self);
void DesignPicker_Teardown(DesignPicker *self);
void DesignPicker_Setup(DesignPicker *self);
int DesignPicker_ScrollWithWipe(DesignPicker *self);
void DesignPicker_WipeOut(DesignPicker *self);
void DesignPicker_StartWipeOut(DesignPicker *self);
int DesignPicker_WipeIn(DesignPicker *self);
void DesignPicker_StartWipeIn(DesignPicker *self);
void DesignPicker_StartSetup(DesignPicker *self);
int DesignPicker_End(DesignPicker *self);
int DesignPicker_Phase4Idle(void);
int DesignPicker_Phase3Idle(void);
int DesignPicker_RunInteractive(DesignPicker *self);
void DesignPicker_RunSubState(DesignPicker *self);
int DesignPicker_RunState(DesignPicker *self);
int DesignPicker_Draw(DesignPicker *self);
int DesignPicker_Close(DesignPicker *self);
int DesignPicker_Start(DesignPicker *self);
DesignPicker *DesignPicker_New(void);

#endif
