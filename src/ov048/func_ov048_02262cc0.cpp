/* func_ov048_02262cc0 @ 0x02262cc0, 0x8c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/helper_ctors.h"

extern "C" {
extern void *func_020a13d0(void);
extern void *func_020984fc(void *arg0);
extern int DWCi_GsMalloc(void *);
extern void *func_020682e0(int);
extern void func_020a8164(void *, void *);
extern void func_02068340(void *, void *);
extern void func_02068404(void *, int, void *);
extern void *func_02099870(void *);
extern void *func_02095074(void *, void *);
extern void *data_ov048_02263d20;
}

struct UnkStruct_02262cc0 {
    char pad_00[0x24];
};

struct Pair {
    int spare;
    UnkStruct_02262cc0 loc;
};

struct UnkStruct_02262cc0_2 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

struct UnkStruct_02262cc0_3 {
    char pad_00[0x658];
    UnkStruct_02262cc0_2 sub;
    char pad_65C[0x1a];
    unsigned char unk_676;
};

struct Res {
    char pad_00[8];
    int unk_08;
};

extern "C" int func_ov048_02262cc0(UnkStruct_02262cc0_3 *obj)
{
    void *a;
    void *b;
    Res *r;

    a = func_020a13d0();
    b = func_020984fc((void *) a);
    if (DWCi_GsMalloc(a) == 0) {
        r = (Res *) func_020682e0(0);
        obj->sub.v2();
        func_020a8164(&obj->sub, data_ov048_02263d20);
        obj->unk_676 = 0x67;
        func_02068340(r, &obj->sub);
        {
            Pair pr;
            func_02094fd4(&pr.loc);
            func_02095074(func_02099870(b), &pr.loc);
            func_02068404(r, 1, &pr.loc);
            r->unk_08 = 1;
            func_02094fbc(&pr.loc);
        }
        return 1;
    }
    return 0;
}
