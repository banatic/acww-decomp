/* The windows a talk opens for its choices (TalkWindows, at 0xb4 of a talk): a window that
 * lists the choices and a window with a slider (talk_slider.h), of which one at a time is
 * shown. The talk hands one its choices (the part at 0x31c of the talk), asks for it to open,
 * then runs and draws it each frame until it has closed.
 *
 * Both derive from a base class (vtable data_020e408c, 8 bytes: its vtable and the request to
 * open) whose vtable is: the destructor, the deleting destructor, then slots 2 (the frame),
 * 3 (drawing), 4 (whether the window is closed) and 5 (whether a choice was just made), which
 * the base leaves empty.
 *
 * Each window goes through four states, the frame running the state's step through a table:
 * closed until asked to open; opening, its message window sliding in for a few frames; open,
 * until a choice is taken; closing, the message window sliding out. Its message window is one
 * of the two classes that derive from the message background (mes_bg.h): with the slider at
 * 0xe4 for the slider window, without it for the list. */
#ifndef CLEAN_MAIN_TALK_WINDOWS_H
#define CLEAN_MAIN_TALK_WINDOWS_H

#include "talk_slider.h"
#include "types.h"

/* TalkSliderWindow.state and TalkChoiceWindow.state */
#define TALK_WINDOW_CLOSED 0
#define TALK_WINDOW_OPENING 1
#define TALK_WINDOW_OPEN 2
#define TALK_WINDOW_CLOSING 3

/* The base class (vtable data_020e408c). */
typedef struct TalkWindow {
    const u32 *vtable;
    u8 open_requested; /* 0x04: the window opens on its next frame */
    u8 pad_05[3];
} TalkWindow;

/* The window with a slider (vtable data_020e404c). */
typedef struct TalkSliderWindow {
    TalkWindow base;
    s32 state;         /* 0x008: TALK_WINDOW_* */
    u8 window[0x148];  /* 0x00c: its message window (with the slider's knob at 0xe4) */
    TalkSlider slider; /* 0x154 */
    s32 offset_x;      /* 0x18c: the message window's place while it slides */
    s32 offset_y;      /* 0x190 */
    s32 frames_left;   /* 0x194: of the slide */
    u8 decided;        /* 0x198: a choice was taken; until the first frame of the closing */
    u8 pad_199[3];
} TalkSliderWindow;

/* The window that lists the choices (vtable data_020e406c). */
typedef struct TalkChoiceWindow {
    TalkWindow base;
    s32 state;       /* 0x08: TALK_WINDOW_* */
    u8 window[0x78]; /* 0x0c: its message window */
    u8 list[0x30];   /* 0x84: the choices' cursor (constructor func_020ab37c) */
    s32 offset_x;    /* 0xb4: the message window's place while it slides */
    s32 offset_y;    /* 0xb8 */
    s32 frames_left; /* 0xbc: of the slide */
    u8 decided;      /* 0xc0: a choice was taken; until the first frame of the closing */
    u8 pad_c1[3];
} TalkChoiceWindow;

/* The pair, at 0xb4 of a talk. */
typedef struct TalkWindows {
    TalkWindow *current;     /* 0x000: the window shown, or NULL */
    TalkChoiceWindow choice; /* 0x004 */
    TalkSliderWindow slider; /* 0x0c8 */
    u8 closed_now;           /* 0x264: the window shown closed on this frame */
    u8 pad_265[3];
} TalkWindows;

void TalkWindows_Draw(TalkWindows *windows);
int TalkWindows_Decided(TalkWindows *windows);
int TalkWindows_NoneShown(TalkWindows *windows);
void TalkWindows_Open(TalkWindows *windows);
void TalkWindows_Update(TalkWindows *windows);
TalkWindows *TalkWindows_Destruct(TalkWindows *windows);
TalkWindows *TalkWindows_Construct(TalkWindows *windows);
void TalkWindows_ShowSlider(TalkWindows *windows, void *choices);
void TalkWindows_ShowChoices(TalkWindows *windows, void *choices);

void TalkSliderWindow_LayOut(TalkSliderWindow *self);
void TalkSliderWindow_StepClosing(TalkSliderWindow *self);
void TalkSliderWindow_StartClosing(TalkSliderWindow *self);
void TalkSliderWindow_StepOpen(TalkSliderWindow *self);
void TalkSliderWindow_EnterOpen(TalkSliderWindow *self);
void TalkSliderWindow_StepOpening(TalkSliderWindow *self);
void TalkSliderWindow_StartOpening(TalkSliderWindow *self);
void TalkSliderWindow_StepClosed(TalkSliderWindow *self);
void TalkSliderWindow_EnterClosed(TalkSliderWindow *self);
u8 TalkSliderWindow_Decided(TalkSliderWindow *self);
int TalkSliderWindow_IsClosed(TalkSliderWindow *self);
void TalkSliderWindow_Draw(TalkSliderWindow *self);
void TalkSliderWindow_Update(TalkSliderWindow *self);
TalkSliderWindow *TalkSliderWindow_Delete(TalkSliderWindow *self);
TalkSliderWindow *TalkSliderWindow_Destruct(TalkSliderWindow *self);
TalkSliderWindow *TalkSliderWindow_Construct(TalkSliderWindow *self);
void TalkSliderWindow_SetChoices(TalkSliderWindow *self, void *choices);

void TalkChoiceWindow_LayOut(TalkChoiceWindow *self);
void TalkChoiceWindow_StepClosing(TalkChoiceWindow *self);
void TalkChoiceWindow_StartClosing(TalkChoiceWindow *self);
void TalkChoiceWindow_StepOpen(TalkChoiceWindow *self);
void TalkChoiceWindow_EnterOpen(TalkChoiceWindow *self);
void TalkChoiceWindow_StepOpening(TalkChoiceWindow *self);
void TalkChoiceWindow_StartOpening(TalkChoiceWindow *self);
void TalkChoiceWindow_StepClosed(TalkChoiceWindow *self);
void TalkChoiceWindow_EnterClosed(TalkChoiceWindow *self);
u8 TalkChoiceWindow_Decided(TalkChoiceWindow *self);
int TalkChoiceWindow_IsClosed(TalkChoiceWindow *self);
void TalkChoiceWindow_Draw(TalkChoiceWindow *self);
void TalkChoiceWindow_Update(TalkChoiceWindow *self);
TalkChoiceWindow *TalkChoiceWindow_Delete(TalkChoiceWindow *self);
TalkChoiceWindow *TalkChoiceWindow_Destruct(TalkChoiceWindow *self);
TalkChoiceWindow *TalkChoiceWindow_Construct(TalkChoiceWindow *self);
void TalkChoiceWindow_SetChoices(TalkChoiceWindow *self, void *choices);

void TalkWindow_RequestOpen(TalkWindow *self);
void TalkWindow_BaseDestruct(TalkWindow *self);
TalkWindow *TalkWindow_Delete(TalkWindow *self);
void TalkWindow_Destruct(TalkWindow *self);
void TalkWindow_Construct(TalkWindow *self);

#endif
