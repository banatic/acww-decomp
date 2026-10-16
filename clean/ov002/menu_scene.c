/* The base of the menu scenes (menu_scene.h). */
#include "menu_scene.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "clean.h"

static_assert(offsetof(MenuScene, keys) == 0x50 && sizeof(KeyRepeat) == 0x14, "key repeat");
static_assert(offsetof(MenuScene, link) == 0x64 && offsetof(MenuScene, wipe) == 0x70, "link and wipe");
static_assert(offsetof(MenuScene, phase) == 0x8f && sizeof(MenuScene) == 0x94, "scene fields");

extern const u8 data_ov002_0220bb24[]; /* the menu scene's vtable */
extern const u8 data_020da13c[];       /* autoload_2's scene vtable */

extern Heap *data_021c9b28; /* the heap the menu scenes are allocated from */

/* autoload_2's scene class */
extern void *func_020ee660(void *scene);         /* constructor */
extern void func_020ee62c(void *scene);          /* destructor */
extern int func_020ee61c(void);                  /* returns 1 */
extern void func_020ee4d8(void *scene, int how); /* slot 0x14 */
extern int func_020ee550(void *scene);           /* slot 0x10 */
extern void *func_020ee45c(void *scene);         /* the word at 0x10 of the object at 0x14, or 0 */
extern void func_020ee3c0(void *scene, unsigned short value);
extern void func_020ee324(void *scene, unsigned short value);
extern void func_0202f144(void *scene, int how);
extern void func_01ffd418(void *scene); /* does nothing */
extern int func_01ffd41c(unsigned char *scene);

/* main's list at data_021cfca0 */
extern void func_02070204(void *link); /* adds */
extern void func_020701e4(void *link); /* removes */

/* input, and the command the input checks send */
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */
extern PadState data_021fbe40;
extern void func_0206fe90(void);            /* clears state flag 2, sets the word at 0x021d36a8 to 2 */
extern void func_0206fe7c(void);            /* sets state flag 2, sets the word at 0x021d36a8 to 1 */
extern void RtcSendPxiCommand(int command); /* func_020f1fb4(&data_021fd1bc, command) */

/* what MenuScene_Wait waits on */
extern int func_0206f258(void);  /* data_021cfc20 is 5, 6 or 7 */
extern int func_0206f244(void);  /* data_021cfc20 is 12 */
extern void func_0206ef70(void); /* clears data_021cfc18, data_021cfc1c and data_021cfc20 */

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

/* func_ov002_02208014: when the pen touched the screen this frame, clears state flag 2 and
 * marks the input as by touch (func_0206fe90), sends command 0x866 and returns 1; else 0. The
 * scene is not read. */
int MenuScene_TakeTouch(MenuScene *scene)
{
    (void) scene;
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        func_0206fe90();
        RtcSendPxiCommand(0x866);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov002_02208014, MenuScene_TakeTouch)

/* func_ov002_02208054: when a button was pressed this frame, sets state flag 2 and marks the
 * input as by buttons (func_0206fe7c), sends command 0x866 (and 0x3b with `also_command_3b`)
 * and returns 1; else 0. The scene is not read. */
int MenuScene_TakeButtons(MenuScene *scene, int also_command_3b)
{
    (void) scene;
    if ((data_021fbe40.pressed & BUTTONS_ALL) == 0) {
        return 0;
    }
    func_0206fe7c();
    RtcSendPxiCommand(0x866);
    if (also_command_3b) {
        RtcSendPxiCommand(0x3b);
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
extern const MemberFunction data_ov002_0220babc; /* slot 0x48 */
extern const MemberFunction data_ov002_0220bac4; /* slot 0x5c */
extern const MemberFunction data_ov002_0220bacc; /* slot 0x50 */
extern const MemberFunction data_ov002_0220bad4; /* slot 0x54 */
extern const MemberFunction data_ov002_0220badc; /* slot 0x4c */
extern const MemberFunction data_ov002_0220bae4; /* slot 0x58 */
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
 * REQUIRES: phase < 6 (the game's phases are 1, 3 and 5 here). */
int MenuScene_Update(MenuScene *scene)
{
    if (!(data_ov002_0220bec0 & 1)) {
        data_ov002_0220bec4[MENU_SCENE_PHASE_0] = data_ov002_0220bad4;
        data_ov002_0220bec4[MENU_SCENE_PHASE_1] = data_ov002_0220bae4;
        data_ov002_0220bec4[MENU_SCENE_PHASE_2] = data_ov002_0220bacc;
        data_ov002_0220bec4[MENU_SCENE_WAIT] = data_ov002_0220babc;
        data_ov002_0220bec4[MENU_SCENE_PHASE_4] = data_ov002_0220bac4;
        data_ov002_0220bec4[MENU_SCENE_RUN] = data_ov002_0220badc;
        data_ov002_0220bec0 |= 1;
    }
    KeyRepeat_Update(&scene->keys);
    call_member(&data_ov002_0220bec4[scene->phase], (u8 *) scene);
    return 1;
}
CLEAN_AS(func_ov002_022080a8, MenuScene_Update)

/* func_ov002_02208154: phase 4 (slot 0x5c) of the base: nothing. */
int MenuScene_Phase4(void)
{
    return 1;
}
CLEAN_AS(func_ov002_02208154, MenuScene_Phase4)

/* func_ov002_02208158: phase 1 (slot 0x58) of the base: nothing. */
int MenuScene_Phase1(void)
{
    return 1;
}
CLEAN_AS(func_ov002_02208158, MenuScene_Phase1)

/* func_ov002_0220815c: phase 0 (slot 0x54) of the base: nothing. */
int MenuScene_Phase0(void)
{
    return 1;
}
CLEAN_AS(func_ov002_0220815c, MenuScene_Phase0)

/* func_ov002_02208160: phase 2 (slot 0x50) of the base: nothing. */
int MenuScene_Phase2(void)
{
    return 1;
}
CLEAN_AS(func_ov002_02208160, MenuScene_Phase2)

/* func_ov002_02208164: the run phase (slot 0x4c) of the base: nothing. */
int MenuScene_Run(void)
{
    return 1;
}
CLEAN_AS(func_ov002_02208164, MenuScene_Run)

/* func_ov002_02208168: the wait phase (slot 0x48): on to phase 1 while data_021cfc20 is 5-7;
 * at 12, clears it and the values beside it and goes on to the run phase. */
int MenuScene_Wait(MenuScene *scene)
{
    if (func_0206f258()) {
        MenuScene_SetPhase(scene, MENU_SCENE_PHASE_1);
    }
    if (func_0206f244()) {
        func_0206ef70();
        MenuScene_SetPhase(scene, MENU_SCENE_RUN);
    }
    return 1;
}
CLEAN_AS(func_ov002_02208168, MenuScene_Wait)

/* func_ov002_02208198 (slot 0x20) */
void MenuScene_Slot20(MenuScene *scene)
{
    func_01ffd418(scene);
}
CLEAN_AS(func_ov002_02208198, MenuScene_Slot20)

/* func_ov002_022081a0 (slot 0x1c): whether the scene's byte at 0x0f is 0 and bit 1 of its byte
 * at 0x13 clear (func_01ffd41c). */
int MenuScene_Slot1c(MenuScene *scene)
{
    return func_01ffd41c((unsigned char *) scene) != 0;
}
CLEAN_AS(func_ov002_022081a0, MenuScene_Slot1c)

/* func_ov002_022081b8 (slot 0x14): with `how` 2, leaves main's list first; then the base's. */
void MenuScene_Slot14(MenuScene *scene, int how)
{
    if (how == 2) {
        func_020701e4(&scene->link);
    }
    func_020ee4d8(scene, how);
}
CLEAN_AS(func_ov002_022081b8, MenuScene_Slot14)

/* func_ov002_022081dc (slot 0x10): the base's answer, as 0 or 1. */
int MenuScene_Slot10(MenuScene *scene)
{
    return func_020ee550(scene) != 0;
}
CLEAN_AS(func_ov002_022081dc, MenuScene_Slot10)

/* func_ov002_022081f4 (slot 0x08): joins main's list; with `how` 2 and an object at 0x14 that
 * has one, takes the halfwords at 0x34 and 0x44 of that object, plus one, as its own two
 * values (func_020ee3c0, func_020ee324). Then the base's. */
void MenuScene_Slot08(MenuScene *scene, int how)
{
    func_02070204(&scene->link);
    if (how == 2) {
        const u8 *other = func_020ee45c(scene);
        if (other != NULL) {
            func_020ee3c0(scene, (unsigned short) (*(const u16 *) (other + 0x34) + 1));
            func_020ee324(scene, (unsigned short) (*(const u16 *) (other + 0x44) + 1));
        }
    }
    func_0202f144(scene, how);
}
CLEAN_AS(func_ov002_022081f4, MenuScene_Slot08)

/* func_ov002_0220823c (slot 0x04): links the scene to main's list and sets the usual key
 * repeat. Returns 0 if func_020ee61c does (it never does). */
int MenuScene_Setup(MenuScene *scene)
{
    if (!func_020ee61c()) {
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
    func_020ee62c(scene);
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
    func_020ee62c(scene);
    return scene;
}
CLEAN_AS(func_ov002_022082d8, MenuScene_Destroy)

/* func_ov002_0220830c
 * QUIRK: stores the base's vtable before its own, as a C++ constructor does. */
MenuScene *MenuScene_Construct(MenuScene *scene)
{
    func_020ee660(scene);
    scene->vtable = data_020da13c;
    scene->vtable = data_ov002_0220bb24;
    KeyRepeat_Construct(&scene->keys);
    scene->link.unk_00 = 0;
    scene->link.unk_04 = 0;
    Wipe_Construct(&scene->wipe);
    return scene;
}
CLEAN_AS(func_ov002_0220830c, MenuScene_Construct)
