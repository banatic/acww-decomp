/* The design editor's input (design_editor_input.h): the pen on the canvas and the places, the
 * d-pad's cursors, the commands of the places, and the sub states that read them. */
#include "design_editor_input.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "clean.h"
#include "design_editor.h"
#include "design_editor_canvas.h"
#include "main/cell_layer_sprite.h"
#include "main/group_params.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov002/key_repeat.h"

/* The buttons (main's PadState) and the touch: its point and whether the pen is down or went
 * down or up this frame (autoload_2/input.c). */
extern PadState data_021fbe40;
extern u8 data_021f6c58, data_021f6c54;
extern u8 data_021fbdd8, data_021fbddc;

#define DESIGN_EDITOR_PAD_A 0x0001
#define DESIGN_EDITOR_PAD_B 0x0002
#define DESIGN_EDITOR_PAD_START 0x0008
#define DESIGN_EDITOR_PAD_RIGHT 0x0010
#define DESIGN_EDITOR_PAD_LEFT 0x0020
#define DESIGN_EDITOR_PAD_UP 0x0040
#define DESIGN_EDITOR_PAD_DOWN 0x0080
#define DESIGN_EDITOR_PAD_R 0x0100
#define DESIGN_EDITOR_PAD_L 0x0200
#define DESIGN_EDITOR_PAD_X 0x0400
#define DESIGN_EDITOR_PAD_Y 0x0800

/* The places' sprite points (by DesignEditorPlace, 0x00-0x20). */
extern const u8 data_ov123_0229ca54[];
extern const u8 data_ov123_0229ca78[];

/* Where the d-pad moves the key cursor from each place. */
extern const u8 data_ov123_0229ca9c[]; /* up */
extern const u8 data_ov123_0229cac0[]; /* right */
extern const u8 data_ov123_0229cae4[]; /* down */
extern const u8 data_ov123_0229cb08[]; /* left */

/* The frames the pen stays on a place, drawing, before it presses it. */
#define DESIGN_EDITOR_HOVER_PRESS 0x14

/* The panel's buttons: the question's "yes" and "no" and the save and quit buttons. */
#define DESIGN_EDITOR_BUTTON_YES 3
#define DESIGN_EDITOR_BUTTON_NO 4
#define DESIGN_EDITOR_BUTTON_QUIT 8
#define DESIGN_EDITOR_BUTTON_SAVE 9

static MenuScene *de_scene(DesignEditor *self)
{
    return &self->base;
}

static int de_is_shape_tool(u8 tool)
{
    return tool >= DESIGN_EDITOR_TOOL_RECTANGLE && tool <= DESIGN_EDITOR_TOOL_LINE;
}

static int de_is_panel_place(u8 place)
{
    return (u8) (place - DESIGN_EDITOR_PLACE_SAVE) <= 1;
}

/* The pen went down this frame. */
static int de_pen_pressed(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* The cursor sprite's update through its class (vtable slot 3). */
static void de_update_cursor_sprite(DesignEditor *self)
{
    Glider *sprite = &self->cursor_sprite;
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* func_ov123_022996dc: a frame of the pen held down. The pixel under it found; while a pen
 * draws, its moves set the sound's level (by how far it went) and a line is drawn from the
 * pixel before. Then the place under it: held on one place (not the canvas) for 20 frames, that
 * place is pressed, the stroke ends and the pen sound stops, once until the pen leaves it. */
void DesignEditor_FollowPen(DesignEditor *self)
{
    u8 old_px = self->pen_px;
    u8 old_py = self->pen_py;
    DesignEditor_PenToPixel(self);
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_STROKE) != 0 && self->tool <= DESIGN_EDITOR_TOOL_PEN_3) {
        int x = data_021f6c58;
        int y = data_021f6c54;
        if (x != self->pen_x || y != self->pen_y) {
            int dx = self->pen_x - x;
            if (dx < 0) {
                dx = -dx;
            }
            int dy = self->pen_y - y;
            if (dy < 0) {
                dy = -dy;
            }
            SoundSys_SetHandleLevel(dx + dy);
            DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_PEN_MOVED);
        }
        if (self->pen_px != old_px || self->pen_py != old_py) {
            if (DesignEditor_Line(self, self->pen_px, self->pen_py, old_px, old_py, self->colour, self->tool) != 0) {
                SoundSys_PlaySe(0x861);
            }
            DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_DIRTY);
        }
    }
    u8 place = (u8) DesignEditor_PlaceUnderPen(self);
    if (place == DESIGN_EDITOR_PLACE_CANVAS || place == DESIGN_EDITOR_NO_PLACE) {
        self->hover = DESIGN_EDITOR_NO_PLACE;
    } else if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_PRESSED) != 0) {
        if (place != self->hover) {
            DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_PRESSED);
            self->hover_frames = 0;
        }
    } else if (place == self->hover) {
        self->hover_frames++;
        if (self->hover_frames >= DESIGN_EDITOR_HOVER_PRESS) {
            if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_PEN_SOUND) != 0) {
                DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_PEN_SOUND);
                DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_PEN_MOVED);
                SoundSys_StopSound(0x862, 1);
            }
            self->command = self->hover;
            DesignEditor_RunCommand(self);
            DesignEditor_EndShape(self);
            DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_STROKE);
            DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_PRESSED);
        }
    } else {
        self->hover = place;
        self->hover_frames = 0;
    }
}
CLEAN_AS(func_ov123_022996dc, DesignEditor_FollowPen)

/* func_ov123_02299878: drawing with the pen starts (sub state 2): nothing under it yet, and its
 * point kept. */
void DesignEditor_BeginPenDraw(DesignEditor *self)
{
    self->hover_frames = 0;
    self->hover = DESIGN_EDITOR_NO_PLACE;
    MenuScene_SetSubState(de_scene(self), DESIGN_EDITOR_SUB_DRAW);
    DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_PRESSED);
    self->pen_x = data_021f6c58;
    self->pen_y = data_021f6c54;
}
CLEAN_AS(func_ov123_02299878, DesignEditor_BeginPenDraw)

/* func_ov123_022998c0: L pressed takes the colour before (15 after 1), R the next (1 after 15).
 * Answers 1 when either was pressed. */
int DesignEditor_ColourByShoulders(DesignEditor *self)
{
    u16 pressed = data_021fbe40.pressed;
    if (pressed & DESIGN_EDITOR_PAD_L) {
        u8 colour = self->colour;
        DesignEditor_SetColour(self, colour > 1 ? (u8) (colour - 1) : 15);
        return 1;
    }
    if (pressed & DESIGN_EDITOR_PAD_R) {
        u8 colour = self->colour;
        DesignEditor_SetColour(self, colour < 15 ? (u8) (colour + 1) : 1);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov123_022998c0, DesignEditor_ColourByShoulders)

/* func_ov123_022999b0: the canvas cursor moved by the d-pad held (one pixel, within the
 * design); left before right and up before down win. A move waits for `key_delay`: a press
 * starts it at 4 and moves at once, a hold moves every fourth frame. A move plays sound 0x865
 * (unless `quiet`) and sets the sound player's byte to the cursor's x on the screen. Answers 1
 * when it moved. The keys handed in are not read. */
int DesignEditor_MoveCanvasCursor(DesignEditor *self, int keys, int quiet)
{
    (void) keys;
    u8 x = self->cursor_px;
    u8 y = self->cursor_py;
    u16 held = data_021fbe40.held;
    u16 pressed = data_021fbe40.pressed;
    if (held & DESIGN_EDITOR_PAD_LEFT) {
        if (pressed & DESIGN_EDITOR_PAD_LEFT) {
            self->key_delay = 4;
        }
        if (x != 0) {
            x--;
        }
    } else if (held & DESIGN_EDITOR_PAD_RIGHT) {
        if (pressed & DESIGN_EDITOR_PAD_RIGHT) {
            self->key_delay = 4;
        }
        if (x < DESIGN_EDITOR_SIZE - 1) {
            x++;
        }
    }
    if (held & DESIGN_EDITOR_PAD_UP) {
        if (pressed & DESIGN_EDITOR_PAD_UP) {
            self->key_delay = 4;
        }
        if (y != 0) {
            y--;
        }
    } else if (held & DESIGN_EDITOR_PAD_DOWN) {
        if (pressed & DESIGN_EDITOR_PAD_DOWN) {
            self->key_delay = 4;
        }
        if (y < DESIGN_EDITOR_SIZE - 1) {
            y++;
        }
    }
    if (self->cursor_px == x && self->cursor_py == y) {
        self->key_delay = 0;
        return 0;
    }
    if (self->key_delay != 0) {
        if (self->key_delay != 4) {
            self->key_delay--;
            return 0;
        }
        self->key_delay--;
    }
    self->cursor_px = x;
    self->cursor_py = y;
    if (quiet == 0) {
        SoundSys_PlaySe(0x865);
    }
    SoundSys_ChangePlayerByte((u8) DesignEditor_ScreenX(self, x));
    return 1;
}
CLEAN_AS(func_ov123_022999b0, DesignEditor_MoveCanvasCursor)

/* func_ov123_02299adc: the key cursor moved among the places by the keys that fired: up from
 * the panel's save or quit button goes to tool 5 (from the places) or the colours; else left
 * and right by their tables, then up and down by theirs (when left and right did nothing, or
 * from a tool). A move within the colours' row jumps the cursor sprite (sound 0x869). Answers 1
 * when it moved. */
int DesignEditor_MovePlaceCursor(DesignEditor *self, int keys)
{
    if (keys == 0) {
        return 0;
    }
    u8 from = self->key_place;
    if (KeyRepeat_HasUp(keys)) {
        if (self->key_place == DESIGN_EDITOR_PLACE_SAVE) {
            self->key_place = self->key_mode == DESIGN_EDITOR_KEYS_PLACES ? DESIGN_EDITOR_TOOL_UNDO : 0x1c;
            return 1;
        }
        if (self->key_place == DESIGN_EDITOR_PLACE_QUIT) {
            self->key_place = self->key_mode == DESIGN_EDITOR_KEYS_PLACES ? DESIGN_EDITOR_TOOL_UNDO : 0x16;
            return 1;
        }
    }
    if (KeyRepeat_HasLeft(keys)) {
        self->key_place = data_ov123_0229cb08[self->key_place];
    } else if (KeyRepeat_HasRight(keys)) {
        self->key_place = data_ov123_0229cac0[self->key_place];
    }
    if (from == self->key_place || self->key_place <= DESIGN_EDITOR_TOOL_CLEAR) {
        if (KeyRepeat_HasUp(keys)) {
            self->key_place = data_ov123_0229ca9c[self->key_place];
        } else if (KeyRepeat_HasDown(keys)) {
            self->key_place = data_ov123_0229cae4[self->key_place];
        }
    }
    u8 to = self->key_place;
    if (from == to) {
        return 0;
    }
    if (to >= DESIGN_EDITOR_PLACE_COLOUR_1 && to <= DESIGN_EDITOR_PLACE_COLOUR_15 && from >= DESIGN_EDITOR_PLACE_COLOUR_1 &&
        from <= DESIGN_EDITOR_PLACE_COLOUR_15) {
        DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_PLACE_AT_ONCE);
        SoundSys_PlaySe(0x869);
    }
    return 1;
}
CLEAN_AS(func_ov123_02299adc, DesignEditor_MovePlaceCursor)

/* func_ov123_02299c04: the cursor sprite sent to the key cursor's place (turned to set B on the
 * panel's buttons, set A elsewhere): at once when it jumps, else easing there in three steps
 * while sub state 9 waits, coming back to this one. */
void DesignEditor_GlideToPlace(DesignEditor *self)
{
    if (de_is_panel_place(self->key_place)) {
        Glider_TurnToSetB(&self->cursor_sprite);
    } else {
        Glider_TurnToSetA(&self->cursor_sprite);
    }
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_PLACE_AT_ONCE) != 0) {
        int x = DesignEditor_PlaceX(self);
        int y = DesignEditor_PlaceY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
        DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_PLACE_AT_ONCE);
    } else {
        int x = DesignEditor_PlaceX(self);
        int y = DesignEditor_PlaceY(self);
        Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
        self->return_sub_state = self->base.sub_state;
        MenuScene_SetSubState(de_scene(self), DESIGN_EDITOR_SUB_SPRITE_MOVE);
    }
}
CLEAN_AS(func_ov123_02299c04, DesignEditor_GlideToPlace)

/* func_ov123_02299ca0: the cursor sprite's press shown (the third of its set), sub state 0x0b. */
void DesignEditor_PressCursorSprite(DesignEditor *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(de_scene(self), DESIGN_EDITOR_SUB_PRESS_END);
}
CLEAN_AS(func_ov123_02299ca0, DesignEditor_PressCursorSprite)

/* func_ov123_02299cc0: a press at the key cursor starts (the second of the sprite's set), sub
 * state 0x0a. */
void DesignEditor_BeginPress(DesignEditor *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(de_scene(self), DESIGN_EDITOR_SUB_PRESS);
}
CLEAN_AS(func_ov123_02299cc0, DesignEditor_BeginPress)

/* func_ov123_02299ce0: the cursor sprite at rest (the first of its set), updated. */
void DesignEditor_ShowCursorIdle(DesignEditor *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    de_update_cursor_sprite(self);
}
CLEAN_AS(func_ov123_02299ce0, DesignEditor_ShowCursorIdle)

/* func_ov123_02299d00: the cursor sprite hidden (no animation), updated. */
void DesignEditor_HideCursor(DesignEditor *self)
{
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_NONE);
    de_update_cursor_sprite(self);
}
CLEAN_AS(func_ov123_02299d00, DesignEditor_HideCursor)

/* func_ov123_02299d24: the y of the key cursor's place. */
unsigned char DesignEditor_PlaceY(DesignEditor *self)
{
    return data_ov123_0229ca78[self->key_place];
}
CLEAN_AS(func_ov123_02299d24, DesignEditor_PlaceY)

/* func_ov123_02299d34: the x of the key cursor's place. */
unsigned char DesignEditor_PlaceX(DesignEditor *self)
{
    return data_ov123_0229ca54[self->key_place];
}
CLEAN_AS(func_ov123_02299d34, DesignEditor_PlaceX)

/* func_ov123_02299d44: the cursor sprite put at the key cursor's place at rest, in set B on the
 * panel's buttons and set A elsewhere. */
void DesignEditor_PlaceCursorSprite(DesignEditor *self)
{
    int x = DesignEditor_PlaceX(self);
    int y = DesignEditor_PlaceY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (de_is_panel_place(self->key_place)) {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_B);
    } else {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
    }
    DesignEditor_ShowCursorIdle(self);
}
CLEAN_AS(func_ov123_02299d44, DesignEditor_PlaceCursorSprite)

/* func_ov123_02299ea8: a dragged shape let go: drawn, ended, and back to the idle sub state. */
void DesignEditor_FinishShape(DesignEditor *self)
{
    DesignEditor_DrawShape(self);
    DesignEditor_EndShape(self);
    DesignEditor_EnterIdle(self);
}
CLEAN_AS(func_ov123_02299ea8, DesignEditor_FinishShape)

/* func_ov123_0229a340: the colour of the pixel under the canvas cursor taken. */
void DesignEditor_PickColour(DesignEditor *self)
{
    DesignEditor_SetColour(self, DesignEditor_PixelAt(self, self->cursor_px, self->cursor_py));
}
CLEAN_AS(func_ov123_0229a340, DesignEditor_PickColour)

/* func_ov123_0229a364: the dragged shape drawn in the colour, after a snapshot (sound 0x867):
 * a line from its start to the pen (pen 1), or the box between them's rectangle or ellipse;
 * nothing without a shape or with another tool. */
void DesignEditor_DrawShape(DesignEditor *self)
{
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_SHAPE) == 0) {
        return;
    }
    if (!de_is_shape_tool(self->tool)) {
        return;
    }
    DesignEditor_Snapshot(self);
    u8 pen_px = self->pen_px;
    u8 start_px = self->start_px;
    int left;
    int right;
    if (start_px >= pen_px) {
        left = pen_px;
        right = start_px;
    } else {
        right = pen_px;
        left = start_px;
    }
    u8 pen_py = self->pen_py;
    u8 start_py = self->start_py;
    int top;
    int bottom;
    if (start_py >= self->pen_py) {
        top = pen_py;
        bottom = start_py;
    } else {
        bottom = pen_py;
        top = start_py;
    }
    switch (self->tool) {
        case DESIGN_EDITOR_TOOL_LINE:
            DesignEditor_Line(self, start_px, start_py, pen_px, pen_py, self->colour, DESIGN_EDITOR_TOOL_PEN_1);
            break;
        case DESIGN_EDITOR_TOOL_RECTANGLE:
            DesignEditor_Rectangle(self, (u8) left, (u8) top, (unsigned int) right, (unsigned int) bottom, self->colour);
            break;
        case DESIGN_EDITOR_TOOL_ELLIPSE:
            DesignEditor_Ellipse(self, left, top, right, (u8) bottom, self->colour, 0);
            break;
    }
    DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_DIRTY);
    SoundSys_PlaySe(0x867);
}
CLEAN_AS(func_ov123_0229a364, DesignEditor_DrawShape)

/* func_ov123_0229a438: A on the canvas: the tool used at the canvas cursor. A shape starts
 * (sub state 6); else a snapshot and the tool, and a pen keeps drawing while A is held (sounds
 * 0x85f and 0x861, sub state 5). */
void DesignEditor_PressCanvasByKeys(DesignEditor *self)
{
    self->pen_px = self->cursor_px;
    self->pen_py = self->cursor_py;
    if (de_is_shape_tool(self->tool)) {
        DesignEditor_StartShape(self);
        MenuScene_SetSubState(de_scene(self), DESIGN_EDITOR_SUB_KEY_SHAPE);
        return;
    }
    DesignEditor_Snapshot(self);
    DesignEditor_UseTool(self, self->pen_px, self->pen_py);
    if (self->tool <= DESIGN_EDITOR_TOOL_PEN_3) {
        SoundSys_PlaySe(0x85f);
        SoundSys_PlaySe(0x861);
        MenuScene_SetSubState(de_scene(self), DESIGN_EDITOR_SUB_KEY_DRAW);
    }
    DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_DIRTY);
}
CLEAN_AS(func_ov123_0229a438, DesignEditor_PressCanvasByKeys)

/* func_ov123_0229a4bc: the pen down on the canvas: the tool used at its pixel. A shape starts;
 * else a snapshot and the tool, and a pen starts a stroke (sounds 0x85f and 0x861). Either way
 * drawing with the pen goes on (sub state 2). */
void DesignEditor_PressCanvasByTouch(DesignEditor *self)
{
    DesignEditor_PenToPixel(self);
    if (de_is_shape_tool(self->tool)) {
        DesignEditor_StartShape(self);
        DesignEditor_BeginPenDraw(self);
        return;
    }
    DesignEditor_Snapshot(self);
    DesignEditor_UseTool(self, self->pen_px, self->pen_py);
    if (self->tool <= DESIGN_EDITOR_TOOL_PEN_3) {
        SoundSys_PlaySe(0x85f);
        SoundSys_PlaySe(0x861);
        DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_STROKE);
    }
    DesignEditor_BeginPenDraw(self);
    DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_DIRTY);
}
CLEAN_AS(func_ov123_0229a4bc, DesignEditor_PressCanvasByTouch)

/* func_ov123_0229a538: the tool used at pixel (px, py) in the colour: a pen's dab, a stamp
 * (sound 0x867), or the fill, the pattern or the clear (sound 0x867 first). */
void DesignEditor_UseTool(DesignEditor *self, int px, int py)
{
    u8 tool = self->tool;
    if (tool <= DESIGN_EDITOR_TOOL_PEN_3) {
        DesignEditor_PaintBrush(self, (u8) px, (u8) py, self->colour, tool, 1);
    } else if (tool >= DESIGN_EDITOR_TOOL_STAMP_0 && tool <= DESIGN_EDITOR_TOOL_STAMP_1) {
        DesignEditor_Stamp(self, px, py, self->colour, tool - DESIGN_EDITOR_TOOL_STAMP_0);
        SoundSys_PlaySe(0x867);
    } else {
        if (tool >= DESIGN_EDITOR_TOOL_FILL && tool <= DESIGN_EDITOR_TOOL_CLEAR) {
            SoundSys_PlaySe(0x867);
        }
        switch (self->tool) {
            case DESIGN_EDITOR_TOOL_FILL:
                DesignEditor_Fill(self, (u8) px, (u8) py, self->colour);
                break;
            case DESIGN_EDITOR_TOOL_CLEAR:
                DesignEditor_Clear(self, self->colour);
                break;
            case DESIGN_EDITOR_TOOL_PATTERN:
                DesignEditor_PaintPattern(self, self->colour);
                break;
        }
    }
}
CLEAN_AS(func_ov123_0229a538, DesignEditor_UseTool)

/* func_ov123_0229ae24: the canvas pixel under the pen (two screen pixels further for pen 2),
 * held within the canvas. */
void DesignEditor_PenToPixel(DesignEditor *self)
{
    int x = data_021f6c58;
    int y = data_021f6c54 + 16;
    if (self->tool == DESIGN_EDITOR_TOOL_PEN_2) {
        x += 2;
        y += 2;
    }
    x -= 64;
    if (x < 0) {
        x = 0;
    } else if (x > 127) {
        x = 127;
    }
    y -= 24;
    if (y < 0) {
        y = 0;
    } else if (y > 127) {
        y = 127;
    }
    self->pen_px = (u8) (x >> 2);
    self->pen_py = (u8) (y >> 2);
}
CLEAN_AS(func_ov123_0229ae24, DesignEditor_PenToPixel)

/* func_ov123_0229ae74: a canvas pixel's y on the screen (for the sprites). */
int DesignEditor_ScreenY(DesignEditor *unused, int py)
{
    (void) unused;
    return py * 4 + 10;
}
CLEAN_AS(func_ov123_0229ae74, DesignEditor_ScreenY)

/* func_ov123_0229ae7c: a canvas pixel's x on the screen. */
int DesignEditor_ScreenX(DesignEditor *unused, int px)
{
    (void) unused;
    return px * 4 + 0x42;
}
CLEAN_AS(func_ov123_0229ae7c, DesignEditor_ScreenX)

/* The editor ends ("yes"): the design saved unless the quit was chosen (sound 0x27 and main's
 * byte 0xc4c 1; sound 0x28 and 0 when not saved). */
static void de_answer_yes(DesignEditor *self)
{
    DesignEditor_PressPanel(self, DESIGN_EDITOR_STATE_DONE, DESIGN_EDITOR_BUTTON_YES);
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_QUIT) != 0) {
        GroupParams_SetC4C(0);
        SoundSys_PlaySe(0x28);
        return;
    }
    switch (GroupParams_Mode()) {
        case 2:
            DesignEditor_SavePlayerDesign(self);
            break;
        case 3:
            DesignEditor_SaveTownDesign(self);
            break;
    }
    GroupParams_SetC4C(1);
    SoundSys_PlaySe(0x27);
}

/* func_ov123_0229ae84: the place in `command` pressed: the panel's save or quit button, a tool
 * chosen, the next palette (lit, sound 0x868), the undo (lit), a colour (sound 0x86a), layer 3
 * shown or hidden, the question's "yes" (de_answer_yes) or "no" (back to editing with the key
 * cursor on the button asked from). */
void DesignEditor_RunCommand(DesignEditor *self)
{
    u8 command = self->command;
    if (command == DESIGN_EDITOR_PLACE_SAVE) {
        DesignEditor_ChooseSave(self);
        return;
    }
    if (command == DESIGN_EDITOR_PLACE_QUIT) {
        DesignEditor_ChooseQuit(self);
        return;
    }
    if (command <= DESIGN_EDITOR_TOOL_CLEAR && command != DESIGN_EDITOR_TOOL_UNDO) {
        DesignEditor_SelectTool(self, command);
        return;
    }
    if (command == DESIGN_EDITOR_PLACE_PALETTE) {
        DesignEditor_LightPlace(self, command);
        DesignEditor_SetPalette(self, (u8) ((self->palette + 1) & 0xf));
        SoundSys_PlaySe(0x868);
        return;
    }
    if (command == DESIGN_EDITOR_TOOL_UNDO) {
        DesignEditor_LightPlace(self, command);
        DesignEditor_Undo(self);
        return;
    }
    if (command >= DESIGN_EDITOR_PLACE_COLOUR_1 && command <= DESIGN_EDITOR_PLACE_COLOUR_15) {
        DesignEditor_SetColour(self, (u8) (command - (DESIGN_EDITOR_PLACE_COLOUR_1 - 1)));
        SoundSys_PlaySe(0x86a);
        return;
    }
    if (command == DESIGN_EDITOR_PLACE_LAYER3) {
        DesignEditor_ToggleLayer3(self);
    }
    if (self->command == DESIGN_EDITOR_PLACE_DONE) {
        de_answer_yes(self);
        return;
    }
    if (self->command == DESIGN_EDITOR_PLACE_CHOICE) {
        DesignEditor_PressPanel(self, DESIGN_EDITOR_STATE_START_END_QUESTION, DESIGN_EDITOR_BUTTON_NO);
        if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_QUIT) != 0) {
            self->key_place = DESIGN_EDITOR_PLACE_QUIT;
            SoundSys_PlaySe(0x29);
        } else {
            self->key_place = DESIGN_EDITOR_PLACE_SAVE;
            SoundSys_PlaySe(0x2a);
        }
    }
}
CLEAN_AS(func_ov123_0229ae84, DesignEditor_RunCommand)

/* func_ov123_0229afa8: the place under the pen. */
int DesignEditor_PlaceUnderPen(DesignEditor *self)
{
    return DesignEditor_PlaceAt(self, data_021f6c58, data_021f6c54);
}
CLEAN_AS(func_ov123_0229afa8, DesignEditor_PlaceUnderPen)

/* func_ov123_0229afc0: the place at screen point (x, y) (DesignEditorPlace): the panel's save
 * and quit buttons, the layer 3 button, the canvas, the two columns of tools (six rows, the
 * second column from tool 6), the palette button, the row of colours (12 pixels each); else
 * none. */
int DesignEditor_PlaceAt(DesignEditor *self, int x, int y)
{
    if (ButtonPanel_HitTest(&self->panel, DESIGN_EDITOR_BUTTON_SAVE, x, y) != 0) {
        return DESIGN_EDITOR_PLACE_SAVE;
    }
    if (ButtonPanel_HitTest(&self->panel, DESIGN_EDITOR_BUTTON_QUIT, x, y) != 0) {
        return DESIGN_EDITOR_PLACE_QUIT;
    }
    if (x >= 8 && x <= 0x28 && y >= 0x18 && y <= 0x38) {
        return DESIGN_EDITOR_PLACE_LAYER3;
    }
    if (x >= 0x40 && x < 0xc0 && y >= 8 && y < 0x88) {
        return DESIGN_EDITOR_PLACE_CANVAS;
    }
    if (x >= 0xca && y >= 8) {
        if (x < 0xe1) {
            if (y < 0x50) {
                return y < 0x20 ? 0 : y < 0x38 ? 1 : 2;
            }
            if (y >= 0x58 && y < 0x88) {
                return y < 0x70 ? 3 : 4;
            }
            if (y >= 0x90 && y < 0xa8) {
                return 5;
            }
        } else if (x < 0xf9) {
            if (y < 0x50) {
                return y < 0x20 ? 6 : y < 0x38 ? 7 : 8;
            }
            if (y >= 0x58 && y < 0xa0) {
                return y < 0x70 ? 9 : y < 0x88 ? 10 : 11;
            }
        }
    }
    if (x >= 8 && x <= 0x28 && y >= 0x80 && y <= 0x94) {
        return DESIGN_EDITOR_PLACE_PALETTE;
    }
    if (x >= 8 && x < 0xbc && y >= 0x94 && y <= 0xa4) {
        return (u8) ((x - 8) / 12 + DESIGN_EDITOR_PLACE_COLOUR_1);
    }
    return DESIGN_EDITOR_NO_PLACE;
}
CLEAN_AS(func_ov123_0229afc0, DesignEditor_PlaceAt)

/* func_ov123_0229b56c: a panel button pressed: state `state` next, the button selected and its
 * press waited for (sub state 0x0c). */
void DesignEditor_PressPanel(DesignEditor *self, unsigned int state, unsigned int button)
{
    MenuScene_SetState(de_scene(self), (u8) state);
    ButtonPanel_Select(&self->panel, (int) button);
    MenuScene_SetSubState(de_scene(self), DESIGN_EDITOR_SUB_PANEL_PRESS);
}
CLEAN_AS(func_ov123_0229b56c, DesignEditor_PressPanel)

/* func_ov123_0229b598: the quit button (sound 0x2a): the quit chosen, the d-pad off the canvas,
 * and the question asked (state 6) once button 8's press is shown. */
void DesignEditor_ChooseQuit(DesignEditor *self)
{
    SoundSys_PlaySe(0x2a);
    DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_QUIT);
    if (self->key_mode == DESIGN_EDITOR_KEYS_CANVAS) {
        self->key_mode = DESIGN_EDITOR_KEYS_PLACES;
    }
    DesignEditor_PressPanel(self, DESIGN_EDITOR_STATE_START_QUESTION, DESIGN_EDITOR_BUTTON_QUIT);
}
CLEAN_AS(func_ov123_0229b598, DesignEditor_ChooseQuit)

/* func_ov123_0229b5cc: the save button (sound 0x29): the save chosen, as DesignEditor_ChooseQuit
 * with button 9. */
void DesignEditor_ChooseSave(DesignEditor *self)
{
    SoundSys_PlaySe(0x29);
    DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_QUIT);
    if (self->key_mode == DESIGN_EDITOR_KEYS_CANVAS) {
        self->key_mode = DESIGN_EDITOR_KEYS_PLACES;
    }
    DesignEditor_PressPanel(self, DESIGN_EDITOR_STATE_START_QUESTION, DESIGN_EDITOR_BUTTON_SAVE);
}
CLEAN_AS(func_ov123_0229b5cc, DesignEditor_ChooseSave)

/* func_ov123_0229b600: the question answered by touch (StateFlags_IsClear2) or by the keys. */
void DesignEditor_EnterPanel(DesignEditor *self)
{
    if (StateFlags_IsClear2() != 0) {
        DesignEditor_EnterPanelByTouch(self);
    } else {
        DesignEditor_EnterPanelByKeys(self);
    }
}
CLEAN_AS(func_ov123_0229b600, DesignEditor_EnterPanel)

/* func_ov123_0229b620: the question by the keys: the key cursor on "no" (sub state 8). */
void DesignEditor_EnterPanelByKeys(DesignEditor *self)
{
    MenuScene_ResetKeyRepeat(de_scene(self));
    self->key_place = DESIGN_EDITOR_PLACE_CHOICE;
    DesignEditor_PlaceCursorSprite(self);
    MenuScene_SetSubState(de_scene(self), DESIGN_EDITOR_SUB_PANEL);
}
CLEAN_AS(func_ov123_0229b620, DesignEditor_EnterPanelByKeys)

/* func_ov123_0229b644: the question by touch: the cursor sprite hidden (sub state 1). */
void DesignEditor_EnterPanelByTouch(DesignEditor *self)
{
    DesignEditor_HideCursor(self);
    MenuScene_SetSubState(de_scene(self), DESIGN_EDITOR_SUB_TOUCH_PANEL);
}
CLEAN_AS(func_ov123_0229b644, DesignEditor_EnterPanelByTouch)

/* func_ov123_0229b65c: editing by touch (StateFlags_IsClear2) or by the keys. */
void DesignEditor_EnterIdle(DesignEditor *self)
{
    if (StateFlags_IsClear2() != 0) {
        DesignEditor_EnterIdleByTouch(self);
    } else {
        DesignEditor_EnterIdleByKeys(self);
    }
}
CLEAN_AS(func_ov123_0229b65c, DesignEditor_EnterIdle)

/* func_ov123_0229b67c: editing by the keys: on the canvas the cursor sprite hidden, the key
 * repeat set (5, 0, 5), the sound player's byte at the cursor's x (sub state 4); else the
 * cursor sprite at the key cursor's place (sub state 3). */
void DesignEditor_EnterIdleByKeys(DesignEditor *self)
{
    if (self->key_mode == DESIGN_EDITOR_KEYS_CANVAS) {
        DesignEditor_HideCursor(self);
        MenuScene_SetKeyRepeat(de_scene(self), 5, 0, 5);
        MenuScene_SetSubState(de_scene(self), DESIGN_EDITOR_SUB_CANVAS);
        SoundSys_ChangePlayerByte((u8) DesignEditor_ScreenX(self, self->cursor_px));
    } else {
        DesignEditor_PlaceCursorSprite(self);
        MenuScene_ResetKeyRepeat(de_scene(self));
        MenuScene_SetSubState(de_scene(self), DESIGN_EDITOR_SUB_PLACES);
    }
}
CLEAN_AS(func_ov123_0229b67c, DesignEditor_EnterIdleByKeys)

/* func_ov123_0229b6d0: editing by touch (sub state 0), the cursor sprite hidden. */
void DesignEditor_EnterIdleByTouch(DesignEditor *self)
{
    MenuScene_SetSubState(de_scene(self), DESIGN_EDITOR_SUB_TOUCH);
    DesignEditor_HideCursor(self);
}
CLEAN_AS(func_ov123_0229b6d0, DesignEditor_EnterIdleByTouch)

/* func_ov123_0229b6e8 (sub state 0x0c): a panel button's press shown; the cursor sprite, when
 * it shows, follows the button as it is pressed. Once done, the cursor sprite hidden and the
 * states run (phase 1). */
void DesignEditor_WaitPanelPress(DesignEditor *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) != 0) {
        if (CellLayerSprite_AnimNumber((CellLayerSprite *) (void *) &self->cursor_sprite) != 0) {
            int frame = ButtonPanel_SelectedPressFrame(&self->panel);
            int x = ButtonPanel_ButtonX(&self->panel, -1);
            int y = ButtonPanel_ButtonY(&self->panel, -1);
            Glider_PlaceAt(&self->cursor_sprite, frame + x, frame + y);
        }
    } else {
        DesignEditor_HideCursor(self);
        MenuScene_SetPhase(de_scene(self), DESIGN_EDITOR_PHASE_STATES);
    }
}
CLEAN_AS(func_ov123_0229b6e8, DesignEditor_WaitPanelPress)

/* func_ov123_0229b754 (sub state 0x0b): once the press's animation ends, the cursor sprite at
 * rest and the places again (sub state 3). */
void DesignEditor_FinishPress(DesignEditor *self)
{
    if (CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->cursor_sprite) != 0) {
        DesignEditor_ShowCursorIdle(self);
        MenuScene_SetSubState(de_scene(self), DESIGN_EDITOR_SUB_PLACES);
    }
}
CLEAN_AS(func_ov123_0229b754, DesignEditor_FinishPress)

/* func_ov123_0229b77c (sub state 0x0a): once the press's first animation ends, the key cursor's
 * place pressed, and the press shown when the command left the sub state as it was. */
void DesignEditor_PressAtCursor(DesignEditor *self)
{
    if (CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->cursor_sprite) != 0) {
        self->command = self->key_place;
        DesignEditor_RunCommand(self);
        if (self->base.sub_state == DESIGN_EDITOR_SUB_PRESS) {
            DesignEditor_PressCursorSprite(self);
        }
    }
}
CLEAN_AS(func_ov123_0229b77c, DesignEditor_PressAtCursor)

/* Obj_ov123_0229d024::func_ov123_0229b7b8 (sub state 9): once the cursor sprite stops, back to
 * the sub state it was sent from, run at once. */
void DesignEditor_WaitCursorSprite(DesignEditor *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) != 0) {
        return;
    }
    MenuScene_SetSubState(de_scene(self), self->return_sub_state);
    DesignEditor_RunSubState(self);
}
CLEAN_AS(_ZN18Obj_ov123_0229d02419func_ov123_0229b7b8Ev, DesignEditor_WaitCursorSprite)

/* func_ov123_0229b7e4 (sub state 8): the question by the keys: a touch turns to touch; left
 * puts the key cursor on "yes" and right on "no" (the sprite glides there); else A presses at
 * the cursor, B answers "no" and START "yes". The repeated keys are taken but only the
 * repeats' tests read. */
void DesignEditor_PanelByKeys(DesignEditor *self)
{
    if (MenuScene_TakeTouch(de_scene(self)) != 0) {
        DesignEditor_EnterPanelByTouch(self);
        return;
    }
    u8 from = self->key_place;
    MenuScene_LatchRepeatedKeys(de_scene(self));
    if (MenuScene_RepeatedLeft(de_scene(self)) != 0) {
        self->key_place = DESIGN_EDITOR_PLACE_DONE;
    } else if (MenuScene_RepeatedRight(de_scene(self)) != 0) {
        self->key_place = DESIGN_EDITOR_PLACE_CHOICE;
    }
    if (from != self->key_place) {
        DesignEditor_GlideToPlace(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & DESIGN_EDITOR_PAD_A) {
        DesignEditor_BeginPress(self);
    } else if (pressed & DESIGN_EDITOR_PAD_B) {
        DesignEditor_HideCursor(self);
        self->command = DESIGN_EDITOR_PLACE_CHOICE;
        DesignEditor_RunCommand(self);
    } else if (pressed & DESIGN_EDITOR_PAD_START) {
        DesignEditor_HideCursor(self);
        self->command = DESIGN_EDITOR_PLACE_DONE;
        DesignEditor_RunCommand(self);
    }
}
CLEAN_AS(func_ov123_0229b7e4, DesignEditor_PanelByKeys)

/* func_ov123_0229b89c (sub state 7): a colour picked under the canvas cursor while B is held;
 * let go, picking ends (sound 0x86d). */
void DesignEditor_PickByKeys(DesignEditor *self)
{
    if ((data_021fbe40.held & DESIGN_EDITOR_PAD_B) == 0) {
        DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_PICKING);
        DesignEditor_EnterIdle(self);
        SoundSys_PlaySe(0x86d);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(de_scene(self));
    if (DesignEditor_MoveCanvasCursor(self, keys, 0) != 0) {
        DesignEditor_PickColour(self);
    }
}
CLEAN_AS(func_ov123_0229b89c, DesignEditor_PickByKeys)

/* func_ov123_0229b8ec (sub state 6): a shape dragged out by the keys: a touch drops it (sound
 * 0x86e); the cursor moves its far end; A draws it; B drops it (sound 0x86e); Y drops it and
 * leaves the canvas (sound 0x864); X shows or hides layer 3. */
void DesignEditor_ShapeByKeys(DesignEditor *self)
{
    if (MenuScene_TakeTouch(de_scene(self)) != 0) {
        SoundSys_PlaySe(0x86e);
        DesignEditor_EndShape(self);
        DesignEditor_EnterIdleByTouch(self);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(de_scene(self));
    if (DesignEditor_MoveCanvasCursor(self, keys, 0) != 0) {
        self->pen_px = self->cursor_px;
        self->pen_py = self->cursor_py;
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & DESIGN_EDITOR_PAD_A) {
        DesignEditor_FinishShape(self);
        return;
    }
    if (pressed & DESIGN_EDITOR_PAD_B) {
        SoundSys_PlaySe(0x86e);
        DesignEditor_EndShape(self);
        DesignEditor_EnterIdle(self);
        return;
    }
    if (pressed & DESIGN_EDITOR_PAD_Y) {
        SoundSys_PlaySe(0x864);
        DesignEditor_EndShape(self);
        self->key_mode = DESIGN_EDITOR_KEYS_PLACES;
        DesignEditor_EnterIdle(self);
        return;
    }
    if (pressed & DESIGN_EDITOR_PAD_X) {
        DesignEditor_ToggleLayer3(self);
    }
}
CLEAN_AS(func_ov123_0229b8ec, DesignEditor_ShapeByKeys)

/* func_ov123_0229b9bc (sub state 5): a pen drawing while A is held: each move of the canvas
 * cursor dabs the pen there (sound 0x861; 0x860 too when held, not pressed). Sound 0x863 runs
 * while the cursor moves without waiting, and stops (in a frame) otherwise or when A is let
 * go. */
void DesignEditor_DrawByKeys(DesignEditor *self)
{
    if ((data_021fbe40.held & DESIGN_EDITOR_PAD_A) == 0) {
        DesignEditor_EnterIdle(self);
        if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_KEY_SOUND) != 0) {
            DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_KEY_SOUND);
            SoundSys_StopSound(0x863, 1);
        }
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(de_scene(self));
    int running = 0;
    if (DesignEditor_MoveCanvasCursor(self, keys, 1) != 0) {
        DesignEditor_PaintBrush(self, self->cursor_px, self->cursor_py, self->colour, self->tool, 1);
        DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_DIRTY);
        SoundSys_PlaySe(0x861);
        if (self->key_delay == 0) {
            running = 1;
        } else {
            SoundSys_PlaySe(0x860);
        }
    }
    if (running) {
        if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_KEY_SOUND) == 0) {
            DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_KEY_SOUND);
            SoundSys_StartOnHandle38(0x863);
        }
    } else if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_KEY_SOUND) != 0) {
        DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_KEY_SOUND);
        SoundSys_StopSound(0x863, 1);
    }
}
CLEAN_AS(func_ov123_0229b9bc, DesignEditor_DrawByKeys)

/* func_ov123_0229baa4 (sub state 4): the canvas by the keys: a touch turns to touch; the cursor
 * moves; A uses the tool; B picks colours while held (sub state 7); Y leaves the canvas for the
 * place it came from (sound 0x864); L and R change the colour; X shows or hides layer 3; START
 * asks to save. */
void DesignEditor_CanvasByKeys(DesignEditor *self)
{
    if (MenuScene_TakeTouch(de_scene(self)) != 0) {
        DesignEditor_EnterIdleByTouch(self);
        return;
    }
    DesignEditor_MoveCanvasCursor(self, (int) MenuScene_LatchRepeatedKeys(de_scene(self)), 0);
    u16 pressed = data_021fbe40.pressed;
    if (pressed & DESIGN_EDITOR_PAD_A) {
        DesignEditor_PressCanvasByKeys(self);
        return;
    }
    if (pressed & DESIGN_EDITOR_PAD_B) {
        DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_PICKING);
        DesignEditor_PickColour(self);
        MenuScene_SetSubState(de_scene(self), DESIGN_EDITOR_SUB_PICK);
        return;
    }
    if (pressed & DESIGN_EDITOR_PAD_Y) {
        SoundSys_PlaySe(0x864);
        self->key_mode = DESIGN_EDITOR_KEYS_PLACES;
        self->key_place = self->saved_place;
        DesignEditor_EnterIdle(self);
        return;
    }
    if (DesignEditor_ColourByShoulders(self) != 0) {
        return;
    }
    pressed = data_021fbe40.pressed;
    if (pressed & DESIGN_EDITOR_PAD_X) {
        DesignEditor_ToggleLayer3(self);
        return;
    }
    if (pressed & DESIGN_EDITOR_PAD_START) {
        DesignEditor_HideCursor(self);
        DesignEditor_ChooseSave(self);
    }
}
CLEAN_AS(func_ov123_0229baa4, DesignEditor_CanvasByKeys)

/* func_ov123_0229bb74 (sub state 3): the places by the keys: a touch turns to touch; the key
 * cursor moves (remembered while on the places); A presses at it; Y goes from the places to the
 * colours (on the colour drawn) and from the colours to the canvas (sound 0x864); L and R change
 * the colour; X shows or hides layer 3; B asks to quit and START to save. */
void DesignEditor_PlacesByKeys(DesignEditor *self)
{
    if (MenuScene_TakeTouch(de_scene(self)) != 0) {
        DesignEditor_EnterIdleByTouch(self);
        return;
    }
    if (DesignEditor_MovePlaceCursor(self, (int) MenuScene_LatchRepeatedKeys(de_scene(self))) != 0) {
        if (self->key_mode == DESIGN_EDITOR_KEYS_PLACES) {
            self->saved_place = self->key_place;
        }
        DesignEditor_GlideToPlace(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & DESIGN_EDITOR_PAD_A) {
        DesignEditor_BeginPress(self);
        return;
    }
    if (pressed & DESIGN_EDITOR_PAD_Y) {
        SoundSys_PlaySe(0x864);
        if (self->key_mode == DESIGN_EDITOR_KEYS_PLACES) {
            self->key_mode = DESIGN_EDITOR_KEYS_COLOURS;
            self->key_place = (u8) (self->colour + (DESIGN_EDITOR_PLACE_COLOUR_1 - 1));
        } else {
            self->key_mode = DESIGN_EDITOR_KEYS_CANVAS;
        }
        DesignEditor_EnterIdle(self);
        return;
    }
    if (DesignEditor_ColourByShoulders(self) != 0) {
        return;
    }
    pressed = data_021fbe40.pressed;
    if (pressed & DESIGN_EDITOR_PAD_X) {
        DesignEditor_ToggleLayer3(self);
        return;
    }
    if (pressed & DESIGN_EDITOR_PAD_B) {
        DesignEditor_HideCursor(self);
        DesignEditor_ChooseQuit(self);
        return;
    }
    if (pressed & DESIGN_EDITOR_PAD_START) {
        DesignEditor_HideCursor(self);
        DesignEditor_ChooseSave(self);
    }
}
CLEAN_AS(func_ov123_0229bb74, DesignEditor_PlacesByKeys)

/* func_ov123_0229bc70 (sub state 2): drawing with the pen. Lifted, the pen sound stops and a
 * dragged shape is drawn (back to idle). Else a frame of the pen (DesignEditor_FollowPen), its
 * point kept, and the pen sound (0x862) running while it moves, stopped when it rests. */
void DesignEditor_DrawByTouch(DesignEditor *self)
{
    if (data_021fbdd8 == 0) {
        if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_PEN_SOUND)) {
            DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_PEN_SOUND);
            SoundSys_StopSound(0x862, 1);
        }
        DesignEditor_FinishShape(self);
        return;
    }
    DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_PEN_MOVED);
    DesignEditor_FollowPen(self);
    self->pen_x = data_021f6c58;
    self->pen_y = data_021f6c54;
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_PEN_MOVED)) {
        if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_PEN_SOUND) == 0) {
            DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_PEN_SOUND);
            SoundSys_StartOnHandle38(0x862);
        }
    } else if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_PEN_SOUND)) {
        DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_PEN_SOUND);
        SoundSys_StopSound(0x862, 1);
    }
}
CLEAN_AS(func_ov123_0229bc70, DesignEditor_DrawByTouch)

/* func_ov123_0229bd20 (sub state 1): the question by touch: a button turns to the keys; the pen
 * put down on "yes" or "no" answers it. */
void DesignEditor_PanelByTouch(DesignEditor *self)
{
    if (MenuScene_TakeButtons(de_scene(self), 1) != 0) {
        DesignEditor_EnterPanelByKeys(self);
        return;
    }
    if (de_pen_pressed()) {
        if (ButtonPanel_IsTouched(&self->panel, DESIGN_EDITOR_BUTTON_YES) != 0) {
            self->command = DESIGN_EDITOR_PLACE_DONE;
            DesignEditor_RunCommand(self);
        } else if (ButtonPanel_IsTouched(&self->panel, DESIGN_EDITOR_BUTTON_NO) != 0) {
            self->command = DESIGN_EDITOR_PLACE_CHOICE;
            DesignEditor_RunCommand(self);
        }
    }
}
CLEAN_AS(func_ov123_0229bd20, DesignEditor_PanelByTouch)

/* func_ov123_0229bd9c (sub state 0): editing by touch: a button turns to the keys; the pen put
 * down on the canvas uses the tool, on a place presses it. */
void DesignEditor_IdleByTouch(DesignEditor *self)
{
    if (MenuScene_TakeButtons(de_scene(self), 1) != 0) {
        DesignEditor_EnterIdleByKeys(self);
        return;
    }
    if (de_pen_pressed()) {
        int place = DesignEditor_PlaceUnderPen(self);
        if (place == DESIGN_EDITOR_PLACE_CANVAS) {
            DesignEditor_PressCanvasByTouch(self);
        } else if (place != DESIGN_EDITOR_NO_PLACE) {
            self->command = (u8) place;
            DesignEditor_RunCommand(self);
        }
    }
}
CLEAN_AS(func_ov123_0229bd9c, DesignEditor_IdleByTouch)
