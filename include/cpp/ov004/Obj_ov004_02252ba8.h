#ifndef CPP_OV004_OBJ_OV004_02252BA8_H
#define CPP_OV004_OBJ_OV004_02252BA8_H

#include "cpp/ov004/RoomObject.h"

// vtable 0x02252ba8: room object
struct Obj_ov004_02252ba8 : public RoomObject {
    virtual ~Obj_ov004_02252ba8();
    // slots overridden here, with the function the ROM vtable holds
    virtual void vfunc_0c();            // func_ov004_02215350
    virtual void vfunc_68();            // func_ov004_0221533c
    virtual void vfunc_6c();            // func_ov004_022152f8
    virtual int vfunc_70(int a, int b); // func_ov004_02215134
    virtual void vfunc_74();            // func_ov004_022151c4
    virtual void vfunc_7c();            // func_ov004_02215394
    virtual void vfunc_80();            // Obj_ov004_02252ba8::func_ov004_02215374
    virtual void vfunc_84();            // func_ov004_02215360

    // state handlers, dispatched through tables in func_ov004_022150b8, func_ov004_02215134
    void func_ov004_022150b8();
    void func_ov004_02214c50();
    int func_ov004_02214cd8();
    void func_ov004_02214d34();
    int func_ov004_02214df8();
    void func_ov004_02214fc8();

    int func_ov004_02215020();
    // update: runs the state handlers, then advances the counter at 0x85c
    int func_ov004_02215374();

    char pad_844[0x1e];
    unsigned char unk_862;
};

#endif
