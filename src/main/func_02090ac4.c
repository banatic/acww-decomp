/* func_02090ac4 @ 0x02090ac4, 0x168 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02090ac4 {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
} UnkStruct_02090ac4;

typedef struct Node {
    u8 pad_00[4];
    UnkStruct_02090ac4 unk_04;
    u8 unk_08;
    u8 unk_09;
    u8 pad_0A[0x10 - 0xa];
    void (*fns[1])(struct Node *);
} Node;

typedef struct UnkStruct_02090ac4_3 {
    u32 b0 : 1;
    u32 rest : 31;
    void **unk_04;
    int unk_08;
} UnkStruct_02090ac4_3;

typedef struct UnkStruct_02090ac4_2 {
    u8 pad_00[0x54];
    int unk_54;
} UnkStruct_02090ac4_2;

extern UnkStruct_02090ac4_2 *data_021d52c4;
extern void *data_021d52d4;
extern UnkStruct_02090ac4_3 data_020d0f88[];

extern void MIi_CpuClear32(u32 v, void *dst, u32 size);
extern Node *func_02090930(void *base, void *a);
extern Node *func_020908a0(void *base, void *a, void *p1, short *p2, void *p3, int t, int i);
extern void func_02090a2c(void *p);

int func_02090ac4(int idx, void *p1, short *p2, u8 *p3)
{
    void *base;
    int cnt;
    int ok;
    int zero2;
    UnkStruct_02090ac4 bufA;
    UnkStruct_02090ac4 bufB;
    UnkStruct_02090ac4 bufC;
    volatile int zero;
    void *arr[10];
    UnkStruct_02090ac4_3 *e;
    void **w;
    Node *n;
    int i;
    int j;
    void (**pf)(Node *);

    ok = 1;
    zero = 0;
    MIi_CpuClear32(zero, arr, 0x28);
    if (p1 == 0) {
        return 0;
    }
    base = data_021d52c4;
    base = (u8 *) base + 0x58;
    e = &data_020d0f88[idx];
    cnt = e->unk_08;
    w = e->unk_04;
    if (p2 != 0) {
        if (e->b0 == 1) {
            cnt = cnt >> 1;
            if (p2[0] >= 0) {
                w = w + cnt;
            }
        }
    }
    data_021d52d4 = p1;
    i = 0;
    zero2 = 0;
    goto test;
body:
    n = func_02090930(base, *w);
    if (n != 0) {
        n->unk_08 = 1;
        n->unk_09 = (u8) i;
        bufB = n->unk_04;
        bufA.a = bufB.a;
        bufA.b = bufB.b;
        bufA.c = bufB.c;
        bufA.d = bufB.d;
        bufA.b = (u8) data_021d52c4->unk_54;
        bufA.c = (u8) i;
        bufC = bufA;
        n->unk_04.a = bufC.a;
        n->unk_04.b = bufC.b;
        n->unk_04.c = bufC.c;
        n->unk_04.d = bufC.d;
        pf = n->fns;
        if (pf != 0) {
            pf[0](n);
        }
    } else {
        n = func_020908a0(base, *w, p1, p2, p3, data_021d52c4->unk_54, i);
        if (n == 0) {
            ok = zero2;
        }
    }
    if (ok == 0) {
        j = 0;
        goto jtest;
    jbody:
        func_02090a2c(arr[j]);
        j++;
    jtest:
        if (j < i) {
            goto jbody;
        }
        goto done;
    }
    arr[i] = n;
    w = w + 1;
    p3 = p3 + 8;
    i++;
test:
    if (i < cnt) {
        goto body;
    }
done:
    data_021d52d4 = 0;
    data_021d52c4->unk_54 = data_021d52c4->unk_54 + 1;
    return ok;
}
