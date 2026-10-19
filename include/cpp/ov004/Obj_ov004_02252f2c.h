#ifndef CPP_OV004_OBJ_OV004_02252F2C_H
#define CPP_OV004_OBJ_OV004_02252F2C_H

#include "cpp/ov004/Member_ov004_0220d0f4.h"
#include "cpp/ov004/RoomObject.h"

// vtable 0x02252f2c: room object
struct Obj_ov004_02252f2c : public RoomObject {
    virtual ~Obj_ov004_02252f2c();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_0c();            // func_ov004_0221a2d8
    virtual int vfunc_70(int a, int b); // func_ov004_0221a240
    virtual void vfunc_74();            // func_ov004_0221a2c4
    virtual void vfunc_7c();            // func_ov004_0221a420
    virtual void vfunc_80();            // Obj_ov004_02252f2c::func_ov004_0221a2dc

    // state handlers, dispatched through tables in func_ov004_0221a1d4, func_ov004_0221a240
    void func_ov004_0221a1d4();
    void func_ov004_0221a150();
    int func_ov004_0221a158();
    void func_ov004_0221a17c();
    int func_ov004_0221a1b0();
    // update: runs the state handlers and reacts to the held item
    int func_ov004_0221a2dc();

    unsigned char unk_844;
    char pad_845[0x3];
    Member_ov004_0220d0f4 unk_848;
};

#endif
