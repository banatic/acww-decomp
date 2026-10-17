/* The scene of overlay 136 (vtable 0x0229d510; constructor TimeScreen_New, 0x2b78 bytes): a menu
 * scene (ov002/menu_scene.h) where the player enters a time, as the evidence says:
 *
 * - overlay 92's dispatcher opens it with overlay 134 as overlay group 0x1d for GroupParams'
 *   mode 0x31 (ov092/menu_dispatch.c);
 * - it sets up overlay 134's entry picker (ov136/entry_picker.h) for a time (kind 1), whose
 *   fields 3 and 4 are the hour and the minute, with a clock whose hands the pen can drag;
 * - confirmed, the time entered is kept as main's date and time (Global021cfc98_CopyIn), which
 *   a villager's talk reads back (VillagerTalkSteps_LineKeptTime), and main is told
 *   (GroupParams_SetC4C(1)).
 *
 * The cursor sprite points at one of three places: the hour, the minute (picker fields 3 and 4)
 * or the panel's OK button (button 6). A on a field opens its list in the picker; the list is
 * then driven by the keys or the pen until it closes. A on OK, or START, confirms. */
#ifndef CLEAN_OV136_TIME_SCREEN_H
#define CLEAN_OV136_TIME_SCREEN_H

#include "ov002/button_panel.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "types.h"

/* The places of the cursor (`place`). */
enum TimeScreenPlace {
    TIME_SCREEN_PLACE_HOUR = 0,
    TIME_SCREEN_PLACE_MINUTE = 1,
    TIME_SCREEN_PLACE_OK = 2, /* the panel's button 6 */
    TIME_SCREEN_PLACES = 3
};

/* The picker's field of a place other than OK is the place plus this. */
#define TIME_SCREEN_FIELD_OF_PLACE 3

/* In `flags`. */
enum TimeScreenFlag {
    TIME_SCREEN_FLAG_DRAWN = 0x01,   /* the scene is drawn (TimeScreen_Draw) */
    TIME_SCREEN_FLAG_IN_LIST = 0x02, /* a field's list is open: the cursor sprite follows its cursor */
    TIME_SCREEN_FLAG_QUICK = 0x04    /* the next glide of the cursor sprite is a quick one (two steps) */
};

/* The states, run from the table of TimeScreen_RunState (MenuScene_SetState). */
enum TimeScreenState {
    TIME_SCREEN_STATE_START_WIPE_IN = 0,  /* TimeScreen_StartWipeIn */
    TIME_SCREEN_STATE_WIPE_IN = 1,        /* TimeScreen_WipeIn */
    TIME_SCREEN_STATE_START_WIPE_OUT = 2, /* TimeScreen_StartWipeOut */
    TIME_SCREEN_STATE_WIPE_OUT = 3,       /* TimeScreen_WipeOut */
    TIME_SCREEN_STATES = 4
};

/* The sub states, run from the table of TimeScreen_RunSubState (MenuScene_SetSubState). */
enum TimeScreenSubState {
    TIME_SCREEN_SUB_TOUCH_FIELDS = 0, /* TimeScreen_FieldsByTouch */
    TIME_SCREEN_SUB_DRAG_HANDS = 1,   /* TimeScreen_DragHands */
    TIME_SCREEN_SUB_SETTLE_HANDS = 2, /* TimeScreen_SettleHands */
    TIME_SCREEN_SUB_TOUCH_LIST = 3,   /* TimeScreen_ListByTouch */
    TIME_SCREEN_SUB_DRAG_BAR = 4,     /* TimeScreen_DragListBar */
    TIME_SCREEN_SUB_DRAG_COLUMN = 5,  /* TimeScreen_DragListColumn */
    TIME_SCREEN_SUB_FIELDS = 6,       /* TimeScreen_FieldsByKeys */
    TIME_SCREEN_SUB_LIST = 7,         /* TimeScreen_ListByKeys */
    TIME_SCREEN_SUB_BAR = 8,          /* TimeScreen_ListBarByKeys */
    TIME_SCREEN_SUB_BAR_RETURN = 9,   /* TimeScreen_ReturnFromBar */
    TIME_SCREEN_SUB_SPRITE_MOVE = 10, /* TimeScreen_WaitCursorSprite */
    TIME_SCREEN_SUB_PRESSED = 11,     /* TimeScreen_AfterPress */
    TIME_SCREEN_SUB_SPRITE_ANIM = 12, /* TimeScreen_WaitSpriteAnim */
    TIME_SCREEN_SUB_OK_PRESSED = 13,  /* TimeScreen_FollowOkPress */
    TIME_SCREEN_SUB_LIST_OPEN = 14,   /* TimeScreen_WaitListOpen */
    TIME_SCREEN_SUB_LIST_CLOSE = 15,  /* TimeScreen_WaitListClosed */
    TIME_SCREEN_SUB_STATES = 16
};

typedef struct TimeScreen {
    MenuScene base;       /* 0x0000 */
    Glider cursor_sprite; /* 0x0094: a Glider0 */
    ButtonPanel panel;    /* 0x00f8 */
    u8 picker[0x28b0];    /* 0x02c4: overlay 134's entry picker (ov136/entry_picker.h) */
    u16 flags;            /* 0x2b74: TimeScreenFlag */
    u8 return_sub_state;  /* 0x2b76: the sub state to go back to once the sprite is done */
    u8 place;             /* 0x2b77: TimeScreenPlace */
} TimeScreen;

TimeScreen *TimeScreen_Destroy(TimeScreen *self);
TimeScreen *TimeScreen_Delete(TimeScreen *self);
void TimeScreen_ClearFlags(TimeScreen *self, u16 flags);
void TimeScreen_SetFlags(TimeScreen *self, u16 flags);
int TimeScreen_TestFlags(TimeScreen *self, int flags);
int TimeScreen_MoveCursor(TimeScreen *self, int keys);
void TimeScreen_PlayReleaseAnim(TimeScreen *self);
void TimeScreen_PressSprite(TimeScreen *self);
void TimeScreen_ShowCursorSprite(TimeScreen *self);
void TimeScreen_GlideSpriteTo(TimeScreen *self, int x, int y);
void TimeScreen_GlideToCursor(TimeScreen *self);
void TimeScreen_HideCursorSprite(TimeScreen *self);
int TimeScreen_CursorY(TimeScreen *self);
int TimeScreen_CursorX(TimeScreen *self);
void TimeScreen_ShowSpriteAtCursor(TimeScreen *self);
void TimeScreen_ResumeList(TimeScreen *self);
void TimeScreen_ResumeListByKeys(TimeScreen *self);
void TimeScreen_ResumeListByTouch(TimeScreen *self);
void TimeScreen_CancelList(TimeScreen *self);
void TimeScreen_PickInList(TimeScreen *self);
void TimeScreen_OpenList(TimeScreen *self, int field);
void TimeScreen_Confirm(TimeScreen *self);
void TimeScreen_ResumeFields(TimeScreen *self);
void TimeScreen_ResumeFieldsByKeys(TimeScreen *self);
void TimeScreen_ResumeFieldsByTouch(TimeScreen *self);
void TimeScreen_WaitListClosed(TimeScreen *self);
void TimeScreen_WaitListOpen(TimeScreen *self);
void TimeScreen_FollowOkPress(TimeScreen *self);
void TimeScreen_WaitSpriteAnim(TimeScreen *self);
void TimeScreen_AfterPress(TimeScreen *self);
void TimeScreen_WaitCursorSprite(TimeScreen *self);
void TimeScreen_ReturnFromBar(TimeScreen *self);
void TimeScreen_ListBarByKeys(TimeScreen *self);
void TimeScreen_ListByKeys(TimeScreen *self);
void TimeScreen_FieldsByKeys(TimeScreen *self);
void TimeScreen_DragListColumn(TimeScreen *self);
void TimeScreen_DragListBar(TimeScreen *self);
void TimeScreen_ListByTouch(TimeScreen *self);
void TimeScreen_SettleHands(TimeScreen *self);
void TimeScreen_DragHands(TimeScreen *self);
void TimeScreen_FieldsByTouch(TimeScreen *self);
void TimeScreen_LoadGraphics(TimeScreen *self);
void TimeScreen_LoadTexts(TimeScreen *self);
void TimeScreen_SetUpLayers(void);
void TimeScreen_EndFrame(TimeScreen *self);
void TimeScreen_BeginFrame(TimeScreen *self);
void TimeScreen_EndInteractiveFrame(TimeScreen *self);
void TimeScreen_BeginInteractiveFrame(TimeScreen *self);
void TimeScreen_Teardown(TimeScreen *self);
void TimeScreen_Setup(TimeScreen *self);
void TimeScreen_ScrollWithWipe(TimeScreen *self);
void TimeScreen_WipeOut(TimeScreen *self);
void TimeScreen_StartWipeOut(TimeScreen *self);
void TimeScreen_WipeIn(TimeScreen *self);
void TimeScreen_StartWipeIn(TimeScreen *self);
int TimeScreen_End(TimeScreen *self);
int TimeScreen_Phase4Idle(void);
int TimeScreen_Phase3Idle(void);
int TimeScreen_RunInteractive(TimeScreen *self);
void TimeScreen_RunSubState(TimeScreen *self);
int TimeScreen_RunState(TimeScreen *self);
int TimeScreen_Draw(TimeScreen *self);
int TimeScreen_Close(TimeScreen *self);
int TimeScreen_Start(TimeScreen *self);
TimeScreen *TimeScreen_New(void);

#endif
