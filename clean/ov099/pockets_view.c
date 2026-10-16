/* Overlay 099's scene (pockets_view.h). */
#include "pockets_view.h"

#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/display_layers.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"

/* The class's vtable. */
extern const u8 data_ov099_0229e040[];

/* The members' destructors, and main's. */
extern void func_02066688(void *object); /* sets the vtable data_020de760 */
extern void *func_ov094_0229a2d0(void *object);
extern void func_ov094_0229bc30(void *object);
extern void *func_ov094_0229afe0(void *object);

/* Main's. */
extern int func_0206fe54(void);                        /* state flag 2 is set */
extern void func_0208aa60(Popup *popup, int x, int y); /* words 0x3c and 0x40: an offset */
extern void func_020b9ccc(void *object);

/* The touch (main's bytes, as ov096/pockets_screen.c reads them) and a byte of main's set to 0
 * by func_020b93e8. */
extern u8 data_021f6c58, data_021f6c54, data_021f6c60, data_021f6c5c;
extern u8 data_021f6c30;

/* ov094's object of the pocket slots (`grid`). */
extern int func_ov094_0229a69c(void *grid, int index); /* the slot is empty */
extern int func_ov094_0229a8bc(void *grid, int index);
extern int func_ov094_0229aba4(void *grid, int index);                       /* the slot's x */
extern int func_ov094_0229ab90(void *grid, int index);                       /* the slot's y */
extern u16 func_ov094_0229aaac(void *grid, int index);                       /* the slot's item */
extern u8 func_ov094_0229aa84(void *grid, int index);                        /* the slot's item's state */
extern void func_ov094_0229aa58(void *grid, int index);                      /* the slot emptied */
extern void func_ov094_0229aa14(void *grid, int index, int item, int state); /* the slot set (and
                                                                              * the pocket slot) */
extern void func_ov094_0229a9b4(void *grid, unsigned int index);             /* the slot redrawn */
extern void func_ov094_0229a99c(void *grid, int item, int state);            /* the held item's sprite */
extern void func_ov094_0229a6bc(void *grid, int x, int y);                   /* draws the held item */
extern void func_ov094_0229abb8(void *grid, Popup *popup, int index);
extern void func_ov094_0229aafc(void *grid, int index);
extern void func_ov094_0229ab0c(void *grid);
extern void func_ov094_0229ab1c(void *grid, int index);
extern void func_ov094_0229ab5c(void *grid);
extern int func_ov094_0229aee8(void *grid, int x, int y); /* the slot under the touch */

/* ov094's object of the letters (`letters`). */
extern int func_ov094_0229b30c(void *letters, int index); /* the letter's place is empty */
extern int func_ov094_0229b788(void *letters, int index);
extern int func_ov094_0229b384(void *letters, int index); /* the place's x */
extern int func_ov094_0229b328(void *letters, int index); /* the place's y */
extern int func_ov094_0229b9b4(void *letters, Popup *popup, int index);
extern void func_ov094_0229b938(void *letters, int index);
extern void func_ov094_0229b944(void *letters);
extern void func_ov094_0229b950(void *letters, int index);
extern void func_ov094_0229b98c(void *letters);
extern int func_ov094_0229bba4(void *letters, int x, int y); /* the place under the touch */

/* What the grid's and the letters' objects answer for no place under the touch. */
#define GRID_NO_INDEX 0x23
#define LETTERS_NO_INDEX 0x37

/* The answers for a place outside the grid (PocketsView_PlaceItem, PocketsView_PlaceItemState). */
#define NO_ITEM 0xfff1
#define NO_ITEM_STATE 0xf1

/* The scene's sub states (MenuScene_SetSubState; the table of PocketsView_RunInteractive). */
#define SUB_IDLE_BY_TOUCH 0x00   /* func_ov099_0229d814: the touch in use, the cursor sprite hidden */
#define SUB_HOLD_TOUCH 0x01      /* func_ov099_0229d7a4: the pen on a touched place */
#define SUB_CHOICE_BY_TOUCH 0x02 /* func_ov099_0229d718 */
#define SUB_HOLD_BY_TOUCH 0x03   /* func_ov099_0229d698: the held item follows the stylus */
#define SUB_IDLE_BY_KEYS 0x04    /* func_ov099_0229d5c0: the cursor waits for the keys */
#define SUB_HOLD_BY_KEYS 0x05    /* func_ov099_0229d518: the held item follows the cursor */
#define SUB_CHOICE_BY_KEYS 0x06  /* func_ov099_0229d49c */
#define SUB_PICK_ROW 0x07        /* func_ov099_0229d44c */
#define SUB_WAIT_SPRITE 0x08     /* func_ov099_0229d400: back to `return_state` after the move */
#define SUB_09 0x09              /* func_ov099_0229d3e0; not set by this overlay */
#define SUB_10 0x0a              /* func_ov099_0229d3b8 */
#define SUB_PICK_UP 0x0b         /* func_ov099_0229d388: PocketsView_PickUpWithCursor */
#define SUB_PICKED_UP 0x0c       /* func_ov099_0229d358 */
#define SUB_PUT_DOWN 0x0d        /* func_ov099_0229d304 */
#define SUB_SWAP 0x0e            /* func_ov099_0229d2bc: PocketsView_SwapHeldWith */
#define SUB_SWAPPED 0x0f         /* func_ov099_0229d278 */
#define SUB_HELD_GLIDE 0x10      /* func_ov099_0229d240: the held item glides back */
#define SUB_CHOICE_OPENING 0x11  /* func_ov099_0229d204 */
#define SUB_CHOICE_CLOSE 0x12    /* func_ov099_0229d1c0 */
#define SUB_CHOICE_CLOSING 0x13  /* func_ov099_0229d1a0: then PocketsView_RunAction */
#define SUB_ERROR 0x14           /* func_ov099_0229d168; not set by this overlay */
#define SUB_STATE_COUNT 21

/* The choice's rows (texts 0-2) and their values (`action`). */
#define ROW_PICK_UP 0
#define ROW_1 1
#define ROW_2 2
#define ACTION_PICK_UP 0
#define ACTION_CLOSE 1

/* The cursor sprite's animations beyond glide.h's names. */
#define CURSOR_ANIM_PUT_DOWN 5
#define CURSOR_ANIM_SWAP 6

static MenuScene *scene_of(PocketsView *self)
{
    return &self->base;
}

static PagedChoice *choice_of(PocketsView *self)
{
    return (PagedChoice *) (void *) self->choice;
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void update_cursor_sprite(PocketsView *self)
{
    Glider *sprite = &self->cursor_sprite;
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* The members' destructors, last member first, then the base's. */
static void destroy_members(PocketsView *self)
{
    self->base.vtable = data_ov099_0229e040;
    func_02066688(self->letter);
    ErrorMessage_Destruct(&self->error);
    PagedChoice_Destroy(choice_of(self));
    Glider0_Destroy(&self->cursor_sprite);
    Glide_Destroy(&self->glide);
    Popup_Destroy(&self->popup);
    func_ov094_0229a2d0(self->wallet);
    func_ov094_0229bc30(self->letters);
    func_ov094_0229afe0(self->grid);
    MenuScene_DestroyBase(scene_of(self));
}

/* func_ov099_0229c180 */
PocketsView *PocketsView_Destroy(PocketsView *self)
{
    destroy_members(self);
    return self;
}
CLEAN_AS(func_ov099_0229c180, PocketsView_Destroy)

/* func_ov099_0229c204 */
PocketsView *PocketsView_Delete(PocketsView *self)
{
    destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov099_0229c204, PocketsView_Delete)

/* func_ov099_0229c28c */
void PocketsView_ClearFlags(PocketsView *self, unsigned int flags)
{
    self->flags &= ~flags;
}
CLEAN_AS(func_ov099_0229c28c, PocketsView_ClearFlags)

/* func_ov099_0229c29c */
void PocketsView_SetFlags(PocketsView *self, unsigned int flags)
{
    self->flags |= flags;
}
CLEAN_AS(func_ov099_0229c29c, PocketsView_SetFlags)

/* func_ov099_0229c2ac: whether any of `flags` is set. */
int PocketsView_TestFlags(PocketsView *self, int flags)
{
    return (self->flags & (u32) flags) != 0;
}
CLEAN_AS(func_ov099_0229c2ac, PocketsView_TestFlags)

/* func_ov099_0229c2c4: the cursor moved by the repeated d-pad keys `keys` (the wrap flags of
 * the last move cleared first); whether it moved. Only a cursor in the grid moves. */
int PocketsView_MoveCursor(PocketsView *self, int keys)
{
    u8 before = self->cursor;
    PocketsView_ClearFlags(self, POCKETS_VIEW_FLAGS_WRAPPED);
    if (keys == 0) {
        return 0;
    }
    if (PocketsView_IsGridPlace(self, self->cursor)) {
        PocketsView_MoveCursorInGrid(self, keys);
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov099_0229c2c4, PocketsView_MoveCursor)

/* func_ov099_0229c30c: the cursor moved in the grid. Left and right move one column, wrapping
 * to the other end of the row (and saying so in the flags); unless the move wrapped, up and
 * down then move one row, stopping at the first and last.
 * QUIRK: left is ignored when up is held too and the cursor is below the first row; right is
 * ignored whenever down is held too. */
void PocketsView_MoveCursorInGrid(PocketsView *self, int keys)
{
    int column = self->cursor % POCKETS_VIEW_GRID_COLUMNS;
    int row = self->cursor / POCKETS_VIEW_GRID_COLUMNS;

    if (KeyRepeat_HasLeft(keys)) {
        if (!(KeyRepeat_HasUp(keys) && row != 0)) {
            if (column == 0) {
                self->cursor += POCKETS_VIEW_GRID_COLUMNS - 1;
                PocketsView_SetFlags(self, POCKETS_VIEW_FLAG_WRAPPED_LEFT);
            } else {
                self->cursor -= 1;
            }
        }
    } else if (KeyRepeat_HasRight(keys)) {
        if (!KeyRepeat_HasDown(keys)) {
            if (column == POCKETS_VIEW_GRID_COLUMNS - 1) {
                self->cursor -= POCKETS_VIEW_GRID_COLUMNS - 1;
                PocketsView_SetFlags(self, POCKETS_VIEW_FLAG_WRAPPED_RIGHT);
            } else {
                self->cursor += 1;
            }
        }
    }

    if (PocketsView_TestFlags(self, POCKETS_VIEW_FLAGS_WRAPPED)) {
        return;
    }
    if (KeyRepeat_HasUp(keys)) {
        if (row > 0) {
            self->cursor -= POCKETS_VIEW_GRID_COLUMNS;
        }
    } else if (KeyRepeat_HasDown(keys) && row < POCKETS_VIEW_GRID_ROWS - 1) {
        self->cursor += POCKETS_VIEW_GRID_COLUMNS;
    }
}
CLEAN_AS(func_ov099_0229c30c, PocketsView_MoveCursorInGrid)

/* func_ov099_0229c3e0: `place` picked: its rows emptied (value 1); for a place of the grid the
 * rows added and the choice opened beside it, with the cursor sprite and the popup hidden. */
void PocketsView_OpenChoice(PocketsView *self, u8 place)
{
    self->slot = place;
    ChoiceEntries_Clear(&self->entries, ACTION_CLOSE);
    if (PocketsView_IsGridPlace(self, place)) {
        PocketsView_AddEntries(self);
        PocketsView_HideCursorSprite(self);
        Popup_Hide(&self->popup, 1);
        PocketsView_ShowChoice(self);
    }
}
CLEAN_AS(func_ov099_0229c3e0, PocketsView_OpenChoice)

/* func_ov099_0229c434: the choice's rows: the pick-up row when state flag 2 is set, then two
 * rows that close it. */
void PocketsView_AddEntries(PocketsView *self)
{
    if (func_0206fe54()) {
        ChoiceEntries_Add(&self->entries, ROW_PICK_UP, ACTION_PICK_UP);
    }
    ChoiceEntries_Add(&self->entries, ROW_1, ACTION_CLOSE);
    ChoiceEntries_Add(&self->entries, ROW_2, ACTION_CLOSE);
}
CLEAN_AS(func_ov099_0229c434, PocketsView_AddEntries)

/* func_ov099_0229c470: the choice closed without a pick: the closing action, the cursor
 * sprite back at the cursor, sub state 0x13. */
void PocketsView_CancelChoice(PocketsView *self)
{
    self->action = ACTION_CLOSE;
    PocketsView_PlaceCursorSprite(self);
    PagedChoice_RequestClose(choice_of(self), 0);
    MenuScene_SetSubState(scene_of(self), SUB_CHOICE_CLOSING);
}
CLEAN_AS(func_ov099_0229c470, PocketsView_CancelChoice)

/* func_ov099_0229c4a0: the rows shown and the choice opened beside the picked place; sub
 * state 0x11. */
void PocketsView_ShowChoice(PocketsView *self)
{
    PagedChoice_ShowEntries(choice_of(self), &self->entries, 0);
    int x = PocketsView_PlaceX(self, self->slot);
    int y = PocketsView_PlaceY(self, self->slot);
    PagedChoice_PlaceBeside(choice_of(self), x, y);
    PagedChoice_RequestOpen(choice_of(self), 0);
    MenuScene_SetSubState(scene_of(self), SUB_CHOICE_OPENING);
}
CLEAN_AS(func_ov099_0229c4a0, PocketsView_ShowChoice)

/* func_ov099_0229c4fc: the picked row's action: the pick-up, or the end of the action. */
void PocketsView_RunAction(PocketsView *self)
{
    if (self->action == ACTION_PICK_UP) {
        PocketsView_StartPickUp(self);
    } else {
        PocketsView_EndAction(self);
    }
}
CLEAN_AS(func_ov099_0229c4fc, PocketsView_RunAction)

/* func_ov099_0229c520: a swap of the held item with `place`'s begins: the popup hidden, the sub
 * state kept, the cursor sprite's animation 6, sub state 0x0e. */
void PocketsView_StartSwap(PocketsView *self, int place)
{
    Popup_Hide(&self->popup, 1);
    self->return_state = self->base.sub_state;
    self->target = (u8) place;
    Glider_SetAnim(&self->cursor_sprite, CURSOR_ANIM_SWAP);
    MenuScene_SetSubState(scene_of(self), SUB_SWAP);
}
CLEAN_AS(func_ov099_0229c520, PocketsView_StartSwap)

/* func_ov099_0229c56c: the held item is put down on `place`: the popup hidden, the cursor
 * sprite's animation 5, sub state 0x0d. */
void PocketsView_StartPutDown(PocketsView *self, u8 place)
{
    Popup_Hide(&self->popup, 1);
    self->target = place;
    Glider_SetAnim(&self->cursor_sprite, CURSOR_ANIM_PUT_DOWN);
    MenuScene_SetSubState(scene_of(self), SUB_PUT_DOWN);
}
CLEAN_AS(func_ov099_0229c56c, PocketsView_StartPutDown)

/* func_ov099_0229c5a8 (action 0): the cursor sprite's animation 4, sub state 0x0b, which
 * picks up the cursor's item once it ends. */
void PocketsView_StartPickUp(PocketsView *self)
{
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_TURN_A);
    MenuScene_SetSubState(scene_of(self), SUB_PICK_UP);
}
CLEAN_AS(func_ov099_0229c5a8, PocketsView_StartPickUp)

/* func_ov099_0229c5c8 */
void PocketsView_BeginSubState10(PocketsView *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(scene_of(self), SUB_10);
}
CLEAN_AS(func_ov099_0229c5c8, PocketsView_BeginSubState10)

/* func_ov099_0229c5e8: the first animation of the cursor sprite's set, then its update. */
void PocketsView_ShowCursorFirstOfSet(PocketsView *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    update_cursor_sprite(self);
}
CLEAN_AS(func_ov099_0229c5e8, PocketsView_ShowCursorFirstOfSet)

/* func_ov099_0229c608: the cursor sprite put at the cursor, animation 1. */
void PocketsView_PlaceCursorSprite(PocketsView *self)
{
    int x = PocketsView_CursorSpriteX(self);
    int y = PocketsView_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
}
CLEAN_AS(func_ov099_0229c608, PocketsView_PlaceCursorSprite)

/* func_ov099_0229c63c: the cursor sprite put at the choice's first row, animation 7. */
void PocketsView_PointAtFirstRow(PocketsView *self)
{
    self->choice_row = 0;
    int x = PagedChoice_TextX(choice_of(self));
    int y = PagedChoice_RowY(choice_of(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_B);
}
CLEAN_AS(func_ov099_0229c63c, PocketsView_PointAtFirstRow)

/* func_ov099_0229c688: the cursor sprite moves to the choice row in 2 steps; the sub state is
 * kept and sub state 8 waits for the move. */
void PocketsView_GlideToRow(PocketsView *self)
{
    int x = PagedChoice_TextX(choice_of(self));
    int y = PagedChoice_RowY(choice_of(self), self->choice_row);
    Glider_MoveTo(&self->cursor_sprite, x, y, 2);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(scene_of(self), SUB_WAIT_SPRITE);
}
CLEAN_AS(func_ov099_0229c688, PocketsView_GlideToRow)

/* func_ov099_0229c6dc: the cursor sprite follows the cursor: put there at once when flag 8 is
 * set (which is then cleared), else eased there in 3 steps (cue 1) with the sub state kept and
 * sub state 8 waiting for the move. */
void PocketsView_GlideToCursor(PocketsView *self)
{
    if (PocketsView_TestFlags(self, POCKETS_VIEW_FLAG_08)) {
        int x = PocketsView_CursorSpriteX(self);
        int y = PocketsView_CursorSpriteY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
        PocketsView_ClearFlags(self, POCKETS_VIEW_FLAG_08);
    } else {
        int x = PocketsView_CursorSpriteX(self);
        int y = PocketsView_CursorSpriteY(self);
        Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
        self->return_state = self->base.sub_state;
        MenuScene_SetSubState(scene_of(self), SUB_WAIT_SPRITE);
    }
}
CLEAN_AS(func_ov099_0229c6dc, PocketsView_GlideToCursor)

/* func_ov099_0229c754: the cursor sprite's animation 0, then its update. */
void PocketsView_HideCursorSprite(PocketsView *self)
{
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_NONE);
    update_cursor_sprite(self);
}
CLEAN_AS(func_ov099_0229c754, PocketsView_HideCursorSprite)

/* func_ov099_0229c778: the cursor sprite's y, the cursor's place's. */
int PocketsView_CursorSpriteY(PocketsView *self)
{
    return PocketsView_PlaceY(self, self->cursor);
}
CLEAN_AS(func_ov099_0229c778, PocketsView_CursorSpriteY)

/* func_ov099_0229c788: the cursor sprite's x: the cursor's place's plus 8, and a screen width
 * (256) further right or left when this move wrapped over the right or left edge. */
int PocketsView_CursorSpriteX(PocketsView *self)
{
    int x = PocketsView_PlaceX(self, self->cursor);
    if (PocketsView_TestFlags(self, POCKETS_VIEW_FLAG_WRAPPED_RIGHT)) {
        x += 0x100;
    } else if (PocketsView_TestFlags(self, POCKETS_VIEW_FLAG_WRAPPED_LEFT)) {
        x -= 0x100;
    }
    return x + 8;
}
CLEAN_AS(func_ov099_0229c788, PocketsView_CursorSpriteX)

/* func_ov099_0229c7d0: the cursor sprite put at the cursor, animation 1, then the first of its
 * set. */
void PocketsView_ShowCursorSprite(PocketsView *self)
{
    int x = PocketsView_CursorSpriteX(self);
    int y = PocketsView_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
    PocketsView_ShowCursorFirstOfSet(self);
}
CLEAN_AS(func_ov099_0229c7d0, PocketsView_ShowCursorSprite)

/* func_ov099_0229c80c: when an item is held, the item at `place` is picked up and the one held
 * before put there. */
void PocketsView_SwapHeldWith(PocketsView *self, int place)
{
    if (self->held_kind == POCKETS_VIEW_HELD_ITEM) {
        u16 item = self->item;
        u8 state = self->held_state;
        PocketsView_PickUpItem(self, place);
        PocketsView_SetSlotItem(self, place, item, state);
    }
}
CLEAN_AS(func_ov099_0229c80c, PocketsView_SwapHeldWith)

/* func_ov099_0229c84c: the held item (if any) put at `place`; nothing is held after. */
void PocketsView_PutHeldAt(PocketsView *self, int place)
{
    if (self->held_kind == POCKETS_VIEW_HELD_ITEM) {
        PocketsView_SetSlotItem(self, place, self->item, self->held_state);
    }
    self->held_kind = POCKETS_VIEW_HELD_NONE;
}
CLEAN_AS(func_ov099_0229c84c, PocketsView_PutHeldAt)

/* func_ov099_0229c880: the item of grid place `place` taken from its slot and held, its
 * sprite given to the grid's object.
 * QUIRK: for other places PocketsView_IsLetterPlace is asked and its answer unused. */
void PocketsView_PickUpItem(PocketsView *self, int place)
{
    if (PocketsView_IsGridPlace(self, (unsigned int) place)) {
        int index = PocketsView_GridIndex(self, place);
        self->held_kind = POCKETS_VIEW_HELD_ITEM;
        self->item = func_ov094_0229aaac(self->grid, index);
        self->held_state = func_ov094_0229aa84(self->grid, index);
        func_ov094_0229aa58(self->grid, index);
        func_ov094_0229a99c(self->grid, self->item, self->held_state);
    } else {
        PocketsView_IsLetterPlace(self, (unsigned int) place);
    }
}
CLEAN_AS(func_ov099_0229c880, PocketsView_PickUpItem)

/* func_ov099_0229c8f8: the held item drawn where the glide is. */
void PocketsView_FollowGlide(PocketsView *self)
{
    self->held_x = Glide_X(&self->glide);
    self->held_y = Glide_Y(&self->glide);
}
CLEAN_AS(func_ov099_0229c8f8, PocketsView_FollowGlide)

/* func_ov099_0229c928: the held item drawn at the cursor sprite's frame, 2 left and 4 up. */
void PocketsView_FollowCursorSprite(PocketsView *self)
{
    self->held_x = Glider_FrameX(&self->cursor_sprite) - 2;
    self->held_y = Glider_FrameY(&self->cursor_sprite) - 4;
}
CLEAN_AS(func_ov099_0229c928, PocketsView_FollowCursorSprite)

/* func_ov099_0229c95c: the held item drawn at the touch, kept at the offset it was grabbed at.
 * QUIRK: the sums wrap at 32 bits (done unsigned, as the ROM's code does). */
void PocketsView_FollowTouch(PocketsView *self)
{
    self->held_x = (s32) ((u32) self->grab_dx + data_021f6c58);
    self->held_y = (s32) ((u32) self->grab_dy + data_021f6c54);
}
CLEAN_AS(func_ov099_0229c95c, PocketsView_FollowTouch)

/* func_ov099_0229c994: the held item drawn by the grid's object, unless it is hidden. */
void PocketsView_DrawHeld(PocketsView *self)
{
    if (PocketsView_TestFlags(self, POCKETS_VIEW_FLAG_HELD_HIDDEN)) {
        return;
    }
    if (self->held_kind == POCKETS_VIEW_HELD_ITEM) {
        func_ov094_0229a6bc(self->grid, self->held_x, self->held_y);
    }
}
CLEAN_AS(func_ov099_0229c994, PocketsView_DrawHeld)

/* func_ov099_0229c9d0: the popup tells of the cursor's place: queued for a taken place of the
 * grid or the letters (kept as `popup_place`), its queue cleared for an empty one or another
 * place. */
void PocketsView_UpdatePopup(PocketsView *self)
{
    if ((PocketsView_IsGridPlace(self, self->cursor) || PocketsView_IsLetterPlace(self, self->cursor)) &&
        !PocketsView_PlaceIsEmpty(self, self->cursor)) {
        self->popup_place = self->cursor;
        Popup_Queue(&self->popup);
    } else {
        Popup_ClearQueued(&self->popup);
    }
}
CLEAN_AS(func_ov099_0229c9d0, PocketsView_UpdatePopup)

/* func_ov099_0229ca34: the popup put above its place (0x6d left and 0x78 up of it, 8 more up
 * when state flag 2 is set) and filled by the grid's or the letters' object. */
void PocketsView_PlacePopup(PocketsView *self)
{
    int x = PocketsView_PlaceX(self, self->popup_place) - 0x6d;
    int y = PocketsView_PlaceY(self, self->popup_place) - 0x78;
    if (func_0206fe54() != 0) {
        y -= 8;
    }
    func_0208aa60(&self->popup, x, y);
    if (PocketsView_IsGridPlace(self, self->popup_place)) {
        func_ov094_0229abb8(self->grid, &self->popup, PocketsView_GridIndex(self, self->popup_place));
    } else if (PocketsView_IsLetterPlace(self, self->popup_place)) {
        func_ov094_0229b9b4(self->letters, &self->popup, PocketsView_LetterIndex(self, self->popup_place));
    }
}
CLEAN_AS(func_ov099_0229ca34, PocketsView_PlacePopup)

/* func_ov099_0229cac8: whether main's byte data_021f6c30 is at least `value` (the scene asks
 * for 9 before opening a touched place's choice). */
int PocketsView_Byte6c30AtLeast(PocketsView *self, int value)
{
    (void) self;
    return data_021f6c30 >= value;
}
CLEAN_AS(func_ov099_0229cac8, PocketsView_Byte6c30AtLeast)

/* The distance between two coordinates. */
static int distance(int a, int b)
{
    return a > b ? a - b : b - a;
}

/* func_ov099_0229cadc: whether the touch at data_021f6c60/5c is more than 8 pixels from the
 * one at data_021f6c58/54, in x or in y. */
int PocketsView_TouchMoved(PocketsView *self)
{
    (void) self;
    return distance(data_021f6c60, data_021f6c58) > 8 || distance(data_021f6c5c, data_021f6c54) > 8;
}
CLEAN_AS(func_ov099_0229cadc, PocketsView_TouchMoved)

/* func_ov099_0229cb20: `place` marked in its part's object. */
void PocketsView_HighlightPlace(PocketsView *self, int place)
{
    if (PocketsView_IsGridPlace(self, (unsigned int) place)) {
        func_ov094_0229aafc(self->grid, PocketsView_GridIndex(self, place));
    } else if (PocketsView_IsLetterPlace(self, (unsigned int) place)) {
        func_ov094_0229b938(self->letters, PocketsView_LetterIndex(self, (unsigned int) place));
    }
}
CLEAN_AS(func_ov099_0229cb20, PocketsView_HighlightPlace)

/* func_ov099_0229cb70: no place marked in either object. */
void PocketsView_ClearHighlights(PocketsView *self)
{
    func_ov094_0229ab0c(self->grid);
    func_ov094_0229b944(self->letters);
}
CLEAN_AS(func_ov099_0229cb70, PocketsView_ClearHighlights)

/* func_ov099_0229cb8c: `place` selected in its part's object, the other part's selection
 * cleared; for a place of neither, both cleared. */
void PocketsView_SelectPlace(PocketsView *self, int place)
{
    if (PocketsView_IsGridPlace(self, (unsigned int) place)) {
        func_ov094_0229ab1c(self->grid, PocketsView_GridIndex(self, place));
        func_ov094_0229b98c(self->letters);
    } else if (PocketsView_IsLetterPlace(self, (unsigned int) place)) {
        func_ov094_0229b950(self->letters, PocketsView_LetterIndex(self, (unsigned int) place));
        func_ov094_0229ab5c(self->grid);
    } else {
        PocketsView_ClearSelection(self);
    }
}
CLEAN_AS(func_ov099_0229cb8c, PocketsView_SelectPlace)

/* func_ov099_0229cbf4 */
void PocketsView_ClearSelection(PocketsView *self)
{
    func_ov094_0229ab5c(self->grid);
    func_ov094_0229b98c(self->letters);
}
CLEAN_AS(func_ov099_0229cbf4, PocketsView_ClearSelection)

/* func_ov099_0229cc10: the state of the item at grid place `place`, else 0xf1. */
int PocketsView_PlaceItemState(PocketsView *self, int place)
{
    if (PocketsView_IsGridPlace(self, (unsigned int) place)) {
        return func_ov094_0229aa84(self->grid, PocketsView_GridIndex(self, place));
    }
    return NO_ITEM_STATE;
}
CLEAN_AS(func_ov099_0229cc10, PocketsView_PlaceItemState)

/* func_ov099_0229cc40: the item at grid place `place`, else none (0xfff1). */
int PocketsView_PlaceItem(PocketsView *self, int place)
{
    if (PocketsView_IsGridPlace(self, (unsigned int) place)) {
        return func_ov094_0229aaac(self->grid, PocketsView_GridIndex(self, place));
    }
    return NO_ITEM;
}
CLEAN_AS(func_ov099_0229cc40, PocketsView_PlaceItem)

/* func_ov099_0229cc74: whether `place` of the grid or the letters is empty (by its part's
 * object); other places count as empty. */
int PocketsView_PlaceIsEmpty(PocketsView *self, int place)
{
    if (PocketsView_IsGridPlace(self, (unsigned int) place)) {
        return func_ov094_0229a69c(self->grid, PocketsView_GridIndex(self, place));
    }
    if (PocketsView_IsLetterPlace(self, (unsigned int) place)) {
        return func_ov094_0229b30c(self->letters, PocketsView_LetterIndex(self, (unsigned int) place));
    }
    return 1;
}
CLEAN_AS(func_ov099_0229cc74, PocketsView_PlaceIsEmpty)

/* func_ov099_0229ccc8: what the part's object answers for `place` being taken; 0 for other
 * places. */
int PocketsView_PlaceIsTaken(PocketsView *self, int place)
{
    if (PocketsView_IsGridPlace(self, (unsigned int) place)) {
        return func_ov094_0229a8bc(self->grid, PocketsView_GridIndex(self, place));
    }
    if (PocketsView_IsLetterPlace(self, (unsigned int) place)) {
        return func_ov094_0229b788(self->letters, PocketsView_LetterIndex(self, (unsigned int) place));
    }
    return 0;
}
CLEAN_AS(func_ov099_0229ccc8, PocketsView_PlaceIsTaken)

/* func_ov099_0229cd1c: the y of `place`, by its part's object; 0 for other places. */
int PocketsView_PlaceY(PocketsView *self, int place)
{
    if (PocketsView_IsGridPlace(self, (unsigned int) place)) {
        return func_ov094_0229ab90(self->grid, PocketsView_GridIndex(self, place));
    }
    if (PocketsView_IsLetterPlace(self, (unsigned int) place)) {
        return func_ov094_0229b328(self->letters, PocketsView_LetterIndex(self, (unsigned int) place));
    }
    return 0;
}
CLEAN_AS(func_ov099_0229cd1c, PocketsView_PlaceY)

/* func_ov099_0229cd70: the x of `place`, by its part's object; 0 for other places. */
int PocketsView_PlaceX(PocketsView *self, int place)
{
    if (PocketsView_IsGridPlace(self, (unsigned int) place)) {
        return func_ov094_0229aba4(self->grid, PocketsView_GridIndex(self, place));
    }
    if (PocketsView_IsLetterPlace(self, (unsigned int) place)) {
        return func_ov094_0229b384(self->letters, PocketsView_LetterIndex(self, (unsigned int) place));
    }
    return 0;
}
CLEAN_AS(func_ov099_0229cd70, PocketsView_PlaceX)

/* func_ov099_0229cdc4: the letter's place under the touch, by the letters' object; with
 * `with_letter`, only one that holds a letter. POCKETS_VIEW_NO_PLACE for none. */
int PocketsView_LetterPlaceAtTouch(PocketsView *self, int x, int y, int with_letter)
{
    int index = func_ov094_0229bba4(self->letters, x, y);
    if (index == LETTERS_NO_INDEX) {
        return POCKETS_VIEW_NO_PLACE;
    }
    if (with_letter != 0 && func_ov094_0229b30c(self->letters, index) != 0) {
        return POCKETS_VIEW_NO_PLACE;
    }
    return PocketsView_LetterPlace(self, (unsigned int) index);
}
CLEAN_AS(func_ov099_0229cdc4, PocketsView_LetterPlaceAtTouch)

/* func_ov099_0229ce04: the place of letter `index` (0-9), else POCKETS_VIEW_NO_PLACE. */
int PocketsView_LetterPlace(PocketsView *self, unsigned int index)
{
    (void) self;
    if (index <= 9) {
        return (int) index + POCKETS_VIEW_LETTERS_FIRST;
    }
    return POCKETS_VIEW_NO_PLACE;
}
CLEAN_AS(func_ov099_0229ce04, PocketsView_LetterPlace)

/* func_ov099_0229ce14: the letter index (0-9) of a letter's place, else 0. */
int PocketsView_LetterIndex(PocketsView *self, unsigned int place)
{
    (void) self;
    if (place >= POCKETS_VIEW_LETTERS_FIRST && place <= POCKETS_VIEW_LETTERS_LAST) {
        return (int) (place - POCKETS_VIEW_LETTERS_FIRST);
    }
    return 0;
}
CLEAN_AS(func_ov099_0229ce14, PocketsView_LetterIndex)

/* func_ov099_0229ce28: for a grid place, its slot set to `item` in `state` (the grid's object
 * writes the pocket slot too) and redrawn. */
void PocketsView_SetSlotItem(PocketsView *self, int place, int item, int state)
{
    if (PocketsView_IsGridPlace(self, (unsigned int) place)) {
        int index = PocketsView_GridIndex(self, place);
        func_ov094_0229aa14(self->grid, index, item, state);
        func_ov094_0229a9b4(self->grid, (unsigned int) index);
    }
}
CLEAN_AS(func_ov099_0229ce28, PocketsView_SetSlotItem)

/* func_ov099_0229ce68: the held item put down at grid place `place`; an item already there goes
 * to the place the held one came from. Whether `place` was a grid place. */
int PocketsView_DropHeldAt(PocketsView *self, int place)
{
    if (!PocketsView_IsGridPlace(self, (unsigned int) place)) {
        return 0;
    }
    int item = PocketsView_PlaceItem(self, place);
    if (item != NO_ITEM) {
        PocketsView_SetSlotItem(self, self->held_place, item, PocketsView_PlaceItemState(self, place));
    }
    PocketsView_PutHeldAt(self, place);
    return 1;
}
CLEAN_AS(func_ov099_0229ce68, PocketsView_DropHeldAt)

/* func_ov099_0229ceb8: the grid's place under the touch, by the grid's object; with
 * `with_item`, only one that holds an item. POCKETS_VIEW_NO_PLACE for none. */
int PocketsView_GridPlaceAtTouch(PocketsView *self, int x, int y, int with_item)
{
    int index = func_ov094_0229aee8(self->grid, x, y);
    if (index == GRID_NO_INDEX) {
        return POCKETS_VIEW_NO_PLACE;
    }
    if (with_item != 0 && func_ov094_0229a69c(self->grid, index) != 0) {
        return POCKETS_VIEW_NO_PLACE;
    }
    return PocketsView_GridPlace(self, (unsigned int) index);
}
CLEAN_AS(func_ov099_0229ceb8, PocketsView_GridPlaceAtTouch)

/* func_ov099_0229cef4: the place of grid slot `index` (0-14), else POCKETS_VIEW_NO_PLACE. */
u8 PocketsView_GridPlace(PocketsView *self, unsigned int index)
{
    (void) self;
    if (index <= POCKETS_VIEW_GRID_LAST) {
        return (u8) index;
    }
    return POCKETS_VIEW_NO_PLACE;
}
CLEAN_AS(func_ov099_0229cef4, PocketsView_GridPlace)

/* func_ov099_0229cf04: the slot index of a grid place, else 0. */
int PocketsView_GridIndex(PocketsView *self, int place)
{
    if (PocketsView_IsGridPlace(self, (unsigned int) place)) {
        return (u8) place;
    }
    return 0;
}
CLEAN_AS(func_ov099_0229cf04, PocketsView_GridIndex)

/* func_ov099_0229cf20: whether `place` is a letter's. */
int PocketsView_IsLetterPlace(PocketsView *self, unsigned int place)
{
    (void) self;
    return place >= POCKETS_VIEW_LETTERS_FIRST && place <= POCKETS_VIEW_LETTERS_LAST;
}
CLEAN_AS(func_ov099_0229cf20, PocketsView_IsLetterPlace)

/* func_ov099_0229cf30: whether `place` is in the grid. */
int PocketsView_IsGridPlace(PocketsView *self, unsigned int place)
{
    (void) self;
    return place <= POCKETS_VIEW_GRID_LAST;
}
CLEAN_AS(func_ov099_0229cf30, PocketsView_IsGridPlace)

/* func_ov099_0229cf3c: the object at 0x94 updated by main's func_020b9ccc. */
void PocketsView_UpdateObject94(PocketsView *self)
{
    func_020b9ccc(self->unk_94);
}
CLEAN_AS(func_ov099_0229cf3c, PocketsView_UpdateObject94)

/* func_ov099_0229cf48: the held item glides from where it is drawn to `place` (kept as
 * `held_place`) in `steps` steps; sub state 0x10 waits for the glide. */
void PocketsView_GlideHeldTo(PocketsView *self, u8 place, u32 steps)
{
    self->held_place = place;
    Glide_SetPlace(&self->glide, self->held_x, self->held_y);
    int x = PocketsView_PlaceX(self, place);
    int y = PocketsView_PlaceY(self, place);
    Glide_MoveTo(&self->glide, x, y, (int) steps);
    Glide_Step(&self->glide);
    PocketsView_FollowGlide(self);
    MenuScene_SetSubState(scene_of(self), SUB_HELD_GLIDE);
}
CLEAN_AS(func_ov099_0229cf48, PocketsView_GlideHeldTo)

/* func_ov099_0229cfb4: the item at `place` picked up with the cursor (the popup hidden); when
 * one is held, the sub state to go back to is 5, where the keys move it. It is drawn at the
 * cursor sprite. */
void PocketsView_PickUpWithCursor(PocketsView *self, int place)
{
    self->held_place = (u8) place;
    Popup_Hide(&self->popup, 1);
    PocketsView_PickUpItem(self, place);
    if (self->held_kind == POCKETS_VIEW_HELD_ITEM) {
        self->return_state = SUB_HOLD_BY_KEYS;
    }
    PocketsView_FollowCursorSprite(self);
}
CLEAN_AS(func_ov099_0229cfb4, PocketsView_PickUpWithCursor)

/* func_ov099_0229d004: the item at `place` picked up with the stylus (the popup hidden); when
 * one is held, sub state 3, where it follows the stylus. It is drawn at the touch. */
void PocketsView_PickUpWithTouch(PocketsView *self, int place)
{
    self->held_place = (u8) place;
    Popup_Hide(&self->popup, 1);
    PocketsView_PickUpItem(self, place);
    if (self->held_kind == POCKETS_VIEW_HELD_ITEM) {
        MenuScene_SetSubState(scene_of(self), SUB_HOLD_BY_TOUCH);
    }
    PocketsView_FollowTouch(self);
}
CLEAN_AS(func_ov099_0229d004, PocketsView_PickUpWithTouch)

/* The sub states and the states the scene runs each frame, its draw, its setup and its
 * construction. */

/* The pad (autoload_2/input.h): the buttons pressed this frame. */
extern PadState data_021fbe40;
#define PAD_A 0x0001
#define PAD_B 0x0002
#define PAD_Y 0x0800

/* The pen (main's bytes, as menu_scene.c reads them). */
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */

/* Main's. */
extern int func_0206fe60(void);                            /* state flag 2 is clear */
extern int func_0208e484(Glider *glider);                  /* whether the animation ended */
extern int func_0208e4bc(Glider *glider);                  /* the animation, anim_id */
extern void func_0208e5cc(Glider *glider);                 /* unk_4a = 1 */
extern void func_0209a088(u16 *item, int state, int slot); /* stores a pocket slot */
extern void *func_020b9af4(void *object);
extern void func_02066694(void *letter);

/* The parent process (ov092's): told the scene ends (its byte 0x91 set to the code; code 0x44
 * also calls func_0206efc0 and, with `flag`, sends PXI command 2), and told of the close. */
extern void func_ov092_02299324(Process *parent, int code, int flag);
extern void func_ov092_0229929c(Process *parent);

/* The objects of ov094's: setup, the frame's updates, the draws at a vertical offset, the
 * teardown and the constructors. */
extern void func_ov094_0229af40(void *grid, int value);
extern void func_ov094_0229bbd8(void *letters, int value);
extern void func_ov094_0229a2b0(void *wallet, int value);
extern void func_ov094_0229a29c(void *wallet, int value); /* func_ov094_0229a204, then func_ov094_0229a1c0 */
extern int func_ov094_0229a098(void *wallet);
extern void func_ov094_0229ad20(void *grid);
extern void func_ov094_0229b2b0(void *letters);
extern void func_ov094_0229a084(void *wallet);
extern void func_ov094_0229af20(void *grid);
extern void func_ov094_0229bbc0(void *letters);
extern void func_ov094_0229a05c(void *wallet);
extern void func_ov094_0229a850(void *grid, int x, int offset_y);
extern void func_ov094_0229b738(void *letters, int x, int offset_y);
extern void func_ov094_02299d84(void *wallet, int offset_y);
extern void func_ov094_0229a038(void *wallet);
extern void func_ov094_0229af18(void *grid);
extern void *func_ov094_0229b000(void *grid);
extern void func_ov094_0229bc3c(void *letters);
extern void *func_ov094_0229a2ec(void *wallet);

/* The tables of member functions (member_pointer.h): the guards, the tables (one block at
 * 0x0229e0a8 in the symbol table: the 5 states, then the 21 sub states at 0x0229e0d0) and
 * their constants. */
#define STATE_COUNT 5
extern u32 data_ov099_0229e0a0; /* the sub states' guard */
extern u32 data_ov099_0229e0a4; /* the states' guard */
extern MemberPointer data_ov099_0229e0a8[STATE_COUNT + SUB_STATE_COUNT];
extern const MemberPointer data_ov099_0229df60, data_ov099_0229df68, data_ov099_0229df70, data_ov099_0229df78,
    data_ov099_0229df80, data_ov099_0229df88, data_ov099_0229df90, data_ov099_0229df98, data_ov099_0229dfa0,
    data_ov099_0229dfa8, data_ov099_0229dfb0, data_ov099_0229dfb8, data_ov099_0229dfc8, data_ov099_0229dfd0,
    data_ov099_0229dfd8, data_ov099_0229dfe0, data_ov099_0229dfe8, data_ov099_0229dff0, data_ov099_0229dff8,
    data_ov099_0229e000, data_ov099_0229e008, data_ov099_0229e010, data_ov099_0229e018, data_ov099_0229e020,
    data_ov099_0229e028, data_ov099_0229e030;

/* The scene's states (MenuScene_SetState; the table of PocketsView_RunState). */
#define STATE_START_SETUP 0    /* func_ov099_0229db94 */
#define STATE_START_WIPE_IN 1  /* func_ov099_0229db24 */
#define STATE_WIPE_IN 2        /* func_ov099_0229dae8 */
#define STATE_START_WIPE_OUT 3 /* func_ov099_0229da84 */
#define STATE_WIPE_OUT 4       /* func_ov099_0229da34 */

/* The scene's 2D layer, and its wipe on window 2. */
#define POCKETS_VIEW_LAYER 6
#define WIPE_LAYERS 8
#define WIPE_MARGIN 0x30

/* What the parent is told when the scene ends. */
#define PARENT_CODE_END 0x44

/* What data_021f6c30 reaches before a touched place's choice opens. */
#define OPEN_CHOICE_BYTE 9

/* The frames a popup stays after the pen leaves a place. */
#define POPUP_FRAMES 60

/* The parent process. */
static Process *parent_of(PocketsView *self)
{
    return Process_GetParent((Process *) (void *) self);
}

/* Calls the draw (vtable slot 2) of a member object through its own vtable, as the game does. */
static void draw_member(void *object)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[2])(object);
}

/* The pen went down this frame. */
static int pen_pressed(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* The value kept with choice row `row`. The game reads the byte `row` places after the values'
 * start whatever the row; read the same way here, within the scene. */
static u8 row_value(PocketsView *self, int row)
{
    const u8 *values = (const u8 *) self + offsetof(PocketsView, entries) + offsetof(ChoiceEntries, values);
    return values[row];
}

/* Choice row `row` picked (with sound 1): its value kept as `action`, and sub state 0x12
 * closes the choice. */
static void pick_row(PocketsView *self, int row)
{
    PagedChoice_PickRowWithSound(choice_of(self), row, 1);
    self->action = row_value(self, row);
    MenuScene_SetSubState(scene_of(self), SUB_CHOICE_CLOSE);
}

/* The repeated keys move the cursor: the popup told of the new place and hidden, the cursor
 * sprite following. Whether they did. */
static int move_cursor_by_keys(PocketsView *self)
{
    u32 keys = MenuScene_LatchRepeatedKeys(scene_of(self));
    if (PocketsView_MoveCursor(self, (int) keys) == 0) {
        return 0;
    }
    PocketsView_UpdatePopup(self);
    PocketsView_GlideToCursor(self);
    Popup_Hide(&self->popup, 0);
    return 1;
}

/* func_ov099_0229d050: the pen touched `place` (sub state 1): the offset from the touch to the
 * place kept and the popup queued for it; POCKETS_VIEW_FLAG_04 set for a grid place its object
 * does not call taken, cleared otherwise. */
void PocketsView_TouchPlace(PocketsView *self, u8 place)
{
    self->touch_place = place;
    MenuScene_SetSubState(scene_of(self), SUB_HOLD_TOUCH);
    u8 touch_x = data_021f6c58;
    u8 touch_y = data_021f6c54;
    self->grab_dx = PocketsView_PlaceX(self, self->touch_place) - touch_x;
    self->grab_dy = PocketsView_PlaceY(self, self->touch_place) - touch_y;
    self->popup_place = place;
    Popup_Queue(&self->popup);
    if (PocketsView_IsLetterPlace(self, place) || PocketsView_PlaceIsTaken(self, place)) {
        PocketsView_ClearFlags(self, POCKETS_VIEW_FLAG_04);
    } else {
        PocketsView_SetFlags(self, POCKETS_VIEW_FLAG_04);
    }
}
CLEAN_AS(func_ov099_0229d050, PocketsView_TouchPlace)

/* func_ov099_0229d0f0: the action ends: back to sub state 0 with the cursor sprite hidden
 * while state flag 2 is clear, else to sub state 4 with it at the cursor. */
void PocketsView_EndAction(PocketsView *self)
{
    if (func_0206fe60() != 0) {
        PocketsView_EndActionHidden(self);
    } else {
        PocketsView_EndActionAtCursor(self);
    }
}
CLEAN_AS(func_ov099_0229d0f0, PocketsView_EndAction)

/* func_ov099_0229d110: no popup place, the cursor sprite shown at the cursor, the key repeat
 * reset, the popup told of the cursor's place, sub state 4 and the cursor's place selected. */
void PocketsView_EndActionAtCursor(PocketsView *self)
{
    self->popup_place = POCKETS_VIEW_NO_PLACE;
    PocketsView_ShowCursorSprite(self);
    MenuScene_ResetKeyRepeat(scene_of(self));
    PocketsView_UpdatePopup(self);
    MenuScene_SetSubState(scene_of(self), SUB_IDLE_BY_KEYS);
    PocketsView_SelectPlace(self, self->cursor);
}
CLEAN_AS(func_ov099_0229d110, PocketsView_EndActionAtCursor)

/* func_ov099_0229d14c */
void PocketsView_EndActionHidden(PocketsView *self)
{
    PocketsView_HideCursorSprite(self);
    PocketsView_ClearSelection(self);
    MenuScene_SetSubState(scene_of(self), SUB_IDLE_BY_TOUCH);
}
CLEAN_AS(func_ov099_0229d14c, PocketsView_EndActionHidden)

/* func_ov099_0229d168 (sub state 0x14): once the error message is done, back to the kept sub
 * state and the cursor sprite's byte 0x4a set. */
void PocketsView_WaitError(PocketsView *self)
{
    if (ErrorMessage_Update(&self->error, 0)) {
        MenuScene_SetSubState(scene_of(self), self->return_state);
        func_0208e5cc(&self->cursor_sprite);
    }
}
CLEAN_AS(func_ov099_0229d168, PocketsView_WaitError)

/* func_ov099_0229d1a0 (sub state 0x13): once the choice is idle, the picked row's action. */
void PocketsView_RunActionWhenIdle(PocketsView *self)
{
    if (PagedChoice_IsIdle(choice_of(self))) {
        PocketsView_RunAction(self);
    }
}
CLEAN_AS(func_ov099_0229d1a0, PocketsView_RunActionWhenIdle)

/* func_ov099_0229d1c0 (sub state 0x12): when the choice's delay has run out, the choice asked
 * to close, the cursor sprite (when it shows an animation) put back at the cursor and sub
 * state 0x13. */
void PocketsView_CloseChoice(PocketsView *self)
{
    if (PagedChoice_CountDown(choice_of(self)) == 0) {
        return;
    }
    PagedChoice_RequestClose(choice_of(self), 0);
    if (func_0208e4bc(&self->cursor_sprite) != 0) {
        PocketsView_PlaceCursorSprite(self);
    }
    MenuScene_SetSubState(scene_of(self), SUB_CHOICE_CLOSING);
}
CLEAN_AS(func_ov099_0229d1c0, PocketsView_CloseChoice)

/* func_ov099_0229d204 (sub state 0x11): once the choice is shown: with state flag 2 the cursor
 * sprite at its first row and sub state 6 (the keys), else sub state 2 (the touch). */
void PocketsView_WaitChoiceToPoint(PocketsView *self)
{
    if (PagedChoice_IsShown(choice_of(self)) == 0) {
        return;
    }
    if (func_0206fe54() != 0) {
        PocketsView_PointAtFirstRow(self);
        MenuScene_SetSubState(scene_of(self), SUB_CHOICE_BY_KEYS);
    } else {
        MenuScene_SetSubState(scene_of(self), SUB_CHOICE_BY_TOUCH);
    }
}
CLEAN_AS(func_ov099_0229d204, PocketsView_WaitChoiceToPoint)

/* func_ov099_0229d240 (sub state 0x10): the held item follows the glide; when it is over, it is
 * put down at the place it came from and the action ends. */
void PocketsView_StepHeldGlide(PocketsView *self)
{
    if (Glide_Step(&self->glide)) {
        PocketsView_PutHeldAt(self, self->held_place);
        PocketsView_EndAction(self);
    } else {
        PocketsView_FollowGlide(self);
    }
}
CLEAN_AS(func_ov099_0229d240, PocketsView_StepHeldGlide)

/* func_ov099_0229d278 (sub state 0x0f): after a swap, back to the kept sub state once the
 * cursor sprite's animation ends. While its turn has settled, the held item is drawn again and
 * follows the cursor sprite. */
void PocketsView_FinishSwapWithCursor(PocketsView *self)
{
    if (func_0208e484(&self->cursor_sprite)) {
        MenuScene_SetSubState(scene_of(self), self->return_state);
    }
    if (Glider_IsTurnSettled(&self->cursor_sprite)) {
        PocketsView_ClearFlags(self, POCKETS_VIEW_FLAG_HELD_HIDDEN);
        PocketsView_FollowCursorSprite(self);
    }
}
CLEAN_AS(func_ov099_0229d278, PocketsView_FinishSwapWithCursor)

/* func_ov099_0229d2bc (sub state 0x0e): the held item changes places with the item at `target`
 * and is hidden while the cursor sprite turns (sub state 0x0f), unless the turn is at its frame
 * 2, which goes back to sub state 4 instead. */
void PocketsView_SwapWithCursor(PocketsView *self)
{
    if (Glider_IsTurnAtFrame2(&self->cursor_sprite) == 0) {
        PocketsView_SwapHeldWith(self, self->target);
        PocketsView_SetFlags(self, POCKETS_VIEW_FLAG_HELD_HIDDEN);
        MenuScene_SetSubState(scene_of(self), SUB_SWAPPED);
        PocketsView_UpdatePopup(self);
    } else {
        MenuScene_SetSubState(scene_of(self), SUB_IDLE_BY_KEYS);
    }
}
CLEAN_AS(func_ov099_0229d2bc, PocketsView_SwapWithCursor)

/* func_ov099_0229d304 (sub state 0x0d): while the cursor sprite's turn has not settled the held
 * item follows it. Then it is put down at `target` when the cursor is there (the popup told of
 * the place, sub state 4), else it glides to `target`. */
void PocketsView_PutDownWithCursor(PocketsView *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite) != 0) {
        PocketsView_FollowCursorSprite(self);
        return;
    }
    u8 target = self->target;
    if (self->cursor == target) {
        PocketsView_DropHeldAt(self, target);
        PocketsView_UpdatePopup(self);
        MenuScene_SetSubState(scene_of(self), SUB_IDLE_BY_KEYS);
    } else {
        PocketsView_GlideHeldTo(self, target, 4);
    }
}
CLEAN_AS(func_ov099_0229d304, PocketsView_PutDownWithCursor)

/* func_ov099_0229d358 (sub state 0x0c): after a pick up, back to the kept sub state once the
 * cursor sprite's animation ends; the held item follows the cursor sprite. */
void PocketsView_FinishPickUp(PocketsView *self)
{
    if (func_0208e484(&self->cursor_sprite) != 0) {
        MenuScene_SetSubState(scene_of(self), self->return_state);
    }
    PocketsView_FollowCursorSprite(self);
}
CLEAN_AS(func_ov099_0229d358, PocketsView_FinishPickUp)

/* func_ov099_0229d388 (sub state 0x0b): once the cursor sprite's turn has settled, the item at
 * the cursor is picked up (sub state 0x0c). */
void PocketsView_PickUpOnTurn(PocketsView *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite)) {
        PocketsView_PickUpWithCursor(self, self->cursor);
        MenuScene_SetSubState(scene_of(self), SUB_PICKED_UP);
    }
}
CLEAN_AS(func_ov099_0229d388, PocketsView_PickUpOnTurn)

/* func_ov099_0229d3b8 (sub state 0x0a): once the cursor sprite's animation ends, the first of
 * its set and sub state 4. */
void PocketsView_WaitCursorAnim(PocketsView *self)
{
    if (func_0208e484(&self->cursor_sprite)) {
        PocketsView_ShowCursorFirstOfSet(self);
        MenuScene_SetSubState(scene_of(self), SUB_IDLE_BY_KEYS);
    }
}
CLEAN_AS(func_ov099_0229d3b8, PocketsView_WaitCursorAnim)

/* func_ov099_0229d3e0 (sub state 9): once the cursor sprite's animation ends,
 * PocketsView_BeginSubState10. */
void PocketsView_WaitAnimToSubState10(PocketsView *self)
{
    if (func_0208e484(&self->cursor_sprite)) {
        PocketsView_BeginSubState10(self);
    }
}
CLEAN_AS(func_ov099_0229d3e0, PocketsView_WaitAnimToSubState10)

/* func_ov099_0229d400 (sub state 8): once the cursor sprite stops, back to the kept sub state;
 * back to 4 or 5 (the keys' sub states), the cursor's place is selected. The held item follows
 * the cursor sprite. */
void PocketsView_WaitCursorGlide(PocketsView *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(scene_of(self), self->return_state);
        if (self->return_state == SUB_IDLE_BY_KEYS || self->return_state == SUB_HOLD_BY_KEYS) {
            PocketsView_SelectPlace(self, self->cursor);
        }
    }
    PocketsView_FollowCursorSprite(self);
}
CLEAN_AS(func_ov099_0229d400, PocketsView_WaitCursorGlide)

/* func_ov099_0229d44c (sub state 7): once the cursor sprite's press animation ends, the row it
 * points at is picked. */
void PocketsView_PickActionRow(PocketsView *self)
{
    if (func_0208e484(&self->cursor_sprite)) {
        pick_row(self, self->choice_row);
    }
}
CLEAN_AS(func_ov099_0229d44c, PocketsView_PickActionRow)

/* func_ov099_0229d49c (sub state 6): the choice by the keys. A touch cancels it; the d-pad moves
 * the cursor sprite over the rows; A presses on the row (sub state 7); B cancels it. */
void PocketsView_ActionChoiceByKeys(PocketsView *self)
{
    if (MenuScene_TakeTouch(scene_of(self)) != 0) {
        PocketsView_CancelChoice(self);
        return;
    }
    u32 keys = MenuScene_LatchRepeatedKeys(scene_of(self));
    if (PagedChoice_MoveCursor(choice_of(self), (int) keys, &self->choice_row, 0) != 0) {
        PocketsView_GlideToRow(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & PAD_A) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(scene_of(self), SUB_PICK_ROW);
    } else if (pressed & PAD_B) {
        PocketsView_CancelChoice(self);
    }
}
CLEAN_AS(func_ov099_0229d49c, PocketsView_ActionChoiceByKeys)

/* func_ov099_0229d518 (sub state 5): an item is held and moves with the cursor. The d-pad moves
 * the cursor. A at a grid place puts it down there when empty, else swaps it with the item
 * there; B puts it back where it came from. Else it follows the cursor sprite and a queued
 * popup is shown. */
void PocketsView_MoveHeldItemByKeys(PocketsView *self)
{
    if (move_cursor_by_keys(self)) {
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & PAD_A) {
        if (PocketsView_IsGridPlace(self, self->cursor)) {
            if (PocketsView_PlaceIsEmpty(self, self->cursor)) {
                PocketsView_StartPutDown(self, self->cursor);
            } else {
                PocketsView_StartSwap(self, self->cursor);
            }
        }
    } else if (pressed & PAD_B) {
        PocketsView_StartPutDown(self, self->held_place);
    } else {
        PocketsView_FollowCursorSprite(self);
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov099_0229d518, PocketsView_MoveHeldItemByKeys)

/* func_ov099_0229d5c0 (sub state 4): the cursor waits for the keys. A touch hides the cursor
 * sprite and the popup (sub state 0). The d-pad moves the cursor. A on a grid place that holds
 * an item opens its choice. Y closes the scene (state 3 in phase 1, the popup and the cursor
 * sprite hidden); else a queued popup is shown.
 * QUIRK: A at a place the grid's object calls taken is not taken as A: Y is tested next. */
void PocketsView_IdleByKeys(PocketsView *self)
{
    if (MenuScene_TakeTouch(scene_of(self)) != 0) {
        PocketsView_EndActionHidden(self);
        Popup_Hide(&self->popup, 1);
        return;
    }
    if (move_cursor_by_keys(self)) {
        return;
    }
    if (PocketsView_PlaceIsTaken(self, self->cursor) == 0 && (data_021fbe40.pressed & PAD_A) != 0) {
        if (PocketsView_IsGridPlace(self, self->cursor) && PocketsView_PlaceIsEmpty(self, self->cursor) == 0) {
            PocketsView_OpenChoice(self, self->cursor);
        }
        return;
    }
    if (data_021fbe40.pressed & PAD_Y) {
        self->base.state = STATE_START_WIPE_OUT;
        MenuScene_SetPhase(scene_of(self), MENU_SCENE_PHASE_1);
        Popup_Hide(&self->popup, 1);
        PocketsView_HideCursorSprite(self);
    } else {
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov099_0229d5c0, PocketsView_IdleByKeys)

/* func_ov099_0229d698 (sub state 3): the held item follows the stylus; while the pen is down
 * only the grid place under the item's middle (8 pixels right and down of where it is drawn)
 * is marked. The pen lifted there puts the item down (an item there goes where the held one
 * came from) and ends the action; lifted elsewhere, the item glides back (sub state 0x10).
 * QUIRK: were the drop refused, the item would glide back and the action still end, replacing
 * the glide's sub state; the place found under the touch is always one of the grid. */
void PocketsView_DragHeldItem(PocketsView *self)
{
    PocketsView_FollowTouch(self);
    PocketsView_ClearHighlights(self);
    int x = (int) ((u32) self->held_x + 8);
    int y = (int) ((u32) self->held_y + 8);
    int place = PocketsView_GridPlaceAtTouch(self, x, y, 0);
    if (place == POCKETS_VIEW_NO_PLACE) {
        if (data_021fbdd8 == 0) {
            PocketsView_GlideHeldTo(self, self->held_place, 4);
        }
        return;
    }
    if (data_021fbdd8 != 0) {
        PocketsView_HighlightPlace(self, place);
        return;
    }
    if (PocketsView_DropHeldAt(self, place) == 0) {
        PocketsView_GlideHeldTo(self, self->held_place, 4);
    }
    PocketsView_EndAction(self);
}
CLEAN_AS(func_ov099_0229d698, PocketsView_DragHeldItem)

/* func_ov099_0229d718 (sub state 2): the choice by touch. A button cancels it; a touch on a row
 * (or below the rows: the last one) picks it. */
void PocketsView_ActionChoiceByTouch(PocketsView *self)
{
    if (MenuScene_TakeButtons(scene_of(self), 1) != 0) {
        PocketsView_CancelChoice(self);
        return;
    }
    if (!pen_pressed()) {
        return;
    }
    int row = PagedChoice_RowAtOrLast(choice_of(self), data_021f6c58, data_021f6c54);
    if (row >= 0) {
        pick_row(self, row);
    }
}
CLEAN_AS(func_ov099_0229d718, PocketsView_ActionChoiceByTouch)

/* func_ov099_0229d7a4 (sub state 1): the pen is on a touched place (PocketsView_TouchPlace).
 * Lifted: back to sub state 0 with the popup closing after 60 frames. Held, at a place with
 * POCKETS_VIEW_FLAG_04: dragged more than 8 pixels it picks the item up; once main's byte
 * data_021f6c30 reaches 9 the place's choice opens. Else a queued popup is shown. */
void PocketsView_HoldTouchOnPlace(PocketsView *self)
{
    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(scene_of(self), SUB_IDLE_BY_TOUCH);
        Popup_SetTimer(&self->popup, POPUP_FRAMES);
        return;
    }
    if (PocketsView_TestFlags(self, POCKETS_VIEW_FLAG_04) != 0) {
        if (PocketsView_TouchMoved(self) != 0) {
            PocketsView_PickUpWithTouch(self, self->touch_place);
            return;
        }
        if (PocketsView_Byte6c30AtLeast(self, OPEN_CHOICE_BYTE) != 0) {
            PocketsView_OpenChoice(self, self->touch_place);
            return;
        }
    }
    Popup_ShowQueued(&self->popup);
}
CLEAN_AS(func_ov099_0229d7a4, PocketsView_HoldTouchOnPlace)

/* func_ov099_0229d814 (sub state 0): the touch is in use and the cursor sprite hidden. A button
 * puts the cursor sprite back at the cursor (sub state 4). A touch on a grid place that holds
 * an item, or else on a letter's place that holds a letter, touches it (sub state 1). */
void PocketsView_IdleByTouch(PocketsView *self)
{
    if (MenuScene_TakeButtons(scene_of(self), 1) != 0) {
        PocketsView_EndActionAtCursor(self);
        return;
    }
    if (!pen_pressed()) {
        return;
    }
    int x = data_021f6c58;
    int y = data_021f6c54;
    int place = PocketsView_GridPlaceAtTouch(self, x, y, 1);
    if (place != POCKETS_VIEW_NO_PLACE) {
        PocketsView_TouchPlace(self, (u8) place);
        return;
    }
    place = PocketsView_LetterPlaceAtTouch(self, x, y, 1);
    if (place != POCKETS_VIEW_NO_PLACE) {
        PocketsView_TouchPlace(self, (u8) place);
    }
}
CLEAN_AS(func_ov099_0229d814, PocketsView_IdleByTouch)

/* func_ov099_0229d894: a step of the wallet display's setup; its answer. */
int PocketsView_StepWalletSetup(PocketsView *self)
{
    return func_ov094_0229a098(self->wallet);
}
CLEAN_AS(func_ov099_0229d894, PocketsView_StepWalletSetup)

/* func_ov099_0229d8a4: the wallet's display started with 0 and prepared. */
void PocketsView_PrepareWallet(PocketsView *self)
{
    func_ov094_0229a29c(self->wallet, 0);
}
CLEAN_AS(func_ov099_0229d8a4, PocketsView_PrepareWallet)

/* func_ov099_0229d8b8: layer 6 at priority 2, with its plain background settings. */
void PocketsView_SetUpLayer6(void)
{
    DisplayLayer_SetPriority(POCKETS_VIEW_LAYER, 2);
    DisplayLayer_SetBgControl(POCKETS_VIEW_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov099_0229d8b8, PocketsView_SetUpLayer6)

/* func_ov099_0229d8d8: the end of a frame: the choice and the wallet's display updated, and
 * the popup placed when its update asks for it. */
void PocketsView_EndFrame(PocketsView *self)
{
    PagedChoice_Update(choice_of(self));
    func_ov094_0229a05c(self->wallet);
    if (Popup_Update(&self->popup) != 0) {
        PocketsView_PlacePopup(self);
    }
}
CLEAN_AS(func_ov099_0229d8d8, PocketsView_EndFrame)

/* func_ov099_0229d910: the start of a frame: the object at 0x94 and the three objects of
 * ov094's updated. */
void PocketsView_BeginFrame(PocketsView *self)
{
    PocketsView_UpdateObject94(self);
    func_ov094_0229a084(self->wallet);
    func_ov094_0229af20(self->grid);
    func_ov094_0229bbc0(self->letters);
}
CLEAN_AS(func_ov099_0229d910, PocketsView_BeginFrame)

/* func_ov099_0229d940 */
void PocketsView_EndInteractiveFrame(PocketsView *self)
{
    PocketsView_EndFrame(self);
}
CLEAN_AS(func_ov099_0229d940, PocketsView_EndInteractiveFrame)

/* func_ov099_0229d948: the start of a frame, then the cursor sprite's update through its class
 * (vtable slot 3). */
void PocketsView_BeginInteractiveFrame(PocketsView *self)
{
    PocketsView_BeginFrame(self);
    update_cursor_sprite(self);
}
CLEAN_AS(func_ov099_0229d948, PocketsView_BeginInteractiveFrame)

/* func_ov099_0229d964: the members' teardown before the scene closes. */
void PocketsView_Teardown(PocketsView *self)
{
    PocketsView_UpdateObject94(self);
    func_ov094_0229a038(self->wallet);
    func_ov094_0229af18(self->grid);
    PagedChoice_Dismiss(choice_of(self));
}
CLEAN_AS(func_ov099_0229d964, PocketsView_Teardown)

/* func_ov099_0229d994: the scene's setup: no flags, the three objects of ov094's set up, no
 * popup place, the glide stopped, nothing held, the cursor at place 0, the choice on layer 3;
 * then item 0x11a9 stored in pocket slot 0 (in state 1) and item 0x1548 in slot 2. */
void PocketsView_Setup(PocketsView *self)
{
    self->flags = 0;
    func_ov094_0229af40(self->grid, 2);
    func_ov094_0229bbd8(self->letters, 2);
    func_ov094_0229a2b0(self->wallet, 6);
    self->popup_place = POCKETS_VIEW_NO_PLACE;
    Glide_Stop(&self->glide);
    self->held_kind = POCKETS_VIEW_HELD_NONE;
    self->cursor = POCKETS_VIEW_GRID_FIRST;
    PagedChoice_Init(choice_of(self), 3, 1, NULL);
    u16 first = 0x11a9;
    func_0209a088(&first, 1, 0);
    u16 second = 0x1548;
    func_0209a088(&second, 0, 2);
}
CLEAN_AS(func_ov099_0229d994, PocketsView_Setup)

/* func_ov099_0229da34 (state 4): the scene wipes out. When done, layer 6 hidden, the run phase
 * set and nothing drawn. The objects' offset follows the wipe. */
void PocketsView_WipeOut(PocketsView *self)
{
    if (MenuScene_StepWipe(scene_of(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(POCKETS_VIEW_LAYER);
        MenuScene_SetPhase(scene_of(self), MENU_SCENE_RUN);
        PocketsView_ClearFlags(self, POCKETS_VIEW_FLAG_DRAWN);
        PocketsView_ClearFlags(self, POCKETS_VIEW_FLAG_OBJECTS_DRAWN);
    } else {
        MenuScene_ScrollWipe(scene_of(self), POCKETS_VIEW_LAYER, 0, 0);
    }
    self->wipe_y = MenuScene_WipeOffsetY(scene_of(self));
}
CLEAN_AS(func_ov099_0229da34, PocketsView_WipeOut)

/* func_ov099_0229da84 (state 3): the popup and the cursor sprite hidden, the parent told the
 * scene ends (code 0x44), and the scene starts to wipe out (state 4). */
void PocketsView_StartWipeOut(PocketsView *self)
{
    Popup_Hide(&self->popup, 1);
    PocketsView_HideCursorSprite(self);
    func_ov092_02299324(parent_of(self), PARENT_CODE_END, 1);
    MenuScene_StartWipeOnWindow2(scene_of(self), WIPE_LAYERS, 0, 0, WIPE_MARGIN);
    MenuScene_ScrollWipe(scene_of(self), POCKETS_VIEW_LAYER, 0, 0);
    MenuScene_SetState(scene_of(self), STATE_WIPE_OUT);
    self->wipe_y = MenuScene_WipeOffsetY(scene_of(self));
}
CLEAN_AS(func_ov099_0229da84, PocketsView_StartWipeOut)

/* func_ov099_0229dae8 (state 2): the scene wipes in; when done, phase 2 and the action ends
 * (PocketsView_EndAction picks the first sub state). The objects' offset follows the wipe. */
void PocketsView_WipeIn(PocketsView *self)
{
    if (MenuScene_StepWipeBack(scene_of(self), 0) != 0) {
        MenuScene_SetPhase(scene_of(self), MENU_SCENE_PHASE_2);
        PocketsView_EndAction(self);
    }
    MenuScene_ScrollWipe(scene_of(self), POCKETS_VIEW_LAYER, 0, 0);
    self->wipe_y = MenuScene_WipeOffsetY(scene_of(self));
}
CLEAN_AS(func_ov099_0229dae8, PocketsView_WipeIn)

/* func_ov099_0229db24 (state 1): a step of the wallet display's setup (its answer unused), the
 * grid's and the letters' objects prepared, layer 6 shown and wiping in (state 2); the scene
 * and its objects drawn. */
void PocketsView_StartWipeIn(PocketsView *self)
{
    PocketsView_StepWalletSetup(self);
    func_ov094_0229ad20(self->grid);
    func_ov094_0229b2b0(self->letters);
    MenuScene_StartWipeCoveredOnWindow2(scene_of(self), WIPE_LAYERS, 0, 0, WIPE_MARGIN);
    DisplayLayer_Show(POCKETS_VIEW_LAYER);
    MenuScene_ScrollWipe(scene_of(self), POCKETS_VIEW_LAYER, 0, 0);
    MenuScene_SetState(scene_of(self), STATE_WIPE_IN);
    PocketsView_SetFlags(self, POCKETS_VIEW_FLAG_DRAWN);
    PocketsView_SetFlags(self, POCKETS_VIEW_FLAG_OBJECTS_DRAWN);
    self->wipe_y = MenuScene_WipeOffsetY(scene_of(self));
}
CLEAN_AS(func_ov099_0229db24, PocketsView_StartWipeIn)

/* func_ov099_0229db94 (state 0): layer 6 set up and the wallet's display prepared, then
 * state 1. */
void PocketsView_StartSetup(PocketsView *self)
{
    PocketsView_SetUpLayer6();
    PocketsView_PrepareWallet(self);
    MenuScene_SetState(scene_of(self), STATE_START_WIPE_IN);
}
CLEAN_AS(func_ov099_0229db94, PocketsView_StartSetup)

/* func_ov099_0229dbb0 (vtable slot 0x5c, phase 4): the scene asks to be deleted. */
int PocketsView_RequestDelete(PocketsView *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov099_0229dbb0, PocketsView_RequestDelete)

/* func_ov099_0229dbc0 (vtable slot 0x58, phase 1): nothing. */
int PocketsView_Phase1Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov099_0229dbc0, PocketsView_Phase1Idle)

/* func_ov099_0229dbc4 (vtable slot 0x54, phase 0): nothing. */
int PocketsView_Phase0Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov099_0229dbc4, PocketsView_Phase0Idle)

/* Obj_ov099_0229e040::func_ov099_0229dbc8 (vtable slot 0x50, phase 2): a frame of the scene in
 * use: its start, its sub state through the table of member functions (filled once from its
 * constants), its end. The sub states:
 *   0     PocketsView_IdleByTouch            0x0b  PocketsView_PickUpOnTurn
 *   1     PocketsView_HoldTouchOnPlace       0x0c  PocketsView_FinishPickUp
 *   2     PocketsView_ActionChoiceByTouch    0x0d  PocketsView_PutDownWithCursor
 *   3     PocketsView_DragHeldItem           0x0e  PocketsView_SwapWithCursor
 *   4     PocketsView_IdleByKeys             0x0f  PocketsView_FinishSwapWithCursor
 *   5     PocketsView_MoveHeldItemByKeys     0x10  PocketsView_StepHeldGlide
 *   6     PocketsView_ActionChoiceByKeys     0x11  PocketsView_WaitChoiceToPoint
 *   7     PocketsView_PickActionRow          0x12  PocketsView_CloseChoice
 *   8     PocketsView_WaitCursorGlide        0x13  PocketsView_RunActionWhenIdle
 *   9     PocketsView_WaitAnimToSubState10   0x14  PocketsView_WaitError
 *   0x0a  PocketsView_WaitCursorAnim
 * REQUIRES: the sub state is below 21; the game reads past the table for others. */
int PocketsView_RunInteractive(PocketsView *self)
{
    static const MemberPointer *const sub_states[SUB_STATE_COUNT] = {
        &data_ov099_0229dfa0, &data_ov099_0229dff8, &data_ov099_0229dff0, &data_ov099_0229dfe8, &data_ov099_0229dfe0,
        &data_ov099_0229dfd8, &data_ov099_0229dfd0, &data_ov099_0229df88, &data_ov099_0229dfc8, &data_ov099_0229dfb8,
        &data_ov099_0229dfb0, &data_ov099_0229e010, &data_ov099_0229df70, &data_ov099_0229df98, &data_ov099_0229df90,
        &data_ov099_0229df80, &data_ov099_0229e000, &data_ov099_0229df78, &data_ov099_0229dfa8, &data_ov099_0229df68,
        &data_ov099_0229e008,
    };
    MemberPointer *table = &data_ov099_0229e0a8[STATE_COUNT];
    PocketsView_BeginInteractiveFrame(self);
    MemberTable_InitOnce(&data_ov099_0229e0a0, table, sub_states, SUB_STATE_COUNT);
    MemberPointer_CallVoid(&table[self->base.sub_state], self);
    PocketsView_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov099_0229e04019func_ov099_0229dbc8Ev, PocketsView_RunInteractive)

/* Obj_ov099_0229e040::func_ov099_0229dd4c (vtable slot 0x4c, the run phase): a frame of the
 * scene's states, between the frame's start and end, through the table of member functions
 * (filled once from its constants): 0 PocketsView_StartSetup, 1 PocketsView_StartWipeIn,
 * 2 PocketsView_WipeIn, 3 PocketsView_StartWipeOut, 4 PocketsView_WipeOut.
 * REQUIRES: the state is below 5; the game reads past the table for others. */
int PocketsView_RunState(PocketsView *self)
{
    static const MemberPointer *const states[STATE_COUNT] = {
        &data_ov099_0229df60, &data_ov099_0229e030, &data_ov099_0229e028, &data_ov099_0229e020, &data_ov099_0229e018,
    };
    MemberPointer *table = data_ov099_0229e0a8;
    MemberTable_InitOnce(&data_ov099_0229e0a4, table, states, STATE_COUNT);
    PocketsView_BeginFrame(self);
    MemberPointer_CallVoid(&table[self->base.state], self);
    PocketsView_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov099_0229e04019func_ov099_0229dd4cEv, PocketsView_RunState)

/* func_ov099_0229ddec (vtable slot 0x24): the scene's draw: the choice; while the scene is
 * drawn, the popup (through its class, slot 2), the cursor sprite (with the keys in use), the
 * held item and the three objects of ov094's at the wipe's offset
 * (POCKETS_VIEW_FLAG_OBJECTS_DRAWN). Answers 1. */
int PocketsView_Draw(PocketsView *self)
{
    PagedChoice_Draw(choice_of(self));
    if (PocketsView_TestFlags(self, POCKETS_VIEW_FLAG_DRAWN) == 0) {
        return 1;
    }
    draw_member(&self->popup);
    if (func_0206fe54() != 0) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    PocketsView_DrawHeld(self);
    if (PocketsView_TestFlags(self, POCKETS_VIEW_FLAG_OBJECTS_DRAWN) != 0) {
        func_ov094_0229a850(self->grid, 0, self->wipe_y);
        func_ov094_0229b738(self->letters, 0, self->wipe_y);
        func_ov094_02299d84(self->wallet, self->wipe_y);
    }
    return 1;
}
CLEAN_AS(func_ov099_0229ddec, PocketsView_Draw)

/* func_ov099_0229de7c (vtable slot 0x0c): the scene closes: the parent told and the members
 * torn down. Answers 1. */
int PocketsView_Close(PocketsView *self)
{
    func_ov092_0229929c(parent_of(self));
    PocketsView_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov099_0229de7c, PocketsView_Close)

/* func_ov099_0229de98 (vtable slot 0x00): the scene starts: its setup, state 0 and phase 0.
 * Answers 1. */
int PocketsView_Start(PocketsView *self)
{
    PocketsView_Setup(self);
    MenuScene_SetState(scene_of(self), STATE_START_SETUP);
    MenuScene_SetPhase(scene_of(self), MENU_SCENE_PHASE_0);
    return 1;
}
CLEAN_AS(func_ov099_0229de98, PocketsView_Start)

/* func_ov099_0229deb8: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base, the scene's vtable and its members constructed. */
PocketsView *PocketsView_New(void)
{
    PocketsView *self = MenuScene_Alloc(sizeof(PocketsView));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov099_0229e040;
    func_020b9af4(self->unk_94);
    func_ov094_0229b000(self->grid);
    func_ov094_0229bc3c(self->letters);
    func_ov094_0229a2ec(self->wallet);
    Popup_Construct(&self->popup);
    Glide_Construct(&self->glide);
    Glider0_Construct(&self->cursor_sprite);
    PagedChoice_Construct(choice_of(self));
    ErrorMessage_Construct(&self->error);
    func_02066694(self->letter);
    return self;
}
CLEAN_AS(func_ov099_0229deb8, PocketsView_New)
