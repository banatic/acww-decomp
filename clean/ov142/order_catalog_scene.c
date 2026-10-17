/* The order catalog as a menu scene (order_catalog_scene.h): its graphics and layers, the
 * frames, the states, the draw, and its construction and destruction. */
#include "order_catalog_scene.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/oam_buffer.h"
#include "main/rom_file.h"
#include "main/state_flags.h"
#include "order_catalog_cursor.h"
#include "order_catalog_list.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"

/* The scene's vtable. */
extern const u8 data_ov142_0229c3e8[];

/* The heap the scenes load into (autoload_2/heap.c). */
extern Heap *data_021fbe94;

/* The files: "menu/catalog/obj0.bch", "obj1.bch", "obj.bpl", "bg0.bch", "bg1.bch", "bg.bpl",
 * "bg_3.bpl", "bg_4.bpl", "b_bg.bsc" and "a_bg.bsc". */
extern const char data_ov142_0229c4d8[];
extern const char data_ov142_0229c4f0[];
extern const char data_ov142_0229c508[];
extern const char data_ov142_0229c520[];
extern const char data_ov142_0229c538[];
extern const char data_ov142_0229c550[];
extern const char data_ov142_0229c564[];
extern const char data_ov142_0229c57c[];
extern const char data_ov142_0229c594[];
extern const char data_ov142_0229c5ac[];

/* The OBJs drawn: the down arrow, the bar's two ends, the up arrow, the order button's cell, a
 * row's cell and the picked row's, and the tabs (two OBJs each, the last tab's first). */
extern const OamEntry data_ov142_0229c358;
extern const OamEntry data_ov142_0229c360;
extern const OamEntry data_ov142_0229c368;
extern const OamEntry data_ov142_0229c370;
extern const OamEntry data_ov142_0229c378[];
extern const OamEntry data_ov142_0229c398[];
extern const OamEntry data_ov142_0229c3b8[];
extern const OamEntry data_ov142_0229c448[2 * ORDER_CATALOG_CATEGORIES];

/* The labels' destructor and constructor (handed to __cxa_vec_cleanup and __cxa_vec_ctor, so
 * the game's symbols). */
extern void func_02070c08(void *label);
extern void func_02070be8(void *label);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The title (message 0xb8) and the panel's messages: the catalog's (layout 5) and the
 * confirmation's (layout 12). */
#define ORDER_CATALOG_MESSAGE_TITLE 0xb8
#define ORDER_CATALOG_MESSAGE_PANEL 0x65
#define ORDER_CATALOG_MESSAGE_CONFIRM 0x22

static MenuScene *catalog_base(OrderCatalog *self)
{
    return &self->base;
}

static MenuDispatch *catalog_parent(OrderCatalog *self)
{
    return (MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self);
}

/* A member's virtual function (slot 2 draws, slot 3 updates). */
static void catalog_member_slot(void *object, int slot)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[slot])(object);
}

/* The members' destructors, last member first, then the base's. */
static void catalog_destroy_members(OrderCatalog *self)
{
    self->base.vtable = data_ov142_0229c3e8;
    __cxa_vec_cleanup(self->labels, ORDER_CATALOG_LABELS, sizeof(TextLabel), func_02070be8);
    ButtonPanel_Destroy(&self->panel);
    PushButton_Destroy(&self->thumb_button);
    Glider0_Destroy(&self->cursor_sprite);
    MenuScene_DestroyBase(catalog_base(self));
}

/* func_ov142_022995a0 (vtable slot 0x40) */
OrderCatalog *OrderCatalog_Destroy(OrderCatalog *self)
{
    catalog_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov142_022995a0, OrderCatalog_Destroy)

/* func_ov142_022995f0 (vtable slot 0x44) */
OrderCatalog *OrderCatalog_Delete(OrderCatalog *self)
{
    catalog_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov142_022995f0, OrderCatalog_Delete)

/* func_ov142_0229b804: the panel's text colours, and the OBJ characters (0xc0-0x11f from
 * "obj0.bch", 0x120-0x17f from "obj1.bch") and OBJ palettes 4-9 from the scenes' heap. */
void OrderCatalog_LoadObjGraphics(OrderCatalog *self)
{
    ButtonPanel_LoadTextColors(&self->panel);
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadCharsFromFile(data_ov142_0229c4d8, heap, 8, 0xc0, 0xc0, 0x11f);
    DisplayLayer_LoadCharsFromFile(data_ov142_0229c4f0, heap, 8, 0x120, 0x120, 0x17f);
    DisplayLayer_LoadPalettesFromFile(data_ov142_0229c508, heap, 8, 4, 4, 9);
}
CLEAN_AS(func_ov142_0229b804, OrderCatalog_LoadObjGraphics)

/* func_ov142_0229b874: layer 6's characters (0x11-0x51 and 0x156-0x174) and palettes 1-5, then
 * the rows' two palettes and the rows' and the frame's screens read into the scene. */
void OrderCatalog_LoadBgGraphics(OrderCatalog *self)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadCharsFromFile(data_ov142_0229c520, heap, 6, 0x11, 0x11, 0x51);
    DisplayLayer_LoadCharsFromFile(data_ov142_0229c538, heap, 6, 0x156, 0x156, 0x174);
    DisplayLayer_LoadPalettesFromFile(data_ov142_0229c550, heap, 6, 1, 1, 5);
    RomFile_Read(data_ov142_0229c564, self->row_palette, 0x20);
    RomFile_Read(data_ov142_0229c57c, self->picked_palette, 0x20);
    RomFile_Read(data_ov142_0229c594, self->rows_screen, 0x800);
    RomFile_Read(data_ov142_0229c5ac, self->frame_screen, 0x800);
}
CLEAN_AS(func_ov142_0229b874, OrderCatalog_LoadBgGraphics)

/* func_ov142_0229b928: the sub screen's background mode 0; layer 6 at priority 1, layers 4 and 3
 * at priority 2, each with its control reset. */
void OrderCatalog_SetUpLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(6, 1);
    DisplayLayer_SetBgControl(6, 0, 0, 0);
    DisplayLayer_SetPriority(4, 2);
    DisplayLayer_SetBgControl(4, 0, 0, 0);
    DisplayLayer_SetPriority(3, 2);
    DisplayLayer_SetBgControl(3, 0, 0, 0);
}
CLEAN_AS(func_ov142_0229b928, OrderCatalog_SetUpLayers)

/* func_ov142_0229b974: the frame's end: the fade and the scroll stepped, what is to be done
 * done, and the thumb's release settled. */
void OrderCatalog_EndFrame(OrderCatalog *self)
{
    OrderCatalog_StepFade(self);
    OrderCatalog_StepScroll(self);
    OrderCatalog_FlushChanges(self);
    PushButton_SettleRelease(&self->thumb_button);
}
CLEAN_AS(func_ov142_0229b974, OrderCatalog_EndFrame)

/* func_ov142_0229b99c: the frame's start: the four loads ended, the labels and the panel's texts
 * closed, and the thumb updated (through its class, vtable slot 3). */
void OrderCatalog_BeginFrame(OrderCatalog *self)
{
    for (int i = 0; i < ORDER_CATALOG_TASKS; i++) {
        LayerTask_End(&self->tasks[i]);
    }
    OrderCatalog_CloseLabels(self);
    ButtonPanel_CloseTexts(&self->panel);
    catalog_member_slot(&self->thumb_button, 3);
}
CLEAN_AS(func_ov142_0229b99c, OrderCatalog_BeginFrame)

/* func_ov142_0229b9f8 */
void OrderCatalog_EndInteractiveFrame(OrderCatalog *self)
{
    OrderCatalog_EndFrame(self);
}
CLEAN_AS(func_ov142_0229b9f8, OrderCatalog_EndInteractiveFrame)

/* func_ov142_0229ba00: the frame's start, then the cursor sprite updated (through its class). */
void OrderCatalog_BeginInteractiveFrame(OrderCatalog *self)
{
    OrderCatalog_BeginFrame(self);
    catalog_member_slot(&self->cursor_sprite, 3);
}
CLEAN_AS(func_ov142_0229ba00, OrderCatalog_BeginInteractiveFrame)

/* func_ov142_0229ba18: the members torn down: the labels and the panel's texts closed, the four
 * loads ended. */
void OrderCatalog_Teardown(OrderCatalog *self)
{
    OrderCatalog_CloseLabels(self);
    ButtonPanel_CloseTexts(&self->panel);
    for (int i = 0; i < ORDER_CATALOG_TASKS; i++) {
        LayerTask_End(&self->tasks[i]);
    }
}
CLEAN_AS(func_ov142_0229ba18, OrderCatalog_Teardown)

/* func_ov142_0229ba64: the setup: no counts, no items shown, no flags, no category shown, the
 * rows not faded; nothing picked; the nine lists collected from the player's item record; the
 * thumb at rest. */
void OrderCatalog_Setup(OrderCatalog *self)
{
    for (int i = 0; i < ORDER_CATALOG_CATEGORIES; i++) {
        self->counts[i] = 0;
        self->listed[i] = 0;
    }
    for (int i = 0; i < ORDER_CATALOG_ROWS; i++) {
        self->shown[i] = ORDER_CATALOG_NO_ITEM;
    }
    self->flags = 0;
    self->category = ORDER_CATALOG_NO_CATEGORY;
    self->fade_step = 3;
    self->fade_state = ORDER_CATALOG_FADE_NONE;
    OrderCatalog_PickItem(self, ORDER_CATALOG_NO_CATEGORY, -1);
    OrderCatalog_ListCategory0(self);
    OrderCatalog_ListWallpaper(self);
    OrderCatalog_ListCarpets(self);
    OrderCatalog_ListCategory3(self);
    OrderCatalog_ListCategory4(self);
    OrderCatalog_ListCategory6(self);
    OrderCatalog_ListCategory5(self);
    OrderCatalog_ListCategory7(self);
    OrderCatalog_ListCategory8(self);
    PushButton_ShowUp(&self->thumb_button);
}
CLEAN_AS(func_ov142_0229ba64, OrderCatalog_Setup)

/* func_ov142_0229bb08: layer 6 scrolled with the wipe, layer 4 with it and the list's scroll;
 * the wipe's y kept (for the draw and the panel) and the thumb placed. */
void OrderCatalog_ScrollWithWipe(OrderCatalog *self)
{
    MenuScene_ScrollWipe(catalog_base(self), 6, 0, 0);
    int scroll = self->scroll;
    MenuScene_ScrollWipe(catalog_base(self), 4, 0, 0x20 - scroll);
    self->wipe_y = MenuScene_WipeOffsetY(catalog_base(self));
    self->panel_wipe_y = self->wipe_y;
    OrderCatalog_PlaceThumb(self);
}
CLEAN_AS(func_ov142_0229bb08, OrderCatalog_ScrollWithWipe)

/* func_ov142_0229bb54 (state 7): the panel's wipe back stepped; at its end, back to the catalog
 * (phase 2). The panel follows the wipe. */
void OrderCatalog_PanelInToBrowse(OrderCatalog *self)
{
    if (MenuScene_StepWipeBack(catalog_base(self), -1)) {
        OrderCatalog_Resume(self);
        MenuScene_SetPhase(catalog_base(self), 2);
    }
    self->panel_wipe_y = MenuScene_WipeOffsetY(catalog_base(self));
}
CLEAN_AS(func_ov142_0229bb54, OrderCatalog_PanelInToBrowse)

/* func_ov142_0229bb84 (state 6): the panel's wipe stepped; at its end the panel in layout 5
 * (message 0x65) wipes back in (state 7). The panel follows the wipe. */
void OrderCatalog_PanelOutToBrowse(OrderCatalog *self)
{
    if (MenuScene_StepWipe(catalog_base(self), -1) != 0) {
        MenuScene_SetState(catalog_base(self), ORDER_CATALOG_STATE_BACK_IN);
        MenuScene_StartWipeCovered(catalog_base(self), 0, 0);
        ButtonPanel_SetLayout5(&self->panel, ORDER_CATALOG_MESSAGE_PANEL);
    }
    self->panel_wipe_y = MenuScene_WipeOffsetY(catalog_base(self));
}
CLEAN_AS(func_ov142_0229bb84, OrderCatalog_PanelOutToBrowse)

/* func_ov142_0229bbc4 (state 5): the panel's wipe back stepped; at its end the confirmation
 * (phase 2). The panel follows the wipe. */
void OrderCatalog_PanelInToConfirm(OrderCatalog *self)
{
    if (MenuScene_StepWipeBack(catalog_base(self), -1) != 0) {
        OrderCatalog_ResumeConfirm(self);
        MenuScene_SetPhase(catalog_base(self), 2);
    }
    self->panel_wipe_y = MenuScene_WipeOffsetY(catalog_base(self));
}
CLEAN_AS(func_ov142_0229bbc4, OrderCatalog_PanelInToConfirm)

/* func_ov142_0229bbf4 (state 4): the panel's wipe stepped; at its end the panel in layout 12
 * (message 0x22, the confirmation) wipes back in (state 5). The panel follows the wipe. */
void OrderCatalog_PanelOutToConfirm(OrderCatalog *self)
{
    if (MenuScene_StepWipe(catalog_base(self), -1)) {
        MenuScene_SetState(catalog_base(self), ORDER_CATALOG_STATE_CONFIRM_IN);
        MenuScene_StartWipeCovered(catalog_base(self), 0, 0);
        ButtonPanel_SetLayout12(&self->panel, ORDER_CATALOG_MESSAGE_CONFIRM);
    }
    self->panel_wipe_y = MenuScene_WipeOffsetY(catalog_base(self));
}
CLEAN_AS(func_ov142_0229bbf4, OrderCatalog_PanelOutToConfirm)

/* func_ov142_0229bc34 (state 3): the wipe out stepped; at its end layers 6 and 4 hidden and the
 * scene deleted (phase 5); before, the layers follow it. */
void OrderCatalog_WipeOut(OrderCatalog *self)
{
    if (MenuScene_StepWipe(catalog_base(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(6);
        DisplayLayer_HideAndResetScroll(4);
        MenuScene_SetPhase(catalog_base(self), 5);
    } else {
        OrderCatalog_ScrollWithWipe(self);
    }
}
CLEAN_AS(func_ov142_0229bc34, OrderCatalog_WipeOut)

/* func_ov142_0229bc64 (state 2): the parent told the menu closes (with its sound), the wipe out
 * started on window 2 (layers 2 and 8, margin 0x18) and state 3. */
void OrderCatalog_StartWipeOut(OrderCatalog *self)
{
    MenuDispatch_SetMode(catalog_parent(self), MENU_DISPATCH_MODE_CLOSE, 1);
    MenuScene_StartWipeOnWindow2(catalog_base(self), 0xa, 0, 0, 0x18);
    OrderCatalog_ScrollWithWipe(self);
    MenuScene_SetState(catalog_base(self), ORDER_CATALOG_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov142_0229bc64, OrderCatalog_StartWipeOut)

/* func_ov142_0229bc9c (state 1): the first time, the scene drawn, the title (message 0xb8 at
 * (0x16d, 4), colour 15) and the price's place shown; the wipe in stepped, and at its end the
 * catalog (phase 2). The layers follow the wipe. */
void OrderCatalog_WipeIn(OrderCatalog *self)
{
    if (OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_DRAWN) == 0) {
        OrderCatalog_SetFlags(self, ORDER_CATALOG_FLAG_DRAWN);
        OrderCatalog_ShowMessage(self, ORDER_CATALOG_MESSAGE_TITLE, 0x16d, 4, 0xf, 0);
        OrderCatalog_ClearPriceLabel(self);
    }
    if (MenuScene_StepWipeBack(catalog_base(self), 0) != 0) {
        MenuScene_SetPhase(catalog_base(self), 2);
        OrderCatalog_Resume(self);
    }
    OrderCatalog_ScrollWithWipe(self);
}
CLEAN_AS(func_ov142_0229bc9c, OrderCatalog_WipeIn)

/* func_ov142_0229bcfc (state 0): the layers set up, the graphics loaded, list 0 shown, the wipe
 * in started covered on window 2 (layers 2 and 8, 4 frames, margin 0x18), layers 6 and 4 shown
 * and following it, the panel in layout 5 (message 0x65); state 1. */
void OrderCatalog_StartWipeIn(OrderCatalog *self)
{
    OrderCatalog_SetUpLayers();
    OrderCatalog_LoadBgGraphics(self);
    OrderCatalog_ShowCategory(self, ORDER_CATALOG_CATEGORY_0);
    OrderCatalog_LoadObjGraphics(self);
    MenuScene_StartWipeCoveredOnWindow2(catalog_base(self), 0xa, 4, 0, 0x18);
    DisplayLayer_Show(6);
    DisplayLayer_Show(4);
    OrderCatalog_ScrollWithWipe(self);
    ButtonPanel_SetLayout5(&self->panel, ORDER_CATALOG_MESSAGE_PANEL);
    MenuScene_SetState(catalog_base(self), ORDER_CATALOG_STATE_WIPE_IN);
}
CLEAN_AS(func_ov142_0229bcfc, OrderCatalog_StartWipeIn)

/* func_ov142_0229bd5c (vtable slot 0x5c, phase 5): the scene asks to be deleted. */
int OrderCatalog_End(OrderCatalog *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov142_0229bd5c, OrderCatalog_End)

/* func_ov142_0229bd6c (vtable slot 0x58, phase 4): nothing. */
int OrderCatalog_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov142_0229bd6c, OrderCatalog_Phase4Idle)

/* func_ov142_0229bd70 (vtable slot 0x54, phase 3): nothing. */
int OrderCatalog_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov142_0229bd70, OrderCatalog_Phase3Idle)

/* Obj_ov142_0229c3e8::func_ov142_0229bd74 (vtable slot 0x50, phase 2): a frame of the scene in
 * use: its start, its sub state and its end. Answers 1. */
int OrderCatalog_RunInteractive(OrderCatalog *self)
{
    OrderCatalog_BeginInteractiveFrame(self);
    OrderCatalog_RunSubState(self);
    OrderCatalog_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov142_0229c3e819func_ov142_0229bd74Ev, OrderCatalog_RunInteractive)

/* The table of member functions of the states (ov004/member_pointer.h): its guard, the table
 * and its constants. */
extern u32 data_ov142_0229c5e0;
extern MemberPointer data_ov142_0229c610[ORDER_CATALOG_STATES];
extern const MemberPointer data_ov142_0229c2a0, data_ov142_0229c318, data_ov142_0229c328, data_ov142_0229c330,
    data_ov142_0229c338, data_ov142_0229c340, data_ov142_0229c348, data_ov142_0229c350;

/* Obj_ov142_0229c3e8::func_ov142_0229bea0 (vtable slot 0x4c, phase 1): a frame of the scene's
 * states (OrderCatalogState) between the frame's start and end, through the table of member
 * functions (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 8; the game reads past the table for others. */
int OrderCatalog_RunState(OrderCatalog *self)
{
    static const MemberPointer *const states[ORDER_CATALOG_STATES] = {
        &data_ov142_0229c318, &data_ov142_0229c2a0, &data_ov142_0229c350, &data_ov142_0229c348,
        &data_ov142_0229c340, &data_ov142_0229c338, &data_ov142_0229c330, &data_ov142_0229c328,
    };
    MemberTable_InitOnce(&data_ov142_0229c5e0, data_ov142_0229c610, states, ORDER_CATALOG_STATES);
    OrderCatalog_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov142_0229c610[self->base.state], self);
    OrderCatalog_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov142_0229c3e819func_ov142_0229bea0Ev, OrderCatalog_RunState)

/* func_ov142_0229bf6c (vtable slot 0x24): the scene's draw. The cursor sprite (with the keys in
 * use) is drawn first, even before the scene is (else answers 0). Then the panel with the
 * panel's wipe; with the bar shown, the thumb (through its class), the arrows (palette 9 at the
 * list's end, 2 pixels lower while held) and the bar's ends; the nine tabs (the highlighted one
 * in palette 6, the others 7); the order button in its palette; and the nine rows' cells (the
 * picked row's own when it is on screen), moved by the scroll within a row. All at the wipe's
 * y kept, plus 0x60. Answers 1. */
int OrderCatalog_Draw(OrderCatalog *self)
{
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    if (OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_DRAWN) == 0) {
        return 0;
    }
    ButtonPanel_Draw(&self->panel, self->panel_wipe_y);
    int y = self->wipe_y + 0x60;
    if (OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_NO_BAR) == 0) {
        catalog_member_slot(&self->thumb_button, 2);
        int palette = OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_AT_BOTTOM) != 0 ? 9 : 8;
        int arrow_y = OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_DOWN_HELD) != 0 ? y + 2 : y;
        OamBuffer_DrawObjAffine(1, &data_ov142_0229c358, 0x80, arrow_y, palette, 1, NULL);
        palette = OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_AT_TOP) != 0 ? 9 : 8;
        arrow_y = OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_UP_HELD) != 0 ? y + 2 : y;
        OamBuffer_DrawObjAffine(1, &data_ov142_0229c368, 0x80, arrow_y, palette, 1, NULL);
        OamBuffer_DrawObjAffine(1, &data_ov142_0229c360, 0x80, y, -1, 1, NULL);
        OamBuffer_DrawObjAffine(1, &data_ov142_0229c370, 0x80, y, -1, 1, NULL);
    }
    for (int tab = 0; tab < ORDER_CATALOG_CATEGORIES; tab++) {
        int palette = tab == self->tab ? 6 : 7;
        int obj = 2 * (ORDER_CATALOG_CATEGORIES - 1 - tab);
        OamBuffer_DrawObjAffine(1, &data_ov142_0229c448[obj], 0x80, y, palette, 1, NULL);
        OamBuffer_DrawObjAffine(1, &data_ov142_0229c448[obj + 1], 0x80, y, palette, 1, NULL);
    }
    OamBuffer_DrawCell(1, data_ov142_0229c378, 0x80, y, self->order_palette, 1, 0x1000, 0x1000, 0, -1, 0, 0);

    int row_y = y - (self->scroll & 0xf);
    OrderCatalog_Count(self); /* QUIRK: called, its answer unused */
    int picked = -1;
    if (self->category == self->picked_category) {
        picked = self->picked_row - self->top_row;
        if (picked < 0 || picked >= ORDER_CATALOG_ROWS) {
            picked = -1;
        }
    }
    int row = self->top_row;
    for (int i = 0; i < ORDER_CATALOG_ROWS; i++) {
        const OamEntry *cell = row >= 0 && picked == i ? data_ov142_0229c3b8 : data_ov142_0229c398;
        OamBuffer_DrawCell(1, cell, 0x80, row_y, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        row++;
        row_y += 0x10;
    }
    return 1;
}
CLEAN_AS(func_ov142_0229bf6c, OrderCatalog_Draw)

/* func_ov142_0229c1cc (vtable slot 0x0c): the scene closes: the parent told and the members torn
 * down. Answers 1. */
int OrderCatalog_Shutdown(OrderCatalog *self)
{
    MenuDispatch_ChildClosed(catalog_parent(self));
    OrderCatalog_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov142_0229c1cc, OrderCatalog_Shutdown)

/* func_ov142_0229c1e8 (vtable slot 0x00): the scene starts: its setup, state 0 (set directly)
 * and phase 0. Answers 1. */
int OrderCatalog_Start(OrderCatalog *self)
{
    OrderCatalog_Setup(self);
    self->base.state = ORDER_CATALOG_STATE_START;
    MenuScene_SetPhase(catalog_base(self), 0);
    return 1;
}
CLEAN_AS(func_ov142_0229c1e8, OrderCatalog_Start)

/* func_ov142_0229c208 (named by the profile at 0x0229c2c8): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order (the labels by __cxa_vec_ctor). */
OrderCatalog *OrderCatalog_New(void)
{
    OrderCatalog *self = MenuScene_Alloc(sizeof(OrderCatalog));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov142_0229c3e8;
    Glider0_Construct(&self->cursor_sprite);
    PushButton_Construct(&self->thumb_button);
    ButtonPanel_Construct(&self->panel);
    __cxa_vec_ctor(self->labels, ORDER_CATALOG_LABELS, sizeof(TextLabel), func_02070c08, func_02070be8);
    for (int i = 0; i < ORDER_CATALOG_TASKS; i++) {
        LayerTask_Construct(&self->tasks[i]);
    }
    return self;
}
CLEAN_AS(func_ov142_0229c208, OrderCatalog_New)
