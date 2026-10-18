/* The scene of overlay 135 (vtable 0x0229d610, include/cpp/ov135/Obj_ov135_0229d610.h;
 * constructor PhoneClock_New, 0x2b78 bytes): the screen that sets the town's clock, as the
 * evidence says:
 *
 * - overlay 92's dispatcher opens it with overlay 134 (the clock screens' graphics, files
 *   "menu/clock/...") as overlay group 0x1c for GroupParams' mode 0x30, which the house's
 *   telephone asks for (ov004/rmo_telephone.c);
 * - the object at 0x2c8 is overlay 134's clock setter (ov134/clock_setter.h): it shows the
 *   clock's fields and edits the one picked;
 * - the panel's button 6 sets the clock (PhoneClock_SetClock: the date and time edited become
 *   the town's, as an offset from the RTC's in the state block, main/clock.h) and its button 7
 *   leaves it as it was (PhoneClock_Cancel); either way the menu closes.
 *
 * The cursor (`cursor`) is one of five fields (0-2 in a row, 3 and 4 in a row below them) or
 * one of the panel's two buttons (5 and 6); with a field picked (PHONE_CLOCK_FLAG_EDITING) the
 * cursor sprite follows overlay 134's own cursor instead. */
#ifndef CLEAN_OV135_PHONE_CLOCK_H
#define CLEAN_OV135_PHONE_CLOCK_H

#include "ov002/button_panel.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov134/clock_setter.h"
#include "types.h"

/* The places of the cursor (`cursor`). */
enum PhoneClockPlace {
    PHONE_CLOCK_FIELDS = 5, /* 0-4: the fields */
    PHONE_CLOCK_SET = 5,    /* the panel's button 6 */
    PHONE_CLOCK_CANCEL = 6, /* the panel's button 7 */
    PHONE_CLOCK_PLACES = 7
};

/* In `flags` (the base's bytes 0x92-0x93). */
enum PhoneClockFlag {
    PHONE_CLOCK_FLAG_DRAWN = 0x01,   /* the scene is drawn (PhoneClock_Draw) */
    PHONE_CLOCK_FLAG_EDITING = 0x02, /* a field is being edited by overlay 134's object */
    PHONE_CLOCK_FLAG_QUICK = 0x04    /* the cursor sprite's next glide takes two steps, not three */
};

/* The states, run from the table of PhoneClock_RunState (MenuScene_SetState). */
enum PhoneClockState {
    PHONE_CLOCK_STATE_START_WIPE_IN = 0,  /* PhoneClock_StartWipeIn */
    PHONE_CLOCK_STATE_WIPE_IN = 1,        /* PhoneClock_WipeIn */
    PHONE_CLOCK_STATE_START_WIPE_OUT = 2, /* PhoneClock_StartWipeOut */
    PHONE_CLOCK_STATE_WIPE_OUT = 3,       /* PhoneClock_WipeOut */
    PHONE_CLOCK_STATES = 4
};

/* The sub states, run from the table of PhoneClock_RunSubState (MenuScene_SetSubState). */
enum PhoneClockSubState {
    PHONE_CLOCK_SUB_TOUCH_BROWSE = 0,   /* PhoneClock_BrowseByTouch */
    PHONE_CLOCK_SUB_TOUCH_DRAG = 1,     /* PhoneClock_DragByTouch */
    PHONE_CLOCK_SUB_TOUCH_SETTLE = 2,   /* PhoneClock_WaitDragSettled */
    PHONE_CLOCK_SUB_TOUCH_EDIT = 3,     /* PhoneClock_EditByTouch */
    PHONE_CLOCK_SUB_DRAG_THUMB = 4,     /* PhoneClock_DragThumb */
    PHONE_CLOCK_SUB_THUMB_TO_PEN = 5,   /* PhoneClock_ThumbTowardPen */
    PHONE_CLOCK_SUB_BROWSE = 6,         /* PhoneClock_BrowseByKeys */
    PHONE_CLOCK_SUB_EDIT = 7,           /* PhoneClock_EditByKeys */
    PHONE_CLOCK_SUB_HOLD_A = 8,         /* PhoneClock_HoldButtonA */
    PHONE_CLOCK_SUB_EDIT_WAIT = 9,      /* PhoneClock_WaitEditor */
    PHONE_CLOCK_SUB_SPRITE_MOVE = 10,   /* PhoneClock_WaitCursorSprite */
    PHONE_CLOCK_SUB_PRESS = 11,         /* PhoneClock_PickWhenPressed */
    PHONE_CLOCK_SUB_SHOW_SPRITE = 12,   /* PhoneClock_ShowSpriteWhenDone */
    PHONE_CLOCK_SUB_PANEL_PRESSED = 13, /* PhoneClock_FollowPanelPress */
    PHONE_CLOCK_SUB_FIELD_OPEN = 14,    /* PhoneClock_WaitFieldOpen */
    PHONE_CLOCK_SUB_FIELD_CLOSE = 15,   /* PhoneClock_WaitFieldClosed */
    PHONE_CLOCK_SUB_STATES = 16
};

typedef struct PhoneClock {
    MenuScene base;       /* 0x000: its bytes 0x92-0x93 are the flags (PhoneClock_Flags) */
    u8 return_sub_state;  /* 0x094: the sub state to go back to once the sprite stops */
    u8 cursor;            /* 0x095: PhoneClockPlace */
    u8 pad_96[2];         /* 0x096 */
    Glider cursor_sprite; /* 0x098: a Glider0 */
    ButtonPanel panel;    /* 0x0fc */
    ClockSetter editor;   /* 0x2c8: overlay 134's clock setter */
} PhoneClock;

PhoneClock *PhoneClock_Destroy(PhoneClock *self);
PhoneClock *PhoneClock_Delete(PhoneClock *self);
void PhoneClock_ClearFlags(PhoneClock *self, u16 flags);
void PhoneClock_SetFlags(PhoneClock *self, u16 flags);
int PhoneClock_TestFlags(PhoneClock *self, unsigned int flags);
int PhoneClock_MoveCursor(PhoneClock *self, u32 keys);
void PhoneClock_ShowSpriteThird(PhoneClock *self);
void PhoneClock_PressCursorSprite(PhoneClock *self);
void PhoneClock_ShowCursorSprite(PhoneClock *self);
void PhoneClock_GlideTo(PhoneClock *self, int x, int y);
void PhoneClock_GlideToCursor(PhoneClock *self);
void PhoneClock_HideCursorSprite(PhoneClock *self);
int PhoneClock_CursorY(PhoneClock *self);
int PhoneClock_CursorX(PhoneClock *self);
void PhoneClock_ShowCursorAtCursor(PhoneClock *self);
void PhoneClock_ResumeEditing(PhoneClock *self);
void PhoneClock_ResumeEditingByKeys(PhoneClock *self);
void PhoneClock_ResumeEditingByTouch(PhoneClock *self);
void PhoneClock_CancelField(PhoneClock *self);
void PhoneClock_ConfirmField(PhoneClock *self);
void PhoneClock_OpenField(PhoneClock *self, int field);
void PhoneClock_Cancel(PhoneClock *self);
void PhoneClock_SetClock(PhoneClock *self);
void PhoneClock_Resume(PhoneClock *self);
void PhoneClock_ResumeByKeys(PhoneClock *self);
void PhoneClock_ResumeByTouch(PhoneClock *self);
void PhoneClock_WaitFieldClosed(PhoneClock *self);
void PhoneClock_WaitFieldOpen(PhoneClock *self);
void PhoneClock_FollowPanelPress(PhoneClock *self);
void PhoneClock_ShowSpriteWhenDone(PhoneClock *self);
void PhoneClock_PickWhenPressed(PhoneClock *self);
void PhoneClock_WaitCursorSprite(PhoneClock *self);
void PhoneClock_WaitEditor(PhoneClock *self);
void PhoneClock_HoldButtonA(PhoneClock *self);
void PhoneClock_EditByKeys(PhoneClock *self);
void PhoneClock_BrowseByKeys(PhoneClock *self);
void PhoneClock_ThumbTowardPen(PhoneClock *self);
void PhoneClock_DragThumb(PhoneClock *self);
void PhoneClock_EditByTouch(PhoneClock *self);
void PhoneClock_WaitDragSettled(PhoneClock *self);
void PhoneClock_DragByTouch(PhoneClock *self);
void PhoneClock_BrowseByTouch(PhoneClock *self);
void PhoneClock_LoadGraphics(PhoneClock *self);
void PhoneClock_OpenEditor(PhoneClock *self);
void PhoneClock_SetUpLayers(void);
void PhoneClock_EndFrame(PhoneClock *self);
void PhoneClock_BeginFrame(PhoneClock *self);
void PhoneClock_EndInteractiveFrame(PhoneClock *self);
void PhoneClock_BeginInteractiveFrame(PhoneClock *self);
void PhoneClock_Teardown(PhoneClock *self);
void PhoneClock_Setup(PhoneClock *self);
void PhoneClock_ScrollWithWipe(PhoneClock *self);
void PhoneClock_WipeOut(PhoneClock *self);
void PhoneClock_StartWipeOut(PhoneClock *self);
void PhoneClock_WipeIn(PhoneClock *self);
void PhoneClock_StartWipeIn(PhoneClock *self);
int PhoneClock_End(PhoneClock *self);
int PhoneClock_Phase4Idle(void);
int PhoneClock_Phase3Idle(void);
int PhoneClock_RunInteractive(PhoneClock *self);
void PhoneClock_RunSubState(PhoneClock *self);
int PhoneClock_RunState(PhoneClock *self);
int PhoneClock_Draw(PhoneClock *self);
int PhoneClock_Close(PhoneClock *self);
int PhoneClock_Start(PhoneClock *self);
PhoneClock *PhoneClock_New(void);

#endif
