/* The constructor and the destructors of the RMO family's base class (rmo_object.h, vtable
 * 0x02254b28): the scene object, its animated model, its archive's and its texture's holders
 * and its sound source at 0x250, built in that order and taken down in reverse.
 *
 * Vtable slots 0x40 and 0x44 hold RmoObjectBase_Destruct and RmoObjectBase_Delete; the classes
 * built on it end their own destructors with func_ov004_0222c7a0, a copy of the former. */
#ifndef CLEAN_OV004_RMO_OBJECT_BASE_H
#define CLEAN_OV004_RMO_OBJECT_BASE_H

#include "rmo_object.h"
#include "types.h"

RmoObject *RmoObjectBase_Delete(RmoObject *self);
RmoObject *RmoObjectBase_Destruct(RmoObject *self);
RmoObject *RmoObjectBase_Construct(RmoObject *self);

#endif
