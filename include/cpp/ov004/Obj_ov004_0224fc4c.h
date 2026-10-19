#ifndef CPP_OV004_OBJ_OV004_0224FC4C_H
#define CPP_OV004_OBJ_OV004_0224FC4C_H

#include "cpp/main/Base_0203f080.h"
#include "cpp/main/Base_02066994.h"
#include "cpp/main/Member_020324c4.h"
#include "cpp/main/Member_020b82d0.h"

// vtable 0x0224fc4c
struct Obj_ov004_0224fc4c : public Base_0203f080, public Base_02066994 {
    virtual ~Obj_ov004_0224fc4c();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_00(); // func_ov004_0220c3a0
    virtual void vfunc_0c(); // func_ov004_0220c36c
    virtual void vfunc_18(); // func_ov004_0220c380
    virtual void vfunc_24(); // func_ov004_0220c37c
    virtual void vfunc_48(); // func_ov004_0220c1f4
    virtual void vfunc_4c(); // func_ov004_0220c1d0
    // Base_02066994 slots; primary slots 0x60..0x68
    virtual void vfunc_02066994_10(); // func_ov004_0220c01c
    virtual void vfunc_02066994_14(); // func_ov004_0220bfb4
    virtual void vfunc_02066994_18(); // func_ov004_0220bf00

    // state handlers, dispatched through tables in func_ov004_0220c144
    int func_ov004_0220c050();
    int func_ov004_0220c078();
    int func_ov004_0220c0c4();

    char pad_130[0x4];
    int unk_134;
    Member_020324c4 unk_138;
    char pad_13c[0x98];
    Member_020b82d0 unk_1d4;
};

#endif
