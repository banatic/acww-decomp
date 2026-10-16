/* The object that runs the overlay groups (overlay_groups.h): created by OverlayTask_New, a
 * C++ object of 0x50 bytes whose vtable (data_020df548) starts it with OverlayTask_Init, runs
 * OverlayTask_Update each frame and ends it with OverlayTask_End. Each frame it releases the
 * marked groups, loads the requested one and starts the loaded one; then, while no group is
 * being opened, it answers SELECT, X, Y and a touch in the touch screen's top right corner by
 * setting group 9's mode (group_params.h) and the control mode (control_mode.h). */
#ifndef CLEAN_MAIN_OVERLAY_TASK_H
#define CLEAN_MAIN_OVERLAY_TASK_H

#include "types.h"

/* The vtable slots the functions here fill. */
enum OverlayTaskSlot {
    OVERLAY_TASK_SLOT_INIT = 0,
    OVERLAY_TASK_SLOT_END = 3,
    OVERLAY_TASK_SLOT_UPDATE = 6,
    OVERLAY_TASK_SLOT_9 = 9,
    OVERLAY_TASK_SLOT_DESTRUCT = 16,
    OVERLAY_TASK_SLOT_DESTRUCT_DELETE = 17,
};

typedef struct OverlayTask {
    const void *vtable;
    u8 base[0x4c]; /* the base class's fields (func_020ee660) */
} OverlayTask;

BOOL OverlayTask_Slot9(void);
BOOL OverlayTask_Update(void);
BOOL OverlayTask_End(void);
BOOL OverlayTask_Init(OverlayTask *self);
OverlayTask *OverlayTask_New(void);
OverlayTask *OverlayTask_Destruct(OverlayTask *self);
OverlayTask *OverlayTask_DestructDelete(OverlayTask *self);

#endif
