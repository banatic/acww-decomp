/* The game's main loop (MainLoop_Run, never left): each frame the Wi-Fi Connection processed,
 * the session's error flags taken as the ones shown, the frame's start (the lid, the display's
 * hooks, the session's delivery, the touch history, the pad, the game stop, the clock), the
 * caution window and the processes run (drawing only while errors are shown), the drawing ended
 * and the 3D buffers swapped, then a wait for the next frame (data_021cfb6c set meanwhile, so the
 * VBlank handler wakes the loop when the frame's VBlanks have passed), and the work after the
 * VBlank and after the frame (text boxes, the sky, the line handlers, the sound). */
#ifndef CLEAN_MAIN_MAIN_LOOP_H
#define CLEAN_MAIN_MAIN_LOOP_H

#include "types.h"

void MainLoop_Run(void);
void MainLoop_AfterDraw(void);
void MainLoop_BeforeProcesses(void);
void MainLoop_AfterFrame(int errors);
void MainLoop_AfterVBlank(void);
void MainLoop_EndDraw(u32 errors);
void MainLoop_BeginFrame(int errors);
void MainLoop_WaitFrame(void);
void MainLoop_WaitVBlank(void);
void MainLoop_StartupNothing(void);

#endif
