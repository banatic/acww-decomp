/* Overlay 099's scene (pockets_view.h). */
#include "pockets_view.h"

#include "clean.h"
#include "ov002/key_repeat.h"

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

/* The scene's own, outside these functions: the end of an action (by touch or by keys, as state
 * flag 2 says). Its matching source takes the scene as an int. */
extern void func_ov099_0229d0f0(int self);

/* What the grid's and the letters' objects answer for no place under the touch. */
#define GRID_NO_INDEX 0x23
#define LETTERS_NO_INDEX 0x37

/* The answers for a place outside the grid (PocketsView_PlaceItem, PocketsView_PlaceItemState). */
#define NO_ITEM 0xfff1
#define NO_ITEM_STATE 0xf1

/* The scene's sub states (MenuScene_SetSubState; the table of func_ov099_0229dbc8). */
#define SUB_HOLD_BY_TOUCH 0x03  /* func_ov099_0229d698: the held item follows the stylus */
#define SUB_HOLD_BY_KEYS 0x05   /* func_ov099_0229d518: the held item follows the cursor */
#define SUB_WAIT_SPRITE 0x08    /* func_ov099_0229d400: back to `return_state` after the move */
#define SUB_10 0x0a             /* func_ov099_0229d3b8 */
#define SUB_PICK_UP 0x0b        /* func_ov099_0229d388: PocketsView_PickUpWithCursor */
#define SUB_PUT_DOWN 0x0d       /* func_ov099_0229d304 */
#define SUB_SWAP 0x0e           /* func_ov099_0229d2bc: PocketsView_SwapHeldWith */
#define SUB_HELD_GLIDE 0x10     /* func_ov099_0229d240: the held item glides back */
#define SUB_CHOICE_OPENING 0x11 /* func_ov099_0229d204 */
#define SUB_CHOICE_CLOSING 0x13 /* func_ov099_0229d1a0: then PocketsView_RunAction */

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
        func_ov099_0229d0f0((int) (uintptr_t) self);
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
