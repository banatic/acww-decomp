/* Overlay 101's scene (pockets_pick.h): its destructors and flags, the cursor's moves, the
 * choice, the held item and the places, the sub states and states it runs each frame, its draw,
 * its setup and its construction. */
#include "pockets_pick.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/group_params.h"
#include "main/sliding_window.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"
#include "ov094/pockets_common.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(PocketsPick, flags) == 0x94, "flags");
static_assert(offsetof(PocketsPick, grab_dx) == 0x9c && offsetof(PocketsPick, held_x) == 0xa4, "places");
static_assert(offsetof(PocketsPick, item) == 0xac && offsetof(PocketsPick, held_kind) == 0xaf, "held");
static_assert(offsetof(PocketsPick, cursor) == 0xb3 && offsetof(PocketsPick, open_delay) == 0xb9, "bytes");
static_assert(offsetof(PocketsPick, layer_task) == 0xbc && offsetof(PocketsPick, grid) == 0xf4, "grid");
static_assert(offsetof(PocketsPick, letters) == 0xb54 && offsetof(PocketsPick, wallet) == 0xb7c, "ov094 objects");
static_assert(offsetof(PocketsPick, popup) == 0x21b4 && offsetof(PocketsPick, glide) == 0x2284, "popup");
static_assert(offsetof(PocketsPick, cursor_sprite) == 0x229c && offsetof(PocketsPick, choice) == 0x2300, "sprite");
static_assert(offsetof(PocketsPick, entries) == 0x26e8 && offsetof(PocketsPick, error) == 0x26f4, "choice");
static_assert(offsetof(PocketsPick, panel) == 0x2810 && sizeof(PocketsPick) == 0x29dc, "size (func_ov101_0229ded0)");

/* The scene's vtable. */
extern const u8 data_ov101_0229e078[];

/* The touch (main's bytes, as ov099/pockets_view.c reads them). */
extern u8 data_021f6c58, data_021f6c54;

/* The pen (autoload_2/input.c): down, and gone down or up this frame. */
extern u8 data_021fbdd8;
extern u8 data_021fbddc;

/* The pad (autoload_2/input.h): the buttons pressed this frame. */
extern PadState data_021fbe40;
#define PICK_PAD_A 0x0001
#define PICK_PAD_B 0x0002

/* The tables of member functions (ov004/member_pointer.h): their guards, the tables and the
 * constants they are filled from. The symbol table splits the sub states' table at its 17th
 * entry (data_ov101_0229e190); it is one table of 24. */
extern u32 data_ov101_0229e0e0; /* the states' guard */
extern u32 data_ov101_0229e0e4; /* the sub states' guard */
extern MemberPointer data_ov101_0229e0e8[PICK_STATES];
extern MemberPointer data_ov101_0229e110[PICK_SUB_STATES];
extern const MemberPointer data_ov101_0229df80, data_ov101_0229df88, data_ov101_0229df90, data_ov101_0229dfa0,
    data_ov101_0229dfa8, data_ov101_0229dfb0, data_ov101_0229dfb8, data_ov101_0229dfc0, data_ov101_0229dfc8,
    data_ov101_0229dfd0, data_ov101_0229dfd8, data_ov101_0229dfe0, data_ov101_0229dfe8, data_ov101_0229dff0,
    data_ov101_0229dff8, data_ov101_0229e000, data_ov101_0229e008, data_ov101_0229e010, data_ov101_0229e018,
    data_ov101_0229e020, data_ov101_0229e028, data_ov101_0229e030, data_ov101_0229e038, data_ov101_0229e040,
    data_ov101_0229e048, data_ov101_0229e050, data_ov101_0229e058, data_ov101_0229e060, data_ov101_0229e068;

/* The menu scene's phases this scene sets (MenuScene_Update runs phase n by vtable slot
 * 0x48 + 4 * n, as ov092/menu_dispatch.h says). */
#define PICK_PHASE_0 0           /* slot 0x48 */
#define PICK_PHASE_STATES 1      /* slot 0x4c: PocketsPick_RunState */
#define PICK_PHASE_INTERACTIVE 2 /* slot 0x50: PocketsPick_RunInteractive */
#define PICK_PHASE_DELETE 5      /* slot 0x5c: PocketsPick_RequestDelete */

/* The scene's 2D layer, and its wipe on window 2; the panel and the objects are drawn 16 pixels
 * above the wipe's offset, and the touch is moved 16 pixels down to find a slot. */
#define PICK_LAYER 6
#define PICK_WIPE_LAYERS 8
#define PICK_WIPE_MARGIN 0x30
#define PICK_SCROLL_Y (-16)
#define PICK_GRID_RAISE 0x10

/* What the parent (ov092's dispatcher) is told when the scene ends. */
#define PICK_PARENT_CODE_END 0x44

/* The button panel's layout message and its close button. */
#define PICK_PANEL_MESSAGE 0x65
#define PICK_PANEL_CLOSE 9

/* The sounds: the close button pressed. */
#define PICK_SOUND_CLOSE 0x28

/* The choice's second row, its text (the first row's is GroupParams_MaskArg). */
#define PICK_ROW_CANCEL_TEXT 2

/* The cursor sprite's animations beyond glide.h's names. */
#define PICK_ANIM_HIDDEN 0
#define PICK_ANIM_POINT 1
#define PICK_ANIM_PUT_DOWN 5
#define PICK_ANIM_SWAP 6
#define PICK_ANIM_ROW 7
#define PICK_ANIM_LAST_ROW 8

/* The answers for a place outside the grid. */
#define PICK_NO_ITEM 0xfff1
#define PICK_NO_ITEM_STATE 0xf1
#define PICK_CLOSE_X 0xbc
#define PICK_CLOSE_Y 0xb6

/* What the grid's object answers for no slot under the touch. */
#define PICK_GRID_NO_INDEX 0x23

/* The popup's place left of and above the place it tells of (8 pixels higher with state flag 2),
 * and the frames it stays after the pen leaves a dimmed place. */
#define PICK_POPUP_DX 0x6d
#define PICK_POPUP_DY 0x78
#define PICK_POPUP_KEYS_DY 8
#define PICK_POPUP_FRAMES 0x3c

/* The frames a touched place waits before its choice opens. */
#define PICK_OPEN_DELAY 2

static MenuScene *pick_scene(PocketsPick *self)
{
    return &self->base;
}

static PagedChoice *pick_choice(PocketsPick *self)
{
    return (PagedChoice *) (void *) self->choice;
}

static CellLayerSprite *pick_sprite_cells(PocketsPick *self)
{
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

static Process *pick_parent(PocketsPick *self)
{
    return Process_GetParent((Process *) (void *) self);
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void pick_update_cursor_sprite(PocketsPick *self)
{
    Glider *sprite = &self->cursor_sprite;
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* Calls the draw (vtable slot 2) of a member object through its own vtable, as the game does. */
static void pick_draw_member(void *object)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[2])(object);
}

/* The pen went down this frame. */
static int pick_pen_pressed(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* The value kept with choice row `row`. The game reads the byte `row` places after the values'
 * start whatever the row; read the same way here, within the scene. */
static u8 pick_row_value(PocketsPick *self, int row)
{
    const u8 *values = (const u8 *) self + offsetof(PocketsPick, entries) + offsetof(ChoiceEntries, values);
    return values[row];
}

/* Choice row `row` picked (with sound 1): its value kept as `action`, and the choice closes. */
static void pick_row(PocketsPick *self, int row)
{
    PagedChoice_PickRowWithSound(pick_choice(self), row, 1);
    self->action = pick_row_value(self, row);
    MenuScene_SetSubState(pick_scene(self), PICK_SUB_CHOICE_CLOSE);
}

/* The panel's close button pressed: sub state 0x17 follows its press. */
static void pick_press_close_button(PocketsPick *self)
{
    ButtonPanel_Select(&self->panel, PICK_PANEL_CLOSE);
    MenuScene_SetSubState(pick_scene(self), PICK_SUB_CLOSE_PRESSED);
    SoundSys_PlaySe(PICK_SOUND_CLOSE);
}

/* The repeated keys move the cursor: the popup told of the new place, the cursor sprite
 * following and the popup hidden. Whether they did. */
static int pick_move_cursor_by_keys(PocketsPick *self)
{
    u32 keys = MenuScene_LatchRepeatedKeys(pick_scene(self));
    if (PocketsPick_MoveCursor(self, (int) keys) == 0) {
        return 0;
    }
    PocketsPick_UpdatePopup(self);
    PocketsPick_GlideToCursor(self);
    Popup_Hide(&self->popup, 0);
    return 1;
}

/* The scene closes: the menu scene's state set to `state` (directly, not by MenuScene_SetState)
 * in the states' phase, the popup and the cursor sprite hidden. */
static void pick_close_scene(PocketsPick *self)
{
    self->base.state = PICK_STATE_START_WIPE_OUT;
    MenuScene_SetPhase(pick_scene(self), PICK_PHASE_STATES);
    Popup_Hide(&self->popup, 1);
    PocketsPick_HideCursorSprite(self);
}

/* The members' destructors, last member first, then the base's. */
static void pick_destroy_members(PocketsPick *self)
{
    self->base.vtable = data_ov101_0229e078;
    ButtonPanel_Destroy(&self->panel);
    ErrorMessage_Destruct(&self->error);
    PagedChoice_Destroy(pick_choice(self));
    Glider0_Destroy(&self->cursor_sprite);
    Glide_Destroy(&self->glide);
    Popup_Destroy(&self->popup);
    PocketsWallet_Destruct(&self->wallet);
    PocketsLetters_Destruct(&self->letters);
    PocketsGrid_Destruct(&self->grid);
    MenuScene_DestroyBase(pick_scene(self));
}

/* func_ov101_0229c180 (vtable slot 0x40) */
PocketsPick *PocketsPick_Destroy(PocketsPick *self)
{
    pick_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov101_0229c180, PocketsPick_Destroy)

/* func_ov101_0229c204 (vtable slot 0x44) */
PocketsPick *PocketsPick_Delete(PocketsPick *self)
{
    pick_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov101_0229c204, PocketsPick_Delete)

/* func_ov101_0229c28c */
void PocketsPick_ClearFlags(PocketsPick *self, unsigned int flags)
{
    self->flags &= ~flags;
}
CLEAN_AS(func_ov101_0229c28c, PocketsPick_ClearFlags)

/* func_ov101_0229c29c */
void PocketsPick_SetFlags(PocketsPick *self, int flags)
{
    self->flags |= (u32) flags;
}
CLEAN_AS(func_ov101_0229c29c, PocketsPick_SetFlags)

/* func_ov101_0229c2ac: 1 when any of `flags` is set. */
int PocketsPick_TestFlags(PocketsPick *self, int flags)
{
    return (self->flags & (u32) flags) != 0;
}
CLEAN_AS(func_ov101_0229c2ac, PocketsPick_TestFlags)

/* func_ov101_0229c2c0: the cursor moved by `keys` (KeyRepeat_Has*), the wrap flags of the last
 * move cleared first: in the grid by PocketsPick_MoveCursorInGrid; up from the close button goes
 * to the grid's last slot (14), the cursor sprite turning to set A. 1 when the cursor changed
 * place; 0 at once when `keys` is 0. */
int PocketsPick_MoveCursor(PocketsPick *self, int keys)
{
    u8 before = self->cursor;

    PocketsPick_ClearFlags(self, PICK_FLAGS_WRAPPED);
    if (keys == 0) {
        return 0;
    }
    if (PocketsPick_IsGridPlace(self, self->cursor) != 0) {
        PocketsPick_MoveCursorInGrid(self, keys);
    } else if (self->cursor == PICK_PLACE_CLOSE && KeyRepeat_HasUp(keys) != 0) {
        self->cursor = PICK_PLACE_GRID_LAST;
        Glider_TurnToSetA(&self->cursor_sprite);
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov101_0229c2c0, PocketsPick_MoveCursor)

/* func_ov101_0229c330: the cursor moved in the grid (3 rows of 5). Left and right move one
 * column, wrapping to the other end of the row (and saying so in the flags); unless the move
 * wrapped, up and down then move one row (by the row the cursor started on), up stopping at the
 * first and down from the last going to the close button, the cursor sprite turning to set B.
 * QUIRK: left is ignored when up is held too and the cursor is below the first row; right is
 * ignored whenever down is held too. */
void PocketsPick_MoveCursorInGrid(PocketsPick *self, int keys)
{
    int column = self->cursor % PICK_GRID_COLUMNS;
    int row = self->cursor / PICK_GRID_COLUMNS;

    if (KeyRepeat_HasLeft(keys) != 0) {
        if (!(KeyRepeat_HasUp(keys) != 0 && row != 0)) {
            if (column == 0) {
                self->cursor += PICK_GRID_COLUMNS - 1;
                PocketsPick_SetFlags(self, PICK_FLAG_WRAPPED_LEFT);
            } else {
                self->cursor--;
            }
        }
    } else if (KeyRepeat_HasRight(keys) != 0 && KeyRepeat_HasDown(keys) == 0) {
        if (column == PICK_GRID_COLUMNS - 1) {
            self->cursor -= PICK_GRID_COLUMNS - 1;
            PocketsPick_SetFlags(self, PICK_FLAG_WRAPPED_RIGHT);
        } else {
            self->cursor++;
        }
    }

    if (PocketsPick_TestFlags(self, PICK_FLAGS_WRAPPED) != 0) {
        return;
    }
    if (KeyRepeat_HasUp(keys) != 0) {
        if (row > 0) {
            self->cursor -= PICK_GRID_COLUMNS;
        }
    } else if (KeyRepeat_HasDown(keys) != 0) {
        if (row < PICK_GRID_ROWS - 1) {
            self->cursor += PICK_GRID_COLUMNS;
        } else {
            self->cursor = PICK_PLACE_CLOSE;
            Glider_TurnToSetB(&self->cursor_sprite);
        }
    }
}
CLEAN_AS(func_ov101_0229c330, PocketsPick_MoveCursorInGrid)

/* func_ov101_0229c42c: the choice of the slot at `place`, its entries cleared first (cancel by
 * default); for a grid place its two rows, the cursor sprite hidden, the popup too unless the
 * choice goes above it, and the choice shown. */
void PocketsPick_OpenChoice(PocketsPick *self, int place, int above_popup)
{
    self->slot = (u8) place;
    ChoiceEntries_Clear(&self->entries, PICK_ACTION_CANCEL);
    if (PocketsPick_IsGridPlace(self, (unsigned int) place) == 0) {
        return;
    }
    PocketsPick_AddEntries(self);
    PocketsPick_HideCursorSprite(self);
    if (above_popup == 0) {
        Popup_Hide(&self->popup, 1);
    }
    PocketsPick_ShowChoice(self, above_popup);
}
CLEAN_AS(func_ov101_0229c42c, PocketsPick_OpenChoice)

/* func_ov101_0229c480: the choice's rows: the text the scene was opened with
 * (GroupParams_MaskArg) picks the slot, text 2 cancels. */
void PocketsPick_AddEntries(PocketsPick *self)
{
    ChoiceEntries_Add(&self->entries, GroupParams_MaskArg(), PICK_ACTION_CHOOSE);
    ChoiceEntries_Add(&self->entries, PICK_ROW_CANCEL_TEXT, PICK_ACTION_CANCEL);
}
CLEAN_AS(func_ov101_0229c480, PocketsPick_AddEntries)

/* func_ov101_0229c4ac: the scene closes with nothing picked (GroupParams' byte 0xc4c 0). */
void PocketsPick_Cancel(PocketsPick *self)
{
    GroupParams_SetC4C(0);
    pick_close_scene(self);
}
CLEAN_AS(func_ov101_0229c4ac, PocketsPick_Cancel)

/* func_ov101_0229c4e0 (action 0): the slot whose choice is open is picked: kept as GroupParams'
 * argument, GroupParams' byte 0xc4c 1, and the scene closes. */
void PocketsPick_Choose(PocketsPick *self)
{
    GroupParams_SetArg(self->slot);
    GroupParams_SetC4C(1);
    pick_close_scene(self);
}
CLEAN_AS(func_ov101_0229c4e0, PocketsPick_Choose)

/* func_ov101_0229c51c: the cancel action, the cursor sprite put back at the cursor, the choice
 * asked to close, sub state 0x15. */
void PocketsPick_CancelChoice(PocketsPick *self)
{
    self->action = PICK_ACTION_CANCEL;
    PocketsPick_PlaceCursorSprite(self);
    PagedChoice_RequestClose(pick_choice(self), 0);
    MenuScene_SetSubState(pick_scene(self), PICK_SUB_CHOICE_CLOSING);
}
CLEAN_AS(func_ov101_0229c51c, PocketsPick_CancelChoice)

/* func_ov101_0229c548: the entries shown in the choice, placed above the popup or beside the
 * open place, asked to open; sub state 0x13. */
void PocketsPick_ShowChoice(PocketsPick *self, int above_popup)
{
    PagedChoice_ShowEntries(pick_choice(self), &self->entries, 0);
    int x = PocketsPick_PlaceX(self, self->slot);
    int y = PocketsPick_PlaceY(self, self->slot);
    if (above_popup != 0) {
        PagedChoice_PlaceAboveWindow(pick_choice(self), &self->popup);
    } else {
        PagedChoice_PlaceBeside(pick_choice(self), x, y);
    }
    PagedChoice_RequestOpen(pick_choice(self), 0);
    MenuScene_SetSubState(pick_scene(self), PICK_SUB_CHOICE_OPENING);
}
CLEAN_AS(func_ov101_0229c548, PocketsPick_ShowChoice)

/* func_ov101_0229c5b8: the action picked (`action`); any value but 0 ends the action. */
void PocketsPick_RunAction(PocketsPick *self)
{
    if (self->action == PICK_ACTION_CHOOSE) {
        PocketsPick_Choose(self);
    } else {
        PocketsPick_EndAction(self);
    }
}
CLEAN_AS(func_ov101_0229c5b8, PocketsPick_RunAction)

/* func_ov101_0229c5dc: a swap at `place` starts: the popup hidden, the sub state to go back to
 * kept, the cursor sprite's swap animation, sub state 0x10. */
void PocketsPick_StartSwap(PocketsPick *self, u8 place)
{
    Popup_Hide(&self->popup, 1);
    self->return_state = self->base.sub_state;
    self->target = place;
    Glider_SetAnim(&self->cursor_sprite, PICK_ANIM_SWAP);
    MenuScene_SetSubState(pick_scene(self), PICK_SUB_SWAP);
}
CLEAN_AS(func_ov101_0229c5dc, PocketsPick_StartSwap)

/* func_ov101_0229c624: the held item is to be put down at `place`: the popup hidden, the cursor
 * sprite's put-down animation, sub state 0x0f. */
void PocketsPick_StartPutDown(PocketsPick *self, u8 place)
{
    Popup_Hide(&self->popup, 1);
    self->target = place;
    Glider_SetAnim(&self->cursor_sprite, PICK_ANIM_PUT_DOWN);
    MenuScene_SetSubState(pick_scene(self), PICK_SUB_PUT_DOWN);
}
CLEAN_AS(func_ov101_0229c624, PocketsPick_StartPutDown)

/* func_ov101_0229c660: A on the close button: the cursor sprite's press (the second of its set),
 * then sub state 0x0b presses the button. */
void PocketsPick_PressClose(PocketsPick *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(pick_scene(self), PICK_SUB_PRESS_CLOSE);
}
CLEAN_AS(func_ov101_0229c660, PocketsPick_PressClose)

/* func_ov101_0229c680: the first animation of the cursor sprite's set, then its update. */
void PocketsPick_ShowCursorFirstOfSet(PocketsPick *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    pick_update_cursor_sprite(self);
}
CLEAN_AS(func_ov101_0229c680, PocketsPick_ShowCursorFirstOfSet)

/* func_ov101_0229c6a0: the cursor sprite put at the cursor, pointing. */
void PocketsPick_PlaceCursorSprite(PocketsPick *self)
{
    int x = PocketsPick_CursorSpriteX(self);
    int y = PocketsPick_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, PICK_ANIM_POINT);
}
CLEAN_AS(func_ov101_0229c6a0, PocketsPick_PlaceCursorSprite)

/* func_ov101_0229c6d4: the cursor sprite put at the choice's first row. */
void PocketsPick_PointAtFirstRow(PocketsPick *self)
{
    self->choice_row = 0;
    int x = PagedChoice_TextX(pick_choice(self));
    int y = PagedChoice_RowY(pick_choice(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, PICK_ANIM_ROW);
}
CLEAN_AS(func_ov101_0229c6d4, PocketsPick_PointAtFirstRow)

/* func_ov101_0229c720 (B in the choice): the cancel action, the choice's last row picked and the
 * cursor sprite put at it, showing animation 8 from its last frame; sub state 0x14 closes the
 * choice. */
void PocketsPick_PointAtLastRow(PocketsPick *self)
{
    self->action = PICK_ACTION_CANCEL;
    self->choice_row = PagedChoice_PickLastRow(pick_choice(self), 1);
    int x = PagedChoice_TextX(pick_choice(self));
    int y = PagedChoice_RowY(pick_choice(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    CellLayerSprite_SetAnimAtEnd(pick_sprite_cells(self), PICK_ANIM_LAST_ROW);
    MenuScene_SetSubState(pick_scene(self), PICK_SUB_CHOICE_CLOSE);
}
CLEAN_AS(func_ov101_0229c720, PocketsPick_PointAtLastRow)

/* func_ov101_0229c780: the cursor sprite moved to the choice row in 2 steps; the sub state to go
 * back to kept, sub state 0x0a. */
void PocketsPick_GlideToRow(PocketsPick *self)
{
    int x = PagedChoice_TextX(pick_choice(self));
    int y = PagedChoice_RowY(pick_choice(self), self->choice_row);
    Glider_MoveTo(&self->cursor_sprite, x, y, 2);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(pick_scene(self), PICK_SUB_WAIT_SPRITE);
}
CLEAN_AS(func_ov101_0229c780, PocketsPick_GlideToRow)

/* func_ov101_0229c7d0: the cursor sprite put at the cursor at once when PICK_FLAG_JUMP is set
 * (which this clears), else eased there in 3 steps, the sub state to go back to kept and sub
 * state 0x0a. */
void PocketsPick_GlideToCursor(PocketsPick *self)
{
    if (PocketsPick_TestFlags(self, PICK_FLAG_JUMP) != 0) {
        int x = PocketsPick_CursorSpriteX(self);
        int y = PocketsPick_CursorSpriteY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
        PocketsPick_ClearFlags(self, PICK_FLAG_JUMP);
    } else {
        int x = PocketsPick_CursorSpriteX(self);
        int y = PocketsPick_CursorSpriteY(self);
        Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
        self->return_state = self->base.sub_state;
        MenuScene_SetSubState(pick_scene(self), PICK_SUB_WAIT_SPRITE);
    }
}
CLEAN_AS(func_ov101_0229c7d0, PocketsPick_GlideToCursor)

/* func_ov101_0229c844: the cursor sprite's animation 0, then its update. */
void PocketsPick_HideCursorSprite(PocketsPick *self)
{
    Glider_SetAnim(&self->cursor_sprite, PICK_ANIM_HIDDEN);
    pick_update_cursor_sprite(self);
}
CLEAN_AS(func_ov101_0229c844, PocketsPick_HideCursorSprite)

/* func_ov101_0229c868: the cursor sprite's y, the cursor's place's. */
int PocketsPick_CursorSpriteY(PocketsPick *self)
{
    return PocketsPick_PlaceY(self, self->cursor);
}
CLEAN_AS(func_ov101_0229c868, PocketsPick_CursorSpriteY)

/* func_ov101_0229c878: the cursor sprite's x, the cursor's place's plus 8; a screen width (256)
 * further right when this move wrapped right, further left when it wrapped left, so the sprite
 * goes on over the edge. */
int PocketsPick_CursorSpriteX(PocketsPick *self)
{
    int x = PocketsPick_PlaceX(self, self->cursor);
    if (PocketsPick_TestFlags(self, PICK_FLAG_WRAPPED_RIGHT) != 0) {
        x += 0x100;
    } else if (PocketsPick_TestFlags(self, PICK_FLAG_WRAPPED_LEFT) != 0) {
        x -= 0x100;
    }
    return x + 8;
}
CLEAN_AS(func_ov101_0229c878, PocketsPick_CursorSpriteX)

/* func_ov101_0229c8bc: the cursor sprite put at the cursor, animation 7 on the close button and
 * 1 elsewhere, then its set's first animation shown. */
void PocketsPick_ShowCursorSprite(PocketsPick *self)
{
    int x = PocketsPick_CursorSpriteX(self);
    int y = PocketsPick_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (self->cursor == PICK_PLACE_CLOSE) {
        Glider_SetAnim(&self->cursor_sprite, PICK_ANIM_ROW);
    } else {
        Glider_SetAnim(&self->cursor_sprite, PICK_ANIM_POINT);
    }
    PocketsPick_ShowCursorFirstOfSet(self);
}
CLEAN_AS(func_ov101_0229c8bc, PocketsPick_ShowCursorSprite)

/* func_ov101_0229c90c: when an item is held, it changes places with the item at `place`: the
 * place's item picked up and the one held before set at `place`. */
void PocketsPick_SwapHeldWith(PocketsPick *self, int place)
{
    if (self->held_kind == PICK_HELD_ITEM) {
        u16 item = self->item;
        u8 state = self->held_state;
        PocketsPick_PickUpItem(self, place);
        PocketsPick_SetSlotItem(self, place, item, state);
    }
}
CLEAN_AS(func_ov101_0229c90c, PocketsPick_SwapHeldWith)

/* func_ov101_0229c944: the held item, if any, set at `place`; nothing held after. */
void PocketsPick_PutHeldAt(PocketsPick *self, int place)
{
    if (self->held_kind == PICK_HELD_ITEM) {
        PocketsPick_SetSlotItem(self, place, self->item, self->held_state);
    }
    self->held_kind = PICK_HELD_NONE;
}
CLEAN_AS(func_ov101_0229c944, PocketsPick_PutHeldAt)

/* func_ov101_0229c970: the item of the grid place `place` (other places are left alone) held:
 * its code and state kept, the slot emptied and the grid's held icon set to it. */
void PocketsPick_PickUpItem(PocketsPick *self, int place)
{
    if (PocketsPick_IsGridPlace(self, (unsigned int) place) == 0) {
        return;
    }
    int index = PocketsPick_GridIndex(self, place);
    self->held_kind = PICK_HELD_ITEM;
    self->item = PocketsGrid_Item(&self->grid, index);
    self->held_state = PocketsGrid_ItemState(&self->grid, index);
    PocketsGrid_EmptyPlace(&self->grid, index);
    PocketsGrid_SetHeldIcon(&self->grid, self->item, self->held_state);
}
CLEAN_AS(func_ov101_0229c970, PocketsPick_PickUpItem)

/* func_ov101_0229c9d8: the held item is where the glide is. */
void PocketsPick_FollowGlide(PocketsPick *self)
{
    self->held_x = Glide_X(&self->glide);
    self->held_y = Glide_Y(&self->glide);
}
CLEAN_AS(func_ov101_0229c9d8, PocketsPick_FollowGlide)

/* func_ov101_0229ca00: the held item is at the cursor sprite's frame, 2 left and 4 up. */
void PocketsPick_FollowCursorSprite(PocketsPick *self)
{
    self->held_x = Glider_FrameX(&self->cursor_sprite) - 2;
    self->held_y = Glider_FrameY(&self->cursor_sprite) - 4;
}
CLEAN_AS(func_ov101_0229ca00, PocketsPick_FollowCursorSprite)

/* func_ov101_0229ca2c: the held item is at the touch plus the grab's offset. */
void PocketsPick_FollowTouch(PocketsPick *self)
{
    self->held_x = (s32) ((u32) self->grab_dx + data_021f6c58);
    self->held_y = (s32) ((u32) self->grab_dy + data_021f6c54);
}
CLEAN_AS(func_ov101_0229ca2c, PocketsPick_FollowTouch)

/* func_ov101_0229ca58: the popup told of the cursor's place: queued for a grid slot with an item
 * (which becomes `popup_place`), its queue cleared for an empty slot or the close button. */
void PocketsPick_UpdatePopup(PocketsPick *self)
{
    if (PocketsPick_IsGridPlace(self, self->cursor) != 0 && PocketsPick_PlaceIsEmpty(self, self->cursor) == 0) {
        self->popup_place = self->cursor;
        Popup_Queue(&self->popup);
    } else {
        Popup_ClearQueued(&self->popup);
    }
}
CLEAN_AS(func_ov101_0229ca58, PocketsPick_UpdatePopup)

/* func_ov101_0229caac: the popup placed left of and above `popup_place` (8 pixels higher with
 * state flag 2) and, for a grid place, given the text of its item. */
void PocketsPick_PlacePopup(PocketsPick *self)
{
    int x = PocketsPick_PlaceX(self, self->popup_place) - PICK_POPUP_DX;
    int y = PocketsPick_PlaceY(self, self->popup_place) - PICK_POPUP_DY;
    if (StateFlags_Test2() != 0) {
        y -= PICK_POPUP_KEYS_DY;
    }
    SlidingWindow_SetPlace((SlidingWindow *) (void *) &self->popup, x, y);
    if (PocketsPick_IsGridPlace(self, self->popup_place) != 0) {
        int index = PocketsPick_GridIndex(self, self->popup_place);
        PocketsGrid_ShowItemText(&self->grid, &self->popup, index);
    }
}
CLEAN_AS(func_ov101_0229caac, PocketsPick_PlacePopup)

/* func_ov101_0229cb18: the grid place `place` marked (where a dragged item would land). */
void PocketsPick_MarkPlace(PocketsPick *self, int place)
{
    if (PocketsPick_IsGridPlace(self, (unsigned int) place) != 0) {
        PocketsGrid_MarkPlace(&self->grid, PocketsPick_GridIndex(self, place));
    }
}
CLEAN_AS(func_ov101_0229cb18, PocketsPick_MarkPlace)

/* func_ov101_0229cb44: no place marked in the grid or the letters. */
void PocketsPick_ClearMarks(PocketsPick *self)
{
    PocketsGrid_ClearMarks(&self->grid);
    PocketsLetters_ClearMarks(&self->letters);
}
CLEAN_AS(func_ov101_0229cb44, PocketsPick_ClearMarks)

/* func_ov101_0229cb60: the grid place `place` lifted (the letters' lift dropped); any other place
 * clears the selection. */
void PocketsPick_SelectPlace(PocketsPick *self, int place)
{
    if (PocketsPick_IsGridPlace(self, (unsigned int) place) != 0) {
        PocketsGrid_Lift(&self->grid, PocketsPick_GridIndex(self, place));
        PocketsLetters_Unlift(&self->letters);
    } else {
        PocketsPick_ClearSelection(self);
    }
}
CLEAN_AS(func_ov101_0229cb60, PocketsPick_SelectPlace)

/* func_ov101_0229cba0: nothing lifted in the grid or the letters. */
void PocketsPick_ClearSelection(PocketsPick *self)
{
    PocketsGrid_Unlift(&self->grid);
    PocketsLetters_Unlift(&self->letters);
}
CLEAN_AS(func_ov101_0229cba0, PocketsPick_ClearSelection)

/* func_ov101_0229cbbc: the state of the item at a grid place; 0xf1 elsewhere. */
int PocketsPick_PlaceItemState(PocketsPick *self, int place)
{
    if (PocketsPick_IsGridPlace(self, (unsigned int) place) != 0) {
        return PocketsGrid_ItemState(&self->grid, PocketsPick_GridIndex(self, place));
    }
    return PICK_NO_ITEM_STATE;
}
CLEAN_AS(func_ov101_0229cbbc, PocketsPick_PlaceItemState)

/* func_ov101_0229cbec: the item at a grid place; 0xfff1 (no item) elsewhere. */
int PocketsPick_PlaceItem(PocketsPick *self, int place)
{
    if (PocketsPick_IsGridPlace(self, (unsigned int) place) != 0) {
        return PocketsGrid_Item(&self->grid, PocketsPick_GridIndex(self, place));
    }
    return PICK_NO_ITEM;
}
CLEAN_AS(func_ov101_0229cbec, PocketsPick_PlaceItem)

/* func_ov101_0229cc20: whether a grid place is empty; 1 elsewhere. */
int PocketsPick_PlaceIsEmpty(PocketsPick *self, int place)
{
    if (PocketsPick_IsGridPlace(self, (unsigned int) place) != 0) {
        return PocketsGrid_IsEmpty(&self->grid, PocketsPick_GridIndex(self, place));
    }
    return 1;
}
CLEAN_AS(func_ov101_0229cc20, PocketsPick_PlaceIsEmpty)

/* func_ov101_0229cc50: whether a grid place is dimmed (may not be picked); 0 elsewhere. */
int PocketsPick_PlaceIsDimmed(PocketsPick *self, int place)
{
    if (PocketsPick_IsGridPlace(self, (unsigned int) place) != 0) {
        return PocketsGrid_IsDimmed(&self->grid, PocketsPick_GridIndex(self, place));
    }
    return 0;
}
CLEAN_AS(func_ov101_0229cc50, PocketsPick_PlaceIsDimmed)

/* func_ov101_0229cc80: every slot that holds an item and whose bit is clear in the mask the
 * scene was opened with (GroupParams_Mask) is dimmed. */
void PocketsPick_DimUnselectable(PocketsPick *self)
{
    unsigned int mask = GroupParams_Mask();
    for (int place = 0; place < PICK_GRID_SLOTS; place++) {
        if (PocketsPick_PlaceIsEmpty(self, place) != 0) {
            continue;
        }
        if (mask & (1u << place)) {
            continue;
        }
        PocketsGrid_DimPlace(&self->grid, PocketsPick_GridIndex(self, place));
    }
}
CLEAN_AS(func_ov101_0229cc80, PocketsPick_DimUnselectable)

/* func_ov101_0229ccd0: a place's y: a slot's, 16 pixels above where the grid's object has it;
 * the close button's; 0 for others. */
int PocketsPick_PlaceY(PocketsPick *self, int place)
{
    if (PocketsPick_IsGridPlace(self, (unsigned int) place) != 0) {
        return PocketsGrid_PlaceY(&self->grid, PocketsPick_GridIndex(self, place)) - PICK_GRID_RAISE;
    }
    if (place == PICK_PLACE_CLOSE) {
        return PICK_CLOSE_Y;
    }
    return 0;
}
CLEAN_AS(func_ov101_0229ccd0, PocketsPick_PlaceY)

/* func_ov101_0229cd08: a place's x: a slot's; the close button's; 0 for others. */
int PocketsPick_PlaceX(PocketsPick *self, int place)
{
    if (PocketsPick_IsGridPlace(self, (unsigned int) place) != 0) {
        return PocketsGrid_PlaceX(&self->grid, PocketsPick_GridIndex(self, place));
    }
    if (place == PICK_PLACE_CLOSE) {
        return PICK_CLOSE_X;
    }
    return 0;
}
CLEAN_AS(func_ov101_0229cd08, PocketsPick_PlaceX)

/* func_ov101_0229cd40: a grid place's slot set to `item` in `state` (the pocket slot written
 * through the grid's object) and redrawn; other places are left alone. */
void PocketsPick_SetSlotItem(PocketsPick *self, int place, int item, int state)
{
    if (PocketsPick_IsGridPlace(self, (unsigned int) place) == 0) {
        return;
    }
    int index = PocketsPick_GridIndex(self, place);
    PocketsGrid_SetItem(&self->grid, index, item, state);
    PocketsGrid_RefreshPlace(&self->grid, (unsigned int) index);
}
CLEAN_AS(func_ov101_0229cd40, PocketsPick_SetSlotItem)

/* func_ov101_0229cd80: the held item put down at the grid place `place`; the item there, if any,
 * goes to the place the held one came from. 1 for a grid place, 0 (nothing done) for others. */
int PocketsPick_DropHeldAt(PocketsPick *self, int place)
{
    if (PocketsPick_IsGridPlace(self, (unsigned int) place) == 0) {
        return 0;
    }
    int item = PocketsPick_PlaceItem(self, place);
    if (item != PICK_NO_ITEM) {
        int state = PocketsPick_PlaceItemState(self, place);
        PocketsPick_SetSlotItem(self, self->held_place, item, state);
    }
    PocketsPick_PutHeldAt(self, place);
    return 1;
}
CLEAN_AS(func_ov101_0229cd80, PocketsPick_DropHeldAt)

/* func_ov101_0229cdd0: the grid place under (x, y); PICK_PLACE_NONE for none, and with
 * `with_item` for an empty slot. */
int PocketsPick_GridPlaceAtTouch(PocketsPick *self, int x, int y, int with_item)
{
    int index = PocketsGrid_PocketPlaceAtTouch(&self->grid, x, y);
    if (index == PICK_GRID_NO_INDEX) {
        return PICK_PLACE_NONE;
    }
    if (with_item != 0 && PocketsGrid_IsEmpty(&self->grid, index) != 0) {
        return PICK_PLACE_NONE;
    }
    return PocketsPick_GridPlace(self, (unsigned int) index);
}
CLEAN_AS(func_ov101_0229cdd0, PocketsPick_GridPlaceAtTouch)

/* func_ov101_0229ce0c: the place of grid index `index`; PICK_PLACE_NONE past the grid. */
u8 PocketsPick_GridPlace(PocketsPick *self, unsigned int index)
{
    (void) self;
    if (index <= PICK_PLACE_GRID_LAST) {
        return (u8) index;
    }
    return PICK_PLACE_NONE;
}
CLEAN_AS(func_ov101_0229ce0c, PocketsPick_GridPlace)

/* func_ov101_0229ce1c: the grid index of a grid place; 0 for others. */
int PocketsPick_GridIndex(PocketsPick *self, int place)
{
    if (PocketsPick_IsGridPlace(self, (unsigned int) place) != 0) {
        return (u8) place;
    }
    return 0;
}
CLEAN_AS(func_ov101_0229ce1c, PocketsPick_GridIndex)

/* func_ov101_0229ce38: whether `place` is one of the grid's. */
int PocketsPick_IsGridPlace(PocketsPick *self, unsigned int place)
{
    (void) self;
    return place <= PICK_PLACE_GRID_LAST;
}
CLEAN_AS(func_ov101_0229ce38, PocketsPick_IsGridPlace)

/* func_ov101_0229ce44 */
void PocketsPick_EndLayerTask(PocketsPick *self)
{
    LayerTask_End(&self->layer_task.first);
}
CLEAN_AS(func_ov101_0229ce44, PocketsPick_EndLayerTask)

/* func_ov101_0229ce50: the held item glides from where it is to `place` in `steps` steps (its
 * first step taken at once); `place` is kept as where it goes back to, sub state 0x12. */
void PocketsPick_GlideHeldTo(PocketsPick *self, int place, int steps)
{
    self->held_place = (u8) place;
    Glide_SetPlace(&self->glide, self->held_x, self->held_y);
    int x = PocketsPick_PlaceX(self, place);
    int y = PocketsPick_PlaceY(self, place);
    Glide_MoveTo(&self->glide, x, y, steps);
    Glide_Step(&self->glide);
    PocketsPick_FollowGlide(self);
    MenuScene_SetSubState(pick_scene(self), PICK_SUB_HELD_GLIDE);
}
CLEAN_AS(func_ov101_0229ce50, PocketsPick_GlideHeldTo)

/* func_ov101_0229ceb4: the item at `place` picked up with the cursor: the popup hidden and, when
 * an item is held, the sub state to go back to set to the keys' hold (7); it follows the cursor
 * sprite. */
void PocketsPick_PickUpWithCursor(PocketsPick *self, int place)
{
    self->held_place = (u8) place;
    Popup_Hide(&self->popup, 1);
    PocketsPick_PickUpItem(self, place);
    if (self->held_kind == PICK_HELD_ITEM) {
        self->return_state = PICK_SUB_HOLD_BY_KEYS;
    }
    PocketsPick_FollowCursorSprite(self);
}
CLEAN_AS(func_ov101_0229ceb4, PocketsPick_PickUpWithCursor)

/* func_ov101_0229cef8: the pen touched `place` (sub state 1): the offset from the touch to the
 * place kept, the popup told of it and shown, the choice's delay set, and sound 0x0c for a slot
 * that may be picked. */
void PocketsPick_TouchPlace(PocketsPick *self, int place)
{
    self->touch_place = (u8) place;
    MenuScene_SetSubState(pick_scene(self), PICK_SUB_HOLD_TOUCH);
    u8 touch_x = data_021f6c58;
    u8 touch_y = data_021f6c54;
    self->grab_dx = PocketsPick_PlaceX(self, self->touch_place) - touch_x;
    self->grab_dy = PocketsPick_PlaceY(self, self->touch_place) - touch_y;
    self->popup_place = (u8) place;
    Popup_Queue(&self->popup);
    Popup_ShowQueued(&self->popup);
    self->open_delay = PICK_OPEN_DELAY;
    if (PocketsPick_PlaceIsDimmed(self, place) == 0) {
        PocketsSound_Play0c();
    }
}
CLEAN_AS(func_ov101_0229cef8, PocketsPick_TouchPlace)

/* func_ov101_0229cf80: the action ends: back to the touch (sub state 0, the cursor sprite
 * hidden) while state flag 2 is clear, else to the keys (sub state 6, the sprite at the cursor). */
void PocketsPick_EndAction(PocketsPick *self)
{
    if (StateFlags_IsClear2() != 0) {
        PocketsPick_EndActionHidden(self);
    } else {
        PocketsPick_EndActionAtCursor(self);
    }
}
CLEAN_AS(func_ov101_0229cf80, PocketsPick_EndAction)

/* func_ov101_0229cfa0: no popup place, the cursor sprite shown at the cursor, the key repeat
 * reset, the popup told of the cursor's place, sub state 6 and the cursor's place selected. */
void PocketsPick_EndActionAtCursor(PocketsPick *self)
{
    self->popup_place = PICK_PLACE_NONE;
    PocketsPick_ShowCursorSprite(self);
    MenuScene_ResetKeyRepeat(pick_scene(self));
    PocketsPick_UpdatePopup(self);
    MenuScene_SetSubState(pick_scene(self), PICK_SUB_IDLE_BY_KEYS);
    PocketsPick_SelectPlace(self, self->cursor);
}
CLEAN_AS(func_ov101_0229cfa0, PocketsPick_EndActionAtCursor)

/* func_ov101_0229cfd4 */
void PocketsPick_EndActionHidden(PocketsPick *self)
{
    PocketsPick_HideCursorSprite(self);
    PocketsPick_ClearSelection(self);
    MenuScene_SetSubState(pick_scene(self), PICK_SUB_IDLE_BY_TOUCH);
}
CLEAN_AS(func_ov101_0229cfd4, PocketsPick_EndActionHidden)

/* func_ov101_0229cff0 (sub state 0x17): the close button's press. While it runs, the cursor
 * sprite (when it shows an animation) follows the button's press frame; once over, the scene
 * closes with nothing picked. */
void PocketsPick_FollowClosePress(PocketsPick *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) == 0) {
        PocketsPick_Cancel(self);
        return;
    }
    if (CellLayerSprite_AnimNumber(pick_sprite_cells(self)) != 0) {
        int frame = ButtonPanel_SelectedPressFrame(&self->panel);
        int x = ButtonPanel_ButtonX(&self->panel, -1);
        int y = ButtonPanel_ButtonY(&self->panel, -1);
        Glider_PlaceAt(&self->cursor_sprite, frame + x, frame + y);
    }
}
CLEAN_AS(func_ov101_0229cff0, PocketsPick_FollowClosePress)

/* func_ov101_0229d054 (sub state 0x16): once the error message is done, back to the kept sub
 * state and the cursor sprite's window set. */
void PocketsPick_WaitError(PocketsPick *self)
{
    if (ErrorMessage_Update(&self->error, 0) != 0) {
        MenuScene_SetSubState(pick_scene(self), self->return_state);
        CellLayerSprite_SetWindow(pick_sprite_cells(self));
    }
}
CLEAN_AS(func_ov101_0229d054, PocketsPick_WaitError)

/* func_ov101_0229d088 (sub state 0x15): once the choice is idle, the picked row's action. */
void PocketsPick_RunActionWhenIdle(PocketsPick *self)
{
    if (PagedChoice_IsIdle(pick_choice(self)) != 0) {
        PocketsPick_RunAction(self);
    }
}
CLEAN_AS(func_ov101_0229d088, PocketsPick_RunActionWhenIdle)

/* func_ov101_0229d0a8 (sub state 0x14): when the choice's delay has run out, the choice asked to
 * close, the popup hidden, the cursor sprite (when it shows an animation) put back at the cursor
 * and sub state 0x15. */
void PocketsPick_CloseChoice(PocketsPick *self)
{
    if (PagedChoice_CountDown(pick_choice(self)) == 0) {
        return;
    }
    PagedChoice_RequestClose(pick_choice(self), 0);
    Popup_Hide(&self->popup, 1);
    if (CellLayerSprite_AnimNumber(pick_sprite_cells(self)) != 0) {
        PocketsPick_PlaceCursorSprite(self);
    }
    MenuScene_SetSubState(pick_scene(self), PICK_SUB_CHOICE_CLOSING);
}
CLEAN_AS(func_ov101_0229d0a8, PocketsPick_CloseChoice)

/* func_ov101_0229d0f8 (sub state 0x13): once the choice is shown: with state flag 2 the cursor
 * sprite at its first row and sub state 8 (the keys), else sub state 4 (the touch). */
void PocketsPick_WaitChoiceShown(PocketsPick *self)
{
    if (PagedChoice_IsShown(pick_choice(self)) == 0) {
        return;
    }
    if (StateFlags_Test2() != 0) {
        PocketsPick_PointAtFirstRow(self);
        MenuScene_SetSubState(pick_scene(self), PICK_SUB_CHOICE_BY_KEYS);
    } else {
        MenuScene_SetSubState(pick_scene(self), PICK_SUB_CHOICE_BY_TOUCH);
    }
}
CLEAN_AS(func_ov101_0229d0f8, PocketsPick_WaitChoiceShown)

/* func_ov101_0229d134 (sub state 0x12): the held item follows the glide; when it is over, it is
 * put down at the place it was sent to and the action ends. */
void PocketsPick_StepHeldGlide(PocketsPick *self)
{
    if (Glide_Step(&self->glide) != 0) {
        PocketsPick_PutHeldAt(self, self->held_place);
        PocketsPick_EndAction(self);
    } else {
        PocketsPick_FollowGlide(self);
    }
}
CLEAN_AS(func_ov101_0229d134, PocketsPick_StepHeldGlide)

/* func_ov101_0229d168 (sub state 0x11): after a swap, back to the kept sub state once the cursor
 * sprite's animation ends; once its turn has settled, PICK_FLAG_SWAPPING is cleared and the held
 * item follows the cursor sprite. */
void PocketsPick_FinishSwap(PocketsPick *self)
{
    if (CellLayerSprite_IsDone(pick_sprite_cells(self)) != 0) {
        MenuScene_SetSubState(pick_scene(self), self->return_state);
    }
    if (Glider_IsTurnSettled(&self->cursor_sprite) != 0) {
        PocketsPick_ClearFlags(self, PICK_FLAG_SWAPPING);
        PocketsPick_FollowCursorSprite(self);
    }
}
CLEAN_AS(func_ov101_0229d168, PocketsPick_FinishSwap)

/* func_ov101_0229d1a8 (sub state 0x10): the held item changes places with the item at `target`
 * (sub state 0x11, the popup told of the cursor's place), unless the cursor sprite's turn is at
 * its frame 2, which goes back to sub state 6 instead. */
void PocketsPick_Swap(PocketsPick *self)
{
    if (Glider_IsTurnAtFrame2(&self->cursor_sprite) == 0) {
        PocketsPick_SwapHeldWith(self, self->target);
        PocketsPick_SetFlags(self, PICK_FLAG_SWAPPING);
        MenuScene_SetSubState(pick_scene(self), PICK_SUB_SWAPPED);
        PocketsPick_UpdatePopup(self);
    } else {
        MenuScene_SetSubState(pick_scene(self), PICK_SUB_IDLE_BY_KEYS);
    }
}
CLEAN_AS(func_ov101_0229d1a8, PocketsPick_Swap)

/* func_ov101_0229d1f0 (sub state 0x0f): while the cursor sprite's turn has not settled the held
 * item follows it. Then it is put down at `target` when the cursor is there (the popup told of
 * the place, sub state 6), else it glides to `target`. */
void PocketsPick_PutDownWithCursor(PocketsPick *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite) != 0) {
        PocketsPick_FollowCursorSprite(self);
        return;
    }
    if (self->cursor == self->target) {
        PocketsPick_DropHeldAt(self, self->target);
        PocketsPick_UpdatePopup(self);
        MenuScene_SetSubState(pick_scene(self), PICK_SUB_IDLE_BY_KEYS);
    } else {
        PocketsPick_GlideHeldTo(self, self->target, 4);
    }
}
CLEAN_AS(func_ov101_0229d1f0, PocketsPick_PutDownWithCursor)

/* func_ov101_0229d240 (sub state 0x0e): after a pick up, back to the kept sub state once the
 * cursor sprite's animation ends; the held item follows the cursor sprite. */
void PocketsPick_FinishPickUp(PocketsPick *self)
{
    if (CellLayerSprite_IsDone(pick_sprite_cells(self)) != 0) {
        MenuScene_SetSubState(pick_scene(self), self->return_state);
    }
    PocketsPick_FollowCursorSprite(self);
}
CLEAN_AS(func_ov101_0229d240, PocketsPick_FinishPickUp)

/* func_ov101_0229d26c (sub state 0x0d): once the cursor sprite's turn has settled, the item at
 * the cursor is picked up (sub state 0x0e). */
void PocketsPick_PickUpOnTurn(PocketsPick *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite) != 0) {
        PocketsPick_PickUpWithCursor(self, self->cursor);
        MenuScene_SetSubState(pick_scene(self), PICK_SUB_PICKED_UP);
    }
}
CLEAN_AS(func_ov101_0229d26c, PocketsPick_PickUpOnTurn)

/* func_ov101_0229d29c (sub state 0x0c): once the cursor sprite's animation ends, the first of
 * its set and sub state 6. */
void PocketsPick_WaitCursorAnim(PocketsPick *self)
{
    if (CellLayerSprite_IsDone(pick_sprite_cells(self)) != 0) {
        PocketsPick_ShowCursorFirstOfSet(self);
        MenuScene_SetSubState(pick_scene(self), PICK_SUB_IDLE_BY_KEYS);
    }
}
CLEAN_AS(func_ov101_0229d29c, PocketsPick_WaitCursorAnim)

/* func_ov101_0229d2c4 (sub state 0x0b): once the cursor sprite's press animation ends, the close
 * button is pressed. */
void PocketsPick_PressCloseWhenDone(PocketsPick *self)
{
    if (CellLayerSprite_IsDone(pick_sprite_cells(self)) != 0) {
        pick_press_close_button(self);
    }
}
CLEAN_AS(func_ov101_0229d2c4, PocketsPick_PressCloseWhenDone)

/* Obj_ov101_0229e078::func_ov101_0229d2fc (sub state 0x0a): once the cursor sprite stops, back to
 * the kept sub state, run at once; back to 6 or 7 (the keys' sub states), the cursor's place is
 * selected first. The held item follows the cursor sprite. */
void PocketsPick_WaitCursorSprite(PocketsPick *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(pick_scene(self), self->return_state);
        if (self->return_state == PICK_SUB_IDLE_BY_KEYS || self->return_state == PICK_SUB_HOLD_BY_KEYS) {
            PocketsPick_SelectPlace(self, self->cursor);
        }
        PocketsPick_RunSubState(self);
    }
    PocketsPick_FollowCursorSprite(self);
}
CLEAN_AS(_ZN18Obj_ov101_0229e07819func_ov101_0229d2fcEv, PocketsPick_WaitCursorSprite)

/* func_ov101_0229d34c (sub state 9): once the cursor sprite's press animation ends, the row it
 * points at is picked. */
void PocketsPick_PickChoiceRow(PocketsPick *self)
{
    if (CellLayerSprite_IsDone(pick_sprite_cells(self)) != 0) {
        pick_row(self, self->choice_row);
    }
}
CLEAN_AS(func_ov101_0229d34c, PocketsPick_PickChoiceRow)

/* func_ov101_0229d398 (sub state 8): the choice by the keys. A touch cancels it; the d-pad moves
 * the cursor sprite over the rows; A presses on the row (sub state 9); B points at the last row
 * (the cancel) and closes the choice. */
void PocketsPick_ChooseByKeys(PocketsPick *self)
{
    if (MenuScene_TakeTouch(pick_scene(self)) != 0) {
        PocketsPick_CancelChoice(self);
        return;
    }
    u32 keys = MenuScene_LatchRepeatedKeys(pick_scene(self));
    if (PagedChoice_MoveCursor(pick_choice(self), (int) keys, &self->choice_row, 0) != 0) {
        PocketsPick_GlideToRow(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & PICK_PAD_A) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(pick_scene(self), PICK_SUB_PICK_ROW);
    } else if (pressed & PICK_PAD_B) {
        PocketsPick_PointAtLastRow(self);
    }
}
CLEAN_AS(func_ov101_0229d398, PocketsPick_ChooseByKeys)

/* func_ov101_0229d410 (sub state 7): an item is held and moves with the cursor. The d-pad moves
 * the cursor. A at a grid place puts it down there when empty, else swaps it with the item
 * there; B puts it back where it came from. Else it follows the cursor sprite and a queued popup
 * is shown. */
void PocketsPick_MoveHeldByKeys(PocketsPick *self)
{
    if (pick_move_cursor_by_keys(self)) {
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & PICK_PAD_A) {
        if (PocketsPick_IsGridPlace(self, self->cursor) != 0) {
            if (PocketsPick_PlaceIsEmpty(self, self->cursor) != 0) {
                PocketsPick_StartPutDown(self, self->cursor);
            } else {
                PocketsPick_StartSwap(self, self->cursor);
            }
        }
    } else if (pressed & PICK_PAD_B) {
        PocketsPick_StartPutDown(self, self->held_place);
    } else {
        PocketsPick_FollowCursorSprite(self);
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov101_0229d410, PocketsPick_MoveHeldByKeys)

/* func_ov101_0229d4b4 (sub state 6): the cursor waits for the keys. A touch hides the cursor
 * sprite and the popup (sub state 0). The d-pad moves the cursor. A on a slot with an item opens
 * its choice, A on the close button presses it; B presses the close button (the cursor sprite
 * hidden); else a queued popup is shown.
 * QUIRK: A on a dimmed slot is not taken as A: B is tested next. */
void PocketsPick_IdleByKeys(PocketsPick *self)
{
    if (MenuScene_TakeTouch(pick_scene(self)) != 0) {
        PocketsPick_EndActionHidden(self);
        Popup_Hide(&self->popup, 1);
        return;
    }
    if (pick_move_cursor_by_keys(self)) {
        return;
    }
    if (PocketsPick_PlaceIsDimmed(self, self->cursor) == 0 && (data_021fbe40.pressed & PICK_PAD_A) != 0) {
        if (PocketsPick_IsGridPlace(self, self->cursor) != 0) {
            if (PocketsPick_PlaceIsEmpty(self, self->cursor) == 0) {
                PocketsPick_OpenChoice(self, self->cursor, 0);
            }
        } else if (self->cursor == PICK_PLACE_CLOSE) {
            PocketsPick_PressClose(self);
        }
        return;
    }
    if (data_021fbe40.pressed & PICK_PAD_B) {
        PocketsPick_HideCursorSprite(self);
        pick_press_close_button(self);
        Popup_Hide(&self->popup, 0);
    } else {
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov101_0229d4b4, PocketsPick_IdleByKeys)

/* func_ov101_0229d5a8 (sub state 5): the held item follows the stylus; while the pen is down only
 * the grid place under the item's middle (8 pixels right and down of where it is) is marked. The
 * pen lifted there puts the item down (an item there goes where the held one came from) and ends
 * the action; lifted elsewhere, the item glides back (sub state 0x12).
 * QUIRK: were the drop refused, the item would glide back and the action still end, replacing
 * the glide's sub state; the place found under the touch is always one of the grid. */
void PocketsPick_DragHeld(PocketsPick *self)
{
    PocketsPick_FollowTouch(self);
    PocketsPick_ClearMarks(self);
    int x = (int) ((u32) self->held_x + 8);
    int y = (int) ((u32) self->held_y + 8);
    int place = PocketsPick_GridPlaceAtTouch(self, x, y, 0);
    if (place == PICK_PLACE_NONE) {
        if (data_021fbdd8 == 0) {
            PocketsPick_GlideHeldTo(self, self->held_place, 4);
        }
        return;
    }
    if (data_021fbdd8 != 0) {
        PocketsPick_MarkPlace(self, place);
        return;
    }
    if (PocketsPick_DropHeldAt(self, place) == 0) {
        PocketsPick_GlideHeldTo(self, self->held_place, 4);
    }
    PocketsPick_EndAction(self);
}
CLEAN_AS(func_ov101_0229d5a8, PocketsPick_DragHeld)

/* func_ov101_0229d624 (sub state 4): the choice by touch, once it is shown. A button cancels it;
 * the pen put down on a row (or below them, the last) picks it. */
void PocketsPick_ChooseByTouch(PocketsPick *self)
{
    if (PagedChoice_IsShown(pick_choice(self)) == 0) {
        return;
    }
    if (MenuScene_TakeButtons(pick_scene(self), 1) != 0) {
        PocketsPick_CancelChoice(self);
        return;
    }
    if (!pick_pen_pressed()) {
        return;
    }
    int row = PagedChoice_RowAtOrLast(pick_choice(self), data_021f6c58, data_021f6c54);
    if (row >= 0) {
        pick_row(self, row);
    }
}
CLEAN_AS(func_ov101_0229d624, PocketsPick_ChooseByTouch)

/* func_ov101_0229d6bc (sub state 3): once the popup is up and the delay has run out, the touched
 * place's choice opens above the popup (sub state 2). */
void PocketsPick_OpenTouchedChoice(PocketsPick *self)
{
    if (Popup_IsUp(&self->popup) == 0) {
        return;
    }
    if (self->open_delay != 0) {
        self->open_delay--;
        return;
    }
    PocketsPick_OpenChoice(self, self->touch_place, 1);
    MenuScene_SetSubState(pick_scene(self), PICK_SUB_WAIT_PEN_UP);
}
CLEAN_AS(func_ov101_0229d6bc, PocketsPick_OpenTouchedChoice)

/* func_ov101_0229d704 (sub state 2): once the pen is lifted, sub state 4. */
void PocketsPick_WaitPenUp(PocketsPick *self)
{
    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(pick_scene(self), PICK_SUB_CHOICE_BY_TOUCH);
    }
}
CLEAN_AS(func_ov101_0229d704, PocketsPick_WaitPenUp)

/* Obj_ov101_0229e078::func_ov101_0229d720 (sub state 1): the pen is on a touched place
 * (PocketsPick_TouchPlace). Lifted from a dimmed slot: back to sub state 0 with the popup closing
 * after 60 frames; from another: sub state 3, run at once. Held on a slot that is not dimmed,
 * once the popup is up and the delay has run out, its choice opens above the popup (sub state
 * 2); else a queued popup is shown. */
void PocketsPick_HoldTouchOnPlace(PocketsPick *self)
{
    if (data_021fbdd8 == 0) {
        if (PocketsPick_PlaceIsDimmed(self, self->touch_place) != 0) {
            MenuScene_SetSubState(pick_scene(self), PICK_SUB_IDLE_BY_TOUCH);
            Popup_SetTimer(&self->popup, PICK_POPUP_FRAMES);
        } else {
            MenuScene_SetSubState(pick_scene(self), PICK_SUB_OPEN_TOUCHED);
            PocketsPick_RunSubState(self);
        }
        return;
    }
    if (PocketsPick_PlaceIsDimmed(self, self->touch_place) == 0 && Popup_IsUp(&self->popup) != 0) {
        if (self->open_delay != 0) {
            self->open_delay--;
        } else {
            PocketsPick_OpenChoice(self, self->touch_place, 1);
            MenuScene_SetSubState(pick_scene(self), PICK_SUB_WAIT_PEN_UP);
        }
        return;
    }
    Popup_ShowQueued(&self->popup);
}
CLEAN_AS(_ZN18Obj_ov101_0229e07819func_ov101_0229d720Ev, PocketsPick_HoldTouchOnPlace)

/* func_ov101_0229d7c0 (sub state 0): the touch is in use and the cursor sprite hidden. A button
 * puts the cursor sprite back at the cursor (sub state 6). The pen put down on a slot with an
 * item (16 pixels below the touch, as the grid is drawn raised) touches it (sub state 1); on the
 * panel's close button, presses it. */
void PocketsPick_IdleByTouch(PocketsPick *self)
{
    if (MenuScene_TakeButtons(pick_scene(self), 1) != 0) {
        PocketsPick_EndActionAtCursor(self);
        return;
    }
    if (!pick_pen_pressed()) {
        return;
    }
    int place = PocketsPick_GridPlaceAtTouch(self, data_021f6c58, data_021f6c54 + PICK_GRID_RAISE, 1);
    if (place != PICK_PLACE_NONE) {
        PocketsPick_TouchPlace(self, place);
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, PICK_PANEL_CLOSE) == 0) {
        return;
    }
    pick_press_close_button(self);
}
CLEAN_AS(func_ov101_0229d7c0, PocketsPick_IdleByTouch)

/* func_ov101_0229d850: the wallet's object files loaded (its answer unused) and the panel's text
 * colours. */
void PocketsPick_LoadWalletAndPanel(PocketsPick *self)
{
    PocketsWallet_LoadObjFiles(&self->wallet);
    ButtonPanel_LoadTextColors(&self->panel);
}
CLEAN_AS(func_ov101_0229d850, PocketsPick_LoadWalletAndPanel)

/* func_ov101_0229d874: the wallet's display set up on screen 0. */
void PocketsPick_PrepareWallet(PocketsPick *self)
{
    PocketsWallet_SetUp(&self->wallet, 0);
}
CLEAN_AS(func_ov101_0229d874, PocketsPick_PrepareWallet)

/* func_ov101_0229d888: layer 6 at priority 2, with its plain background settings. */
void PocketsPick_SetUpLayer6(void)
{
    DisplayLayer_SetPriority(PICK_LAYER, 2);
    DisplayLayer_SetBgControl(PICK_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov101_0229d888, PocketsPick_SetUpLayer6)

/* func_ov101_0229d8a8: the end of a frame: the choice and the wallet's display updated, and the
 * popup placed when its update asks for it. */
void PocketsPick_EndFrame(PocketsPick *self)
{
    PagedChoice_Update(pick_choice(self));
    PocketsWallet_Update(&self->wallet);
    if (Popup_Update(&self->popup) != 0) {
        PocketsPick_PlacePopup(self);
    }
}
CLEAN_AS(func_ov101_0229d8a8, PocketsPick_EndFrame)

/* func_ov101_0229d8e0: the start of a frame: the layer task, the three objects of ov094's and the
 * panel's texts. */
void PocketsPick_BeginFrame(PocketsPick *self)
{
    PocketsPick_EndLayerTask(self);
    PocketsWallet_BeginFrame(&self->wallet);
    PocketsGrid_BeginFrame(&self->grid);
    PocketsLetters_BeginFrame(&self->letters);
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov101_0229d8e0, PocketsPick_BeginFrame)

/* func_ov101_0229d91c */
void PocketsPick_EndInteractiveFrame(PocketsPick *self)
{
    PocketsPick_EndFrame(self);
}
CLEAN_AS(func_ov101_0229d91c, PocketsPick_EndInteractiveFrame)

/* func_ov101_0229d924: the start of a frame, then the cursor sprite's update through its class
 * (vtable slot 3). */
void PocketsPick_BeginInteractiveFrame(PocketsPick *self)
{
    PocketsPick_BeginFrame(self);
    pick_update_cursor_sprite(self);
}
CLEAN_AS(func_ov101_0229d924, PocketsPick_BeginInteractiveFrame)

/* func_ov101_0229d940: the members' teardown before the scene closes. */
void PocketsPick_Teardown(PocketsPick *self)
{
    PocketsPick_EndLayerTask(self);
    PocketsWallet_Teardown(&self->wallet);
    PocketsGrid_Teardown(&self->grid);
    PagedChoice_Dismiss(pick_choice(self));
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov101_0229d940, PocketsPick_Teardown)

/* func_ov101_0229d97c: the scene's setup: no flags, the three objects of ov094's set up, no popup
 * place, the glide stopped, nothing held, the cursor at slot 0, the choice on layer 3, no
 * delay. */
void PocketsPick_Setup(PocketsPick *self)
{
    self->flags = 0;
    PocketsGrid_Init(&self->grid, 2);
    PocketsLetters_Init(&self->letters, 2);
    PocketsWallet_Init(&self->wallet, 6);
    self->popup_place = PICK_PLACE_NONE;
    Glide_Stop(&self->glide);
    self->held_kind = PICK_HELD_NONE;
    self->cursor = PICK_PLACE_GRID_FIRST;
    PagedChoice_Init(pick_choice(self), 3, 1, NULL);
    self->open_delay = 0;
}
CLEAN_AS(func_ov101_0229d97c, PocketsPick_Setup)

/* func_ov101_0229d9ec (state 4): the scene wipes out. When done, layer 6 hidden, the delete phase
 * set and nothing drawn. The objects' offset follows the wipe. */
void PocketsPick_WipeOut(PocketsPick *self)
{
    if (MenuScene_StepWipe(pick_scene(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(PICK_LAYER);
        MenuScene_SetPhase(pick_scene(self), PICK_PHASE_DELETE);
        PocketsPick_ClearFlags(self, PICK_FLAG_DRAWN);
        PocketsPick_ClearFlags(self, PICK_FLAG_OBJECTS_DRAWN);
    } else {
        MenuScene_ScrollWipe(pick_scene(self), PICK_LAYER, 0, PICK_SCROLL_Y);
    }
    self->wipe_y = MenuScene_WipeOffsetY(pick_scene(self));
}
CLEAN_AS(func_ov101_0229d9ec, PocketsPick_WipeOut)

/* func_ov101_0229da38 (state 3): the popup and the cursor sprite hidden, the parent told the
 * scene ends (code 0x44), and the scene starts to wipe out (state 4). */
void PocketsPick_StartWipeOut(PocketsPick *self)
{
    Popup_Hide(&self->popup, 1);
    PocketsPick_HideCursorSprite(self);
    MenuDispatch_SetMode((MenuDispatch *) (void *) pick_parent(self), PICK_PARENT_CODE_END, 1);
    MenuScene_StartWipeOnWindow2(pick_scene(self), PICK_WIPE_LAYERS, 0, 0, PICK_WIPE_MARGIN);
    MenuScene_ScrollWipe(pick_scene(self), PICK_LAYER, 0, PICK_SCROLL_Y);
    MenuScene_SetState(pick_scene(self), PICK_STATE_WIPE_OUT);
    self->wipe_y = MenuScene_WipeOffsetY(pick_scene(self));
}
CLEAN_AS(func_ov101_0229da38, PocketsPick_StartWipeOut)

/* func_ov101_0229da98 (state 2): the scene wipes in; when done, the interactive phase and the
 * action ends (PocketsPick_EndAction picks the first sub state). The objects' offset follows the
 * wipe. */
void PocketsPick_WipeIn(PocketsPick *self)
{
    if (MenuScene_StepWipeBack(pick_scene(self), 0) != 0) {
        MenuScene_SetPhase(pick_scene(self), PICK_PHASE_INTERACTIVE);
        PocketsPick_EndAction(self);
    }
    MenuScene_ScrollWipe(pick_scene(self), PICK_LAYER, 0, PICK_SCROLL_Y);
    self->wipe_y = MenuScene_WipeOffsetY(pick_scene(self));
}
CLEAN_AS(func_ov101_0229da98, PocketsPick_WipeIn)

/* func_ov101_0229dad4 (state 1): the wallet's files and the panel's colours loaded, the panel's
 * layout 5 (message 0x65), the grid's pockets loaded and the slots that may not be picked dimmed,
 * the letters loaded and dimmed (states mask 0xf), layer 6 shown and wiping in (state 2); the
 * scene and its objects drawn. */
void PocketsPick_StartWipeIn(PocketsPick *self)
{
    PocketsPick_LoadWalletAndPanel(self);
    ButtonPanel_SetLayout5(&self->panel, PICK_PANEL_MESSAGE);
    PocketsGrid_LoadPockets(&self->grid);
    PocketsPick_DimUnselectable(self);
    PocketsLetters_LoadPockets(&self->letters);
    PocketsLetters_DimByState(&self->letters, 0xf);
    MenuScene_StartWipeCoveredOnWindow2(pick_scene(self), PICK_WIPE_LAYERS, 0, 0, PICK_WIPE_MARGIN);
    DisplayLayer_Show(PICK_LAYER);
    MenuScene_ScrollWipe(pick_scene(self), PICK_LAYER, 0, PICK_SCROLL_Y);
    MenuScene_SetState(pick_scene(self), PICK_STATE_WIPE_IN);
    PocketsPick_SetFlags(self, PICK_FLAG_DRAWN);
    PocketsPick_SetFlags(self, PICK_FLAG_OBJECTS_DRAWN);
    self->wipe_y = MenuScene_WipeOffsetY(pick_scene(self));
}
CLEAN_AS(func_ov101_0229dad4, PocketsPick_StartWipeIn)

/* func_ov101_0229db60 (state 0): layer 6 set up and the wallet's display prepared, then
 * state 1. */
void PocketsPick_StartSetup(PocketsPick *self)
{
    PocketsPick_SetUpLayer6();
    PocketsPick_PrepareWallet(self);
    MenuScene_SetState(pick_scene(self), PICK_STATE_START_WIPE_IN);
}
CLEAN_AS(func_ov101_0229db60, PocketsPick_StartSetup)

/* func_ov101_0229db7c (vtable slot 0x5c, phase 5): the scene asks to be deleted. */
int PocketsPick_RequestDelete(PocketsPick *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov101_0229db7c, PocketsPick_RequestDelete)

/* func_ov101_0229db8c (vtable slot 0x58, phase 4): nothing. */
int PocketsPick_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov101_0229db8c, PocketsPick_Phase4Idle)

/* func_ov101_0229db90 (vtable slot 0x54, phase 3): nothing. */
int PocketsPick_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov101_0229db90, PocketsPick_Phase3Idle)

/* Obj_ov101_0229e078::func_ov101_0229db94 (vtable slot 0x50, phase 2): a frame of the scene in
 * use: its start, its sub state, its end. Answers 1. */
int PocketsPick_RunInteractive(PocketsPick *self)
{
    PocketsPick_BeginInteractiveFrame(self);
    PocketsPick_RunSubState(self);
    PocketsPick_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov101_0229e07819func_ov101_0229db94Ev, PocketsPick_RunInteractive)

/* Obj_ov101_0229e078::func_ov101_0229dbb0: the sub state's function (PocketsPickSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 0x18; the game reads past the table for others. */
void PocketsPick_RunSubState(PocketsPick *self)
{
    static const MemberPointer *const sub_states[PICK_SUB_STATES] = {
        &data_ov101_0229e038, &data_ov101_0229e030, &data_ov101_0229e028, &data_ov101_0229e020, &data_ov101_0229e018,
        &data_ov101_0229e010, &data_ov101_0229e008, &data_ov101_0229e000, &data_ov101_0229dff8, &data_ov101_0229dff0,
        &data_ov101_0229dfa8, &data_ov101_0229dfe8, &data_ov101_0229dfd8, &data_ov101_0229e048, &data_ov101_0229dfc8,
        &data_ov101_0229dfc0, &data_ov101_0229dfb8, &data_ov101_0229dfb0, &data_ov101_0229dfa0, &data_ov101_0229e040,
        &data_ov101_0229dfd0, &data_ov101_0229df90, &data_ov101_0229df88, &data_ov101_0229e060,
    };
    MemberTable_InitOnce(&data_ov101_0229e0e4, data_ov101_0229e110, sub_states, PICK_SUB_STATES);
    MemberPointer_CallVoid(&data_ov101_0229e110[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov101_0229e07819func_ov101_0229dbb0Ev, PocketsPick_RunSubState)

/* Obj_ov101_0229e078::func_ov101_0229dd54 (vtable slot 0x4c, phase 1): a frame of the scene's
 * states (PocketsPickState) between the frame's start and end, through the table of member
 * functions (filled once from its constants, before the frame starts). Answers 1.
 * REQUIRES: the state is below 5; the game reads past the table for others. */
int PocketsPick_RunState(PocketsPick *self)
{
    static const MemberPointer *const states[PICK_STATES] = {
        &data_ov101_0229df80, &data_ov101_0229e068, &data_ov101_0229dfe0, &data_ov101_0229e058, &data_ov101_0229e050,
    };
    MemberTable_InitOnce(&data_ov101_0229e0e0, data_ov101_0229e0e8, states, PICK_STATES);
    PocketsPick_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov101_0229e0e8[self->base.state], self);
    PocketsPick_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov101_0229e07819func_ov101_0229dd54Ev, PocketsPick_RunState)

/* func_ov101_0229ddf4 (vtable slot 0x24): the scene's draw: the choice; while the scene is drawn,
 * the popup (through its class, slot 2) and the cursor sprite (with the keys in use); with
 * PICK_FLAG_OBJECTS_DRAWN the panel at the wipe's offset and the three objects of ov094's 16
 * pixels above it. Answers 1. */
int PocketsPick_Draw(PocketsPick *self)
{
    PagedChoice_Draw(pick_choice(self));
    if (PocketsPick_TestFlags(self, PICK_FLAG_DRAWN) == 0) {
        return 1;
    }
    pick_draw_member(&self->popup);
    if (StateFlags_Test2() != 0) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    if (PocketsPick_TestFlags(self, PICK_FLAG_OBJECTS_DRAWN) != 0) {
        ButtonPanel_Draw(&self->panel, self->wipe_y);
        int y = self->wipe_y - PICK_GRID_RAISE;
        PocketsGrid_DrawPockets(&self->grid, 0, y);
        PocketsLetters_DrawPockets(&self->letters, 0, y);
        PocketsWallet_Draw(&self->wallet, y);
    }
    return 1;
}
CLEAN_AS(func_ov101_0229ddf4, PocketsPick_Draw)

/* func_ov101_0229de94 (vtable slot 0x0c): the scene closes: the parent told and the members torn
 * down. Answers 1. */
int PocketsPick_Close(PocketsPick *self)
{
    MenuDispatch_ChildClosed((MenuDispatch *) (void *) pick_parent(self));
    PocketsPick_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov101_0229de94, PocketsPick_Close)

/* func_ov101_0229deb0 (vtable slot 0x00): the scene starts: its setup, state 0 and phase 0.
 * Answers 1. */
int PocketsPick_Start(PocketsPick *self)
{
    PocketsPick_Setup(self);
    MenuScene_SetState(pick_scene(self), PICK_STATE_START_SETUP);
    MenuScene_SetPhase(pick_scene(self), PICK_PHASE_0);
    return 1;
}
CLEAN_AS(func_ov101_0229deb0, PocketsPick_Start)

/* func_ov101_0229ded0: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base, the scene's vtable and its members constructed. */
PocketsPick *PocketsPick_New(void)
{
    PocketsPick *self = MenuScene_Alloc(sizeof(PocketsPick));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov101_0229e078;
    LayerTask_ConstructPair(&self->layer_task);
    PocketsGrid_Construct(&self->grid);
    PocketsLetters_Construct(&self->letters);
    PocketsWallet_Construct(&self->wallet);
    Popup_Construct(&self->popup);
    Glide_Construct(&self->glide);
    Glider0_Construct(&self->cursor_sprite);
    PagedChoice_Construct(pick_choice(self));
    ErrorMessage_Construct(&self->error);
    ButtonPanel_Construct(&self->panel);
    return self;
}
CLEAN_AS(func_ov101_0229ded0, PocketsPick_New)
