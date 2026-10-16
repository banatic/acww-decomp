/* The screen's transition between scenes (data_021c75b8): the screen opened from closed
 * (ScreenTransition_Open) or closed from shown (ScreenTransition_Close) over a number of
 * frames, in one of four kinds, each with four functions in the table data_020ca514 (begin,
 * finish, update after the drawing, apply after the VBlank):
 *
 *   0  a fade from or to black (the master brightness)
 *   1  the same from or to white
 *   2  a circle (window 0 of both engines, set a line at a time from the HBlank) that grows
 *      from or shrinks to the screen's centre, background 2 (black) covering the rest
 *   3  none: the screen is shown or closed at once
 *
 * `cover` goes from 0x1000 (closed) to 0 (shown) when opening and back when closing, by `speed`
 * each frame (ScreenTransition_AfterDraw); once it is there `speed` is 0 and the next
 * ScreenTransition_AfterVBlank ends the transition. A closed screen shows only the main
 * engine's OBJ, black. */
#ifndef CLEAN_MAIN_SCREEN_TRANSITION_H
#define CLEAN_MAIN_SCREEN_TRANSITION_H

#include "itcm/interrupts.h" /* LineHandler */
#include "types.h"

/* ScreenTransition.state */
enum ScreenTransitionState {
    SCREEN_TRANSITION_CLOSED = 0,
    SCREEN_TRANSITION_OPENING = 1,
    SCREEN_TRANSITION_SHOWN = 2,
    SCREEN_TRANSITION_CLOSING = 3,
};

/* ScreenTransition.kind */
enum ScreenTransitionKind {
    SCREEN_TRANSITION_BLACK = 0,
    SCREEN_TRANSITION_WHITE = 1,
    SCREEN_TRANSITION_CIRCLE = 2,
    SCREEN_TRANSITION_NONE = 3,
};

#define SCREEN_TRANSITION_COVERED 0x1000 /* `cover` of a closed screen */
#define SCREEN_TRANSITION_LINES 96       /* the circle's lines: the top half, mirrored below */

typedef struct ScreenTransition {
    u8 state; /* enum ScreenTransitionState */
    u8 kind;  /* 0x01: enum ScreenTransitionKind */
    u8 unk_02[2];
    int cover;      /* 0x04: 0x1000 closed .. 0 shown */
    int speed;      /* 0x08: added to `cover` each frame, 0 once it is there */
    int brightness; /* 0x0c: the fades' master brightness (-16 black .. 16 white) */
} ScreenTransition;

/* The functions of a kind (data_020ca514); the game's, NULL for none. */
typedef struct ScreenTransitionFunctions {
    void (*begin)(void);
    void (*finish)(void);
    void (*update)(void);
    void (*apply)(void);
} ScreenTransitionFunctions;

/* The circle's flags (data_021c75ac) */
#define SCREEN_TRANSITION_HANDLER 0x01 /* its line handler (data_021c75cc) is in the list */
#define SCREEN_TRANSITION_WRITE_FIRST                                                                                         \
    0x02 /* the circle is written to the first table of lines, the
                                           * second shown; swapped after each VBlank */

void ScreenTransition_ClearBg2(void);
void ScreenTransition_HideBg2(void);
void ScreenTransition_ShowClosed(void);
void ScreenTransition_AfterVBlank(void);
void ScreenTransition_AfterDraw(void);
int ScreenTransition_Open(int kind, int frames, int keep_music);
int ScreenTransition_Close(int kind, int frames);
void ScreenTransition_Reset(void);
void ScreenTransitionNone_Apply(void);
void ScreenTransitionNone_Update(void);
void ScreenTransitionNone_Finish(void);
void ScreenTransitionNone_Begin(void);
void ScreenTransitionCircle_Apply(void);
void ScreenTransitionCircle_Update(void);
void ScreenTransitionCircle_Finish(void);
void ScreenTransitionCircle_Begin(void);
void ScreenTransitionCircle_SetUp(void);
void ScreenTransitionCircle_VBlank(void);
void ScreenTransitionCircle_HBlank(void);
void ScreenTransitionFade_Apply(void);
void ScreenTransitionFade_Update(void);
void ScreenTransitionFade_Finish(void);
void ScreenTransitionFade_Begin(void);

#endif
