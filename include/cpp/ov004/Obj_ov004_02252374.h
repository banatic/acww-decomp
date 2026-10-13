#ifndef CPP_OV004_OBJ_OV004_02252374_H
#define CPP_OV004_OBJ_OV004_02252374_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x02252374: room object
struct Obj_ov004_02252374 : public RoomObject {
    virtual ~Obj_ov004_02252374();

    // state handlers, dispatched through tables in func_ov004_02213e74, func_ov004_02213ee0
    void func_ov004_02213e74();
    void func_ov004_02213d70();
    int func_ov004_02213d84();
    void func_ov004_02213e10();
    int func_ov004_02213e24();

    char pad_844[0x30];
    unsigned char unk_874;
};

#endif
