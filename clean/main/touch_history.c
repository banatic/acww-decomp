/* The touch screen and its frames before (touch_history.h). */
#include "touch_history.h"

#include "autoload_2/input.h"
#include "clean.h"
#include "sound.h"

/* The ARM7's word of extra buttons; bit 15 is set while the lid is closed. */
#define TOUCH_HISTORY_BUTTONS (*(const volatile u16 *) 0x027fffa8)
#define TOUCH_HISTORY_LID_CLOSED 0x8000

/* The touch screen this frame (Touch_Update). */
extern u8 data_021fbdd8;  /* the pen is down */
extern u8 data_021fbddc;  /* the pen went down or up this frame */
extern u16 data_021fbde0; /* the touch's x */
extern u16 data_021fbde4; /* the touch's y */

/* Kept from frame to frame. */
extern u8 data_021f6c30; /* frames since the pen went down */
extern u8 data_021f6c64; /* frames since the pen went up */
extern u8 data_021f6c60; /* where the pen went down: x */
extern u8 data_021f6c5c; /* and y */
extern u8 data_021f6c58; /* the touch's x, while the pen is down */
extern u8 data_021f6c54; /* and its y */

/* The same in the frame before. */
extern u8 data_021f6c40;  /* frames since the pen went down */
extern u8 data_021f6c3c;  /* frames since the pen went up */
extern u8 data_021f6c50;  /* where the pen went down: x */
extern u8 data_021f6c4c;  /* and y */
extern u8 data_021f6c48;  /* the touch's x */
extern u8 data_021f6c44;  /* and its y */
extern u8 data_021f6c38;  /* the pen was down */
extern u8 data_021f6c34;  /* the pen went down or up */
extern u16 data_021f6c68; /* the raw x (data_021fbde0) */
extern u16 data_021f6c6c; /* the raw y (data_021fbde4) */

/* func_020b9280: this frame's touch read. The values of the frame before are kept first; with
 * the lid closed the pen is lifted (going up this frame if it was down, at (0, 0)), else the
 * touch screen is read. While the pen is down its place is kept (and, when it just went down,
 * where it went down) and the x is handed to the sound system (SoundSys_SetPlayerByte); the
 * count since it went down or up runs.
 * QUIRK: the raw x and y of the frame before keep only their low byte. */
void TouchHistory_Update(void)
{
    u8 was_down = data_021fbdd8;

    data_021f6c50 = data_021f6c60;
    data_021f6c4c = data_021f6c5c;
    data_021f6c48 = data_021f6c58;
    data_021f6c44 = data_021f6c54;
    data_021f6c40 = data_021f6c30;
    data_021f6c3c = data_021f6c64;
    data_021f6c38 = was_down;
    data_021f6c34 = data_021fbddc != 0;
    data_021f6c68 = (u8) data_021fbde0;
    data_021f6c6c = (u8) data_021fbde4;

    if (TOUCH_HISTORY_BUTTONS & TOUCH_HISTORY_LID_CLOSED) {
        data_021fbddc = was_down;
        data_021fbdd8 = 0;
        data_021fbde0 = 0;
        data_021fbde4 = 0;
    } else {
        Touch_Update();
    }

    if (data_021fbdd8 != 0) {
        if (data_021fbddc != 0) {
            data_021f6c60 = (u8) data_021fbde0;
            data_021f6c5c = (u8) data_021fbde4;
            data_021f6c30 = 0;
        }
        if (data_021f6c30 < TOUCH_HISTORY_MAX_FRAMES) {
            data_021f6c30++;
        }
        u8 x = (u8) data_021fbde0;
        data_021f6c58 = x;
        data_021f6c54 = (u8) data_021fbde4;
        SoundSys_SetPlayerByte(x);
    } else {
        if (data_021fbddc != 0) {
            data_021f6c64 = 0;
        }
        if (data_021f6c64 < TOUCH_HISTORY_MAX_FRAMES) {
            data_021f6c64++;
        }
    }
}
CLEAN_AS(func_020b9280, TouchHistory_Update)

/* func_020b93e8: the touch screen set up (Touch_Init), the pen counted as up long ago, now and
 * in the frame before. */
void TouchHistory_Init(void)
{
    Touch_Init();
    data_021f6c30 = 0;
    data_021f6c64 = TOUCH_HISTORY_MAX_FRAMES;
    data_021f6c40 = 0;
    data_021f6c3c = TOUCH_HISTORY_MAX_FRAMES;
}
CLEAN_AS(func_020b93e8, TouchHistory_Init)
