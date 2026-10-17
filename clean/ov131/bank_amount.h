/* The bank's amount entry of overlay 131 (vtable 0x0229b8f0,
 * include/cpp/ov131/Obj_ov131_0229b8f0.h; constructor BankAmount_New, 0x1558 bytes): a menu
 * scene (ov002/menu_scene.h) in which the player enters an amount on overlay 130's number pad
 * (ov130/bank_pad.h, at 0x2c4), as the evidence says:
 *
 * - it is overlay group 0x1f (main/overlay_groups.c), which overlay 92's dispatcher opens for
 *   GroupParams modes 0x34-0x3a (ov092/menu_dispatch.c); the mode (BankAmountMode) says where
 *   the bells come from and go to (BankAmount_SetUpRange, BankAmount_Apply); the pad's files
 *   are "menu/bank/...";
 * - the pad's keys are touched with the pen, or pointed at with a cursor sprite (a Glider0 at
 *   0x94) moved by the d-pad and pressed with A (B clears, then cancels; START confirms);
 * - the panel (at 0xf8) has the buttons OK (6, greyed while the amount is 0) and cancel (7);
 * - on OK main is told so (GroupParams_SetC4C(1)) and given the amount (GroupParams_SetC78) and
 *   the bells are moved (BankAmount_Apply); on cancel it is told 0. Then the scene wipes out and
 *   tells the dispatcher it closes (MENU_DISPATCH_MODE_CLOSE). */
#ifndef CLEAN_OV131_BANK_AMOUNT_H
#define CLEAN_OV131_BANK_AMOUNT_H

#include "ov002/button_panel.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov130/bank_pad.h"
#include "types.h"

/* GroupParams' modes the scene is opened in (the pad's kind is the mode less 0x34). */
enum BankAmountMode {
    BANK_AMOUNT_MODE_PAY_LOAN = 0x34,     /* up to the pockets' bells and the loan: both lowered */
    BANK_AMOUNT_MODE_DEPOSIT = 0x35,      /* up to the pockets' bells and the room in the savings */
    BANK_AMOUNT_MODE_WITHDRAW = 0x36,     /* up to the savings and the room in the pockets */
    BANK_AMOUNT_MODE_PAY = 0x37,          /* up to the pockets' bells, taken from them */
    BANK_AMOUNT_MODE_NUMBER = 0x38,       /* up to 9,999,999; nothing moved */
    BANK_AMOUNT_MODE_POCKET_BELLS = 0x39, /* up to the pockets' bells; nothing moved */
    BANK_AMOUNT_MODE_SMALL_NUMBER = 0x3a  /* up to 99; nothing moved */
};

/* The most bells the savings hold. */
#define BANK_AMOUNT_SAVINGS_MAX 999999999

/* In `flags`. */
#define BANK_AMOUNT_FLAG_DRAWN 0x0001 /* the scene is drawn (BankAmount_Draw) */

/* The panel's buttons (layout 6, message 0x65). */
#define BANK_AMOUNT_BUTTON_OK 6
#define BANK_AMOUNT_BUTTON_CANCEL 7

/* The scene's states (MenuScene.state), of the table of BankAmount_RunState, and its sub states
 * (MenuScene.sub_state), of the table of BankAmount_RunSubState. */
enum BankAmountState {
    BANK_AMOUNT_STATE_LOAD = 0,     /* BankAmount_LoadState */
    BANK_AMOUNT_STATE_WIPE_IN = 1,  /* BankAmount_WipeIn: then the input */
    BANK_AMOUNT_STATE_FINISH = 2,   /* BankAmount_Finish: the dispatcher told, the wipe out */
    BANK_AMOUNT_STATE_WIPE_OUT = 3, /* BankAmount_WipeOut: then the end (phase 5) */
    BANK_AMOUNT_STATES = 4
};

enum BankAmountSubState {
    BANK_AMOUNT_SUB_TOUCH = 0,       /* BankAmount_Touch: the pen on the keys and the panel */
    BANK_AMOUNT_SUB_TOUCH_HELD = 1,  /* BankAmount_TouchHeld: a key held by the pen repeats */
    BANK_AMOUNT_SUB_KEYS = 2,        /* BankAmount_Keys: the cursor, by the buttons */
    BANK_AMOUNT_SUB_GLIDE = 3,       /* BankAmount_Glide: the cursor glides, then `return_sub_state` */
    BANK_AMOUNT_SUB_KEY_PRESS = 4,   /* BankAmount_KeyPress: A pressed on the key under the cursor */
    BANK_AMOUNT_SUB_CURSOR_ANIM = 5, /* BankAmount_WaitCursorAnim: then `return_sub_state` */
    BANK_AMOUNT_SUB_KEY_HELD = 6,    /* BankAmount_KeyHeld: a key held by A repeats */
    BANK_AMOUNT_SUB_PANEL_PRESS = 7, /* BankAmount_PanelPress: a button's press plays, then phase 1 */
    BANK_AMOUNT_SUB_STATES = 8
};

/* The phases the scene sets (MenuScene.phase): 0 runs the base's wait (vtable slot 0x48), 1 the
 * states (slot 0x4c, BankAmount_RunState), 2 the input (slot 0x50, BankAmount_RunInput) and 5
 * the end (slot 0x5c, BankAmount_End). */
enum BankAmountPhase {
    BANK_AMOUNT_PHASE_WAIT = 0,
    BANK_AMOUNT_PHASE_STATES = 1,
    BANK_AMOUNT_PHASE_INPUT = 2,
    BANK_AMOUNT_PHASE_END = 5
};

/* The layers: the pad's digits and its keys. */
#define BANK_AMOUNT_DIGITS_LAYER 6
#define BANK_AMOUNT_KEYS_LAYER 4

typedef struct BankAmount {
    MenuScene base;      /* 0x00 */
    Glider cursor;       /* 0x94: a Glider0 */
    ButtonPanel panel;   /* 0xf8 */
    BankPad pad;         /* 0x2c4 */
    u16 flags;           /* 0x1554 */
    u8 return_sub_state; /* 0x1556: after the glide or the cursor's animation */
    u8 unk_1557;
} BankAmount;

BankAmount *BankAmount_Destroy(BankAmount *self);
BankAmount *BankAmount_Delete(BankAmount *self);
void BankAmount_SetFlags(BankAmount *self, int flags);
int BankAmount_TestFlags(BankAmount *self, u16 mask);
void BankAmount_Apply(BankAmount *self);
void BankAmount_SetUpRange(BankAmount *self);
void BankAmount_ShowCursorThird(BankAmount *self);
void BankAmount_ShowCursorSecond(BankAmount *self);
void BankAmount_ShowCursorFirst(BankAmount *self);
void BankAmount_GlideCursorTo(BankAmount *self, int x, int y);
void BankAmount_MoveCursor(BankAmount *self);
void BankAmount_HideCursor(BankAmount *self);
int BankAmount_CursorY(BankAmount *self);
unsigned int BankAmount_CursorX(BankAmount *self);
void BankAmount_PlaceCursor(BankAmount *self);
void BankAmount_Cancel(BankAmount *self);
int BankAmount_Confirm(BankAmount *self);
void BankAmount_BeginInput(BankAmount *self);
void BankAmount_StartKeys(BankAmount *self);
void BankAmount_StartTouch(BankAmount *self);
void BankAmount_PanelPress(BankAmount *self);
void BankAmount_KeyHeld(BankAmount *self);
void BankAmount_WaitCursorAnim(BankAmount *self);
void BankAmount_KeyPress(BankAmount *self);
void BankAmount_Glide(BankAmount *self);
void BankAmount_Keys(BankAmount *self);
void BankAmount_TouchHeld(BankAmount *self);
void BankAmount_Touch(BankAmount *self);
void BankAmount_LoadTexts(BankAmount *self);
void BankAmount_LoadPad(BankAmount *self);
void BankAmount_SetUpLayers(void);
void BankAmount_EndFrame(BankAmount *self);
void BankAmount_BeginFrame(BankAmount *self);
void BankAmount_EndInputFrame(BankAmount *self);
void BankAmount_BeginInputFrame(BankAmount *self);
void BankAmount_Teardown(BankAmount *self);
void BankAmount_Setup(BankAmount *self);
void BankAmount_ScrollWipe(BankAmount *self);
void BankAmount_WipeOut(BankAmount *self);
void BankAmount_Finish(BankAmount *self);
void BankAmount_WipeIn(BankAmount *self);
void BankAmount_LoadState(BankAmount *self);
int BankAmount_End(BankAmount *self);
int BankAmount_Slot58(void);
int BankAmount_Slot54(void);
int BankAmount_RunInput(BankAmount *self);
void BankAmount_RunSubState(BankAmount *self);
int BankAmount_RunState(BankAmount *self);
int BankAmount_Draw(BankAmount *self);
int BankAmount_Close(BankAmount *self);
int BankAmount_Start(BankAmount *self);
BankAmount *BankAmount_New(void);

#endif
