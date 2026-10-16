/* The scene of overlay 099 (vtable 0x0229e040, include/cpp/ov099/Obj_ov099_0229e040.h): a menu
 * scene (ov002/menu_scene.h) built on the same three objects of ov094's as ov096's pockets
 * scene (ov096/pockets_screen.h), set up the same way (func_ov099_0229d994 and ov096's
 * func_ov096_022a1488 both give them 2, 2 and 6): a grid of 15 places in 3 rows of 5 (the
 * current player's pocket slots), a list of 10 letters in 2 columns of 5 and the wallet's
 * display. Unlike ov096's it has no tab bar and no places beside the grid: the cursor walks the
 * grid only, wrapping over the left and right edges.
 *
 * What it does with them, as the evidence says: the popup tells of the place under the cursor
 * (or the touch); picking a place of the grid opens a choice (ov002/paged_choice.h) of three
 * rows, the first (only when state flag 2 is set, func_0206fe54) leading to a pick-up of the
 * slot's item. A held item moves with the cursor or the stylus and is put down on an empty
 * slot or swapped with the item of a taken one; putting it down writes the pocket slot back
 * through the grid's object (func_ov094_0229aa14, func_0209a088).
 *
 * Its setup (func_ov099_0229d994, not here) also puts item 0x11a9 in pocket slot 0 and item
 * 0x1548 in slot 2. Which part of the game opens the scene is not known; the name says only
 * what it shows. */
#ifndef CLEAN_OV099_POCKETS_VIEW_H
#define CLEAN_OV099_POCKETS_VIEW_H

#include "clean.h"
#include "ov002/error_message.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov002/paged_choice.h"
#include "ov002/popup.h"
#include "types.h"

/* In `flags`. */
enum PocketsViewFlag {
    POCKETS_VIEW_FLAG_DRAWN = 0x01,         /* the scene is drawn (func_ov099_0229ddec) */
    POCKETS_VIEW_FLAG_OBJECTS_DRAWN = 0x02, /* the grid, the letters and the wallet are drawn */
    POCKETS_VIEW_FLAG_04 = 0x04,            /* set by func_ov099_0229d050 for a touched place of the
                                             * grid its object does not call taken */
    POCKETS_VIEW_FLAG_08 = 0x08,            /* the cursor sprite jumps instead of easing
                                             * (PocketsView_GlideToCursor); never set here */
    POCKETS_VIEW_FLAG_WRAPPED_LEFT = 0x10,  /* this move wrapped the cursor over the left edge */
    POCKETS_VIEW_FLAG_WRAPPED_RIGHT = 0x20, /* this move wrapped it over the right edge */
    POCKETS_VIEW_FLAG_HELD_HIDDEN = 0x40    /* the held item is not drawn */
};

#define POCKETS_VIEW_FLAGS_WRAPPED (POCKETS_VIEW_FLAG_WRAPPED_LEFT | POCKETS_VIEW_FLAG_WRAPPED_RIGHT)

/* The places of the cursor (`cursor`, `slot`, ...). */
enum PocketsViewPlace {
    POCKETS_VIEW_GRID_FIRST = 0x00, /* 0-14: the grid, row * 5 + column */
    POCKETS_VIEW_GRID_LAST = 0x0e,
    POCKETS_VIEW_LETTERS_FIRST = 0x0f, /* 15-24: the letters */
    POCKETS_VIEW_LETTERS_LAST = 0x18,
    POCKETS_VIEW_NO_PLACE = 0x1d
};

/* What the scene holds (`held_kind`). */
enum PocketsViewHeldKind {
    POCKETS_VIEW_HELD_NONE = 0,
    POCKETS_VIEW_HELD_1 = 1,   /* tested beside 2, never set by this overlay (a letter in ov096's) */
    POCKETS_VIEW_HELD_ITEM = 2 /* `item` and `held_state` */
};

#define POCKETS_VIEW_GRID_COLUMNS 5
#define POCKETS_VIEW_GRID_ROWS 3

typedef struct PocketsView {
    MenuScene base;        /* 0x00 */
    u8 unk_94[0x38];       /* 0x94: an object of main's (constructor func_020b9af4), updated by
                            * func_020b9ccc */
    u8 grid[0xa60];        /* 0xcc: ov094's object of the pocket slots (destructor
                            * func_ov094_0229afe0) */
    u8 letters[0x28];      /* 0xb2c: ov094's object of the letters (func_ov094_0229bc30) */
    u8 wallet[0x1638];     /* 0xb54: ov094's object of the wallet's display (destructor
                            * func_ov094_0229a2d0) */
    Popup popup;           /* 0x218c */
    Glide glide;           /* 0x225c: the held item's glide to a place */
    Glider cursor_sprite;  /* 0x2274: a Glider0 */
    u8 choice[0x3e8];      /* 0x22d8: a PagedChoice */
    ChoiceEntries entries; /* 0x26c0 */
    u8 pad_26cb;           /* 0x26cb */
    ErrorMessage error;    /* 0x26cc */
    u32 flags;             /* 0x27e8: PocketsViewFlag */
    s32 wipe_y;            /* 0x27ec: func_ov002_02207f60's, where the objects are drawn */
    s32 grab_dx;           /* 0x27f0: from the touch to the held item */
    s32 grab_dy;           /* 0x27f4 */
    s32 held_x;            /* 0x27f8: where the held item is drawn */
    s32 held_y;            /* 0x27fc */
    u8 letter[0x100];      /* 0x2800: a letter's copy; vtable reset by func_02066688 */
    u16 item;              /* 0x2900: the held item's code */
    u8 held_state;         /* 0x2902: the held item's state (the grid's func_ov094_0229aa84) */
    u8 held_kind;          /* 0x2903: PocketsViewHeldKind */
    u8 touch_place;        /* 0x2904: the place touched (func_ov099_0229d050) */
    u8 popup_place;        /* 0x2905: the place the popup tells of */
    u8 held_place;         /* 0x2906: the place the held item came from */
    u8 cursor;             /* 0x2907: PocketsViewPlace */
    u8 slot;               /* 0x2908: the place whose choice is open */
    u8 target;             /* 0x2909: the place the held item is put down on or swapped at */
    u8 return_state;       /* 0x290a: the sub state to go back to */
    u8 action;             /* 0x290b: the value of the choice row picked */
    u8 choice_row;         /* 0x290c: the choice row the cursor sprite points at */
    u8 pad_290d[3];
} PocketsView;

static_assert(offsetof(PocketsView, grid) == 0xcc && offsetof(PocketsView, wallet) == 0xb54, "ov094 objects");
static_assert(offsetof(PocketsView, popup) == 0x218c && offsetof(PocketsView, cursor_sprite) == 0x2274, "sprites");
static_assert(offsetof(PocketsView, entries) == 0x26c0 && offsetof(PocketsView, error) == 0x26cc, "choice");
static_assert(offsetof(PocketsView, flags) == 0x27e8 && offsetof(PocketsView, letter) == 0x2800, "flags");
static_assert(offsetof(PocketsView, cursor) == 0x2907 && offsetof(PocketsView, choice_row) == 0x290c, "bytes");
static_assert(sizeof(PocketsView) == 0x2910, "size (func_ov099_0229deb8)");

PocketsView *PocketsView_Destroy(PocketsView *self);
PocketsView *PocketsView_Delete(PocketsView *self);
void PocketsView_ClearFlags(PocketsView *self, unsigned int flags);
void PocketsView_SetFlags(PocketsView *self, unsigned int flags);
int PocketsView_TestFlags(PocketsView *self, int flags);
int PocketsView_MoveCursor(PocketsView *self, int keys);
void PocketsView_MoveCursorInGrid(PocketsView *self, int keys);
void PocketsView_OpenChoice(PocketsView *self, u8 place);
void PocketsView_AddEntries(PocketsView *self);
void PocketsView_CancelChoice(PocketsView *self);
void PocketsView_ShowChoice(PocketsView *self);
void PocketsView_RunAction(PocketsView *self);
void PocketsView_StartSwap(PocketsView *self, int place);
void PocketsView_StartPutDown(PocketsView *self, u8 place);
void PocketsView_StartPickUp(PocketsView *self);
void PocketsView_BeginSubState10(PocketsView *self);
void PocketsView_ShowCursorFirstOfSet(PocketsView *self);
void PocketsView_PlaceCursorSprite(PocketsView *self);
void PocketsView_PointAtFirstRow(PocketsView *self);
void PocketsView_GlideToRow(PocketsView *self);
void PocketsView_GlideToCursor(PocketsView *self);
void PocketsView_HideCursorSprite(PocketsView *self);
int PocketsView_CursorSpriteY(PocketsView *self);
int PocketsView_CursorSpriteX(PocketsView *self);
void PocketsView_ShowCursorSprite(PocketsView *self);
void PocketsView_SwapHeldWith(PocketsView *self, int place);
void PocketsView_PutHeldAt(PocketsView *self, int place);
void PocketsView_PickUpItem(PocketsView *self, int place);
void PocketsView_FollowGlide(PocketsView *self);
void PocketsView_FollowCursorSprite(PocketsView *self);
void PocketsView_FollowTouch(PocketsView *self);
void PocketsView_DrawHeld(PocketsView *self);
void PocketsView_UpdatePopup(PocketsView *self);
void PocketsView_PlacePopup(PocketsView *self);
int PocketsView_Byte6c30AtLeast(PocketsView *self, int value);
int PocketsView_TouchMoved(PocketsView *self);
void PocketsView_HighlightPlace(PocketsView *self, int place);
void PocketsView_ClearHighlights(PocketsView *self);
void PocketsView_SelectPlace(PocketsView *self, int place);
void PocketsView_ClearSelection(PocketsView *self);
int PocketsView_PlaceItemState(PocketsView *self, int place);
int PocketsView_PlaceItem(PocketsView *self, int place);
int PocketsView_PlaceIsEmpty(PocketsView *self, int place);
int PocketsView_PlaceIsTaken(PocketsView *self, int place);
int PocketsView_PlaceY(PocketsView *self, int place);
int PocketsView_PlaceX(PocketsView *self, int place);
int PocketsView_LetterPlaceAtTouch(PocketsView *self, int x, int y, int with_letter);
int PocketsView_LetterPlace(PocketsView *self, unsigned int index);
int PocketsView_LetterIndex(PocketsView *self, unsigned int place);
void PocketsView_SetSlotItem(PocketsView *self, int place, int item, int state);
int PocketsView_DropHeldAt(PocketsView *self, int place);
int PocketsView_GridPlaceAtTouch(PocketsView *self, int x, int y, int with_item);
u8 PocketsView_GridPlace(PocketsView *self, unsigned int index);
int PocketsView_GridIndex(PocketsView *self, int place);
int PocketsView_IsLetterPlace(PocketsView *self, unsigned int place);
int PocketsView_IsGridPlace(PocketsView *self, unsigned int place);
void PocketsView_UpdateObject94(PocketsView *self);
void PocketsView_GlideHeldTo(PocketsView *self, u8 place, u32 steps);
void PocketsView_PickUpWithCursor(PocketsView *self, int place);
void PocketsView_PickUpWithTouch(PocketsView *self, int place);

#endif
