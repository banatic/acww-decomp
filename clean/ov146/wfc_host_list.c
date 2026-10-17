/* The scene of overlay 146 (wfc_host_list.h): its destructors and flags, its graphics and
 * setup, the frame's start and end, its states (the wipes in and out), the tables its states
 * and sub states run from, its draw and its constructor. */
#include "wfc_host_list.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/oam_buffer.h"
#include "main/rom_file.h"
#include "main/screen_map.h"
#include "main/sliding_window.h"
#include "main/state_flags.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"

static_assert(offsetof(WfcHostList, wipe_y) == 0x94 && offsetof(WfcHostList, flags) == 0xac, "fields");
static_assert(offsetof(WfcHostList, chosen) == 0xbb && offsetof(WfcHostList, row_friend) == 0xbc, "chosen");
static_assert(offsetof(WfcHostList, list) == 0xea && offsetof(WfcHostList, hosts) == 0x12a, "list");
static_assert(offsetof(WfcHostList, screen) == 0x58a && offsetof(WfcHostList, rows_screen) == 0xd8a, "screens");
static_assert(offsetof(WfcHostList, palette) == 0x158a && offsetof(WfcHostList, pointer) == 0x15cc, "palettes");
static_assert(offsetof(WfcHostList, labels) == 0x1630 && offsetof(WfcHostList, screen_task) == 0x1ea0, "labels");
static_assert(offsetof(WfcHostList, window) == 0x1ee8 && offsetof(WfcHostList, knob_button) == 0x1fb4, "window");
static_assert(sizeof(WfcHostList) == 0x1ffc, "size (func_ov146_0229b364)");

/* The scene's vtable. */
extern const u8 data_ov146_0229b680[];

/* The heap the scene loads its files with. */
extern Heap *data_021fbe94;

/* The scene's files. */
extern const char data_ov146_0229b6e0[]; /* "menu/wfc/obj0.bch" */
extern const char data_ov146_0229b6f4[]; /* "menu/wfc/obj1.bch" */
extern const char data_ov146_0229b708[]; /* "menu/wfc/obj.bpl" */
extern const char data_ov146_0229b71c[]; /* "menu/wfc/bg.bch" */
extern const char data_ov146_0229b72c[]; /* "menu/wfc/bg.bpl" */
extern const char data_ov146_0229b73c[]; /* "menu/wfc/bg7.bpl" */
extern const char data_ov146_0229b750[]; /* "menu/wfc/a_bg.bsc" */
extern const char data_ov146_0229b764[]; /* "menu/wfc/b_bg.bsc" */

/* The OBJs the scene draws: a row and the chosen friend's row; the icons of a game's 1-4
 * entries; the frame, the quit and go buttons, a further cell, and the five frames of an
 * animation that plays all along. */
extern const OamEntry data_ov146_0229b5b0[], data_ov146_0229b5e0[];
extern const OamEntry data_ov146_0229b418[], data_ov146_0229b460[], data_ov146_0229b420[], data_ov146_0229b490[];
extern const OamEntry data_ov146_0229b618[], data_ov146_0229b550[], data_ov146_0229b590[], data_ov146_0229b498[];
extern const OamEntry data_ov146_0229b570[], data_ov146_0229b4d0[], data_ov146_0229b4f0[], data_ov146_0229b510[],
    data_ov146_0229b530[];

/* The labels' destructor and constructor (handed to __cxa_vec_cleanup and __cxa_vec_ctor, so
 * the game's symbols). */
extern void func_02070c08(void *label);
extern void func_02070be8(void *label);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The SDK's copy (the source first). */
extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);

/* The tables of member functions (ov004/member_pointer.h): their guards, the tables and the
 * constants they are filled from. */
extern u32 data_ov146_0229b784; /* the states' guard */
extern u32 data_ov146_0229b788; /* the sub states' guard */
extern MemberPointer data_ov146_0229b7c4[WFC_HOST_LIST_STATES];
extern MemberPointer data_ov146_0229b804[WFC_HOST_LIST_SUB_STATES];
extern const MemberPointer data_ov146_0229b400, data_ov146_0229b408, data_ov146_0229b410, data_ov146_0229b428,
    data_ov146_0229b430, data_ov146_0229b438, data_ov146_0229b440, data_ov146_0229b448, data_ov146_0229b450,
    data_ov146_0229b458, data_ov146_0229b470, data_ov146_0229b478, data_ov146_0229b480, data_ov146_0229b488;

/* The background's layer (LAYER_SUB_BG3) and the rows' (LAYER_SUB_BG1); the wipes' layers (bit
 * 1 the rows', bit 3 the background's) and margin on window 2. */
#define WFC_HOST_LIST_BG_LAYER LAYER_SUB_BG3
#define WFC_HOST_LIST_ROWS_LAYER LAYER_SUB_BG1
#define WFC_HOST_LIST_WIPE_LAYERS 0x0a
#define WFC_HOST_LIST_WIPE_MARGIN 0x28

/* The palette of the rows the shades are made in, on the rows' layer. */
#define WFC_HOST_LIST_ROWS_PALETTE 7

/* The mode the scene tells its parent it ends with (MENU_DISPATCH_MODE_CLOSE). */
#define WFC_HOST_LIST_PARENT_CLOSE 0x44

/* The message window's message and place. */
#define WFC_HOST_LIST_WINDOW_MESSAGE 0x7f

/* The frames each frame of the busy animation shows, less one. */
#define WFC_HOST_LIST_ANIM_DELAY 10
#define WFC_HOST_LIST_ANIM_FRAMES 5

static MenuScene *wfc_host_list_scene(WfcHostList *self)
{
    return &self->base;
}

static MenuDispatch *wfc_host_list_parent(WfcHostList *self)
{
    return (MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self);
}

/* An object's virtual function at `slot` of its vtable, called with nothing more. */
static void wfc_host_list_call_slot(void *object, int slot)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[slot])(object);
}

/* The members' destructors, last member first (the layer tasks have none), then the base's. */
static void wfc_host_list_destroy_members(WfcHostList *self)
{
    self->base.vtable = data_ov146_0229b680;
    PushButton_Destroy(&self->knob_button);
    MessageWindow_Destroy(&self->window);
    __cxa_vec_cleanup(self->labels, WFC_HOST_LIST_LABELS, sizeof(TextLabel), func_02070be8);
    Glider0_Destroy(&self->pointer);
    MenuScene_DestroyBase(wfc_host_list_scene(self));
}

/* func_ov146_022995a0 (vtable slot 0x40) */
WfcHostList *WfcHostList_Destroy(WfcHostList *self)
{
    wfc_host_list_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov146_022995a0, WfcHostList_Destroy)

/* func_ov146_022995f4 (vtable slot 0x44) */
WfcHostList *WfcHostList_Delete(WfcHostList *self)
{
    wfc_host_list_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov146_022995f4, WfcHostList_Delete)

/* func_ov146_02299650 */
void WfcHostList_ClearFlags(WfcHostList *self, u16 mask)
{
    self->flags &= (u16) ~mask;
}
CLEAN_AS(func_ov146_02299650, WfcHostList_ClearFlags)

/* func_ov146_02299660 */
void WfcHostList_SetFlags(WfcHostList *self, u16 mask)
{
    self->flags |= mask;
}
CLEAN_AS(func_ov146_02299660, WfcHostList_SetFlags)

/* func_ov146_02299670: 1 when any of the flags `mask` is set. */
int WfcHostList_TestFlags(WfcHostList *self, u16 mask)
{
    return (self->flags & mask) != 0;
}
CLEAN_AS(func_ov146_02299670, WfcHostList_TestFlags)

/* func_ov146_022997c8: the two layer tasks ended. */
void WfcHostList_EndLayerTasks(WfcHostList *self)
{
    LayerTask_End(&self->screen_task);
    LayerTask_End(&self->palette_task);
}
CLEAN_AS(func_ov146_022997c8, WfcHostList_EndLayerTasks)

/* func_ov146_02299e28: the rows' screen and the shaded palette queued for the rows' layer when
 * they changed; each stays to be queued until its task takes it. */
void WfcHostList_QueueLayers(WfcHostList *self)
{
    if (WfcHostList_TestFlags(self, WFC_HOST_LIST_FLAG_SCREEN_DIRTY) != 0 &&
        LayerTask_QueueScreen(&self->screen_task, (int) (uintptr_t) self->rows_screen, WFC_HOST_LIST_ROWS_LAYER,
                              sizeof(self->rows_screen), 0) != 0) {
        WfcHostList_ClearFlags(self, WFC_HOST_LIST_FLAG_SCREEN_DIRTY);
    }
    if (WfcHostList_TestFlags(self, WFC_HOST_LIST_FLAG_PALETTE_DIRTY) != 0 &&
        LayerTask_QueuePalette(&self->palette_task, (int) (uintptr_t) self->shaded_palette, WFC_HOST_LIST_ROWS_LAYER,
                               WFC_HOST_LIST_ROWS_PALETTE) != 0) {
        WfcHostList_ClearFlags(self, WFC_HOST_LIST_FLAG_PALETTE_DIRTY);
    }
}
CLEAN_AS(func_ov146_02299e28, WfcHostList_QueueLayers)

/* --- Graphics, setup and the frame --- */

/* func_ov146_0229aac8: the OBJs' characters (two files, from 0x80 and from 0x160) and palettes
 * 4-13 loaded on the sub screen. The scene is not read. */
void WfcHostList_LoadObjFiles(WfcHostList *self)
{
    (void) self;
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadCharsFromFile(data_ov146_0229b6e0, heap, LAYER_SUB_OBJ, 0x80, 0x80, 0xff);
    DisplayLayer_LoadCharsFromFile(data_ov146_0229b6f4, heap, LAYER_SUB_OBJ, 0x160, 0x160, 0x1ff);
    DisplayLayer_LoadPalettesFromFile(data_ov146_0229b708, heap, LAYER_SUB_OBJ, 4, 4, 0xd);
}
CLEAN_AS(func_ov146_0229aac8, WfcHostList_LoadObjFiles)

/* func_ov146_0229ab28: the background's characters (0x11-0x5c), palettes 1-8 and screen loaded
 * on its layer; the rows' palette read (and copied for its shades); the base screen of the rows
 * read, its row slots (lines 7-20, columns 5-14 and 16-23) given palette 7. */
void WfcHostList_LoadScreens(WfcHostList *self)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadCharsFromFile(data_ov146_0229b71c, heap, WFC_HOST_LIST_BG_LAYER, 0x11, 0x11, 0x5c);
    DisplayLayer_LoadPalettesFromFile(data_ov146_0229b72c, heap, WFC_HOST_LIST_BG_LAYER, 1, 1, 8);
    RomFile_Read(data_ov146_0229b73c, self->palette, sizeof(self->palette));
    MIi_CpuCopy16(self->palette, self->shaded_palette, sizeof(self->palette));
    DisplayLayer_LoadScreenFromFile(data_ov146_0229b750, heap, WFC_HOST_LIST_BG_LAYER);
    RomFile_Read(data_ov146_0229b764, self->screen, sizeof(self->screen));
    ScreenMap_SetPalette(self->screen, 5, 7, 0xe, 0x14, WFC_HOST_LIST_ROWS_PALETTE);
    ScreenMap_SetPalette(self->screen, 0x10, 7, 0x17, 0x14, WFC_HOST_LIST_ROWS_PALETTE);
}
CLEAN_AS(func_ov146_0229ab28, WfcHostList_LoadScreens)

/* func_ov146_0229abe0: the sub screen in BG mode 0, the background (priority 1) and the rows
 * (priority 2) set up. */
void WfcHostList_SetLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(WFC_HOST_LIST_BG_LAYER, 1);
    DisplayLayer_SetBgControl(WFC_HOST_LIST_BG_LAYER, 0, 0, 0);
    DisplayLayer_SetPriority(WFC_HOST_LIST_ROWS_LAYER, 2);
    DisplayLayer_SetBgControl(WFC_HOST_LIST_ROWS_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov146_0229abe0, WfcHostList_SetLayers)

/* func_ov146_0229ac18: the end of each frame. Until a friend is chosen, the statuses brought up
 * to date, the list made again (the rows to be set again when it changed) and the go button
 * enabled while the chosen friend can still be chosen. Then a step of the scroll, the rows'
 * labels set again when needed, the rows shaded, the layers queued, the knob settled. */
void WfcHostList_UpdateList(WfcHostList *self)
{
    if (WfcHostList_TestFlags(self, WFC_HOST_LIST_FLAG_LIST_FROZEN) == 0) {
        WfcHostList_UpdateHosts(self);
        if (WfcHostList_RefreshList(self) != 0) {
            WfcHostList_SetFlags(self, WFC_HOST_LIST_FLAG_ROWS_DIRTY);
        }
        if (WfcHostList_IsJoinable(self, self->chosen) != 0) {
            self->go_palette = WFC_HOST_LIST_BUTTON_UP;
        } else {
            self->go_palette = WFC_HOST_LIST_BUTTON_DISABLED;
        }
    }
    WfcHostList_StepScroll(self);
    if (WfcHostList_TestFlags(self, WFC_HOST_LIST_FLAG_ROWS_DIRTY) != 0) {
        WfcHostList_RefreshRowLabels(self);
        WfcHostList_ClearFlags(self, WFC_HOST_LIST_FLAG_ROWS_DIRTY);
    }
    WfcHostList_ShadeRows(self);
    WfcHostList_QueueLayers(self);
    PushButton_SettleRelease(&self->knob_button);
}
CLEAN_AS(func_ov146_0229ac18, WfcHostList_UpdateList)

/* func_ov146_0229aca0: the start of each frame: the labels' boxes closed, the layer tasks ended,
 * the knob updated (its vtable's slot 3). */
void WfcHostList_BeginFrame(WfcHostList *self)
{
    WfcHostList_CloseLabels(self);
    WfcHostList_EndLayerTasks(self);
    wfc_host_list_call_slot(&self->knob_button, 3);
}
CLEAN_AS(func_ov146_0229aca0, WfcHostList_BeginFrame)

/* func_ov146_0229acc4: the end of a frame of the scene in use. */
void WfcHostList_EndFrame(WfcHostList *self)
{
    WfcHostList_UpdateList(self);
}
CLEAN_AS(func_ov146_0229acc4, WfcHostList_EndFrame)

/* func_ov146_0229accc: the start of a frame of the scene in use: also the pointer updated (its
 * vtable's slot 3). */
void WfcHostList_BeginInteractiveFrame(WfcHostList *self)
{
    WfcHostList_BeginFrame(self);
    wfc_host_list_call_slot(&self->pointer, 3);
}
CLEAN_AS(func_ov146_0229accc, WfcHostList_BeginInteractiveFrame)

/* func_ov146_0229ace8: what the labels and the layer tasks hold let go. */
void WfcHostList_Release(WfcHostList *self)
{
    WfcHostList_CloseLabels(self);
    WfcHostList_EndLayerTasks(self);
}
CLEAN_AS(func_ov146_0229ace8, WfcHostList_Release)

/* func_ov146_0229acfc: the scene set up: no flags, the cursor at the top row, the go button
 * disabled, the quit button up; the message window opened with message 0x7f at (0x90, 0x10);
 * the knob up; no friend in the row slots, the list empty; the statuses taken from the live
 * list; no count shown yet, nothing chosen. */
void WfcHostList_Setup(WfcHostList *self)
{
    self->flags = 0;
    self->cursor = WFC_HOST_LIST_CURSOR_FIRST_ROW;
    self->go_palette = WFC_HOST_LIST_BUTTON_DISABLED;
    self->quit_palette = WFC_HOST_LIST_BUTTON_UP;
    MessageWindow_Close(&self->window);
    MessageWindow_Open(&self->window, WFC_HOST_LIST_WINDOW_MESSAGE, 0x90, 0x10);
    SlidingWindow_ShowExtra((SlidingWindow *) (void *) &self->window);
    self->titles_shown = 0;
    PushButton_ShowUp(&self->knob_button);
    for (int i = 0; i < WFC_HOST_LIST_ROWS; i++) {
        self->row_friend[i] = WFC_HOST_LIST_NONE + 1;
        self->row_shade[i] = 0xff;
    }
    for (int i = 0; i < WFC_HOST_LIST_FRIENDS; i++) {
        self->list[i] = WFC_HOST_LIST_NONE;
        self->fade[i] = 0;
    }
    WfcHostList_CopyHosts(self);
    self->host_count = WFC_HOST_LIST_FRIENDS + 1;
    self->anim_delay = WFC_HOST_LIST_ANIM_DELAY;
    self->anim_frame = 0;
    self->unk_b9 = 10;
    self->chosen = WFC_HOST_LIST_NONE;
}
CLEAN_AS(func_ov146_0229acfc, WfcHostList_Setup)

/* func_ov146_0229adb8: the layers placed by the wipe (the rows' also by the scroll, less 0x38),
 * the wipe's y kept, the knob placed. */
void WfcHostList_PlaceSprites(WfcHostList *self)
{
    MenuScene_ScrollWipe(wfc_host_list_scene(self), WFC_HOST_LIST_BG_LAYER, 0, 0);
    MenuScene_ScrollWipe(wfc_host_list_scene(self), WFC_HOST_LIST_ROWS_LAYER, 0, 0x38 - self->scroll);
    self->wipe_y = MenuScene_WipeOffsetY(wfc_host_list_scene(self));
    WfcHostList_PlaceKnob(self);
}
CLEAN_AS(func_ov146_0229adb8, WfcHostList_PlaceSprites)

/* --- The states --- */

/* func_ov146_0229adf8 (WFC_HOST_LIST_STATE_CLOSE_WIPE_OUT): the layers wipe out; when done, both
 * hidden and the scene ends (phase 5). */
void WfcHostList_WipeOut(WfcHostList *self)
{
    if (MenuScene_StepWipe(wfc_host_list_scene(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(WFC_HOST_LIST_BG_LAYER);
        DisplayLayer_HideAndResetScroll(WFC_HOST_LIST_ROWS_LAYER);
        MenuScene_SetPhase(wfc_host_list_scene(self), WFC_HOST_LIST_PHASE_END);
    } else {
        WfcHostList_PlaceSprites(self);
    }
}
CLEAN_AS(func_ov146_0229adf8, WfcHostList_WipeOut)

/* func_ov146_0229ae28 (WFC_HOST_LIST_STATE_CLOSE): the parent told the scene closes, the layers
 * start to wipe out on window 2 (state 3). */
void WfcHostList_StartWipeOut(WfcHostList *self)
{
    MenuDispatch_SetMode(wfc_host_list_parent(self), WFC_HOST_LIST_PARENT_CLOSE, 1);
    MenuScene_StartWipeOnWindow2(wfc_host_list_scene(self), WFC_HOST_LIST_WIPE_LAYERS, 0, 0, WFC_HOST_LIST_WIPE_MARGIN);
    WfcHostList_PlaceSprites(self);
    MenuScene_SetState(wfc_host_list_scene(self), WFC_HOST_LIST_STATE_CLOSE_WIPE_OUT);
}
CLEAN_AS(func_ov146_0229ae28, WfcHostList_StartWipeOut)

/* func_ov146_0229ae60 (WFC_HOST_LIST_STATE_WIPE_IN): the layers wipe in; when done, the input
 * begins (phase 2), else the titles are shown (once). */
void WfcHostList_WipeIn(WfcHostList *self)
{
    if (MenuScene_StepWipeBack(wfc_host_list_scene(self), 0) != 0) {
        MenuScene_SetPhase(wfc_host_list_scene(self), WFC_HOST_LIST_PHASE_INTERACTIVE);
        WfcHostList_BeginInput(self);
    } else {
        WfcHostList_ShowTitlesOnce(self);
    }
    WfcHostList_PlaceSprites(self);
}
CLEAN_AS(func_ov146_0229ae60, WfcHostList_WipeIn)

/* func_ov146_0229ae90 (WFC_HOST_LIST_STATE_START): the layers set up and the graphics loaded,
 * the list made, the scroll at the top, the OBJs loaded; both layers shown and wiping in on
 * window 2 over 4 frames; drawn (state 1). */
void WfcHostList_StartWipeIn(WfcHostList *self)
{
    WfcHostList_SetLayers();
    WfcHostList_LoadScreens(self);
    WfcHostList_RefreshList(self);
    WfcHostList_SetScroll(self, 0);
    self->scroll_target = 0;
    WfcHostList_LoadObjFiles(self);
    MenuScene_StartWipeCoveredOnWindow2(wfc_host_list_scene(self), WFC_HOST_LIST_WIPE_LAYERS, 4, 0, WFC_HOST_LIST_WIPE_MARGIN);
    DisplayLayer_Show(WFC_HOST_LIST_BG_LAYER);
    DisplayLayer_Show(WFC_HOST_LIST_ROWS_LAYER);
    WfcHostList_PlaceSprites(self);
    WfcHostList_SetFlags(self, WFC_HOST_LIST_FLAG_DRAWN);
    MenuScene_SetState(wfc_host_list_scene(self), WFC_HOST_LIST_STATE_WIPE_IN);
}
CLEAN_AS(func_ov146_0229ae90, WfcHostList_StartWipeIn)

/* --- The vtable's phases --- */

/* func_ov146_0229aef8 (vtable slot 0x5c, phase 5): the scene asks to be deleted. Answers 1. */
int WfcHostList_End(WfcHostList *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov146_0229aef8, WfcHostList_End)

/* func_ov146_0229af08 (vtable slot 0x58, phase 4): nothing. */
int WfcHostList_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov146_0229af08, WfcHostList_Phase4Idle)

/* func_ov146_0229af0c (vtable slot 0x54, phase 3): nothing. */
int WfcHostList_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov146_0229af0c, WfcHostList_Phase3Idle)

/* Obj_ov146_0229b680::func_ov146_0229af10 (vtable slot 0x50, phase 2): a frame of the scene in
 * use: its start, its sub state, its end. Answers 1. */
int WfcHostList_RunInteractive(WfcHostList *self)
{
    WfcHostList_BeginInteractiveFrame(self);
    WfcHostList_RunSubState(self);
    WfcHostList_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov146_0229b68019func_ov146_0229af10Ev, WfcHostList_RunInteractive)

/* Obj_ov146_0229b680::func_ov146_0229af2c: the sub state's function (WfcHostListSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 10; the game reads past the table for others. */
void WfcHostList_RunSubState(WfcHostList *self)
{
    static const MemberPointer *const sub_states[WFC_HOST_LIST_SUB_STATES] = {
        &data_ov146_0229b478, &data_ov146_0229b440, &data_ov146_0229b450, &data_ov146_0229b458, &data_ov146_0229b448,
        &data_ov146_0229b408, &data_ov146_0229b438, &data_ov146_0229b400, &data_ov146_0229b428, &data_ov146_0229b470,
    };
    MemberTable_InitOnce(&data_ov146_0229b788, data_ov146_0229b804, sub_states, WFC_HOST_LIST_SUB_STATES);
    MemberPointer_CallVoid(&data_ov146_0229b804[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov146_0229b68019func_ov146_0229af2cEv, WfcHostList_RunSubState)

/* Obj_ov146_0229b680::func_ov146_0229b004 (vtable slot 0x4c, phase 1): a frame of the scene's
 * states (WfcHostListState) through the table of member functions, filled once from its
 * constants, between the frame's start and end. Answers 1.
 * REQUIRES: the state is below 4; the game reads past the table for others. */
int WfcHostList_RunState(WfcHostList *self)
{
    static const MemberPointer *const states[WFC_HOST_LIST_STATES] = {
        &data_ov146_0229b410,
        &data_ov146_0229b430,
        &data_ov146_0229b488,
        &data_ov146_0229b480,
    };
    MemberTable_InitOnce(&data_ov146_0229b784, data_ov146_0229b7c4, states, WFC_HOST_LIST_STATES);
    WfcHostList_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov146_0229b7c4[self->base.state], self);
    WfcHostList_UpdateList(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov146_0229b68019func_ov146_0229b004Ev, WfcHostList_RunState)

/* An OBJ cell drawn on the sub screen at x 0x80, unscaled. */
static void wfc_host_list_draw_cell(const OamEntry *objs, int y, int palette, int priority)
{
    OamBuffer_DrawCell(1, objs, 0x80, y, palette, priority, 0x1000, 0x1000, 0, -1, 0, 0);
}

/* func_ov146_0229b098 (vtable slot 0x24): the scene's draw. With the keys in use the pointer is
 * drawn. While the scene is drawn: the knob and the message window (at the wipe's y) through
 * their classes (slot 2); the 7 rows from 0x60 below the wipe's y, less the scroll's part of a
 * row, the chosen friend's row apart, each with the icon of its game's entries; the frame, the
 * quit and go buttons in their palettes, a further cell; and a frame of the busy animation,
 * which steps every 11 frames. Answers 1 when drawn, else 0.
 * REQUIRES: a listed game has at most 4 entries; the game reads past its table of icons for
 * more. */
int WfcHostList_Draw(WfcHostList *self)
{
    static const OamEntry *const entry_icons[WFC_HOST_LIST_MAX_ENTRIES + 1] = {
        NULL, data_ov146_0229b418, data_ov146_0229b460, data_ov146_0229b420, data_ov146_0229b490,
    };
    static const OamEntry *const busy_frames[WFC_HOST_LIST_ANIM_FRAMES] = {
        data_ov146_0229b570, data_ov146_0229b4d0, data_ov146_0229b4f0, data_ov146_0229b510, data_ov146_0229b530,
    };

    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->pointer);
    }
    if (WfcHostList_TestFlags(self, WFC_HOST_LIST_FLAG_DRAWN) == 0) {
        return 0;
    }

    wfc_host_list_call_slot(&self->knob_button, 2);
    SlidingWindow_SetPlace((SlidingWindow *) (void *) &self->window, 0, self->wipe_y);
    wfc_host_list_call_slot(&self->window, 2);

    int y = self->wipe_y + 0x60;
    int row_y = y - (self->scroll & 0xf);
    for (int i = 0; i < WFC_HOST_LIST_ROWS; i++) {
        int place = i + self->first_row;
        if (place < WFC_HOST_LIST_FRIENDS && self->chosen < WFC_HOST_LIST_FRIENDS && self->chosen == self->list[place]) {
            wfc_host_list_draw_cell(data_ov146_0229b5e0, row_y, -1, 2);
        } else {
            wfc_host_list_draw_cell(data_ov146_0229b5b0, row_y, -1, 2);
        }
        if (place < WFC_HOST_LIST_FRIENDS) {
            const OamEntry *icon = entry_icons[self->list_entries[place]];
            if (icon != NULL) {
                wfc_host_list_draw_cell(icon, row_y, -1, 2);
            }
        }
        row_y += 16;
    }

    wfc_host_list_draw_cell(data_ov146_0229b618, y, -1, 1);
    wfc_host_list_draw_cell(data_ov146_0229b550, y, self->quit_palette, 1);
    wfc_host_list_draw_cell(data_ov146_0229b590, y, self->go_palette, 1);
    wfc_host_list_draw_cell(data_ov146_0229b498, y, -1, 1);

    if (self->anim_delay != 0) {
        self->anim_delay--;
    } else {
        self->anim_frame++;
        if (self->anim_frame >= WFC_HOST_LIST_ANIM_FRAMES) {
            self->anim_frame = 0;
        }
        self->anim_delay = WFC_HOST_LIST_ANIM_DELAY;
    }
    wfc_host_list_draw_cell(busy_frames[self->anim_frame], y, -1, 1);
    return 1;
}
CLEAN_AS(func_ov146_0229b098, WfcHostList_Draw)

/* func_ov146_0229b328 (vtable slot 0x0c): the scene closes: the parent told, then what the
 * labels and the layer tasks hold let go. Answers 1. */
int WfcHostList_Close(WfcHostList *self)
{
    MenuDispatch_ChildClosed(wfc_host_list_parent(self));
    WfcHostList_Release(self);
    return 1;
}
CLEAN_AS(func_ov146_0229b328, WfcHostList_Close)

/* func_ov146_0229b344 (vtable slot 0x00): the scene starts: its setup, state 0 (set as is) and
 * the base's wait (phase 0). Answers 1. */
int WfcHostList_Start(WfcHostList *self)
{
    WfcHostList_Setup(self);
    self->base.state = WFC_HOST_LIST_STATE_START;
    MenuScene_SetPhase(wfc_host_list_scene(self), WFC_HOST_LIST_PHASE_WAIT);
    return 1;
}
CLEAN_AS(func_ov146_0229b344, WfcHostList_Start)

/* func_ov146_0229b364: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base, the scene's vtable and its members constructed in order, the labels by __cxa_vec_ctor. */
WfcHostList *WfcHostList_New(void)
{
    WfcHostList *self = MenuScene_Alloc(sizeof(WfcHostList));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov146_0229b680;
    Glider0_Construct(&self->pointer);
    __cxa_vec_ctor(self->labels, WFC_HOST_LIST_LABELS, sizeof(TextLabel), func_02070c08, func_02070be8);
    LayerTask_Construct(&self->screen_task);
    LayerTask_Construct(&self->palette_task);
    MessageWindow_Construct(&self->window);
    PushButton_Construct(&self->knob_button);
    return self;
}
CLEAN_AS(func_ov146_0229b364, WfcHostList_New)
