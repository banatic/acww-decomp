#ifndef CPP_OV004_OBJ_OV004_02251564_H
#define CPP_OV004_OBJ_OV004_02251564_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x02251564: room object
struct Obj_ov004_02251564 : public RoomObject {
    virtual ~Obj_ov004_02251564();

    // state handlers, dispatched through tables in func_ov004_022130c4, func_ov004_02213130
    void func_ov004_022130c4();
    void func_ov004_02213008();
    int func_ov004_02213010();
    void func_ov004_02213074();
    int func_ov004_022130c0();

    unsigned char unk_844;
};

#endif
