/* Overlay 094's grid object (pockets_grid.h): its sets of bits, the held item's pick-up and
 * the drawing of a place. */
#include "pockets_grid.h"

#include "clean.h"
#include "main/current_pockets.h"
#include "main/display_layers.h"
#include "main/item_traits.h"
#include "main/message_reader.h"
#include "main/name_texts.h"
#include "main/player_id.h"
#include "main/player_pockets.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/sliding_window.h"
#include "main/state_flags.h"
#include "main/text_label.h"
#include "main/text_string.h"
#include "main/villager_part.h"
#include "pockets_common.h"
#include "pockets_icons.h"

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

/* The grid's origin on the sub screen: the place OBJs' positions are from it. */
#define POCKETS_GRID_ORIGIN_X 0x80
#define POCKETS_GRID_ORIGIN_Y 0x60
#define POCKETS_GRID_POCKETS 15   /* places 0-14: the current player's pocket slots */
#define POCKETS_GRID_BOX_FIRST 15 /* places 15-29: the list at `unk_a34` (PocketsGrid_SetBox) */
#define POCKETS_GRID_BOX_LAST 29
#define POCKETS_GRID_PLACE_BELLS 0x21
#define POCKETS_GRID_PLACE_22 0x22
#define POCKETS_GRID_LIFT_START 2
/* A place is drawn only when its x plus this is right of PocketsGrid_DrawPocketsRightOf's
 * `left`. */
#define POCKETS_GRID_PLACE_RIGHT 0x18
/* The touch finds a place whose 16 x 16 OBJ it is within 4 pixels of. */
#define POCKETS_GRID_TOUCH_BEFORE 0x7c /* x - 0x7c: 4 pixels left of the origin */
#define POCKETS_GRID_TOUCH_AFTER 0x94  /* x - 0x94: 20 pixels right of the origin */
#define POCKETS_GRID_TOUCH_ABOVE 0x5c
#define POCKETS_GRID_TOUCH_BELOW 0x74
/* The touch looks among the box's places above this line and among the pockets below it. */
#define POCKETS_GRID_TOUCH_SPLIT_Y 0x68
/* The mark of place 0x22, from the offset the marks are drawn at. */
#define POCKETS_GRID_MARK_22_X 4
#define POCKETS_GRID_MARK_22_Y 0xac
/* The OBJs' characters are in a sheet 32 tiles wide: a 16 x 16 OBJ is two tiles of one row and
 * two of the next. */
#define POCKETS_GRID_ROW_TILES 0x20
#define POCKETS_GRID_HALF_CHARS 0x40  /* two tiles */
#define POCKETS_GRID_NEXT_ROW 0x400   /* the next row of the icon sheet, in bytes */
#define POCKETS_GRID_TILE_MASK 0x3ff  /* in attr2 */
#define POCKETS_GRID_PALETTE_SHIFT 12 /* in attr2 */
/* PocketsGrid_IconOf for items in slot states 1 and 2. */
#define POCKETS_GRID_ICON_STATE_1 0xb3
#define POCKETS_GRID_ICON_STATE_2 0xb4
/* The popup's menu messages for items in slot states 1 and 2. */
#define POCKETS_GRID_MESSAGE_STATE_1 0x18
#define POCKETS_GRID_MESSAGE_STATE_2 0x40

static_assert(sizeof(PocketsIcons) == sizeof(((PocketsGrid *) 0)->animation), "icons in the grid");
static_assert(sizeof(SlidingWindowText) == 0x30 && sizeof(NameText) == 0x28, "popup texts");
static_assert(sizeof(PlayerIdText) == 0x20, "popup texts");

/* The class's vtable. */
extern const u32 data_ov094_0229bf90[];
/* The lift's offsets by `lift` (-2, -3, -5 pixels). */
extern const s32 data_ov094_0229bc58[];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void func_020edb3c(void *block); /* operator delete */

static PocketsIcons *grid_icons(PocketsGrid *grid)
{
    return (PocketsIcons *) (void *) grid->animation;
}

/* The list of places 15-29, given by PocketsGrid_SetBox. */
static u16 *grid_box(PocketsGrid *grid)
{
    return (u16 *) (uintptr_t) grid->unk_a34;
}

/* PocketsGrid_PlaceObj's first parameter. */
static int grid_address(PocketsGrid *grid)
{
    return (int) (uintptr_t) grid;
}

static int is_pocket(int place)
{
    return place >= 0 && place < POCKETS_GRID_POCKETS;
}

static int is_box(int place)
{
    return place >= POCKETS_GRID_BOX_FIRST && place <= POCKETS_GRID_BOX_LAST;
}

static u16 with_palette(u16 attr2, int palette)
{
    return (u16) ((attr2 & ~(0xfu << POCKETS_GRID_PALETTE_SHIFT)) |
                  ((unsigned int) (palette & 0xf) << POCKETS_GRID_PALETTE_SHIFT));
}

/* func_ov094_0229a69c: whether place `place` holds nothing. */
int PocketsGrid_IsEmpty(PocketsGrid *grid, int place)
{
    return PocketsBits_Test(&grid->filled, place) == 0;
}
CLEAN_AS(func_ov094_0229a69c, PocketsGrid_IsEmpty)

/* func_ov094_0229a6bc: the held item drawn at (x, y): its OBJ at its size (not at all at size
 * 0), the OBJ round it and, when `held_lowered`, the lowered copy under it. */
void PocketsGrid_DrawHeld(PocketsGrid *grid, int x, int y)
{
    int at_x = x + OamBuffer_ObjX(&data_ov094_0229bf70);
    int at_y = y + OamBuffer_ObjY(&data_ov094_0229bf70);
    int scale = PocketsGrid_SizeScale(grid->held_size);

    if (scale != 0) {
        if (scale == POCKETS_GRID_SCALE_ONE) {
            OamBuffer_DrawObjAffine(OAM_BUFFER_SCREEN_SUB, &data_ov094_0229bf70, x, y, POCKETS_GRID_OWN_PALETTE,
                                    grid->priority, NULL);
        } else {
            OamAffine params = {scale, 0, 0, scale};
            OamBuffer_DrawObjAffine(OAM_BUFFER_SCREEN_SUB, &data_ov094_0229bf70, x, y, POCKETS_GRID_OWN_PALETTE,
                                    grid->priority, &params);
        }
    }
    PocketsGrid_DrawSurround(grid, at_x, at_y, POCKETS_GRID_OWN_PALETTE);
    if (grid->held_lowered) {
        PocketsGrid_DrawLowered(grid, at_x, at_y);
    }
}
CLEAN_AS(func_ov094_0229a6bc, PocketsGrid_DrawHeld)

/* func_ov094_0229a768: the marks of places 0x21 (the bells) and 0x22, moved by (x, y), when
 * they are marked; place 0x22's at a fixed place. */
void PocketsGrid_DrawSideMarks(PocketsGrid *grid, int x, int y)
{
    if (PocketsBits_Test(&grid->marked, POCKETS_GRID_PLACE_BELLS)) {
        const OamEntry *obj = PocketsGrid_PlaceObj(grid_address(grid), POCKETS_GRID_PLACE_BELLS);
        int at_x = x + OamBuffer_ObjX(obj) + POCKETS_GRID_ORIGIN_X;
        int at_y = y + OamBuffer_ObjY(obj) + POCKETS_GRID_ORIGIN_Y;
        PocketsGrid_DrawMark(grid, at_x, at_y);
    }
    if (PocketsBits_Test(&grid->marked, POCKETS_GRID_PLACE_22)) {
        PocketsGrid_DrawMark(grid, x + POCKETS_GRID_MARK_22_X, y + POCKETS_GRID_MARK_22_Y);
    }
}
CLEAN_AS(func_ov094_0229a768, PocketsGrid_DrawSideMarks)

/* func_ov094_0229a7cc: the box's places (15-29) drawn, moved by (x, y). */
void PocketsGrid_DrawBox(PocketsGrid *grid, int x, int y)
{
    const OamEntry *obj = PocketsGrid_PlaceObj(grid_address(grid), POCKETS_GRID_BOX_FIRST);

    for (int place = POCKETS_GRID_BOX_FIRST; place <= POCKETS_GRID_BOX_LAST; place++, obj++) {
        PocketsGrid_DrawPlace(grid, obj, place, x + POCKETS_GRID_ORIGIN_X, y + POCKETS_GRID_ORIGIN_Y);
    }
}
CLEAN_AS(func_ov094_0229a7cc, PocketsGrid_DrawBox)

/* func_ov094_0229a804: the pockets' places (0-14) drawn, moved by (x, y), but only those whose
 * right edge is right of `left`. */
void PocketsGrid_DrawPocketsRightOf(PocketsGrid *grid, int x, int y, int left)
{
    const OamEntry *obj = PocketsGrid_PlaceObj(grid_address(grid), 0);

    for (int place = 0; place < POCKETS_GRID_POCKETS; place++, obj++) {
        if (PocketsGrid_PlaceX(grid, place) + POCKETS_GRID_PLACE_RIGHT > left) {
            PocketsGrid_DrawPlace(grid, obj, place, x + POCKETS_GRID_ORIGIN_X, y + POCKETS_GRID_ORIGIN_Y);
        }
    }
}
CLEAN_AS(func_ov094_0229a804, PocketsGrid_DrawPocketsRightOf)

/* func_ov094_0229a850: the pockets' places (0-14) drawn, moved by (x, y). */
void PocketsGrid_DrawPockets(PocketsGrid *grid, int x, int y)
{
    const OamEntry *obj = PocketsGrid_PlaceObj(grid_address(grid), 0);

    for (int place = 0; place < POCKETS_GRID_POCKETS; place++, obj++) {
        PocketsGrid_DrawPlace(grid, obj, place, x + POCKETS_GRID_ORIGIN_X, y + POCKETS_GRID_ORIGIN_Y);
    }
}
CLEAN_AS(func_ov094_0229a850, PocketsGrid_DrawPockets)

/* func_ov094_0229a888: place `place` dimmed (the scenes of ov100 and ov105 lock places so). */
void PocketsGrid_DimPlace(PocketsGrid *grid, int place)
{
    PocketsBits_Set(&grid->dimmed, place);
}
CLEAN_AS(func_ov094_0229a888, PocketsGrid_DimPlace)

/* func_ov094_0229a898: places `first` to `last` dimmed.
 * QUIRK: the matching source declares the grid an unsigned char like the two places, but the
 * ROM's code keeps its whole word: it is a pointer here. */
void PocketsGrid_DimPlaces(PocketsGrid *grid, u8 first, u8 last)
{
    for (u8 place = first; place <= last; place++) {
        PocketsGrid_DimPlace(grid, place);
    }
}
CLEAN_AS(func_ov094_0229a898, PocketsGrid_DimPlaces)

/* func_ov094_0229a8bc: whether place `place` is dimmed. */
int PocketsGrid_IsDimmed(PocketsGrid *grid, int place)
{
    return PocketsBits_Test(&grid->dimmed, place);
}
CLEAN_AS(func_ov094_0229a8bc, PocketsGrid_IsDimmed)

/* func_ov094_0229a8cc: `obj` given the characters `chars` (a 16 x 16 OBJ of a sheet 32 tiles
 * wide) through this frame's next task, which copies them into its own buffer and queues them
 * at the OBJ's tiles, and palette `palette`. */
void PocketsGrid_SetObjChars(PocketsGrid *grid, OamEntry *obj, const u8 *chars, int palette)
{
    int tile = obj->attr2 & POCKETS_GRID_TILE_MASK;
    int task = PocketsGrid_NextTask(grid);
    u8 *top = grid->held_chars[task];
    u8 *bottom = top + POCKETS_GRID_HALF_CHARS;

    MI_CpuCopy8(chars, top, POCKETS_GRID_HALF_CHARS);
    MI_CpuCopy8(chars + POCKETS_GRID_NEXT_ROW, bottom, POCKETS_GRID_HALF_CHARS);
    LayerTask_QueueTwoChars(&grid->tasks[task], (int) (uintptr_t) top, (int) (uintptr_t) bottom, LAYER_SUB_OBJ, tile, tile + 1,
                            tile + POCKETS_GRID_ROW_TILES, tile + POCKETS_GRID_ROW_TILES + 1);
    obj->attr2 = with_palette(obj->attr2, palette);
}
CLEAN_AS(func_ov094_0229a8cc, PocketsGrid_SetObjChars)

/* func_ov094_0229a958: `obj` given the icon of `item` in slot state `state`, through a task. */
void PocketsGrid_SetObjIcon(PocketsGrid *grid, OamEntry *obj, u16 item, int state)
{
    u16 code = item;
    int icon = PocketsGrid_IconOf(grid, &code, state);
    u8 *chars = PocketsIcons_Chars(grid_icons(grid), icon);
    int palette = PocketsIcons_Palette(grid_icons(grid), icon);

    PocketsGrid_SetObjChars(grid, obj, chars, palette);
}
CLEAN_AS(func_ov094_0229a958, PocketsGrid_SetObjIcon)

/* func_ov094_0229a99c: the held item's OBJ given the icon of `item` in slot state `state`. */
void PocketsGrid_SetHeldIcon(PocketsGrid *grid, int item, int state)
{
    PocketsGrid_SetObjIcon(grid, &data_ov094_0229bf70, (u16) item, state);
}
CLEAN_AS(func_ov094_0229a99c, PocketsGrid_SetHeldIcon)

/* func_ov094_0229a9b4: place `place` shown as its item is: empty, or filled with the item's
 * icon (through a task). */
void PocketsGrid_RefreshPlace(PocketsGrid *grid, unsigned int place)
{
    OamEntry *obj = PocketsGrid_PlaceObj(grid_address(grid), (int) place);
    u16 item = PocketsGrid_Item(grid, (int) place);
    int state = PocketsGrid_ItemState(grid, (int) place);

    if (item == PLAYER_POCKETS_NO_ITEM) {
        PocketsBits_Clear(&grid->filled, (int) place);
    } else {
        PocketsBits_Set(&grid->filled, (int) place);
        PocketsGrid_SetObjIcon(grid, obj, item, state);
    }
}
CLEAN_AS(func_ov094_0229a9b4, PocketsGrid_RefreshPlace)

/* func_ov094_0229aa14: the item of place `place` set: a pocket slot of the current player
 * (with its state), or an entry of the box (its state not kept); nothing for other places.
 * REQUIRES: a box given (PocketsGrid_SetBox) before a place of it is set. */
void PocketsGrid_SetItem(PocketsGrid *grid, int place, int item, int state)
{
    u16 code = (u16) item;

    if (is_pocket(place)) {
        CurrentPockets_Set(&code, state, place);
    } else if (is_box(place)) {
        grid_box(grid)[place - POCKETS_GRID_BOX_FIRST] = (u16) item;
    }
}
CLEAN_AS(func_ov094_0229aa14, PocketsGrid_SetItem)

/* func_ov094_0229aa58: place `place` emptied and shown empty. */
void PocketsGrid_EmptyPlace(PocketsGrid *grid, int place)
{
    PocketsGrid_SetItem(grid, place, PLAYER_POCKETS_NO_ITEM, 0);
    PocketsBits_Clear(&grid->filled, place);
}
CLEAN_AS(func_ov094_0229aa58, PocketsGrid_EmptyPlace)

/* func_ov094_0229aa84: the slot state of the item of place `place`: its pocket slot's, 0 for
 * other places. */
u8 PocketsGrid_ItemState(PocketsGrid *grid, int place)
{
    (void) grid;
    if (is_pocket(place)) {
        return (u8) PlayerPockets_SlotState(PlayerRecord_Pockets(PlayerRecords_Current()), place);
    }
    return 0;
}
CLEAN_AS(func_ov094_0229aa84, PocketsGrid_ItemState)

/* func_ov094_0229aaac: the item of place `place`: its pocket slot's, the box's entry (none
 * without a box), else none. */
u16 PocketsGrid_Item(PocketsGrid *grid, int place)
{
    PlayerPockets *pockets = PlayerRecord_Pockets(PlayerRecords_Current());

    if (is_pocket(place)) {
        return PlayerPockets_Slot(pockets, 0)[place];
    }
    if (is_box(place) && grid_box(grid) != NULL) {
        return grid_box(grid)[place - POCKETS_GRID_BOX_FIRST];
    }
    return PLAYER_POCKETS_NO_ITEM;
}
CLEAN_AS(func_ov094_0229aaac, PocketsGrid_Item)

/* func_ov094_0229aafc: place `place` marked. */
void PocketsGrid_MarkPlace(PocketsGrid *grid, int place)
{
    PocketsBits_Set(&grid->marked, place);
}
CLEAN_AS(func_ov094_0229aafc, PocketsGrid_MarkPlace)

/* func_ov094_0229ab0c: no place marked. */
void PocketsGrid_ClearMarks(PocketsGrid *grid)
{
    PocketsBits_ClearAll(&grid->marked);
}
CLEAN_AS(func_ov094_0229ab0c, PocketsGrid_ClearMarks)

/* func_ov094_0229ab1c: place `place` lifted, its lift starting again when it was not the
 * lifted one; none lifted when the place is dimmed. */
void PocketsGrid_Lift(PocketsGrid *grid, int place)
{
    if (PocketsGrid_IsDimmed(grid, (u8) place)) {
        PocketsGrid_Unlift(grid);
    } else if (grid->lifted != place) {
        grid->lifted = (u8) place;
        grid->lift = POCKETS_GRID_LIFT_START;
    }
}
CLEAN_AS(func_ov094_0229ab1c, PocketsGrid_Lift)

/* func_ov094_0229ab5c: no place lifted. */
void PocketsGrid_Unlift(PocketsGrid *grid)
{
    grid->lifted = POCKETS_GRID_NO_PLACE;
}
CLEAN_AS(func_ov094_0229ab5c, PocketsGrid_Unlift)

/* func_ov094_0229ab68: the lifted place's offset now. REQUIRES: `lift` 0-3 (it counts down from
 * 2). */
int PocketsGrid_LiftOffset(PocketsGrid *grid)
{
    return data_ov094_0229bc58[grid->lift];
}
CLEAN_AS(func_ov094_0229ab68, PocketsGrid_LiftOffset)

/* func_ov094_0229ab7c: whether place `place` is the lifted one. */
int PocketsGrid_IsLifted(PocketsGrid *grid, u8 place)
{
    return place == grid->lifted;
}
CLEAN_AS(func_ov094_0229ab7c, PocketsGrid_IsLifted)

/* func_ov094_0229ab90: place `place`'s y on the screen. */
int PocketsGrid_PlaceY(PocketsGrid *grid, int place)
{
    return OamBuffer_ObjY(PocketsGrid_PlaceObj(grid_address(grid), place)) + POCKETS_GRID_ORIGIN_Y;
}
CLEAN_AS(func_ov094_0229ab90, PocketsGrid_PlaceY)

/* func_ov094_0229aba4: place `place`'s x on the screen. */
int PocketsGrid_PlaceX(PocketsGrid *grid, int place)
{
    return OamBuffer_ObjX(PocketsGrid_PlaceObj(grid_address(grid), place)) + POCKETS_GRID_ORIGIN_X;
}
CLEAN_AS(func_ov094_0229aba4, PocketsGrid_PlaceX)

/* func_ov094_0229abb8: `popup` given the text of place `place`'s item, unless it is empty. */
void PocketsGrid_ShowItemText(PocketsGrid *grid, Popup *popup, int place)
{
    u16 item = PocketsGrid_Item(grid, place);

    if (item == PLAYER_POCKETS_NO_ITEM) {
        return;
    }
    PocketsGrid_SetPopupText(grid, popup, &item, PocketsGrid_ItemState(grid, place));
}
CLEAN_AS(func_ov094_0229abb8, PocketsGrid_ShowItemText)

/* func_ov094_0229abf8: `popup` given the text of `item` in slot state `state`: menu message 0x18
 * for state 1; for state 2 the item's name when it is 0x155f or 0x1560, else menu message 0x40
 * with part 0 the name VillagerPart_CurrentNameFor gives for it; the item's name for the other
 * states.
 * BUG: a text is copied into the line by the line's capacity (42 bytes, TextString_CopyBytes),
 * more than the item's name holds, so the line also takes the first bytes of the text after the
 * name in the ROM's frame (the villager's name: its vtable and length). The texts are kept in
 * that order here (PopupTexts) so the window gets the same bytes. */
void PocketsGrid_SetPopupText(PocketsGrid *grid, Popup *popup, u16 *item, int state)
{
    struct PopupTexts {
        SlidingWindowText line; /* 0x00 */
        NameText name;          /* 0x30 */
        PlayerIdText villager;  /* 0x58 */
        TextLabel label;        /* 0x78 */
    } texts;
    static_assert(offsetof(struct PopupTexts, name) == 0x30 && offsetof(struct PopupTexts, villager) == 0x58,
                  "the ROM's frame");

    (void) grid;
    TextLabel_Construct(&texts.label);
    SlidingWindowText_Construct(&texts.line);
    NameText_Construct(&texts.name);
    PlayerIdText_Construct(&texts.villager);
    switch (state) {
        case 1:
            TextLabel_LoadMenuMessage((int) (uintptr_t) &texts.label, POCKETS_GRID_MESSAGE_STATE_1);
            TextString_CopyBytes((TextObject *) (void *) &texts.line, (TextObject *) (void *) &texts.label);
            break;
        case 2:
            if (PocketsItem_IsDayItem(*item)) {
                NameText_SetItem(&texts.name, item);
                TextString_CopyBytes((TextObject *) (void *) &texts.line, (TextObject *) (void *) &texts.name);
            } else {
                VillagerPart_CurrentNameFor(&texts.villager, item);
                MessageReader_SetPart(0, (int) (uintptr_t) &texts.villager);
                TextLabel_LoadMenuMessage((int) (uintptr_t) &texts.label, POCKETS_GRID_MESSAGE_STATE_2);
                TextString_CopyBytes((TextObject *) (void *) &texts.line, (TextObject *) (void *) &texts.label);
            }
            break;
        default:
            NameText_SetItem(&texts.name, item);
            TextString_CopyBytes((TextObject *) (void *) &texts.line, (TextObject *) (void *) &texts.name);
            break;
    }
    SlidingWindow_SetText((SlidingWindow *) (void *) popup, (struct TextObject *) (void *) &texts.line);
    PlayerIdText_Destruct(&texts.villager);
    NameText_Destruct(&texts.name);
    SlidingWindowText_Destruct(&texts.line);
    TextLabel_Destruct(&texts.label);
}
CLEAN_AS(func_ov094_0229abf8, PocketsGrid_SetPopupText)

/* func_ov094_0229acb0: the icon of `item` in slot state `state`: 0xb3 in state 1; in state 2
 * 0xb4 unless the item is one of 0x155f-0x1564; else the item's own (ItemTraits_Unk02). */
int PocketsGrid_IconOf(PocketsGrid *grid, u16 *item, int state)
{
    (void) grid;
    switch (state) {
        case 1:
            return POCKETS_GRID_ICON_STATE_1;
        case 2:
            if (PocketsItem_IsIn155fTo1564(*item) == 0) {
                return POCKETS_GRID_ICON_STATE_2;
            }
            return ItemTraits_Unk02(item);
        default:
            return ItemTraits_Unk02(item);
    }
}
CLEAN_AS(func_ov094_0229acb0, PocketsGrid_IconOf)

/* func_ov094_0229ace4: the box's places (15-29) loaded from `box`'s 15 items, in state 0, and
 * `box` kept as their list. */
void PocketsGrid_SetBox(PocketsGrid *grid, u16 *box)
{
    for (int i = 0; i < POCKETS_GRID_POCKETS; i++) {
        u16 item = box[i];
        PocketsGrid_LoadPlace(grid, POCKETS_GRID_BOX_FIRST + i, &item, 0);
    }
    grid->unk_a34 = (u32) (uintptr_t) box;
}
CLEAN_AS(func_ov094_0229ace4, PocketsGrid_SetBox)

/* func_ov094_0229ad20: the pockets' places (0-14) loaded from the current player's slots. */
void PocketsGrid_LoadPockets(PocketsGrid *grid)
{
    PlayerPockets *pockets = PlayerRecord_Pockets(PlayerRecords_Current());
    u16 *items = PlayerPockets_Slot(pockets, 0);

    for (int place = 0; place < POCKETS_GRID_POCKETS; place++) {
        PocketsGrid_LoadPlace(grid, place, &items[place], PlayerPockets_SlotState(pockets, place));
    }
}
CLEAN_AS(func_ov094_0229ad20, PocketsGrid_LoadPockets)

/* func_ov094_0229ad64: place `place` shown as `item` in slot state `state`: empty, or filled
 * with the item's icon, whose characters are loaded at once at the place OBJ's tiles. */
void PocketsGrid_LoadPlace(PocketsGrid *grid, int place, u16 *item, int state)
{
    int icon;
    OamEntry *obj;
    u32 tile;
    u8 *chars;

    if (*item == PLAYER_POCKETS_NO_ITEM) {
        PocketsBits_Clear(&grid->filled, place);
        return;
    }
    PocketsBits_Set(&grid->filled, place);
    icon = PocketsGrid_IconOf(grid, item, state);
    obj = PocketsGrid_PlaceObj(grid_address(grid), place);
    tile = obj->attr2 & POCKETS_GRID_TILE_MASK;
    chars = PocketsIcons_Chars(grid_icons(grid), icon);
    DisplayLayer_LoadChars((u32) (uintptr_t) chars, LAYER_SUB_OBJ, tile, tile, tile + 1);
    tile += POCKETS_GRID_ROW_TILES;
    DisplayLayer_LoadChars((u32) (uintptr_t) (chars + POCKETS_GRID_NEXT_ROW), LAYER_SUB_OBJ, tile, tile, tile + 1);
    obj->attr2 = with_palette(obj->attr2, PocketsIcons_Palette(grid_icons(grid), icon));
}
CLEAN_AS(func_ov094_0229ad64, PocketsGrid_LoadPlace)

/* func_ov094_0229ae10: whether the touch at (x, y) is on place `place`. */
int PocketsGrid_TouchOnPlace(PocketsGrid *grid, int x, int y, int place)
{
    const OamEntry *obj = PocketsGrid_PlaceObj(grid_address(grid), place);
    int obj_x = OamBuffer_ObjX(obj);

    if (x - POCKETS_GRID_TOUCH_AFTER < obj_x && obj_x < x - POCKETS_GRID_TOUCH_BEFORE) {
        int obj_y = OamBuffer_ObjY(obj);
        if (y - POCKETS_GRID_TOUCH_BELOW < obj_y && obj_y < y - POCKETS_GRID_TOUCH_ABOVE) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov094_0229ae10, PocketsGrid_TouchOnPlace)

/* func_ov094_0229ae54: the first of places `first` to `last` whose OBJ's position is strictly
 * inside (min_x, min_y)-(max_x, max_y); POCKETS_GRID_NO_PLACE for none. */
u8 PocketsGrid_PlaceInside(PocketsGrid *grid, int min_x, int min_y, int max_x, int max_y, u8 first, u8 last)
{
    for (int place = first; place <= last; place++) {
        const OamEntry *obj = PocketsGrid_PlaceObj(grid_address(grid), place);
        int obj_x = OamBuffer_ObjX(obj);
        int obj_y;

        if (min_x >= obj_x || obj_x >= max_x) {
            continue;
        }
        obj_y = OamBuffer_ObjY(obj);
        if (min_y >= obj_y || obj_y >= max_y) {
            continue;
        }
        return (u8) place;
    }
    return POCKETS_GRID_NO_PLACE;
}
CLEAN_AS(func_ov094_0229ae54, PocketsGrid_PlaceInside)

/* func_ov094_0229aea8: whether the touch at (x, y) is on place 0x21 (the bells). */
int PocketsGrid_TouchOnBells(PocketsGrid *grid, int x, int y)
{
    return PocketsGrid_TouchOnPlace(grid, x, y, POCKETS_GRID_PLACE_BELLS);
}
CLEAN_AS(func_ov094_0229aea8, PocketsGrid_TouchOnBells)

/* func_ov094_0229aeb8: the box's place (15-29) under the touch at (x, y); none below the
 * split. */
int PocketsGrid_BoxPlaceAtTouch(PocketsGrid *grid, int x, int y)
{
    if (y > POCKETS_GRID_TOUCH_SPLIT_Y) {
        return POCKETS_GRID_NO_PLACE;
    }
    return PocketsGrid_PlaceInside(grid, x - POCKETS_GRID_TOUCH_AFTER, y - POCKETS_GRID_TOUCH_BELOW,
                                   x - POCKETS_GRID_TOUCH_BEFORE, y - POCKETS_GRID_TOUCH_ABOVE, POCKETS_GRID_BOX_FIRST,
                                   POCKETS_GRID_BOX_LAST);
}
CLEAN_AS(func_ov094_0229aeb8, PocketsGrid_BoxPlaceAtTouch)

/* func_ov094_0229aee8: the pockets' place (0-14) under the touch at (x, y); none above the
 * split. */
int PocketsGrid_PocketPlaceAtTouch(PocketsGrid *grid, int x, int y)
{
    if (y < POCKETS_GRID_TOUCH_SPLIT_Y) {
        return POCKETS_GRID_NO_PLACE;
    }
    return PocketsGrid_PlaceInside(grid, x - POCKETS_GRID_TOUCH_AFTER, y - POCKETS_GRID_TOUCH_BELOW,
                                   x - POCKETS_GRID_TOUCH_BEFORE, y - POCKETS_GRID_TOUCH_ABOVE, 0, POCKETS_GRID_POCKETS - 1);
}
CLEAN_AS(func_ov094_0229aee8, PocketsGrid_PocketPlaceAtTouch)

/* func_ov094_0229af18: last frame's tasks ended. */
void PocketsGrid_Teardown(PocketsGrid *grid)
{
    PocketsGrid_EndTasks(grid);
}
CLEAN_AS(func_ov094_0229af18, PocketsGrid_Teardown)

/* func_ov094_0229af20: a frame begun: last frame's tasks ended, the lift a step on. */
void PocketsGrid_BeginFrame(PocketsGrid *grid)
{
    PocketsGrid_EndTasks(grid);
    if (grid->lift != 0) {
        grid->lift--;
    }
}
CLEAN_AS(func_ov094_0229af20, PocketsGrid_BeginFrame)

/* func_ov094_0229af40: the grid set up empty, with no box, its OBJs at priority `priority` and
 * the held item at full size with the lowered copy under it. */
void PocketsGrid_Init(PocketsGrid *grid, int priority)
{
    PocketsIcons_Forget(grid_icons(grid));
    PocketsBits_ClearAll(&grid->filled);
    PocketsBits_ClearAll(&grid->marked);
    PocketsBits_ClearAll(&grid->dimmed);
    grid->lifted = POCKETS_GRID_NO_PLACE;
    grid->lift = 0;
    grid->priority = priority;
    grid->unk_a34 = 0;
    grid->held_size = POCKETS_GRID_FULL_SIZE;
    grid->held_lowered = 1;
}
CLEAN_AS(func_ov094_0229af40, PocketsGrid_Init)

/* func_ov094_0229afb8 (vtable entry 3): the destructor that frees the grid. */
PocketsGrid *PocketsGrid_DestructDelete(PocketsGrid *grid)
{
    grid->vtable = (u32) (uintptr_t) data_ov094_0229bf90;
    PocketsIcons_Destruct(grid_icons(grid));
    func_020edb3c(grid);
    return grid;
}
CLEAN_AS(func_ov094_0229afb8, PocketsGrid_DestructDelete)

/* func_ov094_0229afe0 (vtable entry 2): the destructor (the tasks have none). */
PocketsGrid *PocketsGrid_Destruct(PocketsGrid *grid)
{
    grid->vtable = (u32) (uintptr_t) data_ov094_0229bf90;
    PocketsIcons_Destruct(grid_icons(grid));
    return grid;
}
CLEAN_AS(func_ov094_0229afe0, PocketsGrid_Destruct)

/* func_ov094_0229b000: the constructor: the icon sheet and the three tasks. */
PocketsGrid *PocketsGrid_Construct(PocketsGrid *grid)
{
    grid->vtable = (u32) (uintptr_t) data_ov094_0229bf90;
    PocketsIcons_Construct(grid_icons(grid));
    for (int i = 0; i < POCKETS_GRID_TASKS; i++) {
        LayerTask_ConstructPair(&grid->tasks[i]);
    }
    return grid;
}
CLEAN_AS(func_ov094_0229b000, PocketsGrid_Construct)
