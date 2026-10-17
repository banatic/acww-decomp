/* The bank's number pad of overlay 130 ("menu/bank/..."): an object the bank screens keep inside
 * their scene (overlay 131's amount entry, ov131/bank_amount.h, at 0x2c4; overlays 132 and 133
 * call some of its functions too). It shows a keypad on one 2D layer (`keys_layer`, the keys'
 * palettes changed to show the one pressed) and the amounts in digits of the screen of another
 * (`digits_layer`), up to five text labels, and a teller's picture on the sub screen's objects.
 *
 * The player enters `amount` with the keys 0-9 and C (BANK_PAD_KEY_CLEAR) by the pen or by a
 * cursor over the keys moved with the d-pad; the cursor also goes to the panel's OK and cancel
 * buttons (BANK_PAD_KEY_OK, BANK_PAD_KEY_CANCEL), which the scene handles. A digit appends to
 * the amount, which never goes above `max_amount`; a key held repeats.
 *
 * The scene sets the kind of entry (BankPadKind, GroupParams' mode less 0x34) and the range
 * (BankPad_SetRange): the most that can be entered, the limit shown (the bells it comes from)
 * and the current value (what the amount is added to or taken from). */
#ifndef CLEAN_OV130_BANK_PAD_H
#define CLEAN_OV130_BANK_PAD_H

#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "types.h"

/* The kinds of entry (`kind`), by GroupParams' mode (0x34-0x3a, ov131/bank_amount.h). */
enum BankPadKind {
    BANK_PAD_KIND_PAY_LOAN = 0,     /* from the pockets to the house's loan */
    BANK_PAD_KIND_DEPOSIT = 1,      /* from the pockets to the savings */
    BANK_PAD_KIND_WITHDRAW = 2,     /* from the savings to the pockets */
    BANK_PAD_KIND_PAY = 3,          /* from the pockets */
    BANK_PAD_KIND_NUMBER = 4,       /* a number up to 9,999,999 */
    BANK_PAD_KIND_POCKET_BELLS = 5, /* a number up to the pockets' bells */
    BANK_PAD_KIND_SMALL_NUMBER = 6, /* a number up to 99 */
    BANK_PAD_KINDS = 7
};

/* The screens' layouts (`layout`, set by the kind): the files of both screens and where the
 * amounts are drawn. Layouts 0 and 1 draw big digits; BankPad_Setup never sets them. */
enum BankPadLayout {
    BANK_PAD_LAYOUT_0 = 0,
    BANK_PAD_LAYOUT_1 = 1,
    BANK_PAD_LAYOUT_TRANSFER = 2, /* the limit, the amount and the result; the keypad 0x40 to the right */
    BANK_PAD_LAYOUT_PAY = 3,      /* the limit and the amount */
    BANK_PAD_LAYOUT_SMALL = 4,    /* a two-digit amount */
    BANK_PAD_LAYOUT_NUMBER = 5,   /* a seven-digit amount */
    BANK_PAD_LAYOUTS = 6
};

/* The keys (`cursor_key`, `pressed_key`). */
enum BankPadKey {
    BANK_PAD_KEY_CLEAR = 10, /* C: the amount back to 0 */
    BANK_PAD_KEY_OK = 11,    /* the panel's OK button */
    BANK_PAD_KEY_CANCEL = 12,
    BANK_PAD_KEY_NONE = 13
};

/* The digits of the digit screen: 0-9, a dash and a blank. */
#define BANK_PAD_DIGIT_DASH 10
#define BANK_PAD_DIGIT_BLANK 11

/* `dirty`: a screen changed and is to be loaded into its layer (BankPad_LoadScreens). */
#define BANK_PAD_DIRTY_DIGITS 0x0001
#define BANK_PAD_DIRTY_KEYS 0x0002

#define BANK_PAD_LABELS 5
#define BANK_PAD_SCREEN_TILES 0x400 /* 32 x 32 */

typedef struct BankPad {
    u16 dirty;          /* 0x00 */
    u8 repeat_timer;    /* 0x02: frames to the held key's next press; 0 when no key repeats */
    u8 highlight_timer; /* 0x03: frames the pressed key stays shown pressed */
    u8 pressed_key;     /* 0x04: BankPadKey */
    u8 cursor_key;      /* 0x05: the key under the cursor */
    u8 label_count;     /* 0x06: of `labels` in use this frame */
    u8 kind;            /* 0x07: BankPadKind */
    u8 layout;          /* 0x08: BankPadLayout */
    u8 picture;         /* 0x09: the teller's picture (BankPad_LoadPicture) */
    u8 digits_layer;    /* 0x0a */
    u8 keys_layer;      /* 0x0b */
    s32 amount;         /* 0x0c: entered */
    s32 max_amount;     /* 0x10 */
    s32 limit;          /* 0x14 */
    s32 current;        /* 0x18 */
    s32 shown_limit;    /* 0x1c: the limit as last drawn */
    s32 shown_result;   /* 0x20: the result as last drawn */
    u8 unk_24[8];
    TextLabel labels[BANK_PAD_LABELS];        /* 0x2c */
    LayerTask tasks[2];                       /* 0x248: the digit screen's load, the keys' */
    u16 digits_screen[BANK_PAD_SCREEN_TILES]; /* 0x290 */
    u16 keys_screen[BANK_PAD_SCREEN_TILES];   /* 0xa90 */
} BankPad;

void BankPad_ClearDirty(BankPad *pad, int mask);
void BankPad_SetDirty(BankPad *pad, int mask);
int BankPad_IsDirty(BankPad *pad, u16 mask);
TextLabel *BankPad_NextLabel(BankPad *pad);
void BankPad_CloseLabels(BankPad *pad);
void BankPad_PutDigit(BankPad *pad, int digit, int x, int y);
void BankPad_DrawNumber(BankPad *pad, int value, int x, int y, int digits);
void BankPad_FillDigits(BankPad *pad, int digit, int x, int y, int digits);
void BankPad_PutBigDigit(BankPad *pad, int digit, int x, int y);
void BankPad_DrawBigNumber(BankPad *pad, int value, int x, int y, int digits);
void BankPad_FillBigDigits(BankPad *pad, int digit, int x, int y, int digits);
void BankPad_DrawAmounts(BankPad *pad);
void BankPad_PressKey(BankPad *pad);
int BankPad_ClearAmount(BankPad *pad);
void BankPad_PlayClearSound(void);
int BankPad_PlayDigitSound(int digit);
int BankPad_Current(BankPad *pad);
int BankPad_Limit(BankPad *pad);
int BankPad_Amount(BankPad *pad);
void BankPad_SetRange(BankPad *pad, int max_amount, int limit, int current);
void BankPad_Draw(BankPad *pad, int wipe_offset);
void BankPad_DrawPayCells(int wipe_offset);
int BankPad_CursorOnOk(BankPad *pad);
int BankPad_PressCursorKey(BankPad *pad);
int BankPad_MoveCursor(BankPad *pad, int keys);
int BankPad_CursorOnButton(BankPad *pad);
u32 BankPad_CursorY(BankPad *pad);
u32 BankPad_CursorX(BankPad *pad);
void BankPad_ShowKeyUp(BankPad *pad, int key);
void BankPad_ShowKeyDown(BankPad *pad, int key);
void BankPad_SetKeyPalette(BankPad *pad, unsigned int key, int palette);
void BankPad_ShowKeysUp(BankPad *pad);
int BankPad_StepRepeat(BankPad *pad);
void BankPad_StopRepeat(BankPad *pad);
void BankPad_StartPress(BankPad *pad);
int BankPad_KeyAt(BankPad *pad, int x, int y);
void BankPad_LoadScreens(BankPad *pad);
void BankPad_BeginFrame(BankPad *pad);
void BankPad_Teardown(BankPad *pad);
void BankPad_ShowMessage(BankPad *pad);
int BankPad_LoadPicture(int picture);
void BankPad_Load(BankPad *pad);
int BankPad_LoadBackground(int layer);
void BankPad_Setup(BankPad *pad, u8 kind, u8 digits_layer, u8 keys_layer);
BankPad *BankPad_Destroy(BankPad *pad);
BankPad *BankPad_Construct(BankPad *pad);

#endif
