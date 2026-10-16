/* A scene's record of its cells (RoomCells, 0x48 bytes): for each of the two layers of the
 * room's map (0 the floor, 1 on top of an object) one switch bit per cell, and up to four cells
 * that keep a 4-bit step.
 *
 * The scenes with a record (RoomCells_ForScene): the player's house rooms 1-5 (func_020b67e8)
 * at 0x400 in their records at data_021ebcd4, the scenes 17-24 (func_020b6694) in
 * data_021c89fc, Nook's scenes 26-31 (func_020b6744) in data_021c884c, and scene 10 in
 * data_021c87b4.
 *
 * The room objects of overlay 4 keep their switch at their cell (room_object_parts.c,
 * Switch_Save and Switch_Load), and some their step (room_object_02252ba8.c). A reset record
 * has every switch bit set and no step. */
#ifndef CLEAN_MAIN_ROOM_CELLS_H
#define CLEAN_MAIN_ROOM_CELLS_H

#include "types.h"

#define ROOM_CELLS_LAYERS 2
#define ROOM_CELLS_ROWS 16        /* a halfword per row (y), a bit per column (x) */
#define ROOM_CELLS_STEP_CELLS 4   /* the cells that can keep a step */
#define ROOM_CELLS_SCENE_OTHER 10 /* the one scene with a record of its own */

/* The cells that keep a step: each cell's x in its low and y in its high nibble, a bit per
 * entry for the entries in use, and the steps two to a byte (entry 0 in the low nibble). */
typedef struct RoomCellSteps {
    u8 cells[ROOM_CELLS_STEP_CELLS];
    u8 used;
    u8 steps[ROOM_CELLS_STEP_CELLS / 2];
    u8 unk_07;
} RoomCellSteps;

typedef struct RoomCells {
    u16 switches[ROOM_CELLS_LAYERS][ROOM_CELLS_ROWS]; /* 0x00 */
    RoomCellSteps steps;                              /* 0x40 */
} RoomCells;

int RoomCells_ClearStep(int x, int y, int scene);
int RoomCells_SetStep(int x, int y, int step, int scene);
int RoomCells_GetStep(int x, int y, int scene);
void RoomCells_SetSwitch(int x, int y, int layer, int on, u8 scene);
int RoomCells_GetSwitch(int x, int y, int layer, int scene);
RoomCells *RoomCells_ForScene(int scene);
int RoomCells_ClearStepIn(RoomCells *cells, int x, int y);
int RoomCells_SetStepIn(RoomCells *cells, int x, int y, int step);
int RoomCells_GetStepIn(RoomCells *cells, int x, int y);
int RoomCells_ResetByIndex(u8 index);
int RoomCells_ResetScene(int scene);
void RoomCells_ResetAll(void);
void RoomCells_ResetOther(void);
void RoomCells_SetSwitchIn(RoomCells *cells, int x, int y, int layer, u8 on);
int RoomCells_GetSwitchIn(RoomCells *cells, int x, int y, int layer);
void RoomCells_Reset(RoomCells *cells);
RoomCells *RoomCells_Destruct(RoomCells *cells);

#endif
