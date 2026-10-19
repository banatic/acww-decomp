/* The menu scenes' button panel (button_panel.h). */
#include "button_panel.h"

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/sliding_window.h"

static_assert(sizeof(PanelSprite) == 0x7c && offsetof(PanelSprite, flags) == 0x78, "panel sprite");
static_assert(offsetof(ButtonPanel, window) == 0xfc && offsetof(ButtonPanel, selected) == 0x1c9, "button panel");

/* By button: its x and y (in the layouts that sit low) and its sprite. The functions read
 * them at the index they are given, as the game does. */
extern const u8 data_ov002_0220ba5c[];
extern const u8 data_ov002_0220ba68[];
extern const u8 data_ov002_0220ba74[];

extern u8 data_021f6c58; /* the touch's x, as a byte */
extern u8 data_021f6c54; /* the touch's y */

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
    return PanelSprite_HasFlag4(sprite_at(panel, ButtonPanel_SpriteOf(panel, button)));
}
CLEAN_AS(func_ov002_0220a620, ButtonPanel_HasSpriteFlag4)

/* func_ov002_0220a63c */
void ButtonPanel_ClearSpriteFlag4(ButtonPanel *panel, int button)
{
    PanelSprite_ClearFlag4(sprite_at(panel, ButtonPanel_SpriteOf(panel, button)));
}
CLEAN_AS(func_ov002_0220a63c, ButtonPanel_ClearSpriteFlag4)

/* func_ov002_0220a658 */
void ButtonPanel_SetSpriteFlag4(ButtonPanel *panel, int button)
{
    PanelSprite_SetFlag4(sprite_at(panel, ButtonPanel_SpriteOf(panel, button)));
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
    SlidingWindow_ClearObjWindow((SlidingWindow *) (void *) &panel->window);
    for (int i = 0; i < BUTTON_PANEL_SPRITES; i++) {
        PanelSprite_ClearFlag2(&panel->sprites[i]);
    }
}
CLEAN_AS(func_ov002_0220a690, ButtonPanel_ClearFlag2)

/* func_ov002_0220a6b8: sets the window's byte 0x58 and flag 2 of both sprites. */
void ButtonPanel_SetFlag2(ButtonPanel *panel)
{
    SlidingWindow_SetObjWindow((SlidingWindow *) (void *) &panel->window);
    for (int i = 0; i < BUTTON_PANEL_SPRITES; i++) {
        PanelSprite_SetFlag2(&panel->sprites[i]);
    }
}
CLEAN_AS(func_ov002_0220a6b8, ButtonPanel_SetFlag2)

/* func_ov002_0220a6e0: the frame of the press of the selected button's sprite. */
int ButtonPanel_SelectedPressFrame(ButtonPanel *panel)
{
    return PanelSprite_PressDepth(sprite_at(panel, ButtonPanel_SpriteOf(panel, SELECTED)));
}
CLEAN_AS(func_ov002_0220a6e0, ButtonPanel_SelectedPressFrame)

/* func_ov002_0220a700: one step of the press of the selected button's sprite; 0 once it is
 * over. */
int ButtonPanel_StepSelectedPress(ButtonPanel *panel)
{
    return PanelSprite_StepPress(sprite_at(panel, ButtonPanel_SpriteOf(panel, SELECTED)));
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
    SlidingWindow_ShowExtra((SlidingWindow *) (void *) &panel->window);
}
CLEAN_AS(func_ov002_0220a8dc, ButtonPanel_SetWindowFlag5b)

/* The panel's class. */
extern const u8 data_ov002_0220bd08[];  /* the panel's vtable */
extern const u16 data_ov002_0220ba58[]; /* the two text colours, 14 and 15 */
extern void GXS_LoadOBJPltt(const void *src, u32 offset, u32 size);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void *func_ov002_0220b3a4(void *sprite); /* PanelSprite_Destroy, for the array */
extern void *func_ov002_0220b3c4(void *sprite); /* PanelSprite_Construct, for the array */

/* The cells the layouts give the sprites, with the text's width and the shadow's cell each
 * is given. */
extern const PanelCell data_ov002_0220bd20[]; /* 4 wide, shadow 1 */
extern const PanelCell data_ov002_0220bd38[]; /* 4 wide, shadow 1 */
extern const PanelCell data_ov002_0220bdc0[]; /* 6 wide, shadow 1 */
extern const PanelCell data_ov002_0220bde0[]; /* 8 wide, shadow 2 */
extern const PanelCell data_ov002_0220be08[]; /* 6 wide, shadow 2 */
extern const PanelCell data_ov002_0220be38[]; /* 6 wide, shadow 2 */
extern const PanelCell data_ov002_0220be68[]; /* 12 wide, shadow 3 */

/* The window's draw, its vtable slot 2. */
#define WINDOW_SLOT_DRAW 2

/* The sprites' priority argument, -1 in every layout. */
#define SPRITE_PRIORITY (-1)

/* The x at which the window opens. */
#define WINDOW_X 0x80

/* QUIRK: the layout functions return 0x1c8, the offset of `layout`, which the callers
 * ignore. */
#define LAYOUT_RESULT 0x1c8

typedef void WindowMethod(MessageWindow *window);

/* Sprite `index` shows `message` in `cells`. */
static void show_sprite(ButtonPanel *panel, int index, const PanelCell *cells, u8 text_cells, u8 shadow_cell, int message)
{
    PanelSprite_SetCells(&panel->sprites[index], cells, text_cells, shadow_cell);
    PanelSprite_Show(&panel->sprites[index], message);
}

/* Closes the window and opens it again with `message` at height `y`. */
static void reopen_window(ButtonPanel *panel, int message, int y)
{
    MessageWindow_Close(&panel->window);
    MessageWindow_Open(&panel->window, message, WINDOW_X, y);
}

static int set_layout(ButtonPanel *panel, u8 layout)
{
    panel->layout = layout;
    return LAYOUT_RESULT;
}

/* func_ov002_0220a8e8: the window with `message` at height 0x12 and its second layer
 * (func_0208aa70), messages 4 and 0x13 on the sprites. */
int ButtonPanel_SetLayout13(ButtonPanel *panel, int message)
{
    reopen_window(panel, message, 0x12);
    SlidingWindow_ShowExtra((SlidingWindow *) (void *) &panel->window);
    ButtonPanel_ShowMessages4And13(panel);
    return set_layout(panel, 13);
}
CLEAN_AS(func_ov002_0220a8e8, ButtonPanel_SetLayout13)

/* func_ov002_0220a924: as layout 13 with the window at 0x2a. */
int ButtonPanel_SetLayout12(ButtonPanel *panel, int message)
{
    reopen_window(panel, message, 0x2a);
    SlidingWindow_ShowExtra((SlidingWindow *) (void *) &panel->window);
    ButtonPanel_ShowMessages4And13(panel);
    return set_layout(panel, 12);
}
CLEAN_AS(func_ov002_0220a924, ButtonPanel_SetLayout12)

/* func_ov002_0220a960: the window at 0x22 without its second layer (func_0208aa68). */
int ButtonPanel_SetLayout11(ButtonPanel *panel, int message)
{
    reopen_window(panel, message, 0x22);
    SlidingWindow_HideExtra((SlidingWindow *) (void *) &panel->window);
    ButtonPanel_ShowMessages4And13(panel);
    return set_layout(panel, 11);
}
CLEAN_AS(func_ov002_0220a960, ButtonPanel_SetLayout11)

/* func_ov002_0220a99c: the window left as it is, messages 0x15 and 0x19 on the sprites. */
int ButtonPanel_SetLayout10(ButtonPanel *panel)
{
    show_sprite(panel, 0, data_ov002_0220be08, 6, 2, 0x15);
    show_sprite(panel, 1, data_ov002_0220be38, 6, 2, 0x19);
    return set_layout(panel, 10);
}
CLEAN_AS(func_ov002_0220a99c, ButtonPanel_SetLayout10)

/* func_ov002_0220a9e4: the window at 4 without its second layer. */
int ButtonPanel_SetLayout9(ButtonPanel *panel, int message)
{
    reopen_window(panel, message, 4);
    SlidingWindow_HideExtra((SlidingWindow *) (void *) &panel->window);
    ButtonPanel_ShowMessages4And13(panel);
    return set_layout(panel, 9);
}
CLEAN_AS(func_ov002_0220a9e4, ButtonPanel_SetLayout9)

/* func_ov002_0220aa20: messages 4 and 0x13 on the sprites, in 6-cell buttons. */
void ButtonPanel_ShowMessages4And13(ButtonPanel *panel)
{
    show_sprite(panel, 0, data_ov002_0220be08, 6, 2, 4);
    show_sprite(panel, 1, data_ov002_0220be38, 6, 2, 0x13);
}
CLEAN_AS(func_ov002_0220aa20, ButtonPanel_ShowMessages4And13)

/* Messages 4 and 0x13 on the sprites, in 4-cell buttons. */
static void show_small_4_and_13(ButtonPanel *panel)
{
    show_sprite(panel, 0, data_ov002_0220bd38, 4, 1, 4);
    show_sprite(panel, 1, data_ov002_0220bd20, 4, 1, 0x13);
}

/* func_ov002_0220aa60: the window at 0x11 without its second layer, messages 4 and 0x13 in
 * 4-cell buttons. */
int ButtonPanel_SetLayout8(ButtonPanel *panel, int message)
{
    reopen_window(panel, message, 0x11);
    SlidingWindow_HideExtra((SlidingWindow *) (void *) &panel->window);
    show_small_4_and_13(panel);
    return set_layout(panel, 8);
}
CLEAN_AS(func_ov002_0220aa60, ButtonPanel_SetLayout8)

/* func_ov002_0220aacc: as layout 8 with the window at 4. */
int ButtonPanel_SetLayout7(ButtonPanel *panel, int message)
{
    reopen_window(panel, message, 4);
    SlidingWindow_HideExtra((SlidingWindow *) (void *) &panel->window);
    show_small_4_and_13(panel);
    return set_layout(panel, 7);
}
CLEAN_AS(func_ov002_0220aacc, ButtonPanel_SetLayout7)

/* func_ov002_0220ab38: message 0x21 on sprite 1, `message` on sprite 0. */
int ButtonPanel_SetLayout6(ButtonPanel *panel, int message)
{
    show_sprite(panel, 1, data_ov002_0220be08, 6, 2, 0x21);
    show_sprite(panel, 0, data_ov002_0220be38, 6, 2, message);
    return set_layout(panel, 6);
}
CLEAN_AS(func_ov002_0220ab38, ButtonPanel_SetLayout6)

/* func_ov002_0220ab84: `message` on sprite 1 only. QUIRK: the message is cut to a byte before
 * it is passed on, where layout 6 passes it whole (PanelSprite_SetMessage keeps a byte either
 * way). */
int ButtonPanel_SetLayout5(ButtonPanel *panel, int message)
{
    show_sprite(panel, 1, data_ov002_0220be08, 6, 2, (u8) message);
    return set_layout(panel, 5);
}
CLEAN_AS(func_ov002_0220ab84, ButtonPanel_SetLayout5)

/* func_ov002_0220abbc: message 0x21 on sprite 1, 0x65 on sprite 0. */
int ButtonPanel_SetLayout4(ButtonPanel *panel)
{
    show_sprite(panel, 1, data_ov002_0220be08, 6, 2, 0x21);
    show_sprite(panel, 0, data_ov002_0220be38, 6, 2, 0x65);
    return set_layout(panel, 4);
}
CLEAN_AS(func_ov002_0220abbc, ButtonPanel_SetLayout4)

/* func_ov002_0220ac04: the sprites of layout 4, which layout 3 draws elsewhere. */
int ButtonPanel_SetLayout3(ButtonPanel *panel)
{
    show_sprite(panel, 1, data_ov002_0220be08, 6, 2, 0x21);
    show_sprite(panel, 0, data_ov002_0220be38, 6, 2, 0x65);
    return set_layout(panel, 3);
}
CLEAN_AS(func_ov002_0220ac04, ButtonPanel_SetLayout3)

/* func_ov002_0220ac4c: message 0x21 on sprite 1 only. */
int ButtonPanel_SetLayout1(ButtonPanel *panel)
{
    show_sprite(panel, 1, data_ov002_0220bdc0, 6, 1, 0x21);
    return set_layout(panel, 1);
}
CLEAN_AS(func_ov002_0220ac4c, ButtonPanel_SetLayout1)

/* func_ov002_0220ac7c: message 0x20 on sprite 0 in a 12-cell button, 0x21 on sprite 1. */
int ButtonPanel_SetLayout2Wide(ButtonPanel *panel)
{
    show_sprite(panel, 0, data_ov002_0220be68, 0xc, 3, 0x20);
    show_sprite(panel, 1, data_ov002_0220bdc0, 6, 1, 0x21);
    return set_layout(panel, 2);
}
CLEAN_AS(func_ov002_0220ac7c, ButtonPanel_SetLayout2Wide)

/* func_ov002_0220acc4: message 2 on sprite 0 in an 8-cell button, 0x21 on sprite 1. */
int ButtonPanel_SetLayout2(ButtonPanel *panel)
{
    show_sprite(panel, 0, data_ov002_0220bde0, 8, 2, 2);
    show_sprite(panel, 1, data_ov002_0220bdc0, 6, 1, 0x21);
    return set_layout(panel, 2);
}
CLEAN_AS(func_ov002_0220acc4, ButtonPanel_SetLayout2)

/* func_ov002_0220ad0c: layout 0, in which ButtonPanel_Draw draws nothing. */
ButtonPanel *ButtonPanel_ClearLayout(ButtonPanel *panel)
{
    panel->layout = 0;
    return panel;
}
CLEAN_AS(func_ov002_0220ad0c, ButtonPanel_ClearLayout)

/* The window moved by (0, dy) from its place and drawn. */
static void draw_window(ButtonPanel *panel, int dy)
{
    SlidingWindow_SetPlace((SlidingWindow *) (void *) &panel->window, 0, dy);
    const u32 *vtable = panel->window.vtable;
    ((WindowMethod *) (uintptr_t) vtable[WINDOW_SLOT_DRAW])(&panel->window);
}

static void draw_sprite(ButtonPanel *panel, int index, int x, int y)
{
    PanelSprite_Draw(&panel->sprites[index], x, y, SPRITE_PRIORITY);
}

/* func_ov002_0220ad18: draws the panel in its layout. `wipe_offset` is the scene's wipe's
 * vertical displacement (MenuScene_WipeOffsetY): the panel moves with it, by all, half or a
 * quarter of it depending on the layout. */
void ButtonPanel_Draw(ButtonPanel *panel, int wipe_offset)
{
    int layout = panel->layout;
    int half = wipe_offset >> 1;
    int quarter = wipe_offset >> 2;

    switch (layout) {
        case 1:
            draw_sprite(panel, 1, 0, wipe_offset + 0xac);
            break;
        case 2:
            draw_sprite(panel, 0, 0, wipe_offset + 0xac);
            draw_sprite(panel, 1, 0, wipe_offset + 0xac);
            break;
        case 3:
            draw_sprite(panel, 1, 0x3c, wipe_offset + 0x35);
            draw_sprite(panel, 0, 0x3c, wipe_offset + 0x48);
            break;
        case 4:
            draw_sprite(panel, 1, 0x3c, wipe_offset + 0x4c);
            draw_sprite(panel, 0, -0x7c, wipe_offset + 0x4c);
            break;
        case 5:
            draw_sprite(panel, 1, 0x3c, wipe_offset + 0x4c);
            break;
        case 6:
            draw_sprite(panel, 1, 0x3c, wipe_offset + 0x4c);
            draw_sprite(panel, 0, -0xc, wipe_offset + 0x4c);
            break;
        case 7:
        case 9:
        case 10:
            /* Layout 10 does not draw the window. */
            if (layout != 10) {
                draw_window(panel, -quarter);
            }
            /* The layout is read again after the window's draw, as the original does. */
            if (panel->layout == 7) {
                draw_sprite(panel, 0, 0, quarter);
                draw_sprite(panel, 1, 0, quarter);
            } else {
                draw_sprite(panel, 0, -0x50, quarter + 0x44);
                draw_sprite(panel, 1, 0x10, quarter + 0x44);
            }
            break;
        case 8:
            draw_window(panel, -quarter - 8);
            draw_sprite(panel, 0, 0, half - 0x1e);
            draw_sprite(panel, 1, 0, half - 0x1e);
            break;
        case 11:
            draw_window(panel, -half);
            draw_sprite(panel, 0, -0x50, half + 0x44);
            draw_sprite(panel, 1, 0x10, half + 0x44);
            break;
        case 12:
            draw_window(panel, -half);
            draw_sprite(panel, 0, -0x50, half + 0x24);
            draw_sprite(panel, 1, 0x10, half + 0x24);
            break;
        case 13:
            draw_window(panel, -half);
            draw_sprite(panel, 0, -0x50, half + 0x36);
            draw_sprite(panel, 1, 0x10, half + 0x36);
            break;
        default: /* layout 0 and any other */
            break;
    }
}
CLEAN_AS(func_ov002_0220ad18, ButtonPanel_Draw)

/* func_ov002_0220af74: frees both sprites' text boxes. */
void ButtonPanel_CloseTexts(ButtonPanel *panel)
{
    for (int i = 0; i < BUTTON_PANEL_SPRITES; i++) {
        PanelSprite_CloseText(&panel->sprites[i]);
    }
}
CLEAN_AS(func_ov002_0220af74, ButtonPanel_CloseTexts)

/* func_ov002_0220af94: loads the sprites' two text colours into entries 14 and 15 of the sub
 * screen's first sprite palette. The panel is not read. */
void ButtonPanel_LoadTextColors(ButtonPanel *panel)
{
    (void) panel;
    GXS_LoadOBJPltt(data_ov002_0220ba58, PANEL_TEXT_COLOR_PRESSED * sizeof(u16), 2 * sizeof(u16));
}
CLEAN_AS(func_ov002_0220af94, ButtonPanel_LoadTextColors)

/* The destructor's body: the window, then the sprites from the last. */
static void destroy(ButtonPanel *panel)
{
    panel->vtable = data_ov002_0220bd08;
    MessageWindow_Destroy(&panel->window);
    __cxa_vec_cleanup(panel->sprites, BUTTON_PANEL_SPRITES, sizeof(PanelSprite),
                      (void (*)(void *))(uintptr_t) func_ov002_0220b3a4);
}

/* func_ov002_0220afa8 (vtable entry 1): destructs and frees the panel. */
ButtonPanel *ButtonPanel_Delete(ButtonPanel *panel)
{
    destroy(panel);
    Heap_OperatorDeleteB(panel);
    return panel;
}
CLEAN_AS(func_ov002_0220afa8, ButtonPanel_Delete)

/* func_ov002_0220afdc (vtable entry 0) */
ButtonPanel *ButtonPanel_Destroy(ButtonPanel *panel)
{
    destroy(panel);
    return panel;
}
CLEAN_AS(func_ov002_0220afdc, ButtonPanel_Destroy)

/* func_ov002_0220b008: the sprites and the window constructed, in layout 0; `selected` is left
 * as it was. */
ButtonPanel *ButtonPanel_Construct(ButtonPanel *panel)
{
    panel->vtable = data_ov002_0220bd08;
    __cxa_vec_ctor(panel->sprites, BUTTON_PANEL_SPRITES, sizeof(PanelSprite),
                   (void (*)(void *))(uintptr_t) func_ov002_0220b3c4, (void (*)(void *))(uintptr_t) func_ov002_0220b3a4);
    MessageWindow_Construct(&panel->window);
    panel->layout = 0;
    return panel;
}
CLEAN_AS(func_ov002_0220b008, ButtonPanel_Construct)
