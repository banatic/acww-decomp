#ifndef CPP_OV054_OBJ_OV054_02263004_H
#define CPP_OV054_OBJ_OV054_02263004_H

// ov054's scene: a main-module scene class (vtable 0x020d8bd4 family) that picks its
// handlers through pointer-to-member tables.
class Obj_ov054_02263004 {
  public:
    virtual ~Obj_ov054_02263004();
    virtual void func_ov054_022612c4(unsigned int arg);
    virtual void func_ov054_02260d9c(unsigned int arg);

    // runs the handler for the current page and step
    void func_ov054_022608ac(unsigned int arg);

    // per-step handlers (tables at 0x02262f3c)
    void func_ov054_022607b8();
    void func_ov054_022607ec();
    void func_ov054_0226083c();
    void func_ov054_02260860();
    void func_ov054_02260894();

    // results of func_ov054_02260d9c
    void func_ov054_02260b30(unsigned int arg);
    void func_ov054_02260b70(unsigned int arg);
    void func_ov054_02260c00(unsigned int arg);

    // results of func_ov054_022612c4
    void func_ov054_02260e58(unsigned int arg);
    void func_ov054_02260ef8(unsigned int arg);
    void func_ov054_02260efc(unsigned int arg);

    char name[0xb0 - 0x04]; // 0x04
    char *unk_B0;
    int page; // 0xb4
};

#endif
