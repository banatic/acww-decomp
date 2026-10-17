/* The scene of overlay 129 (star_designer.h): its construction and teardown, its flags, the
 * layers and the wipes of its states, the question's panel, and its draw. */
#include "star_designer.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/music_queue.h"
#include "main/player_actor_ops.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov004/member_pointer.h"
#include "ov004/room_player_actor.h"
#include "ov092/menu_dispatch.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(StarDesigner, x) == 0x94, "pointer");
static_assert(offsetof(StarDesigner, flags) == 0xa4 && offsetof(StarDesigner, piece) == 0xaa, "pieces");
static_assert(offsetof(StarDesigner, return_sub_state) == 0xac && offsetof(StarDesigner, flash_timer) == 0xb4, "bytes");
static_assert(offsetof(StarDesigner, error) == 0xb8 && offsetof(StarDesigner, panel) == 0x1d4, "error, panel");
static_assert(offsetof(StarDesigner, pointer) == 0x3a0 && offsetof(StarDesigner, palette) == 0x404, "pointer, palette");
static_assert(offsetof(StarDesigner, scope) == 0x734 && offsetof(StarDesigner, name) == 0x2f6c, "scope");
static_assert(offsetof(StarDesigner, pieces) == 0x2f78 && offsetof(StarDesigner, piece_state) == 0x2f98, "states");
static_assert(sizeof(StarDesigner) == 0x3160, "size (func_ov129_0229da80)");

/* The scene's vtable. */
extern const u8 data_ov129_0229dc38[];

/* The current heap, and the field's sound object (its member at 0x2f0, main/music_queue.h). */
extern Heap *data_021fbe94;
extern u8 *data_021c526c;

/* The inventory's characters loaded back to sub BG0 when the screen ends. */
extern const char data_ov129_0229dc98[]; /* menu/inventory/b_itm0.bch */

/* The tables of member functions (ov004/member_pointer.h): their guards, the tables and the
 * constants they are filled from. */
extern u32 data_ov129_0229dcc8; /* the states' guard */
extern u32 data_ov129_0229dcc4; /* the sub states' guard */
extern MemberPointer data_ov129_0229dd24[STAR_DESIGNER_STATES];
extern MemberPointer data_ov129_0229dd84[STAR_DESIGNER_SUB_STATES];
extern const MemberPointer data_ov129_0229db58; /* StarDesigner_SubCursor */
extern const MemberPointer data_ov129_0229db60; /* StarDesigner_SubNudgePen */
extern const MemberPointer data_ov129_0229db68; /* StarDesigner_SubTouch */
extern const MemberPointer data_ov129_0229db70; /* StarDesigner_SubArrowKey */
extern const MemberPointer data_ov129_0229db78; /* StarDesigner_SubNudgeKey */
extern const MemberPointer data_ov129_0229db80; /* StarDesigner_SubPress */
extern const MemberPointer data_ov129_0229db88; /* StarDesigner_SubRelease */
extern const MemberPointer data_ov129_0229db90; /* StarDesigner_StateWipeOut */
extern const MemberPointer data_ov129_0229db98; /* StarDesigner_StateAskStart */
extern const MemberPointer data_ov129_0229dba0; /* StarDesigner_StateOpen */
extern const MemberPointer data_ov129_0229dba8; /* StarDesigner_SubGlide */
extern const MemberPointer data_ov129_0229dbb0; /* StarDesigner_SubButton */
extern const MemberPointer data_ov129_0229dbb8; /* StarDesigner_SubAnswerPen */
extern const MemberPointer data_ov129_0229dbc0; /* StarDesigner_StateBackStart */
extern const MemberPointer data_ov129_0229dbc8; /* StarDesigner_SubFree */
extern const MemberPointer data_ov129_0229dbd0; /* StarDesigner_SubAnswerKeys */
extern const MemberPointer data_ov129_0229dbd8; /* StarDesigner_SubArrowPen */
extern const MemberPointer data_ov129_0229dbe0; /* StarDesigner_SubAnswerPress */
extern const MemberPointer data_ov129_0229dbe8; /* StarDesigner_StateBackWipeIn */
extern const MemberPointer data_ov129_0229dbf0; /* StarDesigner_SubError */
extern const MemberPointer data_ov129_0229dbf8; /* StarDesigner_StateWipeIn */
extern const MemberPointer data_ov129_0229dc00; /* StarDesigner_StateBackShow */
extern const MemberPointer data_ov129_0229dc08; /* StarDesigner_StateBackWipeOut */
extern const MemberPointer data_ov129_0229dc10; /* StarDesigner_StateClose */
extern const MemberPointer data_ov129_0229dc18; /* StarDesigner_StateAskWipeIn */
extern const MemberPointer data_ov129_0229dc20; /* StarDesigner_StateAskShow */
extern const MemberPointer data_ov129_0229dc28; /* StarDesigner_StateAskWipeOut */

/* The layers: the sky on sub BG0, the scope on sub BG3; the wipes are over both (bits 0 and 3)
 * with a margin of 0x30. */
#define STAR_DESIGNER_WIPE_LAYERS 9
#define STAR_DESIGNER_WIPE_MARGIN 0x30
#define STAR_DESIGNER_WINDOW_PLANES 0x1e
#define STAR_DESIGNER_ARROWS_PALETTE 5

/* The scrolling sound (as overlay 127's). */
#define STAR_DESIGNER_SE_SCROLL 0x883

/* The panel's messages of the two questions. */
#define STAR_DESIGNER_MESSAGE_QUIT 0x87
#define STAR_DESIGNER_MESSAGE_DONE 0x22

static MenuScene *star_designer_base(StarDesigner *self)
{
    return &self->base;
}

/* The pointer's update through its class (vtable slot 3). */
static void star_designer_animate_pointer(StarDesigner *self)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) self->pointer.vtable;
    vtable[3](&self->pointer);
}

/* "done" enabled only with pieces drawn. */
static void star_designer_enable_done(StarDesigner *self)
{
    if (self->mode == STAR_DESIGNER_MODE_PIECES) {
        ButtonPanel_ClearSpriteFlag4(&self->panel, STAR_DESIGNER_BUTTON_DONE);
    } else {
        ButtonPanel_SetSpriteFlag4(&self->panel, STAR_DESIGNER_BUTTON_DONE);
    }
}

/* The members' destructors, last member first, then the base's. */
static void star_designer_destroy_members(StarDesigner *self)
{
    self->base.vtable = data_ov129_0229dc38;
    StarScope_Destruct(&self->scope);
    StarPalette_Destruct(&self->palette);
    Glider0_Destroy(&self->pointer);
    ButtonPanel_Destroy(&self->panel);
    ErrorMessage_Destruct(&self->error);
    MenuScene_DestroyBase(star_designer_base(self));
}

/* func_ov129_0229b720 (vtable slot 0x40) */
StarDesigner *StarDesigner_Destroy(StarDesigner *self)
{
    star_designer_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov129_0229b720, StarDesigner_Destroy)

/* func_ov129_0229b774 (vtable slot 0x44): the deleting destructor. */
StarDesigner *StarDesigner_Delete(StarDesigner *self)
{
    star_designer_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov129_0229b774, StarDesigner_Delete)

/* func_ov129_0229b7cc */
void StarDesigner_ClearFlags(StarDesigner *self, unsigned short mask)
{
    self->flags = (u16) (self->flags & ~mask);
}
CLEAN_AS(func_ov129_0229b7cc, StarDesigner_ClearFlags)

/* func_ov129_0229b7dc */
void StarDesigner_SetFlags(StarDesigner *self, unsigned short mask)
{
    self->flags = (u16) (self->flags | mask);
}
CLEAN_AS(func_ov129_0229b7dc, StarDesigner_SetFlags)

/* func_ov129_0229b7ec: whether any of `mask` is set, as 0 or 1. */
int StarDesigner_TestFlags(StarDesigner *self, unsigned short mask)
{
    return (self->flags & mask) != 0;
}
CLEAN_AS(func_ov129_0229b7ec, StarDesigner_TestFlags)

/* func_ov129_0229d110: the sky loaded to sub BG0 and the scope to sub BG3, the twinkling started
 * on sub BG0, the scope's OBJs loaded; the panel's colours and its usual layout, "done" enabled
 * only with pieces drawn. */
void StarDesigner_LoadLayers(StarDesigner *self)
{
    StarScope_LoadSkyLayer(&self->scope, LAYER_SUB_BG0);
    StarScope_LoadScopeLayer(&self->scope, LAYER_SUB_BG3, 1);
    StarPalette_Start(&self->palette, LAYER_SUB_BG0);
    StarScope_LoadObjGraphics(&self->scope);
    ButtonPanel_LoadTextColors(&self->panel);
    ButtonPanel_SetLayout4(&self->panel);
    star_designer_enable_done(self);
}
CLEAN_AS(func_ov129_0229d110, StarDesigner_LoadLayers)

/* func_ov129_0229d180: the sub screen in BG mode 0; sub BG0 at priority 2 with screen size 1,
 * sub BG3 at priority 1. */
void StarDesigner_SetUpLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(LAYER_SUB_BG0, 2);
    DisplayLayer_SetBgControl(LAYER_SUB_BG0, 1, 0, 0);
    DisplayLayer_SetPriority(LAYER_SUB_BG3, 1);
    DisplayLayer_SetBgControl(LAYER_SUB_BG3, 0, 0, 0);
}
CLEAN_AS(func_ov129_0229d180, StarDesigner_SetUpLayers)

/* func_ov129_0229d1b8: the end of a frame: the view updated; the scrolling sound started when
 * the view scrolled this frame and stopped (in a frame) when it did not. */
void StarDesigner_EndFrame(StarDesigner *self)
{
    StarScope_Update(&self->scope);
    if (StarDesigner_TestFlags(self, STAR_DESIGNER_FLAG_SCROLLED) != 0) {
        if (StarDesigner_TestFlags(self, STAR_DESIGNER_FLAG_SCROLL_SE) == 0) {
            StarDesigner_SetFlags(self, STAR_DESIGNER_FLAG_SCROLL_SE);
            SoundSys_StartOnHandle38(STAR_DESIGNER_SE_SCROLL);
        }
    } else if (StarDesigner_TestFlags(self, STAR_DESIGNER_FLAG_SCROLL_SE) != 0) {
        StarDesigner_ClearFlags(self, STAR_DESIGNER_FLAG_SCROLL_SE);
        SoundSys_StopSound(STAR_DESIGNER_SE_SCROLL, 1);
    }
}
CLEAN_AS(func_ov129_0229d1b8, StarDesigner_EndFrame)

/* func_ov129_0229d218: the start of a frame: the twinkling stepped, the panel's texts closed,
 * not scrolled yet. */
void StarDesigner_BeginFrame(StarDesigner *self)
{
    StarPalette_Update(&self->palette);
    ButtonPanel_CloseTexts(&self->panel);
    StarDesigner_ClearFlags(self, STAR_DESIGNER_FLAG_SCROLLED);
}
CLEAN_AS(func_ov129_0229d218, StarDesigner_BeginFrame)

/* func_ov129_0229d244 */
void StarDesigner_EndInteractive(StarDesigner *self)
{
    StarDesigner_EndFrame(self);
}
CLEAN_AS(func_ov129_0229d244, StarDesigner_EndInteractive)

/* func_ov129_0229d24c: the start of an interactive frame, the pointer animated. */
void StarDesigner_BeginInteractive(StarDesigner *self)
{
    StarDesigner_BeginFrame(self);
    star_designer_animate_pointer(self);
}
CLEAN_AS(func_ov129_0229d24c, StarDesigner_BeginInteractive)

/* func_ov129_0229d268: the screen ends: the twinkling cancelled, the view's task ended, the
 * panel's texts closed, the player's state 10 asked for, the music faded back in and the
 * inventory's characters 0-0x10 loaded back to sub BG0. */
void StarDesigner_Teardown(StarDesigner *self)
{
    StarPalette_Cancel(&self->palette);
    StarScope_EndTask(&self->scope);
    ButtonPanel_CloseTexts(&self->panel);
    PlayerActorOps_RequestState10();
    Music2f0_FadeInForScene22((Music2f0 *) (void *) (data_021c526c + 0x2f0));
    DisplayLayer_LoadCharsFromFile(data_ov129_0229dc98, data_021fbe94, LAYER_SUB_BG0, 0, 0x10, 0x10);
}
CLEAN_AS(func_ov129_0229d268, StarDesigner_Teardown)

/* func_ov129_0229d2d0: the scene's values set up: no flag, the view reset, the free pointer at
 * the screen's centre, the key cursor on "done", nothing pointed at or flashed; every piece
 * free, then the other constellations' taken, nothing under the pointer, no end, and the
 * constellation loaded. The player held at a fixed point and the music's tracks set. */
void StarDesigner_Setup(StarDesigner *self)
{
    self->flags = 0;
    StarScope_Reset(&self->scope);
    self->x = 0x80;
    self->y = 0x60;
    self->cursor = STAR_DESIGNER_CURSOR_DONE;
    self->hover_piece = STAR_DESIGNER_NO_PIECE;
    self->flash_piece = STAR_DESIGNER_NO_PIECE;
    self->flash_timer = 0;
    StarDesigner_ClearPieceStates(self);
    StarDesigner_MarkTaken(self);
    self->star = STAR_DESIGNER_NO_STAR;
    self->piece = STAR_DESIGNER_NO_PIECE;
    self->end_star = STAR_DESIGNER_NO_STAR;
    StarDesigner_LoadConstellation(self);
    RoomPlayerActor_RequestFixedPoint();
    Music2f0_SetTracksForScene22((Music2f0 *) (void *) (data_021c526c + 0x2f0));
}
CLEAN_AS(func_ov129_0229d2d0, StarDesigner_Setup)

/* func_ov129_0229d360: the question answered by the pen or the keys as last used (state flag
 * 2). Returns the sub state's address as a number. */
int StarDesigner_StartInput(StarDesigner *self)
{
    if (StateFlags_IsClear2() != 0) {
        return (int) (uintptr_t) StarDesigner_EnterAnswerPen(self);
    }
    return (int) (uintptr_t) StarDesigner_EnterAnswerKeys(self);
}
CLEAN_AS(func_ov129_0229d360, StarDesigner_StartInput)

/* func_ov129_0229d380: the question by the keys (STAR_DESIGNER_SUB_ANSWER_KEYS): the usual key
 * repeat, "no" chosen and the pointer put at it in its first set. */
unsigned char *StarDesigner_EnterAnswerKeys(StarDesigner *self)
{
    int x;
    int y;

    MenuScene_ResetKeyRepeat(star_designer_base(self));
    self->answer = STAR_DESIGNER_ANSWER_NO;
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_A);
    star_designer_animate_pointer(self);
    x = ButtonPanel_ButtonX(&self->panel, STAR_DESIGNER_BUTTON_NO);
    y = ButtonPanel_ButtonY(&self->panel, STAR_DESIGNER_BUTTON_NO);
    Glider_PlaceAt(&self->pointer, x, y);
    return MenuScene_SetSubState(star_designer_base(self), STAR_DESIGNER_SUB_ANSWER_KEYS);
}
CLEAN_AS(func_ov129_0229d380, StarDesigner_EnterAnswerKeys)

/* func_ov129_0229d3e0: the question by the pen (STAR_DESIGNER_SUB_ANSWER_PEN), the pointer
 * hidden. */
unsigned char *StarDesigner_EnterAnswerPen(StarDesigner *self)
{
    StarDesigner_HidePointer(self);
    return MenuScene_SetSubState(star_designer_base(self), STAR_DESIGNER_SUB_ANSWER_PEN);
}
CLEAN_AS(func_ov129_0229d3e0, StarDesigner_EnterAnswerPen)

/* func_ov129_0229d3f8 (state 11): the panel's wipe back in; at its end back to the drawing
 * (phase 2) with the centre drawn and the pieces painted with the open ones. Both offsets
 * follow the wipe. */
void StarDesigner_StateBackWipeIn(StarDesigner *self)
{
    if (MenuScene_StepWipeBack(star_designer_base(self), 0) != 0) {
        MenuScene_SetPhase(star_designer_base(self), STAR_DESIGNER_PHASE_INTERACTIVE);
        StarDesigner_EnterDrawing(self);
        StarDesigner_SetFlags(self, STAR_DESIGNER_FLAG_CENTRE);
        StarDesigner_Refresh(self, 1);
    }
    self->panel_offset = MenuScene_WipeOffsetY(star_designer_base(self));
    self->arrows_offset = MenuScene_WipeOffsetY(star_designer_base(self));
}
CLEAN_AS(func_ov129_0229d3f8, StarDesigner_StateBackWipeIn)

/* func_ov129_0229d440 (state 10): the panel in its usual layout ("done" enabled only with
 * pieces drawn), wiped back in with the arrows. */
void StarDesigner_StateBackShow(StarDesigner *self)
{
    MenuScene_StartWipeCovered(star_designer_base(self), 0, 0);
    ButtonPanel_SetLayout4(&self->panel);
    star_designer_enable_done(self);
    MenuScene_SetState(star_designer_base(self), STAR_DESIGNER_STATE_BACK_WIPE_IN);
    StarDesigner_SetFlags(self, STAR_DESIGNER_FLAG_ARROWS);
}
CLEAN_AS(func_ov129_0229d440, StarDesigner_StateBackShow)

/* func_ov129_0229d490 (state 9): the question's wipe out; at its end the panel shown again. */
void StarDesigner_StateBackWipeOut(StarDesigner *self)
{
    if (MenuScene_StepWipe(star_designer_base(self), -1) != 0) {
        StarDesigner_StateBackShow(self);
    }
    self->panel_offset = MenuScene_WipeOffsetY(star_designer_base(self));
}
CLEAN_AS(func_ov129_0229d490, StarDesigner_StateBackWipeOut)

/* func_ov129_0229d4b8 (state 8): the question's wipe out started. */
void StarDesigner_StateBackStart(StarDesigner *self)
{
    MenuScene_StartWipe(star_designer_base(self), 0, 0);
    MenuScene_SetState(star_designer_base(self), STAR_DESIGNER_STATE_BACK_WIPE_OUT);
}
CLEAN_AS(func_ov129_0229d4b8, StarDesigner_StateBackStart)

/* func_ov129_0229d4d4 (state 7): the question's wipe in; at its end it is answered (phase 2). */
void StarDesigner_StateAskWipeIn(StarDesigner *self)
{
    if (MenuScene_StepWipeBack(star_designer_base(self), 0) != 0) {
        MenuScene_SetPhase(star_designer_base(self), STAR_DESIGNER_PHASE_INTERACTIVE);
        StarDesigner_StartInput(self);
    }
    self->panel_offset = MenuScene_WipeOffsetY(star_designer_base(self));
}
CLEAN_AS(func_ov129_0229d4d4, StarDesigner_StateAskWipeIn)

/* func_ov129_0229d500 (state 6): the question shown on the panel (message 0x87 to quit, 0x22
 * when done), wiped in without the arrows. */
void StarDesigner_StateAskShow(StarDesigner *self)
{
    MenuScene_StartWipeCovered(star_designer_base(self), 0, 0);
    ButtonPanel_ClearSpriteFlag4(&self->panel, STAR_DESIGNER_BUTTON_DONE);
    if (StarDesigner_TestFlags(self, STAR_DESIGNER_FLAG_QUITTING) != 0) {
        ButtonPanel_SetLayout9(&self->panel, STAR_DESIGNER_MESSAGE_QUIT);
    } else {
        ButtonPanel_SetLayout9(&self->panel, STAR_DESIGNER_MESSAGE_DONE);
    }
    StarDesigner_ClearFlags(self, STAR_DESIGNER_FLAG_ARROWS);
    MenuScene_SetState(star_designer_base(self), STAR_DESIGNER_STATE_ASK_WIPE_IN);
}
CLEAN_AS(func_ov129_0229d500, StarDesigner_StateAskShow)

/* func_ov129_0229d554 (state 5): the panel's wipe out; at its end the question shown. Both
 * offsets follow the wipe. */
void StarDesigner_StateAskWipeOut(StarDesigner *self)
{
    if (MenuScene_StepWipe(star_designer_base(self), -1) != 0) {
        StarDesigner_StateAskShow(self);
    }
    self->panel_offset = MenuScene_WipeOffsetY(star_designer_base(self));
    self->arrows_offset = MenuScene_WipeOffsetY(star_designer_base(self));
}
CLEAN_AS(func_ov129_0229d554, StarDesigner_StateAskWipeOut)

/* func_ov129_0229d588 (state 4): the panel's wipe out started. */
void StarDesigner_StateAskStart(StarDesigner *self)
{
    MenuScene_StartWipe(star_designer_base(self), 0, 0);
    MenuScene_SetState(star_designer_base(self), STAR_DESIGNER_STATE_ASK_WIPE_OUT);
}
CLEAN_AS(func_ov129_0229d588, StarDesigner_StateAskStart)

/* func_ov129_0229d5a4: the sub screen's window (3) follows the wipe: from 0x40 above to 0x30
 * above its offset, off while that is not below the top. */
void StarDesigner_FollowWipeWindow(StarDesigner *self)
{
    int top = MenuScene_WipeOffsetY(star_designer_base(self)) - 0x40;
    int bottom;

    if (top < 0) {
        top = 0;
    }
    bottom = MenuScene_WipeOffsetY(star_designer_base(self)) - 0x30;
    if (bottom <= 0) {
        DisplayShadow_DisableSubWindows(WINDOW_1);
    } else {
        DisplayShadow_EnableSubWindows(WINDOW_1);
        DisplayShadow_SetWindow(3, 0, top, 0xff, bottom);
    }
}
CLEAN_AS(func_ov129_0229d5a4, StarDesigner_FollowWipeWindow)

/* func_ov129_0229d5ec: sub BG3 scrolled with the wipe; both offsets follow it. */
void StarDesigner_FollowWipe(StarDesigner *self)
{
    MenuScene_ScrollWipe(star_designer_base(self), LAYER_SUB_BG3, 0, 0);
    self->arrows_offset = MenuScene_WipeOffsetY(star_designer_base(self));
    self->panel_offset = MenuScene_WipeOffsetY(star_designer_base(self));
}
CLEAN_AS(func_ov129_0229d5ec, StarDesigner_FollowWipe)

/* func_ov129_0229d618 (state 3): the wipe out; at its end both layers hidden, the window off
 * and the scene deleted (phase 5). */
void StarDesigner_StateWipeOut(StarDesigner *self)
{
    if (MenuScene_StepWipe(star_designer_base(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(LAYER_SUB_BG0);
        DisplayLayer_HideAndResetScroll(LAYER_SUB_BG3);
        DisplayShadow_DisableSubWindows(WINDOW_1);
        MenuScene_SetPhase(star_designer_base(self), STAR_DESIGNER_PHASE_DELETE);
    } else {
        StarDesigner_FollowWipeWindow(self);
        StarDesigner_FollowWipe(self);
    }
}
CLEAN_AS(func_ov129_0229d618, StarDesigner_StateWipeOut)

/* func_ov129_0229d654 (state 2): the parent told the screen closes (with the backdrop and
 * sound) and the wipe out started. */
void StarDesigner_StateClose(StarDesigner *self)
{
    MenuDispatch_SetMode((MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self), MENU_DISPATCH_MODE_CLOSE, 1);
    MenuScene_StartWipeOnWindow2(star_designer_base(self), STAR_DESIGNER_WIPE_LAYERS, 0, 0, STAR_DESIGNER_WIPE_MARGIN);
    DisplayShadow_SetSubWindow1Planes(STAR_DESIGNER_WINDOW_PLANES, 1);
    StarDesigner_FollowWipeWindow(self);
    StarDesigner_FollowWipe(self);
    MenuScene_SetState(star_designer_base(self), STAR_DESIGNER_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov129_0229d654, StarDesigner_StateClose)

/* func_ov129_0229d69c (state 1): the wipe in; at its end on to the drawing (phase 2) with the
 * centre drawn, the pieces painted with the open ones and the window off. */
void StarDesigner_StateWipeIn(StarDesigner *self)
{
    if (MenuScene_StepWipeBack(star_designer_base(self), 0) != 0) {
        MenuScene_SetPhase(star_designer_base(self), STAR_DESIGNER_PHASE_INTERACTIVE);
        StarDesigner_EnterDrawing(self);
        StarDesigner_SetFlags(self, STAR_DESIGNER_FLAG_CENTRE);
        StarDesigner_Refresh(self, 1);
        DisplayShadow_DisableSubWindows(WINDOW_1);
    } else {
        StarDesigner_FollowWipeWindow(self);
    }
    StarDesigner_FollowWipe(self);
}
CLEAN_AS(func_ov129_0229d69c, StarDesigner_StateWipeIn)

/* func_ov129_0229d6e4 (state 0): the layers set up and loaded, every piece painted, the wipe in
 * started covered (4 frames) with both layers shown, the arrows and the panel drawn. */
void StarDesigner_StateOpen(StarDesigner *self)
{
    StarDesigner_SetUpLayers();
    StarDesigner_LoadLayers(self);
    StarDesigner_PaintAll(self);
    MenuScene_StartWipeCoveredOnWindow2(star_designer_base(self), STAR_DESIGNER_WIPE_LAYERS, 4, 0, STAR_DESIGNER_WIPE_MARGIN);
    DisplayShadow_SetSubWindow1Planes(STAR_DESIGNER_WINDOW_PLANES, 1);
    StarDesigner_FollowWipeWindow(self);
    DisplayLayer_Show(LAYER_SUB_BG0);
    DisplayLayer_Show(LAYER_SUB_BG3);
    StarDesigner_SetFlags(self, STAR_DESIGNER_FLAG_ARROWS);
    StarDesigner_SetFlags(self, STAR_DESIGNER_FLAG_PANEL);
    StarDesigner_FollowWipe(self);
    MenuScene_SetState(star_designer_base(self), STAR_DESIGNER_STATE_WIPE_IN);
}
CLEAN_AS(func_ov129_0229d6e4, StarDesigner_StateOpen)

/* func_ov129_0229d74c (vtable slot 0x5c, phase 5): the scene asks to be deleted. Answers 1. */
int StarDesigner_RequestDelete(StarDesigner *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov129_0229d74c, StarDesigner_RequestDelete)

/* func_ov129_0229d75c (vtable slot 0x58, phase 4): nothing. */
int StarDesigner_Phase4(void)
{
    return 1;
}
CLEAN_AS(func_ov129_0229d75c, StarDesigner_Phase4)

/* func_ov129_0229d760 (vtable slot 0x54, phase 3): nothing. */
int StarDesigner_Phase3(void)
{
    return 1;
}
CLEAN_AS(func_ov129_0229d760, StarDesigner_Phase3)

/* func_ov129_0229d764 (vtable slot 0x50, phase 2): an interactive frame: its start, the sub
 * state, its end. Answers 1. */
int StarDesigner_RunInteractive(StarDesigner *self)
{
    StarDesigner_BeginInteractive(self);
    StarDesigner_RunSubState(self);
    StarDesigner_EndInteractive(self);
    return 1;
}
CLEAN_AS(func_ov129_0229d764, StarDesigner_RunInteractive)

/* func_ov129_0229d780: the sub state (StarDesignerSubState) run through its table of member
 * functions, filled once from its constants.
 * REQUIRES: the sub state is below 15; the game reads past the table for others. */
void StarDesigner_RunSubState(StarDesigner *self)
{
    static const MemberPointer *const sub_states[STAR_DESIGNER_SUB_STATES] = {
        &data_ov129_0229db68, &data_ov129_0229dbd8, &data_ov129_0229db60, &data_ov129_0229dbc8, &data_ov129_0229db58,
        &data_ov129_0229db70, &data_ov129_0229db78, &data_ov129_0229dba8, &data_ov129_0229db80, &data_ov129_0229db88,
        &data_ov129_0229dbb0, &data_ov129_0229dbb8, &data_ov129_0229dbd0, &data_ov129_0229dbe0, &data_ov129_0229dbf0,
    };
    MemberTable_InitOnce(&data_ov129_0229dcc4, data_ov129_0229dd84, sub_states, STAR_DESIGNER_SUB_STATES);
    MemberPointer_CallVoid(&data_ov129_0229dd84[self->base.sub_state], self);
}
CLEAN_AS(func_ov129_0229d780, StarDesigner_RunSubState)

/* func_ov129_0229d8a0 (vtable slot 0x4c, phase 1): a frame of the states (StarDesignerState)
 * through their table of member functions (filled once from its constants), between the
 * frame's start and its end. Answers 1.
 * REQUIRES: the state is below 12; the game reads past the table for others. */
int StarDesigner_RunState(StarDesigner *self)
{
    static const MemberPointer *const states[STAR_DESIGNER_STATES] = {
        &data_ov129_0229dba0, &data_ov129_0229dbf8, &data_ov129_0229dc10, &data_ov129_0229db90,
        &data_ov129_0229db98, &data_ov129_0229dc28, &data_ov129_0229dc20, &data_ov129_0229dc18,
        &data_ov129_0229dbc0, &data_ov129_0229dc08, &data_ov129_0229dc00, &data_ov129_0229dbe8,
    };
    MemberTable_InitOnce(&data_ov129_0229dcc8, data_ov129_0229dd24, states, STAR_DESIGNER_STATES);
    StarDesigner_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov129_0229dd24[self->base.state], self);
    StarDesigner_EndFrame(self);
    return 1;
}
CLEAN_AS(func_ov129_0229d8a0, StarDesigner_RunState)

/* func_ov129_0229d9a4 (vtable slot 0x24): the scene's draw: the pointer (by the keys only), the
 * panel, the scope's centre (by the keys only), the arrows at the wipe's offset and the end of
 * the line's mark, each when its flag is set. Answers 1. */
int StarDesigner_Draw(StarDesigner *self)
{
    if (StateFlags_Test2() != 0) {
        Glider_DrawWrapped(&self->pointer);
    }
    if (StarDesigner_TestFlags(self, STAR_DESIGNER_FLAG_PANEL) != 0) {
        ButtonPanel_Draw(&self->panel, self->panel_offset);
    }
    if (StateFlags_Test2() != 0) {
        if (StarDesigner_TestFlags(self, STAR_DESIGNER_FLAG_CENTRE) != 0) {
            StarScope_DrawCentre(&self->scope, 0);
        }
    }
    if (StarDesigner_TestFlags(self, STAR_DESIGNER_FLAG_ARROWS) != 0) {
        StarScope_DrawArrows(&self->scope, self->arrows_offset, STAR_DESIGNER_ARROWS_PALETTE);
    }
    if (self->end_star != STAR_DESIGNER_NO_STAR) {
        if (StarDesigner_TestFlags(self, STAR_DESIGNER_FLAG_END_MARK) != 0) {
            StarScope_DrawStarMark(&self->scope, self->end_star);
        }
    }
    return 1;
}
CLEAN_AS(func_ov129_0229d9a4, StarDesigner_Draw)

/* func_ov129_0229da44 (vtable slot 0x0c): the scene ends: the parent told and the screen torn
 * down. Answers 1. */
int StarDesigner_End(StarDesigner *self)
{
    MenuDispatch_ChildClosed((MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self));
    StarDesigner_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov129_0229da44, StarDesigner_End)

/* func_ov129_0229da60 (vtable slot 0x00): the scene starts: its setup, state 0 and the wait
 * phase (0). Answers 1. */
int StarDesigner_Start(StarDesigner *self)
{
    StarDesigner_Setup(self);
    self->base.state = STAR_DESIGNER_STATE_OPEN;
    MenuScene_SetPhase(star_designer_base(self), STAR_DESIGNER_PHASE_WAIT);
    return 1;
}
CLEAN_AS(func_ov129_0229da60, StarDesigner_Start)

/* func_ov129_0229da80 (named by the profile at 0x0229db50): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order. */
StarDesigner *StarDesigner_New(void)
{
    StarDesigner *self = MenuScene_Alloc(sizeof(StarDesigner));

    if (self != NULL) {
        MenuScene_Construct(&self->base);
        self->base.vtable = data_ov129_0229dc38;
        ErrorMessage_Construct(&self->error);
        ButtonPanel_Construct(&self->panel);
        Glider0_Construct(&self->pointer);
        StarPalette_Construct(&self->palette);
        StarScope_Construct(&self->scope);
    }
    return self;
}
CLEAN_AS(func_ov129_0229da80, StarDesigner_New)
