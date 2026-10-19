/* The letter reader of overlay 91 (letter_reader.h): its destructors, its input in the two
 * ways, its states and the vtable's slots. */
#include "letter_reader.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/group_params.h"
#include "main/label_sprite.h"
#include "main/music_volume.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov004/member_pointer.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(LetterReader, view) == 0x94, "view");
static_assert(offsetof(LetterReader, button) == 0x3bc && offsetof(LetterReader, cursor) == 0x434, "button");
static_assert(sizeof(LetterReader) == 0x498, "size (func_ov091_02299494)");

/* The scene's vtable. */
extern const u8 data_ov091_02299530[];

/* The pad (autoload_2/input.h) and the buttons read in `pressed`. */
extern PadState data_021fbe40;
#define LETTER_READER_PAD_A 0x0001
#define LETTER_READER_PAD_B 0x0002

/* The field's sound object; its music volume is at 0x1c4 (main/music_volume.h). */
extern u8 *data_021c526c;

/* The tables of member functions (ov004/member_pointer.h): their guards, the tables and the
 * constants they are filled from. */
extern u32 data_ov091_022995a0; /* the sub states' guard */
extern u32 data_ov091_022995a4; /* the states' guard */
extern MemberPointer data_ov091_022995a8[LETTER_READER_SUB_STATES];
extern MemberPointer data_ov091_022995b8[LETTER_READER_STATES];
extern const MemberPointer data_ov091_022994e0; /* LetterReader_ShowLetter */
extern const MemberPointer data_ov091_022994e8; /* LetterReader_TouchInput */
extern const MemberPointer data_ov091_022994f0; /* LetterReader_WipeIn */
extern const MemberPointer data_ov091_02299500; /* LetterReader_StartWipeOut */
extern const MemberPointer data_ov091_02299508; /* LetterReader_WipeOut */
extern const MemberPointer data_ov091_02299510; /* LetterReader_WaitButton */
extern const MemberPointer data_ov091_02299518; /* LetterReader_WaitCursorPress */
extern const MemberPointer data_ov091_02299520; /* LetterReader_PadInput */

/* The layers the letter is shown on (main/display_layers.h): its text and its paper. */
#define LETTER_READER_TEXT_LAYER 0
#define LETTER_READER_PAPER_LAYER 2

/* The wipes, on window 0 (ov002/menu_scene.h), and the screen they step. */
#define LETTER_READER_WIPE_LAYERS 10
#define LETTER_READER_WIPE_MARGIN 0x30
#define LETTER_READER_WIPE_SCREEN 1

/* The label button's message, and its anchor the cursor sprite points at. */
#define LETTER_READER_BUTTON_MESSAGE 0x65
#define LETTER_READER_BUTTON_ANCHOR 1
#define LETTER_READER_BUTTON_PRESSED 2 /* the button's animation once pressed */

static MenuScene *letter_reader_scene(LetterReader *self)
{
    return &self->base;
}

static MusicVolume *letter_reader_music_volume(void)
{
    return (MusicVolume *) (void *) (data_021c526c + 0x1c4);
}

/* The button's and the cursor's bases are main's labelled sprite and cell layer sprite
 * (label_button.h, glide.h). */
static LabelSprite *letter_reader_button_sprite(LetterReader *self)
{
    return (LabelSprite *) (void *) &self->button;
}

static CellLayerSprite *letter_reader_cursor_cells(LetterReader *self)
{
    return (CellLayerSprite *) (void *) &self->cursor;
}

/* A member's virtual function `slot` (taking only the member). */
static void letter_reader_call_slot(void *object, int slot)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[slot])(object);
}

/* The cursor sprite put on the button's anchor. */
static void letter_reader_point_at_button(LetterReader *self)
{
    int x = LabelButton_AnchorX(&self->button, LETTER_READER_BUTTON_ANCHOR);
    int y = LabelButton_AnchorY(&self->button, LETTER_READER_BUTTON_ANCHOR);
    Glider_PlaceAt(&self->cursor, x, y);
}

/* The members' destructors, last member first, then the base's. */
static void letter_reader_destroy_members(LetterReader *self)
{
    self->base.vtable = data_ov091_02299530;
    Glider1_Destroy(&self->cursor);
    LabelButton1_Destroy(&self->button);
    LetterView_Destruct(&self->view);
    MenuScene_DestroyBase(letter_reader_scene(self));
}

/* func_ov091_02298f20 (vtable slot 0x40) */
LetterReader *LetterReader_Destroy(LetterReader *self)
{
    letter_reader_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov091_02298f20, LetterReader_Destroy)

/* func_ov091_02298f5c (vtable slot 0x44) */
LetterReader *LetterReader_Delete(LetterReader *self)
{
    letter_reader_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov091_02298f5c, LetterReader_Delete)

/* func_ov091_02298f9c: input by the pad from now on (sub state 1). */
void LetterReader_UsePad(LetterReader *self)
{
    MenuScene_SetSubState(letter_reader_scene(self), LETTER_READER_SUB_PAD);
}
CLEAN_AS(func_ov091_02298f9c, LetterReader_UsePad)

/* func_ov091_02298fa8: input by touch from now on (sub state 0). */
void LetterReader_UseTouch(LetterReader *self)
{
    MenuScene_SetSubState(letter_reader_scene(self), LETTER_READER_SUB_TOUCH);
}
CLEAN_AS(func_ov091_02298fa8, LetterReader_UseTouch)

/* func_ov091_02298fb4 (sub state 1): the pen going down switches to touch; A or B presses the
 * cursor sprite (the second of its set) and waits for it (state 2, phase 1). */
void LetterReader_PadInput(LetterReader *self)
{
    if (MenuScene_TakeTouch(letter_reader_scene(self))) {
        LetterReader_UseTouch(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if ((pressed & LETTER_READER_PAD_A) || (pressed & LETTER_READER_PAD_B)) {
        Glider_ShowSecondOfSet(&self->cursor);
        self->base.state = LETTER_READER_STATE_PRESS;
        MenuScene_SetPhase(letter_reader_scene(self), MENU_SCENE_PHASE_STATES);
    }
}
CLEAN_AS(func_ov091_02298fb4, LetterReader_PadInput)

/* func_ov091_02299004 (sub state 0): a button of the pad switches to the pad (with command
 * 0x3b); the label button touched is pressed (state 3, phase 1) with sound 0x27. */
void LetterReader_TouchInput(LetterReader *self)
{
    if (MenuScene_TakeButtons(letter_reader_scene(self), 1)) {
        LetterReader_UsePad(self);
        return;
    }
    if (LabelButton_IsTouched(&self->button)) {
        LabelSprite_SetState(letter_reader_button_sprite(self), LETTER_READER_BUTTON_PRESSED);
        self->base.state = LETTER_READER_STATE_BUTTON;
        MenuScene_SetPhase(letter_reader_scene(self), MENU_SCENE_PHASE_STATES);
        SoundSys_PlaySe(0x27);
    }
}
CLEAN_AS(func_ov091_02299004, LetterReader_TouchInput)

/* func_ov091_02299050: after each interactive frame: nothing. */
void LetterReader_EndFrame(void) {}
CLEAN_AS(func_ov091_02299050, LetterReader_EndFrame)

/* func_ov091_02299054: before each interactive frame: nothing. */
void LetterReader_BeginFrame(void) {}
CLEAN_AS(func_ov091_02299054, LetterReader_BeginFrame)

/* func_ov091_02299058: the letter view's text boxes let go. */
void LetterReader_ReleaseView(LetterReader *self)
{
    LetterView_ReleaseBoxes(&self->view);
}
CLEAN_AS(func_ov091_02299058, LetterReader_ReleaseView)

/* func_ov091_02299064: the letter view set up on layer 0, the label button shown at the lower
 * right and the cursor sprite put on it. */
void LetterReader_Init(LetterReader *self)
{
    LetterView_Init(&self->view, LETTER_READER_TEXT_LAYER);
    LabelButton_ShowLowerRight(&self->button, LETTER_READER_BUTTON_MESSAGE);
    letter_reader_point_at_button(self);
}
CLEAN_AS(func_ov091_02299064, LetterReader_Init)

/* func_ov091_022990b0 (state 5): the wipe out stepped; when done, the letter's layers hidden
 * and the scene deleted (phase 5); else they follow the wipe. */
void LetterReader_WipeOut(LetterReader *self)
{
    if (MenuScene_StepWipe(letter_reader_scene(self), LETTER_READER_WIPE_SCREEN) != 0) {
        DisplayLayer_HideAndResetScroll(LETTER_READER_TEXT_LAYER);
        DisplayLayer_HideAndResetScroll(LETTER_READER_PAPER_LAYER);
        MenuScene_SetPhase(letter_reader_scene(self), MENU_SCENE_PHASE_DELETE);
    } else {
        MenuScene_ScrollWipe(letter_reader_scene(self), LETTER_READER_TEXT_LAYER, 0, 0);
        MenuScene_ScrollWipe(letter_reader_scene(self), LETTER_READER_PAPER_LAYER, 0, 0);
    }
}
CLEAN_AS(func_ov091_022990b0, LetterReader_WipeOut)

/* func_ov091_022990f4 (state 4): sound 2, the music volume's slot 1 ended, the letter wipes out
 * on window 0 (state 5). */
void LetterReader_StartWipeOut(LetterReader *self)
{
    SoundSys_PlaySe(2);
    MusicVolume_EndSlot1(letter_reader_music_volume());
    MenuScene_StartWipeOnWindow0(letter_reader_scene(self), LETTER_READER_WIPE_LAYERS, 0, 0, LETTER_READER_WIPE_MARGIN);
    MenuScene_ScrollWipe(letter_reader_scene(self), LETTER_READER_TEXT_LAYER, 0, 0);
    MenuScene_ScrollWipe(letter_reader_scene(self), LETTER_READER_PAPER_LAYER, 0, 0);
    MenuScene_SetState(letter_reader_scene(self), LETTER_READER_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov091_022990f4, LetterReader_StartWipeOut)

/* func_ov091_0229914c (state 3): while the button's animation runs, the cursor sprite follows
 * the button when it has an animation; when it ends, the cursor sprite's animation stopped and
 * the letter closes (state 4). */
void LetterReader_WaitButton(LetterReader *self)
{
    if (LabelButton_StepAnimation(&self->button)) {
        if (CellLayerSprite_AnimNumber(letter_reader_cursor_cells(self))) {
            letter_reader_point_at_button(self);
        }
    } else {
        Glider_SetAnim(&self->cursor, GLIDER_ANIM_NONE);
        MenuScene_SetState(letter_reader_scene(self), LETTER_READER_STATE_CLOSE);
    }
}
CLEAN_AS(func_ov091_0229914c, LetterReader_WaitButton)

/* func_ov091_022991b0 (state 2): once the cursor sprite's press is over, the button is pressed
 * (state 3) with sound 0x27. */
void LetterReader_WaitCursorPress(LetterReader *self)
{
    if (CellLayerSprite_IsDone(letter_reader_cursor_cells(self))) {
        LabelSprite_SetState(letter_reader_button_sprite(self), LETTER_READER_BUTTON_PRESSED);
        MenuScene_SetState(letter_reader_scene(self), LETTER_READER_STATE_BUTTON);
        SoundSys_PlaySe(0x27);
    }
}
CLEAN_AS(func_ov091_022991b0, LetterReader_WaitCursorPress)

/* func_ov091_022991e8 (state 1): the wipe in stepped back; when done, the scene takes input
 * (phase 2) with the cursor sprite's first set, by touch while state flag 2 is clear, else by
 * the pad. The letter's layers follow the wipe either way. */
void LetterReader_WipeIn(LetterReader *self)
{
    if (MenuScene_StepWipeBack(letter_reader_scene(self), LETTER_READER_WIPE_SCREEN) != 0) {
        MenuScene_SetPhase(letter_reader_scene(self), MENU_SCENE_PHASE_INTERACTIVE);
        Glider_SetAnim(&self->cursor, GLIDER_ANIM_SET_A);
        if (StateFlags_IsClear2()) {
            MenuScene_SetSubState(letter_reader_scene(self), LETTER_READER_SUB_TOUCH);
        } else {
            MenuScene_SetSubState(letter_reader_scene(self), LETTER_READER_SUB_PAD);
        }
    }
    MenuScene_ScrollWipe(letter_reader_scene(self), LETTER_READER_TEXT_LAYER, 0, 0);
    MenuScene_ScrollWipe(letter_reader_scene(self), LETTER_READER_PAPER_LAYER, 0, 0);
}
CLEAN_AS(func_ov091_022991e8, LetterReader_WipeIn)

/* func_ov091_02299244 (state 0): sound 1, the music volume's slot 1 at 0, the main screen's BG
 * mode 0; the letter at GroupParams_Pointer shown (text on layer 0, paper on layer 2, priority
 * 1) and wiped in on window 0 from covered; both layers shown at the wipe's place with their
 * BG controls at 0; on to state 1. */
void LetterReader_ShowLetter(LetterReader *self)
{
    SoundSys_PlaySe(1);
    MusicVolume_SetSlot1(letter_reader_music_volume(), 0);
    DisplayShadow_SetMainBgMode(0);
    const Letter *letter = GroupParams_Pointer();
    LetterView_Show(&self->view, letter, LETTER_READER_TEXT_LAYER, LETTER_READER_PAPER_LAYER, 1);
    MenuScene_StartWipeCoveredOnWindow0(letter_reader_scene(self), LETTER_READER_WIPE_LAYERS, 0, 0, LETTER_READER_WIPE_MARGIN);
    DisplayLayer_Show(LETTER_READER_TEXT_LAYER);
    MenuScene_ScrollWipe(letter_reader_scene(self), LETTER_READER_TEXT_LAYER, 0, 0);
    DisplayLayer_SetBgControl(LETTER_READER_TEXT_LAYER, 0, 0, 0);
    DisplayLayer_Show(LETTER_READER_PAPER_LAYER);
    MenuScene_ScrollWipe(letter_reader_scene(self), LETTER_READER_PAPER_LAYER, 0, 0);
    DisplayLayer_SetBgControl(LETTER_READER_PAPER_LAYER, 0, 0, 0);
    MenuScene_SetState(letter_reader_scene(self), LETTER_READER_STATE_WIPE_IN);
}
CLEAN_AS(func_ov091_02299244, LetterReader_ShowLetter)

/* func_ov091_022992e0 (vtable slot 0x5c, phase 5): the scene asks to be deleted. */
int LetterReader_RequestDelete(LetterReader *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov091_022992e0, LetterReader_RequestDelete)

/* func_ov091_022992f0 (vtable slot 0x58, phase 4): nothing. */
int LetterReader_Phase4(void)
{
    return 1;
}
CLEAN_AS(func_ov091_022992f0, LetterReader_Phase4)

/* func_ov091_022992f4 (vtable slot 0x54, phase 3): nothing. */
int LetterReader_Phase3(void)
{
    return 1;
}
CLEAN_AS(func_ov091_022992f4, LetterReader_Phase3)

/* Obj_ov091_02299530::func_ov091_022992f8 (vtable slot 0x50, phase 2): the sub state
 * (LetterReaderSubState) run through its table of member functions (filled once from its
 * constants, after the frame's start), between the frame's start and end. Answers 1.
 * REQUIRES: the sub state is below 2; the game reads past the table for others. */
int LetterReader_RunInteractive(LetterReader *self)
{
    static const MemberPointer *const sub_states[LETTER_READER_SUB_STATES] = {
        &data_ov091_022994e8,
        &data_ov091_02299520,
    };
    LetterReader_BeginFrame();
    MemberTable_InitOnce(&data_ov091_022995a0, data_ov091_022995a8, sub_states, LETTER_READER_SUB_STATES);
    MemberPointer_CallVoid(&data_ov091_022995a8[self->base.sub_state], self);
    LetterReader_EndFrame();
    return 1;
}
CLEAN_AS(_ZN18Obj_ov091_0229953019func_ov091_022992f8Ev, LetterReader_RunInteractive)

/* Obj_ov091_02299530::func_ov091_0229936c (vtable slot 0x4c, phase 1): the state
 * (LetterReaderState) run through its table of member functions, filled once from its
 * constants. Answers 1.
 * REQUIRES: the state is below 6; the game reads past the table for others. */
int LetterReader_RunState(LetterReader *self)
{
    static const MemberPointer *const states[LETTER_READER_STATES] = {
        &data_ov091_022994e0, &data_ov091_022994f0, &data_ov091_02299518,
        &data_ov091_02299510, &data_ov091_02299500, &data_ov091_02299508,
    };
    MemberTable_InitOnce(&data_ov091_022995a4, data_ov091_022995b8, states, LETTER_READER_STATES);
    MemberPointer_CallVoid(&data_ov091_022995b8[self->base.state], self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov091_0229953019func_ov091_0229936cEv, LetterReader_RunState)

/* func_ov091_02299410 (vtable slot 0x24): the scene's draw: the cursor sprite updated through
 * its class (slot 3), the label button drawn through its class (slot 2) at the wipe's y, and
 * the cursor sprite drawn while the pad is in use (state flag 2). Answers 1. */
int LetterReader_Draw(LetterReader *self)
{
    letter_reader_call_slot(&self->cursor, 3);
    int y = MenuScene_WipeOffsetY(letter_reader_scene(self));
    LabelSprite_SetOffset(letter_reader_button_sprite(self), 0, y);
    letter_reader_call_slot(&self->button, 2);
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor);
    }
    return 1;
}
CLEAN_AS(func_ov091_02299410, LetterReader_Draw)

/* func_ov091_0229945c (vtable slot 0x0c): the scene ends: the letter view's boxes let go and
 * the music restored. Answers 1. */
int LetterReader_End(LetterReader *self)
{
    LetterReader_ReleaseView(self);
    SoundSys_RestoreMusic();
    return 1;
}
CLEAN_AS(func_ov091_0229945c, LetterReader_End)

/* func_ov091_02299470 (vtable slot 0x00): the scene starts: set up, state 0 in phase 1, the
 * music lowered. Answers 1. */
int LetterReader_Start(LetterReader *self)
{
    LetterReader_Init(self);
    MenuScene_SetState(letter_reader_scene(self), LETTER_READER_STATE_SHOW);
    MenuScene_SetPhase(letter_reader_scene(self), MENU_SCENE_PHASE_STATES);
    SoundSys_LowerMusic();
    return 1;
}
CLEAN_AS(func_ov091_02299470, LetterReader_Start)

/* func_ov091_02299494: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base, the scene's vtable and its members constructed in order. */
LetterReader *LetterReader_New(void)
{
    LetterReader *self = MenuScene_Alloc(sizeof(LetterReader));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov091_02299530;
    LetterView_Construct(&self->view);
    LabelButton1_Construct(&self->button);
    Glider1_Construct(&self->cursor);
    return self;
}
CLEAN_AS(func_ov091_02299494, LetterReader_New)
