/* The scene of overlay 100 (vtable 0x0229ecb8, include/cpp/ov100/Obj_ov100_0229ecb8.h): a menu
 * scene (ov002/menu_scene.h) built on the same three objects of ov094's as the pockets scenes
 * of overlays 096 and 099 (ov096/pockets_screen.h, ov099/pockets_view.h). Its grid object holds
 * 30 slots here: slots 0-14 are the current player's 15 pocket slots, slots 15-29 a list of 15
 * item codes the scene keeps at `box` (put in the grid by func_ov094_0229ace4). "Box" is only a
 * name for that list: what it stands for in the game is not known.
 *
 * The cursor walks the pockets (3 rows of 5), the box above them (3 rows of 5) and two places
 * to the right of both, which end the scene: PocketsBox_Confirm and PocketsBox_Cancel. Items are
 * picked up from a slot and put down on, or swapped with, another as in ov099's scene; a pocket
 * slot whose item may not move is locked (PocketsBox_LockSlots, drawn so by the grid object).
 *
 * What the box starts as and what is done with it at the end depends on the mode main keeps
 * for group 9's screens (GroupParams_Mode, PocketsBoxMode). Two lists of 15 codes in main's
 * memory, data_021f3a68 (list A) and data_021f3a86 (list B), are also what player messages 3
 * and 4 carry between linked consoles (main/player_messages.h): modes 0x1f and 0x20 start the
 * box from one of them and, at the end, write the box back to it and send it to the others.
 * The scene then waits for the session to reach the message's frame before it leaves
 * (PocketsBox_CanLeave). */
#ifndef CLEAN_OV100_POCKETS_BOX_H
#define CLEAN_OV100_POCKETS_BOX_H

#include "clean.h"
#include "main/text_label.h"
#include "ov002/error_message.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov002/paged_choice.h"
#include "ov002/popup.h"
#include "types.h"

/* In `flags`. */
enum PocketsBoxFlag {
    POCKETS_BOX_FLAG_DRAWN = 0x01,         /* the scene is drawn (func_ov100_0229ea10) */
    POCKETS_BOX_FLAG_OBJECTS_DRAWN = 0x02, /* the grid, the letters and the wallet are drawn */
    POCKETS_BOX_FLAG_TOUCHED_FREE = 0x04,  /* the place touched is not locked (func_ov100_0229d824) */
    POCKETS_BOX_FLAG_SENT = 0x08,          /* the box was sent to the other consoles
                                             * (PocketsBox_SendBox) */
    POCKETS_BOX_FLAG_WRAPPED_LEFT = 0x10,  /* this move wrapped the cursor over the left edge */
    POCKETS_BOX_FLAG_WRAPPED_RIGHT = 0x20, /* this move wrapped it over the right edge */
    POCKETS_BOX_FLAG_HELD_HIDDEN = 0x40,   /* the held item is not drawn */
    POCKETS_BOX_FLAG_80 = 0x80,            /* the grid is drawn at `exit_wipe_y` */
    POCKETS_BOX_FLAG_SPRITE_SET = 0x100,   /* the cursor sprite's set changed; it is updated by
                                             * PocketsBox_GlideToCursor */
    POCKETS_BOX_FLAG_STARTED_EMPTY = 0x200 /* the box started empty (modes 0x1d and 0x1e) */
};

#define POCKETS_BOX_FLAGS_WRAPPED (POCKETS_BOX_FLAG_WRAPPED_LEFT | POCKETS_BOX_FLAG_WRAPPED_RIGHT)

/* The places of the cursor (`cursor`, `target`, ...), which are also the grid object's slots
 * for the first 30. */
enum PocketsBoxPlace {
    POCKETS_BOX_POCKETS_FIRST = 0x00, /* 0-14: the pocket slots, row * 5 + column */
    POCKETS_BOX_POCKETS_LAST = 0x0e,
    POCKETS_BOX_BOX_FIRST = 0x0f, /* 15-29: the box, 15 + row * 5 + column */
    POCKETS_BOX_BOX_LAST = 0x1d,
    POCKETS_BOX_CONFIRM = 0x1e, /* right of the box: PocketsBox_Confirm */
    POCKETS_BOX_CANCEL = 0x1f,  /* below it: PocketsBox_Cancel */
    POCKETS_BOX_NO_PLACE = 0x20
};

/* What is held (`held_kind`). */
enum PocketsBoxHeldKind {
    POCKETS_BOX_HELD_NONE = 0,
    POCKETS_BOX_HELD_ITEM = 1 /* `item` and `held_state` */
};

/* GroupParams_Mode's values this scene is opened in (func_ov100_0229e400 sets the box up). */
enum PocketsBoxMode {
    POCKETS_BOX_MODE_1D = 0x1d, /* the box starts empty; given to Pockets_SetList at the end */
    POCKETS_BOX_MODE_1E = 0x1e, /* the same, with another rule for locked slots */
    POCKETS_BOX_MODE_1F = 0x1f, /* the box starts as list A; every pocket slot is locked, and
                                 * the items taken out go to Pockets_SetList at the end */
    POCKETS_BOX_MODE_20 = 0x20  /* the box starts as list B */
};

#define POCKETS_BOX_COLUMNS 5
#define POCKETS_BOX_ROWS 3
#define POCKETS_BOX_SLOTS 15
#define POCKETS_BOX_LABELS 2

typedef struct PocketsBox {
    MenuScene base;                       /* 0x00 */
    u8 unk_94[0x38];                      /* 0x94: an object of main's (constructor func_020b9af4), updated by
                            * func_020b9ccc */
    u8 grid[0xa60];                       /* 0xcc: ov094's object of the slots (destructor func_ov094_0229afe0) */
    u8 letters[0x28];                     /* 0xb2c: ov094's object of the letters (func_ov094_0229bc30) */
    u8 wallet[0x1638];                    /* 0xb54: ov094's object of the wallet's display (destructor
                            * func_ov094_0229a2d0) */
    Popup popup;                          /* 0x218c */
    Glide glide;                          /* 0x225c: the held item's glide to a place */
    Glider cursor_sprite;                 /* 0x2274: a Glider0 */
    u8 choice[0x3e8];                     /* 0x22d8: a PagedChoice */
    ChoiceEntries entries;                /* 0x26c0 */
    u8 pad_26cb;                          /* 0x26cb */
    ErrorMessage error;                   /* 0x26cc */
    TextLabel labels[POCKETS_BOX_LABELS]; /* 0x27e8: the closing labels (PocketsBox_NextLabel) */
    u32 flags;                            /* 0x28c0: PocketsBoxFlag */
    s32 wipe_y;                           /* 0x28c4: func_ov002_02207f60's, where the objects are drawn */
    s32 exit_wipe_y;                      /* 0x28c8: func_ov002_02207f60's when the scene closes */
    s32 grab_dx;                          /* 0x28cc: from the touch to the held item */
    s32 grab_dy;                          /* 0x28d0 */
    s32 held_x;                           /* 0x28d4: where the held item is drawn */
    s32 held_y;                           /* 0x28d8 */
    u16 box[POCKETS_BOX_SLOTS];           /* 0x28dc: the box's item codes */
    u16 box_start[POCKETS_BOX_SLOTS];     /* 0x28fa: the box as the scene started */
    u16 item;                             /* 0x2918: the held item's code */
    s16 sent_frame;                       /* 0x291a: the session's frame the box was sent in */
    u8 held_state;                        /* 0x291c: the held item's state (the grid's func_ov094_0229aa84) */
    u8 held_kind;                         /* 0x291d: PocketsBoxHeldKind */
    u8 touch_place;                       /* 0x291e: the place touched (func_ov100_0229d824) */
    u8 popup_place;                       /* 0x291f: the place the popup tells of */
    u8 held_place;                        /* 0x2920: the place the held item came from */
    u8 cursor;                            /* 0x2921: PocketsBoxPlace */
    u8 unk_2922;                          /* 0x2922 */
    u8 target;                            /* 0x2923: the place the held item is put down on or swapped at */
    u8 return_state;                      /* 0x2924: the sub state to go back to */
    u8 action;                            /* 0x2925: the value of the choice row picked */
    u8 choice_row;                        /* 0x2926: the choice row the cursor sprite points at */
    u8 label_count;                       /* 0x2927: the labels in use */
    u8 close_delay;                       /* 0x2928: frames before the closed scene leaves (func_ov100_0229d928) */
    u8 pad_2929[3];
} PocketsBox;

static_assert(offsetof(PocketsBox, grid) == 0xcc && offsetof(PocketsBox, wallet) == 0xb54, "ov094 objects");
static_assert(offsetof(PocketsBox, popup) == 0x218c && offsetof(PocketsBox, cursor_sprite) == 0x2274, "sprites");
static_assert(offsetof(PocketsBox, entries) == 0x26c0 && offsetof(PocketsBox, error) == 0x26cc, "choice");
static_assert(offsetof(PocketsBox, labels) == 0x27e8 && offsetof(PocketsBox, flags) == 0x28c0, "labels");
static_assert(offsetof(PocketsBox, box) == 0x28dc && offsetof(PocketsBox, item) == 0x2918, "lists");
static_assert(offsetof(PocketsBox, cursor) == 0x2921 && offsetof(PocketsBox, close_delay) == 0x2928, "bytes");
static_assert(sizeof(PocketsBox) == 0x292c, "size (func_ov100_0229eaec)");

PocketsBox *PocketsBox_Destroy(PocketsBox *self);
PocketsBox *PocketsBox_Delete(PocketsBox *self);
void PocketsBox_ClearFlags(PocketsBox *self, unsigned int flags);
void PocketsBox_SetFlags(PocketsBox *self, unsigned int flags);
int PocketsBox_TestFlags(PocketsBox *self, unsigned int flags);
int PocketsBox_CanLeave(PocketsBox *self);
void PocketsBox_SendBox(PocketsBox *self, int type);
int PocketsBox_Compact(PocketsBox *self, u16 *items);
void PocketsBox_Confirm(PocketsBox *self);
void PocketsBox_Cancel(PocketsBox *self);
void PocketsBox_ShowCancelLabel(PocketsBox *self, int lit);
void PocketsBox_ShowConfirmLabel(PocketsBox *self, int lit);
TextLabel *PocketsBox_NextLabel(PocketsBox *self);
void PocketsBox_CloseLabels(PocketsBox *self);
int PocketsBox_MoveCursor(PocketsBox *self, int keys, int wrap_in_row);
void PocketsBox_MoveCursorAtButtons(PocketsBox *self, int keys);
void PocketsBox_MoveCursorInBox(PocketsBox *self, int keys, int wrap_in_row);
void PocketsBox_MoveCursorInPockets(PocketsBox *self, int keys, int wrap_in_row);
void PocketsBox_CancelChoice(PocketsBox *self);
void PocketsBox_RunAction(PocketsBox *self);
void PocketsBox_StartSwap(PocketsBox *self, u8 place);
void PocketsBox_StartPutDown(PocketsBox *self, u8 place);
void PocketsBox_StartPickUp(PocketsBox *self);
void PocketsBox_BeginSubState10(PocketsBox *self);
void PocketsBox_BeginSubState9(PocketsBox *self);
void PocketsBox_ShowCursorFirstOfSet(PocketsBox *self);
void PocketsBox_PlaceCursorSprite(PocketsBox *self);
void PocketsBox_PointAtFirstRow(PocketsBox *self);
void PocketsBox_PointAtLastRow(PocketsBox *self);
void PocketsBox_GlideToRow(PocketsBox *self);
void PocketsBox_GlideToCursor(PocketsBox *self);
void PocketsBox_HideCursorSprite(PocketsBox *self);
int PocketsBox_CursorSpriteY(PocketsBox *self);
int PocketsBox_CursorSpriteX(PocketsBox *self);
void PocketsBox_ShowCursorSprite(PocketsBox *self);
void PocketsBox_SwapHeldWith(PocketsBox *self, int place);
void PocketsBox_PutHeldAt(PocketsBox *self, int place);
void PocketsBox_PickUpItem(PocketsBox *self, int place);
void PocketsBox_FollowGlide(PocketsBox *self);
void PocketsBox_FollowCursorSprite(PocketsBox *self);
void PocketsBox_FollowTouch(PocketsBox *self);
void PocketsBox_DrawHeld(PocketsBox *self);
void PocketsBox_UpdatePopup(PocketsBox *self);
void PocketsBox_PlacePopup(PocketsBox *self);
int PocketsBox_TouchMoved(PocketsBox *self);
void PocketsBox_HighlightPlace(PocketsBox *self, int place);
void PocketsBox_ClearHighlights(PocketsBox *self);
void PocketsBox_SelectPlace(PocketsBox *self, int place);
void PocketsBox_ClearSelection(PocketsBox *self);
int PocketsBox_PlaceItemState(PocketsBox *self, int place);
int PocketsBox_PlaceItem(PocketsBox *self, int place);
int PocketsBox_PlaceIsEmpty(PocketsBox *self, int place);
int PocketsBox_PlaceIsLocked(PocketsBox *self, int place);
void PocketsBox_LockSlots(PocketsBox *self);
int PocketsBox_SlotMustLock(PocketsBox *self, int place);
int PocketsBox_PlaceY(PocketsBox *self, int place);
int PocketsBox_PlaceX(PocketsBox *self, int place);
int PocketsBox_BoxPlaceOfSlot(PocketsBox *self, unsigned int slot);
int PocketsBox_BoxSlot(PocketsBox *self, int place);
void PocketsBox_SetSlotItem(PocketsBox *self, int place, int item, int state);

#endif
