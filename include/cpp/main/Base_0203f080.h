#ifndef CPP_MAIN_BASE_0203F080_H
#define CPP_MAIN_BASE_0203F080_H

struct Vec_0203f080 {
    int x;
    int y;
    int z;
};

// Scene-object base (vtable 0x020dab34, destructor func_0203f080). Its own bases
// (vtables 0x020d7244 and 0x020da13c) add no slots, so they are folded in here.
// Slot names follow their byte offset; the destructor pair sits at 0x40.
struct Base_0203f080 {
    virtual void vfunc_00();
    virtual void vfunc_04();
    virtual void vfunc_08();
    virtual void vfunc_0c();
    virtual void vfunc_10();
    virtual void vfunc_14();
    virtual void vfunc_18();
    virtual void vfunc_1c();
    virtual void vfunc_20();
    virtual void vfunc_24();
    virtual void vfunc_28();
    virtual void vfunc_2c();
    virtual void vfunc_30();
    virtual void vfunc_34();
    virtual void vfunc_38();
    virtual void vfunc_3c();
    virtual ~Base_0203f080();
    virtual void vfunc_48();
    virtual void vfunc_4c();
    virtual void vfunc_50();
    virtual void vfunc_54();
    virtual void vfunc_58();
    virtual void vfunc_5c();
    char pad_04[0x58];
    Vec_0203f080 unk_5C; // position
    char pad_68[0x48];
    int unk_B0;
    char pad_B4[0x38];
};

#endif
