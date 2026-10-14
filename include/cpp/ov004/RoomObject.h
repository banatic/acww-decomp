#ifndef CPP_OV004_ROOMOBJECT_H
#define CPP_OV004_ROOMOBJECT_H

#include "cpp/main/Base_0203f080.h"
#include "cpp/main/Base_02066994.h"
#include "cpp/main/Elem_020b7ed8.h"
#include "cpp/main/Member_0209d340.h"
#include "cpp/main/Member_020b82d0.h"
#include "cpp/main/Obj_020dd0dc.h"
#include "cpp/ov004/Elem_ov004_0220e4d4.h"
#include "cpp/ov004/Member_ov004_0220d028.h"
#include "cpp/ov004/Member_ov004_0220d258.h"
#include "cpp/ov004/Member_ov004_0220d388.h"
#include "cpp/ov004/Member_ov004_0220d3b4.h"
#include "cpp/ov004/Member_ov004_0220d4d8.h"
#include "cpp/ov004/Member_ov004_0220d824.h"
#include "cpp/ov004/Member_ov004_0220dff0.h"
#include "cpp/ov004/Member_ov004_0220e458.h"
#include "cpp/ov004/Member_ov004_0223b248.h"
#include "cpp/ov004/Member_ov004_0223cfb8.h"

// Base of ov004's room objects (vtable 0x0224fe6c, destructor func_ov004_02210cf0,
// operator delete func_ov004_02211518). The ROM keeps each class's destructors
// together with the this-adjusting thunks its Base_02066994 vtable points at.
struct RoomObject : public Base_0203f080, public Base_02066994 {
    virtual ~RoomObject();
    static void operator delete(void *p);
    virtual void vfunc_60();
    virtual void vfunc_64();
    virtual void vfunc_68();
    virtual void vfunc_6c();
    virtual void vfunc_70(int a, int b);

    // update entry: runs the state handler dispatch below, then returns 1
    int func_ov004_02210abc();

    // state handlers, dispatched through tables in func_ov004_0220cc28, func_ov004_0220ccf8
    void func_ov004_0220cc28();
    void func_ov004_0220c560();
    int func_ov004_0220c5c8();
    void func_ov004_0220c5cc();
    int func_ov004_0220c640();
    void func_ov004_0220c648();
    int func_ov004_0220c6b8();
    void func_ov004_0220c6f4();
    int func_ov004_0220c6fc();
    void func_ov004_0220c774();
    int func_ov004_0220c7e0();
    void func_ov004_0220c858();
    int func_ov004_0220c930();
    void func_ov004_0220c9f4();
    int func_ov004_0220c9f8();
    void func_ov004_0220c9fc();
    int func_ov004_0220cb68();

    char pad_130[0x2];
    Member_0209d340 unk_132;
    char pad_134[0x48];
    Member_ov004_0220d4d8 unk_17c;
    Member_ov004_0220d824 unk_18c;
    Elem_020b7ed8 unk_1d0[4];
    Member_ov004_0223b248 unk_250;
    Member_020b82d0 unk_28c;
    char pad_290[0x2a4];
    int unk_534;
    Obj_020dd0dc unk_538;
    Member_ov004_0220dff0 unk_62c;
    Member_ov004_0220e458 unk_6cc;
    Member_ov004_0220d388 unk_740;
    Member_ov004_0220d3b4 unk_742;
    char pad_744[0x4];
    Member_ov004_0220d258 unk_748;
    Member_ov004_0220d028 unk_764;
    Member_ov004_0223cfb8 unk_798;
    Elem_ov004_0220e4d4 unk_7c4[4];
};

#endif
