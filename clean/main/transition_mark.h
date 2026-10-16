/* A mark that blinks over the main screen while a screen transition closes and opens in a
 * linked game (the object at data_021d3654, vtable data_020e2400, 0x3c bytes, derived from
 * main's screen sprite base, screen_sprite.h), and the process that draws and updates it
 * (TransitionMarkProcess, vtable data_020e241c, 0x50 bytes, a process of the root class
 * data_020da13c). The mark is a cell animation (data_020d71f4) drawn at the base class's
 * place, both as OBJs and as OBJ window. What the cell shows is not known.
 *
 * Its states (TransitionMarkState), stepped by its update (TransitionMark_Update, through a
 * table of member functions):
 *   waiting   `delay` counts down, if set; when it ends the mark starts blinking: the main
 *             screen's OBJ window is enabled with only the OBJs inside it.
 *   blinking  the mark is shown for 0.2 s, hidden for 0.2 s, shown for 0.2 s and hidden for
 *             0.6 s, round again (timed with the system's tick counter); `frames_left`, once
 *             set, counts down, and when it ends the OBJ window is disabled and the mark
 *             waits again.
 *
 * When a transition closes with a begin function (ScreenTransition_Close), the running scene
 * is not the scene change and the session is linked, `delay` is set from the transition's
 * kind; when one opens (ScreenTransition_Open) outside the scene change, `frames_left` is set.
 * While a scene sets its display up the mark is not drawn (`suppressed`). */
#ifndef CLEAN_MAIN_TRANSITION_MARK_H
#define CLEAN_MAIN_TRANSITION_MARK_H

#include "autoload_2/process.h"
#include "screen_icon.h" /* CellAnim */
#include "screen_sprite.h"
#include "types.h"

enum TransitionMarkState {
    TRANSITION_MARK_WAITING = 0,
    TRANSITION_MARK_BLINKING = 1,
};

typedef struct TransitionMark {
    ScreenSprite base; /* vtable data_020e2400 */
    CellAnim anim;     /* 0x0c */
    int state;         /* 0x20: TransitionMarkState */
    int delay;         /* 0x24: frames before blinking starts; 0 for none */
    int frames_left;   /* 0x28: frames of blinking left; 0 for until set */
    int blink_step;    /* 0x2c: 0-3, the part of the blink (TransitionMark_StepBlinking) */
    u32 next_tick[2];  /* 0x30: the system tick (64 bits, low word first) of the next part */
    u8 shown;          /* 0x38: drawn in this part of the blink */
    u8 suppressed;     /* 0x39: not drawn while a scene sets its display up */
    u8 pad_3a[2];
} TransitionMark;

typedef struct TransitionMarkProcess {
    Process process;
} TransitionMarkProcess;

int TransitionMarkProcess_Draw(void);
int TransitionMarkProcess_Execute(void);
int TransitionMarkProcess_Delete(void);
int TransitionMarkProcess_Create(void);
TransitionMarkProcess *TransitionMarkProcess_DestructFree(TransitionMarkProcess *process);
TransitionMarkProcess *TransitionMarkProcess_Destruct(TransitionMarkProcess *process);
TransitionMarkProcess *TransitionMarkProcess_Construct(TransitionMarkProcess *process);
void TransitionMarkProcess_New(void);
void TransitionMark_SetAnim(TransitionMark *mark);
void TransitionMark_StepBlinking(TransitionMark *mark);
void TransitionMark_Start(TransitionMark *mark);
void TransitionMark_StepWaiting(TransitionMark *mark);
void TransitionMark_Stop(TransitionMark *mark);
void *TransitionMark_CallDraw(TransitionMark *mark);
void *TransitionMark_CallUpdate(TransitionMark *mark);
void TransitionMark_Rewind(TransitionMark *mark);
void TransitionMark_Reset(TransitionMark *mark);
void TransitionMark_DrawInstance(void);
void TransitionMark_UpdateInstance(void);
void TransitionMark_RewindInstance(void);
void TransitionMark_ResetInstance(void);
void TransitionMark_Suppress(void);
void TransitionMark_RestoreWithOutside(void);
void TransitionMark_Restore(void);
void TransitionMark_SetBlinkFrames(int kind);
void TransitionMark_SetDelay(int kind);
void TransitionMark_Update(TransitionMark *mark);
void TransitionMark_Draw(TransitionMark *mark);
TransitionMark *TransitionMark_Delete(TransitionMark *mark);
TransitionMark *TransitionMark_Destruct(TransitionMark *mark);
TransitionMark *TransitionMark_Construct(TransitionMark *mark);

#endif
