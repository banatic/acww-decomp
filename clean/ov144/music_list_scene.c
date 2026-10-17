/* The music list scene of overlay 144 (music_list.h): its sub states (the input, the knob, the
 * pointer's moves, the panel's press, the take out's end, the close's delay, the error), its
 * graphics and the frame's start and end, its states (the wipes in and out), the tables they run
 * from, the vtable's slots, its draw, constructor and destructors. */
#include "music_list.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/house_record.h"
#include "main/oam_buffer.h"
#include "main/rom_file.h"
#include "main/state_flags.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"

/* The scene's vtable. */
extern const u8 data_ov144_0229b3f8[];

/* The heap the scene loads its files with. */
extern Heap *data_021fbe94;

/* The scene's files. */
extern const char data_ov144_0229b458[]; /* "menu/music/obj.bch" */
extern const char data_ov144_0229b46c[]; /* "menu/music/obj.bpl" */
extern const char data_ov144_0229b480[]; /* "menu/music/bg0.bch" */
extern const char data_ov144_0229b494[]; /* "menu/music/bg1.bch" */
extern const char data_ov144_0229b4a8[]; /* "menu/music/bg.bpl" */
extern const char data_ov144_0229b4bc[]; /* "menu/music/b_bg.bsc" */
extern const char data_ov144_0229b4d0[]; /* "menu/music/a_bg.bsc" */

/* The scroll bar's OBJs. */
extern const OamEntry data_ov144_0229b3b0[];

/* The labels' constructor and destructor, handed to __cxa_vec_ctor and __cxa_vec_cleanup (the
 * game's symbols). */
extern void *func_02070c08(void *label);
extern int **func_02070be8(void *label);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The pad (autoload_2/input.h). */
typedef struct MusicListButtons {
    u16 held;
    u16 pressed; /* held now and not in the frame before */
} MusicListButtons;
extern MusicListButtons data_021fbe40;
#define MUSIC_LIST_PAD_A 0x0001
#define MUSIC_LIST_PAD_B 0x0002

/* The touch (as menu_scene.c reads it): the pen is down, it went down or up this frame, and its
 * place. */
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;

/* The tables of member functions the states and sub states run from (the overlay's .bss, filled
 * once from the constants after them) and their guards. */
extern u32 data_ov144_0229b500; /* the states' guard */
extern u32 data_ov144_0229b504; /* the sub states' guard */
extern MemberPointer data_ov144_0229b508[MUSIC_LIST_STATES];
extern MemberPointer data_ov144_0229b528[MUSIC_LIST_SUB_STATES];
extern const MemberPointer data_ov144_0229b328, data_ov144_0229b330, data_ov144_0229b338, data_ov144_0229b340,
    data_ov144_0229b348, data_ov144_0229b350, data_ov144_0229b358, data_ov144_0229b360, data_ov144_0229b368,
    data_ov144_0229b370, data_ov144_0229b378, data_ov144_0229b380, data_ov144_0229b388, data_ov144_0229b390,
    data_ov144_0229b398, data_ov144_0229b3a0, data_ov144_0229b3a8;

/* The scroll bar's touch area. */
#define MUSIC_LIST_BAR_MIN_X 0xcf
#define MUSIC_LIST_BAR_MAX_X 0xdf
#define MUSIC_LIST_BAR_MIN_Y 0x1d
#define MUSIC_LIST_BAR_MAX_Y 0x93

/* The panel's message (layout 5), and the modes the scene tells its parent it ends with: the
 * store screen (overlay 109) or MENU_DISPATCH_MODE_CLOSE. */
#define MUSIC_LIST_PANEL_MESSAGE 0x65
#define MUSIC_LIST_PARENT_STORE 0x23
#define MUSIC_LIST_PARENT_CLOSE 0x44

/* The wipes on window 2: the layers (BG1 and BG3 of the sub screen), the frames, the margin. */
#define MUSIC_LIST_WIPE_LAYERS 10
#define MUSIC_LIST_WIPE_MARGIN 0x18

static MenuScene *music_list_scene(MusicList *self)
{
    return &self->base;
}

static Process *music_list_process(MusicList *self)
{
    return (Process *) (void *) self;
}

static CellLayerSprite *music_list_pointer_cells(MusicList *self)
{
    /* The pointer's base is main's cell layer sprite (glide.h). */
    return (CellLayerSprite *) (void *) &self->pointer;
}

/* An object's virtual function at `slot` of its vtable, called with nothing more. */
static void music_list_call_slot(void *object, int slot)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[slot])(object);
}

/* --- The sub states --- */

/* func_ov144_0229a83c (sub state 12): once the error message is done, the input again and the
 * pointer's OBJ window set back. */
void MusicList_ErrorWait(MusicList *self)
{
    if (ErrorMessage_Update(&self->error, 1) != 0) {
        MusicList_StartInput(self);
        CellLayerSprite_SetWindow(music_list_pointer_cells(self));
    }
}
CLEAN_AS(func_ov144_0229a83c, MusicList_ErrorWait)

/* func_ov144_0229a868 (sub state 11): the delay counted down, then the pointer hidden and the
 * states run (phase 1: the close set before). */
void MusicList_CloseDelay(MusicList *self)
{
    if (self->delay != 0) {
        self->delay--;
    } else {
        MusicList_HidePointer(self);
        MenuScene_SetPhase(music_list_scene(self), MUSIC_LIST_PHASE_STATES);
    }
}
CLEAN_AS(func_ov144_0229a868, MusicList_CloseDelay)

/* func_ov144_0229a894 (sub state 10): after the delay, the song taken out leaves the list: out
 * of the house's collection (again), the playing row moved up when it was below, no row chosen,
 * the songs gathered again, the scroll's end and the scroll kept within the list, the knob put
 * by it, the input again.
 * QUIRK: HouseRecord_RemoveSong was already called for the song by MusicList_TakeOut. */
void MusicList_FinishTakeOut(MusicList *self)
{
    if (self->delay != 0) {
        self->delay--;
        return;
    }
    HouseRecord_RemoveSong(self->songs[self->selected]);
    if (self->selected < self->playing) {
        self->playing -= 1;
    }
    MusicList_Select(self, MUSIC_LIST_NO_ROW);
    MusicList_GatherSongs(self);
    self->scroll_max = (self->count - MUSIC_LIST_ROWS_SHOWN) * MUSIC_LIST_ROW_HEIGHT;
    if (self->scroll_max < 0) {
        self->scroll_max = 0;
    }
    if (self->scroll > self->scroll_max) {
        self->scroll = self->scroll_max;
    }
    MusicList_ScrollTo(self, self->scroll);
    self->scroll_target = self->scroll;
    MusicList_KnobFromScroll(self);
    MusicList_StartInput(self);
}
CLEAN_AS(func_ov144_0229a894, MusicList_FinishTakeOut)

/* func_ov144_0229a948 (sub state 9): while the panel's button press plays, the pointer (when
 * shown) follows the button by the press's frame; then the pointer hidden and the states run
 * (phase 1: the close set before). */
void MusicList_PanelPress(MusicList *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) != 0) {
        if (CellLayerSprite_AnimNumber(music_list_pointer_cells(self)) != 0) {
            int frame = ButtonPanel_SelectedPressFrame(&self->panel);
            int x = ButtonPanel_ButtonX(&self->panel, -1);
            int y = ButtonPanel_ButtonY(&self->panel, -1);
            Glider_PlaceAt(&self->pointer, frame + x, frame + y);
        }
    } else {
        MusicList_HidePointer(self);
        MenuScene_SetPhase(music_list_scene(self), MUSIC_LIST_PHASE_STATES);
    }
}
CLEAN_AS(func_ov144_0229a948, MusicList_PanelPress)

/* func_ov144_0229a9b0 (sub state 8): once the pointer's animation ends, the first of its set and
 * back to the sub state kept. */
void MusicList_PointerAnim(MusicList *self)
{
    if (CellLayerSprite_IsDone(music_list_pointer_cells(self)) != 0) {
        MusicList_ShowPointer(self);
        MenuScene_SetSubState(music_list_scene(self), self->return_sub_state);
    }
}
CLEAN_AS(func_ov144_0229a9b0, MusicList_PointerAnim)

/* func_ov144_0229a9d4 (sub state 7): once the pointer's press ends, the cursor's command; when
 * it answers 0, the buttons' input again (sub state 3) with the pointer's third animation. */
void MusicList_PointerPress(MusicList *self)
{
    if (CellLayerSprite_IsDone(music_list_pointer_cells(self)) != 0) {
        if (MusicList_Command(self, self->cursor) == 0) {
            MenuScene_SetSubState(music_list_scene(self), MUSIC_LIST_SUB_KEYS);
            MusicList_StartPointerAnim(self);
        }
    }
}
CLEAN_AS(func_ov144_0229a9d4, MusicList_PointerPress)

/* _ZN18Obj_ov144_0229b3f819func_ov144_0229aa08Ev (sub state 6): once the pointer stops, back to
 * the sub state kept, which runs this frame. */
void MusicList_PointerMove(MusicList *self)
{
    if (Glider_IsMoving(&self->pointer) == 0) {
        MenuScene_SetSubState(music_list_scene(self), self->return_sub_state);
        MusicList_RunSubState(self);
    }
}
CLEAN_AS(_ZN18Obj_ov144_0229b3f819func_ov144_0229aa08Ev, MusicList_PointerMove)

/* func_ov144_0229aa30 (sub state 5): once the knob's release has played, the buttons' input
 * again with the pointer's third animation; the pointer kept at the cursor's place. */
void MusicList_KnobRelease(MusicList *self)
{
    if (MusicList_KnobSettled(self) != 0) {
        MenuScene_SetSubState(music_list_scene(self), MUSIC_LIST_SUB_KEYS);
        MusicList_StartPointerAnim(self);
    }
    int x = MusicList_PointerX(self);
    int y = MusicList_PointerY(self);
    Glider_PlaceAt(&self->pointer, x, y);
}
CLEAN_AS(func_ov144_0229aa30, MusicList_KnobRelease)

/* func_ov144_0229aa70 (sub state 4): while A is held, up and down move the knob and the pointer
 * follows it; then the knob let go (sub state 5). */
void MusicList_KnobKeys(MusicList *self)
{
    if (data_021fbe40.held & MUSIC_LIST_PAD_A) {
        MusicList_KnobByKeys(self);
        int x = MusicList_PointerX(self);
        int y = MusicList_PointerY(self);
        Glider_PlaceAt(&self->pointer, x, y);
    } else {
        MusicList_ReleaseKnob(self);
        MenuScene_SetSubState(music_list_scene(self), MUSIC_LIST_SUB_KNOB_RELEASE);
    }
}
CLEAN_AS(func_ov144_0229aa70, MusicList_KnobKeys)

/* func_ov144_0229aabc (sub state 3): the buttons' input. A touch takes over (the touch's input);
 * else a move of the cursor eases the pointer there; else A presses the cursor's place and B
 * closes the scene by the panel's button, the pointer hidden. */
void MusicList_KeyInput(MusicList *self)
{
    if (MenuScene_TakeTouch(music_list_scene(self)) != 0) {
        MusicList_StartTouch(self);
        return;
    }
    if (MusicList_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(music_list_scene(self))) != 0) {
        MusicList_MovePointer(self);
        return;
    }
    if (data_021fbe40.pressed & MUSIC_LIST_PAD_A) {
        MusicList_StartPointerPress(self);
        return;
    }
    if (data_021fbe40.pressed & MUSIC_LIST_PAD_B) {
        MusicList_HidePointer(self);
        MusicList_CloseByPanel(self);
    }
}
CLEAN_AS(func_ov144_0229aabc, MusicList_KeyInput)

/* func_ov144_0229ab20 (sub state 2): while the pen is down on the bar, the knob moves toward it;
 * then it is let go (the touch's input). */
void MusicList_DragBar(MusicList *self)
{
    if (data_021fbdd8 != 0) {
        MusicList_MoveKnob(self, data_021f6c54, 1);
    } else {
        MusicList_ReleaseKnob(self);
        MenuScene_SetSubState(music_list_scene(self), MUSIC_LIST_SUB_TOUCH);
    }
}
CLEAN_AS(func_ov144_0229ab20, MusicList_DragBar)

/* func_ov144_0229ab54 (sub state 1): while the pen is down, the knob grabbed follows it; then it
 * is let go (the touch's input). */
void MusicList_DragKnob(MusicList *self)
{
    if (data_021fbdd8 != 0) {
        MusicList_MoveKnob(self, data_021f6c54, 0);
    } else {
        MusicList_ReleaseKnob(self);
        MenuScene_SetSubState(music_list_scene(self), MUSIC_LIST_SUB_TOUCH);
    }
}
CLEAN_AS(func_ov144_0229ab54, MusicList_DragKnob)

/* func_ov144_0229ab88 (sub state 0): the touch's input. A button takes over (the buttons'
 * input). When the pen goes down: the command of the place under it; else, when the list
 * scrolls, the knob grabbed (sub state 1) or, on the bar, pressed to move toward the pen (sub
 * state 2). */
void MusicList_TouchInput(MusicList *self)
{
    if (MenuScene_TakeButtons(music_list_scene(self), 1) != 0) {
        MusicList_StartKeys(self);
        return;
    }
    if (data_021fbdd8 == 0 || data_021fbddc == 0) {
        return;
    }

    int x = data_021f6c58;
    int y = data_021f6c54;
    int place = MusicList_HitTest(self, x, y);
    if (place != MUSIC_LIST_PLACE_NONE) {
        MusicList_Command(self, (unsigned int) place);
        return;
    }
    if (self->scroll_max <= 0) {
        return;
    }
    if (MusicList_GrabKnob(self, x, y) != 0) {
        MenuScene_SetSubState(music_list_scene(self), MUSIC_LIST_SUB_KNOB_DRAG);
        return;
    }
    if (x < MUSIC_LIST_BAR_MIN_X || x > MUSIC_LIST_BAR_MAX_X || y < MUSIC_LIST_BAR_MIN_Y || y > MUSIC_LIST_BAR_MAX_Y) {
        return;
    }
    PushButton_Press(&self->knob_button);
    self->knob_cued = self->knob;
    MenuScene_SetSubState(music_list_scene(self), MUSIC_LIST_SUB_BAR_DRAG);
}
CLEAN_AS(func_ov144_0229ab88, MusicList_TouchInput)

/* --- Graphics and the frame --- */

/* func_ov144_0229ac40: the panel's text colours, then the sub screen's OBJ characters 0xc0-0x120
 * and palettes 4-5 from "menu/music/obj.bch" and "obj.bpl". */
void MusicList_LoadObjGraphics(MusicList *self)
{
    ButtonPanel_LoadTextColors(&self->panel);
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadCharsFromFile(data_ov144_0229b458, heap, LAYER_SUB_OBJ, 0xc0, 0xc0, 0x120);
    DisplayLayer_LoadPalettesFromFile(data_ov144_0229b46c, heap, LAYER_SUB_OBJ, 4, 4, 5);
}
CLEAN_AS(func_ov144_0229ac40, MusicList_LoadObjGraphics)

/* func_ov144_0229ac90: the sub screen's BG3 characters (17-152 from "bg0.bch", 0x26e-0x27e from
 * "bg1.bch") and palettes 1-10 ("bg.bpl"), the row screens ("b_bg.bsc") and the buttons' screen
 * ("a_bg.bsc") read, the buttons' faces set. */
void MusicList_LoadScreens(MusicList *self)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadCharsFromFile(data_ov144_0229b480, heap, LAYER_SUB_BG3, 17, 17, 152);
    DisplayLayer_LoadCharsFromFile(data_ov144_0229b494, heap, LAYER_SUB_BG3, 0x26e, 0x26e, 0x27e);
    DisplayLayer_LoadPalettesFromFile(data_ov144_0229b4a8, heap, LAYER_SUB_BG3, 1, 1, 0xa);
    RomFile_Read(data_ov144_0229b4bc, self->row_screens, sizeof(self->row_screens));
    RomFile_Read(data_ov144_0229b4d0, self->buttons_screen, sizeof(self->buttons_screen));
    MusicList_RefreshButtons(self);
}
CLEAN_AS(func_ov144_0229ac90, MusicList_LoadScreens)

/* func_ov144_0229ad24: the sub screen's BG mode 0; its BG3 at priority 1, BG1 and BG0 at 2, all
 * three with BG control (0, 0, 0). */
void MusicList_SetupLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(LAYER_SUB_BG3, 1);
    DisplayLayer_SetBgControl(LAYER_SUB_BG3, 0, 0, 0);
    DisplayLayer_SetPriority(LAYER_SUB_BG1, 2);
    DisplayLayer_SetBgControl(LAYER_SUB_BG1, 0, 0, 0);
    DisplayLayer_SetPriority(LAYER_SUB_BG0, 2);
    DisplayLayer_SetBgControl(LAYER_SUB_BG0, 0, 0, 0);
}
CLEAN_AS(func_ov144_0229ad24, MusicList_SetupLayers)

/* func_ov144_0229ad70: the frame's end: a step of the scroll, the screens sent on, the knob's
 * release settled. */
void MusicList_EndFrame(MusicList *self)
{
    MusicList_StepScroll(self);
    MusicList_FlushScreens(self);
    PushButton_SettleRelease(&self->knob_button);
}
CLEAN_AS(func_ov144_0229ad70, MusicList_EndFrame)

/* func_ov144_0229ad90: the frame's start: the labels and the panel's texts closed, both layer
 * tasks ended, the knob updated (slot 3). */
void MusicList_StartFrame(MusicList *self)
{
    MusicList_CloseLabels(self);
    ButtonPanel_CloseTexts(&self->panel);
    LayerTask_End(&self->list_task);
    LayerTask_End(&self->buttons_task);
    music_list_call_slot(&self->knob_button, 3);
}
CLEAN_AS(func_ov144_0229ad90, MusicList_StartFrame)

/* func_ov144_0229add0: the frame's end, from the interactive phase. */
void MusicList_EndFrameAgain(MusicList *self)
{
    MusicList_EndFrame(self);
}
CLEAN_AS(func_ov144_0229add0, MusicList_EndFrameAgain)

/* func_ov144_0229add8: the frame's start, and the pointer updated (slot 3). */
void MusicList_StartFrameWithPointer(MusicList *self)
{
    MusicList_StartFrame(self);
    music_list_call_slot(&self->pointer, 3);
}
CLEAN_AS(func_ov144_0229add8, MusicList_StartFrameWithPointer)

/* func_ov144_0229adf0: what the members hold let go: the labels and the panel's texts closed,
 * both layer tasks ended. */
void MusicList_Release(MusicList *self)
{
    MusicList_CloseLabels(self);
    ButtonPanel_CloseTexts(&self->panel);
    LayerTask_End(&self->list_task);
    LayerTask_End(&self->buttons_task);
}
CLEAN_AS(func_ov144_0229adf0, MusicList_Release)

/* func_ov144_0229ae24: the scene's setup: no flags, no song shown by the labels, the songs
 * gathered, the playing row found (and chosen), the knob at rest. */
void MusicList_Setup(MusicList *self)
{
    self->flags = 0;
    for (int i = 0; i < MUSIC_LIST_ROWS; i++) {
        self->shown[i] = MUSIC_LIST_NO_ITEM;
    }
    MusicList_GatherSongs(self);
    MusicList_FindPlaying(self);
    PushButton_ShowUp(&self->knob_button);
}
CLEAN_AS(func_ov144_0229ae24, MusicList_Setup)

/* func_ov144_0229ae64: the wipe's place applied: the sub screen's BG3 at (0, 0) and BG1 at
 * (0, 0x18 less the scroll) moved with it, its y kept, the knob put by it. */
void MusicList_ScrollWipe(MusicList *self)
{
    MenuScene_ScrollWipe(music_list_scene(self), LAYER_SUB_BG3, 0, 0);
    MenuScene_ScrollWipe(music_list_scene(self), LAYER_SUB_BG1, 0, 0x18 - self->scroll);
    self->wipe_y = MenuScene_WipeOffsetY(music_list_scene(self));
    MusicList_PlaceKnob(self);
}
CLEAN_AS(func_ov144_0229ae64, MusicList_ScrollWipe)

/* --- The states --- */

/* func_ov144_0229aea4 (state 3): the wipe out; at its end both layers hidden and the scene
 * deleted (phase 5). */
void MusicList_WipeOut(MusicList *self)
{
    if (MenuScene_StepWipe(music_list_scene(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(LAYER_SUB_BG3);
        DisplayLayer_HideAndResetScroll(LAYER_SUB_BG1);
        MenuScene_SetPhase(music_list_scene(self), MUSIC_LIST_PHASE_END);
    } else {
        MusicList_ScrollWipe(self);
    }
}
CLEAN_AS(func_ov144_0229aea4, MusicList_WipeOut)

/* func_ov144_0229aed4 (state 2): the parent told what comes next (with its sound): the store
 * screen after the store button, else the close; the wipe out started (state 3). */
void MusicList_StartClose(MusicList *self)
{
    MenuDispatch *parent = (MenuDispatch *) (void *) Process_GetParent(music_list_process(self));
    if (MusicList_TestFlags(self, MUSIC_LIST_FLAG_STORE)) {
        MenuDispatch_SetMode(parent, MUSIC_LIST_PARENT_STORE, 1);
    } else {
        MenuDispatch_SetMode(parent, MUSIC_LIST_PARENT_CLOSE, 1);
    }
    MenuScene_StartWipeOnWindow2(music_list_scene(self), MUSIC_LIST_WIPE_LAYERS, 0, 0, MUSIC_LIST_WIPE_MARGIN);
    MusicList_ScrollWipe(self);
    MenuScene_SetState(music_list_scene(self), MUSIC_LIST_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov144_0229aed4, MusicList_StartClose)

/* func_ov144_0229af28 (state 1): the wipe in; at its end the interactive phase (2) and the
 * input. */
void MusicList_WipeIn(MusicList *self)
{
    if (MenuScene_StepWipeBack(music_list_scene(self), 0) != 0) {
        MenuScene_SetPhase(music_list_scene(self), MUSIC_LIST_PHASE_INTERACTIVE);
        MusicList_StartInput(self);
    }
    MusicList_ScrollWipe(self);
}
CLEAN_AS(func_ov144_0229af28, MusicList_WipeIn)

/* func_ov144_0229af50 (state 0): the layers set up, the graphics loaded, the list scrolled to the
 * playing row, the wipe in started covered (4 frames), both layers shown, the scene drawn from
 * now on, the panel's layout 5 with message 0x65; state 1. */
void MusicList_Open(MusicList *self)
{
    MusicList_SetupLayers();
    MusicList_LoadScreens(self);
    MusicList_SetupScroll(self);
    MusicList_LoadObjGraphics(self);
    MenuScene_StartWipeCoveredOnWindow2(music_list_scene(self), MUSIC_LIST_WIPE_LAYERS, 4, 0, MUSIC_LIST_WIPE_MARGIN);
    DisplayLayer_Show(LAYER_SUB_BG3);
    DisplayLayer_Show(LAYER_SUB_BG1);
    MusicList_ScrollWipe(self);
    MusicList_SetFlags(self, MUSIC_LIST_FLAG_DRAWN);
    ButtonPanel_SetLayout5(&self->panel, MUSIC_LIST_PANEL_MESSAGE);
    MenuScene_SetState(music_list_scene(self), MUSIC_LIST_STATE_WIPE_IN);
}
CLEAN_AS(func_ov144_0229af50, MusicList_Open)

/* --- The vtable's phases --- */

/* func_ov144_0229afb4 (vtable slot 0x5c, phase 5): the scene asks to be deleted. Answers 1. */
int MusicList_End(MusicList *self)
{
    Process_RequestDelete(music_list_process(self));
    return 1;
}
CLEAN_AS(func_ov144_0229afb4, MusicList_End)

/* func_ov144_0229afc4 (vtable slot 0x58, phase 4): nothing. */
int MusicList_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov144_0229afc4, MusicList_Phase4Idle)

/* func_ov144_0229afc8 (vtable slot 0x54, phase 3): nothing. */
int MusicList_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov144_0229afc8, MusicList_Phase3Idle)

/* _ZN18Obj_ov144_0229b3f819func_ov144_0229afccEv (vtable slot 0x50, phase 2): the menu close's
 * delay counted; when main asked the menu to close in sub states 0-4 (the input and the knob),
 * the pointer hidden and the scene closed by the panel's button, the states run from the next
 * frame (phase 1). Then a frame: its start with the pointer, the sub state, its end. Answers
 * 1. */
int MusicList_RunInteractive(MusicList *self)
{
    StateFlags_CountMenuCloseDelay();
    if (StateFlags_MenuCloseAsked()) {
        switch (self->base.sub_state) {
            case MUSIC_LIST_SUB_TOUCH:
            case MUSIC_LIST_SUB_KNOB_DRAG:
            case MUSIC_LIST_SUB_BAR_DRAG:
            case MUSIC_LIST_SUB_KEYS:
            case MUSIC_LIST_SUB_KNOB_KEYS:
                MusicList_HidePointer(self);
                MusicList_CloseByPanel(self);
                MenuScene_SetPhase(music_list_scene(self), MUSIC_LIST_PHASE_STATES);
                break;
            default:
                break;
        }
    }
    MusicList_StartFrameWithPointer(self);
    MusicList_RunSubState(self);
    MusicList_EndFrameAgain(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov144_0229b3f819func_ov144_0229afccEv, MusicList_RunInteractive)

/* _ZN18Obj_ov144_0229b3f819func_ov144_0229b02cEv: the sub state's function (MusicListSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 13; the game reads past the table for others. */
void MusicList_RunSubState(MusicList *self)
{
    static const MemberPointer *const sub_states[MUSIC_LIST_SUB_STATES] = {
        &data_ov144_0229b348, &data_ov144_0229b378, &data_ov144_0229b370, &data_ov144_0229b368, &data_ov144_0229b360,
        &data_ov144_0229b388, &data_ov144_0229b328, &data_ov144_0229b390, &data_ov144_0229b380, &data_ov144_0229b338,
        &data_ov144_0229b330, &data_ov144_0229b358, &data_ov144_0229b340,
    };
    MemberTable_InitOnce(&data_ov144_0229b504, data_ov144_0229b528, sub_states, MUSIC_LIST_SUB_STATES);
    MemberPointer_CallVoid(&data_ov144_0229b528[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov144_0229b3f819func_ov144_0229b02cEv, MusicList_RunSubState)

/* func_ov144_0229b130 (vtable slot 0x4c, phase 1): a frame of the scene's states
 * (MusicListState) between the frame's start and end, through the table of member functions,
 * filled once from its constants. Answers 1.
 * REQUIRES: the state is below 4; the game reads past the table for others. */
int MusicList_RunState(MusicList *self)
{
    static const MemberPointer *const states[MUSIC_LIST_STATES] = {
        &data_ov144_0229b3a0,
        &data_ov144_0229b3a8,
        &data_ov144_0229b350,
        &data_ov144_0229b398,
    };
    MemberTable_InitOnce(&data_ov144_0229b500, data_ov144_0229b508, states, MUSIC_LIST_STATES);
    MusicList_StartFrame(self);
    MemberPointer_CallVoid(&data_ov144_0229b508[self->base.state], self);
    MusicList_EndFrame(self);
    return 1;
}
CLEAN_AS(func_ov144_0229b130, MusicList_RunState)

/* func_ov144_0229b1c4 (vtable slot 0x24): the scene's draw. With state flag 2 the pointer drawn
 * (and again 256 pixels left near the right edge). Once set up: the panel moved with the wipe
 * and, when the list scrolls, the knob (slot 2) and the scroll bar at 0x60 below the wipe's y.
 * Answers whether the scene was set up. */
int MusicList_Draw(MusicList *self)
{
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->pointer);
    }
    if (MusicList_TestFlags(self, MUSIC_LIST_FLAG_DRAWN) == 0) {
        return 0;
    }
    ButtonPanel_Draw(&self->panel, MenuScene_WipeOffsetY(music_list_scene(self)));
    int y = (int) ((u32) self->wipe_y + 0x60);
    if (self->scroll_max > 0) {
        music_list_call_slot(&self->knob_button, 2);
        OamBuffer_DrawCell(1, data_ov144_0229b3b0, 0x80, y, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
    return 1;
}
CLEAN_AS(func_ov144_0229b1c4, MusicList_Draw)

/* func_ov144_0229b254 (vtable slot 0x0c): the scene closes: the parent told, then what the
 * members hold let go. Answers 1. */
int MusicList_Close(MusicList *self)
{
    MenuDispatch_ChildClosed((MenuDispatch *) (void *) Process_GetParent(music_list_process(self)));
    MusicList_Release(self);
    return 1;
}
CLEAN_AS(func_ov144_0229b254, MusicList_Close)

/* func_ov144_0229b270 (vtable slot 0x00): the scene starts: its setup, state 0 (set as is) and
 * the base's wait (phase 0). Answers 1. */
int MusicList_Start(MusicList *self)
{
    MusicList_Setup(self);
    self->base.state = MUSIC_LIST_STATE_OPEN;
    MenuScene_SetPhase(music_list_scene(self), MUSIC_LIST_PHASE_WAIT);
    return 1;
}
CLEAN_AS(func_ov144_0229b270, MusicList_Start)

/* --- Construction and destruction --- */

/* The members' destructors, last member first, then the base's. The layer tasks have none. */
static void music_list_destroy_members(MusicList *self)
{
    self->base.vtable = data_ov144_0229b3f8;
    ErrorMessage_Destruct(&self->error);
    __cxa_vec_cleanup(self->labels, MUSIC_LIST_ROWS, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    ButtonPanel_Destroy(&self->panel);
    PushButton_Destroy(&self->knob_button);
    Glider0_Destroy(&self->pointer);
    MenuScene_DestroyBase(music_list_scene(self));
}

/* func_ov144_022995a0 (vtable slot 0x40) */
MusicList *MusicList_Destroy(MusicList *self)
{
    music_list_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov144_022995a0, MusicList_Destroy)

/* func_ov144_022995fc (vtable slot 0x44) */
MusicList *MusicList_Delete(MusicList *self)
{
    music_list_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov144_022995fc, MusicList_Delete)

/* func_ov144_0229b290: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base, the scene's vtable and its members constructed in order, the labels by __cxa_vec_ctor. */
MusicList *MusicList_New(void)
{
    MusicList *self = MenuScene_Alloc(sizeof(MusicList));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov144_0229b3f8;
    Glider0_Construct(&self->pointer);
    PushButton_Construct(&self->knob_button);
    ButtonPanel_Construct(&self->panel);
    __cxa_vec_ctor(self->labels, MUSIC_LIST_ROWS, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070c08,
                   (void (*)(void *))(uintptr_t) func_02070be8);
    LayerTask_Construct(&self->list_task);
    LayerTask_Construct(&self->buttons_task);
    ErrorMessage_Construct(&self->error);
    return self;
}
CLEAN_AS(func_ov144_0229b290, MusicList_New)
