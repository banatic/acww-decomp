/* The screen dispatch of overlay 92 (menu_dispatch.h): the screen of each mode, the messages of
 * the screens it starts and the vtable's slots. */
#include "menu_dispatch.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/process.h"
#include "clean.h"
#include "main/control_mode.h"
#include "main/display_shadow.h"
#include "main/group_params.h"
#include "main/menu_backdrop.h"
#include "main/music_volume.h"
#include "main/overlay_groups.h"
#include "main/scene_sound.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov004/member_pointer.h"

static_assert(sizeof(MenuDispatch) == 0x94, "size (func_ov092_022994a0)");

/* The scene's vtable. */
extern const u8 data_ov092_02299508[];

/* The field's sound object; its music volume is at 0x1c4 (main/music_volume.h). */
extern u8 *data_021c526c;

/* The tables of member functions (ov004/member_pointer.h): their guards, the tables and the
 * constants they are filled from. */
extern u32 data_ov092_02299580; /* the states' guard */
extern u32 data_ov092_02299584; /* the sub states' guard */
extern MemberPointer data_ov092_02299588[MENU_DISPATCH_STATES];
extern MemberPointer data_ov092_02299590[MENU_DISPATCH_SUB_STATES];
extern const MemberPointer data_ov092_022994e8; /* MenuDispatch_Idle */
extern const MemberPointer data_ov092_022994f0; /* MenuDispatch_Open */
extern const MemberPointer data_ov092_022994f8; /* MenuDispatch_RequestGroup */

/* The overlay group of each mode's screen (main/overlay_groups.c); 0 for none (the menu of
 * group 0 is never asked for here). */
#define MENU_DISPATCH_MODES 0x43
static const u8
    menu_dispatch_groups[MENU_DISPATCH_MODES] =
        {
            [0x00] = 0x0b,                /* overlay 113 */
            [0x01] = 0x0a,                /* overlays 112, 95 */
            [0x02] = 0x0d,                /* overlay 123 */
            [0x03] = 0x0d, [0x04] = 0x0e, /* 0x04-0x0a: overlays 124, 125 */
            [0x05] = 0x0e, [0x06] = 0x0e, [0x07] = 0x0e, [0x08] = 0x0e, [0x09] = 0x0e,
            [0x0a] = 0x0e, [0x0b] = 0x0f, /* 0x0b-0x17: overlays 124, 126, 95 */
            [0x0c] = 0x0f, [0x0d] = 0x0f, [0x0e] = 0x0f, [0x0f] = 0x0f, [0x10] = 0x0f,
            [0x11] = 0x0f, [0x12] = 0x0f, [0x13] = 0x0f, [0x14] = 0x0f, [0x15] = 0x0f,
            [0x16] = 0x0f, [0x17] = 0x0f, [0x1c] = 0x10,                /* overlay 99, the pockets view */
            [0x1d] = 0x11,                                              /* overlay 100 */
            [0x1e] = 0x11, [0x1f] = 0x2c,                               /* overlay 110 */
            [0x20] = 0x2c, [0x21] = 0x12,                               /* overlay 101 */
            [0x22] = 0x13,                                              /* overlay 102 */
            [0x23] = 0x29,                                              /* overlay 109 */
            [0x24] = 0x14,                                              /* overlay 103 */
            [0x25] = 0x15,                                              /* overlay 104, the letter send */
            [0x26] = 0x16,                                              /* overlay 105, the letter storage */
            [0x27] = 0x17,                                              /* overlay 106, the mailbox */
            [0x28] = 0x28,                                              /* overlay 108 */
            [0x29] = 0x18,                                              /* 0x29-0x2c: overlay 107 */
            [0x2a] = 0x18, [0x2b] = 0x18, [0x2c] = 0x18, [0x2d] = 0x19, /* overlay 128 */
            [0x2e] = 0x1a,                                              /* overlay 129 */
            [0x2f] = 0x1b,                                              /* overlay 120 */
            [0x30] = 0x1c,                                              /* overlay 135 */
            [0x31] = 0x1d,                                              /* overlay 136 */
            [0x32] = 0x1e,                                              /* overlay 137 */
            [0x33] = 0x2a,                                              /* overlay 138 */
            [0x34] = 0x1f,                                              /* 0x34-0x3a: overlay 131 */
            [0x35] = 0x1f, [0x36] = 0x1f, [0x37] = 0x1f, [0x38] = 0x1f, [0x39] = 0x1f,
            [0x3a] = 0x1f, [0x3b] = 0x20, /* overlay 132 */
            [0x3c] = 0x2d,                /* overlay 146 */
            [0x3d] = 0x22,                /* overlay 141 */
            [0x3e] = 0x23,                /* overlay 142 */
            [0x3f] = 0x25,                /* overlay 143 */
            [0x40] = 0x26,                /* overlay 144 */
            [0x41] = 0x27,                /* overlay 145 */
            [0x42] = 0x2d,                /* overlay 146 */
};

static MenuScene *menu_dispatch_scene(MenuDispatch *self)
{
    return &self->base;
}

static u8 *menu_dispatch_mode(MenuDispatch *self)
{
    return &self->base.unk_91[MENU_DISPATCH_BYTE_MODE];
}

static MusicVolume *menu_dispatch_music_volume(void)
{
    return (MusicVolume *) (void *) (data_021c526c + 0x1c4);
}

/* func_ov092_02298f20 (vtable slot 0x40) */
MenuDispatch *MenuDispatch_Destroy(MenuDispatch *self)
{
    self->base.vtable = data_ov092_02299508;
    MenuScene_DestroyBase(menu_dispatch_scene(self));
    return self;
}
CLEAN_AS(func_ov092_02298f20, MenuDispatch_Destroy)

/* func_ov092_02298f38 (vtable slot 0x44) */
MenuDispatch *MenuDispatch_Delete(MenuDispatch *self)
{
    self->base.vtable = data_ov092_02299508;
    MenuScene_DestroyBase(menu_dispatch_scene(self));
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov092_02298f38, MenuDispatch_Delete)

/* func_ov092_02298f58: the end of the scene's own members: there are none. */
void MenuDispatch_EndMembers(MenuDispatch *self)
{
    (void) self;
}
CLEAN_AS(func_ov092_02298f58, MenuDispatch_EndMembers)

/* func_ov092_02298f5c: the mode taken from GroupParams and its screen asked for next frame
 * (sub state 1). Mode 0 runs at once (phase 2); any other opens the backdrop first (state 0 in
 * phase 0). Then the backdrop's style, the sound and the music volume's slot 1 by the mode. */
void MenuDispatch_Setup(MenuDispatch *self)
{
    u8 *mode = menu_dispatch_mode(self);

    *mode = GroupParams_Mode();
    self->base.sub_state = MENU_DISPATCH_SUB_REQUEST;
    if (*mode == MENU_DISPATCH_MODE_0) {
        MenuScene_SetPhase(menu_dispatch_scene(self), MENU_DISPATCH_PHASE_INTERACTIVE);
    } else {
        self->base.state = MENU_DISPATCH_STATE_OPEN;
        MenuScene_SetPhase(menu_dispatch_scene(self), MENU_DISPATCH_PHASE_WAIT);
        MenuBackdrop_Open();
    }

    switch (*mode) {
        case 0x2d:
        case 0x2e:
            MenuBackdrop_SetStyle(3);
            break;
        case 0x0f:
            MenuBackdrop_SetStyle(1);
            break;
        case 0x10:
            MenuBackdrop_SetStyle(2);
            break;
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
            MenuBackdrop_SetStyle(0);
            break;
        default:
            break;
    }

    if (*mode == MENU_DISPATCH_MODE_0) {
        SoundSys_PlaySe(0x11);
    } else if (*mode == MENU_DISPATCH_MODE_3) {
        SceneSound_Vfunc24(1);
    } else {
        SoundSys_PlaySe(1);
    }

    int music_index = 0;
    if (*mode == 0x2d || *mode == 0x2e) {
        music_index = 1;
    } else if (*mode == 0x3f) {
        music_index = 2;
    }
    MusicVolume_SetSlot1(menu_dispatch_music_volume(), music_index);
}
CLEAN_AS(func_ov092_02298f5c, MenuDispatch_Setup)

/* func_ov092_0229906c (state 0): the sub screen's BG mode 0, then the screen is asked for
 * (phase 2). */
void MenuDispatch_Open(MenuDispatch *self)
{
    DisplayShadow_SetSubBgMode(0);
    MenuScene_SetPhase(menu_dispatch_scene(self), MENU_DISPATCH_PHASE_INTERACTIVE);
}
CLEAN_AS(func_ov092_0229906c, MenuDispatch_Open)

/* func_ov092_02299084 (sub state 1): state flag 0x100 set for some modes, the overlay group of
 * the mode's screen asked for (modes 0x18-0x1b and from 0x43 have none), back to sub
 * state 0. */
void MenuDispatch_RequestGroup(MenuDispatch *self)
{
    u8 mode = *menu_dispatch_mode(self);
    switch (mode) {
        case 0x00:
        case 0x01:
        case 0x18:
        case 0x1a:
        case 0x20:
        case 0x22:
        case 0x23:
        case 0x27:
        case 0x40:
            StateFlags_Set100();
            break;
        default:
            break;
    }
    if (mode < MENU_DISPATCH_MODES && menu_dispatch_groups[mode] != 0) {
        OverlayGroups_RequestForOwner(menu_dispatch_groups[mode]);
    }
    self->base.sub_state = MENU_DISPATCH_SUB_IDLE;
}
CLEAN_AS(func_ov092_02299084, MenuDispatch_RequestGroup)

/* func_ov092_02299298 (sub state 0): nothing. */
void MenuDispatch_Idle(void) {}
CLEAN_AS(func_ov092_02299298, MenuDispatch_Idle)

/* func_ov092_0229929c: the screen has closed. MENU_DISPATCH_MODE_END deletes the scene (phase
 * 5); MENU_DISPATCH_MODE_CLOSE waits (phase 0) with the sub screen's BG mode 1 and the
 * backdrop let go. Modes 0 and 1 open the backdrop again and start their screen again; modes
 * 2, 0x23, 0x35, 0x36 and 0x40 are set in GroupParams again and their screen started again. */
void MenuDispatch_ChildClosed(MenuDispatch *self)
{
    u8 mode = *menu_dispatch_mode(self);
    switch (mode) {
        case MENU_DISPATCH_MODE_END:
            MenuScene_SetPhase(menu_dispatch_scene(self), MENU_DISPATCH_PHASE_DELETE);
            break;
        case MENU_DISPATCH_MODE_CLOSE:
            MenuScene_SetPhase(menu_dispatch_scene(self), MENU_DISPATCH_PHASE_WAIT);
            DisplayShadow_SetSubBgMode(1);
            MenuBackdrop_ReleaseClose();
            break;
        case 0x00:
        case 0x01:
            MenuBackdrop_Open();
            self->base.sub_state = MENU_DISPATCH_SUB_REQUEST;
            break;
        case 0x02:
        case 0x23:
        case 0x35:
        case 0x36:
        case 0x40:
            self->base.sub_state = MENU_DISPATCH_SUB_REQUEST;
            GroupParams_SetMode((char) mode);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov092_0229929c, MenuDispatch_ChildClosed)

/* func_ov092_02299324: a screen says what comes after it (its low byte kept as the mode).
 * MENU_DISPATCH_MODE_CLOSE closes the backdrop; both ending modes end the music volume's slot
 * 1, after sound 2 when `with_sound` is set. */
void MenuDispatch_SetMode(MenuDispatch *self, int mode, int with_sound)
{
    *menu_dispatch_mode(self) = (u8) mode;
    if (mode == MENU_DISPATCH_MODE_CLOSE) {
        MenuBackdrop_Close();
    }
    if (mode == MENU_DISPATCH_MODE_END || mode == MENU_DISPATCH_MODE_CLOSE) {
        if (with_sound) {
            SoundSys_PlaySe(2);
        }
        MusicVolume_EndSlot1(menu_dispatch_music_volume());
    }
}
CLEAN_AS(func_ov092_02299324, MenuDispatch_SetMode)

/* func_ov092_02299380 (vtable slot 0x5c, phase 5): the scene asks to be deleted. */
int MenuDispatch_RequestDelete(MenuDispatch *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov092_02299380, MenuDispatch_RequestDelete)

/* func_ov092_02299390 (vtable slot 0x58, phase 4): nothing. */
int MenuDispatch_Phase4(void)
{
    return 1;
}
CLEAN_AS(func_ov092_02299390, MenuDispatch_Phase4)

/* func_ov092_02299394 (vtable slot 0x54, phase 3): nothing. */
int MenuDispatch_Phase3(void)
{
    return 1;
}
CLEAN_AS(func_ov092_02299394, MenuDispatch_Phase3)

/* func_ov092_02299398 (vtable slot 0x50, phase 2): the sub state (MenuDispatchSubState) run
 * through its table of member functions, filled once from its constants. Answers 1.
 * REQUIRES: the sub state is below 2; the game reads past the table for others. */
int MenuDispatch_RunInteractive(MenuDispatch *self)
{
    static const MemberPointer *const sub_states[MENU_DISPATCH_SUB_STATES] = {
        &data_ov092_022994e8,
        &data_ov092_022994f8,
    };
    MemberTable_InitOnce(&data_ov092_02299584, data_ov092_02299590, sub_states, MENU_DISPATCH_SUB_STATES);
    MemberPointer_CallVoid(&data_ov092_02299590[self->base.sub_state], self);
    return 1;
}
CLEAN_AS(func_ov092_02299398, MenuDispatch_RunInteractive)

/* func_ov092_02299400 (vtable slot 0x4c, phase 1): the state (MenuDispatchState) run through
 * its table of member functions, filled once from its constant. Answers 1.
 * REQUIRES: the state is 0; the game reads past the table for others. */
int MenuDispatch_RunState(MenuDispatch *self)
{
    static const MemberPointer *const states[MENU_DISPATCH_STATES] = {
        &data_ov092_022994f0,
    };
    MemberTable_InitOnce(&data_ov092_02299580, data_ov092_02299588, states, MENU_DISPATCH_STATES);
    MemberPointer_CallVoid(&data_ov092_02299588[self->base.state], self);
    return 1;
}
CLEAN_AS(func_ov092_02299400, MenuDispatch_RunState)

/* func_ov092_0229945c (vtable slot 0x24): nothing to draw. Answers 1. */
int MenuDispatch_Draw(void)
{
    return 1;
}
CLEAN_AS(func_ov092_0229945c, MenuDispatch_Draw)

/* func_ov092_02299460 (vtable slot 0x0c): the scene ends: state flag 0x100 cleared, the
 * backdrop ended, the members' end, the music restored. Answers 1. */
int MenuDispatch_End(MenuDispatch *self)
{
    StateFlags_Clear100();
    MenuBackdrop_End();
    MenuDispatch_EndMembers(self);
    SoundSys_RestoreMusic();
    return 1;
}
CLEAN_AS(func_ov092_02299460, MenuDispatch_End)

/* func_ov092_02299480 (vtable slot 0x00): the scene starts: state flag 0x100 cleared, set up,
 * the music lowered and the control mode applied again. Answers 1. */
int MenuDispatch_Start(MenuDispatch *self)
{
    StateFlags_Clear100();
    MenuDispatch_Setup(self);
    SoundSys_LowerMusic();
    ControlMode_Reapply();
    return 1;
}
CLEAN_AS(func_ov092_02299480, MenuDispatch_Start)

/* func_ov092_022994a0: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base and the scene's vtable. */
MenuDispatch *MenuDispatch_New(void)
{
    MenuDispatch *self = MenuScene_Alloc(sizeof(MenuDispatch));
    if (self != NULL) {
        MenuScene_Construct(&self->base);
        self->base.vtable = data_ov092_02299508;
    }
    return self;
}
CLEAN_AS(func_ov092_022994a0, MenuDispatch_New)
