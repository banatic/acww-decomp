/* The design picker of overlay 125 (design_picker.h): its destructors, its flags, the cursor's
 * moves, the cursor sprite, the choice it opens and the popup. */
#include "design_picker.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/design_info.h"
#include "main/design_sets.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/group_params.h"
#include "main/name_texts.h"
#include "main/oam_buffer.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/sliding_window.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "main/text_string.h"
#include "main/tile_convert.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(DesignPicker, title) == 0x94, "title");
static_assert(offsetof(DesignPicker, choice) == 0x180 && offsetof(DesignPicker, entries) == 0x568, "choice");
static_assert(offsetof(DesignPicker, popup) == 0x574 && offsetof(DesignPicker, cursor_sprite) == 0x644, "popup");
static_assert(offsetof(DesignPicker, panel) == 0x6a8 && offsetof(DesignPicker, wipe_y) == 0x874, "panel");
static_assert(offsetof(DesignPicker, flags) == 0x878 && offsetof(DesignPicker, popup_design) == 0x87a, "flags");
static_assert(offsetof(DesignPicker, cursor) == 0x87c && offsetof(DesignPicker, return_sub_state) == 0x87f, "bytes");
static_assert(sizeof(DesignPicker) == 0x880, "size (func_ov125_022a09a4)");

/* The scene's vtable. */
extern const u8 data_ov125_022a0ab8[];

/* The places of the designs (and of the quit button, place 8): x, and y plus 16. */
extern const u8 data_ov125_022a0a04[];
extern const u8 data_ov125_022a0a10[];

/* The OBJ a design is drawn with (32 x 32, affine); its tile is set before each draw. */
extern OamEntry data_ov125_022a0a28;

/* The pad, and the pen (autoload_2/input.c): down, and gone down or up this frame; the touch. */
extern PadState data_021fbe40;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58, data_021f6c54;
#define DESIGN_PICKER_PAD_A 0x0001
#define DESIGN_PICKER_PAD_B 0x0002

/* The heap the scenes load into (autoload_2/heap.c). */
extern Heap *data_021fbe94;

/* Overlay 124's object (the title): destructor, constructor, its texts closed each frame, drawn,
 * its graphics loaded and opened. */
extern void *func_ov124_0229f43c(void *title);
extern void *func_ov124_0229f460(void *title);
extern void func_ov124_0229eea0(void *title);
extern void func_ov124_0229ef08(void *title, int x, int y);
extern void func_ov124_0229ef4c(void *title, int a);
extern void func_ov124_0229f398(void *title, int a, int b);

extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);

/* The panel's button the quit place stands for, and the sound of quitting. */
#define DESIGN_PICKER_QUIT_BUTTON 9
#define DESIGN_PICKER_QUIT_SOUND 0x28

/* The choice's rows: the confirm row's text by GroupParams' mode, and the other row's. */
#define DESIGN_PICKER_MESSAGE_CONFIRM_A 0x91 /* modes 5, 8 and 9 */
#define DESIGN_PICKER_MESSAGE_CONFIRM_B 0x72 /* modes 4, 7 and 10 */
#define DESIGN_PICKER_MESSAGE_CONFIRM_C 0x28 /* mode 6 and any other */
#define DESIGN_PICKER_MESSAGE_BACK 2

/* The cursor sprite's animations (glide.h): at a design, at the quit button or a choice row. */
#define DESIGN_PICKER_ANIM_DESIGN 1
#define DESIGN_PICKER_ANIM_ROW 7

/* What the parent (overlay 92's) is told when the scene wipes out: the menu closes, or (mode 4,
 * not quit) the screen of mode 2 comes next. */
#define DESIGN_PICKER_PARENT_CLOSE 0x44
#define DESIGN_PICKER_PARENT_NEXT 2
#define DESIGN_PICKER_MODE_NEXT 4

static MenuScene *picker_scene(DesignPicker *self)
{
    return &self->base;
}

static PagedChoice *picker_choice(DesignPicker *self)
{
    return (PagedChoice *) (void *) self->choice;
}

static CellLayerSprite *picker_sprite_cells(DesignPicker *self)
{
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

static MenuDispatch *picker_parent(DesignPicker *self)
{
    return (MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self);
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void picker_update_sprite(Glider *sprite)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* The members' destructors, last member first, then the base's. */
static void picker_destroy_members(DesignPicker *self)
{
    self->base.vtable = data_ov125_022a0ab8;
    ButtonPanel_Destroy(&self->panel);
    Glider0_Destroy(&self->cursor_sprite);
    Popup_Destroy(&self->popup);
    PagedChoice_Destroy(picker_choice(self));
    func_ov124_0229f43c(self->title);
    MenuScene_DestroyBase(picker_scene(self));
}

/* func_ov125_0229f6a0 (vtable slot 0x40) */
DesignPicker *DesignPicker_Destroy(DesignPicker *self)
{
    picker_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov125_0229f6a0, DesignPicker_Destroy)

/* func_ov125_0229f6f4 (vtable slot 0x44) */
DesignPicker *DesignPicker_Delete(DesignPicker *self)
{
    picker_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov125_0229f6f4, DesignPicker_Delete)

/* func_ov125_0229f74c */
void DesignPicker_ClearFlags(DesignPicker *self, u16 flags)
{
    self->flags = (u16) (self->flags & ~flags);
}
CLEAN_AS(func_ov125_0229f74c, DesignPicker_ClearFlags)

/* func_ov125_0229f75c */
void DesignPicker_SetFlags(DesignPicker *self, u16 flags)
{
    self->flags = (u16) (self->flags | flags);
}
CLEAN_AS(func_ov125_0229f75c, DesignPicker_SetFlags)

/* func_ov125_0229f76c */
int DesignPicker_TestFlags(DesignPicker *self, u16 flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov125_0229f76c, DesignPicker_TestFlags)

/* func_ov125_0229f784: the cursor moved by the d-pad keys `keys`; whether it moved. Left and
 * right step along the row, wrapping at its ends; up from the bottom row goes to the top one,
 * and from the quit button to the last design (turning the sprite back, set A); down from the
 * top row goes to the bottom one and from the bottom row to the quit button (set B). The wrap
 * flags are cleared first. */
int DesignPicker_MoveCursor(DesignPicker *self, int keys)
{
    u8 before = self->cursor;
    DesignPicker_ClearFlags(self, DESIGN_PICKER_FLAGS_WRAPPED);
    if (KeyRepeat_HasLeft(keys)) {
        if (DesignPicker_StepLeft(self, DESIGN_PICKER_TOP_FIRST, DESIGN_PICKER_TOP_LAST) == 0) {
            DesignPicker_StepLeft(self, DESIGN_PICKER_BOTTOM_FIRST, DESIGN_PICKER_BOTTOM_LAST);
        }
    } else if (KeyRepeat_HasRight(keys)) {
        if (DesignPicker_StepRight(self, DESIGN_PICKER_TOP_FIRST, DESIGN_PICKER_TOP_LAST) == 0) {
            DesignPicker_StepRight(self, DESIGN_PICKER_BOTTOM_FIRST, DESIGN_PICKER_BOTTOM_LAST);
        }
    }
    if (DesignPicker_TestFlags(self, DESIGN_PICKER_FLAGS_WRAPPED) == 0) {
        if (KeyRepeat_HasUp(keys)) {
            if (DesignPicker_RowUp(self, DESIGN_PICKER_BOTTOM_FIRST, DESIGN_PICKER_BOTTOM_LAST, DESIGN_PICKER_TOP_FIRST) ==
                    0 &&
                self->cursor == DESIGN_PICKER_QUIT) {
                self->cursor = DESIGN_PICKER_BOTTOM_LAST;
                Glider_TurnToSetA(&self->cursor_sprite);
            }
        } else if (KeyRepeat_HasDown(keys)) {
            if (DesignPicker_RowDown(self, DESIGN_PICKER_TOP_FIRST, DESIGN_PICKER_TOP_LAST, DESIGN_PICKER_BOTTOM_FIRST) == 0 &&
                self->cursor >= DESIGN_PICKER_BOTTOM_FIRST && self->cursor <= DESIGN_PICKER_BOTTOM_LAST) {
                self->cursor = DESIGN_PICKER_QUIT;
                Glider_TurnToSetB(&self->cursor_sprite);
            }
        }
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov125_0229f784, DesignPicker_MoveCursor)

/* func_ov125_0229f868: a cursor in places `first`-`last` moved to the same column of the row
 * starting at `to`; whether it was there. */
u8 DesignPicker_RowDown(DesignPicker *self, u8 first, u8 last, u8 to)
{
    u8 cursor = self->cursor;
    if (cursor < first || cursor > last) {
        return 0;
    }
    self->cursor = (u8) (cursor + (to - first));
    return 1;
}
CLEAN_AS(func_ov125_0229f868, DesignPicker_RowDown)

/* func_ov125_0229f890: the same as DesignPicker_RowDown, used for the move up. */
int DesignPicker_RowUp(DesignPicker *self, u8 first, u8 last, u8 to)
{
    u8 cursor = self->cursor;
    if (cursor < first || cursor > last) {
        return 0;
    }
    self->cursor = (u8) (cursor + (to - first));
    return 1;
}
CLEAN_AS(func_ov125_0229f890, DesignPicker_RowUp)

/* func_ov125_0229f8b8: a cursor in places `first`-`last` one place left, from `first` to `last`
 * (flagged as wrapped left); whether it was there. */
int DesignPicker_StepLeft(DesignPicker *self, unsigned int first, unsigned int last)
{
    u8 cursor = self->cursor;
    if (cursor < first || cursor > last) {
        return 0;
    }
    if (cursor == first) {
        self->cursor = (u8) last;
        DesignPicker_SetFlags(self, DESIGN_PICKER_FLAG_WRAPPED_LEFT);
    } else {
        self->cursor = (u8) (cursor - 1);
    }
    return 1;
}
CLEAN_AS(func_ov125_0229f8b8, DesignPicker_StepLeft)

/* func_ov125_0229f8ec: a cursor in places `first`-`last` one place right, from `last` to
 * `first` (flagged as wrapped right); whether it was there. */
int DesignPicker_StepRight(DesignPicker *self, u32 first, u32 last)
{
    u8 cursor = self->cursor;
    if (cursor < first || cursor > last) {
        return 0;
    }
    if (cursor == last) {
        DesignPicker_SetFlags(self, DESIGN_PICKER_FLAG_WRAPPED_RIGHT);
        self->cursor = (u8) first;
    } else {
        self->cursor = (u8) (cursor + 1);
    }
    return 1;
}
CLEAN_AS(func_ov125_0229f8ec, DesignPicker_StepRight)

/* func_ov125_0229f928: the cursor sprite shown (the first of its set) and updated. */
void DesignPicker_ShowCursorSprite(DesignPicker *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    picker_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov125_0229f928, DesignPicker_ShowCursorSprite)

/* func_ov125_0229f948: the cursor sprite put at the choice's first row. */
void DesignPicker_PointAtFirstRow(DesignPicker *self)
{
    self->choice_row = 0;
    int x = PagedChoice_TextX(picker_choice(self));
    int y = PagedChoice_RowY(picker_choice(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, DESIGN_PICKER_ANIM_ROW);
}
CLEAN_AS(func_ov125_0229f948, DesignPicker_PointAtFirstRow)

/* func_ov125_0229f994: the cursor sprite put at the cursor's place. */
void DesignPicker_PlaceSpriteAtCursor(DesignPicker *self)
{
    int x = DesignPicker_CursorSpriteX(self);
    int y = DesignPicker_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, DESIGN_PICKER_ANIM_DESIGN);
}
CLEAN_AS(func_ov125_0229f994, DesignPicker_PlaceSpriteAtCursor)

/* func_ov125_0229f9c8: the choice cancelled: the other row's action, its last row picked (with
 * the sound), the cursor sprite put there and its animation 8 run to its end; then the choice
 * closes (sub state 8). */
void DesignPicker_CancelChoice(DesignPicker *self)
{
    self->action = DESIGN_PICKER_ACTION_BACK;
    self->choice_row = PagedChoice_PickLastRow(picker_choice(self), 1);
    int x = PagedChoice_TextX(picker_choice(self));
    int y = PagedChoice_RowY(picker_choice(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    CellLayerSprite_SetAnimAtEnd(picker_sprite_cells(self), 8);
    MenuScene_SetSubState(picker_scene(self), DESIGN_PICKER_SUB_CHOICE_CLOSE);
}
CLEAN_AS(func_ov125_0229f9c8, DesignPicker_CancelChoice)

/* func_ov125_0229fa2c: the cursor sprite moved to the choice row in two steps, the sub state
 * kept to come back to once it stops (sub state 5). */
void DesignPicker_GlideToRow(DesignPicker *self)
{
    int x = PagedChoice_TextX(picker_choice(self));
    int y = PagedChoice_RowY(picker_choice(self), self->choice_row);
    Glider_MoveTo(&self->cursor_sprite, x, y, 2);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(picker_scene(self), DESIGN_PICKER_SUB_SPRITE_MOVE);
}
CLEAN_AS(func_ov125_0229fa2c, DesignPicker_GlideToRow)

/* func_ov125_0229fa80: the cursor sprite put at the cursor at once when flagged (the flag
 * cleared), else eased there in three steps, the sub state kept to come back to (sub state 5). */
void DesignPicker_GlideToCursor(DesignPicker *self)
{
    if (DesignPicker_TestFlags(self, DESIGN_PICKER_FLAG_JUMP)) {
        int x = DesignPicker_CursorSpriteX(self);
        int y = DesignPicker_CursorSpriteY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
        DesignPicker_ClearFlags(self, DESIGN_PICKER_FLAG_JUMP);
    } else {
        int x = DesignPicker_CursorSpriteX(self);
        int y = DesignPicker_CursorSpriteY(self);
        Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
        self->return_sub_state = self->base.sub_state;
        MenuScene_SetSubState(picker_scene(self), DESIGN_PICKER_SUB_SPRITE_MOVE);
    }
}
CLEAN_AS(func_ov125_0229fa80, DesignPicker_GlideToCursor)

/* func_ov125_0229faf8: the cursor sprite hidden (no animation) and updated. */
void DesignPicker_HideCursorSprite(DesignPicker *self)
{
    Glider_SetAnim(&self->cursor_sprite, 0);
    picker_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov125_0229faf8, DesignPicker_HideCursorSprite)

/* func_ov125_0229fb1c: where the cursor sprite points at the cursor's place: y. */
int DesignPicker_CursorSpriteY(DesignPicker *self)
{
    return DesignPicker_DesignY(self, self->cursor) - 11;
}
CLEAN_AS(func_ov125_0229fb1c, DesignPicker_CursorSpriteY)

/* func_ov125_0229fb34: ... x; after a wrap a screen (0x100) further in the move's direction,
 * so the sprite eases on the way it went (it is drawn wrapped, Glider_DrawWrapped). */
int DesignPicker_CursorSpriteX(DesignPicker *self)
{
    int x = DesignPicker_DesignX(self, self->cursor);
    if (DesignPicker_TestFlags(self, DESIGN_PICKER_FLAG_WRAPPED_RIGHT) != 0) {
        x += 0x100;
    } else if (DesignPicker_TestFlags(self, DESIGN_PICKER_FLAG_WRAPPED_LEFT) != 0) {
        x -= 0x100;
    }
    return x + 11;
}
CLEAN_AS(func_ov125_0229fb34, DesignPicker_CursorSpriteX)

/* func_ov125_0229fb7c: the cursor sprite put at the cursor, with the quit button's animation
 * or a design's, and shown. */
void DesignPicker_ShowCursorAtCursor(DesignPicker *self)
{
    int x = DesignPicker_CursorSpriteX(self);
    int y = DesignPicker_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (self->cursor == DESIGN_PICKER_QUIT) {
        Glider_SetAnim(&self->cursor_sprite, DESIGN_PICKER_ANIM_ROW);
    } else {
        Glider_SetAnim(&self->cursor_sprite, DESIGN_PICKER_ANIM_DESIGN);
    }
    DesignPicker_ShowCursorSprite(self);
}
CLEAN_AS(func_ov125_0229fb7c, DesignPicker_ShowCursorAtCursor)

/* func_ov125_0229fbd0: the choice's action. Confirm: the picked design handed back
 * (GroupParams_SetArg), main told (GroupParams_SetC4C(1)), state 3 (set directly), the popup
 * hidden and the states run again (phase 1). Any other: back to the designs. */
void DesignPicker_RunAction(DesignPicker *self)
{
    switch (self->action) {
        case DESIGN_PICKER_ACTION_CONFIRM:
            GroupParams_SetArg(self->picked);
            GroupParams_SetC4C(1);
            self->base.state = DESIGN_PICKER_STATE_START_WIPE_OUT;
            Popup_Hide(&self->popup, 1);
            MenuScene_SetPhase(picker_scene(self), 1);
            break;
        default:
            DesignPicker_Resume(self);
            break;
    }
}
CLEAN_AS(func_ov125_0229fbd0, DesignPicker_RunAction)

/* func_ov125_0229fc24: the choice shown from its entries, placed above the picked design and
 * asked to open (sub state 7). */
void DesignPicker_ShowChoice(DesignPicker *self)
{
    PagedChoice_ShowEntries(picker_choice(self), &self->entries, 0);
    int x = DesignPicker_DesignX(self, self->picked) - 0x18;
    int bottom = DesignPicker_DesignY(self, self->picked) - 0x10;
    PagedChoice_PlaceAbove(picker_choice(self), x, bottom);
    PagedChoice_RequestOpen(picker_choice(self), 0);
    MenuScene_SetSubState(picker_scene(self), DESIGN_PICKER_SUB_CHOICE_OPEN);
}
CLEAN_AS(func_ov125_0229fc24, DesignPicker_ShowChoice)

/* func_ov125_0229fc84: the value kept with choice entry `row`.
 * REQUIRES: row < 5 (the game passes a row of the choice); the game reads on past the entries. */
u8 DesignPicker_EntryValue(DesignPicker *self, int row)
{
    u32 address = (u32) (uintptr_t) self + offsetof(DesignPicker, entries) + offsetof(ChoiceEntries, values) + (u32) row;
    return *(const u8 *) (uintptr_t) address;
}
CLEAN_AS(func_ov125_0229fc84, DesignPicker_EntryValue)

/* func_ov125_0229fc90: the choice's entries: the confirm row (value 0) with the text of
 * GroupParams' mode, and the other row (value 1). */
void DesignPicker_FillEntries(DesignPicker *self)
{
    ChoiceEntries_Clear(&self->entries, 1);
    switch ((unsigned int) GroupParams_Mode() - 4) {
        case 1:
        case 4:
        case 5:
            ChoiceEntries_Add(&self->entries, DESIGN_PICKER_MESSAGE_CONFIRM_A, DESIGN_PICKER_ACTION_CONFIRM);
            break;
        case 0:
        case 3:
        case 6:
            ChoiceEntries_Add(&self->entries, DESIGN_PICKER_MESSAGE_CONFIRM_B, DESIGN_PICKER_ACTION_CONFIRM);
            break;
        default:
            ChoiceEntries_Add(&self->entries, DESIGN_PICKER_MESSAGE_CONFIRM_C, DESIGN_PICKER_ACTION_CONFIRM);
            break;
    }
    ChoiceEntries_Add(&self->entries, DESIGN_PICKER_MESSAGE_BACK, DESIGN_PICKER_ACTION_BACK);
}
CLEAN_AS(func_ov125_0229fc90, DesignPicker_FillEntries)

/* func_ov125_0229fd04: at a design, the popup queued for it; at the quit button, the popup
 * hidden (its queue dropped). */
void DesignPicker_QueuePopup(DesignPicker *self)
{
    u8 cursor = self->cursor;
    if (cursor <= DESIGN_PICKER_BOTTOM_LAST) {
        self->popup_design = cursor;
        Popup_Queue(&self->popup);
    } else {
        Popup_Hide(&self->popup, 1);
    }
}
CLEAN_AS(func_ov125_0229fd04, DesignPicker_QueuePopup)

/* func_ov125_0229fd3c: the popup placed above its design (10 pixels higher with the keys in
 * use) and given the design's title, converted from its wide text. */
void DesignPicker_SetPopupText(DesignPicker *self)
{
    NameWideText title;
    SlidingWindowText line;

    int y = DesignPicker_DesignY(self, self->popup_design) - 0x84;
    if (StateFlags_Test2()) {
        y -= 0xa;
    }
    int x = DesignPicker_DesignX(self, self->popup_design) - 0x78;
    SlidingWindow_SetPlace((SlidingWindow *) (void *) &self->popup, x, y);

    NameWideText_Construct(&title);
    PlayerDesigns *designs = PlayerRecord_Designs(PlayerRecords_Current());
    int design = PlayerDesigns_InOrder(designs, self->popup_design);
    unsigned int info = Design_Info((unsigned int) design);
    DesignInfo_TitleToWide((char *) (uintptr_t) info, (DesignTitleWide *) (void *) &title);

    SlidingWindowText_Construct(&line);
    TextString_WideToBytes((TextObject *) (void *) &line, (TextObject *) (void *) &title);
    SlidingWindow_SetText((SlidingWindow *) (void *) &self->popup, (struct TextObject *) (void *) &line);
    SlidingWindowText_Destruct(&line);
    NameWideText_Destruct(&title);
}
CLEAN_AS(func_ov125_0229fd3c, DesignPicker_SetPopupText)

/* func_ov125_0229fdc4: the place touched: the quit place when the panel's button 9 is, else
 * the first design within 16 pixels of the touch on both axes (by the tables' places), else 9. */
int DesignPicker_TouchedPlace(DesignPicker *self)
{
    if (ButtonPanel_IsTouched(&self->panel, DESIGN_PICKER_QUIT_BUTTON) != 0) {
        return DESIGN_PICKER_QUIT;
    }
    int touch_x = data_021f6c58;
    int touch_y = data_021f6c54;
    for (int place = 0; place < DESIGN_PICKER_DESIGNS; place++) {
        int x = DesignPicker_DesignX(self, place);
        if (x <= touch_x - 0x10 || x >= touch_x + 0x10) {
            continue;
        }
        int y = DesignPicker_DesignY(self, place);
        if (y <= touch_y - 0x10 || y >= touch_y + 0x10) {
            continue;
        }
        return place;
    }
    return DESIGN_PICKER_NO_PLACE;
}
CLEAN_AS(func_ov125_0229fdc4, DesignPicker_TouchedPlace)

/* func_ov125_0229fe40: the y of place `place` (a design's middle, or the quit button's).
 * REQUIRES: place <= 8; the game reads its table on for others. */
int DesignPicker_DesignY(DesignPicker *self, int place)
{
    (void) self;
    return data_ov125_022a0a10[place] - 16;
}
CLEAN_AS(func_ov125_0229fe40, DesignPicker_DesignY)

/* func_ov125_0229fe4c: ... its x. */
u8 DesignPicker_DesignX(DesignPicker *self, int place)
{
    (void) self;
    return data_ov125_022a0a04[place];
}
CLEAN_AS(func_ov125_0229fe4c, DesignPicker_DesignX)

/* func_ov125_0229fe58: the scene quit: the cursor sprite and the popup hidden, flagged, state 3
 * (set directly), main told nothing was picked (GroupParams_SetC4C(0)), the states run again
 * (phase 1) and the quit sound played. */
void DesignPicker_Quit(DesignPicker *self)
{
    DesignPicker_HideCursorSprite(self);
    Popup_Hide(&self->popup, 1);
    DesignPicker_SetFlags(self, DESIGN_PICKER_FLAG_QUIT);
    self->base.state = DESIGN_PICKER_STATE_START_WIPE_OUT;
    GroupParams_SetC4C(0);
    MenuScene_SetPhase(picker_scene(self), 1);
    SoundSys_PlaySe(DESIGN_PICKER_QUIT_SOUND);
}
CLEAN_AS(func_ov125_0229fe58, DesignPicker_Quit)

/* func_ov125_0229fe98: back to the designs, by touch or by the keys as the player last used. */
void DesignPicker_Resume(DesignPicker *self)
{
    if (StateFlags_IsClear2()) {
        DesignPicker_ResumeByTouch(self);
    } else {
        DesignPicker_ResumeByKeys(self);
    }
}
CLEAN_AS(func_ov125_0229fe98, DesignPicker_Resume)

/* func_ov125_0229feb8: back to the designs by the keys: the cursor sprite shown at the cursor,
 * the key repeat reset, the popup queued for the cursor's design (sub state 2). */
void DesignPicker_ResumeByKeys(DesignPicker *self)
{
    self->popup_design = DESIGN_PICKER_NO_PLACE;
    DesignPicker_ShowCursorAtCursor(self);
    MenuScene_ResetKeyRepeat(picker_scene(self));
    DesignPicker_QueuePopup(self);
    MenuScene_SetSubState(picker_scene(self), DESIGN_PICKER_SUB_BROWSE);
}
CLEAN_AS(func_ov125_0229feb8, DesignPicker_ResumeByKeys)

/* func_ov125_0229fee4: back to the designs by touch: the cursor sprite hidden (sub state 0). */
void DesignPicker_ResumeByTouch(DesignPicker *self)
{
    DesignPicker_HideCursorSprite(self);
    MenuScene_SetSubState(picker_scene(self), DESIGN_PICKER_SUB_TOUCH_BROWSE);
}
CLEAN_AS(func_ov125_0229fee4, DesignPicker_ResumeByTouch)

/* func_ov125_0229fefc (sub state 10): while the panel's selected button is pressed, the cursor
 * sprite (when it shows) follows the press; once it is over, the scene quits. */
void DesignPicker_FollowQuitPress(DesignPicker *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) == 0) {
        DesignPicker_Quit(self);
        return;
    }
    if (CellLayerSprite_AnimNumber(picker_sprite_cells(self)) != 0) {
        int frame = ButtonPanel_SelectedPressFrame(&self->panel);
        int x = ButtonPanel_ButtonX(&self->panel, -1);
        int y = ButtonPanel_ButtonY(&self->panel, -1);
        Glider_PlaceAt(&self->cursor_sprite, frame + x, frame + y);
    }
}
CLEAN_AS(func_ov125_0229fefc, DesignPicker_FollowQuitPress)

/* func_ov125_0229ff60 (sub state 9): the choice's action once the choice is idle. */
void DesignPicker_RunActionWhenIdle(DesignPicker *self)
{
    if (PagedChoice_IsIdle(picker_choice(self))) {
        DesignPicker_RunAction(self);
    }
}
CLEAN_AS(func_ov125_0229ff60, DesignPicker_RunActionWhenIdle)

/* func_ov125_0229ff80 (sub state 8): once the pick's delay is over, the choice asked to close
 * and the cursor sprite (when it shows) put back at the cursor (sub state 9). */
void DesignPicker_CloseChoice(DesignPicker *self)
{
    if (PagedChoice_CountDown(picker_choice(self)) == 0) {
        return;
    }
    PagedChoice_RequestClose(picker_choice(self), 0);
    if (CellLayerSprite_AnimNumber(picker_sprite_cells(self)) != 0) {
        DesignPicker_PlaceSpriteAtCursor(self);
    }
    MenuScene_SetSubState(picker_scene(self), DESIGN_PICKER_SUB_CHOICE_RUN);
}
CLEAN_AS(func_ov125_0229ff80, DesignPicker_CloseChoice)

/* func_ov125_0229ffc4 (sub state 7): once the choice is shown, its rows by the keys (the cursor
 * sprite at the first row, sub state 3) or by touch (sub state 1). */
void DesignPicker_WaitChoiceShown(DesignPicker *self)
{
    if (PagedChoice_IsShown(picker_choice(self)) == 0) {
        return;
    }
    if (StateFlags_Test2()) {
        DesignPicker_PointAtFirstRow(self);
        MenuScene_SetSubState(picker_scene(self), DESIGN_PICKER_SUB_CHOICE);
    } else {
        MenuScene_SetSubState(picker_scene(self), DESIGN_PICKER_SUB_TOUCH_CHOICE);
    }
}
CLEAN_AS(func_ov125_0229ffc4, DesignPicker_WaitChoiceShown)

/* func_ov125_022a0000 (sub state 6): once the cursor sprite's press at the quit button is over,
 * the panel's button 9 selected (sub state 10). */
void DesignPicker_WaitQuitSprite(DesignPicker *self)
{
    if (CellLayerSprite_IsDone(picker_sprite_cells(self))) {
        ButtonPanel_Select(&self->panel, DESIGN_PICKER_QUIT_BUTTON);
        MenuScene_SetSubState(picker_scene(self), DESIGN_PICKER_SUB_PANEL_PRESSED);
    }
}
CLEAN_AS(func_ov125_022a0000, DesignPicker_WaitQuitSprite)

/* Obj_ov125_022a0ab8::func_ov125_022a0030 (sub state 5): once the cursor sprite stops, the sub
 * state kept is run again, this frame. */
void DesignPicker_WaitCursorSprite(DesignPicker *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(picker_scene(self), self->return_sub_state);
        DesignPicker_RunSubState(self);
    }
}
CLEAN_AS(_ZN18Obj_ov125_022a0ab819func_ov125_022a0030Ev, DesignPicker_WaitCursorSprite)

/* func_ov125_022a0060 (sub state 4): once the cursor sprite's press is over, the choice row it
 * points at picked (with the sound) and its action kept (sub state 8). */
void DesignPicker_PickChoiceRow(DesignPicker *self)
{
    if (CellLayerSprite_IsDone(picker_sprite_cells(self))) {
        PagedChoice_PickRowWithSound(picker_choice(self), self->choice_row, 1);
        self->action = DesignPicker_EntryValue(self, self->choice_row);
        MenuScene_SetSubState(picker_scene(self), DESIGN_PICKER_SUB_CHOICE_CLOSE);
    }
}
CLEAN_AS(func_ov125_022a0060, DesignPicker_PickChoiceRow)

/* func_ov125_022a00ac (sub state 3): the choice by the keys. A touch hides the cursor sprite and
 * goes on by touch (sub state 1). Else the d-pad moves the cursor sprite between the rows; then
 * A presses the sprite on its row (sub state 4) and B cancels the choice. */
void DesignPicker_ChooseByKeys(DesignPicker *self)
{
    if (MenuScene_TakeTouch(picker_scene(self)) != 0) {
        DesignPicker_HideCursorSprite(self);
        MenuScene_SetSubState(picker_scene(self), DESIGN_PICKER_SUB_TOUCH_CHOICE);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(picker_scene(self));
    if (PagedChoice_MoveCursor(picker_choice(self), keys, &self->choice_row, 0) != 0) {
        DesignPicker_GlideToRow(self);
    }
    if ((data_021fbe40.pressed & DESIGN_PICKER_PAD_A) != 0) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(picker_scene(self), DESIGN_PICKER_SUB_CHOICE_PICK);
    } else if ((data_021fbe40.pressed & DESIGN_PICKER_PAD_B) != 0) {
        DesignPicker_CancelChoice(self);
    }
}
CLEAN_AS(func_ov125_022a00ac, DesignPicker_ChooseByKeys)

/* func_ov125_022a012c (sub state 2): the designs by the keys. A touch hides the cursor sprite
 * and the popup and goes on by touch. A move of the cursor queues the popup for its design and
 * glides the sprite there, the popup hidden meanwhile (its queue kept). A at the quit button
 * presses the sprite (sub state 6); at a design it opens the design's choice. B quits by the
 * panel's button 9 (sub state 10). With none of these the queued popup is shown. */
void DesignPicker_BrowseByKeys(DesignPicker *self)
{
    if (MenuScene_TakeTouch(picker_scene(self)) != 0) {
        DesignPicker_ResumeByTouch(self);
        Popup_Hide(&self->popup, 1);
        return;
    }
    if (DesignPicker_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(picker_scene(self))) != 0) {
        DesignPicker_QueuePopup(self);
        DesignPicker_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if ((pressed & DESIGN_PICKER_PAD_A) != 0) {
        if (self->cursor == DESIGN_PICKER_QUIT) {
            Glider_ShowSecondOfSet(&self->cursor_sprite);
            MenuScene_SetSubState(picker_scene(self), DESIGN_PICKER_SUB_QUIT_PRESS);
        } else {
            Popup_Hide(&self->popup, 1);
            DesignPicker_FillEntries(self);
            self->picked = self->cursor;
            DesignPicker_ShowChoice(self);
            DesignPicker_HideCursorSprite(self);
        }
    } else if ((pressed & DESIGN_PICKER_PAD_B) != 0) {
        DesignPicker_HideCursorSprite(self);
        ButtonPanel_Select(&self->panel, DESIGN_PICKER_QUIT_BUTTON);
        MenuScene_SetSubState(picker_scene(self), DESIGN_PICKER_SUB_PANEL_PRESSED);
        Popup_Hide(&self->popup, 1);
    } else {
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov125_022a012c, DesignPicker_BrowseByKeys)

/* func_ov125_022a0214 (sub state 1): the choice by touch. A button goes on by the keys (the
 * cursor sprite at the first row, sub state 3, the cursor at the picked design). A touch that
 * went down or up this frame on a row picks it (with the sound) and keeps its action (sub
 * state 8). */
void DesignPicker_ChooseByTouch(DesignPicker *self)
{
    if (MenuScene_TakeButtons(picker_scene(self), 1) != 0) {
        DesignPicker_PointAtFirstRow(self);
        MenuScene_SetSubState(picker_scene(self), DESIGN_PICKER_SUB_CHOICE);
        self->cursor = self->picked;
        return;
    }
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        int row = PagedChoice_RowAtOrLast(picker_choice(self), data_021f6c58, data_021f6c54);
        if (row >= 0) {
            PagedChoice_PickRowWithSound(picker_choice(self), row, 1);
            self->action = DesignPicker_EntryValue(self, row);
            MenuScene_SetSubState(picker_scene(self), DESIGN_PICKER_SUB_CHOICE_CLOSE);
        }
    }
}
CLEAN_AS(func_ov125_022a0214, DesignPicker_ChooseByTouch)

/* func_ov125_022a02b4 (sub state 0): the designs by touch. A button goes on by the keys. A
 * touch that went down or up this frame on the quit button quits by the panel's button 9 (sub
 * state 10); on a design it opens the design's choice. */
void DesignPicker_BrowseByTouch(DesignPicker *self)
{
    if (MenuScene_TakeButtons(picker_scene(self), 1) != 0) {
        DesignPicker_ResumeByKeys(self);
        return;
    }
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        int place = DesignPicker_TouchedPlace(self);
        if (place == DESIGN_PICKER_QUIT) {
            ButtonPanel_Select(&self->panel, DESIGN_PICKER_QUIT_BUTTON);
            MenuScene_SetSubState(picker_scene(self), DESIGN_PICKER_SUB_PANEL_PRESSED);
        } else if (place != DESIGN_PICKER_NO_PLACE) {
            DesignPicker_FillEntries(self);
            self->picked = (u8) place;
            DesignPicker_ShowChoice(self);
        }
    }
}
CLEAN_AS(func_ov125_022a02b4, DesignPicker_BrowseByTouch)

/* func_ov125_022a0334: the scene's graphics: the designs, overlay 124's title (4) and the
 * panel's text colours. */
void DesignPicker_LoadGraphics(DesignPicker *self)
{
    DesignPicker_LoadDesigns();
    func_ov124_0229ef4c(self->title, 4);
    ButtonPanel_LoadTextColors(&self->panel);
}
CLEAN_AS(func_ov125_022a0334, DesignPicker_LoadGraphics)

/* func_ov125_022a0358: the current player's designs, in their order, loaded into the OBJs: the
 * pixels of each made into four by four characters (TileConvert_BitmapToSheet, design n at
 * character n * 4 of the sheet) in a block from the back of the scenes' heap, loaded as OBJ
 * characters 0xc0-0x13f; then each design's 16 colours copied into a second block, loaded as
 * OBJ palettes 5-12. */
void DesignPicker_LoadDesigns(void)
{
    Heap *heap = data_021fbe94;
    u32 *sheet = Heap_AllocBack(heap, 0x1000);
    PlayerDesigns *designs = PlayerRecord_Designs(PlayerRecords_Current());
    for (int i = 0; i < DESIGN_PICKER_DESIGNS; i++) {
        Design *design = (Design *) (uintptr_t) (u32) PlayerDesigns_InOrder(designs, i);
        TileConvert_BitmapToSheet(Design_Pixels(design), sheet, i * 4, 4, 4);
    }
    DisplayLayer_LoadChars((u32) (uintptr_t) sheet, 8, 0xc0, 0xc0, 0x13f);
    Heap_Free(heap, sheet);

    u16 *palettes = Heap_AllocBack(heap, 0x100);
    int offset = 0;
    for (int i = 0; i < DESIGN_PICKER_DESIGNS; i++) {
        unsigned int design = (unsigned int) PlayerDesigns_InOrder(designs, i);
        DesignInfo *info = (DesignInfo *) (uintptr_t) Design_Info(design);
        MIi_CpuCopy16((const void *) (uintptr_t) (u32) DesignInfo_PaletteColours(info), palettes + offset, 0x20);
        offset += 0x10;
    }
    DisplayLayer_LoadPalettes((u8 *) palettes, 8, 5, 5, 0xc);
    Heap_Free(heap, palettes);
}
CLEAN_AS(func_ov125_022a0358, DesignPicker_LoadDesigns)

/* func_ov125_022a0418: overlay 124's title opened (6, 4). */
void DesignPicker_OpenTitle(DesignPicker *self)
{
    func_ov124_0229f398(self->title, 6, 4);
}
CLEAN_AS(func_ov125_022a0418, DesignPicker_OpenTitle)

/* func_ov125_022a0428: the sub screen's background mode 0; layers 6 and 4 at priority 2, layer 3
 * at priority 1, each with its control reset. */
void DesignPicker_SetUpLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(6, 2);
    DisplayLayer_SetBgControl(6, 0, 0, 0);
    DisplayLayer_SetPriority(4, 2);
    DisplayLayer_SetBgControl(4, 0, 0, 0);
    DisplayLayer_SetPriority(3, 1);
    DisplayLayer_SetBgControl(3, 0, 0, 0);
}
CLEAN_AS(func_ov125_022a0428, DesignPicker_SetUpLayers)

/* func_ov125_022a0474: the frame's end: the choice updated, and the popup; when the popup asks
 * for its text, it is given. */
void DesignPicker_EndFrame(DesignPicker *self)
{
    PagedChoice_Update(picker_choice(self));
    if (Popup_Update(&self->popup)) {
        DesignPicker_SetPopupText(self);
    }
}
CLEAN_AS(func_ov125_022a0474, DesignPicker_EndFrame)

/* func_ov125_022a04a0: the frame's start: the panel's and the title's texts closed. */
void DesignPicker_BeginFrame(DesignPicker *self)
{
    ButtonPanel_CloseTexts(&self->panel);
    func_ov124_0229eea0(self->title);
}
CLEAN_AS(func_ov125_022a04a0, DesignPicker_BeginFrame)

/* func_ov125_022a04c0 */
void DesignPicker_EndInteractiveFrame(DesignPicker *self)
{
    DesignPicker_EndFrame(self);
}
CLEAN_AS(func_ov125_022a04c0, DesignPicker_EndInteractiveFrame)

/* func_ov125_022a04c8: the frame's start, then the cursor sprite updated. */
void DesignPicker_BeginInteractiveFrame(DesignPicker *self)
{
    DesignPicker_BeginFrame(self);
    picker_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov125_022a04c8, DesignPicker_BeginInteractiveFrame)

/* func_ov125_022a04e4: the members torn down: the choice dismissed, the title's and the panel's
 * texts closed. */
void DesignPicker_Teardown(DesignPicker *self)
{
    PagedChoice_Dismiss(picker_choice(self));
    func_ov124_0229eea0(self->title);
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov125_022a04e4, DesignPicker_Teardown)

/* func_ov125_022a0510: the setup: no flags, the choice on layer 3 at priority 1 (its own
 * screen), no design shown nor picked, the cursor at the first design, main told nothing is
 * picked yet (GroupParams_SetC4C(0)) and the popup's draw value 2. */
void DesignPicker_Setup(DesignPicker *self)
{
    self->flags = 0;
    PagedChoice_Init(picker_choice(self), 3, 1, NULL);
    self->popup_design = DESIGN_PICKER_NO_PLACE;
    self->picked = DESIGN_PICKER_NO_PLACE;
    self->cursor = DESIGN_PICKER_TOP_FIRST;
    GroupParams_SetC4C(0);
    Popup_SetDrawValue(&self->popup, 2);
}
CLEAN_AS(func_ov125_022a0510, DesignPicker_Setup)

/* func_ov125_022a0564: layers 6 and 4 scrolled with the wipe, and the wipe's y kept and
 * answered. */
int DesignPicker_ScrollWithWipe(DesignPicker *self)
{
    MenuScene_ScrollWipe(picker_scene(self), 6, 0, 0);
    MenuScene_ScrollWipe(picker_scene(self), 4, 0, 0);
    int y = MenuScene_WipeOffsetY(picker_scene(self));
    self->wipe_y = y;
    return y;
}
CLEAN_AS(func_ov125_022a0564, DesignPicker_ScrollWithWipe)

/* func_ov125_022a0594 (state 4): the wipe out stepped; at its end layers 6 and 4 hidden, the
 * scene no longer drawn and deleted (phase 5); before, the layers follow it. */
void DesignPicker_WipeOut(DesignPicker *self)
{
    if (MenuScene_StepWipe(picker_scene(self), 0)) {
        DisplayLayer_HideAndResetScroll(6);
        DisplayLayer_HideAndResetScroll(4);
        DesignPicker_ClearFlags(self, DESIGN_PICKER_FLAG_DRAWN);
        MenuScene_SetPhase(picker_scene(self), 5);
    } else {
        DesignPicker_ScrollWithWipe(self);
    }
}
CLEAN_AS(func_ov125_022a0594, DesignPicker_WipeOut)

/* func_ov125_022a05cc (state 3): the cursor sprite hidden and the parent told what comes next:
 * after a quit, or in any mode but 4, the menu closes; in mode 4 the screen of mode 2 follows.
 * Then the wipe out started on window 2 (layers 2 and 8, margin 0x30) and state 4. */
void DesignPicker_StartWipeOut(DesignPicker *self)
{
    DesignPicker_HideCursorSprite(self);
    MenuDispatch *parent = picker_parent(self);
    int mode = GroupParams_Mode();
    if (DesignPicker_TestFlags(self, DESIGN_PICKER_FLAG_QUIT) != 0) {
        MenuDispatch_SetMode(parent, DESIGN_PICKER_PARENT_CLOSE, 1);
    } else if (mode == DESIGN_PICKER_MODE_NEXT) {
        MenuDispatch_SetMode(parent, DESIGN_PICKER_PARENT_NEXT, 1);
    } else {
        MenuDispatch_SetMode(parent, DESIGN_PICKER_PARENT_CLOSE, 1);
    }
    MenuScene_StartWipeOnWindow2(picker_scene(self), 0xa, 0, 0, 0x30);
    DesignPicker_ScrollWithWipe(self);
    MenuScene_SetState(picker_scene(self), DESIGN_PICKER_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov125_022a05cc, DesignPicker_StartWipeOut)

/* func_ov125_022a063c (state 2): the wipe in stepped; at its end the scene goes interactive
 * (phase 2) on the designs. The layers follow the wipe; answers its y. */
int DesignPicker_WipeIn(DesignPicker *self)
{
    if (MenuScene_StepWipeBack(picker_scene(self), 0)) {
        MenuScene_SetPhase(picker_scene(self), 2);
        DesignPicker_Resume(self);
    }
    return DesignPicker_ScrollWithWipe(self);
}
CLEAN_AS(func_ov125_022a063c, DesignPicker_WipeIn)

/* func_ov125_022a0664 (state 1): the choice's and the scene's graphics loaded, the wipe in
 * started covered on window 2 (layers 2 and 8, 4 frames, margin 0x30), layers 6 and 4 shown and
 * following it, the panel in layout 5 with message 0x65, the scene drawn; state 2. */
void DesignPicker_StartWipeIn(DesignPicker *self)
{
    PagedChoice_LoadChoiceGraphics(picker_choice(self));
    DesignPicker_LoadGraphics(self);
    MenuScene_StartWipeCoveredOnWindow2(picker_scene(self), 0xa, 4, 0, 0x30);
    DisplayLayer_Show(6);
    DisplayLayer_Show(4);
    DesignPicker_ScrollWithWipe(self);
    ButtonPanel_SetLayout5(&self->panel, 0x65);
    DesignPicker_SetFlags(self, DESIGN_PICKER_FLAG_DRAWN);
    MenuScene_SetState(picker_scene(self), DESIGN_PICKER_STATE_WIPE_IN);
}
CLEAN_AS(func_ov125_022a0664, DesignPicker_StartWipeIn)

/* func_ov125_022a06c4 (state 0): the layers set up and the title opened; state 1. */
void DesignPicker_StartSetup(DesignPicker *self)
{
    DesignPicker_SetUpLayers();
    DesignPicker_OpenTitle(self);
    MenuScene_SetState(picker_scene(self), DESIGN_PICKER_STATE_START_WIPE_IN);
}
CLEAN_AS(func_ov125_022a06c4, DesignPicker_StartSetup)

/* func_ov125_022a06e0 (vtable slot 0x5c, phase 5): the scene asks to be deleted. */
int DesignPicker_End(DesignPicker *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov125_022a06e0, DesignPicker_End)

/* func_ov125_022a06f0 (vtable slot 0x58, phase 4): nothing. */
int DesignPicker_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov125_022a06f0, DesignPicker_Phase4Idle)

/* func_ov125_022a06f4 (vtable slot 0x54, phase 3): nothing. */
int DesignPicker_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov125_022a06f4, DesignPicker_Phase3Idle)

/* Obj_ov125_022a0ab8::func_ov125_022a06f8 (vtable slot 0x50, phase 2): a frame of the scene in
 * use: its start, its sub state and its end. Answers 1. */
int DesignPicker_RunInteractive(DesignPicker *self)
{
    DesignPicker_BeginInteractiveFrame(self);
    DesignPicker_RunSubState(self);
    DesignPicker_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov125_022a0ab819func_ov125_022a06f8Ev, DesignPicker_RunInteractive)

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables and their
 * constants. */
extern u32 data_ov125_022a0b20; /* the states' guard */
extern u32 data_ov125_022a0b24; /* the sub states' guard */
extern MemberPointer data_ov125_022a0b28[DESIGN_PICKER_STATES];
extern MemberPointer data_ov125_022a0b50[DESIGN_PICKER_SUB_STATES];
extern const MemberPointer data_ov125_022a0a20, data_ov125_022a0a30, data_ov125_022a0a38, data_ov125_022a0a40,
    data_ov125_022a0a48, data_ov125_022a0a50, data_ov125_022a0a58, data_ov125_022a0a60, data_ov125_022a0a68,
    data_ov125_022a0a70, data_ov125_022a0a78, data_ov125_022a0a80, data_ov125_022a0a90, data_ov125_022a0a98,
    data_ov125_022a0aa0, data_ov125_022a0aa8;

/* Obj_ov125_022a0ab8::func_ov125_022a0714: the sub state's function (DesignPickerSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 11; the game reads past the table for others. */
void DesignPicker_RunSubState(DesignPicker *self)
{
    static const MemberPointer *const sub_states[DESIGN_PICKER_SUB_STATES] = {
        &data_ov125_022a0a48, &data_ov125_022a0a78, &data_ov125_022a0a70, &data_ov125_022a0a68,
        &data_ov125_022a0a30, &data_ov125_022a0a58, &data_ov125_022a0a50, &data_ov125_022a0a40,
        &data_ov125_022a0a80, &data_ov125_022a0a38, &data_ov125_022a0a60,
    };
    MemberTable_InitOnce(&data_ov125_022a0b24, data_ov125_022a0b50, sub_states, DESIGN_PICKER_SUB_STATES);
    MemberPointer_CallVoid(&data_ov125_022a0b50[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov125_022a0ab819func_ov125_022a0714Ev, DesignPicker_RunSubState)

/* func_ov125_022a07fc (vtable slot 0x4c, phase 1): a frame of the scene's states
 * (DesignPickerState) between the frame's start and end, through the table of member functions
 * (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 5; the game reads past the table for others. */
int DesignPicker_RunState(DesignPicker *self)
{
    static const MemberPointer *const states[DESIGN_PICKER_STATES] = {
        &data_ov125_022a0a90, &data_ov125_022a0a20, &data_ov125_022a0aa8, &data_ov125_022a0aa0, &data_ov125_022a0a98,
    };
    MemberTable_InitOnce(&data_ov125_022a0b20, data_ov125_022a0b28, states, DESIGN_PICKER_STATES);
    DesignPicker_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov125_022a0b28[self->base.state], self);
    DesignPicker_EndFrame(self);
    return 1;
}
CLEAN_AS(func_ov125_022a07fc, DesignPicker_RunState)

/* A member drawn through its class (vtable slot 2). */
static void picker_draw_member(void *object)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[2])(object);
}

/* func_ov125_022a089c (vtable slot 0x24): the scene's draw, while it is drawn (else answers 0):
 * the popup (through its class), the cursor sprite (with the keys in use), the panel with the
 * wipe, the title at the wipe's y kept, and the eight designs: design n as the OBJ of tile
 * 0xc0 + n * 4 (written into the OBJ's data) in palette 5 + n at its place, moved by the wipe's
 * y kept. Answers 1. */
int DesignPicker_Draw(DesignPicker *self)
{
    int wipe_y = self->wipe_y;
    if (DesignPicker_TestFlags(self, DESIGN_PICKER_FLAG_DRAWN) == 0) {
        return 0;
    }
    picker_draw_member(&self->popup);
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    ButtonPanel_Draw(&self->panel, MenuScene_WipeOffsetY(picker_scene(self)));
    func_ov124_0229ef08(self->title, 0, wipe_y);
    OamEntry *obj = &data_ov125_022a0a28;
    for (int i = 0; i < DESIGN_PICKER_DESIGNS; i++) {
        obj->attr2 = (u16) ((obj->attr2 & ~0x3ffu) | ((unsigned int) (i * 4 + 0xc0) & 0x3ffu));
        int y = wipe_y + DesignPicker_DesignY(self, i);
        int x = DesignPicker_DesignX(self, i);
        OamBuffer_DrawObjAffine(1, obj, x, y, i + 5, 2, NULL);
    }
    return 1;
}
CLEAN_AS(func_ov125_022a089c, DesignPicker_Draw)

/* func_ov125_022a0968 (vtable slot 0x0c): the scene closes: the parent told and the members
 * torn down. Answers 1. */
int DesignPicker_Close(DesignPicker *self)
{
    MenuDispatch_ChildClosed(picker_parent(self));
    DesignPicker_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov125_022a0968, DesignPicker_Close)

/* func_ov125_022a0984 (vtable slot 0x00): the scene starts: its setup, state 0 (set directly)
 * and phase 0. Answers 1. */
int DesignPicker_Start(DesignPicker *self)
{
    DesignPicker_Setup(self);
    self->base.state = DESIGN_PICKER_STATE_START_SETUP;
    MenuScene_SetPhase(picker_scene(self), 0);
    return 1;
}
CLEAN_AS(func_ov125_022a0984, DesignPicker_Start)

/* func_ov125_022a09a4 (named by the profile at 0x022a0a88): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order. */
DesignPicker *DesignPicker_New(void)
{
    DesignPicker *self = MenuScene_Alloc(sizeof(DesignPicker));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov125_022a0ab8;
    func_ov124_0229f460(self->title);
    PagedChoice_Construct(picker_choice(self));
    Popup_Construct(&self->popup);
    Glider0_Construct(&self->cursor_sprite);
    ButtonPanel_Construct(&self->panel);
    return self;
}
CLEAN_AS(func_ov125_022a09a4, DesignPicker_New)
