/* The scene of overlay 126 (vtable 0x022a20c8, include/cpp/ov126/Obj_ov126_022a20c8.h;
 * constructor KeyboardEntry_New, 0x4288 bytes): a menu scene (ov002/menu_scene.h) in which the
 * player types a short text on overlay 95's keyboard, as the evidence says:
 *
 * - it is loaded with overlays 124 and 95 as overlay group 15 (main/overlay_groups.h), which
 *   overlay 92's dispatcher opens for GroupParams modes 0x0b-0x17 (ov092/menu_dispatch.c) and
 *   overlay 90's menu for its tabs 9-12 in modes 0x18-0x1b (ov090/menu_tabs.h); the mode
 *   (KeyboardEntryMode) says what the text is, where it comes from (KeyboardEntry_LoadText) and
 *   where it goes (KeyboardEntry_Commit);
 * - the text is shown in overlay 124's entry field ("menu/han/...") at 0xb0, whose kind (by the
 *   mode) sets the most characters and the field's place on the screen (KeyboardEntry_Setup);
 * - its own files are "menu/chat2/b_cht.bch", "menu/letter/b_key.bsc" and "menu/han/obj.bpl";
 * - the keyboard is at 0x19c (as in overlay 122's letter writing, ov122/letter_write_scene.h,
 *   whose keyboard calls this scene shares), a pointer sprite (a Glider0) points at a key or at
 *   the text cursor, and the panel's buttons 6 and 7 end the input (KeyboardEntryPanelKind);
 * - when it ends without being cancelled, main is told so (GroupParams_SetC4C(1)), the text is
 *   committed and handed to main (GroupParams_SetText); the friend modes tell overlay 90's menu
 *   the friend roster changed (MenuTabs_MarkRosterChanged).
 *
 * The text cursor stands at a character (`position`) and is drawn at (`cursor_x`, `cursor_y`);
 * a range of characters can be marked (`mark_from` to `mark_to`, while KEYBOARD_ENTRY_FLAG_MARKING
 * is set) to be deleted or copied (`clipboard`) as one. */
#ifndef CLEAN_OV126_KEYBOARD_ENTRY_H
#define CLEAN_OV126_KEYBOARD_ENTRY_H

#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "main/wifi_friends.h"
#include "ov002/button_panel.h"
#include "ov002/error_message.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "types.h"

/* GroupParams' modes the scene is opened in (GroupParams_Mode), by what KeyboardEntry_LoadText
 * and KeyboardEntry_Commit do with the text. */
enum KeyboardEntryMode {
    KEYBOARD_ENTRY_MODE_DESIGN_TITLE = 0x0b,        /* the title of the current player's design `arg` */
    KEYBOARD_ENTRY_MODE_GENERAL_WORD = 0x0c,        /* compared with message `arg` of "st_general" */
    KEYBOARD_ENTRY_MODE_SONG = 0x0d,                /* compared with the names of the songs */
    KEYBOARD_ENTRY_MODE_PASSWORD = 0x0e,            /* compared with message `arg` of "st_password" */
    KEYBOARD_ENTRY_MODE_PLAYER_NAME = 0x0f,         /* the current player's name */
    KEYBOARD_ENTRY_MODE_TOWN_NAME = 0x10,           /* the town's name */
    KEYBOARD_ENTRY_MODE_11 = 0x11,                  /* main's text (GroupParams_Text) */
    KEYBOARD_ENTRY_MODE_CONSTELLATION = 0x12,       /* the name of constellation `arg` */
    KEYBOARD_ENTRY_MODE_13 = 0x13,                  /* starts empty */
    KEYBOARD_ENTRY_MODE_RECORD_DESIGN_TITLE = 0x14, /* the title of the town record's design */
    KEYBOARD_ENTRY_MODE_15 = 0x15,                  /* 0x15-0x17: main's text */
    KEYBOARD_ENTRY_MODE_17 = 0x17,
    KEYBOARD_ENTRY_MODE_FRIEND_TEXT_18 = 0x18,     /* text 0x18 of friend `arg` (main/wifi_friends.h) */
    KEYBOARD_ENTRY_MODE_NEW_FRIEND_TEXT_18 = 0x19, /* the same for a friend being added */
    KEYBOARD_ENTRY_MODE_FRIEND_TEXT_0C = 0x1a,     /* text 0x0c of friend `arg` */
    KEYBOARD_ENTRY_MODE_NEW_FRIEND_TEXT_0C = 0x1b  /* the same for a friend being added */
};

#define KEYBOARD_ENTRY_FIRST_FRIEND_MODE KEYBOARD_ENTRY_MODE_FRIEND_TEXT_18
#define KEYBOARD_ENTRY_LAST_FRIEND_MODE KEYBOARD_ENTRY_MODE_NEW_FRIEND_TEXT_0C

/* What main is told of the input (GroupParams_SetC4C). */
enum KeyboardEntryOutcome {
    KEYBOARD_ENTRY_OUTCOME_CANCELLED = 0, /* or the text did not match, or the name is taken */
    KEYBOARD_ENTRY_OUTCOME_DONE = 1,
    KEYBOARD_ENTRY_OUTCOME_NAME_TAKEN = 2 /* another player of the town has the name */
};

/* In `flags`. */
enum KeyboardEntryFlag {
    KEYBOARD_ENTRY_FLAG_DRAWN = 0x0001,           /* the scene is drawn (KeyboardEntry_Draw) */
    KEYBOARD_ENTRY_FLAG_CURSOR_SHOWN = 0x0002,    /* the text cursor is drawn, blinking */
    KEYBOARD_ENTRY_FLAG_MARKING = 0x0004,         /* `mark_from` to `mark_to` is marked */
    KEYBOARD_ENTRY_FLAG_COPIED = 0x0008,          /* `clipboard` holds copied text: the paste key is enabled */
    KEYBOARD_ENTRY_FLAG_FIELD_SHOWN = 0x0010,     /* the field was shown this frame (KeyboardEntry_ShowField) */
    KEYBOARD_ENTRY_FLAG_NEW_FRIEND = 0x0020,      /* modes 0x19 and 0x1b: other sounds for the panel's buttons */
    KEYBOARD_ENTRY_FLAG_CANCELLED = 0x0040,       /* the input ends cancelled */
    KEYBOARD_ENTRY_FLAG_POINTER_ON_TEXT = 0x0080, /* the pointer is at the text cursor, not at a key */
    KEYBOARD_ENTRY_FLAG_HINT = 0x0100             /* modes 0x10, 0x12, 0x18 and 0x19: a hint message and a
                                                   * cell after the text are shown */
};

/* The panel's buttons and its kinds (`panel_kind`, KeyboardEntry_SetPanelLayout). */
#define KEYBOARD_ENTRY_BUTTON_YES 3 /* the question's buttons (layout 9) */
#define KEYBOARD_ENTRY_BUTTON_NO 4
#define KEYBOARD_ENTRY_BUTTON_OK 6
#define KEYBOARD_ENTRY_BUTTON_CANCEL 7

enum KeyboardEntryPanelKind {
    KEYBOARD_ENTRY_PANEL_OK_CANCEL = 0, /* buttons 6 and 7 (layout 6, message 0xd8): modes 0x19, 0x1b */
    KEYBOARD_ENTRY_PANEL_CANCEL = 1,    /* button 6 (layout 5, message 0x65), which cancels; not set here */
    KEYBOARD_ENTRY_PANEL_OK = 2,        /* button 6 (layout 5, message 0x21): the other modes */
    KEYBOARD_ENTRY_PANEL_NONE = 3       /* no buttons; not set here */
};

/* The kinds of overlay 124's entry field (func_ov124_0229f27c, by the mode). */
enum KeyboardEntryFieldKind {
    KEYBOARD_ENTRY_FIELD_10 = 0, /* 10 characters (the modes not below) */
    KEYBOARD_ENTRY_FIELD_6 = 1,  /* 6 characters: modes 0x0f-0x12 and 0x18-0x1b */
    KEYBOARD_ENTRY_FIELD_16 = 2, /* 16 characters; no mode has it */
    KEYBOARD_ENTRY_FIELD_4 = 3,  /* 4 characters: mode 0x15 */
    KEYBOARD_ENTRY_FIELD_8 = 4   /* 8 characters; no mode has it */
};

#define KEYBOARD_ENTRY_TEXT_CHARS 16

/* The scene's states (MenuScene.state), each run by its handler of the table of
 * KeyboardEntry_RunState, and its sub states (MenuScene.sub_state), of the table of
 * KeyboardEntry_RunSubState. */
enum KeyboardEntryState {
    KEYBOARD_ENTRY_STATE_LOAD = 0,           /* KeyboardEntry_LoadState */
    KEYBOARD_ENTRY_STATE_START_WIPE_IN = 1,  /* KeyboardEntry_StartWipeIn */
    KEYBOARD_ENTRY_STATE_WIPE_IN = 2,        /* KeyboardEntry_WipeIn: then the input */
    KEYBOARD_ENTRY_STATE_FINISH = 3,         /* KeyboardEntry_Finish: the parent told, the wipe out */
    KEYBOARD_ENTRY_STATE_ADD_FRIEND = 4,     /* KeyboardEntry_AddFriend: until the connection takes it */
    KEYBOARD_ENTRY_STATE_WIPE_OUT = 5,       /* KeyboardEntry_WipeOut: then the end (phase 5) */
    KEYBOARD_ENTRY_STATE_ASK = 6,            /* KeyboardEntry_StartAsk; nothing here sets it */
    KEYBOARD_ENTRY_STATE_ASK_WIPE_OUT = 7,   /* KeyboardEntry_AskWipeOut: then the question */
    KEYBOARD_ENTRY_STATE_ASK_WIPE_IN = 8,    /* KeyboardEntry_AskWipeIn: then its buttons */
    KEYBOARD_ENTRY_STATE_BACK = 9,           /* KeyboardEntry_StartBack: from the question */
    KEYBOARD_ENTRY_STATE_BACK_WIPE_OUT = 10, /* KeyboardEntry_BackWipeOut: the panel set again */
    KEYBOARD_ENTRY_STATE_BACK_WIPE_IN = 11,  /* KeyboardEntry_BackWipeIn: then the input */
    KEYBOARD_ENTRY_STATES = 12
};

enum KeyboardEntrySubState {
    KEYBOARD_ENTRY_SUB_TOUCH = 0,          /* KeyboardEntry_Touch: the pen on the keys, the text, the panel */
    KEYBOARD_ENTRY_SUB_MARK_DRAG = 1,      /* KeyboardEntry_MarkDrag: the pen marks characters */
    KEYBOARD_ENTRY_SUB_KEY_TOUCH_HELD = 2, /* KeyboardEntry_KeyTouchHeld: a key held by the pen repeats */
    KEYBOARD_ENTRY_SUB_ASK_TOUCH = 3,      /* KeyboardEntry_AskTouch: the question's buttons, by the pen */
    KEYBOARD_ENTRY_SUB_KEYS = 4,           /* KeyboardEntry_Keys: the keyboard, by the buttons */
    KEYBOARD_ENTRY_SUB_ASK_KEYS = 5,       /* KeyboardEntry_AskKeys: the question, until the pen is used */
    KEYBOARD_ENTRY_SUB_TEXT_KEYS = 6,      /* KeyboardEntry_TextKeys: the pointer at the text cursor */
    KEYBOARD_ENTRY_SUB_MARK_KEYS = 7,      /* KeyboardEntry_MarkKeys: A held marks with the d-pad */
    KEYBOARD_ENTRY_SUB_POINTER_GLIDE = 8,  /* KeyboardEntry_PointerGlide: then `return_sub_state` */
    KEYBOARD_ENTRY_SUB_KEY_PRESS = 9,      /* KeyboardEntry_KeyPress: a key pressed by A */
    KEYBOARD_ENTRY_SUB_KEY_REPEAT = 10,    /* KeyboardEntry_KeyRepeat: a key held by A repeats */
    KEYBOARD_ENTRY_SUB_BACK_TO_KEYS = 11,  /* KeyboardEntry_BackToKeys */
    KEYBOARD_ENTRY_SUB_BACKSPACE = 12,     /* KeyboardEntry_BackspaceRepeat: B held deletes again */
    KEYBOARD_ENTRY_SUB_WHILE_L = 13,       /* KeyboardEntry_WhileL: until L is let go */
    KEYBOARD_ENTRY_SUB_WHILE_R = 14,       /* KeyboardEntry_WhileR: until R is let go */
    KEYBOARD_ENTRY_SUB_PANEL_PRESS = 15,   /* KeyboardEntry_PanelPress: a button's press plays, then phase 1 */
    KEYBOARD_ENTRY_SUB_ERROR = 16,         /* KeyboardEntry_Error: an error message, then the input */
    KEYBOARD_ENTRY_SUB_STATES = 17
};

/* The phases the scene sets (MenuScene.phase): 0 runs the base's wait (vtable slot 0x48), 1 the
 * states (slot 0x4c, KeyboardEntry_RunState), 2 the input (slot 0x50, KeyboardEntry_RunInput)
 * and 5 the end (slot 0x5c, KeyboardEntry_End). */
enum KeyboardEntryPhase {
    KEYBOARD_ENTRY_PHASE_WAIT = 0,
    KEYBOARD_ENTRY_PHASE_STATES = 1,
    KEYBOARD_ENTRY_PHASE_INPUT = 2,
    KEYBOARD_ENTRY_PHASE_END = 5
};

typedef struct KeyboardEntry {
    MenuScene base;                           /* 0x00 */
    s32 wipe_y;                               /* 0x94: MenuScene_WipeOffsetY's (KeyboardEntry_ScrollWipe) */
    s32 cursor_x;                             /* 0x98: the text cursor, in pixels */
    s32 cursor_y;                             /* 0x9c: always 0x28 */
    s32 hint_x;                               /* 0xa0: the hint cell's x, after the text */
    u16 flags;                                /* 0xa4: KeyboardEntryFlag */
    u8 max_chars;                             /* 0xa6: the field's characters */
    u8 blink;                                 /* 0xa7: counts frames; the cursor is drawn while bit 4 is set */
    u8 position;                              /* 0xa8: the cursor's character */
    u8 mark_from;                             /* 0xa9 */
    u8 mark_to;                               /* 0xaa */
    u8 field_left;                            /* 0xab: the field's first pixel */
    u8 field_right;                           /* 0xac: and its last, for the pen */
    u8 panel_kind;                            /* 0xad: KeyboardEntryPanelKind */
    u8 return_sub_state;                      /* 0xae: after KEYBOARD_ENTRY_SUB_POINTER_GLIDE and the holds */
    u8 field_width;                           /* 0xaf: the field's width in pixels */
    u8 field[0xec];                           /* 0xb0: overlay 124's entry field (a label, then a panel sprite at 0x6c) */
    u8 keyboard[0x2308];                      /* 0x19c: overlay 95's keyboard */
    LayerTask tasks[2];                       /* 0x24a4 */
    TextLabel labels[2];                      /* 0x24ec */
    u8 unk_25c4[0x1800];                      /* 0x25c4 */
    ButtonPanel panel;                        /* 0x3dc4 */
    Glider pointer;                           /* 0x3f90: a Glider0 */
    TextLabel hint;                           /* 0x3ff4: the hint message (KEYBOARD_ENTRY_FLAG_HINT) */
    TextLabel filter_text;                    /* 0x4060: the 8-bit text the taboo filter reads */
    WideText filter_wide;                     /* 0x40cc: the text carried through it */
    ErrorMessage error;                       /* 0x412c */
    u16 text[KEYBOARD_ENTRY_TEXT_CHARS];      /* 0x4248 */
    u16 clipboard[KEYBOARD_ENTRY_TEXT_CHARS]; /* 0x4268: the text copied (KeyboardEntry_Copy) */
} KeyboardEntry;

/* keyboard_entry.c: the destructors, the flags, the mode's text, the editing. */
KeyboardEntry *KeyboardEntry_Destroy(KeyboardEntry *self);
KeyboardEntry *KeyboardEntry_Delete(KeyboardEntry *self);
void KeyboardEntry_ClearFlags(KeyboardEntry *self, unsigned short mask);
void KeyboardEntry_SetFlags(KeyboardEntry *self, unsigned short mask);
int KeyboardEntry_TestFlags(KeyboardEntry *self, unsigned int mask);
void KeyboardEntry_FilterTaboo(KeyboardEntry *self);
void KeyboardEntry_Commit(KeyboardEntry *self);
void KeyboardEntry_CommitFriendText0C(KeyboardEntry *self);
void KeyboardEntry_CommitFriendText18(KeyboardEntry *self);
void KeyboardEntry_CommitRecordDesignTitle(KeyboardEntry *self);
void KeyboardEntry_CommitConstellation(KeyboardEntry *self);
void KeyboardEntry_CommitTownName(KeyboardEntry *self);
void KeyboardEntry_CommitPlayerName(KeyboardEntry *self);
void KeyboardEntry_CheckPassword(KeyboardEntry *self);
void KeyboardEntry_FindSong(KeyboardEntry *self);
void KeyboardEntry_CheckGeneralWord(KeyboardEntry *self);
void KeyboardEntry_CommitDesignTitle(KeyboardEntry *self);
void KeyboardEntry_LoadText(KeyboardEntry *self);
void KeyboardEntry_LoadFriendText0C(KeyboardEntry *self);
void KeyboardEntry_LoadFriendText18(KeyboardEntry *self);
WifiFriend *KeyboardEntry_Friend(void);
void KeyboardEntry_LoadConstellation(KeyboardEntry *self);
void KeyboardEntry_LoadDesignTitle(KeyboardEntry *self);

/* keyboard_entry_input.c: the buttons, the pointer, the keyboard's codes and the text. */
int KeyboardEntry_PressStart(KeyboardEntry *self);
int KeyboardEntry_PressL(KeyboardEntry *self);
int KeyboardEntry_PressR(KeyboardEntry *self);
int KeyboardEntry_HoldB(KeyboardEntry *self);
int KeyboardEntry_PressA(KeyboardEntry *self);
void KeyboardEntry_PointerFirstOfSet(KeyboardEntry *self);
void KeyboardEntry_ReleaseToKeys(KeyboardEntry *self);
void KeyboardEntry_BeginKeyPress(KeyboardEntry *self);
void KeyboardEntry_PlacePointer(KeyboardEntry *self);
void KeyboardEntry_GlidePointer(KeyboardEntry *self);
int KeyboardEntry_RestPointer(KeyboardEntry *self);
void KeyboardEntry_PointAtKey(KeyboardEntry *self);
void KeyboardEntry_SetPanelLayout(KeyboardEntry *self);
int KeyboardEntry_TouchPanel(KeyboardEntry *self);
void KeyboardEntry_Buzz(KeyboardEntry *self);
void KeyboardEntry_ShowMarks(KeyboardEntry *self);
void KeyboardEntry_ShowField(KeyboardEntry *self);
int KeyboardEntry_Type(KeyboardEntry *self, int character);
int KeyboardEntry_PutCharacter(KeyboardEntry *self, int character);
int KeyboardEntry_Backspace(KeyboardEntry *self, int buzz);
int KeyboardEntry_Convert(KeyboardEntry *self, int code);
int KeyboardEntry_RunCode(KeyboardEntry *self, int code);
int KeyboardEntry_TouchKey(KeyboardEntry *self);
void KeyboardEntry_Paste(KeyboardEntry *self);
void KeyboardEntry_Copy(KeyboardEntry *self);
void KeyboardEntry_MarkToPosition(KeyboardEntry *self);
void KeyboardEntry_MarkFromPosition(KeyboardEntry *self);
void KeyboardEntry_DeleteMarked(KeyboardEntry *self);
void KeyboardEntry_ClearMarks(KeyboardEntry *self);
int KeyboardEntry_IsMarking(KeyboardEntry *self);
int KeyboardEntry_MoveByKeys(KeyboardEntry *self, int keys);
int KeyboardEntry_TouchText(KeyboardEntry *self);
void KeyboardEntry_PlaceCursorAtX(KeyboardEntry *self, int x);
void KeyboardEntry_PlaceCursor(KeyboardEntry *self);
unsigned short KeyboardEntry_CharacterBeforeCursor(KeyboardEntry *self);
void KeyboardEntry_SetPosition(KeyboardEntry *self, char position);
void KeyboardEntry_ShowCursor(KeyboardEntry *self);
void KeyboardEntry_UpdateKeys(KeyboardEntry *self);
int KeyboardEntry_NothingToDelete(KeyboardEntry *self);
int KeyboardEntry_PressOk(KeyboardEntry *self);
void KeyboardEntry_PressButton(KeyboardEntry *self, int cancel);

/* keyboard_entry_states.c: how the input begins, the sub states. */
void KeyboardEntry_BeginAsk(KeyboardEntry *self);
int KeyboardEntry_BeginAskKeys(KeyboardEntry *self);
int KeyboardEntry_BeginAskTouch(KeyboardEntry *self);
int KeyboardEntry_BeginInput(KeyboardEntry *self);
u8 *KeyboardEntry_BeginKeys(KeyboardEntry *self);
u8 *KeyboardEntry_BeginTouch(KeyboardEntry *self);
void KeyboardEntry_Error(KeyboardEntry *self);
void KeyboardEntry_PanelPress(KeyboardEntry *self);
void KeyboardEntry_WhileR(KeyboardEntry *self);
void KeyboardEntry_WhileL(KeyboardEntry *self);
void KeyboardEntry_BackspaceRepeat(KeyboardEntry *self);
void KeyboardEntry_BackToKeys(KeyboardEntry *self);
void KeyboardEntry_KeyRepeat(KeyboardEntry *self);
void KeyboardEntry_KeyPress(KeyboardEntry *self);
void KeyboardEntry_PointerGlide(KeyboardEntry *self);
void KeyboardEntry_MarkKeys(KeyboardEntry *self);
void KeyboardEntry_TextToKeys(KeyboardEntry *self);
void KeyboardEntry_TextKeys(KeyboardEntry *self);
void KeyboardEntry_AskKeys(KeyboardEntry *self);
void KeyboardEntry_Keys(KeyboardEntry *self);
void KeyboardEntry_AskTouch(KeyboardEntry *self);
void KeyboardEntry_KeyTouchHeld(KeyboardEntry *self);
void KeyboardEntry_MarkDrag(KeyboardEntry *self);
void KeyboardEntry_Touch(KeyboardEntry *self);

/* keyboard_entry_scene.c: the screens, the frames, the states, the vtable's slots. */
void KeyboardEntry_LoadField(KeyboardEntry *self);
void KeyboardEntry_LoadScreens(KeyboardEntry *self);
void KeyboardEntry_SetUpLayers(void);
void KeyboardEntry_EndFrame(KeyboardEntry *self);
void KeyboardEntry_BeginFrame(KeyboardEntry *self);
void KeyboardEntry_EndInputFrame(KeyboardEntry *self);
void KeyboardEntry_BeginInputFrame(KeyboardEntry *self);
void KeyboardEntry_Teardown(KeyboardEntry *self);
void KeyboardEntry_Setup(KeyboardEntry *self);
void KeyboardEntry_ScrollWipe(KeyboardEntry *self);
void KeyboardEntry_BackWipeIn(KeyboardEntry *self);
void KeyboardEntry_BackWipeOut(KeyboardEntry *self);
void KeyboardEntry_StartBack(KeyboardEntry *self);
void KeyboardEntry_AskWipeIn(KeyboardEntry *self);
void KeyboardEntry_AskWipeOut(KeyboardEntry *self);
void KeyboardEntry_StartAsk(KeyboardEntry *self);
void KeyboardEntry_WipeOut(KeyboardEntry *self);
void KeyboardEntry_AddFriend(KeyboardEntry *self);
void KeyboardEntry_Finish(KeyboardEntry *self);
void KeyboardEntry_WipeIn(KeyboardEntry *self);
void KeyboardEntry_StartWipeIn(KeyboardEntry *self);
void KeyboardEntry_LoadState(KeyboardEntry *self);
int KeyboardEntry_End(KeyboardEntry *self);
int KeyboardEntry_Slot58(void);
int KeyboardEntry_Slot54(void);
int KeyboardEntry_RunInput(KeyboardEntry *self);
void KeyboardEntry_RunSubState(KeyboardEntry *self);
int KeyboardEntry_RunState(KeyboardEntry *self);
int KeyboardEntry_Draw(KeyboardEntry *self);
int KeyboardEntry_Close(KeyboardEntry *self);
int KeyboardEntry_Start(KeyboardEntry *self);
KeyboardEntry *KeyboardEntry_New(void);

#endif
