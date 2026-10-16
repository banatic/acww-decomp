/* The game's process class (vtable data_020da13c), from which the game's processes derive
 * (plain_process.h, actor.h and others): a Process (autoload_2/process.h) with its own
 * destructors and creation's end (vtable slot 2), and the main program's wrappers that spawn
 * processes. */
#ifndef CLEAN_MAIN_GAME_PROCESS_H
#define CLEAN_MAIN_GAME_PROCESS_H

#include "autoload_2/process.h"
#include "types.h"

Process *GameProcess_Destruct(Process *self);
void *GameProcess_DestructDelete(void *self);
int GameProcess_SpawnRoot(int class_id, int param, int unk_12);
int GameProcess_SpawnChild(int class_id, int parent, int param, int unk_12);
void GameProcess_AfterCreate(Process *self, int outcome);

#endif
