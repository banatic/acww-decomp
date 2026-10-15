#ifndef CPP_OV126_OBJ_OV126_022A20C8_H
#define CPP_OV126_OBJ_OV126_022A20C8_H

#include "cpp/ov002/Obj_ov002_0220bb24.h"

// ov126 scene (vtable 0x022a20c8)
class Obj_ov126_022a20c8 : public Obj_ov002_0220bb24 {
  public:
    virtual ~Obj_ov126_022a20c8();

    // per-frame slots: run the handler for `state` or `subState`
    virtual int func_ov126_022a1c8c();

    // runs the handler for `subState`
    void func_ov126_022a1b4c();

    // states (state)
    void func_ov126_022a16d8();
    void func_ov126_022a16fc();
    void func_ov126_022a172c();
    void func_ov126_022a1748();
    void func_ov126_022a176c();
    void func_ov126_022a17bc();
    void func_ov126_022a17d8();
    void func_ov126_022a185c();
    void func_ov126_022a18ac();
    void func_ov126_022a19a8();
    void func_ov126_022a19d8();
    void func_ov126_022a1a38();

    // sub-states (subState)
    void func_ov126_022a0c34();
    void func_ov126_022a0c64();
    void func_ov126_022a0cd0();
    void func_ov126_022a0d00();
    void func_ov126_022a0d30();
    void func_ov126_022a0d8c();
    void func_ov126_022a0db4();
    void func_ov126_022a0e10();
    void func_ov126_022a0e98();
    void func_ov126_022a0ec4();
    void func_ov126_022a0f40();
    void func_ov126_022a1020();
    void func_ov126_022a1038();
    void func_ov126_022a1108();
    void func_ov126_022a117c();
    void func_ov126_022a11d8();
    void func_ov126_022a1228();
    // update: runs the handlers between the two frame helpers
    int func_ov126_022a1a6c();
};

#endif
