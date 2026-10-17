/* The scene of overlay 137 (vtable 0x0229d440; constructor BirthdayScreen_New, 0x2b78 bytes): a
 * menu scene (ov002/menu_scene.h) where the player enters a birthday, as the evidence says:
 *
 * - overlay 92's dispatcher opens it with overlay 134 as overlay group 0x1e for GroupParams'
 *   mode 0x32 (ov092/menu_dispatch.c);
 * - it sets up overlay 134's entry picker (ov136/entry_picker.h) for a month and day (kind 2),
 *   whose fields 1 and 2 are the month and the day;
 * - confirmed, the month and day entered become the current player's birthday
 *   (PlayerRecord_SetBirthday).
 *
 * It is overlay 136's time screen (ov136/time_screen.h) without the clock: the cursor sprite
 * points at the month, the day (picker fields 1 and 2) or the panel's OK button (button 6); A on
 * a field opens its list in the picker; A on OK, or START, confirms. */
#ifndef CLEAN_OV137_BIRTHDAY_SCREEN_H
#define CLEAN_OV137_BIRTHDAY_SCREEN_H

#include "ov002/button_panel.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "types.h"

/* The places of the cursor (`place`). */
enum BirthdayScreenPlace {
    BIRTHDAY_SCREEN_PLACE_MONTH = 0,
    BIRTHDAY_SCREEN_PLACE_DAY = 1,
    BIRTHDAY_SCREEN_PLACE_OK = 2, /* the panel's button 6 */
    BIRTHDAY_SCREEN_PLACES = 3
};

/* The picker's field of a place other than OK is the place plus this. */
#define BIRTHDAY_SCREEN_FIELD_OF_PLACE 1

/* In `flags`. */
enum BirthdayScreenFlag {
    BIRTHDAY_SCREEN_FLAG_DRAWN = 0x01,   /* the scene is drawn (BirthdayScreen_Draw) */
    BIRTHDAY_SCREEN_FLAG_IN_LIST = 0x02, /* a field's list is open: the cursor sprite follows its cursor */
    BIRTHDAY_SCREEN_FLAG_QUICK = 0x04    /* the next glide of the cursor sprite is a quick one (two steps) */
};

/* The states, run from the table of BirthdayScreen_RunState (MenuScene_SetState). */
enum BirthdayScreenState {
    BIRTHDAY_SCREEN_STATE_START_WIPE_IN = 0,  /* BirthdayScreen_StartWipeIn */
    BIRTHDAY_SCREEN_STATE_WIPE_IN = 1,        /* BirthdayScreen_WipeIn */
    BIRTHDAY_SCREEN_STATE_START_WIPE_OUT = 2, /* BirthdayScreen_StartWipeOut */
    BIRTHDAY_SCREEN_STATE_WIPE_OUT = 3,       /* BirthdayScreen_WipeOut */
    BIRTHDAY_SCREEN_STATES = 4
};

/* The sub states, run from the table of BirthdayScreen_RunSubState (MenuScene_SetSubState). */
enum BirthdayScreenSubState {
    BIRTHDAY_SCREEN_SUB_TOUCH_FIELDS = 0, /* BirthdayScreen_FieldsByTouch */
    BIRTHDAY_SCREEN_SUB_TOUCH_LIST = 1,   /* BirthdayScreen_ListByTouch */
    BIRTHDAY_SCREEN_SUB_DRAG_BAR = 2,     /* BirthdayScreen_DragListBar */
    BIRTHDAY_SCREEN_SUB_DRAG_COLUMN = 3,  /* BirthdayScreen_DragListColumn */
    BIRTHDAY_SCREEN_SUB_FIELDS = 4,       /* BirthdayScreen_FieldsByKeys */
    BIRTHDAY_SCREEN_SUB_LIST = 5,         /* BirthdayScreen_ListByKeys */
    BIRTHDAY_SCREEN_SUB_BAR = 6,          /* BirthdayScreen_ListBarByKeys */
    BIRTHDAY_SCREEN_SUB_BAR_RETURN = 7,   /* BirthdayScreen_ReturnFromBar */
    BIRTHDAY_SCREEN_SUB_SPRITE_MOVE = 8,  /* BirthdayScreen_WaitCursorSprite */
    BIRTHDAY_SCREEN_SUB_PRESSED = 9,      /* BirthdayScreen_AfterPress */
    BIRTHDAY_SCREEN_SUB_SPRITE_ANIM = 10, /* BirthdayScreen_WaitSpriteAnim */
    BIRTHDAY_SCREEN_SUB_OK_PRESSED = 11,  /* BirthdayScreen_FollowOkPress */
    BIRTHDAY_SCREEN_SUB_LIST_OPEN = 12,   /* BirthdayScreen_WaitListOpen */
    BIRTHDAY_SCREEN_SUB_LIST_CLOSE = 13,  /* BirthdayScreen_WaitListClosed */
    BIRTHDAY_SCREEN_SUB_STATES = 14
};

typedef struct BirthdayScreen {
    MenuScene base;       /* 0x0000 */
    Glider cursor_sprite; /* 0x0094: a Glider0 */
    ButtonPanel panel;    /* 0x00f8 */
    u8 picker[0x28b0];    /* 0x02c4: overlay 134's entry picker (ov136/entry_picker.h) */
    u16 flags;            /* 0x2b74: BirthdayScreenFlag */
    u8 return_sub_state;  /* 0x2b76: the sub state to go back to once the sprite is done */
    u8 place;             /* 0x2b77: BirthdayScreenPlace */
} BirthdayScreen;

BirthdayScreen *BirthdayScreen_Destroy(BirthdayScreen *self);
BirthdayScreen *BirthdayScreen_Delete(BirthdayScreen *self);
void BirthdayScreen_ClearFlags(BirthdayScreen *self, u16 flags);
void BirthdayScreen_SetFlags(BirthdayScreen *self, u16 flags);
int BirthdayScreen_TestFlags(BirthdayScreen *self, u16 flags);
int BirthdayScreen_MoveCursor(BirthdayScreen *self, int keys);
void BirthdayScreen_PlayReleaseAnim(BirthdayScreen *self);
void BirthdayScreen_PressSprite(BirthdayScreen *self);
void BirthdayScreen_ShowCursorSprite(BirthdayScreen *self);
void BirthdayScreen_GlideSpriteTo(BirthdayScreen *self, int x, int y);
void BirthdayScreen_GlideToCursor(BirthdayScreen *self);
void BirthdayScreen_HideCursorSprite(BirthdayScreen *self);
int BirthdayScreen_CursorY(BirthdayScreen *self);
int BirthdayScreen_CursorX(BirthdayScreen *self);
void BirthdayScreen_ShowSpriteAtCursor(BirthdayScreen *self);
void BirthdayScreen_ResumeList(BirthdayScreen *self);
void BirthdayScreen_ResumeListByKeys(BirthdayScreen *self);
void BirthdayScreen_ResumeListByTouch(BirthdayScreen *self);
void BirthdayScreen_CancelList(BirthdayScreen *self);
void BirthdayScreen_PickInList(BirthdayScreen *self);
void BirthdayScreen_OpenList(BirthdayScreen *self, int field);
void BirthdayScreen_Confirm(BirthdayScreen *self);
void BirthdayScreen_ResumeFields(BirthdayScreen *self);
void BirthdayScreen_ResumeFieldsByKeys(BirthdayScreen *self);
void BirthdayScreen_ResumeFieldsByTouch(BirthdayScreen *self);
void BirthdayScreen_WaitListClosed(BirthdayScreen *self);
void BirthdayScreen_WaitListOpen(BirthdayScreen *self);
void BirthdayScreen_FollowOkPress(BirthdayScreen *self);
void BirthdayScreen_WaitSpriteAnim(BirthdayScreen *self);
void BirthdayScreen_AfterPress(BirthdayScreen *self);
void BirthdayScreen_WaitCursorSprite(BirthdayScreen *self);
void BirthdayScreen_ReturnFromBar(BirthdayScreen *self);
void BirthdayScreen_ListBarByKeys(BirthdayScreen *self);
void BirthdayScreen_ListByKeys(BirthdayScreen *self);
void BirthdayScreen_FieldsByKeys(BirthdayScreen *self);
void BirthdayScreen_DragListColumn(BirthdayScreen *self);
void BirthdayScreen_DragListBar(BirthdayScreen *self);
void BirthdayScreen_ListByTouch(BirthdayScreen *self);
void BirthdayScreen_FieldsByTouch(BirthdayScreen *self);
void BirthdayScreen_LoadGraphics(BirthdayScreen *self);
void BirthdayScreen_LoadTexts(BirthdayScreen *self);
void BirthdayScreen_SetUpLayers(void);
void BirthdayScreen_EndFrame(BirthdayScreen *self);
void BirthdayScreen_BeginFrame(BirthdayScreen *self);
void BirthdayScreen_EndInteractiveFrame(BirthdayScreen *self);
void BirthdayScreen_BeginInteractiveFrame(BirthdayScreen *self);
void BirthdayScreen_Teardown(BirthdayScreen *self);
void BirthdayScreen_Setup(BirthdayScreen *self);
void BirthdayScreen_ScrollWithWipe(BirthdayScreen *self);
void BirthdayScreen_WipeOut(BirthdayScreen *self);
void BirthdayScreen_StartWipeOut(BirthdayScreen *self);
void BirthdayScreen_WipeIn(BirthdayScreen *self);
void BirthdayScreen_StartWipeIn(BirthdayScreen *self);
int BirthdayScreen_End(BirthdayScreen *self);
int BirthdayScreen_Phase4Idle(void);
int BirthdayScreen_Phase3Idle(void);
int BirthdayScreen_RunInteractive(BirthdayScreen *self);
void BirthdayScreen_RunSubState(BirthdayScreen *self);
int BirthdayScreen_RunState(BirthdayScreen *self);
int BirthdayScreen_Draw(BirthdayScreen *self);
int BirthdayScreen_Close(BirthdayScreen *self);
int BirthdayScreen_Start(BirthdayScreen *self);
BirthdayScreen *BirthdayScreen_New(void);

#endif
