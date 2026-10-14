#ifndef CPP_OV132_OBJ_OV132_0229B990_H
#define CPP_OV132_OBJ_OV132_0229B990_H

#include "cpp/ov002/Obj_ov002_0220bb24.h"

// Scene of ov132 (vtable 0229b990, constructor 0229b888, destructors 0229acc0/0229ad0c).
class Obj_ov132_0229b990 : public Obj_ov002_0220bb24 {
  public:
    virtual ~Obj_ov132_0229b990();

    // states run by func_ov132_0229b6c0, indexed by subState
    void func_ov132_0229b340();
    void func_ov132_0229b2a4();
    void func_ov132_0229b27c();
    void func_ov132_0229b23c();
    void func_ov132_0229b214();
    void func_ov132_0229b1b0();
    void func_ov132_0229b184();
    void func_ov132_0229b158();

    // states run by func_ov132_0229b77c, indexed by state
    void func_ov132_0229b630();
    void func_ov132_0229b608();
    void func_ov132_0229b5c8();
    void func_ov132_0229b598();

    void func_ov132_0229b6c0();
    int func_ov132_0229b77c();
    // update: runs the handlers between the two frame helpers
    int func_ov132_0229b6a4();
};

#endif
