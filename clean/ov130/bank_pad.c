/* The bank's number pad of overlay 130 (bank_pad.h): its digits, its keys, its screens and
 * labels, its setup, constructor and destructor. */
#include "bank_pad.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/display_layers.h"
#include "main/layer_load_task.h"
#include "main/oam_buffer.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/rom_file.h"
#include "main/screen_map.h"
#include "main/sound.h"
#include "main/text_label.h"
#include "ov002/key_repeat.h"

static_assert(offsetof(BankPad, amount) == 0x0c && offsetof(BankPad, shown_result) == 0x20, "amounts");
static_assert(sizeof(TextLabel) == 0x6c && offsetof(BankPad, labels) == 0x2c, "labels");
static_assert(sizeof(LayerTask) == 0x24 && offsetof(BankPad, tasks) == 0x248, "tasks");
static_assert(offsetof(BankPad, digits_screen) == 0x290 && offsetof(BankPad, keys_screen) == 0xa90, "screens");
static_assert(sizeof(BankPad) == 0x1290, "size");

/* The heap the files are loaded with. */
extern Heap *data_021fbe94;

/* The sounds (SoundSys_PlaySe). */
#define BANK_PAD_SE_CLEAR 0x2a   /* the amount cleared */
#define BANK_PAD_SE_REFUSED 0x34 /* a key that changes nothing */

/* The tile numbers of the digits on the digit screen: two tiles high (small), or two by two
 * (big); the blank's big digit is the same pair of tiles twice. */
#define BANK_PAD_SMALL_DIGIT_TILES 0x160
#define BANK_PAD_BIG_DIGIT_TILES 0x84
#define BANK_PAD_BIG_BLANK_TILE 0x176
#define BANK_PAD_TILE_ATTRIBUTES 0xfc00 /* a tile's flips and palette, kept */

/* The palettes of the keys on the key screen. */
#define BANK_PAD_PALETTE_CLEAR_UP 1
#define BANK_PAD_PALETTE_KEY_UP 2
#define BANK_PAD_PALETTE_KEY_DOWN 3

/* The frames of a key press: until the first repeat, between repeats, shown pressed. */
#define BANK_PAD_REPEAT_FIRST 13
#define BANK_PAD_REPEAT_NEXT 2
#define BANK_PAD_HIGHLIGHT_FRAMES 5

/* The layouts that keep the keypad 0x40 pixels (8 tiles) to the right. */
static int bank_pad_is_wide(u8 layout)
{
    return layout == BANK_PAD_LAYOUT_0 || layout == BANK_PAD_LAYOUT_TRANSFER;
}

/* Where each layout draws the amounts on the digit screen: the column of the units and the row
 * of the first amount (the next ones are 3 rows below each other). */
extern const s32 data_ov130_0229a858[BANK_PAD_LAYOUTS]; /* rows */
extern const s32 data_ov130_0229a870[BANK_PAD_LAYOUTS]; /* columns */

/* The cursor's moves by the d-pad: the key reached from each key. */
extern const u8 data_ov130_0229a818[]; /* down */
extern const u8 data_ov130_0229a828[]; /* left */
extern const u8 data_ov130_0229a838[]; /* right */
extern const u8 data_ov130_0229a848[]; /* up */

/* The keys of the keypad by the pen: 3 columns 32 pixels wide, 4 rows 16 high. */
extern const u8 data_ov130_0229a80c[12];

/* The keys' places on the key screen (tiles, keys 0-9 and C): left, right and top; each is two
 * tiles high. */
extern const s32 data_ov130_0229a888[11];
extern const s32 data_ov130_0229a8b4[11];
extern const s32 data_ov130_0229a8e0[11];

/* The cursor's place over each key (in pixels; keys 0-9 and C, OK, cancel). */
extern const u32 data_ov130_0229a90c[13]; /* x */
extern const u32 data_ov130_0229a940[13]; /* y */

/* The menu messages of the labels, by kind. */
extern const u8 data_ov130_0229a7f4[BANK_PAD_KINDS]; /* the result's caption (wide layouts) */
extern const u8 data_ov130_0229a7fc[BANK_PAD_KINDS]; /* the teller's message */
extern const u8 data_ov130_0229a804[BANK_PAD_KINDS]; /* the amount's caption */

/* The files: the teller's pictures ("menu/bank/ten0_0_obj.bch", "ten0_1_obj.bch", five each),
 * the screens of each layout ("menu/bank/a0_bg.bsc" ...), the objects' palettes and
 * characters ("obj.bpl", "obj0.bch", "obj1.bch"), the teller's palettes ("ten0.bpl") and the
 * background's characters and palettes ("bg0.bch", "bg1.bch", "bg.bpl"). */
extern const char *const data_ov130_0229a980[2];
extern const char *const data_ov130_0229aa78[BANK_PAD_LAYOUTS]; /* the key screens */
extern const char *const data_ov130_0229aa90[BANK_PAD_LAYOUTS]; /* the digit screens */
extern const char data_ov130_0229ac30[], data_ov130_0229ac44[], data_ov130_0229ac58[], data_ov130_0229ac6c[];
extern const char data_ov130_0229ac80[], data_ov130_0229ac94[], data_ov130_0229aca8[];

/* The cells drawn over the screens (BankPad_Draw): the frames of the wide layouts and of the
 * others, and the commas after the thousands and the millions of each amount. */
extern const OamEntry data_ov130_0229aae0[], data_ov130_0229ab20[], data_ov130_0229ab70[], data_ov130_0229abb0[],
    data_ov130_0229abf0[];
extern const OamEntry data_ov130_0229ab00[], data_ov130_0229ab08[], data_ov130_0229ab10[], data_ov130_0229ab18[];
extern const OamEntry data_ov130_0229ab40[], data_ov130_0229ab48[], data_ov130_0229ab50[], data_ov130_0229ab58[],
    data_ov130_0229ab60[], data_ov130_0229ab68[];

/* The labels' constructor and destructor, handed to the array helpers (the game's symbols). */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void *func_02070c08(void *label);
extern int **func_02070be8(void *label);

/* --- The flags and the labels --- */

/* func_ov130_022999a0 */
void BankPad_ClearDirty(BankPad *pad, int mask)
{
    pad->dirty &= (u16) ~mask;
}
CLEAN_AS(func_ov130_022999a0, BankPad_ClearDirty)

/* func_ov130_022999a8 */
void BankPad_SetDirty(BankPad *pad, int mask)
{
    pad->dirty |= (u16) mask;
}
CLEAN_AS(func_ov130_022999a8, BankPad_SetDirty)

/* func_ov130_022999b0 */
int BankPad_IsDirty(BankPad *pad, u16 mask)
{
    return (pad->dirty & mask) != 0;
}
CLEAN_AS(func_ov130_022999b0, BankPad_IsDirty)

/* func_ov130_022999c0: the next free label of this frame; the last one again once all five are
 * taken. */
TextLabel *BankPad_NextLabel(BankPad *pad)
{
    if (pad->label_count >= BANK_PAD_LABELS) {
        return &pad->labels[BANK_PAD_LABELS - 1];
    }
    pad->label_count++;
    return &pad->labels[pad->label_count - 1];
}
CLEAN_AS(func_ov130_022999c0, BankPad_NextLabel)

/* func_ov130_022999e4: no label in use, and the boxes of all five closed. */
void BankPad_CloseLabels(BankPad *pad)
{
    pad->label_count = 0;
    for (int i = 0; i < BANK_PAD_LABELS; i++) {
        TextLabel_CloseBox(&pad->labels[i]);
    }
}
CLEAN_AS(func_ov130_022999e4, BankPad_CloseLabels)

/* --- The digits --- */

/* The tile at `index` of a screen set to `tile`, its attributes kept. */
static void put_tile(u16 *screen, int index, u16 tile)
{
    screen[index] = (u16) ((screen[index] & BANK_PAD_TILE_ATTRIBUTES) | tile);
}

/* func_ov130_02299a08: a small digit (BANK_PAD_DIGIT_DASH, BANK_PAD_DIGIT_BLANK too) at column
 * x, row y of the digit screen, two tiles high. */
void BankPad_PutDigit(BankPad *pad, int digit, int x, int y)
{
    u16 tile = (u16) (digit * 2 + BANK_PAD_SMALL_DIGIT_TILES);
    int index = x + y * 32;
    put_tile(pad->digits_screen, index, tile);
    put_tile(pad->digits_screen, index + 32, (u16) (tile + 1));
    BankPad_SetDirty(pad, BANK_PAD_DIRTY_DIGITS);
}
CLEAN_AS(func_ov130_02299a08, BankPad_PutDigit)

/* func_ov130_02299a58: `value` in `digits` small digits whose units are at column x, leftwards;
 * the places before its first digit blank (0 is one 0 and blanks). */
void BankPad_DrawNumber(BankPad *pad, int value, int x, int y, int digits)
{
    for (int i = 0; i < digits; i++) {
        if (value == 0) {
            BankPad_PutDigit(pad, i == 0 ? 0 : BANK_PAD_DIGIT_BLANK, x, y);
        } else {
            BankPad_PutDigit(pad, value % 10, x, y);
            value /= 10;
        }
        x--;
    }
}
CLEAN_AS(func_ov130_02299a58, BankPad_DrawNumber)

/* func_ov130_02299ac0: `digits` small digits `digit`, from column x leftwards. */
void BankPad_FillDigits(BankPad *pad, int digit, int x, int y, int digits)
{
    for (int i = 0; i < digits; i++) {
        BankPad_PutDigit(pad, digit, x, y);
        x--;
    }
}
CLEAN_AS(func_ov130_02299ac0, BankPad_FillDigits)

/* func_ov130_02299af0: a big digit, two by two tiles, its top left at column x, row y; a blank
 * (BANK_PAD_DIGIT_BLANK) is the blank's pair of tiles on both rows. */
void BankPad_PutBigDigit(BankPad *pad, int digit, int x, int y)
{
    u16 tile;
    if (digit != BANK_PAD_DIGIT_BLANK) {
        tile = (u16) (digit * 4 + BANK_PAD_BIG_DIGIT_TILES);
    } else {
        tile = BANK_PAD_BIG_BLANK_TILE;
    }
    int index = x + y * 32;
    put_tile(pad->digits_screen, index, tile);
    put_tile(pad->digits_screen, index + 1, (u16) (tile + 1));
    tile = (u16) (tile + 2);
    if (digit == BANK_PAD_DIGIT_BLANK) {
        tile = BANK_PAD_BIG_BLANK_TILE;
    }
    put_tile(pad->digits_screen, index + 32, tile);
    put_tile(pad->digits_screen, index + 33, (u16) (tile + 1));
    BankPad_SetDirty(pad, BANK_PAD_DIRTY_DIGITS);
}
CLEAN_AS(func_ov130_02299af0, BankPad_PutBigDigit)

/* func_ov130_02299b88: `value` in `digits` big digits whose units are at column x, leftwards;
 * the places before its first digit, and a value of 0, all blank. */
void BankPad_DrawBigNumber(BankPad *pad, int value, int x, int y, int digits)
{
    for (int i = 0; i < digits; i++) {
        if (value == 0) {
            BankPad_PutBigDigit(pad, BANK_PAD_DIGIT_BLANK, x, y);
        } else {
            BankPad_PutBigDigit(pad, value % 10, x, y);
            value /= 10;
        }
        x -= 2;
    }
}
CLEAN_AS(func_ov130_02299b88, BankPad_DrawBigNumber)

/* func_ov130_02299bd8: `digits` big digits `digit`, from column x leftwards. */
void BankPad_FillBigDigits(BankPad *pad, int digit, int x, int y, int digits)
{
    for (int i = 0; i < digits; i++) {
        BankPad_PutBigDigit(pad, digit, x, y);
        x -= 2;
    }
}
CLEAN_AS(func_ov130_02299bd8, BankPad_FillBigDigits)

/* The amount `value` at row y: dashes while it is 0. Small digits (9) in layouts 2 and 3, big
 * ones (6) in layouts 0 and 1. */
static void draw_amount_row(BankPad *pad, int value, int x, int y, int dashes_when_zero)
{
    if (dashes_when_zero && value == 0) {
        if (pad->layout >= BANK_PAD_LAYOUT_TRANSFER) {
            BankPad_FillDigits(pad, BANK_PAD_DIGIT_DASH, x, y, 9);
        } else {
            BankPad_FillBigDigits(pad, BANK_PAD_DIGIT_DASH, x, y, 6);
        }
    } else if (pad->layout >= BANK_PAD_LAYOUT_TRANSFER) {
        BankPad_DrawNumber(pad, value, x, y, 9);
    } else {
        BankPad_DrawBigNumber(pad, value, x, y, 6);
    }
}

/* func_ov130_02299c08: the amounts drawn on the digit screen by the layout. The small layouts
 * show the amount alone (dashes while it is 0: two, or seven after a 0 and blanks); the others
 * the limit (kept as `shown_limit`), the amount below it and, in layouts 0 and 2, the result
 * below that (kept as `shown_result`): the current value plus the amount.
 * QUIRK: when paying the loan the result is the loan as it is, the amount not taken off. */
void BankPad_DrawAmounts(BankPad *pad)
{
    int x = data_ov130_0229a870[pad->layout];
    int y = data_ov130_0229a858[pad->layout];
    switch (pad->layout) {
        case BANK_PAD_LAYOUT_SMALL:
            if (pad->amount == 0) {
                BankPad_FillDigits(pad, BANK_PAD_DIGIT_DASH, x, y, 2);
            } else {
                BankPad_DrawNumber(pad, pad->amount, x, y, 2);
            }
            break;
        case BANK_PAD_LAYOUT_NUMBER:
            if (pad->amount == 0) {
                BankPad_DrawNumber(pad, 0, x, y, 9);
                BankPad_FillDigits(pad, BANK_PAD_DIGIT_DASH, x, y, 7);
            } else {
                BankPad_DrawNumber(pad, pad->amount, x, y, 7);
            }
            break;
        default:
            pad->shown_limit = pad->limit;
            draw_amount_row(pad, pad->shown_limit, x, y, 0);
            draw_amount_row(pad, pad->amount, x, y + 3, 1);
            if (bank_pad_is_wide(pad->layout)) {
                int result = pad->current;
                if (pad->kind != BANK_PAD_KIND_PAY_LOAN) {
                    result += pad->amount;
                }
                pad->shown_result = result;
                draw_amount_row(pad, pad->shown_result, x, y + 6, 0);
            }
            break;
    }
}
CLEAN_AS(func_ov130_02299c08, BankPad_DrawAmounts)

/* --- The keys --- */

/* func_ov130_02299d48: the pressed key acts. C clears the amount (sound 0x34 when it already
 * was 0); a digit is appended to the amount, which stops at `max_amount`: when that changes
 * nothing, sound 0x34, else the digit's sound and the amounts drawn again. */
void BankPad_PressKey(BankPad *pad)
{
    int amount = pad->amount;
    u8 key = pad->pressed_key;
    if (key == BANK_PAD_KEY_CLEAR) {
        if (BankPad_ClearAmount(pad) == 0) {
            SoundSys_PlaySe(BANK_PAD_SE_REFUSED);
        }
        return;
    }
    int entered = key + 10 * amount;
    if (entered > pad->max_amount) {
        entered = pad->max_amount;
    }
    if (entered == amount) {
        SoundSys_PlaySe(BANK_PAD_SE_REFUSED);
    } else {
        BankPad_PlayDigitSound(key);
        pad->amount = entered;
        BankPad_DrawAmounts(pad);
    }
}
CLEAN_AS(func_ov130_02299d48, BankPad_PressKey)

/* func_ov130_02299d98: the amount back to 0 with sound 0x2a and drawn again; 0 when it already
 * was 0. */
int BankPad_ClearAmount(BankPad *pad)
{
    if (pad->amount == 0) {
        return 0;
    }
    pad->amount = 0;
    BankPad_PlayClearSound();
    BankPad_DrawAmounts(pad);
    return 1;
}
CLEAN_AS(func_ov130_02299d98, BankPad_ClearAmount)

/* func_ov130_02299dbc */
void BankPad_PlayClearSound(void)
{
    SoundSys_PlaySe(BANK_PAD_SE_CLEAR);
}
CLEAN_AS(func_ov130_02299dbc, BankPad_PlayClearSound)

/* func_ov130_02299dc8: a digit's sound, the same for every digit. */
int BankPad_PlayDigitSound(int digit)
{
    (void) digit;
    return SoundSys_PlaySound2c(NULL);
}
CLEAN_AS(func_ov130_02299dc8, BankPad_PlayDigitSound)

/* func_ov130_02299dd4 */
int BankPad_Current(BankPad *pad)
{
    return pad->current;
}
CLEAN_AS(func_ov130_02299dd4, BankPad_Current)

/* func_ov130_02299dd8 */
int BankPad_Limit(BankPad *pad)
{
    return pad->limit;
}
CLEAN_AS(func_ov130_02299dd8, BankPad_Limit)

/* func_ov130_02299ddc */
int BankPad_Amount(BankPad *pad)
{
    return pad->amount;
}
CLEAN_AS(func_ov130_02299ddc, BankPad_Amount)

/* func_ov130_02299de0 */
void BankPad_SetRange(BankPad *pad, int max_amount, int limit, int current)
{
    pad->max_amount = max_amount;
    pad->limit = limit;
    pad->current = current;
}
CLEAN_AS(func_ov130_02299de0, BankPad_SetRange)

/* func_ov130_02299de8: the cells over the screens on the sub screen, moved down with the wipe
 * (`wipe_offset`): the layout's two frames (10 pixels lower for the teller's picture 3), then
 * the commas of the amounts of 1,000 and more and of 1,000,000 and more; layout 4 has none, the
 * wide layouts have three rows of them (amount, limit, result), the others two (amount, limit),
 * 8 pixels higher in layout 5. */
void BankPad_Draw(BankPad *pad, int wipe_offset)
{
    const OamEntry *frame;
    const OamEntry *keys;
    int y = wipe_offset + 0x60;
    if (bank_pad_is_wide(pad->layout)) {
        frame = data_ov130_0229ab20;
        keys = data_ov130_0229abf0;
    } else if (pad->layout == BANK_PAD_LAYOUT_SMALL) {
        frame = data_ov130_0229aae0;
        keys = data_ov130_0229abb0;
    } else {
        frame = data_ov130_0229aae0;
        keys = data_ov130_0229ab70;
    }
    int frame_y = y;
    if (pad->picture == 3) {
        frame_y += 10;
    }
    OamBuffer_DrawCell(1, frame, 0x80, frame_y, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    OamBuffer_DrawCell(1, keys, 0x80, frame_y, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);

    if (pad->layout == BANK_PAD_LAYOUT_SMALL) {
        return;
    }
    if (bank_pad_is_wide(pad->layout)) {
        if (pad->amount >= 1000) {
            OamBuffer_DrawObjAffine(1, data_ov130_0229ab40, 0x80, y, -1, 2, NULL);
        }
        if (pad->amount >= 1000000) {
            OamBuffer_DrawObjAffine(1, data_ov130_0229ab48, 0x80, y, -1, 2, NULL);
        }
        if (pad->shown_limit >= 1000) {
            OamBuffer_DrawObjAffine(1, data_ov130_0229ab50, 0x80, y, -1, 2, NULL);
        }
        if (pad->shown_limit >= 1000000) {
            OamBuffer_DrawObjAffine(1, data_ov130_0229ab58, 0x80, y, -1, 2, NULL);
        }
        if (pad->shown_result >= 1000) {
            OamBuffer_DrawObjAffine(1, data_ov130_0229ab60, 0x80, y, -1, 2, NULL);
        }
        if (pad->shown_result >= 1000000) {
            OamBuffer_DrawObjAffine(1, data_ov130_0229ab68, 0x80, y, -1, 2, NULL);
        }
        return;
    }
    if (pad->layout == BANK_PAD_LAYOUT_NUMBER) {
        y -= 8;
    }
    if (pad->amount >= 1000) {
        OamBuffer_DrawObjAffine(1, data_ov130_0229ab10, 0x80, y, -1, 2, NULL);
    }
    if (pad->amount >= 1000000) {
        OamBuffer_DrawObjAffine(1, data_ov130_0229ab18, 0x80, y, -1, 2, NULL);
    }
    if (pad->shown_limit >= 1000) {
        OamBuffer_DrawObjAffine(1, data_ov130_0229ab00, 0x80, y, -1, 2, NULL);
    }
    if (pad->shown_limit >= 1000000) {
        OamBuffer_DrawObjAffine(1, data_ov130_0229ab08, 0x80, y, -1, 2, NULL);
    }
}
CLEAN_AS(func_ov130_02299de8, BankPad_Draw)

/* func_ov130_0229a00c: the two frames of the pay layout alone, moved down with the wipe (for
 * the other bank screens). */
void BankPad_DrawPayCells(int wipe_offset)
{
    int y = wipe_offset + 0x60;
    OamBuffer_DrawCell(1, data_ov130_0229aae0, 0x80, y, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    OamBuffer_DrawCell(1, data_ov130_0229ab70, 0x80, y, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}
CLEAN_AS(func_ov130_0229a00c, BankPad_DrawPayCells)

/* func_ov130_0229a070 */
int BankPad_CursorOnOk(BankPad *pad)
{
    return pad->cursor_key == BANK_PAD_KEY_OK;
}
CLEAN_AS(func_ov130_0229a070, BankPad_CursorOnOk)

/* func_ov130_0229a080: the key under the cursor pressed (BankPad_StartPress); 0 when it is one
 * of the panel's buttons, which the scene handles. */
int BankPad_PressCursorKey(BankPad *pad)
{
    u8 key = pad->cursor_key;
    if (key == BANK_PAD_KEY_OK || key == BANK_PAD_KEY_CANCEL) {
        return 0;
    }
    pad->pressed_key = key;
    BankPad_StartPress(pad);
    return 1;
}
CLEAN_AS(func_ov130_0229a080, BankPad_PressCursorKey)

/* func_ov130_0229a0a4: the cursor moved by the d-pad's `keys` (up before down, left before
 * right; a move of each axis can come in the same frame); whether it went to another key. */
int BankPad_MoveCursor(BankPad *pad, int keys)
{
    if (keys == 0) {
        return 0;
    }
    u8 before = pad->cursor_key;
    if (KeyRepeat_HasUp(keys) != 0) {
        pad->cursor_key = data_ov130_0229a848[pad->cursor_key];
    } else if (KeyRepeat_HasDown(keys) != 0) {
        pad->cursor_key = data_ov130_0229a818[pad->cursor_key];
    }
    if (KeyRepeat_HasLeft(keys) != 0) {
        pad->cursor_key = data_ov130_0229a828[pad->cursor_key];
    } else if (KeyRepeat_HasRight(keys) != 0) {
        pad->cursor_key = data_ov130_0229a838[pad->cursor_key];
    }
    return before != pad->cursor_key;
}
CLEAN_AS(func_ov130_0229a0a4, BankPad_MoveCursor)

/* func_ov130_0229a124: the cursor is on the panel's OK or cancel button. */
int BankPad_CursorOnButton(BankPad *pad)
{
    return pad->cursor_key == BANK_PAD_KEY_OK || pad->cursor_key == BANK_PAD_KEY_CANCEL;
}
CLEAN_AS(func_ov130_0229a124, BankPad_CursorOnButton)

/* func_ov130_0229a138: the cursor's y over its key. */
u32 BankPad_CursorY(BankPad *pad)
{
    return data_ov130_0229a940[pad->cursor_key];
}
CLEAN_AS(func_ov130_0229a138, BankPad_CursorY)

/* func_ov130_0229a148: the cursor's x over its key, 0x40 to the right for the keypad's keys in
 * the wide layouts. */
u32 BankPad_CursorX(BankPad *pad)
{
    u8 key = pad->cursor_key;
    u32 x = data_ov130_0229a90c[key];
    if (bank_pad_is_wide(pad->layout) && key <= BANK_PAD_KEY_CLEAR) {
        x += 0x40;
    }
    return x;
}
CLEAN_AS(func_ov130_0229a148, BankPad_CursorX)

/* func_ov130_0229a168: a key shown up (C in its own palette). */
void BankPad_ShowKeyUp(BankPad *pad, int key)
{
    BankPad_SetKeyPalette(pad, (unsigned int) key,
                          key == BANK_PAD_KEY_CLEAR ? BANK_PAD_PALETTE_CLEAR_UP : BANK_PAD_PALETTE_KEY_UP);
}
CLEAN_AS(func_ov130_0229a168, BankPad_ShowKeyUp)

/* func_ov130_0229a17c: a key shown pressed. */
void BankPad_ShowKeyDown(BankPad *pad, int key)
{
    BankPad_SetKeyPalette(pad, (unsigned int) key, BANK_PAD_PALETTE_KEY_DOWN);
}
CLEAN_AS(func_ov130_0229a17c, BankPad_ShowKeyDown)

/* func_ov130_0229a188: the key's tiles on the key screen in `palette` (8 tiles to the right in
 * the wide layouts).
 * REQUIRES: key is 0-10 (the keypad's keys; the game reads past its tables for others). */
void BankPad_SetKeyPalette(BankPad *pad, unsigned int key, int palette)
{
    int left = data_ov130_0229a888[key];
    int right = data_ov130_0229a8b4[key];
    int top = data_ov130_0229a8e0[key];
    if (bank_pad_is_wide(pad->layout)) {
        left += 8;
        right += 8;
    }
    ScreenMap_SetPalette(pad->keys_screen, left, top, right, top + 1, (u32) palette);
    BankPad_SetDirty(pad, BANK_PAD_DIRTY_KEYS);
}
CLEAN_AS(func_ov130_0229a188, BankPad_SetKeyPalette)

/* func_ov130_0229a1dc: the whole keypad shown up: every key in the up palette, then C in its
 * own. */
void BankPad_ShowKeysUp(BankPad *pad)
{
    int left = bank_pad_is_wide(pad->layout) ? 18 : 10;
    ScreenMap_SetPalette(pad->keys_screen, left, 12, left + 12, 19, BANK_PAD_PALETTE_KEY_UP);
    BankPad_ShowKeyUp(pad, BANK_PAD_KEY_CLEAR);
    BankPad_SetDirty(pad, BANK_PAD_DIRTY_KEYS);
}
CLEAN_AS(func_ov130_0229a1dc, BankPad_ShowKeysUp)

/* func_ov130_0229a224: a frame of the held key's repeat: when its count runs out, the key acts
 * again (and every 2 frames after); whether it did. */
int BankPad_StepRepeat(BankPad *pad)
{
    if (pad->repeat_timer != 0) {
        pad->repeat_timer--;
        if (pad->repeat_timer == 0) {
            pad->repeat_timer = BANK_PAD_REPEAT_NEXT;
            BankPad_PressKey(pad);
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov130_0229a224, BankPad_StepRepeat)

/* func_ov130_0229a24c */
void BankPad_StopRepeat(BankPad *pad)
{
    pad->repeat_timer = 0;
}
CLEAN_AS(func_ov130_0229a24c, BankPad_StopRepeat)

/* func_ov130_0229a254: `pressed_key` pressed: shown pressed alone for 5 frames, its repeat
 * started (13 frames to the first), and its action. */
void BankPad_StartPress(BankPad *pad)
{
    BankPad_ShowKeysUp(pad);
    BankPad_ShowKeyDown(pad, pad->pressed_key);
    pad->repeat_timer = BANK_PAD_REPEAT_FIRST;
    pad->highlight_timer = BANK_PAD_HIGHLIGHT_FRAMES;
    BankPad_PressKey(pad);
}
CLEAN_AS(func_ov130_0229a254, BankPad_StartPress)

/* func_ov130_0229a278: the keypad's key at the pen's (x, y), kept as `pressed_key`; else
 * BANK_PAD_KEY_NONE (and `pressed_key` kept). The keypad is at (0x50, 0x60), 0x40 further
 * right in the wide layouts. */
int BankPad_KeyAt(BankPad *pad, int x, int y)
{
    int dx = x - 0x50;
    int dy = y - 0x60;
    if (bank_pad_is_wide(pad->layout)) {
        dx -= 0x40;
    }
    if (dx >= 0 && dx < 0x60 && dy >= 0 && dy < 0x40) {
        pad->pressed_key = data_ov130_0229a80c[(dx >> 5) + 3 * (dy >> 4)];
        return pad->pressed_key;
    }
    return BANK_PAD_KEY_NONE;
}
CLEAN_AS(func_ov130_0229a278, BankPad_KeyAt)

/* --- The screens and labels --- */

/* func_ov130_0229a2b4: each changed screen queued to be loaded into its layer (the whole
 * 0x800 bytes); it stays changed while its task cannot take it. */
void BankPad_LoadScreens(BankPad *pad)
{
    if (BankPad_IsDirty(pad, BANK_PAD_DIRTY_DIGITS)) {
        if (LayerTask_QueueScreen(&pad->tasks[0], (int) (uintptr_t) pad->digits_screen, pad->digits_layer,
                                  sizeof(pad->digits_screen), 0)) {
            BankPad_ClearDirty(pad, BANK_PAD_DIRTY_DIGITS);
        }
    }
    if (BankPad_IsDirty(pad, BANK_PAD_DIRTY_KEYS)) {
        if (LayerTask_QueueScreen(&pad->tasks[1], (int) (uintptr_t) pad->keys_screen, pad->keys_layer,
                                  sizeof(pad->keys_screen), 0)) {
            BankPad_ClearDirty(pad, BANK_PAD_DIRTY_KEYS);
        }
    }
}
CLEAN_AS(func_ov130_0229a2b4, BankPad_LoadScreens)

/* func_ov130_0229a32c: a frame's start: the labels closed, the screens' tasks ended, and the
 * pressed key's highlight counted down; when it runs out the key is shown up again, unless it
 * still repeats (then it is counted again the next frame). */
void BankPad_BeginFrame(BankPad *pad)
{
    BankPad_CloseLabels(pad);
    LayerTask_End(&pad->tasks[0]);
    LayerTask_End(&pad->tasks[1]);
    if (pad->highlight_timer != 0) {
        pad->highlight_timer--;
        if (pad->highlight_timer == 0) {
            if (pad->repeat_timer != 0) {
                pad->highlight_timer = 1;
            } else {
                BankPad_ShowKeyUp(pad, pad->pressed_key);
            }
        }
    }
}
CLEAN_AS(func_ov130_0229a32c, BankPad_BeginFrame)

/* func_ov130_0229a378: the labels closed and the screens' tasks ended. */
void BankPad_Teardown(BankPad *pad)
{
    BankPad_CloseLabels(pad);
    LayerTask_End(&pad->tasks[0]);
    LayerTask_End(&pad->tasks[1]);
}
CLEAN_AS(func_ov130_0229a378, BankPad_Teardown)

/* func_ov130_0229a3a0: the teller's picture loaded and the teller's message of the kind shown in
 * a label on layer 8. */
void BankPad_ShowMessage(BankPad *pad)
{
    BankPad_LoadPicture(pad->picture);
    TextLabel *label = BankPad_NextLabel(pad);
    TextLabel_LoadMenuMessage(label, (char) data_ov130_0229a7fc[pad->kind]);
    TextLabel_OpenStyledBox2(label, 8, 0x14c, 14, 15, 0, 0);
    TextLabel_Show(label, 1, 0);
}
CLEAN_AS(func_ov130_0229a3a0, BankPad_ShowMessage)

/* func_ov130_0229a3f0: the objects of the sub screen (layer 8): their palettes and characters,
 * then the teller's picture `picture` (the fifth of its file it is in, six rows of 0xc0 bytes
 * 0x400 apart, to characters 0x15a-0x15f, 0x17a-0x17f and so on) and its palette 4. */
int BankPad_LoadPicture(int picture)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadPalettesFromFile(data_ov130_0229ac30, heap, 8, 4, 4, 0xe);
    DisplayLayer_LoadCharsFromFile(data_ov130_0229ac44, heap, 8, 0xc0, 0xc0, 0x15f);
    DisplayLayer_LoadCharsFromFile(data_ov130_0229ac58, heap, 8, 0x160, 0x160, 0x1ff);
    u32 size;
    u8 *file = RomFile_Load(data_ov130_0229a980[picture / 5], heap, -4, &size);
    u8 *row = file + (picture % 5) * 0xc0;
    u32 first = 0x15a;
    for (int i = 0; i < 6; i++) {
        DisplayLayer_LoadChars((u32) (uintptr_t) row, 8, first, first, first + 5);
        row += 0x400;
        first += 0x20;
    }
    Heap_Free(heap, file);
    return DisplayLayer_LoadPaletteFromFile(data_ov130_0229ac6c, heap, 8, picture, 4);
}
CLEAN_AS(func_ov130_0229a3f0, BankPad_LoadPicture)

/* The next label showing menu message `message` in a box of the key screen's layer (the box's
 * place `box_a`, `box_b` as TextLabel_OpenStyledBox2 takes them). */
static void show_caption(BankPad *pad, int message, int box_a, int box_b)
{
    TextLabel *label = BankPad_NextLabel(pad);
    TextLabel_LoadMenuMessage(label, (char) message);
    TextLabel_OpenStyledBox2(label, pad->keys_layer, box_a, box_b, 0xf, 0, 0);
    TextLabel_Show(label, 1, 0);
}

/* func_ov130_0229a4c8: the screens of the layout: the background's characters for the digit
 * layer, the digit screen read (with a part in palette 10 for the kinds that move bells to or
 * from the savings or loan) and loaded, the key screen read and loaded; then the captions
 * (4 for the wide layouts, else 3), the keypad shown up and the amounts drawn. */
void BankPad_Load(BankPad *pad)
{
    BankPad_LoadBackground(pad->digits_layer);
    RomFile_Read(data_ov130_0229aa90[pad->layout], pad->digits_screen, sizeof(pad->digits_screen));
    switch (pad->kind) {
        case BANK_PAD_KIND_PAY_LOAN:
        case BANK_PAD_KIND_DEPOSIT:
            ScreenMap_SetPalette(pad->digits_screen, 2, 8, 0xd, 9, 0xa);
            break;
        case BANK_PAD_KIND_WITHDRAW:
            ScreenMap_SetPalette(pad->digits_screen, 2, 2, 0xd, 3, 0xa);
            break;
    }
    DisplayLayer_LoadScreen(pad->digits_screen, pad->digits_layer, sizeof(pad->digits_screen), 0);
    RomFile_Read(data_ov130_0229aa78[pad->layout], pad->keys_screen, sizeof(pad->keys_screen));
    DisplayLayer_LoadScreen(pad->keys_screen, pad->keys_layer, sizeof(pad->keys_screen), 0);

    show_caption(pad, pad->kind == BANK_PAD_KIND_SMALL_NUMBER ? 0x51 : 0xb8, 0xec, 4);
    int limit_message;
    switch (pad->kind) {
        case BANK_PAD_KIND_WITHDRAW:
            limit_message = 0x59;
            break;
        case BANK_PAD_KIND_NUMBER:
            limit_message = 0x50;
            break;
        default:
            limit_message = 0x54;
            break;
    }
    show_caption(pad, limit_message, 0xb0, 0xa);
    show_caption(pad, data_ov130_0229a804[pad->kind], 0xc4, 0xa);
    if (bank_pad_is_wide(pad->layout)) {
        show_caption(pad, data_ov130_0229a7f4[pad->kind], 0xd8, 0xa);
    }
    BankPad_ShowKeysUp(pad);
    BankPad_DrawAmounts(pad);
}
CLEAN_AS(func_ov130_0229a4c8, BankPad_Load)

/* func_ov130_0229a678: the background's characters ("menu/bank/bg0.bch" to 0x10-0xff,
 * "bg1.bch" to 0x100-0x1a9) and palettes 1-13 ("bg.bpl") of `layer`. */
int BankPad_LoadBackground(int layer)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadCharsFromFile(data_ov130_0229ac80, heap, layer, 0x10, 0x10, 0xff);
    DisplayLayer_LoadCharsFromFile(data_ov130_0229ac94, heap, layer, 0x100, 0x100, 0x1a9);
    return DisplayLayer_LoadPalettesFromFile(data_ov130_0229aca8, heap, layer, 1, 1, 0xd);
}
CLEAN_AS(func_ov130_0229a678, BankPad_LoadBackground)

/* --- Setup, construction --- */

/* func_ov130_0229a6d8: the pad set up for a kind of entry on two layers: the layout and the
 * teller's picture by the kind (both kept for a kind not listed), no label, the cursor on C, no
 * key pressed, the amounts 0. The sound system's byte 0x71 is 0 when there is a current player
 * whose byte 0x1c is 0, else 1. */
void BankPad_Setup(BankPad *pad, u8 kind, u8 digits_layer, u8 keys_layer)
{
    pad->dirty = 0;
    pad->kind = kind;
    switch (pad->kind) {
        case BANK_PAD_KIND_PAY_LOAN:
            pad->layout = BANK_PAD_LAYOUT_TRANSFER;
            pad->picture = 0;
            break;
        case BANK_PAD_KIND_DEPOSIT:
            pad->layout = BANK_PAD_LAYOUT_TRANSFER;
            pad->picture = 5;
            break;
        case BANK_PAD_KIND_WITHDRAW:
            pad->layout = BANK_PAD_LAYOUT_TRANSFER;
            pad->picture = 1;
            break;
        case BANK_PAD_KIND_PAY:
            pad->layout = BANK_PAD_LAYOUT_PAY;
            pad->picture = 2;
            break;
        case BANK_PAD_KIND_NUMBER:
            pad->layout = BANK_PAD_LAYOUT_NUMBER;
            pad->picture = 3;
            break;
        case BANK_PAD_KIND_POCKET_BELLS:
            pad->layout = BANK_PAD_LAYOUT_PAY;
            pad->picture = 4;
            break;
        case BANK_PAD_KIND_SMALL_NUMBER:
            pad->layout = BANK_PAD_LAYOUT_SMALL;
            pad->picture = 6;
            break;
        default:
            break;
    }
    pad->digits_layer = digits_layer;
    pad->keys_layer = keys_layer;
    BankPad_CloseLabels(pad);
    pad->cursor_key = BANK_PAD_KEY_CLEAR;
    pad->pressed_key = BANK_PAD_KEY_NONE;
    pad->highlight_timer = 0;
    pad->repeat_timer = 0;
    pad->amount = 0;
    pad->max_amount = 0;
    pad->limit = 0;
    pad->current = 0;
    u8 *record = PlayerRecords_Current();
    if (record != NULL && PlayerId_Byte1c((const s8 *) (void *) PlayerRecord_Player(record)) == 0) {
        SoundSys_SetByte71(0);
    } else {
        SoundSys_SetByte71(1);
    }
}
CLEAN_AS(func_ov130_0229a6d8, BankPad_Setup)

/* func_ov130_0229a790: the labels destroyed (the screens' tasks need nothing). */
BankPad *BankPad_Destroy(BankPad *pad)
{
    __cxa_vec_cleanup(pad->labels, BANK_PAD_LABELS, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    return pad;
}
CLEAN_AS(func_ov130_0229a790, BankPad_Destroy)

/* func_ov130_0229a7ac: the labels constructed, then the two screens' tasks. */
BankPad *BankPad_Construct(BankPad *pad)
{
    __cxa_vec_ctor(pad->labels, BANK_PAD_LABELS, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070c08,
                   (void (*)(void *))(uintptr_t) func_02070be8);
    for (int i = 0; i < 2; i++) {
        LayerTask_Construct(&pad->tasks[i]);
    }
    return pad;
}
CLEAN_AS(func_ov130_0229a7ac, BankPad_Construct)
