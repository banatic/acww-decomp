/* The software keyboard's keys (soft_keyboard.h): their codes, the key under the pen, and
 * their looks (the palettes of their OBJs in the page's cell): normal, pressed or disabled. */
#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "main/oam_buffer.h"
#include "soft_keyboard.h"

/* The codes of the layouts' keys: English lower case (from key 0x3b), upper case (from 0x3b),
 * symbols (from 0x70), Hangul (from 0xc9). */
extern const u16 data_ov095_0229e874[SOFT_KEYBOARD_KEY_ENGLISH_LAST - SOFT_KEYBOARD_KEY_ENGLISH_FIRST + 1];
extern const s16 data_ov095_0229e8e0[SOFT_KEYBOARD_KEY_ENGLISH_LAST - SOFT_KEYBOARD_KEY_ENGLISH_FIRST + 1];
extern const s16 data_ov095_0229e774[SOFT_KEYBOARD_KEY_SYMBOLS_LAST - SOFT_KEYBOARD_KEY_SYMBOLS_FIRST + 1];
extern const s16 data_ov095_0229e7b8[SOFT_KEYBOARD_KEY_HANGUL_LAST - SOFT_KEYBOARD_KEY_HANGUL_FIRST + 1];

/* The key of each SoftKeyboardSpecial on the English, symbols and Hangul pages (0x110 is no
 * key). */
extern const int data_ov095_0229d050[SOFT_KEYBOARD_SPECIALS];
extern const int data_ov095_0229d088[SOFT_KEYBOARD_SPECIALS];
extern const int data_ov095_0229d0c0[SOFT_KEYBOARD_SPECIALS];

/* The last OBJ of a cell has this in its fourth halfword (main/oam_buffer.h). */
#define SOFT_KEYBOARD_LOOKS_MAX 100

/* `value` shifted as an ARM register shift does: by the low byte of `amount`, 0 from 32 up. */
static u32 soft_keyboard_lsl(u32 value, u32 amount)
{
    amount &= 0xff;
    return amount < 32 ? value << amount : 0;
}

/* An OBJ's palette set (its attribute 2's bits 12-15). */
static void soft_keyboard_set_obj_palette(OamEntry *obj, int palette)
{
    obj->attr2 = (u16) ((obj->attr2 & 0x0fff) | ((palette & 0xf) << 12));
}

/* The table of the page's special keys, or NULL. */
static const int *soft_keyboard_specials(SoftKeyboard *kb)
{
    switch (kb->page) {
        case SOFT_KEYBOARD_PAGE_ENGLISH:
            return data_ov095_0229d050;
        case SOFT_KEYBOARD_PAGE_SYMBOLS:
            return data_ov095_0229d088;
        case SOFT_KEYBOARD_PAGE_HANGUL:
            return data_ov095_0229d0c0;
        default:
            return NULL;
    }
}

/* --- Codes --- */

/* func_ov095_0229c448: the code of `key` in `layout` (from 9 up: the loaded layout): the code of
 * a key around the pages, else the layout's character, else SOFT_KEYBOARD_CODE_SPACE. */
int SoftKeyboard_KeyCode(SoftKeyboard *kb, int key, unsigned int layout)
{
    int code;

    if (layout >= SOFT_KEYBOARD_LAYOUTS) {
        layout = kb->layout;
    }
    code = SoftKeyboard_OutsideKeyCode(kb, key);
    if (code >= 0) {
        return code;
    }
    switch (layout) {
        case SOFT_KEYBOARD_LAYOUT_ENGLISH_LOWER:
            return SoftKeyboard_LowerKeyCode(kb, key);
        case SOFT_KEYBOARD_LAYOUT_ENGLISH_UPPER:
            return SoftKeyboard_UpperKeyCode(kb, key);
        case SOFT_KEYBOARD_LAYOUT_SYMBOLS:
            return SoftKeyboard_SymbolKeyCode(kb, key);
        case SOFT_KEYBOARD_LAYOUT_HANGUL:
            return SoftKeyboard_HangulKeyCode(kb, key);
        default:
            return SOFT_KEYBOARD_CODE_SPACE;
    }
}
CLEAN_AS(func_ov095_0229c448, SoftKeyboard_KeyCode)

/* func_ov095_0229c4bc: a Hangul key's code, 0 for another key.
 * QUIRK: the codes are read signed: a full-width one (0xff01-0xff5e) comes back negative. */
int SoftKeyboard_HangulKeyCode(SoftKeyboard *kb, int key)
{
    (void) kb;
    if (key >= SOFT_KEYBOARD_KEY_HANGUL_FIRST && key <= SOFT_KEYBOARD_KEY_HANGUL_LAST) {
        return data_ov095_0229e7b8[key - SOFT_KEYBOARD_KEY_HANGUL_FIRST];
    }
    return 0;
}
CLEAN_AS(func_ov095_0229c4bc, SoftKeyboard_HangulKeyCode)

/* func_ov095_0229c4d8: a symbol key's code, 0 for another key.
 * QUIRK: read signed, as SoftKeyboard_HangulKeyCode. */
int SoftKeyboard_SymbolKeyCode(SoftKeyboard *kb, int key)
{
    (void) kb;
    if (key >= SOFT_KEYBOARD_KEY_SYMBOLS_FIRST && key <= SOFT_KEYBOARD_KEY_SYMBOLS_LAST) {
        return data_ov095_0229e774[key - SOFT_KEYBOARD_KEY_SYMBOLS_FIRST];
    }
    return 0;
}
CLEAN_AS(func_ov095_0229c4d8, SoftKeyboard_SymbolKeyCode)

/* func_ov095_0229c4f4: an English key's upper case code, 0 for another key.
 * QUIRK: read signed, as SoftKeyboard_HangulKeyCode (the lower case ones are not). */
int SoftKeyboard_UpperKeyCode(SoftKeyboard *kb, int key)
{
    (void) kb;
    if (key >= SOFT_KEYBOARD_KEY_ENGLISH_FIRST && key <= SOFT_KEYBOARD_KEY_ENGLISH_LAST) {
        return data_ov095_0229e8e0[key - SOFT_KEYBOARD_KEY_ENGLISH_FIRST];
    }
    return 0;
}
CLEAN_AS(func_ov095_0229c4f4, SoftKeyboard_UpperKeyCode)

/* func_ov095_0229c510: an English key's lower case code, 0 for another key. */
u16 SoftKeyboard_LowerKeyCode(SoftKeyboard *kb, int key)
{
    (void) kb;
    if (key >= SOFT_KEYBOARD_KEY_ENGLISH_FIRST && key <= SOFT_KEYBOARD_KEY_ENGLISH_LAST) {
        return data_ov095_0229e874[key - SOFT_KEYBOARD_KEY_ENGLISH_FIRST];
    }
    return 0;
}
CLEAN_AS(func_ov095_0229c510, SoftKeyboard_LowerKeyCode)

/* func_ov095_0229c52c: the code of a key around the pages (0xf7-0x10f): the key plus 0xf; -1
 * for another key. */
int SoftKeyboard_OutsideKeyCode(SoftKeyboard *kb, int key)
{
    (void) kb;
    if (key >= SOFT_KEYBOARD_KEY_CHAT_F7 && key <= SOFT_KEYBOARD_KEY_EMOTION_LAST) {
        return key + SOFT_KEYBOARD_CODE_OFFSET;
    }
    return -1;
}
CLEAN_AS(func_ov095_0229c52c, SoftKeyboard_OutsideKeyCode)

/* --- The pen --- */

/* func_ov095_0229c548 */
int SoftKeyboard_PressedKey(SoftKeyboard *kb)
{
    return kb->pressed_key;
}
CLEAN_AS(func_ov095_0229c548, SoftKeyboard_PressedKey)

/* func_ov095_0229c54c: the key at (x, y) taken as the pressed key: a side button, else a key of
 * the page (y measured 8 pixels lower outside kind 0's layout, 0xff from 0xf7 up); -1 for none
 * or a disabled key. */
int SoftKeyboard_KeyAt(SoftKeyboard *kb, int x, u8 y)
{
    int key;

    kb->pressed_key = SOFT_KEYBOARD_KEY_NONE;
    key = SoftKeyboard_SideButtonAt(kb, (unsigned int) x, y);
    if (key == SOFT_KEYBOARD_KEY_NONE) {
        if (SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_CHAT_LAYOUT) == 0) {
            if (y < 0xf7) {
                y = (u8) (y + 8);
            } else {
                y = 0xff;
            }
        }
        switch (kb->page) {
            case SOFT_KEYBOARD_PAGE_NONE:
                break;
            case SOFT_KEYBOARD_PAGE_ENGLISH:
                key = SoftKeyboard_EnglishKeyAt(kb, (unsigned int) x, y);
                if (key == 0x6a || key == 0x6c || key == 0x6d) {
                    key = SOFT_KEYBOARD_KEY_ENGLISH_SPACE;
                }
                break;
            case SOFT_KEYBOARD_PAGE_SYMBOLS:
                key = SoftKeyboard_SymbolKeyAt(kb, (unsigned int) x, y);
                break;
            case SOFT_KEYBOARD_PAGE_3:
                break;
            case SOFT_KEYBOARD_PAGE_HANGUL:
                key = SoftKeyboard_HangulKeyAt(kb, (u16) x, y);
                break;
            default:
                return SOFT_KEYBOARD_KEY_NONE;
        }
    }
    if (SoftKeyboard_IsKeyDisabled(kb, key) != 0) {
        return SOFT_KEYBOARD_KEY_NONE;
    }
    kb->pressed_key = key;
    return key;
}
CLEAN_AS(func_ov095_0229c54c, SoftKeyboard_KeyAt)

/* func_ov095_0229c5fc: the side button at (x, y): left of x 0x30 or right of 0xd0, in the tab
 * row (y 0x48-0x50, or 0x50-0x58 in kind 0's layout); -1 for none. */
int SoftKeyboard_SideButtonAt(SoftKeyboard *kb, unsigned int x, unsigned int y)
{
    unsigned int top = SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_CHAT_LAYOUT) != 0 ? 0x50 : 0x48;

    if (y < top || y > top + 8) {
        return SOFT_KEYBOARD_KEY_NONE;
    }
    if (x < 0x30) {
        return SOFT_KEYBOARD_KEY_SIDE_LEFT;
    }
    if (x > 0xd0) {
        return SOFT_KEYBOARD_KEY_SIDE_RIGHT;
    }
    return SOFT_KEYBOARD_KEY_NONE;
}
CLEAN_AS(func_ov095_0229c5fc, SoftKeyboard_SideButtonAt)

/* func_ov095_0229c654: the Hangul key at (x, y): five rows of 16 pixels from y 0x60, keys 20
 * pixels wide; -1 for none. */
int SoftKeyboard_HangulKeyAt(SoftKeyboard *kb, u16 x, u16 y)
{
    (void) kb;
    if (y < 0x60 || y >= 0xb0) {
        return SOFT_KEYBOARD_KEY_NONE;
    }
    if (y < 0x70) {
        if (x < 4 || x >= 0xcc) {
            return SOFT_KEYBOARD_KEY_NONE;
        }
        return (x - 4) / 20 + 0xc9;
    }
    if (y < 0x80) {
        if (x < 0xc) {
            return SOFT_KEYBOARD_KEY_NONE;
        }
        if (x < 0xd4) {
            return (x - 0xc) / 20 + 0xd3;
        }
        if (x < 0xfc) {
            return SOFT_KEYBOARD_KEY_HANGUL_BACKSPACE;
        }
        return SOFT_KEYBOARD_KEY_NONE;
    }
    if (y < 0x90) {
        if (x < 0x18) {
            return SOFT_KEYBOARD_KEY_NONE;
        }
        if (x < 0xcc) {
            return (x - 0x18) / 20 + 0xde;
        }
        if (x < 0xfc) {
            return SOFT_KEYBOARD_KEY_HANGUL_NEWLINE;
        }
        return SOFT_KEYBOARD_KEY_NONE;
    }
    if (y < 0xa0) {
        if (x < 0x20 || x >= 0xe8) {
            return SOFT_KEYBOARD_KEY_NONE;
        }
        return (x - 0x20) / 20 + 0xe8;
    }
    if (x < 0x28) {
        return SOFT_KEYBOARD_KEY_NONE;
    }
    if (x < 0x3c) {
        return 0xf2;
    }
    if (x < 0x50) {
        return 0xf3;
    }
    if (x < 0xa8) {
        return SOFT_KEYBOARD_KEY_HANGUL_SPACE;
    }
    if (x < 0xbc) {
        return 0xf5;
    }
    if (x < 0xd0) {
        return 0xf6;
    }
    return SOFT_KEYBOARD_KEY_NONE;
}
CLEAN_AS(func_ov095_0229c654, SoftKeyboard_HangulKeyAt)

/* func_ov095_0229c750: the symbol key at (x, y): the grid's three rows of 16 pixels from y
 * 0x68, keys 20 pixels wide from x 8, the keys right of it, and the space below; -1 for none. */
int SoftKeyboard_SymbolKeyAt(SoftKeyboard *kb, unsigned int x, unsigned int y)
{
    (void) kb;
    if (y < 0x68 || y >= 0xa8) {
        return SOFT_KEYBOARD_KEY_NONE;
    }
    if (y >= 0x98) {
        if (x < 0x50 || x >= 0xb0) {
            return SOFT_KEYBOARD_KEY_NONE;
        }
        return SOFT_KEYBOARD_KEY_SYMBOLS_LAST;
    }
    if (x < 8 || x >= 0xf8) {
        return SOFT_KEYBOARD_KEY_NONE;
    }
    if (x < 0xd0) {
        return (int) (x - 8) / 20 + (int) ((y - 0x68) >> 4) * 10 + SOFT_KEYBOARD_KEY_SYMBOLS_FIRST;
    }
    if (y >= 0x78) {
        return 0x90;
    }
    if (x < 0xe4) {
        return 0x8e;
    }
    return 0x8f;
}
CLEAN_AS(func_ov095_0229c750, SoftKeyboard_SymbolKeyAt)

/* func_ov095_0229c7c8: the English key at (x, y): five rows of 16 pixels from y 0x60, keys 20
 * pixels wide; the space bar's keys 0x6a-0x6d all give 0x6b; -1 for none. */
int SoftKeyboard_EnglishKeyAt(SoftKeyboard *kb, unsigned int x, unsigned int y)
{
    (void) kb;
    if (y < 0x60 || y >= 0xb0) {
        return SOFT_KEYBOARD_KEY_NONE;
    }
    if (y < 0x70) {
        if (x < 4 || x >= 0xf4) {
            return SOFT_KEYBOARD_KEY_NONE;
        }
        return (int) (x - 4) / 20 + 0x3b;
    }
    if (y < 0x80) {
        if (x < 0xc || x >= 0xfc) {
            return SOFT_KEYBOARD_KEY_NONE;
        }
        if (x >= 0xd4) {
            return SOFT_KEYBOARD_KEY_ENGLISH_BACKSPACE;
        }
        return (int) (x - 0xc) / 20 + 0x47;
    }
    if (y < 0x90) {
        if (x < 4) {
            return SOFT_KEYBOARD_KEY_NONE;
        }
        if (x < 0x18) {
            return SOFT_KEYBOARD_KEY_ENGLISH_CAPS;
        }
        if (x >= 0xfc) {
            return SOFT_KEYBOARD_KEY_NONE;
        }
        if (x >= 0xcc) {
            return SOFT_KEYBOARD_KEY_ENGLISH_NEWLINE;
        }
        return (int) (x - 0x18) / 20 + 0x53;
    }
    if (y < 0xa0) {
        if (x < 4) {
            return SOFT_KEYBOARD_KEY_NONE;
        }
        if (x < 0x20) {
            return SOFT_KEYBOARD_KEY_ENGLISH_SHIFT;
        }
        if (x >= 0xe8) {
            return SOFT_KEYBOARD_KEY_NONE;
        }
        return (int) (x - 0x20) / 20 + 0x5e;
    }
    if (x < 0x18) {
        return SOFT_KEYBOARD_KEY_NONE;
    }
    if (x >= 0x40 && x < 0xcc) {
        return SOFT_KEYBOARD_KEY_ENGLISH_SPACE;
    }
    if (x < 0x54) {
        return (int) (x - 0x18) / 20 + 0x68;
    }
    if (x >= 0xf4) {
        return SOFT_KEYBOARD_KEY_NONE;
    }
    return (int) (x - 0xa4) / 20 + 0x6c;
}
CLEAN_AS(func_ov095_0229c7c8, SoftKeyboard_EnglishKeyAt)

/* --- Looks --- */

/* func_ov095_0229c8e4 */
void SoftKeyboard_ShowKeyPressed(SoftKeyboard *kb, int key)
{
    SoftKeyboard_SetKeyPalette(kb, key, SOFT_KEYBOARD_PALETTE_PRESSED);
}
CLEAN_AS(func_ov095_0229c8e4, SoftKeyboard_ShowKeyPressed)

/* func_ov095_0229c8f0: `key` of the page shown in `palette`; the screen marked changed. */
void SoftKeyboard_SetKeyPalette(SoftKeyboard *kb, int key, int palette)
{
    switch (kb->page) {
        case SOFT_KEYBOARD_PAGE_ENGLISH:
            SoftKeyboard_SetEnglishKeyPalette(kb, key, palette);
            break;
        case SOFT_KEYBOARD_PAGE_SYMBOLS:
            SoftKeyboard_SetSymbolKeyPalette(kb, key, palette);
            break;
        case SOFT_KEYBOARD_PAGE_HANGUL:
            SoftKeyboard_SetHangulKeyPalette(kb, key, palette);
            break;
        default:
            break;
    }
    SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_SCREEN_DIRTY);
}
CLEAN_AS(func_ov095_0229c8f0, SoftKeyboard_SetKeyPalette)

/* func_ov095_0229c930: a side button's palette kept (SoftKeyboard_DrawSideButtons); answers 0.
 * REQUIRES: `palette` is 12, 13 or 14 (for another the ROM's code stores a register it never
 * set). */
int SoftKeyboard_SetSideButtonPalette(SoftKeyboard *kb, int key, int palette)
{
    switch (key) {
        case SOFT_KEYBOARD_KEY_SIDE_LEFT:
            kb->side_palette[0] = (u8) palette;
            break;
        case SOFT_KEYBOARD_KEY_SIDE_RIGHT:
            kb->side_palette[1] = (u8) palette;
            break;
        default:
            break;
    }
    return 0;
}
CLEAN_AS(func_ov095_0229c930, SoftKeyboard_SetSideButtonPalette)

/* func_ov095_0229c974: a key of the Hangul page (or a side button) shown in `palette`. The cell
 * has an OBJ per key in key order, with the gaps of row ends; the backspace has two OBJs, the
 * newline three and the space four. */
void SoftKeyboard_SetHangulKeyPalette(SoftKeyboard *kb, int key, int palette)
{
    OamEntry *looks;
    int obj;
    int i;

    if (SoftKeyboard_SetSideButtonPalette(kb, key, palette) != 0) {
        return;
    }
    if (key < SOFT_KEYBOARD_KEY_HANGUL_FIRST || key > SOFT_KEYBOARD_KEY_HANGUL_LAST) {
        return;
    }
    looks = SoftKeyboard_KeyLooks(kb);
    if (key < SOFT_KEYBOARD_KEY_HANGUL_BACKSPACE) {
        obj = key - 0xc9;
    } else if (key == SOFT_KEYBOARD_KEY_HANGUL_BACKSPACE) {
        soft_keyboard_set_obj_palette(&looks[0x14], palette);
        soft_keyboard_set_obj_palette(&looks[0x15], palette);
        return;
    } else if (key < SOFT_KEYBOARD_KEY_HANGUL_NEWLINE) {
        obj = key - 0xc8;
    } else if (key == SOFT_KEYBOARD_KEY_HANGUL_NEWLINE) {
        for (i = 0x1f; i <= 0x21; i++) {
            soft_keyboard_set_obj_palette(&looks[i], palette);
        }
        return;
    } else if (key == SOFT_KEYBOARD_KEY_HANGUL_SPACE) {
        for (i = 0x2e; i <= 0x31; i++) {
            soft_keyboard_set_obj_palette(&looks[i], palette);
        }
        return;
    } else if (key < SOFT_KEYBOARD_KEY_HANGUL_SPACE) {
        obj = key - 0xc6;
    } else {
        obj = key - 0xc3;
    }
    soft_keyboard_set_obj_palette(&looks[obj], palette);
}
CLEAN_AS(func_ov095_0229c974, SoftKeyboard_SetHangulKeyPalette)

/* func_ov095_0229ca64: a key of the symbols page (or a side button) shown in `palette`. Keys
 * 0x8e and 0x8f follow row 0's OBJs, 0x90 (two OBJs) row 1's and the space (five) row 2's. */
void SoftKeyboard_SetSymbolKeyPalette(SoftKeyboard *kb, int key, int palette)
{
    OamEntry *looks;
    int obj;

    if (SoftKeyboard_SetSideButtonPalette(kb, key, palette) != 0) {
        return;
    }
    if (key < SOFT_KEYBOARD_KEY_SYMBOLS_FIRST || key > SOFT_KEYBOARD_KEY_SYMBOLS_LAST) {
        return;
    }
    looks = SoftKeyboard_KeyLooks(kb);
    if (key <= 0x79) {
        obj = key - 0x70;
    } else if (key <= 0x83) {
        obj = key - 0x6e;
    } else if (key <= SOFT_KEYBOARD_KEY_SYMBOLS_GRID_LAST) {
        obj = key - 0x6c;
    } else {
        switch (key) {
            case 0x8e:
                obj = 0xa;
                break;
            case 0x8f:
                obj = 0xb;
                break;
            case 0x90:
                obj = 0x16;
                soft_keyboard_set_obj_palette(&looks[0x17], palette);
                break;
            default:
                obj = 0x22;
                soft_keyboard_set_obj_palette(&looks[0x23], palette);
                soft_keyboard_set_obj_palette(&looks[0x24], palette);
                soft_keyboard_set_obj_palette(&looks[0x25], palette);
                soft_keyboard_set_obj_palette(&looks[0x26], palette);
                break;
        }
    }
    soft_keyboard_set_obj_palette(&looks[obj], palette);
}
CLEAN_AS(func_ov095_0229ca64, SoftKeyboard_SetSymbolKeyPalette)

/* func_ov095_0229cb5c: a key of the English page (or a side button) shown in `palette`. The
 * backspace and the newline have two OBJs, the caps one, the space six; keys 0x6a, 0x6c and
 * 0x6d have none. */
void SoftKeyboard_SetEnglishKeyPalette(SoftKeyboard *kb, int key, int palette)
{
    OamEntry *looks;
    int obj;

    if (SoftKeyboard_SetSideButtonPalette(kb, key, palette) != 0) {
        return;
    }
    if (key < SOFT_KEYBOARD_KEY_ENGLISH_FIRST || key > SOFT_KEYBOARD_KEY_ENGLISH_LAST) {
        return;
    }
    looks = SoftKeyboard_KeyLooks(kb);
    if (key < SOFT_KEYBOARD_KEY_ENGLISH_BACKSPACE) {
        obj = key - 0x3b;
    } else if (key == SOFT_KEYBOARD_KEY_ENGLISH_BACKSPACE) {
        obj = 0x16;
        soft_keyboard_set_obj_palette(&looks[0x17], palette);
    } else if (key < SOFT_KEYBOARD_KEY_ENGLISH_NEWLINE) {
        obj = key - 0x3a;
    } else if (key == SOFT_KEYBOARD_KEY_ENGLISH_NEWLINE) {
        obj = 0x22;
        soft_keyboard_set_obj_palette(&looks[0x23], palette);
        soft_keyboard_set_obj_palette(&looks[0x24], palette);
    } else if (key <= 0x69) {
        obj = key - 0x38;
    } else if (key == SOFT_KEYBOARD_KEY_ENGLISH_SPACE) {
        obj = 0x32;
        soft_keyboard_set_obj_palette(&looks[0x33], palette);
        soft_keyboard_set_obj_palette(&looks[0x34], palette);
        soft_keyboard_set_obj_palette(&looks[0x35], palette);
        soft_keyboard_set_obj_palette(&looks[0x36], palette);
        soft_keyboard_set_obj_palette(&looks[0x37], palette);
    } else if (key >= 0x6e) {
        obj = key - 0x36;
    } else {
        return;
    }
    soft_keyboard_set_obj_palette(&looks[obj], palette);
}
CLEAN_AS(func_ov095_0229cb5c, SoftKeyboard_SetEnglishKeyPalette)

/* func_ov095_0229cc9c: the shift's state shown: a shift is let go outside the upper case; in
 * the upper case the shift key (one-shot) or the caps key (kept) is shown pressed. */
void SoftKeyboard_ShowShift(SoftKeyboard *kb)
{
    if (kb->layout != SOFT_KEYBOARD_LAYOUT_ENGLISH_UPPER) {
        SoftKeyboard_ClearFlags(kb, SOFT_KEYBOARD_FLAG_SHIFT);
    }
    if (kb->layout == SOFT_KEYBOARD_LAYOUT_ENGLISH_UPPER) {
        if (SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_SHIFT) != 0) {
            SoftKeyboard_SetEnglishKeyPalette(kb, SOFT_KEYBOARD_KEY_ENGLISH_SHIFT, SOFT_KEYBOARD_PALETTE_PRESSED);
        } else {
            SoftKeyboard_SetEnglishKeyPalette(kb, SOFT_KEYBOARD_KEY_ENGLISH_CAPS, SOFT_KEYBOARD_PALETTE_PRESSED);
        }
    }
}
CLEAN_AS(func_ov095_0229cc9c, SoftKeyboard_ShowShift)

/* The disabled keys shown disabled again, the shift shown, the screen marked changed. */
static void soft_keyboard_show_states(SoftKeyboard *kb)
{
    int i;

    for (i = 0; i < SOFT_KEYBOARD_SPECIALS; i++) {
        if (SoftKeyboard_IsSpecialDisabled(kb, i) != 0) {
            SoftKeyboard_DisableSpecial(kb, i);
        }
    }
    SoftKeyboard_ShowShift(kb);
    SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_SCREEN_DIRTY);
}

/* func_ov095_0229cce0: the pressed key shown normal again. */
void SoftKeyboard_ReleasePressed(SoftKeyboard *kb)
{
    if (kb->pressed_key != SOFT_KEYBOARD_KEY_NONE) {
        SoftKeyboard_SetKeyPalette(kb, kb->pressed_key, SOFT_KEYBOARD_PALETTE_NORMAL);
        kb->pressed_key = SOFT_KEYBOARD_KEY_NONE;
    }
    soft_keyboard_show_states(kb);
}
CLEAN_AS(func_ov095_0229cce0, SoftKeyboard_ReleasePressed)

/* func_ov095_0229cd30: every OBJ of the page's cell (to its last, at most 100) shown normal,
 * then the disabled keys and the shift shown. */
void SoftKeyboard_ResetKeyLooks(SoftKeyboard *kb)
{
    OamEntry *looks = SoftKeyboard_KeyLooks(kb);
    int i;

    if (looks != NULL) {
        for (i = 0; i < SOFT_KEYBOARD_LOOKS_MAX; i++) {
            soft_keyboard_set_obj_palette(&looks[i], SOFT_KEYBOARD_PALETTE_NORMAL);
            if (looks[i].affine == OAM_BUFFER_CELL_LAST) {
                break;
            }
        }
    }
    soft_keyboard_show_states(kb);
}
CLEAN_AS(func_ov095_0229cd30, SoftKeyboard_ResetKeyLooks)

/* --- Kinds of keys, and the disabled ones --- */

/* func_ov095_0229cda4: `key` (-1: the cursor's) is a button 0x104-0x108. */
int SoftKeyboard_IsButtonKey(SoftKeyboard *kb, int key)
{
    if (key == SOFT_KEYBOARD_KEY_NONE) {
        key = kb->key;
    }
    return (u32) key - SOFT_KEYBOARD_KEY_BUTTON_104 <= SOFT_KEYBOARD_KEY_BUTTON_108 - SOFT_KEYBOARD_KEY_BUTTON_104;
}
CLEAN_AS(func_ov095_0229cda4, SoftKeyboard_IsButtonKey)

/* func_ov095_0229cddc: `key` (-1: the cursor's) is a menu tab. */
int SoftKeyboard_IsMenuTabKey(SoftKeyboard *kb, int key)
{
    if (key == SOFT_KEYBOARD_KEY_NONE) {
        key = kb->key;
    }
    return SoftKeyboard_IsMenuTab(kb, key);
}
CLEAN_AS(func_ov095_0229cddc, SoftKeyboard_IsMenuTabKey)

/* func_ov095_0229cdf0 */
int SoftKeyboard_IsMenuTab(SoftKeyboard *kb, int key)
{
    (void) kb;
    return key >= SOFT_KEYBOARD_KEY_MENU_TAB_FIRST && key <= SOFT_KEYBOARD_KEY_MENU_TAB_LAST;
}
CLEAN_AS(func_ov095_0229cdf0, SoftKeyboard_IsMenuTab)

/* func_ov095_0229ce08: `key` is one of the page's special keys and disabled. */
int SoftKeyboard_IsKeyDisabled(SoftKeyboard *kb, int key)
{
    const int *specials;
    int i;

    if (key == SOFT_KEYBOARD_KEY_NONE) {
        return 0;
    }
    specials = soft_keyboard_specials(kb);
    if (specials == NULL) {
        return 0;
    }
    for (i = 0; i < SOFT_KEYBOARD_SPECIALS; i++) {
        if (key == specials[i]) {
            return SoftKeyboard_IsSpecialDisabled(kb, i) != 0;
        }
    }
    return 0;
}
CLEAN_AS(func_ov095_0229ce08, SoftKeyboard_IsKeyDisabled)

/* func_ov095_0229ce84: a special key enabled and shown normal on the page; the screen marked
 * changed. */
void SoftKeyboard_EnableSpecial(SoftKeyboard *kb, int special)
{
    kb->disabled &= ~soft_keyboard_lsl(1, (u32) special);
    switch (kb->page) {
        case SOFT_KEYBOARD_PAGE_ENGLISH:
            SoftKeyboard_SetEnglishKeyPalette(kb, data_ov095_0229d050[special], SOFT_KEYBOARD_PALETTE_NORMAL);
            break;
        case SOFT_KEYBOARD_PAGE_SYMBOLS:
            SoftKeyboard_SetSymbolKeyPalette(kb, data_ov095_0229d088[special], SOFT_KEYBOARD_PALETTE_NORMAL);
            break;
        case SOFT_KEYBOARD_PAGE_HANGUL:
            SoftKeyboard_SetHangulKeyPalette(kb, data_ov095_0229d0c0[special], SOFT_KEYBOARD_PALETTE_NORMAL);
            break;
        default:
            break;
    }
    SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_SCREEN_DIRTY);
}
CLEAN_AS(func_ov095_0229ce84, SoftKeyboard_EnableSpecial)

/* func_ov095_0229cef4: a special key disabled and shown disabled on the page; the screen marked
 * changed. */
void SoftKeyboard_DisableSpecial(SoftKeyboard *kb, int special)
{
    kb->disabled |= soft_keyboard_lsl(1, (u32) special);
    switch (kb->page) {
        case SOFT_KEYBOARD_PAGE_ENGLISH:
            SoftKeyboard_SetEnglishKeyPalette(kb, data_ov095_0229d050[special], SOFT_KEYBOARD_PALETTE_DISABLED);
            break;
        case SOFT_KEYBOARD_PAGE_SYMBOLS:
            SoftKeyboard_SetSymbolKeyPalette(kb, data_ov095_0229d088[special], SOFT_KEYBOARD_PALETTE_DISABLED);
            break;
        case SOFT_KEYBOARD_PAGE_HANGUL:
            SoftKeyboard_SetHangulKeyPalette(kb, data_ov095_0229d0c0[special], SOFT_KEYBOARD_PALETTE_DISABLED);
            break;
        default:
            break;
    }
    SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_SCREEN_DIRTY);
}
CLEAN_AS(func_ov095_0229cef4, SoftKeyboard_DisableSpecial)

/* func_ov095_0229cf64 */
int SoftKeyboard_IsSpecialDisabled(SoftKeyboard *kb, int special)
{
    return (kb->disabled & soft_keyboard_lsl(1, (u32) special)) != 0;
}
CLEAN_AS(func_ov095_0229cf64, SoftKeyboard_IsSpecialDisabled)
