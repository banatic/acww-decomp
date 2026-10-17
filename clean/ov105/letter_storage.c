/* The letter storage scene of overlay 105 (letter_storage.h): its destructors, its flags, the
 * page tabs, the cursor's moves, the choices it opens and the held letter. */
#include "letter_storage.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/current_pockets.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/label_sprite.h"
#include "main/layer_load_task.h"
#include "main/oam_buffer.h"
#include "main/sliding_window.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov002/key_repeat.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(LetterStorage, flags) == 0x94, "flags");
static_assert(offsetof(LetterStorage, wipe_x) == 0xa0 && offsetof(LetterStorage, held_x) == 0xac, "places");
static_assert(sizeof(Letter) == 0x100 && offsetof(LetterStorage, held) == 0xb4, "held letter");
static_assert(offsetof(LetterStorage, swapped) == 0x1b4 && offsetof(LetterStorage, held_kind) == 0x2b4, "swapped");
static_assert(offsetof(LetterStorage, cursor) == 0x2ba && offsetof(LetterStorage, page) == 0x2c0, "cursor");
static_assert(offsetof(LetterStorage, open_delay) == 0x2c3 && offsetof(LetterStorage, grid) == 0x2fc, "grid");
static_assert(offsetof(LetterStorage, letters) == 0xd5c && offsetof(LetterStorage, wallet) == 0xd84, "ov094 objects");
static_assert(offsetof(LetterStorage, popup) == 0x23bc && offsetof(LetterStorage, glide) == 0x248c, "popup");
static_assert(offsetof(LetterStorage, cursor_sprite) == 0x24a4 && offsetof(LetterStorage, choice) == 0x2508, "sprite");
static_assert(offsetof(LetterStorage, entries) == 0x28f0 && offsetof(LetterStorage, error) == 0x28fc, "entries");
static_assert(offsetof(LetterStorage, view) == 0x2a18 && offsetof(LetterStorage, button) == 0x2d40, "view");
static_assert(offsetof(LetterStorage, stored) == 0x2db8 && offsetof(LetterStorage, panel) == 0x5fb8, "stored");
static_assert(sizeof(LetterStorage) == 0x6184, "size (func_ov105_0229f760)");

/* The item code of no item (main/item_code.h). */
#define LETTER_STORAGE_NO_ITEM 0xfff1

/* The pad (autoload_2/input.h): R and L turn the page. */
extern PadState data_021fbe40;
#define LETTER_STORAGE_PAD_R 0x0100
#define LETTER_STORAGE_PAD_L 0x0200

/* The touch (main's bytes, as ov099's pockets_view.c reads them). */
extern u8 data_021f6c58, data_021f6c54, data_021f6c60, data_021f6c5c;

/* The heap the scenes load into (autoload_2/heap.c). */
extern Heap *data_021fbe94;

/* The scene's vtable, the sound of each page and the files of the pages' background
 * characters ("menu/inventory/b_itm_post0.bch", "...post1.bch"). */
extern const u8 data_ov105_0229fad0[];
extern const u16 data_ov105_0229f85c[LETTER_STORE_PAGES];
extern const char *const data_ov105_0229f890[LETTER_STORE_PAGES];

/* The OBJs of the two page tabs, three each (the first one is the tab's touch area). */
extern const OamEntry data_ov105_0229fa80[LETTER_STORE_PAGES * LETTER_STORAGE_TAB_OBJS];

/* The members' destructors (a letter's is handed to __cxa_vec_cleanup, so it is the game's
 * symbol). */
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void func_02066688(void *letter);
extern void *func_ov094_0229a2d0(void *wallet);
extern void func_ov094_0229bc30(void *letters);
extern void *func_ov094_0229afe0(void *grid);

/* The objects of ov094's: the grid at 0x2fc and the letters at 0xd5c. */
extern void func_ov094_0229ab0c(void *grid);
extern void func_ov094_0229ab5c(void *grid);
extern void func_ov094_0229b288(void *letters, Letter *page);
extern void func_ov094_0229b1d8(void *letters);
extern Letter *func_ov094_0229b8d8(void *letters, int index); /* the letter */
extern void func_ov094_0229b890(void *letters, int index);
extern void func_ov094_0229b5e8(void *letters, int x, int y, Letter *letter);
extern int func_ov094_0229b9b4(void *letters, Popup *popup, int index);
extern void func_ov094_0229b938(void *letters, int index);
extern void func_ov094_0229b944(void *letters);
extern void func_ov094_0229b950(void *letters, int index);

/* The scene's own, outside these functions. */
extern void func_ov105_0229ed78(LetterStorage *self);

static PagedChoice *choice_of(LetterStorage *self)
{
    return (PagedChoice *) (void *) self->choice;
}

static MenuScene *scene_of(LetterStorage *self)
{
    return &self->base;
}

/* The place is a letter of the letters object: carried or on the page. */
static int is_letter_place(LetterStorage *self, int place)
{
    return LetterStorage_IsCarriedPlace(self, (unsigned int) place) != 0 ||
           LetterStorage_IsPagePlace(self, (unsigned int) place) != 0;
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void update_cursor_sprite(Glider *sprite)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* The members' destructors, last member first, then the base's. */
static void destroy_members(LetterStorage *self)
{
    self->base.vtable = data_ov105_0229fad0;
    ButtonPanel_Destroy(&self->panel);
    __cxa_vec_cleanup(self->stored, LETTER_STORE_LETTERS, sizeof(Letter), func_02066688);
    LabelButton0_Destroy(&self->button);
    LetterView_Destruct(&self->view);
    ErrorMessage_Destruct(&self->error);
    PagedChoice_Destroy(choice_of(self));
    Glider0_Destroy(&self->cursor_sprite);
    Glide_Destroy(&self->glide);
    Popup_Destroy(&self->popup);
    func_ov094_0229a2d0(self->wallet);
    func_ov094_0229bc30(self->letters);
    func_ov094_0229afe0(self->grid);
    Letter_Destruct(&self->swapped);
    Letter_Destruct(&self->held);
    MenuScene_DestroyBase(scene_of(self));
}

/* func_ov105_0229c180 */
LetterStorage *LetterStorage_Destroy(LetterStorage *self)
{
    destroy_members(self);
    return self;
}
CLEAN_AS(func_ov105_0229c180, LetterStorage_Destroy)

/* func_ov105_0229c24c */
LetterStorage *LetterStorage_Delete(LetterStorage *self)
{
    destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov105_0229c24c, LetterStorage_Delete)

/* func_ov105_0229c320 */
void LetterStorage_ClearFlags(LetterStorage *self, unsigned int flags)
{
    self->flags &= ~flags;
}
CLEAN_AS(func_ov105_0229c320, LetterStorage_ClearFlags)

/* func_ov105_0229c330 */
void LetterStorage_SetFlags(LetterStorage *self, unsigned int flags)
{
    self->flags |= flags;
}
CLEAN_AS(func_ov105_0229c330, LetterStorage_SetFlags)

/* func_ov105_0229c340: 1 when any of `flags` is set. */
int LetterStorage_TestFlags(LetterStorage *self, int flags)
{
    return (self->flags & (u32) flags) != 0;
}
CLEAN_AS(func_ov105_0229c340, LetterStorage_TestFlags)

/* func_ov105_0229c354: L shows the page before, R the page after (L first when both), wrapping
 * around the two pages (LetterStorage_ShowPage). Always 0. */
int LetterStorage_TurnPageByKeys(LetterStorage *self)
{
    int step = 0;
    u16 pressed = data_021fbe40.pressed;

    if (pressed & LETTER_STORAGE_PAD_L) {
        step = -1;
    } else if (pressed & LETTER_STORAGE_PAD_R) {
        step = 1;
    }
    if (step != 0) {
        int page = self->page + step;
        if (page < 0) {
            page = LETTER_STORE_PAGES - 1;
        } else if (page > LETTER_STORE_PAGES - 1) {
            page = 0;
        }
        self->page = (u8) page;
        LetterStorage_ShowPage(self);
    }
    return 0;
}
CLEAN_AS(func_ov105_0229c354, LetterStorage_TurnPageByKeys)

/* func_ov105_0229c3ac: the sub screen back to normal (DisplayShadow_BeginSubObjWindowBrightness
 * undone) and the panel's flag 2 cleared. */
void LetterStorage_EndPanelDim(LetterStorage *self)
{
    DisplayShadow_EndSubObjWindowBrightness();
    ButtonPanel_ClearFlag2(&self->panel);
}
CLEAN_AS(func_ov105_0229c3ac, LetterStorage_EndPanelDim)

/* func_ov105_0229c3c8: the sub screen darkened (brightness -6) outside its OBJ window and the
 * panel's flag 2 set. */
void LetterStorage_BeginPanelDim(LetterStorage *self)
{
    DisplayShadow_BeginSubObjWindowBrightness();
    DisplayShadow_SetSubBrightness((u8) -6);
    ButtonPanel_SetFlag2(&self->panel);
}
CLEAN_AS(func_ov105_0229c3c8, LetterStorage_BeginPanelDim)

/* func_ov105_0229c3ec: the page's sound, the popup and the cursor sprite hidden, state 0x0b
 * (written directly, not through MenuScene_SetState), phase 1 and the held letter hidden. */
void LetterStorage_ShowPage(LetterStorage *self)
{
    SoundSys_PlaySe(data_ov105_0229f85c[self->page]);
    Popup_Hide(&self->popup, 1);
    LetterStorage_HideCursorSprite(self);
    self->base.state = 0x0b;
    MenuScene_SetPhase(scene_of(self), 1);
    LetterStorage_SetFlags(self, LETTER_STORAGE_FLAG_HELD_HIDDEN);
}
CLEAN_AS(func_ov105_0229c3ec, LetterStorage_ShowPage)

/* func_ov105_0229c438: the touch at (x, y) on the tab of the page not shown (its first OBJ,
 * drawn at 0x80, 0x60, with 2 pixels of margin) makes that page the one shown; 1 then, else
 * 0. */
int LetterStorage_PageTabAtTouch(LetterStorage *self, int x, int y)
{
    for (int i = 0; i < LETTER_STORE_PAGES; i++) {
        if (i != self->page &&
            OamBuffer_ObjContains(&data_ov105_0229fa80[i * LETTER_STORAGE_TAB_OBJS], x - 0x80, y - 0x60, 2, 2) != 0) {
            self->page = (u8) i;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov105_0229c438, LetterStorage_PageTabAtTouch)

/* func_ov105_0229c490: the popup and the cursor sprite hidden, a wipe out on window 2. */
void LetterStorage_StartPageWipeOut(LetterStorage *self)
{
    Popup_Hide(&self->popup, 1);
    LetterStorage_HideCursorSprite(self);
    MenuScene_StartWipeOnWindow2(scene_of(self), 2, 0, 2, 0x30);
    MenuScene_SetWipeExtent(scene_of(self), 0xc0);
}
CLEAN_AS(func_ov105_0229c490, LetterStorage_StartPageWipeOut)

/* func_ov105_0229c4cc: the shown page's 25 letters handed to the letters object, its
 * background characters loaded on layer 4, a covered wipe in on window 2, layer 4 shown. */
void LetterStorage_StartPageWipeIn(LetterStorage *self)
{
    func_ov094_0229b288(self->letters, &self->stored[self->page * LETTER_STORE_PAGE_LETTERS]);
    DisplayLayer_LoadCharsFromFile(data_ov105_0229f890[self->page], data_021fbe94, 4, 0x1e2, 0x1e2, 0x1ed);
    MenuScene_StartWipeCoveredOnWindow2(scene_of(self), 2, 0, 2, 0x30);
    MenuScene_SetWipeExtent(scene_of(self), 0xc0);
    DisplayLayer_Show(4);
    LetterStorage_SetFlags(self, LETTER_STORAGE_FLAG_PAGE_WIPE);
    func_ov105_0229ed78(self);
}
CLEAN_AS(func_ov105_0229c4cc, LetterStorage_StartPageWipeIn)

/* func_ov105_0229c55c: the two tabs drawn on the touch screen, 0x80 right of the wipe's x: the
 * shown page's 2 pixels lower than the other, its second OBJ in palette 4 (5 for the other). */
void LetterStorage_DrawPageTabs(LetterStorage *self)
{
    int x = (int) ((u32) self->wipe_x + 0x80);

    for (int i = 0; i < LETTER_STORE_PAGES; i++) {
        const OamEntry *objs = &data_ov105_0229fa80[i * LETTER_STORAGE_TAB_OBJS];
        int y;
        int palette;
        if (i == self->page) {
            y = 0x52;
            palette = 4;
        } else {
            y = 0x50;
            palette = 5;
        }
        OamBuffer_DrawObjAffine(1, &objs[0], x, y, -1, 1, NULL);
        OamBuffer_DrawObjAffine(1, &objs[1], x, y, palette, 1, NULL);
        OamBuffer_DrawObjAffine(1, &objs[2], x, 0x50, -1, 1, NULL);
    }
}
CLEAN_AS(func_ov105_0229c55c, LetterStorage_DrawPageTabs)

/* func_ov105_0229c5fc: sound 0x2a, the panel's button 4 selected, state 0x12 (written
 * directly), sub state 0x1b. */
void LetterStorage_PressPanelButton4(LetterStorage *self)
{
    SoundSys_PlaySe(0x2a);
    ButtonPanel_Select(&self->panel, 4);
    self->base.state = 0x12;
    MenuScene_SetSubState(scene_of(self), 0x1b);
}
CLEAN_AS(func_ov105_0229c5fc, LetterStorage_PressPanelButton4)

/* func_ov105_0229c62c: sound 0x27, the panel's button 3 selected, state 4 (written directly),
 * flag 0x100 cleared, sub state 0x1b. */
void LetterStorage_PressPanelButton3(LetterStorage *self)
{
    SoundSys_PlaySe(0x27);
    ButtonPanel_Select(&self->panel, 3);
    self->base.state = 4;
    LetterStorage_ClearFlags(self, LETTER_STORAGE_FLAG_100);
    MenuScene_SetSubState(scene_of(self), 0x1b);
}
CLEAN_AS(func_ov105_0229c62c, LetterStorage_PressPanelButton3)

/* func_ov105_0229c668: sound 0x29, the panel's button 9 selected, sub state 0x1b, then state
 * 0x0e (written directly). */
void LetterStorage_PressPanelButton9(LetterStorage *self)
{
    SoundSys_PlaySe(0x29);
    ButtonPanel_Select(&self->panel, 9);
    MenuScene_SetSubState(scene_of(self), 0x1b);
    self->base.state = 0x0e;
}
CLEAN_AS(func_ov105_0229c668, LetterStorage_PressPanelButton9)

/* func_ov105_0229c694: nothing (called by the setup, func_ov105_0229eb54). */
void LetterStorage_DoNothing(LetterStorage *self)
{
    (void) self;
}
CLEAN_AS(func_ov105_0229c694, LetterStorage_DoNothing)

/* func_ov105_0229c698 (action 3) */
void LetterStorage_RunActionMenu(LetterStorage *self)
{
    LetterStorage_OpenFixedMenu(self);
}
CLEAN_AS(func_ov105_0229c698, LetterStorage_RunActionMenu)

/* func_ov105_0229c6a0 (action 2): the letter of the place whose choice is open picked up and
 * held where that place is (2 pixels up and left when state flag 2 is set), sub state 0x1c. */
void LetterStorage_PickUpSlotLetter(LetterStorage *self)
{
    u8 place = self->slot;
    LetterStorage_PickUpLetter(self, place);
    self->held_x = LetterStorage_PlaceX(self, place);
    self->held_y = LetterStorage_PlaceY(self, place);
    if (StateFlags_Test2() != 0) {
        self->held_x -= 2;
        self->held_y -= 2;
    }
    MenuScene_SetSubState(scene_of(self), 0x1c);
    func_ov094_0229b1d8(self->letters);
}
CLEAN_AS(func_ov105_0229c6a0, LetterStorage_PickUpSlotLetter)

/* func_ov105_0229c710: sub state 0x1a, the label button's state 2, sound 0x29. */
void LetterStorage_PressLabelButton(LetterStorage *self)
{
    MenuScene_SetSubState(scene_of(self), 0x1a);
    /* The button's base is main's labelled sprite (label_button.h). */
    LabelSprite_SetState((LabelSprite *) (void *) &self->button, 2);
    SoundSys_PlaySe(0x29);
}
CLEAN_AS(func_ov105_0229c710, LetterStorage_PressLabelButton)

/* func_ov105_0229c734 (action 1): state 4, phase 1, flag 0x100. */
void LetterStorage_RunAction1(LetterStorage *self)
{
    MenuScene_SetState(scene_of(self), 4);
    MenuScene_SetPhase(scene_of(self), 1);
    LetterStorage_SetFlags(self, LETTER_STORAGE_FLAG_100);
}
CLEAN_AS(func_ov105_0229c734, LetterStorage_RunAction1)

/* func_ov105_0229c758: the cursor moved by `keys` (KeyRepeat_Has*) in the part of the scene it
 * is in; `mode` 0 lets it go down to LETTER_STORAGE_BELOW. The wrap flags are cleared first.
 * 1 when the cursor changed place; 0 at once when `keys` is 0. */
int LetterStorage_MoveCursor(LetterStorage *self, int keys, int mode)
{
    u8 before = self->cursor;

    LetterStorage_ClearFlags(self, LETTER_STORAGE_FLAGS_WRAPPED);
    if (keys == 0) {
        return 0;
    }
    if (LetterStorage_IsCarriedPlace(self, self->cursor) != 0) {
        LetterStorage_MoveCursorInCarried(self, keys, mode);
    } else if (LetterStorage_IsPagePlace(self, self->cursor) != 0) {
        LetterStorage_MoveCursorInPage(self, keys, mode);
        /* Up from the top row reaches a tab. */
        if (LetterStorage_IsTabPlace(self, self->cursor) != 0 && mode == 1) {
            Glider_SetAnim(&self->cursor_sprite, 1);
        }
    } else if (LetterStorage_IsBelowPlace(self, self->cursor) != 0) {
        LetterStorage_MoveCursorBelow(self, keys);
    } else if (LetterStorage_IsTabPlace(self, self->cursor) != 0) {
        LetterStorage_MoveCursorInTabs(self, keys);
        if (LetterStorage_IsTabPlace(self, self->cursor) == 0 && mode == 1) {
            CellLayerSprite_SetAnimAtEnd((CellLayerSprite *) (void *) &self->cursor_sprite, 4);
        }
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov105_0229c758, LetterStorage_MoveCursor)

/* func_ov105_0229c82c: left and right between the two tabs (no wrap); down from a tab to the
 * page's top row (0x3e to 0x24, 0x3f to 0x25). */
void LetterStorage_MoveCursorInTabs(LetterStorage *self, int keys)
{
    if (KeyRepeat_HasLeft(keys) != 0) {
        if (self->cursor > LETTER_STORAGE_TAB_FIRST) {
            self->cursor--;
        }
    } else if (KeyRepeat_HasRight(keys) != 0) {
        if (self->cursor < LETTER_STORAGE_TAB_LAST) {
            self->cursor++;
        }
    }
    if (KeyRepeat_HasDown(keys) != 0) {
        self->cursor -= LETTER_STORAGE_TAB_FIRST - LETTER_STORAGE_PAGE_FIRST;
    }
}
CLEAN_AS(func_ov105_0229c82c, LetterStorage_MoveCursorInTabs)

/* func_ov105_0229c888: up from LETTER_STORAGE_BELOW goes to the carried letters' last place
 * (0x22, their bottom left), the cursor sprite turning to set A. */
void LetterStorage_MoveCursorBelow(LetterStorage *self, int keys)
{
    if (KeyRepeat_HasUp(keys) != 0) {
        Glider_TurnToSetA(&self->cursor_sprite);
        self->cursor = 0x22;
    }
}
CLEAN_AS(func_ov105_0229c888, LetterStorage_MoveCursorBelow)

/* func_ov105_0229c8b4: the cursor on the page (5 rows of 5). Left of the left column goes to
 * the carried letters' right column of the same row (LETTER_STORAGE_FLAG_WRAPPED_LEFT), right
 * of the right column to their left column (no flag). Up and down are taken only when the move
 * stayed on the page and did not wrap: up from the top row goes to the tab above (columns 0-1
 * to page 0's tab, 2-4 to page 1's), down from the bottom row to LETTER_STORAGE_BELOW when
 * `mode` is 0, the cursor sprite turning to set B. */
void LetterStorage_MoveCursorInPage(LetterStorage *self, int keys, int mode)
{
    int column = (int) self->cursor - LETTER_STORAGE_PAGE_FIRST;
    int row = 0;
    while (column >= LETTER_STORAGE_PAGE_COLUMNS) {
        row++;
        column -= LETTER_STORAGE_PAGE_COLUMNS;
    }

    if (KeyRepeat_HasLeft(keys) != 0) {
        if (column <= 0) {
            self->cursor = (u8) (row * 2 + LETTER_STORAGE_CARRIED_FIRST + 1);
            LetterStorage_SetFlags(self, LETTER_STORAGE_FLAG_WRAPPED_LEFT);
            return;
        }
        self->cursor--;
        column--;
    } else if (KeyRepeat_HasRight(keys) != 0) {
        if (column >= LETTER_STORAGE_PAGE_COLUMNS - 1) {
            self->cursor = (u8) (row * 2 + LETTER_STORAGE_CARRIED_FIRST);
            return;
        }
        self->cursor++;
        column++;
    }

    if (LetterStorage_IsPagePlace(self, self->cursor) == 0 ||
        LetterStorage_TestFlags(self, LETTER_STORAGE_FLAGS_WRAPPED) != 0) {
        return;
    }
    if (KeyRepeat_HasUp(keys) != 0) {
        if (row > 0) {
            self->cursor -= LETTER_STORAGE_PAGE_COLUMNS;
        } else if (column < 2) {
            self->cursor = (u8) (column + LETTER_STORAGE_TAB_FIRST);
        } else {
            self->cursor = LETTER_STORAGE_TAB_LAST;
        }
    } else if (KeyRepeat_HasDown(keys) != 0) {
        if (row < LETTER_STORAGE_ROWS - 1) {
            self->cursor += LETTER_STORAGE_PAGE_COLUMNS;
        } else if (mode == 0) {
            self->cursor = LETTER_STORAGE_BELOW;
            Glider_TurnToSetB(&self->cursor_sprite);
        }
    }
}
CLEAN_AS(func_ov105_0229c8b4, LetterStorage_MoveCursorInPage)

/* func_ov105_0229c9ac: the cursor on the carried letters (5 rows of 2). Left of the left column
 * goes to the page's right column of the same row (no flag), right of the right column to its
 * left column (LETTER_STORAGE_FLAG_WRAPPED_RIGHT). Up and down are taken only when the move
 * stayed on the carried letters and did not wrap: up stops at the top row, down from the
 * bottom row goes to LETTER_STORAGE_BELOW when `mode` is 0, the cursor sprite turning to set B. */
void LetterStorage_MoveCursorInCarried(LetterStorage *self, int keys, int mode)
{
    int index = (int) self->cursor - LETTER_STORAGE_CARRIED_FIRST;
    int column = index & 1;
    /* The ROM shifts arithmetically; `index` is 0-9 for the places this is called on. */
    int row = index >> 1;

    if (KeyRepeat_HasLeft(keys) != 0) {
        if (column <= 0) {
            self->cursor = (u8) (row * LETTER_STORAGE_PAGE_COLUMNS + LETTER_STORAGE_PAGE_FIRST + 4);
            return;
        }
        self->cursor -= 1;
    } else if (KeyRepeat_HasRight(keys) != 0) {
        if (column >= 1) {
            self->cursor = (u8) (row * LETTER_STORAGE_PAGE_COLUMNS + LETTER_STORAGE_PAGE_FIRST);
            LetterStorage_SetFlags(self, LETTER_STORAGE_FLAG_WRAPPED_RIGHT);
            return;
        }
        self->cursor += 1;
    }

    if (LetterStorage_IsCarriedPlace(self, self->cursor) == 0 ||
        LetterStorage_TestFlags(self, LETTER_STORAGE_FLAGS_WRAPPED) != 0) {
        return;
    }
    if (KeyRepeat_HasUp(keys) != 0) {
        if (row > 0) {
            self->cursor -= LETTER_STORAGE_CARRIED_COLUMNS;
        }
    } else if (KeyRepeat_HasDown(keys) != 0) {
        if (row < LETTER_STORAGE_ROWS - 1) {
            self->cursor += LETTER_STORAGE_CARRIED_COLUMNS;
        } else if (mode == 0) {
            self->cursor = LETTER_STORAGE_BELOW;
            Glider_TurnToSetB(&self->cursor_sprite);
        }
    }
}
CLEAN_AS(func_ov105_0229c9ac, LetterStorage_MoveCursorInCarried)

/* func_ov105_0229ca8c: the fixed choice (its first row set apart): texts 0x1a and 0x19 cancel,
 * text 0x15 picks the letter up. */
void LetterStorage_OpenFixedMenu(LetterStorage *self)
{
    LetterStorage_SetFlags(self, LETTER_STORAGE_FLAG_FIXED_MENU);
    ChoiceEntries_Clear(&self->entries, LETTER_STORAGE_ACTION_CANCEL);
    ChoiceEntries_Add(&self->entries, 0x1a, LETTER_STORAGE_ACTION_CANCEL);
    ChoiceEntries_Add(&self->entries, 0x15, LETTER_STORAGE_ACTION_PICK_UP);
    ChoiceEntries_Add(&self->entries, 0x19, LETTER_STORAGE_ACTION_CANCEL);
    LetterStorage_ShowChoice(self, 0);
}
CLEAN_AS(func_ov105_0229ca8c, LetterStorage_OpenFixedMenu)

/* func_ov105_0229cadc: the choice of the letter at `place`: text 0 (action 0) when state flag 2
 * is set; text 0x17 (state 7) or 0x14 (another state but 0) for action 1; text 0x15 for the
 * fixed menu when the letter has no item and its state is 1, 3, 4 or 6; text 2 to cancel. The
 * cursor sprite is hidden, the popup too unless the choice goes above it. */
void LetterStorage_OpenLetterMenu(LetterStorage *self, int place, int above_popup)
{
    LetterStorage_ClearFlags(self, LETTER_STORAGE_FLAG_FIXED_MENU);
    self->slot = (u8) place;
    ChoiceEntries_Clear(&self->entries, LETTER_STORAGE_ACTION_CANCEL);
    Letter *letter = LetterStorage_PlaceLetter(self, place);
    if (StateFlags_Test2() != 0) {
        ChoiceEntries_Add(&self->entries, 0, LETTER_STORAGE_ACTION_0);
    }
    int state = Letter_State(letter);
    if (state != 0) {
        if (state == 7) {
            ChoiceEntries_Add(&self->entries, 0x17, LETTER_STORAGE_ACTION_1);
        } else {
            ChoiceEntries_Add(&self->entries, 0x14, LETTER_STORAGE_ACTION_1);
        }
    }
    if (Letter_Item(letter) == LETTER_STORAGE_NO_ITEM && (state == 3 || state == 6 || state == 1 || state == 4)) {
        ChoiceEntries_Add(&self->entries, 0x15, LETTER_STORAGE_ACTION_MENU);
    }
    ChoiceEntries_Add(&self->entries, 2, LETTER_STORAGE_ACTION_CANCEL);
    LetterStorage_HideCursorSprite(self);
    if (above_popup == 0) {
        Popup_Hide(&self->popup, 1);
    }
    LetterStorage_ShowChoice(self, above_popup);
}
CLEAN_AS(func_ov105_0229cadc, LetterStorage_OpenLetterMenu)

/* func_ov105_0229cbb0: the cancel action, the cursor sprite put back at the cursor, the choice
 * asked to close, sub state 0x18. */
void LetterStorage_CancelChoice(LetterStorage *self)
{
    self->action = LETTER_STORAGE_ACTION_CANCEL;
    LetterStorage_PlaceCursorSprite(self);
    PagedChoice_RequestClose(choice_of(self), 0);
    MenuScene_SetSubState(scene_of(self), 0x18);
}
CLEAN_AS(func_ov105_0229cbb0, LetterStorage_CancelChoice)

/* func_ov105_0229cbe0: the entries shown in the choice (the first row set apart for the fixed
 * menu), placed above the popup or beside the open place, asked to open; sub state 0x16. */
void LetterStorage_ShowChoice(LetterStorage *self, int above_popup)
{
    int fixed = LetterStorage_TestFlags(self, LETTER_STORAGE_FLAG_FIXED_MENU);
    PagedChoice_ShowEntries(choice_of(self), &self->entries, fixed);
    int x = LetterStorage_PlaceX(self, self->slot);
    int y = LetterStorage_PlaceY(self, self->slot);
    if (above_popup != 0) {
        PagedChoice_PlaceAboveWindow(choice_of(self), &self->popup);
    } else {
        PagedChoice_PlaceBeside(choice_of(self), x, y);
    }
    PagedChoice_RequestOpen(choice_of(self), 0);
    MenuScene_SetSubState(scene_of(self), 0x16);
}
CLEAN_AS(func_ov105_0229cbe0, LetterStorage_ShowChoice)

/* func_ov105_0229cc5c: the action picked (`action`); any value above 3 cancels. */
void LetterStorage_RunAction(LetterStorage *self)
{
    switch (self->action) {
        case LETTER_STORAGE_ACTION_0:
            LetterStorage_RunAction0(self);
            break;
        case LETTER_STORAGE_ACTION_1:
            LetterStorage_RunAction1(self);
            break;
        case LETTER_STORAGE_ACTION_PICK_UP:
            LetterStorage_PickUpSlotLetter(self);
            break;
        case LETTER_STORAGE_ACTION_MENU:
            LetterStorage_RunActionMenu(self);
            break;
        default:
            LetterStorage_EndAction(self);
            break;
    }
}
CLEAN_AS(func_ov105_0229cc5c, LetterStorage_RunAction)

/* func_ov105_0229cca8: the popup hidden, the sub state to go back to kept, `target` kept, the
 * cursor sprite's animation 6, sub state 0x13. */
void LetterStorage_BeginSubState13(LetterStorage *self, u8 target)
{
    Popup_Hide(&self->popup, 1);
    self->return_state = self->base.sub_state;
    self->target = target;
    Glider_SetAnim(&self->cursor_sprite, 6);
    MenuScene_SetSubState(scene_of(self), 0x13);
}
CLEAN_AS(func_ov105_0229cca8, LetterStorage_BeginSubState13)

/* func_ov105_0229ccf4: the popup hidden, `target` kept, the cursor sprite's animation 5, sub
 * state 0x12. */
void LetterStorage_BeginSubState12(LetterStorage *self, char target)
{
    Popup_Hide(&self->popup, 1);
    self->target = (u8) target;
    Glider_SetAnim(&self->cursor_sprite, 5);
    MenuScene_SetSubState(scene_of(self), 0x12);
}
CLEAN_AS(func_ov105_0229ccf4, LetterStorage_BeginSubState12)

/* func_ov105_0229cd30 (action 0): the cursor sprite's animation 4, sub state 0x10, the stored
 * letters marked to be written back. */
void LetterStorage_RunAction0(LetterStorage *self)
{
    Glider_SetAnim(&self->cursor_sprite, 4);
    MenuScene_SetSubState(scene_of(self), 0x10);
    LetterStorage_SetFlags(self, LETTER_STORAGE_FLAG_CHANGED);
}
CLEAN_AS(func_ov105_0229cd30, LetterStorage_RunAction0)

/* func_ov105_0229cd5c */
void LetterStorage_BeginSubState0f(LetterStorage *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(scene_of(self), 0x0f);
}
CLEAN_AS(func_ov105_0229cd5c, LetterStorage_BeginSubState0f)

/* func_ov105_0229cd7c */
void LetterStorage_BeginSubState0e(LetterStorage *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(scene_of(self), 0x0e);
}
CLEAN_AS(func_ov105_0229cd7c, LetterStorage_BeginSubState0e)

/* func_ov105_0229cd9c: the first animation of the cursor sprite's set, then its update. */
void LetterStorage_ShowCursorFirstOfSet(LetterStorage *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    update_cursor_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov105_0229cd9c, LetterStorage_ShowCursorFirstOfSet)

/* func_ov105_0229cdbc: the cursor sprite put at the cursor, animation 1. */
void LetterStorage_PlaceCursorSprite(LetterStorage *self)
{
    int x = LetterStorage_CursorSpriteX(self);
    int y = LetterStorage_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, 1);
}
CLEAN_AS(func_ov105_0229cdbc, LetterStorage_PlaceCursorSprite)

/* func_ov105_0229cdf0: the cursor sprite put at the choice's row 1 for the fixed menu (its
 * first row set apart), else at row 0; animation 7. */
void LetterStorage_PointAtDefaultRow(LetterStorage *self)
{
    self->choice_row = LetterStorage_TestFlags(self, LETTER_STORAGE_FLAG_FIXED_MENU) != 0 ? 1 : 0;
    int x = PagedChoice_TextX(choice_of(self));
    int y = PagedChoice_RowY(choice_of(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, 7);
}
CLEAN_AS(func_ov105_0229cdf0, LetterStorage_PointAtDefaultRow)

/* func_ov105_0229ce54: the cancel action, the choice's last row picked and the cursor sprite
 * put at it, showing animation 8 from its last frame; sub state 0x17. */
void LetterStorage_PointAtLastRow(LetterStorage *self)
{
    self->action = LETTER_STORAGE_ACTION_CANCEL;
    self->choice_row = PagedChoice_PickLastRow(choice_of(self), 1);
    int x = PagedChoice_TextX(choice_of(self));
    int y = PagedChoice_RowY(choice_of(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    CellLayerSprite_SetAnimAtEnd((CellLayerSprite *) (void *) &self->cursor_sprite, 8);
    MenuScene_SetSubState(scene_of(self), 0x17);
}
CLEAN_AS(func_ov105_0229ce54, LetterStorage_PointAtLastRow)

/* func_ov105_0229cebc: the cursor sprite moved to the choice row in 2 steps; the sub state to
 * go back to kept, sub state 0x0d. */
void LetterStorage_GlideToRow(LetterStorage *self)
{
    int x = PagedChoice_TextX(choice_of(self));
    int y = PagedChoice_RowY(choice_of(self), self->choice_row);
    Glider_MoveTo(&self->cursor_sprite, x, y, 2);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(scene_of(self), 0x0d);
}
CLEAN_AS(func_ov105_0229cebc, LetterStorage_GlideToRow)

/* func_ov105_0229cf10: the cursor sprite eased to (x, y) in 3 steps; the sub state to go back
 * to kept, sub state 0x0d. */
void LetterStorage_EaseCursorSpriteTo(LetterStorage *self, int x, int y)
{
    Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(scene_of(self), 0x0d);
}
CLEAN_AS(func_ov105_0229cf10, LetterStorage_EaseCursorSpriteTo)

/* func_ov105_0229cf48: the cursor sprite put at the cursor at once when flag 8 is set (which
 * this clears), else eased there as LetterStorage_EaseCursorSpriteTo does. */
void LetterStorage_GlideToCursor(LetterStorage *self)
{
    if (LetterStorage_TestFlags(self, LETTER_STORAGE_FLAG_08) != 0) {
        int x = LetterStorage_CursorSpriteX(self);
        int y = LetterStorage_CursorSpriteY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
        LetterStorage_ClearFlags(self, LETTER_STORAGE_FLAG_08);
    } else {
        int x = LetterStorage_CursorSpriteX(self);
        int y = LetterStorage_CursorSpriteY(self);
        Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
        self->return_state = self->base.sub_state;
        MenuScene_SetSubState(scene_of(self), 0x0d);
    }
}
CLEAN_AS(func_ov105_0229cf48, LetterStorage_GlideToCursor)

/* func_ov105_0229cfc0: the cursor sprite's animation 0, then its update. */
void LetterStorage_HideCursorSprite(LetterStorage *self)
{
    Glider_SetAnim(&self->cursor_sprite, 0);
    update_cursor_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov105_0229cfc0, LetterStorage_HideCursorSprite)

/* func_ov105_0229cfe4: the cursor sprite's y, the cursor's place's. */
int LetterStorage_CursorSpriteY(LetterStorage *self)
{
    return LetterStorage_PlaceY(self, self->cursor);
}
CLEAN_AS(func_ov105_0229cfe4, LetterStorage_CursorSpriteY)

/* func_ov105_0229cff4: the cursor sprite's x, the cursor's place's plus 8; a screen width (256)
 * further right when this move wrapped right, further left when it wrapped left, so the sprite
 * slides there. */
int LetterStorage_CursorSpriteX(LetterStorage *self)
{
    int x = LetterStorage_PlaceX(self, self->cursor);
    if (LetterStorage_TestFlags(self, LETTER_STORAGE_FLAG_WRAPPED_RIGHT) != 0) {
        x += 0x100;
    } else if (LetterStorage_TestFlags(self, LETTER_STORAGE_FLAG_WRAPPED_LEFT) != 0) {
        x -= 0x100;
    }
    return x + 8;
}
CLEAN_AS(func_ov105_0229cff4, LetterStorage_CursorSpriteX)

/* func_ov105_0229d03c: the cursor sprite put at the cursor, animation 7 on LETTER_STORAGE_BELOW
 * and 1 elsewhere, then its set's first animation shown. */
void LetterStorage_ShowCursorAtCursor(LetterStorage *self)
{
    int x = LetterStorage_CursorSpriteX(self);
    int y = LetterStorage_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (LetterStorage_IsBelowPlace(self, self->cursor) != 0) {
        Glider_SetAnim(&self->cursor_sprite, 7);
    } else {
        Glider_SetAnim(&self->cursor_sprite, 1);
    }
    LetterStorage_ShowCursorFirstOfSet(self);
}
CLEAN_AS(func_ov105_0229d03c, LetterStorage_ShowCursorAtCursor)

/* func_ov105_0229d094: when a letter is held, it changes places with the letter at `place`:
 * the held one is copied aside, the place's letter picked up and the copy put at `place`. */
void LetterStorage_SwapHeldWith(LetterStorage *self, int place)
{
    if (self->held_kind == LETTER_STORAGE_HELD_LETTER) {
        Letter_Assign(&self->swapped, &self->held);
        LetterStorage_PickUpLetter(self, place);
        LetterStorage_PutLetterAt(self, place, &self->swapped);
    }
}
CLEAN_AS(func_ov105_0229d094, LetterStorage_SwapHeldWith)

/* func_ov105_0229d0d4: the held letter, if any, put at `place`; nothing held after. */
void LetterStorage_PutHeldAt(LetterStorage *self, int place)
{
    if (self->held_kind == LETTER_STORAGE_HELD_LETTER) {
        LetterStorage_PutLetterAt(self, place, &self->held);
    }
    self->held_kind = LETTER_STORAGE_HELD_NONE;
}
CLEAN_AS(func_ov105_0229d0d4, LetterStorage_PutHeldAt)

/* func_ov105_0229d0f8: the letter at `place` (a carried or page letter; other places are left
 * alone) copied into `held` and taken from the letters object. */
void LetterStorage_PickUpLetter(LetterStorage *self, int place)
{
    if (!is_letter_place(self, place)) {
        return;
    }
    int index = LetterStorage_LetterIndex(self, (unsigned int) place);
    self->held_kind = LETTER_STORAGE_HELD_LETTER;
    Letter_Assign(&self->held, func_ov094_0229b8d8(self->letters, index));
    func_ov094_0229b890(self->letters, index);
}
CLEAN_AS(func_ov105_0229d0f8, LetterStorage_PickUpLetter)

/* func_ov105_0229d154: the held letter drawn where the glide is. */
void LetterStorage_FollowGlide(LetterStorage *self)
{
    self->held_x = Glide_X(&self->glide);
    self->held_y = Glide_Y(&self->glide);
}
CLEAN_AS(func_ov105_0229d154, LetterStorage_FollowGlide)

/* func_ov105_0229d17c: the held letter drawn at the cursor sprite's frame, 2 left and 4 up (22
 * more up while the sprite shows animation 1). */
void LetterStorage_FollowCursorSprite(LetterStorage *self)
{
    self->held_x = Glider_FrameX(&self->cursor_sprite) - 2;
    self->held_y = Glider_FrameY(&self->cursor_sprite) - 4;
    if (CellLayerSprite_AnimNumber((CellLayerSprite *) (void *) &self->cursor_sprite) == 1) {
        self->held_y -= 0x16;
    }
}
CLEAN_AS(func_ov105_0229d17c, LetterStorage_FollowCursorSprite)

/* func_ov105_0229d1c4: the held letter drawn at the touch plus the grab's offset. */
void LetterStorage_FollowTouch(LetterStorage *self)
{
    self->held_x = (s32) ((u32) self->grab_dx + data_021f6c58);
    self->held_y = (s32) ((u32) self->grab_dy + data_021f6c54);
}
CLEAN_AS(func_ov105_0229d1c4, LetterStorage_FollowTouch)

/* func_ov105_0229d1f0: the held letter drawn by the letters object, unless hidden. */
void LetterStorage_DrawHeld(LetterStorage *self)
{
    if (LetterStorage_TestFlags(self, LETTER_STORAGE_FLAG_HELD_HIDDEN) != 0) {
        return;
    }
    if (self->held_kind == LETTER_STORAGE_HELD_LETTER) {
        func_ov094_0229b5e8(self->letters, self->held_x, self->held_y, &self->held);
    }
}
CLEAN_AS(func_ov105_0229d1f0, LetterStorage_DrawHeld)

/* func_ov105_0229d230: the popup queued to tell of the cursor's letter place, when it holds a
 * letter (LetterStorage_PlaceIsEmpty is 0); cleared on any other place. */
void LetterStorage_UpdatePopup(LetterStorage *self)
{
    if (is_letter_place(self, self->cursor)) {
        if (LetterStorage_PlaceIsEmpty(self, self->cursor) != 0) {
            Popup_ClearQueued(&self->popup);
        } else {
            self->popup_place = self->cursor;
            Popup_Queue(&self->popup);
        }
    } else {
        Popup_ClearQueued(&self->popup);
    }
}
CLEAN_AS(func_ov105_0229d230, LetterStorage_UpdatePopup)

/* func_ov105_0229d294: the popup's window put 0x6d left and 0x78 up of its place (8 more up
 * when state flag 2 is set), and filled by the letters object for a letter place. */
void LetterStorage_PlacePopup(LetterStorage *self)
{
    int x = LetterStorage_PlaceX(self, self->popup_place) - 0x6d;
    int y = LetterStorage_PlaceY(self, self->popup_place) - 0x78;
    if (StateFlags_Test2() != 0) {
        y -= 8;
    }
    /* The popup's base is main's sliding window (popup.h). */
    SlidingWindow_SetPlace((SlidingWindow *) (void *) &self->popup, x, y);
    if (is_letter_place(self, self->popup_place)) {
        int index = LetterStorage_LetterIndex(self, self->popup_place);
        func_ov094_0229b9b4(self->letters, &self->popup, index);
    }
}
CLEAN_AS(func_ov105_0229d294, LetterStorage_PlacePopup)

/* func_ov105_0229d310: whether the touch at data_021f6c60/5c is more than 8 pixels from the
 * one at data_021f6c58/54, in x or in y. */
static int distance(int a, int b)
{
    return a > b ? a - b : b - a;
}

int LetterStorage_TouchMoved(LetterStorage *self)
{
    (void) self;
    return distance(data_021f6c60, data_021f6c58) > 8 || distance(data_021f6c5c, data_021f6c54) > 8;
}
CLEAN_AS(func_ov105_0229d310, LetterStorage_TouchMoved)

/* func_ov105_0229d354: a letter place highlighted by the letters object. */
void LetterStorage_HighlightPlace(LetterStorage *self, int place)
{
    if (!is_letter_place(self, place)) {
        return;
    }
    func_ov094_0229b938(self->letters, LetterStorage_LetterIndex(self, (unsigned int) place));
}
CLEAN_AS(func_ov105_0229d354, LetterStorage_HighlightPlace)

/* func_ov105_0229d390: the highlights of the grid and the letters cleared. */
void LetterStorage_ClearHighlights(LetterStorage *self)
{
    func_ov094_0229ab0c(self->grid);
    func_ov094_0229b944(self->letters);
}
CLEAN_AS(func_ov105_0229d390, LetterStorage_ClearHighlights)

/* func_ov105_0229d3b4: a letter place selected in the letters object (the grid's selection
 * cleared); any other place clears both (LetterStorage_ClearSelection). */
void LetterStorage_SelectPlace(LetterStorage *self, int place)
{
    if (is_letter_place(self, place)) {
        int index = LetterStorage_LetterIndex(self, (unsigned int) place);
        func_ov094_0229b950(self->letters, index);
        func_ov094_0229ab5c(self->grid);
    } else {
        LetterStorage_ClearSelection(self);
    }
}
CLEAN_AS(func_ov105_0229d3b4, LetterStorage_SelectPlace)

/* The pen (autoload_2/input.c): down, and gone down or up this frame. */
extern u8 data_021fbdd8;
extern u8 data_021fbddc;

/* The buttons the scenes read in `pressed`. */
#define LETTER_STORAGE_PAD_A 0x0001
#define LETTER_STORAGE_PAD_B 0x0002
#define LETTER_STORAGE_PAD_START 0x0008
#define LETTER_STORAGE_PAD_Y 0x0800

/* The panel's buttons offered by LetterStorage_OfferPanelButtons (and button 9), the selected
 * one, and the label button's anchor the cursor sprite points at. */
#define LETTER_STORAGE_PANEL_BUTTON_3 3
#define LETTER_STORAGE_PANEL_BUTTON_4 4
#define LETTER_STORAGE_PANEL_SELECTED (-1)
#define LETTER_STORAGE_LABEL_ANCHOR 1

/* What the letters object answers for no letter under a touch. */
#define LETTER_STORAGE_LETTERS_NO_INDEX 0x37

/* The objects of ov094's: whether the letters object's letter `index` holds none, whether it is
 * marked (by func_ov094_0229b794), its x and y, the letter under a touch among the carried ones
 * (only for x from 0xc0) and among the page's, a letter put in, the carried letters of some
 * states marked, its selection cleared, its count down after a letter is let go; the grid's
 * slots 0 to 14 set by func_ov094_0229a888; the sounds 0xd, 0xc and 0xe (RtcSendPxiCommand). */
extern int func_ov094_0229b30c(void *letters, int index);
extern int func_ov094_0229b788(void *letters, int index);
extern int func_ov094_0229b384(void *letters, int index);
extern int func_ov094_0229b328(void *letters, int index);
extern int func_ov094_0229bba4(void *letters, int x, int y);
extern int func_ov094_0229bb70(void *letters, int x, int y);
extern void func_ov094_0229b8b4(void *letters, int index, Letter *letter);
extern void func_ov094_0229b794(void *letters, unsigned int states);
extern void func_ov094_0229b98c(void *letters);
extern int func_ov094_0229b19c(void *letters);
extern void func_ov094_0229a898(void *grid, int first, int last);
extern void func_ov094_022999c0(void);
extern void func_ov094_022999cc(void);
extern void func_ov094_022999d8(void);

/* The scene's sub state runner (func_ov105_0229f25c, a member function). */
extern void _ZN18Obj_ov105_0229fad019func_ov105_0229f25cEv(LetterStorage *self);

static CellLayerSprite *cursor_cells(LetterStorage *self)
{
    /* The cursor sprite's base is main's cell layer sprite (glide.h). */
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

/* The value kept with choice row `row` (ChoiceEntries.values), read as the ROM does at
 * 0x28f5 + row. */
static u8 entry_value(LetterStorage *self, int row)
{
    const u8 *bytes = (const u8 *) self;
    return bytes[offsetof(LetterStorage, entries) + offsetof(ChoiceEntries, values) + (size_t) row];
}

/* The first OBJ of a tab's three, as the ROM finds it: 3 OBJs further per place after 0x3e. */
static const OamEntry *tab_obj(int place)
{
    uintptr_t base = (uintptr_t) data_ov105_0229fa80;
    u32 offset = (u32) (place - LETTER_STORAGE_TAB_FIRST) * (u32) (LETTER_STORAGE_TAB_OBJS * sizeof(OamEntry));
    return (const OamEntry *) (base + offset);
}

/* A choice row picked with the sound of a pick, except for the row of action 2 (sound 0x24
 * instead); its action kept; sub state 0x17. */
static void pick_choice_row(LetterStorage *self, int row)
{
    self->action = entry_value(self, row);
    int with_sound = 1;
    if (self->action == LETTER_STORAGE_ACTION_PICK_UP) {
        with_sound = 0;
        SoundSys_PlaySe(0x24);
    }
    PagedChoice_PickRowWithSound(choice_of(self), row, with_sound);
    MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_CHOICE_CLOSE);
}

/* func_ov105_0229d404: the selections of the grid and the letters cleared. */
void LetterStorage_ClearSelection(LetterStorage *self)
{
    func_ov094_0229ab5c(self->grid);
    func_ov094_0229b98c(self->letters);
}
CLEAN_AS(func_ov105_0229d404, LetterStorage_ClearSelection)

/* func_ov105_0229d428: whether a letter place holds no letter (by the letters object); other
 * places count as empty. */
int LetterStorage_PlaceIsEmpty(LetterStorage *self, int place)
{
    if (is_letter_place(self, place)) {
        return func_ov094_0229b30c(self->letters, LetterStorage_LetterIndex(self, (unsigned int) place));
    }
    return 1;
}
CLEAN_AS(func_ov105_0229d428, LetterStorage_PlaceIsEmpty)

/* func_ov105_0229d468: whether a carried letter is marked by the letters object
 * (LetterStorage_MarkCarriedLetters); such a letter is not moved. 0 for any other place. */
int LetterStorage_PlaceIsMarked(LetterStorage *self, int place)
{
    if (LetterStorage_IsCarriedPlace(self, (unsigned int) place)) {
        return func_ov094_0229b788(self->letters, LetterStorage_LetterIndex(self, (unsigned int) place));
    }
    return 0;
}
CLEAN_AS(func_ov105_0229d468, LetterStorage_PlaceIsMarked)

/* func_ov105_0229d49c (by the setup, func_ov105_0229f150): the grid's slots 0 to 14 set by
 * func_ov094_0229a888, and the carried letters of states 7 and 8 marked (its states flag 4). */
void LetterStorage_MarkCarriedLetters(LetterStorage *self)
{
    func_ov094_0229a898(self->grid, 0, 0xe);
    func_ov094_0229b794(self->letters, 4);
}
CLEAN_AS(func_ov105_0229d49c, LetterStorage_MarkCarriedLetters)

/* func_ov105_0229d4c4: the y of `place`: a letter's by the letters object less 0x10, 0xb6 for
 * LETTER_STORAGE_BELOW, a tab's first OBJ's plus 0x58, else 0. */
int LetterStorage_PlaceY(LetterStorage *self, int place)
{
    if (is_letter_place(self, place)) {
        return func_ov094_0229b328(self->letters, LetterStorage_LetterIndex(self, (unsigned int) place)) - 0x10;
    }
    if (place == LETTER_STORAGE_BELOW) {
        return 0xb6;
    }
    if (LetterStorage_IsTabPlace(self, place)) {
        return OamBuffer_ObjY(tab_obj(place)) + 0x58;
    }
    return 0;
}
CLEAN_AS(func_ov105_0229d4c4, LetterStorage_PlaceY)

/* func_ov105_0229d530: the x of `place`: a letter's by the letters object, 0xbc for
 * LETTER_STORAGE_BELOW, a tab's first OBJ's plus 0x80, else 0. */
int LetterStorage_PlaceX(LetterStorage *self, int place)
{
    if (is_letter_place(self, place)) {
        return func_ov094_0229b384(self->letters, LetterStorage_LetterIndex(self, (unsigned int) place));
    }
    if (place == LETTER_STORAGE_BELOW) {
        return 0xbc;
    }
    if (LetterStorage_IsTabPlace(self, place)) {
        return OamBuffer_ObjX(tab_obj(place)) + 0x80;
    }
    return 0;
}
CLEAN_AS(func_ov105_0229d530, LetterStorage_PlaceX)

/* func_ov105_0229d59c: the letter of a letter place (the letters object's), else NULL. */
Letter *LetterStorage_PlaceLetter(LetterStorage *self, int place)
{
    if (is_letter_place(self, place)) {
        return func_ov094_0229b8d8(self->letters, LetterStorage_LetterIndex(self, (unsigned int) place));
    }
    return NULL;
}
CLEAN_AS(func_ov105_0229d59c, LetterStorage_PlaceLetter)

/* func_ov105_0229d5dc: a copy of `letter` put at a letter place by the letters object. Put on
 * a tab, it goes back into the stored letters where the held letter was taken from (`held_from`
 * on `held_page`), whichever tab it is.
 * REQUIRES: on a tab, `held_from` is a page place (the scene glides only a letter of the page to
 * a tab, LetterStorage_MoveHeldByKeys); the ROM writes before `stored` otherwise. */
void LetterStorage_PutLetterAt(LetterStorage *self, int place, Letter *letter)
{
    if (is_letter_place(self, place)) {
        func_ov094_0229b8b4(self->letters, LetterStorage_LetterIndex(self, (unsigned int) place), letter);
    } else if (LetterStorage_IsTabPlace(self, place)) {
        int index = (self->held_from - LETTER_STORAGE_PAGE_FIRST) + LETTER_STORE_PAGE_LETTERS * self->held_page;
        Letter_Assign(&self->stored[index], letter);
    }
}
CLEAN_AS(func_ov105_0229d5dc, LetterStorage_PutLetterAt)

/* func_ov105_0229d650: the held letter put down at `place`; a letter there is copied aside
 * (`swapped`) and put at the held letter's place (`unk_2b7`) first. Always 1. */
int LetterStorage_PutHeldLetterAt(LetterStorage *self, int place)
{
    if (LetterStorage_PlaceIsEmpty(self, place) == 0) {
        Letter_Assign(&self->swapped, LetterStorage_PlaceLetter(self, place));
        LetterStorage_PutLetterAt(self, self->unk_2b7, &self->swapped);
    }
    LetterStorage_PutHeldAt(self, place);
    return 1;
}
CLEAN_AS(func_ov105_0229d650, LetterStorage_PutHeldLetterAt)

/* func_ov105_0229d69c: the letter place under the touch at (x, y), by the letters object (the
 * carried letters first, then the page's); with `with_letter`, only one holding a letter.
 * LETTER_STORAGE_NO_PLACE for none. */
int LetterStorage_LetterPlaceAtTouch(LetterStorage *self, int x, int y, int with_letter)
{
    int index = func_ov094_0229bba4(self->letters, x, y);
    if (index == LETTER_STORAGE_LETTERS_NO_INDEX) {
        index = func_ov094_0229bb70(self->letters, x, y);
    }
    if (index == LETTER_STORAGE_LETTERS_NO_INDEX) {
        return LETTER_STORAGE_NO_PLACE;
    }
    if (with_letter != 0 && func_ov094_0229b30c(self->letters, index) != 0) {
        return LETTER_STORAGE_NO_PLACE;
    }
    return LetterStorage_LetterPlace(self, (unsigned int) index);
}
CLEAN_AS(func_ov105_0229d69c, LetterStorage_LetterPlaceAtTouch)

/* func_ov105_0229d6f8: the place of the letters object's letter `index` (0-9 carried, 10-34 on
 * the page), else LETTER_STORAGE_NO_PLACE. */
u8 LetterStorage_LetterPlace(LetterStorage *self, unsigned int index)
{
    (void) self;
    if (index <= LETTER_STORAGE_PAGE_LAST - LETTER_STORAGE_CARRIED_FIRST) {
        return (u8) (index + LETTER_STORAGE_CARRIED_FIRST);
    }
    return LETTER_STORAGE_NO_PLACE;
}
CLEAN_AS(func_ov105_0229d6f8, LetterStorage_LetterPlace)

/* func_ov105_0229d718: the letters object's index of a letter place, else 0. */
u8 LetterStorage_LetterIndex(LetterStorage *self, unsigned int place)
{
    (void) self;
    if (place >= LETTER_STORAGE_CARRIED_FIRST && place <= LETTER_STORAGE_PAGE_LAST) {
        return (u8) (place - LETTER_STORAGE_CARRIED_FIRST);
    }
    return 0;
}
CLEAN_AS(func_ov105_0229d718, LetterStorage_LetterIndex)

/* func_ov105_0229d73c: whether `place` is a tab.
 * QUIRK: only the low byte of `place` is compared (0x13e is a tab too). */
int LetterStorage_IsTabPlace(LetterStorage *self, int place)
{
    (void) self;
    return (u8) ((unsigned int) place - LETTER_STORAGE_TAB_FIRST) <= LETTER_STORAGE_TAB_LAST - LETTER_STORAGE_TAB_FIRST;
}
CLEAN_AS(func_ov105_0229d73c, LetterStorage_IsTabPlace)

/* func_ov105_0229d750 */
int LetterStorage_IsBelowPlace(LetterStorage *self, int place)
{
    (void) self;
    return place == LETTER_STORAGE_BELOW;
}
CLEAN_AS(func_ov105_0229d750, LetterStorage_IsBelowPlace)

/* func_ov105_0229d75c */
int LetterStorage_IsPagePlace(LetterStorage *self, unsigned int place)
{
    (void) self;
    return place >= LETTER_STORAGE_PAGE_FIRST && place <= LETTER_STORAGE_PAGE_LAST;
}
CLEAN_AS(func_ov105_0229d75c, LetterStorage_IsPagePlace)

/* func_ov105_0229d76c */
int LetterStorage_IsCarriedPlace(LetterStorage *self, unsigned int place)
{
    (void) self;
    return place >= LETTER_STORAGE_CARRIED_FIRST && place <= LETTER_STORAGE_CARRIED_LAST;
}
CLEAN_AS(func_ov105_0229d76c, LetterStorage_IsCarriedPlace)

/* func_ov105_0229d77c (by func_ov105_0229eaa4 and func_ov105_0229eb08): the layer load task at
 * 0x2c4 (a LayerTaskPair by its size) taken off the main loop's queue and reset. */
void LetterStorage_EndLayerTask(LetterStorage *self)
{
    LayerTask_End((LayerTask *) (void *) self->unk_2c4);
}
CLEAN_AS(func_ov105_0229d77c, LetterStorage_EndLayerTask)

/* func_ov105_0229d78c: the first place of the shown page whose stored letter is empty (state
 * 0), else LETTER_STORAGE_NO_PLACE. */
u8 LetterStorage_FirstEmptyPagePlace(LetterStorage *self)
{
    const Letter *page = &self->stored[self->page * LETTER_STORE_PAGE_LETTERS];
    for (int i = 0; i < LETTER_STORE_PAGE_LETTERS; i++) {
        if (Letter_State(&page[i]) == 0) {
            return (u8) (i + LETTER_STORAGE_PAGE_FIRST);
        }
    }
    return LETTER_STORAGE_NO_PLACE;
}
CLEAN_AS(func_ov105_0229d78c, LetterStorage_FirstEmptyPagePlace)

/* func_ov105_0229d7d4: the carried place of the current player's first free letter slot (their
 * pockets', not the letters object's), else LETTER_STORAGE_NO_PLACE. */
int LetterStorage_FreeCarriedPlace(LetterStorage *self)
{
    (void) self;
    int index = CurrentPockets_FreeLetterIndex();
    if (index == -1) {
        return LETTER_STORAGE_NO_PLACE;
    }
    return (u8) (index + LETTER_STORAGE_CARRIED_FIRST);
}
CLEAN_AS(func_ov105_0229d7d4, LetterStorage_FreeCarriedPlace)

/* func_ov105_0229d7f4: the letter at `from` picked up and drawn there, then glided to `to` in
 * 4 steps. */
void LetterStorage_HoldAndGlide(LetterStorage *self, int from, int to)
{
    LetterStorage_PickUpLetter(self, from);
    self->held_x = LetterStorage_PlaceX(self, from);
    self->held_y = LetterStorage_PlaceY(self, from);
    LetterStorage_GlideHeldTo(self, to, 4);
}
CLEAN_AS(func_ov105_0229d7f4, LetterStorage_HoldAndGlide)

/* func_ov105_0229d82c: the dragged letter let go with the touch at `x`: one from the page
 * dropped over the carried letters (x from 0xc0) goes to the player's first free letter slot,
 * a carried one dropped beside them to the shown page's first empty place; else, or when there
 * is none, it glides back to `place`. 4 steps. */
void LetterStorage_DropHeldAtTouch(LetterStorage *self, int place, int x)
{
    int to = LETTER_STORAGE_NO_PLACE;
    if (x >= 0xc0) {
        if (LetterStorage_IsPagePlace(self, (unsigned int) place)) {
            to = LetterStorage_FreeCarriedPlace(self);
        }
    } else if (LetterStorage_IsCarriedPlace(self, (unsigned int) place)) {
        to = LetterStorage_FirstEmptyPagePlace(self);
    }
    if (to != LETTER_STORAGE_NO_PLACE) {
        place = to;
    }
    LetterStorage_GlideHeldTo(self, place, 4);
}
CLEAN_AS(func_ov105_0229d82c, LetterStorage_DropHeldAtTouch)

/* func_ov105_0229d870: the held letter glides from where it is drawn to `place` (kept as its
 * place, `unk_2b7`) in `steps` steps, the first taken now; to a tab it aims 8 pixels higher and
 * LETTER_STORAGE_FLAG_GLIDE_TO_TAB is set (cleared otherwise). Sub state 0x15 follows it. */
void LetterStorage_GlideHeldTo(LetterStorage *self, int place, int steps)
{
    self->unk_2b7 = (u8) place;
    Glide_SetPlace(&self->glide, self->held_x, self->held_y);
    int y = LetterStorage_PlaceY(self, place);
    if (LetterStorage_IsTabPlace(self, place)) {
        y -= 8;
    }
    int x = LetterStorage_PlaceX(self, place);
    Glide_MoveTo(&self->glide, x, y, steps);
    Glide_Step(&self->glide);
    LetterStorage_FollowGlide(self);
    if (LetterStorage_IsTabPlace(self, place)) {
        LetterStorage_SetFlags(self, LETTER_STORAGE_FLAG_GLIDE_TO_TAB);
    } else {
        LetterStorage_ClearFlags(self, LETTER_STORAGE_FLAG_GLIDE_TO_TAB);
    }
    MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_HELD_GLIDE);
}
CLEAN_AS(func_ov105_0229d870, LetterStorage_GlideHeldTo)

/* func_ov105_0229d908: the letter at `place` picked up with the cursor (from the shown page),
 * the popup hidden; when it is held, the sub state to go back to is 8. It follows the cursor
 * sprite; sound 0xd. */
void LetterStorage_PickUpWithCursor(LetterStorage *self, u8 place)
{
    self->unk_2b7 = place;
    self->held_from = place;
    self->held_page = self->page;
    Popup_Hide(&self->popup, 1);
    LetterStorage_PickUpLetter(self, place);
    if (self->held_kind == LETTER_STORAGE_HELD_LETTER) {
        self->return_state = LETTER_STORAGE_SUB_HOLD;
    }
    LetterStorage_FollowCursorSprite(self);
    func_ov094_022999c0();
}
CLEAN_AS(func_ov105_0229d908, LetterStorage_PickUpWithCursor)

/* func_ov105_0229d970: the letter at `place` picked up with the touch (from the shown page),
 * the stored letters marked changed, the popup hidden; when it is held, sub state 4 drags it.
 * It follows the touch; sound 0xd. */
void LetterStorage_PickUpWithTouch(LetterStorage *self, u8 place)
{
    LetterStorage_SetFlags(self, LETTER_STORAGE_FLAG_CHANGED);
    self->unk_2b7 = place;
    self->held_from = place;
    self->held_page = self->page;
    Popup_Hide(&self->popup, 1);
    LetterStorage_PickUpLetter(self, place);
    if (self->held_kind == LETTER_STORAGE_HELD_LETTER) {
        MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_DRAG);
    }
    LetterStorage_FollowTouch(self);
    func_ov094_022999c0();
}
CLEAN_AS(func_ov105_0229d970, LetterStorage_PickUpWithTouch)

/* func_ov105_0229d9e0: `place` touched: sub state 1, the offset from the touch to the place
 * kept, the popup told of the place and shown, its choice opening in 2 frames; the letter may
 * be dragged (LETTER_STORAGE_FLAG_DRAGGABLE, sound 0xc) unless it is marked. */
void LetterStorage_TouchPlace(LetterStorage *self, int place)
{
    self->touch_place = (u8) place;
    MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_TOUCH_HOLD);
    u8 touch_x = data_021f6c58;
    u8 touch_y = data_021f6c54;
    self->grab_dx = LetterStorage_PlaceX(self, self->touch_place) - touch_x;
    self->grab_dy = LetterStorage_PlaceY(self, self->touch_place) - touch_y;
    self->popup_place = (u8) place;
    Popup_Queue(&self->popup);
    Popup_ShowQueued(&self->popup);
    self->open_delay = 2;
    if (LetterStorage_PlaceIsMarked(self, place)) {
        LetterStorage_ClearFlags(self, LETTER_STORAGE_FLAG_DRAGGABLE);
    } else {
        LetterStorage_SetFlags(self, LETTER_STORAGE_FLAG_DRAGGABLE);
        func_ov094_022999cc();
    }
}
CLEAN_AS(func_ov105_0229d9e0, LetterStorage_TouchPlace)

/* func_ov105_0229da7c (by func_ov105_0229ecd8): the panel's buttons 3 and 4 offered, to the
 * touch while state flag 2 is clear, else to the keys. */
void LetterStorage_OfferPanelButtons(LetterStorage *self)
{
    if (StateFlags_IsClear2()) {
        LetterStorage_OfferPanelButtonsByTouch(self);
    } else {
        LetterStorage_OfferPanelButtonsByKeys(self);
    }
}
CLEAN_AS(func_ov105_0229da7c, LetterStorage_OfferPanelButtons)

/* func_ov105_0229da9c: the key repeat reset, button 4 chosen and the cursor sprite shown on it
 * (animation 1, updated); sub state 0x1e. */
void LetterStorage_OfferPanelButtonsByKeys(LetterStorage *self)
{
    MenuScene_ResetKeyRepeat(scene_of(self));
    self->unk_2c2 = 1;
    Glider_SetAnim(&self->cursor_sprite, 1);
    update_cursor_sprite(&self->cursor_sprite);
    int x = ButtonPanel_ButtonX(&self->panel, LETTER_STORAGE_PANEL_BUTTON_4);
    int y = ButtonPanel_ButtonY(&self->panel, LETTER_STORAGE_PANEL_BUTTON_4);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_PANEL_BY_KEYS);
}
CLEAN_AS(func_ov105_0229da9c, LetterStorage_OfferPanelButtonsByKeys)

/* func_ov105_0229dafc: the cursor sprite hidden; sub state 0x1d. */
void LetterStorage_OfferPanelButtonsByTouch(LetterStorage *self)
{
    LetterStorage_HideCursorSprite(self);
    MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_PANEL_BY_TOUCH);
}
CLEAN_AS(func_ov105_0229dafc, LetterStorage_OfferPanelButtonsByTouch)

/* func_ov105_0229db14: the action ends: back to sub state 0 with the cursor sprite hidden while
 * state flag 2 is clear, else to sub state 7 with it at the cursor. */
void LetterStorage_EndAction(LetterStorage *self)
{
    if (StateFlags_IsClear2()) {
        LetterStorage_EndActionHidden(self);
    } else {
        LetterStorage_EndActionAtCursor(self);
    }
}
CLEAN_AS(func_ov105_0229db14, LetterStorage_EndAction)

/* func_ov105_0229db34: no popup place, the cursor sprite shown at the cursor, the key repeat
 * reset, the popup told of the cursor's place, sub state 7 and the cursor's place selected. */
void LetterStorage_EndActionAtCursor(LetterStorage *self)
{
    self->popup_place = LETTER_STORAGE_NO_PLACE;
    LetterStorage_ShowCursorAtCursor(self);
    MenuScene_ResetKeyRepeat(scene_of(self));
    LetterStorage_UpdatePopup(self);
    MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_BROWSE);
    LetterStorage_SelectPlace(self, self->cursor);
}
CLEAN_AS(func_ov105_0229db34, LetterStorage_EndActionAtCursor)

/* func_ov105_0229db70 */
void LetterStorage_EndActionHidden(LetterStorage *self)
{
    LetterStorage_HideCursorSprite(self);
    LetterStorage_ClearSelection(self);
    MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_TOUCH_IDLE);
}
CLEAN_AS(func_ov105_0229db70, LetterStorage_EndActionHidden)

/* func_ov105_0229db8c (sub state 0x1f): once the cursor sprite's animation has ended, the
 * chosen panel button pressed (`unk_2c2` set: button 4, clear: button 3). */
void LetterStorage_PressChosenPanelButton(LetterStorage *self)
{
    if (CellLayerSprite_IsDone(cursor_cells(self))) {
        if (self->unk_2c2 != 0) {
            LetterStorage_PressPanelButton4(self);
        } else {
            LetterStorage_PressPanelButton3(self);
        }
    }
}
CLEAN_AS(func_ov105_0229db8c, LetterStorage_PressChosenPanelButton)

/* func_ov105_0229dbc0 (sub state 0x1e): panel buttons 3 and 4 by the keys. A touch gives them
 * to the touch; A presses the chosen one (sub state 0x1f, once the sprite's second animation of
 * its set has played), B presses button 4 and START button 3 at once; left chooses button 3,
 * right button 4 (`unk_2c2` 0 or 1), the cursor sprite easing to it. */
void LetterStorage_ChoosePanelButtonByKeys(LetterStorage *self)
{
    if (MenuScene_TakeTouch(scene_of(self))) {
        LetterStorage_OfferPanelButtonsByTouch(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & LETTER_STORAGE_PAD_A) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_PANEL_PRESS);
        return;
    }
    if (pressed & LETTER_STORAGE_PAD_B) {
        LetterStorage_HideCursorSprite(self);
        LetterStorage_PressPanelButton4(self);
        return;
    }
    if (pressed & LETTER_STORAGE_PAD_START) {
        LetterStorage_HideCursorSprite(self);
        LetterStorage_PressPanelButton3(self);
        return;
    }

    u8 before = self->unk_2c2;
    int keys = (int) MenuScene_LatchRepeatedKeys(scene_of(self));
    if (KeyRepeat_HasLeft(keys)) {
        if (self->unk_2c2 != 0) {
            self->unk_2c2--;
        }
    } else if (KeyRepeat_HasRight(keys)) {
        if (self->unk_2c2 < 1) {
            self->unk_2c2++;
        }
    }
    if (before != self->unk_2c2) {
        int button = self->unk_2c2 != 0 ? LETTER_STORAGE_PANEL_BUTTON_4 : LETTER_STORAGE_PANEL_BUTTON_3;
        int x = ButtonPanel_ButtonX(&self->panel, button);
        int y = ButtonPanel_ButtonY(&self->panel, button);
        LetterStorage_EaseCursorSpriteTo(self, x, y);
    }
}
CLEAN_AS(func_ov105_0229dbc0, LetterStorage_ChoosePanelButtonByKeys)

/* func_ov105_0229dcc4 (sub state 0x1d): panel buttons 3 and 4 by the touch. A button gives them
 * to the keys; the pen going down on button 3, then on button 4, presses it. */
void LetterStorage_ChoosePanelButtonByTouch(LetterStorage *self)
{
    if (MenuScene_TakeButtons(scene_of(self), 1)) {
        LetterStorage_OfferPanelButtonsByKeys(self);
        return;
    }
    if (data_021fbdd8 == 0 || data_021fbddc == 0) {
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, LETTER_STORAGE_PANEL_BUTTON_3)) {
        LetterStorage_PressPanelButton3(self);
    }
    /* Not an else: both run when both buttons answer the touch. */
    if (ButtonPanel_IsTouched(&self->panel, LETTER_STORAGE_PANEL_BUTTON_4)) {
        LetterStorage_PressPanelButton4(self);
    }
}
CLEAN_AS(func_ov105_0229dcc4, LetterStorage_ChoosePanelButtonByTouch)

/* func_ov105_0229dd30 (sub state 0x1c, after LetterStorage_PickUpSlotLetter): once the
 * letters object's count down ends, the held letter is let go (nothing held, the stored letters
 * marked changed) and the action ends. */
void LetterStorage_WaitLetGo(LetterStorage *self)
{
    if (func_ov094_0229b19c(self->letters)) {
        LetterStorage_SetFlags(self, LETTER_STORAGE_FLAG_CHANGED);
        self->held_kind = LETTER_STORAGE_HELD_NONE;
        LetterStorage_EndAction(self);
    }
}
CLEAN_AS(func_ov105_0229dd30, LetterStorage_WaitLetGo)

/* func_ov105_0229dd68 (sub state 0x1b): while the selected panel button's press plays, the
 * cursor sprite (when shown) follows it, offset by the press's frame; after, the sprite is
 * hidden and phase 1 begins. */
void LetterStorage_FollowPanelPress(LetterStorage *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) != 0) {
        if (CellLayerSprite_AnimNumber(cursor_cells(self)) != 0) {
            int frame = ButtonPanel_SelectedPressFrame(&self->panel);
            int x = ButtonPanel_ButtonX(&self->panel, LETTER_STORAGE_PANEL_SELECTED);
            int y = ButtonPanel_ButtonY(&self->panel, LETTER_STORAGE_PANEL_SELECTED);
            Glider_PlaceAt(&self->cursor_sprite, frame + x, frame + y);
        }
    } else {
        LetterStorage_HideCursorSprite(self);
        MenuScene_SetPhase(scene_of(self), 1);
    }
}
CLEAN_AS(func_ov105_0229dd68, LetterStorage_FollowPanelPress)

/* func_ov105_0229ddd4 (sub state 0x1a): while the label button's animation plays, the cursor
 * sprite (when shown) follows its anchor; after, the sprite is hidden, state 9 and phase 1. */
void LetterStorage_FollowLabelPress(LetterStorage *self)
{
    if (LabelButton_StepAnimation(&self->button) != 0) {
        if (CellLayerSprite_AnimNumber(cursor_cells(self)) != 0) {
            int x = LabelButton_AnchorX(&self->button, LETTER_STORAGE_LABEL_ANCHOR);
            int y = LabelButton_AnchorY(&self->button, LETTER_STORAGE_LABEL_ANCHOR);
            Glider_PlaceAt(&self->cursor_sprite, x, y);
        }
    } else {
        LetterStorage_HideCursorSprite(self);
        MenuScene_SetState(scene_of(self), 9);
        MenuScene_SetPhase(scene_of(self), 1);
    }
}
CLEAN_AS(func_ov105_0229ddd4, LetterStorage_FollowLabelPress)

/* func_ov105_0229de3c (sub state 0x19): once the error message is done, back to the sub state
 * kept, the cursor sprite's window flag set. */
void LetterStorage_WaitError(LetterStorage *self)
{
    if (ErrorMessage_Update(&self->error, 0)) {
        MenuScene_SetSubState(scene_of(self), self->return_state);
        CellLayerSprite_SetWindow(cursor_cells(self));
    }
}
CLEAN_AS(func_ov105_0229de3c, LetterStorage_WaitError)

/* func_ov105_0229de74 (sub state 0x18): the action picked runs once the choice is idle. */
void LetterStorage_RunActionWhenIdle(LetterStorage *self)
{
    if (PagedChoice_IsIdle(choice_of(self)) != 0) {
        LetterStorage_RunAction(self);
    }
}
CLEAN_AS(func_ov105_0229de74, LetterStorage_RunActionWhenIdle)

/* func_ov105_0229de94 (sub state 0x17): once the delay after the pick has run out, the choice
 * asked to close, the popup hidden, the cursor sprite (when shown) put back at the cursor; sub
 * state 0x18. */
void LetterStorage_CloseChoice(LetterStorage *self)
{
    if (PagedChoice_CountDown(choice_of(self)) != 0) {
        PagedChoice_RequestClose(choice_of(self), 0);
        Popup_Hide(&self->popup, 1);
        if (CellLayerSprite_AnimNumber(cursor_cells(self)) != 0) {
            LetterStorage_PlaceCursorSprite(self);
        }
        MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_CHOICE_RUN);
    }
}
CLEAN_AS(func_ov105_0229de94, LetterStorage_CloseChoice)

/* func_ov105_0229dee4 (sub state 0x16): once the choice is shown, it is run by the keys (the
 * cursor sprite at its default row, sub state 0x0b) when state flag 2 is set, else by the touch
 * (sub state 6). */
void LetterStorage_WaitChoiceShown(LetterStorage *self)
{
    if (PagedChoice_IsShown(choice_of(self)) != 0) {
        if (StateFlags_Test2()) {
            LetterStorage_PointAtDefaultRow(self);
            MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_CHOICE_BY_KEYS);
        } else {
            MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_CHOICE_BY_TOUCH);
        }
    }
}
CLEAN_AS(func_ov105_0229dee4, LetterStorage_WaitChoiceShown)

/* func_ov105_0229df20 (sub state 0x15): the held letter follows its glide. When the glide is
 * over the letter is put at its place (`unk_2b7`), the action ends, sound 0xe; a glide to a tab
 * first waits one more frame (LETTER_STORAGE_FLAG_GLIDE_TO_TAB cleared). */
void LetterStorage_StepHeldGlide(LetterStorage *self)
{
    if (Glide_Step(&self->glide) != 0) {
        if (LetterStorage_TestFlags(self, LETTER_STORAGE_FLAG_GLIDE_TO_TAB) != 0) {
            LetterStorage_ClearFlags(self, LETTER_STORAGE_FLAG_GLIDE_TO_TAB);
            LetterStorage_FollowGlide(self);
        } else {
            LetterStorage_PutHeldAt(self, self->unk_2b7);
            LetterStorage_EndAction(self);
            func_ov094_022999d8();
        }
    } else {
        LetterStorage_FollowGlide(self);
    }
}
CLEAN_AS(func_ov105_0229df20, LetterStorage_StepHeldGlide)

/* func_ov105_0229df7c (sub state 0x14): back to the sub state kept once the cursor sprite's
 * animation has ended; once its turn has settled, a hidden held letter is shown again (sound
 * 0xd) and follows the sprite. */
void LetterStorage_FinishSwap(LetterStorage *self)
{
    if (CellLayerSprite_IsDone(cursor_cells(self))) {
        MenuScene_SetSubState(scene_of(self), self->return_state);
    }
    if (Glider_IsTurnSettled(&self->cursor_sprite)) {
        if (LetterStorage_TestFlags(self, LETTER_STORAGE_FLAG_HELD_HIDDEN)) {
            LetterStorage_ClearFlags(self, LETTER_STORAGE_FLAG_HELD_HIDDEN);
            func_ov094_022999c0();
        }
        LetterStorage_FollowCursorSprite(self);
    }
}
CLEAN_AS(func_ov105_0229df7c, LetterStorage_FinishSwap)

/* func_ov105_0229dfd0 (sub state 0x13): unless the cursor sprite's turn is at its frame 2, the
 * held letter changes places with the one at `target`, the new held letter hidden for now, the
 * popup updated; sub state 0x14. At frame 2, sub state 7. */
void LetterStorage_Swap(LetterStorage *self)
{
    if (Glider_IsTurnAtFrame2(&self->cursor_sprite) == 0) {
        LetterStorage_SwapHeldWith(self, self->target);
        LetterStorage_SetFlags(self, LETTER_STORAGE_FLAG_HELD_HIDDEN);
        MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_SWAP_END);
        LetterStorage_UpdatePopup(self);
    } else {
        MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_BROWSE);
    }
}
CLEAN_AS(func_ov105_0229dfd0, LetterStorage_Swap)

/* func_ov105_0229e018 (sub state 0x12): while the cursor sprite's turn has not settled, the
 * held letter is put down at `target` when the cursor is on it (the popup updated, sub state 7,
 * sound 0xe), else glided there in 4 steps; once it has, the letter follows the sprite. */
void LetterStorage_PutDown(LetterStorage *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite) == 0) {
        u8 target = self->target;
        if (self->cursor == target) {
            LetterStorage_PutHeldLetterAt(self, target);
            LetterStorage_UpdatePopup(self);
            MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_BROWSE);
            func_ov094_022999d8();
        } else {
            LetterStorage_GlideHeldTo(self, target, 4);
        }
    } else {
        LetterStorage_FollowCursorSprite(self);
    }
}
CLEAN_AS(func_ov105_0229e018, LetterStorage_PutDown)

/* func_ov105_0229e070 (sub state 0x11): back to the sub state kept once the cursor sprite's
 * animation has ended; the held letter follows the sprite. */
void LetterStorage_FinishPickUp(LetterStorage *self)
{
    if (CellLayerSprite_IsDone(cursor_cells(self))) {
        MenuScene_SetSubState(scene_of(self), self->return_state);
    }
    LetterStorage_FollowCursorSprite(self);
}
CLEAN_AS(func_ov105_0229e070, LetterStorage_FinishPickUp)

/* func_ov105_0229e0a0 (sub state 0x10): once the cursor sprite's turn has settled, the letter
 * at the cursor is picked up; sub state 0x11. */
void LetterStorage_PickUpAtCursor(LetterStorage *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite)) {
        LetterStorage_PickUpWithCursor(self, self->cursor);
        MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_PICK_UP_END);
    }
}
CLEAN_AS(func_ov105_0229e0a0, LetterStorage_PickUpAtCursor)

/* func_ov105_0229e0d0 (sub state 0x0f): once the cursor sprite's animation has ended, its set's
 * first animation; sub state 8 while a letter is held, else 7. */
void LetterStorage_FinishPlacePress(LetterStorage *self)
{
    if (CellLayerSprite_IsDone(cursor_cells(self)) != 0) {
        LetterStorage_ShowCursorFirstOfSet(self);
        if (self->held_kind == LETTER_STORAGE_HELD_LETTER) {
            MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_HOLD);
        } else {
            MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_BROWSE);
        }
    }
}
CLEAN_AS(func_ov105_0229e0d0, LetterStorage_FinishPlacePress)

/* func_ov105_0229e110 (sub state 0x0e): once the cursor sprite's animation has ended, the place
 * is pressed: LETTER_STORAGE_BELOW presses panel button 9; a tab shows its page
 * (LetterStorage_ShowPage), or goes to sub state 0x0f when that page is shown already; other
 * places go to sub state 0x0f. */
void LetterStorage_PressPlace(LetterStorage *self)
{
    if (CellLayerSprite_IsDone(cursor_cells(self)) == 0) {
        return;
    }
    if (LetterStorage_IsBelowPlace(self, self->cursor)) {
        LetterStorage_PressPanelButton9(self);
    } else if (LetterStorage_IsTabPlace(self, self->cursor)) {
        int page = self->cursor - LETTER_STORAGE_TAB_FIRST;
        if (page == self->page) {
            LetterStorage_BeginSubState0f(self);
        } else {
            self->page = (u8) page;
            LetterStorage_ShowPage(self);
        }
    } else {
        LetterStorage_BeginSubState0f(self);
    }
}
CLEAN_AS(func_ov105_0229e110, LetterStorage_PressPlace)

/* func_ov105_0229e180 (sub state 0x0d): once the cursor sprite stops moving, back to the sub
 * state kept (the cursor's place selected for sub state 7), which runs at once; the held letter
 * follows the sprite. */
void LetterStorage_WaitCursorSprite(LetterStorage *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(scene_of(self), self->return_state);
        if (self->return_state == LETTER_STORAGE_SUB_BROWSE) {
            LetterStorage_SelectPlace(self, self->cursor);
        }
        _ZN18Obj_ov105_0229fad019func_ov105_0229f25cEv(self);
    }
    LetterStorage_FollowCursorSprite(self);
}
CLEAN_AS(_ZN18Obj_ov105_0229fad019func_ov105_0229e180Ev, LetterStorage_WaitCursorSprite)

/* func_ov105_0229e1cc (sub state 0x0c): once the cursor sprite's animation has ended, the
 * choice row it points at is picked. */
void LetterStorage_PickChoiceRow(LetterStorage *self)
{
    if (CellLayerSprite_IsDone(cursor_cells(self)) == 0) {
        return;
    }
    pick_choice_row(self, self->choice_row);
}
CLEAN_AS(func_ov105_0229e1cc, LetterStorage_PickChoiceRow)

/* func_ov105_0229e230 (sub state 0x0b): the choice by the keys. A touch cancels it; the keys
 * move the row (from row 1 round for the fixed menu), the cursor sprite gliding to it; A plays
 * the sprite's second animation of its set and picks the row (sub state 0x0c), B points at the
 * last row. */
void LetterStorage_ChooseByKeys(LetterStorage *self)
{
    if (MenuScene_TakeTouch(scene_of(self))) {
        LetterStorage_CancelChoice(self);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(scene_of(self));
    u8 first = (u8) LetterStorage_TestFlags(self, LETTER_STORAGE_FLAG_FIXED_MENU);
    if (PagedChoice_MoveCursor(choice_of(self), keys, &self->choice_row, first)) {
        LetterStorage_GlideToRow(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & LETTER_STORAGE_PAD_A) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_CHOICE_PICK);
    } else if (pressed & LETTER_STORAGE_PAD_B) {
        LetterStorage_PointAtLastRow(self);
    }
}
CLEAN_AS(func_ov105_0229e230, LetterStorage_ChooseByKeys)

/* func_ov105_0229e2c0 (sub state 0x0a): the label button pressed once the cursor sprite's
 * animation has ended. */
void LetterStorage_WaitLabelPress(LetterStorage *self)
{
    if (CellLayerSprite_IsDone(cursor_cells(self))) {
        LetterStorage_PressLabelButton(self);
    }
}
CLEAN_AS(func_ov105_0229e2c0, LetterStorage_WaitLabelPress)

/* func_ov105_0229e2e0 (sub state 9): the label button by the keys. A hidden cursor sprite is
 * shown on its anchor (animation 1); a touch hides it (sub state 5); A or B plays the sprite's
 * second animation of its set, sub state 0x0a. */
void LetterStorage_LabelByKeys(LetterStorage *self)
{
    if (CellLayerSprite_AnimNumber(cursor_cells(self)) == 0) {
        int x = LabelButton_AnchorX(&self->button, LETTER_STORAGE_LABEL_ANCHOR);
        int y = LabelButton_AnchorY(&self->button, LETTER_STORAGE_LABEL_ANCHOR);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
        Glider_SetAnim(&self->cursor_sprite, 1);
    }
    if (MenuScene_TakeTouch(scene_of(self))) {
        LetterStorage_HideCursorSprite(self);
        MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_LABEL_BY_TOUCH);
    } else if (data_021fbe40.pressed & (LETTER_STORAGE_PAD_A | LETTER_STORAGE_PAD_B)) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_LABEL_PRESS);
    }
}
CLEAN_AS(func_ov105_0229e2e0, LetterStorage_LabelByKeys)

/* func_ov105_0229e374 (sub state 8): a held letter moved with the cursor. A move of the cursor
 * updates the popup and moves the sprite (the popup hidden, its queue kept). A on a letter place
 * that is not marked puts the letter down there (sub state 0x12) when it is empty, else swaps
 * (sub state 0x13); A on a tab presses it. B sends the letter back: one taken from the page not
 * shown glides to that page's tab; else it glides to its place when the sprite shows animation
 * 1, or is put down there. Else L and R turn the page, or the letter follows the sprite and a
 * queued popup is shown. */
void LetterStorage_MoveHeldByKeys(LetterStorage *self)
{
    if (LetterStorage_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(scene_of(self)), 1) != 0) {
        LetterStorage_UpdatePopup(self);
        LetterStorage_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & LETTER_STORAGE_PAD_A) {
        if (is_letter_place(self, self->cursor)) {
            if (LetterStorage_PlaceIsMarked(self, self->cursor) == 0) {
                if (LetterStorage_PlaceIsEmpty(self, self->cursor) != 0) {
                    LetterStorage_BeginSubState12(self, (char) self->cursor);
                } else {
                    LetterStorage_BeginSubState13(self, self->cursor);
                }
            }
        } else if (LetterStorage_IsTabPlace(self, self->cursor)) {
            LetterStorage_BeginSubState0e(self);
        }
        return;
    }
    if (pressed & LETTER_STORAGE_PAD_B) {
        if (LetterStorage_IsPagePlace(self, self->unk_2b7) && self->held_page != self->page) {
            LetterStorage_GlideHeldTo(self, (u8) (self->held_page + LETTER_STORAGE_TAB_FIRST), 4);
            return;
        }
        if (CellLayerSprite_AnimNumber(cursor_cells(self)) == 1) {
            LetterStorage_GlideHeldTo(self, self->unk_2b7, 4);
        } else {
            LetterStorage_BeginSubState12(self, (char) self->unk_2b7);
        }
        return;
    }
    if (LetterStorage_TurnPageByKeys(self) == 0) {
        LetterStorage_FollowCursorSprite(self);
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov105_0229e374, LetterStorage_MoveHeldByKeys)

/* func_ov105_0229e4a8 (sub state 7): the cursor moved by the keys, nothing held. A touch ends
 * the action without the sprite. A move updates the popup and moves the sprite (the popup
 * hidden, its queue kept). Unless the cursor's letter is marked: A on a letter opens its
 * choice, A below or on a tab presses the place; Y sends the letter across (a carried one to the
 * shown page's first empty place, one of the page to the player's first free letter slot), the
 * stored letters marked changed. Else START or B presses panel button 9, or L and R turn the
 * page, or a queued popup is shown. */
void LetterStorage_BrowseByKeys(LetterStorage *self)
{
    if (MenuScene_TakeTouch(scene_of(self))) {
        LetterStorage_EndActionHidden(self);
        Popup_Hide(&self->popup, 1);
        return;
    }
    if (LetterStorage_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(scene_of(self)), 0) != 0) {
        LetterStorage_UpdatePopup(self);
        LetterStorage_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    if (LetterStorage_PlaceIsMarked(self, self->cursor) == 0) {
        u16 pressed = data_021fbe40.pressed;
        if (pressed & LETTER_STORAGE_PAD_A) {
            if (is_letter_place(self, self->cursor)) {
                if (LetterStorage_PlaceIsEmpty(self, self->cursor) == 0) {
                    LetterStorage_OpenLetterMenu(self, self->cursor, 0);
                }
            } else if (LetterStorage_IsBelowPlace(self, self->cursor) || LetterStorage_IsTabPlace(self, self->cursor)) {
                LetterStorage_BeginSubState0e(self);
            }
            return;
        }
        if (pressed & LETTER_STORAGE_PAD_Y) {
            if (is_letter_place(self, self->cursor) && LetterStorage_PlaceIsEmpty(self, self->cursor) == 0) {
                int to;
                if (LetterStorage_IsCarriedPlace(self, self->cursor)) {
                    to = LetterStorage_FirstEmptyPagePlace(self);
                } else {
                    to = LetterStorage_FreeCarriedPlace(self);
                }
                if (to != LETTER_STORAGE_NO_PLACE) {
                    LetterStorage_HoldAndGlide(self, self->cursor, to);
                    Popup_Hide(&self->popup, 1);
                    LetterStorage_SetFlags(self, LETTER_STORAGE_FLAG_CHANGED);
                }
            }
            return;
        }
    }
    u16 pressed = data_021fbe40.pressed;
    if ((pressed & LETTER_STORAGE_PAD_START) || (pressed & LETTER_STORAGE_PAD_B)) {
        LetterStorage_HideCursorSprite(self);
        LetterStorage_PressPanelButton9(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    if (LetterStorage_TurnPageByKeys(self) == 0) {
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov105_0229e4a8, LetterStorage_BrowseByKeys)

/* func_ov105_0229e638 (sub state 6): the choice by the touch, once shown. A button cancels it;
 * the pen going down picks the row under it (the last one outside the window), but not the set
 * apart first row of the fixed menu. */
void LetterStorage_ChooseByTouch(LetterStorage *self)
{
    if (PagedChoice_IsShown(choice_of(self)) == 0) {
        return;
    }
    if (MenuScene_TakeButtons(scene_of(self), 1)) {
        LetterStorage_CancelChoice(self);
        return;
    }
    if (data_021fbdd8 == 0 || data_021fbddc == 0) {
        return;
    }
    int row = PagedChoice_RowAtOrLast(choice_of(self), data_021f6c58, data_021f6c54);
    if (row < 0) {
        return;
    }
    if (LetterStorage_TestFlags(self, LETTER_STORAGE_FLAG_FIXED_MENU) != 0 && row == 0) {
        return;
    }
    pick_choice_row(self, row);
}
CLEAN_AS(func_ov105_0229e638, LetterStorage_ChooseByTouch)

/* func_ov105_0229e6f4 (sub state 5): the label button by the touch. A button gives it to the
 * keys (sub state 9); a touch on it presses it. */
void LetterStorage_LabelByTouch(LetterStorage *self)
{
    if (MenuScene_TakeButtons(scene_of(self), 1)) {
        MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_LABEL_BY_KEYS);
    } else if (LabelButton_IsTouched(&self->button)) {
        LetterStorage_PressLabelButton(self);
    }
}
CLEAN_AS(func_ov105_0229e6f4, LetterStorage_LabelByTouch)

/* func_ov105_0229e728 (sub state 4): the held letter dragged with the touch, the highlights
 * cleared. The letter place under it (8 right and 0x18 below where it is drawn) is highlighted
 * while the pen is down. Let go on a place that is not marked, the letter is put down there
 * (sound 0xe) and the action ends; let go elsewhere, LetterStorage_DropHeldAtTouch sends it to
 * its place or across. */
void LetterStorage_DragHeld(LetterStorage *self)
{
    LetterStorage_FollowTouch(self);
    LetterStorage_ClearHighlights(self);
    int x = (int) ((u32) self->held_x + 8);
    int place = LetterStorage_LetterPlaceAtTouch(self, x, (int) ((u32) self->held_y + 0x18), 0);

    if (place == LETTER_STORAGE_NO_PLACE) {
        if (data_021fbdd8 == 0) {
            LetterStorage_DropHeldAtTouch(self, self->unk_2b7, x);
        }
        return;
    }
    if (data_021fbdd8 != 0) {
        LetterStorage_HighlightPlace(self, place);
        return;
    }
    if (LetterStorage_PlaceIsMarked(self, place) == 0 && LetterStorage_PutHeldLetterAt(self, place) != 0) {
        func_ov094_022999d8();
        LetterStorage_EndAction(self);
        return;
    }
    LetterStorage_DropHeldAtTouch(self, self->unk_2b7, x);
}
CLEAN_AS(func_ov105_0229e728, LetterStorage_DragHeld)

/* func_ov105_0229e7bc (sub state 3): once the popup is up, after `open_delay` more frames, the
 * touched place's choice opens above the popup; sub state 2. */
void LetterStorage_OpenTouchedChoice(LetterStorage *self)
{
    if (Popup_IsUp(&self->popup)) {
        if (self->open_delay != 0) {
            self->open_delay--;
        } else {
            LetterStorage_OpenLetterMenu(self, self->touch_place, 1);
            MenuScene_SetSubState(scene_of(self), LETTER_STORAGE_SUB_TOUCH_CHOICE);
        }
    }
}
CLEAN_AS(func_ov105_0229e7bc, LetterStorage_OpenTouchedChoice)
