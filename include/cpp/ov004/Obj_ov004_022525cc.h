#ifndef CPP_OV004_OBJ_OV004_022525CC_H
#define CPP_OV004_OBJ_OV004_022525CC_H

#include "cpp/ov004/Member_ov004_0220d0f4.h"
#include "cpp/ov004/RoomObject.h"

// vtable 0x022525cc: room object
struct Obj_ov004_022525cc : public RoomObject {
    virtual ~Obj_ov004_022525cc();

    // update entry: runs the state handler dispatch below, then returns 1
    int func_ov004_022199a8();

    // state handlers, dispatched through tables in func_ov004_02219884, func_ov004_02219900
    void func_ov004_02219884();
    int func_ov004_0221974c();

    int func_ov004_0221977c();
    int func_ov004_022197b0();

    int func_ov004_022197e0();
    void func_ov004_02219824();
    int func_ov004_0221984c();

    unsigned char unk_844;
    char pad_845[0x7];
    Member_ov004_0220d0f4 unk_84c;
};

#endif
