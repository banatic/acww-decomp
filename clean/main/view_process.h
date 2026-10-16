/* A process that holds a view matrix and makes it the 3D view when it is drawn (vtable
 * data_020e58cc over the game's process class data_020da13c). The field camera
 * (camera_control.h) is one: its own draw ends with ViewProcess_Draw. */
#ifndef CLEAN_MAIN_VIEW_PROCESS_H
#define CLEAN_MAIN_VIEW_PROCESS_H

#include "autoload_2/matrix.h"
#include "autoload_2/process.h"
#include "types.h"

typedef struct ViewProcess {
    Process base;
    Mtx43 view; /* 0x50 */
} ViewProcess;

ViewProcess *ViewProcess_Destroy(ViewProcess *self);
ViewProcess *ViewProcess_Delete(ViewProcess *self);
int ViewProcess_Draw(ViewProcess *self);

#endif
