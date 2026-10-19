#ifndef CPP_OV004_OBJ_OV004_02255538_H
#define CPP_OV004_OBJ_OV004_02255538_H

#include "cpp/main/Base_02066994.h"
#include "cpp/ov004/Obj_ov004_02254b28.h"

// vtable 0x02255538: room object of the 0x290-offset family
struct Obj_ov004_02255538 : public Obj_ov004_02254b28, public Base_02066994 {
    virtual ~Obj_ov004_02255538();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_00();                 // func_ov004_022300fc
    virtual void vfunc_0c();                 // func_ov004_02230020
    virtual void vfunc_18();                 // func_ov004_02230078
    virtual void vfunc_24();                 // func_ov004_02230054
    virtual int vfunc_60(unsigned int mode); // func_ov004_0222ff84

    // state handlers, dispatched through tables in func_ov004_0222fef8, func_ov004_0222ff84
    void func_ov004_0222fef8();
    void func_ov004_0222fddc();
    int func_ov004_0222fe38();
    void func_ov004_0222fe50();
    int func_ov004_0222fea8();
    void func_ov004_0222feac();
    int func_ov004_0222fed4();
    void func_ov004_0222fef0();
    int func_ov004_0222fef4();
};

#endif
