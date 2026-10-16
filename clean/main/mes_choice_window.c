/* The message window of the talk's choice window (mes_choice_window.h). */
#include "mes_choice_window.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "cell_layer_sprite.h"
#include "clean.h"
#include "sound.h" /* SoundSys_PlaySe */

static_assert(offsetof(MesChoiceWindow, marker) == 0x20, "mes choice window");
static_assert(offsetof(MesChoiceWindow, cursor) == 0x6c, "mes choice window");
static_assert(offsetof(MesChoiceWindow, flash_frame) == 0x70, "mes choice window");
static_assert(offsetof(MesChoiceWindow, buttons) == 0x74, "mes choice window");
static_assert(sizeof(MesChoiceWindow) == 0x78, "mes choice window");

/* The class's vtable. */
extern const u8 data_020e3ffc[];

/* The colours of the chosen line, frame by frame, and how many frames it flashes. */
extern const u16 data_020d1de8[];
#define MES_CHOICE_WINDOW_FLASH_FRAMES 5

/* The marker's animations (cell layer sprite numbers). */
#define MES_CHOICE_WINDOW_MARKER_BESIDE 7
#define MES_CHOICE_WINDOW_MARKER_PRESS 8

/* The marker's place beside the cursor's line: 5 pixels right of the window's left, 4 above the
 * line's top. */
#define MES_CHOICE_WINDOW_MARKER_X 5
#define MES_CHOICE_WINDOW_MARKER_Y (-4)
#define MES_CHOICE_WINDOW_LINE_HEIGHT 16

/* The sound of the input shown turning to the buttons. */
#define MES_CHOICE_WINDOW_SE_BUTTONS 0x3b

static CellLayerSprite *mes_choice_window_marker(MesChoiceWindow *self)
{
    return (CellLayerSprite *) &self->marker;
}

/* func_020ac11c: whether the input shown is the buttons (else the touch screen); with `sound`,
 * a sound when it turns to the buttons. */
void MesChoiceWindow_SetButtons(MesChoiceWindow *self, u8 buttons, int sound)
{
    if (sound != 0 && self->buttons == 0 && buttons != 0) {
        SoundSys_PlaySe(MES_CHOICE_WINDOW_SE_BUTTONS);
    }
    self->buttons = buttons;
}
CLEAN_AS(func_020ac11c, MesChoiceWindow_SetButtons)

/* func_020ac198: one frame of the chosen line's flash: the line in this frame's colour and the
 * others' colours 0. Returns whether the flash has had all its frames.
 * REQUIRES: the flash restarted (MesChoiceWindow_ResetFlash) before it, as the game does: the
 * table is read at the frame count as it is. */
int MesChoiceWindow_FlashChoice(MesChoiceWindow *self, int line)
{
    u16 colour = data_020d1de8[self->flash_frame];
    self->flash_frame++;
    int done = self->flash_frame >= MES_CHOICE_WINDOW_FLASH_FRAMES;
    MesBg_HighlightLine(&self->bg, line, colour);
    return done;
}
CLEAN_AS(func_020ac198, MesChoiceWindow_FlashChoice)

/* func_020ac1c4 */
void MesChoiceWindow_ResetFlash(MesChoiceWindow *self)
{
    self->flash_frame = 0;
}
CLEAN_AS(func_020ac1c4, MesChoiceWindow_ResetFlash)

/* func_020ac1cc */
void MesChoiceWindow_SetCursor(MesChoiceWindow *self, int line)
{
    self->cursor = line;
}
CLEAN_AS(func_020ac1cc, MesChoiceWindow_SetCursor)

/* func_020ac1d0: the marker's press animation. */
void MesChoiceWindow_PressMarker(MesChoiceWindow *self)
{
    CellLayerSprite_SetAnim(mes_choice_window_marker(self), MES_CHOICE_WINDOW_MARKER_PRESS);
}
CLEAN_AS(func_020ac1d0, MesChoiceWindow_PressMarker)

/* func_020ac1dc */
void MesChoiceWindow_HideMarker(MesChoiceWindow *self)
{
    CellLayerSprite_SetAnim(mes_choice_window_marker(self), CELL_LAYER_SPRITE_NONE);
}
CLEAN_AS(func_020ac1dc, MesChoiceWindow_HideMarker)

/* func_020ac1e8: the window opened: the cursor on the first line, the marker placed at the
 * window's scroll and shown beside the line. */
void MesChoiceWindow_Open(MesChoiceWindow *self)
{
    self->cursor = 0;
    self->marker.vtable->set_place(&self->marker, -self->bg.scroll_x, -self->bg.scroll_y);
    CellLayerSprite_SetAnim(mes_choice_window_marker(self), MES_CHOICE_WINDOW_MARKER_BESIDE);
}
CLEAN_AS(func_020ac1e8, MesChoiceWindow_Open)

/* func_020ac218: whether the marker's press animation has ended. */
int MesChoiceWindow_PressDone(MesChoiceWindow *self)
{
    return CellLayerSprite_AnimNumber(mes_choice_window_marker(self)) == MES_CHOICE_WINDOW_MARKER_PRESS &&
           CellLayerSprite_IsDone(mes_choice_window_marker(self)) != 0;
}
CLEAN_AS(func_020ac218, MesChoiceWindow_PressDone)

/* func_020ac240: whether the marker is beside the line (no choice pressed yet). */
int MesChoiceWindow_MarkerBeside(MesChoiceWindow *self)
{
    return CellLayerSprite_AnimNumber(mes_choice_window_marker(self)) == MES_CHOICE_WINDOW_MARKER_BESIDE;
}
CLEAN_AS(func_020ac240, MesChoiceWindow_MarkerBeside)

/* func_020ac25c (vtable slot 3): the marker drawn, only while the input shown is the buttons. */
void MesChoiceWindow_Draw(MesChoiceWindow *self)
{
    if (self->buttons != 0) {
        self->marker.vtable->draw(&self->marker);
    }
}
CLEAN_AS(func_020ac25c, MesChoiceWindow_Draw)

/* func_020ac278 (vtable slot 2): the frame: the marker beside the cursor's line, and updated. */
void MesChoiceWindow_Update(MesChoiceWindow *self)
{
    int y = (int) ((u32) self->bg.lines_top + (u32) self->cursor * MES_CHOICE_WINDOW_LINE_HEIGHT +
                   (u32) MES_CHOICE_WINDOW_MARKER_Y);
    CellLayerSprite_SetOffset(mes_choice_window_marker(self), MES_CHOICE_WINDOW_MARKER_X, y);
    self->marker.vtable->update(&self->marker);
}
CLEAN_AS(func_020ac278, MesChoiceWindow_Update)

/* func_020ac2a0 (vtable slot 1): destroyed (as MesChoiceWindow_Destruct) and freed. */
MesChoiceWindow *MesChoiceWindow_DestructDelete(MesChoiceWindow *self)
{
    self->bg.vtable = data_020e3ffc;
    MesBgMarker_Destruct(&self->marker);
    MesBg_DestructBase(&self->bg);
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_020ac2a0, MesChoiceWindow_DestructDelete)

/* func_020ac2c8 (vtable slot 0): the destructor: the marker, then the base. */
MesChoiceWindow *MesChoiceWindow_Destruct(MesChoiceWindow *self)
{
    self->bg.vtable = data_020e3ffc;
    MesBgMarker_Destruct(&self->marker);
    MesBg_DestructBase(&self->bg);
    return self;
}
CLEAN_AS(func_020ac2c8, MesChoiceWindow_Destruct)

/* func_020ac2ec: the constructor: the cursor on the first line, the input shown the touch
 * screen. */
MesChoiceWindow *MesChoiceWindow_Construct(MesChoiceWindow *self)
{
    MesBg_Construct(&self->bg);
    self->bg.vtable = data_020e3ffc;
    MesBgMarker_Construct(&self->marker);
    self->cursor = 0;
    self->flash_frame = 0;
    self->buttons = 0;
    return self;
}
CLEAN_AS(func_020ac2ec, MesChoiceWindow_Construct)
