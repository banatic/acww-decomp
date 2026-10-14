#ifndef CPP_OV003_OBJ_OV003_02238434_H
#define CPP_OV003_OBJ_OV003_02238434_H

#include "cpp/ov009/Obj_ov009_022658dc.h"

// Outdoor scene actor: primary vtable 0x02238434. Its own state index at 0x2b4 is
// moved by func_ov003_0221b8b8 once the matching entry check passes.
class Obj_ov003_02238434 : public Obj_ov009_022658dc {
  public:
    virtual ~Obj_ov003_02238434();

    // entry checks
    int func_ov003_0221b838();
    int func_ov003_0221b818();
    int func_ov003_0221b808();
    int func_ov003_0221b8b8(int state);

    // state changes; 0x4c and 0x70 are primary vtable slots
    void func_ov003_0221b80c();
    void func_ov003_0221b944(int event);
    int func_ov003_0221b9d0();

    int state_2b4;
};

#endif
