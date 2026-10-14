#ifndef CPP_OV009_OBJ_OV009_022658DC_H
#define CPP_OV009_OBJ_OV009_022658DC_H

#include "cpp/autoload_2/Obj_0213f090.h"
#include "cpp/main/Base_0203f080.h"
#include "cpp/main/Base_02066994.h"
#include "cpp/main/Member_0209d340.h"
#include "cpp/main/Member_020b33b8.h"
#include "cpp/main/Obj_020dd05c.h"

// Abstract scene actor shared by ov003 and ov068: primary vtable 0x022658dc
// (47 slots, two pure), the Base_02066994 part at 0xec (vtable 0x022659a0).
// Two state machines drive it through member-pointer tables: an update
// index at 0x27c and a byte mode at 0x134.
class Obj_ov009_022658dc : public Base_0203f080, public Base_02066994 {
  public:
    virtual ~Obj_ov009_022658dc();

    // slots added after Base_0203f080's, named by byte offset
    virtual void vfunc_60();
    virtual int vfunc_64();
    virtual int vfunc_68();
    virtual void vfunc_6c(int mode); // func_ov009_0226418c
    virtual void vfunc_70();
    virtual void vfunc_74(); // func_ov009_022640d8: runs the mode handler
    virtual void vfunc_78();
    virtual void vfunc_7c();
    virtual void vfunc_80();
    virtual void vfunc_84();
    virtual void vfunc_02066994_14(); // func_ov009_02263344, also Base_02066994 slot 0x14
    virtual int vfunc_8c();
    virtual int vfunc_90();
    virtual int vfunc_94();
    virtual void vfunc_98();
    virtual void vfunc_9c();
    virtual void vfunc_a0();
    virtual void vfunc_a4();
    virtual void vfunc_a8();
    virtual void vfunc_ac();
    virtual void vfunc_b0();
    virtual void vfunc_b4();
    virtual void vfunc_b8();

    // update states, indexed by state_27c
    void func_ov009_022638c8();
    void func_ov009_022637ec();
    void func_ov009_02263790();
    void func_ov009_02263748();
    void func_ov009_02263718();
    void func_ov009_02263658();
    void func_ov009_0226357c();
    void func_ov009_0226354c();
    void func_ov009_022634f0();
    void func_ov009_022638d0();

    // state entry checks; a passing check moves state_27c
    int func_ov009_022638cc();
    int func_ov009_02263888();
    int func_ov009_022637bc();
    int func_ov009_0226378c();
    int func_ov009_02263734();
    int func_ov009_02263694();
    int func_ov009_02263648();
    int func_ov009_02263568();
    int func_ov009_02263548();
    int func_ov009_022639a0(int state);

    // primary vtable slots 0x00 (init) and 0x1c (update), and the event handler
    // the derived classes' slot 0x4c falls back to
    int func_ov009_0226523c();
    int func_ov009_02265144();
    void func_ov009_022633ac(unsigned int event, int arg);

    // mode handlers, indexed by state_134
    void func_ov009_02263fbc();
    void func_ov009_02263de8();
    void func_ov009_02263c14();
    void func_ov009_02263b78();
    void func_ov009_02263ab0();
    void func_ov009_02263a98();
    void func_ov009_02263a80();

    char pad_130[0x2];
    volatile unsigned short unk_132;
    unsigned char state_134;
    unsigned char pad_135;
    unsigned short unk_136;
    char pad_138[0x4];
    Obj_020dd05c unk_13c; // its Obj_020dd184 part sits at 0x1d8
    Member_020b33b8 unk_1f4;
    unsigned char unk_235;
    unsigned char flag_236_0 : 1;
    unsigned char flag_236_1 : 1;
    unsigned char pad_236_2 : 6;
    char pad_237;
    Obj_0213f090 unk_238;
    int state_27c;
    unsigned char unk_280;
    char pad_281[0x292 - 0x281];
    Member_0209d340 unk_292;
    char pad_294[0x2b4 - 0x294];
};

#endif
