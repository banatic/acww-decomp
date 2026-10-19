#ifndef CPP_OV004_OBJ_OV004_02255674_H
#define CPP_OV004_OBJ_OV004_02255674_H

#include "cpp/main/Base_02066994.h"
#include "cpp/ov004/Obj_ov004_02254b28.h"

// vtable 0x02255674: room object of the 0x290-offset family
struct Obj_ov004_02255674 : public Obj_ov004_02254b28, public Base_02066994 {
    virtual ~Obj_ov004_02255674();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_00(); // func_ov004_022309f8
    virtual void vfunc_0c(); // func_ov004_022308a8
    virtual void vfunc_18(); // func_ov004_0223097c
    virtual void vfunc_24(); // func_ov004_02230978

    // state handlers, dispatched through tables in func_ov004_02230780, func_ov004_0223080c
    void func_ov004_02230780();
    void func_ov004_02230538();
    int func_ov004_022305a0();
    int func_ov004_02230620();

    int func_ov004_0223063c();
    int func_ov004_022306a8();

    int func_ov004_022306d0();
    void func_ov004_02230750();
    int func_ov004_02230754();

    char pad_2d4[0x404];
    int unk_6d8;
};

#endif
