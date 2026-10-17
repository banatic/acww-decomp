/* Overlay 100's scene (pockets_box.h): the held item's moves, the sub states of the scene in
 * use (phase 2), its states (phase 1) and its vtable's slots.
 *
 * With the touch screen (state flag 2 clear) the scene idles in sub state 0: a touch on an
 * item's slot holds it (1), and moving the pen drags it (3) until it is let go over a place.
 * With the keys it idles in sub state 4: the cursor moves between the places, A picks up the
 * item (0x0b, 0x0c) and puts it down (5, then 0x0d or 0x0e), Y sends it to the other part, B
 * and START end the scene. An item put down elsewhere than under the cursor glides there
 * (0x10). The two end places end the scene (sub state 0x15, then states 4-6 wipe it out). */
#include "pockets_box.h"

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
#include "ov094/pockets_grid.h"
#include "ov094/pockets_letters.h"
#include "ov094/pockets_wallet.h"

/* The class's vtable. */
extern const u8 data_ov100_0229ecb8[];

/* The pen (autoload_2/input.c): down, and gone down or up this frame; where it is. */
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58, data_021f6c54;

/* The pad (autoload_2/input.h) and the buttons read in `pressed`. */
extern PadState data_021fbe40;
#define PBS_PAD_A 0x0001
#define PBS_PAD_B 0x0002
#define PBS_PAD_START 0x0008
#define PBS_PAD_Y 0x0800

/* The current heap. */
extern Heap *data_021fbe94;

/* The labels' constructor and destructor, handed to __cxa_vec_ctor (so the game's symbols). */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void *func_02070c08(void *label);
extern void *func_02070be8(void *label);

/* The files of the box's layer (4): its map and tiles, and by the mode a palette and tiles. */
extern const char data_ov100_0229ed18[]; /* "menu/inventory/b_itm_bg_tra1.bsc" */
extern const char data_ov100_0229ed3c[]; /* "menu/inventory/b_itm_sell.bch" */
extern const char data_ov100_0229ed5c[]; /* "menu/inventory/ten6.bpl", mode 0x1d */
extern const char data_ov100_0229ed74[]; /* "menu/inventory/tanu.bch" */
extern const char data_ov100_0229ed8c[]; /* "menu/inventory/ten7.bpl", mode 0x1e */
extern const char data_ov100_0229eda4[]; /* "menu/inventory/kinu.bch" */
extern const char data_ov100_0229edbc[]; /* "menu/inventory/ten8.bpl", mode 0x1f */
extern const char data_ov100_0229edd4[]; /* "menu/inventory/lost.bch" */
extern const char data_ov100_0229edec[]; /* "menu/inventory/ten9.bpl", mode 0x20 */
extern const char data_ov100_0229ee04[]; /* "menu/inventory/garb.bch" */

/* The lists of player messages 3 and 4 (pockets_box.h). */
extern const u8 data_021f3a68[];
extern const u8 data_021f3a86[];
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The tables of member functions (member_pointer.h): the guards, the tables and their
 * constants (the symbol table also names the sub states' table's part from entry 16, at
 * 0x0229eee0). */
extern u32 data_ov100_0229ee20; /* the states' guard */
extern u32 data_ov100_0229ee24; /* the sub states' guard */
extern MemberPointer data_ov100_0229ee28[POCKETS_BOX_STATES];
extern MemberPointer data_ov100_0229ee60[POCKETS_BOX_SUB_STATES];
extern const MemberPointer data_ov100_0229ebc0, data_ov100_0229ebc8, data_ov100_0229ebd8, data_ov100_0229ebe0,
    data_ov100_0229ebe8, data_ov100_0229ebf0, data_ov100_0229ebf8, data_ov100_0229ec00, data_ov100_0229ec08,
    data_ov100_0229ec10, data_ov100_0229ec18, data_ov100_0229ec20, data_ov100_0229ec28, data_ov100_0229ec30,
    data_ov100_0229ec38, data_ov100_0229ec40, data_ov100_0229ec48, data_ov100_0229ec50, data_ov100_0229ec58,
    data_ov100_0229ec60, data_ov100_0229ec68, data_ov100_0229ec70, data_ov100_0229ec78, data_ov100_0229ec80,
    data_ov100_0229ec88, data_ov100_0229ec90, data_ov100_0229ec98, data_ov100_0229eca0, data_ov100_0229eca8;

/* The layers: 6 holds the pockets, 4 the box (display_layers.h's numbers). */
#define PBS_POCKETS_LAYER 6
#define PBS_BOX_LAYER 4

/* The wipes' screens, layers bits, frames, directions and margin. */
#define PBS_WIPE_SCREEN 0
#define PBS_WIPE_MARGIN 0x30
#define PBS_WIPE_EXTENT 0x80

/* What the parent (overlay 92's) is told when the scene leaves. */
#define PBS_PARENT_MODE_LEAVE 0x44

/* Frames a popup shown by a touch stays. */
#define PBS_POPUP_FRAMES 0x3c

/* The held item glides to a place in this many steps. */
#define PBS_GLIDE_STEPS 4

/* A held item let go at or below this y goes to the pockets, above it to the box. */
#define PBS_POCKETS_TOP_Y 0x6c

/* The end places' area on the touch screen: the confirm place above y 0x60, cancel below. */
#define PBS_BUTTONS_LEFT 0xc8
#define PBS_BUTTONS_RIGHT 0xf8
#define PBS_BUTTONS_TOP 0x50
#define PBS_BUTTONS_BOTTOM 0x70
#define PBS_CANCEL_TOP 0x60

/* The frames of the closed scene before it leaves. */
#define PBS_STATE_LEAVE POCKETS_BOX_STATE_LEAVE

/* A sum of two 32-bit values, wrapping as the ROM's addition does. */
static int pbs_add(int a, int b)
{
    return (int) ((u32) a + (u32) b);
}

static MenuScene *pbs_scene(PocketsBox *self)
{
    return &self->base;
}

static PagedChoice *pbs_choice(PocketsBox *self)
{
    return (PagedChoice *) (void *) self->choice;
}

static PocketsGrid *pbs_grid(PocketsBox *self)
{
    return (PocketsGrid *) (void *) self->grid;
}

static PocketsLetters *pbs_letters(PocketsBox *self)
{
    return (PocketsLetters *) (void *) self->letters;
}

static PocketsWallet *pbs_wallet(PocketsBox *self)
{
    return (PocketsWallet *) (void *) self->wallet;
}

static CellLayerSprite *pbs_cursor_cells(PocketsBox *self)
{
    /* The cursor sprite's base is main's cell layer sprite (glide.h). */
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

static void pbs_set_sub_state(PocketsBox *self, u8 sub_state)
{
    MenuScene_SetSubState(pbs_scene(self), sub_state);
}

/* The pen went down this frame. */
static int pbs_pen_pressed(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* Whether `place` is one of the grid's slots. */
static int pbs_is_slot(PocketsBox *self, unsigned int place)
{
    return PocketsBox_IsPocketPlace(self, place) || PocketsBox_IsBoxPlace(self, place);
}

/* The value kept with choice row `row` (ChoiceEntries.values), read as the ROM does at
 * 0x26c5 + row. */
static u8 pbs_entry_value(PocketsBox *self, int row)
{
    const u8 *bytes = (const u8 *) self;
    return bytes[offsetof(PocketsBox, entries) + offsetof(ChoiceEntries, values) + (size_t) row];
}

/* A member called through its class: slot 3 (the cursor sprite's update), slot 2 (the popup's
 * draw). */
static void pbs_call_slot(void *object, int slot)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[slot])(object);
}

/* ---- the held item's moves */

/* func_ov100_0229d69c: the item at `from` picked up and sent gliding from there to `to`. */
void PocketsBox_MoveItemTo(PocketsBox *self, int from, int to)
{
    PocketsBox_PickUpItem(self, from);
    self->held_x = PocketsBox_PlaceX(self, from);
    self->held_y = PocketsBox_PlaceY(self, from);
    PocketsBox_GlideHeldTo(self, to, PBS_GLIDE_STEPS);
}
CLEAN_AS(func_ov100_0229d69c, PocketsBox_MoveItemTo)

/* func_ov100_0229d6d8: the held item, let go at height `y` where it cannot stay, glides back to
 * `place`; but when it came from the box and was let go over the pockets, to the first free
 * pocket slot, and when it came from the pockets and was let go over the box, to the box's
 * first empty place (when there is one). */
void PocketsBox_GlideHeldBack(PocketsBox *self, int place, int y)
{
    int to = POCKETS_BOX_NO_PLACE;
    if (y >= PBS_POCKETS_TOP_Y) {
        if (PocketsBox_IsBoxPlace(self, (unsigned int) place)) {
            to = PocketsBox_FreePocketPlace(self);
        }
    } else if (PocketsBox_IsPocketPlace(self, (unsigned int) place)) {
        to = PocketsBox_FirstEmptyBoxPlace(self);
    }
    if (to != POCKETS_BOX_NO_PLACE) {
        place = to;
    }
    PocketsBox_GlideHeldTo(self, place, PBS_GLIDE_STEPS);
}
CLEAN_AS(func_ov100_0229d6d8, PocketsBox_GlideHeldBack)

/* func_ov100_0229d71c: the held item glides from where it is drawn to `place` in `steps`
 * steps (its first taken now); `held_place` becomes `place`; sub state 0x10. */
void PocketsBox_GlideHeldTo(PocketsBox *self, int place, int steps)
{
    self->held_place = (u8) place;
    Glide_SetPlace(&self->glide, self->held_x, self->held_y);
    int x = PocketsBox_PlaceX(self, place);
    int y = PocketsBox_PlaceY(self, place);
    Glide_MoveTo(&self->glide, x, y, steps);
    Glide_Step(&self->glide);
    PocketsBox_FollowGlide(self);
    pbs_set_sub_state(self, POCKETS_BOX_SUB_GLIDE);
}
CLEAN_AS(func_ov100_0229d71c, PocketsBox_GlideHeldTo)

/* func_ov100_0229d788: the item at `place` taken with the keys: the popup hidden (its queue
 * dropped), the item picked up and, when one is held, sub state 5 to come back to; drawn at
 * the cursor sprite, with sound 0x0d. */
void PocketsBox_TakeItem(PocketsBox *self, int place)
{
    self->held_place = (u8) place;
    Popup_Hide(&self->popup, 1);
    PocketsBox_PickUpItem(self, place);
    if (self->held_kind == POCKETS_BOX_HELD_ITEM) {
        self->return_state = POCKETS_BOX_SUB_KEYS_HELD;
    }
    PocketsBox_FollowCursorSprite(self);
    PocketsSound_Play0d();
}
CLEAN_AS(func_ov100_0229d788, PocketsBox_TakeItem)

/* func_ov100_0229d7d8: the item at `place` taken by the pen: as PocketsBox_TakeItem, then
 * dragged (sub state 3) when one is held, drawn at the touch. */
void PocketsBox_TakeItemByTouch(PocketsBox *self, int place)
{
    self->held_place = (u8) place;
    Popup_Hide(&self->popup, 1);
    PocketsBox_PickUpItem(self, place);
    if (self->held_kind == POCKETS_BOX_HELD_ITEM) {
        pbs_set_sub_state(self, POCKETS_BOX_SUB_DRAG);
    }
    PocketsBox_FollowTouch(self);
    PocketsSound_Play0d();
}
CLEAN_AS(func_ov100_0229d7d8, PocketsBox_TakeItemByTouch)

/* func_ov100_0229d824: the pen came down on `place`: sub state 1, the offset from the touch to
 * the place kept for the drag, the popup queued to tell of it; a place not locked is marked
 * free to take (with sound 0x0c). */
void PocketsBox_TouchPlace(PocketsBox *self, int place)
{
    self->touch_place = (u8) place;
    pbs_set_sub_state(self, POCKETS_BOX_SUB_TOUCH_HOLD);
    u8 touch_x = data_021f6c58;
    u8 touch_y = data_021f6c54;
    self->grab_dx = pbs_add(PocketsBox_PlaceX(self, self->touch_place), -touch_x);
    self->grab_dy = pbs_add(PocketsBox_PlaceY(self, self->touch_place), -touch_y);
    self->popup_place = (u8) place;
    Popup_Queue(&self->popup);
    if (PocketsBox_PlaceIsLocked(self, place) != 0) {
        PocketsBox_ClearFlags(self, POCKETS_BOX_FLAG_TOUCHED_FREE);
    } else {
        PocketsBox_SetFlags(self, POCKETS_BOX_FLAG_TOUCHED_FREE);
        PocketsSound_Play0c();
    }
}
CLEAN_AS(func_ov100_0229d824, PocketsBox_TouchPlace)

/* func_ov100_0229d8b0: an action ended: back to the touch's idle state, or the keys' when
 * state flag 2 is set. */
void PocketsBox_EndAction(PocketsBox *self)
{
    if (StateFlags_IsClear2()) {
        PocketsBox_ResumeTouch(self);
    } else {
        PocketsBox_ResumeKeys(self);
    }
}
CLEAN_AS(func_ov100_0229d8b0, PocketsBox_EndAction)

/* func_ov100_0229d8d0: back to the keys: no popup place, the cursor sprite shown, the key
 * repeat reset, the popup for the cursor's place, sub state 4, the cursor's place selected. */
void PocketsBox_ResumeKeys(PocketsBox *self)
{
    self->popup_place = POCKETS_BOX_NO_PLACE;
    PocketsBox_ShowCursorSprite(self);
    MenuScene_ResetKeyRepeat(pbs_scene(self));
    PocketsBox_UpdatePopup(self);
    pbs_set_sub_state(self, POCKETS_BOX_SUB_KEYS_IDLE);
    PocketsBox_SelectPlace(self, self->cursor);
}
CLEAN_AS(func_ov100_0229d8d0, PocketsBox_ResumeKeys)

/* func_ov100_0229d90c: back to the touch: the cursor sprite hidden, no selection, sub state 0. */
void PocketsBox_ResumeTouch(PocketsBox *self)
{
    PocketsBox_HideCursorSprite(self);
    PocketsBox_ClearSelection(self);
    pbs_set_sub_state(self, POCKETS_BOX_SUB_TOUCH_IDLE);
}
CLEAN_AS(func_ov100_0229d90c, PocketsBox_ResumeTouch)

/* ---- the sub states */

/* func_ov100_0229d928 (sub state 0x15): after `close_delay` more frames, state 4 (written
 * directly), phase 1, the popup hidden (its queue kept) and the cursor sprite hidden. */
void PocketsBox_WaitClosed(PocketsBox *self)
{
    if (self->close_delay != 0) {
        self->close_delay--;
        return;
    }
    self->base.state = PBS_STATE_LEAVE;
    MenuScene_SetPhase(pbs_scene(self), 1);
    Popup_Hide(&self->popup, 0);
    PocketsBox_HideCursorSprite(self);
}
CLEAN_AS(func_ov100_0229d928, PocketsBox_WaitClosed)

/* func_ov100_0229d968 (sub state 0x14): once the error message is done, back to the sub state
 * kept, the cursor sprite's window set. */
void PocketsBox_WaitError(PocketsBox *self)
{
    if (ErrorMessage_Update(&self->error, 0) != 0) {
        pbs_set_sub_state(self, self->return_state);
        CellLayerSprite_SetWindow(pbs_cursor_cells(self));
    }
}
CLEAN_AS(func_ov100_0229d968, PocketsBox_WaitError)

/* func_ov100_0229d9a0 (sub state 0x13): once the choice is closed, the picked row's action. */
void PocketsBox_WaitChoiceClosed(PocketsBox *self)
{
    if (PagedChoice_IsIdle(pbs_choice(self))) {
        PocketsBox_RunAction(self);
    }
}
CLEAN_AS(func_ov100_0229d9a0, PocketsBox_WaitChoiceClosed)

/* func_ov100_0229d9c0 (sub state 0x12): once the choice's count ends, it is asked to close, the
 * cursor sprite (when animated) put back at the cursor, and sub state 0x13. Answers 0 while
 * counting, else MenuScene_SetSubState's answer.
 * QUIRK: that answer is an address, returned as an int. */
int PocketsBox_CloseChoice(PocketsBox *self)
{
    int counted = PagedChoice_CountDown(pbs_choice(self));
    if (counted == 0) {
        return counted;
    }
    PagedChoice_RequestClose(pbs_choice(self), 0);
    if (CellLayerSprite_AnimNumber(pbs_cursor_cells(self))) {
        PocketsBox_PlaceCursorSprite(self);
    }
    return (int) (uintptr_t) MenuScene_SetSubState(pbs_scene(self), POCKETS_BOX_SUB_CHOICE_CLOSING);
}
CLEAN_AS(func_ov100_0229d9c0, PocketsBox_CloseChoice)

/* func_ov100_0229da04 (sub state 0x11): once the choice is shown, its keys (sub state 6, the
 * cursor sprite at its first row) when state flag 2 is set, else its touch (sub state 2). */
void PocketsBox_WaitChoiceShown(PocketsBox *self)
{
    if (PagedChoice_IsShown(pbs_choice(self)) == 0) {
        return;
    }
    if (StateFlags_Test2()) {
        PocketsBox_PointAtFirstRow(self);
        pbs_set_sub_state(self, POCKETS_BOX_SUB_CHOICE_KEYS);
    } else {
        pbs_set_sub_state(self, POCKETS_BOX_SUB_CHOICE_TOUCH);
    }
}
CLEAN_AS(func_ov100_0229da04, PocketsBox_WaitChoiceShown)

/* func_ov100_0229da40 (sub state 0x10): the glide's step; at its end the held item is put at
 * `held_place`, the action ends and sound 0x0e plays; else the item follows the glide. */
void PocketsBox_StepGlide(PocketsBox *self)
{
    if (Glide_Step(&self->glide)) {
        PocketsBox_PutHeldAt(self, self->held_place);
        PocketsBox_EndAction(self);
        PocketsSound_Play0e();
    } else {
        PocketsBox_FollowGlide(self);
    }
}
CLEAN_AS(func_ov100_0229da40, PocketsBox_StepGlide)

/* func_ov100_0229da7c (sub state 0x0f): back to the sub state kept once the cursor sprite's
 * animation is done; once its turn has settled, the held item (shown again, with sound 0x0d, if
 * it was hidden) follows the sprite. */
void PocketsBox_Swapped(PocketsBox *self)
{
    if (CellLayerSprite_IsDone(pbs_cursor_cells(self)) != 0) {
        pbs_set_sub_state(self, self->return_state);
    }
    if (Glider_IsTurnSettled(&self->cursor_sprite) != 0) {
        if (PocketsBox_TestFlags(self, POCKETS_BOX_FLAG_HELD_HIDDEN) != 0) {
            PocketsBox_ClearFlags(self, POCKETS_BOX_FLAG_HELD_HIDDEN);
            PocketsSound_Play0d();
        }
        PocketsBox_FollowCursorSprite(self);
    }
}
CLEAN_AS(func_ov100_0229da7c, PocketsBox_Swapped)

/* func_ov100_0229dad0 (sub state 0x0e): unless the cursor sprite's turn is at its frame 2 (or
 * it is not turning), the held item swapped with the target's and hidden, sub state 0x0f and
 * the popup for the cursor's place; else sub state 4. */
void PocketsBox_Swap(PocketsBox *self)
{
    if (Glider_IsTurnAtFrame2(&self->cursor_sprite) == 0) {
        PocketsBox_SwapHeldWith(self, self->target);
        PocketsBox_SetFlags(self, POCKETS_BOX_FLAG_HELD_HIDDEN);
        pbs_set_sub_state(self, POCKETS_BOX_SUB_SWAPPED);
        PocketsBox_UpdatePopup(self);
    } else {
        pbs_set_sub_state(self, POCKETS_BOX_SUB_KEYS_IDLE);
    }
}
CLEAN_AS(func_ov100_0229dad0, PocketsBox_Swap)

/* func_ov100_0229db18 (sub state 0x0d): while the cursor sprite's turn has not settled, the
 * held item is put down: at the cursor's place at once (the popup for it, sub state 4, sound
 * 0x0e), elsewhere by a glide to the target. Once it has settled the item follows the sprite. */
void PocketsBox_PutDown(PocketsBox *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite) != 0) {
        PocketsBox_FollowCursorSprite(self);
        return;
    }
    if (self->cursor == self->target) {
        PocketsBox_DropHeld(self, self->target);
        PocketsBox_UpdatePopup(self);
        pbs_set_sub_state(self, POCKETS_BOX_SUB_KEYS_IDLE);
        PocketsSound_Play0e();
    } else {
        PocketsBox_GlideHeldTo(self, self->target, PBS_GLIDE_STEPS);
    }
}
CLEAN_AS(func_ov100_0229db18, PocketsBox_PutDown)

/* func_ov100_0229db70 (sub state 0x0c): back to the sub state kept once the cursor sprite's
 * animation is done; the held item follows the sprite. */
void PocketsBox_PickedUp(PocketsBox *self)
{
    if (CellLayerSprite_IsDone(pbs_cursor_cells(self))) {
        pbs_set_sub_state(self, self->return_state);
    }
    PocketsBox_FollowCursorSprite(self);
}
CLEAN_AS(func_ov100_0229db70, PocketsBox_PickedUp)

/* func_ov100_0229dba0 (sub state 0x0b): once the cursor sprite's turn has settled, the
 * cursor's item taken and sub state 0x0c. */
void PocketsBox_PickUp(PocketsBox *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite) != 0) {
        PocketsBox_TakeItem(self, self->cursor);
        pbs_set_sub_state(self, POCKETS_BOX_SUB_PICKED_UP);
    }
}
CLEAN_AS(func_ov100_0229dba0, PocketsBox_PickUp)

/* func_ov100_0229dbd0 (sub state 0x0a): once the cursor sprite's animation is done, the first
 * of its set and sub state 4. */
void PocketsBox_ButtonDone(PocketsBox *self)
{
    if (CellLayerSprite_IsDone(pbs_cursor_cells(self))) {
        PocketsBox_ShowCursorFirstOfSet(self);
        pbs_set_sub_state(self, POCKETS_BOX_SUB_KEYS_IDLE);
    }
}
CLEAN_AS(func_ov100_0229dbd0, PocketsBox_ButtonDone)

/* func_ov100_0229dbf8 (sub state 9): once the cursor sprite's animation is done, the end place
 * under the cursor picked (confirm or cancel); at another place sub state 0x0a. */
void PocketsBox_PressButton(PocketsBox *self)
{
    if (!CellLayerSprite_IsDone(pbs_cursor_cells(self))) {
        return;
    }
    if (self->cursor == POCKETS_BOX_CONFIRM) {
        PocketsBox_Confirm(self);
    } else if (self->cursor == POCKETS_BOX_CANCEL) {
        PocketsBox_Cancel(self);
    } else {
        PocketsBox_BeginSubState10(self);
    }
}
CLEAN_AS(func_ov100_0229dbf8, PocketsBox_PressButton)

/* Obj_ov100_0229ecb8::func_ov100_0229dc38 (sub state 8): once the cursor sprite has stopped,
 * back to the sub state kept; for sub states 4 and 5 the cursor's place is selected and that
 * sub state runs at once. The held item follows the sprite. */
void PocketsBox_WaitSprite(PocketsBox *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        pbs_set_sub_state(self, self->return_state);
        if (self->return_state == POCKETS_BOX_SUB_KEYS_IDLE || self->return_state == POCKETS_BOX_SUB_KEYS_HELD) {
            PocketsBox_SelectPlace(self, self->cursor);
        }
        PocketsBox_RunSubState(self);
    }
    PocketsBox_FollowCursorSprite(self);
}
CLEAN_AS(_ZN18Obj_ov100_0229ecb819func_ov100_0229dc38Ev, PocketsBox_WaitSprite)

/* func_ov100_0229dc88 (sub state 7): once the cursor sprite's animation is done, the choice row
 * it points at picked (with its sound) and its action kept; sub state 0x12. */
void PocketsBox_PickChoiceRow(PocketsBox *self)
{
    if (CellLayerSprite_IsDone(pbs_cursor_cells(self)) == 0) {
        return;
    }
    PagedChoice_PickRowWithSound(pbs_choice(self), self->choice_row, 1);
    self->action = pbs_entry_value(self, self->choice_row);
    pbs_set_sub_state(self, POCKETS_BOX_SUB_CHOICE_CLOSE);
}
CLEAN_AS(func_ov100_0229dc88, PocketsBox_PickChoiceRow)

/* func_ov100_0229dcd8 (sub state 6): the choice with the keys: a touch closes it without a
 * pick; a move of its cursor sends the cursor sprite to the row; A turns the sprite (sub
 * state 7, which picks the row), B points at the last row. */
void PocketsBox_ChoiceKeys(PocketsBox *self)
{
    if (MenuScene_TakeTouch(pbs_scene(self)) != 0) {
        PocketsBox_CancelChoice(self);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(pbs_scene(self));
    if (PagedChoice_MoveCursor(pbs_choice(self), keys, &self->choice_row, 0) != 0) {
        PocketsBox_GlideToRow(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & PBS_PAD_A) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        pbs_set_sub_state(self, POCKETS_BOX_SUB_CHOICE_PICK);
    } else if (pressed & PBS_PAD_B) {
        PocketsBox_PointAtLastRow(self);
    }
}
CLEAN_AS(func_ov100_0229dcd8, PocketsBox_ChoiceKeys)

/* func_ov100_0229dd54 (sub state 5): an item held with the keys. A move of the cursor (in its
 * row, wrapping) sends the sprite there with the popup hidden. Else A puts the item down on a
 * free slot under the cursor or swaps it with the item there (nothing on a locked slot or an
 * end place), B puts it back where it came from; else the item follows the sprite and a queued
 * popup is shown. */
void PocketsBox_KeysHeld(PocketsBox *self)
{
    int keys = (int) MenuScene_LatchRepeatedKeys(pbs_scene(self));
    if (PocketsBox_MoveCursor(self, keys, 1) != 0) {
        PocketsBox_UpdatePopup(self);
        PocketsBox_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & PBS_PAD_A) {
        if (pbs_is_slot(self, self->cursor) && PocketsBox_PlaceIsLocked(self, self->cursor) == 0) {
            if (PocketsBox_PlaceIsEmpty(self, self->cursor) != 0) {
                PocketsBox_StartPutDown(self, self->cursor);
            } else {
                PocketsBox_StartSwap(self, self->cursor);
            }
        }
    } else if (pressed & PBS_PAD_B) {
        PocketsBox_StartPutDown(self, self->held_place);
    } else {
        PocketsBox_FollowCursorSprite(self);
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov100_0229dd54, PocketsBox_KeysHeld)

/* func_ov100_0229de18 (sub state 4): the keys with nothing held. A touch goes back to the touch
 * (the popup hidden with its queue). A move of the cursor sends the sprite there with the popup
 * hidden. On a place not locked: A picks up the item of a slot (nothing on an empty one) or
 * presses an end place (sub state 9); Y sends a slot's item to the other part's first free
 * place, when there is one (the popup hidden with its queue). Else (or on a locked place) B
 * cancels and START confirms the scene, the cursor sprite and the popup hidden; with no key a
 * queued popup is shown. */
void PocketsBox_KeysIdle(PocketsBox *self)
{
    if (MenuScene_TakeTouch(pbs_scene(self)) != 0) {
        PocketsBox_ResumeTouch(self);
        Popup_Hide(&self->popup, 1);
        return;
    }
    if (PocketsBox_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(pbs_scene(self)), 0) != 0) {
        PocketsBox_UpdatePopup(self);
        PocketsBox_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    if (PocketsBox_PlaceIsLocked(self, self->cursor) == 0) {
        u16 pressed = data_021fbe40.pressed;
        if (pressed & PBS_PAD_A) {
            if (pbs_is_slot(self, self->cursor)) {
                if (PocketsBox_PlaceIsEmpty(self, self->cursor) == 0) {
                    PocketsBox_StartPickUp(self);
                }
            } else if (PocketsBox_IsButtonPlace(self, self->cursor) != 0) {
                PocketsBox_BeginSubState9(self);
            }
            return;
        }
        if (pressed & PBS_PAD_Y) {
            if (pbs_is_slot(self, self->cursor) && PocketsBox_PlaceIsEmpty(self, self->cursor) == 0) {
                int to;
                if (PocketsBox_IsPocketPlace(self, self->cursor) != 0) {
                    to = PocketsBox_FirstEmptyBoxPlace(self);
                } else {
                    to = PocketsBox_FreePocketPlace(self);
                }
                if (to != POCKETS_BOX_NO_PLACE) {
                    PocketsBox_MoveItemTo(self, self->cursor, to);
                    Popup_Hide(&self->popup, 1);
                }
            }
            return;
        }
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & PBS_PAD_B) {
        PocketsBox_HideCursorSprite(self);
        PocketsBox_Cancel(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    if (pressed & PBS_PAD_START) {
        PocketsBox_HideCursorSprite(self);
        PocketsBox_Confirm(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    Popup_ShowQueued(&self->popup);
}
CLEAN_AS(func_ov100_0229de18, PocketsBox_KeysIdle)

/* func_ov100_0229df98 (sub state 3): an item dragged by the pen, drawn at the touch, over the
 * place under its middle (8 pixels right and down of where it is drawn), no place marked. When
 * the box started empty, a place of the other part than the one the item came from that holds
 * an item counts as none. While the pen is down the place (if any) is marked. Once it is up the
 * item is dropped there (sound 0x0e, the action ends); when that cannot be (no place, a locked
 * place) it glides back (PocketsBox_GlideHeldBack). */
void PocketsBox_Drag(PocketsBox *self)
{
    PocketsBox_FollowTouch(self);
    PocketsBox_ClearHighlights(self);
    int y = pbs_add(self->held_y, 8);
    int x = pbs_add(self->held_x, 8);
    int place = PocketsBox_PlaceAtTouch(self, x, y, 0);

    if (PocketsBox_TestFlags(self, POCKETS_BOX_FLAG_STARTED_EMPTY) != 0) {
        int crosses =
            (PocketsBox_IsBoxPlace(self, (unsigned int) place) && PocketsBox_IsPocketPlace(self, self->held_place)) ||
            (PocketsBox_IsPocketPlace(self, (unsigned int) place) && PocketsBox_IsBoxPlace(self, self->held_place));
        if (crosses && PocketsBox_PlaceItem(self, place) != ITEM_CODE_NONE) {
            place = POCKETS_BOX_NO_PLACE;
        }
    }

    if (place == POCKETS_BOX_NO_PLACE) {
        if (data_021fbdd8 == 0) {
            PocketsBox_GlideHeldBack(self, self->held_place, y);
        }
        return;
    }
    if (data_021fbdd8 != 0) {
        PocketsBox_HighlightPlace(self, place);
        return;
    }
    if (PocketsBox_PlaceIsLocked(self, place) == 0 && PocketsBox_DropHeld(self, place) != 0) {
        PocketsSound_Play0e();
        PocketsBox_EndAction(self);
        return;
    }
    PocketsBox_GlideHeldBack(self, self->held_place, y);
}
CLEAN_AS(func_ov100_0229df98, PocketsBox_Drag)

/* func_ov100_0229e098 (sub state 2): the choice by touch: the buttons close it without a pick;
 * the pen coming down on a row picks it (with its sound), keeps its action, sub state 0x12. */
void PocketsBox_ChoiceTouch(PocketsBox *self)
{
    if (MenuScene_TakeButtons(pbs_scene(self), 1) != 0) {
        PocketsBox_CancelChoice(self);
        return;
    }
    if (!pbs_pen_pressed()) {
        return;
    }
    int row = PagedChoice_RowAtOrLast(pbs_choice(self), data_021f6c58, data_021f6c54);
    if (row >= 0) {
        PagedChoice_PickRowWithSound(pbs_choice(self), row, 1);
        self->action = pbs_entry_value(self, row);
        pbs_set_sub_state(self, POCKETS_BOX_SUB_CHOICE_CLOSE);
    }
}
CLEAN_AS(func_ov100_0229e098, PocketsBox_ChoiceTouch)

/* func_ov100_0229e124 (sub state 1): the pen down on a place. Let go: back to sub state 0, the
 * popup staying 0x3c frames. Moved by more than 8 pixels from a place free to take: its item
 * taken (dragged). Else a queued popup is shown. */
void PocketsBox_TouchHold(PocketsBox *self)
{
    if (data_021fbdd8 == 0) {
        pbs_set_sub_state(self, POCKETS_BOX_SUB_TOUCH_IDLE);
        Popup_SetTimer(&self->popup, PBS_POPUP_FRAMES);
        return;
    }
    if (PocketsBox_TestFlags(self, POCKETS_BOX_FLAG_TOUCHED_FREE) != 0 && PocketsBox_TouchMoved(self) != 0) {
        PocketsBox_TakeItemByTouch(self, self->touch_place);
    } else {
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov100_0229e124, PocketsBox_TouchHold)

/* func_ov100_0229e17c (sub state 0): the touch with nothing held. The buttons go back to the
 * keys. The pen coming down on a slot with an item holds it (sub state 1); in the end places'
 * area (x 0xc8-0xf8, y 0x50-0x70) it confirms (above y 0x60) or cancels the scene. */
void PocketsBox_TouchIdle(PocketsBox *self)
{
    if (MenuScene_TakeButtons(pbs_scene(self), 1) != 0) {
        PocketsBox_ResumeKeys(self);
        return;
    }
    if (!pbs_pen_pressed()) {
        return;
    }
    int x = data_021f6c58;
    int y = data_021f6c54;
    int place = PocketsBox_PlaceAtTouch(self, x, y, 1);
    if (place != POCKETS_BOX_NO_PLACE) {
        PocketsBox_TouchPlace(self, place);
        return;
    }
    if (x < PBS_BUTTONS_LEFT || x > PBS_BUTTONS_RIGHT || y < PBS_BUTTONS_TOP || y > PBS_BUTTONS_BOTTOM) {
        return;
    }
    if (y >= PBS_CANCEL_TOP) {
        PocketsBox_Cancel(self);
    } else {
        PocketsBox_Confirm(self);
    }
}
CLEAN_AS(func_ov100_0229e17c, PocketsBox_TouchIdle)

/* ---- set-up and frames */

/* func_ov100_0229e208: the wallet's object files loaded; whether they were. */
int PocketsBox_LoadWalletFiles(PocketsBox *self)
{
    return PocketsWallet_LoadObjFiles(pbs_wallet(self));
}
CLEAN_AS(func_ov100_0229e208, PocketsBox_LoadWalletFiles)

/* func_ov100_0229e218: the box's layer (4) loaded from the current heap: its map and tiles
 * 0x1b9-0x238, then by the mode (0x1d-0x20) a palette 3-5 and tiles 0x208-0x238 (none for
 * another mode); then both closing labels, dim. */
void PocketsBox_LoadLayers(PocketsBox *self)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadScreenFromFile(data_ov100_0229ed18, heap, PBS_BOX_LAYER);
    DisplayLayer_LoadCharsFromFile(data_ov100_0229ed3c, heap, PBS_BOX_LAYER, 0x1b9, 0x1b9, 0x238);
    const char *palette = NULL;
    const char *chars = NULL;
    switch (GroupParams_Mode()) {
        case POCKETS_BOX_MODE_1D:
            palette = data_ov100_0229ed5c;
            chars = data_ov100_0229ed74;
            break;
        case POCKETS_BOX_MODE_1E:
            palette = data_ov100_0229ed8c;
            chars = data_ov100_0229eda4;
            break;
        case POCKETS_BOX_MODE_1F:
            palette = data_ov100_0229edbc;
            chars = data_ov100_0229edd4;
            break;
        case POCKETS_BOX_MODE_20:
            palette = data_ov100_0229edec;
            chars = data_ov100_0229ee04;
            break;
    }
    if (palette != NULL) {
        DisplayLayer_LoadPalettesFromFile(palette, heap, PBS_BOX_LAYER, 3, 3, 5);
    }
    if (chars != NULL) {
        DisplayLayer_LoadCharsFromFile(chars, heap, PBS_BOX_LAYER, 0x208, 0x208, 0x238);
    }
    PocketsBox_ShowConfirmLabel(self, 0);
    PocketsBox_ShowCancelLabel(self, 0);
}
CLEAN_AS(func_ov100_0229e218, PocketsBox_LoadLayers)

/* func_ov100_0229e2f4: the wallet's display set up (on screen B). */
void PocketsBox_SetUpWallet(PocketsBox *self)
{
    PocketsWallet_SetUp(pbs_wallet(self), 0);
}
CLEAN_AS(func_ov100_0229e2f4, PocketsBox_SetUpWallet)

/* func_ov100_0229e308: layer 6 at priority 2 and layer 4 at priority 1, both controls reset. */
void PocketsBox_SetUpLayers(void)
{
    DisplayLayer_SetPriority(PBS_POCKETS_LAYER, 2);
    DisplayLayer_SetBgControl(PBS_POCKETS_LAYER, 0, 0, 0);
    DisplayLayer_SetPriority(PBS_BOX_LAYER, 1);
    DisplayLayer_SetBgControl(PBS_BOX_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov100_0229e308, PocketsBox_SetUpLayers)

/* func_ov100_0229e33c: a frame's end: the choice and the wallet updated; the popup, when its
 * update says so, placed. */
void PocketsBox_EndFrame(PocketsBox *self)
{
    PagedChoice_Update(pbs_choice(self));
    PocketsWallet_Update(pbs_wallet(self));
    if (Popup_Update(&self->popup)) {
        PocketsBox_PlacePopup(self);
    }
}
CLEAN_AS(func_ov100_0229e33c, PocketsBox_EndFrame)

/* func_ov100_0229e374: a frame's start: the layer load task ended, the wallet, the grid and the
 * letters begin their frame, the labels closed. */
void PocketsBox_BeginFrame(PocketsBox *self)
{
    PocketsBox_EndLayerTask(self);
    PocketsWallet_BeginFrame(pbs_wallet(self));
    PocketsGrid_BeginFrame(pbs_grid(self));
    PocketsLetters_BeginFrame(pbs_letters(self));
    PocketsBox_CloseLabels(self);
}
CLEAN_AS(func_ov100_0229e374, PocketsBox_BeginFrame)

/* func_ov100_0229e3a8: an interactive frame's end (PocketsBox_EndFrame). */
void PocketsBox_EndInteractiveFrame(PocketsBox *self)
{
    PocketsBox_EndFrame(self);
}
CLEAN_AS(func_ov100_0229e3a8, PocketsBox_EndInteractiveFrame)

/* func_ov100_0229e3b0: an interactive frame's start: PocketsBox_BeginFrame, then the cursor
 * sprite's update through its class (vtable slot 3). */
void PocketsBox_BeginInteractiveFrame(PocketsBox *self)
{
    PocketsBox_BeginFrame(self);
    pbs_call_slot(&self->cursor_sprite, 3);
}
CLEAN_AS(func_ov100_0229e3b0, PocketsBox_BeginInteractiveFrame)

/* func_ov100_0229e3cc: the members torn down: the layer load task ended, the wallet and the
 * grid torn down, the choice dismissed, the labels closed. */
void PocketsBox_Teardown(PocketsBox *self)
{
    PocketsBox_EndLayerTask(self);
    PocketsWallet_Teardown(pbs_wallet(self));
    PocketsGrid_Teardown(pbs_grid(self));
    PagedChoice_Dismiss(pbs_choice(self));
    PocketsBox_CloseLabels(self);
}
CLEAN_AS(func_ov100_0229e3cc, PocketsBox_Teardown)

/* func_ov100_0229e400: the scene set up: no flags; the grid (priority 1), the letters
 * (priority 2) and the wallet (layer 6) set up; no popup place, the glide stopped, nothing
 * held, the cursor at the first pocket; the choice on layer 3 at priority 1; no label in use.
 * The box by the mode: empty (and marked so) for 0x1d and 0x1e, list A for 0x1f, list B for
 * 0x20 (else as it was); copied as the start's; and the pockets saved for a cancel. */
void PocketsBox_Setup(PocketsBox *self)
{
    self->flags = 0;
    PocketsGrid_Init(pbs_grid(self), 1);
    PocketsLetters_Init(pbs_letters(self), 2);
    PocketsWallet_Init(pbs_wallet(self), PBS_POCKETS_LAYER);
    self->popup_place = POCKETS_BOX_NO_PLACE;
    Glide_Stop(&self->glide);
    self->held_kind = POCKETS_BOX_HELD_NONE;
    self->cursor = POCKETS_BOX_POCKETS_FIRST;
    PagedChoice_Init(pbs_choice(self), 3, 1, NULL);
    self->label_count = 0;

    switch (GroupParams_Mode()) {
        case POCKETS_BOX_MODE_1D:
        case POCKETS_BOX_MODE_1E:
            for (int i = 0; i < POCKETS_BOX_SLOTS; i++) {
                self->box[i] = ITEM_CODE_NONE;
            }
            PocketsBox_SetFlags(self, POCKETS_BOX_FLAG_STARTED_EMPTY);
            break;
        case POCKETS_BOX_MODE_1F:
            MI_CpuCopy8(data_021f3a68, self->box, sizeof self->box);
            break;
        case POCKETS_BOX_MODE_20:
            MI_CpuCopy8(data_021f3a86, self->box, sizeof self->box);
            break;
    }
    MI_CpuCopy8(self->box, self->box_start, sizeof self->box);
    Pockets_Save();
}
CLEAN_AS(func_ov100_0229e400, PocketsBox_Setup)

/* ---- the states */

/* func_ov100_0229e4fc (state 6): the pockets' layer wipes out; at its end the layer is hidden
 * (its scroll reset), the scene asks to be deleted (phase 5) and is no longer drawn. The
 * objects follow the wipe. */
void PocketsBox_Layer6WipeOut(PocketsBox *self)
{
    if (MenuScene_StepWipe(pbs_scene(self), PBS_WIPE_SCREEN)) {
        DisplayLayer_HideAndResetScroll(PBS_POCKETS_LAYER);
        MenuScene_SetPhase(pbs_scene(self), 5);
        PocketsBox_ClearFlags(self, POCKETS_BOX_FLAG_DRAWN);
        PocketsBox_ClearFlags(self, POCKETS_BOX_FLAG_OBJECTS_DRAWN);
    } else {
        MenuScene_ScrollWipe(pbs_scene(self), PBS_POCKETS_LAYER, 0, 0);
    }
    self->wipe_y = MenuScene_WipeOffsetY(pbs_scene(self));
}
CLEAN_AS(func_ov100_0229e4fc, PocketsBox_Layer6WipeOut)

/* func_ov100_0229e54c (state 5): the box's layer wipes out; at its end the layer is hidden (its
 * scroll reset), the box no longer drawn, and the pockets' layer starts wiping out on window 2
 * (state 6, run at once). */
void PocketsBox_Layer4WipeOut(PocketsBox *self)
{
    if (MenuScene_StepWipe(pbs_scene(self), PBS_WIPE_SCREEN)) {
        DisplayLayer_HideAndResetScroll(PBS_BOX_LAYER);
        PocketsBox_ClearFlags(self, POCKETS_BOX_FLAG_80);
        MenuScene_StartWipeOnWindow2(pbs_scene(self), 8, 0, 0, PBS_WIPE_MARGIN);
        MenuScene_ScrollWipe(pbs_scene(self), PBS_POCKETS_LAYER, 0, 0);
        MenuScene_SetState(pbs_scene(self), POCKETS_BOX_STATE_LAYER6_WIPE_OUT);
        PocketsBox_Layer6WipeOut(self);
    } else {
        MenuScene_ScrollWipe(pbs_scene(self), PBS_BOX_LAYER, 0, 0);
        self->exit_wipe_y = MenuScene_WipeOffsetY(pbs_scene(self));
    }
}
CLEAN_AS(func_ov100_0229e54c, PocketsBox_Layer4WipeOut)

/* func_ov100_0229e5b8 (state 4): once the scene may leave (PocketsBox_CanLeave): the popup
 * (with its queue) and the cursor sprite hidden, the parent told (mode 0x44, with sound), and
 * the box's layer starts wiping out on window 2 (state 5). */
void PocketsBox_Leave(PocketsBox *self)
{
    if (PocketsBox_CanLeave(self) == 0) {
        return;
    }
    Popup_Hide(&self->popup, 1);
    PocketsBox_HideCursorSprite(self);
    MenuDispatch_SetMode((MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self), PBS_PARENT_MODE_LEAVE, 1);
    MenuScene_StartWipeOnWindow2(pbs_scene(self), 2, 4, 1, PBS_WIPE_MARGIN);
    MenuScene_SetWipeExtent(pbs_scene(self), PBS_WIPE_EXTENT);
    MenuScene_ScrollWipe(pbs_scene(self), PBS_BOX_LAYER, 0, 0);
    self->exit_wipe_y = MenuScene_WipeOffsetY(pbs_scene(self));
    MenuScene_SetState(pbs_scene(self), POCKETS_BOX_STATE_LAYER4_WIPE_OUT);
}
CLEAN_AS(func_ov100_0229e5b8, PocketsBox_Leave)

/* func_ov100_0229e62c (state 3): the box's layer wipes in; at its end the scene runs (phase 2)
 * from the idle sub state of the touch or the keys. */
void PocketsBox_Layer4WipeIn(PocketsBox *self)
{
    if (MenuScene_StepWipeBack(pbs_scene(self), PBS_WIPE_SCREEN)) {
        MenuScene_SetPhase(pbs_scene(self), 2);
        PocketsBox_EndAction(self);
    }
    MenuScene_ScrollWipe(pbs_scene(self), PBS_BOX_LAYER, 0, 0);
    self->exit_wipe_y = MenuScene_WipeOffsetY(pbs_scene(self));
}
CLEAN_AS(func_ov100_0229e62c, PocketsBox_Layer4WipeIn)

/* func_ov100_0229e668 (state 2): the pockets' layer wipes in; at its end the box's layer is
 * loaded, shown and starts wiping in on window 2 (state 3), the box drawn. */
void PocketsBox_Layer6WipeIn(PocketsBox *self)
{
    int done = MenuScene_StepWipeBack(pbs_scene(self), PBS_WIPE_SCREEN);
    MenuScene_ScrollWipe(pbs_scene(self), PBS_POCKETS_LAYER, 0, 0);
    self->wipe_y = MenuScene_WipeOffsetY(pbs_scene(self));
    if (done == 0) {
        return;
    }
    PocketsBox_LoadLayers(self);
    MenuScene_StartWipeCoveredOnWindow2(pbs_scene(self), 2, 0, 1, PBS_WIPE_MARGIN);
    MenuScene_SetWipeExtent(pbs_scene(self), PBS_WIPE_EXTENT);
    PocketsBox_SetFlags(self, POCKETS_BOX_FLAG_80);
    DisplayLayer_Show(PBS_BOX_LAYER);
    MenuScene_ScrollWipe(pbs_scene(self), PBS_BOX_LAYER, 0, 0);
    self->exit_wipe_y = MenuScene_WipeOffsetY(pbs_scene(self));
    MenuScene_SetState(pbs_scene(self), POCKETS_BOX_STATE_LAYER4_WIPE_IN);
}
CLEAN_AS(func_ov100_0229e668, PocketsBox_Layer6WipeIn)

/* func_ov100_0229e6ec (state 1): the wallet's files loaded (the answer unused), the pockets and
 * the box given to the grid, the slots that must be locked locked, the letters loaded and dimmed
 * by states 0-3; the pockets' layer shown and wiping in on window 2 (state 2), the scene and
 * its objects drawn. */
void PocketsBox_LoadPockets(PocketsBox *self)
{
    PocketsBox_LoadWalletFiles(self);
    PocketsGrid_LoadPockets(pbs_grid(self));
    PocketsGrid_SetBox(pbs_grid(self), self->box);
    PocketsBox_LockSlots(self);
    PocketsLetters_LoadPockets(pbs_letters(self));
    PocketsLetters_DimByState(pbs_letters(self), 0xf);
    MenuScene_StartWipeCoveredOnWindow2(pbs_scene(self), 8, 0, 0, PBS_WIPE_MARGIN);
    DisplayLayer_Show(PBS_POCKETS_LAYER);
    MenuScene_ScrollWipe(pbs_scene(self), PBS_POCKETS_LAYER, 0, 0);
    MenuScene_SetState(pbs_scene(self), POCKETS_BOX_STATE_LAYER6_WIPE_IN);
    PocketsBox_SetFlags(self, POCKETS_BOX_FLAG_DRAWN);
    PocketsBox_SetFlags(self, POCKETS_BOX_FLAG_OBJECTS_DRAWN);
    self->wipe_y = MenuScene_WipeOffsetY(pbs_scene(self));
}
CLEAN_AS(func_ov100_0229e6ec, PocketsBox_LoadPockets)

/* func_ov100_0229e77c (state 0): the layers and the wallet set up, then state 1. */
void PocketsBox_StartSetup(PocketsBox *self)
{
    PocketsBox_SetUpLayers();
    PocketsBox_SetUpWallet(self);
    MenuScene_SetState(pbs_scene(self), POCKETS_BOX_STATE_LOAD);
}
CLEAN_AS(func_ov100_0229e77c, PocketsBox_StartSetup)

/* ---- the vtable's slots */

/* func_ov100_0229e798 (vtable slot 0x5c, phase 5): the scene asks to be deleted. Answers 1. */
int PocketsBox_RequestDelete(PocketsBox *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov100_0229e798, PocketsBox_RequestDelete)

/* func_ov100_0229e7a8 (vtable slot 0x58, phase 4): nothing. */
int PocketsBox_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov100_0229e7a8, PocketsBox_Phase4Idle)

/* func_ov100_0229e7ac (vtable slot 0x54, phase 3): nothing. */
int PocketsBox_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov100_0229e7ac, PocketsBox_Phase3Idle)

/* Obj_ov100_0229ecb8::func_ov100_0229e7b0 (vtable slot 0x50, phase 2): a frame of the scene in
 * use: its start, its sub state and its end. Answers 1. */
int PocketsBox_RunInteractive(PocketsBox *self)
{
    PocketsBox_BeginInteractiveFrame(self);
    PocketsBox_RunSubState(self);
    PocketsBox_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov100_0229ecb819func_ov100_0229e7b0Ev, PocketsBox_RunInteractive)

/* Obj_ov100_0229ecb8::func_ov100_0229e7cc: the sub state's function (PocketsBoxSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 0x16; the game reads past the table for others. */
void PocketsBox_RunSubState(PocketsBox *self)
{
    static const MemberPointer *const sub_states[POCKETS_BOX_SUB_STATES] = {
        &data_ov100_0229ec68, &data_ov100_0229ec60, &data_ov100_0229ec58, &data_ov100_0229ec50, &data_ov100_0229ec48,
        &data_ov100_0229ec40, &data_ov100_0229ec38, &data_ov100_0229ec30, &data_ov100_0229ebe8, &data_ov100_0229ec28,
        &data_ov100_0229ec18, &data_ov100_0229ec10, &data_ov100_0229ec78, &data_ov100_0229ec00, &data_ov100_0229ebf8,
        &data_ov100_0229ebf0, &data_ov100_0229ebe0, &data_ov100_0229ec70, &data_ov100_0229ebd8, &data_ov100_0229ec08,
        &data_ov100_0229ebc8, &data_ov100_0229eca0,
    };
    MemberTable_InitOnce(&data_ov100_0229ee24, data_ov100_0229ee60, sub_states, POCKETS_BOX_SUB_STATES);
    MemberPointer_CallVoid(&data_ov100_0229ee60[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov100_0229ecb819func_ov100_0229e7ccEv, PocketsBox_RunSubState)

/* Obj_ov100_0229ecb8::func_ov100_0229e954 (vtable slot 0x4c, phase 1): a frame of the scene's
 * states (PocketsBoxState) between the frame's start and end, through the table of member
 * functions (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 7; the game reads past the table for others. */
int PocketsBox_RunState(PocketsBox *self)
{
    static const MemberPointer *const states[POCKETS_BOX_STATES] = {
        &data_ov100_0229ebc0, &data_ov100_0229eca8, &data_ov100_0229ec20, &data_ov100_0229ec98,
        &data_ov100_0229ec90, &data_ov100_0229ec88, &data_ov100_0229ec80,
    };
    MemberTable_InitOnce(&data_ov100_0229ee20, data_ov100_0229ee28, states, POCKETS_BOX_STATES);
    PocketsBox_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov100_0229ee28[self->base.state], self);
    PocketsBox_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov100_0229ecb819func_ov100_0229e954Ev, PocketsBox_RunState)

/* func_ov100_0229ea10 (vtable slot 0x24): the scene's draw, while it is drawn: the popup
 * (through its class, slot 2), the cursor sprite (with the keys in use), the held item; the box
 * at the exit wipe's y; with the objects drawn, the grid's pockets, the letters and the wallet
 * at the wipe's y. Answers 1. */
int PocketsBox_Draw(PocketsBox *self)
{
    if (PocketsBox_TestFlags(self, POCKETS_BOX_FLAG_DRAWN) == 0) {
        return 1;
    }
    pbs_call_slot(&self->popup, 2);
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    PocketsBox_DrawHeld(self);
    if (PocketsBox_TestFlags(self, POCKETS_BOX_FLAG_80)) {
        PocketsGrid_DrawBox(pbs_grid(self), 0, self->exit_wipe_y);
    }
    if (PocketsBox_TestFlags(self, POCKETS_BOX_FLAG_OBJECTS_DRAWN)) {
        PocketsGrid_DrawPockets(pbs_grid(self), 0, self->wipe_y);
        PocketsLetters_DrawPockets(pbs_letters(self), 0, self->wipe_y);
        PocketsWallet_Draw(pbs_wallet(self), self->wipe_y);
    }
    return 1;
}
CLEAN_AS(func_ov100_0229ea10, PocketsBox_Draw)

/* func_ov100_0229eab0 (vtable slot 0x0c): the scene closes: the parent told and the members
 * torn down. Answers 1. */
int PocketsBox_Close(PocketsBox *self)
{
    MenuDispatch_ChildClosed((MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self));
    PocketsBox_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov100_0229eab0, PocketsBox_Close)

/* func_ov100_0229eacc (vtable slot 0x00): the scene starts: its setup, state 0 and phase 0.
 * Answers 1. */
int PocketsBox_Start(PocketsBox *self)
{
    PocketsBox_Setup(self);
    MenuScene_SetState(pbs_scene(self), POCKETS_BOX_STATE_SETUP);
    MenuScene_SetPhase(pbs_scene(self), 0);
    return 1;
}
CLEAN_AS(func_ov100_0229eacc, PocketsBox_Start)

/* func_ov100_0229eaec: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base, the scene's vtable and its members constructed in order, the two labels by
 * __cxa_vec_ctor. */
PocketsBox *PocketsBox_New(void)
{
    PocketsBox *self = MenuScene_Alloc(sizeof(PocketsBox));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov100_0229ecb8;
    LayerTask_ConstructPair(&self->layer_task);
    PocketsGrid_Construct(pbs_grid(self));
    PocketsLetters_Construct(pbs_letters(self));
    PocketsWallet_Construct(pbs_wallet(self));
    Popup_Construct(&self->popup);
    Glide_Construct(&self->glide);
    Glider0_Construct(&self->cursor_sprite);
    PagedChoice_Construct(pbs_choice(self));
    ErrorMessage_Construct(&self->error);
    __cxa_vec_ctor(self->labels, POCKETS_BOX_LABELS, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070c08,
                   (void (*)(void *))(uintptr_t) func_02070be8);
    return self;
}
CLEAN_AS(func_ov100_0229eaec, PocketsBox_New)
