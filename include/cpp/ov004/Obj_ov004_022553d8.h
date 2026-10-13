#ifndef CPP_OV004_OBJ_OV004_022553D8_H
#define CPP_OV004_OBJ_OV004_022553D8_H

#include "cpp/main/Base_02066994.h"
#include "cpp/main/Member_020324c4.h"
#include "cpp/main/Member_020b82d0.h"
#include "cpp/ov004/Obj_ov004_02254b28.h"

// vtable 0x022553d8, the Base_02066994 part at 0x290
struct Obj_ov004_022553d8 : public Obj_ov004_02254b28, public Base_02066994 {
    virtual ~Obj_ov004_022553d8();
    // Base_02066994 slots; primary slots 0x68..0x70
    virtual void vfunc_02066994_10(); // func_ov004_0222f4f8
    virtual void vfunc_02066994_14(); // func_ov004_0222f4e4
    virtual void vfunc_02066994_18(); // func_ov004_0222f4e0

    // state handlers, dispatched through tables in func_ov004_0222f640, func_ov004_0222f6e8, func_ov004_0222f908
    void func_ov004_0222f908();
    void func_ov004_0222f640();
    void func_ov004_0222f4fc();
    int func_ov004_0222f518();
    void func_ov004_0222f524();
    int func_ov004_0222f54c();
    void func_ov004_0222f568();
    int func_ov004_0222f584();
    void func_ov004_0222f590();
    int func_ov004_0222f5c8();
    void func_ov004_0222f5cc();
    int func_ov004_0222f5f0();
    void func_ov004_0222f638();
    int func_ov004_0222f63c();
    void func_ov004_0222f7a0();
    void func_ov004_0222f818();
    void func_ov004_0222f854();
    void func_ov004_0222f8cc();

    char pad_2d4[0x4];
    Member_020324c4 unk_2d8;
    char pad_2dc[0x98];
    Member_020b82d0 unk_374;
    char pad_378[0x2a4];
    int unk_61c;
};

#endif
