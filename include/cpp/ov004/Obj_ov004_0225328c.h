#ifndef CPP_OV004_OBJ_OV004_0225328C_H
#define CPP_OV004_OBJ_OV004_0225328C_H

#include "cpp/main/Base_0203f080.h"
#include "cpp/main/Base_02066994.h"
#include "cpp/main/Member_020b7f60.h"

// vtable 0x0225328c: object with the main-module bases
struct Obj_ov004_0225328c : public Base_0203f080, public Base_02066994 {
    virtual ~Obj_ov004_0225328c();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_00(); // func_ov004_0221b060
    virtual void vfunc_0c(); // func_ov004_0221b00c
    virtual void vfunc_18(); // Obj_ov004_0225328c::func_ov004_0221b020
    virtual void vfunc_24(); // func_ov004_0221b01c
    virtual void vfunc_48(); // func_ov004_0221af2c
    virtual void vfunc_4c(); // func_ov004_0221af08

    // state handlers, dispatched through tables in func_ov004_0221ae00, func_ov004_0221ae7c
    void func_ov004_0221ae00();
    void func_ov004_0221ad58();
    int func_ov004_0221ad88();
    void func_ov004_0221ad8c();
    int func_ov004_0221adb0();
    void func_ov004_0221adf8();
    int func_ov004_0221adfc();
    // update: runs the state handlers, then draws the model
    int func_ov004_0221b020();

    char pad_130[0x4];
    int unk_134;
    Member_020b7f60 unk_138;
};

#endif
