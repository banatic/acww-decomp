/* The scene of overlay 104 (vtable 0x0229f6d0, include/cpp/ov104/Obj_ov104_0229f6d0.h; constructor
 * func_ov104_0229f460, 0x4380 bytes): the post office's screen for posting letters. It is the
 * screen of group 9's mode 0x25 (GroupParams_OpenLetter, main/group_params.h), which the post
 * office clerk's overlay (54, the pelicans' models) opens and whose result flags it reads back.
 * As the evidence says:
 *
 * - it is a menu scene (ov002/menu_scene.h) built on the three objects of ov094's the pockets
 *   scenes use: the grid at 0x2f8, the letters at 0xd58 (whose places 0-9 are the carried letters
 *   and 0x2d-0x36 the ten at `outbox`) and the wallet at 0xd80; its background is
 *   "menu/inventory/b_itm_bg_ltr2.bsc" with the post office's characters and palette, as the
 *   mailbox scene of overlay 106 (ov106/mailbox_scene.h) uses;
 * - the cursor walks the carried letters (2 columns of 5), the letters to post (`outbox`, 2
 *   columns of 5) and one place below each (LetterSendPlace); letters are picked up, held and
 *   put down as in overlay 106;
 * - its setup (func_ov104_0229eaa8) empties `outbox` and copies the carried letters into
 *   `carried_copy` (LetterSend_SaveCarried); cancelling (panel button 7, LetterSend_Cancel)
 *   puts that copy back (LetterSend_RestoreCarried);
 * - posting (panel button 9, LetterSend_Post) hands the letters of `outbox` on: to the post
 *   office (Mail_HoldAtPostOffice), straight to a villager (Mail_GiveToVillager) or a mailbox of
 *   the town (Mail_PutInMailbox), or, when consoles are linked and this one is not the host,
 *   one by one to the host as message 8 (LetterSend_SendToHost, answered with 9-11, see
 *   main/player_messages.h). What happened is gathered in `result` (LetterSendResult), which
 *   the scene's end stores as the letter screen's result flags (GroupParams_SetLetterFlags);
 *   letters not posted go back to the carried ones (LetterSend_ReturnUnsent). */
#ifndef CLEAN_OV104_LETTER_SEND_H
#define CLEAN_OV104_LETTER_SEND_H

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
enum LetterSendFlag {
    LETTER_SEND_FLAG_SHOWN = 0x1,             /* set by the setup; the draw does nothing without it */
    LETTER_SEND_FLAG_SCROLLED = 0x2,          /* set by the setup; the draw places the objects by unk_98 */
    LETTER_SEND_FLAG_JUMP = 0x8,              /* the cursor sprite jumps to the cursor instead of easing
                                               * (LetterSend_GlideToCursor), once */
    LETTER_SEND_FLAG_WRAPPED_LEFT = 0x10,     /* the cursor sprite's x is a screen width (256) less */
    LETTER_SEND_FLAG_WRAPPED_RIGHT = 0x20,    /* the cursor sprite's x is a screen width more */
    LETTER_SEND_FLAG_HELD_HIDDEN = 0x40,      /* the held letter is not drawn (LetterSend_DrawHeld) */
    LETTER_SEND_FLAG_ACTION_1 = 0x100,        /* set by action 1, cleared by posting and cancelling */
    LETTER_SEND_FLAG_CANCELLED = 0x400,       /* the scene ends without posting (LetterSend_Cancel) */
    LETTER_SEND_FLAG_LINKED = 0x800,          /* posting with consoles linked (LetterSend_BeginLinkedPost) */
    LETTER_SEND_FLAG_SENDING = 0x1000,        /* letters are being sent to the host, one a frame at most */
    LETTER_SEND_FLAG_AWAITING_REPLY = 0x2000, /* a letter was sent; the host's reply is awaited */
    LETTER_SEND_FLAG_HOST = 0x4000,           /* this console is the host: the letters were posted here */
    LETTER_SEND_FLAG_FIXED_MENU = 0x8000      /* the choice is LetterSend_OpenFixedMenu's: its first row is
                                               * set apart */
};

#define LETTER_SEND_FLAGS_WRAPPED (LETTER_SEND_FLAG_WRAPPED_LEFT | LETTER_SEND_FLAG_WRAPPED_RIGHT)

/* The result flags (`result`, and what the post functions return), as the letter screen's result
 * flags of main/group_params.c read them. */
enum LetterSendResult {
    LETTER_SEND_RESULT_ONE_TO_SELF = 0x001,      /* one letter to the player themself: it is kept as
                                                   * the letter screen's letter (GroupParams_SetLetter) */
    LETTER_SEND_RESULT_SEVERAL_TO_SELF = 0x002,  /* more than one letter to the player themself */
    LETTER_SEND_RESULT_NOTHING = 0x004,          /* no letter to post */
    LETTER_SEND_RESULT_NO_ADDRESSEE = 0x008,     /* a written letter has no addressee */
    LETTER_SEND_RESULT_POST_OFFICE_FULL = 0x010, /* the post office had no room for a letter */
    LETTER_SEND_RESULT_STILL_FULL = 0x020,       /* nor on the second try (LetterSend_RetryHold) */
    LETTER_SEND_RESULT_FULL_MAILBOXES = 0x0c0,   /* bits 6-7: how many players' mailboxes were full */
    LETTER_SEND_RESULT_WRITTEN = 0x100,          /* a written letter to someone else was handled */
    LETTER_SEND_RESULT_POSTED = 0x200,           /* a letter was posted or handed on */
    LETTER_SEND_RESULT_NOT_ALL_SENT = 0x400,     /* the host took no more letters, or posting stopped */
    LETTER_SEND_RESULT_TO_SELF_LINKED = 0x800    /* linked: a written letter is to the player themself */
};

#define LETTER_SEND_FULL_MAILBOXES_SHIFT 6

/* The places of the cursor (`cursor`, `slot`, ...). The letters object knows the carried letters
 * as its places 0-9 and the letters to post as its places 0x2d-0x36 (func_ov104_0229da38). */
enum LetterSendPlace {
    LETTER_SEND_CARRIED_FIRST = 0x0b, /* 0x0b-0x14: the carried letters, 0x0b + row * 2 + column */
    LETTER_SEND_CARRIED_LAST = 0x14,
    LETTER_SEND_OUTBOX_FIRST = 0x15, /* 0x15-0x1e: the letters to post, 0x15 + row * 2 + column */
    LETTER_SEND_OUTBOX_LAST = 0x1e,
    LETTER_SEND_BELOW_CARRIED = 0x1f, /* below the carried letters (at 0xbc, 0xb6) */
    LETTER_SEND_BELOW_OUTBOX = 0x20,  /* below the letters to post (at 0x74, 0xb6) */
    LETTER_SEND_NO_PLACE = 0x21
};

#define LETTER_SEND_COLUMNS 2
#define LETTER_SEND_ROWS 5
#define LETTER_SEND_LETTERS 10

/* What the scene holds (`held_kind`). */
enum LetterSendHeldKind {
    LETTER_SEND_HELD_NONE = 0,
    LETTER_SEND_HELD_LETTER = 1 /* a copy of the letter is at `held` */
};

/* The values of the choice rows (`action`), run by LetterSend_RunAction. */
enum LetterSendAction {
    LETTER_SEND_ACTION_0 = 0,       /* LetterSend_RunAction0 */
    LETTER_SEND_ACTION_1 = 1,       /* LetterSend_RunAction1 */
    LETTER_SEND_ACTION_PICK_UP = 2, /* LetterSend_PickUpSlotLetter */
    LETTER_SEND_ACTION_MENU = 3,    /* LetterSend_RunActionMenu */
    LETTER_SEND_ACTION_CANCEL = 4   /* func_ov104_0229dd00 */
};

typedef struct LetterSendScene {
    MenuScene base;                           /* 0x00 */
    u32 flags;                                /* 0x94: LetterSendFlag */
    s32 unk_98;                               /* 0x98: an offset the draw places the objects by */
    s32 unk_9c;                               /* 0x9c */
    s32 grab_dx;                              /* 0xa0: from the touch to the held letter */
    s32 grab_dy;                              /* 0xa4 */
    s32 held_x;                               /* 0xa8: where the held letter is drawn */
    s32 held_y;                               /* 0xac */
    u16 result;                               /* 0xb0: LetterSendResult */
    u16 posted;                               /* 0xb2: bit n: outbox[n] was taken (by the host) */
    u8 held_kind;                             /* 0xb4: LetterSendHeldKind */
    u8 unk_b5;                                /* 0xb5 */
    u8 popup_place;                           /* 0xb6: the place the popup tells of */
    u8 unk_b7;                                /* 0xb7 */
    u8 cursor;                                /* 0xb8: LetterSendPlace */
    u8 slot;                                  /* 0xb9: the place whose choice is open */
    u8 target;                                /* 0xba: the place the held letter is put down on or swapped at */
    u8 return_state;                          /* 0xbb: the sub state to go back to */
    u8 action;                                /* 0xbc: LetterSendAction */
    u8 choice_row;                            /* 0xbd: the choice row the cursor sprite points at */
    u8 next_to_send;                          /* 0xbe: the outbox letter to send to the host next */
    u8 unk_bf;                                /* 0xbf */
    Letter held;                              /* 0xc0: the held letter's copy */
    Letter swapped;                           /* 0x1c0: the letter a swap took from its place */
    u8 unk_2c0[0x38];                         /* 0x2c0: an object of main's (constructor func_020b9af4) */
    PocketsGrid grid;                         /* 0x2f8 */
    PocketsLetters letters;                   /* 0xd58 */
    PocketsWallet wallet;                     /* 0xd80 */
    Popup popup;                              /* 0x23b8 */
    Glide glide;                              /* 0x2488: the held letter's glide to a place */
    Glider cursor_sprite;                     /* 0x24a0: a Glider0 */
    u8 choice[0x3e8];                         /* 0x2504: a PagedChoice (whose structure is not all known) */
    ChoiceEntries entries;                    /* 0x28ec */
    u8 pad_28f7;                              /* 0x28f7 */
    ErrorMessage error;                       /* 0x28f8 */
    LetterView view;                          /* 0x2a14: shows a letter */
    LabelButton button;                       /* 0x2d3c: a LabelButton0 */
    Letter outbox[LETTER_SEND_LETTERS];       /* 0x2db4: the letters to post */
    Letter carried_copy[LETTER_SEND_LETTERS]; /* 0x37b4: the carried letters as the scene began */
    ButtonPanel panel;                        /* 0x41b4 */
} LetterSendScene;

LetterSendScene *LetterSend_Destroy(LetterSendScene *self);
LetterSendScene *LetterSend_Delete(LetterSendScene *self);
void LetterSend_ClearFlags(LetterSendScene *self, unsigned int flags);
void LetterSend_SetFlags(LetterSendScene *self, unsigned int flags);
int LetterSend_TestFlags(LetterSendScene *self, int flags);
int LetterSend_SendToHost(LetterSendScene *self, const Letter *letter);
void LetterSend_ContinueLinkedPost(LetterSendScene *self);
void LetterSend_BeginLinkedPost(LetterSendScene *self);
int LetterSend_GiveToVillagers(LetterSendScene *self, Letter *letters);
u16 LetterSend_DeliverDirectly(LetterSendScene *self, Letter *letters);
int LetterSend_HoldAtPostOffice(LetterSendScene *self, Letter *letter);
u16 LetterSend_RetryHold(LetterSendScene *self, Letter *letters);
u16 LetterSend_PostAll(LetterSendScene *self, Letter *letters, int mark_only);
u16 LetterSend_TakeLetterToSelf(LetterSendScene *self, Letter *letters);
int LetterSend_HasLetterToSelf(LetterSendScene *self, const Letter *letters);
void LetterSend_Cancel(LetterSendScene *self);
void LetterSend_Post(LetterSendScene *self);
void LetterSend_ReturnUnsent(LetterSendScene *self, int drop_posted);
void LetterSend_RestoreCarried(LetterSendScene *self);
void LetterSend_SaveCarried(LetterSendScene *self);
void LetterSend_RunActionMenu(LetterSendScene *self);
void LetterSend_PickUpSlotLetter(LetterSendScene *self);
void LetterSend_PressLabelButton(LetterSendScene *self);
void LetterSend_RunAction1(LetterSendScene *self);
int LetterSend_MoveCursor(LetterSendScene *self, int keys, int mode);
void LetterSend_MoveCursorBelow(LetterSendScene *self, int keys);
void LetterSend_MoveCursorInOutbox(LetterSendScene *self, int keys, int mode);
void LetterSend_MoveCursorInCarried(LetterSendScene *self, int keys, int mode);
void LetterSend_OpenFixedMenu(LetterSendScene *self);
void LetterSend_OpenLetterMenu(LetterSendScene *self, int place, int above_popup);
void LetterSend_CancelChoice(LetterSendScene *self);
void LetterSend_ShowChoice(LetterSendScene *self, int above_popup);
void LetterSend_RunAction(LetterSendScene *self);
void LetterSend_BeginSubState13(LetterSendScene *self, u8 target);
void LetterSend_BeginSubState12(LetterSendScene *self, u8 target);
void LetterSend_RunAction0(LetterSendScene *self);
void LetterSend_BeginSubState0e(LetterSendScene *self);
void LetterSend_ShowCursorFirstOfSet(LetterSendScene *self);
void LetterSend_PlaceCursorSprite(LetterSendScene *self);
void LetterSend_PointAtDefaultRow(LetterSendScene *self);
void LetterSend_PointAtLastRow(LetterSendScene *self);
void LetterSend_GlideToRow(LetterSendScene *self);
void LetterSend_GlideToCursor(LetterSendScene *self);
void LetterSend_HideCursorSprite(LetterSendScene *self);
int LetterSend_CursorSpriteY(LetterSendScene *self);
int LetterSend_CursorSpriteX(LetterSendScene *self);
void LetterSend_ShowCursorAtCursor(LetterSendScene *self);
void LetterSend_SwapHeldWith(LetterSendScene *self, int place);
void LetterSend_PutHeldAt(LetterSendScene *self, int place);
void LetterSend_PickUpLetter(LetterSendScene *self, int place);
void LetterSend_FollowGlide(LetterSendScene *self);
void LetterSend_FollowCursorSprite(LetterSendScene *self);
void LetterSend_FollowTouch(LetterSendScene *self);
void LetterSend_DrawHeld(LetterSendScene *self);
void LetterSend_UpdatePopup(LetterSendScene *self);
void LetterSend_PlacePopup(LetterSendScene *self);
int LetterSend_TouchMoved(LetterSendScene *self);
void LetterSend_HighlightPlace(LetterSendScene *self, int place);
void LetterSend_ClearHighlights(LetterSendScene *self);
void LetterSend_SelectPlace(LetterSendScene *self, int place);

#endif
