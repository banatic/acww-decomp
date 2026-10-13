#ifndef CPP_OV004_OBJ_OV004_02252E00_H
#define CPP_OV004_OBJ_OV004_02252E00_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x02252e00: room object
struct Obj_ov004_02252e00 : public RoomObject {
    virtual ~Obj_ov004_02252e00();

    // state handlers, dispatched through tables in func_ov004_02219f58, func_ov004_02219fc4
    void func_ov004_02219f58();
    void func_ov004_02219e54();
    int func_ov004_02219ed8();
    void func_ov004_02219f00();
    int func_ov004_02219f28();

    unsigned char unk_844;
};

#endif
