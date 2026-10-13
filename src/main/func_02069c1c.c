/* func_02069c1c @ 0x02069c1c, 0x108 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02069c1c {
    u8 pad_00[0xb4];
    int q;
};

struct UnkStruct_02069c1c_2 {
    u8 pad_00[0x24];
    struct UnkStruct_02069c1c *unk_24;
    u8 pad_28[8];
    int unk_30;
    u8 pad_34[4];
    int unk_38;
    u8 pad_3C[0xc];
    int unk_48;
    u8 pad_4C[0x8c];
    u8 unk_D8;
};

extern void *func_0206837c(struct UnkStruct_02069c1c *);
extern int func_020ab550(void *, int);
extern int func_020ab5e4(void *);
extern int func_020ab788(int);
extern int func_020ab794(int);
extern int func_020ab53c(void *);
extern int func_020ab528(void *);
extern int func_020a8370(int *, int, int, int, int, int, int, int, int, int, int);
extern void func_020a93e8(struct UnkStruct_02069c1c_2 *, int);
extern void func_020ab4bc(void *, int);
extern void func_020a9db0(int *, void *);
extern void func_020a9d24(int *);
extern void func_020a93dc(struct UnkStruct_02069c1c_2 *, int);
extern void func_020a9334(struct UnkStruct_02069c1c_2 *, void *);
extern u8 data_020cce98[];

void func_02069c1c(struct UnkStruct_02069c1c_2 *p)
{
    void *x;
    int v0, v1, v2, v3;
    int a, b, c, d, e, f, g, h, i, j;
    int k;

    if (p->unk_D8) {
        p->unk_D8 = 0;
        x = func_0206837c(p->unk_24);
        v0 = func_020ab550(x, 0);
        v1 = func_020ab550(x, 1);
        v2 = func_020ab550(x, 2);
        v3 = func_020ab550(x, 3);
        func_020ab5e4(x);
        a = func_020ab788(v0);
        b = func_020ab794(v0);
        c = func_020ab788(v1);
        d = func_020ab794(v1);
        e = func_020ab788(v2);
        f = func_020ab794(v2);
        g = func_020ab788(v3);
        h = func_020ab794(v3);
        i = func_020ab53c(x);
        j = func_020ab528(x);
        k = func_020a8370(&p->unk_38, a, b, c, d, e, f, g, h, i, j);
        func_020a93e8(p, k);
        func_020ab4bc(x, 4);
        func_020a9db0(&p->unk_24->q, x);
        func_020a9d24(&p->unk_24->q);
        p->unk_30 = 5;
    } else {
        func_020a93dc(p, p->unk_48);
        p->unk_D8 = 1;
        func_020a9334(p, data_020cce98);
    }
}
