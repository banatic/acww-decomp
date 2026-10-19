#ifndef CPP_OV004_OBJ_OV004_022518E8_H
#define CPP_OV004_OBJ_OV004_022518E8_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x022518e8: room object
struct Obj_ov004_022518e8 : public RoomObject {
    virtual ~Obj_ov004_022518e8();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_0c();            // func_ov004_02219270
    virtual int vfunc_70(int a, int b); // func_ov004_022191bc
    virtual void vfunc_74();            // func_ov004_0221925c
    virtual void vfunc_7c();            // func_ov004_02219284
    virtual void vfunc_80();            // Obj_ov004_022518e8::func_ov004_02219274

    // update entry: runs the state handler dispatch below, then returns 1
    int func_ov004_02219274();

    // state handlers, dispatched through tables in func_ov004_02219130, func_ov004_022191bc
    void func_ov004_02219130();
    void func_ov004_02218f28();
    int func_ov004_02218f6c();
    void func_ov004_02218fb4();
    int func_ov004_02218ff8();
    void func_ov004_02219034();
    int func_ov004_0221906c();
    void func_ov004_022190b4();
    int func_ov004_022190f4();

    char pad_844[0x1];
    unsigned char unk_845;
};

#endif
