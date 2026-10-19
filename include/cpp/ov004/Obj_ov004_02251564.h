#ifndef CPP_OV004_OBJ_OV004_02251564_H
#define CPP_OV004_OBJ_OV004_02251564_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x02251564: room object
struct Obj_ov004_02251564 : public RoomObject {
    virtual ~Obj_ov004_02251564();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_0c();            // func_ov004_022131b4
    virtual int vfunc_70(int a, int b); // func_ov004_02213130
    virtual void vfunc_7c();            // func_ov004_022131c8
    virtual void vfunc_80();            // Obj_ov004_02251564::func_ov004_022131b8

    // update entry: runs the state handler dispatch below, then returns 1
    int func_ov004_022131b8();

    // state handlers, dispatched through tables in func_ov004_022130c4, func_ov004_02213130
    void func_ov004_022130c4();
    void func_ov004_02213008();
    int func_ov004_02213010();
    void func_ov004_02213074();
    int func_ov004_022130c0();

    unsigned char unk_844;
};

#endif
