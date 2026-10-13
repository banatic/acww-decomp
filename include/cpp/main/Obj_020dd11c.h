#ifndef CPP_MAIN_OBJ_020DD11C_H
#define CPP_MAIN_OBJ_020DD11C_H

// Root of a small polymorphic family (vtable 0x020dd11c, destructor func_02056390).
// Its deleting destructor frees through func_020edb3c, not the global operator delete.
struct Obj_020dd11c {
    virtual ~Obj_020dd11c();
    static void operator delete(void *p);
};

#endif
