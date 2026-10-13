#ifndef CPP_OV003_OBJ_OV003_02238C54_H
#define CPP_OV003_OBJ_OV003_02238C54_H

#include "cpp/main/Obj_020dd154.h"
#include "cpp/ov009/Obj_ov009_022658dc.h"

// Outdoor scene actor: primary vtable 0x02238c54. Overrides the mode setter
// (vtable slot 0x6c) with its own two entry checks.
class Obj_ov003_02238c54 : public Obj_ov009_022658dc {
  public:
    virtual ~Obj_ov003_02238c54();

    void func_ov003_0221cbc0();
    int func_ov003_0221cc10();
    int func_ov003_0221cb88();
    int func_ov003_0221ccb4(unsigned int mode);

    Obj_020dd154 unk_2b4;
};

#endif
