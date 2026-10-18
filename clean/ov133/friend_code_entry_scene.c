/* The friend code entry scene of overlay 133 (friend_code_entry.h): the sub states of the input
 * (FriendCodeEntrySubState), the screens and the title, the frames, the states
 * (FriendCodeEntryState), the vtable's slots and the constructor. */
#include "autoload_2/input.h"
#include "autoload_2/network.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "friend_code_entry.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/group_params.h"
#include "main/oam_buffer.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/rom_file.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov004/member_pointer.h"
#include "ov090/menu_tabs.h"
#include "ov130/bank_pad.h"

/* The scene's vtable and files: "menu/bank/g0_bg.bsc" (the code's row) and "menu/bank/g1_bg.bsc"
 * (the keypad); the text cursor's cell. */
extern const u8 data_ov133_0229c908[];
extern const char data_ov133_0229c968[];
extern const char data_ov133_0229c97c[];
extern const OamEntry data_ov133_0229c868[];

/* The pad (autoload_2/input.c) and the pen (down, and gone down or up this frame; its place). */
extern PadState data_021fbe40;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58, data_021f6c54;
#define FRIEND_CODE_PAD_A 0x0001
#define FRIEND_CODE_PAD_B 0x0002
#define FRIEND_CODE_PAD_START 0x0008

/* The label's constructor and destructor, handed to __cxa_vec_ctor (the game's symbols). */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern TextLabel *func_02070c08(TextLabel *label);
extern TextLabel *func_02070be8(TextLabel *label);

/* The title's message, and the panel's layout's. */
#define FRIEND_CODE_TITLE_MESSAGE 0xd7
#define FRIEND_CODE_PANEL_MESSAGE 0x65

/* The wipes: on window 2, layers 2 and 8, margin 0x30. */
#define FRIEND_CODE_WIPE_LAYERS 0x0a
#define FRIEND_CODE_WIPE_MARGIN 0x30

/* The layers of the keypad's screen and the code's. */
#define FRIEND_CODE_KEYPAD_LAYER 4
#define FRIEND_CODE_CODE_LAYER 6

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables and their
 * constants. */
extern u32 data_ov133_0229c9a0; /* the states' guard */
extern u32 data_ov133_0229c9a4; /* the sub states' guard */
extern MemberPointer data_ov133_0229c9a8[FRIEND_CODE_STATES];
extern MemberPointer data_ov133_0229c9d0[FRIEND_CODE_SUB_STATES];
extern const MemberPointer data_ov133_0229c860, data_ov133_0229c870, data_ov133_0229c878, data_ov133_0229c888,
    data_ov133_0229c890, data_ov133_0229c898, data_ov133_0229c8a0, data_ov133_0229c8a8, data_ov133_0229c8b0,
    data_ov133_0229c8b8, data_ov133_0229c8c0, data_ov133_0229c8c8, data_ov133_0229c8d0, data_ov133_0229c8d8,
    data_ov133_0229c8e0, data_ov133_0229c8e8, data_ov133_0229c8f0, data_ov133_0229c8f8;

static MenuScene *friend_code_scene_of(FriendCodeEntry *self)
{
    return &self->base;
}

static MenuTabs *friend_code_menu(FriendCodeEntry *self)
{
    return (MenuTabs *) (void *) Process_GetParent((Process *) (void *) self);
}

static CellLayerSprite *friend_code_pointer_cells(FriendCodeEntry *self)
{
    return (CellLayerSprite *) (void *) &self->pointer;
}

/* The pointer sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void friend_code_scene_update_pointer(Glider *pointer)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) pointer->vtable;
    vtable[3](pointer);
}

/* The pointer put at its key at once. */
static void friend_code_place_pointer_at_key(FriendCodeEntry *self)
{
    int x = FriendCodeEntry_PointerX(self);
    int y = FriendCodeEntry_PointerY(self);
    Glider_PlaceAt(&self->pointer, x, y);
}

/* Layers 4 and 6 scrolled with the wipe, and the wipe's y kept. */
static void friend_code_scroll_with_wipe(FriendCodeEntry *self)
{
    MenuScene_ScrollWipe(friend_code_scene_of(self), FRIEND_CODE_KEYPAD_LAYER, 0, 0);
    MenuScene_ScrollWipe(friend_code_scene_of(self), FRIEND_CODE_CODE_LAYER, 0, 0);
    self->wipe_y = MenuScene_WipeOffsetY(friend_code_scene_of(self));
}

/* func_ov133_0229bc08 (sub state 12): the friend handed to the Wi-Fi connection again; once it
 * took it, the scene wipes out after the button's press (sub state 10). */
void FriendCodeEntry_RetrySetFriend(FriendCodeEntry *self)
{
    WifiFriend *friend = FriendCodeEntry_Friend(self);
    int index = GroupParams_Arg();
    WifiFriendData *data = WifiFriendData_GetData(WifiFriend_GetFriendData(friend));
    if (Wfc_SetFriend(index, data)) {
        MenuScene_SetSubState(friend_code_scene_of(self), FRIEND_CODE_SUB_BUTTON_PRESS);
    }
}
CLEAN_AS(func_ov133_0229bc08, FriendCodeEntry_RetrySetFriend)

/* func_ov133_0229bc40 (sub state 11): once the error message closes, back to the input. */
void FriendCodeEntry_WaitError(FriendCodeEntry *self)
{
    if (ErrorMessage_Update(&self->error, 1)) {
        FriendCodeEntry_Resume(self);
    }
}
CLEAN_AS(func_ov133_0229bc40, FriendCodeEntry_WaitError)

/* func_ov133_0229bc64 (sub state 10): while the panel's selected button is pressed, the pointer
 * (when it shows) follows the press; once it is over, the pointer hidden and the states run
 * (phase 1, state 3: the wipe out). */
void FriendCodeEntry_FollowButtonPress(FriendCodeEntry *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel)) {
        if (CellLayerSprite_AnimNumber(friend_code_pointer_cells(self)) != 0) {
            int frame = ButtonPanel_SelectedPressFrame(&self->panel);
            int x = ButtonPanel_ButtonX(&self->panel, -1);
            int y = ButtonPanel_ButtonY(&self->panel, -1);
            Glider_PlaceAt(&self->pointer, frame + (x - 6), frame + y);
        }
    } else {
        FriendCodeEntry_HidePointer(self);
        MenuScene_SetPhase(friend_code_scene_of(self), FRIEND_CODE_PHASE_STATES);
    }
}
CLEAN_AS(func_ov133_0229bc64, FriendCodeEntry_FollowButtonPress)

/* func_ov133_0229bcd4 (sub state 9): with A held at the code's row, the d-pad moves the mark's
 * end; once A is let go, back to the keys (sub state 3) with the pointer pressed (sub state 6). */
void FriendCodeEntry_MarkByKeys(FriendCodeEntry *self)
{
    if ((data_021fbe40.held & FRIEND_CODE_PAD_A) == 0) {
        MenuScene_SetSubState(friend_code_scene_of(self), FRIEND_CODE_SUB_KEYS);
        FriendCodeEntry_PressPointer(self);
    } else if (FriendCodeEntry_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(friend_code_scene_of(self)))) {
        FriendCodeEntry_MarkTo(self, self->position);
    }
}
CLEAN_AS(func_ov133_0229bcd4, FriendCodeEntry_MarkByKeys)

/* func_ov133_0229bd18 (sub state 8): while B is held, the delete repeats (the pointer following
 * the cursor at the code's row); once B is let go, back to the keys (sub state 3). */
void FriendCodeEntry_DeleteHeld(FriendCodeEntry *self)
{
    if ((data_021fbe40.held & FRIEND_CODE_PAD_B) == 0) {
        FriendCodeEntry_StopRepeat(self);
        MenuScene_SetSubState(friend_code_scene_of(self), FRIEND_CODE_SUB_KEYS);
    } else if (FriendCodeEntry_RepeatDue(self)) {
        if (FriendCodeEntry_DeleteBack(self, 1) && self->key == FRIEND_CODE_KEY_CODE) {
            friend_code_place_pointer_at_key(self);
        }
    }
}
CLEAN_AS(func_ov133_0229bd18, FriendCodeEntry_DeleteHeld)

/* func_ov133_0229bd80 (sub state 7): while A is held, the key's action repeats; once A is let
 * go, back to the keys (sub state 3) with the pointer pressed (sub state 6). */
void FriendCodeEntry_KeyHeld(FriendCodeEntry *self)
{
    if ((data_021fbe40.held & FRIEND_CODE_PAD_A) == 0) {
        FriendCodeEntry_StopRepeat(self);
        MenuScene_SetSubState(friend_code_scene_of(self), FRIEND_CODE_SUB_KEYS);
        FriendCodeEntry_PressPointer(self);
    } else if (FriendCodeEntry_RepeatDue(self)) {
        FriendCodeEntry_UseKey(self, 0);
    }
}
CLEAN_AS(func_ov133_0229bd80, FriendCodeEntry_KeyHeld)

/* func_ov133_0229bdc0 (sub state 6): once the pointer's press is over, it is shown again (sub
 * state 3). */
void FriendCodeEntry_WaitPointerPress(FriendCodeEntry *self)
{
    if (CellLayerSprite_IsDone(friend_code_pointer_cells(self)) != 0) {
        FriendCodeEntry_ShowPointer(self);
        MenuScene_SetSubState(friend_code_scene_of(self), FRIEND_CODE_SUB_KEYS);
    }
}
CLEAN_AS(func_ov133_0229bdc0, FriendCodeEntry_WaitPointerPress)

/* func_ov133_0229bde8 (sub state 5): once the pointer's press is over, the key pressed; unless
 * that went on elsewhere (answer 1) the pointer is pressed again (sub state 6). */
void FriendCodeEntry_PressWhenDone(FriendCodeEntry *self)
{
    if (CellLayerSprite_IsDone(friend_code_pointer_cells(self)) != 0) {
        if (FriendCodeEntry_PressSelected(self) == 1) {
            return;
        }
        FriendCodeEntry_PressPointer(self);
    }
}
CLEAN_AS(func_ov133_0229bde8, FriendCodeEntry_PressWhenDone)

/* func_ov133_0229be20 (sub state 4): once the pointer stops, the sub state kept is run again,
 * this frame (with the menu close's check). */
void FriendCodeEntry_WaitPointerGlide(FriendCodeEntry *self)
{
    if (Glider_IsMoving(&self->pointer) == 0) {
        MenuScene_SetSubState(friend_code_scene_of(self), self->return_sub_state);
        FriendCodeEntry_RunSubState(self);
    }
}
CLEAN_AS(func_ov133_0229be20, FriendCodeEntry_WaitPointerGlide)

/* func_ov133_0229be4c (sub state 3): the input by the keys. A touch goes on by touch. A move of
 * the pointer's key glides it there. A presses at the key. B deletes (repeating while held, sub
 * state 8) or, with nothing to delete, cancels. START confirms when OK is enabled. */
void FriendCodeEntry_BrowseByKeys(FriendCodeEntry *self)
{
    if (MenuScene_TakeTouch(friend_code_scene_of(self))) {
        FriendCodeEntry_ResumeByTouch(self);
        return;
    }
    if (FriendCodeEntry_MoveKey(self, (int) MenuScene_LatchRepeatedKeys(friend_code_scene_of(self)))) {
        FriendCodeEntry_GlidePointer(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if ((pressed & FRIEND_CODE_PAD_A) != 0) {
        FriendCodeEntry_PressAtKey(self);
        return;
    }
    if ((pressed & FRIEND_CODE_PAD_B) != 0) {
        if (FriendCodeEntry_DeleteBack(self, 0)) {
            self->repeat = 13;
            MenuScene_SetSubState(friend_code_scene_of(self), FRIEND_CODE_SUB_DELETE_HELD);
            if (self->key == FRIEND_CODE_KEY_CODE) {
                friend_code_place_pointer_at_key(self);
            }
        } else {
            FriendCodeEntry_Cancel(self);
            FriendCodeEntry_HidePointer(self);
        }
        return;
    }
    if ((pressed & FRIEND_CODE_PAD_START) != 0) {
        if (ButtonPanel_HasSpriteFlag4(&self->panel, FRIEND_CODE_BUTTON_OK) == 0) {
            FriendCodeEntry_Confirm(self);
            FriendCodeEntry_HidePointer(self);
        }
    }
}
CLEAN_AS(func_ov133_0229be4c, FriendCodeEntry_BrowseByKeys)

/* func_ov133_0229bf24 (sub state 2): while the pen is down, the mark's end follows it along the
 * code's row; once it is up, back to the input by touch (sub state 0). */
void FriendCodeEntry_TouchMark(FriendCodeEntry *self)
{
    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(friend_code_scene_of(self), FRIEND_CODE_SUB_TOUCH);
    } else {
        FriendCodeEntry_MarkTo(self, FriendCodeEntry_PositionAtTouch(self));
    }
}
CLEAN_AS(func_ov133_0229bf24, FriendCodeEntry_TouchMark)

/* func_ov133_0229bf54 (sub state 1): while the pen is down, the touched key's action repeats;
 * once it is up, back to the input by touch (sub state 0). */
void FriendCodeEntry_TouchKeyHeld(FriendCodeEntry *self)
{
    if (data_021fbdd8 == 0) {
        FriendCodeEntry_StopRepeat(self);
        MenuScene_SetSubState(friend_code_scene_of(self), FRIEND_CODE_SUB_TOUCH);
    } else if (FriendCodeEntry_RepeatDue(self)) {
        FriendCodeEntry_UseKey(self, 0);
    }
}
CLEAN_AS(func_ov133_0229bf54, FriendCodeEntry_TouchKeyHeld)

/* func_ov133_0229bf88 (sub state 0): the input by touch. A button goes on by the keys. A touch
 * that went down this frame on OK (when enabled) confirms, on Back cancels; on the code's row it
 * puts the cursor there and drags a mark (sub state 2); on a key it presses it (repeating while
 * held, sub state 1). */
void FriendCodeEntry_BrowseByTouch(FriendCodeEntry *self)
{
    if (MenuScene_TakeButtons(friend_code_scene_of(self), 1)) {
        FriendCodeEntry_ResumeByKeys(self);
        return;
    }
    if (data_021fbdd8 == 0 || data_021fbddc == 0) {
        return;
    }
    if (ButtonPanel_HasSpriteFlag4(&self->panel, FRIEND_CODE_BUTTON_OK) == 0 &&
        ButtonPanel_IsTouched(&self->panel, FRIEND_CODE_BUTTON_OK)) {
        FriendCodeEntry_Confirm(self);
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, FRIEND_CODE_BUTTON_BACK)) {
        FriendCodeEntry_Cancel(self);
        return;
    }
    int key = FriendCodeEntry_KeyAtTouch(self, data_021f6c58, data_021f6c54);
    if (key == FRIEND_CODE_KEY_CODE) {
        FriendCodeEntry_SetCursor(self, (u8) FriendCodeEntry_PositionAtTouch(self));
        MenuScene_SetSubState(friend_code_scene_of(self), FRIEND_CODE_SUB_TOUCH_MARK);
    } else if (key != FRIEND_CODE_KEY_NONE) {
        if (FriendCodeEntry_PressKey(self)) {
            MenuScene_SetSubState(friend_code_scene_of(self), FRIEND_CODE_SUB_TOUCH_KEY_HELD);
        }
    }
}
CLEAN_AS(func_ov133_0229bf88, FriendCodeEntry_BrowseByTouch)

/* func_ov133_0229c050: overlay 130's graphics (7) loaded and the title opened: message 0xd7 in
 * the label, its box in style 8, shown centred; the panel's text colours. */
void FriendCodeEntry_OpenTitle(FriendCodeEntry *self)
{
    BankPad_LoadPicture(7);
    TextLabel *label = FriendCodeEntry_NextLabel(self);
    TextLabel_LoadMenuMessage((int) (uintptr_t) label, (char) FRIEND_CODE_TITLE_MESSAGE);
    TextLabel_OpenStyledBox2(label, 8, 0x14c, 0xe, 0xf, 0, 0);
    TextLabel_Show(label, 1, 0);
    ButtonPanel_LoadTextColors(&self->panel);
}
CLEAN_AS(func_ov133_0229c050, FriendCodeEntry_OpenTitle)

/* func_ov133_0229c0a4: overlay 130's graphics (4) loaded, the two screens read, the friend's
 * code loaded into them; both to be loaded to their layers. */
void FriendCodeEntry_LoadScreens(FriendCodeEntry *self)
{
    BankPad_LoadBackground(4);
    RomFile_Read(data_ov133_0229c968, self->code_screen, sizeof(self->code_screen));
    RomFile_Read(data_ov133_0229c97c, self->keypad_screen, sizeof(self->keypad_screen));
    FriendCodeEntry_LoadCode(self);
    FriendCodeEntry_SetFlags(self, FRIEND_CODE_FLAG_KEYPAD_DIRTY);
    FriendCodeEntry_SetFlags(self, FRIEND_CODE_FLAG_CODE_DIRTY);
}
CLEAN_AS(func_ov133_0229c0a4, FriendCodeEntry_LoadScreens)

/* func_ov133_0229c0f8: layers 4 and 6 at priority 2, each with its control reset. */
void FriendCodeEntry_SetUpLayers(void)
{
    DisplayLayer_SetPriority(FRIEND_CODE_KEYPAD_LAYER, 2);
    DisplayLayer_SetPriority(FRIEND_CODE_CODE_LAYER, 2);
    DisplayLayer_SetBgControl(FRIEND_CODE_KEYPAD_LAYER, 0, 0, 0);
    DisplayLayer_SetBgControl(FRIEND_CODE_CODE_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov133_0229c0f8, FriendCodeEntry_SetUpLayers)

/* func_ov133_0229c12c */
void FriendCodeEntry_EndInteractiveFrame(FriendCodeEntry *self)
{
    FriendCodeEntry_EndFrame(self);
}
CLEAN_AS(func_ov133_0229c12c, FriendCodeEntry_EndInteractiveFrame)

/* func_ov133_0229c134: the frame's start, then the pointer updated. */
void FriendCodeEntry_BeginInteractiveFrame(FriendCodeEntry *self)
{
    FriendCodeEntry_BeginFrame(self);
    friend_code_scene_update_pointer(&self->pointer);
}
CLEAN_AS(func_ov133_0229c134, FriendCodeEntry_BeginInteractiveFrame)

/* func_ov133_0229c150: the frame's end: the screens updated. */
void FriendCodeEntry_EndFrame(FriendCodeEntry *self)
{
    FriendCodeEntry_UpdateScreens(self);
}
CLEAN_AS(func_ov133_0229c150, FriendCodeEntry_EndFrame)

/* func_ov133_0229c158: the frame's start: the screens' tasks ended, the label and the panel's
 * texts closed; the lit key's time counted down, and at its end the key unlit (or kept lit one
 * more frame while it repeats); the blink counted. */
void FriendCodeEntry_BeginFrame(FriendCodeEntry *self)
{
    LayerTask_End(&self->tasks[0]);
    LayerTask_End(&self->tasks[1]);
    FriendCodeEntry_CloseLabels(self);
    ButtonPanel_CloseTexts(&self->panel);
    if (self->lit_frames != 0) {
        self->lit_frames--;
        if (self->lit_frames == 0) {
            if (self->repeat != 0) {
                self->lit_frames = 1;
            } else {
                FriendCodeEntry_UnlightKey(self, self->lit_key);
            }
        }
    }
    self->blink++;
}
CLEAN_AS(func_ov133_0229c158, FriendCodeEntry_BeginFrame)

/* func_ov133_0229c1dc: the members torn down: the screens' tasks ended, the label and the
 * panel's texts closed. */
void FriendCodeEntry_Teardown(FriendCodeEntry *self)
{
    LayerTask_End(&self->tasks[0]);
    LayerTask_End(&self->tasks[1]);
    FriendCodeEntry_CloseLabels(self);
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov133_0229c1dc, FriendCodeEntry_Teardown)

/* func_ov133_0229c210: the setup: no label nor flags, the pointer at the clear key, nothing lit
 * nor repeating; sound byte 0x71 cleared when the current player's byte 0x1c is 0, else set. */
void FriendCodeEntry_Setup(FriendCodeEntry *self)
{
    self->label_count = 0;
    self->flags = 0;
    self->key = FRIEND_CODE_KEY_CLEAR;
    self->lit_frames = 0;
    self->repeat = 0;
    u8 *record = PlayerRecords_Current();
    if (record != NULL) {
        if (PlayerId_Byte1c((const s8 *) (void *) PlayerRecord_Player(record)) == 0) {
            SoundSys_SetByte71(0);
            return;
        }
    }
    SoundSys_SetByte71(1);
}
CLEAN_AS(func_ov133_0229c210, FriendCodeEntry_Setup)

/* func_ov133_0229c25c (state 4): the wipe out stepped; at its end layers 4 and 6 hidden, the
 * scene no longer drawn and deleted (phase 5); before, the layers follow it. */
void FriendCodeEntry_WipeOut(FriendCodeEntry *self)
{
    if (MenuScene_StepWipe(friend_code_scene_of(self), 0)) {
        DisplayLayer_HideAndResetScroll(FRIEND_CODE_KEYPAD_LAYER);
        DisplayLayer_HideAndResetScroll(FRIEND_CODE_CODE_LAYER);
        FriendCodeEntry_ClearFlags(self, FRIEND_CODE_FLAG_DRAWN);
        MenuScene_SetPhase(friend_code_scene_of(self), FRIEND_CODE_PHASE_END);
    } else {
        friend_code_scroll_with_wipe(self);
    }
}
CLEAN_AS(func_ov133_0229c25c, FriendCodeEntry_WipeOut)

/* func_ov133_0229c2b0 (state 3): the pointer hidden, the wipe out started on window 2 and
 * followed by the layers; state 4. */
void FriendCodeEntry_StartWipeOut(FriendCodeEntry *self)
{
    FriendCodeEntry_HidePointer(self);
    MenuScene_StartWipeOnWindow2(friend_code_scene_of(self), FRIEND_CODE_WIPE_LAYERS, 0, 0, FRIEND_CODE_WIPE_MARGIN);
    MenuScene_ScrollWipe(friend_code_scene_of(self), FRIEND_CODE_KEYPAD_LAYER, 0, 0);
    MenuScene_ScrollWipe(friend_code_scene_of(self), FRIEND_CODE_CODE_LAYER, 0, 0);
    MenuScene_SetState(friend_code_scene_of(self), FRIEND_CODE_STATE_WIPE_OUT);
    self->wipe_y = MenuScene_WipeOffsetY(friend_code_scene_of(self));
}
CLEAN_AS(func_ov133_0229c2b0, FriendCodeEntry_StartWipeOut)

/* func_ov133_0229c2fc (state 2): the wipe in stepped; at its end the scene goes interactive
 * (phase 2) on the input. The layers follow the wipe. */
void FriendCodeEntry_WipeIn(FriendCodeEntry *self)
{
    if (MenuScene_StepWipeBack(friend_code_scene_of(self), 0)) {
        MenuScene_SetPhase(friend_code_scene_of(self), FRIEND_CODE_PHASE_INTERACTIVE);
        FriendCodeEntry_Resume(self);
    }
    friend_code_scroll_with_wipe(self);
}
CLEAN_AS(func_ov133_0229c2fc, FriendCodeEntry_WipeIn)

/* func_ov133_0229c340 (state 1): the wipe in started covered on window 2, layers 4 and 6 shown
 * and following it, the scene drawn; state 2. */
void FriendCodeEntry_StartWipeIn(FriendCodeEntry *self)
{
    MenuScene_StartWipeCoveredOnWindow2(friend_code_scene_of(self), FRIEND_CODE_WIPE_LAYERS, 0, 0, FRIEND_CODE_WIPE_MARGIN);
    DisplayLayer_Show(FRIEND_CODE_KEYPAD_LAYER);
    MenuScene_ScrollWipe(friend_code_scene_of(self), FRIEND_CODE_KEYPAD_LAYER, 0, 0);
    DisplayLayer_Show(FRIEND_CODE_CODE_LAYER);
    MenuScene_ScrollWipe(friend_code_scene_of(self), FRIEND_CODE_CODE_LAYER, 0, 0);
    FriendCodeEntry_SetFlags(self, FRIEND_CODE_FLAG_DRAWN);
    self->wipe_y = MenuScene_WipeOffsetY(friend_code_scene_of(self));
    MenuScene_SetState(friend_code_scene_of(self), FRIEND_CODE_STATE_WIPE_IN);
}
CLEAN_AS(func_ov133_0229c340, FriendCodeEntry_StartWipeIn)

/* func_ov133_0229c39c (state 0): the layers set up, the screens and the title loaded, the panel
 * in layout 6 with message 0x65; state 1, run at once. */
void FriendCodeEntry_Load(FriendCodeEntry *self)
{
    FriendCodeEntry_SetUpLayers();
    FriendCodeEntry_LoadScreens(self);
    FriendCodeEntry_OpenTitle(self);
    MenuScene_SetState(friend_code_scene_of(self), FRIEND_CODE_STATE_START_WIPE_IN);
    ButtonPanel_SetLayout6(&self->panel, FRIEND_CODE_PANEL_MESSAGE);
    FriendCodeEntry_StartWipeIn(self);
}
CLEAN_AS(func_ov133_0229c39c, FriendCodeEntry_Load)

/* func_ov133_0229c3d4: overlay 90's menu switched to `tab` (its low byte). Answers 1. */
int FriendCodeEntry_SelectTab(FriendCodeEntry *self, int tab)
{
    MenuTabs_SelectTab(friend_code_menu(self), (u8) tab);
    return 1;
}
CLEAN_AS(func_ov133_0229c3d4, FriendCodeEntry_SelectTab)

/* func_ov133_0229c3ec (vtable slot 0x5c, phase 5): the scene asks to be deleted. */
int FriendCodeEntry_End(FriendCodeEntry *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov133_0229c3ec, FriendCodeEntry_End)

/* func_ov133_0229c3fc (vtable slot 0x58, phase 4): nothing. */
int FriendCodeEntry_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov133_0229c3fc, FriendCodeEntry_Phase4Idle)

/* func_ov133_0229c400 (vtable slot 0x54, phase 3): nothing. */
int FriendCodeEntry_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov133_0229c400, FriendCodeEntry_Phase3Idle)

/* func_ov133_0229c404 (vtable slot 0x50, phase 2): a frame of the input: its start, its sub
 * state and its end. Answers 1. */
int FriendCodeEntry_RunInteractive(FriendCodeEntry *self)
{
    FriendCodeEntry_BeginInteractiveFrame(self);
    FriendCodeEntry_RunSubState(self);
    FriendCodeEntry_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(func_ov133_0229c404, FriendCodeEntry_RunInteractive)

/* func_ov133_0229c420: the sub state's function (FriendCodeEntrySubState) through the table of
 * member functions, filled once from its constants. Before it, the menu close's delay is
 * counted; when the menu is asked to close in a sub state of the input (0-3, 7-9), the input is
 * cancelled: the pointer hidden, the wipe out (state 3, phase 1), the menu closed (tab 7) and a
 * friend being added cleared from the roster.
 * REQUIRES: the sub state is below 13; the game reads past the table for others. */
void FriendCodeEntry_RunSubState(FriendCodeEntry *self)
{
    static const MemberPointer *const sub_states[FRIEND_CODE_SUB_STATES] = {
        &data_ov133_0229c8f0, &data_ov133_0229c8e8, &data_ov133_0229c8e0, &data_ov133_0229c8d8, &data_ov133_0229c8d0,
        &data_ov133_0229c888, &data_ov133_0229c8c0, &data_ov133_0229c8b8, &data_ov133_0229c8b0, &data_ov133_0229c8a8,
        &data_ov133_0229c8f8, &data_ov133_0229c898, &data_ov133_0229c890,
    };
    MemberTable_InitOnce(&data_ov133_0229c9a4, data_ov133_0229c9d0, sub_states, FRIEND_CODE_SUB_STATES);
    StateFlags_CountMenuCloseDelay();
    if (StateFlags_MenuCloseAsked()) {
        switch (self->base.sub_state) {
            case FRIEND_CODE_SUB_TOUCH:
            case FRIEND_CODE_SUB_TOUCH_KEY_HELD:
            case FRIEND_CODE_SUB_TOUCH_MARK:
            case FRIEND_CODE_SUB_KEYS:
            case FRIEND_CODE_SUB_KEY_HELD:
            case FRIEND_CODE_SUB_DELETE_HELD:
            case FRIEND_CODE_SUB_MARK_KEYS:
                FriendCodeEntry_HidePointer(self);
                MenuScene_SetState(friend_code_scene_of(self), FRIEND_CODE_STATE_START_WIPE_OUT);
                FriendCodeEntry_SelectTab(self, FRIEND_CODE_TAB_CLOSE);
                if (GroupParams_Mode() == FRIEND_CODE_MODE_NEW) {
                    WifiFriend_Clear(FriendCodeEntry_Friend(self));
                }
                MenuScene_SetPhase(friend_code_scene_of(self), FRIEND_CODE_PHASE_STATES);
                break;
            default:
                break;
        }
    }
    MemberPointer_CallVoid(&data_ov133_0229c9d0[self->base.sub_state], self);
}
CLEAN_AS(func_ov133_0229c420, FriendCodeEntry_RunSubState)

/* Obj_ov133_0229c908::func_ov133_0229c58c (vtable slot 0x4c, phase 1): a frame of the scene's
 * states (FriendCodeEntryState) between the frame's start and end, through the table of member
 * functions (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 5; the game reads past the table for others. */
int FriendCodeEntry_RunState(FriendCodeEntry *self)
{
    static const MemberPointer *const states[FRIEND_CODE_STATES] = {
        &data_ov133_0229c878, &data_ov133_0229c8a0, &data_ov133_0229c870, &data_ov133_0229c8c8, &data_ov133_0229c860,
    };
    MemberTable_InitOnce(&data_ov133_0229c9a0, data_ov133_0229c9a8, states, FRIEND_CODE_STATES);
    FriendCodeEntry_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov133_0229c9a8[self->base.state], self);
    FriendCodeEntry_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov133_0229c90819func_ov133_0229c58cEv, FriendCodeEntry_RunState)

/* func_ov133_0229c62c (vtable slot 0x24): the scene's draw, while it is drawn: the pointer (with
 * the keys in use), the panel and overlay 130's frame at the wipe's y kept, and the text cursor
 * while bit 4 of its blink is set. QUIRK: answers 1 also when not drawn. */
int FriendCodeEntry_Draw(FriendCodeEntry *self)
{
    if (FriendCodeEntry_TestFlags(self, FRIEND_CODE_FLAG_DRAWN) == 0) {
        return 1;
    }
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->pointer);
    }
    ButtonPanel_Draw(&self->panel, self->wipe_y);
    BankPad_DrawPayCells(self->wipe_y);
    if ((self->blink & 0x10) != 0) {
        OamBuffer_DrawCell(1, data_ov133_0229c868, (self->position << 4) + 0x20, self->wipe_y + 0x40, -1, 1, 0x1000, 0x1000, 0,
                           -1, 0, 0);
    }
    return 1;
}
CLEAN_AS(func_ov133_0229c62c, FriendCodeEntry_Draw)

/* func_ov133_0229c6c0 (vtable slot 0x0c): the scene closes: overlay 90's menu told (it slides
 * its bar in when the tab it goes back to is the roster), then the teardown. Answers 1. */
int FriendCodeEntry_Close(FriendCodeEntry *self)
{
    MenuTabs *menu = friend_code_menu(self);
    if (MenuTabs_ChildClosed(menu) == FRIEND_CODE_TAB_ROSTER) {
        MenuTabs_SlideIn(menu);
    }
    FriendCodeEntry_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov133_0229c6c0, FriendCodeEntry_Close)

/* func_ov133_0229c6ec (vtable slot 0x00): the scene starts: its setup, state 0 and the states
 * run (phase 1). Answers 1. */
int FriendCodeEntry_Start(FriendCodeEntry *self)
{
    FriendCodeEntry_Setup(self);
    MenuScene_SetState(friend_code_scene_of(self), FRIEND_CODE_STATE_LOAD);
    MenuScene_SetPhase(friend_code_scene_of(self), FRIEND_CODE_PHASE_STATES);
    return 1;
}
CLEAN_AS(func_ov133_0229c6ec, FriendCodeEntry_Start)

/* func_ov133_0229c70c (named by the profile at 0x0229c880): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order, the label by __cxa_vec_ctor and the two tasks one by one. */
FriendCodeEntry *FriendCodeEntry_New(void)
{
    FriendCodeEntry *self = MenuScene_Alloc(sizeof(FriendCodeEntry));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov133_0229c908;
    __cxa_vec_ctor(&self->label, 1, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070c08,
                   (void (*)(void *))(uintptr_t) func_02070be8);
    Glider0_Construct(&self->pointer);
    ButtonPanel_Construct(&self->panel);
    for (int i = 0; i < 2; i++) {
        LayerTask_Construct(&self->tasks[i]);
    }
    ErrorMessage_Construct(&self->error);
    return self;
}
CLEAN_AS(func_ov133_0229c70c, FriendCodeEntry_New)
