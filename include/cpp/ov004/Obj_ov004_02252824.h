#ifndef CPP_OV004_OBJ_OV004_02252824_H
#define CPP_OV004_OBJ_OV004_02252824_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x02252824: room object
struct Obj_ov004_02252824 : public RoomObject {
    virtual ~Obj_ov004_02252824();

    // update entry: runs the state handler dispatch below, then returns 1
    int func_ov004_022148e0();

    // state handlers, dispatched through tables in func_ov004_0221479c, func_ov004_02214828
    void func_ov004_0221479c();
    void func_ov004_02214474();
    int func_ov004_022144e0();
    int func_ov004_02214568();

    int func_ov004_02214598();
    void func_ov004_02214610();
    int func_ov004_02214680();
    void func_ov004_02214704();
    int func_ov004_0221472c();

    unsigned char unk_844;
};

#endif
