/* A spinning sprite of the talks (vtable data_020e23e4, 0x24 bytes, derived from main's screen
 * sprite base, screen_sprite.h). Each talk keeps one at its 0x50, places it every frame from
 * two of its own fields and starts and stops it (func_02068c24, func_02068c10).
 *
 * It is drawn on the main screen as two cells: the first frame of animation 0 of the table
 * data_020d71cc turned by `angle` (one fifteenth of a turn more every frame) and, over it, the
 * first frame of animation 2, not turned. While it spins a sound plays on sound handle 0x38,
 * picked by `sound` from data_020d0bac.
 *
 * Its states (TalkSpinnerState), stepped by its update (TalkSpinner_Update, through a table of
 * member functions):
 *   idle      until a start is requested: then it spins and its sound starts;
 *   spinning  until the request is withdrawn: then its sound stops and it is idle again.
 * When `window` is set it is also drawn as OBJ window, and the main screen's OBJ window is
 * enabled while it spins; nothing in the game sets it. */
#ifndef CLEAN_MAIN_TALK_SPINNER_H
#define CLEAN_MAIN_TALK_SPINNER_H

#include "screen_sprite.h"
#include "types.h"

enum TalkSpinnerState {
    TALK_SPINNER_IDLE = 0,
    TALK_SPINNER_SPINNING = 1,
};

typedef struct TalkSpinner {
    ScreenSprite base; /* vtable data_020e23e4 */
    int state;         /* 0x0c: TalkSpinnerState */
    u16 angle;         /* 0x10: the first cell's angle (0x10000 a turn) */
    u8 window;         /* 0x12: also drawn as OBJ window */
    u8 requested;      /* 0x13: a start requested, until it is withdrawn */
    int offset_x;      /* 0x14: added to the base class's place */
    int offset_y;      /* 0x18 */
    u32 sound;         /* 0x1c: index in data_020d0bac */
    u8 sound_on;       /* 0x20: the sound was started and not stopped */
    u8 pad_21[3];
} TalkSpinner;

void TalkSpinner_StopSound(TalkSpinner *spinner);
void TalkSpinner_StartSound(TalkSpinner *spinner);
void TalkSpinner_StepSpinning(TalkSpinner *spinner);
void TalkSpinner_Begin(TalkSpinner *spinner);
void TalkSpinner_StepIdle(TalkSpinner *spinner);
void TalkSpinner_SetIdle(TalkSpinner *spinner);
void TalkSpinner_SetOffset(TalkSpinner *spinner, int x, int y);
int TalkSpinner_CallDraw(TalkSpinner *spinner);
int TalkSpinner_CallUpdate(TalkSpinner *spinner);
void TalkSpinner_Finish(TalkSpinner *spinner);
void TalkSpinner_Init(TalkSpinner *spinner);
void TalkSpinner_Update(TalkSpinner *spinner);
void TalkSpinner_Draw(TalkSpinner *spinner);
TalkSpinner *TalkSpinner_Delete(TalkSpinner *spinner);
TalkSpinner *TalkSpinner_Destruct(TalkSpinner *spinner);
TalkSpinner *TalkSpinner_Construct(TalkSpinner *spinner);
void TalkSpinner_Stop(TalkSpinner *spinner);
void TalkSpinner_Start(TalkSpinner *spinner, int sound);

#endif
