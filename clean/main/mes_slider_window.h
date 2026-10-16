/* The message window of the talk's slider window (talk_windows.h): the class of vtable
 * 0x020e3fe4 (0x148 bytes) that derives from the message background (mes_bg.h) and holds the
 * marker (a cell layer sprite, cell_layer_sprite.h) at 0x20, main's button sprite at 0x6c and
 * the slider (MesBgSlider) at 0xe4.
 *
 * Its frame (func_020abe7c) first acts on the requests the talk's window set, then runs the
 * step of the state it is in through a table, places the marker by the slider (states 1 to 5)
 * or by the button (states 6 to 11), and updates the three sprites. The states:
 *   0  hidden (nothing shown)
 *   1  the slider is focused, the marker beside it
 *   2  the slider is grabbed: the marker's grab animation plays
 *   3  the slider is held: its indicator plays
 *   4  the slider is let go: its indicator plays back
 *   5  the marker's release animation plays, then back to 1
 *   6  the button is focused
 *   7  a choice was taken: the marker's press animation plays
 *   8  the button's press animation plays
 *   9  the button's animation ends, then the marker plays animation 9
 *   10 the marker's animation 9 plays
 *   11 done: the window can close
 * The marker's animations are the cell layer sprite's numbers 0 (hidden), 1, 2, 3, 7, 8, 9;
 * the button's 0 (hidden), 1 (shown), 2 (pressed). */
#ifndef CLEAN_MAIN_MES_SLIDER_WINDOW_H
#define CLEAN_MAIN_MES_SLIDER_WINDOW_H

#include "mes_bg.h"
#include "types.h"

#define MES_SLIDER_WINDOW_HIDDEN 0
#define MES_SLIDER_WINDOW_SLIDER 1
#define MES_SLIDER_WINDOW_GRABBING 2
#define MES_SLIDER_WINDOW_HELD 3
#define MES_SLIDER_WINDOW_LETTING_GO 4
#define MES_SLIDER_WINDOW_RELEASING 5
#define MES_SLIDER_WINDOW_BUTTON 6
#define MES_SLIDER_WINDOW_CHOSEN 7
#define MES_SLIDER_WINDOW_PRESSING 8
#define MES_SLIDER_WINDOW_STATE_9 9
#define MES_SLIDER_WINDOW_STATE_10 10
#define MES_SLIDER_WINDOW_DONE 11

typedef struct MesSliderWindow {
    MesBg bg;           /* 0x000: vtable 0x020e3fe4 */
    MesBgMarker marker; /* 0x020 */
    u8 button[0x78];    /* 0x06c: main's button sprite (func_0208f0c4, func_0208f098) */
    MesBgSlider slider; /* 0x0e4 */
    s32 state;          /* 0x13c: MES_SLIDER_WINDOW_* */
    u8 focus_slider;    /* 0x140: request: to state 1 on the next frame */
    u8 grabbed;         /* 0x141: the slider is held */
    u8 focus_button;    /* 0x142: request: to state 6 on the next frame */
    u8 chosen;          /* 0x143: a choice was taken (states 1 and 6 go on to 7) */
    u8 hide;            /* 0x144: request: to state 0 on the next frame */
    u8 buttons;         /* 0x145: the input shown is the buttons (grabbing plays a sound) */
    u8 pad_146[2];
} MesSliderWindow;

void MesSliderWindow_StepDone(MesSliderWindow *self);
void MesSliderWindow_EnterDone(MesSliderWindow *self);
void MesSliderWindow_Step10(MesSliderWindow *self);
void MesSliderWindow_Enter10(MesSliderWindow *self);
void MesSliderWindow_Step9(MesSliderWindow *self);
void MesSliderWindow_StepPressing(MesSliderWindow *self);
void MesSliderWindow_EnterPressing(MesSliderWindow *self);
void MesSliderWindow_StepChosen(MesSliderWindow *self);
void MesSliderWindow_EnterChosen(MesSliderWindow *self);
void MesSliderWindow_StepButton(MesSliderWindow *self);
void MesSliderWindow_EnterButton(MesSliderWindow *self);
void MesSliderWindow_StepReleasing(MesSliderWindow *self);
void MesSliderWindow_EnterReleasing(MesSliderWindow *self);
void MesSliderWindow_StepLettingGo(MesSliderWindow *self);
void MesSliderWindow_EnterLettingGo(MesSliderWindow *self);
void MesSliderWindow_StepHeld(MesSliderWindow *self);
void MesSliderWindow_EnterHeld(MesSliderWindow *self);
void MesSliderWindow_StepGrabbing(MesSliderWindow *self);
void MesSliderWindow_EnterGrabbing(MesSliderWindow *self);
void MesSliderWindow_StepSlider(MesSliderWindow *self);
void MesSliderWindow_EnterSlider(MesSliderWindow *self);
void MesSliderWindow_StepHidden(void);

#endif
