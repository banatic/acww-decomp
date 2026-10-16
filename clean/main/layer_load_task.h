/* The main loop queue's tasks (transfer_task.h, kinds 4 to 9): loads of a 2D layer's
 * characters, screen or palettes (display_layers.h) run from the main loop when there are lines
 * enough left for them.
 *
 * A LayerTask (vtable data_020e5934, 0x24 bytes) holds one load; a LayerTaskPair (vtable
 * data_020e5944, 0x38 bytes) a second one after it: two ranges of characters, or characters
 * and a palette. Their vtable's second slot resets the task.
 *
 * Each queue function first takes the task off the queue and resets it (through the vtable),
 * then sets it up, marks it queued and queues it (priority 4); it answers 1 when it is queued
 * (always, the queue takes any task), else resets it through the vtable and answers 0. */
#ifndef CLEAN_MAIN_LAYER_LOAD_TASK_H
#define CLEAN_MAIN_LAYER_LOAD_TASK_H

#include "transfer_task.h"
#include "types.h"

/* One load into a layer (enum DisplayLayer); what follows `layer` depends on the task's kind. */
typedef struct LayerLoad {
    u32 data; /* 0x00: the address of the characters, screen or palettes */
    u8 layer; /* 0x04 */
    union {
        struct {
            u32 data_first; /* 0x08: the first character at `data` */
            u32 first;      /* 0x0c: the characters loaded, from 16-colour character units */
            u32 last;       /* 0x10 */
        } chars;
        struct {
            u32 size;   /* 0x08: in bytes */
            u32 offset; /* 0x0c: in the layer's screen, in bytes */
        } screen;
        struct {
            u32 index; /* 0x08: the palette, also the first palette at `data` */
        } palette;
        struct {
            u32 first; /* 0x08: also the first palette at `data` */
            u32 last;  /* 0x0c */
        } palettes;
    } u;
} LayerLoad;

typedef struct LayerTask {
    TransferTask base;
    LayerLoad load; /* 0x10 */
} LayerTask;

typedef struct LayerTaskPair {
    LayerTask first;
    LayerLoad second; /* 0x24 */
} LayerTaskPair;

int LayerTask_QueueCharsAndPalette(LayerTaskPair *task, int data, int layer, int data_first, int first, int last,
                                   int palette_data, u8 palette);
int LayerTask_QueueTwoChars(LayerTaskPair *task, int data, int second_data, int layer, int first, int last, int second_first,
                            int second_last);
int LayerTask_RunPair(LayerTaskPair *task);
void LayerTask_ResetPair(LayerTaskPair *task);
LayerTaskPair *LayerTask_ConstructPair(LayerTaskPair *task);
int LayerTask_QueuePalettes(LayerTask *task, int data, int layer, int first, u8 last);
int LayerTask_QueuePalette(LayerTask *task, int data, int layer, int palette);
int LayerTask_QueueScreen(LayerTask *task, int data, int layer, int size, int offset);
int LayerTask_QueueChars(LayerTask *task, int data, int layer, int data_first, int first, int last);
void LayerTask_Prepare(LayerTask *task);
int LayerTask_Run(LayerTask *task);
void LayerTask_End(LayerTask *task);
void LayerTask_Reset(LayerTask *task);
LayerTask *LayerTask_Construct(LayerTask *task);
LayerTask *LayerTask_ConstructBase(LayerTask *task);
int LayerLoad_PalettesLines(void);
void LayerLoad_LoadPalettes(LayerLoad *load);
void LayerLoad_SetPalettes(LayerLoad *load, int data, u8 layer, int first, u8 last);
int LayerLoad_PaletteLines(LayerLoad *load);
void LayerLoad_LoadPalette(LayerLoad *load);
void LayerLoad_SetPalette(LayerLoad *load, int data, int layer, int palette);
int LayerLoad_ScreenLines(void);
void LayerLoad_LoadScreen(LayerLoad *load);
void LayerLoad_SetScreen(LayerLoad *load, int data, char layer, int size, int offset);
unsigned int LayerLoad_CharsLines(LayerLoad *load);
unsigned int LayerLoad_LoadChars(LayerLoad *load);
void LayerLoad_SetChars(LayerLoad *load, int data, u8 layer, int data_first, int first, int last);
void LayerLoad_Clear(LayerLoad *load);

#endif
