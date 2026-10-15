/* func_020a1038 @ 0x020a1038, 0x180 bytes, Thumb, module main
 * mwccarm 1.2/base -O2,s
 */

#include "types.h"

typedef struct {
    u16 v;
} UnkStruct_020a1038;

typedef struct {
    u8 pad_00[0x68];
    int unk_68;
} UnkStruct_020a1038_2;

extern void func_0207428c(void);
extern int func_0209ffb0(void *a);
extern void func_02096294(int a);
extern void func_020738f4(UnkStruct_020a1038_2 *g, int a);
extern void func_020962a4(int a, int b);
extern int func_02096284(int a);
extern void *func_0209847c(int a);
extern void func_02099a38(void *p);
extern void func_0209dfa4(int a);
extern void func_0209e6ec(void *p, int a);
extern void func_0209e604(void *p);
extern void *func_0204e414(void);
extern void func_0204e4bc(void *p);
extern void func_0204e42c(void *p);
extern void func_0204d0ac(void *p);
extern void func_0204de34(void);
extern void func_0204dde0(void);
extern void func_02046830(void);
extern void func_02075104(int a);
extern u8 *func_0209626c(void);
extern void func_0209e474(void *p);
extern u16 *func_0209627c(void);
extern void func_02099794(void *p, UnkStruct_020a1038 w);

extern UnkStruct_020a1038_2 *data_020ccf94;
extern int data_021dc7a8;

void func_020a1038(void *a0, int a1, int a2)
{
    UnkStruct_020a1038 w;
    unsigned int rec[2];
    UnkStruct_020a1038_2 *g;
    int x;
    int i;
    int j;
    void *p;
    void *obj;
    u8 *pf;
    int k;

    func_0207428c();
    func_0209ffb0(a0);
    if (a1 < 7) {
        g = data_020ccf94;
        func_02096294(g->unk_68);
        g->unk_68 = 0;
    }
    g = data_020ccf94;
    func_020738f4(g, 1);
    if (a1 < 7) {
        func_020962a4(g->unk_68, a1);
    }
    x = g->unk_68;
    func_02096284(x);
    i = 3;
    do {
        if (i != x) {
            func_02096294(i);
        }
        i--;
    } while (i >= 0);
    j = 2;
    do {
        p = func_0209847c(j + 4);
        if (p != 0) {
            func_02099a38(p);
        }
        j--;
    } while (j >= 0);
    if (a2 == 0) {
        func_0209dfa4(0);
        func_0209e6ec(&data_021dc7a8, 2);
        func_0209e604(&data_021dc7a8);
        if (func_0204e414() != 0) {
            func_0204e4bc(func_0204e414());
            func_0204e42c(func_0204e414());
            func_0204d0ac(func_0204e414());
        }
        func_0204de34();
        func_0204dde0();
    } else {
        func_02046830();
    }
    func_02075104(-4);
    if (a2 != 0) {
        return;
    }
    k = func_02096284(0);
    if (k >= 7) {
        return;
    }
    obj = func_0209847c(k);
    pf = func_0209626c();
    if ((*pf & 6) != 0) {
        rec[0] = 0;
        rec[1] = 0;
        func_0209e474(rec);
        w.v = (w.v & ~0x7f) | (((u8 *) rec)[5] & 0x7f);
        w.v = (w.v & 0xfffff87f) | ((((u8 *) rec)[4] & 0xf) << 7);
        w.v = (w.v & 0xffff07ff) | ((((u8 *) rec)[3] & 0x1f) << 11);
        if ((*pf & 2) != 0) {
            *pf |= 0x11;
        }
    } else {
        w.v = *func_0209627c();
        *pf = *pf | ((*pf >> 4) & 1);
    }
    func_02099794(obj, w);
}
