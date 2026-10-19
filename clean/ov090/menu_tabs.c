/* The menu of overlay 90 (menu_tabs.h): the bar of tabs, the switches between the tabs' scenes
 * and the friend roster's write when the menu closes. */
#include "menu_tabs.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/c_library.h"
#include "main/card_save.h"
#include "main/control_mode.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/group_params.h"
#include "main/menu_backdrop.h"
#include "main/music_volume.h"
#include "main/oam_buffer.h"
#include "main/overlay_groups.h"
#include "main/rom_file.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov004/member_pointer.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(MenuTabs, shown) == 0x94, "shown");
static_assert(offsetof(MenuTabs, roster) == 0x97 && offsetof(MenuTabs, opening) == 0x98, "bytes");
static_assert(sizeof(LayerTaskPair) == 0x38 && offsetof(MenuTabs, tasks) == 0x9c, "tasks");
static_assert(offsetof(MenuTabs, bar_chars) == 0x144 && offsetof(MenuTabs, tab_chars) == 0x944, "chars");
static_assert(offsetof(MenuTabs, palette) == 0x1144 && offsetof(MenuTabs, error) == 0x1164, "error");
static_assert(sizeof(MenuTabs) == 0x1280, "size (func_ov090_02299774)");

/* The menu's vtable. */
extern const u8 data_ov090_02299820[];

/* Frames left before sub state 1 asks for the tab's group: ten after each R or L. */
extern u8 data_ov090_02299960;
#define MENU_TABS_SWITCH_DELAY 10

/* The files of the bar: each tab's palette (by number), the bar's palette, its characters and
 * the tabs' characters. */
extern const char data_ov090_02299900[]; /* "menu/tag/obj%d.bpl" */
extern const char data_ov090_02299914[]; /* "menu/tag/obj.bpl" */
extern const char data_ov090_02299928[]; /* "menu/tag/obj1.bch" */
extern const char data_ov090_0229993c[]; /* "menu/tag/obj2.bch" */
#define MENU_TABS_PATH_SIZE 0x24

/* The bar's sixteen OBJs, drawn on the sub screen. */
#define MENU_TABS_OBJS 16
extern const OamEntry data_ov090_02299880[MENU_TABS_OBJS];

/* The layer the bar's characters and palette go to (main/display_layers.h): the sub screen's
 * OBJ. */
#define MENU_TABS_LAYER 8
#define MENU_TABS_PALETTE 0xf
#define MENU_TABS_FIRST_CHAR 0x80 /* the bar's characters: 0x80-0xbf */
#define MENU_TABS_LAST_CHAR 0xbf
#define MENU_TABS_LOWER_ROW_CHARS 0x20  /* a tab's lower row, in characters */
#define MENU_TABS_LOWER_ROW_BYTES 0x400 /* and in the tabs' file */
#define MENU_TABS_TAB_BYTES 0x60        /* three 16-colour characters */

/* The heap the bar's palette file is read with. */
extern Heap *data_021fbe94;

/* The pen: down, and gone down this frame; its place (autoload_2/input.c). */
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58; /* x */
extern u8 data_021f6c54; /* y */

/* The pad (autoload_2/input.h) and the buttons read in `pressed`. */
extern PadState data_021fbe40;
#define MENU_TABS_PAD_R 0x0100
#define MENU_TABS_PAD_L 0x0200

/* The field's sound object; its music volume is at 0x1c4 (main/music_volume.h). */
extern u8 *data_021c526c;

/* Set when the player is in a room. */
extern u8 data_020e54a8;

/* The tables of member functions (ov004/member_pointer.h): their guards, the tables and the
 * constants they are filled from. */
extern u32 data_ov090_02299964; /* the states' guard */
extern u32 data_ov090_02299968; /* the sub states' guard */
extern MemberPointer data_ov090_0229996c[MENU_TABS_STATES];
extern MemberPointer data_ov090_02299984[MENU_TABS_SUB_STATES];
extern const MemberPointer data_ov090_022997e8; /* MenuTabs_Setup */
extern const MemberPointer data_ov090_022997f0; /* MenuTabs_Idle */
extern const MemberPointer data_ov090_022997f8; /* MenuTabs_UpdateError */
extern const MemberPointer data_ov090_02299800; /* MenuTabs_RequestTabGroup */
extern const MemberPointer data_ov090_02299808; /* MenuTabs_Hide */
extern const MemberPointer data_ov090_02299810; /* MenuTabs_Show */

/* The error message shown when the roster's write fails. */
#define MENU_TABS_ROSTER_ERROR 31

/* GroupParams modes and overlay groups the tabs ask for. */
#define MENU_TABS_POCKETS_ROOM_GROUP 1
#define MENU_TABS_POCKETS_TOWN_GROUP 2
#define MENU_TABS_GROUP_9_12 0xf
#define MENU_TABS_MODE_9_12 0xf /* added to the tab */
#define MENU_TABS_GROUP_13_14 0x2b

static MenuScene *menu_tabs_scene(MenuTabs *self)
{
    return &self->base;
}

static MusicVolume *menu_tabs_music_volume(void)
{
    return (MusicVolume *) (void *) (data_021c526c + 0x1c4);
}

static u8 *menu_tabs_byte(MenuTabs *self, int which)
{
    return &self->base.unk_91[which];
}

/* The base's destructor, after the error message's. The layer tasks have none. */
static void menu_tabs_destroy_members(MenuTabs *self)
{
    self->base.vtable = data_ov090_02299820;
    ErrorMessage_Destruct(&self->error);
    MenuScene_DestroyBase(menu_tabs_scene(self));
}

/* func_ov090_02298f20 (vtable slot 0x40) */
MenuTabs *MenuTabs_Destroy(MenuTabs *self)
{
    menu_tabs_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov090_02298f20, MenuTabs_Destroy)

/* func_ov090_02298f48 (vtable slot 0x44) */
MenuTabs *MenuTabs_Delete(MenuTabs *self)
{
    menu_tabs_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov090_02298f48, MenuTabs_Delete)

/* func_ov090_02298f74: whether no tab was selected since the menu started (the pockets set up
 * step by step then). */
int MenuTabs_IsOpening(MenuTabs *self)
{
    return self->opening != 0;
}
CLEAN_AS(func_ov090_02298f74, MenuTabs_IsOpening)

/* func_ov090_02298f84: the place of the bar under `x`: 25 pixels each from x 51, 0 to the
 * left of the first and 7 (the close place) from the eighth on. */
int MenuTabs_TabAtX(int x)
{
    int place = (int) ((u32) x - 51) / 25;
    if (place < 0) {
        place = 0;
    }
    if (place > MENU_TABS_PLACES - 1) {
        place = MENU_TABS_PLACES - 1;
    }
    return place;
}
CLEAN_AS(func_ov090_02298f84, MenuTabs_TabAtX)

/* func_ov090_02298fa4: a child changed the friend roster: it is written when the menu
 * closes. */
void MenuTabs_MarkRosterChanged(MenuTabs *self)
{
    self->roster = MENU_TABS_ROSTER_CHANGED;
}
CLEAN_AS(func_ov090_02298fa4, MenuTabs_MarkRosterChanged)

/* func_ov090_02298fac: `tab` becomes the current tab; for one of the bar's eight places not
 * shown yet, the bar's characters are put back, the tab's three characters (and the three
 * below them) put in its place and its palette loaded, all by the layer tasks.
 * QUIRK: the current tab is set to any value, even one the bar has no look for. */
void MenuTabs_ShowTab(MenuTabs *self, int tab)
{
    char path[MENU_TABS_PATH_SIZE];

    *menu_tabs_byte(self, MENU_TABS_BYTE_TAB) = (u8) tab;
    if ((unsigned int) tab >= MENU_TABS_PLACES) {
        return;
    }
    if (tab == self->loaded_tab) {
        return;
    }
    LayerTask_QueueChars(&self->tasks[0].first, (int) (uintptr_t) self->bar_chars, MENU_TABS_LAYER, MENU_TABS_FIRST_CHAR,
                         MENU_TABS_FIRST_CHAR, MENU_TABS_LAST_CHAR);
    u8 *chars = &self->tab_chars[tab * MENU_TABS_TAB_BYTES];
    int first = MENU_TABS_FIRST_CHAR + tab * 3;
    LayerTask_QueueTwoChars(&self->tasks[1], (int) (uintptr_t) chars, (int) (uintptr_t) (chars + MENU_TABS_LOWER_ROW_BYTES),
                            MENU_TABS_LAYER, first, first + 2, first + MENU_TABS_LOWER_ROW_CHARS,
                            first + MENU_TABS_LOWER_ROW_CHARS + 2);
    CLib_SPrintf(path, data_ov090_02299900, tab);
    RomFile_Read(path, self->palette, sizeof(self->palette));
    LayerTask_QueuePalette(&self->tasks[2].first, (int) (uintptr_t) self->palette, MENU_TABS_LAYER, MENU_TABS_PALETTE);
    self->loaded_tab = (u8) tab;
}
CLEAN_AS(func_ov090_02298fac, MenuTabs_ShowTab)

/* func_ov090_02299058: the three layer tasks ended. */
void MenuTabs_EndTasks(MenuTabs *self)
{
    for (int i = 0; i < MENU_TABS_TASKS; i++) {
        LayerTask_End(&self->tasks[i].first);
    }
}
CLEAN_AS(func_ov090_02299058, MenuTabs_EndTasks)

/* func_ov090_02299078: the bar's tab after `tab` (6 wraps to 0); a tab past the bar stays.
 * The switch delay starts again either way. */
u8 MenuTabs_NextTab(u8 tab)
{
    data_ov090_02299960 = MENU_TABS_SWITCH_DELAY;
    if (tab > MENU_TABS_LAST_BAR_TAB) {
        return tab;
    }
    if (tab == MENU_TABS_LAST_BAR_TAB) {
        return MENU_TAB_POCKETS;
    }
    return (u8) (tab + 1);
}
CLEAN_AS(func_ov090_02299078, MenuTabs_NextTab)

/* func_ov090_02299098: the bar's tab before `tab` (0 wraps to 6); a tab past the bar stays.
 * QUIRK: unlike MenuTabs_NextTab, the switch delay starts again only for the bar's tabs. */
u8 MenuTabs_PreviousTab(u8 tab)
{
    if (tab > MENU_TABS_LAST_BAR_TAB) {
        return tab;
    }
    data_ov090_02299960 = MENU_TABS_SWITCH_DELAY;
    if (tab == MENU_TAB_POCKETS) {
        return MENU_TABS_LAST_BAR_TAB;
    }
    return (u8) (tab - 1);
}
CLEAN_AS(func_ov090_02299098, MenuTabs_PreviousTab)

/* func_ov090_022990b8: the x of a place of the bar: 25 pixels each from 0x3f, the close place
 * at 0xf3. */
int MenuTabs_TabX(int tab)
{
    if (tab == MENU_TAB_CLOSE) {
        return 0xf3;
    }
    return (int) ((u32) tab * 25 + 0x3f);
}
CLEAN_AS(func_ov090_022990b8, MenuTabs_TabX)

/* func_ov090_022990c8: the bar slides out. */
void MenuTabs_SlideOut(MenuTabs *self)
{
    self->shown = 0;
}
CLEAN_AS(func_ov090_022990c8, MenuTabs_SlideOut)

/* func_ov090_022990d0: the bar is drawn and slides in. */
void MenuTabs_SlideIn(MenuTabs *self)
{
    self->shown = 1;
    *menu_tabs_byte(self, MENU_TABS_BYTE_DRAWN) = 1;
}
CLEAN_AS(func_ov090_022990d0, MenuTabs_SlideIn)

/* func_ov090_022990e0: the place of the bar the pen went down on this frame (as
 * MenuTabs_TabAtX, from x 53), or -1: none, the pen above y 17 or left of x 53.
 * QUIRK: it also tests x against 256, which a byte never reaches. */
int MenuTabs_TabAtTouch(void)
{
    if (!(data_021fbdd8 != 0 && data_021fbddc != 0)) {
        return -1;
    }
    int x = data_021f6c58;
    int y = data_021f6c54;
    if (y > 16 || x < 53 || x >= 256) {
        return -1;
    }
    int place = (x - 53) / 25;
    return place < MENU_TABS_PLACES - 1 ? place : MENU_TABS_PLACES - 1;
}
CLEAN_AS(func_ov090_022990e0, MenuTabs_TabAtTouch)

/* func_ov090_02299154 */
void MenuTabs_EndTasksOnClose(MenuTabs *self)
{
    MenuTabs_EndTasks(self);
}
CLEAN_AS(func_ov090_02299154, MenuTabs_EndTasksOnClose)

/* func_ov090_0229915c: the bar not drawn, at its place and not sliding, no switch under way;
 * sound 1 and the music volume's slot 1 at 0. */
void MenuTabs_ResetBar(MenuTabs *self)
{
    *menu_tabs_byte(self, MENU_TABS_BYTE_DRAWN) = 0;
    *menu_tabs_byte(self, MENU_TABS_BYTE_SLIDE) = 0;
    self->shown = 0;
    self->switching = 0;
    SoundSys_PlaySe(1);
    MusicVolume_SetSlot1(menu_tabs_music_volume(), 0);
}
CLEAN_AS(func_ov090_0229915c, MenuTabs_ResetBar)

/* func_ov090_0229919c (state 2): the bar slides out by 4 pixels a frame; at 4 or less it is no
 * longer drawn and the menu waits (phase 0).
 * QUIRK: the slide is left where it was, not cleared. */
void MenuTabs_Hide(MenuTabs *self)
{
    u8 *slide = menu_tabs_byte(self, MENU_TABS_BYTE_SLIDE);
    if (*slide <= 4) {
        *menu_tabs_byte(self, MENU_TABS_BYTE_DRAWN) = 0;
        MenuScene_SetPhase(menu_tabs_scene(self), MENU_SCENE_PHASE_WAIT);
    } else {
        *slide = (u8) (*slide - 4);
    }
}
CLEAN_AS(func_ov090_0229919c, MenuTabs_Hide)

/* func_ov090_022991cc (state 1): the bar slides in while the menu runs (phase 2). */
void MenuTabs_Show(MenuTabs *self)
{
    self->shown = 1;
    MenuScene_SetPhase(menu_tabs_scene(self), MENU_SCENE_PHASE_INTERACTIVE);
}
CLEAN_AS(func_ov090_022991cc, MenuTabs_Show)

/* func_ov090_022991e0 (state 0): the bar's palette and both character files loaded, the tab
 * of GroupParams' mode shown, the bar drawn at its place; on to state 1, the sub screen's BG
 * mode 0. */
void MenuTabs_Setup(MenuTabs *self)
{
    DisplayLayer_LoadPalettesFromFile(data_ov090_02299914, data_021fbe94, MENU_TABS_LAYER, MENU_TABS_PALETTE,
                                      MENU_TABS_PALETTE, MENU_TABS_PALETTE);
    RomFile_Read(data_ov090_02299928, self->bar_chars, sizeof(self->bar_chars));
    RomFile_Read(data_ov090_0229993c, self->tab_chars, sizeof(self->tab_chars));
    MenuTabs_ShowTab(self, GroupParams_Mode());
    *menu_tabs_byte(self, MENU_TABS_BYTE_DRAWN) = 1;
    *menu_tabs_byte(self, MENU_TABS_BYTE_SLIDE) = 0;
    self->base.state = MENU_TABS_STATE_SHOW;
    DisplayShadow_SetSubBgMode(0);
}
CLEAN_AS(func_ov090_022991e0, MenuTabs_Setup)

/* func_ov090_02299258 (sub state 2): the roster's error message (it never closes). */
int MenuTabs_UpdateError(MenuTabs *self)
{
    return ErrorMessage_Update(&self->error, 0);
}
CLEAN_AS(func_ov090_02299258, MenuTabs_UpdateError)

/* func_ov090_0229926c (sub state 1): once the switch delay is over, the current tab's overlay
 * group asked for (tabs 9-14 also set GroupParams' mode); the switch is over and the menu goes
 * back to sub state 0. Nothing is asked for the close tab. */
void MenuTabs_RequestTabGroup(MenuTabs *self)
{
    static const u8 bar_groups[MENU_TAB_6 + 1] = {
        [MENU_TAB_1] = 3, [MENU_TAB_2] = 4, [MENU_TAB_3] = 5, [MENU_TAB_4] = 6, [MENU_TAB_5] = 7, [MENU_TAB_6] = 0x24,
    };

    if (data_ov090_02299960 != 0) {
        return;
    }
    self->switching = 0;
    u8 tab = *menu_tabs_byte(self, MENU_TABS_BYTE_TAB);
    if (tab == MENU_TAB_POCKETS) {
        OverlayGroups_RequestForOwner(data_020e54a8 == 0 ? MENU_TABS_POCKETS_TOWN_GROUP : MENU_TABS_POCKETS_ROOM_GROUP);
    } else if (tab <= MENU_TAB_6) {
        OverlayGroups_RequestForOwner(bar_groups[tab]);
    } else if (tab == MENU_TAB_LETTER_WRITE) {
        OverlayGroups_RequestForOwner(8);
    } else if (tab >= MENU_TAB_9 && tab <= MENU_TAB_12) {
        OverlayGroups_RequestForOwner(MENU_TABS_GROUP_9_12);
        GroupParams_SetMode((char) (tab + MENU_TABS_MODE_9_12));
    } else if (tab == MENU_TAB_13 || tab == MENU_TAB_14) {
        OverlayGroups_RequestForOwner(MENU_TABS_GROUP_13_14);
        GroupParams_SetMode((char) tab);
    }
    self->base.sub_state = MENU_TABS_SUB_IDLE;
}
CLEAN_AS(func_ov090_0229926c, MenuTabs_RequestTabGroup)

/* func_ov090_02299348 (sub state 0): nothing. */
void MenuTabs_Idle(MenuTabs *self)
{
    (void) self;
}
CLEAN_AS(func_ov090_02299348, MenuTabs_Idle)

/* func_ov090_0229934c: the menu closes: the bar slides out (state 2, phase 1), the sub screen's
 * BG mode 1. */
void MenuTabs_Close(MenuTabs *self)
{
    self->base.state = MENU_TABS_STATE_HIDE;
    MenuScene_SetPhase(menu_tabs_scene(self), MENU_SCENE_PHASE_STATES);
    DisplayShadow_SetSubBgMode(1);
}
CLEAN_AS(func_ov090_0229934c, MenuTabs_Close)

/* func_ov090_0229936c: the child scene has closed: for the close tab with the roster saved,
 * the backdrop let go and the menu closes; for any other tab of 0-14 the next frame asks for
 * its group (sub state 1). Returns the current tab. */
u8 MenuTabs_ChildClosed(MenuTabs *self)
{
    u8 tab = *menu_tabs_byte(self, MENU_TABS_BYTE_TAB);
    if (tab == MENU_TAB_CLOSE) {
        if (self->roster == MENU_TABS_ROSTER_SAVED) {
            MenuBackdrop_ReleaseClose();
            MenuTabs_Close(self);
        }
    } else if (tab <= MENU_TAB_14) {
        self->base.sub_state = MENU_TABS_SUB_REQUEST;
    }
    return *menu_tabs_byte(self, MENU_TABS_BYTE_TAB);
}
CLEAN_AS(func_ov090_0229936c, MenuTabs_ChildClosed)

/* func_ov090_022993cc: a child switches to `tab`: no longer opening, the tab shown. The close
 * tab slides the bar out, has a changed roster written (else the backdrop closes), sound 2
 * and the music volume's slot 1 ended; a switch between the bar's tabs plays sound 3 and lets
 * R and L go on moving it. The pockets clear GroupParams' value C50. */
void MenuTabs_SelectTab(MenuTabs *self, u32 tab)
{
    self->opening = 0;
    u8 before = *menu_tabs_byte(self, MENU_TABS_BYTE_TAB);
    MenuTabs_ShowTab(self, (int) tab);
    if (tab == MENU_TAB_CLOSE) {
        self->shown = 0;
        if (self->roster == MENU_TABS_ROSTER_CHANGED) {
            self->roster = MENU_TABS_ROSTER_WRITE;
        }
        if (self->roster == MENU_TABS_ROSTER_SAVED) {
            MenuBackdrop_Close();
        }
        SoundSys_PlaySe(2);
        MusicVolume_EndSlot1(menu_tabs_music_volume());
    } else if (tab <= MENU_TABS_LAST_BAR_TAB && before <= MENU_TABS_LAST_BAR_TAB) {
        SoundSys_PlaySe(3);
    }
    if (tab == MENU_TAB_POCKETS) {
        GroupParams_ClearC50();
    }
    if (before <= MENU_TABS_LAST_BAR_TAB && tab <= MENU_TABS_LAST_BAR_TAB) {
        self->switching = 1;
    }
}
CLEAN_AS(func_ov090_022993cc, MenuTabs_SelectTab)

/* func_ov090_02299458 (vtable slot 0x5c, phase 5): the menu asks to be deleted. */
int MenuTabs_RequestDelete(MenuTabs *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov090_02299458, MenuTabs_RequestDelete)

/* func_ov090_02299468 (vtable slot 0x58, phase 4): nothing. */
int MenuTabs_Phase4(void)
{
    return 1;
}
CLEAN_AS(func_ov090_02299468, MenuTabs_Phase4)

/* func_ov090_0229946c (vtable slot 0x54, phase 3): nothing. */
int MenuTabs_Phase3(void)
{
    return 1;
}
CLEAN_AS(func_ov090_0229946c, MenuTabs_Phase3)

/* Obj_ov090_02299820::func_ov090_02299470 (vtable slot 0x50, phase 2): a frame of the menu
 * while a child runs. The layer tasks ended; a roster to write is written (a failure opens
 * error message 31, fatal, in sub state 2; a success closes the backdrop); the switch delay
 * counted down; the sub state (MenuTabsSubState) run through its table of member functions
 * (filled once from its constants); the bar slid; while a switch is under way, R and L move to
 * the next and previous tab with sound 3. Answers 1.
 * REQUIRES: the sub state is below 3; the game reads past the table for others. */
int MenuTabs_RunInteractive(MenuTabs *self)
{
    static const MemberPointer *const sub_states[MENU_TABS_SUB_STATES] = {
        &data_ov090_022997f0,
        &data_ov090_02299800,
        &data_ov090_022997f8,
    };
    MemberTable_InitOnce(&data_ov090_02299968, data_ov090_02299984, sub_states, MENU_TABS_SUB_STATES);
    MenuTabs_EndTasks(self);

    if (self->roster == MENU_TABS_ROSTER_WRITE) {
        if (CardSave_WriteFriendRoster() != 0) {
            self->base.sub_state = MENU_TABS_SUB_ERROR;
            u8 message = MENU_TABS_ROSTER_ERROR;
            ErrorMessage_Open(&self->error, &message, 1, 1);
            self->roster = MENU_TABS_ROSTER_FAILED;
        } else {
            self->roster = MENU_TABS_ROSTER_SAVED;
            MenuBackdrop_Close();
        }
    }

    if (data_ov090_02299960 != 0) {
        data_ov090_02299960--;
    }

    MemberPointer_CallVoid(&data_ov090_02299984[self->base.sub_state], self);

    u8 *slide = menu_tabs_byte(self, MENU_TABS_BYTE_SLIDE);
    if (self->shown != 0) {
        if (*slide != MENU_TABS_SLIDE_IN) {
            *slide = *slide >= MENU_TABS_SLIDE_IN - 2 ? MENU_TABS_SLIDE_IN : (u8) (*slide + 2);
        }
    } else if (*slide != 0) {
        if (*slide <= 4) {
            *menu_tabs_byte(self, MENU_TABS_BYTE_DRAWN) = 0;
            *slide = 0;
        } else {
            *slide = (u8) (*slide - 4);
        }
    }

    if (self->switching != 0) {
        if (data_021fbe40.pressed & MENU_TABS_PAD_R) {
            MenuTabs_ShowTab(self, MenuTabs_NextTab(*menu_tabs_byte(self, MENU_TABS_BYTE_TAB)));
            SoundSys_PlaySe(3);
        }
        if (data_021fbe40.pressed & MENU_TABS_PAD_L) {
            MenuTabs_ShowTab(self, MenuTabs_PreviousTab(*menu_tabs_byte(self, MENU_TABS_BYTE_TAB)));
            SoundSys_PlaySe(3);
        }
    }
    return 1;
}
CLEAN_AS(_ZN18Obj_ov090_0229982019func_ov090_02299470Ev, MenuTabs_RunInteractive)

/* func_ov090_02299608 (vtable slot 0x4c, phase 1): the layer tasks ended, then the state
 * (MenuTabsState) run through its table of member functions (filled once from its constants,
 * before the tasks end). Answers 1.
 * REQUIRES: the state is below 3; the game reads past the table for others. */
int MenuTabs_RunState(MenuTabs *self)
{
    static const MemberPointer *const states[MENU_TABS_STATES] = {
        &data_ov090_022997e8,
        &data_ov090_02299810,
        &data_ov090_02299808,
    };
    MemberTable_InitOnce(&data_ov090_02299964, data_ov090_0229996c, states, MENU_TABS_STATES);
    MenuTabs_EndTasks(self);
    MemberPointer_CallVoid(&data_ov090_0229996c[self->base.state], self);
    return 1;
}
CLEAN_AS(func_ov090_02299608, MenuTabs_RunState)

/* func_ov090_02299688 (vtable slot 0x24): while the bar is drawn, its sixteen OBJs drawn on
 * the sub screen at (0x80, 0x50) lowered by the slide, priority 2, in their own palettes.
 * Answers whether it was drawn. */
int MenuTabs_Draw(MenuTabs *self)
{
    if (*menu_tabs_byte(self, MENU_TABS_BYTE_DRAWN) == 0) {
        return 0;
    }
    for (int i = 0; i < MENU_TABS_OBJS; i++) {
        OamBuffer_DrawObjAffine(1, &data_ov090_02299880[i], 0x80, *menu_tabs_byte(self, MENU_TABS_BYTE_SLIDE) + 0x50, -1, 2,
                                NULL);
    }
    return 1;
}
CLEAN_AS(func_ov090_02299688, MenuTabs_Draw)

/* func_ov090_022996fc (vtable slot 0x0c): the menu ends: the backdrop ended, the layer tasks
 * ended, the music restored, state flag 0x100 cleared. Answers 1. */
int MenuTabs_End(MenuTabs *self)
{
    MenuBackdrop_End();
    MenuTabs_EndTasksOnClose(self);
    SoundSys_RestoreMusic();
    StateFlags_Clear100();
    return 1;
}
CLEAN_AS(func_ov090_022996fc, MenuTabs_End)

/* func_ov090_0229971c (vtable slot 0x00): the menu starts: opening, state flag 0x100 set, the
 * bar reset, the backdrop opened, no tab's look loaded, no delay, the roster saved, sub state 1
 * (the first tab's group asked for), state 0 after the wait (phase 0); GroupParams' value C50
 * cleared, the music lowered and the control mode applied again. Answers 1. */
int MenuTabs_Start(MenuTabs *self)
{
    self->opening = 1;
    StateFlags_Set100();
    MenuTabs_ResetBar(self);
    MenuBackdrop_Open();
    self->loaded_tab = MENU_TAB_NONE;
    data_ov090_02299960 = 0;
    self->roster = MENU_TABS_ROSTER_SAVED;
    self->base.sub_state = MENU_TABS_SUB_REQUEST;
    self->base.state = MENU_TABS_STATE_SETUP;
    MenuScene_SetPhase(menu_tabs_scene(self), MENU_SCENE_PHASE_WAIT);
    GroupParams_ClearC50();
    SoundSys_LowerMusic();
    ControlMode_Reapply();
    return 1;
}
CLEAN_AS(func_ov090_0229971c, MenuTabs_Start)

/* func_ov090_02299774: a new menu from the menu scenes' heap (NULL when it has no room): the
 * base, the menu's vtable, the three layer tasks and the error message. */
MenuTabs *MenuTabs_New(void)
{
    MenuTabs *self = MenuScene_Alloc(sizeof(MenuTabs));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov090_02299820;
    for (int i = 0; i < MENU_TABS_TASKS; i++) {
        LayerTask_ConstructPair(&self->tasks[i]);
    }
    ErrorMessage_Construct(&self->error);
    return self;
}
CLEAN_AS(func_ov090_02299774, MenuTabs_New)
