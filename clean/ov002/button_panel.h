/* A panel of the menu scenes at the bottom of the touch screen (at 0x4698 in ov122's scene;
 * used by overlays from 101 to 146; class vtable 0x0220bd08, constructor
 * func_ov002_0220b008, destructor func_ov002_0220afdc): a message window (message_window.h)
 * with two button sprites (panel_sprite.h) over it.
 *
 * The panel knows ten buttons by number (0-9), each with a place, a touch area and the sprite
 * (0 or 1) that shows it; `selected` is the button the functions given -1 act on. The functions
 * from func_ov002_0220a8e8 to func_ov002_0220ad0c set up the panel in one of its layouts
 * (0-13): which cells and messages the sprites show and whether the window is open.
 * ButtonPanel_Draw places them by layout, moved with the scene's wipe; layouts 8, 12 and 13
 * sit higher on the screen. */
#ifndef CLEAN_OV002_BUTTON_PANEL_H
#define CLEAN_OV002_BUTTON_PANEL_H

#include "message_window.h"
#include "panel_sprite.h"
#include "types.h"

#define BUTTON_PANEL_BUTTONS 10
#define BUTTON_PANEL_SPRITES 2

typedef struct ButtonPanel {
    const void *vtable;                        /* data_ov002_0220bd08 */
    PanelSprite sprites[BUTTON_PANEL_SPRITES]; /* 0x04 */
    MessageWindow window;                      /* 0xfc */
    u8 layout;                                 /* 0x1c8 */
    u8 selected;                               /* 0x1c9: the button that -1 stands for */
} ButtonPanel;

int ButtonPanel_HasSpriteFlag4(ButtonPanel *panel, int button);
void ButtonPanel_ClearSpriteFlag4(ButtonPanel *panel, int button);
void ButtonPanel_SetSpriteFlag4(ButtonPanel *panel, int button);
int ButtonPanel_SpriteOf(ButtonPanel *panel, int button);
void ButtonPanel_ClearFlag2(ButtonPanel *panel);
void ButtonPanel_SetFlag2(ButtonPanel *panel);
int ButtonPanel_SelectedPressFrame(ButtonPanel *panel);
int ButtonPanel_StepSelectedPress(ButtonPanel *panel);
ButtonPanel *ButtonPanel_Select(ButtonPanel *panel, int button);
int ButtonPanel_ButtonY(ButtonPanel *panel, int button);
int ButtonPanel_ButtonX(ButtonPanel *panel, int button);
int ButtonPanel_IsTouched(ButtonPanel *panel, int button);
int ButtonPanel_HitTest(ButtonPanel *panel, int button, int x, int y);
void ButtonPanel_SetWindowFlag5b(ButtonPanel *panel);
int ButtonPanel_SetLayout13(ButtonPanel *panel, int message);
int ButtonPanel_SetLayout12(ButtonPanel *panel, int message);
int ButtonPanel_SetLayout11(ButtonPanel *panel, int message);
int ButtonPanel_SetLayout10(ButtonPanel *panel);
int ButtonPanel_SetLayout9(ButtonPanel *panel, int message);
void ButtonPanel_ShowMessages4And13(ButtonPanel *panel);
int ButtonPanel_SetLayout8(ButtonPanel *panel, int message);
int ButtonPanel_SetLayout7(ButtonPanel *panel, int message);
int ButtonPanel_SetLayout6(ButtonPanel *panel, int message);
int ButtonPanel_SetLayout5(ButtonPanel *panel, int message);
int ButtonPanel_SetLayout4(ButtonPanel *panel);
int ButtonPanel_SetLayout3(ButtonPanel *panel);
int ButtonPanel_SetLayout1(ButtonPanel *panel);
int ButtonPanel_SetLayout2Wide(ButtonPanel *panel);
int ButtonPanel_SetLayout2(ButtonPanel *panel);
ButtonPanel *ButtonPanel_ClearLayout(ButtonPanel *panel);
void ButtonPanel_Draw(ButtonPanel *panel, int wipe_offset);
void ButtonPanel_CloseTexts(ButtonPanel *panel);
void ButtonPanel_LoadTextColors(ButtonPanel *panel);
ButtonPanel *ButtonPanel_Delete(ButtonPanel *panel);
ButtonPanel *ButtonPanel_Destroy(ButtonPanel *panel);
ButtonPanel *ButtonPanel_Construct(ButtonPanel *panel);

#endif
