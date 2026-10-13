#ifndef CPP_MAIN_OBJ_020DD0DC_H
#define CPP_MAIN_OBJ_020DD0DC_H

#include "cpp/main/Obj_020dd05c.h"
#include "cpp/main/Obj_020dd174.h"

// vtable 0x020dd0dc; the Obj_020dd184 part at 0x9c (vtable 0x020dd0ec) and the
// Obj_020dd174 part at 0xb8 (vtable 0x020dd0fc). Destructor func_02054d9c
// (complete: func_02054e18), constructor func_02054e54.
struct Obj_020dd0dc : public Obj_020dd05c, public Obj_020dd174 {
    virtual ~Obj_020dd0dc();
    static void operator delete(void *p);
};

#endif
