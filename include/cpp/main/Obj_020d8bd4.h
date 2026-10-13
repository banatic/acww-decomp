#ifndef CPP_MAIN_OBJ_020D8BD4_H
#define CPP_MAIN_OBJ_020D8BD4_H

#include "cpp/main/Base_02066994.h"

// Scene base (vtable 0x020d8bd4, destructors func_02016174/func_02016194, base-object
// destructor func_0201615c). Overrides the Base_02066994 slots that drive the scene and
// adds four: a pure slot at 0x78, 0x7c, 0x80 and the state-finished hook at 0x84.
// Its states run through nested pointer-to-member tables: func_0201584c picks a
// sub-machine by unk_64, each sub-machine dispatches on unk_AC, unk_98 or unk_0A.
// Scene classes in main (vtables 0x020d9ff8, 0x020e7bd0, 0x020e7e14, 0x020e86ec) and in
// many overlays derive from it.
class Obj_020d8bd4 : public Base_02066994 {
  public:
    virtual ~Obj_020d8bd4();
    virtual void vfunc_02066994_08();
    virtual void vfunc_02066994_34();
    virtual void vfunc_02066994_38();
    virtual void vfunc_02066994_3c();
    virtual void vfunc_02066994_40();
    virtual void vfunc_02066994_44();
    virtual void vfunc_02066994_48();
    virtual void vfunc_02066994_4c();
    virtual void vfunc_02066994_50();
    virtual void vfunc_02066994_54();
    virtual void vfunc_02066994_58();
    virtual void vfunc_02066994_5c();
    virtual void vfunc_02066994_60();
    virtual void vfunc_02066994_6c();
    virtual void vfunc_78() = 0;
    virtual void vfunc_7c();
    virtual void vfunc_80();
    virtual void vfunc_84(int state);

    // sub-machine dispatchers
    void func_02013c34(void *arg);
    void func_02013d5c(void *arg);
    void func_02013e68(void *arg);
    void func_020142e4(void *arg);
    int func_020148a0();
    int func_02014a68();
    int func_02014bf0();
    int func_02014d1c();
    int func_02014e44();
    int func_02014f78();
    int func_020150ac();
    int func_020151d8();
    int func_02015370();
    int func_020154f4();
    int func_020155d8();
    void func_020169b8(void *arg);
    void func_02017370(void *arg);
    void func_020174e0(int arg);
    void func_020175d4(void *arg);
    void func_0201793c(int p2);
    void func_02018610(int arg);
    void func_02018a8c(void *arg);
    void func_02018c3c(void *arg);
    void func_02019030(void *arg);
    void func_020191dc(int arg);
    void func_02019450(int arg);

    // state handlers
    int func_02014920();
    int func_020149c4();
    int func_02014a20();
    int func_02014ae8();
    int func_02014b14();
    int func_02014b30();
    int func_02014c60();
    int func_02014cb0();
    int func_02014d8c();
    int func_02014dd8();
    int func_02014eb4();
    int func_02014f04();
    int func_02014fe8();
    int func_02015038();
    int func_0201511c();
    int func_0201516c();
    int func_02015248();
    int func_020152a4();
    int func_020153e0();
    int func_0201542c();
    int func_02015564();
    int func_02015578();
    int func_02015654();
    int func_02015688();
    int func_02015760();
    int func_02017ab4(int);
    int func_02017af0(int);
    int func_02017b44(int);
    int func_02017c18(int);
    int func_02017c70(int);
    int func_02017cac(int);
    int func_02017cf8(int);
    int func_02017d14(int);
    int func_02017d80(int);
    int func_02017dd8(int);
    int func_02017e00(int);
    int func_02017e20(int);
    int func_02017e7c(int);
    int func_02017ee4(int);
    int func_02017ff4(int);
    int func_02018090(int);
    int func_02018298(int);
    int func_02018304(int);
    int func_02018340(int);
    int func_020183cc(int);
    void func_02013c98(void *);
    void func_02013ee4(void *);
    void func_02013f58(void *);
    void func_0201404c(void *);
    void func_020141c4(void *);
    void func_02014360(void *);
    void func_020143d4(void *);
    void func_020144c8(void *);
    void func_02016a48(void *);
    void func_02016bfc(void *);
    void func_02016d6c(void *);
    void func_02016f30(void *);
    void func_020173d8(void *);
    void func_02017550(int arg);
    void func_02017574(int arg);
    void func_02017654(void *);
    void func_02017674(void *);
    void func_020176bc(void *);
    void func_020186b0(int);
    void func_02018714(int);
    void func_0201873c(int);
    void func_0201875c(int);
    void func_020187b8(int);
    void func_02018af4(void *);
    void func_02018ca4(void *);
    void func_02019098(void *);
    void func_0201924c(int arg);
    void func_02019304(int arg);
    void func_020194c0(int arg);
    void func_020194c8(int arg);

    char pad_44[0x20];
    int unk_64; // sub-machine
    char pad_68[0x30];
    unsigned char unk_98;
    char pad_99[0x13];
    unsigned char unk_AC;
    unsigned char unk_AD;
};

#endif
