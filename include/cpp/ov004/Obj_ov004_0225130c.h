#ifndef CPP_OV004_OBJ_OV004_0225130C_H
#define CPP_OV004_OBJ_OV004_0225130C_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x0225130c: room object
struct Obj_ov004_0225130c : public RoomObject {
    virtual ~Obj_ov004_0225130c();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_0c();            // func_ov004_02212ed0
    virtual int vfunc_70(int a, int b); // func_ov004_02212e10
    virtual void vfunc_74();            // func_ov004_02212ebc
    virtual void vfunc_7c();            // func_ov004_02212f1c
    virtual void vfunc_80();            // Obj_ov004_0225130c::func_ov004_02212f0c
    virtual void vfunc_84();            // func_ov004_02212ed4

    // update entry: runs the state handler dispatch below, then returns 1
    int func_ov004_02212f0c();

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
