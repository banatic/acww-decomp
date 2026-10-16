/* The camera grid, the window of the menu tab (camera_grid.h). */
#include "camera_grid.h"

#include "autoload_2/heap.h"  /* Heap_OperatorDeleteB */
#include "autoload_2/input.h" /* PadState */
#include "camera_control.h"   /* CameraControl_SelectPreset */
#include "cell_anim.h"
#include "clean.h"
#include "menu_input.h"
#include "oam_buffer.h" /* OamBuffer_DrawCell */
#include "ov004/member_pointer.h"
#include "sound.h" /* SoundSys_PlaySe */

static_assert(offsetof(CameraGrid, buttons) == 0x0c && offsetof(CameraGrid, state) == 0xc0, "CameraGrid");
static_assert(offsetof(CameraGrid, cursor) == 0xc4 && offsetof(CameraGrid, chosen) == 0xd0, "CameraGrid");
static_assert(offsetof(CameraGrid, asked_open) == 0xd4 && sizeof(CameraGrid) == 0xd8, "CameraGrid");

/* A button's place in the grid, -1 to 1 from the centre. */
typedef struct CameraGridPlace {
    s8 column;
    s8 row;
} CameraGridPlace;

/* A button's preset of the camera (CameraControl_SelectPreset), 0 to 2. */
typedef struct CameraGridPreset {
    u8 column;
    u8 row;
} CameraGridPreset;

/* A button's top left corner on the touch screen, from (0x80, 0x60). */
typedef struct CameraGridSpot {
    u8 x;
    u8 y;
} CameraGridSpot;

extern const CameraGridSpot data_020d0a70[CAMERA_GRID_BUTTONS];
extern const CameraGridPlace data_020d0a84[CAMERA_GRID_BUTTONS];
extern const CameraGridPreset data_020d0a98[CAMERA_GRID_BUTTONS];

/* The animations of main's sprites; button i opens with entry 14 + i, closes with 23 + i. */
extern const CellAnimData data_020d5b3c[];
#define CAMERA_GRID_ANIM_OPENING 0x0e
#define CAMERA_GRID_ANIM_CLOSING 0x17

extern const u32 data_020e2250[]; /* the class's vtable */

extern PadState data_021fbe40;

/* The member function table of CameraGrid_Update (a function-local static of the game): its
 * guard, the table, and the constants it is filled from. */
extern u32 data_021d314c;
extern MemberPointer data_021d31d0[4];
extern const MemberPointer data_020e211c, data_020e2124, data_020e21bc, data_020e21c4;

/* The buttons' animations' constructor and destructor, as the game hands them to
 * __cxa_vec_ctor and __cxa_vec_cleanup (CellAnim_Construct, CellAnim_Destruct). */
extern void func_0208a1f8(void *anim);
extern void func_0208a1f4(void *anim);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

#define CAMERA_GRID_PAD_RIGHT 0x0010
#define CAMERA_GRID_PAD_LEFT 0x0020
#define CAMERA_GRID_PAD_UP 0x0040
#define CAMERA_GRID_PAD_DOWN 0x0080

#define CAMERA_GRID_ORIGIN_X 0x80
#define CAMERA_GRID_ORIGIN_Y 0x60
#define CAMERA_GRID_BUTTON_SIZE 0x10

/* The sounds of a choice: the chosen button higher, lower, or on the same row. */
#define CAMERA_GRID_SE_HIGHER 0x4d
#define CAMERA_GRID_SE_LOWER 0x4c
#define CAMERA_GRID_SE_SAME_ROW 0x4e

/* The palettes of the chosen button and of the others. */
#define CAMERA_GRID_PALETTE_CHOSEN 6
#define CAMERA_GRID_PALETTE 5

#define CAMERA_GRID_FX_ONE 0x1000

/* vtable slots */
#define CAMERA_GRID_SLOT_DRAW 2
#define CAMERA_GRID_SLOT_UPDATE 3

static int camera_grid_call_slot(CameraGrid *grid, int slot)
{
    return ((int (*)(CameraGrid *))(uintptr_t) grid->base.vtable[slot])(grid);
}

/* Every button's animation advanced; whether all are done. */
static int camera_grid_advance_all(CameraGrid *grid)
{
    int done = 1;
    for (int i = 0; i < CAMERA_GRID_BUTTONS; i++) {
        CellAnim_Advance(&grid->buttons[i]);
        if (CellAnim_IsDone(&grid->buttons[i]) == 0) {
            done = 0;
        }
    }
    return done;
}

/* Every button's animation set to entry `first` + i, held at its end, from the start. */
static void camera_grid_start_all(CameraGrid *grid, int first)
{
    for (int i = 0; i < CAMERA_GRID_BUTTONS; i++) {
        CellAnim *anim = &grid->buttons[i];
        CellAnim_SetData(anim, &data_020d5b3c[first + i]);
        CellAnim_SetHold(anim, 1);
        CellAnim_Restart(anim);
    }
}

/* func_0208c21c: once the closing animations are done, closed. */
void CameraGrid_StepClosing(CameraGrid *grid)
{
    if (camera_grid_advance_all(grid)) {
        CameraGrid_EnterClosed(grid);
    }
}
CLEAN_AS(func_0208c21c, CameraGrid_StepClosing)

/* func_0208c260 */
void CameraGrid_EnterClosing(CameraGrid *grid)
{
    grid->state = CAMERA_GRID_CLOSING;
    camera_grid_start_all(grid, CAMERA_GRID_ANIM_CLOSING);
}
CLEAN_AS(func_0208c260, CameraGrid_EnterClosing)

/* func_0208c2ac: closing once asked to; else the cursor moved by a tap (touch chosen) or the
 * d-pad (buttons chosen), unless the press switches the input, and a move chooses. */
void CameraGrid_StepOpen(CameraGrid *grid)
{
    if (grid->asked_open == 0) {
        CameraGrid_EnterClosing(grid);
        return;
    }
    if (CameraGrid_InputSwitches() != 0) {
        return;
    }
    int moved = 0;
    if (MenuInput_UsesTouch() != 0) {
        moved = CameraGrid_MoveByTouch(grid) != 0;
    } else if (MenuInput_UsesButtons() != 0) {
        moved = CameraGrid_MoveByPad(grid) != 0;
    }
    if (moved) {
        CameraGrid_Choose(grid);
    }
}
CLEAN_AS(func_0208c2ac, CameraGrid_StepOpen)

/* func_0208c308 */
void CameraGrid_EnterOpen(CameraGrid *grid)
{
    grid->state = CAMERA_GRID_OPEN;
}
CLEAN_AS(func_0208c308, CameraGrid_EnterOpen)

/* func_0208c310: once the opening animations are done, open. */
void CameraGrid_StepOpening(CameraGrid *grid)
{
    if (camera_grid_advance_all(grid)) {
        CameraGrid_EnterOpen(grid);
    }
}
CLEAN_AS(func_0208c310, CameraGrid_StepOpening)

/* func_0208c354 */
void CameraGrid_EnterOpening(CameraGrid *grid)
{
    grid->state = CAMERA_GRID_OPENING;
    camera_grid_start_all(grid, CAMERA_GRID_ANIM_OPENING);
}
CLEAN_AS(func_0208c354, CameraGrid_EnterOpening)

/* func_0208c3a0 */
void CameraGrid_StepClosed(CameraGrid *grid)
{
    if (grid->asked_open != 0) {
        CameraGrid_EnterOpening(grid);
    }
}
CLEAN_AS(func_0208c3a0, CameraGrid_StepClosed)

/* func_0208c3b8 */
void CameraGrid_EnterClosed(CameraGrid *grid)
{
    grid->state = CAMERA_GRID_CLOSED;
}
CLEAN_AS(func_0208c3b8, CameraGrid_EnterClosed)

/* func_0208c3c0: the column and row of the button at the cursor.
 * REQUIRES: the cursor is 0-8 (the ROM indexes its table unchecked). */
void CameraGrid_PlaceFromCursor(CameraGrid *grid)
{
    grid->column = data_020d0a84[grid->cursor].column;
    grid->row = data_020d0a84[grid->cursor].row;
}
CLEAN_AS(func_0208c3c0, CameraGrid_PlaceFromCursor)

/* func_0208c3ec: the cursor on the button at the column and row; 9 when none is there. */
void CameraGrid_CursorFromPlace(CameraGrid *grid)
{
    int i;
    for (i = 0; i < CAMERA_GRID_BUTTONS; i++) {
        if (grid->column == data_020d0a84[i].column && grid->row == data_020d0a84[i].row) {
            break;
        }
    }
    grid->cursor = (u32) i;
}
CLEAN_AS(func_0208c3ec, CameraGrid_CursorFromPlace)

/* func_0208c42c: the camera's preset of the button at the cursor selected; when that is not the
 * chosen button, the sound of where it is from the chosen one, and it is the chosen one.
 * REQUIRES: the cursor and the chosen button are 0-8 (the ROM indexes its tables unchecked). */
void CameraGrid_Choose(CameraGrid *grid)
{
    const CameraGridPreset *preset = &data_020d0a98[grid->cursor];
    CameraControl_SelectPreset(preset->row, preset->column);
    if (grid->cursor == grid->chosen) {
        return;
    }
    int row = data_020d0a84[grid->cursor].row;
    int chosen_row = data_020d0a84[grid->chosen].row;
    int se;
    if (row < chosen_row) {
        se = CAMERA_GRID_SE_HIGHER;
    } else if (row > chosen_row) {
        se = CAMERA_GRID_SE_LOWER;
    } else {
        se = CAMERA_GRID_SE_SAME_ROW;
    }
    SoundSys_PlaySe(se);
    grid->chosen = grid->cursor;
}
CLEAN_AS(func_0208c42c, CameraGrid_Choose)

static int camera_grid_clamp_step(int value)
{
    if (value < -1) {
        return -1;
    }
    if (value > 1) {
        return 1;
    }
    return value;
}

/* func_0208c490: the cursor moved one step by the d-pad's press (right, left, up, down, the
 * first of them pressed), kept in the grid; whether its column or row changed. */
int CameraGrid_MoveByPad(CameraGrid *grid)
{
    int column = grid->column;
    int row = grid->row;
    u16 pressed = data_021fbe40.pressed;
    if ((pressed & CAMERA_GRID_PAD_RIGHT) != 0) {
        grid->column++;
    } else if ((pressed & CAMERA_GRID_PAD_LEFT) != 0) {
        grid->column--;
    } else if ((pressed & CAMERA_GRID_PAD_UP) != 0) {
        grid->row--;
    } else if ((pressed & CAMERA_GRID_PAD_DOWN) != 0) {
        grid->row++;
    }
    grid->column = camera_grid_clamp_step(grid->column);
    grid->row = camera_grid_clamp_step(grid->row);
    CameraGrid_CursorFromPlace(grid);
    return column != grid->column || row != grid->row;
}
CLEAN_AS(func_0208c490, CameraGrid_MoveByPad)

/* func_0208c56c: the cursor put on the first button the pen tapped; whether there was one. */
int CameraGrid_MoveByTouch(CameraGrid *grid)
{
    for (int i = 0; i < CAMERA_GRID_BUTTONS; i++) {
        int left = data_020d0a70[i].x + CAMERA_GRID_ORIGIN_X;
        int top = data_020d0a70[i].y + CAMERA_GRID_ORIGIN_Y;
        if (MenuInput_TouchPressedIn(left, left + CAMERA_GRID_BUTTON_SIZE, top, top + CAMERA_GRID_BUTTON_SIZE) != 0) {
            grid->cursor = (u32) i;
            CameraGrid_PlaceFromCursor(grid);
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0208c56c, CameraGrid_MoveByTouch)

/* func_0208c5bc: whether this frame's press only switches the input: a button with touch
 * chosen, or the pen with the buttons chosen. */
int CameraGrid_InputSwitches(void)
{
    if (MenuInput_UsesTouch() != 0) {
        return MenuInput_AnyPressed() != 0;
    }
    return MenuInput_UsesButtons() != 0 && MenuInput_TouchPressed() != 0;
}
CLEAN_AS(func_0208c5bc, CameraGrid_InputSwitches)

/* func_0208c5f0: closed or open, not moving. */
int CameraGrid_IsSettled(CameraGrid *grid)
{
    return grid->state == CAMERA_GRID_CLOSED || grid->state == CAMERA_GRID_OPEN;
}
CLEAN_AS(func_0208c5f0, CameraGrid_IsSettled)

/* func_0208c610 */
int CameraGrid_IsOpen(CameraGrid *grid)
{
    return grid->state == CAMERA_GRID_OPEN;
}
CLEAN_AS(func_0208c610, CameraGrid_IsOpen)

/* func_0208c620 */
int CameraGrid_IsClosed(CameraGrid *grid)
{
    return grid->state == CAMERA_GRID_CLOSED;
}
CLEAN_AS(func_0208c620, CameraGrid_IsClosed)

/* func_0208c630 */
void CameraGrid_AskOpen(CameraGrid *grid, u8 open)
{
    grid->asked_open = open;
}
CLEAN_AS(func_0208c630, CameraGrid_AskOpen)

/* func_0208c638: the class's draw, its result returned.
 * QUIRK: while open, MenuInput_UsesButtons is asked first and its answer not used. */
int CameraGrid_CallDraw(CameraGrid *grid)
{
    if (grid->state == CAMERA_GRID_OPEN) {
        (void) MenuInput_UsesButtons();
    }
    return camera_grid_call_slot(grid, CAMERA_GRID_SLOT_DRAW);
}
CLEAN_AS(func_0208c638, CameraGrid_CallDraw)

/* func_0208c658: the class's update, its result returned. */
int CameraGrid_CallUpdate(CameraGrid *grid)
{
    return camera_grid_call_slot(grid, CAMERA_GRID_SLOT_UPDATE);
}
CLEAN_AS(func_0208c658, CameraGrid_CallUpdate)

/* func_0208c668 */
void CameraGrid_RestartButtons(CameraGrid *grid)
{
    for (int i = 0; i < CAMERA_GRID_BUTTONS; i++) {
        CellAnim_Restart(&grid->buttons[i]);
    }
}
CLEAN_AS(func_0208c668, CameraGrid_RestartButtons)

/* func_0208c688: not asked to open, the cursor and the chosen button on the centre, closed. */
void CameraGrid_Reset(CameraGrid *grid)
{
    grid->asked_open = 0;
    grid->cursor = 0;
    grid->column = 0;
    grid->row = 0;
    grid->chosen = 0;
    CameraGrid_EnterClosed(grid);
}
CLEAN_AS(func_0208c688, CameraGrid_Reset)

/* func_0208c6b0 (vtable slot 3): the state's step, through the game's table (filled on the first
 * call).
 * REQUIRES: the state is 0-3 (the ROM indexes its table unchecked). */
void CameraGrid_Update(CameraGrid *grid)
{
    static const MemberPointer *const constants[4] = {
        &data_020e211c, /* CameraGrid_StepClosed */
        &data_020e2124, /* CameraGrid_StepOpening */
        &data_020e21bc, /* CameraGrid_StepOpen */
        &data_020e21c4, /* CameraGrid_StepClosing */
    };
    MemberTable_InitOnce(&data_021d314c, data_021d31d0, constants, 4);
    MemberPointer_CallVoid(&data_021d31d0[grid->state], grid);
}
CLEAN_AS(func_0208c6b0, CameraGrid_Update)

/* func_0208c734 (vtable slot 2): unless closed, each button's cell drawn on the main screen at
 * the sprite's place plus the frame's offset, the chosen one in its own palette. */
void CameraGrid_Draw(CameraGrid *grid)
{
    if (grid->state == CAMERA_GRID_CLOSED) {
        return;
    }
    int x = ScreenSprite_X(&grid->base);
    int y = ScreenSprite_Y(&grid->base);
    for (int i = 0; i < CAMERA_GRID_BUTTONS; i++) {
        CellAnim *anim = &grid->buttons[i];
        const OamEntry *cell = CellAnim_Cell(anim);
        if (cell == NULL) {
            continue;
        }
        int dx = CellAnim_FrameX(anim, -1);
        int dy = CellAnim_FrameY(anim, -1);
        int palette = (u32) i == grid->chosen ? CAMERA_GRID_PALETTE_CHOSEN : CAMERA_GRID_PALETTE;
        OamBuffer_DrawCell(OAM_BUFFER_SCREEN_MAIN, cell, x + dx, y + dy, palette, -1, CAMERA_GRID_FX_ONE, CAMERA_GRID_FX_ONE,
                           0, -1, 0, 0);
    }
}
CLEAN_AS(func_0208c734, CameraGrid_Draw)

static void camera_grid_destruct(CameraGrid *grid)
{
    grid->base.vtable = data_020e2250;
    CameraGrid_RestartButtons(grid);
    __cxa_vec_cleanup(grid->buttons, CAMERA_GRID_BUTTONS, sizeof(CellAnim), func_0208a1f4);
    ScreenSprite_DestructBase(&grid->base);
}

/* func_0208c7cc (vtable slot 1): destructed and freed. */
CameraGrid *CameraGrid_Delete(CameraGrid *grid)
{
    camera_grid_destruct(grid);
    Heap_OperatorDeleteB(grid);
    return grid;
}
CLEAN_AS(func_0208c7cc, CameraGrid_Delete)

/* func_0208c804 (vtable slot 0): the destructor: the animations restarted, then destructed. */
CameraGrid *CameraGrid_Destruct(CameraGrid *grid)
{
    camera_grid_destruct(grid);
    return grid;
}
CLEAN_AS(func_0208c804, CameraGrid_Destruct)

/* func_0208c834: the constructor: closed, not asked to open, the cursor on the centre. */
CameraGrid *CameraGrid_Construct(CameraGrid *grid)
{
    ScreenSprite_Construct(&grid->base);
    grid->base.vtable = data_020e2250;
    __cxa_vec_ctor(grid->buttons, CAMERA_GRID_BUTTONS, sizeof(CellAnim), func_0208a1f8, func_0208a1f4);
    grid->state = CAMERA_GRID_CLOSED;
    grid->cursor = 0;
    grid->column = 0;
    grid->row = 0;
    grid->chosen = 0;
    grid->asked_open = 0;
    return grid;
}
CLEAN_AS(func_0208c834, CameraGrid_Construct)
