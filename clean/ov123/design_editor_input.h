/* The design editor's input (design_editor.h): the pen on the canvas and on the places, the
 * d-pad's two cursors (the key cursor on the places, drawn by the cursor sprite, and the canvas
 * cursor on the pixels), the commands of the places and the sub states that read them. */
#ifndef CLEAN_OV123_DESIGN_EDITOR_INPUT_H
#define CLEAN_OV123_DESIGN_EDITOR_INPUT_H

#include "design_editor.h"
#include "types.h"

void DesignEditor_FollowPen(DesignEditor *self);
void DesignEditor_BeginPenDraw(DesignEditor *self);
int DesignEditor_ColourByShoulders(DesignEditor *self);
int DesignEditor_MoveCanvasCursor(DesignEditor *self, int keys, int quiet);
int DesignEditor_MovePlaceCursor(DesignEditor *self, int keys);
void DesignEditor_GlideToPlace(DesignEditor *self);
void DesignEditor_PressCursorSprite(DesignEditor *self);
void DesignEditor_BeginPress(DesignEditor *self);
void DesignEditor_ShowCursorIdle(DesignEditor *self);
void DesignEditor_HideCursor(DesignEditor *self);
unsigned char DesignEditor_PlaceY(DesignEditor *self);
unsigned char DesignEditor_PlaceX(DesignEditor *self);
void DesignEditor_PlaceCursorSprite(DesignEditor *self);
void DesignEditor_FinishShape(DesignEditor *self);
void DesignEditor_PickColour(DesignEditor *self);
void DesignEditor_DrawShape(DesignEditor *self);
void DesignEditor_PressCanvasByKeys(DesignEditor *self);
void DesignEditor_PressCanvasByTouch(DesignEditor *self);
void DesignEditor_UseTool(DesignEditor *self, int px, int py);
void DesignEditor_PenToPixel(DesignEditor *self);
int DesignEditor_ScreenY(DesignEditor *unused, int py);
int DesignEditor_ScreenX(DesignEditor *unused, int px);
void DesignEditor_RunCommand(DesignEditor *self);
int DesignEditor_PlaceUnderPen(DesignEditor *self);
int DesignEditor_PlaceAt(DesignEditor *self, int x, int y);
void DesignEditor_PressPanel(DesignEditor *self, unsigned int state, unsigned int button);
void DesignEditor_ChooseQuit(DesignEditor *self);
void DesignEditor_ChooseSave(DesignEditor *self);
void DesignEditor_EnterPanel(DesignEditor *self);
void DesignEditor_EnterPanelByKeys(DesignEditor *self);
void DesignEditor_EnterPanelByTouch(DesignEditor *self);
void DesignEditor_EnterIdle(DesignEditor *self);
void DesignEditor_EnterIdleByKeys(DesignEditor *self);
void DesignEditor_EnterIdleByTouch(DesignEditor *self);
void DesignEditor_WaitPanelPress(DesignEditor *self);
void DesignEditor_FinishPress(DesignEditor *self);
void DesignEditor_PressAtCursor(DesignEditor *self);
void DesignEditor_WaitCursorSprite(DesignEditor *self);
void DesignEditor_PanelByKeys(DesignEditor *self);
void DesignEditor_PickByKeys(DesignEditor *self);
void DesignEditor_ShapeByKeys(DesignEditor *self);
void DesignEditor_DrawByKeys(DesignEditor *self);
void DesignEditor_CanvasByKeys(DesignEditor *self);
void DesignEditor_PlacesByKeys(DesignEditor *self);
void DesignEditor_DrawByTouch(DesignEditor *self);
void DesignEditor_PanelByTouch(DesignEditor *self);
void DesignEditor_IdleByTouch(DesignEditor *self);

#endif
