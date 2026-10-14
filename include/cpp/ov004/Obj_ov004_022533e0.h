#ifndef CPP_OV004_OBJ_OV004_022533E0_H
#define CPP_OV004_OBJ_OV004_022533E0_H

#include "cpp/main/Base_0203f080.h"
#include "cpp/main/Base_02066994.h"
#include "cpp/main/Member_020b7f60.h"

// vtable 0x022533e0
struct Obj_ov004_022533e0 : public Base_0203f080, public Base_02066994 {
    virtual ~Obj_ov004_022533e0();
    // Base_02066994 slots; primary slots 0x60..0x68
    virtual void vfunc_02066994_10(); // func_ov004_0221b808
    virtual void vfunc_02066994_14(); // func_ov004_0221b6d8
    virtual void vfunc_02066994_18(); // func_ov004_0221b60c

    // state handlers, dispatched through tables in func_ov004_0221b4e4, func_ov004_0221b570
    void func_ov004_0221b4e4();
    void func_ov004_0221b294();
    int func_ov004_0221b2b8();
    void func_ov004_0221b354();
    int func_ov004_0221b384();
    void func_ov004_0221b388();
    int func_ov004_0221b3ac();
    void func_ov004_0221b4b0();
    int func_ov004_0221b4e0();
    // update: runs the state handlers, then draws the model unless hidden
    int func_ov004_0221bce0();

    char pad_130[0x4];
    int unk_134;
    Member_020b7f60 unk_138;
};

#endif
