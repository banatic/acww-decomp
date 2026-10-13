#ifndef CPP_OV147_OBJ_OV147_0229AA28_H
#define CPP_OV147_OBJ_OV147_0229AA28_H

#include "cpp/ov002/Obj_ov002_0220bb24.h"
#include "cpp/ov147/Obj_ov147_0229ac1c.h"

// Scene of ov147 (vtable 0229aa28, constructor 0229a200, destructors 0229a1cc/0229a194).
// It derives from main's scene root directly, not from ov002's scene base. Its states
// live in a table of {enter, update} pointer-to-member pairs (data_ov147_0229ad4c).
class Obj_ov147_0229aa28 : public Obj_020da13c {
  public:
    virtual ~Obj_ov147_0229aa28();
    char pad_04[0x50 - 4];
    int unk_50;
    char pad_54[0xb0 - 0x54];
    Obj_ov147_0229ac1c unk_B0;

    void func_ov147_02299fc8(int index);
    int func_ov147_0229a090();
};

#endif
