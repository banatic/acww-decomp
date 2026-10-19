#ifndef CPP_OV004_OBJ_OV004_02251690_H
#define CPP_OV004_OBJ_OV004_02251690_H

#include "cpp/autoload_2/Member_020f655c.h"
#include "cpp/ov004/RoomObject.h"

// vtable 0x02251690: room object
struct Obj_ov004_02251690 : public RoomObject {
    virtual ~Obj_ov004_02251690();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_0c();            // func_ov004_022132a4
    virtual int vfunc_70(int a, int b); // func_ov004_02213270
    virtual void vfunc_7c();            // func_ov004_02213328
    virtual void vfunc_80();            // func_ov004_022132f4
    virtual void vfunc_84();            // func_ov004_022132bc

    Member_020f655c unk_844;
};

#endif
