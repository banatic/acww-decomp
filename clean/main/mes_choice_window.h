/* The message window of the talk's choice window (talk_windows.h): the class of vtable
 * 0x020e3ffc (0x78 bytes) that derives from the message background (mes_bg.h) and holds the
 * marker (a cell layer sprite, cell_layer_sprite.h) at 0x20, drawn beside the line of the
 * cursor while the input shown is the buttons.
 *
 * The talk's window sets the cursor each frame; when a choice is taken the marker plays its
 * press animation, then the chosen line flashes for a few frames before the window closes.
 * The marker's animations are the cell layer sprite's numbers 0 (hidden), 7 (beside the line)
 * and 8 (pressed). */
#ifndef CLEAN_MAIN_MES_CHOICE_WINDOW_H
#define CLEAN_MAIN_MES_CHOICE_WINDOW_H

#include "mes_bg.h"
#include "types.h"

typedef struct MesChoiceWindow {
    MesBg bg;           /* 0x00: vtable 0x020e3ffc */
    MesBgMarker marker; /* 0x20 */
    s32 cursor;         /* 0x6c: the line the cursor is on */
    s32 flash_frame;    /* 0x70: frames of the chosen line's flash so far */
    u8 buttons;         /* 0x74: the input shown is the buttons */
    u8 pad_75[3];
} MesChoiceWindow;

void MesChoiceWindow_SetButtons(MesChoiceWindow *self, u8 buttons, int sound);
int MesChoiceWindow_FlashChoice(MesChoiceWindow *self, int line);
void MesChoiceWindow_ResetFlash(MesChoiceWindow *self);
void MesChoiceWindow_SetCursor(MesChoiceWindow *self, int line);
void MesChoiceWindow_PressMarker(MesChoiceWindow *self);
void MesChoiceWindow_HideMarker(MesChoiceWindow *self);
void MesChoiceWindow_Open(MesChoiceWindow *self);
int MesChoiceWindow_PressDone(MesChoiceWindow *self);
int MesChoiceWindow_MarkerBeside(MesChoiceWindow *self);
void MesChoiceWindow_Draw(MesChoiceWindow *self);
void MesChoiceWindow_Update(MesChoiceWindow *self);
MesChoiceWindow *MesChoiceWindow_DestructDelete(MesChoiceWindow *self);
MesChoiceWindow *MesChoiceWindow_Destruct(MesChoiceWindow *self);
MesChoiceWindow *MesChoiceWindow_Construct(MesChoiceWindow *self);

#endif
