#ifndef CPP_OV146_OBJ_OV146_0229B680_H
#define CPP_OV146_OBJ_OV146_0229B680_H

#include "cpp/ov002/Obj_ov002_0220bb24.h"

// Scene of ov146 (vtable 0229b680, constructor 0229b364, destructors 022995a0/022995f4).
class Obj_ov146_0229b680 : public Obj_ov002_0220bb24 {
  public:
    virtual ~Obj_ov146_0229b680();

    // states run by func_ov146_0229af2c, indexed by subState
    void func_ov146_0229a9b8();
    void func_ov146_0229a984();
    void func_ov146_0229a950();
    void func_ov146_0229a8ec();
    void func_ov146_0229a89c();
    void func_ov146_0229a858();
    void func_ov146_0229a82c();
    void func_ov146_0229a7f4();
    void func_ov146_0229a7a4();
    void func_ov146_0229a778();

    // states run by func_ov146_0229b004, indexed by state
    void func_ov146_0229ae90();
    void func_ov146_0229ae60();
    void func_ov146_0229ae28();
    void func_ov146_0229adf8();

    void func_ov146_0229af2c();
    int func_ov146_0229b004();
    // update: runs the handlers between the two frame helpers
    int func_ov146_0229af10();
};

#endif
