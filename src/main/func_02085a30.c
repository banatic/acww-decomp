/* func_02085a30 @ 0x02085a30, 0x1b0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02085a30_4 {
    u8 unk_00;
    u8 unk_01[2];
    u8 unk_03;
    u8 unk_04[5];
    u8 unk_09[0x15];
} UnkStruct_02085a30_4;
typedef struct UnkStruct_02085a30 {
    u8 unk_00;
    u8 pad_01;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
} UnkStruct_02085a30;
typedef struct UnkStruct_02085a30_2 {
    int a, b;
} UnkStruct_02085a30_2;
typedef struct UnkStruct_02085a30_3 {
    UnkStruct_02085a30_2 p;
    int c;
} UnkStruct_02085a30_3;

extern int data_021e5a2c;
extern UnkStruct_02085a30_4 data_021d213c[];

extern int func_02082240(void);
extern void *func_0207cec0(int *, int);
extern void *func_0208150c(void *);
extern int func_02003704(void *);
extern int func_0207c72c(int *, void *);
extern UnkStruct_02085a30_4 *func_020852e4(u16 *);
extern void func_02077a34(u8 *, UnkStruct_02085a30 *, int);
extern int func_020b65c4(void);
extern void func_02077978(u8 *, UnkStruct_02085a30_2 *, int *);
extern void MI_CpuCopy8(u8 *, u16 *, int);
extern u8 *func_020800d0(void *);
extern void func_0204f794(UnkStruct_02085a30_2 *, int, int);
extern int func_020a7278(void);
extern int func_020b6674(int);
extern int func_020b6654(int);
extern void func_02085be0(void *, UnkStruct_02085a30_2 *);
extern int func_02003348(int, int, UnkStruct_02085a30_2 *, u16 *, int);

void func_02085a30(int p0)
{
    int lim;
    int cnt;
    int t;
    UnkStruct_02085a30 w;
    UnkStruct_02085a30_3 m;
    int i;
    void *e;
    UnkStruct_02085a30_4 *q;
    u8 *p;

    w.unk_02 = 0xfff1;
    w.unk_04 = 0;
    w.unk_06 = 0;
    w.unk_08 = 0;
    lim = func_02082240();
    cnt = 0;
    w.unk_00 = 0;
    if (lim <= 0) {
        return;
    }
    for (i = 0; i < 8 && cnt < lim; i++) {
        e = func_0207cec0(&data_021e5a2c, i);
        if (e == 0) {
            continue;
        }
        if (func_02003704(func_0208150c(e)) == 0) {
            continue;
        }
        if (func_0207c72c(&data_021e5a2c, func_0208150c(e)) == 0) {
            continue;
        }
        w.unk_00 = 0;
        m.p.a = 0;
        m.p.b = 0;
        m.c = 0;
        w.unk_04 = 0;
        w.unk_06 = 0;
        w.unk_08 = 0;
        w.unk_02 = (u16) ((i & 0xfff) | 0xe000);
        q = func_020852e4(&w.unk_02);
        if (q != 0 && q->unk_00 != 0) {
            func_02077a34(&q->unk_03, &w, 0);
            if (w.unk_00 == func_020b65c4()) {
                func_02077978(q->unk_04, &m.p, &m.c);
                MI_CpuCopy8(q->unk_09, &w.unk_06, 2);
            } else {
                p = func_020800d0(e);
                func_0204f794(&m.p, p[0] + 1, p[1] + 2);
            }
        } else if (func_020a7278() != 0 && data_021d213c[i].unk_00 != 0) {
            q = &data_021d213c[i];
            func_02077a34(&q->unk_03, &w, 0);
            t = w.unk_00;
            if (t != func_020b65c4() && func_020b6674(t) == 0 && func_020b6654(w.unk_00) == 0 && w.unk_00 != 0x2c) {
                p = func_020800d0(e);
                func_0204f794(&m.p, p[0] + 1, p[1] + 2);
            } else {
                func_02077978(q->unk_04, &m.p, &m.c);
                func_02085be0(e, &m.p);
            }
        } else {
            p = func_020800d0(e);
            func_0204f794(&m.p, p[0] + 1, p[1] + 2);
        }
        if (func_02003348(0x84, w.unk_02, &m.p, &w.unk_04, p0) != 0) {
            cnt++;
        }
    }
}
