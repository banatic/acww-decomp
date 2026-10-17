/* The scene of overlay 122 (vtable 0x022a2738, include/cpp/ov122/Obj_ov122_022a2738.h; its
 * profile at 0x022a26b0, class 0xa5, names the constructor func_ov122_022a24bc, 0x4980 bytes):
 * a menu scene (ov002/menu_scene.h) in which a player writes a letter, as the evidence says:
 *
 * - it is loaded with overlay 95 (overlay group 8, main/overlay_groups.h), whose keyboard
 *   ("menu/chat2/key*.bch") it keeps at 0xc0, and its own screen is "menu/chat2/b_key0.bsc";
 * - it shows the letter it is given (`letter`) in main's letter view (main/letter_view.h) and
 *   edits the letter's three texts (main/letter.h): the header (10 characters, with the
 *   addressee's name put in at `header_line`), the body (64) and the footer (16);
 * - when it ends it filters the taboo words out of the three texts (LetterWrite_FilterTaboo)
 *   and keeps the header and the footer as the player's defaults (LetterWrite_SaveDefaults).
 *
 * The text cursor stands in one part of the letter (`part`, LetterWritePart) at a character
 * (`position`) and is drawn at (`cursor_x`, `cursor_y`), in pixels of the letter: the header's
 * line at y 0x28, the body's four lines from y 0x40 on, 16 pixels apart, and the footer at y
 * 0x88, from x 0x30 on. The letter scrolls by `scroll` pixels (0-0x58) toward `scroll_target`
 * (LetterWrite_StepScroll), by the d-pad, by dragging the scroll button or to keep the cursor in
 * view. A range of characters can be marked with the pen (`mark_from` to `mark_to`, while
 * LETTER_WRITE_FLAG_MARKING is set) and is deleted as one (LetterWrite_DeleteMarked).
 *
 * A pointer sprite (`pointer`, a Glider0 of ov002/glide.h) points at the keyboard's key, at
 * the text cursor, at a row of the choice or at a button of the panel. */
#ifndef CLEAN_OV122_LETTER_WRITE_SCENE_H
#define CLEAN_OV122_LETTER_WRITE_SCENE_H

#include "main/letter.h"
#include "main/letter_view.h"
#include "main/mail_part_texts.h"
#include "main/text_label.h"
#include "ov002/button_panel.h"
#include "ov002/error_message.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov002/paged_choice.h"
#include "ov002/push_button.h"
#include "types.h"

/* In `flags`. */
enum LetterWriteFlag {
    LETTER_WRITE_FLAG_01 = 0x0001,                /* the panel and keyboard follow `unk_94` (func_ov122_022a223c) */
    LETTER_WRITE_FLAG_02 = 0x0002,                /* the panel follows `unk_98` (func_ov122_022a223c) */
    LETTER_WRITE_FLAG_CURSOR_SHOWN = 0x0004,      /* the text cursor is drawn, blinking (func_ov122_022a223c) */
    LETTER_WRITE_FLAG_MARKING = 0x0008,           /* the pen marks from `mark_from` to `mark_to` */
    LETTER_WRITE_FLAG_NO_HEADER = 0x0010,         /* the header cannot be entered */
    LETTER_WRITE_FLAG_DIMMED = 0x0020,            /* the screen is dimmed: scrolled past 0x40 */
    LETTER_WRITE_FLAG_POINTER_ON_TEXT = 0x0100,   /* the pointer is at the text cursor, not at a key */
    LETTER_WRITE_FLAG_POINTER_ON_BUTTON = 0x0200, /* the pointer follows the scroll button */
    LETTER_WRITE_FLAG_KEY_0C_SHOWN = 0x0400,      /* the keyboard's key 12 is shown (func_ov122_022a14c0) */
    LETTER_WRITE_FLAG_SCROLLING = 0x0800,         /* `scroll` moves toward `scroll_target` */
    LETTER_WRITE_FLAG_1000 = 0x1000,              /* set whenever the cursor's part is set */
    LETTER_WRITE_FLAG_CLOSE_ASKED = 0x2000        /* main asked the menu to close (StateFlags_MenuCloseAsked) */
};

/* The part of the letter the cursor is in (`part`). */
enum LetterWritePart {
    LETTER_WRITE_PART_HEADER = 0,       /* the header before the addressee's name */
    LETTER_WRITE_PART_HEADER_AFTER = 1, /* the header after the name: `position` counts from
                                         * `header_line` */
    LETTER_WRITE_PART_BODY = 2,
    LETTER_WRITE_PART_FOOTER = 3
};

/* The scene's sub states (MenuScene.sub_state), each run by its handler of the table of
 * func_ov122_022a1f40. Only those set here are named. */
enum LetterWriteSubState {
    LETTER_WRITE_SUB_TOUCH = 0,             /* func_ov122_022a1380: the pen on the keyboard and the letter */
    LETTER_WRITE_SUB_04 = 4,                /* func_ov122_022a1220 */
    LETTER_WRITE_SUB_CHOICE_TOUCH = 5,      /* func_ov122_022a116c: the choice's rows, by the pen */
    LETTER_WRITE_SUB_KEYS = 6,              /* func_ov122_022a0afc: the keyboard, by the buttons */
    LETTER_WRITE_SUB_POINTER_GLIDE = 7,     /* func_ov122_022a0ad0: until the pointer stops, then
                                           * `return_sub_state` */
    LETTER_WRITE_SUB_08 = 8,                /* func_ov122_022a09f4: a key pressed */
    LETTER_WRITE_SUB_0A = 10,               /* func_ov122_022a0974 */
    LETTER_WRITE_SUB_0C = 12,               /* func_ov122_022a0848 */
    LETTER_WRITE_SUB_PANEL_KEYS = 0x13,     /* func_ov122_022a05d0: the panel, by the buttons */
    LETTER_WRITE_SUB_CHOICE_KEYS = 0x14,    /* func_ov122_022a053c: the choice, by the buttons */
    LETTER_WRITE_SUB_CHOICE_OPENING = 0x16, /* func_ov122_022a04bc */
    LETTER_WRITE_SUB_CHOICE_CLOSING = 0x18, /* func_ov122_022a03b0: then what was picked */
    LETTER_WRITE_SUB_BUTTON = 0x19          /* func_ov122_022a02c8: a button of the panel pressed */
};

#define LETTER_WRITE_SCROLL_MAX 0x58
#define LETTER_WRITE_SHOWN_HEADER_CHARS 40 /* the header with the name in (LetterView_SetGreeting) */

typedef struct LetterWriteScene {
    MenuScene base;                                    /* 0x00 */
    s32 unk_94;                                        /* 0x94: func_ov002_02207f60's (func_ov122_022a1998) */
    s32 unk_98;                                        /* 0x98 */
    s32 cursor_x;                                      /* 0x9c: in pixels of the letter */
    s32 cursor_y;                                      /* 0xa0 */
    u8 unk_a4[4];                                      /* 0xa4 */
    u16 flags;                                         /* 0xa8: LetterWriteFlag */
    u8 part;                                           /* 0xaa: LetterWritePart */
    u8 blink;                                          /* 0xab: counts frames; the cursor is drawn while bit 4 is set */
    u8 position;                                       /* 0xac: the cursor's character in its part */
    u8 mark_from;                                      /* 0xad */
    u8 mark_to;                                        /* 0xae */
    u8 cue_scroll;                                     /* 0xaf: the scroll at which the scroll button last cued */
    u8 drag_touch_y;                                   /* 0xb0: the pen's y when the drag began */
    u8 drag_scroll;                                    /* 0xb1: the scroll when the drag began */
    u8 scroll;                                         /* 0xb2 */
    u8 scroll_target;                                  /* 0xb3 */
    u8 return_sub_state;                               /* 0xb4: after LETTER_WRITE_SUB_POINTER_GLIDE */
    u8 unk_b5;                                         /* 0xb5 */
    u8 choice_row;                                     /* 0xb6 */
    u8 choice_page;                                    /* 0xb7 */
    u8 button;                                         /* 0xb8: the panel's button pressed (LetterWrite_PressButton) */
    u8 pad_b9[3];                                      /* 0xb9 */
    Letter *letter;                                    /* 0xbc: the letter written */
    u8 keyboard[0x2308];                               /* 0xc0: overlay 95's keyboard */
    u8 unk_23c8[2][0x24];                              /* 0x23c8: objects of main's (constructor func_020b9cfc) */
    TextLabel labels[2];                               /* 0x2410 */
    u8 unk_24e8[0x1800];                               /* 0x24e8 */
    LetterView view;                                   /* 0x3ce8 */
    PushButton scroll_button;                          /* 0x4010 */
    Glider pointer;                                    /* 0x4058: a Glider0 */
    MailMsgText filter_text;                           /* 0x40bc: the 8-bit text the taboo filter reads */
    LetterBodyText filter_wide;                        /* 0x4150: a text carried through it */
    u16 shown_header[LETTER_WRITE_SHOWN_HEADER_CHARS]; /* 0x41e0: the header as the view shows it */
    u8 unk_4230[0x80];                                 /* 0x4230 */
    u8 choice[0x3e8];                                  /* 0x42b0: a PagedChoice */
    ButtonPanel panel;                                 /* 0x4698 */
    ErrorMessage error;                                /* 0x4864 */
} LetterWriteScene;

LetterWriteScene *LetterWrite_Destroy(LetterWriteScene *self);
LetterWriteScene *LetterWrite_Delete(LetterWriteScene *self);
void LetterWrite_ClearFlags(LetterWriteScene *self, unsigned short mask);
void LetterWrite_SetFlags(LetterWriteScene *self, unsigned short mask);
int LetterWrite_TestFlags(LetterWriteScene *self, unsigned short mask);
void LetterWrite_FilterTaboo(LetterWriteScene *self);
void LetterWrite_FilterTabooText(LetterWriteScene *self, u16 *text, int count);
void LetterWrite_SaveDefaults(LetterWriteScene *self);
void LetterWrite_CloseChoice(LetterWriteScene *self);
void LetterWrite_OpenChoicePage(LetterWriteScene *self, int wipe);
void LetterWrite_GlideToChoiceRow(LetterWriteScene *self);
void LetterWrite_PointerFirstOfSet(LetterWriteScene *self);
void LetterWrite_BeginSub0A(LetterWriteScene *self);
void LetterWrite_BeginSub08(LetterWriteScene *self);
void LetterWrite_PlacePointer(LetterWriteScene *self);
void LetterWrite_GlidePointerTo(LetterWriteScene *self, int x, int y);
void LetterWrite_GlidePointer(LetterWriteScene *self);
void LetterWrite_HidePointer(LetterWriteScene *self);
void LetterWrite_PointAtKey(LetterWriteScene *self);
void LetterWrite_PressButton(LetterWriteScene *self, int index);
void LetterWrite_PlaySound34(LetterWriteScene *self);
void LetterWrite_ScrollToCursor(LetterWriteScene *self);
void LetterWrite_StepScroll(LetterWriteScene *self);
int LetterWrite_IsScrolling(LetterWriteScene *self);
void LetterWrite_ScrollTo(LetterWriteScene *self, unsigned char target);
void LetterWrite_SetScroll(LetterWriteScene *self, int scroll);
void LetterWrite_ScrollByKeys(LetterWriteScene *self);
void LetterWrite_DragScroll(LetterWriteScene *self);
int LetterWrite_StartDrag(LetterWriteScene *self);
void LetterWrite_SetPosition(LetterWriteScene *self, unsigned char position);
unsigned char LetterWrite_HeaderPosition(LetterWriteScene *self);
int LetterWrite_PartCapacity(LetterWriteScene *self);
int LetterWrite_PartTextAddress(LetterWriteScene *self);
u16 *LetterWrite_PartText(LetterWriteScene *self);
int LetterWrite_MoveCursorByKeys(LetterWriteScene *self, int keys, int across_parts);
void LetterWrite_DeleteMarked(LetterWriteScene *self);
void LetterWrite_EndMark(LetterWriteScene *self);
int LetterWrite_HasMark(LetterWriteScene *self);
unsigned short LetterWrite_CharBeforeCursor(LetterWriteScene *self);
void LetterWrite_PlaceCursor(LetterWriteScene *self);
int LetterWrite_PlaceCursorInFooter(LetterWriteScene *self);
void LetterWrite_PlaceCursorInBody(LetterWriteScene *self);
void LetterWrite_PlaceCursorInHeader(LetterWriteScene *self);
void LetterWrite_TouchAt(LetterWriteScene *self, int x, int y, int below_to_footer);
int LetterWrite_DragMark(LetterWriteScene *self);
void LetterWrite_Nothing(LetterWriteScene *self);
int LetterWrite_StartTouch(LetterWriteScene *self);
int LetterWrite_FooterPositionAt(LetterWriteScene *self, s32 *x);
unsigned char LetterWrite_BodyPositionAt(LetterWriteScene *self, int line, s32 *x);
void LetterWrite_EnterFooter(LetterWriteScene *self);
void LetterWrite_EnterBody(LetterWriteScene *self, int below_to_footer);
u8 LetterWrite_HeaderPositionAt(LetterWriteScene *self, int x, u8 *part);
void LetterWrite_EnterHeader(LetterWriteScene *self);
void LetterWrite_Start(LetterWriteScene *self);
void LetterWrite_BeginChoiceKeys(LetterWriteScene *self);
void LetterWrite_BeginChoiceTouch(LetterWriteScene *self);
void LetterWrite_BeginPanelKeys(LetterWriteScene *self);
void LetterWrite_BeginSub04(LetterWriteScene *self);
unsigned char *LetterWrite_BeginInput(LetterWriteScene *self);
unsigned char *LetterWrite_BeginKeys(LetterWriteScene *self);

#endif
