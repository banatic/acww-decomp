#ifndef CPP_OV004_OBJ_OV004_0225130C_H
#define CPP_OV004_OBJ_OV004_0225130C_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x0225130c: room object
struct Obj_ov004_0225130c : public RoomObject {
    virtual ~Obj_ov004_0225130c();

    // state handlers, dispatched through tables in func_ov004_02212d78, func_ov004_02212e10
    void func_ov004_02212d78();
    void func_ov004_02212a14();
    int func_ov004_02212a84();
    void func_ov004_02212ab8();
    int func_ov004_02212b70();
    void func_ov004_02212bb0();
    int func_ov004_02212c64();
    void func_ov004_02212c90();
    int func_ov004_02212ce4();
    void func_ov004_02212d1c();
    int func_ov004_02212d44();

    char pad_844[0x3];
    unsigned char unk_847;
};

#endif
