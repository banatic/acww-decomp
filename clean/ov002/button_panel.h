/* A panel of the menu scenes at the bottom of the touch screen (at 0x4698 in ov122's scene;
 * used by overlays from 101 to 146): a window of ov002's (func_ov002_0220b04c and
 * func_ov002_0220b06c fill it, as for the paged choice) with two button sprites over it.
 *
 * The panel knows ten buttons by number (0-9), each with a place, a touch area and the sprite
 * (0 or 1) that shows it; `selected` is the button the functions given -1 act on. The functions
 * from func_ov002_0220a8e8 on set up the panel in one of its layouts (6, 7, 9, 12 or 13; 8 is
 * also tested); layouts 8, 12 and 13 sit higher on the screen. */
#ifndef CLEAN_OV002_BUTTON_PANEL_H
#define CLEAN_OV002_BUTTON_PANEL_H

#include "types.h"

#define BUTTON_PANEL_BUTTONS 10
#define BUTTON_PANEL_SPRITES 2

/* A button sprite: what it shows (func_ov002_0220b36c) and a byte of flags at 0x78
 * (func_ov002_0220b29c clears, func_ov002_0220b2ac sets, func_ov002_0220b2bc tests). */
typedef struct PanelSprite {
    u8 unk_00[0x75];
    u8 press_step; /* 0x75: func_ov002_0220b168 counts it up to 2 */
    u8 unk_76[2];
    u8 flags; /* 0x78 */
    u8 pad_79[3];
} PanelSprite;

typedef struct ButtonPanel {
    u32 unk_00;
    PanelSprite sprites[BUTTON_PANEL_SPRITES]; /* 0x04 */
    u8 window[0xcc];                           /* 0xfc */
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

#endif
