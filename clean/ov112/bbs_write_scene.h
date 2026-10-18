/* The scene of overlay 112 (vtable 0x022a20d0; constructor BbsWrite_New, 0x6c6c bytes): a menu
 * scene (ov002/menu_scene.h) in which the player writes a post for the town's bulletin board
 * (main/bbs.h), as the evidence says:
 *
 * - it is loaded with overlay 95 (overlay group 0x0a, which ov092's dispatcher asks for in
 *   GroupParams' mode 1, ov092/menu_dispatch.c), whose keyboard it keeps at 0x384; its own
 *   graphics are "menu/chat2/b_bbs.bpl", "b_bbs.bsc", "b_bbs.bch", "b_bbs2.bch", "b_cht.bch"
 *   and the keyboard's screen "menu/chat2/b_key0.bsc";
 * - the text is a post's 96 characters (`text`) broken into at most six lines of 16 characters
 *   and 0xa0 pixels (LetterView_BreakLines); its first line is the signature, menu message
 *   0x89 with the player's name, which the cursor cannot enter (`first_position` 0x10);
 * - on "yes" to the post question the text is posted (Bbs_PostText), sent to the other players
 *   of a Wi-Fi session (BbsWrite_SendPost) and the scene waits until they have it.
 *
 * As in overlay 122's letter writing (ov122/letter_write_scene.h), whose code this scene shares
 * in shape: the text cursor stands at a character (`position`) drawn at (`cursor_x`,
 * `cursor_y`), in pixels of the text: the lines at y 0x28 + 16 * line, from x 0x30 on. The text
 * scrolls by `scroll` pixels (0-0x3c) toward `scroll_target` (BbsWrite_StepScroll); the scroll
 * bar's knob (`scroll_button`) stands at two thirds of the scroll (`knob`). A range of characters
 * can be marked (`mark_from` to `mark_to`, BBS_WRITE_FLAG_MARKING), copied and pasted
 * (`clipboard`). A pointer sprite (`pointer`, a Glider0 of ov002/glide.h) points at the
 * keyboard's key, at the text cursor or at a button of the panel. */
#ifndef CLEAN_OV112_BBS_WRITE_SCENE_H
#define CLEAN_OV112_BBS_WRITE_SCENE_H

#include "main/bbs.h"
#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "ov002/button_panel.h"
#include "ov002/error_message.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov002/push_button.h"
#include "types.h"

/* In `flags`. */
enum BbsWriteFlag {
    BBS_WRITE_FLAG_DRAWN = 0x0001,             /* the keyboard, the scroll bar and the cursor are drawn
                                                * (BbsWrite_Draw) */
    BBS_WRITE_FLAG_CHARS_DIRTY = 0x0002,       /* the lines' characters are queued for the layer
                                                * (BbsWrite_EndFrame) */
    BBS_WRITE_FLAG_LINES_DIRTY = 0x0004,       /* the line labels were set again: shown at the frame's end */
    BBS_WRITE_FLAG_08 = 0x0008,                /* the characters queued at the frame's end; not set here */
    BBS_WRITE_FLAG_10 = 0x0010,                /* no line ends drawn (BbsWrite_Refresh); not set here */
    BBS_WRITE_FLAG_SCROLLING = 0x0020,         /* `scroll` moves toward `scroll_target` */
    BBS_WRITE_FLAG_CURSOR_SHOWN = 0x0040,      /* the text cursor is drawn, blinking */
    BBS_WRITE_FLAG_80 = 0x0080,                /* set while the keyboard is in; not read here */
    BBS_WRITE_FLAG_MARKING = 0x0100,           /* a range is marked from `mark_from` to `mark_to` */
    BBS_WRITE_FLAG_COPIED = 0x0200,            /* `clipboard` holds copied text: the paste key is enabled */
    BBS_WRITE_FLAG_ASKING = 0x0400,            /* the post or quit question is up: no line ends drawn */
    BBS_WRITE_FLAG_POINTER_ON_TEXT = 0x0800,   /* the pointer is at the text cursor, not at a key */
    BBS_WRITE_FLAG_POINTER_ON_BUTTON = 0x1000, /* the pointer follows the scroll bar's knob */
    BBS_WRITE_FLAG_QUITTING = 0x2000,          /* the question asks to quit without posting (else to post) */
    BBS_WRITE_FLAG_DATE_PENDING = 0x4000       /* today's date is drawn on the first frame of the wipe in */
};

/* The phases the scene sets (MenuScene.phase; menu_scene.c's MenuScene_Update runs phase 0 by
 * the vtable's slot 0x48, 1 by 0x4c, 2 by 0x50 and 5 by 0x5c). */
enum BbsWritePhase {
    BBS_WRITE_PHASE_WAIT = 0,        /* the base's wait */
    BBS_WRITE_PHASE_STATES = 1,      /* BbsWrite_RunState */
    BBS_WRITE_PHASE_INTERACTIVE = 2, /* BbsWrite_RunInteractive */
    BBS_WRITE_PHASE_END = 5          /* BbsWrite_End */
};

/* The scene's states (MenuScene.state), each run by its handler of the table of
 * BbsWrite_RunState. */
enum BbsWriteState {
    BBS_WRITE_STATE_START = 0,             /* BbsWrite_StartWipeIn */
    BBS_WRITE_STATE_WIPE_IN = 1,           /* BbsWrite_WipeIn: then the input */
    BBS_WRITE_STATE_ASK = 2,               /* BbsWrite_StartKeyboardWipeOut: the question asked */
    BBS_WRITE_STATE_KEYBOARD_WIPE_OUT = 3, /* BbsWrite_KeyboardWipeOut */
    BBS_WRITE_STATE_QUESTION = 4,          /* BbsWrite_ShowQuestion: the panel's question */
    BBS_WRITE_STATE_QUESTION_WIPE_IN = 5,  /* BbsWrite_QuestionWipeIn: then the panel's answer */
    BBS_WRITE_STATE_ANSWER_NO = 6,         /* BbsWrite_AnswerNoWipeOut: back to the writing */
    BBS_WRITE_STATE_QUESTION_WIPE_OUT = 7, /* BbsWrite_QuestionWipeOut */
    BBS_WRITE_STATE_BACK = 8,              /* BbsWrite_StartKeyboardWipeIn */
    BBS_WRITE_STATE_KEYBOARD_WIPE_IN = 9,  /* BbsWrite_KeyboardWipeIn: then the input */
    BBS_WRITE_STATE_ANSWER_YES = 10,       /* BbsWrite_FinishAfterAnswer: the scene ends */
    BBS_WRITE_STATE_FINISH_WIPE_OUT = 11,  /* BbsWrite_FinishWipeOut */
    BBS_WRITE_STATE_CLOSE = 12,            /* BbsWrite_StartCloseWipeOut: main closes the menu */
    BBS_WRITE_STATE_CLOSE_WIPE_OUT = 13,   /* BbsWrite_CloseWipeOut */
    BBS_WRITE_STATES = 14
};

/* The scene's sub states (MenuScene.sub_state), each run by its handler of the table of
 * BbsWrite_RunSubState. */
enum BbsWriteSubState {
    BBS_WRITE_SUB_TOUCH = 0,             /* BbsWrite_RunTouch: the pen on the panel, the text and the keyboard */
    BBS_WRITE_SUB_KNOB_DRAG = 1,         /* BbsWrite_RunKnobDrag: the pen drags the scroll bar's knob */
    BBS_WRITE_SUB_BAR_TOUCH = 2,         /* BbsWrite_RunBarTouch: the pen on the scroll bar draws the knob */
    BBS_WRITE_SUB_MARK_DRAG = 3,         /* BbsWrite_RunMarkDrag: the pen marks characters */
    BBS_WRITE_SUB_KEY_TOUCH_HELD = 4,    /* BbsWrite_RunKeyTouchHeld: a key held down by the pen repeats */
    BBS_WRITE_SUB_PANEL_TOUCH = 5,       /* BbsWrite_RunPanelTouch: the question's answer, by the pen */
    BBS_WRITE_SUB_KEYS = 6,              /* BbsWrite_RunKeys: the keyboard, by the buttons */
    BBS_WRITE_SUB_POINTER_GLIDE = 7,     /* BbsWrite_RunPointerGlide: until the pointer stops, then
                                          * `return_sub_state` */
    BBS_WRITE_SUB_KEY_PRESSED = 8,       /* BbsWrite_RunKeyPressed: a key pressed by A */
    BBS_WRITE_SUB_KEY_REPEAT = 9,        /* BbsWrite_RunKeyRepeat: a key held down by A repeats */
    BBS_WRITE_SUB_KEY_RELEASED = 10,     /* BbsWrite_RunKeyReleased: back to the keyboard */
    BBS_WRITE_SUB_BACKSPACE_REPEAT = 11, /* BbsWrite_RunBackspaceRepeat: B held down deletes again */
    BBS_WRITE_SUB_TEXT_KEYS = 12,        /* BbsWrite_RunTextKeys: the pointer at the text cursor, by the buttons */
    BBS_WRITE_SUB_MARK_KEYS = 13,        /* BbsWrite_RunMarkKeys: A held down marks with the d-pad */
    BBS_WRITE_SUB_WHILE_L = 14,          /* BbsWrite_RunWhileL: until L is let go */
    BBS_WRITE_SUB_WHILE_R = 15,          /* BbsWrite_RunWhileR: until R is let go */
    BBS_WRITE_SUB_SCROLL_PRESS = 16,     /* BbsWrite_RunScrollPress: the knob's press plays */
    BBS_WRITE_SUB_SCROLL_HELD = 17,      /* BbsWrite_RunScrollHeld: the d-pad scrolls while A is held */
    BBS_WRITE_SUB_SCROLL_RELEASE = 18,   /* BbsWrite_RunScrollRelease: the knob's release plays */
    BBS_WRITE_SUB_PANEL_KEYS = 19,       /* BbsWrite_RunPanelKeys: the question's answer, by the buttons */
    BBS_WRITE_SUB_PANEL_PRESSED = 20,    /* BbsWrite_RunPanelPressed: the pointer's press plays, then the answer */
    BBS_WRITE_SUB_BUTTON = 21,           /* BbsWrite_RunButton: a button of the panel pressed */
    BBS_WRITE_SUB_ERROR = 22,            /* BbsWrite_RunError: an error message, then the input; not set here */
    BBS_WRITE_SUB_STATES = 23
};

/* The codes of the keyboard's keys (func_ov095_0229c448) the scene acts on; others are
 * characters or the keyboard's own (func_ov095_0229ba44). */
enum BbsWriteCode {
    BBS_WRITE_CODE_NEWLINE = 0x0a,
    BBS_WRITE_CODE_BACKSPACE = 0x100,
    BBS_WRITE_CODE_CONVERT_1 = 0x103, /* the character before the cursor converted (func_ov095_0229bb9c) */
    BBS_WRITE_CODE_CONVERT_2 = 0x104, /* (func_ov095_0229bb98) */
    BBS_WRITE_CODE_CONVERT_3 = 0x105, /* (func_ov095_0229bb94) */
    BBS_WRITE_CODE_SCROLL = 0x112,    /* the scroll bar's knob pressed: the d-pad scrolls */
    BBS_WRITE_CODE_POST = 0x113,      /* the post question */
    BBS_WRITE_CODE_QUIT = 0x115,      /* the quit question */
    BBS_WRITE_CODE_COPY = 0x118,
    BBS_WRITE_CODE_PASTE = 0x119
};

#define BBS_WRITE_LINES 6
#define BBS_WRITE_LINE_CHARS 16
#define BBS_WRITE_LINE_WIDTH 0xa0 /* pixels */
#define BBS_WRITE_LINE_CHAR_BYTES 0x500
#define BBS_WRITE_FIRST_POSITION 0x10 /* after the signature's line */
#define BBS_WRITE_SCROLL_MAX 0x3c

typedef struct BbsWriteScene {
    MenuScene base;                                            /* 0x00 */
    s32 last_line;                                             /* 0x94: the last line's index
                                                                * (LetterView_BreakLines' end line) */
    s32 cursor_x;                                              /* 0x98: in pixels of the text */
    s32 cursor_y;                                              /* 0x9c */
    s32 keyboard_y;                                            /* 0xa0: the wipe's y, for the keyboard's objects */
    s32 unk_a4;                                                /* 0xa4: the wipe's y, only written */
    s32 panel_y;                                               /* 0xa8: the wipe's y, for the panel */
    u32 flags;                                                 /* 0xac: BbsWriteFlag */
    u8 unk_b0[4];                                              /* 0xb0 */
    s16 post_sequence;                                         /* 0xb4: the session's frame of the post sent */
    u8 scroll;                                                 /* 0xb6 */
    u8 scroll_target;                                          /* 0xb7 */
    u8 knob;                                                   /* 0xb8: two thirds of the scroll */
    u8 drag_touch_y;                                           /* 0xb9: the pen's y when the knob's drag began */
    u8 drag_knob;                                              /* 0xba: the knob when the drag began */
    u8 cue_scroll;                                             /* 0xbb: the scroll at which the knob last cued */
    u8 blink;                                                  /* 0xbc: counts frames; the cursor is drawn while bit
                                                                * 4 is set */
    u8 position;                                               /* 0xbd: the cursor's character in `text` */
    u8 mark_from;                                              /* 0xbe */
    u8 mark_to;                                                /* 0xbf */
    u8 first_position;                                         /* 0xc0: where the cursor may go back to */
    u8 return_sub_state;                                       /* 0xc1 */
    u8 answer;                                                 /* 0xc2: the panel's button pointed at by the keys,
                                                                * 0 button 3 (yes), 1 button 4 (no) */
    u8 pad_c3;                                                 /* 0xc3 */
    u16 text[BBS_POST_LENGTH];                                 /* 0xc4: the post */
    u16 clipboard[BBS_POST_LENGTH];                            /* 0x184: the text copied (BbsWrite_Copy) */
    ErrorMessage error;                                        /* 0x244 */
    LayerTask chars_task;                                      /* 0x360: the lines' characters to their layer */
    u8 keyboard[0x2308];                                       /* 0x384: overlay 95's keyboard; its functions
                                                                * also reach the members up to `lines` */
    u8 unk_268c[2][0x24];                                      /* 0x268c: layer tasks (func_020b9cfc) */
    TextLabel unk_26d4[2];                                     /* 0x26d4: only constructed and destructed */
    u8 unk_27ac[0x1800];                                       /* 0x27ac */
    TextLabel lines[BBS_WRITE_LINES];                          /* 0x3fac: the text's lines */
    PushButton scroll_button;                                  /* 0x4234: the scroll bar's knob */
    ButtonPanel panel;                                         /* 0x427c */
    Glider pointer;                                            /* 0x4448: a Glider0 */
    BbsLabel filter_text;                                      /* 0x44ac: the 8-bit text the taboo filter reads */
    BbsWideText filter_wide;                                   /* 0x4580: the post carried through it */
    u16 screen[0x400];                                         /* 0x4650: the board's screen ("b_bbs.bsc") */
    u8 line_chars[BBS_WRITE_LINES][BBS_WRITE_LINE_CHAR_BYTES]; /* 0x4e50: the lines drawn as characters */
    s32 line_start[BBS_WRITE_LINES + 1];                       /* 0x6c50: the first character of each line */
} BbsWriteScene;

/* bbs_write_text.c */
BbsWriteScene *BbsWrite_Destroy(BbsWriteScene *self);
BbsWriteScene *BbsWrite_Delete(BbsWriteScene *self);
int BbsWrite_PostDelivered(BbsWriteScene *self);
void BbsWrite_SendPost(BbsWriteScene *self);
void BbsWrite_EndDim(BbsWriteScene *self);
void BbsWrite_BeginDim(BbsWriteScene *self);
void BbsWrite_OpenDateLabel(BbsWriteScene *self, int line, int first_char, int p3, int p4);
void BbsWrite_ClearDateLabel(BbsWriteScene *self);
void BbsWrite_ShowDate(BbsWriteScene *self);
void BbsWrite_FilterTaboo(BbsWriteScene *self);
void BbsWrite_PointerFirstOfSet(BbsWriteScene *self);
void BbsWrite_BeginKeyReleased(BbsWriteScene *self);
void BbsWrite_BeginKeyPressed(BbsWriteScene *self);
void BbsWrite_PlacePointer(BbsWriteScene *self);
void BbsWrite_GlidePointerTo(BbsWriteScene *self, int x, int y);
void BbsWrite_GlidePointer(BbsWriteScene *self);
void BbsWrite_HidePointer(BbsWriteScene *self);
void BbsWrite_PointAtKey(BbsWriteScene *self);
void BbsWrite_PressPanelButton(BbsWriteScene *self, unsigned char state, int button);
void BbsWrite_UpdateKeys(BbsWriteScene *self);
int BbsWrite_MoveCursorByKeys(BbsWriteScene *self, int keys);
int BbsWrite_LineOf(BbsWriteScene *self, int position);
void BbsWrite_PlaceCursor(BbsWriteScene *self);
unsigned short BbsWrite_CharBeforeCursor(BbsWriteScene *self);
void BbsWrite_SetPosition(BbsWriteScene *self, char position);
void BbsWrite_StartEditing(BbsWriteScene *self);
int BbsWrite_DragMark(BbsWriteScene *self);
void BbsWrite_Nothing(BbsWriteScene *self);
int BbsWrite_StartTouch(BbsWriteScene *self);
void BbsWrite_TouchAt(BbsWriteScene *self, int x, int y);
unsigned char BbsWrite_PositionAt(BbsWriteScene *self, int line, s32 *x);
void BbsWrite_DeleteMarked(BbsWriteScene *self);
void BbsWrite_EndMark(BbsWriteScene *self);
int BbsWrite_HasMark(BbsWriteScene *self);
void BbsWrite_ScrollByKeys(BbsWriteScene *self);
void BbsWrite_MoveKnobToTouch(BbsWriteScene *self);
void BbsWrite_DragKnob(BbsWriteScene *self);
void BbsWrite_SetKnob(BbsWriteScene *self, int knob);
int BbsWrite_TouchesBar(BbsWriteScene *self);
int BbsWrite_StartDrag(BbsWriteScene *self);
void BbsWrite_ScrollToCursor(BbsWriteScene *self);
void BbsWrite_StepScroll(BbsWriteScene *self);
int BbsWrite_IsScrolling(BbsWriteScene *self);
void BbsWrite_ScrollTo(BbsWriteScene *self, char target);
void BbsWrite_SetScroll(BbsWriteScene *self, unsigned char scroll);
void BbsWrite_QueueLineChars(BbsWriteScene *self);
void BbsWrite_Idle(BbsWriteScene *self);
void BbsWrite_CloseLineBoxes(BbsWriteScene *self);
void BbsWrite_ShowLines(BbsWriteScene *self);
void BbsWrite_MarkLines(BbsWriteScene *self, int color_38, int color_39, unsigned int from, unsigned int count);
void BbsWrite_ShowMark(BbsWriteScene *self);
void BbsWrite_Refresh(BbsWriteScene *self);
void BbsWrite_ClearFlags(BbsWriteScene *self, unsigned int mask);
void BbsWrite_SetFlags(BbsWriteScene *self, unsigned int mask);
int BbsWrite_TestFlags(BbsWriteScene *self, int mask);

/* bbs_write_input.c */
void BbsWrite_BeginPanelKeys(BbsWriteScene *self);
int BbsWrite_BeginPanelTouch(BbsWriteScene *self);
int BbsWrite_BeginInput(BbsWriteScene *self);
unsigned char *BbsWrite_BeginKeys(BbsWriteScene *self);
unsigned char *BbsWrite_BeginTouch(BbsWriteScene *self);
void BbsWrite_PlaySound34(BbsWriteScene *self);
void BbsWrite_CloseOnRequest(BbsWriteScene *self);
void BbsWrite_AnswerNo(BbsWriteScene *self);
void BbsWrite_AnswerYes(BbsWriteScene *self);
void BbsWrite_AskQuit(BbsWriteScene *self);
void BbsWrite_AskPost(BbsWriteScene *self);
void BbsWrite_Paste(BbsWriteScene *self);
void BbsWrite_Copy(BbsWriteScene *self);
int BbsWrite_ConvertChar(BbsWriteScene *self, int code);
int BbsWrite_TypeChar(BbsWriteScene *self, int code);
int BbsWrite_InsertChar(BbsWriteScene *self, int code, int notify);
int BbsWrite_Backspace(BbsWriteScene *self, int sound_on_fail);
int BbsWrite_Command(BbsWriteScene *self, int code);
int BbsWrite_TouchKey(BbsWriteScene *self);
int BbsWrite_PostKey(BbsWriteScene *self);
int BbsWrite_CopyKey(BbsWriteScene *self);
int BbsWrite_PasteKey(BbsWriteScene *self);
int BbsWrite_SwitchPointerKey(BbsWriteScene *self);
int BbsWrite_BackspaceKey(BbsWriteScene *self);
int BbsWrite_PressKeyByA(BbsWriteScene *self);
void BbsWrite_RunError(BbsWriteScene *self);
void BbsWrite_RunButton(BbsWriteScene *self);
void BbsWrite_RunPanelPressed(BbsWriteScene *self);
void BbsWrite_RunPanelKeys(BbsWriteScene *self);
void BbsWrite_RunScrollRelease(BbsWriteScene *self);
void BbsWrite_RunScrollHeld(BbsWriteScene *self);
void BbsWrite_RunScrollPress(BbsWriteScene *self);
void BbsWrite_RunWhileR(BbsWriteScene *self);
void BbsWrite_RunWhileL(BbsWriteScene *self);
void BbsWrite_RunMarkKeys(BbsWriteScene *self);
void BbsWrite_RunTextKeys(BbsWriteScene *self);
void BbsWrite_RunBackspaceRepeat(BbsWriteScene *self);
void BbsWrite_RunKeyReleased(BbsWriteScene *self);
void BbsWrite_RunKeyRepeat(BbsWriteScene *self);
void BbsWrite_RunKeyPressed(BbsWriteScene *self);
void BbsWrite_RunPointerGlide(BbsWriteScene *self);
void BbsWrite_RunKeys(BbsWriteScene *self);
void BbsWrite_RunPanelTouch(BbsWriteScene *self);
void BbsWrite_RunKeyTouchHeld(BbsWriteScene *self);
void BbsWrite_RunMarkDrag(BbsWriteScene *self);
void BbsWrite_RunBarTouch(BbsWriteScene *self);
void BbsWrite_RunKnobDrag(BbsWriteScene *self);
void BbsWrite_RunTouch(BbsWriteScene *self);

/* bbs_write_scene.c */
void BbsWrite_LoadScreens(BbsWriteScene *self);
void BbsWrite_SetLayers(void);
void BbsWrite_EndFrame(BbsWriteScene *self);
void BbsWrite_UpdateSprites(BbsWriteScene *self);
void BbsWrite_Release(BbsWriteScene *self);
void BbsWrite_Setup(BbsWriteScene *self);
void BbsWrite_CloseWipeOut(BbsWriteScene *self);
void BbsWrite_StartCloseWipeOut(BbsWriteScene *self);
void BbsWrite_FinishWipeOut(BbsWriteScene *self);
void BbsWrite_FinishAfterAnswer(BbsWriteScene *self);
void BbsWrite_KeyboardWipeIn(BbsWriteScene *self);
void BbsWrite_StartKeyboardWipeIn(BbsWriteScene *self);
void BbsWrite_QuestionWipeOut(BbsWriteScene *self);
void BbsWrite_AnswerNoWipeOut(BbsWriteScene *self);
void BbsWrite_QuestionWipeIn(BbsWriteScene *self);
void BbsWrite_ShowQuestion(BbsWriteScene *self);
void BbsWrite_KeyboardWipeOut(BbsWriteScene *self);
void BbsWrite_StartKeyboardWipeOut(BbsWriteScene *self);
void BbsWrite_WipeIn(BbsWriteScene *self);
void BbsWrite_StartWipeIn(BbsWriteScene *self);
int BbsWrite_End(BbsWriteScene *self);
int BbsWrite_Phase4Idle(void);
int BbsWrite_Phase3Idle(void);
int BbsWrite_RunInteractive(BbsWriteScene *self);
void BbsWrite_RunSubState(BbsWriteScene *self);
int BbsWrite_RunState(BbsWriteScene *self);
int BbsWrite_Draw(BbsWriteScene *self);
int BbsWrite_Close(BbsWriteScene *self);
int BbsWrite_Start(BbsWriteScene *self);
BbsWriteScene *BbsWrite_New(void);

#endif
