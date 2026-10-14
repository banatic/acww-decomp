#ifndef CPP_OV004_OBJ_OV004_02254C58_H
#define CPP_OV004_OBJ_OV004_02254C58_H

#include "cpp/main/Base_02066994.h"
#include "cpp/main/Member_020324c4.h"
#include "cpp/ov004/Obj_ov004_02254b28.h"

// vtable 0x02254c58: room object of the 0x290-offset family
struct Obj_ov004_02254c58 : public Obj_ov004_02254b28, public Base_02066994 {
    virtual ~Obj_ov004_02254c58();

    // state handlers, dispatched through tables in func_ov004_0222cafc, func_ov004_0222cb88
    void func_ov004_0222cafc();
    void func_ov004_0222c934();
    int func_ov004_0222c964();
    void func_ov004_0222c9b8();
    int func_ov004_0222c9fc();
    void func_ov004_0222ca34();
    int func_ov004_0222ca78();
    void func_ov004_0222cac0();
    int func_ov004_0222cac4();
    // update: runs the state handlers
    int func_ov004_0222cc74();

    char pad_2d4[0x4];
    Member_020324c4 unk_2d8;
};

#endif
