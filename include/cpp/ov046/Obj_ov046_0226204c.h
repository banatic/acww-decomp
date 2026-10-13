#ifndef CPP_OV046_OBJ_OV046_0226204C_H
#define CPP_OV046_OBJ_OV046_0226204C_H

// ov046's scene: a main-module scene class (vtable 0x020d8bd4 family). Two virtuals
// look up the current mode in a {mode, handler} table and run the matching handlers.
class Obj_ov046_0226204c {
  public:
    virtual ~Obj_ov046_0226204c();
    virtual void func_ov046_02260abc();
    virtual void func_ov046_02260ebc();

    // handlers run by func_ov046_02260abc, given the value of func_020ab504()
    void func_ov046_0226068c(int arg);
    void func_ov046_02260644(int arg);
    void func_ov046_02260664(int arg);
    void func_ov046_022606e0(int arg);
    void func_ov046_022606f4(int arg);
    void func_ov046_02260720(int arg);
    void func_ov046_0226077c(int arg);
    void func_ov046_022607f0(int arg);
    void func_ov046_0226086c(int arg);
    void func_ov046_022608a4(int arg);
    void func_ov046_022608e4(int arg);
    void func_ov046_02260914(int arg);
    void func_ov046_02260aa8(int arg);

    // handlers run by func_ov046_02260ebc
    void func_ov046_02260cd0();
    void func_ov046_02260cf4();
    void func_ov046_02260d18();
    void func_ov046_02260d3c();
    void func_ov046_02260d50();
    void func_ov046_02260d64();
    void func_ov046_02260d98();
    void func_ov046_02260ddc();
    void func_ov046_02260e34();

    char pad_04[0x1e - 0x04];
    unsigned char mode; // 0x1e
    char pad_1f[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xdc - 0x44];
    int next; // 0xdc
};

#endif
