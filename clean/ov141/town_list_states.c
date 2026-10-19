/* The town list of overlay 141 (town_list.h): its graphics, the frame's start and end, its
 * setup and teardown, the states, the draw and the vtable's slots. */
#include "town_list.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/group_params.h"
#include "main/oam_buffer.h"
#include "main/rom_file.h"
#include "main/screen_map.h"
#include "main/state_flags.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"
#include "ov139/res_rows.h"

/* The scene's vtable. */
extern const u8 data_ov141_0229af48[];

/* The cells of overlay 139's object (func_ov139_022995d8). */
#define TOWN_LIST_CELL_FRAME 0
#define TOWN_LIST_CELL_PICKED 1
#define TOWN_LIST_CELL_QUIT 2
#define TOWN_LIST_CELL_OK 3

/* The heap the scenes load into (autoload_2/heap.c). */
extern Heap *data_021fbe94;

/* The files of the list's BG layer 6: its screen and its palettes. */
extern const char data_ov141_0229afa8[]; /* "menu/res/b0_bg.bsc" */
extern const char data_ov141_0229afbc[]; /* "menu/res/ten0.bpl" */

/* What the parent (overlay 92's) is told when the scene wipes out: the menu closes. */
#define TOWN_LIST_PARENT_CLOSE 0x44

static MenuScene *town_list_scene(TownList *self)
{
    return &self->base;
}

static MenuDispatch *town_list_parent(TownList *self)
{
    return (MenuDispatch *) Process_GetParent((Process *) (void *) self);
}

static void *town_list_rows(TownList *self)
{
    return self->rows;
}

/* func_ov141_0229a834: overlay 139's OBJ graphics and the panel's text colours loaded. */
void TownList_LoadPanelGraphics(TownList *self)
{
    ResRows_LoadObjFiles(town_list_rows(self));
    ButtonPanel_LoadTextColors(&self->panel);
}
CLEAN_AS(func_ov141_0229a834, TownList_LoadPanelGraphics)

/* func_ov141_0229a850: overlay 139's BG graphics loaded and its rows cleared; layer 6's screen
 * read into `screen`, two of its rectangles set to palette 7 and queued; layer 6's palette 3
 * loaded. */
void TownList_LoadGraphics(TownList *self)
{
    ResRows_LoadBg(town_list_rows(self));
    ResRows_ClearRows(town_list_rows(self));
    RomFile_Read(data_ov141_0229afa8, self->screen, sizeof(self->screen));
    ScreenMap_SetPalette(self->screen, 7, 8, 0x10, 0x13, 7);
    ScreenMap_SetPalette(self->screen, 0x12, 8, 0x19, 0x13, 7);
    TownList_SetFlags(self, TOWN_LIST_FLAG_SCREEN_DIRTY);
    DisplayLayer_LoadPalettesFromFile(data_ov141_0229afbc, data_021fbe94, 6, 3, 3, 3);
}
CLEAN_AS(func_ov141_0229a850, TownList_LoadGraphics)

/* func_ov141_0229a8d0: the sub screen's BG mode 0, layers 6, 4 and 3 at priority 2 with a
 * plain control. */
void TownList_SetUpLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(6, 2);
    DisplayLayer_SetBgControl(6, 0, 0, 0);
    DisplayLayer_SetPriority(4, 2);
    DisplayLayer_SetBgControl(4, 0, 0, 0);
    DisplayLayer_SetPriority(3, 2);
    DisplayLayer_SetBgControl(3, 0, 0, 0);
}
CLEAN_AS(func_ov141_0229a8d0, TownList_SetUpLayers)

/* func_ov141_0229a91c: the end of a frame: the screen queued when it changed, and overlay
 * 139's end. */
void TownList_EndFrame(TownList *self)
{
    TownList_QueueScreen(self);
    ResRows_QueuePalette(town_list_rows(self));
}
CLEAN_AS(func_ov141_0229a91c, TownList_EndFrame)

/* func_ov141_0229a934: the start of a frame: the screen's task ended, the panel's texts closed
 * and overlay 139's start. */
void TownList_BeginFrame(TownList *self)
{
    LayerTask_End(&self->screen_task);
    ButtonPanel_CloseTexts(&self->panel);
    ResRows_Teardown(town_list_rows(self));
}
CLEAN_AS(func_ov141_0229a934, TownList_BeginFrame)

/* func_ov141_0229a960: the end of an interactive frame. */
void TownList_EndInteractiveFrame(TownList *self)
{
    TownList_EndFrame(self);
}
CLEAN_AS(func_ov141_0229a960, TownList_EndInteractiveFrame)

/* func_ov141_0229a968: the start of an interactive frame, then the cursor sprite's update
 * through its class (vtable slot 3). */
void TownList_BeginInteractiveFrame(TownList *self)
{
    TownList_BeginFrame(self);
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) self->cursor_sprite.vtable;
    vtable[3](&self->cursor_sprite);
}
CLEAN_AS(func_ov141_0229a968, TownList_BeginInteractiveFrame)

/* func_ov141_0229a984: the members torn down: the panel's texts closed, overlay 139's
 * teardown, the screen's task ended. */
void TownList_Teardown(TownList *self)
{
    ButtonPanel_CloseTexts(&self->panel);
    ResRows_End(town_list_rows(self));
    LayerTask_End(&self->screen_task);
}
CLEAN_AS(func_ov141_0229a984, TownList_Teardown)

/* func_ov141_0229a9b0: the scene's own fields set up: no flag, overlay 139's object on layer 6,
 * every row empty, none picked, the quit button as drawn, the cursor on the first row. */
void TownList_Setup(TownList *self)
{
    self->flags = 0;
    ResRows_Open(town_list_rows(self), 6, 0x7e);
    for (int row = 0; row < TOWN_LIST_ROWS; row++) {
        self->row_state[row] = TOWN_LIST_ROW_EMPTY;
    }
    TownList_SetPicked(self, -1);
    self->quit_palette = TOWN_LIST_BUTTON_NORMAL;
    self->cursor = TOWN_LIST_ROW_FIRST;
}
CLEAN_AS(func_ov141_0229a9b0, TownList_Setup)

/* func_ov141_0229aa04: layer 6 scrolled with the wipe, and the wipe's y kept. */
void TownList_ScrollWithWipe(TownList *self)
{
    MenuScene_ScrollWipe(town_list_scene(self), 6, 0, 0);
    self->wipe_y = MenuScene_WipeOffsetY(town_list_scene(self));
}
CLEAN_AS(func_ov141_0229aa04, TownList_ScrollWithWipe)

/* func_ov141_0229aa28 (state 4): the wipe out stepped; at its end layer 6 hidden and the scene
 * deleted (phase 5); before, the layer follows it. */
void TownList_WipeOut(TownList *self)
{
    if (MenuScene_StepWipe(town_list_scene(self), 0)) {
        DisplayLayer_HideAndResetScroll(6);
        MenuScene_SetPhase(town_list_scene(self), TOWN_LIST_PHASE_DELETE);
    } else {
        TownList_ScrollWithWipe(self);
    }
}
CLEAN_AS(func_ov141_0229aa28, TownList_WipeOut)

/* func_ov141_0229aa54 (state 3): the parent told the menu closes, the wipe out started on
 * window 2 (layer 8, margin 0x30) with the layer following it; state 4. */
void TownList_StartWipeOut(TownList *self)
{
    TownList_BeforeWipeOut();
    MenuDispatch_SetMode(town_list_parent(self), TOWN_LIST_PARENT_CLOSE, 1);
    MenuScene_StartWipeOnWindow2(town_list_scene(self), 8, 0, 0, 0x30);
    TownList_ScrollWithWipe(self);
    MenuScene_SetState(town_list_scene(self), TOWN_LIST_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov141_0229aa54, TownList_StartWipeOut)

/* func_ov141_0229aa94 (state 2): the wipe in stepped; at its end the scene goes interactive
 * (phase 2) by touch or the keys. The layer follows the wipe. */
void TownList_WipeIn(TownList *self)
{
    if (MenuScene_StepWipeBack(town_list_scene(self), 0)) {
        MenuScene_SetPhase(town_list_scene(self), TOWN_LIST_PHASE_INTERACTIVE);
        TownList_Resume(self);
        TownList_AfterWipeIn(self);
    }
    TownList_ScrollWithWipe(self);
}
CLEAN_AS(func_ov141_0229aa94, TownList_WipeIn)

/* func_ov141_0229aac4 (state 1): overlay 139's labels opened, the wipe in started covered on
 * window 2 (layer 8, 4 frames, margin 0x30), layer 6 shown and following it, the scene drawn;
 * state 2. */
void TownList_StartWipeIn(TownList *self)
{
    ResRows_MakeHeadings(town_list_rows(self));
    MenuScene_StartWipeCoveredOnWindow2(town_list_scene(self), 8, 4, 0, 0x30);
    DisplayLayer_Show(6);
    TownList_ScrollWithWipe(self);
    TownList_SetFlags(self, TOWN_LIST_FLAG_DRAWN);
    MenuScene_SetState(town_list_scene(self), TOWN_LIST_STATE_WIPE_IN);
}
CLEAN_AS(func_ov141_0229aac4, TownList_StartWipeIn)

/* func_ov141_0229ab04 (state 0): the layers set up, the graphics loaded; state 1. */
void TownList_StartSetup(TownList *self)
{
    TownList_SetUpLayers();
    TownList_LoadGraphics(self);
    TownList_LoadPanelGraphics(self);
    MenuScene_SetState(town_list_scene(self), TOWN_LIST_STATE_START_WIPE_IN);
}
CLEAN_AS(func_ov141_0229ab04, TownList_StartSetup)

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* func_ov141_0229ab28 (vtable slot 0x5c, phase 5): main told the result: after a quit 0; else
 * 1, with the picked row's parent and data copied to the places GroupParams keeps (those that
 * are set). The places are cleared and the scene asks to be deleted. Answers 1.
 * REQUIRES: a row is picked unless the scene was quit (TownList_Confirm is only reached so). */
int TownList_End(TownList *self)
{
    if (TownList_TestFlags(self, TOWN_LIST_FLAG_QUIT)) {
        GroupParams_SetC4C(0);
    } else {
        GroupParams_SetC4C(1);
        u32 *parent = GroupParams_C80();
        if (parent != NULL) {
            MI_CpuCopy8(&self->parents[self->picked], parent, sizeof(LocalParent));
        }
        int data = GroupParams_C88();
        if (data != 0) {
            MI_CpuCopy8(self->data[self->picked], (void *) (uintptr_t) (u32) data, TOWN_LIST_DATA_SIZE);
        }
    }
    GroupParams_ClearC80C88();
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov141_0229ab28, TownList_End)

/* func_ov141_0229ab9c (vtable slot 0x58, phase 4): nothing. */
int TownList_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov141_0229ab9c, TownList_Phase4Idle)

/* func_ov141_0229aba0 (vtable slot 0x54, phase 3): nothing. */
int TownList_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov141_0229aba0, TownList_Phase3Idle)

/* Obj_ov141_0229af48::func_ov141_0229aba4 (vtable slot 0x50, phase 2): a frame of the list in
 * use: its start, its sub state and its end. Answers 1. */
int TownList_RunInteractive(TownList *self)
{
    TownList_BeginInteractiveFrame(self);
    TownList_RunSubState(self);
    TownList_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov141_0229af4819func_ov141_0229aba4Ev, TownList_RunInteractive)

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables and their
 * constants. */
extern u32 data_ov141_0229afe0; /* the sub states' guard */
extern u32 data_ov141_0229afe4; /* the states' guard */
extern MemberPointer data_ov141_0229afe8[TOWN_LIST_STATES];
extern MemberPointer data_ov141_0229b010[TOWN_LIST_SUB_STATES];
extern const MemberPointer data_ov141_0229aee8, data_ov141_0229aef0, data_ov141_0229aef8, data_ov141_0229af00,
    data_ov141_0229af08, data_ov141_0229af10, data_ov141_0229af18, data_ov141_0229af20, data_ov141_0229af28,
    data_ov141_0229af30, data_ov141_0229af38;

/* Obj_ov141_0229af48::func_ov141_0229abc0: the sub state's function (TownListSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 6; the game reads past the table for others. */
void TownList_RunSubState(TownList *self)
{
    static const MemberPointer *const sub_states[TOWN_LIST_SUB_STATES] = {
        &data_ov141_0229af00, &data_ov141_0229af08, &data_ov141_0229aef8,
        &data_ov141_0229aef0, &data_ov141_0229aee8, &data_ov141_0229af10,
    };
    MemberTable_InitOnce(&data_ov141_0229afe0, data_ov141_0229b010, sub_states, TOWN_LIST_SUB_STATES);
    MemberPointer_CallVoid(&data_ov141_0229b010[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov141_0229af4819func_ov141_0229abc0Ev, TownList_RunSubState)

/* Obj_ov141_0229af48::func_ov141_0229ac60 (vtable slot 0x4c, phase 1): a frame of the scene's
 * states (TownListState) between the frame's start and end, through the table of member
 * functions (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 5; the game reads past the table for others. */
int TownList_RunState(TownList *self)
{
    static const MemberPointer *const states[TOWN_LIST_STATES] = {
        &data_ov141_0229af18, &data_ov141_0229af38, &data_ov141_0229af30, &data_ov141_0229af28, &data_ov141_0229af20,
    };
    MemberTable_InitOnce(&data_ov141_0229afe4, data_ov141_0229afe8, states, TOWN_LIST_STATES);
    TownList_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov141_0229afe8[self->base.state], self);
    TownList_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov141_0229af4819func_ov141_0229ac60Ev, TownList_RunState)

/* The address of cell `cell` of overlay 139's object. */
static const OamEntry *town_list_cell(TownList *self, unsigned int cell)
{
    return (const OamEntry *) (uintptr_t) ResRows_Cells((unsigned int) (uintptr_t) town_list_rows(self), cell);
}

/* A cell drawn at (0x80, y) on the sub screen in `palette` (-1: its own) at priority 2,
 * unscaled. */
static void town_list_draw_cell(const OamEntry *cell, int y, int palette)
{
    OamBuffer_DrawCell(1, cell, 0x80, y, palette, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}

/* func_ov141_0229ad00 (vtable slot 0x24): the scene's draw: the cursor sprite (with the keys in
 * use), then, while the scene is drawn (else answers 0), the panel, the cells of overlay 139's
 * object at the wipe's y kept plus 0x60 (the mark at the row picked, if any, before the frame;
 * the buttons in their palettes) and its rows. Answers 1. */
int TownList_Draw(TownList *self)
{
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    if (TownList_TestFlags(self, TOWN_LIST_FLAG_DRAWN) == 0) {
        return 0;
    }
    ButtonPanel_Draw(&self->panel, self->panel_offset);

    int y = self->wipe_y + 0x60;
    const OamEntry *frame = town_list_cell(self, TOWN_LIST_CELL_FRAME);
    const OamEntry *mark = town_list_cell(self, TOWN_LIST_CELL_PICKED);
    const OamEntry *quit = town_list_cell(self, TOWN_LIST_CELL_QUIT);
    const OamEntry *ok = town_list_cell(self, TOWN_LIST_CELL_OK);
    if (self->picked != -1) {
        town_list_draw_cell(mark, y + (self->picked << 4), -1);
    }
    town_list_draw_cell(frame, y, -1);
    town_list_draw_cell(quit, y, self->quit_palette);
    town_list_draw_cell(ok, y, self->ok_palette);
    ResRows_DrawAt(town_list_rows(self), 0, self->wipe_y);
    return 1;
}
CLEAN_AS(func_ov141_0229ad00, TownList_Draw)

/* func_ov141_0229ae44 (vtable slot 0x0c): the scene closes: the parent told and the members
 * torn down. Answers 1. */
int TownList_Close(TownList *self)
{
    MenuDispatch_ChildClosed(town_list_parent(self));
    TownList_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov141_0229ae44, TownList_Close)

/* func_ov141_0229ae60 (vtable slot 0x00): the scene starts: its setup, state 0 (set directly)
 * and phase 0. Answers 1. */
int TownList_Start(TownList *self)
{
    TownList_Setup(self);
    self->base.state = TOWN_LIST_STATE_START_SETUP;
    MenuScene_SetPhase(town_list_scene(self), TOWN_LIST_PHASE_WAIT);
    return 1;
}
CLEAN_AS(func_ov141_0229ae60, TownList_Start)

/* func_ov141_0229ae80 (named by the profile at 0x0229aee0): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order. */
TownList *TownList_New(void)
{
    TownList *self = MenuScene_Alloc(sizeof(TownList));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov141_0229af48;
    ResRows_Construct((ResRows *) (void *) self->rows);
    Glider0_Construct(&self->cursor_sprite);
    ButtonPanel_Construct(&self->panel);
    LayerTask_Construct(&self->screen_task);
    return self;
}
CLEAN_AS(func_ov141_0229ae80, TownList_New)
