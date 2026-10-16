/* The cursor of a talk's choice window (0x30 bytes at 0x84 of the window, talk_windows.h):
 * where it is among the talk's answers (talk_answers.h), shown as a list of labels in the
 * window's message window, one label per answer.
 *
 * Each frame (TalkChoiceCursor_Update), while no answer is picked: a press of the input not in
 * use switches to it; else with the touch screen an answer's row is touched to pick it, and
 * with the buttons up and down move the cursor (repeating while held, wrapping at both ends),
 * A picks the answer under it and B moves it to the cancelling answer, which is picked on the
 * next frame. A pick plays the answer's sound, or the cancel sound for the cancelling answer. */
#ifndef CLEAN_MAIN_TALK_CHOICE_CURSOR_H
#define CLEAN_MAIN_TALK_CHOICE_CURSOR_H

#include "types.h"

#define TALK_CHOICE_CURSOR_LABELS 5

struct LabelBox;
struct TalkAnswers;

typedef struct TalkChoiceCursor {
    s32 position;                                       /* 0x00: the answer under the cursor */
    void *window;                                       /* 0x04: the choice window's message window */
    struct LabelBox *labels[TALK_CHOICE_CURSOR_LABELS]; /* 0x08: the answers' labels, or NULL */
    u32 label_cells;                                    /* 0x1c: the widest label, in tiles */
    struct TalkAnswers *answers;                        /* 0x20 */
    s32 cancel_frames; /* 0x24: B was pressed: the frames until the cancelling answer is picked */
    s32 repeat_frames; /* 0x28: until the held direction moves the cursor again */
    s32 direction;     /* 0x2c: -1 up, 1 down, 0 while neither is held */
} TalkChoiceCursor;

void TalkChoiceCursor_PlayAnswerSound(TalkChoiceCursor *cursor);
int TalkChoiceCursor_StepButtons(TalkChoiceCursor *cursor);
int TalkChoiceCursor_StepTouch(TalkChoiceCursor *cursor);
int TalkChoiceCursor_SwitchInput(TalkChoiceCursor *cursor);
void TalkChoiceCursor_FreeLabels(TalkChoiceCursor *cursor);
void TalkChoiceCursor_ClearLabels(TalkChoiceCursor *cursor);
void TalkChoiceCursor_DrawLabels(TalkChoiceCursor *cursor);
void TalkChoiceCursor_MakeLabels(TalkChoiceCursor *cursor);
void TalkChoiceCursor_StopRepeat(TalkChoiceCursor *cursor);
void TalkChoiceCursor_MeasureLabels(TalkChoiceCursor *cursor);
int TalkChoiceCursor_UsesTouch(TalkChoiceCursor *cursor);
void TalkChoiceCursor_Update(TalkChoiceCursor *cursor);
void TalkChoiceCursor_Close(TalkChoiceCursor *cursor);
void TalkChoiceCursor_Hide(TalkChoiceCursor *cursor);
void TalkChoiceCursor_Show(TalkChoiceCursor *cursor);
void TalkChoiceCursor_Start(TalkChoiceCursor *cursor);
int TalkChoiceCursor_LabelCells(TalkChoiceCursor *cursor);
int TalkChoiceCursor_Picked(TalkChoiceCursor *cursor);
int TalkChoiceCursor_Position(TalkChoiceCursor *cursor);
unsigned int TalkChoiceCursor_Count(TalkChoiceCursor *cursor);
void TalkChoiceCursor_SetAnswers(TalkChoiceCursor *cursor, struct TalkAnswers *answers);
TalkChoiceCursor *TalkChoiceCursor_Destruct(TalkChoiceCursor *cursor);
void TalkChoiceCursor_Construct(TalkChoiceCursor *cursor, void *window);

#endif
