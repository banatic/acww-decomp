#ifndef CPP_MAIN_BASE_02066994_H
#define CPP_MAIN_BASE_02066994_H

// Message-receiver base (vtable 0x020df008, destructor func_02066994): the
// destructor pair, then 28 slots. Most slots are empty stubs
// (func_02066858..func_020668c0) that derived classes override. Used as the
// primary base of Obj_020d8bd4 and as the second base of scene objects.
//
// Slot names: vfunc_02066994_<byte offset in this vtable>. They differ from the
// vfunc_<offset> slots of Base_0203f080 on purpose. A class that has this base
// second and overrides one of its slots overrides only this vtable (through a
// this-adjusting thunk); mwcc also gives the override a slot in the class's own
// primary vtable, in declaration order, as the ROM's vtables show.
struct Base_02066994 {
    virtual ~Base_02066994();
    virtual void vfunc_02066994_08();
    virtual void vfunc_02066994_0c();
    virtual void vfunc_02066994_10();
    virtual void vfunc_02066994_14();
    virtual void vfunc_02066994_18();
    virtual void vfunc_02066994_1c();
    virtual void vfunc_02066994_20();
    virtual void vfunc_02066994_24();
    virtual void vfunc_02066994_28();
    virtual void vfunc_02066994_2c();
    virtual void vfunc_02066994_30();
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
    virtual void vfunc_02066994_64();
    virtual void vfunc_02066994_68();
    virtual void vfunc_02066994_6c();
    virtual void vfunc_02066994_70();
    virtual void vfunc_02066994_74();
    char pad_04[6];
    unsigned char unk_0A;
    char pad_0B[0x1e - 0xb];
    unsigned char unk_1E;
    char pad_1F[0x40 - 0x1f];
    void *unk_40;
};

#endif
