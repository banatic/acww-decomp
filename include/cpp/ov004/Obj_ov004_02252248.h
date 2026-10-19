#ifndef CPP_OV004_OBJ_OV004_02252248_H
#define CPP_OV004_OBJ_OV004_02252248_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x02252248: room object
struct Obj_ov004_02252248 : public RoomObject {
    virtual ~Obj_ov004_02252248();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_0c();            // func_ov004_02219654
    virtual int vfunc_70(int a, int b); // func_ov004_022195a0
    virtual void vfunc_74();            // func_ov004_02219640
    virtual void vfunc_7c();            // func_ov004_02219668
    virtual void vfunc_80();            // Obj_ov004_02252248::func_ov004_02219658

    // update entry: runs the state handler dispatch below, then returns 1
    int func_ov004_02219658();

    // state handlers, dispatched through tables in func_ov004_02219514, func_ov004_022195a0
    void func_ov004_02219514();
    void func_ov004_02219368();
    int func_ov004_02219398();
    void func_ov004_022193cc();
    int func_ov004_0221940c();
    void func_ov004_02219438();
    int func_ov004_02219468();
    void func_ov004_022194a0();
    int func_ov004_022194e0();

    unsigned char unk_844;
};

#endif
