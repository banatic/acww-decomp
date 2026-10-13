#ifndef CPP_OV004_OBJ_OV004_02253058_H
#define CPP_OV004_OBJ_OV004_02253058_H

#include "cpp/ov004/Member_ov004_0220d0f4.h"
#include "cpp/ov004/RoomObject.h"

// vtable 0x02253058: room object
struct Obj_ov004_02253058 : public RoomObject {
    virtual ~Obj_ov004_02253058();
    virtual void vfunc_70(int a, int b);
    // Base_02066994 slots; also appended after that vtable
    virtual void vfunc_02066994_14(); // func_ov004_022178fc
    virtual void vfunc_02066994_18(); // func_ov004_02217864

    // state handlers, dispatched through tables in func_ov004_02218110, func_ov004_02218228
    void func_ov004_02218110();
    void func_ov004_022179e8();
    int func_ov004_02217a28();
    void func_ov004_02217a38();
    int func_ov004_02217ac4();
    void func_ov004_02217af4();
    int func_ov004_02217b70();
    void func_ov004_02217b74();
    int func_ov004_02217bd8();
    void func_ov004_02217bdc();
    int func_ov004_02217c0c();
    void func_ov004_02217c10();
    int func_ov004_02217c14();
    void func_ov004_02217c58();
    int func_ov004_02217c6c();
    void func_ov004_02217c70();
    int func_ov004_02217cb4();
    void func_ov004_02217cb8();
    int func_ov004_02217cf8();
    void func_ov004_02217cfc();
    int func_ov004_02217d00();
    void func_ov004_02217d68();
    int func_ov004_02217d98();
    void func_ov004_02217da8();
    int func_ov004_02217e08();
    void func_ov004_02217e0c();
    int func_ov004_02217eb8();
    void func_ov004_02217f2c();
    int func_ov004_02218100();

    char pad_844[0x1a];
    unsigned char unk_85e;
    char pad_85f[0x1];
    Member_ov004_0220d0f4 unk_860;
};

#endif
