/* The box scene of overlay 110 (public_box.h): its sub states (the interactive frame), its states
 * (the wipes in and out), its frames, its draw and its constructor. */
#include "public_box.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/group_params.h"
#include "main/item_code.h"
#include "main/pockets.h"
#include "main/state_flags.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"
#include "ov094/pockets_common.h"

static_assert(offsetof(PublicBox, entries) + offsetof(ChoiceEntries, values) == 0x2731, "choice values");

/* The class's vtable. */
extern const u8 data_ov110_0229ecb8[];

/* The labels' constructor and destructor, handed to __cxa_vec_ctor (so the game's symbols). */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void *func_02070c08(void *label);
extern int **func_02070be8(int **label);

/* The town's lists A and B (main/town_item_lists.h). */
extern u16 data_021f3a68[PUBLIC_BOX_SLOTS];
extern u16 data_021f3a86[PUBLIC_BOX_SLOTS];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The heap the layers' files are read with. */
extern Heap *data_021fbe94;

/* The background's files: its screen and characters, then a palette and characters by the
 * mode (PublicBox_LoadBoxLayer). */
extern const char data_ov110_0229ed18[]; /* "menu/inventory/b_itm_bg_tra2.bsc" */
extern const char data_ov110_0229ed3c[]; /* "menu/inventory/b_itm_sell.bch" */
extern const char data_ov110_0229ed5c[]; /* "menu/inventory/ten6.bpl" */
extern const char data_ov110_0229ed74[]; /* "menu/inventory/tanu.bch" */
extern const char data_ov110_0229ed8c[]; /* "menu/inventory/ten7.bpl" */
extern const char data_ov110_0229eda4[]; /* "menu/inventory/kinu.bch" */
extern const char data_ov110_0229edbc[]; /* "menu/inventory/ten8.bpl" */
extern const char data_ov110_0229edd4[]; /* "menu/inventory/lost.bch" */
extern const char data_ov110_0229edec[]; /* "menu/inventory/ten9.bpl" */
extern const char data_ov110_0229ee04[]; /* "menu/inventory/garb.bch" */

/* The pen (autoload_2/input.c): down, and gone down this frame. */
extern u8 data_021fbdd8;
extern u8 data_021fbddc;

/* The touch (main's bytes, as ov099/pockets_view.c reads them). */
extern u8 data_021f6c58, data_021f6c54;

/* The pad (autoload_2/input.h) and the buttons read in `pressed`. */
extern PadState data_021fbe40;
#define PUBLIC_BOX_PAD_A 0x0001
#define PUBLIC_BOX_PAD_B 0x0002
#define PUBLIC_BOX_PAD_START 0x0008
#define PUBLIC_BOX_PAD_Y 0x0800

/* The tables of member functions (member_pointer.h): the guards, the tables and their
 * constants (the symbol table also names the sub states' table's later part, at 0x0229eee0). */
extern u32 data_ov110_0229ee20; /* the states' guard */
extern u32 data_ov110_0229ee24; /* the sub states' guard */
extern MemberPointer data_ov110_0229ee28[PUBLIC_BOX_STATES];
extern MemberPointer data_ov110_0229ee60[PUBLIC_BOX_SUB_STATES];
extern const MemberPointer data_ov110_0229ebc0, data_ov110_0229ebc8, data_ov110_0229ebd8, data_ov110_0229ebe0,
    data_ov110_0229ebe8, data_ov110_0229ebf0, data_ov110_0229ebf8, data_ov110_0229ec00, data_ov110_0229ec08,
    data_ov110_0229ec10, data_ov110_0229ec18, data_ov110_0229ec20, data_ov110_0229ec28, data_ov110_0229ec30,
    data_ov110_0229ec38, data_ov110_0229ec40, data_ov110_0229ec48, data_ov110_0229ec50, data_ov110_0229ec58,
    data_ov110_0229ec60, data_ov110_0229ec68, data_ov110_0229ec70, data_ov110_0229ec78, data_ov110_0229ec80,
    data_ov110_0229ec88, data_ov110_0229ec90, data_ov110_0229ec98, data_ov110_0229eca0, data_ov110_0229eca8;

/* The two layers: the pockets' (with the wallet) and the box's background. */
#define PUBLIC_BOX_POCKETS_LAYER 6
#define PUBLIC_BOX_BOX_LAYER 4

/* The choice's text layer. */
#define PUBLIC_BOX_TEXT_LAYER 3

/* The wipes' layer masks (MenuScene_StartWipe*OnWindow2): the pockets', the box's. */
#define PUBLIC_BOX_WIPE_POCKETS 8
#define PUBLIC_BOX_WIPE_BOX 2

/* The box's extent in the wipe (MenuScene_SetWipeExtent) and the wipes' margin. */
#define PUBLIC_BOX_WIPE_EXTENT 0x80
#define PUBLIC_BOX_WIPE_MARGIN 0x30

/* The frames the popup stays up once the pen leaves a place. */
#define PUBLIC_BOX_POPUP_FRAMES 0x3c

/* The end place's area for the touch. */
#define PUBLIC_BOX_DONE_LEFT 0xc8
#define PUBLIC_BOX_DONE_RIGHT 0xf8
#define PUBLIC_BOX_DONE_TOP 0x60
#define PUBLIC_BOX_DONE_BOTTOM 0x70

/* A touch let go at this height or lower is over the pockets (PublicBox_DropHeldAtTouch). */
#define PUBLIC_BOX_HELD_HOTSPOT 8

static MenuScene *pbox_scene(PublicBox *self)
{
    return &self->base;
}

static PagedChoice *pbox_choice(PublicBox *self)
{
    return (PagedChoice *) (void *) self->choice;
}

static CellLayerSprite *pbox_cursor_cells(PublicBox *self)
{
    /* The cursor sprite's base is main's cell layer sprite (glide.h). */
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

/* The pen went down this frame. */
static int pbox_pen_pressed(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* The value kept with choice row `row` (ChoiceEntries.values), read as the ROM does at
 * 0x2731 + row. */
static u8 pbox_entry_value(PublicBox *self, int row)
{
    const u8 *bytes = (const u8 *) self;
    return bytes[offsetof(PublicBox, entries) + offsetof(ChoiceEntries, values) + (size_t) row];
}

/* Whether `place` is one of the grid's slots: a pocket's, else the box's. */
static int pbox_is_slot(PublicBox *self, int place)
{
    return PublicBox_IsPocketPlace(self, (unsigned int) place) || PublicBox_IsBoxPlace(self, (unsigned int) place);
}

/* A member drawn or updated through its class (vtable slot `slot`). */
static void pbox_call_member(void *object, int slot)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[slot])(object);
}

/* The scene ends at once as the menu closes: the held item (if any) put back, the cursor sprite
 * and the popup hidden. */
static void pbox_close_holding(PublicBox *self)
{
    PublicBox_PutHeldAt(self, self->held_place);
    PublicBox_HideCursorSprite(self);
    Popup_Hide(&self->popup, 0);
    PublicBox_Finish(self, 0);
}

/* func_ov110_0229d8b0 (sub state 0x15): the ended scene's delay counted down; then state 4 (the
 * wipe out, set directly) in the states phase, the popup and the cursor sprite hidden. */
void PublicBox_WaitClosed(PublicBox *self)
{
    if (self->close_delay != 0) {
        self->close_delay--;
        return;
    }
    self->base.state = PUBLIC_BOX_STATE_START_WIPE_OUT;
    MenuScene_SetPhase(pbox_scene(self), PUBLIC_BOX_PHASE_STATES);
    Popup_Hide(&self->popup, 0);
    PublicBox_HideCursorSprite(self);
}
CLEAN_AS(func_ov110_0229d8b0, PublicBox_WaitClosed)

/* func_ov110_0229d8f4 (sub state 0x14): once the error message is done, back to the kept sub
 * state with the cursor sprite in its window. */
void PublicBox_WaitError(PublicBox *self)
{
    if (ErrorMessage_Update(&self->error, 1)) {
        MenuScene_SetSubState(pbox_scene(self), self->return_state);
        CellLayerSprite_SetWindow(pbox_cursor_cells(self));
    }
}
CLEAN_AS(func_ov110_0229d8f4, PublicBox_WaitError)

/* func_ov110_0229d928 (sub state 0x13): the picked row's action once the choice is idle. */
void PublicBox_RunActionWhenIdle(PublicBox *self)
{
    if (PagedChoice_IsIdle(pbox_choice(self))) {
        PublicBox_RunAction(self);
    }
}
CLEAN_AS(func_ov110_0229d928, PublicBox_RunActionWhenIdle)

/* func_ov110_0229d948 (sub state 0x12): after the choice's countdown, it is asked to close, the
 * cursor sprite put back at the cursor unless hidden, and sub state 0x13. */
void PublicBox_CloseChoice(PublicBox *self)
{
    if (PagedChoice_CountDown(pbox_choice(self))) {
        PagedChoice_RequestClose(pbox_choice(self), 0);
        if (CellLayerSprite_AnimNumber(pbox_cursor_cells(self)) != 0) {
            PublicBox_PlaceCursorSprite(self);
        }
        MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_CHOICE_RUN);
    }
}
CLEAN_AS(func_ov110_0229d948, PublicBox_CloseChoice)

/* func_ov110_0229d98c (sub state 0x11): once the choice is shown, by keys (state flag 2: the
 * cursor sprite at its first row, sub state 6) or by touch (sub state 2). */
void PublicBox_WaitChoiceShown(PublicBox *self)
{
    if (PagedChoice_IsShown(pbox_choice(self))) {
        if (StateFlags_Test2()) {
            PublicBox_PointAtFirstRow(self);
            MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_CHOICE_BY_KEYS);
        } else {
            MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_TOUCH_CHOICE);
        }
    }
}
CLEAN_AS(func_ov110_0229d98c, PublicBox_WaitChoiceShown)

/* func_ov110_0229d9c8 (sub state 0x10): a step of the held item's glide; at its end the item is
 * put at the place it glided to, the action ends and sound 0x0e plays. */
void PublicBox_StepHeldGlide(PublicBox *self)
{
    if (Glide_Step(&self->glide)) {
        PublicBox_PutHeldAt(self, self->held_place);
        PublicBox_EndAction(self);
        PocketsSound_Play0e();
    } else {
        PublicBox_FollowGlide(self);
    }
}
CLEAN_AS(func_ov110_0229d9c8, PublicBox_StepHeldGlide)

/* func_ov110_0229da00 (sub state 0x0f): once the cursor sprite's animation is done, back to the
 * kept sub state. Once its turn has settled, the held item hidden for the swap is shown again
 * (sound 0x0d) and follows the sprite. */
void PublicBox_FinishSwap(PublicBox *self)
{
    if (CellLayerSprite_IsDone(pbox_cursor_cells(self))) {
        MenuScene_SetSubState(pbox_scene(self), self->return_state);
    }
    if (Glider_IsTurnSettled(&self->cursor_sprite)) {
        if (PublicBox_TestFlags(self, PUBLIC_BOX_FLAG_HELD_HIDDEN)) {
            PublicBox_ClearFlags(self, PUBLIC_BOX_FLAG_HELD_HIDDEN);
            PocketsSound_Play0d();
        }
        PublicBox_FollowCursorSprite(self);
    }
}
CLEAN_AS(func_ov110_0229da00, PublicBox_FinishSwap)

/* func_ov110_0229da50 (sub state 0x0e): while Glider_IsTurnAtFrame2 answers 0, the held item is
 * swapped with the target's (and hidden), sub state 0x0f and the popup updated; else sub state 4. */
void PublicBox_Swap(PublicBox *self)
{
    if (Glider_IsTurnAtFrame2(&self->cursor_sprite) == 0) {
        PublicBox_SwapHeldWith(self, self->target);
        PublicBox_SetFlags(self, PUBLIC_BOX_FLAG_HELD_HIDDEN);
        MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_SWAP_END);
        PublicBox_UpdatePopup(self);
    } else {
        MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_BROWSE);
    }
}
CLEAN_AS(func_ov110_0229da50, PublicBox_Swap)

/* func_ov110_0229da98 (sub state 0x0d): while Glider_IsTurnSettled answers 0, the held item is
 * put down: on the cursor's place at once (the popup updated, sub state 4, sound 0x0e), else it
 * glides to the target in 4 steps. Once settled, it follows the cursor sprite. */
void PublicBox_PutDown(PublicBox *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite) == 0) {
        u8 target = self->target;
        if (self->cursor == target) {
            PublicBox_PutHeldAtPlace(self, target);
            PublicBox_UpdatePopup(self);
            MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_BROWSE);
            PocketsSound_Play0e();
        } else {
            PublicBox_GlideHeldTo(self, target, 4);
        }
    } else {
        PublicBox_FollowCursorSprite(self);
    }
}
CLEAN_AS(func_ov110_0229da98, PublicBox_PutDown)

/* func_ov110_0229daec (sub state 0x0c): once the cursor sprite's animation is done, back to the
 * kept sub state; the held item follows the sprite. */
void PublicBox_FinishPickUp(PublicBox *self)
{
    if (CellLayerSprite_IsDone(pbox_cursor_cells(self))) {
        MenuScene_SetSubState(pbox_scene(self), self->return_state);
    }
    PublicBox_FollowCursorSprite(self);
}
CLEAN_AS(func_ov110_0229daec, PublicBox_FinishPickUp)

/* func_ov110_0229db18 (sub state 0x0b): once the cursor sprite's turn has settled, the cursor's
 * item is picked up, sub state 0x0c. */
void PublicBox_PickUpAtCursor(PublicBox *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite) == 0) {
        return;
    }
    PublicBox_PickUpWithCursor(self, (char) self->cursor);
    MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_PICK_UP_END);
}
CLEAN_AS(func_ov110_0229db18, PublicBox_PickUpAtCursor)

/* func_ov110_0229db48 (sub state 0x0a): once the cursor sprite's animation is done, the first of
 * its set shown, sub state 4. */
void PublicBox_FinishButtonPress(PublicBox *self)
{
    if (CellLayerSprite_IsDone(pbox_cursor_cells(self))) {
        PublicBox_ShowCursorFirstOfSet(self);
        MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_BROWSE);
    }
}
CLEAN_AS(func_ov110_0229db48, PublicBox_FinishButtonPress)

/* func_ov110_0229db70 (sub state 9): once the cursor sprite's animation is done, the end place
 * ends the scene (after its delay); any other place goes on to sub state 0x0a. */
void PublicBox_PressButton(PublicBox *self)
{
    if (CellLayerSprite_IsDone(pbox_cursor_cells(self))) {
        if (self->cursor == PUBLIC_BOX_DONE) {
            PublicBox_Finish(self, 1);
        } else {
            PublicBox_BeginButtonEnd(self);
        }
    }
}
CLEAN_AS(func_ov110_0229db70, PublicBox_PressButton)

/* Obj_ov110_0229ecb8::func_ov110_0229dba4 (sub state 8): once the cursor sprite has stopped,
 * back to the kept sub state (lifting the cursor's place when that is 4 or 5) and that sub state
 * run at once. The held item follows the sprite. */
void PublicBox_WaitCursorSprite(PublicBox *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(pbox_scene(self), self->return_state);
        if (self->return_state == PUBLIC_BOX_SUB_BROWSE || self->return_state == PUBLIC_BOX_SUB_HOLD) {
            PublicBox_SelectPlace(self, self->cursor);
        }
        PublicBox_RunSubState(self);
    }
    PublicBox_FollowCursorSprite(self);
}
CLEAN_AS(_ZN18Obj_ov110_0229ecb819func_ov110_0229dba4Ev, PublicBox_WaitCursorSprite)

/* func_ov110_0229dbf4 (sub state 7): once the cursor sprite's animation is done, the row it
 * points at picked (with its sound), its value kept as the action; sub state 0x12. */
void PublicBox_PickChoiceRow(PublicBox *self)
{
    if (CellLayerSprite_IsDone(pbox_cursor_cells(self))) {
        PagedChoice_PickRowWithSound(pbox_choice(self), self->choice_row, 1);
        self->action = pbox_entry_value(self, self->choice_row);
        MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_CHOICE_CLOSE);
    }
}
CLEAN_AS(func_ov110_0229dbf4, PublicBox_PickChoiceRow)

/* func_ov110_0229dc40 (sub state 6): the choice by keys. A touch or the menu closing cancels it;
 * the d-pad moves its row (the cursor sprite gliding there); A picks the row (sub state 7), B
 * points at the last row. */
void PublicBox_ChooseByKeys(PublicBox *self)
{
    if (MenuScene_TakeTouch(pbox_scene(self)) != 0 || PublicBox_CloseAsked(self) != 0) {
        PublicBox_CancelChoice(self);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(pbox_scene(self));
    if (PagedChoice_MoveCursor(pbox_choice(self), keys, &self->choice_row, 0)) {
        PublicBox_GlideToRow(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & PUBLIC_BOX_PAD_A) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_CHOICE_PICK);
    } else if (pressed & PUBLIC_BOX_PAD_B) {
        PublicBox_PointAtLastRow(self);
    }
}
CLEAN_AS(func_ov110_0229dc40, PublicBox_ChooseByKeys)

/* func_ov110_0229dcc0 (sub state 5): an item held by keys. The menu closing puts it back and ends
 * the scene. The d-pad moves the cursor (with a wrap in its row). A puts it down on a free slot
 * place or swaps it with the item there (not on a locked one); B puts it back where it came
 * from. Else it follows the cursor sprite and a queued popup is shown. */
void PublicBox_MoveHeldByKeys(PublicBox *self)
{
    if (PublicBox_CloseAsked(self) != 0) {
        pbox_close_holding(self);
        return;
    }
    if (PublicBox_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(pbox_scene(self)), 1) != 0) {
        PublicBox_UpdatePopup(self);
        PublicBox_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & PUBLIC_BOX_PAD_A) {
        if (!pbox_is_slot(self, self->cursor)) {
            return;
        }
        if (PublicBox_PlaceIsLocked(self, self->cursor) != 0) {
            return;
        }
        if (PublicBox_PlaceIsEmpty(self, self->cursor) != 0) {
            PublicBox_StartPutDown(self, self->cursor);
        } else {
            PublicBox_StartSwap(self, self->cursor);
        }
        return;
    }
    if (pressed & PUBLIC_BOX_PAD_B) {
        PublicBox_StartPutDown(self, self->held_place);
        return;
    }
    PublicBox_FollowCursorSprite(self);
    Popup_ShowQueued(&self->popup);
}
CLEAN_AS(func_ov110_0229dcc0, PublicBox_MoveHeldByKeys)

/* func_ov110_0229ddb4 (sub state 4): the cursor by keys. A touch hands over to it (sub state 0).
 * The d-pad moves the cursor. On a place not locked: A picks up a slot's item or presses the end
 * place; Y sends a slot's item across, from the pockets to the box's first empty slot or from the
 * box to a free pocket slot. START or B end the scene. Else a queued popup is shown. */
void PublicBox_BrowseByKeys(PublicBox *self)
{
    if (MenuScene_TakeTouch(pbox_scene(self)) != 0) {
        PublicBox_EndActionHidden(self);
        Popup_Hide(&self->popup, 1);
        return;
    }
    if (PublicBox_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(pbox_scene(self)), 0) != 0) {
        PublicBox_UpdatePopup(self);
        PublicBox_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    if (PublicBox_PlaceIsLocked(self, self->cursor) == 0) {
        u16 pressed = data_021fbe40.pressed;
        if (pressed & PUBLIC_BOX_PAD_A) {
            if (pbox_is_slot(self, self->cursor)) {
                if (PublicBox_PlaceIsEmpty(self, self->cursor) == 0) {
                    PublicBox_StartPickUp(self);
                }
            } else if (PublicBox_IsButtonPlace(self, self->cursor) != 0) {
                PublicBox_BeginButtonPress(self);
            }
            return;
        }
        if (pressed & PUBLIC_BOX_PAD_Y) {
            if (pbox_is_slot(self, self->cursor) && PublicBox_PlaceIsEmpty(self, self->cursor) == 0) {
                int to;
                if (PublicBox_IsPocketPlace(self, self->cursor) != 0) {
                    to = PublicBox_FirstEmptyBoxPlace(self);
                } else {
                    to = PublicBox_FreePocketPlace(self);
                }
                if (to != PUBLIC_BOX_NO_PLACE) {
                    PublicBox_HoldAndGlide(self, self->cursor, to);
                    Popup_Hide(&self->popup, 1);
                }
            }
            return;
        }
    }
    u16 pressed = data_021fbe40.pressed;
    if ((pressed & PUBLIC_BOX_PAD_START) || (pressed & PUBLIC_BOX_PAD_B)) {
        PublicBox_HideCursorSprite(self);
        Popup_Hide(&self->popup, 0);
        PublicBox_Finish(self, 1);
        return;
    }
    Popup_ShowQueued(&self->popup);
}
CLEAN_AS(func_ov110_0229ddb4, PublicBox_BrowseByKeys)

/* func_ov110_0229df2c (sub state 3): an item dragged by the touch. The menu closing puts it back
 * and ends the scene. The item follows the touch and the place under its hot spot (8 pixels in) is
 * marked while the pen is down; when the box started empty, a place across the pockets and the
 * box from where the item came that holds an item counts as none. Let go on a place: not locked,
 * the item is put down there (sound 0x0e) and the action ends; else, or let go on no place, it
 * glides back or across (PublicBox_DropHeldAtTouch). */
void PublicBox_DragHeld(PublicBox *self)
{
    if (PublicBox_CloseAsked(self) != 0) {
        pbox_close_holding(self);
        return;
    }
    PublicBox_FollowTouch(self);
    PublicBox_ClearHighlights(self);
    int y = (int) ((u32) self->held_y + PUBLIC_BOX_HELD_HOTSPOT);
    int x = (int) ((u32) self->held_x + PUBLIC_BOX_HELD_HOTSPOT);
    int place = PublicBox_PlaceAtTouch(self, x, y, 0);

    if (PublicBox_TestFlags(self, PUBLIC_BOX_FLAG_STARTED_EMPTY) != 0) {
        int across = (PublicBox_IsBoxPlace(self, (unsigned int) place) && PublicBox_IsPocketPlace(self, self->held_place)) ||
                     (PublicBox_IsPocketPlace(self, (unsigned int) place) && PublicBox_IsBoxPlace(self, self->held_place));
        if (across && PublicBox_PlaceItem(self, place) != ITEM_CODE_NONE) {
            place = PUBLIC_BOX_NO_PLACE;
        }
    }

    if (place == PUBLIC_BOX_NO_PLACE) {
        if (data_021fbdd8 == 0) {
            PublicBox_DropHeldAtTouch(self, self->held_place, y);
        }
        return;
    }
    if (data_021fbdd8 != 0) {
        PublicBox_HighlightPlace(self, place);
        return;
    }
    if (PublicBox_PlaceIsLocked(self, place) != 0) {
        PublicBox_DropHeldAtTouch(self, self->held_place, y);
        return;
    }
    if (PublicBox_PutHeldAtPlace(self, place) != 0) {
        PocketsSound_Play0e();
        PublicBox_EndAction(self);
        return;
    }
    PublicBox_DropHeldAtTouch(self, self->held_place, y);
}
CLEAN_AS(func_ov110_0229df2c, PublicBox_DragHeld)

/* func_ov110_0229e05c (sub state 2): the choice by touch. The menu closing or a button cancels
 * it; the pen going down on a row (or below the last) picks it with its sound, its value kept as
 * the action; sub state 0x12. */
void PublicBox_WatchChoiceTouch(PublicBox *self)
{
    if (PublicBox_CloseAsked(self) != 0) {
        PublicBox_CancelChoice(self);
        return;
    }
    if (MenuScene_TakeButtons(pbox_scene(self), 1) != 0) {
        PublicBox_CancelChoice(self);
        return;
    }
    if (!pbox_pen_pressed()) {
        return;
    }
    int row = PagedChoice_RowAtOrLast(pbox_choice(self), data_021f6c58, data_021f6c54);
    if (row >= 0) {
        PagedChoice_PickRowWithSound(pbox_choice(self), row, 1);
        self->action = pbox_entry_value(self, row);
        MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_CHOICE_CLOSE);
    }
}
CLEAN_AS(func_ov110_0229e05c, PublicBox_WatchChoiceTouch)

/* func_ov110_0229e0f8 (sub state 1): a place is touched. Let go, back to sub state 0 with the
 * popup's timer at 60 frames. Held down on a place not locked, moving off it picks its item up
 * (PublicBox_PickUpWithTouch); else a queued popup is shown. */
void PublicBox_HoldTouchOnPlace(PublicBox *self)
{
    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_TOUCH_IDLE);
        Popup_SetTimer(&self->popup, PUBLIC_BOX_POPUP_FRAMES);
        return;
    }
    if (PublicBox_TestFlags(self, PUBLIC_BOX_FLAG_TOUCHED_FREE) != 0 && PublicBox_TouchMoved(self) != 0) {
        PublicBox_PickUpWithTouch(self, self->touch_place);
        return;
    }
    Popup_ShowQueued(&self->popup);
}
CLEAN_AS(func_ov110_0229e0f8, PublicBox_HoldTouchOnPlace)

/* func_ov110_0229e14c (sub state 0): the touch is in use and the cursor sprite hidden. A button
 * puts the cursor sprite back at the cursor (sub state 4). The pen going down touches the slot
 * under it when it holds an item, else ends the scene when on the end place. */
void PublicBox_IdleByTouch(PublicBox *self)
{
    if (MenuScene_TakeButtons(pbox_scene(self), 1) != 0) {
        PublicBox_EndActionAtCursor(self);
        return;
    }
    if (!pbox_pen_pressed()) {
        return;
    }
    int x = data_021f6c58;
    int y = data_021f6c54;
    int place = PublicBox_PlaceAtTouch(self, x, y, 1);
    if (place != PUBLIC_BOX_NO_PLACE) {
        PublicBox_TouchPlace(self, place);
        return;
    }
    if (x < PUBLIC_BOX_DONE_LEFT || x > PUBLIC_BOX_DONE_RIGHT || y < PUBLIC_BOX_DONE_TOP || y > PUBLIC_BOX_DONE_BOTTOM) {
        return;
    }
    PublicBox_Finish(self, 1);
}
CLEAN_AS(func_ov110_0229e14c, PublicBox_IdleByTouch)

/* func_ov110_0229e1cc: a step of the wallet display's setup; its answer. */
unsigned int PublicBox_LoadWalletFiles(PublicBox *self)
{
    return (unsigned int) PocketsWallet_LoadObjFiles(&self->wallet);
}
CLEAN_AS(func_ov110_0229e1cc, PublicBox_LoadWalletFiles)

/* func_ov110_0229e1dc: the box layer's screen and characters 0x1b9-0x238 loaded from their files,
 * then by the mode its palettes 3-5 and characters 0x208-0x238: Nook's (0x1d), the Able Sisters'
 * (0x1e), the lost and found's (0x1f) or the recycle bin's (0x20); none for other modes. Then the
 * end place's label, not lit. */
void PublicBox_LoadBoxLayer(PublicBox *self)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadScreenFromFile(data_ov110_0229ed18, heap, PUBLIC_BOX_BOX_LAYER);
    DisplayLayer_LoadCharsFromFile(data_ov110_0229ed3c, heap, PUBLIC_BOX_BOX_LAYER, 0x1b9, 0x1b9, 0x238);
    const char *palettes = NULL;
    const char *chars = NULL;
    switch (GroupParams_Mode()) {
        case PUBLIC_BOX_MODE_1D:
            palettes = data_ov110_0229ed5c;
            chars = data_ov110_0229ed74;
            break;
        case PUBLIC_BOX_MODE_1E:
            palettes = data_ov110_0229ed8c;
            chars = data_ov110_0229eda4;
            break;
        case PUBLIC_BOX_MODE_LOST:
            palettes = data_ov110_0229edbc;
            chars = data_ov110_0229edd4;
            break;
        case PUBLIC_BOX_MODE_RECYCLE:
            palettes = data_ov110_0229edec;
            chars = data_ov110_0229ee04;
            break;
    }
    if (palettes != NULL) {
        DisplayLayer_LoadPalettesFromFile(palettes, heap, PUBLIC_BOX_BOX_LAYER, 3, 3, 5);
    }
    if (chars != NULL) {
        DisplayLayer_LoadCharsFromFile(chars, heap, PUBLIC_BOX_BOX_LAYER, 0x208, 0x208, 0x238);
    }
    PublicBox_ShowDoneLabel(self, 0);
}
CLEAN_AS(func_ov110_0229e1dc, PublicBox_LoadBoxLayer)

/* func_ov110_0229e2b0: the wallet's display started with 0. */
void PublicBox_PrepareWallet(PublicBox *self)
{
    PocketsWallet_SetUp(&self->wallet, 0);
}
CLEAN_AS(func_ov110_0229e2b0, PublicBox_PrepareWallet)

/* func_ov110_0229e2c4: the pockets' layer at priority 2 and the box's at priority 1, both with
 * their plain background settings. */
void PublicBox_SetUpLayers(void)
{
    DisplayLayer_SetPriority(PUBLIC_BOX_POCKETS_LAYER, 2);
    DisplayLayer_SetBgControl(PUBLIC_BOX_POCKETS_LAYER, 0, 0, 0);
    DisplayLayer_SetPriority(PUBLIC_BOX_BOX_LAYER, 1);
    DisplayLayer_SetBgControl(PUBLIC_BOX_BOX_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov110_0229e2c4, PublicBox_SetUpLayers)

/* func_ov110_0229e2f8: the end of a frame: the choice and the wallet's display updated, and the
 * popup placed when its update asks for it. */
void PublicBox_EndFrame(PublicBox *self)
{
    PagedChoice_Update(pbox_choice(self));
    PocketsWallet_Update(&self->wallet);
    if (Popup_Update(&self->popup)) {
        PublicBox_PlacePopup(self);
    }
}
CLEAN_AS(func_ov110_0229e2f8, PublicBox_EndFrame)

/* func_ov110_0229e330: the start of a frame: the layer task ended, the three objects of ov094's
 * updated and the labels closed. */
void PublicBox_BeginFrame(PublicBox *self)
{
    PublicBox_EndLayerTask(self);
    PocketsWallet_BeginFrame(&self->wallet);
    PocketsGrid_BeginFrame(&self->grid);
    PocketsLetters_BeginFrame(&self->letters);
    PublicBox_CloseLabels(self);
}
CLEAN_AS(func_ov110_0229e330, PublicBox_BeginFrame)

/* func_ov110_0229e368 */
void PublicBox_EndInteractiveFrame(PublicBox *self)
{
    PublicBox_EndFrame(self);
}
CLEAN_AS(func_ov110_0229e368, PublicBox_EndInteractiveFrame)

/* func_ov110_0229e370: the start of a frame, then the cursor sprite's update through its class
 * (vtable slot 3). */
void PublicBox_BeginInteractiveFrame(PublicBox *self)
{
    PublicBox_BeginFrame(self);
    pbox_call_member(&self->cursor_sprite, 3);
}
CLEAN_AS(func_ov110_0229e370, PublicBox_BeginInteractiveFrame)

/* func_ov110_0229e38c: the members' teardown before the scene closes. */
void PublicBox_Teardown(PublicBox *self)
{
    PublicBox_EndLayerTask(self);
    PocketsWallet_Teardown(&self->wallet);
    PocketsGrid_Teardown(&self->grid);
    PagedChoice_Dismiss(pbox_choice(self));
    PublicBox_CloseLabels(self);
}
CLEAN_AS(func_ov110_0229e38c, PublicBox_Teardown)

/* func_ov110_0229e3c4: the scene's setup: no flags, the three objects of ov094's set up, no
 * popup place, the glide stopped, nothing held, the cursor on the first pocket, the choice on
 * layer 3, no label in use. The box by the mode: empty for 0x1d and 0x1e
 * (PUBLIC_BOX_FLAG_STARTED_EMPTY), list A for 0x1f, list B for 0x20 (left as it is for any
 * other); its copy kept as `box_start`, and the pockets saved (Pockets_Save). */
void PublicBox_Setup(PublicBox *self)
{
    self->flags = 0;
    PocketsGrid_Init(&self->grid, 1);
    PocketsLetters_Init(&self->letters, 2);
    PocketsWallet_Init(&self->wallet, PUBLIC_BOX_POCKETS_LAYER);
    self->popup_place = PUBLIC_BOX_NO_PLACE;
    Glide_Stop(&self->glide);
    self->held_kind = PUBLIC_BOX_HELD_NONE;
    self->cursor = PUBLIC_BOX_POCKETS_FIRST;
    PagedChoice_Init(pbox_choice(self), PUBLIC_BOX_TEXT_LAYER, 1, NULL);
    self->label_count = 0;
    switch (GroupParams_Mode()) {
        case PUBLIC_BOX_MODE_1D:
        case PUBLIC_BOX_MODE_1E:
            for (int i = 0; i < PUBLIC_BOX_SLOTS; i++) {
                self->box[i] = ITEM_CODE_NONE;
            }
            PublicBox_SetFlags(self, PUBLIC_BOX_FLAG_STARTED_EMPTY);
            break;
        case PUBLIC_BOX_MODE_LOST:
            MI_CpuCopy8(data_021f3a68, self->box, sizeof self->box);
            break;
        case PUBLIC_BOX_MODE_RECYCLE:
            MI_CpuCopy8(data_021f3a86, self->box, sizeof self->box);
            break;
    }
    MI_CpuCopy8(self->box, self->box_start, sizeof self->box);
    Pockets_Save();
}
CLEAN_AS(func_ov110_0229e3c4, PublicBox_Setup)

/* func_ov110_0229e4b0 (state 6): the pockets wipe out; when done, their layer hidden, the end
 * phase begins and the scene is no longer drawn. Else their layer follows the wipe. The wipe's y
 * kept for the pockets. */
void PublicBox_PocketsWipeOut(PublicBox *self)
{
    if (MenuScene_StepWipe(pbox_scene(self), 0)) {
        DisplayLayer_HideAndResetScroll(PUBLIC_BOX_POCKETS_LAYER);
        MenuScene_SetPhase(pbox_scene(self), PUBLIC_BOX_PHASE_END);
        PublicBox_ClearFlags(self, PUBLIC_BOX_FLAG_DRAWN);
        PublicBox_ClearFlags(self, PUBLIC_BOX_FLAG_POCKETS_DRAWN);
    } else {
        MenuScene_ScrollWipe(pbox_scene(self), PUBLIC_BOX_POCKETS_LAYER, 0, 0);
    }
    self->pockets_y = MenuScene_WipeOffsetY(pbox_scene(self));
}
CLEAN_AS(func_ov110_0229e4b0, PublicBox_PocketsWipeOut)

/* func_ov110_0229e4fc (state 5): the box wipes out; when done, its layer hidden and the box no
 * longer drawn, and the pockets' wipe out starts (state 6, run at once). Else its layer follows
 * the wipe and the wipe's y is kept for the box. */
void PublicBox_BoxWipeOut(PublicBox *self)
{
    if (MenuScene_StepWipe(pbox_scene(self), 0)) {
        DisplayLayer_HideAndResetScroll(PUBLIC_BOX_BOX_LAYER);
        PublicBox_ClearFlags(self, PUBLIC_BOX_FLAG_BOX_DRAWN);
        MenuScene_StartWipeOnWindow2(pbox_scene(self), PUBLIC_BOX_WIPE_POCKETS, 0, 0, PUBLIC_BOX_WIPE_MARGIN);
        MenuScene_ScrollWipe(pbox_scene(self), PUBLIC_BOX_POCKETS_LAYER, 0, 0);
        MenuScene_SetState(pbox_scene(self), PUBLIC_BOX_STATE_POCKETS_WIPE_OUT);
        PublicBox_PocketsWipeOut(self);
    } else {
        MenuScene_ScrollWipe(pbox_scene(self), PUBLIC_BOX_BOX_LAYER, 0, 0);
        self->box_y = MenuScene_WipeOffsetY(pbox_scene(self));
    }
}
CLEAN_AS(func_ov110_0229e4fc, PublicBox_BoxWipeOut)

/* func_ov110_0229e564 (state 4): once the scene may leave (PublicBox_CanLeave), the popup and the
 * cursor sprite hidden, the parent (overlay 92's dispatcher) told the screen ends with the
 * backdrop closed, and the box's wipe out started (state 5). */
void PublicBox_StartWipeOut(PublicBox *self)
{
    if (PublicBox_CanLeave(self) == 0) {
        return;
    }
    Popup_Hide(&self->popup, 1);
    PublicBox_HideCursorSprite(self);
    MenuDispatch *parent = (MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self);
    MenuDispatch_SetMode(parent, MENU_DISPATCH_MODE_CLOSE, 1);
    MenuScene_StartWipeOnWindow2(pbox_scene(self), PUBLIC_BOX_WIPE_BOX, 4, 1, PUBLIC_BOX_WIPE_MARGIN);
    MenuScene_SetWipeExtent(pbox_scene(self), PUBLIC_BOX_WIPE_EXTENT);
    MenuScene_ScrollWipe(pbox_scene(self), PUBLIC_BOX_BOX_LAYER, 0, 0);
    self->box_y = MenuScene_WipeOffsetY(pbox_scene(self));
    MenuScene_SetState(pbox_scene(self), PUBLIC_BOX_STATE_BOX_WIPE_OUT);
}
CLEAN_AS(func_ov110_0229e564, PublicBox_StartWipeOut)

/* func_ov110_0229e5d4 (state 3): the box wipes in; when done, the interactive phase begins with
 * the end of an action (PublicBox_EndAction). Its layer follows the wipe and the wipe's y is kept
 * for the box. */
void PublicBox_BoxWipeIn(PublicBox *self)
{
    if (MenuScene_StepWipeBack(pbox_scene(self), 0)) {
        MenuScene_SetPhase(pbox_scene(self), PUBLIC_BOX_PHASE_INTERACTIVE);
        PublicBox_EndAction(self);
    }
    MenuScene_ScrollWipe(pbox_scene(self), PUBLIC_BOX_BOX_LAYER, 0, 0);
    self->box_y = MenuScene_WipeOffsetY(pbox_scene(self));
}
CLEAN_AS(func_ov110_0229e5d4, PublicBox_BoxWipeIn)

/* func_ov110_0229e60c (state 2): the pockets wipe in (their layer following, the wipe's y kept
 * for them); when done, the box layer is loaded and its covered wipe in starts, the box drawn
 * from then on (state 3). */
void PublicBox_PocketsWipeIn(PublicBox *self)
{
    int done = MenuScene_StepWipeBack(pbox_scene(self), 0);
    MenuScene_ScrollWipe(pbox_scene(self), PUBLIC_BOX_POCKETS_LAYER, 0, 0);
    self->pockets_y = MenuScene_WipeOffsetY(pbox_scene(self));
    if (done == 0) {
        return;
    }
    PublicBox_LoadBoxLayer(self);
    MenuScene_StartWipeCoveredOnWindow2(pbox_scene(self), PUBLIC_BOX_WIPE_BOX, 0, 1, PUBLIC_BOX_WIPE_MARGIN);
    MenuScene_SetWipeExtent(pbox_scene(self), PUBLIC_BOX_WIPE_EXTENT);
    PublicBox_SetFlags(self, PUBLIC_BOX_FLAG_BOX_DRAWN);
    DisplayLayer_Show(PUBLIC_BOX_BOX_LAYER);
    MenuScene_ScrollWipe(pbox_scene(self), PUBLIC_BOX_BOX_LAYER, 0, 0);
    self->box_y = MenuScene_WipeOffsetY(pbox_scene(self));
    MenuScene_SetState(pbox_scene(self), PUBLIC_BOX_STATE_BOX_WIPE_IN);
}
CLEAN_AS(func_ov110_0229e60c, PublicBox_PocketsWipeIn)

/* func_ov110_0229e68c (state 1): a step of the wallet display's setup (its answer unused), the
 * pockets loaded into the grid with the box, the slots that may not move locked, the pockets'
 * letters loaded and those in states 0-3 dimmed; the pockets' covered wipe in starts, their layer
 * shown and the scene and the pockets drawn from then on (state 2). */
void PublicBox_StartWipeIn(PublicBox *self)
{
    PublicBox_LoadWalletFiles(self);
    PocketsGrid_LoadPockets(&self->grid);
    PocketsGrid_SetBox(&self->grid, self->box);
    PublicBox_LockSlots(self);
    PocketsLetters_LoadPockets(&self->letters);
    PocketsLetters_DimByState(&self->letters, 0xf);
    MenuScene_StartWipeCoveredOnWindow2(pbox_scene(self), PUBLIC_BOX_WIPE_POCKETS, 0, 0, PUBLIC_BOX_WIPE_MARGIN);
    DisplayLayer_Show(PUBLIC_BOX_POCKETS_LAYER);
    MenuScene_ScrollWipe(pbox_scene(self), PUBLIC_BOX_POCKETS_LAYER, 0, 0);
    MenuScene_SetState(pbox_scene(self), PUBLIC_BOX_STATE_POCKETS_WIPE_IN);
    PublicBox_SetFlags(self, PUBLIC_BOX_FLAG_DRAWN);
    PublicBox_SetFlags(self, PUBLIC_BOX_FLAG_POCKETS_DRAWN);
    self->pockets_y = MenuScene_WipeOffsetY(pbox_scene(self));
}
CLEAN_AS(func_ov110_0229e68c, PublicBox_StartWipeIn)

/* func_ov110_0229e718 (state 0): the layers set up and the wallet's display started; state 1. */
void PublicBox_StartSetup(PublicBox *self)
{
    PublicBox_SetUpLayers();
    PublicBox_PrepareWallet(self);
    MenuScene_SetState(pbox_scene(self), PUBLIC_BOX_STATE_START_WIPE_IN);
}
CLEAN_AS(func_ov110_0229e718, PublicBox_StartSetup)

/* func_ov110_0229e734 (vtable slot 0x5c, phase 5): the scene asks to be deleted. Answers 1. */
int PublicBox_End(PublicBox *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov110_0229e734, PublicBox_End)

/* func_ov110_0229e744 (vtable slot 0x58, phase 4): nothing. */
int PublicBox_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov110_0229e744, PublicBox_Phase4Idle)

/* func_ov110_0229e748 (vtable slot 0x54, phase 3): nothing. */
int PublicBox_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov110_0229e748, PublicBox_Phase3Idle)

/* Obj_ov110_0229ecb8::func_ov110_0229e74c (vtable slot 0x50, phase 2): a frame of the scene in
 * use. The menu close's delay is counted first; when the menu is asked to close (in the recycle
 * bin's mode) in sub state 0, 1 or 4, the cursor sprite and the popup are hidden and the scene
 * ends at once. Else the frame's start, its sub state and its end. Answers 1. */
int PublicBox_RunInteractive(PublicBox *self)
{
    StateFlags_CountMenuCloseDelay();
    if (PublicBox_CloseAsked(self) != 0) {
        u8 sub_state = self->base.sub_state;
        if (sub_state == PUBLIC_BOX_SUB_TOUCH_IDLE || sub_state == PUBLIC_BOX_SUB_TOUCH_HOLD ||
            sub_state == PUBLIC_BOX_SUB_BROWSE) {
            PublicBox_HideCursorSprite(self);
            Popup_Hide(&self->popup, 0);
            PublicBox_Finish(self, 0);
            return 1;
        }
    }
    PublicBox_BeginInteractiveFrame(self);
    PublicBox_RunSubState(self);
    PublicBox_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov110_0229ecb819func_ov110_0229e74cEv, PublicBox_RunInteractive)

/* func_ov110_0229e7ac: whether main asks the menu to close and the box is the recycle bin's
 * (mode 0x20); the other modes do not close this way. */
int PublicBox_CloseAsked(PublicBox *self)
{
    (void) self;
    if (StateFlags_MenuCloseAsked()) {
        if (GroupParams_Mode() == PUBLIC_BOX_MODE_RECYCLE) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov110_0229e7ac, PublicBox_CloseAsked)

/* Obj_ov110_0229ecb8::func_ov110_0229e7cc: the sub state's function (PublicBoxSubState) through
 * the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 0x16; the game reads past the table for others. */
void PublicBox_RunSubState(PublicBox *self)
{
    static const MemberPointer *const sub_states[PUBLIC_BOX_SUB_STATES] = {
        &data_ov110_0229ec68, &data_ov110_0229ec60, &data_ov110_0229ec58, &data_ov110_0229ec50, &data_ov110_0229ec48,
        &data_ov110_0229ec40, &data_ov110_0229ec38, &data_ov110_0229ec30, &data_ov110_0229ebe8, &data_ov110_0229ec28,
        &data_ov110_0229ec18, &data_ov110_0229ec10, &data_ov110_0229ec78, &data_ov110_0229ec00, &data_ov110_0229ebf8,
        &data_ov110_0229ebf0, &data_ov110_0229ebe0, &data_ov110_0229ec70, &data_ov110_0229ebd8, &data_ov110_0229ec08,
        &data_ov110_0229ebc8, &data_ov110_0229eca0,
    };
    MemberTable_InitOnce(&data_ov110_0229ee24, data_ov110_0229ee60, sub_states, PUBLIC_BOX_SUB_STATES);
    MemberPointer_CallVoid(&data_ov110_0229ee60[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov110_0229ecb819func_ov110_0229e7ccEv, PublicBox_RunSubState)

/* Obj_ov110_0229ecb8::func_ov110_0229e954 (vtable slot 0x4c, phase 1): a frame of the scene's
 * states (PublicBoxState) between the frame's start and end, through the table of member
 * functions (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 7; the game reads past the table for others. */
int PublicBox_RunState(PublicBox *self)
{
    static const MemberPointer *const states[PUBLIC_BOX_STATES] = {
        &data_ov110_0229ebc0, &data_ov110_0229eca8, &data_ov110_0229ec20, &data_ov110_0229ec98,
        &data_ov110_0229ec90, &data_ov110_0229ec88, &data_ov110_0229ec80,
    };
    MemberTable_InitOnce(&data_ov110_0229ee20, data_ov110_0229ee28, states, PUBLIC_BOX_STATES);
    PublicBox_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov110_0229ee28[self->base.state], self);
    PublicBox_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov110_0229ecb819func_ov110_0229e954Ev, PublicBox_RunState)

/* func_ov110_0229ea10 (vtable slot 0x24): the scene's draw, while it is drawn: the popup (through
 * its class, slot 2), the cursor sprite (with the keys in use), the held item; with the box
 * drawn, the box at its wipe's y; with the pockets drawn, the pockets, their letters and the
 * wallet at theirs. Answers 1. */
int PublicBox_Draw(PublicBox *self)
{
    if (PublicBox_TestFlags(self, PUBLIC_BOX_FLAG_DRAWN) == 0) {
        return 1;
    }
    pbox_call_member(&self->popup, 2);
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    PublicBox_DrawHeld(self);
    if (PublicBox_TestFlags(self, PUBLIC_BOX_FLAG_BOX_DRAWN) != 0) {
        PocketsGrid_DrawBox(&self->grid, 0, self->box_y);
    }
    if (PublicBox_TestFlags(self, PUBLIC_BOX_FLAG_POCKETS_DRAWN) != 0) {
        PocketsGrid_DrawPockets(&self->grid, 0, self->pockets_y);
        PocketsLetters_DrawPockets(&self->letters, 0, self->pockets_y);
        PocketsWallet_Draw(&self->wallet, self->pockets_y);
    }
    return 1;
}
CLEAN_AS(func_ov110_0229ea10, PublicBox_Draw)

/* func_ov110_0229eab4 (vtable slot 0x0c): the scene closes: the parent told and the members torn
 * down. Answers 1. */
int PublicBox_Close(PublicBox *self)
{
    MenuDispatch_ChildClosed((MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self));
    PublicBox_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov110_0229eab4, PublicBox_Close)

/* func_ov110_0229ead0 (vtable slot 0x00): the scene starts: its setup, state 0 and phase 0 (the
 * base's wait). Answers 1. */
int PublicBox_Start(PublicBox *self)
{
    PublicBox_Setup(self);
    MenuScene_SetState(pbox_scene(self), PUBLIC_BOX_STATE_START_SETUP);
    MenuScene_SetPhase(pbox_scene(self), PUBLIC_BOX_PHASE_WAIT);
    return 1;
}
CLEAN_AS(func_ov110_0229ead0, PublicBox_Start)

/* func_ov110_0229eaf0 (named by the profile at 0x0229ebd0): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order, the two labels by __cxa_vec_ctor. */
PublicBox *PublicBox_New(void)
{
    PublicBox *self = MenuScene_Alloc(sizeof(PublicBox));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov110_0229ecb8;
    LayerTask_ConstructPair(&self->task);
    PocketsGrid_Construct(&self->grid);
    PocketsLetters_Construct(&self->letters);
    PocketsWallet_Construct(&self->wallet);
    Popup_Construct(&self->popup);
    Glide_Construct(&self->glide);
    Glider0_Construct(&self->cursor_sprite);
    PagedChoice_Construct(pbox_choice(self));
    ErrorMessage_Construct(&self->error);
    __cxa_vec_ctor(self->labels, PUBLIC_BOX_LABELS, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070c08,
                   (void (*)(void *))(uintptr_t) func_02070be8);
    return self;
}
CLEAN_AS(func_ov110_0229eaf0, PublicBox_New)
