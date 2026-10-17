/* The software keyboard of overlay 95 ("menu/chat2/key*.bch"): the keyboard on the sub screen
 * that the chat (ov111, kind 0), the letter writing (ov122/letter_write_scene.h, kind 1) and
 * overlay 126 (kinds 3-5) keep inside their scenes and drive every frame.
 *
 * - It has three pages of keys (`page`): English (a QWERTY board, lower and upper case),
 *   symbols and Hangul (a two-set jamo board). Each page has a layout (`layout`, the files
 *   "key%d.bch" and "b_key%d.bsc"/"b_chtk%d.bsc"), and main keeps the page and each page's
 *   layout between scenes (main/group_params.h: GroupParams_C60, GroupParams_C90).
 * - A key is a number (SoftKeyboardKey): the keys of the pages, then the keys around them: the
 *   page tabs, the side buttons, the chat's menu tabs and emotion tabs, the owners' buttons.
 *   A key has a code (SoftKeyboard_KeyCode): a character of the page's layout, or a command
 *   (0x100-0x123) the keyboard (SoftKeyboard_HandleCommand) or its owner acts on.
 * - The d-pad moves a cursor between the keys (soft_keyboard_cursor.c), the pen picks the key
 *   under it (soft_keyboard_keys.c). The keys are drawn as OBJs of a cell per page whose
 *   palettes show a key normal (12), pressed (13) or disabled (14).
 * - Hangul is typed by jamo and composed into syllables before the cursor
 *   (soft_keyboard_hangul.c, soft_keyboard_text.c).
 *
 * The keyboard's object runs past its own fields: its owner keeps it with 0x2308 bytes of its
 * own after it (two layer tasks, then bytes of the owner's, then the screen and the emotion
 * characters, at fixed offsets from the keyboard). */
#ifndef CLEAN_OV095_SOFT_KEYBOARD_H
#define CLEAN_OV095_SOFT_KEYBOARD_H

#include "main/layer_load_task.h"
#include "main/oam_buffer.h"
#include "types.h"

/* The flags (`flags`). */
enum SoftKeyboardFlag {
    SOFT_KEYBOARD_FLAG_SCREEN_DIRTY = 0x0001, /* the screen is to be loaded (SoftKeyboard_QueueScreen) */
    SOFT_KEYBOARD_FLAG_02 = 0x0002,           /* set by the owner around a paste; cleared each draw */
    SOFT_KEYBOARD_FLAG_CHAT_LAYOUT = 0x0004,  /* kind 0's layout: the keys 8 pixels lower, the emotion tabs */
    SOFT_KEYBOARD_FLAG_08 = 0x0008,           /* set by the letter scene for a letter without a header */
    SOFT_KEYBOARD_FLAG_LEFT_KEYS = 0x0010,    /* the cursor moved off the keyboard (SoftKeyboard_MoveCursor: 4) */
    SOFT_KEYBOARD_FLAG_SHIFT = 0x0020,        /* the shift key is down: the next character goes back to lower case */
    SOFT_KEYBOARD_FLAG_TEXT_FULL = 0x0040,    /* a character did not fit: no room */
    SOFT_KEYBOARD_FLAG_TOO_WIDE = 0x0080,     /* a character did not fit: too wide */
    SOFT_KEYBOARD_FLAG_PROBING = 0x0100,      /* an insertion only tried: the two above are not set */
    SOFT_KEYBOARD_FLAG_TYPED = 0x0200         /* the typing sound played this frame */
};

/* The pages (`page`); 0 and 3 have no keys. */
enum SoftKeyboardPage {
    SOFT_KEYBOARD_PAGE_NONE = 0,
    SOFT_KEYBOARD_PAGE_ENGLISH = 1,
    SOFT_KEYBOARD_PAGE_SYMBOLS = 2,
    SOFT_KEYBOARD_PAGE_3 = 3,
    SOFT_KEYBOARD_PAGE_HANGUL = 4,
    SOFT_KEYBOARD_PAGES = 5
};

/* The owners (`kind`), by the buttons they have below the keys. */
enum SoftKeyboardKind {
    SOFT_KEYBOARD_KIND_CHAT = 0,   /* ov111: the menu tabs, key 0xf7 and the emotion tabs */
    SOFT_KEYBOARD_KIND_LETTER = 1, /* ov122: the scroll button (0x103) and buttons 0x104, 0x105 */
    SOFT_KEYBOARD_KIND_2 = 2,      /* buttons 0x103, 0x104 and 0x106 */
    SOFT_KEYBOARD_KIND_3 = 3,      /* ov126: no buttons */
    SOFT_KEYBOARD_KIND_4 = 4,      /* ov126: button 0x107 */
    SOFT_KEYBOARD_KIND_5 = 5       /* ov126: buttons 0x107 and 0x108 */
};

/* The layouts (`layout`): the files of each are the tables data_ov095_0229e5f8 (characters),
 * data_ov095_0229e61c (screen, kind 0) and data_ov095_0229e640 (screen). Only 2, 3, 6 and 8 have
 * characters (SoftKeyboard_KeyCode). */
enum SoftKeyboardLayout {
    SOFT_KEYBOARD_LAYOUT_ENGLISH_LOWER = 2, /* "key6" */
    SOFT_KEYBOARD_LAYOUT_ENGLISH_UPPER = 3, /* "key7" */
    SOFT_KEYBOARD_LAYOUT_SYMBOLS = 6,       /* "key9" */
    SOFT_KEYBOARD_LAYOUT_HANGUL = 8,        /* "key10" */
    SOFT_KEYBOARD_LAYOUTS = 9,
    SOFT_KEYBOARD_LAYOUT_SAVED = 9 /* asked for: the page's layout main keeps; in `layout`: none loaded */
};

/* The keys. A page's keys are numbered row by row. */
enum SoftKeyboardKey {
    SOFT_KEYBOARD_KEY_NONE = -1,
    /* English: rows 0x3b-0x46, 0x47-0x51, 0x52-0x5c, 0x5d-0x67 and 0x68-0x6f. */
    SOFT_KEYBOARD_KEY_ENGLISH_FIRST = 0x3b,
    SOFT_KEYBOARD_KEY_ENGLISH_BACKSPACE = 0x51, /* the end of row 1 */
    SOFT_KEYBOARD_KEY_ENGLISH_CAPS = 0x52,      /* the start of row 2 */
    SOFT_KEYBOARD_KEY_ENGLISH_NEWLINE = 0x5c,   /* the end of row 2 */
    SOFT_KEYBOARD_KEY_ENGLISH_SHIFT = 0x5d,     /* the start of row 3 */
    SOFT_KEYBOARD_KEY_ENGLISH_SPACE = 0x6b,     /* also over the places of 0x6a, 0x6c and 0x6d */
    SOFT_KEYBOARD_KEY_ENGLISH_LAST = 0x6f,
    /* Symbols: a grid of 10 by 3 (0x70-0x8d), then 0x8e and 0x8f right of row 0, 0x90 right of
     * rows 1 and 2, 0x91 (space) below. */
    SOFT_KEYBOARD_KEY_SYMBOLS_FIRST = 0x70,
    SOFT_KEYBOARD_KEY_SYMBOLS_GRID_LAST = 0x8d,
    SOFT_KEYBOARD_KEY_SYMBOLS_LAST = 0x91,
    /* Hangul: rows 0xc9-0xd2, 0xd3-0xdd, 0xde-0xe7, 0xe8-0xf1 and 0xf2-0xf6. */
    SOFT_KEYBOARD_KEY_HANGUL_FIRST = 0xc9,
    SOFT_KEYBOARD_KEY_HANGUL_BACKSPACE = 0xdd, /* the end of row 1 */
    SOFT_KEYBOARD_KEY_HANGUL_NEWLINE = 0xe7,   /* the end of row 2 */
    SOFT_KEYBOARD_KEY_HANGUL_SPACE = 0xf4,
    SOFT_KEYBOARD_KEY_HANGUL_LAST = 0xf6,
    /* The keys around the pages; their code is the key plus SOFT_KEYBOARD_CODE_OFFSET. */
    SOFT_KEYBOARD_KEY_CHAT_F7 = 0xf7,    /* kind 0: above the right side button (cell data_ov095_0229e380) */
    SOFT_KEYBOARD_KEY_TAB_HANGUL = 0xf8, /* the page tabs (the first three OBJs of `controls`) */
    SOFT_KEYBOARD_KEY_TAB_ENGLISH = 0xf9,
    SOFT_KEYBOARD_KEY_TAB_SYMBOLS = 0xfa,
    SOFT_KEYBOARD_KEY_MENU_TAB_FIRST = 0xfb, /* kind 0: the eight places of ov090's tab bar */
    SOFT_KEYBOARD_KEY_MENU_TAB_LAST = 0x102,
    SOFT_KEYBOARD_KEY_MOVABLE = 0x103, /* kinds 1, 2: a button the owner places (SoftKeyboard_SetMovableKeyPlace) */
    SOFT_KEYBOARD_KEY_BUTTON_104 = 0x104,
    SOFT_KEYBOARD_KEY_BUTTON_105 = 0x105,
    SOFT_KEYBOARD_KEY_BUTTON_106 = 0x106,
    SOFT_KEYBOARD_KEY_BUTTON_107 = 0x107,
    SOFT_KEYBOARD_KEY_BUTTON_108 = 0x108,
    SOFT_KEYBOARD_KEY_SIDE_LEFT = 0x109, /* the buttons at the two ends of the tab row */
    SOFT_KEYBOARD_KEY_SIDE_RIGHT = 0x10a,
    SOFT_KEYBOARD_KEY_EMOTION_FIRST = 0x10c, /* kind 0: one tab per motion slot filled */
    SOFT_KEYBOARD_KEY_EMOTION_LAST = 0x10f
};

#define SOFT_KEYBOARD_CODE_OFFSET 0xf

/* The codes the keyboard knows. */
enum SoftKeyboardCode {
    SOFT_KEYBOARD_CODE_NEWLINE = 0x0a,
    SOFT_KEYBOARD_CODE_COMMAND_FIRST = 0x100, /* 0x100-0x123 are commands */
    SOFT_KEYBOARD_CODE_BACKSPACE = 0x100,
    SOFT_KEYBOARD_CODE_101 = 0x101,
    SOFT_KEYBOARD_CODE_102 = 0x102,
    SOFT_KEYBOARD_CODE_PAGE_HANGUL = 0x107, /* the page tabs' codes */
    SOFT_KEYBOARD_CODE_PAGE_ENGLISH = 0x108,
    SOFT_KEYBOARD_CODE_PAGE_SYMBOLS = 0x109,
    SOFT_KEYBOARD_CODE_EMOTION_FIRST = 0x11b, /* the emotion tabs' codes */
    SOFT_KEYBOARD_CODE_SHIFT = 0x11f,
    SOFT_KEYBOARD_CODE_CAPS = 0x120,
    SOFT_KEYBOARD_CODE_121 = 0x121,
    SOFT_KEYBOARD_CODE_122 = 0x122,
    SOFT_KEYBOARD_CODE_123 = 0x123,
    SOFT_KEYBOARD_CODE_COMMAND_END = 0x124,
    SOFT_KEYBOARD_CODE_SPACE = 0x3000 /* also the code of a key with no character */
};

/* The palettes of a key's OBJs. */
enum SoftKeyboardKeyPalette {
    SOFT_KEYBOARD_PALETTE_NORMAL = 12,
    SOFT_KEYBOARD_PALETTE_PRESSED = 13,
    SOFT_KEYBOARD_PALETTE_DISABLED = 14
};

/* The keys that can be disabled (`disabled`, bits 0-13). Each page's table
 * (data_ov095_0229d050, ...d088, ...d0c0) gives its key for each; 0x110 is no key. */
enum SoftKeyboardSpecial {
    SOFT_KEYBOARD_SPECIAL_NEWLINE = 0,
    SOFT_KEYBOARD_SPECIAL_1 = 1, /* 1-5: no key on any page */
    SOFT_KEYBOARD_SPECIAL_2 = 2,
    SOFT_KEYBOARD_SPECIAL_3 = 3,
    SOFT_KEYBOARD_SPECIAL_4 = 4,
    SOFT_KEYBOARD_SPECIAL_5 = 5,
    SOFT_KEYBOARD_SPECIAL_BACKSPACE = 6,
    SOFT_KEYBOARD_SPECIAL_SHIFT = 7, /* English */
    SOFT_KEYBOARD_SPECIAL_6A = 8,    /* English: keys 0x6a, 0x6c and 0x6d */
    SOFT_KEYBOARD_SPECIAL_6C = 9,
    SOFT_KEYBOARD_SPECIAL_6D = 10,
    SOFT_KEYBOARD_SPECIAL_SIDE_LEFT = 11,
    SOFT_KEYBOARD_SPECIAL_SIDE_RIGHT = 12,
    SOFT_KEYBOARD_SPECIAL_CAPS = 13, /* English */
    SOFT_KEYBOARD_SPECIALS = 14
};

/* Where the cursor wrapped to (`wrap`): its pointer glides off that side. */
enum SoftKeyboardWrap { SOFT_KEYBOARD_WRAP_NONE = 0, SOFT_KEYBOARD_WRAP_LEFT = 1, SOFT_KEYBOARD_WRAP_RIGHT = 2 };

/* What SoftKeyboard_MoveCursor did. */
enum SoftKeyboardMove {
    SOFT_KEYBOARD_MOVE_NONE = 0,
    SOFT_KEYBOARD_MOVE_KEY = 1,      /* to another key */
    SOFT_KEYBOARD_MOVE_MENU_TAB = 2, /* to a menu tab */
    SOFT_KEYBOARD_MOVE_BUTTON = 3,   /* to a button 0x104-0x108 */
    SOFT_KEYBOARD_MOVE_LEFT = 4      /* off the keyboard (SOFT_KEYBOARD_FLAG_LEFT_KEYS) */
};

/* What SoftKeyboard_HangulAddJamo did. */
enum SoftKeyboardCompose {
    SOFT_KEYBOARD_COMPOSE_NEW = 0,     /* `carried` is a new character */
    SOFT_KEYBOARD_COMPOSE_REPLACE = 1, /* `composed` replaces the syllable before the cursor */
    SOFT_KEYBOARD_COMPOSE_SPLIT = 2    /* `composed` replaces it and `carried` follows */
};

#define SOFT_KEYBOARD_COMPOSITION 6 /* the jamo kept of the syllable being typed */
#define SOFT_KEYBOARD_EMOTIONS 4    /* main/motion_slots.h: MOTION_SLOTS */
#define SOFT_KEYBOARD_NO_EMOTION 0xff
#define SOFT_KEYBOARD_KEY_CHARS_SIZE 0x22c0
#define SOFT_KEYBOARD_SCREEN_SIZE 0x800
#define SOFT_KEYBOARD_EMOTION_CHARS_SIZE 0x1000

typedef struct SoftKeyboard {
    u16 composition[SOFT_KEYBOARD_COMPOSITION]; /* 0x00: the jamo of the syllable before the cursor */
    s32 composition_length;                     /* 0x0c */
    u16 composed;                               /* 0x10: SoftKeyboard_HangulAddJamo's syllable */
    u16 carried;                                /* 0x12: and the character after it */
    u16 flags;                                  /* 0x14: SoftKeyboardFlag */
    u8 page;                                    /* 0x16: SoftKeyboardPage */
    u8 emotion;                                 /* 0x17: the emotion tab picked, SOFT_KEYBOARD_NO_EMOTION */
    u8 emotion_count;                           /* 0x18: the motion slots filled */
    u8 side_palette[2];                         /* 0x19: of the side buttons */
    u8 layout;                                  /* 0x1b: SoftKeyboardLayout */
    u8 pressed_timer;                           /* 0x1c: frames the pressed key is still shown */
    u8 pad_1d[3];                               /* 0x1d */
    u32 disabled;                               /* 0x20: SoftKeyboardSpecial bits */
    s32 pressed_key;                            /* 0x24: the key under the pen or pressed, -1 */
    s32 key;                                    /* 0x28: the cursor's key, -1 */
    s32 key_x;                                  /* 0x2c: where the cursor's pointer points */
    s32 key_y;                                  /* 0x30 */
    s32 movable_x;                              /* 0x34: SOFT_KEYBOARD_KEY_MOVABLE's place */
    s32 movable_y;                              /* 0x38 */
    u8 emotion_numbers[SOFT_KEYBOARD_EMOTIONS]; /* 0x3c: the motions of the slots */
    u8 repeat_timer;                            /* 0x40: frames to a held key's next repeat */
    u8 pad_41;                                  /* 0x41 */
    u8 kind;                                    /* 0x42: SoftKeyboardKind */
    u8 wrap;                                    /* 0x43: SoftKeyboardWrap */
    OamEntry *controls;                         /* 0x44: the page tabs (3 OBJs), then the tab row's cell */
    u8 key_chars[SOFT_KEYBOARD_KEY_CHARS_SIZE]; /* 0x48: the layout's characters */
    /* The owner's part. */
    LayerTask chars_task;                               /* 0x2308: loads `key_chars` */
    LayerTask screen_task;                              /* 0x232c: loads `screen` */
    u8 owner_2350[0xd8];                                /* 0x2350: the owner's (ov122: two text labels) */
    u16 screen[SOFT_KEYBOARD_SCREEN_SIZE / 2];          /* 0x2428 */
    u8 emotion_chars[SOFT_KEYBOARD_EMOTION_CHARS_SIZE]; /* 0x2c28: "menu/chat2/ten0.bch" */
} SoftKeyboard;

/* soft_keyboard.c: flags, set up, layouts, commands, drawing. */
void SoftKeyboard_ClearFlags(SoftKeyboard *kb, int mask);
void SoftKeyboard_SetFlags(SoftKeyboard *kb, int mask);
int SoftKeyboard_TestFlags(SoftKeyboard *kb, unsigned int mask);
void SoftKeyboard_PlayTypeSound(SoftKeyboard *kb, int character);
void SoftKeyboard_PlaySe23(SoftKeyboard *kb);
void SoftKeyboard_PlaySe22(SoftKeyboard *kb);
void SoftKeyboard_DrawSideButtons(SoftKeyboard *kb, int x, int y);
void SoftKeyboard_DrawChatSideButtons(SoftKeyboard *kb, int x, int y);
int SoftKeyboard_DrawCaret(SoftKeyboard *kb, int x, int y, int priority);
u8 SoftKeyboard_PickedEmotion(SoftKeyboard *kb);
SoftKeyboard *SoftKeyboard_PickEmotionByCode(SoftKeyboard *kb, int code);
void SoftKeyboard_DropEmotion(SoftKeyboard *kb);
int SoftKeyboard_TouchEmotion(SoftKeyboard *kb);
int SoftKeyboard_TouchPageTab(SoftKeyboard *kb);
int SoftKeyboard_TouchChatF7(SoftKeyboard *kb);
void SoftKeyboard_DrawChatF7(SoftKeyboard *kb, int x, int y, int palette, int dy);
void SoftKeyboard_DrawEmotionTabs(SoftKeyboard *kb, int x, int y);
OamEntry *SoftKeyboard_KeyLooks(SoftKeyboard *kb);
void SoftKeyboard_DrawKeys(SoftKeyboard *kb, int x, int y);
void SoftKeyboard_DrawTabRow(SoftKeyboard *kb, int x, int y, int priority);
void SoftKeyboard_LoadEmotions(SoftKeyboard *kb);
int SoftKeyboard_LoadObjGraphics(SoftKeyboard *kb);
void SoftKeyboard_ClearFlag02(SoftKeyboard *kb);
void SoftKeyboard_SetFlag02(SoftKeyboard *kb);
int SoftKeyboard_HandleCommand(SoftKeyboard *kb, int code, int layer);
int SoftKeyboard_IsCommand(SoftKeyboard *kb, int code);
void SoftKeyboard_EnableBackspace(SoftKeyboard *kb, int character);
void SoftKeyboard_DisableEditKeys(SoftKeyboard *kb);
int SoftKeyboard_StepRepeat(SoftKeyboard *kb);
void SoftKeyboard_StartRepeat(SoftKeyboard *kb);
int SoftKeyboard_StepPressed(SoftKeyboard *kb);
void SoftKeyboard_MarkScreenDirty(SoftKeyboard *kb);
void SoftKeyboard_QueueScreen(SoftKeyboard *kb, unsigned int layer);
void SoftKeyboard_LoadScreenNow(SoftKeyboard *kb, int layer);
int SoftKeyboard_ReadScreen(SoftKeyboard *kb, const char *path);
int SoftKeyboard_LoadLetterChars(SoftKeyboard *kb, int layer);
void SoftKeyboard_SetFlag08(SoftKeyboard *kb);
void SoftKeyboard_Finish(SoftKeyboard *kb);
void SoftKeyboard_Init(SoftKeyboard *kb, int kind);
void SoftKeyboard_ReleaseShift(SoftKeyboard *kb, int layer);
void SoftKeyboard_ToggleShift(SoftKeyboard *kb, unsigned int layer);
void SoftKeyboard_ToggleCaps(SoftKeyboard *kb, int layer);
void SoftKeyboard_SwitchPage(SoftKeyboard *kb, int code, int layer);
void SoftKeyboard_Restore(SoftKeyboard *kb, unsigned int layer);
void SoftKeyboard_LoadLayout(SoftKeyboard *kb, int layout, unsigned int layer, int keep);
void SoftKeyboard_LoadSavedLayout(SoftKeyboard *kb, int layer);

/* soft_keyboard_cursor.c: the cursor and the d-pad. */
int SoftKeyboard_PressCursorKey(SoftKeyboard *kb);
int SoftKeyboard_MoveCursor(SoftKeyboard *kb, int keys);
void SoftKeyboard_PlaceCursorHome(SoftKeyboard *kb);
void SoftKeyboard_SetMovableKeyPlace(SoftKeyboard *kb, int x, int y);
int SoftKeyboard_CursorY(SoftKeyboard *kb);
int SoftKeyboard_CursorX(SoftKeyboard *kb);
int SoftKeyboard_MoveOutsideKeys(SoftKeyboard *kb, int keys);
int SoftKeyboard_MoveOnKind4Buttons(SoftKeyboard *kb, int keys);
int SoftKeyboard_MoveOnLetterButtons(SoftKeyboard *kb, int keys);
int SoftKeyboard_MoveOnChatTabs(SoftKeyboard *kb, int keys);
int SoftKeyboard_MoveOnTabRow(SoftKeyboard *kb, int keys);
void SoftKeyboard_CursorToTabRowAt(SoftKeyboard *kb, int x);
void SoftKeyboard_CursorToChatF7(SoftKeyboard *kb);
void SoftKeyboard_CursorToMenuTabAt(SoftKeyboard *kb, int x);
void SoftKeyboard_CursorToTabRowAtB(SoftKeyboard *kb, int x);
void SoftKeyboard_CursorToPageAt(SoftKeyboard *kb, int x);
void SoftKeyboard_CursorUpToTabRow(SoftKeyboard *kb);
void SoftKeyboard_NearestTabRowKey(SoftKeyboard *kb, int x);
void SoftKeyboard_CursorUpFromTabRow(SoftKeyboard *kb);
void SoftKeyboard_MoveOnHangul(SoftKeyboard *kb, int keys);
void SoftKeyboard_MoveOnSymbols(SoftKeyboard *kb, int keys);
void SoftKeyboard_MoveOnEnglish(SoftKeyboard *kb, int keys);
void SoftKeyboard_CursorToFirstButton(SoftKeyboard *kb);
void SoftKeyboard_CursorToLastButton(SoftKeyboard *kb);
void SoftKeyboard_PlaceCursor(SoftKeyboard *kb);
void SoftKeyboard_PlaceHangulCursor(SoftKeyboard *kb);
void SoftKeyboard_PlaceSymbolCursor(SoftKeyboard *kb);
void SoftKeyboard_PlaceEnglishCursor(SoftKeyboard *kb);
int SoftKeyboard_PlaceOutsideCursor(SoftKeyboard *kb);
int SoftKeyboard_PlaceKind4Cursor(SoftKeyboard *kb);
int SoftKeyboard_PlaceLetterCursor(SoftKeyboard *kb);
int SoftKeyboard_PlaceChatCursor(SoftKeyboard *kb);
int SoftKeyboard_EmotionTabX(SoftKeyboard *kb, int key);
int SoftKeyboard_PlaceTabRowCursor(SoftKeyboard *kb);
int SoftKeyboard_PageTabX(SoftKeyboard *kb, int key);

/* soft_keyboard_hangul.c: the jamo composed into syllables. */
int SoftKeyboard_HangulBackspace(SoftKeyboard *kb, u16 *text, int position);
void SoftKeyboard_HangulReset(SoftKeyboard *kb);
void SoftKeyboard_HangulPush(SoftKeyboard *kb, int jamo, int how);
int SoftKeyboard_HangulParse(SoftKeyboard *kb, const u16 *jamo, u16 *parts);
int SoftKeyboard_HangulCompose(SoftKeyboard *kb, const u16 *jamo);
int SoftKeyboard_HangulAddJamo(SoftKeyboard *kb, u16 jamo);
int SoftKeyboard_HangulFinalIndex(SoftKeyboard *kb, int jamo);
int SoftKeyboard_HangulJamoValue(SoftKeyboard *kb, unsigned int jamo);
int SoftKeyboard_IsJamo(SoftKeyboard *kb, unsigned int character);
int SoftKeyboard_IsConsonant(SoftKeyboard *kb, unsigned int character);
int SoftKeyboard_IsVowel(SoftKeyboard *kb, unsigned int character);

/* soft_keyboard_text.c: characters put into and taken out of the owner's text. */
u8 SoftKeyboard_TextColumnAt(SoftKeyboard *kb, const u16 *text, int length, int width, u8 x, u8 *index);
int SoftKeyboard_Convert3(SoftKeyboard *kb, int character);
int SoftKeyboard_Convert2(SoftKeyboard *kb, int character);
int SoftKeyboard_Convert1(SoftKeyboard *kb, int character);
int SoftKeyboard_ReplaceBefore(SoftKeyboard *kb, u16 *text, int character, int position);
int SoftKeyboard_DeleteRange(SoftKeyboard *kb, u16 *text, int from, int to, int length);
int SoftKeyboard_InsertInLines(SoftKeyboard *kb, u16 *text, u32 character, u8 *position, u32 length, u32 max_chars, u32 lines,
                               u32 width, u32 probe, u32 sound);
int SoftKeyboard_Insert(SoftKeyboard *kb, u16 *text, int character, u8 *position, int length, int width, int probe, int sound);
int SoftKeyboard_InsertComposed(SoftKeyboard *kb, u16 *text, int character, u8 *position, int length, int probe, int sound);
int SoftKeyboard_InsertAt(SoftKeyboard *kb, u16 *text, u16 character, int at, int length, int width);
int SoftKeyboard_CanInsert(SoftKeyboard *kb, u16 *text, int character, int at, int length, int width);

/* soft_keyboard_keys.c: the keys' codes, the pen and the keys' looks. */
int SoftKeyboard_KeyCode(SoftKeyboard *kb, int key, unsigned int layout);
int SoftKeyboard_HangulKeyCode(SoftKeyboard *kb, int key);
int SoftKeyboard_SymbolKeyCode(SoftKeyboard *kb, int key);
int SoftKeyboard_UpperKeyCode(SoftKeyboard *kb, int key);
u16 SoftKeyboard_LowerKeyCode(SoftKeyboard *kb, int key);
int SoftKeyboard_OutsideKeyCode(SoftKeyboard *kb, int key);
int SoftKeyboard_PressedKey(SoftKeyboard *kb);
int SoftKeyboard_KeyAt(SoftKeyboard *kb, int x, u8 y);
int SoftKeyboard_SideButtonAt(SoftKeyboard *kb, unsigned int x, unsigned int y);
int SoftKeyboard_HangulKeyAt(SoftKeyboard *kb, u16 x, u16 y);
int SoftKeyboard_SymbolKeyAt(SoftKeyboard *kb, unsigned int x, unsigned int y);
int SoftKeyboard_EnglishKeyAt(SoftKeyboard *kb, unsigned int x, unsigned int y);
void SoftKeyboard_ShowKeyPressed(SoftKeyboard *kb, int key);
void SoftKeyboard_SetKeyPalette(SoftKeyboard *kb, int key, int palette);
int SoftKeyboard_SetSideButtonPalette(SoftKeyboard *kb, int key, int palette);
void SoftKeyboard_SetHangulKeyPalette(SoftKeyboard *kb, int key, int palette);
void SoftKeyboard_SetSymbolKeyPalette(SoftKeyboard *kb, int key, int palette);
void SoftKeyboard_SetEnglishKeyPalette(SoftKeyboard *kb, int key, int palette);
void SoftKeyboard_ShowShift(SoftKeyboard *kb);
void SoftKeyboard_ReleasePressed(SoftKeyboard *kb);
void SoftKeyboard_ResetKeyLooks(SoftKeyboard *kb);
int SoftKeyboard_IsButtonKey(SoftKeyboard *kb, int key);
int SoftKeyboard_IsMenuTabKey(SoftKeyboard *kb, int key);
int SoftKeyboard_IsMenuTab(SoftKeyboard *kb, int key);
int SoftKeyboard_IsKeyDisabled(SoftKeyboard *kb, int key);
void SoftKeyboard_EnableSpecial(SoftKeyboard *kb, int special);
void SoftKeyboard_DisableSpecial(SoftKeyboard *kb, int special);
int SoftKeyboard_IsSpecialDisabled(SoftKeyboard *kb, int special);

#endif
