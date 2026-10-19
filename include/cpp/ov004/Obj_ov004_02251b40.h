#ifndef CPP_OV004_OBJ_OV004_02251B40_H
#define CPP_OV004_OBJ_OV004_02251B40_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x02251b40: room object
struct Obj_ov004_02251b40 : public RoomObject {
    virtual ~Obj_ov004_02251b40();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_0c(); // func_ov004_02213650
    virtual void vfunc_4c(); // func_ov004_0221362c
    virtual void vfunc_7c(); // func_ov004_02213664
    virtual void vfunc_80(); // Obj_ov004_02251b40::func_ov004_02213654

    // update entry: runs the state handler dispatch below, then returns 1
    int func_ov004_02213654();

    // state handlers, dispatched through tables in func_ov004_02213504, func_ov004_02213590
    void func_ov004_02213504();
    void func_ov004_022133f8();
    int func_ov004_02213428();
    void func_ov004_0221342c();
    int func_ov004_02213450();
    void func_ov004_022134cc();
    int func_ov004_022134d8();
    int func_ov004_022134dc();

    int func_ov004_02213500();

    int unk_844;
};

#endif
