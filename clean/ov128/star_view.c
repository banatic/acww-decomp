/* The telescope's view (star_view.h): its construction and teardown, its states, phases and
 * draw. */
#include "star_view.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/music_queue.h"
#include "main/player_actor_ops.h"
#include "main/state_flags.h"
#include "ov004/member_pointer.h"
#include "ov004/room_player_actor.h"
#include "ov092/menu_dispatch.h"

static_assert(sizeof(MenuScene) == 0x94 && sizeof(PanelSprite) == 0x7c && offsetof(StarView, pointer) == 0x110, "members");
static_assert(sizeof(Glider) == 0x64 && offsetof(StarView, twinkle) == 0x174, "pointer");
static_assert(offsetof(StarView, scope) == 0x4a4, "twinkle");
static_assert(sizeof(StarScope) == 0x2838 && offsetof(StarView, name_label) == 0x2cdc, "scope");
static_assert(sizeof(TextLabel) == 0x6c && offsetof(StarView, cursor_x) == 0x2d48, "label");
static_assert(offsetof(StarView, flags) == 0x2d68 && offsetof(StarView, name_cells) == 0x2d70, "bytes");
static_assert(sizeof(StarView) == 0x2d74, "size (func_ov128_0229c830)");

/* The scene's vtable. */
extern const u8 data_ov128_0229cbc0[];

/* The closing button's cells. */
extern const PanelCell data_ov128_0229cb38[];
/* "menu/inventory/b_itm0.bch". */
extern const char data_ov128_0229cd20[];

extern Heap *data_021fbe94; /* the current heap */
extern Obj021c526c *data_021c526c;

/* The tables of member functions (ov004/member_pointer.h): their guards, the tables and the
 * constants they are filled from. */
extern u32 data_ov128_0229cd40; /* the sub states' guard */
extern u32 data_ov128_0229cd44; /* the states' guard */
extern MemberPointer data_ov128_0229cd48[STAR_VIEW_STATES];
extern MemberPointer data_ov128_0229cd68[STAR_VIEW_SUB_STATES];
extern const MemberPointer data_ov128_0229c8c8; /* StarView_StateOpen */
extern const MemberPointer data_ov128_0229c8d0; /* StarView_StateWipeOut */
extern const MemberPointer data_ov128_0229c8d8; /* StarView_SubButton */
extern const MemberPointer data_ov128_0229c8e0; /* StarView_SubRelease */
extern const MemberPointer data_ov128_0229c8e8; /* StarView_SubPress */
extern const MemberPointer data_ov128_0229c8f0; /* StarView_SubGlide */
extern const MemberPointer data_ov128_0229c900; /* StarView_SubPenNudge */
extern const MemberPointer data_ov128_0229c908; /* StarView_StateWipeIn */
extern const MemberPointer data_ov128_0229c910; /* StarView_SubKeys */
extern const MemberPointer data_ov128_0229c918; /* StarView_SubTouch */
extern const MemberPointer data_ov128_0229c920; /* StarView_SubPenHold */
extern const MemberPointer data_ov128_0229c928; /* StarView_SubKeyHold */
extern const MemberPointer data_ov128_0229c930; /* StarView_SubKeyNudge */
extern const MemberPointer data_ov128_0229c938; /* StarView_SubFree */
extern const MemberPointer data_ov128_0229c940; /* StarView_StateStartWipeOut */

/* The sky on sub BG0, the scope's frame on sub BG3; the wipes on window 2 over both (layers
 * 9), margin 0x30. */
#define STAR_VIEW_SKY_LAYER LAYER_SUB_BG0
#define STAR_VIEW_SCOPE_LAYER LAYER_SUB_BG3
#define STAR_VIEW_WIPE_LAYERS 9
#define STAR_VIEW_WIPE_MARGIN 0x30
/* Sub window 1 (window 3 of DisplayShadow_SetWindow, bit 2 of the sub windows). */
#define STAR_VIEW_WINDOW 3
#define STAR_VIEW_WINDOW_BIT 2
#define STAR_VIEW_WINDOW_PLANES 0x1e

#define STAR_VIEW_BUTTON_MESSAGE 0x69
#define STAR_VIEW_ARROW_PALETTE 6

static MenuScene *star_view_scene(StarView *self)
{
    return &self->base;
}

static MenuDispatch *star_view_parent(StarView *self)
{
    return (MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self);
}

static Music2f0 *star_view_music(void)
{
    return (Music2f0 *) (void *) data_021c526c->unk_2f0;
}

static int star_view_asr(int value, int shift)
{
    return value >= 0 ? value >> shift : ~(~value >> shift);
}

/* The members' destructors, last member first, then the base's. */
static void star_view_destroy_members(StarView *self)
{
    self->base.vtable = data_ov128_0229cbc0;
    TextLabel_Destruct(&self->name_label);
    StarScope_Destruct(&self->scope);
    StarPalette_Destruct(&self->twinkle);
    Glider0_Destroy(&self->pointer);
    PanelSprite_Destroy(&self->button);
    MenuScene_DestroyBase(star_view_scene(self));
}

/* func_ov128_0229b720 (vtable slot 0x40) */
StarView *StarView_Destroy(StarView *self)
{
    star_view_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov128_0229b720, StarView_Destroy)

/* func_ov128_0229b774 (vtable slot 0x44): the deleting destructor. */
StarView *StarView_Delete(StarView *self)
{
    star_view_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov128_0229b774, StarView_Delete)

/* func_ov128_0229b7cc */
void StarView_ClearFlags(StarView *self, unsigned short mask)
{
    self->flags = (u16) (self->flags & ~mask);
}
CLEAN_AS(func_ov128_0229b7cc, StarView_ClearFlags)

/* func_ov128_0229b7dc */
void StarView_SetFlags(StarView *self, unsigned short mask)
{
    self->flags = (u16) (self->flags | mask);
}
CLEAN_AS(func_ov128_0229b7dc, StarView_SetFlags)

/* func_ov128_0229b7ec: whether any of `mask` is set, as 0 or 1. */
int StarView_TestFlags(StarView *self, unsigned short mask)
{
    return (self->flags & mask) != 0;
}
CLEAN_AS(func_ov128_0229b7ec, StarView_TestFlags)

/* func_ov128_0229c2a0: the sky loaded on sub BG0 and the scope's frame on sub BG3, the sky's
 * twinkle started, the arrows' graphics loaded, the closing button made (6 cells of text,
 * the shadow under cell 2) and the view looked at. */
void StarView_LoadGraphics(StarView *self)
{
    StarScope_LoadSkyLayer(&self->scope, STAR_VIEW_SKY_LAYER);
    StarScope_LoadScopeLayer(&self->scope, STAR_VIEW_SCOPE_LAYER, 0);
    StarPalette_Start(&self->twinkle, STAR_VIEW_SKY_LAYER);
    StarScope_LoadObjGraphics(&self->scope);
    PanelSprite_SetCells(&self->button, data_ov128_0229cb38, 6, 2);
    PanelSprite_Show(&self->button, STAR_VIEW_BUTTON_MESSAGE);
    StarView_UpdateView(self);
}
CLEAN_AS(func_ov128_0229c2a0, StarView_LoadGraphics)

/* func_ov128_0229c2fc: the sub screen in background mode 0, the sky (sub BG0, priority 2, size
 * 1) behind the scope's frame (sub BG3, priority 1). */
void StarView_SetUpLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(STAR_VIEW_SKY_LAYER, 2);
    DisplayLayer_SetBgControl(STAR_VIEW_SKY_LAYER, 1, 0, 0);
    DisplayLayer_SetPriority(STAR_VIEW_SCOPE_LAYER, 1);
    DisplayLayer_SetBgControl(STAR_VIEW_SCOPE_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov128_0229c2fc, StarView_SetUpLayers)

/* func_ov128_0229c334: the end of a frame: the sky view and the name panel stepped. */
void StarView_EndFrame(StarView *self)
{
    StarScope_Update(&self->scope);
    StarView_StepName(self);
}
CLEAN_AS(func_ov128_0229c334, StarView_EndFrame)

/* func_ov128_0229c350: the start of a frame: the name's box let go (made again as needed), the
 * twinkle stepped, the button's text let go. */
void StarView_BeginFrame(StarView *self)
{
    TextLabel_CloseBox(&self->name_label);
    StarPalette_Update(&self->twinkle);
    PanelSprite_CloseText(&self->button);
}
CLEAN_AS(func_ov128_0229c350, StarView_BeginFrame)

/* func_ov128_0229c37c: the end of an interactive frame: the constellation pointed at followed,
 * then the frame's end. */
void StarView_EndInteractive(StarView *self)
{
    StarView_FollowPointed(self);
    StarView_EndFrame(self);
}
CLEAN_AS(func_ov128_0229c37c, StarView_EndInteractive)

/* func_ov128_0229c390 */
void StarView_BeginInteractive(StarView *self)
{
    StarView_BeginFrame(self);
}
CLEAN_AS(func_ov128_0229c390, StarView_BeginInteractive)

/* func_ov128_0229c398: the twinkle stopped, the sky's layer task ended, the texts let go; the
 * player asked back to state 0x10, the music's tracks of scene 0x22 faded in, and sub BG0's
 * character 0x10 loaded again from "menu/inventory/b_itm0.bch". */
void StarView_Teardown(StarView *self)
{
    StarPalette_Cancel(&self->twinkle);
    StarScope_EndTask(&self->scope);
    PanelSprite_CloseText(&self->button);
    TextLabel_CloseBox(&self->name_label);
    PlayerActorOps_RequestState10();
    Music2f0_FadeInForScene22(star_view_music());
    DisplayLayer_LoadCharsFromFile(data_ov128_0229cd20, data_021fbe94, LAYER_SUB_BG0, 0, 0x10, 0x10);
}
CLEAN_AS(func_ov128_0229c398, StarView_Teardown)

/* func_ov128_0229baa8: no constellation pointed at, wanted or named; the panel hidden. */
void StarView_ResetName(StarView *self)
{
    self->pointed = STAR_VIEW_NONE;
    self->wanted = STAR_VIEW_NONE;
    self->named = STAR_VIEW_NONE;
    self->name_state = STAR_VIEW_NAME_HIDDEN;
    self->name_slide = 0;
    self->name_cells = STAR_VIEW_NAME_MIN_CELLS;
}
CLEAN_AS(func_ov128_0229baa8, StarView_ResetName)

/* func_ov128_0229c408: the scene's values set up: no flags, the sky view reset, the free
 * pointer at the middle, the pointer's spot by arrow 1, no name; the player held at a fixed
 * point and the music's tracks of scene 0x22 set. */
void StarView_Setup(StarView *self)
{
    self->flags = 0;
    StarScope_Reset(&self->scope);
    self->cursor_x = 0x80;
    self->cursor_y = 0x60;
    self->pointer_spot = STAR_SCOPE_ARROW_RIGHT;
    StarView_ResetName(self);
    RoomPlayerActor_RequestFixedPoint();
    Music2f0_SetTracksForScene22(star_view_music());
}
CLEAN_AS(func_ov128_0229c408, StarView_Setup)

/* func_ov128_0229c464: sub window 1 over the rows from 64 to 48 above the wipe's offset (from
 * the top at least), on while that band is below the top. */
void StarView_SetWipeWindow(StarView *self)
{
    int top = MenuScene_WipeOffsetY(star_view_scene(self)) - 64;
    int bottom;

    if (top < 0) {
        top = 0;
    }
    bottom = MenuScene_WipeOffsetY(star_view_scene(self)) - 48;
    if (bottom > 0) {
        DisplayShadow_EnableSubWindows(STAR_VIEW_WINDOW_BIT);
        DisplayShadow_SetWindow(STAR_VIEW_WINDOW, 0, top, 0xff, bottom);
    } else {
        DisplayShadow_DisableSubWindows(STAR_VIEW_WINDOW_BIT);
    }
}
CLEAN_AS(func_ov128_0229c464, StarView_SetWipeWindow)

/* func_ov128_0229c4ac: the scope's frame scrolled with the wipe and its offset kept. */
void StarView_FollowWipe(StarView *self)
{
    MenuScene_ScrollWipe(star_view_scene(self), STAR_VIEW_SCOPE_LAYER, 0, 0);
    self->wipe_y = MenuScene_WipeOffsetY(star_view_scene(self));
}
CLEAN_AS(func_ov128_0229c4ac, StarView_FollowWipe)

/* func_ov128_0229c4d0 (state 3): the wipe out; at its end both layers and the window hidden and
 * the scene deleted (phase 5). */
void StarView_StateWipeOut(StarView *self)
{
    if (MenuScene_StepWipe(star_view_scene(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(STAR_VIEW_SKY_LAYER);
        DisplayLayer_HideAndResetScroll(STAR_VIEW_SCOPE_LAYER);
        DisplayShadow_DisableSubWindows(STAR_VIEW_WINDOW_BIT);
        MenuScene_SetPhase(star_view_scene(self), STAR_VIEW_PHASE_DELETE);
    } else {
        StarView_SetWipeWindow(self);
        StarView_FollowWipe(self);
    }
}
CLEAN_AS(func_ov128_0229c4d0, StarView_StateWipeOut)

/* func_ov128_0229c50c (state 2): the parent told the screen closes (with the backdrop and
 * sound), and the wipe out started. */
void StarView_StateStartWipeOut(StarView *self)
{
    MenuDispatch_SetMode(star_view_parent(self), MENU_DISPATCH_MODE_CLOSE, 1);
    MenuScene_StartWipeOnWindow2(star_view_scene(self), STAR_VIEW_WIPE_LAYERS, 0, 0, STAR_VIEW_WIPE_MARGIN);
    DisplayShadow_SetSubWindow1Planes(STAR_VIEW_WINDOW_PLANES, 1);
    StarView_SetWipeWindow(self);
    StarView_FollowWipe(self);
    MenuScene_SetState(star_view_scene(self), STAR_VIEW_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov128_0229c50c, StarView_StateStartWipeOut)

/* func_ov128_0229c554 (state 1): the wipe in; at its end phase 2 and on to the pen or the
 * keys. */
void StarView_StateWipeIn(StarView *self)
{
    if (MenuScene_StepWipeBack(star_view_scene(self), 0) != 0) {
        MenuScene_SetPhase(star_view_scene(self), STAR_VIEW_PHASE_INTERACTIVE);
        StarView_EnterInput(self);
        StarView_SetFlags(self, STAR_VIEW_FLAG_INTERACTIVE);
    } else {
        StarView_SetWipeWindow(self);
    }
    StarView_FollowWipe(self);
}
CLEAN_AS(func_ov128_0229c554, StarView_StateWipeIn)

/* func_ov128_0229c58c (state 0): the layers set up and loaded, the wipe in started (4 frames)
 * with both layers shown, the scene's OBJs drawn from now. */
void StarView_StateOpen(StarView *self)
{
    StarView_SetUpLayers();
    StarView_LoadGraphics(self);
    MenuScene_StartWipeCoveredOnWindow2(star_view_scene(self), STAR_VIEW_WIPE_LAYERS, 4, 0, STAR_VIEW_WIPE_MARGIN);
    DisplayLayer_Show(STAR_VIEW_SKY_LAYER);
    DisplayLayer_Show(STAR_VIEW_SCOPE_LAYER);
    StarView_SetFlags(self, STAR_VIEW_FLAG_DRAWN);
    DisplayShadow_SetSubWindow1Planes(STAR_VIEW_WINDOW_PLANES, 1);
    StarView_SetWipeWindow(self);
    StarView_FollowWipe(self);
    MenuScene_SetState(star_view_scene(self), STAR_VIEW_STATE_WIPE_IN);
}
CLEAN_AS(func_ov128_0229c58c, StarView_StateOpen)

/* func_ov128_0229c5e4 (vtable slot 0x5c, phase 5): the scene asks to be deleted. Answers 1. */
int StarView_RequestDelete(StarView *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov128_0229c5e4, StarView_RequestDelete)

/* func_ov128_0229c5f4 (vtable slot 0x58, phase 4): nothing. */
int StarView_Phase4(void)
{
    return 1;
}
CLEAN_AS(func_ov128_0229c5f4, StarView_Phase4)

/* func_ov128_0229c5f8 (vtable slot 0x54, phase 3): nothing. */
int StarView_Phase3(void)
{
    return 1;
}
CLEAN_AS(func_ov128_0229c5f8, StarView_Phase3)

/* func_ov128_0229c5fc (vtable slot 0x50, phase 2): an interactive frame: its start, the sub
 * state, its end. Answers 1. */
int StarView_RunInteractive(StarView *self)
{
    StarView_BeginInteractive(self);
    StarView_RunSubState(self);
    StarView_EndInteractive(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov128_0229cbc019func_ov128_0229c5fcEv, StarView_RunInteractive)

/* func_ov128_0229c618: the sub state (StarViewSubState) run through its table of member
 * functions, filled once from its constants.
 * REQUIRES: the sub state is below 11; the game reads past the table for others. */
void StarView_RunSubState(StarView *self)
{
    static const MemberPointer *const sub_states[STAR_VIEW_SUB_STATES] = {
        &data_ov128_0229c918, &data_ov128_0229c920, &data_ov128_0229c900, &data_ov128_0229c938,
        &data_ov128_0229c910, &data_ov128_0229c928, &data_ov128_0229c930, &data_ov128_0229c8f0,
        &data_ov128_0229c8e8, &data_ov128_0229c8e0, &data_ov128_0229c8d8,
    };
    MemberTable_InitOnce(&data_ov128_0229cd40, data_ov128_0229cd68, sub_states, STAR_VIEW_SUB_STATES);
    MemberPointer_CallVoid(&data_ov128_0229cd68[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov128_0229cbc019func_ov128_0229c618Ev, StarView_RunSubState)

/* func_ov128_0229c700 (vtable slot 0x4c, phase 1): a frame of the states (StarViewState)
 * through their table of member functions (filled once from its constants), between the
 * frame's start and end. Answers 1.
 * REQUIRES: the state is below 4; the game reads past the table for others. */
int StarView_RunState(StarView *self)
{
    static const MemberPointer *const states[STAR_VIEW_STATES] = {
        &data_ov128_0229c8c8,
        &data_ov128_0229c908,
        &data_ov128_0229c940,
        &data_ov128_0229c8d0,
    };
    MemberTable_InitOnce(&data_ov128_0229cd44, data_ov128_0229cd48, states, STAR_VIEW_STATES);
    StarView_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov128_0229cd48[self->base.state], self);
    StarView_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov128_0229cbc019func_ov128_0229c700Ev, StarView_RunState)

/* func_ov128_0229c794 (vtable slot 0x24): the scene's draw: the name panel; while
 * STAR_VIEW_FLAG_DRAWN the button (a quarter of the wipe's offset down), the arrows (spread by
 * the offset, palette 6) and the grid at the offset. Answers 1.
 * QUIRK: main's state flag 2 is read first and its answer left unused. */
int StarView_Draw(StarView *self)
{
    StateFlags_Test2();
    StarView_DrawName(self);
    if (StarView_TestFlags(self, STAR_VIEW_FLAG_DRAWN) != 0) {
        PanelSprite_Draw(&self->button, 0, star_view_asr(self->wipe_y, 2), 1);
        StarScope_DrawArrows(&self->scope, self->wipe_y, STAR_VIEW_ARROW_PALETTE);
    }
    if (StarView_TestFlags(self, STAR_VIEW_FLAG_DRAWN) != 0) {
        StarView_DrawGrid(self, self->wipe_y);
    }
    return 1;
}
CLEAN_AS(func_ov128_0229c794, StarView_Draw)

/* func_ov128_0229c7f4 (vtable slot 0x0c): the scene ends: the parent told and the scene torn
 * down. Answers 1. */
int StarView_End(StarView *self)
{
    MenuDispatch_ChildClosed(star_view_parent(self));
    StarView_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov128_0229c7f4, StarView_End)

/* func_ov128_0229c810 (vtable slot 0x00): the scene starts: its setup, state 0 and the wait
 * phase. Answers 1. */
int StarView_Start(StarView *self)
{
    StarView_Setup(self);
    self->base.state = STAR_VIEW_STATE_OPEN;
    MenuScene_SetPhase(star_view_scene(self), STAR_VIEW_PHASE_WAIT);
    return 1;
}
CLEAN_AS(func_ov128_0229c810, StarView_Start)

/* func_ov128_0229c830 (named by the profile at 0x0229c8f8): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order. */
StarView *StarView_New(void)
{
    StarView *self = MenuScene_Alloc(sizeof(StarView));

    if (self != NULL) {
        MenuScene_Construct(&self->base);
        self->base.vtable = data_ov128_0229cbc0;
        PanelSprite_Construct(&self->button);
        Glider0_Construct(&self->pointer);
        StarPalette_Construct(&self->twinkle);
        StarScope_Construct(&self->scope);
        TextLabel_Construct(&self->name_label);
    }
    return self;
}
CLEAN_AS(func_ov128_0229c830, StarView_New)
