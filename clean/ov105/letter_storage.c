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
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/label_sprite.h"
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

/* The scene's own, outside these functions: the kinds of place, the letters object's index of
 * a place, a place's coordinates (for the tabs, OBJ 0's), the letter of a place, whether a
 * place holds no letter, putting a letter at a place, and others. */
extern int func_ov105_0229d76c(LetterStorage *self, unsigned int place); /* 0x1a-0x23 */
extern int func_ov105_0229d75c(LetterStorage *self, unsigned int place); /* 0x24-0x3c */
extern int func_ov105_0229d750(LetterStorage *self, int place);          /* 0x3d */
extern int func_ov105_0229d73c(LetterStorage *self, int place);          /* 0x3e-0x3f */
extern u8 func_ov105_0229d718(LetterStorage *self, unsigned int place);
extern int func_ov105_0229d530(LetterStorage *self, int place); /* x */
extern int func_ov105_0229d4c4(LetterStorage *self, int place); /* y */
extern Letter *func_ov105_0229d59c(LetterStorage *self, int place);
extern int func_ov105_0229d428(LetterStorage *self, int place);
extern void func_ov105_0229d5dc(LetterStorage *self, int place, Letter *letter);
extern void func_ov105_0229d404(LetterStorage *self);
extern void func_ov105_0229db14(LetterStorage *self);
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
    return func_ov105_0229d76c(self, (unsigned int) place) != 0 || func_ov105_0229d75c(self, (unsigned int) place) != 0;
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
    self->held_x = func_ov105_0229d530(self, place);
    self->held_y = func_ov105_0229d4c4(self, place);
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
    if (func_ov105_0229d76c(self, self->cursor) != 0) {
        LetterStorage_MoveCursorInCarried(self, keys, mode);
    } else if (func_ov105_0229d75c(self, self->cursor) != 0) {
        LetterStorage_MoveCursorInPage(self, keys, mode);
        /* Up from the top row reaches a tab. */
        if (func_ov105_0229d73c(self, self->cursor) != 0 && mode == 1) {
            Glider_SetAnim(&self->cursor_sprite, 1);
        }
    } else if (func_ov105_0229d750(self, self->cursor) != 0) {
        LetterStorage_MoveCursorBelow(self, keys);
    } else if (func_ov105_0229d73c(self, self->cursor) != 0) {
        LetterStorage_MoveCursorInTabs(self, keys);
        if (func_ov105_0229d73c(self, self->cursor) == 0 && mode == 1) {
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

    if (func_ov105_0229d75c(self, self->cursor) == 0 || LetterStorage_TestFlags(self, LETTER_STORAGE_FLAGS_WRAPPED) != 0) {
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

    if (func_ov105_0229d76c(self, self->cursor) == 0 || LetterStorage_TestFlags(self, LETTER_STORAGE_FLAGS_WRAPPED) != 0) {
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
    Letter *letter = func_ov105_0229d59c(self, place);
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
    int x = func_ov105_0229d530(self, self->slot);
    int y = func_ov105_0229d4c4(self, self->slot);
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
            func_ov105_0229db14(self);
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
    return func_ov105_0229d4c4(self, self->cursor);
}
CLEAN_AS(func_ov105_0229cfe4, LetterStorage_CursorSpriteY)

/* func_ov105_0229cff4: the cursor sprite's x, the cursor's place's plus 8; a screen width (256)
 * further right when this move wrapped right, further left when it wrapped left, so the sprite
 * slides there. */
int LetterStorage_CursorSpriteX(LetterStorage *self)
{
    int x = func_ov105_0229d530(self, self->cursor);
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
    if (func_ov105_0229d750(self, self->cursor) != 0) {
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
        func_ov105_0229d5dc(self, place, &self->swapped);
    }
}
CLEAN_AS(func_ov105_0229d094, LetterStorage_SwapHeldWith)

/* func_ov105_0229d0d4: the held letter, if any, put at `place`; nothing held after. */
void LetterStorage_PutHeldAt(LetterStorage *self, int place)
{
    if (self->held_kind == LETTER_STORAGE_HELD_LETTER) {
        func_ov105_0229d5dc(self, place, &self->held);
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
    int index = func_ov105_0229d718(self, (unsigned int) place);
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
 * letter (func_ov105_0229d428 is 0); cleared on any other place. */
void LetterStorage_UpdatePopup(LetterStorage *self)
{
    if (is_letter_place(self, self->cursor)) {
        if (func_ov105_0229d428(self, self->cursor) != 0) {
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
    int x = func_ov105_0229d530(self, self->popup_place) - 0x6d;
    int y = func_ov105_0229d4c4(self, self->popup_place) - 0x78;
    if (StateFlags_Test2() != 0) {
        y -= 8;
    }
    /* The popup's base is main's sliding window (popup.h). */
    SlidingWindow_SetPlace((SlidingWindow *) (void *) &self->popup, x, y);
    if (is_letter_place(self, self->popup_place)) {
        int index = func_ov105_0229d718(self, self->popup_place);
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
    func_ov094_0229b938(self->letters, func_ov105_0229d718(self, (unsigned int) place));
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
 * cleared); any other place clears both (func_ov105_0229d404). */
void LetterStorage_SelectPlace(LetterStorage *self, int place)
{
    if (is_letter_place(self, place)) {
        int index = func_ov105_0229d718(self, (unsigned int) place);
        func_ov094_0229b950(self->letters, index);
        func_ov094_0229ab5c(self->grid);
    } else {
        func_ov105_0229d404(self);
    }
}
CLEAN_AS(func_ov105_0229d3b4, LetterStorage_SelectPlace)
