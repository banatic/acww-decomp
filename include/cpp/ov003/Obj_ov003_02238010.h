#ifndef CPP_OV003_OBJ_OV003_02238010_H
#define CPP_OV003_OBJ_OV003_02238010_H

#include "cpp/main/Base_0203f080.h"
#include "cpp/main/Base_02066994.h"
#include "cpp/main/Member_020b7f60.h"

// Outdoor scene object: primary vtable 0x02238010, the Base_02066994 part at
// 0xec (vtable 0x02238078). One state index at 0x134 selects both the update
// handler and the entry check.
class Obj_ov003_02238010 : public Base_0203f080, public Base_02066994 {
  public:
    virtual ~Obj_ov003_02238010();

    // update states
    void func_ov003_0220bfe0();
    void func_ov003_0220bf4c();
    void func_ov003_0220bf18();
    void func_ov003_0220bfe8();

    // entry checks; a passing check moves state_134
    int func_ov003_0220bfe4();
    int func_ov003_0220bf70();
    int func_ov003_0220bf48();
    int func_ov003_0220c064(int state);

    // vtable slots 0x00, 0x18 and 0x4c of the primary vtable
    int func_ov003_0220c1e4();
    int func_ov003_0220c1a8();
    void func_ov003_0220c0f0(int event);

    char pad_130[0x4];
    int state_134;
    Member_020b7f60 unk_138;
};

#endif
