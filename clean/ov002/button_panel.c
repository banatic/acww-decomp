/* The menu scenes' button panel (button_panel.h). */
#include "button_panel.h"

#include <assert.h>
#include <limits.h>
#include <stddef.h>

#include "clean.h"

static_assert(sizeof(PanelSprite) == 0x7c && offsetof(PanelSprite, flags) == 0x78, "panel sprite");
static_assert(offsetof(ButtonPanel, window) == 0xfc && offsetof(ButtonPanel, selected) == 0x1c9, "button panel");

/* By button: its x and y (in the layouts that sit low) and its sprite. The functions read
 * them at the index they are given, as the game does. */
extern const u8 data_ov002_0220ba5c[];
extern const u8 data_ov002_0220ba68[];
extern const u8 data_ov002_0220ba74[];

extern u8 data_021f6c58; /* the touch's x, as a byte */
extern u8 data_021f6c54; /* the touch's y */

extern int func_ov002_0220b12c(PanelSprite *sprite);  /* flag 4 set */
extern void func_ov002_0220b138(PanelSprite *sprite); /* clear flag 4 */
extern void func_ov002_0220b144(PanelSprite *sprite); /* set flag 4 */
extern void func_ov002_0220b150(PanelSprite *sprite); /* clear flag 2 */
extern void func_ov002_0220b15c(PanelSprite *sprite); /* set flag 2 */
extern int func_ov002_0220b168(PanelSprite *sprite);  /* step the press */
extern int func_ov002_0220b280(PanelSprite *sprite);  /* the press's frame */
extern void func_0208aa70(u8 *window);                /* byte 0x5b = 1 */
extern void func_0208aa90(u8 *window);                /* byte 0x58 = 0 */
extern void func_0208aa98(u8 *window);                /* byte 0x58 = 1 */

#define SELECTED (-1)

/* The sprite at index `sprite`; only 0 and 1 are the panel's. */
static PanelSprite *sprite_at(ButtonPanel *panel, int sprite)
{
    return (PanelSprite *) ((u8 *) panel->sprites + sprite * (int) sizeof(PanelSprite));
}

static int button_or_selected(ButtonPanel *panel, int button)
{
    return button == SELECTED ? panel->selected : button;
}

/* How much higher than the table's places a layout puts the buttons. */
static int layout_rise(int layout)
{
    switch (layout) {
        case 8:
            return 0x1e;
        case 12:
            return 0x20;
        case 13:
            return 0xe;
        default:
            return 0;
    }
}

/* func_ov002_0220a620: whether the sprite of `button` (or the selected one, for -1) has
 * flag 4. */
int ButtonPanel_HasSpriteFlag4(ButtonPanel *panel, int button)
{
    return func_ov002_0220b12c(sprite_at(panel, ButtonPanel_SpriteOf(panel, button)));
}
CLEAN_AS(func_ov002_0220a620, ButtonPanel_HasSpriteFlag4)

/* func_ov002_0220a63c */
void ButtonPanel_ClearSpriteFlag4(ButtonPanel *panel, int button)
{
    func_ov002_0220b138(sprite_at(panel, ButtonPanel_SpriteOf(panel, button)));
}
CLEAN_AS(func_ov002_0220a63c, ButtonPanel_ClearSpriteFlag4)

/* func_ov002_0220a658 */
void ButtonPanel_SetSpriteFlag4(ButtonPanel *panel, int button)
{
    func_ov002_0220b144(sprite_at(panel, ButtonPanel_SpriteOf(panel, button)));
}
CLEAN_AS(func_ov002_0220a658, ButtonPanel_SetSpriteFlag4)

/* func_ov002_0220a674: the sprite (0 or 1) that shows `button`, the selected one for -1. */
int ButtonPanel_SpriteOf(ButtonPanel *panel, int button)
{
    return data_ov002_0220ba74[button_or_selected(panel, button)];
}
CLEAN_AS(func_ov002_0220a674, ButtonPanel_SpriteOf)

/* func_ov002_0220a690: clears the window's byte 0x58 and flag 2 of both sprites. */
void ButtonPanel_ClearFlag2(ButtonPanel *panel)
{
    func_0208aa90(panel->window);
    for (int i = 0; i < BUTTON_PANEL_SPRITES; i++) {
        func_ov002_0220b150(&panel->sprites[i]);
    }
}
CLEAN_AS(func_ov002_0220a690, ButtonPanel_ClearFlag2)

/* func_ov002_0220a6b8: sets the window's byte 0x58 and flag 2 of both sprites. */
void ButtonPanel_SetFlag2(ButtonPanel *panel)
{
    func_0208aa98(panel->window);
    for (int i = 0; i < BUTTON_PANEL_SPRITES; i++) {
        func_ov002_0220b15c(&panel->sprites[i]);
    }
}
CLEAN_AS(func_ov002_0220a6b8, ButtonPanel_SetFlag2)

/* func_ov002_0220a6e0: the frame of the press of the selected button's sprite. */
int ButtonPanel_SelectedPressFrame(ButtonPanel *panel)
{
    return func_ov002_0220b280(sprite_at(panel, ButtonPanel_SpriteOf(panel, SELECTED)));
}
CLEAN_AS(func_ov002_0220a6e0, ButtonPanel_SelectedPressFrame)

/* func_ov002_0220a700: one step of the press of the selected button's sprite; 0 once it is
 * over. */
int ButtonPanel_StepSelectedPress(ButtonPanel *panel)
{
    return func_ov002_0220b168(sprite_at(panel, ButtonPanel_SpriteOf(panel, SELECTED)));
}
CLEAN_AS(func_ov002_0220a700, ButtonPanel_StepSelectedPress)

/* func_ov002_0220a720 */
ButtonPanel *ButtonPanel_Select(ButtonPanel *panel, int button)
{
    panel->selected = (u8) button;
    return panel;
}
CLEAN_AS(func_ov002_0220a720, ButtonPanel_Select)

/* func_ov002_0220a72c: the y of `button` (the selected one for -1) in the panel's layout. */
int ButtonPanel_ButtonY(ButtonPanel *panel, int button)
{
    int y = data_ov002_0220ba68[button_or_selected(panel, button)];
    return y - layout_rise(panel->layout);
}
CLEAN_AS(func_ov002_0220a72c, ButtonPanel_ButtonY)

/* func_ov002_0220a768: the x of `button` (the selected one for -1). */
int ButtonPanel_ButtonX(ButtonPanel *panel, int button)
{
    return data_ov002_0220ba5c[button_or_selected(panel, button)];
}
CLEAN_AS(func_ov002_0220a768, ButtonPanel_ButtonX)

/* func_ov002_0220a784: whether the touch is in the area of `button`, the areas moving up with
 * the layout as the buttons do. */
int ButtonPanel_IsTouched(ButtonPanel *panel, int button)
{
    int x = data_021f6c58;
    int y = data_021f6c54 + layout_rise(panel->layout);
    return ButtonPanel_HitTest(panel, button, x, y);
}
CLEAN_AS(func_ov002_0220a784, ButtonPanel_IsTouched)

/* The touch area of a button, edges included. */
typedef struct TouchArea {
    int left;
    int right;
    int top;
    int bottom;
} TouchArea;

/* QUIRK: the areas of buttons 1, 2 and 9 have no right edge. */
static const TouchArea touch_areas[BUTTON_PANEL_BUTTONS] = {
    {0x52, 0xba, 0xac, 0xc0}, {0xc0, INT_MAX, 0x95, 0xa4}, {0xc0, INT_MAX, 0xa9, 0xb8}, {0x38, 0x68, 0xa4, 0xb3},
    {0x98, 0xc8, 0xa4, 0xb3}, {0x00, 0x40, 0xac, 0xc0},    {0xc0, 0x100, 0xac, 0xc0},   {0x78, 0xb8, 0xac, 0xc0},
    {0x6a, 0xbc, 0xac, 0xc0}, {0xc0, INT_MAX, 0xac, 0xc0},
};

/* func_ov002_0220a7c0: whether the point (x, y) is in the touch area of `button` (0-9; any
 * other number has none), with the panel low on the screen. */
int ButtonPanel_HitTest(ButtonPanel *panel, int button, int x, int y)
{
    (void) panel;
    if (button < 0 || button >= BUTTON_PANEL_BUTTONS) {
        return 0;
    }
    const TouchArea *area = &touch_areas[button];
    return x >= area->left && x <= area->right && y >= area->top && y <= area->bottom;
}
CLEAN_AS(func_ov002_0220a7c0, ButtonPanel_HitTest)

/* func_ov002_0220a8dc: sets the window's byte 0x5b. */
void ButtonPanel_SetWindowFlag5b(ButtonPanel *panel)
{
    func_0208aa70(panel->window);
}
CLEAN_AS(func_ov002_0220a8dc, ButtonPanel_SetWindowFlag5b)
