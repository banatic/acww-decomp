/* The buttons and the touch screen, read once a frame into the game's input state. */
#ifndef CLEAN_AUTOLOAD_2_INPUT_H
#define CLEAN_AUTOLOAD_2_INPUT_H

#include "types.h"

/* A touch screen sample (NitroSDK's TPData). */
typedef struct TouchSample {
    u16 x;
    u16 y;
    u16 touch;    /* the pen is down */
    u16 validity; /* not 0: the position is not reliable */
} TouchSample;

/* The buttons as the game reads them each frame. */
typedef struct PadState {
    u16 held;
    u16 pressed;    /* held now and not in the frame before */
    s16 dpad_angle; /* the d-pad's direction as an angle (fx_math.h), from the game's table */
} PadState;

void Touch_Update(void);
void Touch_Init(void);
void Pad_Update(void);

#endif
