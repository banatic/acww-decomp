#ifndef CPP_MAIN_OBJ_020E2F6C_H
#define CPP_MAIN_OBJ_020E2F6C_H

// vtable 0x020e2f6c: constructor func_02094fd4, destructor func_02094fbc, both
// with C linkage, so callers build one in raw stack storage and call them by
// hand; they fill it through func_02082438 and read slot 0x0c.
struct Obj_020e2f6c {
    virtual ~Obj_020e2f6c(); // slot 0x00; func_02094fbc
    virtual int vfunc_08();  // func_02094f98
    virtual int vfunc_0c();  // func_02094f94
    char pad_04[0x1c];
};

#endif
