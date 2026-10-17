/* The scene of overlay 133 (vtable 0x0229c908, include/cpp/ov133/Obj_ov133_0229c908.h;
 * constructor FriendCodeEntry_New, 0x14b0 bytes): a menu scene (ov002/menu_scene.h) in which
 * the player types a friend code of twelve digits on a keypad, as the evidence says:
 *
 * - overlay 90's menu (ov090/menu_tabs.h) loads it as overlay group 0x2b for its tabs 13 and 14,
 *   setting GroupParams' mode to the tab (FriendCodeEntryMode); it is the menu's child and calls
 *   it as its parent process (MenuTabs_SelectTab, MenuTabs_ChildClosed);
 * - the code is that of friend `arg` (GroupParams_Arg) of the current player's roster
 *   (main/wifi_friends.h): its digits are loaded at the start (FriendCodeEntry_LoadCode), checked
 *   and stored when the player confirms (FriendCodeEntry_Confirm), with error messages 0x19 (the
 *   digits make no valid code), 0x1d (the player's own code) and 0x14 (another friend's code);
 * - its screens are "menu/bank/g1_bg.bsc" (the keypad, layer 4) and "menu/bank/g0_bg.bsc" (the
 *   code's row, layer 6); overlay 130's functions load the rest of the graphics and draw the
 *   frame, and are called by symbol;
 * - a pointer sprite (a Glider0) points at the key, the code's row or the panel's buttons 6
 *   (OK, enabled once all twelve digits are typed) and 7 (back to the roster).
 *
 * The keypad has three columns and four rows of keys (FriendCodeEntryKey): the digits 7 8 9,
 * 4 5 6, 1 2 3 and 0, the delete key and the clear key. The code's text cursor stands before
 * digit `position`; a range of digits from `mark_from` to `mark_to` can be marked by dragging
 * (touch) or by moving with A held, and is deleted or typed over as one. */
#ifndef CLEAN_OV133_FRIEND_CODE_ENTRY_H
#define CLEAN_OV133_FRIEND_CODE_ENTRY_H

#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "main/wifi_friends.h"
#include "ov002/button_panel.h"
#include "ov002/error_message.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "types.h"

#define FRIEND_CODE_DIGITS 12
#define FRIEND_CODE_NO_DIGIT 0x0a /* a place of `digits` with no digit typed */

/* GroupParams' modes the scene is opened in: overlay 90's tabs 13 and 14. */
enum FriendCodeEntryMode {
    FRIEND_CODE_MODE_CHANGE = 0x0d, /* the code of a friend of the roster: back to the roster (tab 6) */
    FRIEND_CODE_MODE_NEW = 0x0e     /* a friend being added: cleared when cancelled; on confirm the
                                     * friend's name entry (tab 12, overlay 126) follows */
};

/* Overlay 90's tabs the scene switches to (MenuTabs_SelectTab). */
enum FriendCodeEntryTab {
    FRIEND_CODE_TAB_ROSTER = 6,     /* the friend roster */
    FRIEND_CODE_TAB_CLOSE = 7,      /* the menu closes */
    FRIEND_CODE_TAB_NAME_ENTRY = 12 /* overlay 126's entry of a friend's text */
};

/* What `key` points at. 0-11 are the keypad's keys, three a row (FriendCodeEntry_KeyDigit gives
 * the digit of 0-9). */
enum FriendCodeEntryKey {
    FRIEND_CODE_KEY_0 = 9,       /* the key of digit 0, the bottom row's first */
    FRIEND_CODE_KEY_DELETE = 10, /* the digit before the cursor (or the marked range) deleted */
    FRIEND_CODE_KEY_CLEAR = 11,  /* every digit cleared */
    FRIEND_CODE_KEYPAD_LAST = 11,
    FRIEND_CODE_KEY_CODE = 12, /* the code's row (the text cursor) */
    FRIEND_CODE_KEY_OK = 13,   /* the panel's button 6 */
    FRIEND_CODE_KEY_BACK = 14, /* the panel's button 7 */
    FRIEND_CODE_KEY_NONE = 15  /* FriendCodeEntry_KeyAtTouch: nothing there */
};

/* The panel's buttons. */
#define FRIEND_CODE_BUTTON_OK 6
#define FRIEND_CODE_BUTTON_BACK 7

/* In `flags`. */
enum FriendCodeEntryFlag {
    FRIEND_CODE_FLAG_DRAWN = 0x01,        /* the scene is drawn (FriendCodeEntry_Draw) */
    FRIEND_CODE_FLAG_KEYPAD_DIRTY = 0x02, /* the keypad's screen is to be loaded to its layer */
    FRIEND_CODE_FLAG_CODE_DIRTY = 0x04,   /* the code's screen is to be loaded to its layer */
    FRIEND_CODE_FLAG_DIGITS = 0x08,       /* the digits changed: their characters are to be written */
    FRIEND_CODE_FLAG_CURSOR = 0x10        /* the cursor or the mark moved: the mark's colours too */
};

/* The states (MenuScene.state), run by FriendCodeEntry_RunState. */
enum FriendCodeEntryState {
    FRIEND_CODE_STATE_LOAD = 0,           /* FriendCodeEntry_Load */
    FRIEND_CODE_STATE_START_WIPE_IN = 1,  /* FriendCodeEntry_StartWipeIn */
    FRIEND_CODE_STATE_WIPE_IN = 2,        /* FriendCodeEntry_WipeIn */
    FRIEND_CODE_STATE_START_WIPE_OUT = 3, /* FriendCodeEntry_StartWipeOut */
    FRIEND_CODE_STATE_WIPE_OUT = 4,       /* FriendCodeEntry_WipeOut */
    FRIEND_CODE_STATES = 5
};

/* The sub states (MenuScene.sub_state), run by FriendCodeEntry_RunSubState. */
enum FriendCodeEntrySubState {
    FRIEND_CODE_SUB_TOUCH = 0,          /* FriendCodeEntry_BrowseByTouch */
    FRIEND_CODE_SUB_TOUCH_KEY_HELD = 1, /* FriendCodeEntry_TouchKeyHeld */
    FRIEND_CODE_SUB_TOUCH_MARK = 2,     /* FriendCodeEntry_TouchMark */
    FRIEND_CODE_SUB_KEYS = 3,           /* FriendCodeEntry_BrowseByKeys */
    FRIEND_CODE_SUB_POINTER_GLIDE = 4,  /* FriendCodeEntry_WaitPointerGlide */
    FRIEND_CODE_SUB_KEY_PRESS = 5,      /* FriendCodeEntry_PressWhenDone */
    FRIEND_CODE_SUB_POINTER_PRESS = 6,  /* FriendCodeEntry_WaitPointerPress */
    FRIEND_CODE_SUB_KEY_HELD = 7,       /* FriendCodeEntry_KeyHeld */
    FRIEND_CODE_SUB_DELETE_HELD = 8,    /* FriendCodeEntry_DeleteHeld */
    FRIEND_CODE_SUB_MARK_KEYS = 9,      /* FriendCodeEntry_MarkByKeys */
    FRIEND_CODE_SUB_BUTTON_PRESS = 10,  /* FriendCodeEntry_FollowButtonPress */
    FRIEND_CODE_SUB_ERROR = 11,         /* FriendCodeEntry_WaitError */
    FRIEND_CODE_SUB_SET_FRIEND = 12,    /* FriendCodeEntry_RetrySetFriend */
    FRIEND_CODE_SUB_STATES = 13
};

/* The phases the scene sets (MenuScene.phase; the vtable's slot 0x48 + 4 * phase runs). */
enum FriendCodeEntryPhase {
    FRIEND_CODE_PHASE_STATES = 1,      /* FriendCodeEntry_RunState */
    FRIEND_CODE_PHASE_INTERACTIVE = 2, /* FriendCodeEntry_RunInteractive */
    FRIEND_CODE_PHASE_END = 5          /* FriendCodeEntry_End */
};

typedef struct FriendCodeEntry {
    MenuScene base;                /* 0x0000 */
    s32 wipe_y;                    /* 0x0094: MenuScene_WipeOffsetY's, the panel and the frame drawn there */
    u16 flags;                     /* 0x0098: FriendCodeEntryFlag */
    u8 label_count;                /* 0x009a: labels in use this frame (FriendCodeEntry_NextLabel) */
    u8 return_sub_state;           /* 0x009b: the sub state to go back to once the pointer stops */
    u8 key;                        /* 0x009c: FriendCodeEntryKey */
    u8 repeat;                     /* 0x009d: frames before a held key acts again (0: it does not) */
    u8 lit_frames;                 /* 0x009e: frames the pressed key stays lit */
    u8 position;                   /* 0x009f: the text cursor, before digit `position` (0-12) */
    u8 lit_key;                    /* 0x00a0: the key lit */
    u8 blink;                      /* 0x00a1: the cursor's blink: drawn while bit 4 is set */
    u8 mark_to;                    /* 0x00a2: the end of the marked range moved */
    u8 mark_from;                  /* 0x00a3: where the mark started; no mark when equal */
    u8 digits[FRIEND_CODE_DIGITS]; /* 0x00a4: the code (FRIEND_CODE_NO_DIGIT after the last) */
    TextLabel label;               /* 0x00b0: the title, an array of one */
    Glider pointer;                /* 0x011c: a Glider0 */
    ButtonPanel panel;             /* 0x0180 */
    LayerTask tasks[2];            /* 0x034c: the keypad's screen and the code's */
    u16 keypad_screen[0x400];      /* 0x0394: "menu/bank/g1_bg.bsc" */
    u16 code_screen[0x400];        /* 0x0b94: "menu/bank/g0_bg.bsc" */
    ErrorMessage error;            /* 0x1394 */
} FriendCodeEntry;

FriendCodeEntry *FriendCodeEntry_Destroy(FriendCodeEntry *self);
FriendCodeEntry *FriendCodeEntry_Delete(FriendCodeEntry *self);
void FriendCodeEntry_ClearFlags(FriendCodeEntry *self, u16 flags);
void FriendCodeEntry_SetFlags(FriendCodeEntry *self, u16 flags);
int FriendCodeEntry_TestFlags(FriendCodeEntry *self, unsigned int flags);
void FriendCodeEntry_UnlightKey(FriendCodeEntry *self, int key);
void FriendCodeEntry_LightKey(FriendCodeEntry *self, int key);
void FriendCodeEntry_ColourKey(FriendCodeEntry *self, int key, int palette);
void FriendCodeEntry_UnlightKeypad(FriendCodeEntry *self);
int FriendCodeEntry_RepeatDue(FriendCodeEntry *self);
void FriendCodeEntry_StopRepeat(FriendCodeEntry *self);
int FriendCodeEntry_PressKey(FriendCodeEntry *self);
void FriendCodeEntry_UpdateScreens(FriendCodeEntry *self);
void FriendCodeEntry_ColourMark(FriendCodeEntry *self);
void FriendCodeEntry_WriteDigits(FriendCodeEntry *self);
int FriendCodeEntry_DigitCount(FriendCodeEntry *self);
int FriendCodeEntry_InsertDigit(FriendCodeEntry *self, u8 digit);
void FriendCodeEntry_DeleteMark(FriendCodeEntry *self);
int FriendCodeEntry_DeleteBack(FriendCodeEntry *self, int sound_when_empty);
void FriendCodeEntry_Clear(FriendCodeEntry *self);
void FriendCodeEntry_LoadCode(FriendCodeEntry *self);
void FriendCodeEntry_MarkTo(FriendCodeEntry *self, int position);
void FriendCodeEntry_SetCursor(FriendCodeEntry *self, u8 position);
int FriendCodeEntry_PositionAtTouch(FriendCodeEntry *self);
int FriendCodeEntry_MoveCursor(FriendCodeEntry *self, int keys);
int FriendCodeEntry_UseKey(FriendCodeEntry *self, int first);
int FriendCodeEntry_PressSelected(FriendCodeEntry *self);
void FriendCodeEntry_Cancel(FriendCodeEntry *self);
void FriendCodeEntry_Confirm(FriendCodeEntry *self);
int FriendCodeEntry_IsOwnCode(FriendCodeEntry *self);
int FriendCodeEntry_IsOtherFriendsCode(FriendCodeEntry *self, WifiFriendData *code);
WifiFriend *FriendCodeEntry_Friend(FriendCodeEntry *self);
int FriendCodeEntry_KeyAtTouch(FriendCodeEntry *self, int x, int y);
int FriendCodeEntry_MoveKey(FriendCodeEntry *self, int keys);
void FriendCodeEntry_ShowPointer(FriendCodeEntry *self);
int FriendCodeEntry_PressPointer(FriendCodeEntry *self);
void FriendCodeEntry_PressAtKey(FriendCodeEntry *self);
void FriendCodeEntry_GlidePointer(FriendCodeEntry *self);
void FriendCodeEntry_HidePointer(FriendCodeEntry *self);
int FriendCodeEntry_PointerY(FriendCodeEntry *self);
int FriendCodeEntry_PointerX(FriendCodeEntry *self);
void FriendCodeEntry_PlacePointer(FriendCodeEntry *self);
TextLabel *FriendCodeEntry_NextLabel(FriendCodeEntry *self);
void FriendCodeEntry_CloseLabels(FriendCodeEntry *self);
void FriendCodeEntry_ShowError(FriendCodeEntry *self, int message, int flag);
void FriendCodeEntry_Resume(FriendCodeEntry *self);
void FriendCodeEntry_ResumeByKeys(FriendCodeEntry *self);
int FriendCodeEntry_ResumeByTouch(FriendCodeEntry *self);

void FriendCodeEntry_RetrySetFriend(FriendCodeEntry *self);
void FriendCodeEntry_WaitError(FriendCodeEntry *self);
void FriendCodeEntry_FollowButtonPress(FriendCodeEntry *self);
void FriendCodeEntry_MarkByKeys(FriendCodeEntry *self);
void FriendCodeEntry_DeleteHeld(FriendCodeEntry *self);
void FriendCodeEntry_KeyHeld(FriendCodeEntry *self);
void FriendCodeEntry_WaitPointerPress(FriendCodeEntry *self);
void FriendCodeEntry_PressWhenDone(FriendCodeEntry *self);
void FriendCodeEntry_WaitPointerGlide(FriendCodeEntry *self);
void FriendCodeEntry_BrowseByKeys(FriendCodeEntry *self);
void FriendCodeEntry_TouchMark(FriendCodeEntry *self);
void FriendCodeEntry_TouchKeyHeld(FriendCodeEntry *self);
void FriendCodeEntry_BrowseByTouch(FriendCodeEntry *self);
void FriendCodeEntry_OpenTitle(FriendCodeEntry *self);
void FriendCodeEntry_LoadScreens(FriendCodeEntry *self);
void FriendCodeEntry_SetUpLayers(void);
void FriendCodeEntry_EndInteractiveFrame(FriendCodeEntry *self);
void FriendCodeEntry_BeginInteractiveFrame(FriendCodeEntry *self);
void FriendCodeEntry_EndFrame(FriendCodeEntry *self);
void FriendCodeEntry_BeginFrame(FriendCodeEntry *self);
void FriendCodeEntry_Teardown(FriendCodeEntry *self);
void FriendCodeEntry_Setup(FriendCodeEntry *self);
void FriendCodeEntry_WipeOut(FriendCodeEntry *self);
void FriendCodeEntry_StartWipeOut(FriendCodeEntry *self);
void FriendCodeEntry_WipeIn(FriendCodeEntry *self);
void FriendCodeEntry_StartWipeIn(FriendCodeEntry *self);
void FriendCodeEntry_Load(FriendCodeEntry *self);
int FriendCodeEntry_SelectTab(FriendCodeEntry *self, int tab);
int FriendCodeEntry_End(FriendCodeEntry *self);
int FriendCodeEntry_Phase4Idle(void);
int FriendCodeEntry_Phase3Idle(void);
int FriendCodeEntry_RunInteractive(FriendCodeEntry *self);
void FriendCodeEntry_RunSubState(FriendCodeEntry *self);
int FriendCodeEntry_RunState(FriendCodeEntry *self);
int FriendCodeEntry_Draw(FriendCodeEntry *self);
int FriendCodeEntry_Close(FriendCodeEntry *self);
int FriendCodeEntry_Start(FriendCodeEntry *self);
FriendCodeEntry *FriendCodeEntry_New(void);

#endif
