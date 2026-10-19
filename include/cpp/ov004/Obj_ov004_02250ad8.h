#ifndef CPP_OV004_OBJ_OV004_02250AD8_H
#define CPP_OV004_OBJ_OV004_02250AD8_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x02250ad8: room object
struct Obj_ov004_02250ad8 : public RoomObject {
    virtual ~Obj_ov004_02250ad8();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_0c();            // func_ov004_0221259c
    virtual int vfunc_70(int a, int b); // func_ov004_022124b8
    virtual void vfunc_74();            // func_ov004_0221253c
    virtual void vfunc_7c();            // func_ov004_022125b0
    virtual void vfunc_80();            // Obj_ov004_02250ad8::func_ov004_022125a0
    virtual void vfunc_88();            // func_ov004_02212578

    // update entry: runs the state handler dispatch below, then returns 1
    int func_ov004_022125a0();

    // state handlers, dispatched through tables in func_ov004_0221244c, func_ov004_022124b8
    void func_ov004_0221244c();
    void func_ov004_022123c4();

    int func_ov004_022123ec();
    void func_ov004_02212408();

    int func_ov004_02212430();

    unsigned char unk_844;
};

#endif
