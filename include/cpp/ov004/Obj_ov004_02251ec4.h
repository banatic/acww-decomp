#ifndef CPP_OV004_OBJ_OV004_02251EC4_H
#define CPP_OV004_OBJ_OV004_02251EC4_H

#include "cpp/autoload_2/Obj_0213f074.h"
#include "cpp/ov004/RoomObject.h"

// vtable 0x02251ec4: room object
struct Obj_ov004_02251ec4 : public RoomObject {
    virtual ~Obj_ov004_02251ec4();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_0c(); // func_ov004_02213984
    virtual void vfunc_7c(); // func_ov004_02213a08
    virtual void vfunc_80(); // func_ov004_022139a8

    char pad_844[0x4];
    Obj_0213f074 unk_848;
};

#endif
