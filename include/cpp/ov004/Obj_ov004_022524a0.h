#ifndef CPP_OV004_OBJ_OV004_022524A0_H
#define CPP_OV004_OBJ_OV004_022524A0_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x022524a0: room object
struct Obj_ov004_022524a0 : public RoomObject {
    virtual ~Obj_ov004_022524a0();

    // state handlers, dispatched through tables in func_ov004_022141f0, func_ov004_0221425c
    void func_ov004_022141f0();
    void func_ov004_0221412c();
    int func_ov004_02214160();
    void func_ov004_02214198();
    int func_ov004_022141c0();

    unsigned char unk_844;
};

#endif
