#ifndef CPP_OV068_OBJ_OV068_02277DC0_H
#define CPP_OV068_OBJ_OV068_02277DC0_H

// Arrival-sequence object: primary vtable 0x02277dc0. func_ov068_02274358
// (called from vtable slot 0x14) runs every handler whose key matches the
// byte at 0x1e; one handler is listed twice.
class Obj_ov068_02277dc0 {
  public:
    virtual void vfunc_00();

    void func_ov068_02274334();
    void func_ov068_02274314();
    void func_ov068_02274358();

    char pad_04[0x1e - 0x4];
    unsigned char state_1e;
};

#endif
