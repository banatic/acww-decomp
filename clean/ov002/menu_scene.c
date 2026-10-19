/* The base of the menu scenes (menu_scene.h). */
#include "menu_scene.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "itcm/process_phases.h"
#include "main/control_mode.h"
#include "main/game_process.h"
#include "main/menu_backdrop.h"
#include "main/overlay_groups.h"
#include "main/sound.h"

static_assert(offsetof(MenuScene, keys) == 0x50 && sizeof(KeyRepeat) == 0x14, "key repeat");
static_assert(offsetof(MenuScene, link) == 0x64 && offsetof(MenuScene, wipe) == 0x70, "link and wipe");
static_assert(offsetof(MenuScene, phase) == 0x8f && sizeof(MenuScene) == 0x94, "scene fields");

extern const u8 data_ov002_0220bb24[]; /* the menu scene's vtable */
extern const u8 data_020da13c[];       /* autoload_2's scene vtable */

extern Heap *data_021c9b28; /* the heap the menu scenes are allocated from */

/* The pen and the buttons. */
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */
extern PadState data_021fbe40;

/* The scene as the process of autoload_2 it derives from (its first 0x50 bytes). */
static Process *process_of(MenuScene *scene)
{
    return (Process *) (void *) scene;
}

/* The scene's entry in main's list of overlay group owners. */
static OverlayGroupsOwner *owner_of(MenuScene *scene)
{
    return (OverlayGroupsOwner *) (void *) &scene->link;
}

#define WIPE_MARGIN 0x30
#define BUTTONS_ALL 0xfff

/* The game's memset (autoload_2, ARM), called by its address: in the PC build the name memset
 * is the C library's, which the PC's own start-up code uses. */
#define GAME_MEMSET 0x0212a00cu
typedef void *(*MemsetFunction)(void *dest, int value, u32 size);

/* func_ov002_02207e80 */
void MenuScene_ScrollWipe(MenuScene *scene, int layer, int x, int y)
{
    Wipe_ApplyScroll(&scene->wipe, layer, x, y);
}
CLEAN_AS(func_ov002_02207e80, MenuScene_ScrollWipe)

/* func_ov002_02207e90 */
void MenuScene_SetWipeExtent(MenuScene *scene, int extent)
{
    Wipe_SetExtent(&scene->wipe, extent);
}
CLEAN_AS(func_ov002_02207e90, MenuScene_SetWipeExtent)

/* func_ov002_02207e9c: 0 frames means 3. */
void MenuScene_StartWipe(MenuScene *scene, int frames, int direction)
{
    if (frames == 0) {
        frames = 3;
    }
    Wipe_Start(&scene->wipe, frames, (u8) direction, WIPE_MARGIN);
}
CLEAN_AS(func_ov002_02207e9c, MenuScene_StartWipe)

/* func_ov002_02207eb4: 0 frames means 4. */
void MenuScene_StartWipeCovered(MenuScene *scene, int frames, int direction)
{
    if (frames == 0) {
        frames = 4;
    }
    Wipe_StartCovered(&scene->wipe, frames, (u8) direction, WIPE_MARGIN);
}
CLEAN_AS(func_ov002_02207eb4, MenuScene_StartWipeCovered)

/* func_ov002_02207ecc: 0 frames means 3. */
void MenuScene_StartWipeOnWindow0(MenuScene *scene, int layers, int frames, int direction, int margin)
{
    if (frames == 0) {
        frames = 3;
    }
    Wipe_StartOnWindow0(&scene->wipe, layers, frames, direction, margin);
}
CLEAN_AS(func_ov002_02207ecc, MenuScene_StartWipeOnWindow0)

/* func_ov002_02207ee8: 0 frames means 4. */
void MenuScene_StartWipeCoveredOnWindow0(MenuScene *scene, int layers, int frames, int direction, int margin)
{
    if (frames == 0) {
        frames = 4;
    }
    Wipe_StartCoveredOnWindow0(&scene->wipe, layers, frames, direction, margin);
}
CLEAN_AS(func_ov002_02207ee8, MenuScene_StartWipeCoveredOnWindow0)

/* func_ov002_02207f04: 0 frames means 3. */
void MenuScene_StartWipeOnWindow2(MenuScene *scene, int layers, int frames, int direction, int margin)
{
    if (frames == 0) {
        frames = 3;
    }
    Wipe_StartOnWindow2(&scene->wipe, layers, frames, direction, margin);
}
CLEAN_AS(func_ov002_02207f04, MenuScene_StartWipeOnWindow2)

/* func_ov002_02207f20: 0 frames means 4. */
void MenuScene_StartWipeCoveredOnWindow2(MenuScene *scene, int layers, int frames, int direction, int margin)
{
    if (frames == 0) {
        frames = 4;
    }
    Wipe_StartCoveredOnWindow2(&scene->wipe, layers, frames, direction, margin);
}
CLEAN_AS(func_ov002_02207f20, MenuScene_StartWipeCoveredOnWindow2)

/* func_ov002_02207f3c: a frame of the wipe; 1 when it has run its course. */
int MenuScene_StepWipe(MenuScene *scene, int screen)
{
    return Wipe_Step(&scene->wipe, screen);
}
CLEAN_AS(func_ov002_02207f3c, MenuScene_StepWipe)

/* func_ov002_02207f48: a frame of the wipe the other way; 1 when it has run its course. */
int MenuScene_StepWipeBack(MenuScene *scene, int screen)
{
    return Wipe_StepBack(&scene->wipe, screen);
}
CLEAN_AS(func_ov002_02207f48, MenuScene_StepWipeBack)

/* func_ov002_02207f54: the wipe's horizontal displacement (0 for a vertical wipe). */
int MenuScene_WipeOffsetX(MenuScene *scene)
{
    return Wipe_OffsetX(&scene->wipe);
}
CLEAN_AS(func_ov002_02207f54, MenuScene_WipeOffsetX)

/* func_ov002_02207f60: the wipe's vertical displacement (0 for a horizontal wipe). */
int MenuScene_WipeOffsetY(MenuScene *scene)
{
    return Wipe_OffsetY(&scene->wipe);
}
CLEAN_AS(func_ov002_02207f60, MenuScene_WipeOffsetY)

/* func_ov002_02207f6c: the menu scenes' operator delete. */
void MenuScene_Free(void *block)
{
    Heap_Free(data_021c9b28, block);
}
CLEAN_AS(func_ov002_02207f6c, MenuScene_Free)

/* func_ov002_02207f80: the menu scenes' operator new: `size` bytes from the back of their heap,
 * cleared; NULL when the heap has no room. */
void *MenuScene_Alloc(int size)
{
    void *block = Heap_AllocBack(data_021c9b28, size);
    if (block == NULL) {
        return NULL;
    }
    ((MemsetFunction) (uintptr_t) GAME_MEMSET)(block, 0, (u32) size);
    return block;
}
CLEAN_AS(func_ov002_02207f80, MenuScene_Alloc)

/* func_ov002_02207fb0 */
void MenuScene_SetKeyRepeat(MenuScene *scene, int first_delay, int min_delay, int speedup)
{
    KeyRepeat_Set(&scene->keys, (unsigned short) first_delay, (unsigned short) min_delay, (unsigned short) speedup);
}
CLEAN_AS(func_ov002_02207fb0, MenuScene_SetKeyRepeat)

/* func_ov002_02207fc0: the usual repeat: first delay 8, then 1 (8 less 7). */
void MenuScene_ResetKeyRepeat(MenuScene *scene)
{
    KeyRepeat_Set(&scene->keys, 8, 1, 7);
}
CLEAN_AS(func_ov002_02207fc0, MenuScene_ResetKeyRepeat)

/* func_ov002_02207fd8: whether the latched keys hold right. */
int MenuScene_RepeatedRight(MenuScene *scene)
{
    return KeyRepeat_Right(&scene->keys);
}
CLEAN_AS(func_ov002_02207fd8, MenuScene_RepeatedRight)

/* func_ov002_02207fe4: left. */
int MenuScene_RepeatedLeft(MenuScene *scene)
{
    return KeyRepeat_Left(&scene->keys);
}
CLEAN_AS(func_ov002_02207fe4, MenuScene_RepeatedLeft)

/* func_ov002_02207ff0: down. */
int MenuScene_RepeatedDown(MenuScene *scene)
{
    return KeyRepeat_Down(&scene->keys);
}
CLEAN_AS(func_ov002_02207ff0, MenuScene_RepeatedDown)

/* func_ov002_02207ffc: up. */
int MenuScene_RepeatedUp(MenuScene *scene)
{
    return KeyRepeat_Up(&scene->keys);
}
CLEAN_AS(func_ov002_02207ffc, MenuScene_RepeatedUp)

/* func_ov002_02208008: takes the keys fired since the last call (the repeat tests then read
 * them); returns them. */
u32 MenuScene_LatchRepeatedKeys(MenuScene *scene)
{
    return KeyRepeat_Latch(&scene->keys);
}
CLEAN_AS(func_ov002_02208008, MenuScene_LatchRepeatedKeys)

/* func_ov002_02208014: when the pen touched the screen this frame, clears state flag 2 and marks
 * the input as by touch (ControlMode_UseTouch), sends command 0x866 and returns 1; else 0. The
 * scene is not read. */
int MenuScene_TakeTouch(MenuScene *scene)
{
    (void) scene;
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        ControlMode_UseTouch();
        SoundSys_PlaySe(0x866);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov002_02208014, MenuScene_TakeTouch)

/* func_ov002_02208054: when a button was pressed this frame, sets state flag 2 and marks the input
 * as by buttons (ControlMode_UseButtons), sends command 0x866 (and 0x3b with `also_command_3b`) and
 * returns 1; else 0. The scene is not read. */
int MenuScene_TakeButtons(MenuScene *scene, int also_command_3b)
{
    (void) scene;
    if ((data_021fbe40.pressed & BUTTONS_ALL) == 0) {
        return 0;
    }
    ControlMode_UseButtons();
    SoundSys_PlaySe(0x866);
    if (also_command_3b) {
        SoundSys_PlaySe(0x3b);
    }
    return 1;
}
CLEAN_AS(func_ov002_02208054, MenuScene_TakeButtons)

/* func_ov002_02208090 */
void MenuScene_SetState(MenuScene *scene, u8 state)
{
    scene->state = state;
}
CLEAN_AS(func_ov002_02208090, MenuScene_SetState)

/* func_ov002_02208098 (assembly in the ROM).
 * QUIRK: returns the field's address, which the assembly leaves in r0; the game's callers
 * ignore it.
 * Its source is assembly only, so it has no Native version: this is checked by reading. */
u8 *MenuScene_SetSubState(MenuScene *scene, u8 sub_state)
{
    scene->sub_state = sub_state;
    return &scene->sub_state;
}
CLEAN_AS(func_ov002_02208098, MenuScene_SetSubState)

/* func_ov002_022080a0 (assembly in the ROM).
 * QUIRK: returns the field's address, as MenuScene_SetSubState.
 * Assembly only in its source, as MenuScene_SetSubState. */
u8 *MenuScene_SetPhase(MenuScene *scene, u8 phase)
{
    scene->phase = phase;
    return &scene->phase;
}
CLEAN_AS(func_ov002_022080a0, MenuScene_SetPhase)

/* An mwccarm pointer to member function: `function` is the function's address, or for a
 * virtual one its offset in the vtable; `adjust` is the offset to add to `this`, doubled, plus
 * 1 for a virtual function. */
typedef struct MemberFunction {
    u32 function;
    s32 adjust;
} MemberFunction;

/* The phases' functions, as constants (all virtual, no adjustment) and as the table
 * MenuScene_Update fills from them on its first call (a function-local static). */
extern const MemberFunction data_ov002_0220babc; /* slot 0x54 */
extern const MemberFunction data_ov002_0220bac4; /* slot 0x58 */
extern const MemberFunction data_ov002_0220bacc; /* slot 0x50 */
extern const MemberFunction data_ov002_0220bad4; /* slot 0x48 */
extern const MemberFunction data_ov002_0220badc; /* slot 0x5c */
extern const MemberFunction data_ov002_0220bae4; /* slot 0x4c */
extern u32 data_ov002_0220bec0;                  /* bit 0: the table is filled */
extern MemberFunction data_ov002_0220bec4[MENU_SCENE_PHASES];

typedef int (*MenuSceneMethod)(void *self);

/* Calls `member` on `object` as mwccarm does. */
static void call_member(const MemberFunction *member, u8 *object)
{
    u8 *self = object + (member->adjust >> 1);
    u32 function = member->function;
    if (member->adjust & 1) {
        u32 vtable = *(const u32 *) self;
        function = *(const u32 *) (uintptr_t) (vtable + function);
    }
    ((MenuSceneMethod) (uintptr_t) function)(self);
}

/* func_ov002_022080a8 (vtable slot 0x18): a frame of the scene: the key repeat, then the
 * virtual function of its phase. Returns 1.
 * REQUIRES: phase < 6 (the game sets phases 0, 1, 2 and 5). */
int MenuScene_Update(MenuScene *scene)
{
    if (!(data_ov002_0220bec0 & 1)) {
        data_ov002_0220bec4[MENU_SCENE_PHASE_WAIT] = data_ov002_0220bad4;
        data_ov002_0220bec4[MENU_SCENE_PHASE_STATES] = data_ov002_0220bae4;
        data_ov002_0220bec4[MENU_SCENE_PHASE_INTERACTIVE] = data_ov002_0220bacc;
        data_ov002_0220bec4[MENU_SCENE_PHASE_3] = data_ov002_0220babc;
        data_ov002_0220bec4[MENU_SCENE_PHASE_4] = data_ov002_0220bac4;
        data_ov002_0220bec4[MENU_SCENE_PHASE_DELETE] = data_ov002_0220badc;
        data_ov002_0220bec0 |= 1;
    }
    KeyRepeat_Update(&scene->keys);
    call_member(&data_ov002_0220bec4[scene->phase], (u8 *) scene);
    return 1;
}
CLEAN_AS(func_ov002_022080a8, MenuScene_Update)

/* func_ov002_02208154: phase 5, the delete request (slot 0x5c), of the base: nothing. */
int MenuScene_Phase5(void)
{
    return 1;
}
CLEAN_AS(func_ov002_02208154, MenuScene_Phase5)

/* func_ov002_02208158: phase 4 (slot 0x58) of the base: nothing. */
int MenuScene_Phase4(void)
{
    return 1;
}
CLEAN_AS(func_ov002_02208158, MenuScene_Phase4)

/* func_ov002_0220815c: phase 3 (slot 0x54) of the base: nothing. */
int MenuScene_Phase3(void)
{
    return 1;
}
CLEAN_AS(func_ov002_0220815c, MenuScene_Phase3)

/* func_ov002_02208160: phase 2, the interactive one (slot 0x50), of the base: nothing. */
int MenuScene_Phase2(void)
{
    return 1;
}
CLEAN_AS(func_ov002_02208160, MenuScene_Phase2)

/* func_ov002_02208164: phase 1, the state table (slot 0x4c), of the base: nothing. */
int MenuScene_Phase1(void)
{
    return 1;
}
CLEAN_AS(func_ov002_02208164, MenuScene_Phase1)

/* func_ov002_02208168: phase 0, the wait (slot 0x48): on to the state table (phase 1) while
 * data_021cfc20 is 5-7; at 12, clears it and the values beside it and goes on to the delete
 * request (phase 5). */
int MenuScene_Wait(MenuScene *scene)
{
    if (MenuBackdrop_IsUp()) {
        MenuScene_SetPhase(scene, MENU_SCENE_PHASE_STATES);
    }
    if (MenuBackdrop_IsClosed()) {
        MenuBackdrop_Reset();
        MenuScene_SetPhase(scene, MENU_SCENE_PHASE_DELETE);
    }
    return 1;
}
CLEAN_AS(func_ov002_02208168, MenuScene_Wait)

/* func_ov002_02208198 (slot 0x20) */
void MenuScene_Slot20(MenuScene *scene)
{
    Process_AfterExecute(process_of(scene));
}
CLEAN_AS(func_ov002_02208198, MenuScene_Slot20)

/* func_ov002_022081a0 (slot 0x1c): whether the scene's byte at 0x0f is 0 and bit 1 of its byte
 * at 0x13 clear (Process_CanExecute). */
int MenuScene_Slot1c(MenuScene *scene)
{
    return Process_CanExecute(process_of(scene)) != 0;
}
CLEAN_AS(func_ov002_022081a0, MenuScene_Slot1c)

/* func_ov002_022081b8 (slot 0x14): with `how` 2, leaves main's list first; then the base's. */
void MenuScene_Slot14(MenuScene *scene, int how)
{
    if (how == 2) {
        OverlayGroups_RemoveOwner(owner_of(scene));
    }
    Process_AfterDelete(process_of(scene), how);
}
CLEAN_AS(func_ov002_022081b8, MenuScene_Slot14)

/* func_ov002_022081dc (slot 0x10): the base's answer, as 0 or 1. */
int MenuScene_Slot10(MenuScene *scene)
{
    return Process_CanDelete(process_of(scene)) != 0;
}
CLEAN_AS(func_ov002_022081dc, MenuScene_Slot10)

/* func_ov002_022081f4 (slot 0x08): joins main's list; with `how` 2 and a parent process, takes
 * the parent's execute and draw orders, plus one, as its own. Then the base's. */
void MenuScene_Slot08(MenuScene *scene, int how)
{
    OverlayGroups_AddOwner(owner_of(scene));
    if (how == 2) {
        const Process *parent = Process_GetParent(process_of(scene));
        if (parent != NULL) {
            Process_SetExecuteOrder(process_of(scene), (u16) (parent->link.order + 1));
            Process_SetDrawOrder(process_of(scene), (u16) (parent->draw_link.order + 1));
        }
    }
    GameProcess_AfterCreate(process_of(scene), how);
}
CLEAN_AS(func_ov002_022081f4, MenuScene_Slot08)

/* func_ov002_0220823c (slot 0x04): links the scene to main's list and sets the usual key
 * repeat. Returns 0 if Process_CanCreateDefault does (it never does). */
int MenuScene_Setup(MenuScene *scene)
{
    if (!Process_CanCreateDefault()) {
        return 0;
    }
    scene->list_value = (u8) scene->unk_08;
    scene->link.owner = scene;
    KeyRepeat_Set(&scene->keys, 8, 1, 7);
    return 1;
}
CLEAN_AS(func_ov002_0220823c, MenuScene_Setup)

/* func_ov002_0220826c: the destructor as one of the base's pair (it does what
 * MenuScene_Destroy does). */
MenuScene *MenuScene_DestroyBase(MenuScene *scene)
{
    scene->vtable = data_ov002_0220bb24;
    Wipe_Destroy(&scene->wipe);
    KeyRepeat_Destroy(&scene->keys);
    scene->vtable = data_020da13c;
    Process_Destruct(process_of(scene));
    return scene;
}
CLEAN_AS(func_ov002_0220826c, MenuScene_DestroyBase)

/* func_ov002_022082a0: the deleting destructor. */
MenuScene *MenuScene_Delete(MenuScene *scene)
{
    MenuScene_Destroy(scene);
    MenuScene_Free(scene);
    return scene;
}
CLEAN_AS(func_ov002_022082a0, MenuScene_Delete)

/* func_ov002_022082d8 */
MenuScene *MenuScene_Destroy(MenuScene *scene)
{
    scene->vtable = data_ov002_0220bb24;
    Wipe_Destroy(&scene->wipe);
    KeyRepeat_Destroy(&scene->keys);
    scene->vtable = data_020da13c;
    Process_Destruct(process_of(scene));
    return scene;
}
CLEAN_AS(func_ov002_022082d8, MenuScene_Destroy)

/* func_ov002_0220830c
 * QUIRK: stores the base's vtable before its own, as a C++ constructor does. */
MenuScene *MenuScene_Construct(MenuScene *scene)
{
    Process_Construct(process_of(scene));
    scene->vtable = data_020da13c;
    scene->vtable = data_ov002_0220bb24;
    KeyRepeat_Construct(&scene->keys);
    scene->link.unk_00 = 0;
    scene->link.unk_04 = 0;
    Wipe_Construct(&scene->wipe);
    return scene;
}
CLEAN_AS(func_ov002_0220830c, MenuScene_Construct)
