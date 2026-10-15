#ifndef CPP_OV090_OBJ_OV090_02299820_H
#define CPP_OV090_OBJ_OV090_02299820_H

#include "cpp/ov002/Obj_ov002_0220bb24.h"

// ov090 scene (vtable 0x02299820)
class Obj_ov090_02299820 : public Obj_ov002_0220bb24 {
  public:
    virtual ~Obj_ov090_02299820();

    // per-frame slot: runs the handler for `subState`
    virtual int func_ov090_02299470();

    // sub-states (subState)
    int func_ov090_02299258();

    void func_ov090_0229926c();
    void func_ov090_02299348();

    unsigned char unk_94;
    unsigned char unk_95;
    unsigned char pad_96;
    unsigned char unk_97;
    unsigned char pad_98[0x1164 - 0x98];
    unsigned char buf1164[4];
};

#endif
