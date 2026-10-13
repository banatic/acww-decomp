#ifndef CPP_OV138_OBJ_OV138_0229D4E0_H
#define CPP_OV138_OBJ_OV138_0229D4E0_H

#include "cpp/ov002/Obj_ov002_0220bb24.h"

// Scene of ov138 (vtable 0x0229d4e0).
class Obj_ov138_0229d4e0 : public Obj_ov002_0220bb24 {
  public:
    virtual ~Obj_ov138_0229d4e0();

    // per-frame slot: runs the handler for `state`
    virtual int func_ov138_0229d27c();

    // states (state)
    void func_ov138_0229d0dc();
    void func_ov138_0229d0b4();
    void func_ov138_0229d07c();
    void func_ov138_0229d04c();

    // states run by func_ov138_0229d16c, indexed by subState
    void func_ov138_0229ce68();
    void func_ov138_0229cdd0();
    void func_ov138_0229cd94();
    void func_ov138_0229cd58();
    void func_ov138_0229ccdc();
    void func_ov138_0229cc44();
    void func_ov138_0229cbec();
    void func_ov138_0229cba4();
    void func_ov138_0229cb7c();
    void func_ov138_0229caf8();
    void func_ov138_0229cad4();
    void func_ov138_0229ca70();
    void func_ov138_0229ca50();
    void func_ov138_0229ca14();

    // dispatchers and helpers
    void func_ov138_0229d16c();
};

#endif
