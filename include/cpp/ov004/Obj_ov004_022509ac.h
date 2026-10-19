#ifndef CPP_OV004_OBJ_OV004_022509AC_H
#define CPP_OV004_OBJ_OV004_022509AC_H

#include "cpp/ov004/Member_ov004_0220d0f4.h"
#include "cpp/ov004/RoomObject.h"

// vtable 0x022509ac: room object
struct Obj_ov004_022509ac : public RoomObject {
    virtual ~Obj_ov004_022509ac();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_0c();            // func_ov004_02212260
    virtual int vfunc_70(int a, int b); // func_ov004_022121c8
    virtual void vfunc_74();            // func_ov004_0221224c
    virtual void vfunc_7c();            // func_ov004_02212280
    virtual void vfunc_80();            // Obj_ov004_022509ac::func_ov004_02212264

    // update entry: runs the state handler dispatch below, then returns 1
    int func_ov004_02212264();

    // state handlers, dispatched through tables in func_ov004_0221215c, func_ov004_022121c8
    void func_ov004_0221215c();
    int func_ov004_0221206c();

    int func_ov004_022120b0();
    int func_ov004_022120e8();

    int func_ov004_02212124();

    Member_ov004_0220d0f4 unk_844;
    char pad_848[0x54];
    unsigned char unk_89c;
};

#endif
