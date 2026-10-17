/* Overlay 094's grid object (pockets_grid.h): its sets of bits, the held item's pick-up and
 * the drawing of a place. */
#include "pockets_grid.h"

#include "clean.h"
#include "main/state_flags.h"

static_assert(offsetof(PocketsGrid, animation) == 0x184 && offsetof(PocketsGrid, tasks) == 0x98c, "grid");
static_assert(offsetof(PocketsGrid, filled) == 0xa38 && offsetof(PocketsGrid, marked) == 0xa40, "grid bits");
static_assert(offsetof(PocketsGrid, dimmed) == 0xa48 && offsetof(PocketsGrid, priority) == 0xa50, "grid bits");
static_assert(offsetof(PocketsGrid, held_item) == 0xa54 && offsetof(PocketsGrid, tasks_used) == 0xa58, "grid");
static_assert(offsetof(PocketsGrid, held_lowered) == 0xa5c && sizeof(PocketsGrid) == 0xa60, "grid size");
static_assert(sizeof(OamEntry) == 8, "OBJ");

/* The sizes of the pick-up's steps 6 to 11 (8, 4, 0, 3, 7, 10 tenths; step 8 sets 0 itself). */
extern const u8 data_ov094_0229bc48[];
/* The animation frames of steps 0 to 5 (0, none, 1, 2, 3, none). */
extern const u8 data_ov094_0229bc50[];
/* The scales of sizes 0 to 9 (10 / size in 20.12 fixed point; 0 for size 0). */
extern const s32 data_ov094_0229bc64[];
/* The held item's OBJ; the place OBJs; the OBJs drawn round a filled place, under a lifted one
 * and on a marked one (pockets_grid.h). */
extern OamEntry data_ov094_0229bf70;
extern OamEntry data_ov094_0229bfb0[];
extern const OamEntry data_ov094_0229bf98;
extern const OamEntry data_ov094_0229bfa0;
extern const OamEntry data_ov094_0229bfa8;

/* The rest of the grid (overlay 094's code). */
extern void *func_ov094_0229b048(char *animation, unsigned int frame, unsigned int variant);
extern void func_ov094_0229a8cc(void *grid, OamEntry *obj, void *chars, int palette);
extern void func_ov094_0229a99c(void *grid, int item, int unused);
extern int func_ov094_0229ab7c(unsigned char *grid, unsigned char place);
extern void *func_ov094_0229ab68(void *grid);
extern int func_ov094_0229a8bc(int grid, int place);

#define POCKETS_GRID_PICKUP_FRAMES 6 /* steps 0 to 5 */
#define POCKETS_GRID_PICKUP_HIDDEN 8 /* the step that sets the held OBJ's item */
#define POCKETS_GRID_PICKUP_END 12
#define POCKETS_GRID_NO_FRAME 0xff
#define POCKETS_GRID_HELD_PALETTE 8
#define POCKETS_GRID_DIMMED_PALETTE 0xe
#define POCKETS_GRID_OWN_PALETTE (-1)
#define POCKETS_GRID_SIZES 10
#define POCKETS_GRID_SCALE_ONE 0x1000
#define POCKETS_GRID_OBJ_MARGIN 8 /* the 32 x 32 OBJs round a 16 x 16 one */

/* func_ov094_0229a328. REQUIRES: `bit` in 0-63 (the places use 0-0x22). */
int PocketsBits_Test(PocketsBits *bits, int bit)
{
    return (bits->words[bit >> 5] & (1u << (bit & 31))) != 0;
}
CLEAN_AS(func_ov094_0229a328, PocketsBits_Test)

/* func_ov094_0229a34c. REQUIRES: `bit` in 0-63. */
void PocketsBits_Clear(PocketsBits *bits, int bit)
{
    bits->words[bit >> 5] &= ~(1u << (bit & 31));
}
CLEAN_AS(func_ov094_0229a34c, PocketsBits_Clear)

/* func_ov094_0229a36c. REQUIRES: `bit` in 0-63. */
void PocketsBits_Set(PocketsBits *bits, int bit)
{
    bits->words[bit >> 5] |= 1u << (bit & 31);
}
CLEAN_AS(func_ov094_0229a36c, PocketsBits_Set)

/* func_ov094_0229a38c */
void PocketsBits_ClearAll(PocketsBits *bits)
{
    for (int i = 0; i < 2; i++) {
        bits->words[i] = 0;
    }
}
CLEAN_AS(func_ov094_0229a38c, PocketsBits_ClearAll)

/* func_ov094_0229a39c: the held OBJ's size at this step of the pick-up. REQUIRES: the step is
 * 6 to 11 (PocketsGrid_StepPickUp's only calls). */
u8 PocketsGrid_PickUpSize(PocketsGrid *grid)
{
    return data_ov094_0229bc48[grid->pickup_step - POCKETS_GRID_PICKUP_FRAMES];
}
CLEAN_AS(func_ov094_0229a39c, PocketsGrid_PickUpSize)

/* func_ov094_0229a3b0: a step of the pick-up; 1 once it is over. Steps 0 to 5 copy the
 * animation's frames into the held OBJ (in palette 8), steps 6, 7 and 9 to 11 size it, step 8
 * hides it and gives it the held item; step 12 ends it at full size. */
int PocketsGrid_StepPickUp(PocketsGrid *grid)
{
    u8 step = grid->pickup_step;

    if (step < POCKETS_GRID_PICKUP_FRAMES) {
        u8 frame = data_ov094_0229bc50[step];
        if (frame != POCKETS_GRID_NO_FRAME) {
            void *chars = func_ov094_0229b048((char *) grid->animation, frame, grid->pickup_variant);
            func_ov094_0229a8cc(grid, &data_ov094_0229bf70, chars, POCKETS_GRID_HELD_PALETTE);
        }
        grid->pickup_step++;
    } else if (step < POCKETS_GRID_PICKUP_HIDDEN) {
        grid->held_size = PocketsGrid_PickUpSize(grid);
        grid->pickup_step++;
    } else if (step == POCKETS_GRID_PICKUP_HIDDEN) {
        func_ov094_0229a99c(grid, grid->held_item, 0);
        grid->held_size = 0;
        grid->pickup_step++;
    } else if (step < POCKETS_GRID_PICKUP_END) {
        grid->held_size = PocketsGrid_PickUpSize(grid);
        grid->pickup_step++;
    } else {
        PocketsGrid_EndPickUp(grid);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov094_0229a3b0, PocketsGrid_StepPickUp)

/* func_ov094_0229a464: the held OBJ at full size, with data_ov094_0229bfa0 under it. */
void PocketsGrid_EndPickUp(PocketsGrid *grid)
{
    grid->held_size = POCKETS_GRID_FULL_SIZE;
    grid->held_lowered = 1;
}
CLEAN_AS(func_ov094_0229a464, PocketsGrid_EndPickUp)

/* func_ov094_0229a47c: a pick-up of `item` (in pocket slot state `state`) started: frames of
 * variant 0 for state 1, else variant 1; data_ov094_0229bfa0 no longer drawn under it when
 * StateFlags_IsClear2. */
void PocketsGrid_StartPickUp(PocketsGrid *grid, u16 item, int state)
{
    grid->held_item = item;
    grid->pickup_step = 0;
    grid->pickup_variant = state == 1 ? 0 : 1;
    if (StateFlags_IsClear2() != 0) {
        grid->held_lowered = 0;
    }
}
CLEAN_AS(func_ov094_0229a47c, PocketsGrid_StartPickUp)

/* func_ov094_0229a4c0: the next of this frame's three tasks. QUIRK: once the three are used,
 * the last one is answered again. */
int PocketsGrid_NextTask(PocketsGrid *grid)
{
    u8 used = grid->tasks_used;

    if (used >= POCKETS_GRID_TASKS) {
        return POCKETS_GRID_TASKS - 1;
    }
    grid->tasks_used = (u8) (used + 1);
    return used;
}
CLEAN_AS(func_ov094_0229a4c0, PocketsGrid_NextTask)

/* func_ov094_0229a4d8: last frame's tasks ended, none used. */
void PocketsGrid_EndTasks(PocketsGrid *grid)
{
    for (int i = 0; i < POCKETS_GRID_TASKS; i++) {
        LayerTask_End(&grid->tasks[i].first);
    }
    grid->tasks_used = 0;
}
CLEAN_AS(func_ov094_0229a4d8, PocketsGrid_EndTasks)

/* func_ov094_0229a50c: the affine scale of the held OBJ at `size` tenths; one for full size
 * and above. */
int PocketsGrid_SizeScale(unsigned int size)
{
    if (size >= POCKETS_GRID_SIZES) {
        return POCKETS_GRID_SCALE_ONE;
    }
    return data_ov094_0229bc64[size];
}
CLEAN_AS(func_ov094_0229a50c, PocketsGrid_SizeScale)

/* func_ov094_0229a524: the OBJ of place `place`. REQUIRES: `place` in 0-0x23. */
OamEntry *PocketsGrid_PlaceObj(int unused, int place)
{
    (void) unused;
    return &data_ov094_0229bfb0[place];
}
CLEAN_AS(func_ov094_0229a524, PocketsGrid_PlaceObj)

/* func_ov094_0229a530: place `place` drawn with its OBJ `obj` moved by (x, y): the mark when
 * marked; when filled, the OBJ (dimmed in palette 14 when the place is) with the OBJ round it,
 * and for the lifted place the lowered copy under it. The lifted place is raised by the lift's
 * offset, all but the OBJ itself through x and y. */
void PocketsGrid_DrawPlace(PocketsGrid *grid, const OamEntry *obj, int place, int x, int y)
{
    int at_x = OamBuffer_ObjX(obj) + x;
    int at_y = OamBuffer_ObjY(obj) + y;
    int lift = 0;

    if (func_ov094_0229ab7c((unsigned char *) grid, (unsigned char) place) != 0) {
        lift = (int) (intptr_t) func_ov094_0229ab68(grid);
        at_x += lift;
        at_y += lift;
    }
    if (PocketsBits_Test(&grid->marked, place) != 0) {
        PocketsGrid_DrawMark(grid, at_x, at_y);
    }
    if (PocketsBits_Test(&grid->filled, place) != 0) {
        int palette = POCKETS_GRID_OWN_PALETTE;

        if (func_ov094_0229a8bc((int) (uintptr_t) grid, (unsigned char) place) != 0) {
            palette = POCKETS_GRID_DIMMED_PALETTE;
        }
        OamBuffer_DrawObjAffine(OAM_BUFFER_SCREEN_SUB, obj, x + lift, y + lift, palette, grid->priority, NULL);
        PocketsGrid_DrawSurround(grid, at_x, at_y, palette);
        if (func_ov094_0229ab7c((unsigned char *) grid, (unsigned char) place) != 0) {
            PocketsGrid_DrawLowered(grid, at_x, at_y);
        }
    }
}
CLEAN_AS(func_ov094_0229a530, PocketsGrid_DrawPlace)

/* func_ov094_0229a600: data_ov094_0229bfa0 centred on (x, y). */
int PocketsGrid_DrawLowered(PocketsGrid *grid, int x, int y)
{
    return OamBuffer_DrawObjAffine(OAM_BUFFER_SCREEN_SUB, &data_ov094_0229bfa0, x - POCKETS_GRID_OBJ_MARGIN,
                                   y - POCKETS_GRID_OBJ_MARGIN, POCKETS_GRID_OWN_PALETTE, grid->priority, NULL);
}
CLEAN_AS(func_ov094_0229a600, PocketsGrid_DrawLowered)

/* func_ov094_0229a634: data_ov094_0229bf98 centred on (x, y), in `palette` (-1: its own). */
void PocketsGrid_DrawSurround(PocketsGrid *grid, int x, int y, int palette)
{
    OamBuffer_DrawObjAffine(OAM_BUFFER_SCREEN_SUB, &data_ov094_0229bf98, x - POCKETS_GRID_OBJ_MARGIN,
                            y - POCKETS_GRID_OBJ_MARGIN, palette, grid->priority, NULL);
}
CLEAN_AS(func_ov094_0229a634, PocketsGrid_DrawSurround)

/* func_ov094_0229a668: data_ov094_0229bfa8 centred on (x, y). */
int PocketsGrid_DrawMark(PocketsGrid *grid, int x, int y)
{
    return OamBuffer_DrawObjAffine(OAM_BUFFER_SCREEN_SUB, &data_ov094_0229bfa8, x - POCKETS_GRID_OBJ_MARGIN,
                                   y - POCKETS_GRID_OBJ_MARGIN, POCKETS_GRID_OWN_PALETTE, grid->priority, NULL);
}
CLEAN_AS(func_ov094_0229a668, PocketsGrid_DrawMark)
