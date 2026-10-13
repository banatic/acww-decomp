#ifndef CPP_OV004_OBJ_OV004_02252F2C_H
#define CPP_OV004_OBJ_OV004_02252F2C_H

#include "cpp/ov004/Member_ov004_0220d0f4.h"
#include "cpp/ov004/RoomObject.h"

// vtable 0x02252f2c: room object
struct Obj_ov004_02252f2c : public RoomObject {
    virtual ~Obj_ov004_02252f2c();

    // state handlers, dispatched through tables in func_ov004_0221a1d4, func_ov004_0221a240
    void func_ov004_0221a1d4();
    void func_ov004_0221a150();
    int func_ov004_0221a158();
    void func_ov004_0221a17c();
    int func_ov004_0221a1b0();

    unsigned char unk_844;
    char pad_845[0x3];
    Member_ov004_0220d0f4 unk_848;
};

#endif
