#ifndef CPP_OV004_OBJ_OV004_022510B4_H
#define CPP_OV004_OBJ_OV004_022510B4_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x022510b4: room object
struct Obj_ov004_022510b4 : public RoomObject {
    virtual ~Obj_ov004_022510b4();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_0c();            // func_ov004_02218e28
    virtual int vfunc_70(int a, int b); // func_ov004_02218d74
    virtual void vfunc_74();            // func_ov004_02218e14
    virtual void vfunc_7c();            // func_ov004_02218e3c
    virtual void vfunc_80();            // Obj_ov004_022510b4::func_ov004_02218e2c

    // update entry: runs the state handler dispatch below, then returns 1
    int func_ov004_02218e2c();

    // state handlers, dispatched through tables in func_ov004_02218ce8, func_ov004_02218d74
    void func_ov004_02218ce8();
    void func_ov004_02218b2c();
    int func_ov004_02218b5c();
    void func_ov004_02218b90();
    int func_ov004_02218be0();
    void func_ov004_02218c0c();
    int func_ov004_02218c3c();
    void func_ov004_02218c74();
    int func_ov004_02218cb4();

    char pad_844[0x1];
    unsigned char unk_845;
};

#endif
