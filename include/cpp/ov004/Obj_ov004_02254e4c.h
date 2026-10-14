#ifndef CPP_OV004_OBJ_OV004_02254E4C_H
#define CPP_OV004_OBJ_OV004_02254E4C_H

#include "cpp/main/Base_02066994.h"
#include "cpp/ov004/Obj_ov004_02254b28.h"

// vtable 0x02254e4c: room object of the 0x290-offset family
struct Obj_ov004_02254e4c : public Obj_ov004_02254b28, public Base_02066994 {
    virtual ~Obj_ov004_02254e4c();

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
