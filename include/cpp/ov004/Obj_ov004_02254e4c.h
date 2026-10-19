#ifndef CPP_OV004_OBJ_OV004_02254E4C_H
#define CPP_OV004_OBJ_OV004_02254E4C_H

#include "cpp/main/Base_02066994.h"
#include "cpp/ov004/Obj_ov004_02254b28.h"

// vtable 0x02254e4c: room object of the 0x290-offset family
struct Obj_ov004_02254e4c : public Obj_ov004_02254b28, public Base_02066994 {
    virtual ~Obj_ov004_02254e4c();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_00();                 // func_ov004_0222d790
    virtual void vfunc_0c();                 // func_ov004_0222d71c
    virtual void vfunc_18();                 // Obj_ov004_02254e4c::func_ov004_0222d774
    virtual void vfunc_24();                 // func_ov004_0222d760
    virtual int vfunc_60(unsigned int mode); // func_ov004_0222d1e0

    // state handlers, dispatched through tables in func_ov004_0222d154
    void func_ov004_0222d154();
    void func_ov004_0222ce1c();
    void func_ov004_0222cf18();

    void func_ov004_0222cfbc();
    void func_ov004_0222d0bc();

    // update: runs the state handlers between the two helpers
    int func_ov004_0222d774();
};

#endif
