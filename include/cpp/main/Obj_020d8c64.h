#ifndef CPP_MAIN_OBJ_020D8C64_H
#define CPP_MAIN_OBJ_020D8C64_H

#include "cpp/main/Base_0203f080.h"

// Scene object (vtable 0x020d8c64, destructor func_0202ee5c) that the vtable
// 0x020da088 class derives from. It overrides most Base_0203f080 slots and adds
// three (0x60..0x68). Members with destructors sit between 0xec and 0x640.
class Obj_020d8c64 : public Base_0203f080 {
  public:
    virtual ~Obj_020d8c64();
    virtual int vfunc_60();
    virtual int vfunc_64();
    virtual int vfunc_68();
};

#endif
