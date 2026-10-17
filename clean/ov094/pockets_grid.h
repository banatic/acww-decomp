/* Overlay 094's grid object (vtable data_ov094_0229bf90, 0xa60 bytes), the first of the
 * objects the pockets scenes keep (at 0x358 of ov096's PocketsScreen, 0xcc of ov099's
 * PocketsView, 0x2fc of ov105's LetterStorage). It draws the scenes' places as OBJs on the sub
 * screen (one OBJ of data_ov094_0229bfb0 per place, PocketsGrid_PlaceObj) and the item the
 * cursor holds (the OBJ data_ov094_0229bf70), whose pick-up is animated
 * (PocketsGrid_StepPickUp): frames of an animation (the object at 0x184) copied into the held
 * OBJ's characters, and a scale from 1/10 to full size.
 *
 * Three sets of 64 bits hold, per place: whether it holds something (`filled`, drawn), whether
 * it has a mark (`marked`, OBJ data_ov094_0229bfa8) and whether it is shown dimmed (`dimmed`,
 * palette 14). A filled place is drawn with OBJ data_ov094_0229bf98 round it; the place the
 * cursor lifts (`lifted`) is raised by an offset (data_ov094_0229bc58 by `lift`, which counts
 * down: 5, 3, then 2 pixels), with data_ov094_0229bfa0 (the tile of data_ov094_0229bf98, 2
 * pixels lower, palette 1) under it. */
#ifndef CLEAN_OV094_POCKETS_GRID_H
#define CLEAN_OV094_POCKETS_GRID_H

#include "main/layer_load_task.h"
#include "main/oam_buffer.h"
#include "types.h"

#define POCKETS_GRID_TASKS 3
#define POCKETS_GRID_NO_PLACE 0x23
#define POCKETS_GRID_FULL_SIZE 10 /* `held_size`, in tenths */

/* A set of 64 bits (two words, bit n in word n / 32). */
typedef struct PocketsBits {
    u32 words[2];
} PocketsBits;

typedef struct PocketsGrid {
    u32 vtable;                              /* 0x000: data_ov094_0229bf90 */
    u8 held_chars[3][0x80];                  /* 0x004: characters copied for the held OBJ, one per task */
    u8 animation[0x808];                     /* 0x184: the pick-up's frames (func_ov094_0229b0d4, func_ov094_0229b048) */
    LayerTaskPair tasks[POCKETS_GRID_TASKS]; /* 0x98c */
    u32 unk_a34;                             /* 0xa34 */
    PocketsBits filled;                      /* 0xa38 */
    PocketsBits marked;                      /* 0xa40 */
    PocketsBits dimmed;                      /* 0xa48 */
    s32 priority;                            /* 0xa50: the OBJs' priority */
    u16 held_item;                           /* 0xa54 */
    u8 lifted;                               /* 0xa56: the place lifted, POCKETS_GRID_NO_PLACE for none */
    u8 lift;                                 /* 0xa57: an index into the lift's offsets, counting down */
    u8 tasks_used;                           /* 0xa58: this frame's tasks */
    u8 held_size;                            /* 0xa59: the held OBJ's size in tenths, 0 hidden */
    u8 pickup_step;                          /* 0xa5a */
    u8 pickup_variant;                       /* 0xa5b: 0 for an item of state 1, else 1 */
    u8 held_lowered;                         /* 0xa5c: data_ov094_0229bfa0 is drawn under the held item */
    u8 pad_a5d[3];
} PocketsGrid;

int PocketsBits_Test(PocketsBits *bits, int bit);
void PocketsBits_Clear(PocketsBits *bits, int bit);
void PocketsBits_Set(PocketsBits *bits, int bit);
void PocketsBits_ClearAll(PocketsBits *bits);
u8 PocketsGrid_PickUpSize(PocketsGrid *grid);
int PocketsGrid_StepPickUp(PocketsGrid *grid);
void PocketsGrid_EndPickUp(PocketsGrid *grid);
void PocketsGrid_StartPickUp(PocketsGrid *grid, u16 item, int state);
int PocketsGrid_NextTask(PocketsGrid *grid);
void PocketsGrid_EndTasks(PocketsGrid *grid);
int PocketsGrid_SizeScale(unsigned int size);
OamEntry *PocketsGrid_PlaceObj(int unused, int place);
void PocketsGrid_DrawPlace(PocketsGrid *grid, const OamEntry *obj, int place, int x, int y);
int PocketsGrid_DrawLowered(PocketsGrid *grid, int x, int y);
void PocketsGrid_DrawSurround(PocketsGrid *grid, int x, int y, int palette);
int PocketsGrid_DrawMark(PocketsGrid *grid, int x, int y);

#endif
