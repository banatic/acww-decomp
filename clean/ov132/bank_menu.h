/* The scene of overlay 132 (vtable 0x0229b990, include/cpp/ov132/Obj_ov132_0229b990.h;
 * constructor BankMenu_New, 0x1508 bytes): the first screen of the bank machine, as the evidence
 * says:
 *
 * - overlay 92's dispatcher opens it with overlay 130 (the bank's graphics) as overlay group 0x20
 *   for GroupParams' mode 0x3b (ov092/menu_dispatch.c);
 * - its two screens are "menu/bank/c0_bg.bsc" and "menu/bank/c1_bg.bsc", and it shows two rows
 *   (menu messages 0x5f and 0x60) and the panel's button 6;
 * - the first row (BANK_MENU_DEPOSIT) refuses with error message 14 when the player's savings
 *   (main/savings.h) hold 999,999,999 Bells, else hands the parent mode 0x35; the second
 *   (BANK_MENU_WITHDRAW) refuses with error message 15 when the player's pockets have no room for
 *   Bells (PlayerPockets_BellsRoom), else hands the parent mode 0x36. Both modes open overlay
 *   131's screen (group 0x1f). The panel's button 6 closes the menu (mode 0x44).
 *
 * The cursor is one of the three places; the d-pad moves it up and down, the pen picks a row by
 * its rectangle on the touch screen. */
#ifndef CLEAN_OV132_BANK_MENU_H
#define CLEAN_OV132_BANK_MENU_H

#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "ov002/button_panel.h"
#include "ov002/error_message.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "types.h"

#define BANK_MENU_LABELS 2
#define BANK_MENU_SCREEN_SIZE 0x800

/* The places of the cursor (`cursor`). */
enum BankMenuPlace {
    BANK_MENU_DEPOSIT = 0,  /* the first row */
    BANK_MENU_WITHDRAW = 1, /* the second row */
    BANK_MENU_QUIT = 2      /* the panel's button 6 */
};

/* In `flags`. */
enum BankMenuFlag {
    BANK_MENU_FLAG_DRAWN = 0x01 /* the scene is drawn (BankMenu_Draw) */
};

/* The states, run from the table of BankMenu_RunState (MenuScene_SetState). */
enum BankMenuState {
    BANK_MENU_STATE_START_WIPE_IN = 0,  /* BankMenu_StartWipeIn */
    BANK_MENU_STATE_WIPE_IN = 1,        /* BankMenu_WipeIn */
    BANK_MENU_STATE_START_WIPE_OUT = 2, /* BankMenu_StartWipeOut */
    BANK_MENU_STATE_WIPE_OUT = 3,       /* BankMenu_WipeOut */
    BANK_MENU_STATES = 4
};

/* The sub states, run from the table of BankMenu_RunSubState (MenuScene_SetSubState). */
enum BankMenuSubState {
    BANK_MENU_SUB_TOUCH = 0,         /* BankMenu_BrowseByTouch */
    BANK_MENU_SUB_KEYS = 1,          /* BankMenu_BrowseByKeys */
    BANK_MENU_SUB_SPRITE_MOVE = 2,   /* BankMenu_WaitCursorSprite */
    BANK_MENU_SUB_PRESS = 3,         /* BankMenu_PickWhenPressed */
    BANK_MENU_SUB_SHOW_SPRITE = 4,   /* BankMenu_ShowSpriteWhenDone */
    BANK_MENU_SUB_PANEL_PRESSED = 5, /* BankMenu_FollowQuitPress */
    BANK_MENU_SUB_LEAVE_DELAY = 6,   /* BankMenu_WaitToLeave */
    BANK_MENU_SUB_ERROR = 7,         /* BankMenu_WaitError */
    BANK_MENU_SUB_STATES = 8
};

typedef struct BankMenu {
    MenuScene base;                          /* 0x0000 */
    Glider cursor_sprite;                    /* 0x0094: a Glider0 */
    ButtonPanel panel;                       /* 0x00f8 */
    TextLabel labels[BANK_MENU_LABELS];      /* 0x02c4: the two rows' texts */
    LayerTask screen_tasks[2];               /* 0x039c: the two screens queued for loading */
    ErrorMessage error;                      /* 0x03e4 */
    u16 screen_a[BANK_MENU_SCREEN_SIZE / 2]; /* 0x0500: c0_bg.bsc, on layer 6 */
    u16 screen_b[BANK_MENU_SCREEN_SIZE / 2]; /* 0x0d00: c1_bg.bsc, on layer 4 */
    u16 flags;                               /* 0x1500: BankMenuFlag */
    u8 cursor;                               /* 0x1502: BankMenuPlace */
    u8 return_sub_state;                     /* 0x1503: the sub state to go back to once the sprite stops */
    u8 labels_used;                          /* 0x1504: the labels BankMenu_NextLabel handed out */
    u8 next_mode;                            /* 0x1505: what the parent is told when the scene wipes out */
    u8 leave_delay;                          /* 0x1506: the frames left before the wipe out */
    u8 pad_1507;
} BankMenu;

BankMenu *BankMenu_Destroy(BankMenu *self);
BankMenu *BankMenu_Delete(BankMenu *self);
void BankMenu_SetFlags(BankMenu *self, u16 flags);
int BankMenu_TestFlags(BankMenu *self, int flags);
TextLabel *BankMenu_NextLabel(BankMenu *self);
void BankMenu_CloseLabels(BankMenu *self);
void BankMenu_PressCursorSprite(BankMenu *self);
void BankMenu_ShowCursorSprite(BankMenu *self);
void BankMenu_GlideTo(BankMenu *self, int x, int y);
void BankMenu_GlideToCursor(BankMenu *self);
void BankMenu_HideCursorSprite(BankMenu *self);
int BankMenu_CursorY(BankMenu *self);
int BankMenu_CursorX(BankMenu *self);
void BankMenu_ShowCursorAtCursor(BankMenu *self);
void BankMenu_ShowError(BankMenu *self, u8 message);
void BankMenu_PickWithdraw(BankMenu *self);
void BankMenu_PickDeposit(BankMenu *self);
void BankMenu_Leave(BankMenu *self);
void BankMenu_Quit(BankMenu *self);
void BankMenu_Resume(BankMenu *self);
int BankMenu_ResumeByKeys(BankMenu *self);
int BankMenu_ResumeByTouch(BankMenu *self);
void BankMenu_WaitError(BankMenu *self);
void BankMenu_WaitToLeave(BankMenu *self);
void BankMenu_FollowQuitPress(BankMenu *self);
void BankMenu_ShowSpriteWhenDone(BankMenu *self);
void BankMenu_PickWhenPressed(BankMenu *self);
void BankMenu_WaitCursorSprite(BankMenu *self);
void BankMenu_BrowseByKeys(BankMenu *self);
void BankMenu_BrowseByTouch(BankMenu *self);
void BankMenu_LoadPanelColors(BankMenu *self);
void BankMenu_LoadScreens(BankMenu *self);
void BankMenu_SetUpLayers(void);
void BankMenu_EndFrame(void);
void BankMenu_BeginFrame(BankMenu *self);
void BankMenu_EndInteractiveFrame(void);
void BankMenu_BeginInteractiveFrame(BankMenu *self);
void BankMenu_Teardown(BankMenu *self);
void BankMenu_Setup(BankMenu *self);
void BankMenu_ScrollWithWipe(BankMenu *self);
void BankMenu_WipeOut(BankMenu *self);
void BankMenu_StartWipeOut(BankMenu *self);
void BankMenu_WipeIn(BankMenu *self);
void BankMenu_StartWipeIn(BankMenu *self);
int BankMenu_End(BankMenu *self);
int BankMenu_Phase4Idle(void);
int BankMenu_Phase3Idle(void);
int BankMenu_RunInteractive(BankMenu *self);
void BankMenu_RunSubState(BankMenu *self);
int BankMenu_RunState(BankMenu *self);
int BankMenu_Draw(BankMenu *self);
int BankMenu_Close(BankMenu *self);
int BankMenu_Start(BankMenu *self);
BankMenu *BankMenu_New(void);

#endif
