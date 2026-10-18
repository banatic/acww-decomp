/* The friend roster of overlay 119 (friend_roster.h): its destructors and flags, the roster as
 * the scene reads it, the frame, the states, the phases, the draw and the constructor. */
#include "friend_roster.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/network.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/bbs.h"
#include "main/display_layers.h"
#include "main/group_params.h"
#include "main/oam_buffer.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/state_flags.h"
#include "ov004/member_pointer.h"
#include "ov090/menu_tabs.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(FriendRoster, wipe_y) == 0x94, "wipe_y");
static_assert(offsetof(FriendRoster, flags) == 0x98 && offsetof(FriendRoster, page) == 0x9c, "flags");
static_assert(offsetof(FriendRoster, cursor) == 0xa0 && offsetof(FriendRoster, action) == 0xad, "cursor");
static_assert(offsetof(FriendRoster, friend_index) == 0xb4 && offsetof(FriendRoster, fade) == 0xb8, "fade");
static_assert(offsetof(FriendRoster, slots) == 0xbc && offsetof(FriendRoster, choice) == 0xdc, "slots");
static_assert(offsetof(FriendRoster, entries) == 0x4c4 && offsetof(ChoiceEntries, values) == 5, "entries");
static_assert(offsetof(FriendRoster, labels) == 0x4d0 && sizeof(TextLabel) == 0x6c, "labels");
static_assert(offsetof(FriendRoster, header) == 0xcd4 && offsetof(FriendRoster, cursor_sprite) == 0xda8, "header");
static_assert(sizeof(Glider) == 0x64 && offsetof(FriendRoster, list_map) == 0xe0c, "maps");
static_assert(offsetof(FriendRoster, map) == 0x1e0c && offsetof(FriendRoster, obj_palette) == 0x1e10, "palettes");
static_assert(offsetof(FriendRoster, bg_faded) == 0x1e70 && offsetof(FriendRoster, tasks) == 0x1e90, "tasks");
static_assert(sizeof(LayerTask) == 0x24 && offsetof(FriendRoster, error) == 0x1efc, "error");
static_assert(sizeof(FriendRoster) == 0x2018, "size (func_ov119_0229cb34)");

/* The scene's vtable. */
extern const u8 data_ov119_0229cea0[];

/* A text label's constructor and destructor, handed to the vector helpers (so the game's). */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void func_02070c08(void *label);
extern void func_02070be8(void *label);

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The cells drawn (OamEntry lists ending with OAM_BUFFER_CELL_LAST): the frame, the six page
 * tabs, the button, the friend key page's and the picked row's mark; one OBJ whose tile is set
 * to each digit of the friend key in turn. */
extern const OamEntry data_ov119_0229ccc0[];
extern const OamEntry *const data_ov119_0229cca8[FRIEND_ROSTER_PAGE_TABS];
extern const OamEntry data_ov119_0229cdd8[];
extern const OamEntry data_ov119_0229ce38[];
extern const OamEntry data_ov119_0229ce08[];
extern OamEntry data_ov119_0229cbe8;

/* The choice's window: "menu/friend/c_bg.bsc". */
extern const char data_ov119_0229cfe0[];

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables (the symbol
 * table also names the sub states' table's later part, at 0x0229d0b0) and their constants. */
extern u32 data_ov119_0229d000; /* the sub states' guard */
extern u32 data_ov119_0229d004; /* the states' guard */
extern MemberPointer data_ov119_0229d008[FRIEND_ROSTER_STATES];
extern MemberPointer data_ov119_0229d030[FRIEND_ROSTER_SUB_STATES];
extern const MemberPointer data_ov119_0229cbe0, data_ov119_0229cbf0, data_ov119_0229cbf8, data_ov119_0229cc00,
    data_ov119_0229cc08, data_ov119_0229cc10, data_ov119_0229cc18, data_ov119_0229cc20, data_ov119_0229cc28,
    data_ov119_0229cc38, data_ov119_0229cc40, data_ov119_0229cc48, data_ov119_0229cc50, data_ov119_0229cc58,
    data_ov119_0229cc60, data_ov119_0229cc68, data_ov119_0229cc70, data_ov119_0229cc78, data_ov119_0229cc80,
    data_ov119_0229cc88, data_ov119_0229cc90, data_ov119_0229cc98, data_ov119_0229cca0;

/* The network modes in which NitroDWC's friend list is kept with the roster (network.c's
 * MODE_HOSTING and MODE_JOINING). */
#define FRIEND_ROSTER_NET_HOSTING 3
#define FRIEND_ROSTER_NET_JOINING 4

/* The layers: the frame (a_bg.bsc), the page's map behind it, the choice's (PagedChoice_Init). */
#define FRIEND_ROSTER_LAYER_FRAME 6
#define FRIEND_ROSTER_LAYER_PAGE 4
#define FRIEND_ROSTER_LAYER_CHOICE 3

static MenuScene *fr_scene(FriendRoster *self)
{
    return &self->base;
}

static PagedChoice *fr_choice(FriendRoster *self)
{
    return (PagedChoice *) (void *) self->choice;
}

static MenuTabs *fr_menu(FriendRoster *self)
{
    return (MenuTabs *) (void *) Process_GetParent((Process *) (void *) self);
}

/* The members' destructors, last member first, then the base's. */
static void fr_destroy_members(FriendRoster *self)
{
    self->base.vtable = data_ov119_0229cea0;
    ErrorMessage_Destruct(&self->error);
    Glider0_Destroy(&self->cursor_sprite);
    BbsLabel_Destruct(&self->header);
    __cxa_vec_cleanup(self->labels, FRIEND_ROSTER_LABELS, sizeof(TextLabel), func_02070be8);
    PagedChoice_Destroy(fr_choice(self));
    MenuScene_DestroyBase(fr_scene(self));
}

/* func_ov119_0229a340 (vtable slot 0x40): the scene destructed. */
FriendRoster *FriendRoster_Destroy(FriendRoster *self)
{
    fr_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov119_0229a340, FriendRoster_Destroy)

/* func_ov119_0229a39c (vtable slot 0x44): the scene destructed and freed. */
FriendRoster *FriendRoster_Delete(FriendRoster *self)
{
    fr_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov119_0229a39c, FriendRoster_Delete)

/* func_ov119_0229a400 */
void FriendRoster_ClearFlags(FriendRoster *self, unsigned short flags)
{
    self->flags = (u16) (self->flags & ~flags);
}
CLEAN_AS(func_ov119_0229a400, FriendRoster_ClearFlags)

/* func_ov119_0229a410 */
void FriendRoster_SetFlags(FriendRoster *self, unsigned short flags)
{
    self->flags = (u16) (self->flags | flags);
}
CLEAN_AS(func_ov119_0229a410, FriendRoster_SetFlags)

/* func_ov119_0229a420: whether any of `flags` is set. */
int FriendRoster_TestFlags(FriendRoster *self, unsigned int flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov119_0229a420, FriendRoster_TestFlags)

/* ---- The roster */

/* func_ov119_0229ac3c: whether a set friend of the roster has `friend_data`
 * (WifiFriendData_Matches). */
int FriendRoster_HasFriend(FriendRoster *self, const void *friend_data)
{
    WifiFriend *friends = FriendRoster_Friends(self);
    for (int i = 0; i < WIFI_FRIENDS; i++) {
        if (WifiFriendData_IsSet(WifiFriend_GetFriendData(&friends[i])) &&
            WifiFriendData_Matches(friend_data, WifiFriend_GetFriendData(&friends[i])) != 0) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov119_0229ac3c, FriendRoster_HasFriend)

/* func_ov119_0229ac80: the first friend of the roster not set, -1 when all 32 are. */
int FriendRoster_FreeIndex(FriendRoster *self)
{
    WifiFriend *friends = FriendRoster_Friends(self);
    for (int i = 0; i < WIFI_FRIENDS; i++) {
        if (!WifiFriendData_IsSet(WifiFriend_GetFriendData(&friends[i]))) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_ov119_0229ac80, FriendRoster_FreeIndex)

/* func_ov119_0229acb4: the roster's friend data made NitroDWC's (Wfc_GetFriendList): each
 * place where either has a friend (a type not 0, or a set friend) takes NitroDWC's data, unless
 * func_0210101c finds the two alike and both are buddies or both not. Whether any changed. */
int FriendRoster_SyncFromNetwork(FriendRoster *self)
{
    FriendList *list = Wfc_GetFriendList();
    WifiFriend *friends = FriendRoster_Friends(self);
    int changed = 0;
    for (int i = 0; i < WIFI_FRIENDS; i++) {
        WifiFriendData data;
        MI_CpuCopy8(list->friend_data[i], &data, sizeof(data));
        if (Wfc_GetFriendDataType(&data) == 0 && !WifiFriendData_IsSet(WifiFriend_GetFriendData(&friends[i]))) {
            continue;
        }
        WifiFriend *entry = &friends[i];
        if (Wfc_Call0210101c(&data, WifiFriendData_GetData(WifiFriend_GetFriendData(entry)))) {
            int buddy = Wfc_IsBuddyFriendData(&data);
            if (buddy == Wfc_IsBuddyFriendData(WifiFriendData_GetData(WifiFriend_GetFriendData(entry)))) {
                continue;
            }
        }
        MI_CpuCopy8(&data, WifiFriendData_GetData(WifiFriend_GetFriendData(entry)), sizeof(data));
        changed = 1;
    }
    return changed;
}
CLEAN_AS(func_ov119_0229acb4, FriendRoster_SyncFromNetwork)

/* func_ov119_0229ad5c: the gaps a removed friend leaves: online the friends keep their places
 * (NitroDWC's list is by index) and only the scene's slots are made again; offline the roster
 * itself is compacted (and the slots are left as they were). */
void FriendRoster_Compact(FriendRoster *self)
{
    if (FriendRoster_IsOnline(self)) {
        FriendRoster_BuildSlots(self);
    } else {
        WifiFriendList_Compact(PlayerRecord_WifiFriends(PlayerRecords_Current()));
    }
}
CLEAN_AS(func_ov119_0229ad5c, FriendRoster_Compact)

/* func_ov119_0229ad84: whether a set friend follows one not set. */
int FriendRoster_HasGap(FriendRoster *self)
{
    WifiFriend *friends = FriendRoster_Friends(self);
    int gap = 0;
    for (int i = 0; i < WIFI_FRIENDS; i++) {
        if (WifiFriendData_IsSet(WifiFriend_GetFriendData(&friends[i]))) {
            if (gap) {
                return 1;
            }
        } else {
            gap = 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov119_0229ad84, FriendRoster_HasGap)

/* func_ov119_0229adc4: the slots: the set friends' indices in order, then
 * FRIEND_ROSTER_NO_SLOT. */
void FriendRoster_BuildSlots(FriendRoster *self)
{
    WifiFriend *friends = FriendRoster_Friends(self);
    int count = 0;
    for (int i = 0; i < WIFI_FRIENDS; i++) {
        if (WifiFriendData_IsSet(WifiFriend_GetFriendData(&friends[i]))) {
            self->slots[count] = (u8) i;
            count++;
        }
    }
    for (; count < WIFI_FRIENDS; count++) {
        self->slots[count] = FRIEND_ROSTER_NO_SLOT;
    }
}
CLEAN_AS(func_ov119_0229adc4, FriendRoster_BuildSlots)

/* func_ov119_0229ae10: the slot of the cursor's row on the page shown: slots[page * 8 +
 * cursor]. QUIRK: read from the scene's bytes as the ROM does, also for the pages and places
 * that are not rows (the callers ask only on a friends' page). */
unsigned char FriendRoster_SlotAtCursor(FriendRoster *self)
{
    const u8 *bytes = (const u8 *) self;
    return bytes[offsetof(FriendRoster, slots) + self->cursor + (self->page << 3)];
}
CLEAN_AS(func_ov119_0229ae10, FriendRoster_SlotAtCursor)

/* func_ov119_0229ae28: the friend of the cursor's row, NULL for a slot past the set friends. */
WifiFriend *FriendRoster_FriendAtCursor(FriendRoster *self)
{
    WifiFriend *friends = FriendRoster_Friends(self);
    int slot = FriendRoster_SlotAtCursor(self);
    if (slot >= WIFI_FRIENDS) {
        return NULL;
    }
    return &friends[slot];
}
CLEAN_AS(func_ov119_0229ae28, FriendRoster_FriendAtCursor)

/* func_ov119_0229ae50: the current player's roster. */
WifiFriend *FriendRoster_Friends(FriendRoster *self)
{
    (void) self;
    return WifiFriendList_GetEntries(PlayerRecord_WifiFriends(PlayerRecords_Current()));
}
CLEAN_AS(func_ov119_0229ae50, FriendRoster_Friends)

/* func_ov119_0229ae68: whether the network is hosting or joining a game (Net_GetMode 3 or 4):
 * then NitroDWC's friend list is changed with the roster. */
int FriendRoster_IsOnline(FriendRoster *self)
{
    (void) self;
    u8 mode = Net_GetMode();
    return mode == FRIEND_ROSTER_NET_HOSTING || mode == FRIEND_ROSTER_NET_JOINING;
}
CLEAN_AS(func_ov119_0229ae68, FriendRoster_IsOnline)

/* ---- The frame */

/* func_ov119_0229c2a8: the frame's layer and the page's at priority 2, with BG control 0. */
void FriendRoster_SetUpLayers(void)
{
    DisplayLayer_SetPriority(FRIEND_ROSTER_LAYER_FRAME, 2);
    DisplayLayer_SetPriority(FRIEND_ROSTER_LAYER_PAGE, 2);
    DisplayLayer_SetBgControl(FRIEND_ROSTER_LAYER_FRAME, 0, 0, 0);
    DisplayLayer_SetBgControl(FRIEND_ROSTER_LAYER_PAGE, 0, 0, 0);
}
CLEAN_AS(func_ov119_0229c2a8, FriendRoster_SetUpLayers)

/* func_ov119_0229c2dc: the end of a frame in use. */
void FriendRoster_EndInteractiveFrame(FriendRoster *self)
{
    FriendRoster_EndFrame(self);
}
CLEAN_AS(func_ov119_0229c2dc, FriendRoster_EndInteractiveFrame)

/* func_ov119_0229c2e4: the start of a frame in use: the frame's start, then the cursor sprite's
 * update through its class (vtable slot 3). */
void FriendRoster_BeginInteractiveFrame(FriendRoster *self)
{
    FriendRoster_BeginFrame(self);
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) self->cursor_sprite.vtable;
    vtable[3](&self->cursor_sprite);
}
CLEAN_AS(func_ov119_0229c2e4, FriendRoster_BeginInteractiveFrame)

/* func_ov119_0229c300: the end of a frame: the graphics queued, the choice updated. */
void FriendRoster_EndFrame(FriendRoster *self)
{
    FriendRoster_UpdateGraphics(self);
    PagedChoice_Update(fr_choice(self));
}
CLEAN_AS(func_ov119_0229c300, FriendRoster_EndFrame)

/* func_ov119_0229c318: the start of a frame: the labels handed out again, the layer tasks
 * ended. */
void FriendRoster_BeginFrame(FriendRoster *self)
{
    FriendRoster_ReleaseLabels(self);
    for (int i = 0; i < FRIEND_ROSTER_TASKS; i++) {
        LayerTask_End(&self->tasks[i]);
    }
}
CLEAN_AS(func_ov119_0229c318, FriendRoster_BeginFrame)

/* func_ov119_0229c34c: the scene's members torn down: the choice dismissed, the labels
 * released, the layer tasks ended. */
void FriendRoster_Teardown(FriendRoster *self)
{
    PagedChoice_Dismiss(fr_choice(self));
    FriendRoster_ReleaseLabels(self);
    for (int i = 0; i < FRIEND_ROSTER_TASKS; i++) {
        LayerTask_End(&self->tasks[i]);
    }
}
CLEAN_AS(func_ov119_0229c34c, FriendRoster_Teardown)

/* func_ov119_0229c388: the scene's setup. Offline a roster with gaps is compacted, online it
 * takes NitroDWC's friend data; either change is told to the menu. Then no labels, no flags, the
 * cursor on the first page tab, the list's map, no row picked, no page yet, the button's palette
 * 7, the fade at its end, this user's friend key, the choice on layer 3 and the slots. */
void FriendRoster_Setup(FriendRoster *self)
{
    if (!FriendRoster_IsOnline(self)) {
        if (FriendRoster_HasGap(self)) {
            FriendRoster_Compact(self);
            MenuTabs_MarkRosterChanged(fr_menu(self));
        }
    } else if (FriendRoster_SyncFromNetwork(self)) {
        MenuTabs_MarkRosterChanged(fr_menu(self));
    }
    self->labels_used = 0;
    self->flags = 0;
    self->cursor = FRIEND_ROSTER_PLACE_TAB;
    self->map = self->list_map;
    self->highlight = -1;
    self->page = FRIEND_ROSTER_PAGE_NONE;
    self->rows_shown = 0;
    self->button_palette = 7;
    self->fade = FRIEND_ROSTER_FADE_STEPS;
    FriendRoster_LoadKeyDigits(self);
    PagedChoice_Init(fr_choice(self), FRIEND_ROSTER_LAYER_CHOICE, 1, data_ov119_0229cfe0);
    FriendRoster_BuildSlots(self);
}
CLEAN_AS(func_ov119_0229c388, FriendRoster_Setup)

/* ---- The states */

/* Obj_ov119_0229cea0::func_ov119_0229c434 (state 4): the wipe out steps; at its end both layers
 * are hidden, the scene no longer drawn and phase 5 ends it. */
void FriendRoster_WipeOut(FriendRoster *self)
{
    if (MenuScene_StepWipe(fr_scene(self), 0)) {
        DisplayLayer_HideAndResetScroll(FRIEND_ROSTER_LAYER_FRAME);
        DisplayLayer_HideAndResetScroll(FRIEND_ROSTER_LAYER_PAGE);
        FriendRoster_ClearFlags(self, FRIEND_ROSTER_FLAG_DRAWN);
        MenuScene_SetPhase(fr_scene(self), FRIEND_ROSTER_PHASE_END);
    } else {
        MenuScene_ScrollWipe(fr_scene(self), FRIEND_ROSTER_LAYER_FRAME, 0, 0);
        MenuScene_ScrollWipe(fr_scene(self), FRIEND_ROSTER_LAYER_PAGE, 0, 0);
        self->wipe_y = MenuScene_WipeOffsetY(fr_scene(self));
    }
}
CLEAN_AS(_ZN18Obj_ov119_0229cea019func_ov119_0229c434Ev, FriendRoster_WipeOut)

/* Obj_ov119_0229cea0::func_ov119_0229c488 (state 3): the cursor sprite hidden, the wipe out
 * started on window 2, state 4. */
void FriendRoster_StartWipeOut(FriendRoster *self)
{
    FriendRoster_HideCursorSprite(self);
    MenuScene_StartWipeOnWindow2(fr_scene(self), 10, 0, 0, 0x30);
    MenuScene_ScrollWipe(fr_scene(self), FRIEND_ROSTER_LAYER_FRAME, 0, 0);
    MenuScene_ScrollWipe(fr_scene(self), FRIEND_ROSTER_LAYER_PAGE, 0, 0);
    MenuScene_SetState(fr_scene(self), FRIEND_ROSTER_STATE_WIPING_OUT);
    self->wipe_y = MenuScene_WipeOffsetY(fr_scene(self));
}
CLEAN_AS(_ZN18Obj_ov119_0229cea019func_ov119_0229c488Ev, FriendRoster_StartWipeOut)

/* Obj_ov119_0229cea0::func_ov119_0229c4d4 (state 2): the header made once, then the wipe in
 * steps back; at its end the scene runs (phase 2) from the idle sub state. */
void FriendRoster_WipeIn(FriendRoster *self)
{
    if (FriendRoster_TestFlags(self, FRIEND_ROSTER_FLAG_HEADER)) {
        FriendRoster_ClearFlags(self, FRIEND_ROSTER_FLAG_HEADER);
        FriendRoster_ShowHeader(self);
    }
    if (MenuScene_StepWipeBack(fr_scene(self), 0)) {
        MenuScene_SetPhase(fr_scene(self), FRIEND_ROSTER_PHASE_INTERACTIVE);
        FriendRoster_ReturnToIdle(self);
    }
    MenuScene_ScrollWipe(fr_scene(self), FRIEND_ROSTER_LAYER_FRAME, 0, 0);
    MenuScene_ScrollWipe(fr_scene(self), FRIEND_ROSTER_LAYER_PAGE, 0, 0);
    self->wipe_y = MenuScene_WipeOffsetY(fr_scene(self));
}
CLEAN_AS(_ZN18Obj_ov119_0229cea019func_ov119_0229c4d4Ev, FriendRoster_WipeIn)

/* Obj_ov119_0229cea0::func_ov119_0229c534 (state 1): the covered wipe in started on window 2,
 * both layers shown, the scene drawn, the header asked for, state 2. */
void FriendRoster_StartWipeIn(FriendRoster *self)
{
    MenuScene_StartWipeCoveredOnWindow2(fr_scene(self), 10, 0, 0, 0x30);
    DisplayLayer_Show(FRIEND_ROSTER_LAYER_FRAME);
    MenuScene_ScrollWipe(fr_scene(self), FRIEND_ROSTER_LAYER_FRAME, 0, 0);
    DisplayLayer_Show(FRIEND_ROSTER_LAYER_PAGE);
    MenuScene_ScrollWipe(fr_scene(self), FRIEND_ROSTER_LAYER_PAGE, 0, 0);
    FriendRoster_SetFlags(self, FRIEND_ROSTER_FLAG_DRAWN);
    self->wipe_y = MenuScene_WipeOffsetY(fr_scene(self));
    FriendRoster_SetFlags(self, FRIEND_ROSTER_FLAG_HEADER);
    MenuScene_SetState(fr_scene(self), FRIEND_ROSTER_STATE_WIPING_IN);
}
CLEAN_AS(_ZN18Obj_ov119_0229cea019func_ov119_0229c534Ev, FriendRoster_StartWipeIn)

/* Obj_ov119_0229cea0::func_ov119_0229c598 (state 0): the layers set up, the graphics loaded,
 * the title made, the choice's graphics loaded. The page shown first is that of the friend
 * GroupParams' argument names when flag 0x200 of the state flags is set (taking it), else that
 * of the first friend. Then state 1, run at once. */
void FriendRoster_Load(FriendRoster *self)
{
    FriendRoster_SetUpLayers();
    FriendRoster_LoadBgGraphics(self);
    FriendRoster_LoadObjGraphics(self);
    FriendRoster_ShowTitle(self);
    PagedChoice_LoadFriendGraphics(fr_choice(self));
    int index = 0;
    if (StateFlags_Test200()) {
        StateFlags_Clear200();
        index = GroupParams_Arg();
    }
    FriendRoster_ShowPage(self, (u8) FriendRoster_PageOfFriend(self, index));
    MenuScene_SetState(fr_scene(self), FRIEND_ROSTER_STATE_WIPE_IN);
    FriendRoster_StartWipeIn(self);
}
CLEAN_AS(_ZN18Obj_ov119_0229cea019func_ov119_0229c598Ev, FriendRoster_Load)

/* ---- The phases */

/* func_ov119_0229c718 (vtable slot 0x5c, phase 5): the scene asks to be deleted. Answers 1. */
int FriendRoster_End(FriendRoster *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov119_0229c718, FriendRoster_End)

/* func_ov119_0229c728 (vtable slot 0x58, phase 4): nothing. */
int FriendRoster_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov119_0229c728, FriendRoster_Phase4Idle)

/* func_ov119_0229c72c (vtable slot 0x54, phase 3): nothing. */
int FriendRoster_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov119_0229c72c, FriendRoster_Phase3Idle)

/* Obj_ov119_0229cea0::func_ov119_0229c730 (vtable slot 0x50, phase 2): a frame of the scene in
 * use, unless the menu's keys (or a close) switch tabs first. Answers 1. */
int FriendRoster_RunInteractive(FriendRoster *self)
{
    if (FriendRoster_TakeMenuKeys(self)) {
        return 1;
    }
    FriendRoster_BeginInteractiveFrame(self);
    FriendRoster_RunSubState(self);
    FriendRoster_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov119_0229cea019func_ov119_0229c730Ev, FriendRoster_RunInteractive)

/* Obj_ov119_0229cea0::func_ov119_0229c75c: the sub state's function (FriendRosterSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 0x12; the game reads past the table for others. */
void FriendRoster_RunSubState(FriendRoster *self)
{
    static const MemberPointer *const sub_states[FRIEND_ROSTER_SUB_STATES] = {
        &data_ov119_0229cc68, &data_ov119_0229cc08, &data_ov119_0229cc48, &data_ov119_0229cc50, &data_ov119_0229cc00,
        &data_ov119_0229cc10, &data_ov119_0229cc70, &data_ov119_0229cbe0, &data_ov119_0229cc28, &data_ov119_0229cc20,
        &data_ov119_0229cc78, &data_ov119_0229cc60, &data_ov119_0229cbf8, &data_ov119_0229cc58, &data_ov119_0229cc38,
        &data_ov119_0229cbf0, &data_ov119_0229cc18, &data_ov119_0229cc40,
    };
    MemberTable_InitOnce(&data_ov119_0229d000, data_ov119_0229d030, sub_states, FRIEND_ROSTER_SUB_STATES);
    MemberPointer_CallVoid(&data_ov119_0229d030[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov119_0229cea019func_ov119_0229c75cEv, FriendRoster_RunSubState)

/* Obj_ov119_0229cea0::func_ov119_0229c8ac (vtable slot 0x4c, phase 1): a frame of the scene's
 * states (FriendRosterState) between the frame's start and end, through the table of member
 * functions (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 5; the game reads past the table for others. */
int FriendRoster_RunState(FriendRoster *self)
{
    static const MemberPointer *const states[FRIEND_ROSTER_STATES] = {
        &data_ov119_0229cca0, &data_ov119_0229cc98, &data_ov119_0229cc90, &data_ov119_0229cc88, &data_ov119_0229cc80,
    };
    MemberTable_InitOnce(&data_ov119_0229d004, data_ov119_0229d008, states, FRIEND_ROSTER_STATES);
    FriendRoster_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov119_0229d008[self->base.state], self);
    FriendRoster_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov119_0229cea019func_ov119_0229c8acEv, FriendRoster_RunState)

/* The cells are drawn on the sub screen at x 0x80, 0x60 below the wipe's offset, at priority 2
 * and unscaled. */
#define FRIEND_ROSTER_CELL_X 0x80
#define FRIEND_ROSTER_CELL_Y 0x60
#define FRIEND_ROSTER_DIGIT_STEP 0x0e
#define FRIEND_ROSTER_DIGIT_TILES 0x1a0 /* digit d is tile 0x1a0 + 2 * d (10: blank) */

static void fr_draw_cell(const OamEntry *cells, int y, int palette)
{
    OamBuffer_DrawCell(OAM_BUFFER_SCREEN_SUB, cells, FRIEND_ROSTER_CELL_X, y, palette, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}

/* func_ov119_0229c94c (vtable slot 0x24): the scene's draw, while it is drawn: the choice, the
 * cursor sprite (with the keys in use), the frame, the six page tabs (the selected one in
 * palette 5, the others 4), the button. Page 4 adds the twelve digits of the friend key and its
 * cells, a friends' page the picked row's mark. Answers 1.
 * QUIRK: each digit is drawn by setting the tile of the overlay's own OBJ (0x0229cbe8) before
 * drawing it, so the last digit's tile stays there. */
int FriendRoster_Draw(FriendRoster *self)
{
    int y = self->wipe_y + FRIEND_ROSTER_CELL_Y;
    if (!FriendRoster_TestFlags(self, FRIEND_ROSTER_FLAG_DRAWN)) {
        return 1;
    }
    PagedChoice_Draw(fr_choice(self));
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    fr_draw_cell(data_ov119_0229ccc0, y, -1);
    for (int i = 0; i < FRIEND_ROSTER_PAGE_TABS; i++) {
        fr_draw_cell(data_ov119_0229cca8[i], y, i == self->tab ? 5 : 4);
    }
    fr_draw_cell(data_ov119_0229cdd8, y, self->button_palette);
    switch (self->page) {
        case FRIEND_ROSTER_PAGE_OWN_KEY: {
            int x = FRIEND_ROSTER_CELL_X;
            for (int i = 0; i < WIFI_FRIEND_KEY_DIGITS; i++) {
                u16 tile = (u16) ((self->key_digits[i] << 1) + FRIEND_ROSTER_DIGIT_TILES);
                data_ov119_0229cbe8.attr2 = (u16) ((data_ov119_0229cbe8.attr2 & 0xfc00) | (tile & 0x3ff));
                OamBuffer_DrawObjAffine(OAM_BUFFER_SCREEN_SUB, &data_ov119_0229cbe8, x, y, -1, 2, NULL);
                x += FRIEND_ROSTER_DIGIT_STEP;
            }
            fr_draw_cell(data_ov119_0229ce38, y, -1);
            break;
        }
        case FRIEND_ROSTER_PAGE_PLAYERS:
            break;
        default:
            if (self->highlight != -1) {
                fr_draw_cell(data_ov119_0229ce08, y + self->highlight * 16 - 0x10, -1);
            }
            break;
    }
    return 1;
}
CLEAN_AS(func_ov119_0229c94c, FriendRoster_Draw)

/* func_ov119_0229caf8 (vtable slot 0x0c): the scene closes: the menu told (MenuTabs_ChildClosed,
 * its answer unused) and the members torn down. Answers 1. */
int FriendRoster_Close(FriendRoster *self)
{
    MenuTabs_ChildClosed(fr_menu(self));
    FriendRoster_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov119_0229caf8, FriendRoster_Close)

/* func_ov119_0229cb14 (vtable slot 0x00): the scene starts: its setup, state 0 and phase 1.
 * Answers 1. */
int FriendRoster_Start(FriendRoster *self)
{
    FriendRoster_Setup(self);
    MenuScene_SetState(fr_scene(self), FRIEND_ROSTER_STATE_LOAD);
    MenuScene_SetPhase(fr_scene(self), FRIEND_ROSTER_PHASE_STATES);
    return 1;
}
CLEAN_AS(func_ov119_0229cb14, FriendRoster_Start)

/* func_ov119_0229cb34 (named by the profile at 0x0229cc30): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order, the nineteen labels by __cxa_vec_ctor. */
FriendRoster *FriendRoster_New(void)
{
    FriendRoster *self = MenuScene_Alloc(sizeof(FriendRoster));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov119_0229cea0;
    PagedChoice_Construct(fr_choice(self));
    __cxa_vec_ctor(self->labels, FRIEND_ROSTER_LABELS, sizeof(TextLabel), func_02070c08, func_02070be8);
    BbsLabel_Construct(&self->header);
    Glider0_Construct(&self->cursor_sprite);
    for (int i = 0; i < FRIEND_ROSTER_TASKS; i++) {
        LayerTask_Construct(&self->tasks[i]);
    }
    ErrorMessage_Construct(&self->error);
    return self;
}
CLEAN_AS(func_ov119_0229cb34, FriendRoster_New)
