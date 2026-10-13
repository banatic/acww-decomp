#ifndef CPP_MAIN_OBJ_020DD05C_H
#define CPP_MAIN_OBJ_020DD05C_H

#include "cpp/main/Obj_020dd03c.h"
#include "cpp/main/Obj_020dd184.h"

// vtable 0x020dd05c, the Obj_020dd184 part at 0x9c (vtable 0x020dd06c).
// Destructor func_0205517c (complete: func_020551e0), constructor func_02055210.
struct Obj_020dd05c : public Obj_020dd03c, public Obj_020dd184 {
    virtual ~Obj_020dd05c();
    static void operator delete(void *p);
    int unk_B4;
};

#endif
