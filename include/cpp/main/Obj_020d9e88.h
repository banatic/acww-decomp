#ifndef CPP_MAIN_OBJ_020D9E88_H
#define CPP_MAIN_OBJ_020D9E88_H

#include "cpp/main/Obj_020d8c64.h"

// Scene object (vtable 0x020d9e88, 48 slots): Obj_020d8c64's 27 slots, then 21 more.
class Obj_020d9e88 : public Obj_020d8c64 {
  public:
    virtual ~Obj_020d9e88();
    virtual void *vfunc_6c();
    virtual void *vfunc_70();
    virtual void vfunc_74(int state);
    virtual int vfunc_78();
    virtual int vfunc_7c();
    virtual void vfunc_80();
    virtual int vfunc_84();
    virtual void vfunc_88(unsigned short *message, int flag);
    virtual void vfunc_8c();
    virtual void vfunc_90();
    virtual int vfunc_94();
    virtual int vfunc_98();
    virtual unsigned short vfunc_9c();
    virtual int vfunc_a0();
    virtual void vfunc_a4(int first, int second);
    virtual int vfunc_a8();
    virtual int vfunc_ac();
    virtual int vfunc_b0();
    virtual int vfunc_b4();
    virtual int vfunc_b8();
    virtual int vfunc_bc(); // func_0201ce2c, returns 0 here
};

#endif
