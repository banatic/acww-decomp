#ifndef CPP_OV004_OBJ_OV004_0225211C_H
#define CPP_OV004_OBJ_OV004_0225211C_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x0225211c: room object
struct Obj_ov004_0225211c : public RoomObject {
    virtual ~Obj_ov004_0225211c();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_0c();            // func_ov004_022176e4
    virtual void vfunc_4c();            // func_ov004_02217264
    virtual int vfunc_70(int a, int b); // func_ov004_0221760c
    virtual void vfunc_74();            // func_ov004_022176ac
    virtual void vfunc_7c();            // func_ov004_02217700
    virtual void vfunc_80();            // Obj_ov004_0225211c::func_ov004_022176e8
    virtual void vfunc_a0();            // func_ov004_022176c0

    // update entry: runs the state handler dispatch below, then returns 1
    int func_ov004_022176e8();

    // state handlers, dispatched through tables in func_ov004_02217028, func_ov004_02217124, func_ov004_02217580, func_ov004_0221760c
    void func_ov004_02217580();
    void func_ov004_02217028();
    void func_ov004_02216c60();
    int func_ov004_02216c8c();
    void func_ov004_02216cd0();
    int func_ov004_02216cf4();
    void func_ov004_02216cf8();
    int func_ov004_02216d1c();
    void func_ov004_02216df0();
    int func_ov004_02216e0c();
    void func_ov004_02216e20();
    int func_ov004_02216e50();
    void func_ov004_02216ea8();
    int func_ov004_02216eb4();
    void func_ov004_02216eb8();
    int func_ov004_02216ed4();
    int func_ov004_02216f18();

    int func_ov004_02216f34();
    void func_ov004_02216f50();
    int func_ov004_02216f6c();
    void func_ov004_02216f80();
    int func_ov004_02216fb0();
    void func_ov004_02217010();
    int func_ov004_0221701c();
    void func_ov004_02217020();
    int func_ov004_02217024();
    void func_ov004_022172ac();
    int func_ov004_022172dc();
    void func_ov004_02217330();
    int func_ov004_02217360();
    void func_ov004_022173b8();
    int func_ov004_022173e8();
    void func_ov004_02217420();
    int func_ov004_02217534();

    Member_ov004_0220d258 unk_844;
    unsigned char unk_860;
    char pad_861[0x3];
    int unk_864;
};

#endif
