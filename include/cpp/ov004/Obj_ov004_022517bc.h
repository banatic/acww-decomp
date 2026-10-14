#ifndef CPP_OV004_OBJ_OV004_022517BC_H
#define CPP_OV004_OBJ_OV004_022517BC_H

#include "cpp/ov004/Member_ov004_0220d0f4.h"
#include "cpp/ov004/RoomObject.h"

// vtable 0x022517bc: room object
struct Obj_ov004_022517bc : public RoomObject {
    virtual ~Obj_ov004_022517bc();

    // update entry: runs the state handler dispatch below, then returns 1
    int func_ov004_02216694();

    // state handlers, dispatched through tables in func_ov004_02216110, func_ov004_0221617c, func_ov004_022163f8, func_ov004_022164a0
    void func_ov004_022163f8();
    void func_ov004_02216110();
    void func_ov004_02215f8c();
    int func_ov004_02215ff0();
    void func_ov004_0221605c();
    int func_ov004_022160b0();
    void func_ov004_02216214();
    int func_ov004_02216244();
    void func_ov004_02216248();
    int func_ov004_0221626c();
    void func_ov004_02216350();
    int func_ov004_0221635c();
    void func_ov004_02216360();
    int func_ov004_022163c4();
    void func_ov004_022163e0();
    int func_ov004_022163ec();
    void func_ov004_022163f0();
    int func_ov004_022163f4();

    char pad_844[0x4];
    Member_ov004_0220d0f4 unk_848;
    char pad_84c[0x54];
    unsigned char unk_8a0;
    char pad_8a1[0x3];
    int unk_8a4;
};

#endif
