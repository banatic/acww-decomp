/* The scene object class with vtable 0x020d8c64 (include/cpp/main/Obj_020d8c64.h): a
 * Base_0203f080 with members that have destructors between 0xec and 0x640, among them a sound
 * emitter of class 0x020d8414 at 0x514 (sound_emitter.h). Many overlays derive their scene
 * objects from it (vtable 0x020da088 in the main program). */
#ifndef CLEAN_MAIN_OBJ_020D8C64_H
#define CLEAN_MAIN_OBJ_020D8C64_H

#include "types.h"

void *Obj020d8c64_Destruct(void *object);
void *Obj020d8c64_DestructDelete(void *object);

/* The motion number kept at 0x63e (obj_020d8c64.c): a number 1 to 59 the object's motion (its
 * member at 0x564) shows in its byte 0xa9, taken once while the object talks alone. */
int Obj020d8c64_NoMotionNumber(void *object);
int Obj020d8c64_TakeNewMotionNumber(void *object);
s16 Obj020d8c64_LastMotionNumber(s16 *object);
void Obj020d8c64_SetLastMotionNumber(void *object, u16 number);
void Obj020d8c64_ClearLastMotionNumber(void *object);

#endif
