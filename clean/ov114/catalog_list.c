/* Overlay 114's catalog list (catalog_list.h): its flags, the caught entries, the cursor and its
 * moves, the picture, the icons, the row and its scrolling, the labels, the description's pages,
 * the files and the frame's start and end. */
#include "catalog_list.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "clean.h"
#include "main/c_library.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/dual_cell_sprite.h"
#include "main/item_traits.h"
#include "main/message_query.h"
#include "main/message_reader.h"
#include "main/name_texts.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/rom_file.h"
#include "main/sound.h"
#include "main/text_base.h"
#include "ov002/key_repeat.h"
#include "ov090/menu_tabs.h"

static_assert(offsetof(CatalogList, description) == 0x808 && sizeof(CatalogText) == 0x11c, "description");
static_assert(offsetof(CatalogList, palette_task) == 0x924 && offsetof(CatalogList, palette_file) == 0x948, "palette");
static_assert(offsetof(CatalogList, icon_chars) == 0x988 && offsetof(CatalogList, icon_tasks) == 0xe08, "icons");
static_assert(sizeof(LayerTaskPair) == 0x38 && sizeof(CatalogListEntry) == 0xc, "members");
static_assert(offsetof(CatalogList, entries) == 0x1000 && offsetof(CatalogList, labels) == 0x106c, "entries");
static_assert(offsetof(CatalogList, handle) == 0x121c && offsetof(CatalogList, caught) == 0x1264, "handle");
static_assert(offsetof(CatalogList, handle_x) == 0x1270 && offsetof(CatalogList, scroll) == 0x127c, "scroll");
static_assert(offsetof(CatalogList, count) == 0x1294 && offsetof(CatalogList, page_arrow_palette) == 0x129c, "count");
static_assert(offsetof(CatalogList, planes_b) == 0x12a4 && offsetof(CatalogList, flags) == 0x12ac, "flags");
static_assert(offsetof(CatalogList, pages) == 0x12b0 && offsetof(CatalogList, kind) == 0x12b7, "bytes");
static_assert(offsetof(CatalogList, cursor) == 0x12bc && sizeof(CatalogList) == 0x12c0, "size (ov115 0x0229e7e0)");

/* The description's vtable. */
extern const u8 data_ov114_0229daf0[];

/* The keys (autoload_2/input.h): the d-pad's left and right held. */
extern PadState data_021fbe40;
#define CATALOG_LIST_PAD_RIGHT 0x10
#define CATALOG_LIST_PAD_LEFT 0x20

/* The scene heap. */
extern Heap *data_021fbe94;

/* The cursor's places 0-3 (the page arrows and the scroll buttons): their x and y. */
extern const s32 data_ov114_0229da94[4];
extern const s32 data_ov114_0229daa4[4];

/* The places left and right of the scroll buttons and the handle (by place - 2). */
extern const u8 data_ov114_0229da8c[3]; /* right */
extern const u8 data_ov114_0229da90[3]; /* left */

/* The cells. */
extern const OamEntry data_ov114_0229dac0[]; /* an entry not caught (and the copy of a caught one) */
extern const OamEntry data_ov114_0229dac8[]; /* the next page arrow, then the previous page arrow */
extern const OamEntry data_ov114_0229dad0[]; /* the previous page arrow */
extern const OamEntry data_ov114_0229dad8[]; /* an entry's frame */
extern const OamEntry data_ov114_0229dae0[]; /* the selected entry's mark */
extern const OamEntry data_ov114_0229db00[]; /* the left scroll button */
extern const OamEntry data_ov114_0229db08[]; /* the right scroll button */
extern const OamEntry data_ov114_0229db10[]; /* the track */
extern const OamEntry data_ov114_0229db20[]; /* the row's frame; its y places the row */

/* The files and the archives. */
extern const char data_ov114_0229db68[]; /* "menu/fish_pic" */
extern const char data_ov114_0229db78[]; /* "menu/bug_pic" */
extern const char data_ov114_0229db88[]; /* "%s/%d/%d_%02d.bch" */
extern const char data_ov114_0229db9c[]; /* "%s/%d/%d.bpl" */
extern const char data_ov114_0229dbac[]; /* "obj_etc_fish" */
extern const char data_ov114_0229dbbc[]; /* "obj_etc_insect" */
extern const char data_ov114_0229dbcc[]; /* "menu/icon/b_obj_itm.bpl" */
extern const char data_ov114_0229dbe4[]; /* "menu/fish/obj.bpl" */
extern const char data_ov114_0229dbf8[]; /* "menu/fish/obj0.bch" */
extern const char data_ov114_0229dc0c[]; /* "menu/fish/obj1.bch" */
extern const char data_ov114_0229dc20[]; /* "menu/fish/bg0.bch" */
extern const char data_ov114_0229dc34[]; /* "menu/fish/bg1.bch" */
extern const char data_ov114_0229dc48[]; /* "menu/fish/bug_bg.bch" */
extern const char data_ov114_0229dc60[]; /* "menu/fish/bg.bpl" */
extern const char data_ov114_0229dc74[]; /* "menu/fish/bug_bg.bpl" */
extern const char data_ov114_0229dc8c[]; /* "menu/fish/bg4.bpl" */
extern const char data_ov114_0229dca0[]; /* "menu/fish/a_bg.bsc" */
extern const char data_ov114_0229dcb4[]; /* "menu/fish/b_bg.bsc" */
extern const char data_ov114_0229dcc8[]; /* "menu/fish/c_bg.bsc" */

/* The overlay's words: the picture's folder, the background's palette file and the path built
 * for the picture. */
extern const char *data_ov114_0229dce0;
extern const char *data_ov114_0229dce4;
extern char data_ov114_0229dce8[];

/* The text labels' constructor and destructor, handed to __cxa_vec_ctor and __cxa_vec_cleanup
 * (so the game's symbols). */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void *func_02070c08(void *label);
extern int **func_02070be8(void *label);

extern void MI_CpuCopy8(const void *source, void *destination, u32 size);
extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);

/* The layer of the main engine's OBJs (main/display_layers.h). */
#define CATALOG_LIST_OBJ_LAYER 8

/* The sounds. */
#define CATALOG_LIST_SE_SELECT 0x29 /* another entry picked */
#define CATALOG_LIST_SE_PAGE 0x39   /* the description's page turned */

/* The first item code of the list's kind. */
#define CATALOG_LIST_FISH_FIRST ITEM_RECORD_FISH_FIRST
#define CATALOG_LIST_INSECT_FIRST ITEM_RECORD_INSECT_FIRST

/* The ROM's signed division (_s32_div_f): a divisor of 0 gives the numerator back. */
static int catalog_div(int numerator, int divisor)
{
    if (divisor == 0) {
        return numerator;
    }
    if (divisor == -1) {
        return (int) (0u - (u32) numerator);
    }
    return numerator / divisor;
}

/* The item code of `entry`, 0 the first, from the kind's first code (the first one again past
 * the 56). */
static ItemCode catalog_item(unsigned int entry, unsigned int first)
{
    return (ItemCode) (entry < CATALOG_LIST_ENTRIES ? entry + first : first);
}

/* The word of `caught` that holds entry `entry`'s bit (entry / 32 words on, as the ROM indexes
 * it, for any entry). */
static u32 *catalog_caught_word(CatalogList *self, int entry)
{
    return (u32 *) (uintptr_t) ((uintptr_t) self->caught + (uintptr_t) (u32) (entry >> 5) * 4u);
}

static DualCellSprite *catalog_handle_cells(CatalogList *self)
{
    /* The handle's base is main's second sprite class (push_button.h). */
    return (DualCellSprite *) (void *) &self->handle;
}

/* The handle's function of vtable slot `slot`. */
static void catalog_handle_virtual(CatalogList *self, int slot)
{
    const u32 *vtable = (const u32 *) self->handle.vtable;
    ((void (*)(PushButton *))(uintptr_t) vtable[slot])(&self->handle);
}

/* func_ov114_0229c180 */
void CatalogList_ClearFlags(CatalogList *self, u16 flags)
{
    self->flags &= (u16) ~flags;
}
CLEAN_AS(func_ov114_0229c180, CatalogList_ClearFlags)

/* func_ov114_0229c190 */
void CatalogList_SetFlags(CatalogList *self, u16 flags)
{
    self->flags |= flags;
}
CLEAN_AS(func_ov114_0229c190, CatalogList_SetFlags)

/* func_ov114_0229c1a0: whether any of `flags` is set. */
int CatalogList_TestFlags(CatalogList *self, u16 flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov114_0229c1a0, CatalogList_TestFlags)

/* func_ov114_0229c1b8: whether the current player has had entry `entry`.
 * REQUIRES: entry is 0 or more and below 96; the game reads the word it falls in otherwise. */
int CatalogList_IsCaught(CatalogList *self, int entry)
{
    return (*catalog_caught_word(self, entry) & (1u << (entry & 31))) != 0;
}
CLEAN_AS(func_ov114_0229c1b8, CatalogList_IsCaught)

/* func_ov114_0229c1e4: `caught` filled from the current player's item record: the fish's codes
 * for kind 0, the insects' for any other. */
void CatalogList_LoadCaught(CatalogList *self)
{
    for (int i = 0; i < 3; i++) {
        self->caught[i] = 0;
    }
    u8 *record = PlayerRecords_Current();
    unsigned int first = self->kind == CATALOG_LIST_FISH ? CATALOG_LIST_FISH_FIRST : CATALOG_LIST_INSECT_FIRST;
    for (int j = 0; j < self->count; j++) {
        ItemCode item = catalog_item((unsigned int) j, first);
        if (ItemRecord_Has((ItemRecord *) (void *) PlayerRecord_ItemRecord(record), &item) != 0) {
            *catalog_caught_word(self, j) |= 1u << (j & 31);
        }
    }
}
CLEAN_AS(func_ov114_0229c1e4, CatalogList_LoadCaught)

/* func_ov114_0229c2c8: A (or the pen) on the cursor's place; whether the scroll starts.
 *
 * - An entry caught is picked (CatalogList_Select), with sound 0x29 when it is another one.
 * - The page arrows turn the description's page.
 * - The scroll buttons start a scroll to their side; the handle is pressed and scrolls by the
 *   d-pad (CATALOG_LIST_SCROLL_DRAG). These answer 1. */
int CatalogList_RunAction(CatalogList *self)
{
    unsigned int place = self->cursor;
    if (place >= CATALOG_LIST_PLACE_ENTRY) {
        unsigned int entry = place - CATALOG_LIST_PLACE_ENTRY;
        if (CatalogList_IsCaught(self, (int) entry) != 0) {
            if (self->selected != entry) {
                SoundSys_PlaySe(CATALOG_LIST_SE_SELECT);
            }
            CatalogList_Select(self, (u8) entry);
        }
        return 0;
    }
    switch (place) {
        case CATALOG_LIST_PLACE_PREVIOUS_PAGE:
            CatalogList_PreviousPage(self);
            return 0;
        case CATALOG_LIST_PLACE_NEXT_PAGE:
            CatalogList_NextPage(self);
            return 0;
        case CATALOG_LIST_PLACE_SCROLL_LEFT:
            self->scroll_mode = CATALOG_LIST_SCROLL_LEFT;
            return 1;
        case CATALOG_LIST_PLACE_SCROLL_RIGHT:
            self->scroll_mode = CATALOG_LIST_SCROLL_RIGHT;
            return 1;
        case CATALOG_LIST_PLACE_HANDLE:
            self->scroll_mode = CATALOG_LIST_SCROLL_DRAG;
            PushButton_Press(&self->handle);
            PushButton_PressCue(&self->handle);
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov114_0229c2c8, CatalogList_RunAction)

/* func_ov114_0229c370: the entry under the cursor's x, as a place (the last entry past the
 * end). */
u8 CatalogList_EntryUnderCursor(CatalogList *self)
{
    int x = CatalogList_CursorX(self) - (21 - self->scroll);
    if (x < 0) {
        x = 0;
    }
    int entry = x / CATALOG_LIST_ENTRY_WIDTH;
    if (entry >= self->count) {
        entry = self->count - 1;
    }
    return (u8) (entry + CATALOG_LIST_PLACE_ENTRY);
}
CLEAN_AS(func_ov114_0229c370, CatalogList_EntryUnderCursor)

/* func_ov114_0229c3ac: a cursor on an entry brought into the row drawn: left of x 0x20 it goes
 * to the first entry drawn (the next one if that is still left of it), right of 0xe0 to the
 * eighth (the seventh if that is still right of it). */
void CatalogList_KeepCursorInView(CatalogList *self)
{
    if (self->cursor < CATALOG_LIST_PLACE_ENTRY) {
        return;
    }
    int x = CatalogList_CursorX(self);
    if (x < 0x20) {
        self->cursor = (u8) (self->first_entry + CATALOG_LIST_PLACE_ENTRY);
        if (CatalogList_CursorX(self) < 0x20) {
            self->cursor++;
        }
    } else if (x > 0xe0) {
        self->cursor = (u8) (self->first_entry + CATALOG_LIST_PLACE_ENTRY + 7);
        if (CatalogList_CursorX(self) > 0xe0) {
            self->cursor--;
        }
    }
}
CLEAN_AS(func_ov114_0229c3ac, CatalogList_KeepCursorInView)

/* func_ov114_0229c410: the cursor moved by the d-pad's repeated `keys` (none without keys);
 * whether it moved. The first key held of the order below is taken.
 *
 * - On the bar: down to the next page arrow; left and right along the bar.
 * - On a page arrow: up to the bar's place of this catalog, down to the entry under it; left to
 *   the previous page arrow, right to the next.
 * - On an entry: up to the previous page arrow (left of x 0x48) or the next; down to the left
 *   scroll button (left of 0x40), the right one (from 0xc0) or the handle; left and right to the
 *   entries beside, the row scrolling when the cursor would be within 0x20 of an edge.
 * - On the scroll buttons and the handle: up to the entry above, left and right between them. */
int CatalogList_MoveCursor(CatalogList *self, u32 keys)
{
    if (keys == 0) {
        return 0;
    }
    int k = (int) keys;
    unsigned int was = self->cursor;

    if (CatalogList_TabUnderCursor(self) != -1) {
        if (KeyRepeat_HasDown(k) != 0) {
            self->cursor = CATALOG_LIST_PLACE_NEXT_PAGE;
        } else if (KeyRepeat_HasLeft(k) != 0) {
            if (self->cursor > CATALOG_LIST_PLACE_TAB) {
                self->cursor--;
            }
        } else if (KeyRepeat_HasRight(k) != 0) {
            if (self->cursor < CATALOG_LIST_PLACE_LAST_TAB) {
                self->cursor++;
            }
        }
    } else {
        unsigned int place = self->cursor;
        if (place <= CATALOG_LIST_PLACE_PREVIOUS_PAGE) {
            if (KeyRepeat_HasUp(k) != 0) {
                self->cursor = self->cursor_up;
            } else if (KeyRepeat_HasDown(k) != 0) {
                self->cursor = CatalogList_EntryUnderCursor(self);
            } else if (KeyRepeat_HasLeft(k) != 0) {
                self->cursor = CATALOG_LIST_PLACE_PREVIOUS_PAGE;
            } else if (KeyRepeat_HasRight(k) != 0) {
                self->cursor = CATALOG_LIST_PLACE_NEXT_PAGE;
            }
        } else if (place >= CATALOG_LIST_PLACE_ENTRY) {
            int entry = (int) (place - CATALOG_LIST_PLACE_ENTRY);
            if (KeyRepeat_HasUp(k) != 0) {
                self->cursor =
                    CatalogList_CursorX(self) < 0x48 ? CATALOG_LIST_PLACE_PREVIOUS_PAGE : CATALOG_LIST_PLACE_NEXT_PAGE;
            } else if (KeyRepeat_HasDown(k) != 0) {
                int x = CatalogList_CursorX(self);
                if (x < 0x40) {
                    self->cursor = CATALOG_LIST_PLACE_SCROLL_LEFT;
                } else if (x >= 0xc0) {
                    self->cursor = CATALOG_LIST_PLACE_SCROLL_RIGHT;
                } else {
                    self->cursor = CATALOG_LIST_PLACE_HANDLE;
                }
            } else if (KeyRepeat_HasRight(k) != 0) {
                if (entry < self->count - 1) {
                    self->cursor++;
                    int x = CatalogList_CursorX(self);
                    if (x > 0xe0) {
                        self->scroll_left = x - 0xe0;
                    }
                }
            } else if (KeyRepeat_HasLeft(k) != 0) {
                if (entry > 0) {
                    self->cursor--;
                    int x = CatalogList_CursorX(self);
                    if (x < 0x20) {
                        self->scroll_left = x - 0x20;
                    }
                }
            }
        } else {
            unsigned int row = place - CATALOG_LIST_PLACE_SCROLL_LEFT;
            if (KeyRepeat_HasUp(k) != 0) {
                self->cursor = CatalogList_EntryUnderCursor(self);
            } else if (KeyRepeat_HasLeft(k) != 0) {
                self->cursor = data_ov114_0229da90[row];
            } else if (KeyRepeat_HasRight(k) != 0) {
                self->cursor = data_ov114_0229da8c[row];
            }
        }
    }
    return was != self->cursor;
}
CLEAN_AS(func_ov114_0229c410, CatalogList_MoveCursor)

/* func_ov114_0229c5f4: whether the cursor is on a page arrow. */
int CatalogList_OnPageArrow(CatalogList *self)
{
    return self->cursor == CATALOG_LIST_PLACE_NEXT_PAGE || self->cursor == CATALOG_LIST_PLACE_PREVIOUS_PAGE;
}
CLEAN_AS(func_ov114_0229c5f4, CatalogList_OnPageArrow)

/* func_ov114_0229c60c: the menu bar's place under the cursor, or -1. */
int CatalogList_TabUnderCursor(CatalogList *self)
{
    u8 place = self->cursor;
    if (place >= CATALOG_LIST_PLACE_TAB && place <= CATALOG_LIST_PLACE_LAST_TAB) {
        return place - CATALOG_LIST_PLACE_TAB;
    }
    return -1;
}
CLEAN_AS(func_ov114_0229c60c, CatalogList_TabUnderCursor)

/* func_ov114_0229c628: the cursor's y: 8 on the bar, the handle's face, the table's for the
 * arrows and the buttons (2 lower for the scroll button being held), 0x9e on the entries. */
int CatalogList_CursorY(CatalogList *self)
{
    if (CatalogList_TabUnderCursor(self) != -1) {
        return 8;
    }
    u8 place = self->cursor;
    if (place == CATALOG_LIST_PLACE_HANDLE) {
        return PushButton_FaceY(&self->handle);
    }
    if (place < CATALOG_LIST_PLACE_HANDLE) {
        int y = data_ov114_0229daa4[place];
        if (place == CATALOG_LIST_PLACE_SCROLL_LEFT && self->scroll_mode == CATALOG_LIST_SCROLL_LEFT) {
            return y + 2;
        }
        if (place == CATALOG_LIST_PLACE_SCROLL_RIGHT && self->scroll_mode == CATALOG_LIST_SCROLL_RIGHT) {
            return y + 2;
        }
        return y;
    }
    return 0x9e;
}
CLEAN_AS(func_ov114_0229c628, CatalogList_CursorY)

/* func_ov114_0229c690: the cursor's x: the bar's place's (MenuTabs_TabX), the handle's face, the
 * table's, or an entry's centre in the row as it is drawn once the scroll left is done. */
int CatalogList_CursorX(CatalogList *self)
{
    if (CatalogList_TabUnderCursor(self) != -1) {
        return MenuTabs_TabX(self->cursor - CATALOG_LIST_PLACE_TAB);
    }
    u8 place = self->cursor;
    if (place == CATALOG_LIST_PLACE_HANDLE) {
        return PushButton_FaceX(&self->handle);
    }
    if (place < CATALOG_LIST_PLACE_HANDLE) {
        return data_ov114_0229da94[place];
    }
    return CATALOG_LIST_ENTRY_WIDTH * (place - CATALOG_LIST_PLACE_ENTRY) + 34 - self->scroll - self->scroll_left;
}
CLEAN_AS(func_ov114_0229c690, CatalogList_CursorX)

/* func_ov114_0229c6f8: entry `entry` picked; another than the one shown gets its name shown
 * now (its picture and description once the shown one has faded out, CatalogList_UpdatePicture). */
void CatalogList_Select(CatalogList *self, u8 entry)
{
    self->selected = entry;
    if (self->selected != self->shown) {
        CatalogList_ShowName(self, entry);
    }
}
CLEAN_AS(func_ov114_0229c6f8, CatalogList_Select)

/* func_ov114_0229c720 (each frame): the picture fades. While the entry picked is shown, a
 * picture not fully shown fades in by 4 a frame (layer C shown as it starts); once at 12 or more
 * the sub engine's blending is switched off (each frame). Another entry picked: the picture fades
 * out by 4 a frame, layer C hidden at the end, then the picked entry is shown. A change of fade
 * fades colour 2 of the palette with it.
 * QUIRK: the fade stops at 12, not 16; only CatalogList_HoldPicture sets 16. */
void CatalogList_UpdatePicture(CatalogList *self)
{
    u8 fade = self->fade;
    u8 shown = self->shown;
    if (shown == self->selected) {
        if (shown != CATALOG_LIST_NONE && fade != CATALOG_LIST_FADE_FULL) {
            if (fade < 0xc) {
                if (fade == 0) {
                    DisplayLayer_Show(self->layer_c);
                }
                self->fade += 4;
                DisplayShadow_SetSubAlpha((u8) self->planes_c, (u8) self->planes_b, self->fade);
            } else {
                DisplayShadow_SubBlendOff();
            }
        }
    } else if (fade == 0) {
        CatalogList_ShowSelected(self);
    } else if (fade > 4) {
        self->fade = (u8) (fade - 4);
        DisplayShadow_SetSubAlpha((u8) self->planes_c, (u8) self->planes_b, self->fade);
    } else {
        self->fade = 0;
        DisplayLayer_Hide(self->layer_c);
    }
    if (fade != self->fade) {
        CatalogList_FadePalette(self, self->fade, CATALOG_LIST_FADE_FULL);
    }
}
CLEAN_AS(func_ov114_0229c720, CatalogList_UpdatePicture)

/* func_ov114_0229c7d0: the shown entry's picture loaded on layer C: its characters (0x11-0xa0)
 * from "<folder>/<entry / 12>/<entry / 12>_<entry>.bch" and palette entry % 12 of
 * "<folder>/<entry / 12>/<entry / 12>.bpl" as palette 5. Nothing for no entry or another kind;
 * the folder is kept in the overlay's word and read back from it. */
void CatalogList_LoadPicture(CatalogList *self)
{
    u8 entry = self->shown;
    if (entry == CATALOG_LIST_NONE) {
        return;
    }
    int folder = entry / 12;
    Heap *heap = data_021fbe94;
    switch (self->kind) {
        case CATALOG_LIST_FISH:
            data_ov114_0229dce0 = data_ov114_0229db68;
            break;
        case CATALOG_LIST_INSECTS:
            data_ov114_0229dce0 = data_ov114_0229db78;
            break;
        default:
            return;
    }
    CLib_SPrintf(data_ov114_0229dce8, data_ov114_0229db88, data_ov114_0229dce0, folder, folder, entry);
    DisplayLayer_LoadCharsFromFile(data_ov114_0229dce8, heap, self->layer_c, 0x11, 0x11, 0xa0);
    CLib_SPrintf(data_ov114_0229dce8, data_ov114_0229db9c, data_ov114_0229dce0, folder, folder, entry);
    DisplayLayer_LoadPaletteFromFile(data_ov114_0229dce8, heap, self->layer_c, entry % 12, 5);
}
CLEAN_AS(func_ov114_0229c7d0, CatalogList_LoadPicture)

/* func_ov114_0229c890: the entry picked becomes the one shown: its picture and description. */
void CatalogList_ShowSelected(CatalogList *self)
{
    self->shown = self->selected;
    CatalogList_LoadPicture(self);
    CatalogList_LoadDescription(self);
}
CLEAN_AS(func_ov114_0229c890, CatalogList_ShowSelected)

/* func_ov114_0229c8b4 (the scene starts to wipe out): the picture held as it is: the shown entry
 * kept picked, the sub engine's blending switched off, the fade full. */
void CatalogList_HoldPicture(CatalogList *self)
{
    self->selected = self->shown;
    DisplayShadow_SubBlendOff();
    self->fade = CATALOG_LIST_FADE_FULL;
}
CLEAN_AS(func_ov114_0229c8b4, CatalogList_HoldPicture)

/* func_ov114_0229c8dc: no entry picked or shown: the name cleared, no picture and an empty
 * description, the palette and the blending at fade 0. */
void CatalogList_ResetPicture(CatalogList *self)
{
    self->selected = CATALOG_LIST_NONE;
    self->fade = 0;
    CatalogList_ShowName(self, CATALOG_LIST_NONE);
    CatalogList_ShowSelected(self);
    CatalogList_FadePalette(self, 0, CATALOG_LIST_FADE_FULL);
    DisplayShadow_SetSubAlpha((u8) self->planes_c, (u8) self->planes_b, 0);
}
CLEAN_AS(func_ov114_0229c8dc, CatalogList_ResetPicture)

/* func_ov114_0229c924: the ring's place `slot` given the icon of `item` when it has another:
 * the icon's two rows of characters copied into the next free OBJ place of this frame and
 * queued for the main engine's OBJs at the place's tiles (t, t + 1 and t + 0x20, t + 0x21), the
 * place's palette the icon's. */
void CatalogList_LoadIcon(CatalogList *self, const ItemCode *item, int slot)
{
    CatalogListEntry *entry = &self->entries[slot];
    int icon = ItemTraits_Unk02(item);
    if ((u32) icon == (u32) entry->icon) {
        return;
    }
    entry->icon = icon;
    int tile = entry->obj.attr2 & 0x3ff;
    u8 *src = PocketsIcons_Chars(&self->icons, icon);
    int place = CatalogList_NextIconSlot(self);
    u8 *top = self->icon_chars[place];
    u8 *bottom = top + 0x40;
    MI_CpuCopy8(src, top, 0x40);
    MI_CpuCopy8(src + 0x400, bottom, 0x40);
    LayerTask_QueueTwoChars(&self->icon_tasks[place], (int) (uintptr_t) top, (int) (uintptr_t) bottom, CATALOG_LIST_OBJ_LAYER,
                            tile, tile + 1, tile + 0x20, tile + 0x21);
    u8 palette = PocketsIcons_Palette(&self->icons, icon);
    entry->obj.attr2 = (u16) ((entry->obj.attr2 & 0x0fff) | (palette & 0xf) << 12);
}
CLEAN_AS(func_ov114_0229c924, CatalogList_LoadIcon)

/* func_ov114_0229c9dc: the ring's places made from the empty entry's cell, place i at tile
 * 0xc0 + 2i and no icon; the row's y from the frame's cell; the row at the start. */
void CatalogList_InitEntries(CatalogList *self)
{
    for (int i = 0; i < CATALOG_LIST_IN_VIEW; i++) {
        CatalogListEntry *entry = &self->entries[i];
        MI_CpuCopy8(data_ov114_0229dac0, entry, sizeof(OamEntry));
        entry->obj.attr2 = (u16) ((entry->obj.attr2 & ~0x3ffu) | ((u32) (i * 2 + 0xc0) & 0x3ffu));
        entry->icon = -1;
    }
    self->row_y = OamBuffer_ObjY(data_ov114_0229db20) + 0x70;
    CatalogList_SetScroll(self, 0);
}
CLEAN_AS(func_ov114_0229c9dc, CatalogList_InitEntries)

/* func_ov114_0229ca50: the entry under a touch of the row (y 0x90-0xaf, x 0x10-0xef, the x
 * kept within 0x18-0xe8) picked when caught, with sound 0x29 when it is another one; whether it
 * was. */
int CatalogList_TouchEntry(CatalogList *self, int x, int y)
{
    if (y < 0x90 || y >= 0xb0) {
        return 0;
    }
    if (x < 0x10 || x >= 0xf0) {
        return 0;
    }
    if (x < 0x18) {
        x = 0x18;
    }
    if (x > 0xe8) {
        x = 0xe8;
    }
    int dx = x - (21 - self->scroll);
    if (dx < 0) {
        dx = 0;
    }
    int entry = dx / CATALOG_LIST_ENTRY_WIDTH;
    if (entry >= self->count) {
        entry = self->count - 1;
    }
    if (CatalogList_IsCaught(self, entry) == 0) {
        return 0;
    }
    if (self->selected != entry) {
        SoundSys_PlaySe(CATALOG_LIST_SE_SELECT);
    }
    CatalogList_Select(self, (u8) entry);
    return 1;
}
CLEAN_AS(func_ov114_0229ca50, CatalogList_TouchEntry)

/* func_ov114_0229cadc: the icons of the entries drawn from the first one (up to the 56th) given
 * to their places of the ring, the first one's place being first_entry % 9. Nothing for a kind
 * other than the two. */
void CatalogList_FillEntries(CatalogList *self)
{
    self->first_slot = self->first_entry % CATALOG_LIST_IN_VIEW;
    unsigned int entry = (unsigned int) self->first_entry;
    int slot = self->first_slot;
    for (int n = 0; n < CATALOG_LIST_IN_VIEW; n++) {
        ItemCode item;
        switch (self->kind) {
            case CATALOG_LIST_FISH:
                item = catalog_item(entry, CATALOG_LIST_FISH_FIRST);
                break;
            case CATALOG_LIST_INSECTS:
                item = catalog_item(entry, CATALOG_LIST_INSECT_FIRST);
                break;
            default:
                return;
        }
        CatalogList_LoadIcon(self, &item, slot);
        slot++;
        if (slot >= CATALOG_LIST_IN_VIEW) {
            slot = 0;
        }
        entry++;
        if (entry >= CATALOG_LIST_ENTRIES) {
            return;
        }
    }
}
CLEAN_AS(func_ov114_0229cadc, CatalogList_FillEntries)

/* func_ov114_0229cb7c: the row scrolled to `scroll` pixels (within 0 and max_scroll): the first
 * entry drawn is the first whose x (0x22 - scroll, then 27 apart) is 8 or more; whether that
 * entry changed. */
int CatalogList_SetScroll(CatalogList *self, int scroll)
{
    if (scroll < 0) {
        scroll = 0;
    }
    if (scroll >= self->max_scroll) {
        scroll = self->max_scroll;
    }
    self->scroll = scroll;
    int was = self->first_entry;
    self->first_x = 0x22 - scroll;
    self->first_entry = 0;
    while (self->first_x < 8) {
        self->first_x += CATALOG_LIST_ENTRY_WIDTH;
        self->first_entry++;
    }
    return was != self->first_entry;
}
CLEAN_AS(func_ov114_0229cb7c, CatalogList_SetScroll)

/* func_ov114_0229cbe4: the nine entries drawn at the row's y plus `y` on the sub engine: a
 * caught one by its ring place, else the empty cell in palette 4 frame; the picked one's mark;
 * each one's frame (palette 4 when not caught). */
void CatalogList_DrawEntries(CatalogList *self, int y)
{
    int x = self->first_x;
    int row_y = self->row_y + y;
    int slot = self->first_slot;
    for (int i = 0; i < CATALOG_LIST_IN_VIEW; i++) {
        const OamEntry *obj;
        int frame_palette;
        if (CatalogList_IsCaught(self, self->first_entry + i) != 0) {
            obj = &self->entries[slot].obj;
            frame_palette = -1;
        } else {
            obj = data_ov114_0229dac0;
            frame_palette = 4;
        }
        OamBuffer_DrawObjAffine(1, obj, x, row_y, -1, 2, NULL);
        if (self->selected == self->first_entry + i) {
            OamBuffer_DrawObjAffine(1, data_ov114_0229dae0, x, row_y, -1, 2, NULL);
        }
        OamBuffer_DrawObjAffine(1, data_ov114_0229dad8, x, row_y, frame_palette, 2, NULL);
        x += CATALOG_LIST_ENTRY_WIDTH;
        slot++;
        if (slot >= CATALOG_LIST_IN_VIEW) {
            slot = 0;
        }
    }
}
CLEAN_AS(func_ov114_0229cbe4, CatalogList_DrawEntries)

/* func_ov114_0229ccc0: entry `entry`'s name (its item's, NameText_SetItem; empty for
 * CATALOG_LIST_NONE) in the next label, opened at (0xa1, 0xd) in colours 1 and 3 on layer A
 * and centred. Nothing for a kind other than the two. */
void CatalogList_ShowName(CatalogList *self, u16 entry)
{
    NameText name;
    NameText_Construct(&name);
    if (entry == CATALOG_LIST_NONE) {
        TextBase_Clear(&name);
    } else {
        ItemCode item;
        switch (self->kind) {
            case CATALOG_LIST_FISH:
                item = catalog_item(entry, CATALOG_LIST_FISH_FIRST);
                break;
            case CATALOG_LIST_INSECTS:
                item = catalog_item(entry, CATALOG_LIST_INSECT_FIRST);
                break;
            default:
                NameText_Destruct(&name);
                return;
        }
        NameText_SetItem(&name, &item);
    }
    TextLabel *label = CatalogList_NextLabel(self);
    TextBase_Copy((TextBase *) (void *) label, (TextBase *) (void *) &name);
    TextLabel_OpenStyledBox2(label, self->layer_a, 0xa1, 0xd, 1, 3, 0);
    TextLabel_Show(label, 1, 0);
    NameText_Destruct(&name);
}
CLEAN_AS(func_ov114_0229ccc0, CatalogList_ShowName)

/* func_ov114_0229cd70: the next label of this frame (the last one again once all four are
 * used). */
TextLabel *CatalogList_NextLabel(CatalogList *self)
{
    if (self->labels_used >= CATALOG_LIST_LABELS) {
        return &self->labels[CATALOG_LIST_LABELS - 1];
    }
    self->labels_used++;
    return &self->labels[self->labels_used - 1];
}
CLEAN_AS(func_ov114_0229cd70, CatalogList_NextLabel)

/* func_ov114_0229cda0: the labels' boxes freed, none used. */
void CatalogList_CloseLabels(CatalogList *self)
{
    self->labels_used = 0;
    for (int i = 0; i < CATALOG_LIST_LABELS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
}
CLEAN_AS(func_ov114_0229cda0, CatalogList_CloseLabels)

/* func_ov114_0229cdcc: the next OBJ place of this frame for an icon's characters (the last one
 * again once all nine are used). */
u8 CatalogList_NextIconSlot(CatalogList *self)
{
    u8 slot = self->icon_slots;
    if (slot >= CATALOG_LIST_IN_VIEW) {
        return CATALOG_LIST_IN_VIEW - 1;
    }
    self->icon_slots = (u8) (slot + 1);
    return slot;
}
CLEAN_AS(func_ov114_0229cdcc, CatalogList_NextIconSlot)

/* func_ov114_0229cde4: the icons' tasks ended, none used. */
void CatalogList_EndIconTasks(CatalogList *self)
{
    for (int i = 0; i < CATALOG_LIST_IN_VIEW; i++) {
        LayerTask_End(&self->icon_tasks[i].first);
    }
    self->icon_slots = 0;
}
CLEAN_AS(func_ov114_0229cde4, CatalogList_EndIconTasks)

/* func_ov114_0229ce18: colour 2 of the palette faded from the file's colour 3 (step 0) to its
 * colour 2 (step `steps`), each component on its own; queued again. */
void CatalogList_FadePalette(CatalogList *self, int step, int steps)
{
    u16 from = self->palette_file[3];
    u8 from_r = (u8) (from & 0x1f);
    u8 from_g = (u8) ((from & 0x3e0) >> 5);
    u8 from_b = (u8) ((from & 0x7c00) >> 10);
    int rest = steps - step;
    u16 to = self->palette_file[2];
    u8 r = (u8) catalog_div((u8) (to & 0x1f) * step + from_r * rest, steps);
    u8 g = (u8) catalog_div((u8) ((to & 0x3e0) >> 5) * step + from_g * rest, steps);
    u8 b = (u8) catalog_div((u8) ((to & 0x7c00) >> 10) * step + from_b * rest, steps);
    self->palette[2] = (u16) (r | g << 5 | b << 10);
    CatalogList_SetFlags(self, CATALOG_LIST_FLAG_PALETTE_DIRTY);
}
CLEAN_AS(func_ov114_0229ce18, CatalogList_FadePalette)

/* func_ov114_0229cee0: the description's previous page, when there is one: its arrow flashes
 * for 5 frames, sound 0x39; whether it turned. */
int CatalogList_PreviousPage(CatalogList *self)
{
    if (self->page == 0) {
        return 0;
    }
    self->page--;
    self->page_arrow_flash[1] = 5;
    CatalogList_ShowPage(self);
    SoundSys_PlaySe(CATALOG_LIST_SE_PAGE);
    return 1;
}
CLEAN_AS(func_ov114_0229cee0, CatalogList_PreviousPage)

/* func_ov114_0229cf18: the description's next page, when there is one, as the previous. */
int CatalogList_NextPage(CatalogList *self)
{
    if (self->page + 1 >= self->pages) {
        return 0;
    }
    self->page++;
    self->page_arrow_flash[0] = 5;
    CatalogList_ShowPage(self);
    SoundSys_PlaySe(CATALOG_LIST_SE_PAGE);
    return 1;
}
CLEAN_AS(func_ov114_0229cf18, CatalogList_NextPage)

/* func_ov114_0229cf58: the page's three lines of the description in the next three labels (an
 * empty one for a line the message lacks), opened in colours 2 and 3 on layer A at 0xbb, 0xd5
 * and 0xef (by 0xd), not centred; each page arrow in palette 5, or 4 when there is no page its
 * way. */
void CatalogList_ShowPage(CatalogList *self)
{
    TextLabel *lines[3];
    int line = self->page * 3;
    lines[0] = CatalogList_NextLabel(self);
    lines[1] = CatalogList_NextLabel(self);
    lines[2] = CatalogList_NextLabel(self);
    int a = 0xbb;
    for (int i = 0; i < 3; i++) {
        int chars = MessageQuery_Line((int) (uintptr_t) self->description.text, line);
        if (chars != 0) {
            TextBase_SetLine((TextBase *) (void *) lines[i], (const char *) (uintptr_t) chars);
        } else {
            TextBase_Clear(lines[i]);
        }
        TextLabel_OpenStyledBox2(lines[i], self->layer_a, a, 0xd, 2, 3, 0);
        TextLabel_Show(lines[i], 0, 0);
        line++;
        a += 0x1a;
    }
    self->page_arrow_palette[1] = self->page == 0 ? 4 : 5;
    self->page_arrow_palette[0] = self->page + 1 >= self->pages ? 4 : 5;
}
CLEAN_AS(func_ov114_0229cf58, CatalogList_ShowPage)

/* func_ov114_0229d030: the description's pages: up to 4, ending at the first three lines that
 * are all missing. */
int CatalogList_CountPages(CatalogList *self)
{
    int text = (int) (uintptr_t) self->description.text;
    int line = 0;
    for (int page = 0; page < 4; page++) {
        int a = MessageQuery_Line(text, line);
        int b = MessageQuery_Line(text, line + 1);
        int c = MessageQuery_Line(text, line + 2);
        line += 3;
        if (a == 0 && b == 0 && c == 0) {
            return page;
        }
    }
    return 4;
}
CLEAN_AS(func_ov114_0229d030, CatalogList_CountPages)

/* func_ov114_0229d088: the shown entry's description: message `shown` of the kind's archive
 * (one page), or empty for no entry; its first page shown.
 * REQUIRES: the kind is fish or insects (the game hands the archive's loader an unset pointer
 * for another). */
void CatalogList_LoadDescription(CatalogList *self)
{
    u8 entry = self->shown;
    const char *archive = NULL;
    switch (self->kind) {
        case CATALOG_LIST_FISH:
            archive = data_ov114_0229dbac;
            break;
        case CATALOG_LIST_INSECTS:
            archive = data_ov114_0229dbbc;
            break;
        default:
            break;
    }
    if (entry == CATALOG_LIST_NONE) {
        TextBase_Clear(&self->description);
        self->pages = 1;
    } else {
        u8 number = entry;
        MessageReader_LoadMessage((int) (uintptr_t) &self->description, &number, (int) (uintptr_t) archive);
        self->pages = (u8) CatalogList_CountPages(self);
    }
    self->page = 0;
    CatalogList_ShowPage(self);
}
CLEAN_AS(func_ov114_0229d088, CatalogList_LoadDescription)

/* func_ov114_0229d104 (vtable entry 3): the address of the characters. */
int CatalogText_Buffer(int text)
{
    return (int) ((u32) text + offsetof(CatalogText, text));
}
CLEAN_AS(func_ov114_0229d104, CatalogText_Buffer)

/* func_ov114_0229d108 (vtable entry 2) */
int CatalogText_Capacity(void)
{
    return CATALOG_TEXT_CAPACITY;
}
CLEAN_AS(func_ov114_0229d108, CatalogText_Capacity)

/* func_ov114_0229d110 (vtable entry 1) */
CatalogText *CatalogText_DestructDelete(CatalogText *text)
{
    text->vtable = (const TextVtable *) (const void *) data_ov114_0229daf0;
    TextBase_Destruct((TextBase *) (void *) text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_ov114_0229d110, CatalogText_DestructDelete)

/* func_ov114_0229d130 (vtable entry 0) */
CatalogText *CatalogText_Destruct(CatalogText *text)
{
    text->vtable = (const TextVtable *) (const void *) data_ov114_0229daf0;
    TextBase_Destruct((TextBase *) (void *) text);
    return text;
}
CLEAN_AS(func_ov114_0229d130, CatalogText_Destruct)

/* func_ov114_0229d148: an empty text. */
CatalogText *CatalogText_Construct(CatalogText *text)
{
    TextBase_Construct(text);
    text->vtable = (const TextVtable *) (const void *) data_ov114_0229daf0;
    TextBase_Clear(text);
    return text;
}
CLEAN_AS(func_ov114_0229d148, CatalogText_Construct)

/* func_ov114_0229d168 (each frame): up to 11 pixels of the scroll left done; when the row
 * moved, the handle follows it and a new first entry refills the ring's icons. */
void CatalogList_ApplyScroll(CatalogList *self)
{
    int scroll = self->scroll;
    int left = self->scroll_left;
    if (left > 0) {
        if (left < 11) {
            scroll += left;
            self->scroll_left = 0;
        } else {
            scroll += 11;
            self->scroll_left = left - 11;
        }
    } else if (left < 0) {
        if (left > -11) {
            scroll += left;
            self->scroll_left = 0;
        } else {
            scroll -= 11;
            self->scroll_left = left + 11;
        }
    }
    if (scroll != self->scroll) {
        CatalogList_HandleFromScroll(self);
        if (CatalogList_SetScroll(self, scroll) != 0) {
            CatalogList_FillEntries(self);
        }
    }
}
CLEAN_AS(func_ov114_0229d168, CatalogList_ApplyScroll)

/* func_ov114_0229d1dc: a scroll by keys ends: a held handle once its animation is done is shown
 * at rest; whether the scroll has ended (no scroll mode). */
int CatalogList_FinishHandle(CatalogList *self)
{
    if (self->scroll_mode != CATALOG_LIST_SCROLL_DRAG) {
        self->scroll_mode = CATALOG_LIST_SCROLL_NONE;
        return 1;
    }
    if (DualCellSprite_IsDone(catalog_handle_cells(self))) {
        PushButton_ShowUp(&self->handle);
        self->scroll_mode = CATALOG_LIST_SCROLL_NONE;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov114_0229d1dc, CatalogList_FinishHandle)

/* func_ov114_0229d220: a held handle released. */
void CatalogList_ReleaseHandle(CatalogList *self)
{
    if (self->scroll_mode == CATALOG_LIST_SCROLL_DRAG) {
        PushButton_Release(&self->handle);
    }
}
CLEAN_AS(func_ov114_0229d220, CatalogList_ReleaseHandle)

/* func_ov114_0229d244 (a frame of a scroll by keys): the handle moves 2 pixels to its button's
 * side, or held by the d-pad's left or right (left first), within its range; a move cues its
 * sound. The row follows the handle. */
void CatalogList_ScrollByKeys(CatalogList *self)
{
    int was = self->handle_x;
    switch (self->scroll_mode) {
        case CATALOG_LIST_SCROLL_DRAG: {
            u16 held = data_021fbe40.held;
            if (held & CATALOG_LIST_PAD_LEFT) {
                self->handle_x = was - 2;
            } else if (held & CATALOG_LIST_PAD_RIGHT) {
                self->handle_x = was + 2;
            }
            break;
        }
        case CATALOG_LIST_SCROLL_LEFT:
            self->handle_x = was - 2;
            break;
        case CATALOG_LIST_SCROLL_RIGHT:
            self->handle_x = was + 2;
            break;
        default:
            break;
    }
    if (self->handle_x < 0) {
        self->handle_x = 0;
    }
    if (self->handle_x > CATALOG_LIST_HANDLE_RANGE) {
        self->handle_x = CATALOG_LIST_HANDLE_RANGE;
    }
    if (self->handle_x != was) {
        PushButton_ScrollCue(&self->handle);
    }
    CatalogList_ScrollFromHandle(self);
}
CLEAN_AS(func_ov114_0229d244, CatalogList_ScrollByKeys)

/* func_ov114_0229d2d8: a held handle waits for its animation (whether done); else a frame of the
 * scroll by keys (1). */
int CatalogList_HandleSettled(CatalogList *self)
{
    if (self->scroll_mode == CATALOG_LIST_SCROLL_DRAG) {
        return DualCellSprite_IsDone(catalog_handle_cells(self));
    }
    CatalogList_ScrollByKeys(self);
    return 1;
}
CLEAN_AS(func_ov114_0229d2d8, CatalogList_HandleSettled)

/* func_ov114_0229d304: the pen let go: a held handle released; no scroll mode. */
void CatalogList_EndDrag(CatalogList *self)
{
    if (self->scroll_mode == CATALOG_LIST_SCROLL_DRAG) {
        PushButton_Release(&self->handle);
    }
    self->scroll_mode = CATALOG_LIST_SCROLL_NONE;
}
CLEAN_AS(func_ov114_0229d304, CatalogList_EndDrag)

/* func_ov114_0229d32c (a frame with the pen down at x): the handle follows the pen (held), its
 * button's side by 2 pixels, or approaches x - 0x3a by a quarter (the track touched), within its
 * range; the row follows it. A held handle cues its sound once it has moved 4 pixels from the
 * last cue, any other at each move. */
void CatalogList_Drag(CatalogList *self, int x)
{
    int was = self->handle_x;
    switch (self->scroll_mode) {
        case CATALOG_LIST_SCROLL_DRAG:
            self->handle_x = x + self->grab_dx;
            break;
        case CATALOG_LIST_SCROLL_LEFT:
            self->handle_x = was - 2;
            break;
        case CATALOG_LIST_SCROLL_RIGHT:
            self->handle_x = was + 2;
            break;
        case CATALOG_LIST_SCROLL_TRACK:
            Approach_S32Again(&self->handle_x, x - 0x3a, 4);
            break;
        default:
            break;
    }
    if (self->handle_x < 0) {
        self->handle_x = 0;
    }
    if (self->handle_x > CATALOG_LIST_HANDLE_RANGE) {
        self->handle_x = CATALOG_LIST_HANDLE_RANGE;
    }
    CatalogList_ScrollFromHandle(self);
    if (self->scroll_mode == CATALOG_LIST_SCROLL_DRAG) {
        int moved = self->cued_x - self->handle_x;
        if (moved >= 4 || moved <= -4) {
            PushButton_ScrollCue(&self->handle);
            self->cued_x = self->handle_x;
        }
    } else if (self->handle_x != was) {
        PushButton_ScrollCue(&self->handle);
    }
}
CLEAN_AS(func_ov114_0229d32c, CatalogList_Drag)

/* func_ov114_0229d3f4: a touch at (x, y) of the handle (pressed and held, grabbed where it was
 * touched), a scroll button, or the track (x 0x3b-0xc5, y 0xad-0xb7: the handle pressed and
 * approaching the pen); whether one was touched. */
int CatalogList_TouchHandle(CatalogList *self, int x, int y)
{
    if (PushButton_Contains(&self->handle, x, y)) {
        self->grab_dx = self->handle_x - x;
        PushButton_Press(&self->handle);
        self->scroll_mode = CATALOG_LIST_SCROLL_DRAG;
        self->cued_x = self->handle_x;
        return 1;
    }
    int dx = x - 0x80;
    int dy = y - 0x60;
    if (OamBuffer_ObjContains(data_ov114_0229db00, dx, dy, 2, 2)) {
        self->scroll_mode = CATALOG_LIST_SCROLL_LEFT;
        return 1;
    }
    if (OamBuffer_ObjContains(data_ov114_0229db08, dx, dy, 2, 2)) {
        self->scroll_mode = CATALOG_LIST_SCROLL_RIGHT;
        return 1;
    }
    if (x > 0x3a && x < 0xc6 && y > 0xac && y < 0xb8) {
        PushButton_Press(&self->handle);
        self->scroll_mode = CATALOG_LIST_SCROLL_TRACK;
        self->cued_x = self->handle_x;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov114_0229d3f4, CatalogList_TouchHandle)

/* func_ov114_0229d4c0: the row scrolled to where the handle is (in proportion), the ring's icons
 * refilled when the first entry changed; the scroll left dropped. */
void CatalogList_ScrollFromHandle(CatalogList *self)
{
    if (CatalogList_SetScroll(self, self->handle_x * self->max_scroll / CATALOG_LIST_HANDLE_RANGE) != 0) {
        CatalogList_FillEntries(self);
    }
    self->scroll_left = 0;
}
CLEAN_AS(func_ov114_0229d4c0, CatalogList_ScrollFromHandle)

/* func_ov114_0229d500: the handle put where the row's scroll is (in proportion). */
void CatalogList_HandleFromScroll(CatalogList *self)
{
    self->handle_x = catalog_div(self->scroll * CATALOG_LIST_HANDLE_RANGE, self->max_scroll);
}
CLEAN_AS(func_ov114_0229d500, CatalogList_HandleFromScroll)

/* func_ov114_0229d52c: the handle's offset: its x less 0x4e, `y` plus 0x4a. */
void CatalogList_PlaceHandle(CatalogList *self, int y)
{
    DualCellSprite_SetOffset(catalog_handle_cells(self), self->handle_x - 0x4e, y + 0x4a);
}
CLEAN_AS(func_ov114_0229d52c, CatalogList_PlaceHandle)

/* func_ov114_0229d54c: the handle drawn through its class (vtable slot 2). */
void CatalogList_DrawHandle(CatalogList *self)
{
    catalog_handle_virtual(self, 2);
}
CLEAN_AS(func_ov114_0229d54c, CatalogList_DrawHandle)

/* func_ov114_0229d564: a touch at (x, y) of the next page arrow or the previous one turns the
 * page; whether it turned. */
int CatalogList_TouchPageArrow(CatalogList *self, int x, int y)
{
    int dx = x - 0x80;
    int dy = y - 0x60;
    if (OamBuffer_ObjContains(data_ov114_0229dac8, dx, dy, 2, 2)) {
        return CatalogList_NextPage(self);
    }
    if (OamBuffer_ObjContains(data_ov114_0229dad0, dx, dy, 2, 2)) {
        return CatalogList_PreviousPage(self);
    }
    return 0;
}
CLEAN_AS(func_ov114_0229d564, CatalogList_TouchPageArrow)

/* func_ov114_0229d5b8: on the sub engine at `y` plus 0x60: the two page arrows (palette 6 while
 * one flashes, a frame counted off), the scroll buttons (2 lower while scrolling to their side)
 * and the track. */
void CatalogList_DrawArrows(CatalogList *self, int y)
{
    int base = y + 0x60;
    for (int i = 0; i < 2; i++) {
        int palette = self->page_arrow_palette[i];
        u8 *flash = &self->page_arrow_flash[i];
        if (*flash != 0) {
            (*flash)--;
            palette = 6;
        }
        OamBuffer_DrawObjAffine(1, &data_ov114_0229dac8[i], 0x80, base, palette, 1, NULL);
    }
    int left_y = self->scroll_mode == CATALOG_LIST_SCROLL_LEFT ? base + 2 : base;
    OamBuffer_DrawObjAffine(1, data_ov114_0229db00, 0x80, left_y, -1, 1, NULL);
    int right_y = self->scroll_mode == CATALOG_LIST_SCROLL_RIGHT ? base + 2 : base;
    OamBuffer_DrawObjAffine(1, data_ov114_0229db08, 0x80, right_y, -1, 1, NULL);
    OamBuffer_DrawCell(1, data_ov114_0229db10, 0x80, base, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
}
CLEAN_AS(func_ov114_0229d5b8, CatalogList_DrawArrows)

/* func_ov114_0229d688: the OBJ files of the main engine: the item icons' palettes 7-14, the
 * list's palettes 4-6 and its characters 0xc0-0x140 and 0x141-0x1bf. */
void CatalogList_LoadObjFiles(CatalogList *self)
{
    (void) self;
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadPalettesFromFile(data_ov114_0229dbcc, heap, CATALOG_LIST_OBJ_LAYER, 7, 7, 14);
    DisplayLayer_LoadPalettesFromFile(data_ov114_0229dbe4, heap, CATALOG_LIST_OBJ_LAYER, 4, 4, 6);
    DisplayLayer_LoadCharsFromFile(data_ov114_0229dbf8, heap, CATALOG_LIST_OBJ_LAYER, 0xc0, 0xc0, 0x140);
    DisplayLayer_LoadCharsFromFile(data_ov114_0229dc0c, heap, CATALOG_LIST_OBJ_LAYER, 0x141, 0x141, 0x1bf);
}
CLEAN_AS(func_ov114_0229d688, CatalogList_LoadObjFiles)

/* func_ov114_0229d700: the background: layer A's characters (0x109-0x153 and 0x154-0x19f, and
 * the insects' 0x150-0x164 over them) and palettes 1-6 (the kind's file, kept in the overlay's
 * word and read back from it: for another kind the last one), the palette read and copied (to
 * be faded), the three layers' screens. */
void CatalogList_LoadBackground(CatalogList *self)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadCharsFromFile(data_ov114_0229dc20, heap, self->layer_a, 0x109, 0x109, 0x153);
    DisplayLayer_LoadCharsFromFile(data_ov114_0229dc34, heap, self->layer_a, 0x154, 0x154, 0x19f);
    if (self->kind == CATALOG_LIST_INSECTS) {
        DisplayLayer_LoadCharsFromFile(data_ov114_0229dc48, heap, self->layer_a, 0x150, 0x150, 0x164);
    }
    switch (self->kind) {
        case CATALOG_LIST_FISH:
            data_ov114_0229dce4 = data_ov114_0229dc60;
            break;
        case CATALOG_LIST_INSECTS:
            data_ov114_0229dce4 = data_ov114_0229dc74;
            break;
        default:
            break;
    }
    DisplayLayer_LoadPalettesFromFile(data_ov114_0229dce4, heap, self->layer_a, 1, 1, 6);
    RomFile_Read(data_ov114_0229dc8c, self->palette_file, sizeof(self->palette_file));
    MIi_CpuCopy16(self->palette_file, self->palette, sizeof(self->palette));
    DisplayLayer_LoadScreenFromFile(data_ov114_0229dca0, heap, self->layer_a);
    DisplayLayer_LoadScreenFromFile(data_ov114_0229dcb4, heap, self->layer_b);
    DisplayLayer_LoadScreenFromFile(data_ov114_0229dcc8, heap, self->layer_c);
}
CLEAN_AS(func_ov114_0229d700, CatalogList_LoadBackground)

/* func_ov114_0229d824 (a frame's end): the scroll left, the handle's release settled, the
 * picture's fade, and a changed palette queued as palette 4 of layer A. */
void CatalogList_EndFrame(CatalogList *self)
{
    CatalogList_ApplyScroll(self);
    PushButton_SettleRelease(&self->handle);
    CatalogList_UpdatePicture(self);
    if (CatalogList_TestFlags(self, CATALOG_LIST_FLAG_PALETTE_DIRTY) != 0) {
        if (LayerTask_QueuePalette(&self->palette_task, (int) (uintptr_t) self->palette, self->layer_a, 4) != 0) {
            CatalogList_ClearFlags(self, CATALOG_LIST_FLAG_PALETTE_DIRTY);
        }
    }
}
CLEAN_AS(func_ov114_0229d824, CatalogList_EndFrame)

/* func_ov114_0229d87c (a frame's start): last frame's tasks ended, the handle animated (vtable
 * slot 3) and the labels' boxes freed. */
void CatalogList_BeginFrame(CatalogList *self)
{
    LayerTask_End(&self->palette_task);
    CatalogList_EndIconTasks(self);
    catalog_handle_virtual(self, 3);
    CatalogList_CloseLabels(self);
}
CLEAN_AS(func_ov114_0229d87c, CatalogList_BeginFrame)

/* func_ov114_0229d8ac: the list's end: the tasks ended and the labels' boxes freed. */
void CatalogList_Teardown(CatalogList *self)
{
    LayerTask_End(&self->palette_task);
    CatalogList_EndIconTasks(self);
    CatalogList_CloseLabels(self);
}
CLEAN_AS(func_ov114_0229d8ac, CatalogList_Teardown)

/* func_ov114_0229d8d0: the list started on its layers for `kind`: no flags, the sub engine's
 * planes of layers B and C, the icons' file forgotten, the ring made, 56 entries with the bar's
 * place of the kind's tab above the page arrows (7 for the fish, 8 for the insects, else 0), the
 * caught entries read, the cursor on the fourth entry, no scroll left, the handle at rest, no
 * arrow flashing, no description and no scroll mode. */
void CatalogList_Start(CatalogList *self, u8 layer_a, u8 layer_b, u8 layer_c, u8 kind)
{
    self->flags = 0;
    self->layer_a = layer_a;
    self->layer_b = layer_b;
    self->layer_c = layer_c;
    self->planes_b = DisplayLayer_PlaneMask(layer_b);
    self->planes_c = DisplayLayer_PlaneMask(layer_c);
    self->kind = kind;
    PocketsIcons_Forget(&self->icons);
    CatalogList_InitEntries(self);
    switch (kind) {
        case CATALOG_LIST_FISH:
            self->count = CATALOG_LIST_ENTRIES;
            self->cursor_up = CATALOG_LIST_PLACE_TAB + 2;
            break;
        case CATALOG_LIST_INSECTS:
            self->count = CATALOG_LIST_ENTRIES;
            self->cursor_up = CATALOG_LIST_PLACE_TAB + 3;
            break;
        default:
            self->count = CATALOG_LIST_ENTRIES;
            self->cursor_up = 0;
            break;
    }
    CatalogList_LoadCaught(self);
    self->cursor = CATALOG_LIST_PLACE_ENTRY + 3;
    self->max_scroll = (self->count - 8) * CATALOG_LIST_ENTRY_WIDTH;
    self->scroll_left = 0;
    PushButton_ShowUp(&self->handle);
    self->page_arrow_flash[1] = 0;
    self->page_arrow_flash[0] = 0;
    TextBase_Clear(&self->description);
    self->scroll_mode = CATALOG_LIST_SCROLL_NONE;
}
CLEAN_AS(func_ov114_0229d8d0, CatalogList_Start)

/* func_ov114_0229d9d8: the members' destructors, the last first. */
CatalogList *CatalogList_Destroy(CatalogList *self)
{
    PushButton_Destroy(&self->handle);
    __cxa_vec_cleanup(self->labels, CATALOG_LIST_LABELS, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    CatalogText_Destruct(&self->description);
    PocketsIcons_Destruct(&self->icons);
    return self;
}
CLEAN_AS(func_ov114_0229d9d8, CatalogList_Destroy)

/* func_ov114_0229da18: the members constructed in order, the labels by __cxa_vec_ctor. */
CatalogList *CatalogList_Construct(CatalogList *self)
{
    PocketsIcons_Construct(&self->icons);
    CatalogText_Construct(&self->description);
    LayerTask_Construct(&self->palette_task);
    for (int i = 0; i < CATALOG_LIST_IN_VIEW; i++) {
        LayerTask_ConstructPair(&self->icon_tasks[i]);
    }
    __cxa_vec_ctor(self->labels, CATALOG_LIST_LABELS, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070c08,
                   (void (*)(void *))(uintptr_t) func_02070be8);
    PushButton_Construct(&self->handle);
    return self;
}
CLEAN_AS(func_ov114_0229da18, CatalogList_Construct)
