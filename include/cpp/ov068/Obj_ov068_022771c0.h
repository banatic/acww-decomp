#ifndef CPP_OV068_OBJ_OV068_022771C0_H
#define CPP_OV068_OBJ_OV068_022771C0_H

// Arrival-sequence director: primary vtable 0x022771c0 over a main-side base.
// Scenes are member functions taking one int argument; the global table
// data_ov068_02278484 holds the top-level scenes, and each scene steps
// through its own sub-scenes indexed by the byte at 0x1c.
class Obj_ov068_022771c0 {
  public:
    virtual void vfunc_00();

    // sub-scenes
    void func_ov068_02267400(int arg);
    void func_ov068_02267468(int arg);
    void func_ov068_022675c4(int arg);
    void func_ov068_022675c8(int arg);
    void func_ov068_02267724(int arg);
    void func_ov068_02267728(int arg);
    void func_ov068_022677a0(int arg);
    void func_ov068_0226793c(int arg);
    void func_ov068_02267964(int arg);
    void func_ov068_02267b0c(int arg);
    void func_ov068_02267b3c(int arg);
    void func_ov068_02267b8c(int arg);
    void func_ov068_02268020(int arg);
    void func_ov068_022680a4(int arg);
    void func_ov068_02268254(int arg);
    void func_ov068_0226831c(int arg);
    void func_ov068_0226840c(int arg);
    void func_ov068_0226863c(int arg);
    void func_ov068_022686c4(int arg);
    void func_ov068_0226893c(int arg);
    void func_ov068_022689d4(int arg);
    void func_ov068_02268c30(int arg);
    void func_ov068_02268c84(int arg);
    void func_ov068_02268d04(int arg);
    void func_ov068_02268fac(int arg);
    void func_ov068_02269028(int arg);
    void func_ov068_0226918c(int arg);
    void func_ov068_02269314(int arg);
    void func_ov068_022693f0(int arg);
    void func_ov068_02269450(int arg);
    void func_ov068_02269548(int arg);
    void func_ov068_02269684(int arg);
    void func_ov068_02269940(int arg);
    void func_ov068_02269944(int arg);
    void func_ov068_0226af6c(int arg);
    void func_ov068_0226af70(int arg);
    void func_ov068_0226b0ec(int arg);
    void func_ov068_0226b1d0(int arg);
    void func_ov068_0226b39c(int arg);
    void func_ov068_0226b3ac(int arg);
    void func_ov068_0226b4f8(int arg);
    void func_ov068_0226b640(int arg);
    void func_ov068_0226b7c8(int arg);
    void func_ov068_0226b88c(int arg);
    void func_ov068_0226b904(int arg);

    // scenes that step through sub-scenes; all return 0
    int func_ov068_02267394(int arg);
    int func_ov068_02267558(int arg);
    int func_ov068_022676a8(int arg);
    int func_ov068_022678d0(int arg);
    int func_ov068_02267a90(int arg);
    int func_ov068_02267d5c(int arg);
    int func_ov068_02267f84(int arg);
    int func_ov068_022685d0(int arg);
    int func_ov068_022688d0(int arg);
    int func_ov068_02268bb4(int arg);
    int func_ov068_02268f40(int arg);
    int func_ov068_02269128(int arg);
    int func_ov068_02269278(int arg);
    int func_ov068_022698d4(int arg);
    int func_ov068_0226af00(int arg);
    int func_ov068_0226b080(int arg);
    int func_ov068_0226b330(int arg);
    int func_ov068_0226b48c(int arg);
    int func_ov068_0226b74c(int arg);

    // choices tried in random order by func_ov068_02269b88
    int func_ov068_0226ab58(int arg);
    int func_ov068_0226aad4(int arg);
    int func_ov068_0226a91c(int arg);
    int func_ov068_0226a618(int arg);
    int func_ov068_0226a49c(int arg);
    int func_ov068_0226a3e0(int arg);
    int func_ov068_0226a260(int arg);
    void func_ov068_02269b88(int arg);

    char pad_04[0x1c - 0x4];
    unsigned char state_1c;
};

#endif
