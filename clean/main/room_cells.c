/* The scenes' records of their cells (room_cells.h). */
#include "room_cells.h"

#include "clean.h"

static_assert(offsetof(RoomCells, steps) == 0x40, "RoomCells steps");
static_assert(sizeof(RoomCells) == 0x48, "RoomCells size");

extern int func_020b67e8(int scene);                /* whether the scene is a house room (1-5) */
extern int func_020b6818(int scene);                /* the house room's index (scene - 1), or -1 */
extern int func_02060ee0(void *records, int index); /* one of the records at data_021ebcd4, or 0 */
extern int func_02061220(int record);               /* the record's RoomCells (at 0x400) */
extern int func_020b6694(int scene);                /* whether the scene is 17-24 */
extern int func_020b66c4(int scene);                /* 0-7 for 17-24, else -1 */
extern int func_020b6744(int scene);                /* whether the scene is one of Nook's (26-31) */
extern int func_020b6774(int scene);                /* 0-5 for 26-31, else -1 */

extern u8 data_021ebcd4[];        /* the house rooms' records */
extern RoomCells data_021c89fc[]; /* scenes 17-24 */
extern RoomCells data_021c884c[]; /* Nook's scenes 26-31 */
extern RoomCells data_021c87b4;   /* scene 10 */
extern u8 data_020d20cc;          /* 17: the first scene of data_021c89fc */

#define SCENES_17_24 8
#define SCENES_NOOK 6

/* The step table's functions and the switch grid's. */
extern int func_020531fc(RoomCellSteps *steps, int x, int y);           /* forgets the cell's step */
extern int func_02053108(RoomCellSteps *steps, int x, int y, u32 step); /* keeps a step at the cell */
extern int func_02053278(RoomCellSteps *steps, int x, int y);           /* the cell's step, or -1 */
extern void func_020532d0(RoomCellSteps *steps);                        /* no step anywhere */
extern void func_02053300(RoomCellSteps *steps);                        /* the steps' destructor */
extern void func_02053314(u16 *grid, int x, int y, int on);             /* sets or clears the cell's bit */
extern int func_02053340(u16 *grid, int x, int y);                      /* the cell's bit */
extern void func_02053358(u16 *grid);                                   /* every bit set */
extern void func_0205336c(void *grid);                                  /* a grid's destructor */
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* func_02052e70: forgets the step at cell (x, y) of the scene's record; 0 without a record. */
int RoomCells_ClearStep(int x, int y, int scene)
{
    RoomCells *cells = RoomCells_ForScene(scene);
    if (cells == NULL) {
        return 0;
    }
    return RoomCells_ClearStepIn(cells, x, y);
}
CLEAN_AS(func_02052e70, RoomCells_ClearStep)

/* func_02052e98: keeps `step` at cell (x, y) of the scene's record; 0 without a record or when
 * it cannot be kept. */
int RoomCells_SetStep(int x, int y, int step, int scene)
{
    RoomCells *cells = RoomCells_ForScene(scene);
    if (cells == NULL) {
        return 0;
    }
    return RoomCells_SetStepIn(cells, x, y, step);
}
CLEAN_AS(func_02052e98, RoomCells_SetStep)

/* func_02052ec0: the step at cell (x, y) of the scene's record; -1 without a record or step. */
int RoomCells_GetStep(int x, int y, int scene)
{
    RoomCells *cells = RoomCells_ForScene(scene);
    if (cells == NULL) {
        return -1;
    }
    return RoomCells_GetStepIn(cells, x, y);
}
CLEAN_AS(func_02052ec0, RoomCells_GetStep)

/* func_02052ee8: sets the switch bit of cell (x, y) on `layer` of the scene's record to `on`;
 * nothing without a record. */
void RoomCells_SetSwitch(int x, int y, int layer, int on, u8 scene)
{
    RoomCells *cells = RoomCells_ForScene(scene);
    if (cells != NULL) {
        RoomCells_SetSwitchIn(cells, x, y, layer, (u8) on);
    }
}
CLEAN_AS(func_02052ee8, RoomCells_SetSwitch)

/* func_02052f14: the switch bit of cell (x, y) on `layer` of the scene's record; 0 without a
 * record. */
int RoomCells_GetSwitch(int x, int y, int layer, int scene)
{
    RoomCells *cells = RoomCells_ForScene(scene);
    if (cells == NULL) {
        return 0;
    }
    return RoomCells_GetSwitchIn(cells, x, y, layer);
}
CLEAN_AS(func_02052f14, RoomCells_GetSwitch)

/* func_02052f3c: the scene's record (room_cells.h), or NULL: a house room without its record,
 * or a scene without one. */
RoomCells *RoomCells_ForScene(int scene)
{
    if (func_020b67e8(scene)) {
        int record = func_02060ee0(data_021ebcd4, func_020b6818(scene));
        if (record != 0) {
            return (RoomCells *) (uintptr_t) (u32) func_02061220(record);
        }
    } else if (func_020b6694(scene)) {
        return &data_021c89fc[func_020b66c4(scene)];
    } else if (func_020b6744(scene)) {
        return &data_021c884c[func_020b6774(scene)];
    } else if (scene == ROOM_CELLS_SCENE_OTHER) {
        return &data_021c87b4;
    }
    return NULL;
}
CLEAN_AS(func_02052f3c, RoomCells_ForScene)

/* func_02052fb4 */
int RoomCells_ClearStepIn(RoomCells *cells, int x, int y)
{
    return func_020531fc(&cells->steps, x, y);
}
CLEAN_AS(func_02052fb4, RoomCells_ClearStepIn)

/* func_02052fc0 */
int RoomCells_SetStepIn(RoomCells *cells, int x, int y, int step)
{
    return func_02053108(&cells->steps, x, y, (u32) step);
}
CLEAN_AS(func_02052fc0, RoomCells_SetStepIn)

/* func_02052fd0 */
int RoomCells_GetStepIn(RoomCells *cells, int x, int y)
{
    return func_02053278(&cells->steps, x, y);
}
CLEAN_AS(func_02052fd0, RoomCells_GetStepIn)

/* func_02052fdc: resets the record of scene 17 + `index` (data_020d20cc holds the 17).
 * QUIRK: the scene is cut to 8 bits. */
int RoomCells_ResetByIndex(u8 index)
{
    return RoomCells_ResetScene((u8) (data_020d20cc + index));
}
CLEAN_AS(func_02052fdc, RoomCells_ResetByIndex)

/* func_02052ff4: resets the scene's record; 0 without one. */
int RoomCells_ResetScene(int scene)
{
    RoomCells *cells = RoomCells_ForScene(scene);
    if (cells == NULL) {
        return 0;
    }
    RoomCells_Reset(cells);
    return 1;
}
CLEAN_AS(func_02052ff4, RoomCells_ResetScene)

/* func_02053010: resets the records of scenes 17-24, Nook's and scene 10 (the house rooms keep
 * theirs). */
void RoomCells_ResetAll(void)
{
    for (int i = 0; i < SCENES_17_24; i++) {
        RoomCells_Reset(&data_021c89fc[i]);
    }
    for (int i = 0; i < SCENES_NOOK; i++) {
        RoomCells_Reset(&data_021c884c[i]);
    }
    RoomCells_ResetOther();
}
CLEAN_AS(func_02053010, RoomCells_ResetAll)

/* func_02053050: resets scene 10's record. */
void RoomCells_ResetOther(void)
{
    RoomCells_Reset(&data_021c87b4);
}
CLEAN_AS(func_02053050, RoomCells_ResetOther)

/* func_02053060: sets the switch bit of cell (x, y) on `layer` to `on`.
 * REQUIRES: layer is 0 or 1 (the ROM takes the grid at layer * 0x20 unchecked). */
void RoomCells_SetSwitchIn(RoomCells *cells, int x, int y, int layer, u8 on)
{
    func_02053314(cells->switches[layer], x, y, on);
}
CLEAN_AS(func_02053060, RoomCells_SetSwitchIn)

/* func_0205307c: the switch bit of cell (x, y) on `layer`.
 * REQUIRES: layer is 0 or 1 (the ROM takes the grid at layer * 0x20 unchecked). */
int RoomCells_GetSwitchIn(RoomCells *cells, int x, int y, int layer)
{
    return func_02053340(cells->switches[layer], x, y);
}
CLEAN_AS(func_0205307c, RoomCells_GetSwitchIn)

/* func_02053088: every switch bit set on both layers, and no step. */
void RoomCells_Reset(RoomCells *cells)
{
    for (int layer = 0; layer < ROOM_CELLS_LAYERS; layer++) {
        func_02053358(cells->switches[layer]);
    }
    func_020532d0(&cells->steps);
}
CLEAN_AS(func_02053088, RoomCells_Reset)

/* func_020530b0: the record's destructor: the steps', then each grid's (func_0205336c, handed
 * to __cxa_vec_cleanup). */
RoomCells *RoomCells_Destruct(RoomCells *cells)
{
    func_02053300(&cells->steps);
    __cxa_vec_cleanup(cells->switches, ROOM_CELLS_LAYERS, sizeof(cells->switches[0]), func_0205336c);
    return cells;
}
CLEAN_AS(func_020530b0, RoomCells_Destruct)
