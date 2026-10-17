/* The RMO family's base class (rmo_object.h, rmo_object_base.h; vtable 0x02254b28): the loading
 * and releasing of its body's archive and textures (rmo_model.h), its shared value (main's
 * room_object_state.h, by the number in its byte 0xea; 0xff for none), the vtable slots it
 * defines and the copy of its destructor the derived classes end theirs with:
 *   0x04  asked before its creation: the scene object's set-up, then no id and its sound
 *         stopped;
 *   0x10  whether it can be deleted: the scene object's answer; yes, the sound's slot 0x10;
 *   0x1c  asked before it runs: the scene object's answer; yes and with a shared value whose
 *         value differs from the state it shows (its byte 0x24c), it is told to show it (slot
 *         0x60);
 *   0x20  its run: its sound follows the point of slot 0x64, then the actor's run;
 *   0x60  told a state to show: the base class shows nothing and answers 1;
 *   0x64  the point its sound is at: its position. */
#ifndef CLEAN_OV004_RMO_OBJECT_SLOTS_H
#define CLEAN_OV004_RMO_OBJECT_SLOTS_H

#include "autoload_2/vector.h"
#include "ov004/rmo_object.h"
#include "types.h"

int RmoObjectSlots_SetSharedValue(RmoObject *object, unsigned int value);
int RmoObjectSlots_SharedValue(RmoObject *object);
void RmoObjectSlots_SetValueNumber(RmoObject *object, u8 number);
void RmoObjectSlots_ReleaseBody(RmoObject *object);
int RmoObjectSlots_LoadNamed(RmoObject *object, const char *name);
int RmoObjectSlots_Load(RmoObject *object, const char *archive, const char *texture);

int RmoObjectSlots_ShowState(RmoObject *object, unsigned int state);
void RmoObjectSlots_SoundPoint(RmoObject *object, Vec3 *point);
int RmoObjectSlots_CanDelete(RmoObject *object);
void RmoObjectSlots_Run(RmoObject *object, int status);
int RmoObjectSlots_CanRun(RmoObject *object);
int RmoObjectSlots_CanCreate(RmoObject *object);
RmoObject *RmoObjectSlots_Destruct(RmoObject *object);

#endif
