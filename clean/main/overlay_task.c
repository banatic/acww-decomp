/* The object that runs the overlay groups (overlay_task.h). */
#include "overlay_task.h"

#include <assert.h>

#include "autoload_2/input.h"
#include "autoload_2/links.h"
#include "clean.h"
#include "control_mode.h"
#include "overlay_groups.h"
#include "state_flags.h"

/* The buttons the update answers (PadState.pressed bits). */
#define BUTTON_SELECT 0x0004
#define BUTTON_X 0x0400
#define BUTTON_Y 0x0800

/* The corner of the touch screen it answers: x 232 and up, y 16 and down. */
#define CORNER_MIN_X 0xe8
#define CORNER_MAX_Y 0x10

/* The modes group 9 is given for each (group_params.h). */
#define MODE_CORNER 0
#define MODE_SELECT 4
#define MODE_Y 0
#define MODE_X 5

#define REQUEST_NO_GROUP OVERLAY_GROUP_COUNT

extern u8 data_020da13c[]; /* the base class's vtable */
extern u8 data_020df548[]; /* this class's */

extern u32 data_021cfcb4[3]; /* the groups marked to be released */
extern u32 data_021cfccc[3]; /* the groups loaded */
extern OverlayGroupsRequest data_020df328;
extern List data_021cfca0;  /* the owners (overlay_groups.h) */
extern void *data_021cfc84; /* the object groups are started under without an owner */
extern u16 data_021cfc6c;   /* the state flags (state_flags.h) */
extern void *data_021cfc8c; /* group 12's pointer (group_params.h) */
extern u32 data_021cfc74;
extern u8 data_021cfc5c; /* group 9's mode (group_params.h) */

extern PadState data_021fbe40;
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */
extern u8 data_021f6c58; /* the touch's x, as a byte */
extern u8 data_021f6c54; /* the touch's y */
extern u8 data_021dc6c4;

extern void *func_020edf70(int size);   /* a zeroed block from the game's heap */
extern void *func_020ee660(void *self); /* the base class's constructor */
extern void func_0205cb00(int size, void *heap);
extern void func_0205cae4(void);
extern void func_0206ef70(void);
extern void func_0206ef34(void);
extern void func_0206eec8(void);
extern void func_02051d40(void);
extern void func_02065c68(List *list); /* empties a list */
extern int func_0203de78(void);
extern u8 func_020b65c4(void);
extern int func_0203ec98(void);
extern int func_0203e3c8(int arg);
extern u8 func_02011ed4(void);

/* func_02070214: slot 9 of the vtable; always TRUE. */
BOOL OverlayTask_Slot9(void)
{
    return TRUE;
}
CLEAN_AS(func_02070214, OverlayTask_Slot9)

/* Answer a button or the corner: func_0203e3c8(0), group 9's mode, and the control mode. */
static void answer(int mode, void (*control)(void))
{
    func_0203e3c8(0);
    data_021cfc5c = (u8) mode;
    control();
}

/* func_02070218: one frame; always TRUE. */
BOOL OverlayTask_Update(void)
{
    OverlayGroups_ReleaseMarked();
    OverlayGroups_LoadRequested();
    OverlayGroups_StartLoaded();
    func_0206eec8();

    if (func_0203de78() != 0 || func_020b65c4() == 6 || data_021dc6c4 != 0 || func_0203ec98() != 0) {
        return TRUE;
    }
    if (!OverlayGroups_IsIdle()) {
        return TRUE;
    }

    BOOL pen_went_down = data_021fbdd8 != 0 && data_021fbddc != 0;
    if (pen_went_down && data_021f6c54 <= CORNER_MAX_Y && data_021f6c58 >= CORNER_MIN_X) {
        answer(MODE_CORNER, ControlMode_UseTouch);
    } else if (data_021fbe40.pressed & BUTTON_SELECT) {
        answer(MODE_SELECT, ControlMode_UseButtons);
    } else if (data_021fbe40.pressed & BUTTON_Y) {
        answer(MODE_Y, ControlMode_UseButtons);
    } else if (func_02011ed4() != 2 && (data_021fbe40.pressed & BUTTON_X)) {
        answer(MODE_X, ControlMode_UseButtons);
    }
    return TRUE;
}
CLEAN_AS(func_02070218, OverlayTask_Update)

/* func_02070334: release every loaded group, and stop taking requests; always TRUE. */
BOOL OverlayTask_End(void)
{
    for (int i = 0; i < 3; i++) {
        data_021cfcb4[i] |= data_021cfccc[i];
    }
    OverlayGroups_ReleaseMarked();
    func_0206ef34();
    func_0205cae4();
    func_02065c68(&data_021cfca0);
    data_020df328.group = REQUEST_NO_GROUP;
    data_020df328.state = OVERLAY_GROUPS_OFF;
    data_021cfc84 = NULL;
    return TRUE;
}
CLEAN_AS(func_02070334, OverlayTask_End)

/* func_02070390: start with nothing loaded, marked or requested, groups started under `self`;
 * always TRUE. */
BOOL OverlayTask_Init(OverlayTask *self)
{
    func_0205cb00(0x8c00, NULL);
    for (int i = 0; i < 3; i++) {
        data_021cfccc[i] = 0;
        data_021cfcb4[i] = 0;
    }
    data_020df328.group = REQUEST_NO_GROUP;
    data_020df328.state = OVERLAY_GROUPS_IDLE;
    data_021cfc84 = self;
    /* QUIRK: the flags are cleared here and again by StateFlags_Reset. */
    data_021cfc6c = 0;
    StateFlags_Reset();
    func_0206ef70();
    data_021cfc8c = NULL;
    func_02051d40();
    data_021cfc74 = 0;
    return TRUE;
}
CLEAN_AS(func_02070390, OverlayTask_Init)

/* func_02070400: a new object, constructed; NULL when there is no memory for it. The vtable is
 * the base class's while its constructor runs, then this class's. */
OverlayTask *OverlayTask_New(void)
{
    OverlayTask *task = func_020edf70(sizeof(OverlayTask));
    if (task != NULL) {
        func_020ee660(task);
        task->vtable = data_020da13c;
        task->vtable = data_020df548;
    }
    return task;
}
CLEAN_AS(func_02070400, OverlayTask_New)

static_assert(sizeof(OverlayTask) == 0x50, "OverlayTask layout");
