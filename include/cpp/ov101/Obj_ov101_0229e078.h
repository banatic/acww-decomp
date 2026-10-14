#ifndef CPP_OV101_OBJ_OV101_0229E078_H
#define CPP_OV101_OBJ_OV101_0229E078_H

#include "cpp/ov002/Obj_ov002_0220bb24.h"

// ov101 scene (vtable 0x0229e078)
class Obj_ov101_0229e078 : public Obj_ov002_0220bb24 {
  public:
    virtual ~Obj_ov101_0229e078();

    // per-frame slots: run the handler for `state` or `subState`
    virtual int func_ov101_0229dd54();

    // runs the handler for `subState`
    void func_ov101_0229dbb0();

    // states (state)
    void func_ov101_0229d9ec();
    void func_ov101_0229da38();
    void func_ov101_0229da98();
    void func_ov101_0229dad4();
    void func_ov101_0229db60();

    // sub-states (subState)
    void func_ov101_0229cff0();
    void func_ov101_0229d054();
    void func_ov101_0229d088();
    void func_ov101_0229d0a8();
    void func_ov101_0229d0f8();
    void func_ov101_0229d134();
    void func_ov101_0229d168();
    void func_ov101_0229d1a8();
    void func_ov101_0229d1f0();
    void func_ov101_0229d240();
    void func_ov101_0229d26c();
    void func_ov101_0229d29c();
    void func_ov101_0229d2c4();
    void func_ov101_0229d2fc();
    void func_ov101_0229d34c();
    void func_ov101_0229d398();
    void func_ov101_0229d410();
    void func_ov101_0229d4b4();
    void func_ov101_0229d5a8();
    void func_ov101_0229d624();
    void func_ov101_0229d6bc();
    void func_ov101_0229d704();
    void func_ov101_0229d720();
    void func_ov101_0229d7c0();
    // update: runs the handlers between the two frame helpers
    int func_ov101_0229db94();
};

#endif
