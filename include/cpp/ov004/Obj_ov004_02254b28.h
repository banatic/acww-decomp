#ifndef CPP_OV004_OBJ_OV004_02254B28_H
#define CPP_OV004_OBJ_OV004_02254B28_H

#include "cpp/main/Base_0203f080.h"

// vtable 0x02254b28: primary base of the room objects whose Base_02066994 part sits
// at 0x290 (destructor func_ov004_0222c7a0).
struct Obj_ov004_02254b28 : public Base_0203f080 {
    virtual ~Obj_ov004_02254b28();
    virtual int vfunc_60(unsigned int mode); // func_ov004_0222c6cc: accepts every mode
    virtual void vfunc_64(void *position);   // func_ov004_0222c6d0
    char pad_ec[0x160];
    unsigned char unk_24c;
    char pad_24d[0x43];
};

#endif
