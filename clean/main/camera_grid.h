/* The window the menu tab opens (menu_tab.h, its member at 0x28): a sprite (vtable
 * data_020e2250, 0xd8 bytes, derived from main's screen sprite base, screen_sprite.h) of nine
 * buttons in a 3 by 3 grid on the touch screen, each choosing one of the field camera's preset
 * views (CameraControl_SelectPreset, camera_control.h): the centre button the middle view, the
 * others the view of their column (left to right) and row (top to bottom).
 *
 * The cursor moves by the d-pad while the buttons are chosen (MenuInput_UsesButtons), one step
 * a press, kept inside the grid; a tap on a button (16 by 16 pixels) puts it there while the
 * touch screen is chosen. A press that only switches the input (MenuInput_AnyPressed with
 * touch chosen, MenuInput_TouchPressed with buttons chosen) moves nothing. Once the cursor
 * moved, its button's preset is selected, with a sound telling whether the chosen button is
 * now higher, lower or on the same row; the chosen button is drawn in palette 6, the others
 * in palette 5.
 *
 * Its states (CameraGridState), stepped through a table of member functions by its update:
 * closed, until asked to open; opening, until the nine buttons' opening animations are done;
 * open, until asked to close; closing, until their closing animations are done. */
#ifndef CLEAN_MAIN_CAMERA_GRID_H
#define CLEAN_MAIN_CAMERA_GRID_H

#include "screen_icon.h" /* CellAnim */
#include "screen_sprite.h"
#include "types.h"

#define CAMERA_GRID_BUTTONS 9

enum CameraGridState {
    CAMERA_GRID_CLOSED = 0,
    CAMERA_GRID_OPENING = 1,
    CAMERA_GRID_OPEN = 2,
    CAMERA_GRID_CLOSING = 3,
};

typedef struct CameraGrid {
    ScreenSprite base;                     /* vtable data_020e2250 */
    CellAnim buttons[CAMERA_GRID_BUTTONS]; /* 0x0c: one animation a button */
    int state;                             /* 0xc0: CameraGridState */
    u32 cursor;                            /* 0xc4: the button at the cursor (0 the centre) */
    int column;                            /* 0xc8: the cursor's column, -1 to 1 */
    int row;                               /* 0xcc: the cursor's row, -1 to 1 */
    u32 chosen;                            /* 0xd0: the button whose preset was selected last */
    u8 asked_open;                         /* 0xd4: 1 asked to open, 0 to close */
    u8 pad_d5[3];
} CameraGrid;

void CameraGrid_StepClosing(CameraGrid *grid);
void CameraGrid_EnterClosing(CameraGrid *grid);
void CameraGrid_StepOpen(CameraGrid *grid);
void CameraGrid_EnterOpen(CameraGrid *grid);
void CameraGrid_StepOpening(CameraGrid *grid);
void CameraGrid_EnterOpening(CameraGrid *grid);
void CameraGrid_StepClosed(CameraGrid *grid);
void CameraGrid_EnterClosed(CameraGrid *grid);
void CameraGrid_PlaceFromCursor(CameraGrid *grid);
void CameraGrid_CursorFromPlace(CameraGrid *grid);
void CameraGrid_Choose(CameraGrid *grid);
int CameraGrid_MoveByPad(CameraGrid *grid);
int CameraGrid_MoveByTouch(CameraGrid *grid);
int CameraGrid_InputSwitches(void);
int CameraGrid_IsSettled(CameraGrid *grid);
int CameraGrid_IsOpen(CameraGrid *grid);
int CameraGrid_IsClosed(CameraGrid *grid);
void CameraGrid_AskOpen(CameraGrid *grid, u8 open);
int CameraGrid_CallDraw(CameraGrid *grid);
int CameraGrid_CallUpdate(CameraGrid *grid);
void CameraGrid_RestartButtons(CameraGrid *grid);
void CameraGrid_Reset(CameraGrid *grid);
void CameraGrid_Update(CameraGrid *grid);
void CameraGrid_Draw(CameraGrid *grid);
CameraGrid *CameraGrid_Delete(CameraGrid *grid);
CameraGrid *CameraGrid_Destruct(CameraGrid *grid);
CameraGrid *CameraGrid_Construct(CameraGrid *grid);

#endif
