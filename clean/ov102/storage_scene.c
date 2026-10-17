/* The item storage scene of overlay 102 (storage_scene.h): its destructors, its flags, the page
 * tabs, the cursor's moves, the places and the held item. */
#include "storage_scene.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/c_library.h"
#include "main/cell_layer_sprite.h"
#include "main/current_pockets.h"
#include "main/display_layers.h"
#include "main/group_params.h"
#include "main/oam_buffer.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/player_storage.h"
#include "main/pockets.h"
#include "main/sliding_window.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"
#include "ov094/pockets_common.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(StorageScene, layer_task) == 0x94, "layer task");
static_assert(offsetof(StorageScene, grid) == 0xcc && offsetof(StorageScene, letters) == 0xb2c, "grid");
static_assert(offsetof(StorageScene, wallet) == 0xb54 && offsetof(StorageScene, popup) == 0x218c, "wallet");
static_assert(offsetof(StorageScene, glide) == 0x225c && offsetof(StorageScene, cursor_sprite) == 0x2274, "glide");
static_assert(offsetof(StorageScene, error) == 0x22d8 && offsetof(StorageScene, labels) == 0x23f4, "error");
static_assert(offsetof(StorageScene, flags) == 0x24cc && offsetof(StorageScene, held_x) == 0x24e0, "flags");
static_assert(offsetof(StorageScene, storage) == 0x24e8 && offsetof(StorageScene, held_item) == 0x259c, "storage");
static_assert(offsetof(StorageScene, held_kind) == 0x259f && offsetof(StorageScene, home) == 0x25a2, "held");
static_assert(offsetof(StorageScene, cursor) == 0x25a5 && offsetof(StorageScene, page) == 0x25aa, "cursor");
static_assert(sizeof(StorageScene) == 0x25ac, "size (func_ov102_0229e8b0)");

/* The item code of no item (main/item_code.h), and the state PlaceItemState answers for a place
 * outside the grid. */
#define STORAGE_NO_ITEM 0xfff1
#define STORAGE_NO_ITEM_STATE 0xf1

/* What the grid's object answers for no place under the touch. */
#define STORAGE_GRID_NO_PLACE 0x23

/* The pad (autoload_2/input.h): R and L turn the page. */
extern PadState data_021fbe40;
#define STORAGE_PAD_A 0x0001
#define STORAGE_PAD_B 0x0002
#define STORAGE_PAD_X 0x0008
#define STORAGE_PAD_R 0x0100
#define STORAGE_PAD_L 0x0200
#define STORAGE_PAD_Y 0x0800

/* The touch (main's bytes, as ov099's pockets_view.c reads them) and the pen (as menu_scene.c
 * reads it). */
extern u8 data_021f6c58, data_021f6c54, data_021f6c60, data_021f6c5c;
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */

/* The heap the scenes load into (autoload_2/heap.c). */
extern Heap *data_021fbe94;

/* The scene's vtable, the sound of each page (0x1e-0x23), the OBJs of the six tabs (three each),
 * and the files: "menu/inventory/ten%d.bpl", "menu/inventory/b_itm_bg_tra0.bsc" and
 * "menu/inventory/b_itm_chest.bch". */
extern const u8 data_ov102_0229ea60[];
extern const u16 data_ov102_0229e95c[STORAGE_SCENE_PAGES];
extern const OamEntry data_ov102_0229eac0[STORAGE_SCENE_PAGES * STORAGE_SCENE_TAB_OBJS];
extern const char data_ov102_0229eb50[];
extern const char data_ov102_0229eb6c[];
extern const char data_ov102_0229eb90[];

/* The labels' destructor and constructor (handed to __cxa_vec_cleanup and __cxa_vec_ctor, so
 * the game's symbols). */
extern void func_02070c08(void *label);
extern void func_02070be8(void *label);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The SDK's copy (the source first). */
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The sounds of the scene (main/sound.h). */
#define STORAGE_SOUND_CLOSE 0x27

/* The title label: style 4, at (0x1d6, 6), colour 15 when highlighted (else 1) and 9, message
 * 0x88 of the menu's messages. */
#define STORAGE_TITLE_STYLE 4
#define STORAGE_TITLE_X 0x1d6
#define STORAGE_TITLE_Y 6
#define STORAGE_TITLE_MESSAGE 0x88

/* The close button's touch area. */
#define STORAGE_CLOSE_MIN_X 0xc8
#define STORAGE_CLOSE_MAX_X 0xf8
#define STORAGE_CLOSE_MIN_Y 0x68
#define STORAGE_CLOSE_MAX_Y 0x78

/* The frames before the wipe out after a close with a delay, and before a turned page wipes in. */
#define STORAGE_CLOSE_DELAY 5
#define STORAGE_PAGE_DELAY 4

/* The cursor sprite's animations beyond glide.h's names. */
#define STORAGE_ANIM_PUT_DOWN 5
#define STORAGE_ANIM_SWAP 6

static MenuScene *storage_base(StorageScene *self)
{
    return &self->base;
}

static CellLayerSprite *storage_cursor_cells(StorageScene *self)
{
    /* The cursor sprite's base is main's cell layer sprite (glide.h). */
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

static SlidingWindow *storage_popup_window(StorageScene *self)
{
    /* The popup's base is main's sliding window (popup.h). */
    return (SlidingWindow *) (void *) &self->popup;
}

static Process *storage_parent(StorageScene *self)
{
    return Process_GetParent((Process *) (void *) self);
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void storage_update_cursor_sprite(StorageScene *self)
{
    Glider *sprite = &self->cursor_sprite;
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* The place is one of the grid's: a pocket or a place of the page. */
static int storage_is_grid_place(StorageScene *self, int place)
{
    return StorageScene_IsPocketPlace(self, (unsigned int) place) != 0 ||
           StorageScene_IsBoxPlace(self, (unsigned int) place) != 0;
}

/* The members' destructors, last member first, then the base's. */
static void storage_destroy_members(StorageScene *self)
{
    self->base.vtable = data_ov102_0229ea60;
    __cxa_vec_cleanup(self->labels, STORAGE_SCENE_LABELS, sizeof(TextLabel), func_02070be8);
    ErrorMessage_Destruct(&self->error);
    Glider0_Destroy(&self->cursor_sprite);
    Glide_Destroy(&self->glide);
    Popup_Destroy(&self->popup);
    PocketsWallet_Destruct(&self->wallet);
    PocketsLetters_Destruct(&self->letters);
    PocketsGrid_Destruct(&self->grid);
    MenuScene_DestroyBase(storage_base(self));
}

/* func_ov102_0229c180 (vtable slot 0x40) */
StorageScene *StorageScene_Destroy(StorageScene *self)
{
    storage_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov102_0229c180, StorageScene_Destroy)

/* func_ov102_0229c200 (vtable slot 0x44) */
StorageScene *StorageScene_Delete(StorageScene *self)
{
    storage_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov102_0229c200, StorageScene_Delete)

/* func_ov102_0229c288 */
void StorageScene_ClearFlags(StorageScene *self, unsigned int flags)
{
    self->flags &= ~flags;
}
CLEAN_AS(func_ov102_0229c288, StorageScene_ClearFlags)

/* func_ov102_0229c298 */
void StorageScene_SetFlags(StorageScene *self, unsigned int flags)
{
    self->flags |= flags;
}
CLEAN_AS(func_ov102_0229c298, StorageScene_SetFlags)

/* func_ov102_0229c2a8: 1 when any of `flags` is set. */
int StorageScene_TestFlags(StorageScene *self, unsigned int flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov102_0229c2a8, StorageScene_TestFlags)

/* func_ov102_0229c2c0: L shows the page before, R the page after (L first when both), wrapping
 * around the six pages (StorageScene_ShowPage). Always 0. */
int StorageScene_TurnPageByKeys(StorageScene *self)
{
    int step = 0;
    u16 pressed = data_021fbe40.pressed;

    if (pressed & STORAGE_PAD_L) {
        step = -1;
    } else if (pressed & STORAGE_PAD_R) {
        step = 1;
    }
    if (step != 0) {
        int page = step + self->page;
        if (page < 0) {
            page = STORAGE_SCENE_PAGES - 1;
        } else if (page >= STORAGE_SCENE_PAGES) {
            page = 0;
        }
        self->page = (u8) page;
        StorageScene_ShowPage(self);
    }
    return 0;
}
CLEAN_AS(func_ov102_0229c2c0, StorageScene_TurnPageByKeys)

/* func_ov102_0229c318: the page shown changes: the popup and the cursor sprite hidden, state 7
 * (written directly, not through MenuScene_SetState) in phase 1, the page's sound, the held item
 * hidden. */
void StorageScene_ShowPage(StorageScene *self)
{
    Popup_Hide(&self->popup, 1);
    StorageScene_HideCursorSprite(self);
    self->base.state = STORAGE_SCENE_STATE_TURN_PAGE;
    MenuScene_SetPhase(storage_base(self), STORAGE_SCENE_PHASE_STATES);
    SoundSys_PlaySe(data_ov102_0229e95c[self->page]);
    StorageScene_SetFlags(self, STORAGE_SCENE_FLAG_HELD_HIDDEN);
}
CLEAN_AS(func_ov102_0229c318, StorageScene_ShowPage)

/* func_ov102_0229c364: the touch at (x, y) on the tab of a page not shown (its first OBJ, drawn
 * at 0x80, 0x60, with 2 pixels of margin) makes that page the one shown; 1 then, else 0. */
int StorageScene_TabAtTouch(StorageScene *self, int x, int y)
{
    int dx = x - 0x80;
    int dy = y - 0x60;

    for (int i = 0; i < STORAGE_SCENE_PAGES; i++) {
        if (i != self->page && OamBuffer_ObjContains(&data_ov102_0229eac0[i * STORAGE_SCENE_TAB_OBJS], dx, dy, 2, 2) != 0) {
            self->page = (u8) i;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov102_0229c364, StorageScene_TabAtTouch)

/* func_ov102_0229c3bc: the six tabs drawn on the touch screen at x 0x80 and 0x60 below the page's
 * wipe y: the shown page's first two OBJs 2 pixels lower and its second in palette 4 (5 for the
 * others). */
void StorageScene_DrawTabs(StorageScene *self)
{
    int y = (int) ((u32) self->page_y + 0x60);

    for (int i = 0; i < STORAGE_SCENE_PAGES; i++) {
        const OamEntry *objs = &data_ov102_0229eac0[i * STORAGE_SCENE_TAB_OBJS];
        int tab_y;
        int palette;
        if (i == self->page) {
            tab_y = (int) ((u32) y + 2);
            palette = 4;
        } else {
            tab_y = y;
            palette = 5;
        }
        OamBuffer_DrawObjAffine(1, &objs[0], 0x80, tab_y, -1, 1, NULL);
        OamBuffer_DrawObjAffine(1, &objs[1], 0x80, tab_y, palette, 1, NULL);
        OamBuffer_DrawObjAffine(1, &objs[2], 0x80, y, -1, 1, NULL);
    }
}
CLEAN_AS(func_ov102_0229c3bc, StorageScene_DrawTabs)

/* func_ov102_0229c460: the scene closes: sound 0x27, a delay of 5 frames (or none) before the
 * wipe out (sub state 0x0f), the title highlighted, main told the storage changed
 * (GroupParams_SetC4C(1), always) and the scene's 90 items copied back to the current player's
 * storage. */
void StorageScene_SaveAndClose(StorageScene *self, int with_delay)
{
    SoundSys_PlaySe(STORAGE_SOUND_CLOSE);
    self->delay = with_delay ? STORAGE_CLOSE_DELAY : 0;
    MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_CLOSE_DELAY);
    StorageScene_ShowTitle(self, 1);
    GroupParams_SetC4C(1);
    u16 *items = PlayerStorage_Items(PlayerRecord_Storage(PlayerRecords_Current()));
    MI_CpuCopy8(self->storage, items, sizeof(self->storage));
}
CLEAN_AS(func_ov102_0229c460, StorageScene_SaveAndClose)

/* func_ov102_0229c4c0: the title shown this frame in the next label: style 4 at (0x1d6, 6) in
 * colours 15 (highlighted) or 1 and 9, message 0x88. */
void StorageScene_ShowTitle(StorageScene *self, int highlighted)
{
    int color = highlighted ? 15 : 1;
    TextLabel *label = StorageScene_NextLabel(self);
    TextLabel_OpenStyledBox2(label, STORAGE_TITLE_STYLE, STORAGE_TITLE_X, STORAGE_TITLE_Y, (u8) color, 9, 0);
    TextLabel_LoadMenuMessage((int) (uintptr_t) label, (char) STORAGE_TITLE_MESSAGE);
    TextLabel_Show(label, 1, 1);
}
CLEAN_AS(func_ov102_0229c4c0, StorageScene_ShowTitle)

/* func_ov102_0229c504: the next of the two labels this frame; once both are used, the second
 * again. */
TextLabel *StorageScene_NextLabel(StorageScene *self)
{
    if (self->labels_used >= STORAGE_SCENE_LABELS) {
        return &self->labels[STORAGE_SCENE_LABELS - 1];
    }
    self->labels_used++;
    return &self->labels[self->labels_used - 1];
}
CLEAN_AS(func_ov102_0229c504, StorageScene_NextLabel)

/* func_ov102_0229c534: no label used, both labels' boxes closed. */
void StorageScene_CloseLabels(StorageScene *self)
{
    self->labels_used = 0;
    for (int i = 0; i < STORAGE_SCENE_LABELS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
}
CLEAN_AS(func_ov102_0229c534, StorageScene_CloseLabels)

/* func_ov102_0229c560: the cursor moved by the repeated d-pad keys `keys` (the wrap and close
 * turn flags of the last move cleared first), `holding` (1) while an item is held; whether it
 * moved. With an item held, the cursor sprite shows animation 1 on reaching a tab from the page
 * and animation 4 (at its end) on leaving the tabs. When the move takes it onto the close button
 * the cursor sprite turns to its set B, off it to its set A (STORAGE_SCENE_FLAG_CLOSE_TURN). */
int StorageScene_MoveCursor(StorageScene *self, int keys, int holding)
{
    u8 before = self->cursor;

    StorageScene_ClearFlags(self, STORAGE_SCENE_FLAGS_WRAPPED);
    StorageScene_ClearFlags(self, STORAGE_SCENE_FLAG_CLOSE_TURN);
    if (keys == 0) {
        return 0;
    }

    if (StorageScene_IsPocketPlace(self, self->cursor)) {
        StorageScene_MoveCursorInPockets(self, keys, holding);
    } else if (StorageScene_IsBoxPlace(self, self->cursor)) {
        StorageScene_MoveCursorInBox(self, keys, holding);
        if (holding == 1 && StorageScene_IsTabPlace(self, self->cursor)) {
            Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
        }
    } else if (StorageScene_IsClosePlace(self, self->cursor)) {
        StorageScene_MoveCursorFromClose(self, keys);
    } else if (StorageScene_IsTabPlace(self, self->cursor)) {
        StorageScene_MoveCursorInTabs(self, keys, holding);
        if (holding == 1 && !StorageScene_IsTabPlace(self, self->cursor)) {
            CellLayerSprite_SetAnimAtEnd(storage_cursor_cells(self), GLIDER_ANIM_TURN_A);
        }
    }

    int on_close = StorageScene_IsClosePlace(self, self->cursor);
    if (on_close != StorageScene_IsClosePlace(self, before)) {
        if (StorageScene_IsClosePlace(self, self->cursor)) {
            Glider_TurnToSetB(&self->cursor_sprite);
        } else {
            Glider_TurnToSetA(&self->cursor_sprite);
        }
        StorageScene_SetFlags(self, STORAGE_SCENE_FLAG_CLOSE_TURN);
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov102_0229c560, StorageScene_MoveCursor)

/* func_ov102_0229c684: the cursor moved among the tabs (2 rows of 3). Right from the last column
 * goes to the first place of the page's row (saying so in the flags), left from the first column
 * to the last place of the page's row; either ends the move. Else up and down move one row; down
 * from the second row goes to the close button unless an item is held.
 * QUIRK: left onto the page sets no wrap flag, unlike right. */
void StorageScene_MoveCursorInTabs(StorageScene *self, int keys, int holding)
{
    int column = self->cursor - STORAGE_SCENE_TAB_FIRST;
    int row = 0;
    while (column >= STORAGE_SCENE_TAB_COLUMNS) {
        column -= STORAGE_SCENE_TAB_COLUMNS;
        row++;
    }

    if (KeyRepeat_HasRight(keys)) {
        if (column < STORAGE_SCENE_TAB_COLUMNS - 1) {
            self->cursor++;
        } else {
            StorageScene_SetFlags(self, STORAGE_SCENE_FLAG_WRAPPED_RIGHT);
            self->cursor = (u8) (STORAGE_SCENE_COLUMNS * row + STORAGE_SCENE_BOX_FIRST);
            return;
        }
    } else if (KeyRepeat_HasLeft(keys)) {
        if (column > 0) {
            self->cursor--;
        } else {
            self->cursor = (u8) (STORAGE_SCENE_COLUMNS * row + STORAGE_SCENE_BOX_FIRST + STORAGE_SCENE_COLUMNS - 1);
            return;
        }
    }

    if (KeyRepeat_HasUp(keys)) {
        if (row > 0) {
            self->cursor -= STORAGE_SCENE_TAB_COLUMNS;
        }
    } else if (KeyRepeat_HasDown(keys)) {
        if (row < 1) {
            self->cursor += STORAGE_SCENE_TAB_COLUMNS;
        } else if (holding != 1) {
            self->cursor = STORAGE_SCENE_CLOSE;
        }
    }
}
CLEAN_AS(func_ov102_0229c684, StorageScene_MoveCursorInTabs)

/* func_ov102_0229c740: the cursor moved from the close button: up to the first tab of the second
 * row; then right to the first pocket (saying it wrapped right) or else left to the last pocket
 * of the first row. */
void StorageScene_MoveCursorFromClose(StorageScene *self, int keys)
{
    if (KeyRepeat_HasUp(keys)) {
        self->cursor = STORAGE_SCENE_TAB_FIRST + STORAGE_SCENE_TAB_COLUMNS;
    }
    if (KeyRepeat_HasRight(keys)) {
        self->cursor = STORAGE_SCENE_POCKET_FIRST;
        StorageScene_SetFlags(self, STORAGE_SCENE_FLAG_WRAPPED_RIGHT);
    } else if (KeyRepeat_HasLeft(keys)) {
        self->cursor = STORAGE_SCENE_POCKET_FIRST + STORAGE_SCENE_COLUMNS - 1;
    }
}
CLEAN_AS(func_ov102_0229c740, StorageScene_MoveCursorFromClose)

/* func_ov102_0229c790: the cursor moved in the page (3 rows of 5). Left from the first column
 * goes to the last tab of the first or the second row, from the third row to the last place of
 * the row with an item held (else the close button), saying it wrapped left; right from the last
 * column goes to the first tab of the first or second row, from the third row to the first place
 * of the row (saying it wrapped right) with an item held, else the close button. Either of these
 * ends the move. Unless it did, up and down move one row; down from the third row goes to the
 * pockets' first row.
 * QUIRK: left is ignored when up is held too and the cursor is below the first row; right is
 * ignored whenever down is held too. */
void StorageScene_MoveCursorInBox(StorageScene *self, int keys, int holding)
{
    int column = self->cursor - STORAGE_SCENE_BOX_FIRST;
    int row = 0;
    while (column >= STORAGE_SCENE_COLUMNS) {
        column -= STORAGE_SCENE_COLUMNS;
        row++;
    }

    if (KeyRepeat_HasLeft(keys)) {
        if (!(KeyRepeat_HasUp(keys) && row != 0)) {
            if (column == 0) {
                switch (row) {
                    case 0:
                        self->cursor = STORAGE_SCENE_TAB_FIRST + STORAGE_SCENE_TAB_COLUMNS - 1;
                        break;
                    case 1:
                        self->cursor = STORAGE_SCENE_TAB_LAST;
                        break;
                    default:
                        if (holding == 1) {
                            self->cursor += STORAGE_SCENE_COLUMNS - 1;
                        } else {
                            self->cursor = STORAGE_SCENE_CLOSE;
                        }
                        break;
                }
                StorageScene_SetFlags(self, STORAGE_SCENE_FLAG_WRAPPED_LEFT);
                return;
            }
            self->cursor--;
            column--;
        }
    } else if (KeyRepeat_HasRight(keys) && !KeyRepeat_HasDown(keys)) {
        if (column == STORAGE_SCENE_COLUMNS - 1) {
            switch (row) {
                case 0:
                    self->cursor = STORAGE_SCENE_TAB_FIRST;
                    return;
                case 1:
                    self->cursor = STORAGE_SCENE_TAB_FIRST + STORAGE_SCENE_TAB_COLUMNS;
                    return;
                default:
                    if (holding == 1) {
                        self->cursor -= STORAGE_SCENE_COLUMNS - 1;
                        StorageScene_SetFlags(self, STORAGE_SCENE_FLAG_WRAPPED_RIGHT);
                    } else {
                        self->cursor = STORAGE_SCENE_CLOSE;
                    }
                    return;
            }
        }
        self->cursor++;
        column++;
    }

    if (KeyRepeat_HasUp(keys)) {
        if (row > 0) {
            self->cursor -= STORAGE_SCENE_COLUMNS;
        }
        return;
    }
    if (KeyRepeat_HasDown(keys)) {
        if (row < STORAGE_SCENE_ROWS - 1) {
            self->cursor += STORAGE_SCENE_COLUMNS;
        } else {
            self->cursor = (u8) column;
        }
    }
}
CLEAN_AS(func_ov102_0229c790, StorageScene_MoveCursorInBox)

/* func_ov102_0229c8bc: the cursor moved in the pockets (3 rows of 5). Left from the first column
 * goes to the last place of the row with an item held, else to the close button; right from the
 * last column to the first place of the row with an item held (saying it wrapped right), else to
 * the close button. Either ends the move, left saying it wrapped left. Unless it did, up and down
 * move one row; up from the first row goes to the page's last row.
 * QUIRK: left is ignored when up is held too and the cursor is below the first row; right is
 * ignored whenever down is held too. */
void StorageScene_MoveCursorInPockets(StorageScene *self, int keys, int holding)
{
    int column = self->cursor;
    int row = 0;
    while (column >= STORAGE_SCENE_COLUMNS) {
        column -= STORAGE_SCENE_COLUMNS;
        row++;
    }

    if (KeyRepeat_HasLeft(keys)) {
        if (!(KeyRepeat_HasUp(keys) && row != 0)) {
            if (column == 0) {
                if (holding == 1) {
                    self->cursor += STORAGE_SCENE_COLUMNS - 1;
                } else {
                    self->cursor = STORAGE_SCENE_CLOSE;
                }
                StorageScene_SetFlags(self, STORAGE_SCENE_FLAG_WRAPPED_LEFT);
                return;
            }
            self->cursor--;
            column--;
        }
    } else if (KeyRepeat_HasRight(keys) && !KeyRepeat_HasDown(keys)) {
        if (column == STORAGE_SCENE_COLUMNS - 1) {
            if (holding == 1) {
                self->cursor -= STORAGE_SCENE_COLUMNS - 1;
                StorageScene_SetFlags(self, STORAGE_SCENE_FLAG_WRAPPED_RIGHT);
            } else {
                self->cursor = STORAGE_SCENE_CLOSE;
            }
            return;
        }
        self->cursor++;
        column++;
    }

    if (KeyRepeat_HasUp(keys)) {
        if (row > 0) {
            self->cursor -= STORAGE_SCENE_COLUMNS;
        } else {
            self->cursor = (u8) (column + STORAGE_SCENE_BOX_FIRST + (STORAGE_SCENE_ROWS - 1) * STORAGE_SCENE_COLUMNS);
        }
        return;
    }
    if (KeyRepeat_HasDown(keys) && row < STORAGE_SCENE_ROWS - 1) {
        self->cursor += STORAGE_SCENE_COLUMNS;
    }
}
CLEAN_AS(func_ov102_0229c8bc, StorageScene_MoveCursorInPockets)

/* func_ov102_0229c9b0: a swap of the held item with `place`'s begins: the popup hidden, the sub
 * state kept, the cursor sprite's animation 6, sub state 0x0b. */
void StorageScene_StartSwap(StorageScene *self, int place)
{
    Popup_Hide(&self->popup, 1);
    self->return_state = self->base.sub_state;
    self->target = (u8) place;
    Glider_SetAnim(&self->cursor_sprite, STORAGE_ANIM_SWAP);
    MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_SWAP);
}
CLEAN_AS(func_ov102_0229c9b0, StorageScene_StartSwap)

/* func_ov102_0229c9fc: the held item is put down on `place`: the popup hidden, the cursor
 * sprite's animation 5, sub state 0x0a. */
void StorageScene_StartPutDown(StorageScene *self, u8 place)
{
    Popup_Hide(&self->popup, 1);
    self->target = place;
    Glider_SetAnim(&self->cursor_sprite, STORAGE_ANIM_PUT_DOWN);
    MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_PUT_DOWN);
}
CLEAN_AS(func_ov102_0229c9fc, StorageScene_StartPutDown)

/* func_ov102_0229ca38: the cursor sprite's animation 4, sub state 8, which picks up the cursor's
 * item once its turn has settled. */
void StorageScene_StartPickUp(StorageScene *self)
{
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_TURN_A);
    MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_PICK_UP);
}
CLEAN_AS(func_ov102_0229ca38, StorageScene_StartPickUp)

/* func_ov102_0229ca58: the third animation of the cursor sprite's set, sub state 7. */
void StorageScene_StartPressAnim(StorageScene *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_PRESS_END);
}
CLEAN_AS(func_ov102_0229ca58, StorageScene_StartPressAnim)

/* func_ov102_0229ca78: the second animation of the cursor sprite's set (a press on a tab or the
 * close button), sub state 6. */
void StorageScene_StartButtonPress(StorageScene *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_BUTTON_PRESS);
}
CLEAN_AS(func_ov102_0229ca78, StorageScene_StartButtonPress)

/* func_ov102_0229ca98: the first animation of the cursor sprite's set, then its update. */
void StorageScene_ShowCursorFirstOfSet(StorageScene *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    storage_update_cursor_sprite(self);
}
CLEAN_AS(func_ov102_0229ca98, StorageScene_ShowCursorFirstOfSet)

/* func_ov102_0229cab8: the cursor sprite follows the cursor: put there at once when
 * STORAGE_SCENE_FLAG_JUMP is set (which is then cleared), else eased there in 3 steps (cue 1)
 * with the sub state kept and sub state 5 waiting for the move; after a turn onto or off the
 * close button the sprite is updated at once. */
void StorageScene_GlideToCursor(StorageScene *self)
{
    if (StorageScene_TestFlags(self, STORAGE_SCENE_FLAG_JUMP)) {
        int x = StorageScene_CursorSpriteX(self);
        int y = StorageScene_CursorSpriteY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
        StorageScene_ClearFlags(self, STORAGE_SCENE_FLAG_JUMP);
        return;
    }
    int x = StorageScene_CursorSpriteX(self);
    int y = StorageScene_CursorSpriteY(self);
    Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_SPRITE_MOVE);
    if (StorageScene_TestFlags(self, STORAGE_SCENE_FLAG_CLOSE_TURN)) {
        storage_update_cursor_sprite(self);
        StorageScene_ClearFlags(self, STORAGE_SCENE_FLAG_CLOSE_TURN);
    }
}
CLEAN_AS(func_ov102_0229cab8, StorageScene_GlideToCursor)

/* func_ov102_0229cb50: the cursor sprite's animation 0, then its update. */
void StorageScene_HideCursorSprite(StorageScene *self)
{
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_NONE);
    storage_update_cursor_sprite(self);
}
CLEAN_AS(func_ov102_0229cb50, StorageScene_HideCursorSprite)

/* func_ov102_0229cb74: the cursor sprite's y, the cursor's place's. */
int StorageScene_CursorSpriteY(StorageScene *self)
{
    return StorageScene_PlaceY(self, self->cursor);
}
CLEAN_AS(func_ov102_0229cb74, StorageScene_CursorSpriteY)

/* func_ov102_0229cb84: the cursor sprite's x: the cursor's place's plus 8, and a screen width
 * (256) further right or left when this move wrapped right or left. */
int StorageScene_CursorSpriteX(StorageScene *self)
{
    int x = StorageScene_PlaceX(self, self->cursor);
    if (StorageScene_TestFlags(self, STORAGE_SCENE_FLAG_WRAPPED_RIGHT)) {
        x += 0x100;
    } else if (StorageScene_TestFlags(self, STORAGE_SCENE_FLAG_WRAPPED_LEFT)) {
        x -= 0x100;
    }
    return x + 8;
}
CLEAN_AS(func_ov102_0229cb84, StorageScene_CursorSpriteX)

/* func_ov102_0229cbcc: the cursor sprite put at the cursor, animation 7 on the close button
 * (else 1), then the first of its set. */
void StorageScene_ShowCursorSprite(StorageScene *self)
{
    int x = StorageScene_CursorSpriteX(self);
    int y = StorageScene_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (StorageScene_IsClosePlace(self, self->cursor)) {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_B);
    } else {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
    }
    StorageScene_ShowCursorFirstOfSet(self);
}
CLEAN_AS(func_ov102_0229cbcc, StorageScene_ShowCursorSprite)

/* func_ov102_0229cc24: when an item is held, the item at `place` is picked up and the one held
 * before put there. */
void StorageScene_SwapHeldWith(StorageScene *self, int place)
{
    if (self->held_kind == STORAGE_SCENE_HELD_ITEM) {
        u16 item = self->held_item;
        u8 state = self->held_state;
        StorageScene_PickUpItem(self, (unsigned int) place);
        StorageScene_SetPlaceItem(self, (unsigned int) place, item, state);
    }
}
CLEAN_AS(func_ov102_0229cc24, StorageScene_SwapHeldWith)

/* func_ov102_0229cc60: the held item (if any) put at `place`; nothing is held after. */
void StorageScene_PutHeldAt(StorageScene *self, int place)
{
    if (self->held_kind == STORAGE_SCENE_HELD_ITEM) {
        StorageScene_SetPlaceItem(self, (unsigned int) place, self->held_item, self->held_state);
    }
    self->held_kind = STORAGE_SCENE_HELD_NONE;
}
CLEAN_AS(func_ov102_0229cc60, StorageScene_PutHeldAt)

/* func_ov102_0229cc90: the item of grid place `place` taken from it and held, its sprite given
 * to the grid's object; nothing for other places. */
void StorageScene_PickUpItem(StorageScene *self, unsigned int place)
{
    if (storage_is_grid_place(self, (int) place)) {
        int index = StorageScene_GridPlace(self, (int) place);
        self->held_kind = STORAGE_SCENE_HELD_ITEM;
        self->held_item = PocketsGrid_Item(&self->grid, index);
        self->held_state = PocketsGrid_ItemState(&self->grid, index);
        PocketsGrid_EmptyPlace(&self->grid, index);
        PocketsGrid_SetHeldIcon(&self->grid, self->held_item, self->held_state);
    }
}
CLEAN_AS(func_ov102_0229cc90, StorageScene_PickUpItem)

/* func_ov102_0229cd08: the held item drawn where the glide is. */
void StorageScene_FollowGlide(StorageScene *self)
{
    self->held_x = Glide_X(&self->glide);
    self->held_y = Glide_Y(&self->glide);
}
CLEAN_AS(func_ov102_0229cd08, StorageScene_FollowGlide)

/* func_ov102_0229cd38: the held item drawn at the cursor sprite's frame, 2 left and 4 up, and
 * 22 more up while the sprite shows animation 1. */
void StorageScene_FollowCursorSprite(StorageScene *self)
{
    self->held_x = Glider_FrameX(&self->cursor_sprite) - 2;
    self->held_y = Glider_FrameY(&self->cursor_sprite) - 4;
    if (CellLayerSprite_AnimNumber(storage_cursor_cells(self)) == GLIDER_ANIM_SET_A) {
        self->held_y -= 22;
    }
}
CLEAN_AS(func_ov102_0229cd38, StorageScene_FollowCursorSprite)

/* func_ov102_0229cd80: the held item drawn at the touch, kept at the offset it was grabbed at.
 * QUIRK: the sums wrap at 32 bits (done unsigned, as the ROM's code does). */
void StorageScene_FollowTouch(StorageScene *self)
{
    self->held_x = (s32) ((u32) self->grab_dx + data_021f6c58);
    self->held_y = (s32) ((u32) self->grab_dy + data_021f6c54);
}
CLEAN_AS(func_ov102_0229cd80, StorageScene_FollowTouch)

/* func_ov102_0229cdb8: the held item drawn by the grid's object, unless it is hidden. */
void StorageScene_DrawHeld(StorageScene *self)
{
    if (StorageScene_TestFlags(self, STORAGE_SCENE_FLAG_HELD_HIDDEN)) {
        return;
    }
    if (self->held_kind == STORAGE_SCENE_HELD_ITEM) {
        PocketsGrid_DrawHeld(&self->grid, self->held_x, self->held_y);
    }
}
CLEAN_AS(func_ov102_0229cdb8, StorageScene_DrawHeld)

/* func_ov102_0229cdf4: the popup tells of the cursor's place: queued for a grid place that holds
 * an item (kept as `popup_place`), its queue cleared for an empty one or another place. */
void StorageScene_UpdatePopup(StorageScene *self)
{
    if (storage_is_grid_place(self, self->cursor) && !StorageScene_PlaceIsEmpty(self, self->cursor)) {
        self->popup_place = self->cursor;
        Popup_Queue(&self->popup);
    } else {
        Popup_ClearQueued(&self->popup);
    }
}
CLEAN_AS(func_ov102_0229cdf4, StorageScene_UpdatePopup)

/* func_ov102_0229ce58: the popup put above its place (0x6d left and 0x78 up of it, 8 more up
 * when state flag 2 is set); when that is above y -92 it slides the other way, 0x50 above the
 * place. For a grid place the grid's object gives it the item's text. */
void StorageScene_PlacePopup(StorageScene *self)
{
    int x = StorageScene_PlaceX(self, self->popup_place) - 0x6d;
    int y = StorageScene_PlaceY(self, self->popup_place) - 0x78;
    if (StateFlags_Test2()) {
        y -= 8;
    }
    if (y < -92) {
        SlidingWindow_SetSlideFlip(storage_popup_window(self));
        y = StorageScene_PlaceY(self, self->popup_place) - 0x50;
    } else {
        SlidingWindow_ClearSlideFlip(storage_popup_window(self));
    }
    SlidingWindow_SetPlace(storage_popup_window(self), x, y);
    if (storage_is_grid_place(self, self->popup_place)) {
        PocketsGrid_ShowItemText(&self->grid, &self->popup, StorageScene_GridPlace(self, self->popup_place));
    }
}
CLEAN_AS(func_ov102_0229ce58, StorageScene_PlacePopup)

/* The distance between two coordinates. */
static int storage_distance(int a, int b)
{
    return a > b ? a - b : b - a;
}

/* func_ov102_0229cef8: whether the touch at data_021f6c60/5c is more than 8 pixels from the one
 * at data_021f6c58/54, in x or in y. */
int StorageScene_TouchMoved(StorageScene *self)
{
    (void) self;
    return storage_distance(data_021f6c60, data_021f6c58) > 8 || storage_distance(data_021f6c5c, data_021f6c54) > 8;
}
CLEAN_AS(func_ov102_0229cef8, StorageScene_TouchMoved)

/* func_ov102_0229cf3c: a grid place marked in the grid's object. */
void StorageScene_HighlightPlace(StorageScene *self, unsigned int place)
{
    if (storage_is_grid_place(self, (int) place)) {
        PocketsGrid_MarkPlace(&self->grid, StorageScene_GridPlace(self, (int) place));
    }
}
CLEAN_AS(func_ov102_0229cf3c, StorageScene_HighlightPlace)

/* func_ov102_0229cf74: no place marked in the grid's or the letters' object. */
void StorageScene_ClearHighlights(StorageScene *self)
{
    PocketsGrid_ClearMarks(&self->grid);
    PocketsLetters_ClearMarks(&self->letters);
}
CLEAN_AS(func_ov102_0229cf74, StorageScene_ClearHighlights)

/* func_ov102_0229cf90: a grid place lifted in the grid's object (the letters' lift cleared); for
 * other places both cleared. */
void StorageScene_SelectPlace(StorageScene *self, unsigned int place)
{
    if (storage_is_grid_place(self, (int) place)) {
        PocketsGrid_Lift(&self->grid, StorageScene_GridPlace(self, (int) place));
        PocketsLetters_Unlift(&self->letters);
    } else {
        StorageScene_ClearSelection(self);
    }
}
CLEAN_AS(func_ov102_0229cf90, StorageScene_SelectPlace)

/* func_ov102_0229cfdc */
void StorageScene_ClearSelection(StorageScene *self)
{
    PocketsGrid_Unlift(&self->grid);
    PocketsLetters_Unlift(&self->letters);
}
CLEAN_AS(func_ov102_0229cfdc, StorageScene_ClearSelection)

/* func_ov102_0229cff8: the state of the item at grid place `place`, else 0xf1. */
int StorageScene_PlaceItemState(StorageScene *self, int place)
{
    if (storage_is_grid_place(self, place)) {
        return PocketsGrid_ItemState(&self->grid, StorageScene_GridPlace(self, place));
    }
    return STORAGE_NO_ITEM_STATE;
}
CLEAN_AS(func_ov102_0229cff8, StorageScene_PlaceItemState)

/* func_ov102_0229d034: the item at grid place `place`, else none (0xfff1). */
int StorageScene_PlaceItem(StorageScene *self, int place)
{
    if (storage_is_grid_place(self, place)) {
        return PocketsGrid_Item(&self->grid, StorageScene_GridPlace(self, place));
    }
    return STORAGE_NO_ITEM;
}
CLEAN_AS(func_ov102_0229d034, StorageScene_PlaceItem)

/* func_ov102_0229d074: whether grid place `place` is empty; other places count as empty. */
int StorageScene_PlaceIsEmpty(StorageScene *self, int place)
{
    if (storage_is_grid_place(self, place)) {
        return PocketsGrid_IsEmpty(&self->grid, StorageScene_GridPlace(self, place));
    }
    return 1;
}
CLEAN_AS(func_ov102_0229d074, StorageScene_PlaceIsEmpty)

/* func_ov102_0229d0b0: whether grid place `place` is dimmed; other places are not. */
int StorageScene_PlaceIsDimmed(StorageScene *self, int place)
{
    if (storage_is_grid_place(self, place)) {
        return PocketsGrid_IsDimmed(&self->grid, StorageScene_GridPlace(self, place));
    }
    return 0;
}
CLEAN_AS(func_ov102_0229d0b0, StorageScene_PlaceIsDimmed)

/* func_ov102_0229d0ec: the pockets whose items cannot be stored dimmed. */
void StorageScene_DimUnstorable(StorageScene *self)
{
    for (int place = STORAGE_SCENE_POCKET_FIRST; place <= STORAGE_SCENE_POCKET_LAST; place++) {
        if (StorageScene_CannotStore(self, place)) {
            PocketsGrid_DimPlace(&self->grid, StorageScene_GridPlace(self, place));
        }
    }
}
CLEAN_AS(func_ov102_0229d0ec, StorageScene_DimUnstorable)

/* func_ov102_0229d124: whether the item at `place` cannot be stored: not for an empty place; yes
 * for an item in a state (not 0), one in the ranges letters refuse
 * (PocketsItem_InLetterRefusedRanges) and item 0x155d. */
int StorageScene_CannotStore(StorageScene *self, int place)
{
    if (StorageScene_PlaceIsEmpty(self, place)) {
        return 0;
    }
    if (StorageScene_PlaceItemState(self, place)) {
        return 1;
    }
    int item = StorageScene_PlaceItem(self, place);
    if (PocketsItem_InLetterRefusedRanges((unsigned int) item)) {
        return 1;
    }
    if (PocketsItem_Is155d((u16) item)) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov102_0229d124, StorageScene_CannotStore)

/* The OBJs of the tab of place `place`. */
static const OamEntry *storage_tab_obj(int place)
{
    return &data_ov102_0229eac0[(place - STORAGE_SCENE_TAB_FIRST) * STORAGE_SCENE_TAB_OBJS];
}

/* func_ov102_0229d178: the y of `place`: a grid place's by the grid's object, 0x70 for the close
 * button, a tab's first OBJ's plus 0x68; 0 for others. */
int StorageScene_PlaceY(StorageScene *self, int place)
{
    if (storage_is_grid_place(self, place)) {
        return PocketsGrid_PlaceY(&self->grid, StorageScene_GridPlace(self, place));
    }
    if (StorageScene_IsClosePlace(self, place)) {
        return 0x70;
    }
    if (StorageScene_IsTabPlace(self, (unsigned int) place)) {
        return OamBuffer_ObjY(storage_tab_obj(place)) + 0x68;
    }
    return 0;
}
CLEAN_AS(func_ov102_0229d178, StorageScene_PlaceY)

/* func_ov102_0229d1e8: the x of `place`: a grid place's by the grid's object, 0xc4 for the close
 * button, a tab's first OBJ's plus 0x80; 0 for others. */
int StorageScene_PlaceX(StorageScene *self, int place)
{
    if (storage_is_grid_place(self, place)) {
        return PocketsGrid_PlaceX(&self->grid, StorageScene_GridPlace(self, place));
    }
    if (StorageScene_IsClosePlace(self, place)) {
        return 0xc4;
    }
    if (StorageScene_IsTabPlace(self, (unsigned int) place)) {
        return OamBuffer_ObjX(storage_tab_obj(place)) + 0x80;
    }
    return 0;
}
CLEAN_AS(func_ov102_0229d1e8, StorageScene_PlaceX)

/* func_ov102_0229d258: the 15 items of the page shown. */
u16 *StorageScene_PageItems(StorageScene *self)
{
    return &self->storage[self->page * STORAGE_SCENE_PAGE_ITEMS];
}
CLEAN_AS(func_ov102_0229d258, StorageScene_PageItems)

/* func_ov102_0229d274: the place of the grid's page place `index` (15-29: the same number),
 * else STORAGE_SCENE_NO_PLACE. */
unsigned int StorageScene_BoxPlace(StorageScene *self, unsigned int index)
{
    (void) self;
    if (index >= STORAGE_SCENE_BOX_FIRST && index <= STORAGE_SCENE_BOX_LAST) {
        return (u8) index;
    }
    return STORAGE_SCENE_NO_PLACE;
}
CLEAN_AS(func_ov102_0229d274, StorageScene_BoxPlace)

/* func_ov102_0229d288: the grid's place of a page place (the same number), else 15. */
int StorageScene_BoxIndex(StorageScene *self, int place)
{
    if (StorageScene_IsBoxPlace(self, (unsigned int) place)) {
        return (u8) place;
    }
    return STORAGE_SCENE_BOX_FIRST;
}
CLEAN_AS(func_ov102_0229d288, StorageScene_BoxIndex)

/* func_ov102_0229d2a4: `item` in `state` put at `place`: for a grid place by the grid's object
 * (which writes the pocket slot or the page's item) and redrawn; for a tab, into the storage at
 * the place the held item was taken from, on the page it was taken from.
 * REQUIRES: for a tab, `from_place` is a place of the page (15-29); the game writes outside the
 * storage for others. */
void StorageScene_SetPlaceItem(StorageScene *self, unsigned int place, int item, int state)
{
    if (storage_is_grid_place(self, (int) place)) {
        int index = StorageScene_GridPlace(self, (int) place);
        PocketsGrid_SetItem(&self->grid, index, item, state);
        PocketsGrid_RefreshPlace(&self->grid, (unsigned int) index);
    } else if (StorageScene_IsTabPlace(self, place)) {
        int index = self->from_page * STORAGE_SCENE_PAGE_ITEMS + (self->from_place - STORAGE_SCENE_BOX_FIRST);
        self->storage[index] = (u16) item;
    }
}
CLEAN_AS(func_ov102_0229d2a4, StorageScene_SetPlaceItem)

/* func_ov102_0229d320: the held item put down at grid place `place`; an item already there goes
 * to `home`, the place the held one came from. Whether `place` was a grid place. */
int StorageScene_DropHeldAt(StorageScene *self, int place)
{
    if (!storage_is_grid_place(self, place)) {
        return 0;
    }
    int item = StorageScene_PlaceItem(self, place);
    if (item != STORAGE_NO_ITEM) {
        int state = StorageScene_PlaceItemState(self, place);
        StorageScene_SetPlaceItem(self, self->home, item, state);
    }
    StorageScene_PutHeldAt(self, place);
    return 1;
}
CLEAN_AS(func_ov102_0229d320, StorageScene_DropHeldAt)

/* func_ov102_0229d37c: the place under the touch at (x, y): a pocket, else a place of the page,
 * by the grid's object; with `with_item`, only one that holds an item. STORAGE_SCENE_NO_PLACE
 * for none. */
int StorageScene_PlaceAtTouch(StorageScene *self, int x, int y, int with_item)
{
    int index = PocketsGrid_PocketPlaceAtTouch(&self->grid, x, y);
    if (index != STORAGE_GRID_NO_PLACE) {
        if (with_item != 0 && PocketsGrid_IsEmpty(&self->grid, index) != 0) {
            return STORAGE_SCENE_NO_PLACE;
        }
        return StorageScene_PocketPlace(self, (unsigned int) index);
    }
    index = PocketsGrid_BoxPlaceAtTouch(&self->grid, x, y);
    if (index != STORAGE_GRID_NO_PLACE) {
        if (with_item != 0 && PocketsGrid_IsEmpty(&self->grid, index) != 0) {
            return STORAGE_SCENE_NO_PLACE;
        }
        return (int) StorageScene_BoxPlace(self, (unsigned int) index);
    }
    return STORAGE_SCENE_NO_PLACE;
}
CLEAN_AS(func_ov102_0229d37c, StorageScene_PlaceAtTouch)

/* func_ov102_0229d3f0: the place of the grid's pocket `index` (0-14: the same number), else
 * STORAGE_SCENE_NO_PLACE. */
u8 StorageScene_PocketPlace(StorageScene *self, unsigned int index)
{
    (void) self;
    if (index <= STORAGE_SCENE_POCKET_LAST) {
        return (u8) index;
    }
    return STORAGE_SCENE_NO_PLACE;
}
CLEAN_AS(func_ov102_0229d3f0, StorageScene_PocketPlace)

/* func_ov102_0229d400: the grid's place of a pocket or a page place (the same number), else 0. */
int StorageScene_GridPlace(StorageScene *self, int place)
{
    if (StorageScene_IsPocketPlace(self, (unsigned int) place)) {
        return (u8) place;
    }
    if (StorageScene_IsBoxPlace(self, (unsigned int) place)) {
        return StorageScene_BoxIndex(self, place);
    }
    return 0;
}
CLEAN_AS(func_ov102_0229d400, StorageScene_GridPlace)

/* func_ov102_0229d438 */
int StorageScene_IsClosePlace(StorageScene *self, int place)
{
    (void) self;
    return place == STORAGE_SCENE_CLOSE;
}
CLEAN_AS(func_ov102_0229d438, StorageScene_IsClosePlace)

/* func_ov102_0229d444 */
int StorageScene_IsTabPlace(StorageScene *self, unsigned int place)
{
    (void) self;
    return place >= STORAGE_SCENE_TAB_FIRST && place <= STORAGE_SCENE_TAB_LAST;
}
CLEAN_AS(func_ov102_0229d444, StorageScene_IsTabPlace)

/* func_ov102_0229d454 */
int StorageScene_IsBoxPlace(StorageScene *self, unsigned int place)
{
    (void) self;
    return place >= STORAGE_SCENE_BOX_FIRST && place <= STORAGE_SCENE_BOX_LAST;
}
CLEAN_AS(func_ov102_0229d454, StorageScene_IsBoxPlace)

/* func_ov102_0229d464 */
int StorageScene_IsPocketPlace(StorageScene *self, unsigned int place)
{
    (void) self;
    return place <= STORAGE_SCENE_POCKET_LAST;
}
CLEAN_AS(func_ov102_0229d464, StorageScene_IsPocketPlace)

/* func_ov102_0229d470: the layer load task at 0x94 ended (main's LayerTask_End). */
void StorageScene_EndLayerTask(StorageScene *self)
{
    LayerTask_End((LayerTask *) (void *) &self->layer_task);
}
CLEAN_AS(func_ov102_0229d470, StorageScene_EndLayerTask)

/* func_ov102_0229d47c: the first empty place of the page shown, else STORAGE_SCENE_NO_PLACE. */
u8 StorageScene_FreeBoxPlace(StorageScene *self)
{
    u16 *items = StorageScene_PageItems(self);
    for (int i = 0; i < STORAGE_SCENE_PAGE_ITEMS; i++) {
        if (items[i] == STORAGE_NO_ITEM) {
            return (u8) (i + STORAGE_SCENE_BOX_FIRST);
        }
    }
    return STORAGE_SCENE_NO_PLACE;
}
CLEAN_AS(func_ov102_0229d47c, StorageScene_FreeBoxPlace)

/* func_ov102_0229d4ac: the place of the current player's first free pocket slot, else
 * STORAGE_SCENE_NO_PLACE. */
int StorageScene_FreePocketPlace(StorageScene *self)
{
    (void) self;
    int slot = CurrentPockets_FreeSlot();
    if (slot == -1) {
        return STORAGE_SCENE_NO_PLACE;
    }
    return (u8) slot;
}
CLEAN_AS(func_ov102_0229d4ac, StorageScene_FreePocketPlace)

/* func_ov102_0229d4cc: the item at `place` picked up where it is drawn and sent gliding to `to`
 * (Y's quick move). */
void StorageScene_SendTo(StorageScene *self, int place, int to)
{
    StorageScene_PickUpItem(self, (unsigned int) place);
    self->held_x = StorageScene_PlaceX(self, place);
    self->held_y = StorageScene_PlaceY(self, place);
    StorageScene_GlideHeldTo(self, to, 4);
}
CLEAN_AS(func_ov102_0229d4cc, StorageScene_SendTo)

/* func_ov102_0229d508: the held item let go off any place, at y `y` (its middle): an item of the
 * page let go at y 108 or below glides to the first free pocket, one of the pockets let go above
 * it to the first empty place of the page; else (or with no such place) it glides back to
 * `place`. */
void StorageScene_DropOffPlace(StorageScene *self, int place, int y)
{
    int to = STORAGE_SCENE_NO_PLACE;
    if (y >= 108) {
        if (StorageScene_IsBoxPlace(self, (unsigned int) place)) {
            to = StorageScene_FreePocketPlace(self);
        }
    } else if (StorageScene_IsPocketPlace(self, (unsigned int) place)) {
        to = StorageScene_FreeBoxPlace(self);
    }
    if (to != STORAGE_SCENE_NO_PLACE) {
        place = to;
    }
    StorageScene_GlideHeldTo(self, place, 4);
}
CLEAN_AS(func_ov102_0229d508, StorageScene_DropOffPlace)

/* func_ov102_0229d54c: the held item glides from where it is drawn to `place` (kept as `home`)
 * in `steps` steps, 8 pixels higher at a tab (STORAGE_SCENE_FLAG_TO_TAB says so); sub state
 * 0x0d follows the glide. */
void StorageScene_GlideHeldTo(StorageScene *self, int place, int steps)
{
    self->home = (u8) place;
    Glide_SetPlace(&self->glide, self->held_x, self->held_y);
    int y = StorageScene_PlaceY(self, place);
    if (StorageScene_IsTabPlace(self, (unsigned int) place)) {
        y -= 8;
    }
    int x = StorageScene_PlaceX(self, place);
    Glide_MoveTo(&self->glide, x, y, steps);
    Glide_Step(&self->glide);
    StorageScene_FollowGlide(self);
    if (StorageScene_IsTabPlace(self, (unsigned int) place)) {
        StorageScene_SetFlags(self, STORAGE_SCENE_FLAG_TO_TAB);
    } else {
        StorageScene_ClearFlags(self, STORAGE_SCENE_FLAG_TO_TAB);
    }
    MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_HELD_GLIDE);
}
CLEAN_AS(func_ov102_0229d54c, StorageScene_GlideHeldTo)

/* func_ov102_0229d5e8: the item at `place` picked up with the cursor (the place and the page
 * kept, the popup hidden); when one is held, the sub state to go back to is 4, where the keys
 * move it. It is drawn at the cursor sprite; sound 0x0d. */
void StorageScene_PickUpWithCursor(StorageScene *self, u8 place)
{
    self->home = place;
    self->from_place = place;
    self->from_page = self->page;
    Popup_Hide(&self->popup, 1);
    StorageScene_PickUpItem(self, place);
    if (self->held_kind == STORAGE_SCENE_HELD_ITEM) {
        self->return_state = STORAGE_SCENE_SUB_HOLD_BY_KEYS;
    }
    StorageScene_FollowCursorSprite(self);
    PocketsSound_Play0d();
}
CLEAN_AS(func_ov102_0229d5e8, StorageScene_PickUpWithCursor)

/* func_ov102_0229d650: the item at `place` picked up with the stylus (the place and the page
 * kept, the popup hidden); when one is held, sub state 2, where it follows the stylus. It is
 * drawn at the touch; sound 0x0d. */
void StorageScene_PickUpWithTouch(StorageScene *self, u8 place)
{
    self->home = place;
    self->from_place = place;
    self->from_page = self->page;
    Popup_Hide(&self->popup, 1);
    StorageScene_PickUpItem(self, place);
    if (self->held_kind == STORAGE_SCENE_HELD_ITEM) {
        MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_DRAG);
    }
    StorageScene_FollowTouch(self);
    PocketsSound_Play0d();
}
CLEAN_AS(func_ov102_0229d650, StorageScene_PickUpWithTouch)

/* func_ov102_0229d6b4: the pen touched `place` (sub state 1): the offset from the touch to the
 * place kept and the popup queued for it; STORAGE_SCENE_FLAG_DRAGGABLE set (with sound 0x0c)
 * unless its item is dimmed. */
void StorageScene_TouchPlace(StorageScene *self, int place)
{
    self->touch_place = (u8) place;
    MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_HOLD_TOUCH);
    u8 touch_x = data_021f6c58;
    u8 touch_y = data_021f6c54;
    self->grab_dx = StorageScene_PlaceX(self, self->touch_place) - touch_x;
    self->grab_dy = StorageScene_PlaceY(self, self->touch_place) - touch_y;
    self->popup_place = (u8) place;
    Popup_Queue(&self->popup);
    if (StorageScene_PlaceIsDimmed(self, place)) {
        StorageScene_ClearFlags(self, STORAGE_SCENE_FLAG_DRAGGABLE);
    } else {
        StorageScene_SetFlags(self, STORAGE_SCENE_FLAG_DRAGGABLE);
        PocketsSound_Play0c();
    }
}
CLEAN_AS(func_ov102_0229d6b4, StorageScene_TouchPlace)

/* func_ov102_0229d740: the action ends: back to sub state 0 with the cursor sprite hidden while
 * state flag 2 is clear, else to sub state 3 with it at the cursor. */
void StorageScene_EndAction(StorageScene *self)
{
    if (StateFlags_IsClear2()) {
        StorageScene_EndActionHidden(self);
    } else {
        StorageScene_EndActionAtCursor(self);
    }
}
CLEAN_AS(func_ov102_0229d740, StorageScene_EndAction)

/* func_ov102_0229d760: no popup place, the cursor sprite shown at the cursor, the key repeat
 * reset, the popup told of the cursor's place, sub state 3 and the cursor's place selected. */
void StorageScene_EndActionAtCursor(StorageScene *self)
{
    self->popup_place = STORAGE_SCENE_NO_PLACE;
    StorageScene_ShowCursorSprite(self);
    MenuScene_ResetKeyRepeat(storage_base(self));
    StorageScene_UpdatePopup(self);
    MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_IDLE_BY_KEYS);
    StorageScene_SelectPlace(self, self->cursor);
}
CLEAN_AS(func_ov102_0229d760, StorageScene_EndActionAtCursor)

/* func_ov102_0229d79c */
void StorageScene_EndActionHidden(StorageScene *self)
{
    StorageScene_HideCursorSprite(self);
    StorageScene_ClearSelection(self);
    MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_IDLE_BY_TOUCH);
}
CLEAN_AS(func_ov102_0229d79c, StorageScene_EndActionHidden)

/* func_ov102_0229d7b8 (sub state 0x0f): once the delay has run out, state 4 (written directly)
 * in phase 1, the popup and the cursor sprite hidden. */
void StorageScene_WaitCloseDelay(StorageScene *self)
{
    if (self->delay != 0) {
        self->delay--;
        return;
    }
    self->base.state = STORAGE_SCENE_STATE_START_WIPE_OUT;
    MenuScene_SetPhase(storage_base(self), STORAGE_SCENE_PHASE_STATES);
    Popup_Hide(&self->popup, 1);
    StorageScene_HideCursorSprite(self);
}
CLEAN_AS(func_ov102_0229d7b8, StorageScene_WaitCloseDelay)

/* func_ov102_0229d7f8 (sub state 0x0e): once the error message is done, back to the kept sub
 * state and the cursor sprite's window flag set. */
void StorageScene_WaitError(StorageScene *self)
{
    if (ErrorMessage_Update(&self->error, 1)) {
        MenuScene_SetSubState(storage_base(self), self->return_state);
        CellLayerSprite_SetWindow(storage_cursor_cells(self));
    }
}
CLEAN_AS(func_ov102_0229d7f8, StorageScene_WaitError)

/* func_ov102_0229d830 (sub state 0x0d): the held item follows the glide. When the glide is over:
 * after a glide to a tab, the flag saying so is cleared (the next frame puts it down); else it is
 * put down at `home`, the action ends and sound 0x0e plays. */
void StorageScene_StepHeldGlide(StorageScene *self)
{
    if (Glide_Step(&self->glide) == 0) {
        StorageScene_FollowGlide(self);
        return;
    }
    if (StorageScene_TestFlags(self, STORAGE_SCENE_FLAG_TO_TAB)) {
        StorageScene_ClearFlags(self, STORAGE_SCENE_FLAG_TO_TAB);
        StorageScene_FollowGlide(self);
    } else {
        StorageScene_PutHeldAt(self, self->home);
        StorageScene_EndAction(self);
        PocketsSound_Play0e();
    }
}
CLEAN_AS(func_ov102_0229d830, StorageScene_StepHeldGlide)

/* func_ov102_0229d88c (sub state 0x0c): after a swap, back to the kept sub state once the cursor
 * sprite's animation ends. While its turn has settled, the held item is drawn again (with sound
 * 0x0d, once) and follows the cursor sprite. */
void StorageScene_FinishSwap(StorageScene *self)
{
    if (CellLayerSprite_IsDone(storage_cursor_cells(self))) {
        MenuScene_SetSubState(storage_base(self), self->return_state);
    }
    if (Glider_IsTurnSettled(&self->cursor_sprite)) {
        if (StorageScene_TestFlags(self, STORAGE_SCENE_FLAG_HELD_HIDDEN)) {
            StorageScene_ClearFlags(self, STORAGE_SCENE_FLAG_HELD_HIDDEN);
            PocketsSound_Play0d();
        }
        StorageScene_FollowCursorSprite(self);
    }
}
CLEAN_AS(func_ov102_0229d88c, StorageScene_FinishSwap)

/* func_ov102_0229d8e0 (sub state 0x0b): the held item changes places with the item at `target`
 * and is hidden while the cursor sprite turns (sub state 0x0c), unless the turn is at its frame
 * 2, which goes back to sub state 3 instead. */
void StorageScene_SwapWithCursor(StorageScene *self)
{
    if (Glider_IsTurnAtFrame2(&self->cursor_sprite) == 0) {
        StorageScene_SwapHeldWith(self, self->target);
        StorageScene_SetFlags(self, STORAGE_SCENE_FLAG_HELD_HIDDEN);
        MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_SWAP_END);
        StorageScene_UpdatePopup(self);
    } else {
        MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_IDLE_BY_KEYS);
    }
}
CLEAN_AS(func_ov102_0229d8e0, StorageScene_SwapWithCursor)

/* func_ov102_0229d928 (sub state 0x0a): while the cursor sprite's turn has not settled the held
 * item follows it. Then it is put down at `target` when the cursor is there (the popup told of
 * the place, sub state 3, sound 0x0e), else it glides to `target`. */
void StorageScene_PutDownWithCursor(StorageScene *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite) != 0) {
        StorageScene_FollowCursorSprite(self);
        return;
    }
    if (self->cursor == self->target) {
        StorageScene_DropHeldAt(self, self->target);
        StorageScene_UpdatePopup(self);
        MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_IDLE_BY_KEYS);
        PocketsSound_Play0e();
    } else {
        StorageScene_GlideHeldTo(self, self->target, 4);
    }
}
CLEAN_AS(func_ov102_0229d928, StorageScene_PutDownWithCursor)

/* func_ov102_0229d980 (sub state 9): after a pick up, back to the kept sub state once the cursor
 * sprite's animation ends; the held item follows the cursor sprite. */
void StorageScene_FinishPickUp(StorageScene *self)
{
    if (CellLayerSprite_IsDone(storage_cursor_cells(self))) {
        MenuScene_SetSubState(storage_base(self), self->return_state);
    }
    StorageScene_FollowCursorSprite(self);
}
CLEAN_AS(func_ov102_0229d980, StorageScene_FinishPickUp)

/* func_ov102_0229d9b0 (sub state 8): once the cursor sprite's turn has settled, the item at the
 * cursor is picked up (sub state 9). */
void StorageScene_PickUpOnTurn(StorageScene *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite)) {
        StorageScene_PickUpWithCursor(self, self->cursor);
        MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_PICK_UP_END);
    }
}
CLEAN_AS(func_ov102_0229d9b0, StorageScene_PickUpOnTurn)

/* func_ov102_0229d9e0 (sub state 7): once the cursor sprite's animation ends, the first of its
 * set and back to the keys: sub state 4 with an item held, else 3. */
void StorageScene_FinishPressAnim(StorageScene *self)
{
    if (CellLayerSprite_IsDone(storage_cursor_cells(self))) {
        StorageScene_ShowCursorFirstOfSet(self);
        if (self->held_kind == STORAGE_SCENE_HELD_ITEM) {
            MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_HOLD_BY_KEYS);
        } else {
            MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_IDLE_BY_KEYS);
        }
    }
}
CLEAN_AS(func_ov102_0229d9e0, StorageScene_FinishPressAnim)

/* func_ov102_0229da20 (sub state 6): once the cursor sprite's press animation ends: on a tab, its
 * page shown (just the press's end for the page already shown); on the close button the scene
 * closes, with the delay; else the press's end. */
void StorageScene_FinishButtonPress(StorageScene *self)
{
    if (CellLayerSprite_IsDone(storage_cursor_cells(self)) == 0) {
        return;
    }
    if (StorageScene_IsTabPlace(self, self->cursor)) {
        u8 page = (u8) (self->cursor - STORAGE_SCENE_TAB_FIRST);
        if (page == self->page) {
            StorageScene_StartPressAnim(self);
        } else {
            self->page = page;
            StorageScene_ShowPage(self);
        }
    } else if (self->cursor == STORAGE_SCENE_CLOSE) {
        StorageScene_SaveAndClose(self, 1);
    } else {
        StorageScene_StartPressAnim(self);
    }
}
CLEAN_AS(func_ov102_0229da20, StorageScene_FinishButtonPress)

/* func_ov102_0229da90 (sub state 5): once the cursor sprite stops, back to the kept sub state,
 * run at once; back to 3 or 4 (the keys' sub states), the cursor's place is selected first. The
 * held item follows the cursor sprite. */
void StorageScene_WaitCursorSprite(StorageScene *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(storage_base(self), self->return_state);
        if (self->return_state == STORAGE_SCENE_SUB_IDLE_BY_KEYS || self->return_state == STORAGE_SCENE_SUB_HOLD_BY_KEYS) {
            StorageScene_SelectPlace(self, self->cursor);
        }
        StorageScene_RunSubState(self);
    }
    StorageScene_FollowCursorSprite(self);
}
CLEAN_AS(func_ov102_0229da90, StorageScene_WaitCursorSprite)

/* The repeated keys move the cursor (`holding` while an item is held): the popup told of the new
 * place and hidden, the cursor sprite following. Whether they did. */
static int storage_move_cursor_by_keys(StorageScene *self, int holding)
{
    u32 keys = MenuScene_LatchRepeatedKeys(storage_base(self));
    if (StorageScene_MoveCursor(self, (int) keys, holding) == 0) {
        return 0;
    }
    StorageScene_UpdatePopup(self);
    StorageScene_GlideToCursor(self);
    Popup_Hide(&self->popup, 0);
    return 1;
}

/* The menu was asked to close while an item is held: it goes back to `home`, the cursor sprite
 * and the popup (its queue kept) are hidden and the scene closes without the delay. */
static void storage_close_holding(StorageScene *self)
{
    StorageScene_PutHeldAt(self, self->home);
    StorageScene_HideCursorSprite(self);
    Popup_Hide(&self->popup, 0);
    StorageScene_SaveAndClose(self, 0);
}

/* func_ov102_0229dae0 (sub state 4): an item is held and moves with the cursor. A menu close puts
 * it back and closes the scene. The d-pad moves the cursor. A at a grid place not dimmed puts it
 * down there when empty, else swaps it with the item there; A at a tab presses it. B sends it
 * back: to the tab of its page when it came from another page, else gliding home (while the
 * cursor sprite shows animation 1) or put down there. Else L and R turn the page, it follows the
 * cursor sprite and a queued popup is shown. */
void StorageScene_MoveHeldByKeys(StorageScene *self)
{
    if (StateFlags_MenuCloseAsked()) {
        storage_close_holding(self);
        return;
    }
    if (storage_move_cursor_by_keys(self, 1)) {
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & STORAGE_PAD_A) {
        if (storage_is_grid_place(self, self->cursor)) {
            if (StorageScene_PlaceIsDimmed(self, self->cursor) == 0) {
                if (StorageScene_PlaceIsEmpty(self, self->cursor)) {
                    StorageScene_StartPutDown(self, self->cursor);
                } else {
                    StorageScene_StartSwap(self, self->cursor);
                }
            }
        } else if (StorageScene_IsTabPlace(self, self->cursor)) {
            StorageScene_StartButtonPress(self);
        }
        return;
    }
    if (pressed & STORAGE_PAD_B) {
        if (StorageScene_IsBoxPlace(self, self->home) && self->from_page != self->page) {
            StorageScene_GlideHeldTo(self, (u8) (self->from_page + STORAGE_SCENE_TAB_FIRST), 4);
            return;
        }
        if (CellLayerSprite_AnimNumber(storage_cursor_cells(self)) == GLIDER_ANIM_SET_A) {
            StorageScene_GlideHeldTo(self, self->home, 4);
        } else {
            StorageScene_StartPutDown(self, self->home);
        }
        return;
    }
    if (StorageScene_TurnPageByKeys(self) == 0) {
        StorageScene_FollowCursorSprite(self);
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov102_0229dae0, StorageScene_MoveHeldByKeys)

/* func_ov102_0229dc44 (sub state 3): the cursor waits for the keys. A touch hides the cursor
 * sprite and the popup (sub state 0). The d-pad moves the cursor. At a place not dimmed: A on a
 * grid place's item picks it up, on a tab or the close button presses it; Y on a grid place's
 * item sends it to the first free place of the other part (a pocket's to the page, the page's to
 * the pockets), if there is one. X or B closes the scene (the cursor sprite and the popup, its
 * queue kept, hidden); else L and R turn the page and a queued popup is shown. */
void StorageScene_IdleByKeys(StorageScene *self)
{
    if (MenuScene_TakeTouch(storage_base(self)) != 0) {
        StorageScene_EndActionHidden(self);
        Popup_Hide(&self->popup, 1);
        return;
    }
    if (storage_move_cursor_by_keys(self, 0)) {
        return;
    }
    if (StorageScene_PlaceIsDimmed(self, self->cursor) == 0) {
        u16 pressed = data_021fbe40.pressed;
        if (pressed & STORAGE_PAD_A) {
            if (storage_is_grid_place(self, self->cursor)) {
                if (StorageScene_PlaceIsEmpty(self, self->cursor) == 0) {
                    StorageScene_StartPickUp(self);
                }
            } else if (StorageScene_IsClosePlace(self, self->cursor)) {
                StorageScene_StartButtonPress(self);
            } else if (StorageScene_IsTabPlace(self, self->cursor)) {
                StorageScene_StartButtonPress(self);
            }
            return;
        }
        if (pressed & STORAGE_PAD_Y) {
            if (storage_is_grid_place(self, self->cursor) && StorageScene_PlaceIsEmpty(self, self->cursor) == 0) {
                int to;
                if (StorageScene_IsPocketPlace(self, self->cursor)) {
                    to = StorageScene_FreeBoxPlace(self);
                } else {
                    to = StorageScene_FreePocketPlace(self);
                }
                if (to != STORAGE_SCENE_NO_PLACE) {
                    StorageScene_SendTo(self, self->cursor, to);
                    Popup_Hide(&self->popup, 1);
                }
            }
            return;
        }
    }
    u16 pressed = data_021fbe40.pressed;
    if ((pressed & STORAGE_PAD_X) || (pressed & STORAGE_PAD_B)) {
        StorageScene_HideCursorSprite(self);
        StorageScene_SaveAndClose(self, 1);
        Popup_Hide(&self->popup, 0);
        return;
    }
    if (StorageScene_TurnPageByKeys(self) == 0) {
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov102_0229dc44, StorageScene_IdleByKeys)

/* func_ov102_0229ddcc (sub state 2): the held item follows the stylus. A menu close puts it back
 * and closes the scene. The place under the item's middle (8 pixels right and down of where it
 * is drawn) is marked while the pen is down. The pen lifted on a place not dimmed puts the item
 * down there (an item there goes home), sound 0x0e, and the action ends; lifted on a dimmed
 * place, off any place, or where the drop is refused, it is let go off a place
 * (StorageScene_DropOffPlace). */
void StorageScene_DragHeld(StorageScene *self)
{
    if (StateFlags_MenuCloseAsked()) {
        storage_close_holding(self);
        return;
    }
    StorageScene_FollowTouch(self);
    StorageScene_ClearHighlights(self);
    int x = (int) ((u32) self->held_x + 8);
    int y = (int) ((u32) self->held_y + 8);
    int place = StorageScene_PlaceAtTouch(self, x, y, 0);
    if (place == STORAGE_SCENE_NO_PLACE) {
        if (data_021fbdd8 == 0) {
            StorageScene_DropOffPlace(self, self->home, y);
        }
        return;
    }
    if (data_021fbdd8 != 0) {
        StorageScene_HighlightPlace(self, (unsigned int) place);
        return;
    }
    if (StorageScene_PlaceIsDimmed(self, place) != 0 || StorageScene_DropHeldAt(self, place) == 0) {
        StorageScene_DropOffPlace(self, self->home, y);
        return;
    }
    PocketsSound_Play0e();
    StorageScene_EndAction(self);
}
CLEAN_AS(func_ov102_0229ddcc, StorageScene_DragHeld)

/* func_ov102_0229dea4 (sub state 1): the pen is on a touched place (StorageScene_TouchPlace).
 * Lifted: back to sub state 0 with the popup closing after 60 frames. Held at a place that may be
 * dragged and moved more than 8 pixels, it picks the item up; else a queued popup is shown. */
void StorageScene_HoldTouchOnPlace(StorageScene *self)
{
    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_IDLE_BY_TOUCH);
        Popup_SetTimer(&self->popup, 60);
        return;
    }
    if (StorageScene_TestFlags(self, STORAGE_SCENE_FLAG_DRAGGABLE) && StorageScene_TouchMoved(self)) {
        StorageScene_PickUpWithTouch(self, self->touch_place);
    } else {
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov102_0229dea4, StorageScene_HoldTouchOnPlace)

/* func_ov102_0229defc (sub state 0): the touch is in use and the cursor sprite hidden. A button
 * puts the cursor sprite back at the cursor (sub state 3). A touch on a place that holds an item
 * touches it (sub state 1); on the close button it closes the scene (with the delay); on the tab
 * of another page it shows that page. */
void StorageScene_IdleByTouch(StorageScene *self)
{
    if (MenuScene_TakeButtons(storage_base(self), 1) != 0) {
        StorageScene_EndActionAtCursor(self);
        return;
    }
    if (!(data_021fbdd8 != 0 && data_021fbddc != 0)) {
        return;
    }
    int x = data_021f6c58;
    int y = data_021f6c54;
    int place = StorageScene_PlaceAtTouch(self, x, y, 1);
    if (place != STORAGE_SCENE_NO_PLACE) {
        StorageScene_TouchPlace(self, place);
        return;
    }
    if (x >= STORAGE_CLOSE_MIN_X && x <= STORAGE_CLOSE_MAX_X && y >= STORAGE_CLOSE_MIN_Y && y <= STORAGE_CLOSE_MAX_Y) {
        StorageScene_SaveAndClose(self, 1);
        return;
    }
    if (StorageScene_TabAtTouch(self, x, y)) {
        StorageScene_ShowPage(self);
    }
}
CLEAN_AS(func_ov102_0229defc, StorageScene_IdleByTouch)

/* The scene's layers and their wipes, its states, its frames, its draw and its construction. */

/* The 2D layers: the pockets' (6) and the page's (4). */
#define STORAGE_POCKETS_LAYER 6
#define STORAGE_PAGE_LAYER 4

/* The wipes on window 2: the pockets' over 8 layers, the page's over 2; the page's extent. */
#define STORAGE_POCKETS_WIPE_LAYERS 8
#define STORAGE_PAGE_WIPE_LAYERS 2
#define STORAGE_WIPE_MARGIN 0x30
#define STORAGE_PAGE_WIPE_EXTENT 0x90

/* What the parent is told when the scene ends (MenuDispatch_SetMode). */
#define STORAGE_PARENT_CODE_END MENU_DISPATCH_MODE_CLOSE

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables (in the
 * overlay's .bss) and the constants they are filled from. */
extern u32 data_ov102_0229ebc0; /* the states' guard */
extern u32 data_ov102_0229ebc4; /* the sub states' guard */
extern MemberPointer data_ov102_0229ebc8[STORAGE_SCENE_STATES];
extern MemberPointer data_ov102_0229ec18[STORAGE_SCENE_SUB_STATES];
extern const MemberPointer data_ov102_0229e980, data_ov102_0229e988, data_ov102_0229e990, data_ov102_0229e998,
    data_ov102_0229e9a0, data_ov102_0229e9a8, data_ov102_0229e9b0, data_ov102_0229e9b8, data_ov102_0229e9c0,
    data_ov102_0229e9c8, data_ov102_0229e9d0, data_ov102_0229e9d8, data_ov102_0229e9e0, data_ov102_0229e9f0,
    data_ov102_0229e9f8, data_ov102_0229ea00, data_ov102_0229ea08, data_ov102_0229ea10, data_ov102_0229ea18,
    data_ov102_0229ea20, data_ov102_0229ea28, data_ov102_0229ea30, data_ov102_0229ea38, data_ov102_0229ea40,
    data_ov102_0229ea48, data_ov102_0229ea50;

/* Calls the draw (vtable slot 2) of a member object through its own vtable, as the game does. */
static void storage_draw_member(void *object)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[2])(object);
}

/* func_ov102_0229df94: a step of the wallet display's setup (its OBJ files); its answer. */
int StorageScene_LoadWalletFiles(StorageScene *self)
{
    return PocketsWallet_LoadObjFiles(&self->wallet);
}
CLEAN_AS(func_ov102_0229df94, StorageScene_LoadWalletFiles)

/* func_ov102_0229dfa4: the page shown loaded: its palettes ("menu/inventory/ten<page>.bpl", 3-5
 * of the file to 3-5 of layer 4) and its 15 items handed to the grid's object. */
void StorageScene_LoadPage(StorageScene *self)
{
    Heap *heap = data_021fbe94;
    char path[0x24];
    CLib_SPrintf(path, data_ov102_0229eb50, self->page);
    DisplayLayer_LoadPalettesFromFile(path, heap, STORAGE_PAGE_LAYER, 3, 3, 5);
    PocketsGrid_SetBox(&self->grid, StorageScene_PageItems(self));
}
CLEAN_AS(func_ov102_0229dfa4, StorageScene_LoadPage)

/* func_ov102_0229dff0: the page's layer loaded (its screen and characters 0x1b9-0x238), and the
 * title shown. */
void StorageScene_LoadBackground(StorageScene *self)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadScreenFromFile(data_ov102_0229eb6c, heap, STORAGE_PAGE_LAYER);
    DisplayLayer_LoadCharsFromFile(data_ov102_0229eb90, heap, STORAGE_PAGE_LAYER, 0x1b9, 0x1b9, 0x238);
    StorageScene_ShowTitle(self, 0);
}
CLEAN_AS(func_ov102_0229dff0, StorageScene_LoadBackground)

/* func_ov102_0229e03c: the wallet's display set up on the main screen's side (0). */
void StorageScene_PrepareWallet(StorageScene *self)
{
    PocketsWallet_SetUp(&self->wallet, 0);
}
CLEAN_AS(func_ov102_0229e03c, StorageScene_PrepareWallet)

/* func_ov102_0229e050: layer 6 at priority 2 and layer 4 at priority 1, both with their plain
 * background settings. */
void StorageScene_SetUpLayers(void)
{
    DisplayLayer_SetPriority(STORAGE_POCKETS_LAYER, 2);
    DisplayLayer_SetBgControl(STORAGE_POCKETS_LAYER, 0, 0, 0);
    DisplayLayer_SetPriority(STORAGE_PAGE_LAYER, 1);
    DisplayLayer_SetBgControl(STORAGE_PAGE_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov102_0229e050, StorageScene_SetUpLayers)

/* func_ov102_0229e084: the end of a frame: the wallet's display updated, and the popup placed
 * when its update asks for it. */
void StorageScene_EndFrame(StorageScene *self)
{
    PocketsWallet_Update(&self->wallet);
    if (Popup_Update(&self->popup)) {
        StorageScene_PlacePopup(self);
    }
}
CLEAN_AS(func_ov102_0229e084, StorageScene_EndFrame)

/* func_ov102_0229e0b0: the start of a frame: the layer task ended, the three objects of ov094's
 * updated, and the labels closed (the title is shown again each frame it is wanted). */
void StorageScene_BeginFrame(StorageScene *self)
{
    StorageScene_EndLayerTask(self);
    PocketsWallet_BeginFrame(&self->wallet);
    PocketsGrid_BeginFrame(&self->grid);
    PocketsLetters_BeginFrame(&self->letters);
    StorageScene_CloseLabels(self);
}
CLEAN_AS(func_ov102_0229e0b0, StorageScene_BeginFrame)

/* func_ov102_0229e0e4 */
void StorageScene_EndInteractiveFrame(StorageScene *self)
{
    StorageScene_EndFrame(self);
}
CLEAN_AS(func_ov102_0229e0e4, StorageScene_EndInteractiveFrame)

/* func_ov102_0229e0ec: the start of a frame, then the cursor sprite's update through its class
 * (vtable slot 3). */
void StorageScene_BeginInteractiveFrame(StorageScene *self)
{
    StorageScene_BeginFrame(self);
    storage_update_cursor_sprite(self);
}
CLEAN_AS(func_ov102_0229e0ec, StorageScene_BeginInteractiveFrame)

/* func_ov102_0229e108: the members' teardown before the scene closes. */
void StorageScene_Teardown(StorageScene *self)
{
    StorageScene_EndLayerTask(self);
    PocketsWallet_Teardown(&self->wallet);
    PocketsGrid_Teardown(&self->grid);
    StorageScene_CloseLabels(self);
}
CLEAN_AS(func_ov102_0229e108, StorageScene_Teardown)

/* func_ov102_0229e130: the scene's setup: no flags, the three objects of ov094's set up (the
 * grid's OBJs at priority 1, the letters' at 2, the wallet on layer 6), no popup place, the glide
 * stopped, nothing held, the cursor at the first pocket, no label used; the current player's 90
 * stored items copied into `storage`, the pockets saved (Pockets_Save) and page 0 shown. */
void StorageScene_Setup(StorageScene *self)
{
    self->flags = 0;
    PocketsGrid_Init(&self->grid, 1);
    PocketsLetters_Init(&self->letters, 2);
    PocketsWallet_Init(&self->wallet, STORAGE_POCKETS_LAYER);
    self->popup_place = STORAGE_SCENE_NO_PLACE;
    Glide_Stop(&self->glide);
    self->held_kind = STORAGE_SCENE_HELD_NONE;
    self->cursor = STORAGE_SCENE_POCKET_FIRST;
    self->labels_used = 0;
    u16 *items = PlayerStorage_Items(PlayerRecord_Storage(PlayerRecords_Current()));
    MI_CpuCopy8(items, self->storage, sizeof(self->storage));
    Pockets_Save();
    self->page = 0;
}
CLEAN_AS(func_ov102_0229e130, StorageScene_Setup)

/* func_ov102_0229e1c4 (state 9): the turned page wipes in, as in state 3. */
void StorageScene_TurnPageWipeIn(StorageScene *self)
{
    StorageScene_PageWipeIn(self);
}
CLEAN_AS(func_ov102_0229e1c4, StorageScene_TurnPageWipeIn)

/* func_ov102_0229e1cc (state 8): the page wipes out. Once done, layer 4 is hidden and, after
 * `delay` more frames, the page shown wipes in (state 9). The page's offset follows the wipe while
 * it runs. */
void StorageScene_TurnPageWipeOut(StorageScene *self)
{
    if (MenuScene_StepWipe(storage_base(self), 0) == 0) {
        MenuScene_ScrollWipe(storage_base(self), STORAGE_PAGE_LAYER, 0, 0);
        self->page_y = MenuScene_WipeOffsetY(storage_base(self));
        return;
    }
    DisplayLayer_HideAndResetScroll(STORAGE_PAGE_LAYER);
    if (self->delay != 0) {
        self->delay--;
    } else {
        StorageScene_StartPageWipeIn(self);
        MenuScene_SetState(storage_base(self), STORAGE_SCENE_STATE_TURN_PAGE_WIPE_IN);
    }
}
CLEAN_AS(func_ov102_0229e1cc, StorageScene_TurnPageWipeOut)

/* func_ov102_0229e224 (state 7): the page starts to wipe out (state 8, run at once), with a delay
 * of 4 frames before the next one wipes in. */
void StorageScene_TurnPage(StorageScene *self)
{
    StorageScene_StartPageWipeOut(self);
    MenuScene_SetState(storage_base(self), STORAGE_SCENE_STATE_TURN_PAGE_WIPE_OUT);
    self->delay = STORAGE_PAGE_DELAY;
    StorageScene_TurnPageWipeOut(self);
}
CLEAN_AS(func_ov102_0229e224, StorageScene_TurnPage)

/* func_ov102_0229e24c (state 6): the pockets wipe out. When done, layer 6 hidden, phase 5 (the
 * scene is deleted) and nothing drawn. The pockets' offset follows the wipe. */
void StorageScene_PocketsWipeOut(StorageScene *self)
{
    if (MenuScene_StepWipe(storage_base(self), 0)) {
        DisplayLayer_HideAndResetScroll(STORAGE_POCKETS_LAYER);
        MenuScene_SetPhase(storage_base(self), STORAGE_SCENE_PHASE_DELETE);
        StorageScene_ClearFlags(self, STORAGE_SCENE_FLAG_DRAWN);
        StorageScene_ClearFlags(self, STORAGE_SCENE_FLAG_POCKETS_DRAWN);
    } else {
        MenuScene_ScrollWipe(storage_base(self), STORAGE_POCKETS_LAYER, 0, 0);
    }
    self->objects_y = MenuScene_WipeOffsetY(storage_base(self));
}
CLEAN_AS(func_ov102_0229e24c, StorageScene_PocketsWipeOut)

/* func_ov102_0229e29c (state 5): the page wipes out. When done, layer 4 is hidden, the page no
 * longer drawn and the pockets start to wipe out (state 6, run at once); while it runs the page's
 * offset follows the wipe. */
void StorageScene_PageWipeOut(StorageScene *self)
{
    if (MenuScene_StepWipe(storage_base(self), 0)) {
        DisplayLayer_HideAndResetScroll(STORAGE_PAGE_LAYER);
        StorageScene_ClearFlags(self, STORAGE_SCENE_FLAG_PAGE_DRAWN);
        MenuScene_StartWipeOnWindow2(storage_base(self), STORAGE_POCKETS_WIPE_LAYERS, 0, 0, STORAGE_WIPE_MARGIN);
        MenuScene_ScrollWipe(storage_base(self), STORAGE_POCKETS_LAYER, 0, 0);
        MenuScene_SetState(storage_base(self), STORAGE_SCENE_STATE_POCKETS_WIPE_OUT);
        StorageScene_PocketsWipeOut(self);
    } else {
        MenuScene_ScrollWipe(storage_base(self), STORAGE_PAGE_LAYER, 0, 0);
        self->page_y = MenuScene_WipeOffsetY(storage_base(self));
    }
}
CLEAN_AS(func_ov102_0229e29c, StorageScene_PageWipeOut)

/* func_ov102_0229e308 (state 4): the page starts to wipe out, the parent is told the scene ends
 * (MENU_DISPATCH_MODE_CLOSE, with its sound), state 5. */
void StorageScene_StartWipeOut(StorageScene *self)
{
    StorageScene_StartPageWipeOut(self);
    MenuDispatch_SetMode((MenuDispatch *) (void *) storage_parent(self), STORAGE_PARENT_CODE_END, 1);
    MenuScene_SetState(storage_base(self), STORAGE_SCENE_STATE_PAGE_WIPE_OUT);
}
CLEAN_AS(func_ov102_0229e308, StorageScene_StartWipeOut)

/* func_ov102_0229e32c: the popup and the cursor sprite hidden, the page's wipe out on window 2. */
void StorageScene_StartPageWipeOut(StorageScene *self)
{
    Popup_Hide(&self->popup, 1);
    StorageScene_HideCursorSprite(self);
    MenuScene_StartWipeOnWindow2(storage_base(self), STORAGE_PAGE_WIPE_LAYERS, 4, 1, STORAGE_WIPE_MARGIN);
    MenuScene_SetWipeExtent(storage_base(self), STORAGE_PAGE_WIPE_EXTENT);
    MenuScene_ScrollWipe(storage_base(self), STORAGE_PAGE_LAYER, 0, 0);
    self->page_y = MenuScene_WipeOffsetY(storage_base(self));
}
CLEAN_AS(func_ov102_0229e32c, StorageScene_StartPageWipeOut)

/* func_ov102_0229e380 (state 3): the page wipes in. When done: phase 2, the action ends
 * (StorageScene_EndAction picks the first sub state) and the held item is drawn again; with an
 * item held and state flag 2 set, the cursor sprite ends on animation 4 (off a tab), is updated,
 * the item follows it and sub state 4 moves it. The page's offset follows the wipe. */
void StorageScene_PageWipeIn(StorageScene *self)
{
    if (MenuScene_StepWipeBack(storage_base(self), 0)) {
        MenuScene_SetPhase(storage_base(self), STORAGE_SCENE_PHASE_INTERACTIVE);
        StorageScene_EndAction(self);
        StorageScene_ClearFlags(self, STORAGE_SCENE_FLAG_HELD_HIDDEN);
        if (self->held_kind != STORAGE_SCENE_HELD_NONE && StateFlags_Test2()) {
            if (self->cursor < STORAGE_SCENE_TAB_FIRST || self->cursor > STORAGE_SCENE_TAB_LAST) {
                CellLayerSprite_SetAnimAtEnd(storage_cursor_cells(self), GLIDER_ANIM_TURN_A);
            }
            storage_update_cursor_sprite(self);
            StorageScene_FollowCursorSprite(self);
            MenuScene_SetSubState(storage_base(self), STORAGE_SCENE_SUB_HOLD_BY_KEYS);
        }
    }
    MenuScene_ScrollWipe(storage_base(self), STORAGE_PAGE_LAYER, 0, 0);
    self->page_y = MenuScene_WipeOffsetY(storage_base(self));
}
CLEAN_AS(func_ov102_0229e380, StorageScene_PageWipeIn)

/* func_ov102_0229e410 (state 2): the pockets wipe in, their offset following the wipe; when done,
 * the page's layer is loaded and the page starts to wipe in (state 3). */
void StorageScene_PocketsWipeIn(StorageScene *self)
{
    int done = MenuScene_StepWipeBack(storage_base(self), 0);
    MenuScene_ScrollWipe(storage_base(self), STORAGE_POCKETS_LAYER, 0, 0);
    self->objects_y = MenuScene_WipeOffsetY(storage_base(self));
    if (done) {
        StorageScene_LoadBackground(self);
        StorageScene_StartPageWipeIn(self);
        MenuScene_SetState(storage_base(self), STORAGE_SCENE_STATE_PAGE_WIPE_IN);
    }
}
CLEAN_AS(func_ov102_0229e410, StorageScene_PocketsWipeIn)

/* func_ov102_0229e458 (state 1): a step of the wallet display's setup (its answer unused), the
 * pockets loaded into the grid's object (those that cannot be stored dimmed) and into the letters'
 * (dimmed by state 0xf), layer 6 shown and wiping in (state 2); the scene and the pockets drawn. */
void StorageScene_StartWipeIn(StorageScene *self)
{
    StorageScene_LoadWalletFiles(self);
    PocketsGrid_LoadPockets(&self->grid);
    StorageScene_DimUnstorable(self);
    PocketsLetters_LoadPockets(&self->letters);
    PocketsLetters_DimByState(&self->letters, 0xf);
    MenuScene_StartWipeCoveredOnWindow2(storage_base(self), STORAGE_POCKETS_WIPE_LAYERS, 0, 0, STORAGE_WIPE_MARGIN);
    DisplayLayer_Show(STORAGE_POCKETS_LAYER);
    MenuScene_ScrollWipe(storage_base(self), STORAGE_POCKETS_LAYER, 0, 0);
    MenuScene_SetState(storage_base(self), STORAGE_SCENE_STATE_POCKETS_WIPE_IN);
    StorageScene_SetFlags(self, STORAGE_SCENE_FLAG_DRAWN);
    StorageScene_SetFlags(self, STORAGE_SCENE_FLAG_POCKETS_DRAWN);
    self->objects_y = MenuScene_WipeOffsetY(storage_base(self));
}
CLEAN_AS(func_ov102_0229e458, StorageScene_StartWipeIn)

/* func_ov102_0229e4d8 (state 0): the layers set up and the wallet's display prepared, then
 * state 1. */
void StorageScene_StartSetup(StorageScene *self)
{
    StorageScene_SetUpLayers();
    StorageScene_PrepareWallet(self);
    MenuScene_SetState(storage_base(self), STORAGE_SCENE_STATE_START_WIPE_IN);
}
CLEAN_AS(func_ov102_0229e4d8, StorageScene_StartSetup)

/* func_ov102_0229e4f4: the page shown loaded, its covered wipe in on window 2, the page drawn and
 * layer 4 shown; the page's offset follows the wipe. */
void StorageScene_StartPageWipeIn(StorageScene *self)
{
    StorageScene_LoadPage(self);
    MenuScene_StartWipeCoveredOnWindow2(storage_base(self), STORAGE_PAGE_WIPE_LAYERS, 0, 1, STORAGE_WIPE_MARGIN);
    MenuScene_SetWipeExtent(storage_base(self), STORAGE_PAGE_WIPE_EXTENT);
    StorageScene_SetFlags(self, STORAGE_SCENE_FLAG_PAGE_DRAWN);
    DisplayLayer_Show(STORAGE_PAGE_LAYER);
    MenuScene_ScrollWipe(storage_base(self), STORAGE_PAGE_LAYER, 0, 0);
    self->page_y = MenuScene_WipeOffsetY(storage_base(self));
}
CLEAN_AS(func_ov102_0229e4f4, StorageScene_StartPageWipeIn)

/* func_ov102_0229e548 (vtable slot 0x5c, phase 5): the scene asks to be deleted. Answers 1. */
int StorageScene_RequestDelete(StorageScene *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov102_0229e548, StorageScene_RequestDelete)

/* func_ov102_0229e558 (vtable slot 0x58, phase 4): nothing. */
int StorageScene_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov102_0229e558, StorageScene_Phase4Idle)

/* func_ov102_0229e55c (vtable slot 0x54, phase 3): nothing. */
int StorageScene_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov102_0229e55c, StorageScene_Phase3Idle)

/* func_ov102_0229e560 (vtable slot 0x50, phase 2): a frame of the scene in use. The menu close's
 * delay is counted first; when the menu is asked to close in sub state 0, 1 or 3, the cursor
 * sprite and the popup (its queue kept) are hidden and the scene closes without the delay. Then,
 * in any case, the frame's start, its sub state and its end. Answers 1. */
int StorageScene_RunInteractive(StorageScene *self)
{
    StateFlags_CountMenuCloseDelay();
    if (StateFlags_MenuCloseAsked()) {
        u8 sub_state = self->base.sub_state;
        if (sub_state == STORAGE_SCENE_SUB_IDLE_BY_TOUCH || sub_state == STORAGE_SCENE_SUB_HOLD_TOUCH ||
            sub_state == STORAGE_SCENE_SUB_IDLE_BY_KEYS) {
            StorageScene_HideCursorSprite(self);
            Popup_Hide(&self->popup, 0);
            StorageScene_SaveAndClose(self, 0);
        }
    }
    StorageScene_BeginInteractiveFrame(self);
    StorageScene_RunSubState(self);
    StorageScene_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(func_ov102_0229e560, StorageScene_RunInteractive)

/* func_ov102_0229e5b8: the sub state's function (StorageSceneSubState) through the table of
 * member functions, filled once from its constants.
 * REQUIRES: the sub state is below 0x10; the game reads past the table for others. */
void StorageScene_RunSubState(StorageScene *self)
{
    static const MemberPointer *const sub_states[STORAGE_SCENE_SUB_STATES] = {
        &data_ov102_0229ea00, &data_ov102_0229e9f8, &data_ov102_0229e9f0, &data_ov102_0229e9a8,
        &data_ov102_0229e988, &data_ov102_0229e9d8, &data_ov102_0229e9d0, &data_ov102_0229e9c8,
        &data_ov102_0229e990, &data_ov102_0229ea10, &data_ov102_0229e9b0, &data_ov102_0229e9a0,
        &data_ov102_0229e9e0, &data_ov102_0229e998, &data_ov102_0229e980, &data_ov102_0229e9b8,
    };
    MemberTable_InitOnce(&data_ov102_0229ebc4, data_ov102_0229ec18, sub_states, STORAGE_SCENE_SUB_STATES);
    MemberPointer_CallVoid(&data_ov102_0229ec18[self->base.sub_state], self);
}
CLEAN_AS(func_ov102_0229e5b8, StorageScene_RunSubState)

/* Obj_ov102_0229ea60::func_ov102_0229e6e4 (vtable slot 0x4c, phase 1): a frame of the scene's
 * states (StorageSceneState) between the frame's start and end, through the table of member
 * functions (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 10; the game reads past the table for others. */
int StorageScene_RunState(StorageScene *self)
{
    static const MemberPointer *const states[STORAGE_SCENE_STATES] = {
        &data_ov102_0229ea08, &data_ov102_0229ea20, &data_ov102_0229ea50, &data_ov102_0229ea48, &data_ov102_0229ea40,
        &data_ov102_0229ea38, &data_ov102_0229ea30, &data_ov102_0229ea28, &data_ov102_0229e9c0, &data_ov102_0229ea18,
    };
    MemberTable_InitOnce(&data_ov102_0229ebc0, data_ov102_0229ebc8, states, STORAGE_SCENE_STATES);
    StorageScene_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov102_0229ebc8[self->base.state], self);
    StorageScene_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov102_0229ea6019func_ov102_0229e6e4Ev, StorageScene_RunState)

/* func_ov102_0229e7cc (vtable slot 0x24): the scene's draw, while it is drawn: the popup (through
 * its class, slot 2), the cursor sprite (with the keys in use), the held item; with the page
 * drawn, the page's places at its wipe y and the tabs; with the pockets drawn, the pockets, the
 * letters and the wallet at theirs. Answers 1. */
int StorageScene_Draw(StorageScene *self)
{
    if (StorageScene_TestFlags(self, STORAGE_SCENE_FLAG_DRAWN) == 0) {
        return 1;
    }
    storage_draw_member(&self->popup);
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    StorageScene_DrawHeld(self);
    if (StorageScene_TestFlags(self, STORAGE_SCENE_FLAG_PAGE_DRAWN)) {
        PocketsGrid_DrawBox(&self->grid, 0, self->page_y);
        StorageScene_DrawTabs(self);
    }
    if (StorageScene_TestFlags(self, STORAGE_SCENE_FLAG_POCKETS_DRAWN)) {
        PocketsGrid_DrawPockets(&self->grid, 0, self->objects_y);
        PocketsLetters_DrawPockets(&self->letters, 0, self->objects_y);
        PocketsWallet_Draw(&self->wallet, self->objects_y);
    }
    return 1;
}
CLEAN_AS(func_ov102_0229e7cc, StorageScene_Draw)

/* func_ov102_0229e874 (vtable slot 0x0c): the scene closes: the parent told and the members torn
 * down. Answers 1. */
int StorageScene_Close(StorageScene *self)
{
    MenuDispatch_ChildClosed((MenuDispatch *) (void *) storage_parent(self));
    StorageScene_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov102_0229e874, StorageScene_Close)

/* func_ov102_0229e890 (vtable slot 0x00): the scene starts: its setup, state 0 and phase 0.
 * Answers 1. */
int StorageScene_Start(StorageScene *self)
{
    StorageScene_Setup(self);
    MenuScene_SetState(storage_base(self), STORAGE_SCENE_STATE_START_SETUP);
    MenuScene_SetPhase(storage_base(self), STORAGE_SCENE_PHASE_WAIT);
    return 1;
}
CLEAN_AS(func_ov102_0229e890, StorageScene_Start)

/* func_ov102_0229e8b0 (named by the profile at 0x0229e9e8): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order, the two labels by __cxa_vec_ctor. */
StorageScene *StorageScene_New(void)
{
    StorageScene *self = MenuScene_Alloc(sizeof(StorageScene));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov102_0229ea60;
    LayerTask_ConstructPair(&self->layer_task);
    PocketsGrid_Construct(&self->grid);
    PocketsLetters_Construct(&self->letters);
    PocketsWallet_Construct(&self->wallet);
    Popup_Construct(&self->popup);
    Glide_Construct(&self->glide);
    Glider0_Construct(&self->cursor_sprite);
    ErrorMessage_Construct(&self->error);
    __cxa_vec_ctor(self->labels, STORAGE_SCENE_LABELS, sizeof(TextLabel), func_02070c08, func_02070be8);
    return self;
}
CLEAN_AS(func_ov102_0229e8b0, StorageScene_New)
