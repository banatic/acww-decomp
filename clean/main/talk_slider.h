/* The slider of a talk's slider window (talk_windows.h; 0x38 bytes at 0x154 of it, constructor
 * func_020aaeb4, frame func_020aad9c): a knob on a vertical track whose level runs from 0 to
 * 0x1000, and an OK button. The level is handed to the talk's choices (func_020ab3a8) when
 * the OK button is pressed.
 *
 * Its focus is the knob (0) or the OK button (1); each frame runs the focus's step through a
 * table (TalkSlider_MoveKnob, TalkSlider_PressOk). The knob is moved while it is held: with
 * the touch screen by dragging it, with the buttons by holding A and pressing up or down, which
 * speeds up the longer it is held. A sound plays when the knob passes one of the track's ten
 * notches or reaches the top. */
#ifndef CLEAN_MAIN_TALK_SLIDER_H
#define CLEAN_MAIN_TALK_SLIDER_H

#include "types.h"

#define TALK_SLIDER_LEVEL_MAX 0x1000

/* TalkSlider.focus */
#define TALK_SLIDER_FOCUS_KNOB 0
#define TALK_SLIDER_FOCUS_OK 1

typedef struct TalkSlider {
    void *window;    /* 0x00: the slider window's message window (its knob and track) */
    s32 speed;       /* 0x04: how far the buttons move the knob each frame */
    s32 level;       /* 0x08: 0 to TALK_SLIDER_LEVEL_MAX */
    s32 last_level;  /* 0x0c: the level of the last frame, for the notches' sound */
    s32 grab_offset; /* 0x10: where the knob was touched, from its top */
    u8 unk_14[0x2c - 0x14];
    s32 focus;             /* 0x2c: TALK_SLIDER_FOCUS_* */
    u8 held;               /* 0x30: the knob is held (dragged, or A held) */
    u8 confirmed_by_start; /* 0x31: the OK button was pressed with START */
    u8 pad_32[2];
    void *choices; /* 0x34: the talk's choices the level is handed to */
} TalkSlider;

void TalkSlider_PressOk(TalkSlider *slider);
void TalkSlider_FocusOk(TalkSlider *slider);
void TalkSlider_MoveKnob(TalkSlider *slider);
void TalkSlider_FocusKnob(TalkSlider *slider);
int TalkSlider_OkPressedWithButtons(TalkSlider *slider);
int TalkSlider_OkTouched(TalkSlider *slider);
int TalkSlider_ReleasedByButtons(TalkSlider *slider);
int TalkSlider_ReleasedByTouch(TalkSlider *slider);
int TalkSlider_GrabbedByButtons(TalkSlider *slider);
int TalkSlider_GrabbedByTouch(TalkSlider *slider);

#endif
