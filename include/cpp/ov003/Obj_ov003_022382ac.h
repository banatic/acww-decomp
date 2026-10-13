#ifndef CPP_OV003_OBJ_OV003_022382AC_H
#define CPP_OV003_OBJ_OV003_022382AC_H

#include "cpp/autoload_2/Obj_0213f074.h"
#include "cpp/main/Base_0203f080.h"
#include "cpp/main/Base_02066994.h"
#include "cpp/main/Member_02032c50.h"
#include "cpp/main/Obj_020dd03c.h"
#include "cpp/ov003/Member_ov003_0221b75c.h"

// Outdoor scene object: primary vtable 0x022382ac, the Base_02066994 part at
// 0xec (vtable 0x02238314). Its update (vtable slot 0x18) runs two state
// machines; most handlers of the first one live in ov068.
class Obj_ov003_022382ac : public Base_0203f080, public Base_02066994 {
  public:
    virtual ~Obj_ov003_022382ac();
    static void operator delete(void *p); // func_ov003_0221b5a4

    // first machine, indexed by state_39c
    void func_ov068_0226f854();
    void func_ov068_0226f648();
    void func_ov068_0226f504();
    void func_ov068_0226f49c();
    void func_ov068_0226f3b0();
    void func_ov068_0226f298();
    void func_ov068_0226f178();
    void func_ov068_0226effc();
    void func_ov068_0226ee54();
    void func_ov003_0221a1dc();
    void func_ov068_0226ed9c();
    void func_ov003_0221a128();
    void func_ov068_0226eca8();
    void func_ov068_0226ebc4();
    void func_ov003_0221a244();

    // second machine, indexed by state_3a0
    void func_ov003_02219f80();
    void func_ov003_02219e98();
    void func_ov003_02219e64();
    void func_ov003_02219f88();

    char pad_130[0x4];
    Obj_020dd03c unk_134;
    Obj_020dd03c unk_1d0;
    char pad_26c[0x274 - 0x26c];
    Member_02032c50 unk_274;
    char pad_284[0x2a4 - 0x284];
    Member_ov003_0221b75c unk_2a4;
    Obj_0213f074 unk_328;
    char pad_36c[0x39c - 0x36c];
    int state_39c;
    int state_3a0;
};

#endif
