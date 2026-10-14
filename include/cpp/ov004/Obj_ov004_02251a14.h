#ifndef CPP_OV004_OBJ_OV004_02251A14_H
#define CPP_OV004_OBJ_OV004_02251A14_H

#include "cpp/ov004/Member_ov004_0220d0f4.h"
#include "cpp/ov004/RoomObject.h"

// vtable 0x02251a14: room object
struct Obj_ov004_02251a14 : public RoomObject {
    virtual ~Obj_ov004_02251a14();

    // update entry: runs the state handler dispatch below, then returns 1
    int func_ov004_02219d08();

    // state handlers, dispatched through tables in func_ov004_02219c00, func_ov004_02219c6c
    void func_ov004_02219c00();
    void func_ov004_02219b38();
    int func_ov004_02219b70();
    void func_ov004_02219ba4();
    int func_ov004_02219bcc();

    unsigned char unk_844;
    char pad_845[0x3];
    Member_ov004_0220d0f4 unk_848;
};

#endif
