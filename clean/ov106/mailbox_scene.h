/* The scene of overlay 106 (vtable 0x0229f6e0, include/cpp/ov106/Obj_ov106_0229f6e0.h; constructor
 * func_ov106_0229f41c, 0x4380 bytes): a menu scene (ov002/menu_scene.h) that shows the ten letters
 * of the current player's mailbox (main/mail.h) beside the ten letters they carry, as the evidence
 * says:
 *
 * - its setup (func_ov106_0229ea08) copies the ten letters of PlayerRecord_Mailbox for the
 *   current player into `mailbox`, and its end (func_ov106_0229eed0) compacts them (Mail_Compact)
 *   and copies them back;
 * - its background is "menu/inventory/b_itm_bg_ltr2.bsc" with the post office's characters and
 *   palette ("menu/inventory/b_itm_post.bch", "...post.bpl"), as overlay 105's letter storage
 *   (ov105/letter_storage.h) uses;
 * - it is built on three of the objects of ov094's that the pockets scenes of overlays 096-105
 *   use: the grid at 0xf8, the letters at 0xb58 (whose places 0-9 are the carried letters and
 *   0x23-0x2c the mailbox's, PocketsLetters_SetTenAt23) and the wallet at 0xb80.
 *
 * The cursor walks the carried letters (2 columns of 5), the mailbox's letters (2 columns of 5)
 * and one more place below both (MailboxScenePlace). Picking a letter opens a choice
 * (ov002/paged_choice.h) whose rows carry an action (`action`, MailboxScene_RunAction); a letter
 * can be picked up, held (`held`) and put down on or swapped with another place's. A letter put
 * among the carried ones that is in state 2 or 3 has its paper recorded in the player's item
 * record (MailboxScene_RecordPaper). */
#ifndef CLEAN_OV106_MAILBOX_SCENE_H
#define CLEAN_OV106_MAILBOX_SCENE_H

#include "main/letter.h"
#include "main/letter_view.h"
#include "ov002/button_panel.h"
#include "ov002/error_message.h"
#include "ov002/glide.h"
#include "ov002/label_button.h"
#include "ov002/menu_scene.h"
#include "ov002/paged_choice.h"
#include "ov002/popup.h"
#include "ov094/pockets_grid.h"
#include "ov094/pockets_letters.h"
#include "ov094/pockets_wallet.h"
#include "types.h"

/* In `flags`. */
enum MailboxSceneFlag {
    MAILBOX_SCENE_FLAG_08 = 0x08,            /* the cursor sprite jumps to the cursor instead of easing
                                                * (MailboxScene_GlideToCursor), once */
    MAILBOX_SCENE_FLAG_WRAPPED_LEFT = 0x10,  /* this move wrapped the cursor from the mailbox's left
                                                * column to the carried letters */
    MAILBOX_SCENE_FLAG_WRAPPED_RIGHT = 0x20, /* this move wrapped it from the carried letters' right
                                                * column to the mailbox */
    MAILBOX_SCENE_FLAG_HELD_HIDDEN = 0x40,   /* the held letter is not drawn (MailboxScene_DrawHeld) */
    MAILBOX_SCENE_FLAG_100 = 0x100,          /* set by action 1 (MailboxScene_RunAction1) */
    MAILBOX_SCENE_FLAG_4000 = 0x4000,        /* set by the setup */
    MAILBOX_SCENE_FLAG_CLOSING = 0x8000,     /* the scene was asked to close (MailboxScene_CloseOnRequest) */
    MAILBOX_SCENE_FLAG_FIXED_MENU = 0x10000  /* the choice is MailboxScene_OpenFixedMenu's: its first
                                                * row is set apart */
};

#define MAILBOX_SCENE_FLAGS_WRAPPED (MAILBOX_SCENE_FLAG_WRAPPED_LEFT | MAILBOX_SCENE_FLAG_WRAPPED_RIGHT)

/* The places of the cursor (`cursor`, `slot`, ...). The letters object of ov094's knows the
 * carried letters as its places 0-9 and the mailbox's as its places 0x23-0x2c
 * (func_ov106_0229d360, func_ov106_0229d340). */
enum MailboxScenePlace {
    MAILBOX_SCENE_CARRIED_FIRST = 0x0b, /* 0x0b-0x14: the carried letters, 0x0b + row * 2 + column */
    MAILBOX_SCENE_CARRIED_LAST = 0x14,
    MAILBOX_SCENE_MAILBOX_FIRST = 0x15, /* 0x15-0x1e: the mailbox's letters, 0x15 + row * 2 + column */
    MAILBOX_SCENE_MAILBOX_LAST = 0x1e,
    MAILBOX_SCENE_BELOW = 0x1f,   /* below the carried letters and the mailbox's (at 0xbc, 0xb6) */
    MAILBOX_SCENE_NO_PLACE = 0x20 /* `popup_place` before any (the setup) */
};

#define MAILBOX_SCENE_COLUMNS 2
#define MAILBOX_SCENE_ROWS 5
#define MAILBOX_SCENE_LETTERS 10

/* What the scene holds (`held_kind`). */
enum MailboxSceneHeldKind {
    MAILBOX_SCENE_HELD_NONE = 0,
    MAILBOX_SCENE_HELD_LETTER = 1 /* a copy of the letter is at `held` */
};

/* The values of the choice rows (`action`), run by MailboxScene_RunAction. */
enum MailboxSceneAction {
    MAILBOX_SCENE_ACTION_0 = 0,       /* MailboxScene_RunAction0 */
    MAILBOX_SCENE_ACTION_1 = 1,       /* MailboxScene_RunAction1 */
    MAILBOX_SCENE_ACTION_PICK_UP = 2, /* MailboxScene_PickUpSlotLetter */
    MAILBOX_SCENE_ACTION_MENU = 3,    /* MailboxScene_OpenFixedMenu */
    MAILBOX_SCENE_ACTION_CANCEL = 4   /* func_ov106_0229d73c */
};

typedef struct MailboxScene {
    MenuScene base;                         /* 0x00 */
    u32 flags;                              /* 0x94: MailboxSceneFlag */
    s32 unk_98;                             /* 0x98 */
    s32 unk_9c;                             /* 0x9c */
    s32 unk_a0;                             /* 0xa0 */
    s32 grab_dx;                            /* 0xa4: from the touch to the held letter */
    s32 grab_dy;                            /* 0xa8 */
    s32 held_x;                             /* 0xac: where the held letter is drawn */
    s32 held_y;                             /* 0xb0 */
    u8 held_kind;                           /* 0xb4: MailboxSceneHeldKind */
    u8 unk_b5;                              /* 0xb5 */
    u8 popup_place;                         /* 0xb6: the place the popup tells of */
    u8 held_from;                           /* 0xb7: the place the held letter was taken from */
    u8 cursor;                              /* 0xb8: MailboxScenePlace */
    u8 slot;                                /* 0xb9: the place whose choice is open */
    u8 target;                              /* 0xba: the place the held letter is put down on or swapped at */
    u8 return_state;                        /* 0xbb: the sub state to go back to */
    u8 action;                              /* 0xbc: MailboxSceneAction */
    u8 choice_row;                          /* 0xbd: the choice row the cursor sprite points at */
    u8 unk_be;                              /* 0xbe */
    u8 unk_bf;                              /* 0xbf */
    u8 unk_c0[0x38];                        /* 0xc0: an object of main's (constructor func_020b9af4) */
    PocketsGrid grid;                       /* 0xf8 */
    PocketsLetters letters;                 /* 0xb58 */
    PocketsWallet wallet;                   /* 0xb80 */
    Popup popup;                            /* 0x21b8 */
    Glide glide;                            /* 0x2288: the held letter's glide to a place */
    Glider cursor_sprite;                   /* 0x22a0: a Glider0 */
    u8 choice[0x3e8];                       /* 0x2304: a PagedChoice (whose structure is not all known) */
    ChoiceEntries entries;                  /* 0x26ec */
    u8 pad_26f7;                            /* 0x26f7 */
    ErrorMessage error;                     /* 0x26f8 */
    LetterView view;                        /* 0x2814: shows a letter */
    LabelButton button;                     /* 0x2b3c: a LabelButton0 */
    Letter mailbox[MAILBOX_SCENE_LETTERS];  /* 0x2bb4: the mailbox's letters */
    Letter unk_35b4[MAILBOX_SCENE_LETTERS]; /* 0x35b4: only constructed and destructed */
    ButtonPanel panel;                      /* 0x3fb4 */
    Letter held;                            /* 0x4180: the held letter's copy */
    Letter swapped;                         /* 0x4280: the letter a swap took from its place */
} MailboxScene;

MailboxScene *MailboxScene_Destroy(MailboxScene *self);
MailboxScene *MailboxScene_Delete(MailboxScene *self);
void MailboxScene_ClearFlags(MailboxScene *self, unsigned int flags);
void MailboxScene_SetFlags(MailboxScene *self, unsigned int flags);
int MailboxScene_TestFlags(MailboxScene *self, int flags);
void MailboxScene_PressPanelButton9(MailboxScene *self);
void MailboxScene_RunActionMenu(MailboxScene *self);
void MailboxScene_PickUpSlotLetter(MailboxScene *self);
void MailboxScene_CloseOnRequest(MailboxScene *self);
void MailboxScene_PressLabelButton(MailboxScene *self);
void MailboxScene_RunAction1(MailboxScene *self);
int MailboxScene_MoveCursor(MailboxScene *self, int keys, int mode);
void MailboxScene_MoveCursorBelow(MailboxScene *self, int keys);
void MailboxScene_MoveCursorInMailbox(MailboxScene *self, int keys, int mode);
void MailboxScene_MoveCursorInCarried(MailboxScene *self, int keys, int mode);
void MailboxScene_OpenFixedMenu(MailboxScene *self);
void MailboxScene_OpenLetterMenu(MailboxScene *self, int place, int above_popup);
void MailboxScene_CancelChoice(MailboxScene *self);
void MailboxScene_ShowChoice(MailboxScene *self, int above_popup);
void MailboxScene_RunAction(MailboxScene *self);
void MailboxScene_BeginSubState13(MailboxScene *self, u8 target);
void MailboxScene_BeginSubState12(MailboxScene *self, u8 target);
void MailboxScene_RunAction0(MailboxScene *self);
void MailboxScene_BeginSubState0f(MailboxScene *self);
void MailboxScene_BeginSubState0e(MailboxScene *self);
void MailboxScene_ShowCursorFirstOfSet(MailboxScene *self);
void MailboxScene_PlaceCursorSprite(MailboxScene *self);
void MailboxScene_PointAtDefaultRow(MailboxScene *self);
int MailboxScene_PointAtLastRow(MailboxScene *self);
void MailboxScene_GlideToRow(MailboxScene *self);
void MailboxScene_EaseCursorSpriteTo(MailboxScene *self, int x, int y);
void MailboxScene_GlideToCursor(MailboxScene *self);
void MailboxScene_HideCursorSprite(MailboxScene *self);
int MailboxScene_CursorSpriteY(MailboxScene *self);
int MailboxScene_CursorSpriteX(MailboxScene *self);
void MailboxScene_ShowCursorAtCursor(MailboxScene *self);
void MailboxScene_SwapHeldWith(MailboxScene *self, int place);
void MailboxScene_PutHeldAt(MailboxScene *self, int place);
void MailboxScene_PickUpLetter(MailboxScene *self, int place);
void MailboxScene_FollowGlide(MailboxScene *self);
void MailboxScene_FollowCursorSprite(MailboxScene *self);
void MailboxScene_FollowTouch(MailboxScene *self);
void MailboxScene_DrawHeld(MailboxScene *self);
void MailboxScene_UpdatePopup(MailboxScene *self);
void MailboxScene_PlacePopup(MailboxScene *self);
int MailboxScene_TouchMoved(MailboxScene *self);
void MailboxScene_HighlightPlace(MailboxScene *self, int place);
void MailboxScene_ClearHighlights(MailboxScene *self);
void MailboxScene_SelectPlace(MailboxScene *self, int place);
void MailboxScene_ClearSelection(MailboxScene *self);
int MailboxScene_PlaceIsEmpty(MailboxScene *self, int place);
int MailboxScene_PlaceIsDimmed(MailboxScene *self, int place);
void MailboxScene_DimCarriedLetters(MailboxScene *self);
int MailboxScene_PlaceY(MailboxScene *self, int place);
int MailboxScene_PlaceX(MailboxScene *self, int place);
void MailboxScene_RecordPaper(MailboxScene *self, Letter *letter);
Letter *MailboxScene_PlaceLetter(MailboxScene *self, int place);
void MailboxScene_PutLetterAt(MailboxScene *self, int place, Letter *letter);
int MailboxScene_PutHeldLetterAt(MailboxScene *self, int place);
int MailboxScene_LetterPlaceAtTouch(MailboxScene *self, int x, int y, int with_letter);

#endif
