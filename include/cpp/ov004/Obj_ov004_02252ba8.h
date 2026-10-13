#ifndef CPP_OV004_OBJ_OV004_02252BA8_H
#define CPP_OV004_OBJ_OV004_02252BA8_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x02252ba8: room object
struct Obj_ov004_02252ba8 : public RoomObject {
    virtual ~Obj_ov004_02252ba8();

    // state handlers, dispatched through tables in func_ov004_022150b8, func_ov004_02215134
    void func_ov004_022150b8();
    void func_ov004_02214c50();
    int func_ov004_02214cd8();
    void func_ov004_02214d34();
    int func_ov004_02214df8();
    void func_ov004_02214fc8();
    int func_ov004_02215020();

    char pad_844[0x1e];
    unsigned char unk_862;
};

#endif
