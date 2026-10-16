/* The process of a scene on the field: process class 6 (vtable data_020e5574, 0x50 bytes,
 * profile data_020e54ec), which the process between scenes asks for (scene_change.h); and
 * process class 3 (vtable data_020e5764, profile data_020e5754), which only makes the scene's
 * sound.
 *
 * Class 6's creation runs six steps, some per frame while each frame's 40 ms last (the step
 * reached is the scene base's byte data_021f42f0, 1-6):
 *   1 SceneProcess_Enter: the scene taken from main's entry record (data_021f69d0) becomes the
 *     current one (scene_query.h) and its overlays are loaded: overlay 2, the mode's (3
 *     outdoors, 4 in a room; the mode of each scene is data_020e5538) and the scene's own
 *     (data_020e5688), then the two its SceneInfo names. The SceneInfo (the overlays' table
 *     data_020e55bc) becomes the running one (data_021f6948);
 *   2 SceneProcess_SetUpPlayers: the display set up (scene_display.h), the scene's sound made
 *     and the session's players numbered;
 *   3 SceneProcess_LoadResources: the field's resources loaded;
 *   4 SceneProcess_SpawnSetupEnd and 5 SceneProcess_RunSetup: the scene's setup
 *     (scene_setup.h);
 *   6 SceneProcess_Finish: the fog, the first background's priority, the frame rate (three
 *     VBlanks a frame) and the scene's music.
 * Its end (SceneProcess_End) undoes them and leaves the mode 2 (between scenes); each frame
 * it asks for the change of scene once main's entry record names one (SceneProcess_Update);
 * its drawing applies the fog and handles the pen on the field (SceneProcess_Draw). */
#ifndef CLEAN_MAIN_SCENE_PROCESS_H
#define CLEAN_MAIN_SCENE_PROCESS_H

#include "autoload_2/process.h"
#include "main/scene_exit.h"
#include "types.h"

/* What a scene is made of (data_021f6948 points to the running one). The low byte of
 * setup.unk_04 is 1 for the scenes whose field is loaded whole (SceneProcess_LoadResources). */
typedef struct SceneInfo {
    SceneExitScene base; /* 0x00: the setup and the exits */
    s32 overlays[2];     /* 0x10: two more overlays of the scene, -1 for none */
} SceneInfo;

/* The modes (data_020e54a8). */
enum SceneMode { SCENE_MODE_OUTDOORS = 0, SCENE_MODE_ROOM = 1, SCENE_MODE_NONE = 2 };

void SceneProcess_Slot12(void);
int SceneProcess_Draw(void *process);
int SceneProcess_Update(int unused);
int SceneProcess_End(void);
int SceneProcess_Create(Process *process);
int SceneProcess_Finish(void *process);
void SceneProcess_RunSetup(int unused, u64 start);
int SceneProcess_SpawnSetupEnd(void);
int SceneProcess_LoadResources(void);
int SceneProcess_SetUpPlayers(void);
int SceneProcess_Enter(void);
void SceneProcess_ReleaseOverlays(void);
void SceneProcess_LoadModeOverlays(void);
void SceneProcess_ReleaseInfoOverlays(void);
void SceneProcess_LoadInfoOverlays(SceneInfo *info);
void SceneProcess_ReleaseCommonOverlay(void);
void SceneProcess_LoadCommonOverlay(void);
Process *SceneProcess_New(void);

Process *SceneClass3_Destruct(Process *process);
Process *SceneClass3_Delete(Process *process);
void SceneClass3_Slot12(void);
int SceneClass3_Draw(void);
int SceneClass3_Update(void);
int SceneClass3_End(void);
int SceneClass3_Init(void);
Process *SceneClass3_New(void);

#endif
