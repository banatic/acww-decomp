/* The insect catalog of overlay 116 (insect_catalog.h): tab 3 of the menu's bar, overlay 114's
 * catalog list of the insects, with a cursor sprite that follows the list's cursor. */
#include "insect_catalog.h"

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
static_assert(sizeof(CatalogList) == 0x12c0, "list size");
static_assert(sizeof(TextLabel) == 0x6c && offsetof(CatalogScene, label) == 0x13b8, "label");
static_assert(offsetof(CatalogScene, wipe_y) == 0x1424 && offsetof(CatalogScene, flags) == 0x1428, "flags");
static_assert(offsetof(CatalogScene, return_sub_state) == 0x142c, "return sub state");
static_assert(sizeof(CatalogScene) == 0x1430, "size (func_ov116_0229e7e0)");

/* The tab of the menu's bar this scene is, and the list it shows. */
#define INSECT_CATALOG_TAB MENU_TAB_3
#define INSECT_CATALOG_KIND CATALOG_KIND_INSECTS

/* The scene's vtable. */
extern const u8 data_ov116_0229e8b8[];

/* The pen: down, and gone down this frame; its place (autoload_2/input.c). */
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58; /* x */
extern u8 data_021f6c54; /* y */

/* The pad (autoload_2/input.h) and the buttons the scene reads. */
extern PadState data_021fbe40;
#define INSECT_CATALOG_PAD_A 0x0001
#define INSECT_CATALOG_PAD_B 0x0002
#define INSECT_CATALOG_PAD_SELECT 0x0004
#define INSECT_CATALOG_PAD_R 0x0100
#define INSECT_CATALOG_PAD_L 0x0200
#define INSECT_CATALOG_PAD_X 0x0400
#define INSECT_CATALOG_PAD_Y 0x0800

/* The label's constructor and destructor, as the game hands them to __cxa_vec_ctor and
 * __cxa_vec_cleanup (TextLabel_Construct, TextLabel_Destruct). */
extern void func_02070c08(void *label);
extern void func_02070be8(void *label);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The tables of member functions (ov004/member_pointer.h): their guards, the tables and the
 * constants they are filled from. */
extern u32 data_ov116_0229e920; /* the sub states' guard */
extern u32 data_ov116_0229e924; /* the states' guard */
extern MemberPointer data_ov116_0229e948[CATALOG_SCENE_SUB_STATES];
extern MemberPointer data_ov116_0229e928[CATALOG_SCENE_STATES];
extern const MemberPointer data_ov116_0229e880; /* InsectCatalog_IdleByTouch */
extern const MemberPointer data_ov116_0229e878; /* InsectCatalog_DragByTouch */
extern const MemberPointer data_ov116_0229e870; /* InsectCatalog_IdleByKeys */
extern const MemberPointer data_ov116_0229e860; /* InsectCatalog_WaitCursorGlide */
extern const MemberPointer data_ov116_0229e888; /* InsectCatalog_FinishPress */
extern const MemberPointer data_ov116_0229e890; /* InsectCatalog_FinishRelease */
extern const MemberPointer data_ov116_0229e850; /* InsectCatalog_StartScrollByKeys */
extern const MemberPointer data_ov116_0229e848; /* InsectCatalog_ScrollWhileHeld */
extern const MemberPointer data_ov116_0229e8a0; /* InsectCatalog_EndScrollByKeys */
extern const MemberPointer data_ov116_0229e840; /* InsectCatalog_Setup */
extern const MemberPointer data_ov116_0229e8a8; /* InsectCatalog_WipeIn */
extern const MemberPointer data_ov116_0229e868; /* InsectCatalog_StartWipeOut */
extern const MemberPointer data_ov116_0229e898; /* InsectCatalog_WipeOut */

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
    self->base.vtable = data_ov116_0229e8b8;
    __cxa_vec_cleanup(&self->label, 1, sizeof(TextLabel), func_02070be8);
    CatalogList_Destroy(&self->list);
    Glider0_Destroy(&self->cursor);
    MenuScene_DestroyBase(scene_of(self));
}

/* func_ov116_0229dd20 (vtable slot 0x40) */
CatalogScene *InsectCatalog_Destroy(CatalogScene *self)
{
    destroy_members(self);
    return self;
}
CLEAN_AS(func_ov116_0229dd20, InsectCatalog_Destroy)

/* func_ov116_0229dd60 (vtable slot 0x44) */
CatalogScene *InsectCatalog_Delete(CatalogScene *self)
{
    destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov116_0229dd60, InsectCatalog_Delete)

/* func_ov116_0229dda8 */
void InsectCatalog_SetFlags(CatalogScene *self, u16 flags)
{
    self->flags |= flags;
}
CLEAN_AS(func_ov116_0229dda8, InsectCatalog_SetFlags)

/* func_ov116_0229ddb8 */
int InsectCatalog_TestFlags(CatalogScene *self, u16 flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov116_0229ddb8, InsectCatalog_TestFlags)

/* func_ov116_0229ddd0: the cursor sprite shows the third animation of its set, and the scene
 * waits for it (sub state 5) before going back to the current sub state.
 * QUIRK: returns MenuScene_SetSubState's answer, the field's address. */
u8 *InsectCatalog_BeginRelease(CatalogScene *self)
{
    Glider_ShowThirdOfSet(&self->cursor);
    self->return_sub_state = self->base.sub_state;
    return MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_RELEASE);
}
CLEAN_AS(func_ov116_0229ddd0, InsectCatalog_BeginRelease)

/* func_ov116_0229ddf8: A was pressed: the cursor sprite shows the second animation of its set
 * and the scene waits for it (sub state 4). */
void InsectCatalog_BeginPress(CatalogScene *self)
{
    Glider_ShowSecondOfSet(&self->cursor);
    MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_PRESS);
}
CLEAN_AS(func_ov116_0229ddf8, InsectCatalog_BeginPress)

/* func_ov116_0229de10: the cursor sprite shows the first animation of its set, updated. */
void InsectCatalog_ShowCursorIdle(CatalogScene *self)
{
    Glider_ShowFirstOfSet(&self->cursor);
    update_cursor(&self->cursor);
}
CLEAN_AS(func_ov116_0229de10, InsectCatalog_ShowCursorIdle)

/* func_ov116_0229de2c: the cursor sprite eases to (x, y) in 3 steps, and the scene waits for it
 * (sub state 3) before going back to the current sub state. */
void InsectCatalog_GlideCursorTo(CatalogScene *self, int x, int y)
{
    Glider_EaseTo(&self->cursor, x, y, 3, 1);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_CURSOR_GLIDE);
}
CLEAN_AS(func_ov116_0229de2c, InsectCatalog_GlideCursorTo)

/* The list's cursor is on the bar or on a page arrow: the cursor sprite takes its other set
 * of animations there. */
static int cursor_on_bar_or_page_arrow(CatalogScene *self)
{
    return CatalogList_TabUnderCursor(&self->list) != -1 || CatalogList_OnPageArrow(&self->list) != 0;
}

/* func_ov116_0229de60: the list's cursor moved: the cursor sprite turns to the set of its new
 * place and glides there. */
void InsectCatalog_FollowListCursor(CatalogScene *self)
{
    if (cursor_on_bar_or_page_arrow(self)) {
        Glider_TurnToSetC(&self->cursor);
    } else {
        Glider_TurnToSetA(&self->cursor);
    }
    int x = InsectCatalog_CursorX(self);
    int y = InsectCatalog_CursorY(self);
    InsectCatalog_GlideCursorTo(self, x, y);
}
CLEAN_AS(func_ov116_0229de60, InsectCatalog_FollowListCursor)

/* func_ov116_0229deb4: the cursor sprite hidden (animation 0), updated. */
void InsectCatalog_HideCursor(CatalogScene *self)
{
    Glider_SetAnim(&self->cursor, GLIDER_ANIM_NONE);
    update_cursor(&self->cursor);
}
CLEAN_AS(func_ov116_0229deb4, InsectCatalog_HideCursor)

/* func_ov116_0229ded0: the y of the list's cursor. */
int InsectCatalog_CursorY(CatalogScene *self)
{
    return CatalogList_CursorY(&self->list);
}
CLEAN_AS(func_ov116_0229ded0, InsectCatalog_CursorY)

/* func_ov116_0229dedc: the x of the list's cursor. */
int InsectCatalog_CursorX(CatalogScene *self)
{
    return CatalogList_CursorX(&self->list);
}
CLEAN_AS(func_ov116_0229dedc, InsectCatalog_CursorX)

/* func_ov116_0229dee8: the cursor's entry brought into view, the cursor sprite put at the
 * list's cursor with the set of animations of its place (13-15 on the bar or a page arrow,
 * else 1-3) and shown. */
void InsectCatalog_PlaceCursor(CatalogScene *self)
{
    CatalogList_KeepCursorInView(&self->list);
    int x = InsectCatalog_CursorX(self);
    int y = InsectCatalog_CursorY(self);
    Glider_PlaceAt(&self->cursor, x, y);
    if (cursor_on_bar_or_page_arrow(self)) {
        Glider_SetAnim(&self->cursor, GLIDER_ANIM_SET_C);
    } else {
        Glider_SetAnim(&self->cursor, GLIDER_ANIM_SET_A);
    }
    InsectCatalog_ShowCursorIdle(self);
}
CLEAN_AS(func_ov116_0229dee8, InsectCatalog_PlaceCursor)

/* func_ov116_0229df50: the label's box closed. */
void InsectCatalog_CloseLabel(CatalogScene *self)
{
    self->unk_142a = 0;
    TextLabel_CloseBox(&self->label);
}
CLEAN_AS(func_ov116_0229df50, InsectCatalog_CloseLabel)

/* func_ov116_0229df6c: the scene is used with the pen when the last input was by touch (state
 * flag 2 clear), else with the buttons. */
void InsectCatalog_EnterInputMode(CatalogScene *self)
{
    if (StateFlags_IsClear2()) {
        InsectCatalog_EnterTouchMode(self);
    } else {
        InsectCatalog_EnterKeysMode(self);
    }
}
CLEAN_AS(func_ov116_0229df6c, InsectCatalog_EnterInputMode)

/* func_ov116_0229df8c: used with the buttons: the cursor sprite at the list's cursor, the key
 * repeat started again, sub state 2. */
void InsectCatalog_EnterKeysMode(CatalogScene *self)
{
    InsectCatalog_PlaceCursor(self);
    MenuScene_ResetKeyRepeat(scene_of(self));
    MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_KEYS_IDLE);
}
CLEAN_AS(func_ov116_0229df8c, InsectCatalog_EnterKeysMode)

/* func_ov116_0229dfa8: used with the pen: no cursor sprite, sub state 0. */
void InsectCatalog_EnterTouchMode(CatalogScene *self)
{
    InsectCatalog_HideCursor(self);
    MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_TOUCH_IDLE);
}
CLEAN_AS(func_ov116_0229dfa8, InsectCatalog_EnterTouchMode)

/* The scroll handle and the cursor sprite kept at their places while the list scrolls. */
static void follow_scroll(CatalogScene *self)
{
    CatalogList_PlaceHandle(&self->list, self->wipe_y);
    int x = InsectCatalog_CursorX(self);
    int y = InsectCatalog_CursorY(self);
    Glider_PlaceAt(&self->cursor, x, y);
}

/* func_ov116_0229dfc0 (sub state 8): once the list is done with the scroll (overlay 114's
 * CatalogList_FinishHandle), back to the buttons (sub state 2) through the cursor's release. */
void InsectCatalog_EndScrollByKeys(CatalogScene *self)
{
    if (CatalogList_FinishHandle(&self->list)) {
        MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_KEYS_IDLE);
        InsectCatalog_BeginRelease(self);
    }
    follow_scroll(self);
}
CLEAN_AS(func_ov116_0229dfc0, InsectCatalog_EndScrollByKeys)

/* func_ov116_0229e010 (sub state 7): while A is held the list goes on scrolling; once it is let
 * go, sub state 8. */
void InsectCatalog_ScrollWhileHeld(CatalogScene *self)
{
    if (data_021fbe40.held & INSECT_CATALOG_PAD_A) {
        CatalogList_ScrollByKeys(&self->list);
    } else {
        CatalogList_ReleaseHandle(&self->list);
        MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_SCROLL_END);
    }
    follow_scroll(self);
}
CLEAN_AS(func_ov116_0229e010, InsectCatalog_ScrollWhileHeld)

/* func_ov116_0229e074 (sub state 6): the first step of a scroll asked for with A; once the
 * list is ready (overlay 114's CatalogList_HandleSettled), sub state 7. */
void InsectCatalog_StartScrollByKeys(CatalogScene *self)
{
    if (CatalogList_HandleSettled(&self->list) != 0) {
        MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_SCROLL_HOLD);
    }
    follow_scroll(self);
}
CLEAN_AS(func_ov116_0229e074, InsectCatalog_StartScrollByKeys)

/* func_ov116_0229e0c0 (sub state 5): once the cursor sprite's animation is over, its first
 * animation and back to the sub state it came from. */
void InsectCatalog_FinishRelease(CatalogScene *self)
{
    if (CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->cursor)) {
        InsectCatalog_ShowCursorIdle(self);
        MenuScene_SetSubState(scene_of(self), self->return_sub_state);
    }
}
CLEAN_AS(func_ov116_0229e0c0, InsectCatalog_FinishRelease)

/* func_ov116_0229e0e8 (sub state 4): once the cursor sprite's press animation is over, A acts on
 * the list's cursor: on a tab of the bar the menu switches to it (unless it is this tab); on
 * any other place the list acts (overlay 114's CatalogList_RunAction) and on a scroll arrow or
 * the handle a scroll starts (sub state 6). Otherwise back to the buttons (sub state 2)
 * through the cursor's release. Answers 0 while the animation runs, else what the last step
 * answers.
 * QUIRK: the answers of MenuScene_SetSubState and InsectCatalog_BeginRelease are the address of
 * the sub state field, returned as an int. */
int InsectCatalog_FinishPress(CatalogScene *self)
{
    int done = CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->cursor);
    if (done == 0) {
        return done;
    }
    int tab = CatalogList_TabUnderCursor(&self->list);
    if (tab != -1) {
        int switched = InsectCatalog_SelectTab(self, tab);
        if (switched != 0) {
            return switched;
        }
    } else if (CatalogList_RunAction(&self->list) != 0) {
        return (int) (uintptr_t) MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_SCROLL_START);
    }
    MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_KEYS_IDLE);
    return (int) (uintptr_t) InsectCatalog_BeginRelease(self);
}
CLEAN_AS(func_ov116_0229e0e8, InsectCatalog_FinishPress)

/* Obj_ov116_0229e8b8::func_ov116_0229e140 (sub state 3): once the cursor sprite has stopped,
 * back to the sub state it came from, which runs at once. */
void InsectCatalog_WaitCursorGlide(CatalogScene *self)
{
    if (Glider_IsMoving(&self->cursor) == 0) {
        MenuScene_SetSubState(scene_of(self), self->return_sub_state);
        InsectCatalog_RunSubState(self);
    }
}
CLEAN_AS(_ZN18Obj_ov116_0229e8b819func_ov116_0229e140Ev, InsectCatalog_WaitCursorGlide)

/* func_ov116_0229e168 (sub state 2): used with the buttons. A touch goes over to the pen; the
 * key repeat moves the list's cursor (the cursor sprite follows); A presses; R and L switch to
 * the bar's next and previous tab. */
void InsectCatalog_IdleByKeys(CatalogScene *self)
{
    if (MenuScene_TakeTouch(scene_of(self)) != 0) {
        InsectCatalog_EnterTouchMode(self);
        return;
    }
    u32 keys = MenuScene_LatchRepeatedKeys(scene_of(self));
    if (CatalogList_MoveCursor(&self->list, keys) != 0) {
        InsectCatalog_FollowListCursor(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & INSECT_CATALOG_PAD_A) {
        InsectCatalog_BeginPress(self);
    } else if (pressed & INSECT_CATALOG_PAD_R) {
        InsectCatalog_SelectTab(self, MenuTabs_NextTab(INSECT_CATALOG_TAB));
    } else if (pressed & INSECT_CATALOG_PAD_L) {
        InsectCatalog_SelectTab(self, MenuTabs_PreviousTab(INSECT_CATALOG_TAB));
    }
}
CLEAN_AS(func_ov116_0229e168, InsectCatalog_IdleByKeys)

/* func_ov116_0229e1f0 (sub state 1): while the pen is down the scroll handle follows its x;
 * once it is lifted, the handle is let go and back to sub state 0. */
void InsectCatalog_DragByTouch(CatalogScene *self)
{
    if (data_021fbdd8 != 0) {
        CatalogList_Drag(&self->list, data_021f6c58);
    } else {
        CatalogList_EndDrag(&self->list);
        MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_TOUCH_IDLE);
    }
}
CLEAN_AS(func_ov116_0229e1f0, InsectCatalog_DragByTouch)

/* func_ov116_0229e228 (sub state 0): used with the pen. A button goes over to the buttons
 * (sound 0x3b too); a touch this frame goes to a page arrow, else to the scroll handle or a
 * scroll arrow (then dragged, sub state 1), else to an entry. */
void InsectCatalog_IdleByTouch(CatalogScene *self)
{
    if (MenuScene_TakeButtons(scene_of(self), 1)) {
        InsectCatalog_EnterKeysMode(self);
        return;
    }
    if (!(data_021fbdd8 != 0 && data_021fbddc != 0)) {
        return;
    }
    u8 x = data_021f6c58;
    u8 y = data_021f6c54;
    if (CatalogList_TouchPageArrow(&self->list, x, y) != 0) {
        return;
    }
    if (CatalogList_TouchHandle(&self->list, x, y) != 0) {
        MenuScene_SetSubState(scene_of(self), CATALOG_SCENE_SUB_DRAG);
        return;
    }
    CatalogList_TouchEntry(&self->list, x, y);
}
CLEAN_AS(func_ov116_0229e228, InsectCatalog_IdleByTouch)

/* func_ov116_0229e2b0: the list's OBJ files loaded and its entries filled. */
void InsectCatalog_LoadObjects(CatalogScene *self)
{
    CatalogList_LoadObjFiles(&self->list);
    CatalogList_FillEntries(&self->list);
}
CLEAN_AS(func_ov116_0229e2b0, InsectCatalog_LoadObjects)

/* func_ov116_0229e2c8: the list's background files loaded, then overlay 114's
 * CatalogList_ResetPicture. */
void InsectCatalog_LoadBackground(CatalogScene *self)
{
    CatalogList_LoadBackground(&self->list);
    CatalogList_ResetPicture(&self->list);
}
CLEAN_AS(func_ov116_0229e2c8, InsectCatalog_LoadBackground)

/* func_ov116_0229e2e0: the list's three layers: layer 3 at priority 1, layers 6 and 4 at
 * priority 2, each with BG control (0, 0, 0). */
void InsectCatalog_SetUpLayers(void)
{
    DisplayLayer_SetPriority(CATALOG_SCENE_LAYER_A, 1);
    DisplayLayer_SetBgControl(CATALOG_SCENE_LAYER_A, 0, 0, 0);
    DisplayLayer_SetPriority(CATALOG_SCENE_LAYER_B, 2);
    DisplayLayer_SetBgControl(CATALOG_SCENE_LAYER_B, 0, 0, 0);
    DisplayLayer_SetPriority(CATALOG_SCENE_LAYER_C, 2);
    DisplayLayer_SetBgControl(CATALOG_SCENE_LAYER_C, 0, 0, 0);
}
CLEAN_AS(func_ov116_0229e2e0, InsectCatalog_SetUpLayers)

/* func_ov116_0229e328: the end of a frame of the list. */
void InsectCatalog_EndFrame(CatalogScene *self)
{
    CatalogList_EndFrame(&self->list);
}
CLEAN_AS(func_ov116_0229e328, InsectCatalog_EndFrame)

/* func_ov116_0229e334: the start of a frame: the list's, the label's box closed. */
void InsectCatalog_BeginFrame(CatalogScene *self)
{
    CatalogList_BeginFrame(&self->list);
    InsectCatalog_CloseLabel(self);
}
CLEAN_AS(func_ov116_0229e334, InsectCatalog_BeginFrame)

/* func_ov116_0229e34c */
void InsectCatalog_EndInteractiveFrame(CatalogScene *self)
{
    InsectCatalog_EndFrame(self);
}
CLEAN_AS(func_ov116_0229e34c, InsectCatalog_EndInteractiveFrame)

/* func_ov116_0229e354: the start of a frame, then the cursor sprite's update. */
void InsectCatalog_BeginInteractiveFrame(CatalogScene *self)
{
    InsectCatalog_BeginFrame(self);
    update_cursor(&self->cursor);
}
CLEAN_AS(func_ov116_0229e354, InsectCatalog_BeginInteractiveFrame)

/* func_ov116_0229e36c: the list's end, the label's box closed. */
void InsectCatalog_Teardown(CatalogScene *self)
{
    CatalogList_Teardown(&self->list);
    InsectCatalog_CloseLabel(self);
}
CLEAN_AS(func_ov116_0229e36c, InsectCatalog_Teardown)

/* func_ov116_0229e384: no flags; the list started on the three layers with the insects. */
void InsectCatalog_Init(CatalogScene *self)
{
    self->flags = 0;
    CatalogList_Start(&self->list, CATALOG_SCENE_LAYER_A, CATALOG_SCENE_LAYER_B, CATALOG_SCENE_LAYER_C, INSECT_CATALOG_KIND);
}
CLEAN_AS(func_ov116_0229e384, InsectCatalog_Init)

/* func_ov116_0229e3a8: the three layers scrolled with the wipe, whose y is kept for the list. */
void InsectCatalog_ScrollLayers(CatalogScene *self)
{
    MenuScene_ScrollWipe(scene_of(self), CATALOG_SCENE_LAYER_A, 0, 0);
    MenuScene_ScrollWipe(scene_of(self), CATALOG_SCENE_LAYER_B, 0, 0);
    MenuScene_ScrollWipe(scene_of(self), CATALOG_SCENE_LAYER_C, 0, 0);
    self->wipe_y = MenuScene_WipeOffsetY(scene_of(self));
}
CLEAN_AS(func_ov116_0229e3a8, InsectCatalog_ScrollLayers)

/* func_ov116_0229e3e4 (state 3): the wipe out; once over, the three layers hidden and the scene
 * asks to be deleted (phase 5). */
void InsectCatalog_WipeOut(CatalogScene *self)
{
    if (MenuScene_StepWipe(scene_of(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(CATALOG_SCENE_LAYER_A);
        DisplayLayer_HideAndResetScroll(CATALOG_SCENE_LAYER_B);
        DisplayLayer_HideAndResetScroll(CATALOG_SCENE_LAYER_C);
        MenuScene_SetPhase(scene_of(self), CATALOG_SCENE_PHASE_DELETE);
    } else {
        InsectCatalog_ScrollLayers(self);
    }
}
CLEAN_AS(func_ov116_0229e3e4, InsectCatalog_WipeOut)

/* func_ov116_0229e41c (state 2): no cursor sprite, the wipe out started on window 2 (layers
 * 0xb, margin 0x30), then state 3. */
void InsectCatalog_StartWipeOut(CatalogScene *self)
{
    InsectCatalog_HideCursor(self);
    MenuScene_StartWipeOnWindow2(scene_of(self), 0xb, 0, 0, 0x30);
    InsectCatalog_ScrollLayers(self);
    MenuScene_SetState(scene_of(self), CATALOG_SCENE_STATE_WIPE_OUT);
    CatalogList_HoldPicture(&self->list);
}
CLEAN_AS(func_ov116_0229e41c, InsectCatalog_StartWipeOut)

/* func_ov116_0229e454 (state 1): the wipe in; once over, the scene is used (phase 2) with the
 * pen or the buttons. */
void InsectCatalog_WipeIn(CatalogScene *self)
{
    if (MenuScene_StepWipeBack(scene_of(self), 0) != 0) {
        MenuScene_SetPhase(scene_of(self), CATALOG_SCENE_PHASE_INTERACTIVE);
        InsectCatalog_EnterInputMode(self);
    }
    InsectCatalog_ScrollLayers(self);
}
CLEAN_AS(func_ov116_0229e454, InsectCatalog_WipeIn)

/* func_ov116_0229e47c (state 0): the layers set up, the list's files loaded, the wipe in
 * started covered on window 2 (layers 0xb, margin 0x30), layers 3 and 6 shown, the scene
 * drawn; then state 1. */
void InsectCatalog_Setup(CatalogScene *self)
{
    InsectCatalog_SetUpLayers();
    InsectCatalog_LoadBackground(self);
    InsectCatalog_LoadObjects(self);
    MenuScene_StartWipeCoveredOnWindow2(scene_of(self), 0xb, 0, 0, 0x30);
    DisplayLayer_Show(CATALOG_SCENE_LAYER_A);
    DisplayLayer_Show(CATALOG_SCENE_LAYER_B);
    InsectCatalog_SetFlags(self, CATALOG_SCENE_FLAG_DRAWN);
    InsectCatalog_ScrollLayers(self);
    MenuScene_SetState(scene_of(self), CATALOG_SCENE_STATE_WIPE_IN);
}
CLEAN_AS(func_ov116_0229e47c, InsectCatalog_Setup)

/* func_ov116_0229e4cc: a switch to `tab` of the menu (MenuTabs_SelectTab of the parent), unless
 * it is none (-1) or this tab: then the scene wipes out (state 2, phase 1). Answers whether it
 * switched. */
int InsectCatalog_SelectTab(CatalogScene *self, int tab)
{
    MenuTabs *menu = menu_of(self);
    if (tab == -1 || tab == INSECT_CATALOG_TAB) {
        return 0;
    }
    MenuTabs_SelectTab(menu, (u8) tab);
    self->base.state = CATALOG_SCENE_STATE_START_WIPE_OUT;
    MenuScene_SetPhase(scene_of(self), CATALOG_SCENE_PHASE_STATES);
    return 1;
}
CLEAN_AS(func_ov116_0229e4cc, InsectCatalog_SelectTab)

/* func_ov116_0229e50c: the menu's own switches, before each frame of use: when main asks the
 * menu to close, the close tab; else, in sub states 0 and 2 only, the tab of the bar touched
 * this frame (with the pen) or the tab of a button (B closes, Y the pockets, X tab 5, Select
 * tab 4). Answers whether the menu switched. */
int InsectCatalog_CheckTabKeys(CatalogScene *self)
{
    StateFlags_CountMenuCloseDelay();
    if (StateFlags_MenuCloseAsked()) {
        return InsectCatalog_SelectTab(self, MENU_TAB_CLOSE);
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
        if (pressed & INSECT_CATALOG_PAD_B) {
            tab = MENU_TAB_CLOSE;
        } else if (pressed & INSECT_CATALOG_PAD_Y) {
            tab = MENU_TAB_POCKETS;
        } else if (pressed & INSECT_CATALOG_PAD_X) {
            tab = MENU_TAB_5;
        } else if (pressed & INSECT_CATALOG_PAD_SELECT) {
            tab = MENU_TAB_4;
        }
    }
    return InsectCatalog_SelectTab(self, tab);
}
CLEAN_AS(func_ov116_0229e50c, InsectCatalog_CheckTabKeys)

/* func_ov116_0229e5a4 (vtable slot 0x5c, phase 5): the scene asks to be deleted. */
int InsectCatalog_RequestDelete(CatalogScene *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov116_0229e5a4, InsectCatalog_RequestDelete)

/* func_ov116_0229e5b4 (vtable slot 0x58, phase 4): nothing. */
int InsectCatalog_Phase4(void)
{
    return 1;
}
CLEAN_AS(func_ov116_0229e5b4, InsectCatalog_Phase4)

/* func_ov116_0229e5b8 (vtable slot 0x54, phase 3): nothing. */
int InsectCatalog_Phase3(void)
{
    return 1;
}
CLEAN_AS(func_ov116_0229e5b8, InsectCatalog_Phase3)

/* Obj_ov116_0229e8b8::func_ov116_0229e5bc (vtable slot 0x50, phase 2): a frame of the scene in
 * use, unless the menu switched tabs first: its start, its sub state, its end. Answers 1. */
int InsectCatalog_RunInteractive(CatalogScene *self)
{
    if (InsectCatalog_CheckTabKeys(self)) {
        return 1;
    }
    InsectCatalog_BeginInteractiveFrame(self);
    InsectCatalog_RunSubState(self);
    InsectCatalog_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov116_0229e8b819func_ov116_0229e5bcEv, InsectCatalog_RunInteractive)

/* Obj_ov116_0229e8b8::func_ov116_0229e5e8: the sub state's function (CatalogSceneSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 9; the game reads past the table for others. */
void InsectCatalog_RunSubState(CatalogScene *self)
{
    static const MemberPointer *const sub_states[CATALOG_SCENE_SUB_STATES] = {
        &data_ov116_0229e880, &data_ov116_0229e878, &data_ov116_0229e870, &data_ov116_0229e860, &data_ov116_0229e888,
        &data_ov116_0229e890, &data_ov116_0229e850, &data_ov116_0229e848, &data_ov116_0229e8a0,
    };
    MemberTable_InitOnce(&data_ov116_0229e920, data_ov116_0229e948, sub_states, CATALOG_SCENE_SUB_STATES);
    MemberPointer_CallVoid(&data_ov116_0229e948[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov116_0229e8b819func_ov116_0229e5e8Ev, InsectCatalog_RunSubState)

/* Obj_ov116_0229e8b8::func_ov116_0229e6b4 (vtable slot 0x4c, phase 1): a frame of the scene's states
 * (CatalogSceneState) between the frame's start and end, through the table of member functions
 * (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 4; the game reads past the table for others. */
int InsectCatalog_RunState(CatalogScene *self)
{
    static const MemberPointer *const states[CATALOG_SCENE_STATES] = {
        &data_ov116_0229e840,
        &data_ov116_0229e8a8,
        &data_ov116_0229e868,
        &data_ov116_0229e898,
    };
    MemberTable_InitOnce(&data_ov116_0229e924, data_ov116_0229e928, states, CATALOG_SCENE_STATES);
    InsectCatalog_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov116_0229e928[self->base.state], self);
    InsectCatalog_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov116_0229e8b819func_ov116_0229e6b4Ev, InsectCatalog_RunState)

/* func_ov116_0229e748 (vtable slot 0x24): the scene's draw, once drawn: the scroll handle at
 * the wipe's y, the cursor sprite (while the buttons are in use), the list's arrows, entries
 * and member at 0x121c. Answers 1. */
int InsectCatalog_Draw(CatalogScene *self)
{
    if (InsectCatalog_TestFlags(self, CATALOG_SCENE_FLAG_DRAWN) == 0) {
        return 1;
    }
    CatalogList_PlaceHandle(&self->list, self->wipe_y);
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor);
    }
    CatalogList_DrawArrows(&self->list, self->wipe_y);
    CatalogList_DrawEntries(&self->list, self->wipe_y);
    CatalogList_DrawHandle(&self->list);
    return 1;
}
CLEAN_AS(func_ov116_0229e748, InsectCatalog_Draw)

/* func_ov116_0229e7a4 (vtable slot 0x0c): the scene closes: the menu told (MenuTabs_ChildClosed)
 * and the list ended. Answers 1. */
int InsectCatalog_End(CatalogScene *self)
{
    MenuTabs_ChildClosed(menu_of(self));
    InsectCatalog_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov116_0229e7a4, InsectCatalog_End)

/* func_ov116_0229e7c0 (vtable slot 0x00): the scene starts: the list started, state 0 and
 * phase 1. Answers 1. */
int InsectCatalog_Start(CatalogScene *self)
{
    InsectCatalog_Init(self);
    MenuScene_SetState(scene_of(self), CATALOG_SCENE_STATE_SETUP);
    MenuScene_SetPhase(scene_of(self), CATALOG_SCENE_PHASE_STATES);
    return 1;
}
CLEAN_AS(func_ov116_0229e7c0, InsectCatalog_Start)

/* func_ov116_0229e7e0: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base, the scene's vtable, the cursor sprite, the list and the label. */
CatalogScene *InsectCatalog_New(void)
{
    CatalogScene *self = MenuScene_Alloc(sizeof(CatalogScene));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov116_0229e8b8;
    Glider0_Construct(&self->cursor);
    CatalogList_Construct(&self->list);
    __cxa_vec_ctor(&self->label, 1, sizeof(TextLabel), func_02070c08, func_02070be8);
    return self;
}
CLEAN_AS(func_ov116_0229e7e0, InsectCatalog_New)
