#ifndef CPP_OV091_OBJ_OV091_02299530_H
#define CPP_OV091_OBJ_OV091_02299530_H

#include "cpp/ov002/Obj_ov002_0220bb24.h"

// ov091 scene (vtable 0x02299530)
class Obj_ov091_02299530 : public Obj_ov002_0220bb24 {
  public:
    virtual ~Obj_ov091_02299530();

    // per-frame slots: run the handler for `state` or `subState`
    virtual int func_ov091_0229936c();
    virtual int func_ov091_022992f8();

    // states (state)
    void func_ov091_022990b0();
    void func_ov091_022990f4();
    void func_ov091_0229914c();
    void func_ov091_022991b0();
    void func_ov091_022991e8();
    void func_ov091_02299244();

    // sub-states (subState)
    void func_ov091_02298fb4();
    void func_ov091_02299004();
};

#endif
