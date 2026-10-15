#ifndef CPP_MAIN_OBJ_020DA13C_H
#define CPP_MAIN_OBJ_020DA13C_H

// Root of the scene-object classes (vtable 0x020da13c, destructor func_020ee62c):
// 16 slots named after their byte offset, then the destructor pair at 0x40.
// Base_0203f080 extends the same slot list (through the class at vtable 0x020d7244).
class Obj_020da13c {
  public:
    virtual int vfunc_00();
    virtual int vfunc_04();
    virtual void vfunc_08(int flag);
    virtual int vfunc_0c();
    virtual int vfunc_10();
    virtual void vfunc_14(int marker);
    virtual int vfunc_18();
    virtual int vfunc_1c();
    virtual void vfunc_20();
    virtual int vfunc_24();
    virtual int vfunc_28();
    virtual void vfunc_2c();
    virtual void vfunc_30();
    virtual int vfunc_34(unsigned int size, void *heap);
    virtual int vfunc_38(void *block, int size);
    virtual int vfunc_3c();
    virtual ~Obj_020da13c();
};

#endif
