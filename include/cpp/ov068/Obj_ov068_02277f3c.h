#ifndef CPP_OV068_OBJ_OV068_02277F3C_H
#define CPP_OV068_OBJ_OV068_02277F3C_H

#include "cpp/ov004/Obj_ov004_02254b28.h"

// Arrival-sequence object: primary vtable 0x02277f3c. The base's mode byte
// at 0x24c picks the update handler; func_ov068_02274f84 (vtable slot 0x60,
// func_ov004_0222c6cc in the base) changes it.
class Obj_ov068_02277f3c : public Obj_ov004_02254b28 {
  public:
    // update handlers
    void func_ov068_02274efc();
    void func_ov068_02274ee0();
    void func_ov068_02274f18();

    // entry checks
    int func_ov068_02274f08();
    int func_ov068_02274eec();
    int func_ov068_02274f84(unsigned int mode);
    // update: runs the mode handler, then fades the model
    int func_ov068_0227507c();
};

#endif
