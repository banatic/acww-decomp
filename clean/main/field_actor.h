/* The main program's part of the field actor's class (vtable 0x020d82b4, second vtable
 * 0x020d832c for its message receiver at 0xec; include/cpp/main/Obj_020d82b4.h): the
 * allocation and freeing of its objects, the vtable slots that only pass on to the real work,
 * and the deleting destructor. Overlay 3's part is in ov003/field_actor.h.
 *
 * Its objects come from the heap at data_021c9ab4, zeroed and aligned to 4. */
#ifndef CLEAN_MAIN_FIELD_ACTOR_H
#define CLEAN_MAIN_FIELD_ACTOR_H

#include "types.h"

struct FieldActor;

void FieldActor_Delete(void *actor);
void *FieldActor_New(int size);
void FieldActor_Teardown(struct FieldActor *actor);
int FieldActor_Vfunc24(struct FieldActor *actor);
int FieldActor_Update(struct FieldActor *actor);
void FieldActor_Setup(struct FieldActor *actor);
struct FieldActor *FieldActor_DestructDelete(struct FieldActor *actor);

#endif
