/* The caution window of a wireless session (data_021c5c4c, one object built at start-up): when
 * the session reports trouble, a 3D window ("caution/caution_window.nsbmd") shows a message
 * line by line with a countdown of seconds; when the trouble lasts or is serious, the sound,
 * the backup card and the session are shut down and a last message waits for a touch or the A
 * button before func_02116a1c(0) is called.
 *
 * The main loop calls CautionWindow_UpdateGlobal each frame with whether the session shows
 * error flags, then CautionWindow_SetCameraGlobal; CautionWindow_ApplyBlendGlobal runs at the
 * frame's end. The window's text is drawn into a 32 x 2-tile bitmap in RAM and copied into four
 * 0x800-byte parts of the model's texture, one per line.
 *
 * The update is a state machine (CautionWindow.state) dispatched through a table of member
 * functions:
 *   0 off;
 *   1 idle: on trouble, either 5 at once (flags 0x7c) or 2;
 *   2 delay: 20 frames of trouble, then 3 (the screen's planes are hidden);
 *   3 the message and the seconds' label are copied, then 4;
 *   4 countdown: the lines are drawn, the seconds counted down from 15; back to 1 when the
 *     trouble ends, else 5 one second after 0;
 *   5 shutdown: the last message is copied, then 6;
 *   6 its lines are drawn; after 20 frames, a touch or A goes to 7;
 *   7 one frame, then func_02116a1c(0). */
#ifndef CLEAN_MAIN_CAUTION_WINDOW_H
#define CLEAN_MAIN_CAUTION_WINDOW_H

#include "autoload_2/matrix.h"
#include "types.h"

#define CAUTION_WINDOW_LINES 4
#define CAUTION_WINDOW_BITMAP_SIZE 0x800 /* 32 x 2 tiles of 32 bytes */

enum CautionWindowState {
    CAUTION_WINDOW_OFF = 0,
    CAUTION_WINDOW_IDLE = 1,
    CAUTION_WINDOW_DELAY = 2,
    CAUTION_WINDOW_OPEN = 3,
    CAUTION_WINDOW_COUNTDOWN = 4,
    CAUTION_WINDOW_SHUTDOWN = 5,
    CAUTION_WINDOW_LAST_MESSAGE = 6,
    CAUTION_WINDOW_END = 7,
    CAUTION_WINDOW_STATES = 8
};

typedef struct CautionWindow {
    const void *vtable;                    /* 0x000 */
    u8 model[0x5c];                        /* 0x004: the window's model (func_0205556c) */
    u8 *model_resource;                    /* 0x060: inside the model: its resource, the texture is found through it */
    u8 unk_64[4];                          /* 0x064 */
    Mtx43 matrix;                          /* 0x068: a translation to z -1.0 */
    u8 unk_98[8];                          /* 0x098 */
    u8 transfer[0x1c];                     /* 0x0a0: the copy of the bitmap into the texture (func_020b9f80) */
    s32 state;                             /* 0x0bc: CautionWindowState */
    s32 timer;                             /* 0x0c0: frames */
    s32 line;                              /* 0x0c4: the next line to draw; CAUTION_WINDOW_LINES when all are */
    u8 shown;                              /* 0x0c8: the camera and the model's scale are set each frame */
    u8 trouble;                            /* 0x0c9: the session showed error flags this frame */
    u8 planes_hidden;                      /* 0x0ca */
    u8 blend_pending;                      /* 0x0cb: the blend registers are to be saved or restored */
    u16 blend_main;                        /* 0x0cc: the saved BLDCNT of the main screen */
    u16 blend_sub;                         /* 0x0ce: and of the sub screen */
    u32 main_planes;                       /* 0x0d0: the saved planes and windows (display_shadow.h) */
    u32 sub_planes;                        /* 0x0d4 */
    u32 main_windows;                      /* 0x0d8 */
    u32 sub_windows;                       /* 0x0dc */
    s32 text_width;                        /* 0x0e0: of the last line before its seconds; 0 when it has none */
    s32 seconds;                           /* 0x0e4: the seconds shown on the last line; -1 none */
    u8 message[0x114];                     /* 0x0e8: label: the message, a line of it on each texture part */
    u8 unit[0x54];                         /* 0x1fc: label: what follows the seconds */
    u8 line_text[0x94];                    /* 0x250: label: the line being drawn */
    u8 bitmap[CAUTION_WINDOW_BITMAP_SIZE]; /* 0x2e4 */
} CautionWindow;

void CautionWindow_EndUpdate(CautionWindow *self);
void CautionWindow_LastMessageUpdate(CautionWindow *self);
void CautionWindow_EnterEnd(CautionWindow *self);
void CautionWindow_EnterLastMessage(CautionWindow *self);
void CautionWindow_ShutdownUpdate(CautionWindow *self);
void CautionWindow_EnterShutdown(CautionWindow *self);
void CautionWindow_CountdownUpdate(CautionWindow *self);
void CautionWindow_EnterCountdown(CautionWindow *self);
void CautionWindow_OpenUpdate(CautionWindow *self);
void CautionWindow_EnterOpen(CautionWindow *self);
void CautionWindow_DelayUpdate(CautionWindow *self);
void CautionWindow_EnterDelay(CautionWindow *self);
void CautionWindow_IdleUpdate(CautionWindow *self);
void CautionWindow_EnterIdle(CautionWindow *self);
void CautionWindow_OffUpdate(CautionWindow *self);
void CautionWindow_EnterOff(CautionWindow *self);
void CautionWindow_CheckNetError(void);
void CautionWindow_StopSound(CautionWindow *self);
void CautionWindow_RestorePlanes(CautionWindow *self);
void CautionWindow_HidePlanes(CautionWindow *self);
void CautionWindow_Reset(CautionWindow *self);
void CautionWindow_ComposeLine(CautionWindow *self, int line, int with_code);
void CautionWindow_DrawSeconds(CautionWindow *self, void *chars, int x);
void CautionWindow_DrawLine(CautionWindow *self);
void CautionWindow_ClearTexture(CautionWindow *self);
void CautionWindow_UploadLine(CautionWindow *self, int part);
void CautionWindow_SetMatrix(CautionWindow *self);
void CautionWindow_ApplyBlend(CautionWindow *self);
void CautionWindow_SetCamera(CautionWindow *self);
void CautionWindow_Update(CautionWindow *self, unsigned char trouble);
void CautionWindow_Close(CautionWindow *self);
void CautionWindow_Start(CautionWindow *self);
int CautionWindow_LoadMessages(void);
void CautionWindow_ApplyBlendGlobal(void);
void CautionWindow_SetCameraGlobal(void);
void CautionWindow_UpdateGlobal(int trouble);
void CautionWindow_CloseGlobal(void);
void CautionWindow_StartGlobal(void);
int CautionWindow_IsShuttingDown(void);

#endif
