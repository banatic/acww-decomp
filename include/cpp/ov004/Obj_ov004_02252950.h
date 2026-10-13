#ifndef CPP_OV004_OBJ_OV004_02252950_H
#define CPP_OV004_OBJ_OV004_02252950_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x02252950: room object
struct Obj_ov004_02252950 : public RoomObject {
    virtual ~Obj_ov004_02252950();

    // state handlers, dispatched through tables in func_ov004_02211824, func_ov004_022118bc, func_ov004_02211a14, func_ov004_02211aa0
    void func_ov004_02211a14();
    void func_ov004_02211824();
    void func_ov004_0221167c();
    int func_ov004_022116a4();
    void func_ov004_022116c4();
    int func_ov004_022116f8();
    void func_ov004_022116fc();
    int func_ov004_02211720();
    void func_ov004_02211764();
    int func_ov004_02211790();
    void func_ov004_022117b0();
    int func_ov004_02211820();
    void func_ov004_02211964();
    int func_ov004_02211978();
    void func_ov004_0221199c();
    int func_ov004_022119a0();
    void func_ov004_022119bc();
    int func_ov004_022119d0();
    void func_ov004_022119f4();
    int func_ov004_022119f8();

    char pad_844[0x10];
    unsigned char unk_854;
    char pad_855[0x3];
    int unk_858;
};

#endif
