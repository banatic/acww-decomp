/* The scene of overlay 138 (vtable 0x0229d4e0, include/cpp/ov138/Obj_ov138_0229d4e0.h;
 * constructor DateScreen_New, 0x2b78 bytes): a menu scene (ov002/menu_scene.h) where a date is
 * set, as the evidence says:
 *
 * - overlay 92's dispatcher opens it with overlay 134 as overlay group 0x2a for GroupParams'
 *   mode 0x33 (ov092/menu_dispatch.c), the last of the four clock screens (modes 0x30-0x33,
 *   overlays 135-138);
 * - it embeds overlay 134's clock setter at 0x2c8 (ov134/clock_setter.h), set up in its
 *   mode 3 (the date, bounded below by the panel's minimum): the year, the month and the day
 *   are its fields 0-2, and touching or picking one opens the list of its values;
 * - the panel's buttons 6 and 7 (ov002/button_panel.h, layout 6) confirm and cancel: confirming
 *   copies the panel's date into main's date and time (Global021cfc98_CopyIn) and tells main a
 *   date was set (GroupParams_SetC4C(1)); cancelling tells it none was (0).
 *
 * The cursor (`cursor`, DateScreenPlace) is a Glider0 sprite that points at a field, at a
 * button, or, while a field's list is open (DATE_SCREEN_FLAG_LIST), at the list's cursor row.
 */
#ifndef CLEAN_OV138_DATE_SCREEN_H
#define CLEAN_OV138_DATE_SCREEN_H

#include "ov002/button_panel.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov134/clock_setter.h"
#include "types.h"

/* The places of the cursor (`cursor`). */
enum DateScreenPlace {
    DATE_SCREEN_YEAR = 0, /* 0-2: the clock setter's fields, in a row */
    DATE_SCREEN_MONTH = 1,
    DATE_SCREEN_DAY = 2,
    DATE_SCREEN_CONFIRM = 3, /* the panel's button 6 */
    DATE_SCREEN_CANCEL = 4,  /* the panel's button 7 */
    DATE_SCREEN_PLACES = 5
};

/* In `flags` (the base's bytes 0x92-0x93). */
enum DateScreenFlag {
    DATE_SCREEN_FLAG_DRAWN = 0x01, /* the scene is drawn (DateScreen_Draw) */
    DATE_SCREEN_FLAG_LIST = 0x02,  /* a field's list is open and the keys move in it */
    DATE_SCREEN_FLAG_QUICK = 0x04  /* the next glide of the cursor takes two steps, not three */
};

/* The states, run from the table of DateScreen_RunState (MenuScene_SetState). */
enum DateScreenState {
    DATE_SCREEN_STATE_START_SETUP = 0,    /* DateScreen_StartSetup */
    DATE_SCREEN_STATE_WIPE_IN = 1,        /* DateScreen_WipeIn */
    DATE_SCREEN_STATE_START_WIPE_OUT = 2, /* DateScreen_StartWipeOut */
    DATE_SCREEN_STATE_WIPE_OUT = 3,       /* DateScreen_WipeOut */
    DATE_SCREEN_STATES = 4
};

/* The sub states, run from the table of DateScreen_RunSubState (MenuScene_SetSubState). */
enum DateScreenSubState {
    DATE_SCREEN_SUB_TOUCH_BROWSE = 0,   /* DateScreen_BrowseByTouch */
    DATE_SCREEN_SUB_TOUCH_LIST = 1,     /* DateScreen_ListByTouch */
    DATE_SCREEN_SUB_DRAG_THUMB = 2,     /* DateScreen_DragThumb */
    DATE_SCREEN_SUB_THUMB_TO_PEN = 3,   /* DateScreen_ThumbTowardPen */
    DATE_SCREEN_SUB_BROWSE = 4,         /* DateScreen_BrowseByKeys */
    DATE_SCREEN_SUB_LIST = 5,           /* DateScreen_ListByKeys */
    DATE_SCREEN_SUB_THUMB_KEYS = 6,     /* DateScreen_MoveThumbByKeys */
    DATE_SCREEN_SUB_THUMB_SETTLE = 7,   /* DateScreen_SettleThumb */
    DATE_SCREEN_SUB_SPRITE_MOVE = 8,    /* DateScreen_WaitCursorSprite */
    DATE_SCREEN_SUB_PRESS_ACT = 9,      /* DateScreen_ActOnPress */
    DATE_SCREEN_SUB_PRESS_RELEASE = 10, /* DateScreen_WaitPressRelease */
    DATE_SCREEN_SUB_PANEL_PRESSED = 11, /* DateScreen_FollowPanelPress */
    DATE_SCREEN_SUB_LIST_OPENING = 12,  /* DateScreen_WaitListOpen */
    DATE_SCREEN_SUB_LIST_CLOSING = 13,  /* DateScreen_WaitListClose */
    DATE_SCREEN_SUB_STATES = 14
};

typedef struct DateScreen {
    MenuScene base;       /* 0x000: its bytes 0x92-0x93 are `flags` (DateScreen_Flags) */
    u8 return_sub_state;  /* 0x094: the sub state to go back to once the sprite stops */
    u8 cursor;            /* 0x095: DateScreenPlace */
    u8 pad_96[2];         /* 0x096 */
    Glider cursor_sprite; /* 0x098: a Glider0 */
    ButtonPanel panel;    /* 0x0fc */
    ClockSetter clock;    /* 0x2c8: overlay 134's clock setter */
} DateScreen;

DateScreen *DateScreen_Destroy(DateScreen *self);
DateScreen *DateScreen_Delete(DateScreen *self);
void DateScreen_ClearFlags(DateScreen *self, u16 flags);
void DateScreen_SetFlags(DateScreen *self, u16 flags);
int DateScreen_TestFlags(DateScreen *self, u16 flags);
int DateScreen_MoveCursor(DateScreen *self, int keys);
void DateScreen_PressAndReturn(DateScreen *self);
void DateScreen_PressToAct(DateScreen *self);
void DateScreen_ShowCursorSprite(DateScreen *self);
void DateScreen_GlideTo(DateScreen *self, int x, int y);
void DateScreen_GlideToCursor(DateScreen *self);
int DateScreen_HideCursorSprite(DateScreen *self);
int DateScreen_CursorSpriteY(DateScreen *self);
int DateScreen_CursorSpriteX(DateScreen *self);
void DateScreen_PlaceSpriteAtCursor(DateScreen *self);
void DateScreen_EnterList(DateScreen *self);
void DateScreen_EnterListByKeys(DateScreen *self);
void DateScreen_EnterListByTouch(DateScreen *self);
void DateScreen_CancelList(DateScreen *self);
void DateScreen_PickListRow(DateScreen *self);
void DateScreen_OpenList(DateScreen *self, int field);
void DateScreen_Cancel(DateScreen *self);
void DateScreen_Confirm(DateScreen *self);
int DateScreen_Resume(DateScreen *self);
u8 *DateScreen_ResumeByKeys(DateScreen *self);
int DateScreen_ResumeByTouch(DateScreen *self);
void DateScreen_WaitListClose(DateScreen *self);
void DateScreen_WaitListOpen(DateScreen *self);
void DateScreen_FollowPanelPress(DateScreen *self);
void DateScreen_WaitPressRelease(DateScreen *self);
void DateScreen_ActOnPress(DateScreen *self);
void DateScreen_WaitCursorSprite(DateScreen *self);
void DateScreen_SettleThumb(DateScreen *self);
void DateScreen_MoveThumbByKeys(DateScreen *self);
void DateScreen_ListByKeys(DateScreen *self);
void DateScreen_BrowseByKeys(DateScreen *self);
void DateScreen_ThumbTowardPen(DateScreen *self);
void DateScreen_DragThumb(DateScreen *self);
void DateScreen_ListByTouch(DateScreen *self);
void DateScreen_BrowseByTouch(DateScreen *self);
void DateScreen_LoadSprites(DateScreen *self);
void DateScreen_LoadBackground(DateScreen *self);
void DateScreen_SetUpLayers(void);
void DateScreen_EndFrame(DateScreen *self);
void DateScreen_BeginFrame(DateScreen *self);
void DateScreen_EndInteractiveFrame(DateScreen *self);
int DateScreen_BeginInteractiveFrame(DateScreen *self);
void DateScreen_Teardown(DateScreen *self);
void DateScreen_Setup(DateScreen *self);
void DateScreen_ScrollWithWipe(DateScreen *self);
void DateScreen_WipeOut(DateScreen *self);
void DateScreen_StartWipeOut(DateScreen *self);
void DateScreen_WipeIn(DateScreen *self);
void DateScreen_StartSetup(DateScreen *self);
int DateScreen_End(DateScreen *self);
int DateScreen_Phase4Idle(void);
int DateScreen_Phase3Idle(void);
int DateScreen_RunInteractive(DateScreen *self);
void DateScreen_RunSubState(DateScreen *self);
int DateScreen_RunState(DateScreen *self);
int DateScreen_Draw(DateScreen *self);
int DateScreen_Close(DateScreen *self);
int DateScreen_Start(DateScreen *self, int unused);
DateScreen *DateScreen_New(void);

#endif
