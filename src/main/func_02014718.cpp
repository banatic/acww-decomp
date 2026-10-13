/* func_02014718 @ 0x02014718, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/helper_ctors.h"

extern "C" {
extern int func_0201c250(void *);
extern void func_02066954(void *, int, int);
extern void func_0203ee14(void *, void *);
extern void func_020a8164(void *, int);
}

struct UnkStruct_02014718 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
    char pad[0x20];
};

// Same layout as UnkStruct_02014718; built and torn down by its out-of-line pair.
struct LocalBuf {
    void *vtbl;
    char pad[0x20];
};

struct Res {
    int a;
    unsigned char b;
};
struct UnkStruct_02014718_2 {
    int spare;
    Res in;
};
struct Flag {
    char pad[8];
    int unk_08;
};

struct UnkStruct_02014718_3 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30(Res *);
    char pad_04[0x1a];
    unsigned char unk_1E;
    char pad_1F[0x21];
    Flag *unk_40;
};

struct UnkStruct_02014718_4 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29(UnkStruct_02014718 *);
    char pad_04[0x630];
    UnkStruct_02014718_3 *unk_634;
};

extern "C" void func_02014718(void *self, UnkStruct_02014718_4 *obj)
{
    UnkStruct_02014718_3 *p;
    UnkStruct_02014718_2 out;
    int n;

    p = obj->unk_634;
    if (p != 0) {
        LocalBuf loc;
        UnkStruct_02014718 *lp;
        func_02094fd4(&loc);
        obj->v29((UnkStruct_02014718 *) &loc);
        lp = (UnkStruct_02014718 *) &loc;
        n = lp->v3();
        func_02066954(p, n, func_0201c250(obj));
        func_0203ee14(obj, p);
        p->v30(&out.in);
        func_020a8164(p, out.in.a);
        p->unk_1E = out.in.b;
        p->unk_40->unk_08 = 1;
        func_02094fbc(&loc);
    }
}
