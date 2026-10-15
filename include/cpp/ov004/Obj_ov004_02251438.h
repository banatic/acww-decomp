#ifndef CPP_OV004_OBJ_OV004_02251438_H
#define CPP_OV004_OBJ_OV004_02251438_H

#include "cpp/ov004/Member_ov004_0220d258.h"
#include "cpp/ov004/RoomObject.h"

// vtable 0x02251438: a room object that is itself a base class (destructor 02215e70)
struct Obj_ov004_02251438 : public RoomObject {
    virtual ~Obj_ov004_02251438();

    // update entry: runs the state handler dispatch below, then returns 1
    int func_ov004_02215de0();

    // state handlers, dispatched through tables in func_ov004_02215c70, func_ov004_02215cdc
    void func_ov004_02215c70();
    int func_ov004_02215ba8();

    int func_ov004_02215bd0();
    void func_ov004_02215c0c();
    int func_ov004_02215c34();

    unsigned char unk_844;
    char pad_845[0x3];
    Member_ov004_0220d258 unk_848;
};

#endif
