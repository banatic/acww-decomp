#ifndef CPP_OV003_OBJ_OV003_0223948C_H
#define CPP_OV003_OBJ_OV003_0223948C_H

#include "cpp/main/Member_020b7f60.h"
#include "cpp/main/Obj_020dd154.h"
#include "cpp/ov009/Obj_ov009_022658dc.h"

// Outdoor scene actor: primary vtable 0x0223948c. Its own state index at 0x2b4 is
// moved by func_ov003_0221e580 once the matching entry check passes.
class Obj_ov003_0223948c : public Obj_ov009_022658dc {
  public:
    virtual ~Obj_ov003_0223948c();

    // entry checks
    int func_ov003_0221e4e4();
    int func_ov003_0221e4a4();
    int func_ov003_0221e46c();
    int func_ov003_0221e45c();
    int func_ov003_0221e424();
    int func_ov003_0221e580(int state);

    int state_2b4;
    Obj_020dd154 unk_2b8;
    Member_020b7f60 unk_2d8;
};

#endif
