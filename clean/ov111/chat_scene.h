/* The scene of overlay 111 (vtable 0x022a1008, include/cpp/ov111/Obj_ov111_022a1008.h; its
 * profile at 0x022a0ee0 names the constructor ChatScene_New, 0x3ed8 bytes): a menu scene
 * (ov002/menu_scene.h) in which the player types a chat message of up to 16 characters and
 * posts it to the multiplayer session, as the evidence says:
 *
 * - it is tab 4 of overlay 90's menu (ov090/menu_tabs.h: overlay group 6, overlays 111 and
 *   95) and calls the menu as its parent process (MenuTabs_SelectTab, MenuTabs_ChildClosed);
 * - its screen is "menu/chat2/b_cht.bsc" ("b_cht_bg.bpl", "b_cht.bch"), with overlay 95's
 *   keyboard at 0xac, the keyboard the letter writing of overlay 122 also uses
 *   (ov122/letter_write_scene.h);
 * - the message typed is kept in a wide text of 16 characters (`line`) and posted as a quick
 *   message of the session (main/quick_message.h) under this system's slot, with the current
 *   player's name, once its taboo words are filtered out (ChatScene_PostMessage);
 * - the keyboard's expression keys make the player's character act one out
 *   (ChatScene_Express), at most one every 20 frames.
 *
 * The text cursor stands at a character (`cursor`) and is drawn `cursor_x` pixels into the
 * line, which starts at x 0x18 and is at most 0xa0 pixels wide. A range (`mark_from` to
 * `mark_to`, while CHAT_SCENE_FLAG_MARKING is set) can be marked with the pen or with A held
 * and the d-pad, and is copied (L, the copy key), replaced or deleted as one.
 *
 * A pointer sprite (`pointer`, a Glider0 of ov002/glide.h) points at the keyboard's key or at
 * the text cursor while the buttons are in use. */
#ifndef CLEAN_OV111_CHAT_SCENE_H
#define CLEAN_OV111_CHAT_SCENE_H

#include "main/label_box.h"
#include "main/layer_load_task.h"
#include "main/text_base.h"
#include "main/text_label.h"
#include "ov002/error_message.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "types.h"

/* In `flags`. */
enum ChatSceneFlag {
    CHAT_SCENE_FLAG_MARKING = 0x01,         /* `mark_from` to `mark_to` is marked */
    CHAT_SCENE_FLAG_POINTER_ON_TEXT = 0x02, /* the pointer is at the text cursor, not at a key */
    CHAT_SCENE_FLAG_DRAWN = 0x04,           /* the keyboard is drawn (ChatScene_Draw) */
    CHAT_SCENE_FLAG_COPIED = 0x08,          /* `clipboard` holds copied text: the paste key is enabled */
    CHAT_SCENE_FLAG_CLOSING = 0x10,         /* the menu is closing (tab 7 switched to) */
    CHAT_SCENE_FLAG_OPENING = 0x20          /* the menu opened with this tab (MenuTabs_IsOpening): the
                                             * setup runs one state a frame */
};

/* The scene's states (MenuScene.state), each run by its handler of the table of
 * ChatScene_RunState. */
enum ChatSceneState {
    CHAT_SCENE_STATE_LOAD_KEYBOARD = 0, /* ChatScene_LoadKeyboard */
    CHAT_SCENE_STATE_LOAD_SCREEN = 1,   /* ChatScene_LoadScreen */
    CHAT_SCENE_STATE_START_WIPE_IN = 2, /* ChatScene_StartWipeIn */
    CHAT_SCENE_STATE_WIPE_IN = 3,       /* ChatScene_WipeIn: then the input (phase 2) */
    CHAT_SCENE_STATE_LEAVE = 4,         /* ChatScene_StartWipeOut: set by ChatScene_SwitchTab */
    CHAT_SCENE_STATE_WIPE_OUT = 5,      /* ChatScene_WipeOut: then phase 5 */
    CHAT_SCENE_STATES = 6
};

/* The scene's sub states (MenuScene.sub_state), each run by its handler of the table of
 * ChatScene_RunSubState. */
enum ChatSceneSubState {
    CHAT_SCENE_SUB_TOUCH = 0,          /* ChatScene_IdleByTouch: the pen on the keyboard and the line */
    CHAT_SCENE_SUB_KEY_TOUCH_HELD = 1, /* ChatScene_RepeatTouchedKey: a key held down by the pen repeats */
    CHAT_SCENE_SUB_MARK_DRAG = 2,      /* ChatScene_MarkByDrag: the pen marks characters */
    CHAT_SCENE_SUB_KEYS = 3,           /* ChatScene_KeyboardByKeys: the keyboard, by the buttons */
    CHAT_SCENE_SUB_POINTER_GLIDE = 4,  /* ChatScene_WaitPointerGlide: then `return_sub_state` */
    CHAT_SCENE_SUB_KEY_PRESS = 5,      /* ChatScene_PressKey: a key pressed by A */
    CHAT_SCENE_SUB_KEY_REPEAT = 6,     /* ChatScene_RepeatKey: a key held down by A repeats */
    CHAT_SCENE_SUB_KEY_RELEASE = 7,    /* ChatScene_WaitKeyRelease: the pointer's release plays */
    CHAT_SCENE_SUB_BACKSPACE = 8,      /* ChatScene_RepeatBackspace: B held down deletes again */
    CHAT_SCENE_SUB_TEXT_KEYS = 9,      /* ChatScene_TextByKeys: the pointer at the text cursor */
    CHAT_SCENE_SUB_MARK_KEYS = 10,     /* ChatScene_MarkByKeys: A held down marks with the d-pad */
    CHAT_SCENE_SUB_WHILE_L = 11,       /* ChatScene_WaitLRelease */
    CHAT_SCENE_SUB_WHILE_R = 12,       /* ChatScene_WaitRRelease */
    CHAT_SCENE_SUB_SEND_IN = 13,       /* ChatScene_SendAnimIn: the send's look comes in */
    CHAT_SCENE_SUB_SEND_OUT = 14,      /* ChatScene_SendAnimOut: the message posted, the look goes */
    CHAT_SCENE_SUB_ERROR = 15,         /* ChatScene_UpdateError */
    CHAT_SCENE_SUB_STATES = 16
};

/* The phases the scene sets (MenuScene.phase; menu_scene.c's MenuScene_Update runs phase 0 by
 * the vtable's slot 0x48, 1 by 0x4c, 2 by 0x50 and 5 by 0x5c). */
enum ChatScenePhase {
    CHAT_SCENE_PHASE_WAIT = 0,
    CHAT_SCENE_PHASE_STATES = 1,      /* ChatScene_RunState */
    CHAT_SCENE_PHASE_INTERACTIVE = 2, /* ChatScene_RunInteractive */
    CHAT_SCENE_PHASE_DELETE = 5       /* ChatScene_RequestDelete */
};

/* The codes of the keyboard's keys (SoftKeyboard_KeyCode) the scene acts on; others are
 * characters or the keyboard's own (SoftKeyboard_HandleCommand). */
enum ChatSceneCode {
    CHAT_SCENE_CODE_BACKSPACE = 0x100,
    CHAT_SCENE_CODE_CONVERT_1 = 0x103, /* the character before the cursor converted (SoftKeyboard_Convert1) */
    CHAT_SCENE_CODE_CONVERT_2 = 0x104, /* (SoftKeyboard_Convert2) */
    CHAT_SCENE_CODE_CONVERT_3 = 0x105, /* (SoftKeyboard_Convert3) */
    CHAT_SCENE_CODE_SEND = 0x106,
    CHAT_SCENE_CODE_TAB_FIRST = 0x10a, /* 0x10a-0x111: the menu's tabs 0-7 */
    CHAT_SCENE_CODE_TAB_LAST = 0x111,
    CHAT_SCENE_CODE_COPY = 0x118,
    CHAT_SCENE_CODE_PASTE = 0x119,
    CHAT_SCENE_CODE_EXPRESSION_FIRST = 0x11b, /* 0x11b-0x11e: the four expression keys */
    CHAT_SCENE_CODE_EXPRESSION_LAST = 0x11e
};

/* What ChatScene_RunCode did (when the keyboard's own code handling did nothing). */
enum ChatSceneCodeResult {
    CHAT_SCENE_CODE_IGNORED = 0,
    CHAT_SCENE_CODE_DONE = 1,     /* a character, a backspace or the send key */
    CHAT_SCENE_CODE_CHANGED = 2,  /* a conversion, a copy, a paste or a tab key */
    CHAT_SCENE_CODE_EXPRESSED = 3 /* an expression key */
};

#define CHAT_SCENE_LINE_CHARS 16
#define CHAT_SCENE_LINE_WIDTH 0xa0 /* pixels */
#define CHAT_SCENE_LINE_X 0x18     /* where the line starts on the screen */

/* The wide text the message is typed into (vtable data_ov111_022a0ff0, 0x30 bytes): the wide
 * text base (main/text_base.h) and its 16 characters. */
typedef struct ChatLine {
    const TextVtable *vtable;                 /* 0x00 */
    u8 attributes[TEXT_BASE_ATTRIBUTES_SIZE]; /* 0x04: the wide text base's */
    u16 chars[CHAT_SCENE_LINE_CHARS];         /* 0x0e */
    u8 pad_2e[2];
} ChatLine;

/* Overlay 95's keyboard (ov095/soft_keyboard.h's SoftKeyboard, with its owner's part), 0x3c28
 * bytes. It has no constructor of its own: the scene's constructs the members below. */
typedef struct ChatKeyboard {
    u8 base[0x2308];     /* 0x0000 */
    LayerTask tasks[2];  /* 0x2308 */
    TextLabel labels[2]; /* 0x2350 */
    u16 map[0x400];      /* 0x2428: the screen's map, 32 by 32 entries */
    u8 chars[0x1000];    /* 0x2c28: the expression keys' characters (SoftKeyboard_LoadEmotions) */
} ChatKeyboard;

typedef struct ChatScene {
    MenuScene base;                       /* 0x00 */
    u8 unk_94[4];                         /* 0x94 */
    u8 return_sub_state;                  /* 0x98: after CHAT_SCENE_SUB_POINTER_GLIDE and the waits for a button */
    u8 unk_99;                            /* 0x99: only cleared */
    u8 send_frame;                        /* 0x9a: the send's look, 0-4 (ChatScene_ShowSendFrame) */
    u8 send_fade;                         /* 0x9b: 0-2, up while sending, down after; no send while above 0 */
    u8 blink;                             /* 0x9c: counts frames; the cursor is drawn while bit 4 is set */
    u8 send_delay;                        /* 0x9d: frames before the look goes again */
    u8 cursor;                            /* 0x9e: the cursor's character */
    u8 mark_from;                         /* 0x9f */
    u8 mark_to;                           /* 0xa0 */
    u8 cursor_x;                          /* 0xa1: in pixels from CHAT_SCENE_LINE_X */
    u8 reaction_wait;                     /* 0xa2: frames before the next expression */
    u8 pad_a3;                            /* 0xa3 */
    u16 flags;                            /* 0xa4: ChatSceneFlag */
    u8 pad_a6[2];                         /* 0xa6 */
    LabelBox *box;                        /* 0xa8: the line drawn, or NULL */
    ChatKeyboard keyboard;                /* 0xac */
    u32 message[13];                      /* 0x3cd4: an 8-bit text (main/quick_message.c's QuickMessageText)
                              * holding the line as posted */
    ChatLine line;                        /* 0x3d08 */
    Glider pointer;                       /* 0x3d38: a Glider0 */
    ErrorMessage error;                   /* 0x3d9c */
    u16 clipboard[CHAT_SCENE_LINE_CHARS]; /* 0x3eb8: the text copied */
} ChatScene;

ChatScene *ChatScene_Destroy(ChatScene *self);
ChatScene *ChatScene_Delete(ChatScene *self);
ChatLine *ChatLine_Destruct(ChatLine *line);
ChatLine *ChatLine_Delete(ChatLine *line);
int ChatLine_Chars(int line);
int ChatLine_Capacity(void);
void ChatScene_ClearFlags(ChatScene *self, unsigned short mask);
void ChatScene_SetFlags(ChatScene *self, unsigned short mask);
int ChatScene_TestFlags(ChatScene *self, unsigned int mask);
void ChatScene_UpdateKeys(ChatScene *self);
void ChatScene_DrawKeyboardLayer(ChatScene *self);
void ChatScene_SetKeyboardState(ChatScene *self, int state);
void ChatScene_PointerFirstOfSet(ChatScene *self);
void ChatScene_PointerThirdOfSet(ChatScene *self);
void ChatScene_PointerSecondOfSet(ChatScene *self);
void ChatScene_PlacePointer(ChatScene *self);
void ChatScene_GlidePointer(ChatScene *self);
void ChatScene_HidePointer(ChatScene *self);
void ChatScene_PointAtKey(ChatScene *self);
int ChatScene_SendOnStart(ChatScene *self);
int ChatScene_CopyOnL(ChatScene *self);
int ChatScene_PasteOnR(ChatScene *self);
int ChatScene_BackspaceOnB(ChatScene *self);
int ChatScene_PressOnA(ChatScene *self);
int ChatScene_MoveCursorByKeys(ChatScene *self, int keys);
void ChatScene_ClearMark(ChatScene *self);
int ChatScene_IsMarking(ChatScene *self);
unsigned short ChatScene_CharBeforeCursor(ChatScene *self);
void ChatScene_PlaceCursorAtChar(ChatScene *self);
void ChatScene_PlaceCursorAtX(ChatScene *self);
void ChatScene_MoveCursorToX(ChatScene *self, int x);
void ChatScene_FollowPen(ChatScene *self);
int ChatScene_TouchLine(ChatScene *self);
int ChatScene_Send(ChatScene *self);
int ChatScene_TouchSend(ChatScene *self);
int ChatScene_TouchKey(ChatScene *self);
int ChatScene_RunCode(ChatScene *self, int code);
void ChatScene_Buzz(ChatScene *self);
void ChatScene_Paste(ChatScene *self);
void ChatScene_Copy(ChatScene *self);
void ChatScene_ClearLine(ChatScene *self);
void ChatScene_Convert3(ChatScene *self);
int ChatScene_TryConvert3(ChatScene *self);
void ChatScene_Convert2(ChatScene *self);
int ChatScene_TryConvert2(ChatScene *self);
void ChatScene_Convert1(ChatScene *self);
int ChatScene_TryConvert1(ChatScene *self);
void ChatScene_DeleteMarked(ChatScene *self);
int ChatScene_Backspace(ChatScene *self, int buzz);
int ChatScene_InsertChar(ChatScene *self, int character);
void ChatScene_DismissOwnMessage(ChatScene *self);
void ChatScene_PostMessage(ChatScene *self);
void ChatScene_RedrawLine(ChatScene *self);
void ChatScene_EnsureBox(ChatScene *self);
void ChatScene_FreeBox(ChatScene *self);
void ChatScene_DrawKeyboard(ChatScene *self);
void ChatScene_ShowSendFrame(ChatScene *self, int frame);
void ChatScene_Teardown(ChatScene *self);
void ChatScene_Setup(ChatScene *self);

void ChatScene_UpdateError(ChatScene *self);
void ChatScene_SendAnimOut(ChatScene *self);
void ChatScene_SendAnimIn(ChatScene *self);
void ChatScene_Express(ChatScene *self);
void ChatScene_EnterInput(ChatScene *self);
void ChatScene_EnterKeys(ChatScene *self);
void ChatScene_EnterTouch(ChatScene *self);
void ChatScene_WaitRRelease(ChatScene *self);
void ChatScene_WaitLRelease(ChatScene *self);
void ChatScene_MarkByKeys(ChatScene *self);
void ChatScene_TextByKeys(ChatScene *self);
void ChatScene_RepeatBackspace(ChatScene *self);
void ChatScene_WaitKeyRelease(ChatScene *self);
void ChatScene_RepeatKey(ChatScene *self);
void ChatScene_PressKey(ChatScene *self);
void ChatScene_WaitPointerGlide(ChatScene *self);
void ChatScene_KeyboardByKeys(ChatScene *self);
void ChatScene_MarkByDrag(ChatScene *self);
void ChatScene_RepeatTouchedKey(ChatScene *self);
void ChatScene_IdleByTouch(ChatScene *self);
void ChatScene_WipeOut(ChatScene *self);
void ChatScene_StartWipeOut(ChatScene *self);
void ChatScene_WipeIn(ChatScene *self);
void ChatScene_StartWipeIn(ChatScene *self);
void ChatScene_LoadScreen(ChatScene *self);
void ChatScene_LoadKeyboard(ChatScene *self);
void ChatScene_LoadScreenFiles(ChatScene *self);
void ChatScene_SetUpLayer(void);
int ChatScene_SwitchTab(ChatScene *self, int tab, int keep_line);
int ChatScene_CheckLeave(ChatScene *self);
void ChatScene_EndFrame(ChatScene *self);
void ChatScene_UpdatePointer(ChatScene *self);
int ChatScene_Update(ChatScene *self);
int ChatScene_RequestDelete(ChatScene *self);
int ChatScene_Phase4(void);
int ChatScene_Phase3(void);
int ChatScene_RunInteractive(ChatScene *self);
void ChatScene_RunSubState(ChatScene *self);
int ChatScene_RunState(ChatScene *self);
int ChatScene_Draw(ChatScene *self);
int ChatScene_End(ChatScene *self);
int ChatScene_Start(ChatScene *self);
ChatScene *ChatScene_New(void);

#endif
