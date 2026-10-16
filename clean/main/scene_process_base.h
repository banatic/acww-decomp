/* The base class of the scenes' processes (vtable data_020e3c94, derived from the processes'
 * root class data_020da13c; the process between scenes, scene_change.h, and the field's,
 * scene_process.h, derive from it), and the request for the next scene.
 *
 * The next scene is asked for as a process class (data_020e3c80; 0xd8 for none) with the
 * kinds of transition that close the screen before it and open it after (data_021f42ec,
 * data_021f42e8): SceneProcessBase_Request. Each frame the resident process spawns the class
 * asked for under itself, once (SceneProcessBase_StartAsked). While a change is pending the
 * running scene (data_021f42f4) stops executing and closes the screen once it is shown; once
 * the screen is closed the scene deletes itself (SceneProcessBase_CheckChange). The next one
 * opens the screen four frames into its execution.
 *
 * The screen's transition (data_021c75b8) is 0 while the screen is closed, 1 while it opens,
 * 2 while it is shown and 3 while it closes: func_02041c88 starts opening it (from 0) and
 * func_02041d14 closing it (from 2, or at any time while data_021c75b0 is set), each with a
 * kind of transition and a number of frames.
 *
 * Its creation sets the display up for a scene in the first frame (the step data_021f42f0
 * goes from 0 to 1) and moves the link on (6 to 7, 0xd to 0xe) when this system's slot of the
 * session is taken; its execution runs the link's work of the frame (func_020a6c08) first. */
#ifndef CLEAN_MAIN_SCENE_PROCESS_BASE_H
#define CLEAN_MAIN_SCENE_PROCESS_BASE_H

#include "autoload_2/process.h"
#include "types.h"

#define SCENE_PROCESS_BASE_NONE 0xd8 /* data_020e3c80 when no scene is asked for */

Process *SceneProcessBase_Destruct(Process *process);
Process *SceneProcessBase_DestructFree(Process *process);
void SceneProcessBase_CheckChange(Process *process);
int SceneProcessBase_StartAsked(void);
void SceneProcessBase_ResetRequest(void);
void SceneProcessBase_Request(int class_id, int param, int arg, int unused);
void SceneProcessBase_AfterDraw(Process *process, int outcome);
int SceneProcessBase_CanDraw(Process *process);
void SceneProcessBase_AfterExecute(Process *process);
int SceneProcessBase_CanExecute(Process *process);
void SceneProcessBase_AfterDelete(Process *process, int outcome);
int SceneProcessBase_CanDelete(Process *process);
void SceneProcessBase_AfterCreate(Process *process, int outcome);
int SceneProcessBase_CanCreate(Process *process);
void SceneProcessBase_SetUpDisplay(void);
Process *SceneProcessBase_New(void);

#endif
