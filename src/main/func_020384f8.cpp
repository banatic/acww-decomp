/* func_020384f8 @ 0x020384f8, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/helper_ctors.h"

struct UnkStruct_020384f8 {
    char pad_00[0x10];
    int unk_10;
    char pad_14[0x14];
    void *unk_28;
    int unk_2C;
    int unk_30;
    char pad_34[4];
    unsigned char unk_38;
    unsigned char unk_39;
    char pad_3A[0x16];
    int unk_50;
    unsigned char unk_54;
    unsigned char unk_55;
    unsigned char unk_56;
    char pad_57;
    int unk_58;
};

struct Loc {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
    char pad_04[0x3c];
};

// Same layout as Loc; built and torn down by its out-of-line pair.
struct LocBuf {
    void *vtbl;
    char pad_04[0x3c];
};

extern "C" {
extern int func_020b45d0(Loc *, void *, int, int, int, int);
extern unsigned int func_020a8f74(Loc *);
extern UnkStruct_020384f8 *func_020a8fe8(void *, int, int);
extern void func_02051694(UnkStruct_020384f8 *);
extern void func_020a8fb8(UnkStruct_020384f8 *);
extern char data_021c8230;
}

struct UnkStruct_020384f8_2 {
    char pad_00[0xe0];
    int unk_E0;
    void *unk_E4;
};

extern "C" void func_020384f8(UnkStruct_020384f8_2 *a, void *b, int c)
{
    LocBuf loc;
    Loc *lp;
    unsigned int w;
    unsigned int k;
    int x;
    UnkStruct_020384f8 *p;

    func_020b5630(&loc);
    func_020b45d0((Loc *) &loc, a->unk_E4, 2, 0, 0, 0);
    w = func_020a8f74((Loc *) &loc);
    if (w < 0x12) {
        k = (0x12 - w) / 2;
    } else {
        k = 0;
    }
    x = k + (c + a->unk_E0);
    p = func_020a8fe8(b, 0x20, 2);
    if (p != 0) {
        p->unk_2C = 5;
        lp = (Loc *) &loc;
        p->unk_10 = lp->v3();
        p->unk_58 = 2;
        p->unk_50 = 0;
        p->unk_28 = &data_021c8230;
        p->unk_55 = 0;
        p->unk_30 = x;
        p->unk_39 = 1;
        p->unk_38 = 0;
        p->unk_56 = 1;
        func_02051694(p);
        func_020a8fb8(p);
    }
    func_020b5618(&loc);
}
