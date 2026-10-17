/* The software keyboard's cursor (soft_keyboard.h): the key it is on (`key`), moved by the
 * d-pad (the keys of ov002/key_repeat.h) over the page's keys and the keys around them, and the
 * place its pointer points at (`key_x`, `key_y`). Moving off a side of a row wraps round to
 * the other end and says so (`wrap`), so the pointer can glide off that side. */
#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "main/oam_buffer.h"
#include "ov002/key_repeat.h"
#include "ov090/menu_tabs.h"
#include "soft_keyboard.h"

/* For each page: the key for an x past the first row's end, the first row's first key, the
 * Hangul rows' first and last keys, the first row's last key, and the first row's x. */
extern const int data_ov095_0229cf78[SOFT_KEYBOARD_PAGES];
extern const int data_ov095_0229cf8c[SOFT_KEYBOARD_PAGES];
extern const int data_ov095_0229cfa0[5];
extern const int data_ov095_0229cfb4[5];
extern const int data_ov095_0229cfc8[SOFT_KEYBOARD_PAGES];
extern const int data_ov095_0229cfdc[SOFT_KEYBOARD_PAGES];

/* The English rows' first and last keys. */
extern const int data_ov095_0229e410[5];
extern const int data_ov095_0229e3e8[5];

/* Where the Hangul keys are pointed at, by key. */
extern const u8 data_ov095_0229d020[SOFT_KEYBOARD_KEY_HANGUL_LAST - SOFT_KEYBOARD_KEY_HANGUL_FIRST + 1];
extern const u8 data_ov095_0229cff0[SOFT_KEYBOARD_KEY_HANGUL_LAST - SOFT_KEYBOARD_KEY_HANGUL_FIRST + 1];

/* Key 0xf7's OBJ and the emotion tabs' (soft_keyboard.c). */
extern OamEntry data_ov095_0229e380[];
extern OamEntry data_ov095_0229e814[];

#define SOFT_KEYBOARD_HANGUL_ROWS 5
#define SOFT_KEYBOARD_ENGLISH_ROWS 5
#define SOFT_KEYBOARD_KEY_WIDTH 20

/* The key the cursor goes to from a kind 4-5 or letter button, up to the page: by page. */
static void soft_keyboard_up_to_page(SoftKeyboard *kb, int none, int english, int symbols, int page_3, int hangul)
{
    switch (kb->page) {
        case SOFT_KEYBOARD_PAGE_NONE:
            kb->key = none;
            break;
        case SOFT_KEYBOARD_PAGE_ENGLISH:
            kb->key = english;
            break;
        case SOFT_KEYBOARD_PAGE_SYMBOLS:
            kb->key = symbols;
            break;
        case SOFT_KEYBOARD_PAGE_3:
            kb->key = page_3;
            break;
        case SOFT_KEYBOARD_PAGE_HANGUL:
            kb->key = hangul;
            break;
    }
}

/* func_ov095_02299a00: the cursor's key pressed (as the pressed key): the key, or -1 for a
 * disabled key or the tab of the page already shown. */
int SoftKeyboard_PressCursorKey(SoftKeyboard *kb)
{
    if (SoftKeyboard_IsKeyDisabled(kb, kb->key) != 0) {
        return SOFT_KEYBOARD_KEY_NONE;
    }
    switch (kb->key) {
        case SOFT_KEYBOARD_KEY_TAB_HANGUL:
            if (kb->page == SOFT_KEYBOARD_PAGE_HANGUL) {
                return SOFT_KEYBOARD_KEY_NONE;
            }
            break;
        case SOFT_KEYBOARD_KEY_TAB_ENGLISH:
            if (kb->page == SOFT_KEYBOARD_PAGE_ENGLISH) {
                return SOFT_KEYBOARD_KEY_NONE;
            }
            break;
        case SOFT_KEYBOARD_KEY_TAB_SYMBOLS:
            if (kb->page == SOFT_KEYBOARD_PAGE_SYMBOLS) {
                return SOFT_KEYBOARD_KEY_NONE;
            }
            break;
    }
    kb->pressed_key = kb->key;
    return kb->key;
}
CLEAN_AS(func_ov095_02299a00, SoftKeyboard_PressCursorKey)

/* func_ov095_02299a54: the cursor moved by `keys` on the page (SoftKeyboardMove); when its key
 * changed, it is placed. */
int SoftKeyboard_MoveCursor(SoftKeyboard *kb, int keys)
{
    int before = kb->key;

    kb->wrap = SOFT_KEYBOARD_WRAP_NONE;
    SoftKeyboard_ClearFlags(kb, SOFT_KEYBOARD_FLAG_LEFT_KEYS);
    switch (kb->page) {
        case SOFT_KEYBOARD_PAGE_ENGLISH:
            SoftKeyboard_MoveOnEnglish(kb, keys);
            break;
        case SOFT_KEYBOARD_PAGE_SYMBOLS:
            SoftKeyboard_MoveOnSymbols(kb, keys);
            break;
        case SOFT_KEYBOARD_PAGE_HANGUL:
            SoftKeyboard_MoveOnHangul(kb, keys);
            break;
    }
    if (SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_LEFT_KEYS) != 0) {
        return SOFT_KEYBOARD_MOVE_LEFT;
    }
    if (before != kb->key) {
        SoftKeyboard_PlaceCursor(kb);
        if (SoftKeyboard_IsMenuTabKey(kb, kb->key) != 0) {
            return SOFT_KEYBOARD_MOVE_MENU_TAB;
        }
        if (SoftKeyboard_IsButtonKey(kb, kb->key) != 0) {
            return SOFT_KEYBOARD_MOVE_BUTTON;
        }
        return SOFT_KEYBOARD_MOVE_KEY;
    }
    return SOFT_KEYBOARD_MOVE_NONE;
}
CLEAN_AS(func_ov095_02299a54, SoftKeyboard_MoveCursor)

/* func_ov095_02299aec: the cursor on the page's first key, placed. */
void SoftKeyboard_PlaceCursorHome(SoftKeyboard *kb)
{
    switch (kb->page) {
        case SOFT_KEYBOARD_PAGE_ENGLISH:
            kb->key = SOFT_KEYBOARD_KEY_ENGLISH_FIRST;
            SoftKeyboard_PlaceEnglishCursor(kb);
            break;
        case SOFT_KEYBOARD_PAGE_SYMBOLS:
            kb->key = SOFT_KEYBOARD_KEY_SYMBOLS_FIRST;
            SoftKeyboard_PlaceSymbolCursor(kb);
            break;
        case SOFT_KEYBOARD_PAGE_HANGUL:
            kb->key = SOFT_KEYBOARD_KEY_HANGUL_FIRST;
            SoftKeyboard_PlaceHangulCursor(kb);
            break;
    }
}
CLEAN_AS(func_ov095_02299aec, SoftKeyboard_PlaceCursorHome)

/* func_ov095_02299b30 */
void SoftKeyboard_SetMovableKeyPlace(SoftKeyboard *kb, int x, int y)
{
    kb->movable_x = x;
    kb->movable_y = y;
}
CLEAN_AS(func_ov095_02299b30, SoftKeyboard_SetMovableKeyPlace)

/* func_ov095_02299b38: the pointer's y; a key of the page 8 pixels higher outside kind 0's
 * layout. On the movable key its place is taken first. */
int SoftKeyboard_CursorY(SoftKeyboard *kb)
{
    if (kb->key == SOFT_KEYBOARD_KEY_MOVABLE) {
        kb->key_y = kb->movable_y;
        return kb->key_y;
    }
    if (SoftKeyboard_OutsideKeyCode(kb, kb->key) != -1) {
        return kb->key_y;
    }
    if (SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_CHAT_LAYOUT) == 0) {
        return kb->key_y - 8;
    }
    return kb->key_y;
}
CLEAN_AS(func_ov095_02299b38, SoftKeyboard_CursorY)

/* func_ov095_02299b7c: the pointer's x, a screen's width off to the side the cursor wrapped
 * to. On the movable key its place is taken first. */
int SoftKeyboard_CursorX(SoftKeyboard *kb)
{
    if (kb->key == SOFT_KEYBOARD_KEY_MOVABLE) {
        kb->key_x = kb->movable_x;
    }
    switch (kb->wrap) {
        case SOFT_KEYBOARD_WRAP_LEFT:
            return kb->key_x - 0x100;
        case SOFT_KEYBOARD_WRAP_RIGHT:
            return kb->key_x + 0x100;
        default:
            return kb->key_x;
    }
}
CLEAN_AS(func_ov095_02299b7c, SoftKeyboard_CursorX)

/* --- Off the page's keys --- */

/* func_ov095_02299bb4: the cursor moved when it is on a key around the page: 1 when it was. */
int SoftKeyboard_MoveOutsideKeys(SoftKeyboard *kb, int keys)
{
    if (SoftKeyboard_MoveOnTabRow(kb, keys) != 0) {
        return 1;
    }
    switch (kb->kind) {
        case SOFT_KEYBOARD_KIND_CHAT:
            return SoftKeyboard_MoveOnChatTabs(kb, keys);
        case SOFT_KEYBOARD_KIND_LETTER:
        case SOFT_KEYBOARD_KIND_2:
            return SoftKeyboard_MoveOnLetterButtons(kb, keys);
        case SOFT_KEYBOARD_KIND_4:
        case SOFT_KEYBOARD_KIND_5:
            return SoftKeyboard_MoveOnKind4Buttons(kb, keys);
        default:
            return 0;
    }
}
CLEAN_AS(func_ov095_02299bb4, SoftKeyboard_MoveOutsideKeys)

/* func_ov095_02299c14: on buttons 0x107 and 0x108 (1), up to the page's last row, or across
 * (to 0x108 only for kind 5). */
int SoftKeyboard_MoveOnKind4Buttons(SoftKeyboard *kb, int keys)
{
    unsigned int key = (unsigned int) kb->key;

    if (key == SOFT_KEYBOARD_KEY_BUTTON_107) {
        if (KeyRepeat_HasUp(keys) != 0) {
            soft_keyboard_up_to_page(kb, 0x2c, 0x6e, 0x90, 0xc8, 0xf6);
        } else if (kb->kind == SOFT_KEYBOARD_KIND_5 && KeyRepeat_HasLeft(keys) != 0) {
            kb->key = SOFT_KEYBOARD_KEY_BUTTON_108;
        }
        return 1;
    }
    if (key == SOFT_KEYBOARD_KEY_BUTTON_108) {
        if (KeyRepeat_HasUp(keys) != 0) {
            soft_keyboard_up_to_page(kb, 0x18, 0x6b, 0x91, 0xc3, 0xf4);
        } else if (KeyRepeat_HasRight(keys) != 0) {
            kb->key = SOFT_KEYBOARD_KEY_BUTTON_107;
        }
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov095_02299c14, SoftKeyboard_MoveOnKind4Buttons)

/* func_ov095_02299cf8: on the movable key (down to the right side button) or buttons
 * 0x104-0x106 (up to the page's last row, or across): 1 when it was. */
int SoftKeyboard_MoveOnLetterButtons(SoftKeyboard *kb, int keys)
{
    switch (kb->key) {
        case SOFT_KEYBOARD_KEY_MOVABLE:
            if (KeyRepeat_HasDown(keys) != 0) {
                kb->key = SOFT_KEYBOARD_KEY_SIDE_RIGHT;
            }
            return 1;
        case SOFT_KEYBOARD_KEY_BUTTON_104:
            if (KeyRepeat_HasUp(keys) != 0) {
                soft_keyboard_up_to_page(kb, 0x2c, 0x6e, 0x90, 0xc8, 0xf6);
            } else if (KeyRepeat_HasLeft(keys) != 0) {
                SoftKeyboard_CursorToFirstButton(kb);
            }
            return 1;
        case SOFT_KEYBOARD_KEY_BUTTON_105:
            if (KeyRepeat_HasUp(keys) != 0) {
                soft_keyboard_up_to_page(kb, 0x0e, 0x69, 0x91, 0xc0, 0xf4);
            } else if (KeyRepeat_HasRight(keys) != 0) {
                kb->key = SOFT_KEYBOARD_KEY_BUTTON_104;
            }
            return 1;
        case SOFT_KEYBOARD_KEY_BUTTON_106:
            if (KeyRepeat_HasUp(keys) != 0) {
                soft_keyboard_up_to_page(kb, 0x13, 0x6b, 0x91, 0xc2, 0xf4);
            } else if (KeyRepeat_HasRight(keys) != 0) {
                kb->key = SOFT_KEYBOARD_KEY_BUTTON_104;
            }
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov095_02299cf8, SoftKeyboard_MoveOnLetterButtons)

/* func_ov095_02299e80: kind 0 on key 0xf7 (down to the right side button, up to the menu tab
 * above, left off the keyboard) or on the menu tabs (down to 0xf7 from the last two, else off
 * the keyboard; across): 1 when it was. */
int SoftKeyboard_MoveOnChatTabs(SoftKeyboard *kb, int keys)
{
    if (kb->key == SOFT_KEYBOARD_KEY_CHAT_F7) {
        if (KeyRepeat_HasDown(keys) != 0) {
            kb->key = SOFT_KEYBOARD_KEY_SIDE_RIGHT;
        } else if (KeyRepeat_HasUp(keys) != 0) {
            kb->key = MenuTabs_TabAtX(kb->key_x) + SOFT_KEYBOARD_KEY_MENU_TAB_FIRST;
        } else if (KeyRepeat_HasLeft(keys) != 0) {
            SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_LEFT_KEYS);
        }
        return 1;
    }
    if (SoftKeyboard_IsMenuTab(kb, kb->key) == 0) {
        return 0;
    }
    if (KeyRepeat_HasDown(keys) != 0) {
        if (kb->key >= 0x101) {
            kb->key = SOFT_KEYBOARD_KEY_CHAT_F7;
        } else {
            SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_LEFT_KEYS);
        }
        return 1;
    }
    if (KeyRepeat_HasRight(keys) != 0) {
        if (kb->key < SOFT_KEYBOARD_KEY_MENU_TAB_LAST) {
            kb->key++;
        }
    } else if (KeyRepeat_HasLeft(keys) != 0) {
        if (kb->key > SOFT_KEYBOARD_KEY_MENU_TAB_FIRST) {
            kb->key--;
        }
    }
    return 1;
}
CLEAN_AS(func_ov095_02299e80, SoftKeyboard_MoveOnChatTabs)

/* func_ov095_02299f3c: on the tab row (side buttons, page tabs, emotion tabs): down to the page,
 * up off the row, across with wrapping at the side buttons: 1 when it was. */
int SoftKeyboard_MoveOnTabRow(SoftKeyboard *kb, int keys)
{
    switch (kb->key) {
        case SOFT_KEYBOARD_KEY_TAB_HANGUL:
        case SOFT_KEYBOARD_KEY_TAB_ENGLISH:
        case SOFT_KEYBOARD_KEY_TAB_SYMBOLS:
            if (KeyRepeat_HasRight(keys) != 0) {
                if (kb->key < SOFT_KEYBOARD_KEY_TAB_SYMBOLS) {
                    kb->key++;
                } else if (kb->emotion_count != 0) {
                    kb->key = SOFT_KEYBOARD_KEY_EMOTION_FIRST;
                } else {
                    kb->key = SOFT_KEYBOARD_KEY_SIDE_RIGHT;
                }
                return 1;
            }
            if (KeyRepeat_HasLeft(keys) != 0) {
                if (kb->key > SOFT_KEYBOARD_KEY_TAB_HANGUL) {
                    kb->key--;
                } else {
                    kb->key = SOFT_KEYBOARD_KEY_SIDE_LEFT;
                }
                return 1;
            }
            if (KeyRepeat_HasDown(keys) != 0) {
                SoftKeyboard_CursorToPageAt(kb, kb->key_x);
            } else if (KeyRepeat_HasUp(keys) != 0) {
                SoftKeyboard_CursorUpFromTabRow(kb);
            }
            return 1;
        case SOFT_KEYBOARD_KEY_SIDE_LEFT:
            if (KeyRepeat_HasUp(keys) != 0) {
                SoftKeyboard_CursorUpFromTabRow(kb);
            } else if (KeyRepeat_HasDown(keys) != 0) {
                SoftKeyboard_CursorToPageAt(kb, kb->key_x);
            } else if (KeyRepeat_HasRight(keys) != 0) {
                kb->key = SOFT_KEYBOARD_KEY_TAB_HANGUL;
            } else if (KeyRepeat_HasLeft(keys) != 0) {
                kb->key = SOFT_KEYBOARD_KEY_SIDE_RIGHT;
                kb->wrap = SOFT_KEYBOARD_WRAP_LEFT;
            }
            return 1;
        case SOFT_KEYBOARD_KEY_SIDE_RIGHT:
            if (KeyRepeat_HasUp(keys) != 0) {
                SoftKeyboard_CursorUpFromTabRow(kb);
            } else if (KeyRepeat_HasDown(keys) != 0) {
                SoftKeyboard_CursorToPageAt(kb, kb->key_x);
            } else if (KeyRepeat_HasLeft(keys) != 0) {
                if (kb->emotion_count != 0) {
                    kb->key = kb->emotion_count + SOFT_KEYBOARD_KEY_EMOTION_FIRST - 1;
                } else {
                    kb->key = SOFT_KEYBOARD_KEY_TAB_SYMBOLS;
                }
            } else if (KeyRepeat_HasRight(keys) != 0) {
                kb->key = SOFT_KEYBOARD_KEY_SIDE_LEFT;
                kb->wrap = SOFT_KEYBOARD_WRAP_RIGHT;
            }
            return 1;
        case 0x10c:
        case 0x10d:
        case 0x10e:
        case 0x10f:
            if (KeyRepeat_HasUp(keys) != 0) {
                SoftKeyboard_CursorUpFromTabRow(kb);
            } else if (KeyRepeat_HasDown(keys) != 0) {
                SoftKeyboard_CursorToPageAt(kb, kb->key_x);
            } else if (KeyRepeat_HasLeft(keys) != 0) {
                if (kb->key > SOFT_KEYBOARD_KEY_EMOTION_FIRST) {
                    kb->key--;
                } else {
                    kb->key = SOFT_KEYBOARD_KEY_TAB_SYMBOLS;
                }
            } else if (KeyRepeat_HasRight(keys) != 0) {
                if (kb->key < kb->emotion_count + SOFT_KEYBOARD_KEY_EMOTION_FIRST - 1) {
                    kb->key++;
                } else {
                    kb->key = SOFT_KEYBOARD_KEY_SIDE_RIGHT;
                }
            }
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov095_02299f3c, SoftKeyboard_MoveOnTabRow)

/* func_ov095_0229a134: the cursor to the tab row's key nearest x, placed. */
void SoftKeyboard_CursorToTabRowAt(SoftKeyboard *kb, int x)
{
    SoftKeyboard_NearestTabRowKey(kb, x);
    SoftKeyboard_PlaceCursor(kb);
}
CLEAN_AS(func_ov095_0229a134, SoftKeyboard_CursorToTabRowAt)

/* func_ov095_0229a148: the cursor to key 0xf7, placed. */
void SoftKeyboard_CursorToChatF7(SoftKeyboard *kb)
{
    kb->key = SOFT_KEYBOARD_KEY_CHAT_F7;
    SoftKeyboard_PlaceCursor(kb);
}
CLEAN_AS(func_ov095_0229a148, SoftKeyboard_CursorToChatF7)

/* func_ov095_0229a154: the cursor to the menu tab under x, placed. */
void SoftKeyboard_CursorToMenuTabAt(SoftKeyboard *kb, int x)
{
    kb->key = MenuTabs_TabAtX(x) + SOFT_KEYBOARD_KEY_MENU_TAB_FIRST;
    SoftKeyboard_PlaceCursor(kb);
}
CLEAN_AS(func_ov095_0229a154, SoftKeyboard_CursorToMenuTabAt)

/* func_ov095_0229a170: the same as SoftKeyboard_CursorToTabRowAt (a second copy in the ROM). */
void SoftKeyboard_CursorToTabRowAtB(SoftKeyboard *kb, int x)
{
    SoftKeyboard_NearestTabRowKey(kb, x);
    SoftKeyboard_PlaceCursor(kb);
}
CLEAN_AS(func_ov095_0229a170, SoftKeyboard_CursorToTabRowAtB)

/* func_ov095_0229a184: the cursor to the key of the page's first row under x (keys 20 pixels
 * wide from the row's x; past the row's end, the page's key for that), placed. */
void SoftKeyboard_CursorToPageAt(SoftKeyboard *kb, int x)
{
    int page = kb->page;
    int left = data_ov095_0229cfdc[page];
    int key;

    if (x < left) {
        x = left;
    }
    key = (x - left) / SOFT_KEYBOARD_KEY_WIDTH + data_ov095_0229cf8c[page];
    if (key > data_ov095_0229cfc8[page]) {
        key = data_ov095_0229cf78[page];
    }
    kb->key = key;
    SoftKeyboard_PlaceCursor(kb);
}
CLEAN_AS(func_ov095_0229a184, SoftKeyboard_CursorToPageAt)

/* func_ov095_0229a1d4: the cursor up from the page's first row to the tab row's key nearest
 * the pointer. */
void SoftKeyboard_CursorUpToTabRow(SoftKeyboard *kb)
{
    SoftKeyboard_NearestTabRowKey(kb, SoftKeyboard_CursorX(kb));
}
CLEAN_AS(func_ov095_0229a1d4, SoftKeyboard_CursorUpToTabRow)

/* func_ov095_0229a1ec: the cursor to the tab row's key nearest x: the side button of x's half,
 * a page tab nearer, then (kind 0's layout) an emotion tab nearer.
 * QUIRK: the side button's distance stays signed until the emotion tabs are tried, so from x
 * 0x80 to 0xe7 (and below 0x18) no page tab beats the side button. */
void SoftKeyboard_NearestTabRowKey(SoftKeyboard *kb, int x)
{
    int best;
    int distance;
    int i;

    if (x < 0x80) {
        kb->key = SOFT_KEYBOARD_KEY_SIDE_LEFT;
        best = x - 0x18;
    } else {
        kb->key = SOFT_KEYBOARD_KEY_SIDE_RIGHT;
        best = x - 0xe8;
    }
    for (i = 0; i < 3; i++) {
        distance = x - SoftKeyboard_PageTabX(kb, i + SOFT_KEYBOARD_KEY_TAB_HANGUL);
        if (distance < 0) {
            distance = -distance;
        }
        if (distance < best) {
            best = distance;
            kb->key = i + SOFT_KEYBOARD_KEY_TAB_HANGUL;
        }
    }
    if (SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_CHAT_LAYOUT) != 0) {
        if (best < 0) {
            best = -best;
        }
        for (i = 0; i < kb->emotion_count; i++) {
            distance = x - SoftKeyboard_EmotionTabX(kb, i + SOFT_KEYBOARD_KEY_EMOTION_FIRST);
            if (distance < 0) {
                distance = -distance;
            }
            if (distance < best) {
                best = distance;
                kb->key = i + SOFT_KEYBOARD_KEY_EMOTION_FIRST;
            }
        }
    }
}
CLEAN_AS(func_ov095_0229a1ec, SoftKeyboard_NearestTabRowKey)

/* func_ov095_0229a280: up from the tab row: kind 0 from the right side button to key 0xf7,
 * kinds 1-2 to the movable key; otherwise off the keyboard. */
void SoftKeyboard_CursorUpFromTabRow(SoftKeyboard *kb)
{
    switch (kb->kind) {
        case SOFT_KEYBOARD_KIND_CHAT:
            if (kb->key == SOFT_KEYBOARD_KEY_SIDE_RIGHT) {
                kb->key = SOFT_KEYBOARD_KEY_CHAT_F7;
            } else {
                SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_LEFT_KEYS);
            }
            break;
        case SOFT_KEYBOARD_KIND_LETTER:
        case SOFT_KEYBOARD_KIND_2:
            kb->key = SOFT_KEYBOARD_KEY_MOVABLE;
            break;
        case SOFT_KEYBOARD_KIND_3:
        case SOFT_KEYBOARD_KIND_4:
        case SOFT_KEYBOARD_KIND_5:
            SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_LEFT_KEYS);
            break;
    }
}
CLEAN_AS(func_ov095_0229a280, SoftKeyboard_CursorUpFromTabRow)

/* --- On the pages --- */

/* func_ov095_0229a2d8: on the Hangul page. Up and down keep the column (a key pressed left or
 * right at the same time moves it), with the long keys of rows 2 and 4 their own way; across
 * wraps round the row. */
void SoftKeyboard_MoveOnHangul(SoftKeyboard *kb, int keys)
{
    const int *first = data_ov095_0229cfa0;
    const int *last = data_ov095_0229cfb4;
    int key;
    int row = 0;
    int column = 0;

    if (SoftKeyboard_MoveOutsideKeys(kb, keys) != 0) {
        return;
    }
    key = kb->key;
    if (key < SOFT_KEYBOARD_KEY_HANGUL_FIRST || key > SOFT_KEYBOARD_KEY_HANGUL_LAST) {
        return;
    }
    for (row = 0; row < SOFT_KEYBOARD_HANGUL_ROWS; row++) {
        if (key <= last[row]) {
            column = key - first[row];
            break;
        }
    }

    if (KeyRepeat_HasUp(keys) != 0) {
        if (row == 0) {
            SoftKeyboard_CursorUpToTabRow(kb);
            return;
        }
        if (row == 4) {
            if (kb->key <= 0xf3) {
                if (KeyRepeat_HasRight(keys) != 0) {
                    column++;
                }
                kb->key = column + first[3];
                return;
            }
            if (kb->key == SOFT_KEYBOARD_KEY_HANGUL_SPACE) {
                kb->key = 0xec;
                if (KeyRepeat_HasRight(keys) != 0) {
                    kb->key++;
                    return;
                }
                if (KeyRepeat_HasLeft(keys) != 0) {
                    kb->key--;
                }
                return;
            }
            kb->key -= 6;
            if (KeyRepeat_HasLeft(keys) != 0) {
                kb->key--;
            }
            return;
        }
        if (kb->key == SOFT_KEYBOARD_KEY_HANGUL_NEWLINE) {
            if (KeyRepeat_HasLeft(keys) != 0) {
                kb->key = 0xe6;
                return;
            }
            kb->key = SOFT_KEYBOARD_KEY_HANGUL_BACKSPACE;
            return;
        }
        if (KeyRepeat_HasRight(keys) != 0) {
            column++;
        }
        kb->key = column + first[row - 1];
        if (kb->key > last[row - 1]) {
            kb->key = last[row - 1];
        }
        return;
    }

    if (KeyRepeat_HasDown(keys) != 0) {
        if (row == 4) {
            if (kb->key <= SOFT_KEYBOARD_KEY_HANGUL_SPACE) {
                SoftKeyboard_CursorToFirstButton(kb);
                return;
            }
            SoftKeyboard_CursorToLastButton(kb);
            return;
        }
        if (row == 3) {
            if (kb->key <= 0xea) {
                if (KeyRepeat_HasLeft(keys) != 0 && column > 0) {
                    column--;
                }
                kb->key = column + first[4];
                return;
            }
            if (KeyRepeat_HasRight(keys) != 0) {
                kb->key++;
            }
            if (kb->key <= 0xee) {
                kb->key = SOFT_KEYBOARD_KEY_HANGUL_SPACE;
            } else if (kb->key == 0xef) {
                kb->key = 0xf5;
            } else {
                kb->key = 0xf6;
            }
            return;
        }
        if (KeyRepeat_HasLeft(keys) != 0 && column > 0) {
            column--;
        }
        kb->key = column + first[row + 1];
        if (kb->key > last[row + 1]) {
            kb->key = last[row + 1];
        }
        return;
    }

    if (KeyRepeat_HasLeft(keys) != 0) {
        kb->key--;
        if (kb->key < first[row]) {
            kb->key = last[row];
            kb->wrap = SOFT_KEYBOARD_WRAP_LEFT;
        }
        return;
    }
    if (KeyRepeat_HasRight(keys) != 0) {
        kb->key++;
        if (kb->key > last[row]) {
            kb->key = first[row];
            kb->wrap = SOFT_KEYBOARD_WRAP_RIGHT;
        }
    }
}
CLEAN_AS(func_ov095_0229a2d8, SoftKeyboard_MoveOnHangul)

/* func_ov095_0229a4d4: on the symbols page: the grid of 10 by 3 (up from row 0 to the tab row,
 * down from row 2 to the space), the keys right of it and the space below. */
void SoftKeyboard_MoveOnSymbols(SoftKeyboard *kb, int keys)
{
    if (SoftKeyboard_MoveOutsideKeys(kb, keys) != 0) {
        return;
    }
    if (kb->key < SOFT_KEYBOARD_KEY_SYMBOLS_FIRST) {
        return;
    }

    if (kb->key <= SOFT_KEYBOARD_KEY_SYMBOLS_GRID_LAST) {
        int n = kb->key - SOFT_KEYBOARD_KEY_SYMBOLS_FIRST;
        int column = n % 10;
        int row = n / 10;

        if (KeyRepeat_HasUp(keys) != 0) {
            if (row > 0) {
                row--;
                kb->key -= 10;
            } else {
                SoftKeyboard_CursorUpToTabRow(kb);
                return;
            }
        } else if (KeyRepeat_HasDown(keys) != 0) {
            if (row < 2) {
                row++;
                kb->key += 10;
            } else {
                kb->key = SOFT_KEYBOARD_KEY_SYMBOLS_LAST;
                return;
            }
        }

        if (KeyRepeat_HasLeft(keys) != 0) {
            if (column > 0) {
                kb->key--;
            } else {
                kb->wrap = SOFT_KEYBOARD_WRAP_LEFT;
                kb->key = row == 0 ? 0x8f : 0x90;
            }
        } else if (KeyRepeat_HasRight(keys) != 0) {
            if (column < 9) {
                kb->key++;
            } else {
                kb->key = row == 0 ? 0x8e : 0x90;
            }
        }
        return;
    }

    switch (kb->key) {
        case 0x8e:
            if (KeyRepeat_HasUp(keys) != 0) {
                SoftKeyboard_CursorUpToTabRow(kb);
            } else if (KeyRepeat_HasDown(keys) != 0) {
                kb->key = KeyRepeat_HasLeft(keys) != 0 ? 0x83 : 0x90;
            } else if (KeyRepeat_HasLeft(keys) != 0) {
                kb->key = 0x79;
            } else if (KeyRepeat_HasRight(keys) != 0) {
                kb->key = 0x8f;
            }
            break;
        case 0x8f:
            if (KeyRepeat_HasUp(keys) != 0) {
                SoftKeyboard_CursorUpToTabRow(kb);
            } else if (KeyRepeat_HasDown(keys) != 0) {
                kb->key = 0x90;
            } else if (KeyRepeat_HasLeft(keys) != 0) {
                kb->key = 0x8e;
            } else if (KeyRepeat_HasRight(keys) != 0) {
                kb->wrap = SOFT_KEYBOARD_WRAP_RIGHT;
                kb->key = SOFT_KEYBOARD_KEY_SYMBOLS_FIRST;
            }
            break;
        case 0x90:
            if (KeyRepeat_HasUp(keys) != 0) {
                kb->key = 0x8f;
                if (KeyRepeat_HasLeft(keys) != 0) {
                    kb->key--;
                }
                break;
            }
            if (KeyRepeat_HasDown(keys) != 0) {
                SoftKeyboard_CursorToLastButton(kb);
                if (kb->key != 0x90) {
                    break;
                }
            }
            if (KeyRepeat_HasLeft(keys) != 0) {
                kb->key = KeyRepeat_HasDown(keys) != 0 ? SOFT_KEYBOARD_KEY_SYMBOLS_GRID_LAST : 0x83;
            } else if (KeyRepeat_HasRight(keys) != 0) {
                kb->wrap = SOFT_KEYBOARD_WRAP_RIGHT;
                kb->key = KeyRepeat_HasDown(keys) != 0 ? 0x84 : 0x7a;
            }
            break;
        case SOFT_KEYBOARD_KEY_SYMBOLS_LAST:
            if (KeyRepeat_HasUp(keys) != 0) {
                kb->key = 0x8a;
                if (KeyRepeat_HasLeft(keys) != 0) {
                    kb->key--;
                }
            } else if (KeyRepeat_HasRight(keys) != 0) {
                SoftKeyboard_CursorToLastButton(kb);
            } else if (KeyRepeat_HasDown(keys) != 0) {
                SoftKeyboard_CursorToFirstButton(kb);
            }
            break;
    }
}
CLEAN_AS(func_ov095_0229a4d4, SoftKeyboard_MoveOnSymbols)

/* func_ov095_0229a720: on the English page. Up and down keep the column as the rows are offset
 * (a key pressed left or right at the same time moves it), with the long keys (backspace,
 * newline, shift, space) their own way; across wraps round the row, the space bar's places
 * 0x6a, 0x6c and 0x6d being the space.
 * REQUIRES: the cursor is on a key (from 0x3b up): below, the ROM's code reads a row it never
 * set. */
void SoftKeyboard_MoveOnEnglish(SoftKeyboard *kb, int keys)
{
    const int *first = data_ov095_0229e410;
    const int *last = data_ov095_0229e3e8;
    int row;

    if (SoftKeyboard_MoveOutsideKeys(kb, keys) != 0) {
        return;
    }
    if (kb->key < SOFT_KEYBOARD_KEY_ENGLISH_FIRST) {
        return;
    }
    if (kb->key <= 0x46) {
        row = 0;
    } else if (kb->key <= SOFT_KEYBOARD_KEY_ENGLISH_BACKSPACE) {
        row = 1;
        if (kb->key == SOFT_KEYBOARD_KEY_ENGLISH_BACKSPACE) {
            if (KeyRepeat_HasUp(keys) != 0) {
                kb->key = KeyRepeat_HasLeft(keys) != 0 ? 0x45 : 0x46;
                return;
            }
            if (KeyRepeat_HasDown(keys) != 0) {
                kb->key = SOFT_KEYBOARD_KEY_ENGLISH_NEWLINE;
                return;
            }
        }
    } else if (kb->key <= SOFT_KEYBOARD_KEY_ENGLISH_NEWLINE) {
        row = 2;
        if (kb->key == SOFT_KEYBOARD_KEY_ENGLISH_NEWLINE) {
            if (KeyRepeat_HasUp(keys) != 0) {
                kb->key = KeyRepeat_HasLeft(keys) != 0 ? 0x50 : SOFT_KEYBOARD_KEY_ENGLISH_BACKSPACE;
                return;
            }
        }
    } else if (kb->key <= 0x67) {
        row = 3;
        if (KeyRepeat_HasDown(keys) != 0) {
            if (KeyRepeat_HasLeft(keys) != 0) {
                kb->key--;
            }
            if (kb->key < SOFT_KEYBOARD_KEY_ENGLISH_SHIFT) {
                kb->key = SOFT_KEYBOARD_KEY_ENGLISH_SHIFT;
            }
            if (kb->key <= 0x5e) {
                kb->key += 0xb;
            } else if (kb->key <= 0x65) {
                kb->key = SOFT_KEYBOARD_KEY_ENGLISH_SPACE;
            } else {
                kb->key += 8;
            }
            return;
        }
    } else if (kb->key <= SOFT_KEYBOARD_KEY_ENGLISH_LAST) {
        row = 4;
        if (KeyRepeat_HasUp(keys) != 0) {
            if (kb->key == SOFT_KEYBOARD_KEY_ENGLISH_SPACE) {
                kb->key = 0x63;
                if (KeyRepeat_HasLeft(keys) != 0) {
                    kb->key--;
                    return;
                }
                if (KeyRepeat_HasRight(keys) == 0) {
                    return;
                }
                kb->key++;
                return;
            }
            if (kb->key > SOFT_KEYBOARD_KEY_ENGLISH_SPACE) {
                kb->key -= 8;
                if (KeyRepeat_HasRight(keys) == 0) {
                    return;
                }
                if (kb->key < 0x67) {
                    kb->key++;
                }
                return;
            }
        } else if (KeyRepeat_HasDown(keys) != 0) {
            if (kb->key < 0x6c) {
                SoftKeyboard_CursorToFirstButton(kb);
            } else {
                SoftKeyboard_CursorToLastButton(kb);
            }
            return;
        }
    } else {
        return;
    }

    if (KeyRepeat_HasUp(keys) != 0) {
        int low;
        int high;

        if (row == 0) {
            SoftKeyboard_CursorUpToTabRow(kb);
            return;
        }
        low = first[row - 1];
        high = last[row - 1];
        kb->key -= high - low + 1;
        if (row == 2) {
            kb->key--;
        }
        if (KeyRepeat_HasRight(keys) != 0) {
            kb->key++;
        }
        if (kb->key < low) {
            kb->key = low;
        } else if (kb->key > high) {
            kb->key = high;
        }
    } else if (KeyRepeat_HasDown(keys) != 0 && row < 3) {
        int low = first[row + 1];
        int high = last[row + 1];

        kb->key += last[row] - first[row] + 1;
        if (row == 1) {
            kb->key++;
        }
        if (KeyRepeat_HasLeft(keys) != 0) {
            kb->key--;
        }
        if (kb->key > high) {
            kb->key = high;
        } else if (kb->key < low) {
            kb->key = low;
        }
    } else {
        if (kb->key == SOFT_KEYBOARD_KEY_ENGLISH_SPACE) {
            if (KeyRepeat_HasLeft(keys) != 0) {
                kb->key = 0x69;
                return;
            }
            if (KeyRepeat_HasRight(keys) != 0) {
                kb->key = 0x6e;
            }
            return;
        }
        if (KeyRepeat_HasLeft(keys) != 0) {
            if (kb->key > first[row]) {
                kb->key--;
            } else {
                kb->wrap = SOFT_KEYBOARD_WRAP_LEFT;
                kb->key = last[row];
            }
        } else if (KeyRepeat_HasRight(keys) != 0) {
            if (kb->key < last[row]) {
                kb->key++;
            } else {
                kb->wrap = SOFT_KEYBOARD_WRAP_RIGHT;
                kb->key = first[row];
            }
        }
        if (kb->key == 0x6a || kb->key == 0x6c || kb->key == 0x6d) {
            kb->key = SOFT_KEYBOARD_KEY_ENGLISH_SPACE;
        }
    }
}
CLEAN_AS(func_ov095_0229a720, SoftKeyboard_MoveOnEnglish)

/* func_ov095_0229a9d4: the cursor to the owner's first button (the letter's 0x104 for a letter
 * with flag 0x08, else 0x105); kinds 0 and 3 have none. */
void SoftKeyboard_CursorToFirstButton(SoftKeyboard *kb)
{
    switch (kb->kind) {
        case SOFT_KEYBOARD_KIND_CHAT:
            break;
        case SOFT_KEYBOARD_KIND_LETTER:
            if (SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_08) != 0) {
                kb->key = SOFT_KEYBOARD_KEY_BUTTON_104;
            } else {
                kb->key = SOFT_KEYBOARD_KEY_BUTTON_105;
            }
            break;
        case SOFT_KEYBOARD_KIND_2:
            kb->key = SOFT_KEYBOARD_KEY_BUTTON_106;
            break;
        case SOFT_KEYBOARD_KIND_5:
            kb->key = SOFT_KEYBOARD_KEY_BUTTON_108;
            break;
        case SOFT_KEYBOARD_KIND_4:
            kb->key = SOFT_KEYBOARD_KEY_BUTTON_107;
            break;
    }
}
CLEAN_AS(func_ov095_0229a9d4, SoftKeyboard_CursorToFirstButton)

/* func_ov095_0229aa3c: the cursor to the owner's last (rightmost) button. */
void SoftKeyboard_CursorToLastButton(SoftKeyboard *kb)
{
    switch (kb->kind) {
        case SOFT_KEYBOARD_KIND_LETTER:
        case SOFT_KEYBOARD_KIND_2:
            kb->key = SOFT_KEYBOARD_KEY_BUTTON_104;
            break;
        case SOFT_KEYBOARD_KIND_4:
        case SOFT_KEYBOARD_KIND_5:
            kb->key = SOFT_KEYBOARD_KEY_BUTTON_107;
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov095_0229aa3c, SoftKeyboard_CursorToLastButton)

/* --- The pointer's place --- */

/* func_ov095_0229aa74: the pointer placed at the cursor's key, by page. */
void SoftKeyboard_PlaceCursor(SoftKeyboard *kb)
{
    switch (kb->page) {
        case SOFT_KEYBOARD_PAGE_ENGLISH:
            SoftKeyboard_PlaceEnglishCursor(kb);
            break;
        case SOFT_KEYBOARD_PAGE_SYMBOLS:
            SoftKeyboard_PlaceSymbolCursor(kb);
            break;
        case SOFT_KEYBOARD_PAGE_HANGUL:
            SoftKeyboard_PlaceHangulCursor(kb);
            break;
    }
}
CLEAN_AS(func_ov095_0229aa74, SoftKeyboard_PlaceCursor)

/* func_ov095_0229aaac: a key around the page, else a Hangul key by its table. */
void SoftKeyboard_PlaceHangulCursor(SoftKeyboard *kb)
{
    if (SoftKeyboard_PlaceOutsideCursor(kb) != 0) {
        return;
    }
    if (kb->key >= SOFT_KEYBOARD_KEY_HANGUL_FIRST && kb->key <= SOFT_KEYBOARD_KEY_HANGUL_LAST) {
        int n = kb->key - SOFT_KEYBOARD_KEY_HANGUL_FIRST;
        kb->key_x = data_ov095_0229d020[n];
        kb->key_y = data_ov095_0229cff0[n];
    }
}
CLEAN_AS(func_ov095_0229aaac, SoftKeyboard_PlaceHangulCursor)

/* func_ov095_0229aae0: a key around the page, else a symbol key: the grid's 20 by 16 pixels
 * from (0x12, 0x70), and the keys after it. */
void SoftKeyboard_PlaceSymbolCursor(SoftKeyboard *kb)
{
    int key;

    if (SoftKeyboard_PlaceOutsideCursor(kb) != 0) {
        return;
    }
    key = kb->key;
    if (key < SOFT_KEYBOARD_KEY_SYMBOLS_FIRST) {
        return;
    }
    if (key <= SOFT_KEYBOARD_KEY_SYMBOLS_GRID_LAST) {
        int n = key - SOFT_KEYBOARD_KEY_SYMBOLS_FIRST;
        kb->key_x = (n % 10) * 20 + 0x12;
        kb->key_y = ((n / 10) * 2 + 14) * 8;
        return;
    }
    switch (key) {
        case 0x8e:
            kb->key_x = 0xda;
            kb->key_y = 0x70;
            break;
        case 0x8f:
            kb->key_x = 0xee;
            kb->key_y = 0x70;
            break;
        case 0x90:
            kb->key_x = 0xe4;
            kb->key_y = 0x88;
            break;
        case SOFT_KEYBOARD_KEY_SYMBOLS_LAST:
            kb->key_x = 0x80;
            kb->key_y = 0xa0;
            break;
    }
}
CLEAN_AS(func_ov095_0229aae0, SoftKeyboard_PlaceSymbolCursor)

/* func_ov095_0229ab68: a key around the page, else an English key: rows 16 pixels apart from
 * y 0x68, keys 20 pixels apart, each row offset, the long keys their own way. */
void SoftKeyboard_PlaceEnglishCursor(SoftKeyboard *kb)
{
    int key;

    if (SoftKeyboard_PlaceOutsideCursor(kb) != 0) {
        return;
    }
    key = kb->key;
    if (key < SOFT_KEYBOARD_KEY_ENGLISH_FIRST) {
        return;
    }
    if (key <= 0x46) {
        kb->key_y = 0x68;
        kb->key_x = (key - 0x3b) * 20 + 0xe;
        return;
    }
    if (key <= SOFT_KEYBOARD_KEY_ENGLISH_BACKSPACE) {
        kb->key_y = 0x78;
        kb->key_x = (key - 0x47) * 20 + 0x16;
        if (key == SOFT_KEYBOARD_KEY_ENGLISH_BACKSPACE) {
            kb->key_x += 0xa;
        }
        return;
    }
    if (key <= SOFT_KEYBOARD_KEY_ENGLISH_NEWLINE) {
        kb->key_y = 0x88;
        kb->key_x = (key - 0x52) * 20 + 0xe;
        if (key == SOFT_KEYBOARD_KEY_ENGLISH_NEWLINE) {
            kb->key_x += 0xe;
        }
        return;
    }
    if (key <= 0x67) {
        kb->key_y = 0x98;
        kb->key_x = (key - 0x5d) * 20 + 0x16;
        if (key == SOFT_KEYBOARD_KEY_ENGLISH_SHIFT) {
            kb->key_x -= 3;
        }
        return;
    }
    if (key <= SOFT_KEYBOARD_KEY_ENGLISH_LAST) {
        kb->key_y = 0xa8;
        if (key < SOFT_KEYBOARD_KEY_ENGLISH_SPACE) {
            kb->key_x = (key - 0x68) * 20 + 0x22;
        } else if (key == SOFT_KEYBOARD_KEY_ENGLISH_SPACE) {
            kb->key_x = 0x86;
        } else {
            kb->key_x = (key - 0x6c) * 20 + 0xae;
        }
    }
}
CLEAN_AS(func_ov095_0229ab68, SoftKeyboard_PlaceEnglishCursor)

/* func_ov095_0229ac2c: a key around the page placed (the tab row's, then the owner's): 1 when
 * it was one. */
int SoftKeyboard_PlaceOutsideCursor(SoftKeyboard *kb)
{
    if (SoftKeyboard_PlaceTabRowCursor(kb) != 0) {
        return 1;
    }
    switch (kb->kind) {
        case SOFT_KEYBOARD_KIND_CHAT:
            return SoftKeyboard_PlaceChatCursor(kb);
        case SOFT_KEYBOARD_KIND_LETTER:
        case SOFT_KEYBOARD_KIND_2:
            return SoftKeyboard_PlaceLetterCursor(kb);
        case SOFT_KEYBOARD_KIND_3:
        case SOFT_KEYBOARD_KIND_4:
        case SOFT_KEYBOARD_KIND_5:
            return SoftKeyboard_PlaceKind4Cursor(kb);
        default:
            return 0;
    }
}
CLEAN_AS(func_ov095_0229ac2c, SoftKeyboard_PlaceOutsideCursor)

/* func_ov095_0229ac8c: buttons 0x107 and 0x108. */
int SoftKeyboard_PlaceKind4Cursor(SoftKeyboard *kb)
{
    switch (kb->key) {
        case SOFT_KEYBOARD_KEY_BUTTON_107:
            kb->key_x = 0xc4;
            kb->key_y = 0xb6;
            return 1;
        case SOFT_KEYBOARD_KEY_BUTTON_108:
            kb->key_x = 0x7c;
            kb->key_y = 0xb6;
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov095_0229ac8c, SoftKeyboard_PlaceKind4Cursor)

/* func_ov095_0229acc0: the movable key (its place is taken when read) and buttons
 * 0x104-0x106. */
int SoftKeyboard_PlaceLetterCursor(SoftKeyboard *kb)
{
    switch (kb->key) {
        case SOFT_KEYBOARD_KEY_MOVABLE:
            return 1;
        case SOFT_KEYBOARD_KEY_BUTTON_104:
            kb->key_x = 0xca;
            kb->key_y = 0xb6;
            return 1;
        case SOFT_KEYBOARD_KEY_BUTTON_105:
            kb->key_x = 0x58;
            kb->key_y = 0xb6;
            return 1;
        case SOFT_KEYBOARD_KEY_BUTTON_106:
            kb->key_x = 0x74;
            kb->key_y = 0xb6;
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov095_0229acc0, SoftKeyboard_PlaceLetterCursor)

/* func_ov095_0229ad18: kind 0's key 0xf7, emotion tabs and menu tabs (at the top). */
int SoftKeyboard_PlaceChatCursor(SoftKeyboard *kb)
{
    if (kb->key == SOFT_KEYBOARD_KEY_CHAT_F7) {
        kb->key_x = OamBuffer_ObjX(data_ov095_0229e380) + 0x98;
        kb->key_y = OamBuffer_ObjY(data_ov095_0229e380) + 0x70;
        return 1;
    }
    if (kb->key >= SOFT_KEYBOARD_KEY_EMOTION_FIRST && kb->key <= SOFT_KEYBOARD_KEY_EMOTION_LAST) {
        kb->key_x = SoftKeyboard_EmotionTabX(kb, kb->key);
        kb->key_y = OamBuffer_ObjY(data_ov095_0229e814) + 0x68;
        return 1;
    }
    if (SoftKeyboard_IsMenuTab(kb, kb->key) != 0) {
        kb->key_x = MenuTabs_TabX(kb->key - SOFT_KEYBOARD_KEY_MENU_TAB_FIRST);
        kb->key_y = 8;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov095_0229ad18, SoftKeyboard_PlaceChatCursor)

/* func_ov095_0229ad90: an emotion tab's x (0x80 for another key). The keyboard is not used. */
int SoftKeyboard_EmotionTabX(SoftKeyboard *kb, int key)
{
    (void) kb;
    if (key >= SOFT_KEYBOARD_KEY_EMOTION_FIRST && key <= SOFT_KEYBOARD_KEY_EMOTION_LAST) {
        return OamBuffer_ObjX(&data_ov095_0229e814[key - SOFT_KEYBOARD_KEY_EMOTION_FIRST]) + 0x88;
    }
    return 0x80;
}
CLEAN_AS(func_ov095_0229ad90, SoftKeyboard_EmotionTabX)

/* func_ov095_0229adc4: the page tabs and side buttons (8 pixels higher outside kind 0's
 * layout). */
int SoftKeyboard_PlaceTabRowCursor(SoftKeyboard *kb)
{
    int key = kb->key;

    switch (key) {
        case SOFT_KEYBOARD_KEY_TAB_HANGUL:
        case SOFT_KEYBOARD_KEY_TAB_ENGLISH:
        case SOFT_KEYBOARD_KEY_TAB_SYMBOLS:
            kb->key_x = SoftKeyboard_PageTabX(kb, key);
            kb->key_y = OamBuffer_ObjY(&kb->controls[key - SOFT_KEYBOARD_KEY_TAB_HANGUL]) + 0x68;
            return 1;
        case SOFT_KEYBOARD_KEY_SIDE_LEFT:
            kb->key_x = 0x18;
            break;
        case SOFT_KEYBOARD_KEY_SIDE_RIGHT:
            kb->key_x = 0xe8;
            break;
        default:
            return 0;
    }
    kb->key_y = 0x54;
    if (SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_CHAT_LAYOUT) == 0) {
        kb->key_y -= 8;
    }
    return 1;
}
CLEAN_AS(func_ov095_0229adc4, SoftKeyboard_PlaceTabRowCursor)

/* func_ov095_0229ae5c: a page tab's x (0x80 for another key). */
int SoftKeyboard_PageTabX(SoftKeyboard *kb, int key)
{
    if (key >= SOFT_KEYBOARD_KEY_TAB_HANGUL && key <= SOFT_KEYBOARD_KEY_TAB_SYMBOLS) {
        return OamBuffer_ObjX(&kb->controls[key - SOFT_KEYBOARD_KEY_TAB_HANGUL]) + 0x88;
    }
    return 0x80;
}
CLEAN_AS(func_ov095_0229ae5c, SoftKeyboard_PageTabX)
