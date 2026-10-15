#ifndef CPP_OV116_OBJ_OV116_0229E8B8_H
#define CPP_OV116_OBJ_OV116_0229E8B8_H

#include "cpp/ov002/Obj_ov002_0220bb24.h"

// ov116 scene (vtable 0x0229e8b8)
class Obj_ov116_0229e8b8 : public Obj_ov002_0220bb24 {
  public:
    virtual ~Obj_ov116_0229e8b8();

    // per-frame slots: run the handler for `state` or `subState`
    virtual int func_ov116_0229e6b4();

    // runs the handler for `subState`
    void func_ov116_0229e5e8();

    // states (state)
    void func_ov116_0229e3e4();
    void func_ov116_0229e41c();
    void func_ov116_0229e454();
    void func_ov116_0229e47c();

    // sub-states (subState)
    void func_ov116_0229dfc0();
    void func_ov116_0229e010();
    void func_ov116_0229e074();
    void func_ov116_0229e0c0();
    int func_ov116_0229e0e8();
    void func_ov116_0229e140();
    void func_ov116_0229e168();
    void func_ov116_0229e1f0();
    void func_ov116_0229e228();
    // update: runs the handlers between the two frame helpers
    int func_ov116_0229e5bc();
};

#endif
