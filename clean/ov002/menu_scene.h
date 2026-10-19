/* The base of the small menu scenes (vtable 0x0220bb24, include/cpp/ov002/Obj_ov002_0220bb24.h):
 * each scene overlay (096-125 among others) derives one class from it, allocates it with
 * MenuScene_Alloc and drives it through the slots of the scene class of autoload_2 (vtable
 * 0x020da13c, constructor Process_Construct).
 *
 * The base keeps a key repeat for the d-pad, a screen wipe (wipe.h), a link in a list of main's
 * (data_021cfca0) and a phase: each frame (MenuScene_Update) runs the virtual function of the
 * phase, which the derived classes override. Derived members start at 0x94. */
#ifndef CLEAN_OV002_MENU_SCENE_H
#define CLEAN_OV002_MENU_SCENE_H

#include "types.h"
#include "key_repeat.h"
#include "wipe.h"

/* An entry of main's list at data_021cfca0 (OverlayGroups_AddOwner adds, OverlayGroups_RemoveOwner
 * removes); the list reads the owner's `list_value`. */
typedef struct MenuSceneLink {
    u32 unk_00;
    u32 unk_04;
    struct MenuScene *owner;
} MenuSceneLink;

/* The phases MenuScene_Update runs, each by a virtual function (at the offset in the vtable;
 * the table data_ov002_0220bec4 is filled from the constants at 0x0220babc-0x0220bae4). Only
 * the wait has a body in the base; the derived classes override the others (ov090/menu_tabs.h,
 * ov092/menu_dispatch.h). What phases 3 and 4 are for is not known. */
enum MenuScenePhase {
    MENU_SCENE_PHASE_WAIT = 0,        /* slot 0x48: MenuScene_Wait */
    MENU_SCENE_PHASE_STATES = 1,      /* slot 0x4c: the scene's own state table */
    MENU_SCENE_PHASE_INTERACTIVE = 2, /* slot 0x50 */
    MENU_SCENE_PHASE_3 = 3,           /* slot 0x54 */
    MENU_SCENE_PHASE_4 = 4,           /* slot 0x58 */
    MENU_SCENE_PHASE_DELETE = 5,      /* slot 0x5c: the scene asks to be deleted */
    MENU_SCENE_PHASES = 6
};

typedef struct MenuScene {
    const void *vtable; /* data_ov002_0220bb24, or a derived class's */
    u32 unk_04;         /* fields of autoload_2's scene class */
    u32 unk_08;         /* 0x08 */
    u8 unk_0c[0x44];    /* 0x0c */
    KeyRepeat keys;     /* 0x50 */
    MenuSceneLink link; /* 0x64 */
    Wipe wipe;          /* 0x70 */
    u8 state;           /* 0x8c: the derived class's */
    u8 sub_state;       /* 0x8d */
    u8 unk_8e;          /* 0x8e */
    u8 phase;           /* 0x8f: MenuScenePhase */
    u8 list_value;      /* 0x90: unk_08's low byte, handed to func_0206ff24 by the list */
    u8 unk_91[3];       /* 0x91 */
} MenuScene;

void MenuScene_ScrollWipe(MenuScene *scene, int layer, int x, int y);
void MenuScene_SetWipeExtent(MenuScene *scene, int extent);
void MenuScene_StartWipe(MenuScene *scene, int frames, int direction);
void MenuScene_StartWipeCovered(MenuScene *scene, int frames, int direction);
void MenuScene_StartWipeOnWindow0(MenuScene *scene, int layers, int frames, int direction, int margin);
void MenuScene_StartWipeCoveredOnWindow0(MenuScene *scene, int layers, int frames, int direction, int margin);
void MenuScene_StartWipeOnWindow2(MenuScene *scene, int layers, int frames, int direction, int margin);
void MenuScene_StartWipeCoveredOnWindow2(MenuScene *scene, int layers, int frames, int direction, int margin);
int MenuScene_StepWipe(MenuScene *scene, int screen);
int MenuScene_StepWipeBack(MenuScene *scene, int screen);
int MenuScene_WipeOffsetX(MenuScene *scene);
int MenuScene_WipeOffsetY(MenuScene *scene);
void MenuScene_Free(void *block);
void *MenuScene_Alloc(int size);
void MenuScene_SetKeyRepeat(MenuScene *scene, int first_delay, int min_delay, int speedup);
void MenuScene_ResetKeyRepeat(MenuScene *scene);
int MenuScene_RepeatedRight(MenuScene *scene);
int MenuScene_RepeatedLeft(MenuScene *scene);
int MenuScene_RepeatedDown(MenuScene *scene);
int MenuScene_RepeatedUp(MenuScene *scene);
u32 MenuScene_LatchRepeatedKeys(MenuScene *scene);
int MenuScene_TakeTouch(MenuScene *scene);
int MenuScene_TakeButtons(MenuScene *scene, int also_command_3b);
void MenuScene_SetState(MenuScene *scene, u8 state);
u8 *MenuScene_SetSubState(MenuScene *scene, u8 sub_state);
u8 *MenuScene_SetPhase(MenuScene *scene, u8 phase);
int MenuScene_Update(MenuScene *scene);
int MenuScene_Phase5(void);
int MenuScene_Phase4(void);
int MenuScene_Phase3(void);
int MenuScene_Phase2(void);
int MenuScene_Phase1(void);
int MenuScene_Wait(MenuScene *scene);
void MenuScene_Slot20(MenuScene *scene);
int MenuScene_Slot1c(MenuScene *scene);
void MenuScene_Slot14(MenuScene *scene, int how);
int MenuScene_Slot10(MenuScene *scene);
void MenuScene_Slot08(MenuScene *scene, int how);
int MenuScene_Setup(MenuScene *scene);
MenuScene *MenuScene_DestroyBase(MenuScene *scene);
MenuScene *MenuScene_Delete(MenuScene *scene);
MenuScene *MenuScene_Destroy(MenuScene *scene);
MenuScene *MenuScene_Construct(MenuScene *scene);

#endif
