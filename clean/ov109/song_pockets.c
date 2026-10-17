/* Overlay 109's scene (song_pockets.h). */
#include "song_pockets.h"

#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/group_params.h"
#include "main/house_record.h"
#include "main/sliding_window.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"
#include "ov094/pockets_common.h"

/* The class's vtable. */
extern const u8 data_ov109_0229dbd8[];

/* The touch (main's bytes, as ov099/pockets_view.c reads them). */
extern u8 data_021f6c58; /* x */
extern u8 data_021f6c54; /* y */

/* What the grid's object answers for no slot under the touch. */
#define GRID_NO_INDEX POCKETS_GRID_NO_PLACE

/* The answers for a place outside the grid (SongPockets_PlaceItem, SongPockets_PlaceItemState). */
#define NO_ITEM 0xfff1
#define NO_ITEM_STATE 0xf1

/* Where SONG_POCKETS_BUTTON is (SongPockets_PlaceX, SongPockets_PlaceY). */
#define BUTTON_X 0xbc
#define BUTTON_Y 0xb6

/* The grid's places are drawn 0x10 lower than its object says (SongPockets_PlaceY). */
#define GRID_OFFSET_Y 0x10

/* The song items the scene leaves undimmed (main/house_record.h's range). */
#define SONG_FIRST 0x1323
#define SONG_LAST 0x1368

/* The choice's row texts. */
#define ROW_TEXT_ADD 0x73
#define ROW_TEXT_CANCEL 2

/* The panel's button that closes the scene, and the sound of its press. */
#define PANEL_BUTTON_CLOSE 9
#define SOUND_PANEL_PRESS 0x28

/* The error message for a song the house has already. */
#define ERROR_HAS_SONG 17

/* The cursor sprite's animation at the end of a back out of the choice. */
#define CURSOR_ANIM_BACK 8

static MenuScene *scene_of(SongPockets *self)
{
    return &self->base;
}

static PagedChoice *choice_of(SongPockets *self)
{
    return (PagedChoice *) (void *) self->choice;
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base);
 * what it leaves in the result register. */
static int update_cursor_sprite(SongPockets *self)
{
    Glider *sprite = &self->cursor_sprite;
    const u32 *vtable = (const u32 *) sprite->vtable;
    return ((int (*)(Glider *))(uintptr_t) vtable[3])(sprite);
}

/* The members' destructors, last member first, then the base's. */
static void destroy_members(SongPockets *self)
{
    self->base.vtable = data_ov109_0229dbd8;
    ButtonPanel_Destroy(&self->panel);
    ErrorMessage_Destruct(&self->error);
    PagedChoice_Destroy(choice_of(self));
    Glider0_Destroy(&self->cursor_sprite);
    Glide_Destroy(&self->glide);
    Popup_Destroy(&self->popup);
    PocketsWallet_Destruct(&self->wallet);
    PocketsLetters_Destruct(&self->letters);
    PocketsGrid_Destruct(&self->grid);
    MenuScene_DestroyBase(scene_of(self));
}

/* func_ov109_0229c180 (vtable slot 0x40) */
SongPockets *SongPockets_Destroy(SongPockets *self)
{
    destroy_members(self);
    return self;
}
CLEAN_AS(func_ov109_0229c180, SongPockets_Destroy)

/* func_ov109_0229c204 (vtable slot 0x44) */
SongPockets *SongPockets_Delete(SongPockets *self)
{
    destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov109_0229c204, SongPockets_Delete)

/* func_ov109_0229c28c */
void SongPockets_ClearFlags(SongPockets *self, unsigned int flags)
{
    self->flags &= ~flags;
}
CLEAN_AS(func_ov109_0229c28c, SongPockets_ClearFlags)

/* func_ov109_0229c29c */
void SongPockets_SetFlags(SongPockets *self, unsigned int flags)
{
    self->flags |= flags;
}
CLEAN_AS(func_ov109_0229c29c, SongPockets_SetFlags)

/* func_ov109_0229c2ac: whether any of `flags` is set. */
int SongPockets_TestFlags(SongPockets *self, int flags)
{
    return (self->flags & (u32) flags) != 0;
}
CLEAN_AS(func_ov109_0229c2ac, SongPockets_TestFlags)

/* func_ov109_0229c2c4: the cursor moved by the repeated d-pad keys `keys` (the wrap flags of
 * the last move cleared first); whether it moved. In the grid it moves by
 * SongPockets_MoveCursorInGrid; from the button, up goes back to the grid's last slot with the
 * cursor sprite turning to its first set. */
int SongPockets_MoveCursor(SongPockets *self, int keys)
{
    u8 before = self->cursor;
    SongPockets_ClearFlags(self, SONG_POCKETS_FLAGS_WRAPPED);
    if (keys == 0) {
        return 0;
    }
    if (SongPockets_IsGridPlace(self, self->cursor)) {
        SongPockets_MoveCursorInGrid(self, keys);
    } else if (self->cursor == SONG_POCKETS_BUTTON && KeyRepeat_HasUp(keys)) {
        self->cursor = SONG_POCKETS_GRID_LAST;
        Glider_TurnToSetA(&self->cursor_sprite);
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov109_0229c2c4, SongPockets_MoveCursor)

/* func_ov109_0229c330: the cursor moved in the grid. Left and right move one column, wrapping
 * to the other end of the row (and saying so in the flags); unless the move wrapped, up and
 * down then move one row, stopping at the first; down from the last row goes to the button,
 * with the cursor sprite turning to its second set.
 * QUIRK: left is ignored when up is held too and the cursor is below the first row; right is
 * ignored whenever down is held too. */
void SongPockets_MoveCursorInGrid(SongPockets *self, int keys)
{
    int column = self->cursor % SONG_POCKETS_COLUMNS;
    int row = self->cursor / SONG_POCKETS_COLUMNS;

    if (KeyRepeat_HasLeft(keys)) {
        if (!(KeyRepeat_HasUp(keys) && row != 0)) {
            if (column == 0) {
                self->cursor += SONG_POCKETS_COLUMNS - 1;
                SongPockets_SetFlags(self, SONG_POCKETS_FLAG_WRAPPED_LEFT);
            } else {
                self->cursor -= 1;
            }
        }
    } else if (KeyRepeat_HasRight(keys) && !KeyRepeat_HasDown(keys)) {
        if (column == SONG_POCKETS_COLUMNS - 1) {
            self->cursor -= SONG_POCKETS_COLUMNS - 1;
            SongPockets_SetFlags(self, SONG_POCKETS_FLAG_WRAPPED_RIGHT);
        } else {
            self->cursor += 1;
        }
    }

    if (SongPockets_TestFlags(self, SONG_POCKETS_FLAGS_WRAPPED)) {
        return;
    }
    if (KeyRepeat_HasUp(keys)) {
        if (row > 0) {
            self->cursor -= SONG_POCKETS_COLUMNS;
        }
    } else if (KeyRepeat_HasDown(keys)) {
        if (row < SONG_POCKETS_ROWS - 1) {
            self->cursor += SONG_POCKETS_COLUMNS;
        } else {
            self->cursor = SONG_POCKETS_BUTTON;
            Glider_TurnToSetB(&self->cursor_sprite);
        }
    }
}
CLEAN_AS(func_ov109_0229c330, SongPockets_MoveCursorInGrid)

/* func_ov109_0229c418: `place` picked: its rows emptied (value: cancel); for a place of the
 * grid the rows added, the cursor sprite hidden (and the popup, unless the choice goes above
 * it) and the choice shown. */
void SongPockets_OpenChoice(SongPockets *self, u8 place, int above_popup)
{
    self->slot = place;
    ChoiceEntries_Clear(&self->entries, SONG_POCKETS_ACTION_CANCEL);
    if (SongPockets_IsGridPlace(self, place)) {
        SongPockets_AddEntries(self);
        SongPockets_HideCursorSprite(self);
        if (above_popup == 0) {
            Popup_Hide(&self->popup, 1);
        }
        SongPockets_ShowChoice(self, above_popup);
    }
}
CLEAN_AS(func_ov109_0229c418, SongPockets_OpenChoice)

/* func_ov109_0229c470: the choice's rows: the song added, then cancel. */
void SongPockets_AddEntries(SongPockets *self)
{
    ChoiceEntries_Add(&self->entries, ROW_TEXT_ADD, SONG_POCKETS_ACTION_ADD);
    ChoiceEntries_Add(&self->entries, ROW_TEXT_CANCEL, SONG_POCKETS_ACTION_CANCEL);
}
CLEAN_AS(func_ov109_0229c470, SongPockets_AddEntries)

/* func_ov109_0229c498: the scene closes without a song: GroupParams_SetC4C(0), state 3 in the
 * states' phase, the popup and the cursor sprite hidden. */
void SongPockets_CloseWithoutSong(SongPockets *self)
{
    GroupParams_SetC4C(0);
    self->base.state = SONG_POCKETS_STATE_START_WIPE_OUT;
    MenuScene_SetPhase(scene_of(self), SONG_POCKETS_PHASE_STATES);
    Popup_Hide(&self->popup, 1);
    SongPockets_HideCursorSprite(self);
}
CLEAN_AS(func_ov109_0229c498, SongPockets_CloseWithoutSong)

/* func_ov109_0229c4cc: the panel's button 9 pressed (sub state 0x0f follows its press), with
 * its sound. */
void SongPockets_PressPanelButton9(SongPockets *self)
{
    ButtonPanel_Select(&self->panel, PANEL_BUTTON_CLOSE);
    MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_PANEL_PRESS);
    SoundSys_PlaySe(SOUND_PANEL_PRESS);
}
CLEAN_AS(func_ov109_0229c4cc, SongPockets_PressPanelButton9)

/* func_ov109_0229c4f4: the scene closes after a song was added: the slot it came from given to
 * GroupParams, GroupParams_SetC4C(1), state 3 in the states' phase, the popup and the cursor
 * sprite hidden. */
void SongPockets_CloseWithSong(SongPockets *self)
{
    GroupParams_SetArg(self->slot);
    GroupParams_SetC4C(1);
    self->base.state = SONG_POCKETS_STATE_START_WIPE_OUT;
    MenuScene_SetPhase(scene_of(self), SONG_POCKETS_PHASE_STATES);
    Popup_Hide(&self->popup, 1);
    SongPockets_HideCursorSprite(self);
}
CLEAN_AS(func_ov109_0229c4f4, SongPockets_CloseWithSong)

/* func_ov109_0229c534: the choice closed without a pick: the cancel action, the cursor sprite
 * back at the cursor, sub state 0x0d. */
void SongPockets_CancelChoice(SongPockets *self)
{
    self->action = SONG_POCKETS_ACTION_CANCEL;
    SongPockets_PlaceCursorSprite(self);
    PagedChoice_RequestClose(choice_of(self), 0);
    MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_CHOICE_CLOSING);
}
CLEAN_AS(func_ov109_0229c534, SongPockets_CancelChoice)

/* func_ov109_0229c564: the rows shown and the choice opened above the popup or beside the
 * picked place; sub state 0x0b. The place's x and y are asked for either way. */
void SongPockets_ShowChoice(SongPockets *self, int above_popup)
{
    PagedChoice_ShowEntries(choice_of(self), &self->entries, 0);
    int x = SongPockets_PlaceX(self, self->slot);
    int y = SongPockets_PlaceY(self, self->slot);
    if (above_popup) {
        PagedChoice_PlaceAboveWindow(choice_of(self), &self->popup);
    } else {
        PagedChoice_PlaceBeside(choice_of(self), x, y);
    }
    PagedChoice_RequestOpen(choice_of(self), 0);
    MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_CHOICE_OPENING);
}
CLEAN_AS(func_ov109_0229c564, SongPockets_ShowChoice)

/* func_ov109_0229c5d4: the picked row's action. To add: when the house has the slot's song
 * already, error message 17; else the song added, the slot emptied and the scene closed with
 * it. Any other action ends the choice. */
void SongPockets_RunAction(SongPockets *self)
{
    if (self->action == SONG_POCKETS_ACTION_ADD) {
        int item = SongPockets_PlaceItem(self, self->slot);
        if (HouseRecord_HasSong((unsigned int) item)) {
            SongPockets_ShowError(self, ERROR_HAS_SONG);
        } else {
            HouseRecord_AddSong((unsigned int) item);
            SongPockets_SetSlotItem(self, self->slot, NO_ITEM, 0);
            SongPockets_CloseWithSong(self);
        }
    } else {
        SongPockets_EndAction(self);
    }
}
CLEAN_AS(func_ov109_0229c5d4, SongPockets_RunAction)

/* func_ov109_0229c638: A on the button: the cursor sprite's press (the second of its set);
 * sub state 9 presses the panel's button once it ends. */
void SongPockets_PressButtonPlace(SongPockets *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_BUTTON_BY_KEYS);
}
CLEAN_AS(func_ov109_0229c638, SongPockets_PressButtonPlace)

/* func_ov109_0229c658: the first animation of the cursor sprite's set, then its update.
 * QUIRK: answers what the update leaves in the result register; no caller reads it. */
int SongPockets_ShowCursorFirstOfSet(SongPockets *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    return update_cursor_sprite(self);
}
CLEAN_AS(func_ov109_0229c658, SongPockets_ShowCursorFirstOfSet)

/* func_ov109_0229c678: the cursor sprite put at the cursor, animation 1. */
void SongPockets_PlaceCursorSprite(SongPockets *self)
{
    int x = SongPockets_CursorSpriteX(self);
    int y = SongPockets_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
}
CLEAN_AS(func_ov109_0229c678, SongPockets_PlaceCursorSprite)

/* func_ov109_0229c6ac: the cursor sprite put at the choice's first row, animation 7. */
void SongPockets_PointAtFirstRow(SongPockets *self)
{
    self->choice_row = 0;
    int x = PagedChoice_TextX(choice_of(self));
    int y = PagedChoice_RowY(choice_of(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_B);
}
CLEAN_AS(func_ov109_0229c6ac, SongPockets_PointAtFirstRow)

/* func_ov109_0229c6f8: B in the choice: the cancel action, the last row picked (with sound 1)
 * and the cursor sprite put there, animation 8 once its own ends; sub state 0x0c. Answers
 * MenuScene_SetSubState's result. */
int SongPockets_PointAtLastRow(SongPockets *self)
{
    self->action = SONG_POCKETS_ACTION_CANCEL;
    self->choice_row = PagedChoice_PickLastRow(choice_of(self), 1);
    int x = PagedChoice_TextX(choice_of(self));
    int y = PagedChoice_RowY(choice_of(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    CellLayerSprite_SetAnimAtEnd((CellLayerSprite *) (void *) &self->cursor_sprite, CURSOR_ANIM_BACK);
    return (int) (uintptr_t) MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_CHOICE_CLOSE);
}
CLEAN_AS(func_ov109_0229c6f8, SongPockets_PointAtLastRow)

/* func_ov109_0229c75c: the cursor sprite moves to the choice row in 2 steps; the sub state is
 * kept and sub state 8 waits for the move. */
void SongPockets_GlideToRow(SongPockets *self)
{
    int x = PagedChoice_TextX(choice_of(self));
    int y = PagedChoice_RowY(choice_of(self), self->choice_row);
    Glider_MoveTo(&self->cursor_sprite, x, y, 2);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_WAIT_SPRITE);
}
CLEAN_AS(func_ov109_0229c75c, SongPockets_GlideToRow)

/* func_ov109_0229c7b0: the cursor sprite follows the cursor: put there at once when
 * SONG_POCKETS_FLAG_SPRITE_JUMP is set (which is then cleared), else eased there in 3 steps
 * (cue 1) with the sub state kept and sub state 8 waiting for the move. */
void SongPockets_GlideToCursor(SongPockets *self)
{
    if (SongPockets_TestFlags(self, SONG_POCKETS_FLAG_SPRITE_JUMP)) {
        int x = SongPockets_CursorSpriteX(self);
        int y = SongPockets_CursorSpriteY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
        SongPockets_ClearFlags(self, SONG_POCKETS_FLAG_SPRITE_JUMP);
    } else {
        int x = SongPockets_CursorSpriteX(self);
        int y = SongPockets_CursorSpriteY(self);
        Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
        self->return_state = self->base.sub_state;
        MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_WAIT_SPRITE);
    }
}
CLEAN_AS(func_ov109_0229c7b0, SongPockets_GlideToCursor)

/* func_ov109_0229c828: the cursor sprite's animation 0, then its update. */
void SongPockets_HideCursorSprite(SongPockets *self)
{
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_NONE);
    update_cursor_sprite(self);
}
CLEAN_AS(func_ov109_0229c828, SongPockets_HideCursorSprite)

/* func_ov109_0229c84c: the cursor sprite's y, the cursor's place's. */
int SongPockets_CursorSpriteY(SongPockets *self)
{
    return SongPockets_PlaceY(self, self->cursor);
}
CLEAN_AS(func_ov109_0229c84c, SongPockets_CursorSpriteY)

/* func_ov109_0229c85c: the cursor sprite's x: the cursor's place's plus 8, and a screen width
 * (256) further right or left when this move wrapped over the right or left edge. */
int SongPockets_CursorSpriteX(SongPockets *self)
{
    int x = SongPockets_PlaceX(self, self->cursor);
    if (SongPockets_TestFlags(self, SONG_POCKETS_FLAG_WRAPPED_RIGHT)) {
        x += 0x100;
    } else if (SongPockets_TestFlags(self, SONG_POCKETS_FLAG_WRAPPED_LEFT)) {
        x -= 0x100;
    }
    return x + 8;
}
CLEAN_AS(func_ov109_0229c85c, SongPockets_CursorSpriteX)

/* func_ov109_0229c8a4: the cursor sprite put at the cursor, animation 7 at the button and 1
 * elsewhere, then the first of its set. */
void SongPockets_ShowCursorSprite(SongPockets *self)
{
    int x = SongPockets_CursorSpriteX(self);
    int y = SongPockets_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (self->cursor == SONG_POCKETS_BUTTON) {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_B);
    } else {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
    }
    SongPockets_ShowCursorFirstOfSet(self);
}
CLEAN_AS(func_ov109_0229c8a4, SongPockets_ShowCursorSprite)

/* func_ov109_0229c8f8: the held item drawn by the grid's object, unless it is hidden. */
void SongPockets_DrawHeld(SongPockets *self)
{
    if (SongPockets_TestFlags(self, SONG_POCKETS_FLAG_HELD_HIDDEN)) {
        return;
    }
    if (self->held_kind == SONG_POCKETS_HELD_ITEM) {
        PocketsGrid_DrawHeld(&self->grid, self->held_x, self->held_y);
    }
}
CLEAN_AS(func_ov109_0229c8f8, SongPockets_DrawHeld)

/* func_ov109_0229c934: the popup tells of the cursor's place: queued for a grid place that
 * holds an item (kept as `popup_place`), its queue cleared for an empty one or the button. */
void SongPockets_UpdatePopup(SongPockets *self)
{
    if (SongPockets_IsGridPlace(self, self->cursor) && !SongPockets_PlaceIsEmpty(self, self->cursor)) {
        self->popup_place = self->cursor;
        Popup_Queue(&self->popup);
    } else {
        Popup_ClearQueued(&self->popup);
    }
}
CLEAN_AS(func_ov109_0229c934, SongPockets_UpdatePopup)

/* func_ov109_0229c988: the popup put above its place (0x6d left and 0x78 up of it, 8 more up
 * when state flag 2 is set) and, for a grid place, filled with its item's text. */
void SongPockets_PlacePopup(SongPockets *self)
{
    int x = SongPockets_PlaceX(self, self->popup_place) - 0x6d;
    int y = SongPockets_PlaceY(self, self->popup_place) - 0x78;
    if (StateFlags_Test2()) {
        y -= 8;
    }
    SlidingWindow_SetPlace((SlidingWindow *) (void *) &self->popup, x, y);
    if (SongPockets_IsGridPlace(self, self->popup_place)) {
        int index = SongPockets_GridIndex(self, self->popup_place);
        PocketsGrid_ShowItemText(&self->grid, &self->popup, index);
    }
}
CLEAN_AS(func_ov109_0229c988, SongPockets_PlacePopup)

/* func_ov109_0229c9f0: `place` lifted in the grid (the letters' lift dropped); for another
 * place, both dropped. */
void SongPockets_SelectPlace(SongPockets *self, unsigned int place)
{
    if (SongPockets_IsGridPlace(self, place)) {
        PocketsGrid_Lift(&self->grid, SongPockets_GridIndex(self, (int) place));
        PocketsLetters_Unlift(&self->letters);
    } else {
        SongPockets_ClearSelection(self);
    }
}
CLEAN_AS(func_ov109_0229c9f0, SongPockets_SelectPlace)

/* func_ov109_0229ca30 */
void SongPockets_ClearSelection(SongPockets *self)
{
    PocketsGrid_Unlift(&self->grid);
    PocketsLetters_Unlift(&self->letters);
}
CLEAN_AS(func_ov109_0229ca30, SongPockets_ClearSelection)

/* func_ov109_0229ca4c: the state of the item at grid place `place`, else 0xf1. */
int SongPockets_PlaceItemState(SongPockets *self, int place)
{
    if (SongPockets_IsGridPlace(self, (unsigned int) place)) {
        return PocketsGrid_ItemState(&self->grid, SongPockets_GridIndex(self, place));
    }
    return NO_ITEM_STATE;
}
CLEAN_AS(func_ov109_0229ca4c, SongPockets_PlaceItemState)

/* func_ov109_0229ca7c: the item at grid place `place`, else none (0xfff1). */
int SongPockets_PlaceItem(SongPockets *self, int place)
{
    if (SongPockets_IsGridPlace(self, (unsigned int) place)) {
        return PocketsGrid_Item(&self->grid, SongPockets_GridIndex(self, place));
    }
    return NO_ITEM;
}
CLEAN_AS(func_ov109_0229ca7c, SongPockets_PlaceItem)

/* func_ov109_0229cab0: whether grid place `place` is empty; other places count as empty. */
int SongPockets_PlaceIsEmpty(SongPockets *self, int place)
{
    if (SongPockets_IsGridPlace(self, (unsigned int) place)) {
        return PocketsGrid_IsEmpty(&self->grid, SongPockets_GridIndex(self, place));
    }
    return 1;
}
CLEAN_AS(func_ov109_0229cab0, SongPockets_PlaceIsEmpty)

/* func_ov109_0229cae0: whether grid place `place` is dimmed; other places are not. */
int SongPockets_PlaceIsDimmed(SongPockets *self, int place)
{
    if (SongPockets_IsGridPlace(self, (unsigned int) place)) {
        return PocketsGrid_IsDimmed(&self->grid, SongPockets_GridIndex(self, place));
    }
    return 0;
}
CLEAN_AS(func_ov109_0229cae0, SongPockets_PlaceIsDimmed)

/* func_ov109_0229cb10: every slot that holds an item but not a song in the plain state (0)
 * dimmed. */
void SongPockets_DimNonSongs(SongPockets *self)
{
    for (int place = SONG_POCKETS_GRID_FIRST; place <= SONG_POCKETS_GRID_LAST; place++) {
        int dim = 0;
        if (!SongPockets_PlaceIsEmpty(self, place)) {
            if (SongPockets_PlaceItemState(self, place) != 0) {
                dim = 1;
            } else {
                u16 item = (u16) SongPockets_PlaceItem(self, place);
                dim = !(item >= SONG_FIRST && item <= SONG_LAST);
            }
        }
        if (dim) {
            PocketsGrid_DimPlace(&self->grid, SongPockets_GridIndex(self, place));
        }
    }
}
CLEAN_AS(func_ov109_0229cb10, SongPockets_DimNonSongs)

/* func_ov109_0229cb9c: the y of `place`: a grid slot's (its object's, 0x10 lower), the
 * button's, else 0. */
int SongPockets_PlaceY(SongPockets *self, int place)
{
    if (SongPockets_IsGridPlace(self, (unsigned int) place)) {
        return PocketsGrid_PlaceY(&self->grid, SongPockets_GridIndex(self, place)) - GRID_OFFSET_Y;
    }
    if (place == SONG_POCKETS_BUTTON) {
        return BUTTON_Y;
    }
    return 0;
}
CLEAN_AS(func_ov109_0229cb9c, SongPockets_PlaceY)

/* func_ov109_0229cbd4: the x of `place`: a grid slot's, the button's, else 0. */
int SongPockets_PlaceX(SongPockets *self, int place)
{
    if (SongPockets_IsGridPlace(self, (unsigned int) place)) {
        return PocketsGrid_PlaceX(&self->grid, SongPockets_GridIndex(self, place));
    }
    if (place == SONG_POCKETS_BUTTON) {
        return BUTTON_X;
    }
    return 0;
}
CLEAN_AS(func_ov109_0229cbd4, SongPockets_PlaceX)

/* func_ov109_0229cc0c: for a grid place, its slot set to `item` in `state` (the grid's object
 * writes the pocket slot too) and redrawn. */
void SongPockets_SetSlotItem(SongPockets *self, int place, int item, int state)
{
    if (SongPockets_IsGridPlace(self, (unsigned int) place)) {
        int index = SongPockets_GridIndex(self, place);
        PocketsGrid_SetItem(&self->grid, index, item, state);
        PocketsGrid_RefreshPlace(&self->grid, (unsigned int) index);
    }
}
CLEAN_AS(func_ov109_0229cc0c, SongPockets_SetSlotItem)

/* func_ov109_0229cc4c: the grid's place under the touch, by the grid's object; with
 * `with_item`, only one that holds an item. SONG_POCKETS_NO_PLACE for none. */
int SongPockets_GridPlaceAtTouch(SongPockets *self, int x, int y, int with_item)
{
    int index = PocketsGrid_PocketPlaceAtTouch(&self->grid, x, y);
    if (index == GRID_NO_INDEX) {
        return SONG_POCKETS_NO_PLACE;
    }
    if (with_item != 0 && PocketsGrid_IsEmpty(&self->grid, index)) {
        return SONG_POCKETS_NO_PLACE;
    }
    return SongPockets_GridPlace(self, (unsigned int) index);
}
CLEAN_AS(func_ov109_0229cc4c, SongPockets_GridPlaceAtTouch)

/* func_ov109_0229cc88: the place of grid slot `index` (0-14), else SONG_POCKETS_NO_PLACE. */
int SongPockets_GridPlace(SongPockets *self, unsigned int index)
{
    (void) self;
    if (index <= SONG_POCKETS_GRID_LAST) {
        return (u8) index;
    }
    return SONG_POCKETS_NO_PLACE;
}
CLEAN_AS(func_ov109_0229cc88, SongPockets_GridPlace)

/* func_ov109_0229cc98: the slot index of a grid place, else 0. */
unsigned char SongPockets_GridIndex(SongPockets *self, int place)
{
    if (SongPockets_IsGridPlace(self, (unsigned int) place)) {
        return (unsigned char) place;
    }
    return 0;
}
CLEAN_AS(func_ov109_0229cc98, SongPockets_GridIndex)

/* func_ov109_0229ccb4: whether `place` is in the grid. */
int SongPockets_IsGridPlace(SongPockets *self, unsigned int place)
{
    (void) self;
    return place <= SONG_POCKETS_GRID_LAST;
}
CLEAN_AS(func_ov109_0229ccb4, SongPockets_IsGridPlace)

/* func_ov109_0229ccc0: the load task at 0x94 ended for this frame. */
void SongPockets_EndLayerTask(SongPockets *self)
{
    LayerTask_End((LayerTask *) (void *) &self->tasks);
}
CLEAN_AS(func_ov109_0229ccc0, SongPockets_EndLayerTask)

/* func_ov109_0229cccc: error message `message` opened (sub state 0x0e) and the cursor
 * sprite's window cleared. (The ROM first reads data_021f43ec into the message's byte, then
 * overwrites it.) */
void SongPockets_ShowError(SongPockets *self, unsigned char message)
{
    u8 text = message;
    ErrorMessage_Open(&self->error, &text, 1, 0);
    MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_ERROR);
    CellLayerSprite_ClearWindow((CellLayerSprite *) (void *) &self->cursor_sprite);
}
CLEAN_AS(func_ov109_0229cccc, SongPockets_ShowError)

/* func_ov109_0229cd10: the pen touched `place` (sub state 1): the offset from the touch to the
 * place kept, the popup told of it and shown, the choice due in 2 frames; sound 0xc unless
 * the place is dimmed. */
void SongPockets_TouchPlace(SongPockets *self, int place)
{
    self->touch_place = (u8) place;
    MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_HOLD_TOUCH);
    u8 touch_x = data_021f6c58;
    u8 touch_y = data_021f6c54;
    self->grab_dx = SongPockets_PlaceX(self, self->touch_place) - touch_x;
    self->grab_dy = SongPockets_PlaceY(self, self->touch_place) - touch_y;
    self->popup_place = (u8) place;
    Popup_Queue(&self->popup);
    Popup_ShowQueued(&self->popup);
    self->open_delay = 2;
    if (SongPockets_PlaceIsDimmed(self, place) == 0) {
        PocketsSound_Play0c();
    }
}
CLEAN_AS(func_ov109_0229cd10, SongPockets_TouchPlace)

/* The sub states and the states the scene runs each frame, its draw, its setup and its
 * construction. */

/* The pad (autoload_2/input.h): the buttons pressed this frame. */
extern PadState data_021fbe40;
#define PAD_A 0x0001
#define PAD_B 0x0002

/* The pen (main's bytes, as menu_scene.c reads them). */
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */

/* The tables of member functions (ov004/member_pointer.h): their guards, the tables and the
 * constants they are filled from. */
extern u32 data_ov109_0229dc40; /* the states' guard */
extern u32 data_ov109_0229dc44; /* the sub states' guard */
extern MemberPointer data_ov109_0229dc48[SONG_POCKETS_STATES];
extern MemberPointer data_ov109_0229dc70[SONG_POCKETS_SUB_STATES];
extern const MemberPointer data_ov109_0229db28, data_ov109_0229db30, data_ov109_0229db38, data_ov109_0229db40,
    data_ov109_0229db48, data_ov109_0229db50, data_ov109_0229db58, data_ov109_0229db60, data_ov109_0229db68,
    data_ov109_0229db70, data_ov109_0229db78, data_ov109_0229db80, data_ov109_0229db88, data_ov109_0229db90,
    data_ov109_0229db98, data_ov109_0229dba0, data_ov109_0229dba8, data_ov109_0229dbb0, data_ov109_0229dbb8,
    data_ov109_0229dbc0, data_ov109_0229dbc8;

/* The scene's 2D layer, and its wipe on window 2. */
#define SONG_POCKETS_LAYER 6
#define WIPE_LAYERS 8
#define WIPE_MARGIN 0x30
#define WIPE_SCROLL_Y (-0x10)

/* The panel's message in layout 5. */
#define PANEL_MESSAGE 0x65

/* The letters' states dimmed: all of them. */
#define LETTERS_DIMMED 0xf

/* The objects of ov094's are drawn 0x10 above the wipe's offset. */
#define OBJECTS_OFFSET_Y 0x10

/* What ov092's dispatch is told comes after the scene: mode 0x40's screen, or the close. */
#define NEXT_MODE 0x40

/* The frames a popup stays after the pen leaves a dimmed place. */
#define POPUP_FRAMES 60

/* The parent process (ov092's dispatch). */
static MenuDispatch *parent_of(SongPockets *self)
{
    return (MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self);
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
static u8 row_value(SongPockets *self, int row)
{
    const u8 *values = (const u8 *) self + offsetof(SongPockets, entries) + offsetof(ChoiceEntries, values);
    return values[row];
}

/* Choice row `row` picked (with sound 1): its value kept as `action`, and sub state 0x0c
 * closes the choice. */
static void pick_row(SongPockets *self, int row)
{
    PagedChoice_PickRowWithSound(choice_of(self), row, 1);
    self->action = row_value(self, row);
    MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_CHOICE_CLOSE);
}

static CellLayerSprite *cursor_cells(SongPockets *self)
{
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

/* func_ov109_0229cd9c: the action ends: back to sub state 0 with the cursor sprite hidden
 * while state flag 2 is clear, else to sub state 5 with it at the cursor. */
void SongPockets_EndAction(SongPockets *self)
{
    if (StateFlags_IsClear2()) {
        SongPockets_EndActionHidden(self);
    } else {
        SongPockets_EndActionAtCursor(self);
    }
}
CLEAN_AS(func_ov109_0229cd9c, SongPockets_EndAction)

/* func_ov109_0229cdbc: no popup place, the cursor sprite shown at the cursor, the key repeat
 * reset, the popup told of the cursor's place, sub state 5 and the cursor's place lifted. */
void SongPockets_EndActionAtCursor(SongPockets *self)
{
    self->popup_place = SONG_POCKETS_NO_PLACE;
    SongPockets_ShowCursorSprite(self);
    MenuScene_ResetKeyRepeat(scene_of(self));
    SongPockets_UpdatePopup(self);
    MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_IDLE_BY_KEYS);
    SongPockets_SelectPlace(self, self->cursor);
}
CLEAN_AS(func_ov109_0229cdbc, SongPockets_EndActionAtCursor)

/* func_ov109_0229cdf8 */
void SongPockets_EndActionHidden(SongPockets *self)
{
    SongPockets_HideCursorSprite(self);
    SongPockets_ClearSelection(self);
    MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_IDLE_BY_TOUCH);
}
CLEAN_AS(func_ov109_0229cdf8, SongPockets_EndActionHidden)

/* func_ov109_0229ce14 (sub state 0x0f): while the panel's selected button is being pressed,
 * the cursor sprite (when it shows an animation) follows the button down; once the press is
 * over the scene closes without a song. */
void SongPockets_FollowPanelPress(SongPockets *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) == 0) {
        SongPockets_CloseWithoutSong(self);
        return;
    }
    if (CellLayerSprite_AnimNumber(cursor_cells(self)) != 0) {
        int depth = ButtonPanel_SelectedPressFrame(&self->panel);
        int x = ButtonPanel_ButtonX(&self->panel, -1);
        int y = ButtonPanel_ButtonY(&self->panel, -1);
        Glider_PlaceAt(&self->cursor_sprite, depth + x, depth + y);
    }
}
CLEAN_AS(func_ov109_0229ce14, SongPockets_FollowPanelPress)

/* func_ov109_0229ce78 (sub state 0x0e): once the error message is done (looking at its flag
 * 0x80), the action ends and the cursor sprite's window is set again. */
void SongPockets_WaitError(SongPockets *self)
{
    if (ErrorMessage_Update(&self->error, 1)) {
        SongPockets_EndAction(self);
        CellLayerSprite_SetWindow(cursor_cells(self));
    }
}
CLEAN_AS(func_ov109_0229ce78, SongPockets_WaitError)

/* func_ov109_0229cea8 (sub state 0x0d): once the choice is idle, the picked row's action. */
void SongPockets_RunActionWhenIdle(SongPockets *self)
{
    if (PagedChoice_IsIdle(choice_of(self))) {
        SongPockets_RunAction(self);
    }
}
CLEAN_AS(func_ov109_0229cea8, SongPockets_RunActionWhenIdle)

/* func_ov109_0229cec8 (sub state 0x0c): when the choice's delay has run out, the choice asked
 * to close, the popup hidden, the cursor sprite (when it shows an animation) put back at the
 * cursor and sub state 0x0d. */
void SongPockets_CloseChoice(SongPockets *self)
{
    if (PagedChoice_CountDown(choice_of(self)) == 0) {
        return;
    }
    PagedChoice_RequestClose(choice_of(self), 0);
    Popup_Hide(&self->popup, 1);
    if (CellLayerSprite_AnimNumber(cursor_cells(self)) != 0) {
        SongPockets_PlaceCursorSprite(self);
    }
    MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_CHOICE_CLOSING);
}
CLEAN_AS(func_ov109_0229cec8, SongPockets_CloseChoice)

/* func_ov109_0229cf18 (sub state 0x0b): once the choice is shown: with state flag 2 the cursor
 * sprite at its first row and sub state 6 (the keys), else sub state 4 (the touch). */
void SongPockets_WaitChoiceShown(SongPockets *self)
{
    if (PagedChoice_IsShown(choice_of(self)) == 0) {
        return;
    }
    if (StateFlags_Test2()) {
        SongPockets_PointAtFirstRow(self);
        MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_CHOICE_BY_KEYS);
    } else {
        MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_CHOICE_BY_TOUCH);
    }
}
CLEAN_AS(func_ov109_0229cf18, SongPockets_WaitChoiceShown)

/* func_ov109_0229cf54 (sub state 0x0a): once the cursor sprite's animation ends, the first of
 * its set and sub state 5. */
void SongPockets_WaitCursorAnim(SongPockets *self)
{
    if (CellLayerSprite_IsDone(cursor_cells(self))) {
        SongPockets_ShowCursorFirstOfSet(self);
        MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_IDLE_BY_KEYS);
    }
}
CLEAN_AS(func_ov109_0229cf54, SongPockets_WaitCursorAnim)

/* func_ov109_0229cf7c (sub state 9): once the cursor sprite's press on the button ends, the
 * panel's button 9 pressed (sub state 0x0f), with its sound. */
void SongPockets_PressButtonAfterAnim(SongPockets *self)
{
    if (CellLayerSprite_IsDone(cursor_cells(self))) {
        ButtonPanel_Select(&self->panel, PANEL_BUTTON_CLOSE);
        MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_PANEL_PRESS);
        SoundSys_PlaySe(SOUND_PANEL_PRESS);
    }
}
CLEAN_AS(func_ov109_0229cf7c, SongPockets_PressButtonAfterAnim)

/* func_ov109_0229cfb4 (sub state 8): once the cursor sprite stops, back to the kept sub state
 * (back to 5, the cursor's place is lifted), which then runs at once this frame. */
void SongPockets_WaitCursorGlide(SongPockets *self)
{
    if (Glider_IsMoving(&self->cursor_sprite)) {
        return;
    }
    MenuScene_SetSubState(scene_of(self), self->return_state);
    if (self->return_state == SONG_POCKETS_SUB_IDLE_BY_KEYS) {
        SongPockets_SelectPlace(self, self->cursor);
    }
    SongPockets_RunSubState(self);
}
CLEAN_AS(func_ov109_0229cfb4, SongPockets_WaitCursorGlide)

/* func_ov109_0229cff8 (sub state 7): once the cursor sprite's press animation ends, the row it
 * points at is picked. */
void SongPockets_PickChoiceRow(SongPockets *self)
{
    if (CellLayerSprite_IsDone(cursor_cells(self))) {
        pick_row(self, self->choice_row);
    }
}
CLEAN_AS(func_ov109_0229cff8, SongPockets_PickChoiceRow)

/* func_ov109_0229d048 (sub state 6): the choice by the keys. The menu's close or a touch
 * cancels it; the d-pad moves the cursor sprite over the rows; A presses on the row (sub
 * state 7); B goes to the last row and cancels (SongPockets_PointAtLastRow). */
void SongPockets_ChooseByKeys(SongPockets *self)
{
    if (StateFlags_MenuCloseAsked()) {
        SongPockets_CancelChoice(self);
        return;
    }
    if (MenuScene_TakeTouch(scene_of(self))) {
        SongPockets_CancelChoice(self);
        return;
    }
    u32 keys = MenuScene_LatchRepeatedKeys(scene_of(self));
    if (PagedChoice_MoveCursor(choice_of(self), (int) keys, &self->choice_row, 0)) {
        SongPockets_GlideToRow(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & PAD_A) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_PICK_ROW);
    } else if (pressed & PAD_B) {
        SongPockets_PointAtLastRow(self);
    }
}
CLEAN_AS(func_ov109_0229d048, SongPockets_ChooseByKeys)

/* func_ov109_0229d0d4 (sub state 5): the cursor waits for the keys. A touch hides the cursor
 * sprite and the popup (sub state 0). The d-pad moves the cursor, the popup telling of the
 * new place and hidden. A at a place that is not dimmed opens the choice of a grid place that
 * holds an item, or presses on the button. B hides the cursor sprite and presses the panel's
 * button 9; else a queued popup is shown.
 * QUIRK: A at a dimmed place is not taken as A: B is tested next. */
void SongPockets_IdleByKeys(SongPockets *self)
{
    if (MenuScene_TakeTouch(scene_of(self))) {
        SongPockets_EndActionHidden(self);
        Popup_Hide(&self->popup, 1);
        return;
    }
    u32 keys = MenuScene_LatchRepeatedKeys(scene_of(self));
    if (SongPockets_MoveCursor(self, (int) keys)) {
        SongPockets_UpdatePopup(self);
        SongPockets_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    if (SongPockets_PlaceIsDimmed(self, self->cursor) == 0 && (data_021fbe40.pressed & PAD_A) != 0) {
        if (SongPockets_IsGridPlace(self, self->cursor)) {
            if (SongPockets_PlaceIsEmpty(self, self->cursor) == 0) {
                SongPockets_OpenChoice(self, self->cursor, 0);
            }
        } else if (self->cursor == SONG_POCKETS_BUTTON) {
            SongPockets_PressButtonPlace(self);
        }
        return;
    }
    if (data_021fbe40.pressed & PAD_B) {
        SongPockets_HideCursorSprite(self);
        SongPockets_PressPanelButton9(self);
        Popup_Hide(&self->popup, 0);
    } else {
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov109_0229d0d4, SongPockets_IdleByKeys)

/* func_ov109_0229d1b0 (sub state 4): the choice by touch, once it is shown. The menu's close
 * or a button cancels it; a touch on a row (or below the rows: the last one) picks it. */
void SongPockets_ChooseByTouch(SongPockets *self)
{
    if (PagedChoice_IsShown(choice_of(self)) == 0) {
        return;
    }
    if (StateFlags_MenuCloseAsked()) {
        SongPockets_CancelChoice(self);
        return;
    }
    if (MenuScene_TakeButtons(scene_of(self), 1)) {
        SongPockets_CancelChoice(self);
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
CLEAN_AS(func_ov109_0229d1b0, SongPockets_ChooseByTouch)

/* func_ov109_0229d258 (sub state 3): once the popup is up and the delay has run out, the
 * touched place's choice opens above the popup and sub state 2 waits for the pen to lift. */
void SongPockets_OpenTouchedChoice(SongPockets *self)
{
    if (Popup_IsUp(&self->popup) == 0) {
        return;
    }
    if (self->open_delay != 0) {
        self->open_delay--;
    } else {
        SongPockets_OpenChoice(self, self->touch_place, 1);
        MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_WAIT_PEN_UP);
    }
}
CLEAN_AS(func_ov109_0229d258, SongPockets_OpenTouchedChoice)

/* func_ov109_0229d2a0 (sub state 2): once the menu is asked to close or the pen lifts, sub
 * state 4 (the choice by touch). */
void SongPockets_WaitPenUp(SongPockets *self)
{
    if (StateFlags_MenuCloseAsked()) {
        MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_CHOICE_BY_TOUCH);
    } else if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_CHOICE_BY_TOUCH);
    }
}
CLEAN_AS(func_ov109_0229d2a0, SongPockets_WaitPenUp)

/* func_ov109_0229d2d0 (sub state 1): the pen is on a touched place (SongPockets_TouchPlace).
 * Lifted from a dimmed place: back to sub state 0 with the popup closing after 60 frames;
 * from another, sub state 3, run at once. Held on a place that is not dimmed while the popup
 * is up: once the delay has run out its choice opens above the popup (sub state 2). Else a
 * queued popup is shown. */
void SongPockets_HoldTouchOnPlace(SongPockets *self)
{
    if (data_021fbdd8 == 0) {
        if (SongPockets_PlaceIsDimmed(self, self->touch_place)) {
            MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_IDLE_BY_TOUCH);
            Popup_SetTimer(&self->popup, POPUP_FRAMES);
            return;
        }
        MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_OPEN_TOUCHED);
        SongPockets_RunSubState(self);
        return;
    }
    if (SongPockets_PlaceIsDimmed(self, self->touch_place) == 0 && Popup_IsUp(&self->popup)) {
        if (self->open_delay != 0) {
            self->open_delay--;
        } else {
            SongPockets_OpenChoice(self, self->touch_place, 1);
            MenuScene_SetSubState(scene_of(self), SONG_POCKETS_SUB_WAIT_PEN_UP);
        }
        return;
    }
    Popup_ShowQueued(&self->popup);
}
CLEAN_AS(func_ov109_0229d2d0, SongPockets_HoldTouchOnPlace)

/* func_ov109_0229d368 (sub state 0): the touch is in use and the cursor sprite hidden. A
 * button puts the cursor sprite back at the cursor (sub state 5). A touch on a grid place that
 * holds an item (looked for 0x10 below the touch) touches it; else a touch on the panel's
 * button 9 presses it. */
void SongPockets_IdleByTouch(SongPockets *self)
{
    if (MenuScene_TakeButtons(scene_of(self), 1)) {
        SongPockets_EndActionAtCursor(self);
        return;
    }
    if (!pen_pressed()) {
        return;
    }
    int place = SongPockets_GridPlaceAtTouch(self, data_021f6c58, data_021f6c54 + GRID_OFFSET_Y, 1);
    if (place != SONG_POCKETS_NO_PLACE) {
        SongPockets_TouchPlace(self, place);
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, PANEL_BUTTON_CLOSE)) {
        SongPockets_PressPanelButton9(self);
    }
}
CLEAN_AS(func_ov109_0229d368, SongPockets_IdleByTouch)

/* func_ov109_0229d3e8: a step of the wallet display's loads (its answer unused) and the
 * panel's text colours. */
void SongPockets_LoadGraphics(SongPockets *self)
{
    PocketsWallet_LoadObjFiles(&self->wallet);
    ButtonPanel_LoadTextColors(&self->panel);
}
CLEAN_AS(func_ov109_0229d3e8, SongPockets_LoadGraphics)

/* func_ov109_0229d40c: the wallet's display set up with 0. */
void SongPockets_PrepareWallet(SongPockets *self)
{
    PocketsWallet_SetUp(&self->wallet, 0);
}
CLEAN_AS(func_ov109_0229d40c, SongPockets_PrepareWallet)

/* func_ov109_0229d420: layer 6 at priority 2, with its plain background settings. */
void SongPockets_SetUpLayer6(void)
{
    DisplayLayer_SetPriority(SONG_POCKETS_LAYER, 2);
    DisplayLayer_SetBgControl(SONG_POCKETS_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov109_0229d420, SongPockets_SetUpLayer6)

/* func_ov109_0229d440: the end of a frame: the choice and the wallet's display updated, and
 * the popup placed when its update asks for it. */
void SongPockets_EndFrame(SongPockets *self)
{
    PagedChoice_Update(choice_of(self));
    PocketsWallet_Update(&self->wallet);
    if (Popup_Update(&self->popup)) {
        SongPockets_PlacePopup(self);
    }
}
CLEAN_AS(func_ov109_0229d440, SongPockets_EndFrame)

/* func_ov109_0229d478: the start of a frame: the load task ended, the three objects of
 * ov094's updated and the panel's texts closed. */
void SongPockets_BeginFrame(SongPockets *self)
{
    SongPockets_EndLayerTask(self);
    PocketsWallet_BeginFrame(&self->wallet);
    PocketsGrid_BeginFrame(&self->grid);
    PocketsLetters_BeginFrame(&self->letters);
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov109_0229d478, SongPockets_BeginFrame)

/* func_ov109_0229d4b4 */
void SongPockets_EndInteractiveFrame(SongPockets *self)
{
    SongPockets_EndFrame(self);
}
CLEAN_AS(func_ov109_0229d4b4, SongPockets_EndInteractiveFrame)

/* func_ov109_0229d4bc: the start of a frame, then the cursor sprite's update through its class
 * (vtable slot 3). */
void SongPockets_BeginInteractiveFrame(SongPockets *self)
{
    SongPockets_BeginFrame(self);
    update_cursor_sprite(self);
}
CLEAN_AS(func_ov109_0229d4bc, SongPockets_BeginInteractiveFrame)

/* func_ov109_0229d4d8: the members' teardown before the scene closes. */
void SongPockets_Teardown(SongPockets *self)
{
    SongPockets_EndLayerTask(self);
    PocketsWallet_Teardown(&self->wallet);
    PocketsGrid_Teardown(&self->grid);
    PagedChoice_Dismiss(choice_of(self));
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov109_0229d4d8, SongPockets_Teardown)

/* func_ov109_0229d514: the scene's setup: no flags, the three objects of ov094's set up, no
 * popup place, the glide stopped, nothing held, the cursor at place 0, the choice on layer 3,
 * no delay. */
void SongPockets_Setup(SongPockets *self)
{
    self->flags = 0;
    PocketsGrid_Init(&self->grid, 2);
    PocketsLetters_Init(&self->letters, 2);
    PocketsWallet_Init(&self->wallet, 6);
    self->popup_place = SONG_POCKETS_NO_PLACE;
    Glide_Stop(&self->glide);
    self->held_kind = SONG_POCKETS_HELD_NONE;
    self->cursor = SONG_POCKETS_GRID_FIRST;
    PagedChoice_Init(choice_of(self), 3, 1, NULL);
    self->open_delay = 0;
}
CLEAN_AS(func_ov109_0229d514, SongPockets_Setup)

/* func_ov109_0229d590 (state 4): the scene wipes out. When done, layer 6 hidden, the delete
 * phase set and nothing drawn; else the layer scrolls with the wipe. The objects' offset
 * follows the wipe. */
void SongPockets_WipeOut(SongPockets *self)
{
    if (MenuScene_StepWipe(scene_of(self), 0)) {
        DisplayLayer_HideAndResetScroll(SONG_POCKETS_LAYER);
        MenuScene_SetPhase(scene_of(self), SONG_POCKETS_PHASE_DELETE);
        SongPockets_ClearFlags(self, SONG_POCKETS_FLAG_DRAWN);
        SongPockets_ClearFlags(self, SONG_POCKETS_FLAG_OBJECTS_DRAWN);
    } else {
        MenuScene_ScrollWipe(scene_of(self), SONG_POCKETS_LAYER, 0, WIPE_SCROLL_Y);
    }
    self->wipe_y = MenuScene_WipeOffsetY(scene_of(self));
}
CLEAN_AS(func_ov109_0229d590, SongPockets_WipeOut)

/* func_ov109_0229d5e0 (state 3): the popup and the cursor sprite hidden, the dispatch told
 * what comes next (mode 0x40's screen, or the close when the menu was asked to close, with
 * sound), and the scene starts to wipe out (state 4). */
void SongPockets_StartWipeOut(SongPockets *self)
{
    Popup_Hide(&self->popup, 1);
    SongPockets_HideCursorSprite(self);
    MenuDispatch *parent = parent_of(self);
    if (SongPockets_TestFlags(self, SONG_POCKETS_FLAG_MENU_CLOSE)) {
        MenuDispatch_SetMode(parent, MENU_DISPATCH_MODE_CLOSE, 1);
    } else {
        MenuDispatch_SetMode(parent, NEXT_MODE, 1);
    }
    MenuScene_StartWipeOnWindow2(scene_of(self), WIPE_LAYERS, 0, 0, WIPE_MARGIN);
    MenuScene_ScrollWipe(scene_of(self), SONG_POCKETS_LAYER, 0, WIPE_SCROLL_Y);
    MenuScene_SetState(scene_of(self), SONG_POCKETS_STATE_WIPE_OUT);
    self->wipe_y = MenuScene_WipeOffsetY(scene_of(self));
}
CLEAN_AS(func_ov109_0229d5e0, SongPockets_StartWipeOut)

/* func_ov109_0229d660 (state 2): the scene wipes in; when done, the interactive phase and the
 * action ends (SongPockets_EndAction picks the first sub state). The objects' offset follows
 * the wipe. */
void SongPockets_WipeIn(SongPockets *self)
{
    if (MenuScene_StepWipeBack(scene_of(self), 0)) {
        MenuScene_SetPhase(scene_of(self), SONG_POCKETS_PHASE_INTERACTIVE);
        SongPockets_EndAction(self);
    }
    MenuScene_ScrollWipe(scene_of(self), SONG_POCKETS_LAYER, 0, WIPE_SCROLL_Y);
    self->wipe_y = MenuScene_WipeOffsetY(scene_of(self));
}
CLEAN_AS(func_ov109_0229d660, SongPockets_WipeIn)

/* func_ov109_0229d6a0 (state 1): the graphics loaded, the panel in layout 5 with message 0x65,
 * the pockets put in the grid with the slots that are not songs dimmed, the letters loaded and
 * all dimmed, layer 6 shown and wiping in (state 2); the scene and its objects drawn. */
void SongPockets_StartWipeIn(SongPockets *self)
{
    SongPockets_LoadGraphics(self);
    ButtonPanel_SetLayout5(&self->panel, PANEL_MESSAGE);
    PocketsGrid_LoadPockets(&self->grid);
    SongPockets_DimNonSongs(self);
    PocketsLetters_LoadPockets(&self->letters);
    PocketsLetters_DimByState(&self->letters, LETTERS_DIMMED);
    MenuScene_StartWipeCoveredOnWindow2(scene_of(self), WIPE_LAYERS, 0, 0, WIPE_MARGIN);
    DisplayLayer_Show(SONG_POCKETS_LAYER);
    MenuScene_ScrollWipe(scene_of(self), SONG_POCKETS_LAYER, 0, WIPE_SCROLL_Y);
    MenuScene_SetState(scene_of(self), SONG_POCKETS_STATE_WIPE_IN);
    SongPockets_SetFlags(self, SONG_POCKETS_FLAG_DRAWN);
    SongPockets_SetFlags(self, SONG_POCKETS_FLAG_OBJECTS_DRAWN);
    self->wipe_y = MenuScene_WipeOffsetY(scene_of(self));
}
CLEAN_AS(func_ov109_0229d6a0, SongPockets_StartWipeIn)

/* func_ov109_0229d730 (state 0): layer 6 set up and the wallet's display prepared, then
 * state 1. */
void SongPockets_StartSetup(SongPockets *self)
{
    SongPockets_SetUpLayer6();
    SongPockets_PrepareWallet(self);
    MenuScene_SetState(scene_of(self), SONG_POCKETS_STATE_START_WIPE_IN);
}
CLEAN_AS(func_ov109_0229d730, SongPockets_StartSetup)

/* func_ov109_0229d74c (vtable slot 0x5c, phase 5): the scene asks to be deleted. */
int SongPockets_RequestDelete(SongPockets *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov109_0229d74c, SongPockets_RequestDelete)

/* func_ov109_0229d75c (vtable slot 0x58, phase 4): nothing. */
int SongPockets_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov109_0229d75c, SongPockets_Phase4Idle)

/* func_ov109_0229d760 (vtable slot 0x54, phase 3): nothing. */
int SongPockets_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov109_0229d760, SongPockets_Phase3Idle)

/* func_ov109_0229d764 (vtable slot 0x50, phase 2): a frame of the scene in use. The menu's
 * close delay counted; when the menu is asked to close, in sub states 0, 1 and 5 the panel's
 * button 9 is pressed and the scene closes without a song, remembering the menu's close.
 * Then the frame's start, its sub state and its end. */
int SongPockets_RunInteractive(SongPockets *self)
{
    StateFlags_CountMenuCloseDelay();
    if (StateFlags_MenuCloseAsked()) {
        u8 sub_state = self->base.sub_state;
        if (sub_state == SONG_POCKETS_SUB_IDLE_BY_TOUCH || sub_state == SONG_POCKETS_SUB_HOLD_TOUCH ||
            sub_state == SONG_POCKETS_SUB_IDLE_BY_KEYS) {
            SongPockets_PressPanelButton9(self);
            SongPockets_CloseWithoutSong(self);
            SongPockets_SetFlags(self, SONG_POCKETS_FLAG_MENU_CLOSE);
        }
    }
    SongPockets_BeginInteractiveFrame(self);
    SongPockets_RunSubState(self);
    SongPockets_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(func_ov109_0229d764, SongPockets_RunInteractive)

/* func_ov109_0229d7b4: the sub state run through the table of member functions (filled once
 * from its constants; SongPocketsSubState names them).
 * REQUIRES: the sub state is below 16; the game reads past the table for others. */
void SongPockets_RunSubState(SongPockets *self)
{
    static const MemberPointer *const sub_states[SONG_POCKETS_SUB_STATES] = {
        &data_ov109_0229db98, &data_ov109_0229db90, &data_ov109_0229db48, &data_ov109_0229db80,
        &data_ov109_0229db78, &data_ov109_0229db70, &data_ov109_0229db68, &data_ov109_0229db60,
        &data_ov109_0229db58, &data_ov109_0229db50, &data_ov109_0229db40, &data_ov109_0229db88,
        &data_ov109_0229db38, &data_ov109_0229db30, &data_ov109_0229db28, &data_ov109_0229dba0,
    };
    MemberTable_InitOnce(&data_ov109_0229dc44, data_ov109_0229dc70, sub_states, SONG_POCKETS_SUB_STATES);
    MemberPointer_CallVoid(&data_ov109_0229dc70[self->base.sub_state], self);
}
CLEAN_AS(func_ov109_0229d7b4, SongPockets_RunSubState)

/* func_ov109_0229d8e0 (vtable slot 0x4c, phase 1): a frame of the scene's states, between the
 * frame's start and end, through the table of member functions (filled once from its
 * constants, before the frame starts; SongPocketsState names them).
 * REQUIRES: the state is below 5; the game reads past the table for others. */
int SongPockets_RunState(SongPockets *self)
{
    static const MemberPointer *const states[SONG_POCKETS_STATES] = {
        &data_ov109_0229dba8, &data_ov109_0229dbc8, &data_ov109_0229dbc0, &data_ov109_0229dbb8, &data_ov109_0229dbb0,
    };
    MemberTable_InitOnce(&data_ov109_0229dc40, data_ov109_0229dc48, states, SONG_POCKETS_STATES);
    SongPockets_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov109_0229dc48[self->base.state], self);
    SongPockets_EndFrame(self);
    return 1;
}
CLEAN_AS(func_ov109_0229d8e0, SongPockets_RunState)

/* func_ov109_0229d980 (vtable slot 0x24): the scene's draw: the choice; while the scene is
 * drawn, the popup (through its class, slot 2), the cursor sprite (with the keys in use) and
 * the held item; with SONG_POCKETS_FLAG_OBJECTS_DRAWN the panel at the wipe's offset and the
 * three objects of ov094's 0x10 above it. Answers 1. */
int SongPockets_Draw(SongPockets *self)
{
    PagedChoice_Draw(choice_of(self));
    if (SongPockets_TestFlags(self, SONG_POCKETS_FLAG_DRAWN) == 0) {
        return 1;
    }
    draw_member(&self->popup);
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    SongPockets_DrawHeld(self);
    if (SongPockets_TestFlags(self, SONG_POCKETS_FLAG_OBJECTS_DRAWN)) {
        ButtonPanel_Draw(&self->panel, self->wipe_y);
        int y = self->wipe_y - OBJECTS_OFFSET_Y;
        PocketsGrid_DrawPockets(&self->grid, 0, y);
        PocketsLetters_DrawPockets(&self->letters, 0, y);
        PocketsWallet_Draw(&self->wallet, y);
    }
    return 1;
}
CLEAN_AS(func_ov109_0229d980, SongPockets_Draw)

/* func_ov109_0229da24 (vtable slot 0x0c): the scene closes: the dispatch told and the members
 * torn down. Answers 1. */
int SongPockets_Close(SongPockets *self)
{
    MenuDispatch_ChildClosed(parent_of(self));
    SongPockets_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov109_0229da24, SongPockets_Close)

/* func_ov109_0229da40 (vtable slot 0x00): the scene starts: its setup, state 0 and the wait
 * phase. Answers 1. */
int SongPockets_Start(SongPockets *self)
{
    SongPockets_Setup(self);
    MenuScene_SetState(scene_of(self), SONG_POCKETS_STATE_START_SETUP);
    MenuScene_SetPhase(scene_of(self), SONG_POCKETS_PHASE_WAIT);
    return 1;
}
CLEAN_AS(func_ov109_0229da40, SongPockets_Start)

/* func_ov109_0229da60: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base, the scene's vtable and its members constructed. */
SongPockets *SongPockets_New(void)
{
    SongPockets *self = MenuScene_Alloc(sizeof(SongPockets));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov109_0229dbd8;
    LayerTask_ConstructPair(&self->tasks);
    PocketsGrid_Construct(&self->grid);
    PocketsLetters_Construct(&self->letters);
    PocketsWallet_Construct(&self->wallet);
    Popup_Construct(&self->popup);
    Glide_Construct(&self->glide);
    Glider0_Construct(&self->cursor_sprite);
    PagedChoice_Construct(choice_of(self));
    ErrorMessage_Construct(&self->error);
    ButtonPanel_Construct(&self->panel);
    return self;
}
CLEAN_AS(func_ov109_0229da60, SongPockets_New)
