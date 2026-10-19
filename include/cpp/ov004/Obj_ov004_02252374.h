#ifndef CPP_OV004_OBJ_OV004_02252374_H
#define CPP_OV004_OBJ_OV004_02252374_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x02252374: room object
struct Obj_ov004_02252374 : public RoomObject {
    virtual ~Obj_ov004_02252374();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_0c();            // func_ov004_02213fa4
    virtual int vfunc_70(int a, int b); // func_ov004_02213ee0
    virtual void vfunc_74();            // func_ov004_02213f64
    virtual void vfunc_7c();            // func_ov004_02213fb8
    virtual void vfunc_80();            // Obj_ov004_02252374::func_ov004_02213fa8
    virtual void vfunc_8c();            // func_ov004_02213fa0

    // update entry: runs the state handler dispatch below, then returns 1
    int func_ov004_02213fa8();

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
