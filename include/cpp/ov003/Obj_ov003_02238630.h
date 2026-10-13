#ifndef CPP_OV003_OBJ_OV003_02238630_H
#define CPP_OV003_OBJ_OV003_02238630_H

#include "cpp/ov009/Obj_ov009_022658dc.h"

// Outdoor scene actor: primary vtable 0x02238630. Its own state index at 0x2b4 is
// moved by func_ov003_0221bfa8 once the matching entry check passes.
class Obj_ov003_02238630 : public Obj_ov009_022658dc {
  public:
    virtual ~Obj_ov003_02238630();
    // Base_02066994 slots; 0x10, 0x18 and 0x6c are also appended after that vtable
    virtual void vfunc_02066994_10(); // func_ov003_0221c0dc
    virtual void vfunc_02066994_14(); // func_ov003_0221c0a0
    virtual void vfunc_02066994_18(); // func_ov003_0221c09c
    virtual void vfunc_02066994_6c(); // func_ov003_0221c098

    // entry checks
    int func_ov003_0221bec4();
    int func_ov003_0221be7c();
    int func_ov003_0221bd90();
    int func_ov003_0221bd68();
    int func_ov003_0221bd34();
    int func_ov003_0221bcf8();
    int func_ov003_0221bc74();
    int func_ov003_0221bc3c();
    int func_ov003_0221bc00();
    int func_ov003_0221bb9c();
    int func_ov003_0221bfa8(int state);

    int state_2b4;
};

#endif
