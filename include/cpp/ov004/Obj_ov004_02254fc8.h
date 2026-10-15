#ifndef CPP_OV004_OBJ_OV004_02254FC8_H
#define CPP_OV004_OBJ_OV004_02254FC8_H

#include "cpp/main/Base_02066994.h"
#include "cpp/ov004/Obj_ov004_02254b28.h"

// vtable 0x02254fc8: room object of the 0x290-offset family
struct Obj_ov004_02254fc8 : public Obj_ov004_02254b28, public Base_02066994 {
    virtual ~Obj_ov004_02254fc8();

    // state handlers, dispatched through tables in func_ov004_0222e65c, func_ov004_0222e73c
    void func_ov004_0222e65c();
    void func_ov004_0222deb4();
    int func_ov004_0222df3c();
    void func_ov004_0222df4c();
    int func_ov004_0222e0a0();
    void func_ov004_0222e0b8();

    int func_ov004_0222e124();
    void func_ov004_0222e128();
    int func_ov004_0222e1b4();
    void func_ov004_0222e1b8();

    int func_ov004_0222e220();
    void func_ov004_0222e25c();
    int func_ov004_0222e44c();
    void func_ov004_0222e450();
    int func_ov004_0222e4f8();
    void func_ov004_0222e4fc();
    int func_ov004_0222e5a0();
    void func_ov004_0222e5a4();
    int func_ov004_0222e644();
    // update: advances the animations, runs the state handlers, keeps the sounds alive
    int func_ov004_0222ec34();

    char pad_2d4[0xc28];
    int unk_efc;
};

#endif
