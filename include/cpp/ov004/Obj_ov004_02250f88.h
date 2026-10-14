#ifndef CPP_OV004_OBJ_OV004_02250F88_H
#define CPP_OV004_OBJ_OV004_02250F88_H

#include "cpp/ov004/Obj_ov004_02251438.h"

// vtable 0x02250f88: room object derived from Obj_ov004_02251438
struct Obj_ov004_02250f88 : public Obj_ov004_02251438 {
    virtual ~Obj_ov004_02250f88();

    // update entry: runs the state handler dispatch below, then returns 1
    int func_ov004_02215a80();

    // state handlers, dispatched through tables in func_ov004_0221593c, func_ov004_022159c8
    void func_ov004_0221593c();
    void func_ov004_02215758();
    int func_ov004_02215788();
    void func_ov004_022157d4();
    int func_ov004_022157fc();
    void func_ov004_02215844();
    int func_ov004_02215874();
    void func_ov004_022158c8();
    int func_ov004_022158f0();

    char pad_864[0x1];
    unsigned char unk_865;
};

#endif
