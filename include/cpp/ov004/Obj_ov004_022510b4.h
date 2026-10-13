#ifndef CPP_OV004_OBJ_OV004_022510B4_H
#define CPP_OV004_OBJ_OV004_022510B4_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x022510b4: room object
struct Obj_ov004_022510b4 : public RoomObject {
    virtual ~Obj_ov004_022510b4();

    // state handlers, dispatched through tables in func_ov004_02218ce8, func_ov004_02218d74
    void func_ov004_02218ce8();
    void func_ov004_02218b2c();
    int func_ov004_02218b5c();
    void func_ov004_02218b90();
    int func_ov004_02218be0();
    void func_ov004_02218c0c();
    int func_ov004_02218c3c();
    void func_ov004_02218c74();
    int func_ov004_02218cb4();

    char pad_844[0x1];
    unsigned char unk_845;
};

#endif
