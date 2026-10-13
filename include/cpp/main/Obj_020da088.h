#ifndef CPP_MAIN_OBJ_020DA088_H
#define CPP_MAIN_OBJ_020DA088_H

#include "cpp/main/Obj_020d8c64.h"

// Scene object (vtable 0x020da088, destructor func_0202ee5c): overrides Obj_020d8c64
// slots (0x00..0x10, the destructor pair) without adding any.
class Obj_020da088 : public Obj_020d8c64 {
  public:
    virtual ~Obj_020da088();
    virtual void vfunc_0c();
    virtual void vfunc_10();
};

#endif
