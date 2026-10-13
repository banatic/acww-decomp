#ifndef CPP_OV141_OBJ_OV141_0229AF48_H
#define CPP_OV141_OBJ_OV141_0229AF48_H

#include "cpp/ov002/Obj_ov002_0220bb24.h"

// ov141 scene (vtable 0x0229af48)
class Obj_ov141_0229af48 : public Obj_ov002_0220bb24 {
  public:
    virtual ~Obj_ov141_0229af48();

    // per-frame slots: run the handler for `state` or `subState`
    virtual int func_ov141_0229ac60();

    // runs the handler for `subState`
    void func_ov141_0229abc0();

    // states (state)
    void func_ov141_0229aa28();
    void func_ov141_0229aa54();
    void func_ov141_0229aa94();
    void func_ov141_0229aac4();
    void func_ov141_0229ab04();

    // sub-states (subState)
    void func_ov141_0229a5b4();
    void func_ov141_0229a5e0();
    void func_ov141_0229a634();
    void func_ov141_0229a6b4();
    void func_ov141_0229a6e4();
    void func_ov141_0229a774();
};

#endif
