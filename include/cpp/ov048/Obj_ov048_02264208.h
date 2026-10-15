#ifndef CPP_OV048_OBJ_OV048_02264208_H
#define CPP_OV048_OBJ_OV048_02264208_H

// ov048's game object (vtable 0x02264208; main base vtable 0x020d8bd4, destructor
// func_0201615c). Two virtuals look up the current mode in a {mode, handler} table
// and run the matching handlers.
class Obj_ov048_02264208 {
  public:
    virtual ~Obj_ov048_02264208();
    virtual void func_ov048_02261f14();
    virtual void func_ov048_02261748();

    // handlers run by func_ov048_02261748, keyed by mode
    void func_ov048_02261b1c(int arg);
    void func_ov048_02261b10(int arg);

    void func_ov048_02261b04(int arg);

    void func_ov048_02261af8(int arg);
    void func_ov048_02261b28(int arg);
    void func_ov048_02261ce4(int arg);
    void func_ov048_02261b54(int arg);
    void func_ov048_02261be8(int arg);
    void func_ov048_02261a38(int arg);
    void func_ov048_02261a14(int arg);
    void func_ov048_022619f0(int arg);
    void func_ov048_022619b0(int arg);
    void func_ov048_022619ac(int arg);
    void func_ov048_0226196c(int arg);
    void func_ov048_02261e5c(int arg);
    void func_ov048_02261e1c(int arg);
    void func_ov048_02261ddc(int arg);
    void func_ov048_02261e78(int arg);
    void func_ov048_02261ee4(int arg);
    void func_ov048_02261ed0(int arg);

    // handlers run by func_ov048_02261f14, keyed by mode
    void func_ov048_022623f0();
    void func_ov048_022623b8();
    void func_ov048_02262358();

    void func_ov048_022622ec();
    void func_ov048_02262320();
    void func_ov048_02262368();

    void func_ov048_022622bc();
    void func_ov048_02262298();
    void func_ov048_022621e8();
    void func_ov048_0226224c();
    void func_ov048_022621d8();

    void func_ov048_022621c8();

    void func_ov048_022621a0();
    void func_ov048_0226213c();
    void func_ov048_02262114();
    void func_ov048_0226242c();

    char pad_04[0x1e - 0x04];
    unsigned char mode; // 0x1e
    char pad_1f[0x40 - 0x1f];
    int unk_40;
};

#endif
