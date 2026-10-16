/* The scene class with vtable 0x020d9ff8 (include/cpp/main/Obj_020d9ff8.h): a scene base
 * (scene_base.h) that only replaces the destructors (its vtable slots 0x00 and 0x04). The
 * main program's and the overlays' scenes derive from it. */
#ifndef CLEAN_MAIN_OBJ_020D9FF8_H
#define CLEAN_MAIN_OBJ_020D9FF8_H

#include "scene_base.h"
#include "types.h"

void *Obj020d9ff8_DestructBody(void *scene);
void *Obj020d9ff8_DestructDelete(void *scene);
void *Obj020d9ff8_Destruct(void *scene);
void *Obj020d9ff8_Construct(void *scene);

#endif
