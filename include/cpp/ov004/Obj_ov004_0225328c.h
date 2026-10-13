#ifndef CPP_OV004_OBJ_OV004_0225328C_H
#define CPP_OV004_OBJ_OV004_0225328C_H

#include "cpp/main/Base_0203f080.h"
#include "cpp/main/Base_02066994.h"
#include "cpp/main/Member_020b7f60.h"

// vtable 0x0225328c: object with the main-module bases
struct Obj_ov004_0225328c : public Base_0203f080, public Base_02066994 {
    virtual ~Obj_ov004_0225328c();

    // state handlers, dispatched through tables in func_ov004_0221ae00, func_ov004_0221ae7c
    void func_ov004_0221ae00();
    void func_ov004_0221ad58();
    int func_ov004_0221ad88();
    void func_ov004_0221ad8c();
    int func_ov004_0221adb0();
    void func_ov004_0221adf8();
    int func_ov004_0221adfc();

    char pad_130[0x4];
    int unk_134;
    Member_020b7f60 unk_138;
};

#endif
