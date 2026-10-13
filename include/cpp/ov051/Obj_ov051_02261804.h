#ifndef CPP_OV051_OBJ_OV051_02261804_H
#define CPP_OV051_OBJ_OV051_02261804_H

// ov051's game object (vtable 0x02261804; main base vtable 0x020d8bd4, destructor
// func_0201615c). A virtual looks up the current mode in a {mode, handler} table
// and runs the matching handlers.
class Obj_ov051_02261804 {
  public:
    virtual ~Obj_ov051_02261804();
    virtual void func_ov051_02260928();

    // handlers run by func_ov051_02260928, keyed by mode
    void func_ov051_02260e08();
    void func_ov051_02260de4();
    void func_ov051_02260dc0();
    void func_ov051_02260b60();
    void func_ov051_02260d94();
    void func_ov051_02260d44();
    void func_ov051_02260d1c();
    void func_ov051_02260cd8();
    void func_ov051_02260c94();
    void func_ov051_02260c44();
    void func_ov051_02260c1c();

    char pad_04[0x1e - 0x04];
    unsigned char mode; // 0x1e
    char pad_1f[0x40 - 0x1f];
    int unk_40;
};

#endif
