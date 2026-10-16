/* What every task of the transfer queues (transfer_queue.h) starts from: the base class's
 * constructor (vtable data_020e5954, both slots empty) and the reset its subclasses share.
 *
 * A task's kind says what it copies. Kinds 0 to 3 are copies into the 3D engine's texture and
 * palette VRAM, queued for the VBlank (vram_copy_task.h); kinds 4 to 9 are loads of the 2D
 * layers' characters, screens and palettes, queued for the main loop (layer_load_task.h). */
#ifndef CLEAN_MAIN_TRANSFER_TASK_H
#define CLEAN_MAIN_TRANSFER_TASK_H

#include "transfer_queue.h"
#include "types.h"

/* TransferTask.state before the task is first set up (TransferTaskState goes on from here). */
#define TRANSFER_TASK_IDLE 0

/* The lowest priority: a task constructed but never set up queues after all others. */
#define TRANSFER_TASK_PRIORITY_LAST 0xff

/* The vtable slot of the subclass's reset, called when a task is taken off its queue (the
 * VBlank's classes leave it empty). */
#define TRANSFER_TASK_SLOT_RESET 1

/* TransferTask.kind. */
enum TransferTaskKind {
    TRANSFER_KIND_TEXTURE = 0,          /* a texture resource's images and palettes */
    TRANSFER_KIND_TEXTURE_IMAGE = 1,    /* a copy into texture VRAM */
    TRANSFER_KIND_TEXTURE_PALETTE = 2,  /* a copy into texture palette VRAM */
    TRANSFER_KIND_MATERIAL = 3,         /* a material's texture image and its palette */
    TRANSFER_KIND_LAYER_CHARS = 4,      /* a range of a layer's characters */
    TRANSFER_KIND_LAYER_SCREEN = 5,     /* a layer's screen */
    TRANSFER_KIND_LAYER_PALETTE = 6,    /* one of a layer's palettes */
    TRANSFER_KIND_LAYER_PALETTES = 7,   /* a range of a layer's palettes */
    TRANSFER_KIND_LAYER_CHARS_TWO = 8,  /* two ranges of characters */
    TRANSFER_KIND_LAYER_CHARS_PLTT = 9, /* a range of characters and one palette */
    TRANSFER_KIND_NONE = 10
};

void TransferTask_Reset(TransferTask *task);
void TransferTask_Construct(TransferTask *task);

#endif
