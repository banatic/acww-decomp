#ifndef CPP_OV004_OBJ_OV004_022524A0_H
#define CPP_OV004_OBJ_OV004_022524A0_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x022524a0: room object
struct Obj_ov004_022524a0 : public RoomObject {
    virtual ~Obj_ov004_022524a0();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_0c();            // func_ov004_0221438c
    virtual void vfunc_6c();            // func_ov004_022142e0
    virtual int vfunc_70(int a, int b); // func_ov004_0221425c
    virtual void vfunc_7c();            // func_ov004_022143b8
    virtual void vfunc_80();            // Obj_ov004_022524a0::func_ov004_022143a8
    virtual void vfunc_90();            // func_ov004_02214370

    // update entry: runs the state handler dispatch below, then returns 1
    int func_ov004_022143a8();

    // state handlers, dispatched through tables in func_ov004_022141f0, func_ov004_0221425c
    void func_ov004_022141f0();
    int func_ov004_0221412c();

    int func_ov004_02214160();
    void func_ov004_02214198();
    int func_ov004_022141c0();

    unsigned char unk_844;
};

#endif
