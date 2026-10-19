/* The buttons and the touch screen (input.h). */
#include "input.h"

#include <assert.h>

#include "clean.h"
#include "main/game_halt.h"

static_assert(sizeof(TouchSample) == 8, "NitroSDK's TPData");

#define TOUCH_RING_SIZE 9
/* The ARM7 samples the touch screen four times a frame into this ring (TP auto sampling). */
extern TouchSample data_021fbdf0[TOUCH_RING_SIZE];
/* The calibrated touch the game goes by; while the pen is up, (0xff, 0xff). */
extern TouchSample data_021fbde8;
extern u8 data_021fbdd8;  /* the pen is down */
extern u8 data_021fbddc;  /* the pen went down or up this frame */
extern u16 data_021fbde0; /* the touch's x */
extern u16 data_021fbde4; /* the touch's y */

extern int TP_GetLatestIndexInAuto(void);
extern void TP_GetCalibratedPoint(TouchSample *calibrated, const TouchSample *raw);
extern void TP_Init(void);
extern int TP_GetUserInfo(void *calibration);
extern void TP_SetCalibrateParam(const void *calibration);
extern void TP_RequestSetStabilityAsync(int retry, int range);
extern void TP_RequestAutoSamplingStartAsync(int vcount, int frequency, TouchSample *ring, int size);
extern void TP_WaitBusy(int command);
extern int TP_CheckError(int command);

/* NitroSDK's TP_REQUEST_COMMAND_FLAG_* */
#define TP_COMMAND_AUTO_ON 2
#define TP_COMMAND_SET_STABILITY 8

/* func_020e9314: the touch for this frame from the four samples before the newest in the ring.
 * Three valid touches in a row give the middle one: of the last three first, else of the first
 * three. Without any touch in the four, the pen is up; with touches that are not three valid
 * in a row, the touch stays as it was. */
void Touch_Update(void)
{
    int newest = TP_GetLatestIndexInAuto();
    TouchSample sample[4] = {{0}};
    BOOL any = FALSE;
    for (int i = 0; i < 4; i++) {
        int index = newest - 4 + i;
        if (index < 0) {
            index += TOUCH_RING_SIZE;
        }
        const TouchSample *raw = &data_021fbdf0[index];
        if (raw->touch != 0) {
            any = TRUE;
        }
        if (raw->validity != 0) {
            sample[i].touch = 0;
        } else {
            sample[i] = *raw;
        }
    }

    if (sample[3].touch != 0 && sample[2].touch != 0 && sample[1].touch != 0) {
        TP_GetCalibratedPoint(&data_021fbde8, &sample[2]);
    } else if (sample[0].touch != 0 && sample[1].touch != 0 && sample[2].touch != 0) {
        TP_GetCalibratedPoint(&data_021fbde8, &sample[1]);
    } else if (!any) {
        data_021fbde8.touch = 0;
        data_021fbde8.x = 0xff;
        data_021fbde8.y = 0xff;
        data_021fbde8.validity = 0;
    }
    data_021fbddc = (u8) (data_021fbde8.touch ^ data_021fbdd8);
    data_021fbdd8 = (u8) data_021fbde8.touch;
    data_021fbde0 = data_021fbde8.x;
    data_021fbde4 = data_021fbde8.y;
}
CLEAN_AS(func_020e9314, Touch_Update)

/* func_020e948c: the touch screen set up with the user's calibration and sampling into the
 * ring four times a frame; the game stops (OS_Terminate) when the ARM7 reports an error. */
void Touch_Init(void)
{
    u8 calibration[12];
    TP_Init();
    TP_GetUserInfo(calibration);
    TP_SetCalibrateParam(calibration);
    TP_RequestSetStabilityAsync(3, 30);
    TP_WaitBusy(TP_COMMAND_SET_STABILITY);
    if (TP_CheckError(TP_COMMAND_SET_STABILITY) != 0) {
        GameHalt_Terminate();
    }
    TP_RequestAutoSamplingStartAsync(0, 4, data_021fbdf0, TOUCH_RING_SIZE);
    TP_WaitBusy(TP_COMMAND_AUTO_ON);
    if (TP_CheckError(TP_COMMAND_AUTO_ON) != 0) {
        GameHalt_Terminate();
    }
    data_021fbdd8 = 0;
    data_021fbddc = 0;
    data_021fbde0 = 0xff;
    data_021fbde4 = 0xff;
}
CLEAN_AS(func_020e948c, Touch_Init)

/* The buttons: KEYINPUT has A-L (bits 0-9, 0 when pressed); the ARM7 copies X, Y, the debug
 * button (bits 10, 11, 13, also 0 when pressed) and the lid (bit 15, 1 when closed) to a word
 * of the shared area (NitroSDK's PAD_Read and PAD_DetectFold). */
#define REG_KEYINPUT (*(const volatile u16 *) 0x04000130)
#define BUTTON_XY_BUF (*(const volatile u16 *) 0x027fffa8)
#define PAD_KEYS_MASK 0x2fff
#define PAD_LID_CLOSED 0x8000

/* The d-pad's angle by bits 4-7 of the keys (right, left, up, down). */
extern const s16 data_02138f6c[16];
extern u8 data_021fbe38;
extern u16 data_021fbe3c; /* the keys held in the frame before */
extern PadState data_021fbe40;

/* func_020e9548: the buttons for this frame; none while the lid is closed.
 * HW: the shared word is read first for the lid, then KEYINPUT and the shared word again for
 * the keys, as NitroSDK's PAD_Read does. */
void Pad_Update(void)
{
    u16 keys = 0;
    if ((BUTTON_XY_BUF & PAD_LID_CLOSED) == 0) {
        u16 key_input = REG_KEYINPUT;
        u16 xy = BUTTON_XY_BUF;
        keys = (u16) (((key_input | xy) ^ PAD_KEYS_MASK) & PAD_KEYS_MASK);
    }
    u16 before = data_021fbe3c;
    data_021fbe38 = 0;
    data_021fbe40.pressed = (u16) (keys & ~before);
    data_021fbe3c = keys;
    data_021fbe40.held = keys;
    data_021fbe40.dpad_angle = data_02138f6c[(keys & 0xf0) >> 4];
}
CLEAN_AS(func_020e9548, Pad_Update)
