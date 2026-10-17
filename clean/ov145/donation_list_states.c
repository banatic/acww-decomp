/* The museum donation list of overlay 145 (donation_list.h): its sub states (used by the touch
 * or by the keys), its states (the setup and the wipes), the frames, the files, the vtable's
 * slots and the constructor. */
#include "donation_list.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/dual_cell_sprite.h"
#include "main/oam_buffer.h"
#include "main/rom_file.h"
#include "main/state_flags.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"

/* The scene's vtable; the OBJs of the handle's track (one cell) and of the four tabs (a cell of
 * two OBJs each); the files: "menu/donation/obj.bch", "obj.bpl", "bg0.bch", "bg1.bch",
 * "bg.bpl", "bg_3.bpl", "b_bg.bsc" and "a_bg.bsc". */
extern const u8 data_ov145_0229ae00[];
extern const OamEntry data_ov145_0229ae60[];
extern const OamEntry data_ov145_0229aea0[];
extern const char data_ov145_0229aee0[];
extern const char data_ov145_0229aef8[];
extern const char data_ov145_0229af10[];
extern const char data_ov145_0229af28[];
extern const char data_ov145_0229af40[];
extern const char data_ov145_0229af58[];
extern const char data_ov145_0229af70[];
extern const char data_ov145_0229af88[];

/* The heap the scenes load into (autoload_2/heap.c). */
extern Heap *data_021fbe94;

/* The pad (autoload_2/input.h) and the touch (main's bytes, as ov126 reads them). */
extern PadState data_021fbe40;
#define DONATION_PAD_A 0x0001
#define DONATION_PAD_B 0x0002
extern u8 data_021f6c58; /* the touch's x */
extern u8 data_021f6c54; /* and its y */
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */

/* The tables of member functions (ov004/member_pointer.h): their guards, the tables and the
 * constants they are filled from. */
extern u32 data_ov145_0229afa4; /* the sub states' guard */
extern u32 data_ov145_0229afa8; /* the states' guard */
extern MemberPointer data_ov145_0229afbc[DONATION_STATES];
extern MemberPointer data_ov145_0229afdc[DONATION_SUB_STATES];
extern const MemberPointer data_ov145_0229ad80; /* DonationList_WipeIn */
extern const MemberPointer data_ov145_0229ad88; /* DonationList_FinishClosePress */
extern const MemberPointer data_ov145_0229ad90; /* DonationList_FinishCursorAnim */
extern const MemberPointer data_ov145_0229ada0; /* DonationList_WaitCursorGlide */
extern const MemberPointer data_ov145_0229ada8; /* DonationList_WaitHandleRelease */
extern const MemberPointer data_ov145_0229adb0; /* DonationList_HandleByKeys */
extern const MemberPointer data_ov145_0229adb8; /* DonationList_IdleByKeys */
extern const MemberPointer data_ov145_0229adc0; /* DonationList_TrackTouch */
extern const MemberPointer data_ov145_0229adc8; /* DonationList_DragHandle */
extern const MemberPointer data_ov145_0229add0; /* DonationList_IdleByTouch */
extern const MemberPointer data_ov145_0229add8; /* DonationList_FinishPress */
extern const MemberPointer data_ov145_0229ade0; /* DonationList_StartSetup */
extern const MemberPointer data_ov145_0229ade8; /* DonationList_WipeOut */
extern const MemberPointer data_ov145_0229adf0; /* DonationList_StartWipeOut */

/* The labels' constructor and destructor, handed to __cxa_vec_ctor (so the game's symbols). */
extern void func_02070c08(void *label);
extern void func_02070be8(void *label);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

/* The layers: the frame on 6 (priority 1), the list on 4 (priority 2), the OBJs' "layer" 8. */
#define DONATION_FRAME_LAYER 6
#define DONATION_LIST_LAYER 4
#define DONATION_OBJ_LAYER 8
#define DONATION_LIST_SCROLL_OFFSET 0x18

/* The wipes: on window 2, layers 10 (the frame's and the list's planes), margin 40; the wipe in
 * covered. */
#define DONATION_WIPE_LAYERS 10
#define DONATION_WIPE_MARGIN 40

/* The tab shown first, the panel's layout message, its close button and GroupParams' mode the
 * dispatcher ends with. */
#define DONATION_FIRST_TAB DONATION_TAB_FOSSILS
#define DONATION_PANEL_MESSAGE 0x65
#define DONATION_CLOSE_BUTTON 6
#define DONATION_NO_ITEM 0xfff1

/* The touch areas: the handle's track. */
#define DONATION_TRACK_MIN_X 0xe4
#define DONATION_TRACK_MAX_X 0xec
#define DONATION_TRACK_MIN_Y 0x15
#define DONATION_TRACK_MAX_Y 0x8d

/* The OBJs: drawn on the sub screen at (0x80, the wipe's y + 0x60), priority 1; the tabs in
 * palette 5, the selected one in 7. */
#define DONATION_OBJ_X 0x80
#define DONATION_OBJ_Y 0x60
#define DONATION_TAB_PALETTE 5
#define DONATION_SELECTED_TAB_PALETTE 7
#define DONATION_TAB_OBJS 2

static MenuScene *donation_base(DonationList *self)
{
    return &self->base;
}

static CellLayerSprite *donation_cursor_cells(DonationList *self)
{
    /* The cursor sprite's base is main's cell layer sprite (glide.h). */
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

static Process *donation_parent(DonationList *self)
{
    return Process_GetParent((Process *) (void *) self);
}

/* The handle's function of vtable slot `slot` (2 draws, 3 updates). */
static void donation_handle_virtual(DonationList *self, int slot)
{
    void (*const *vtable)(PushButton *) = (void (*const *)(PushButton *)) self->handle.vtable;
    vtable[slot](&self->handle);
}

/* The cursor sprite's update through its class (vtable slot 3). */
static void donation_update_cursor_sprite(DonationList *self)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) self->cursor_sprite.vtable;
    vtable[3](&self->cursor_sprite);
}

/* func_ov145_0229a310: the scene in use, by the touch when state flag 2 is clear, else by the
 * keys. */
void DonationList_StartInteractive(DonationList *self)
{
    if (StateFlags_IsClear2()) {
        DonationList_UseTouch(self);
    } else {
        DonationList_UseKeys(self);
    }
}
CLEAN_AS(func_ov145_0229a310, DonationList_StartInteractive)

/* func_ov145_0229a330: used by the keys: the cursor on the selected tab, its sprite shown there,
 * the key repeat reset (sub state 3). */
void DonationList_UseKeys(DonationList *self)
{
    self->cursor = self->selected_tab;
    DonationList_ShowCursorSprite(self);
    MenuScene_ResetKeyRepeat(donation_base(self));
    MenuScene_SetSubState(donation_base(self), DONATION_SUB_IDLE_BY_KEYS);
}
CLEAN_AS(func_ov145_0229a330, DonationList_UseKeys)

/* func_ov145_0229a358: used by the touch: the cursor sprite hidden (sub state 0). */
void DonationList_UseTouch(DonationList *self)
{
    DonationList_HideCursorSprite(self);
    MenuScene_SetSubState(donation_base(self), DONATION_SUB_IDLE_BY_TOUCH);
}
CLEAN_AS(func_ov145_0229a358, DonationList_UseTouch)

/* func_ov145_0229a370 (sub state 9): the close button's press played; while it plays, a cursor
 * sprite that is shown follows the button (moved by the press's frame on both axes). Then the
 * sprite is hidden and the states run again (phase 1, state 2: the wipe out). */
void DonationList_FinishClosePress(DonationList *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel)) {
        if (CellLayerSprite_AnimNumber(donation_cursor_cells(self)) != 0) {
            int frame = ButtonPanel_SelectedPressFrame(&self->panel);
            int x = ButtonPanel_ButtonX(&self->panel, -1);
            int y = ButtonPanel_ButtonY(&self->panel, -1);
            Glider_PlaceAt(&self->cursor_sprite, frame + x, frame + y);
        }
    } else {
        DonationList_HideCursorSprite(self);
        MenuScene_SetPhase(donation_base(self), DONATION_PHASE_STATES);
    }
}
CLEAN_AS(func_ov145_0229a370, DonationList_FinishClosePress)

/* func_ov145_0229a3d8 (sub state 8): once the cursor sprite's animation ends, its first of the
 * set and back to the sub state it was started in. */
void DonationList_FinishCursorAnim(DonationList *self)
{
    if (CellLayerSprite_IsDone(donation_cursor_cells(self))) {
        DonationList_ShowCursorFirstOfSet(self);
        MenuScene_SetSubState(donation_base(self), self->return_sub_state);
    }
}
CLEAN_AS(func_ov145_0229a3d8, DonationList_FinishCursorAnim)

/* func_ov145_0229a3fc (sub state 7): once the cursor sprite's press animation ends, the place
 * under the cursor is chosen; a tab (or nothing) goes back to the keys (sub state 3) by the
 * sprite's third animation. */
void DonationList_FinishPress(DonationList *self)
{
    if (CellLayerSprite_IsDone(donation_cursor_cells(self)) == 0) {
        return;
    }
    if (DonationList_Choose(self, self->cursor) != 0) {
        return;
    }
    MenuScene_SetSubState(donation_base(self), DONATION_SUB_IDLE_BY_KEYS);
    DonationList_StartCursorAnim(self);
}
CLEAN_AS(func_ov145_0229a3fc, DonationList_FinishPress)

/* Obj_ov145_0229ae00::func_ov145_0229a430 (sub state 6): once the cursor sprite has stopped,
 * back to the sub state the glide started in, which runs this same frame. */
void DonationList_WaitCursorGlide(DonationList *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(donation_base(self), self->return_sub_state);
        DonationList_RunSubState(self);
    }
}
CLEAN_AS(_ZN18Obj_ov145_0229ae0019func_ov145_0229a430Ev, DonationList_WaitCursorGlide)

/* func_ov145_0229a458 (sub state 5): once the handle's release has played, the handle at rest
 * and back to the keys (sub state 3) by the sprite's third animation. The cursor sprite is put
 * on the handle each frame. */
void DonationList_WaitHandleRelease(DonationList *self)
{
    if (DonationList_HandleReleased(self)) {
        MenuScene_SetSubState(donation_base(self), DONATION_SUB_IDLE_BY_KEYS);
        DonationList_StartCursorAnim(self);
    }
    int x = DonationList_CursorX(self);
    int y = DonationList_CursorY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
}
CLEAN_AS(func_ov145_0229a458, DonationList_WaitHandleRelease)

/* func_ov145_0229a498 (sub state 4): while A is held, up and down move the handle, with the
 * cursor sprite on it; then the handle is released (sub state 5). */
void DonationList_HandleByKeys(DonationList *self)
{
    if (data_021fbe40.held & DONATION_PAD_A) {
        DonationList_MoveHandleByKeys(self);
        int x = DonationList_CursorX(self);
        int y = DonationList_CursorY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
    } else {
        DonationList_ReleaseHandle(self);
        MenuScene_SetSubState(donation_base(self), DONATION_SUB_HANDLE_RELEASE);
    }
}
CLEAN_AS(func_ov145_0229a498, DonationList_HandleByKeys)

/* func_ov145_0229a4e4 (sub state 3): used by the keys. A touch goes over to the touch; a move
 * of the cursor glides its sprite there; A presses the place under it (sub state 7); B hides
 * the sprite and closes. */
void DonationList_IdleByKeys(DonationList *self)
{
    if (MenuScene_TakeTouch(donation_base(self))) {
        DonationList_UseTouch(self);
        return;
    }
    if (DonationList_MoveCursor(self, MenuScene_LatchRepeatedKeys(donation_base(self)))) {
        DonationList_GlideToCursor(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & DONATION_PAD_A) {
        DonationList_StartPress(self);
        return;
    }
    if (pressed & DONATION_PAD_B) {
        DonationList_HideCursorSprite(self);
        DonationList_StartClose(self);
    }
}
CLEAN_AS(func_ov145_0229a4e4, DonationList_IdleByKeys)

/* func_ov145_0229a548 (sub state 2): the track touched: the handle approaches the pen while it
 * is down; then it is released (sub state 0). */
void DonationList_TrackTouch(DonationList *self)
{
    if (data_021fbdd8 != 0) {
        DonationList_MoveHandleTo(self, data_021f6c54, 1);
    } else {
        DonationList_ReleaseHandle(self);
        MenuScene_SetSubState(donation_base(self), DONATION_SUB_IDLE_BY_TOUCH);
    }
}
CLEAN_AS(func_ov145_0229a548, DonationList_TrackTouch)

/* func_ov145_0229a57c (sub state 1): the handle dragged while the pen is down; then it is
 * released (sub state 0). */
void DonationList_DragHandle(DonationList *self)
{
    if (data_021fbdd8 != 0) {
        DonationList_MoveHandleTo(self, data_021f6c54, 0);
    } else {
        DonationList_ReleaseHandle(self);
        MenuScene_SetSubState(donation_base(self), DONATION_SUB_IDLE_BY_TOUCH);
    }
}
CLEAN_AS(func_ov145_0229a57c, DonationList_DragHandle)

/* func_ov145_0229a5b0 (sub state 0): used by the touch. A button goes over to the keys. When
 * the pen goes down: on the close button it closes; on a tab it chooses it; when the list
 * scrolls, on the handle it grabs it (sub state 1), on the track it presses the handle and moves
 * it to the pen (sub state 2). */
void DonationList_IdleByTouch(DonationList *self)
{
    if (MenuScene_TakeButtons(donation_base(self), 1) != 0) {
        DonationList_UseKeys(self);
        return;
    }
    if (data_021fbdd8 == 0 || data_021fbddc == 0) {
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, DONATION_CLOSE_BUTTON) != 0) {
        DonationList_StartClose(self);
        return;
    }
    int x = data_021f6c58;
    int y = data_021f6c54;
    int tab = DonationList_TabAtTouch(self, x, y);
    if (tab != DONATION_NO_TAB) {
        DonationList_Choose(self, (unsigned int) tab);
        return;
    }
    if (self->max_scroll <= 0) {
        return;
    }
    if (DonationList_GrabHandle(self, x, y) != 0) {
        MenuScene_SetSubState(donation_base(self), DONATION_SUB_DRAG_HANDLE);
        return;
    }
    if (x < DONATION_TRACK_MIN_X || x > DONATION_TRACK_MAX_X || y < DONATION_TRACK_MIN_Y || y > DONATION_TRACK_MAX_Y) {
        return;
    }
    PushButton_Press(&self->handle);
    MenuScene_SetSubState(donation_base(self), DONATION_SUB_TRACK_TOUCH);
}
CLEAN_AS(func_ov145_0229a5b0, DonationList_IdleByTouch)

/* func_ov145_0229a678: the panel's text colours, and the OBJs' characters (file 0xc0-0x13f to
 * 0xc0) and palettes (4-9). */
void DonationList_LoadObjFiles(DonationList *self)
{
    ButtonPanel_LoadTextColors(&self->panel);
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadCharsFromFile(data_ov145_0229aee0, heap, DONATION_OBJ_LAYER, 0xc0, 0xc0, 0x13f);
    DisplayLayer_LoadPalettesFromFile(data_ov145_0229aef8, heap, DONATION_OBJ_LAYER, 4, 4, 9);
}
CLEAN_AS(func_ov145_0229a678, DonationList_LoadObjFiles)

/* func_ov145_0229a6c8: the backgrounds' characters (two files) and palettes (1-7) for layer 6;
 * the text's palette, the row patterns and the frame's screen read into the scene; the frame's
 * screen loaded to layer 6. */
void DonationList_LoadBackground(DonationList *self)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadCharsFromFile(data_ov145_0229af10, heap, DONATION_FRAME_LAYER, 0x11, 0x11, 0x63);
    DisplayLayer_LoadCharsFromFile(data_ov145_0229af28, heap, DONATION_FRAME_LAYER, 0x26e, 0x26e, 0x27d);
    DisplayLayer_LoadPalettesFromFile(data_ov145_0229af40, heap, DONATION_FRAME_LAYER, 1, 1, 7);
    RomFile_Read(data_ov145_0229af58, self->palette_file, sizeof(self->palette_file));
    RomFile_Read(data_ov145_0229af70, self->row_screen, sizeof(self->row_screen));
    RomFile_Read(data_ov145_0229af88, self->frame_screen, sizeof(self->frame_screen));
    DisplayLayer_LoadScreen(self->frame_screen, DONATION_FRAME_LAYER, sizeof(self->frame_screen), 0);
}
CLEAN_AS(func_ov145_0229a6c8, DonationList_LoadBackground)

/* func_ov145_0229a778: the sub engine's background mode 0; layer 6 at priority 1 and layer 4 at
 * 2, both with control 0 (size 0, 16 colours, characters at 0). */
void DonationList_SetUpLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(DONATION_FRAME_LAYER, 1);
    DisplayLayer_SetBgControl(DONATION_FRAME_LAYER, 0, 0, 0);
    DisplayLayer_SetPriority(DONATION_LIST_LAYER, 2);
    DisplayLayer_SetBgControl(DONATION_LIST_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov145_0229a778, DonationList_SetUpLayers)

/* func_ov145_0229a7b0: a frame's end: the fade, the scroll, what the flags ask for and the
 * handle's release. */
void DonationList_EndFrame(DonationList *self)
{
    DonationList_StepFade(self);
    DonationList_StepScroll(self);
    DonationList_UploadPending(self);
    PushButton_SettleRelease(&self->handle);
}
CLEAN_AS(func_ov145_0229a7b0, DonationList_EndFrame)

/* func_ov145_0229a7d8: a frame's start: the labels and the panel's texts closed, the three layer
 * tasks ended, the handle updated (its vtable slot 3). */
void DonationList_BeginFrame(DonationList *self)
{
    DonationList_CloseLabels(self);
    ButtonPanel_CloseTexts(&self->panel);
    LayerTask_End(&self->list_task);
    LayerTask_End(&self->frame_task);
    LayerTask_End(&self->palette_task);
    donation_handle_virtual(self, 3);
}
CLEAN_AS(func_ov145_0229a7d8, DonationList_BeginFrame)

/* func_ov145_0229a824: an interactive frame's end. */
void DonationList_EndInteractiveFrame(DonationList *self)
{
    DonationList_EndFrame(self);
}
CLEAN_AS(func_ov145_0229a824, DonationList_EndInteractiveFrame)

/* func_ov145_0229a82c: an interactive frame's start, then the cursor sprite's update. */
void DonationList_BeginInteractiveFrame(DonationList *self)
{
    DonationList_BeginFrame(self);
    donation_update_cursor_sprite(self);
}
CLEAN_AS(func_ov145_0229a82c, DonationList_BeginInteractiveFrame)

/* func_ov145_0229a844: the labels and the panel's texts closed, the layer tasks ended. */
void DonationList_Teardown(DonationList *self)
{
    DonationList_CloseLabels(self);
    ButtonPanel_CloseTexts(&self->panel);
    LayerTask_End(&self->list_task);
    LayerTask_End(&self->frame_task);
    LayerTask_End(&self->palette_task);
}
CLEAN_AS(func_ov145_0229a844, DonationList_Teardown)

/* func_ov145_0229a884: the scene's setup: no flags, tab 0, no row shown, the text colour at
 * full and no fade; the lists gathered from the museum's record (the fossils, the paintings,
 * the fish, the insects) and the handle at rest. */
void DonationList_Setup(DonationList *self)
{
    self->flags = 0;
    self->tab = DONATION_TAB_PAINTINGS;
    for (int i = 0; i < DONATION_ROWS_IN_VIEW; i++) {
        self->shown[i] = DONATION_NO_ITEM;
    }
    self->fade = DONATION_FADE_FULL;
    self->fade_mode = DONATION_FADE_NONE;
    DonationList_CollectFossils(self);
    DonationList_CollectPaintings(self);
    DonationList_CollectFish(self);
    DonationList_CollectInsects(self);
    PushButton_ShowUp(&self->handle);
}
CLEAN_AS(func_ov145_0229a884, DonationList_Setup)

/* func_ov145_0229a8e8: the layers moved with the wipe (the list's by its scroll too), the wipe's
 * y kept and the handle drawn at it. */
void DonationList_FollowWipe(DonationList *self)
{
    MenuScene_ScrollWipe(donation_base(self), DONATION_FRAME_LAYER, 0, 0);
    MenuScene_ScrollWipe(donation_base(self), DONATION_LIST_LAYER, 0, DONATION_LIST_SCROLL_OFFSET - self->scroll);
    self->wipe_y = MenuScene_WipeOffsetY(donation_base(self));
    DonationList_PlaceHandle(self);
}
CLEAN_AS(func_ov145_0229a8e8, DonationList_FollowWipe)

/* func_ov145_0229a928 (state 3): the wipe out; at its end the two layers are hidden and the
 * scene asks to be deleted (phase 5). */
void DonationList_WipeOut(DonationList *self)
{
    if (MenuScene_StepWipe(donation_base(self), 0)) {
        DisplayLayer_HideAndResetScroll(DONATION_FRAME_LAYER);
        DisplayLayer_HideAndResetScroll(DONATION_LIST_LAYER);
        MenuScene_SetPhase(donation_base(self), DONATION_PHASE_DELETE);
    } else {
        DonationList_FollowWipe(self);
    }
}
CLEAN_AS(func_ov145_0229a928, DonationList_WipeOut)

/* func_ov145_0229a958 (state 2): the dispatcher told to end with the backdrop closed (with its
 * sound), and the wipe out started (state 3). */
void DonationList_StartWipeOut(DonationList *self)
{
    MenuDispatch_SetMode((MenuDispatch *) (void *) donation_parent(self), MENU_DISPATCH_MODE_CLOSE, 1);
    MenuScene_StartWipeOnWindow2(donation_base(self), DONATION_WIPE_LAYERS, 0, 0, DONATION_WIPE_MARGIN);
    DonationList_FollowWipe(self);
    MenuScene_SetState(donation_base(self), DONATION_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov145_0229a958, DonationList_StartWipeOut)

/* func_ov145_0229a990 (state 1): the wipe in; at its end the scene is in use (phase 2). */
void DonationList_WipeIn(DonationList *self)
{
    if (MenuScene_StepWipeBack(donation_base(self), 0)) {
        MenuScene_SetPhase(donation_base(self), DONATION_PHASE_INTERACTIVE);
        DonationList_StartInteractive(self);
    }
    DonationList_FollowWipe(self);
}
CLEAN_AS(func_ov145_0229a990, DonationList_WipeIn)

/* func_ov145_0229a9b8 (state 0): the layers and the files; the fossils' tab shown and selected
 * (`tab` made 4 first so that it changes); the covered wipe in started with both layers shown;
 * the scene drawn, the panel in layout 5 with message 0x65, then state 1. */
void DonationList_StartSetup(DonationList *self)
{
    DonationList_SetUpLayers();
    DonationList_LoadBackground(self);
    self->tab = DONATION_TABS;
    DonationList_ShowTab(self, DONATION_FIRST_TAB);
    self->selected_tab = DONATION_FIRST_TAB;
    DonationList_LoadObjFiles(self);
    MenuScene_StartWipeCoveredOnWindow2(donation_base(self), DONATION_WIPE_LAYERS, 4, 0, DONATION_WIPE_MARGIN);
    DisplayLayer_Show(DONATION_FRAME_LAYER);
    DisplayLayer_Show(DONATION_LIST_LAYER);
    DonationList_FollowWipe(self);
    DonationList_SetFlags(self, DONATION_FLAG_DRAWN);
    ButtonPanel_SetLayout5(&self->panel, DONATION_PANEL_MESSAGE);
    MenuScene_SetState(donation_base(self), DONATION_STATE_WIPE_IN);
}
CLEAN_AS(func_ov145_0229a9b8, DonationList_StartSetup)

/* func_ov145_0229aa30 (vtable slot 0x5c, phase 5): the scene asks to be deleted. Answers 1. */
int DonationList_RequestDelete(DonationList *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov145_0229aa30, DonationList_RequestDelete)

/* func_ov145_0229aa40 (vtable slot 0x58, phase 4): nothing. */
int DonationList_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov145_0229aa40, DonationList_Phase4Idle)

/* func_ov145_0229aa44 (vtable slot 0x54, phase 3): nothing. */
int DonationList_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov145_0229aa44, DonationList_Phase3Idle)

/* Obj_ov145_0229ae00::func_ov145_0229aa48 (vtable slot 0x50, phase 2): a frame of the scene in
 * use: its start, its sub state and its end. Answers 1. */
int DonationList_RunInteractive(DonationList *self)
{
    DonationList_BeginInteractiveFrame(self);
    DonationList_RunSubState(self);
    DonationList_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov145_0229ae0019func_ov145_0229aa48Ev, DonationList_RunInteractive)

/* Obj_ov145_0229ae00::func_ov145_0229aa64: the sub state's function (DonationListSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 10; the game reads past the table for others. */
void DonationList_RunSubState(DonationList *self)
{
    static const MemberPointer *const sub_states[DONATION_SUB_STATES] = {
        &data_ov145_0229add0, &data_ov145_0229adc8, &data_ov145_0229adc0, &data_ov145_0229adb8, &data_ov145_0229adb0,
        &data_ov145_0229ada8, &data_ov145_0229ada0, &data_ov145_0229add8, &data_ov145_0229ad90, &data_ov145_0229ad88,
    };
    MemberTable_InitOnce(&data_ov145_0229afa4, data_ov145_0229afdc, sub_states, DONATION_SUB_STATES);
    MemberPointer_CallVoid(&data_ov145_0229afdc[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov145_0229ae0019func_ov145_0229aa64Ev, DonationList_RunSubState)

/* func_ov145_0229ab3c (vtable slot 0x4c, phase 1): a frame of the scene's states
 * (DonationListState) between the frame's start and end, through the table of member functions
 * (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 4; the game reads past the table for others. */
int DonationList_RunState(DonationList *self)
{
    static const MemberPointer *const states[DONATION_STATES] = {
        &data_ov145_0229ade0,
        &data_ov145_0229ad80,
        &data_ov145_0229adf0,
        &data_ov145_0229ade8,
    };
    MemberTable_InitOnce(&data_ov145_0229afa8, data_ov145_0229afbc, states, DONATION_STATES);
    DonationList_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov145_0229afbc[self->base.state], self);
    DonationList_EndFrame(self);
    return 1;
}
CLEAN_AS(func_ov145_0229ab3c, DonationList_RunState)

/* func_ov145_0229abd0 (vtable slot 0x24): the scene's draw. The cursor sprite (with the keys in
 * use); then, while the scene is drawn, the panel, and at the wipe's y the handle and its track
 * (when the list scrolls) and the four tabs, the selected one in its own palette. Answers 0
 * when the scene is not drawn, else 1. */
int DonationList_Draw(DonationList *self)
{
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    if (DonationList_TestFlags(self, DONATION_FLAG_DRAWN) == 0) {
        return 0;
    }
    ButtonPanel_Draw(&self->panel, MenuScene_WipeOffsetY(donation_base(self)));
    int y = self->wipe_y + DONATION_OBJ_Y;
    if (self->max_scroll > 0) {
        donation_handle_virtual(self, 2);
        OamBuffer_DrawCell(1, data_ov145_0229ae60, DONATION_OBJ_X, y, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
    const OamEntry *tab_objs = data_ov145_0229aea0;
    for (int tab = 0; tab < DONATION_TABS; tab++) {
        int palette = tab == self->selected_tab ? DONATION_SELECTED_TAB_PALETTE : DONATION_TAB_PALETTE;
        OamBuffer_DrawCell(1, tab_objs, DONATION_OBJ_X, y, palette, 1, 0x1000, 0x1000, 0, -1, 0, 0);
        tab_objs += DONATION_TAB_OBJS;
    }
    return 1;
}
CLEAN_AS(func_ov145_0229abd0, DonationList_Draw)

/* func_ov145_0229acac (vtable slot 0x0c): the scene ends: the parent told and the members torn
 * down. Answers 1. */
int DonationList_End(DonationList *self)
{
    MenuDispatch_ChildClosed((MenuDispatch *) (void *) donation_parent(self));
    DonationList_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov145_0229acac, DonationList_End)

/* func_ov145_0229acc8 (vtable slot 0x00): the scene starts: its setup, state 0 (written
 * directly) and phase 0. Answers 1. */
int DonationList_Start(DonationList *self)
{
    DonationList_Setup(self);
    self->base.state = DONATION_STATE_START_SETUP;
    MenuScene_SetPhase(donation_base(self), DONATION_PHASE_WAIT);
    return 1;
}
CLEAN_AS(func_ov145_0229acc8, DonationList_Start)

/* func_ov145_0229ace8 (named by the profile at 0x0229ad98): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order, the labels by __cxa_vec_ctor. */
DonationList *DonationList_New(void)
{
    DonationList *self = MenuScene_Alloc(sizeof(DonationList));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov145_0229ae00;
    Glider0_Construct(&self->cursor_sprite);
    PushButton_Construct(&self->handle);
    ButtonPanel_Construct(&self->panel);
    __cxa_vec_ctor(self->labels, DONATION_LABELS, sizeof(TextLabel), func_02070c08, func_02070be8);
    LayerTask_Construct(&self->list_task);
    LayerTask_Construct(&self->frame_task);
    LayerTask_Construct(&self->palette_task);
    return self;
}
CLEAN_AS(func_ov145_0229ace8, DonationList_New)
