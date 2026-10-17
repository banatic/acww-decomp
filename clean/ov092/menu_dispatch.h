/* The scene of overlay 92 (overlay group 9, which GroupParams_Open and its kin open in a mode;
 * vtable 0x02299508; constructor MenuDispatch_New, 0x94 bytes, the base's alone): a menu scene
 * (ov002/menu_scene.h) with nothing of its own to show, that starts the screen of GroupParams'
 * mode as an overlay group (MenuDispatch_RequestGroup) and is the parent process of those
 * screens: the pockets view (ov099/pockets_view.h), the letter scenes (ov104/letter_send.h,
 * ov105/letter_storage.h, ov106/mailbox_scene.h) and others.
 *
 * A screen tells it what comes next with MenuDispatch_SetMode (MENU_DISPATCH_MODE_END or
 * MENU_DISPATCH_MODE_CLOSE to end) and, when it has closed, MenuDispatch_ChildClosed starts the
 * next one or ends the scene. */
#ifndef CLEAN_OV092_MENU_DISPATCH_H
#define CLEAN_OV092_MENU_DISPATCH_H

#include "ov002/menu_scene.h"
#include "types.h"

/* GroupParams' modes this scene treats apart (MenuDispatch.mode). */
enum MenuDispatchMode {
    MENU_DISPATCH_MODE_0 = 0,       /* the backdrop is not opened; sound 0x11 */
    MENU_DISPATCH_MODE_3 = 3,       /* SceneSound_Vfunc24(1) instead of sound 1 */
    MENU_DISPATCH_MODE_END = 0x43,  /* the scene ends (deleted) */
    MENU_DISPATCH_MODE_CLOSE = 0x44 /* the scene ends with the backdrop closed */
};

/* The base's byte 0x91 (MenuScene.unk_91[0]) is the mode. */
#define MENU_DISPATCH_BYTE_MODE 0

/* The states and sub states (MenuScene.state, MenuScene.sub_state) and the phases set
 * (menu_scene.c's MenuScene_Update runs phase 0 by the vtable's slot 0x48, 1 by 0x4c, 2 by 0x50
 * and 5 by 0x5c). */
enum MenuDispatchState {
    MENU_DISPATCH_STATE_OPEN = 0, /* MenuDispatch_Open */
    MENU_DISPATCH_STATES = 1
};

enum MenuDispatchSubState {
    MENU_DISPATCH_SUB_IDLE = 0,    /* MenuDispatch_Idle */
    MENU_DISPATCH_SUB_REQUEST = 1, /* MenuDispatch_RequestGroup */
    MENU_DISPATCH_SUB_STATES = 2
};

enum MenuDispatchPhase {
    MENU_DISPATCH_PHASE_WAIT = 0,
    MENU_DISPATCH_PHASE_STATES = 1,      /* MenuDispatch_RunState */
    MENU_DISPATCH_PHASE_INTERACTIVE = 2, /* MenuDispatch_RunInteractive */
    MENU_DISPATCH_PHASE_DELETE = 5       /* MenuDispatch_RequestDelete */
};

typedef struct MenuDispatch {
    MenuScene base; /* 0x00: its byte 0x91 is the mode */
} MenuDispatch;

MenuDispatch *MenuDispatch_Destroy(MenuDispatch *self);
MenuDispatch *MenuDispatch_Delete(MenuDispatch *self);
void MenuDispatch_EndMembers(MenuDispatch *self);
void MenuDispatch_Setup(MenuDispatch *self);
void MenuDispatch_Open(MenuDispatch *self);
void MenuDispatch_RequestGroup(MenuDispatch *self);
void MenuDispatch_Idle(void);
void MenuDispatch_ChildClosed(MenuDispatch *self);
void MenuDispatch_SetMode(MenuDispatch *self, int mode, int with_sound);
int MenuDispatch_RequestDelete(MenuDispatch *self);
int MenuDispatch_Phase4(void);
int MenuDispatch_Phase3(void);
int MenuDispatch_RunInteractive(MenuDispatch *self);
int MenuDispatch_RunState(MenuDispatch *self);
int MenuDispatch_Draw(void);
int MenuDispatch_End(MenuDispatch *self);
int MenuDispatch_Start(MenuDispatch *self);
MenuDispatch *MenuDispatch_New(void);

#endif
