/* The fish catalog of overlay 115 (fish_catalog.h): tab 2 of the menu's bar, overlay 114's
 * catalog list of the fish, with a cursor sprite that follows the list's cursor. */
#include "fish_catalog.h"

#include <stdint.h>

#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/state_flags.h"
#include "ov004/member_pointer.h"
#include "ov090/menu_tabs.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(CatalogScene, cursor) == 0x94, "cursor");
static_assert(sizeof(Glider) == 0x64 && offsetof(CatalogScene, list) == 0xf8, "list");
static_assert(sizeof(TextLabel) == 0x6c && offsetof(CatalogScene, label) == 0x13b8, "label");
static_assert(offsetof(CatalogScene, wipe_y) == 0x1424 && offsetof(CatalogScene, flags) == 0x1428, "flags");
static_assert(offsetof(CatalogScene, return_sub_state) == 0x142c, "return sub state");
static_assert(sizeof(CatalogScene) == 0x1430, "size (func_ov115_0229e7e0)");

/* The tab of the menu's bar this scene is, and the list it shows. */
#define FISH_CATALOG_TAB MENU_TAB_2
#define FISH_CATALOG_KIND CATALOG_KIND_FISH

/* The scene's vtable. */
extern const u8 data_ov115_0229e8b8[];

/* The pen: down, and gone down this frame; its place (autoload_2/input.c). */
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58; /* x */
extern u8 data_021f6c54; /* y */

/* The pad (autoload_2/input.h) and the buttons the scene reads. */
extern PadState data_021fbe40;
#define FISH_CATALOG_PAD_A 0x0001
#define FISH_CATALOG_PAD_B 0x0002
#define FISH_CATALOG_PAD_SELECT 0x0004
#define FISH_CATALOG_PAD_R 0x0100
#define FISH_CATALOG_PAD_L 0x0200
#define FISH_CATALOG_PAD_X 0x0400
#define FISH_CATALOG_PAD_Y 0x0800

/* The label's constructor and destructor, as the game hands them to __cxa_vec_ctor and
 * __cxa_vec_cleanup (TextLabel_Construct, TextLabel_Destruct). */
extern void func_02070c08(void *label);
extern void func_02070be8(void *label);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The tables of member functions (ov004/member_pointer.h): their guards, the tables and the
 * constants they are filled from. */
extern u32 data_ov115_0229e920; /* the sub states' guard */
extern u32 data_ov115_0229e924; /* the states' guard */
extern MemberPointer data_ov115_0229e948[CATALOG_SCENE_SUB_STATES];
extern MemberPointer data_ov115_0229e928[CATALOG_SCENE_STATES];
extern const MemberPointer data_ov115_0229e880; /* FishCatalog_IdleByTouch */
extern const MemberPointer data_ov115_0229e878; /* FishCatalog_DragByTouch */
extern const MemberPointer data_ov115_0229e870; /* FishCatalog_IdleByKeys */
extern const MemberPointer data_ov115_0229e860; /* FishCatalog_WaitCursorGlide */
extern const MemberPointer data_ov115_0229e888; /* FishCatalog_FinishPress */
extern const MemberPointer data_ov115_0229e890; /* FishCatalog_FinishRelease */
extern const MemberPointer data_ov115_0229e850; /* FishCatalog_StartScrollByKeys */
extern const MemberPointer data_ov115_0229e848; /* FishCatalog_ScrollWhileHeld */
extern const MemberPointer data_ov115_0229e8a0; /* FishCatalog_EndScrollByKeys */
extern const MemberPointer data_ov115_0229e840; /* FishCatalog_Setup */
extern const MemberPointer data_ov115_0229e8a8; /* FishCatalog_WipeIn */
extern const MemberPointer data_ov115_0229e868; /* FishCatalog_StartWipeOut */
extern const MemberPointer data_ov115_0229e898; /* FishCatalog_WipeOut */

static MenuScene *scene_of(CatalogScene *self)
{
    return &self->base;
}

static MenuTabs *menu_of(CatalogScene *self)
{
    return (MenuTabs *) (void *) Process_GetParent((Process *) (void *) self);
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base),
 * with whatever it answers. */
static int update_cursor(Glider *cursor)
{
    int (*const *vtable)(Glider *) = (int (*const *)(Glider *)) cursor->vtable;
    return vtable[3](cursor);
}

/* The members' destructors, last member first, then the base's. */
static void destroy_members(CatalogScene *self)
{
    self->base.vtable = data_ov115_0229e8b8;
    __cxa_vec_cleanup(&self->label, 1, sizeof(TextLabel), func_02070be8);
    func_ov114_0229d9d8(self->list);
    Glider0_Destroy(&self->cursor);
    MenuScene_DestroyBase(scene_of(self));
}

/* func_ov115_0229dd20 (vtable slot 0x40) */
CatalogScene *FishCatalog_Destroy(CatalogScene *self)
{
    destroy_members(self);
    return self;
}
CLEAN_AS(func_ov115_0229dd20, FishCatalog_Destroy)

/* func_ov115_0229dd60 (vtable slot 0x44) */
CatalogScene *FishCatalog_Delete(CatalogScene *self)
{
    destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov115_0229dd60, FishCatalog_Delete)

/* func_ov115_0229dda8 */
void FishCatalog_SetFlags(CatalogScene *self, u16 flags)
{
    self->flags |= flags;
}
CLEAN_AS(func_ov115_0229dda8, FishCatalog_SetFlags)

/* func_ov115_0229ddb8 */
int FishCatalog_TestFlags(CatalogScene *self, u16 flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov115_0229ddb8, FishCatalog_TestFlags)

/* func_ov115_0229ddd0: the cursor sprite shows the third animation of its set, and the scene
 * waits for it (sub state 5) before going back to the current sub state.
 * QUIRK: returns MenuScene_SetSubState's answer, the field's address. */
u8 *FishCatalog_BeginRelease(CatalogScene *self)
{
    Glider_ShowThirdOfSet(&self->cursor);
    self->return_sub_state = self->base.sub_state;
    return MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_RELEASE);
}
CLEAN_AS(func_ov115_0229ddd0, FishCatalog_BeginRelease)

/* func_ov115_0229ddf8: A was pressed: the cursor sprite shows the second animation of its set
 * and the scene waits for it (sub state 4). */
void FishCatalog_BeginPress(CatalogScene *self)
{
    Glider_ShowSecondOfSet(&self->cursor);
    MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_PRESS);
}
CLEAN_AS(func_ov115_0229ddf8, FishCatalog_BeginPress)

/* func_ov115_0229de10: the cursor sprite shows the first animation of its set, updated. */
void FishCatalog_ShowCursorIdle(CatalogScene *self)
{
    Glider_ShowFirstOfSet(&self->cursor);
    update_cursor(&self->cursor);
}
CLEAN_AS(func_ov115_0229de10, FishCatalog_ShowCursorIdle)

/* func_ov115_0229de2c: the cursor sprite eases to (x, y) in 3 steps, and the scene waits for it
 * (sub state 3) before going back to the current sub state. */
void FishCatalog_GlideCursorTo(CatalogScene *self, int x, int y)
{
    Glider_EaseTo(&self->cursor, x, y, 3, 1);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_CURSOR_GLIDE);
}
CLEAN_AS(func_ov115_0229de2c, FishCatalog_GlideCursorTo)

/* The list's cursor is on the bar or on a page arrow: the cursor sprite takes its other set
 * of animations there. */
static int cursor_on_bar_or_page_arrow(CatalogScene *self)
{
    return func_ov114_0229c60c(self->list) != -1 || func_ov114_0229c5f4(self->list) != 0;
}

/* func_ov115_0229de60: the list's cursor moved: the cursor sprite turns to the set of its new
 * place and glides there. */
void FishCatalog_FollowListCursor(CatalogScene *self)
{
    if (cursor_on_bar_or_page_arrow(self)) {
        Glider_TurnToSetC(&self->cursor);
    } else {
        Glider_TurnToSetA(&self->cursor);
    }
    int x = FishCatalog_CursorX(self);
    int y = FishCatalog_CursorY(self);
    FishCatalog_GlideCursorTo(self, x, y);
}
CLEAN_AS(func_ov115_0229de60, FishCatalog_FollowListCursor)

/* func_ov115_0229deb4: the cursor sprite hidden (animation 0), updated. */
void FishCatalog_HideCursor(CatalogScene *self)
{
    Glider_SetAnim(&self->cursor, GLIDER_ANIM_NONE);
    update_cursor(&self->cursor);
}
CLEAN_AS(func_ov115_0229deb4, FishCatalog_HideCursor)

/* func_ov115_0229ded0: the y of the list's cursor. */
int FishCatalog_CursorY(CatalogScene *self)
{
    return func_ov114_0229c628(self->list);
}
CLEAN_AS(func_ov115_0229ded0, FishCatalog_CursorY)

/* func_ov115_0229dedc: the x of the list's cursor. */
int FishCatalog_CursorX(CatalogScene *self)
{
    return func_ov114_0229c690(self->list);
}
CLEAN_AS(func_ov115_0229dedc, FishCatalog_CursorX)

/* func_ov115_0229dee8: the cursor's entry brought into view, the cursor sprite put at the
 * list's cursor with the set of animations of its place (13-15 on the bar or a page arrow,
 * else 1-3) and shown. */
void FishCatalog_PlaceCursor(CatalogScene *self)
{
    func_ov114_0229c3ac(self->list);
    int x = FishCatalog_CursorX(self);
    int y = FishCatalog_CursorY(self);
    Glider_PlaceAt(&self->cursor, x, y);
    if (cursor_on_bar_or_page_arrow(self)) {
        Glider_SetAnim(&self->cursor, GLIDER_ANIM_SET_C);
    } else {
        Glider_SetAnim(&self->cursor, GLIDER_ANIM_SET_A);
    }
    FishCatalog_ShowCursorIdle(self);
}
CLEAN_AS(func_ov115_0229dee8, FishCatalog_PlaceCursor)

/* func_ov115_0229df50: the label's box closed. */
void FishCatalog_CloseLabel(CatalogScene *self)
{
    self->unk_142a = 0;
    TextLabel_CloseBox(&self->label);
}
CLEAN_AS(func_ov115_0229df50, FishCatalog_CloseLabel)

/* func_ov115_0229df6c: the scene is used with the pen when the last input was by touch (state
 * flag 2 clear), else with the buttons. */
void FishCatalog_EnterInputMode(CatalogScene *self)
{
    if (StateFlags_IsClear2()) {
        FishCatalog_EnterTouchMode(self);
    } else {
        FishCatalog_EnterKeysMode(self);
    }
}
CLEAN_AS(func_ov115_0229df6c, FishCatalog_EnterInputMode)

/* func_ov115_0229df8c: used with the buttons: the cursor sprite at the list's cursor, the key
 * repeat started again, sub state 2. */
void FishCatalog_EnterKeysMode(CatalogScene *self)
{
    FishCatalog_PlaceCursor(self);
    MenuScene_ResetKeyRepeat(scene_of(self));
    MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_KEYS_IDLE);
}
CLEAN_AS(func_ov115_0229df8c, FishCatalog_EnterKeysMode)

/* func_ov115_0229dfa8: used with the pen: no cursor sprite, sub state 0. */
void FishCatalog_EnterTouchMode(CatalogScene *self)
{
    FishCatalog_HideCursor(self);
    MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_TOUCH_IDLE);
}
CLEAN_AS(func_ov115_0229dfa8, FishCatalog_EnterTouchMode)

/* The scroll handle and the cursor sprite kept at their places while the list scrolls. */
static void follow_scroll(CatalogScene *self)
{
    func_ov114_0229d52c(self->list, self->wipe_y);
    int x = FishCatalog_CursorX(self);
    int y = FishCatalog_CursorY(self);
    Glider_PlaceAt(&self->cursor, x, y);
}

/* func_ov115_0229dfc0 (sub state 8): once the list is done with the scroll (overlay 114's
 * func_ov114_0229d1dc), back to the buttons (sub state 2) through the cursor's release. */
void FishCatalog_EndScrollByKeys(CatalogScene *self)
{
    if (func_ov114_0229d1dc(self->list)) {
        MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_KEYS_IDLE);
        FishCatalog_BeginRelease(self);
    }
    follow_scroll(self);
}
CLEAN_AS(func_ov115_0229dfc0, FishCatalog_EndScrollByKeys)

/* func_ov115_0229e010 (sub state 7): while A is held the list goes on scrolling; once it is let
 * go, sub state 8. */
void FishCatalog_ScrollWhileHeld(CatalogScene *self)
{
    if (data_021fbe40.held & FISH_CATALOG_PAD_A) {
        func_ov114_0229d244(self->list);
    } else {
        func_ov114_0229d220(self->list);
        MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_SCROLL_END);
    }
    follow_scroll(self);
}
CLEAN_AS(func_ov115_0229e010, FishCatalog_ScrollWhileHeld)

/* func_ov115_0229e074 (sub state 6): the first step of a scroll asked for with A; once the
 * list is ready (overlay 114's func_ov114_0229d2d8), sub state 7. */
void FishCatalog_StartScrollByKeys(CatalogScene *self)
{
    if (func_ov114_0229d2d8(self->list) != 0) {
        MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_SCROLL_HOLD);
    }
    follow_scroll(self);
}
CLEAN_AS(func_ov115_0229e074, FishCatalog_StartScrollByKeys)

/* func_ov115_0229e0c0 (sub state 5): once the cursor sprite's animation is over, its first
 * animation and back to the sub state it came from. */
void FishCatalog_FinishRelease(CatalogScene *self)
{
    if (CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->cursor)) {
        FishCatalog_ShowCursorIdle(self);
        MenuScene_SetSubState(scene_of(self), self->return_sub_state);
    }
}
CLEAN_AS(func_ov115_0229e0c0, FishCatalog_FinishRelease)

/* func_ov115_0229e0e8 (sub state 4): once the cursor sprite's press animation is over, A acts on
 * the list's cursor: on a tab of the bar the menu switches to it (unless it is this tab); on
 * any other place the list acts (overlay 114's func_ov114_0229c2c8) and on a scroll arrow or
 * the handle a scroll starts (sub state 6). Otherwise back to the buttons (sub state 2)
 * through the cursor's release. Answers 0 while the animation runs, else what the last step
 * answers.
 * QUIRK: the answers of MenuScene_SetSubState and FishCatalog_BeginRelease are the address of
 * the sub state field, returned as an int. */
int FishCatalog_FinishPress(CatalogScene *self)
{
    int done = CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->cursor);
    if (done == 0) {
        return done;
    }
    int tab = func_ov114_0229c60c(self->list);
    if (tab != -1) {
        int switched = FishCatalog_SelectTab(self, tab);
        if (switched != 0) {
            return switched;
        }
    } else if (func_ov114_0229c2c8(self->list) != 0) {
        return (int) (uintptr_t) MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_SCROLL_START);
    }
    MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_KEYS_IDLE);
    return (int) (uintptr_t) FishCatalog_BeginRelease(self);
}
CLEAN_AS(func_ov115_0229e0e8, FishCatalog_FinishPress)

/* Obj_ov115_0229e8b8::func_ov115_0229e140 (sub state 3): once the cursor sprite has stopped,
 * back to the sub state it came from, which runs at once. */
void FishCatalog_WaitCursorGlide(CatalogScene *self)
{
    if (Glider_IsMoving(&self->cursor) == 0) {
        MenuScene_SetSubState(scene_of(self), self->return_sub_state);
        FishCatalog_RunSubState(self);
    }
}
CLEAN_AS(_ZN18Obj_ov115_0229e8b819func_ov115_0229e140Ev, FishCatalog_WaitCursorGlide)

/* func_ov115_0229e168 (sub state 2): used with the buttons. A touch goes over to the pen; the
 * key repeat moves the list's cursor (the cursor sprite follows); A presses; R and L switch to
 * the bar's next and previous tab. */
void FishCatalog_IdleByKeys(CatalogScene *self)
{
    if (MenuScene_TakeTouch(scene_of(self)) != 0) {
        FishCatalog_EnterTouchMode(self);
        return;
    }
    u32 keys = MenuScene_LatchRepeatedKeys(scene_of(self));
    if (func_ov114_0229c410(self->list, (void *) (uintptr_t) keys) != 0) {
        FishCatalog_FollowListCursor(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & FISH_CATALOG_PAD_A) {
        FishCatalog_BeginPress(self);
    } else if (pressed & FISH_CATALOG_PAD_R) {
        FishCatalog_SelectTab(self, MenuTabs_NextTab(FISH_CATALOG_TAB));
    } else if (pressed & FISH_CATALOG_PAD_L) {
        FishCatalog_SelectTab(self, MenuTabs_PreviousTab(FISH_CATALOG_TAB));
    }
}
CLEAN_AS(func_ov115_0229e168, FishCatalog_IdleByKeys)

/* func_ov115_0229e1f0 (sub state 1): while the pen is down the scroll handle follows its x;
 * once it is lifted, the handle is let go and back to sub state 0. */
void FishCatalog_DragByTouch(CatalogScene *self)
{
    if (data_021fbdd8 != 0) {
        func_ov114_0229d32c(self->list, data_021f6c58);
    } else {
        func_ov114_0229d304(self->list);
        MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_TOUCH_IDLE);
    }
}
CLEAN_AS(func_ov115_0229e1f0, FishCatalog_DragByTouch)

/* func_ov115_0229e228 (sub state 0): used with the pen. A button goes over to the buttons
 * (sound 0x3b too); a touch this frame goes to a page arrow, else to the scroll handle or a
 * scroll arrow (then dragged, sub state 1), else to an entry. */
void FishCatalog_IdleByTouch(CatalogScene *self)
{
    if (MenuScene_TakeButtons(scene_of(self), 1)) {
        FishCatalog_EnterKeysMode(self);
        return;
    }
    if (!(data_021fbdd8 != 0 && data_021fbddc != 0)) {
        return;
    }
    u8 x = data_021f6c58;
    u8 y = data_021f6c54;
    if (func_ov114_0229d564(self->list, x, y) != 0) {
        return;
    }
    if (func_ov114_0229d3f4(self->list, x, y) != 0) {
        MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_DRAG);
        return;
    }
    func_ov114_0229ca50(self->list, x, y);
}
CLEAN_AS(func_ov115_0229e228, FishCatalog_IdleByTouch)

/* func_ov115_0229e2b0: the list's OBJ files loaded and its entries filled. */
void FishCatalog_LoadObjects(CatalogScene *self)
{
    func_ov114_0229d688(self->list);
    func_ov114_0229cadc(self->list);
}
CLEAN_AS(func_ov115_0229e2b0, FishCatalog_LoadObjects)

/* func_ov115_0229e2c8: the list's background files loaded, then overlay 114's
 * func_ov114_0229c8dc. */
void FishCatalog_LoadBackground(CatalogScene *self)
{
    func_ov114_0229d700(self->list);
    func_ov114_0229c8dc(self->list);
}
CLEAN_AS(func_ov115_0229e2c8, FishCatalog_LoadBackground)

/* func_ov115_0229e2e0: the list's three layers: layer 3 at priority 1, layers 6 and 4 at
 * priority 2, each with BG control (0, 0, 0). */
void FishCatalog_SetUpLayers(void)
{
    DisplayLayer_SetPriority(CATALOG_SCENE_LAYER_A, 1);
    DisplayLayer_SetBgControl(CATALOG_SCENE_LAYER_A, 0, 0, 0);
    DisplayLayer_SetPriority(CATALOG_SCENE_LAYER_B, 2);
    DisplayLayer_SetBgControl(CATALOG_SCENE_LAYER_B, 0, 0, 0);
    DisplayLayer_SetPriority(CATALOG_SCENE_LAYER_C, 2);
    DisplayLayer_SetBgControl(CATALOG_SCENE_LAYER_C, 0, 0, 0);
}
CLEAN_AS(func_ov115_0229e2e0, FishCatalog_SetUpLayers)

/* func_ov115_0229e328: the end of a frame of the list. */
void FishCatalog_EndFrame(CatalogScene *self)
{
    func_ov114_0229d824(self->list);
}
CLEAN_AS(func_ov115_0229e328, FishCatalog_EndFrame)

/* func_ov115_0229e334: the start of a frame: the list's, the label's box closed. */
void FishCatalog_BeginFrame(CatalogScene *self)
{
    func_ov114_0229d87c(self->list);
    FishCatalog_CloseLabel(self);
}
CLEAN_AS(func_ov115_0229e334, FishCatalog_BeginFrame)

/* func_ov115_0229e34c */
void FishCatalog_EndInteractiveFrame(CatalogScene *self)
{
    FishCatalog_EndFrame(self);
}
CLEAN_AS(func_ov115_0229e34c, FishCatalog_EndInteractiveFrame)

/* func_ov115_0229e354: the start of a frame, then the cursor sprite's update, whose answer it
 * returns. */
int FishCatalog_BeginInteractiveFrame(CatalogScene *self)
{
    FishCatalog_BeginFrame(self);
    return update_cursor(&self->cursor);
}
CLEAN_AS(func_ov115_0229e354, FishCatalog_BeginInteractiveFrame)

/* func_ov115_0229e36c: the list's end, the label's box closed. */
void FishCatalog_Teardown(CatalogScene *self)
{
    func_ov114_0229d8ac(self->list);
    FishCatalog_CloseLabel(self);
}
CLEAN_AS(func_ov115_0229e36c, FishCatalog_Teardown)

/* func_ov115_0229e384: no flags; the list started on the three layers with the fish. */
void FishCatalog_Init(CatalogScene *self)
{
    self->flags = 0;
    func_ov114_0229d8d0(self->list, CATALOG_SCENE_LAYER_A, CATALOG_SCENE_LAYER_B, CATALOG_SCENE_LAYER_C, FISH_CATALOG_KIND);
}
CLEAN_AS(func_ov115_0229e384, FishCatalog_Init)

/* func_ov115_0229e3a8: the three layers scrolled with the wipe, whose y is kept for the list. */
void FishCatalog_ScrollLayers(CatalogScene *self)
{
    MenuScene_ScrollWipe(scene_of(self), CATALOG_SCENE_LAYER_A, 0, 0);
    MenuScene_ScrollWipe(scene_of(self), CATALOG_SCENE_LAYER_B, 0, 0);
    MenuScene_ScrollWipe(scene_of(self), CATALOG_SCENE_LAYER_C, 0, 0);
    self->wipe_y = MenuScene_WipeOffsetY(scene_of(self));
}
CLEAN_AS(func_ov115_0229e3a8, FishCatalog_ScrollLayers)

/* func_ov115_0229e3e4 (state 3): the wipe out; once over, the three layers hidden and the scene
 * asks to be deleted (phase 5). */
void FishCatalog_WipeOut(CatalogScene *self)
{
    if (MenuScene_StepWipe(scene_of(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(CATALOG_SCENE_LAYER_A);
        DisplayLayer_HideAndResetScroll(CATALOG_SCENE_LAYER_B);
        DisplayLayer_HideAndResetScroll(CATALOG_SCENE_LAYER_C);
        MenuScene_SetPhase(scene_of(self), CATALOG_SCENE_PHASE_DELETE);
    } else {
        FishCatalog_ScrollLayers(self);
    }
}
CLEAN_AS(func_ov115_0229e3e4, FishCatalog_WipeOut)

/* func_ov115_0229e41c (state 2): no cursor sprite, the wipe out started on window 2 (layers
 * 0xb, margin 0x30), then state 3. */
void FishCatalog_StartWipeOut(CatalogScene *self)
{
    FishCatalog_HideCursor(self);
    MenuScene_StartWipeOnWindow2(scene_of(self), 0xb, 0, 0, 0x30);
    FishCatalog_ScrollLayers(self);
    MenuScene_SetState(scene_of(self), CATALOG_SCENE_STATE_WIPE_OUT);
    func_ov114_0229c8b4(self->list);
}
CLEAN_AS(func_ov115_0229e41c, FishCatalog_StartWipeOut)

/* func_ov115_0229e454 (state 1): the wipe in; once over, the scene is used (phase 2) with the
 * pen or the buttons. */
void FishCatalog_WipeIn(CatalogScene *self)
{
    if (MenuScene_StepWipeBack(scene_of(self), 0) != 0) {
        MenuScene_SetPhase(scene_of(self), CATALOG_SCENE_PHASE_INTERACTIVE);
        FishCatalog_EnterInputMode(self);
    }
    FishCatalog_ScrollLayers(self);
}
CLEAN_AS(func_ov115_0229e454, FishCatalog_WipeIn)

/* func_ov115_0229e47c (state 0): the layers set up, the list's files loaded, the wipe in
 * started covered on window 2 (layers 0xb, margin 0x30), layers 3 and 6 shown, the scene
 * drawn; then state 1. */
void FishCatalog_Setup(CatalogScene *self)
{
    FishCatalog_SetUpLayers();
    FishCatalog_LoadBackground(self);
    FishCatalog_LoadObjects(self);
    MenuScene_StartWipeCoveredOnWindow2(scene_of(self), 0xb, 0, 0, 0x30);
    DisplayLayer_Show(CATALOG_SCENE_LAYER_A);
    DisplayLayer_Show(CATALOG_SCENE_LAYER_B);
    FishCatalog_SetFlags(self, CATALOG_SCENE_FLAG_DRAWN);
    FishCatalog_ScrollLayers(self);
    MenuScene_SetState(scene_of(self), CATALOG_SCENE_STATE_WIPE_IN);
}
CLEAN_AS(func_ov115_0229e47c, FishCatalog_Setup)

/* func_ov115_0229e4cc: a switch to `tab` of the menu (MenuTabs_SelectTab of the parent), unless
 * it is none (-1) or this tab: then the scene wipes out (state 2, phase 1). Answers whether it
 * switched. */
int FishCatalog_SelectTab(CatalogScene *self, int tab)
{
    MenuTabs *menu = menu_of(self);
    if (tab == -1 || tab == FISH_CATALOG_TAB) {
        return 0;
    }
    MenuTabs_SelectTab(menu, (u8) tab);
    self->base.state = CATALOG_SCENE_STATE_START_WIPE_OUT;
    MenuScene_SetPhase(scene_of(self), CATALOG_SCENE_PHASE_STATES);
    return 1;
}
CLEAN_AS(func_ov115_0229e4cc, FishCatalog_SelectTab)

/* func_ov115_0229e50c: the menu's own switches, before each frame of use: when main asks the
 * menu to close, the close tab; else, in sub states 0 and 2 only, the tab of the bar touched
 * this frame (with the pen) or the tab of a button (B closes, Y the pockets, X tab 5, Select
 * tab 4). Answers whether the menu switched. */
int FishCatalog_CheckTabKeys(CatalogScene *self)
{
    StateFlags_CountMenuCloseDelay();
    if (StateFlags_MenuCloseAsked()) {
        return FishCatalog_SelectTab(self, MENU_TAB_CLOSE);
    }
    u8 sub_state = self->base.sub_state;
    if (sub_state != CATALOG_SCENE_SUB_TOUCH_IDLE && sub_state != CATALOG_SCENE_SUB_KEYS_IDLE) {
        return 0;
    }
    int tab = -1;
    if (StateFlags_IsClear2()) {
        tab = MenuTabs_TabAtTouch();
    } else {
        u16 pressed = data_021fbe40.pressed;
        if (pressed & FISH_CATALOG_PAD_B) {
            tab = MENU_TAB_CLOSE;
        } else if (pressed & FISH_CATALOG_PAD_Y) {
            tab = MENU_TAB_POCKETS;
        } else if (pressed & FISH_CATALOG_PAD_X) {
            tab = MENU_TAB_5;
        } else if (pressed & FISH_CATALOG_PAD_SELECT) {
            tab = MENU_TAB_4;
        }
    }
    return FishCatalog_SelectTab(self, tab);
}
CLEAN_AS(func_ov115_0229e50c, FishCatalog_CheckTabKeys)

/* func_ov115_0229e5a4 (vtable slot 0x5c, phase 5): the scene asks to be deleted. */
int FishCatalog_RequestDelete(CatalogScene *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov115_0229e5a4, FishCatalog_RequestDelete)

/* func_ov115_0229e5b4 (vtable slot 0x58, phase 4): nothing. */
int FishCatalog_Phase4(void)
{
    return 1;
}
CLEAN_AS(func_ov115_0229e5b4, FishCatalog_Phase4)

/* func_ov115_0229e5b8 (vtable slot 0x54, phase 3): nothing. */
int FishCatalog_Phase3(void)
{
    return 1;
}
CLEAN_AS(func_ov115_0229e5b8, FishCatalog_Phase3)

/* Obj_ov115_0229e8b8::func_ov115_0229e5bc (vtable slot 0x50, phase 2): a frame of the scene in
 * use, unless the menu switched tabs first: its start, its sub state, its end. Answers 1. */
int FishCatalog_RunInteractive(CatalogScene *self)
{
    if (FishCatalog_CheckTabKeys(self)) {
        return 1;
    }
    FishCatalog_BeginInteractiveFrame(self);
    FishCatalog_RunSubState(self);
    FishCatalog_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov115_0229e8b819func_ov115_0229e5bcEv, FishCatalog_RunInteractive)

/* Obj_ov115_0229e8b8::func_ov115_0229e5e8: the sub state's function (CatalogSceneSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 9; the game reads past the table for others. */
void FishCatalog_RunSubState(CatalogScene *self)
{
    static const MemberPointer *const sub_states[CATALOG_SCENE_SUB_STATES] = {
        &data_ov115_0229e880, &data_ov115_0229e878, &data_ov115_0229e870, &data_ov115_0229e860, &data_ov115_0229e888,
        &data_ov115_0229e890, &data_ov115_0229e850, &data_ov115_0229e848, &data_ov115_0229e8a0,
    };
    MemberTable_InitOnce(&data_ov115_0229e920, data_ov115_0229e948, sub_states, CATALOG_SCENE_SUB_STATES);
    MemberPointer_CallVoid(&data_ov115_0229e948[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov115_0229e8b819func_ov115_0229e5e8Ev, FishCatalog_RunSubState)

/* func_ov115_0229e6b4 (vtable slot 0x4c, phase 1): a frame of the scene's states
 * (CatalogSceneState) between the frame's start and end, through the table of member functions
 * (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 4; the game reads past the table for others. */
int FishCatalog_RunState(CatalogScene *self)
{
    static const MemberPointer *const states[CATALOG_SCENE_STATES] = {
        &data_ov115_0229e840,
        &data_ov115_0229e8a8,
        &data_ov115_0229e868,
        &data_ov115_0229e898,
    };
    MemberTable_InitOnce(&data_ov115_0229e924, data_ov115_0229e928, states, CATALOG_SCENE_STATES);
    FishCatalog_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov115_0229e928[self->base.state], self);
    FishCatalog_EndFrame(self);
    return 1;
}
CLEAN_AS(func_ov115_0229e6b4, FishCatalog_RunState)

/* func_ov115_0229e748 (vtable slot 0x24): the scene's draw, once drawn: the scroll handle at
 * the wipe's y, the cursor sprite (while the buttons are in use), the list's arrows, entries
 * and member at 0x121c. Answers 1. */
int FishCatalog_Draw(CatalogScene *self)
{
    if (FishCatalog_TestFlags(self, CATALOG_SCENE_FLAG_DRAWN) == 0) {
        return 1;
    }
    func_ov114_0229d52c(self->list, self->wipe_y);
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor);
    }
    func_ov114_0229d5b8(self->list, self->wipe_y);
    func_ov114_0229cbe4(self->list, self->wipe_y);
    func_ov114_0229d54c(self->list);
    return 1;
}
CLEAN_AS(func_ov115_0229e748, FishCatalog_Draw)

/* func_ov115_0229e7a4 (vtable slot 0x0c): the scene closes: the menu told (MenuTabs_ChildClosed)
 * and the list ended. Answers 1. */
int FishCatalog_End(CatalogScene *self)
{
    MenuTabs_ChildClosed(menu_of(self));
    FishCatalog_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov115_0229e7a4, FishCatalog_End)

/* func_ov115_0229e7c0 (vtable slot 0x00): the scene starts: the list started, state 0 and
 * phase 1. Answers 1. */
int FishCatalog_Start(CatalogScene *self)
{
    FishCatalog_Init(self);
    MenuScene_SetState(scene_of(self), CATALOG_SCENE_STATE_SETUP);
    MenuScene_SetPhase(scene_of(self), CATALOG_SCENE_PHASE_STATES);
    return 1;
}
CLEAN_AS(func_ov115_0229e7c0, FishCatalog_Start)

/* func_ov115_0229e7e0: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base, the scene's vtable, the cursor sprite, the list and the label. */
CatalogScene *FishCatalog_New(void)
{
    CatalogScene *self = MenuScene_Alloc(sizeof(CatalogScene));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov115_0229e8b8;
    Glider0_Construct(&self->cursor);
    func_ov114_0229da18(self->list);
    __cxa_vec_ctor(&self->label, 1, sizeof(TextLabel), func_02070c08, func_02070be8);
    return self;
}
CLEAN_AS(func_ov115_0229e7e0, FishCatalog_New)
