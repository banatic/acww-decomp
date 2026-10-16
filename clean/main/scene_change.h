/* The process between scenes, and the destructors of the two process classes next to it.
 *
 * - Process class 5 (vtable data_020e5408, 0x54 bytes, profile data_020e53e0) is what
 *   func_020b5e44 asks for to change scenes (the boot screen does with 3, boot_screen.h).
 *   Started, it sets up the display, the scene's sound and the shared objects; in a session it
 *   then waits for the link's state 0x0b (and moves it on to 0x0c). It then asks for process
 *   class 6 with 3 and the byte func_020b5e44 kept (global_021dc5b0.h), and idles. Ended, it
 *   clears the running scene's display hooks.
 * - Process class 4 (vtable data_020e5460, 0x50 bytes, profile data_020e5450) has only the
 *   process base's functions.
 * - Process class 6 (vtable data_020e5574) is made by func_020b7238. */
#ifndef CLEAN_MAIN_SCENE_CHANGE_H
#define CLEAN_MAIN_SCENE_CHANGE_H

#include "autoload_2/process.h"
#include "types.h"

/* The steps of the process between scenes (SceneChange.step). */
enum SceneChangeStep {
    SCENE_CHANGE_WAIT_LINK = 0, /* in a session: until the link's state is 0x0b */
    SCENE_CHANGE_START = 1,     /* class 6 asked for */
    SCENE_CHANGE_IDLE = 2
};

typedef struct SceneChange {
    Process base;
    s32 step; /* 0x50: enum SceneChangeStep */
} SceneChange;

SceneChange *SceneChange_Destruct(SceneChange *change);
SceneChange *SceneChange_Delete(SceneChange *change);
int SceneChange_Slot9(void);
int SceneChange_Update(SceneChange *change);
int SceneChange_End(void);
int SceneChange_Init(SceneChange *change);
void SceneChange_Idle(SceneChange *change);
void SceneChange_Start(SceneChange *change);
void SceneChange_WaitLink(SceneChange *change);
SceneChange *SceneChange_New(void);

Process *SceneClass4_New(void);
Process *SceneClass4_Destruct(Process *process);
Process *SceneClass4_Delete(Process *process);

Process *SceneClass6_Destruct(Process *process);
Process *SceneClass6_Delete(Process *process);

#endif
