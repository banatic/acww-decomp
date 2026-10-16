/* The main loop queue's loads into the 2D layers (layer_load_task.h). */
#include "layer_load_task.h"

#include "clean.h"
#include "display_layers.h"

static_assert(offsetof(LayerLoad, u.chars.last) == 0x10, "LayerLoad");
static_assert(sizeof(LayerLoad) == 0x14, "LayerLoad");
static_assert(offsetof(LayerTask, load) == 0x10, "LayerTask");
static_assert(offsetof(LayerTaskPair, second) == 0x24, "LayerTaskPair");
static_assert(sizeof(LayerTaskPair) == 0x38, "LayerTaskPair");

extern const u32 data_020e5934[]; /* LayerTask's vtable */
extern const u32 data_020e5944[]; /* LayerTaskPair's */

/* The priority every queue function gives its task. */
#define LAYER_TASK_PRIORITY 4

/* LayerLoad.layer while there is no load. */
#define LAYER_LOAD_NO_LAYER 0xff

/* The 16-colour characters one scan line stands for (as a shift). */
#define LAYER_LOAD_CHARS_LINE_SHIFT 6

typedef void LayerTaskReset(LayerTask *task);

/* The task's reset through its vtable (LayerTask_Reset or LayerTask_ResetPair). */
static void reset_virtual(LayerTask *task)
{
    LayerTaskReset *reset = (LayerTaskReset *) (uintptr_t) task->base.vtable[TRANSFER_TASK_SLOT_RESET];
    reset(task);
}

/* Queued on the main loop's queue at priority 4 once set up; 1 when queued, else reset. */
static int queue(LayerTask *task)
{
    task->base.priority = LAYER_TASK_PRIORITY;
    if (TransferQueue_QueueMain(&task->base) != 0) {
        return 1;
    }
    reset_virtual(task);
    return 0;
}

/* func_020b99a0: queued to load characters `first` to `last` of `layer` from `data` (which
 * starts at character `data_first`), and palette `palette` of the same layer from
 * `palette_data` (which starts at that palette); 1 when queued. */
int LayerTask_QueueCharsAndPalette(LayerTaskPair *task, int data, int layer, int data_first, int first, int last,
                                   int palette_data, u8 palette)
{
    LayerTask_Prepare(&task->first);
    task->first.base.kind = TRANSFER_KIND_LAYER_CHARS_PLTT;
    LayerLoad_SetChars(&task->first.load, data, (u8) layer, data_first, first, last);
    task->first.base.lines = (u8) LayerLoad_CharsLines(&task->first.load);
    LayerLoad_SetPalette(&task->second, palette_data, layer, palette);
    task->first.base.lines = (u8) (LayerLoad_PaletteLines(&task->second) + task->first.base.lines);
    return queue(&task->first);
}
CLEAN_AS(func_020b99a0, LayerTask_QueueCharsAndPalette)

/* func_020b9a18: queued to load characters `first` to `last` of `layer` from `data`, and
 * `second_first` to `second_last` from `second_data` (each block starting at the first character
 * it loads); 1 when queued. */
int LayerTask_QueueTwoChars(LayerTaskPair *task, int data, int second_data, int layer, int first, int last, int second_first,
                            int second_last)
{
    LayerTask_Prepare(&task->first);
    task->first.base.kind = TRANSFER_KIND_LAYER_CHARS_TWO;
    LayerLoad_SetChars(&task->first.load, data, (u8) layer, first, first, last);
    task->first.base.lines = (u8) LayerLoad_CharsLines(&task->first.load);
    LayerLoad_SetChars(&task->second, second_data, (u8) layer, second_first, second_first, second_last);
    task->first.base.lines = (u8) (LayerLoad_CharsLines(&task->second) + task->first.base.lines);
    return queue(&task->first);
}
CLEAN_AS(func_020b9a18, LayerTask_QueueTwoChars)

/* func_020b9a90 (vtable slot 0): the load or loads its kind says; 0 for a kind it has none
 * for, else 1. */
int LayerTask_RunPair(LayerTaskPair *task)
{
    if (LayerTask_Run(&task->first) != 0) {
        return 1;
    }
    switch (task->first.base.kind) {
        case TRANSFER_KIND_LAYER_CHARS_TWO:
            LayerLoad_LoadChars(&task->first.load);
            LayerLoad_LoadChars(&task->second);
            return 1;
        case TRANSFER_KIND_LAYER_CHARS_PLTT:
            LayerLoad_LoadChars(&task->first.load);
            LayerLoad_LoadPalette(&task->second);
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_020b9a90, LayerTask_RunPair)

/* func_020b9adc (vtable slot 1) */
void LayerTask_ResetPair(LayerTaskPair *task)
{
    LayerTask_Reset(&task->first);
    LayerLoad_Clear(&task->second);
}
CLEAN_AS(func_020b9adc, LayerTask_ResetPair)

/* func_020b9af4: the constructor. */
LayerTaskPair *LayerTask_ConstructPair(LayerTaskPair *task)
{
    LayerTask_ConstructBase(&task->first);
    task->first.base.vtable = data_020e5944;
    LayerLoad_Clear(&task->second);
    return task;
}
CLEAN_AS(func_020b9af4, LayerTask_ConstructPair)

/* func_020b9b14: queued to load palettes `first` to `last` of `layer` from `data` (which starts
 * at palette `first`); 1 when queued. */
int LayerTask_QueuePalettes(LayerTask *task, int data, int layer, int first, u8 last)
{
    LayerTask_Prepare(task);
    task->base.kind = TRANSFER_KIND_LAYER_PALETTES;
    LayerLoad_SetPalettes(&task->load, data, (u8) layer, first, last);
    task->base.lines = (u8) LayerLoad_PalettesLines();
    return queue(task);
}
CLEAN_AS(func_020b9b14, LayerTask_QueuePalettes)

/* func_020b9b6c: queued to load palette `palette` of `layer` from `data` (which starts at that
 * palette); 1 when queued. */
int LayerTask_QueuePalette(LayerTask *task, int data, int layer, int palette)
{
    LayerTask_Prepare(task);
    task->base.kind = TRANSFER_KIND_LAYER_PALETTE;
    LayerLoad_SetPalette(&task->load, data, layer, palette);
    task->base.lines = (u8) LayerLoad_PaletteLines(&task->load);
    return queue(task);
}
CLEAN_AS(func_020b9b6c, LayerTask_QueuePalette)

/* func_020b9bbc: queued to load `size` bytes of `layer`'s screen at byte `offset` from `data`;
 * 1 when queued. */
int LayerTask_QueueScreen(LayerTask *task, int data, int layer, int size, int offset)
{
    LayerTask_Prepare(task);
    task->base.kind = TRANSFER_KIND_LAYER_SCREEN;
    LayerLoad_SetScreen(&task->load, data, (char) layer, size, offset);
    task->base.lines = (u8) LayerLoad_ScreenLines();
    return queue(task);
}
CLEAN_AS(func_020b9bbc, LayerTask_QueueScreen)

/* func_020b9c10: queued to load characters `first` to `last` of `layer` from `data` (which
 * starts at character `data_first`); 1 when queued. */
int LayerTask_QueueChars(LayerTask *task, int data, int layer, int data_first, int first, int last)
{
    LayerTask_Prepare(task);
    task->base.kind = TRANSFER_KIND_LAYER_CHARS;
    LayerLoad_SetChars(&task->load, data, (u8) layer, data_first, first, last);
    task->base.lines = (u8) LayerLoad_CharsLines(&task->load);
    return queue(task);
}
CLEAN_AS(func_020b9c10, LayerTask_QueueChars)

/* func_020b9c68: off the queue and reset, then marked queued. */
void LayerTask_Prepare(LayerTask *task)
{
    LayerTask_End(task);
    task->base.state = TRANSFER_TASK_QUEUED;
}
CLEAN_AS(func_020b9c68, LayerTask_Prepare)

/* func_020b9c7c (vtable slot 0): the load its kind says; 0 for a kind of two loads (or none),
 * else 1. */
int LayerTask_Run(LayerTask *task)
{
    switch (task->base.kind) {
        case TRANSFER_KIND_LAYER_CHARS:
            LayerLoad_LoadChars(&task->load);
            break;
        case TRANSFER_KIND_LAYER_SCREEN:
            LayerLoad_LoadScreen(&task->load);
            break;
        case TRANSFER_KIND_LAYER_PALETTE:
            LayerLoad_LoadPalette(&task->load);
            break;
        case TRANSFER_KIND_LAYER_PALETTES:
            LayerLoad_LoadPalettes(&task->load);
            break;
        default:
            return 0;
    }
    return 1;
}
CLEAN_AS(func_020b9c7c, LayerTask_Run)

/* func_020b9ccc: off the main loop's queue, then reset through the vtable. */
void LayerTask_End(LayerTask *task)
{
    TransferQueue_UnqueueMain(&task->base);
    reset_virtual(task);
}
CLEAN_AS(func_020b9ccc, LayerTask_End)

/* func_020b9ce4 (vtable slot 1) */
void LayerTask_Reset(LayerTask *task)
{
    TransferTask_Reset(&task->base);
    LayerLoad_Clear(&task->load);
}
CLEAN_AS(func_020b9ce4, LayerTask_Reset)

/* func_020b9cfc: the constructor (the same code as LayerTask_ConstructBase). */
LayerTask *LayerTask_Construct(LayerTask *task)
{
    TransferTask_Construct(&task->base);
    task->base.vtable = data_020e5934;
    LayerLoad_Clear(&task->load);
    return task;
}
CLEAN_AS(func_020b9cfc, LayerTask_Construct)

/* func_020b9d1c: the constructor LayerTask_ConstructPair builds on (the same code as
 * LayerTask_Construct). */
LayerTask *LayerTask_ConstructBase(LayerTask *task)
{
    TransferTask_Construct(&task->base);
    task->base.vtable = data_020e5934;
    LayerLoad_Clear(&task->load);
    return task;
}
CLEAN_AS(func_020b9d1c, LayerTask_ConstructBase)

/* func_020ba03c: a range of palettes needs one line. */
int LayerLoad_PalettesLines(void)
{
    return 1;
}
CLEAN_AS(func_020ba03c, LayerLoad_PalettesLines)

/* func_020ba040: palettes `first` to `last` (the low byte of each). */
void LayerLoad_LoadPalettes(LayerLoad *load)
{
    u8 first = (u8) load->u.palettes.first;
    DisplayLayer_LoadPalettes((u8 *) (uintptr_t) load->data, load->layer, first, first, (u8) load->u.palettes.last);
}
CLEAN_AS(func_020ba040, LayerLoad_LoadPalettes)

/* func_020ba064 */
void LayerLoad_SetPalettes(LayerLoad *load, int data, u8 layer, int first, u8 last)
{
    load->data = (u32) data;
    load->layer = layer;
    load->u.palettes.first = (u32) first;
    load->u.palettes.last = last;
}
CLEAN_AS(func_020ba064, LayerLoad_SetPalettes)

/* func_020ba078: a palette needs one line. */
int LayerLoad_PaletteLines(LayerLoad *load)
{
    (void) load;
    return 1;
}
CLEAN_AS(func_020ba078, LayerLoad_PaletteLines)

/* func_020ba07c: the one palette (the low byte of its number). */
void LayerLoad_LoadPalette(LayerLoad *load)
{
    u8 palette = (u8) load->u.palette.index;
    DisplayLayer_LoadPalettes((u8 *) (uintptr_t) load->data, load->layer, palette, palette, palette);
}
CLEAN_AS(func_020ba07c, LayerLoad_LoadPalette)

/* func_020ba09c */
void LayerLoad_SetPalette(LayerLoad *load, int data, int layer, int palette)
{
    load->data = (u32) data;
    load->layer = (u8) layer;
    load->u.palette.index = (u32) palette;
}
CLEAN_AS(func_020ba09c, LayerLoad_SetPalette)

/* func_020ba0a4: a screen needs one line. */
int LayerLoad_ScreenLines(void)
{
    return 1;
}
CLEAN_AS(func_020ba0a4, LayerLoad_ScreenLines)

/* func_020ba0a8 */
void LayerLoad_LoadScreen(LayerLoad *load)
{
    DisplayLayer_LoadScreen((void *) (uintptr_t) load->data, load->layer, (int) load->u.screen.size,
                            (int) load->u.screen.offset);
}
CLEAN_AS(func_020ba0a8, LayerLoad_LoadScreen)

/* func_020ba0c0 */
void LayerLoad_SetScreen(LayerLoad *load, int data, char layer, int size, int offset)
{
    load->data = (u32) data;
    load->layer = (u8) layer;
    load->u.screen.size = (u32) size;
    load->u.screen.offset = (u32) offset;
}
CLEAN_AS(func_020ba0c0, LayerLoad_SetScreen)

/* func_020ba0cc: the lines a range of characters needs: one for every 64 characters past the
 * first, rounded up, kept to a byte.
 * QUIRK: the count leaves out the first character, so a single character needs no line and 65
 * need one. */
unsigned int LayerLoad_CharsLines(LayerLoad *load)
{
    return ((load->u.chars.last - load->u.chars.first + 63) >> LAYER_LOAD_CHARS_LINE_SHIFT) & 0xff;
}
CLEAN_AS(func_020ba0cc, LayerLoad_CharsLines)

/* func_020ba0dc: DisplayLayer_LoadChars's answer (1). */
unsigned int LayerLoad_LoadChars(LayerLoad *load)
{
    return (unsigned int) DisplayLayer_LoadChars(load->data, load->layer, load->u.chars.data_first, load->u.chars.first,
                                                 load->u.chars.last);
}
CLEAN_AS(func_020ba0dc, LayerLoad_LoadChars)

/* func_020ba0f8 */
void LayerLoad_SetChars(LayerLoad *load, int data, u8 layer, int data_first, int first, int last)
{
    load->data = (u32) data;
    load->layer = layer;
    load->u.chars.data_first = (u32) data_first;
    load->u.chars.first = (u32) first;
    load->u.chars.last = (u32) last;
}
CLEAN_AS(func_020ba0f8, LayerLoad_SetChars)

/* func_020ba108: no load, no layer. */
void LayerLoad_Clear(LayerLoad *load)
{
    load->data = 0;
    load->layer = LAYER_LOAD_NO_LAYER;
    load->u.chars.data_first = 0;
    load->u.chars.first = 0;
    load->u.chars.last = 0;
}
CLEAN_AS(func_020ba108, LayerLoad_Clear)
