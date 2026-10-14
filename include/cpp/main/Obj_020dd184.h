#ifndef CPP_MAIN_OBJ_020DD184_H
#define CPP_MAIN_OBJ_020DD184_H

// vtable 0x020dd184, destructor func_02057054 (complete: func_02057078). Used as a
// base at 0x9c of Obj_020dd05c and as a member; frees through func_020edb3c.
// func_02056ffc (C linkage) advances it; call it with the object's address.
struct Obj_020dd184 {
    virtual ~Obj_020dd184();
    static void operator delete(void *p);
    char pad_04[4];
    int unk_08;
    int unk_0C;
    int unk_10; // 0x1000 after construction
    char pad_14[4];
};

#endif
