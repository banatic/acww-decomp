/* The resident process: a process (the C++ class with vtable data_020e360c, derived from
 * data_020da13c's; 0x50 bytes, made by func_0209db24) that holds what the game keeps loaded
 * across scenes. Created, it notes itself in data_021dc740 and loads the building shapes, the
 * acre kinds, the furniture info, the design archive, the acre map's template set, town and
 * rooms, and the session's heap; deleted, it frees them. Each frame it starts the scene that
 * was asked for (func_020a536c spawns the class in data_020e3c80 under it).
 *
 * At boot (ResidentProcess_SpawnAll) scene 1 is asked for and the root process (class 0) is
 * spawned with seven children of fixed classes. */
#ifndef CLEAN_MAIN_RESIDENT_PROCESS_H
#define CLEAN_MAIN_RESIDENT_PROCESS_H

#include "autoload_2/process.h"
#include "types.h"

#define RESIDENT_PROCESS_CHILDREN 7

Process *ResidentProcess_Destruct(Process *self);
Process *ResidentProcess_DestructFree(Process *self);
int ResidentProcess_Draw(void);
int ResidentProcess_Execute(void);
int ResidentProcess_Delete(void);
int ResidentProcess_Create(Process *self);
void ResidentProcess_SpawnAll(void);
Process *ResidentProcess_New(void);

#endif
