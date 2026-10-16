/* The turns of a talk between two speakers in a scene (class 0x020d8bd4,
 * include/cpp/main/Obj_020d8bd4.h): one of the scene's sub-machines, on its byte 0xac. The
 * scene keeps its two speakers (scene objects of class 0x020d8c64, obj_020d8c64.h) at 0x4c and
 * 0x50 (func_02015d78 gives them by number), the number of the one speaking at 0x55, and the
 * talk's state at 0x40 (word 4: 5 once a line is shown to its end; word 8: 1 to show the next;
 * word 0x14).
 *
 * State 0 begins (to state 1 when the scene's byte 0xa4 is set, else 2); state 1 aims the
 * camera at the next speaker; state 2 passes the turn to it, naming it as the speaker of the
 * next line (state 3). */
#ifndef CLEAN_MAIN_SCENE_TALK_H
#define CLEAN_MAIN_SCENE_TALK_H

#include "types.h"

int SceneTalk_Run(void *scene);
int SceneTalk_PassTurn(void *scene);
int SceneTalk_LookAtNext(void *scene);
int SceneTalk_Begin(void *scene);

#endif
