/* The game's process class (game_process.h). */
#include "game_process.h"

#include "autoload_2/heap.h"
#include "clean.h"

/* The class's vtable. */
extern const u32 data_020da13c[];

/* func_0202f0f4 (slot 16): the destructor: the class's vtable, then the base's
 * (Process_Destruct). Returns the process. */
Process *GameProcess_Destruct(Process *self)
{
    self->vtable = data_020da13c;
    Process_Destruct(self);
    return self;
}
CLEAN_AS(func_0202f0f4, GameProcess_Destruct)

/* func_0202f10c (slot 17): destructed, then freed to the auxiliary heap. */
void *GameProcess_DestructDelete(void *self)
{
    ((Process *) self)->vtable = data_020da13c;
    Process_Destruct(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_0202f10c, GameProcess_DestructDelete)

/* func_0202f12c: a root process of class `class_id` spawned (Process_SpawnRoot). */
int GameProcess_SpawnRoot(int class_id, int param, int unk_12)
{
    return (int) (intptr_t) Process_SpawnRoot(class_id, param, unk_12);
}
CLEAN_AS(func_0202f12c, GameProcess_SpawnRoot)

/* func_0202f134: a process of class `class_id` spawned under `parent` (Process_SpawnChild). */
int GameProcess_SpawnChild(int class_id, int parent, int param, int unk_12)
{
    return (int) (intptr_t) Process_SpawnChild(class_id, (Process *) (intptr_t) parent, (u32) param, (u8) unk_12);
}
CLEAN_AS(func_0202f134, GameProcess_SpawnChild)

/* func_0202f144 (slot 2): a creation that ends with OUTCOME_PENDING asks for the process's
 * deletion (Process_RequestDelete); then the base's end of creation (Process_AfterCreate). */
void GameProcess_AfterCreate(Process *self, int outcome)
{
    if (outcome == OUTCOME_PENDING) {
        Process_RequestDelete(self);
    }
    Process_AfterCreate(self, outcome);
}
CLEAN_AS(func_0202f144, GameProcess_AfterCreate)
