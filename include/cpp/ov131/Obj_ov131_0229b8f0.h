#ifndef CPP_OV131_OBJ_OV131_0229B8F0_H
#define CPP_OV131_OBJ_OV131_0229B8F0_H

#include "cpp/ov002/Obj_ov002_0220bb24.h"

// Scene of ov131 (vtable 0x0229b8f0).
class Obj_ov131_0229b8f0 : public Obj_ov002_0220bb24 {
  public:
    virtual ~Obj_ov131_0229b8f0();

    // states run by func_ov131_0229b644, indexed by subState
    void func_ov131_0229b338();
    void func_ov131_0229b304();
    void func_ov131_0229b274();
    void func_ov131_0229b24c();
    void func_ov131_0229b1f0();
    void func_ov131_0229b1c8();
    void func_ov131_0229b188();
    void func_ov131_0229b124();

    // dispatchers and helpers
    void func_ov131_0229b644();
    // update: runs the handlers between the two frame helpers
    int func_ov131_0229b628();
};

#endif
