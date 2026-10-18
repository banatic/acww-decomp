/* The scenes' records of their cells (room_cells.h). */
#include "room_cells.h"

#include "clean.h"
#include "house_record.h"
#include "scene_kinds.h"
#include "scene_query.h"

static_assert(offsetof(RoomCells, steps) == 0x40, "RoomCells steps");
static_assert(sizeof(RoomCells) == 0x48, "RoomCells size");

extern u8 data_021ebcd4[];        /* the house rooms' records */
extern RoomCells data_021c89fc[]; /* scenes 17-24 */
extern RoomCells data_021c884c[]; /* Nook's scenes 26-31 */
extern RoomCells data_021c87b4;   /* scene 10 */
extern u8 data_020d20cc;          /* 17: the first scene of data_021c89fc */

#define SCENES_17_24 8
#define SCENES_NOOK 6

/* The step table's functions and the switch grid's. */
extern void func_0205336c(void *grid); /* a grid's destructor */
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
    if (SceneKinds_IsHouseRoom(scene)) {
        int record =
            (int) (uintptr_t) HouseRecord_Room((HouseRecord *) (void *) data_021ebcd4, SceneKinds_HouseRoomIndex(scene));
        if (record != 0) {
            return (RoomCells *) (uintptr_t) (u32) HouseRecord_RoomCells((HouseRoom *) (uintptr_t) record);
        }
    } else if (SceneQuery_In11(scene)) {
        return &data_021c89fc[SceneQuery_IndexIn11(scene)];
    } else if (SceneQuery_InNook(scene)) {
        return &data_021c884c[SceneQuery_IndexInNook(scene)];
    } else if (scene == ROOM_CELLS_SCENE_OTHER) {
        return &data_021c87b4;
    }
    return NULL;
}
CLEAN_AS(func_02052f3c, RoomCells_ForScene)

/* func_02052fb4 */
int RoomCells_ClearStepIn(RoomCells *cells, int x, int y)
{
    return RoomCellSteps_Clear(&cells->steps, x, y);
}
CLEAN_AS(func_02052fb4, RoomCells_ClearStepIn)

/* func_02052fc0 */
int RoomCells_SetStepIn(RoomCells *cells, int x, int y, int step)
{
    return RoomCellSteps_Set(&cells->steps, x, y, (u32) step);
}
CLEAN_AS(func_02052fc0, RoomCells_SetStepIn)

/* func_02052fd0 */
int RoomCells_GetStepIn(RoomCells *cells, int x, int y)
{
    return RoomCellSteps_Get(&cells->steps, x, y);
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
    RoomSwitchGrid_Set(cells->switches[layer], x, y, on);
}
CLEAN_AS(func_02053060, RoomCells_SetSwitchIn)

/* func_0205307c: the switch bit of cell (x, y) on `layer`.
 * REQUIRES: layer is 0 or 1 (the ROM takes the grid at layer * 0x20 unchecked). */
int RoomCells_GetSwitchIn(RoomCells *cells, int x, int y, int layer)
{
    return RoomSwitchGrid_Get(cells->switches[layer], x, y);
}
CLEAN_AS(func_0205307c, RoomCells_GetSwitchIn)

/* func_02053088: every switch bit set on both layers, and no step. */
void RoomCells_Reset(RoomCells *cells)
{
    for (int layer = 0; layer < ROOM_CELLS_LAYERS; layer++) {
        RoomSwitchGrid_SetAll(cells->switches[layer]);
    }
    RoomCellSteps_Reset(&cells->steps);
}
CLEAN_AS(func_02053088, RoomCells_Reset)

/* func_020530b0: the record's destructor: the steps', then each grid's (func_0205336c, handed
 * to __cxa_vec_cleanup). */
RoomCells *RoomCells_Destruct(RoomCells *cells)
{
    RoomCellSteps_Destruct(&cells->steps);
    __cxa_vec_cleanup(cells->switches, ROOM_CELLS_LAYERS, sizeof(cells->switches[0]), func_0205336c);
    return cells;
}
CLEAN_AS(func_020530b0, RoomCells_Destruct)

/* The game's constructor and destructors handed to __cxa_vec_ctor and __cxa_vec_cleanup. */
extern void func_02053370(void *grid);  /* a grid's constructor */
extern void func_020530b0(void *cells); /* a record's destructor */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

/* func_020530d4: the record's constructor: each grid's (func_02053370, handed to
 * __cxa_vec_ctor), the steps', then a reset. */
RoomCells *RoomCells_Construct(RoomCells *cells)
{
    __cxa_vec_ctor(cells->switches, ROOM_CELLS_LAYERS, sizeof(cells->switches[0]), func_02053370, func_0205336c);
    RoomCellSteps_Construct(&cells->steps);
    RoomCells_Reset(cells);
    return cells;
}
CLEAN_AS(func_020530d4, RoomCells_Construct)

/* Whether entry `i` of the steps is in use. */
static int step_entry_used(const RoomCellSteps *steps, u32 i)
{
    return (steps->used >> i) & 1;
}

/* Whether entry `i` is for cell (x, y). */
static int step_entry_is(const RoomCellSteps *steps, u32 i, int x, int y)
{
    return x == (steps->cells[i] & 0xf) && y == (steps->cells[i] >> 4);
}

/* The bit position of entry `i`'s step within its byte. */
static int step_shift(u32 i)
{
    return (int) (i & 1) * 4;
}

/* Stores `step` (below 16) as entry `i`'s step. */
static void step_entry_store(RoomCellSteps *steps, u32 i, u32 step)
{
    int shift = step_shift(i);
    steps->steps[i / 2] = (u8) ((steps->steps[i / 2] & ~(0xf << shift)) | (step << shift));
}

/* func_02053108: keeps `step` at cell (x, y): in the cell's entry when it has one, else in the
 * first free entry, which then takes x and y (each cut to 4 bits). 0 for a step of 16 or more
 * or when all four entries are in use by other cells. */
int RoomCellSteps_Set(RoomCellSteps *steps, int x, int y, unsigned int step)
{
    if (step >= 16) {
        return 0;
    }
    if (RoomCellSteps_Get(steps, x, y) == -1) {
        for (u32 i = 0; i < ROOM_CELLS_STEP_CELLS; i++) {
            if (!step_entry_used(steps, i)) {
                steps->cells[i] = (u8) ((x & 0xf) | (y & 0xf) << 4);
                step_entry_store(steps, i, step);
                steps->used |= (u8) (1 << i);
                return 1;
            }
        }
    } else {
        for (u32 i = 0; i < ROOM_CELLS_STEP_CELLS; i++) {
            if (step_entry_used(steps, i) && step_entry_is(steps, i, x, y)) {
                step_entry_store(steps, i, step);
                return 1;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_02053108, RoomCellSteps_Set)

/* func_020531fc: forgets the step of cell (x, y) and frees its entry; whether it had one. */
int RoomCellSteps_Clear(RoomCellSteps *steps, int x, int y)
{
    for (u32 i = 0; i < ROOM_CELLS_STEP_CELLS; i++) {
        if (step_entry_used(steps, i) && step_entry_is(steps, i, x, y)) {
            steps->cells[i] = 0;
            steps->used &= (u8) ~(1 << i);
            steps->steps[i / 2] &= (u8) ~(0xf << step_shift(i));
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_020531fc, RoomCellSteps_Clear)

/* func_02053278: the step of cell (x, y), or -1 when it keeps none. */
int RoomCellSteps_Get(RoomCellSteps *steps, int x, int y)
{
    for (u32 i = 0; i < ROOM_CELLS_STEP_CELLS; i++) {
        if (step_entry_used(steps, i) && step_entry_is(steps, i, x, y)) {
            return (steps->steps[i / 2] >> step_shift(i)) & 0xf;
        }
    }
    return -1;
}
CLEAN_AS(func_02053278, RoomCellSteps_Get)

/* func_020532d0: no entry in use and no step (unk_07 is left alone). */
void RoomCellSteps_Reset(RoomCellSteps *steps)
{
    for (u32 i = 0; i < ROOM_CELLS_STEP_CELLS; i++) {
        steps->cells[i] = 0;
    }
    steps->used = 0;
    for (u32 i = 0; i < ROOM_CELLS_STEP_CELLS / 2; i++) {
        steps->steps[i] = 0;
    }
}
CLEAN_AS(func_020532d0, RoomCellSteps_Reset)

/* func_02053300: nothing to take down. */
void RoomCellSteps_Destruct(RoomCellSteps *steps)
{
    (void) steps;
}
CLEAN_AS(func_02053300, RoomCellSteps_Destruct)

/* func_02053304 */
RoomCellSteps *RoomCellSteps_Construct(RoomCellSteps *steps)
{
    RoomCellSteps_Reset(steps);
    return steps;
}
CLEAN_AS(func_02053304, RoomCellSteps_Construct)

/* func_02053314: sets (`on` not 0) or clears the bit of cell (x, y) of a switch grid; x and y
 * are cut to 4 bits. */
void RoomSwitchGrid_Set(u16 *grid, int x, int y, int on)
{
    u16 bit = (u16) (1 << (x & 0xf));
    if (on) {
        grid[y & 0xf] |= bit;
    } else {
        grid[y & 0xf] &= (u16) ~bit;
    }
}
CLEAN_AS(func_02053314, RoomSwitchGrid_Set)

/* func_02053340: the bit of cell (x, y), x and y cut to 4 bits. */
int RoomSwitchGrid_Get(u16 *grid, int x, int y)
{
    return (grid[y & 0xf] >> (x & 0xf)) & 1;
}
CLEAN_AS(func_02053340, RoomSwitchGrid_Get)

/* func_02053358: every bit set. */
void RoomSwitchGrid_SetAll(u16 *grid)
{
    for (u32 row = 0; row < ROOM_CELLS_ROWS; row++) {
        grid[row] = 0xffff;
    }
}
CLEAN_AS(func_02053358, RoomSwitchGrid_SetAll)

/* func_0205336c: nothing to take down. */
void RoomSwitchGrid_Destruct(void *grid)
{
    (void) grid;
}
CLEAN_AS(func_0205336c, RoomSwitchGrid_Destruct)

/* func_02053370: a grid starts with every bit set. */
u16 *RoomSwitchGrid_Construct(u16 *grid)
{
    RoomSwitchGrid_SetAll(grid);
    return grid;
}
CLEAN_AS(func_02053370, RoomSwitchGrid_Construct)

/* func_020534ac: the destructor registered for Nook's scenes' records at start-up. */
void RoomCells_DestructNookRecords(void)
{
    __cxa_vec_cleanup(data_021c884c, SCENES_NOOK, sizeof(RoomCells), func_020530b0);
}
CLEAN_AS(func_020534ac, RoomCells_DestructNookRecords)

/* func_020534cc: the destructor registered for the records of scenes 17-24 at start-up. */
void RoomCells_Destruct17To24Records(void)
{
    __cxa_vec_cleanup(data_021c89fc, SCENES_17_24, sizeof(RoomCells), func_020530b0);
}
CLEAN_AS(func_020534cc, RoomCells_Destruct17To24Records)
