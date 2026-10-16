/* The game's main loop (main_loop.h). */
#include "main_loop.h"

#include <stdint.h>

#include "autoload_2/input.h"
#include "autoload_2/network.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/a_mes_obj.h"
#include "main/caution_window.h"
#include "main/clock.h"
#include "main/display_frame.h"
#include "main/empty_0203de64.h"
#include "main/game_stop.h"
#include "main/lid_sleep.h"
#include "main/line_handlers.h"
#include "main/link_scene.h"
#include "main/scene_sound.h"
#include "main/session.h"
#include "main/session_link.h"
#include "main/sky.h"
#include "main/text_draw.h"
#include "main/touch_history.h"
#include "main/transfer_queue.h"

#define REG32(address) (*(volatile u32 *) (uintptr_t) (address))
#define REG_DB_DISPCNT 0x04001000u
#define REG_SWAP_BUFFERS 0x04000540u
#define DB_DISPCNT_DISPLAY_ON 0x00010000u /* the sub screen's display mode 1: its graphics */
#define SWAP_MANUAL_SORT 0x1
#define SWAP_W_BUFFER 0x2

extern NetSession *data_020ccf94;
extern u16 data_021cfb6c;  /* set while the loop waits for the next frame */
extern int data_021fbdd0;  /* the frames drawn */
extern u8 data_021cfb98[]; /* the threads waiting for the next frame (OSThreadQueue) */
extern u8 data_021cfb90[]; /* the threads waiting for the next VBlank */

extern void GX_DispOn(void);
extern void OS_SleepThread(void *queue);

/* func_0206e560: the main loop. Never returns. QUIRK: the session is read once, before the
 * loop. HW: the sub screen's display is turned on first. */
void MainLoop_Run(void)
{
    GX_DispOn();
    REG32(REG_DB_DISPCNT) |= DB_DISPCNT_DISPLAY_ON;
    LidSleep_Reset();
    NetSession *session = data_020ccf94;
    for (;;) {
        Wfc_Process();
        Session_SetShownErrorFlags(session, (int) Session_GetErrorFlags(session));
        u32 errors = Session_GetShownErrorFlags(session);
        MainLoop_BeginFrame((int) errors);
        MainLoop_BeforeProcesses();
        int trouble = errors != 0;
        CautionWindow_UpdateGlobal(trouble);
        Process_RunFrame(trouble);
        CautionWindow_SetCameraGlobal();
        MainLoop_EndDraw(errors);
        MainLoop_AfterDraw();
        data_021cfb6c = 1;
        MainLoop_WaitFrame();
        data_021cfb6c = 0;
        MainLoop_AfterVBlank();
        MainLoop_AfterFrame((int) errors);
    }
}
CLEAN_AS(func_0206e560, MainLoop_Run)

/* func_0206e5ec */
void MainLoop_AfterDraw(void)
{
    Empty0203de64_Nothing70();
}
CLEAN_AS(func_0206e5ec, MainLoop_AfterDraw)

/* func_0206e5f4 */
void MainLoop_BeforeProcesses(void)
{
    Empty0203de64_Nothing74();
}
CLEAN_AS(func_0206e5f4, MainLoop_BeforeProcesses)

/* func_0206e5fc: the text boxes of group 0 drawn, the message objects' pending uploads, the
 * sky's line shift swapped, the line handlers' frame and the sound's. QUIRK: the ROM passes
 * whether errors are shown to SoundLayer_Frame, which takes nothing. */
void MainLoop_AfterFrame(int errors)
{
    (void) errors;
    TextDraw_FlushGroup0();
    AMesObj_UploadPending();
    Sky_SwapLineShift();
    LineHandlers_RunFrame();
    SoundLayer_Frame();
}
CLEAN_AS(func_0206e5fc, MainLoop_AfterFrame)

/* func_0206e624 */
void MainLoop_AfterVBlank(void)
{
    DisplayFrame_AfterVBlank();
    CautionWindow_ApplyBlendGlobal();
    TransferQueue_RunMain();
}
CLEAN_AS(func_0206e624, MainLoop_AfterVBlank)

/* func_0206e63c: the drawing ended: without errors shown the link scene's hook (empty), the
 * session's frame (counted only without errors), the display's end of drawing, one frame more
 * drawn. HW: then the 3D buffers swapped, with translucent polygons sorted by hand and
 * w-buffering. */
void MainLoop_EndDraw(u32 errors)
{
    if (errors == 0) {
        LinkScene_Empty6C04();
    }
    Session_Update((int) errors);
    DisplayFrame_EndDraw();
    data_021fbdd0++;
    REG32(REG_SWAP_BUFFERS) = SWAP_MANUAL_SORT | SWAP_W_BUFFER;
}
CLEAN_AS(func_0206e63c, MainLoop_EndDraw)

/* func_0206e670: the frame's start; while errors are shown the clock is read without its check.
 * QUIRK: Session_Deliver is called only while errors are shown, and it does nothing when given
 * a value other than 0, so the call has no effect. */
void MainLoop_BeginFrame(int errors)
{
    LidSleep_Update();
    DisplayFrame_Begin();
    if (errors != 0) {
        Session_Deliver(errors);
    }
    TouchHistory_Update();
    Pad_Update();
    GameStop_Update();
    Clock_Refresh((const void *) (uintptr_t) errors);
}
CLEAN_AS(func_0206e670, MainLoop_BeginFrame)

/* func_0206e6a0: this thread put to sleep until the next frame. */
void MainLoop_WaitFrame(void)
{
    OS_SleepThread(data_021cfb98);
}
CLEAN_AS(func_0206e6a0, MainLoop_WaitFrame)

/* func_0206e6b0: this thread put to sleep until the next VBlank. */
void MainLoop_WaitVBlank(void)
{
    OS_SleepThread(data_021cfb90);
}
CLEAN_AS(func_0206e6b0, MainLoop_WaitVBlank)

/* func_0206e6c0: called once at start-up (Startup_InitGame); does nothing. */
void MainLoop_StartupNothing(void) {}
CLEAN_AS(func_0206e6c0, MainLoop_StartupNothing)
