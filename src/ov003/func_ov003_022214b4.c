/* func_ov003_022214b4 @ 0x022214b4, 0x494 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int m[12];
} Mtx;

typedef struct {
    volatile u16 id;
    u16 pad_02;
    Vec3 unk_04;
    Vec3 unk_10;
    Vec3 unk_1C;
    Vec3 unk_28;
    Vec3 unk_34;
    Vec3 unk_40;
    Vec3 unk_4C;
} Draw;

extern Mtx data_021fbe48;
extern void *data_ov003_0223cf70;

extern void func_01ffd070(Vec3 *out, void *a, void *b);
extern int func_0203f8d0(Vec3 *a, Vec3 *b);
extern void func_020e96c8(Mtx *m, int x, int y, int z);
extern void func_020e9774(Mtx *m, int a);
extern void func_020e9838(Mtx *m, int x, int y, int z);
extern void func_ov003_02225da0(void *g, int id, Vec3 *a, int s, Vec3 *b, int p, int q, int r);
extern void func_ov003_02225404(void *g, Draw *d, Mtx m);
extern void func_ov003_02225598(void *g, Draw *d, Mtx m);
extern void func_ov003_02225538(void *g, Draw *d, Mtx m);
extern void func_ov003_02225474(void *g, Draw *d, Mtx m);
extern void func_ov003_022252fc(void *g, Draw *d, Mtx m);
extern void func_ov003_02225608(void *g, Draw *d, Mtx m);
extern void func_ov003_02225768(void *g, Draw *d, int a, int b, Vec3 *v, Mtx m);
extern void func_ov003_02225694(void *g, Draw *d, int a, int b, Mtx m);
extern void func_ov003_022253a8(void *g, Draw *d, Mtx m);
extern void func_ov003_02225240(void *g, Draw *d, Mtx m);
extern void func_ov003_022251e8(void *g, Draw *d, Mtx m);

void func_ov003_022214b4(char *e)
{
    int dd, cc, bb, aa;
    Draw d;
    int t;
    int f1;
    u16 lo;
    Draw *pd;
    u16 kk;
    int i;
    int f4;
    int r;
    Vec3 *q;
    int a10, a14, b10, b14;

    d.id = 0xfff1;
    i = 0;
    do {
        if (*(int *) (e + 4) == 0) {
            goto L_next;
        }
        if (*(u16 *) (e + 8) == 0xfff1) {
            goto L_next;
        }
        func_01ffd070(&d.unk_28, e + 0x18, e + 0x24);
        d.unk_10.x = d.unk_28.x;
        d.unk_10.y = d.unk_28.y;
        d.unk_10.z = d.unk_28.z;
        d.id = *(u16 *) (e + 8);
        t = (d.id & 0xf000) >> 12;
        switch (t) {
            case 1:
            case 3:
            case 4:
                d.unk_34.x = d.unk_10.x;
                d.unk_34.y = d.unk_10.y;
                d.unk_34.z = d.unk_10.z;
                d.unk_40.x = 0x1000;
                d.unk_40.y = 0x1000;
                d.unk_40.z = 0x1000;
                func_ov003_02225da0(data_ov003_0223cf70, *(u16 *) (e + 8), &d.unk_34, *(short *) (e + 0x52), &d.unk_40, 0, 0,
                                    0);
                goto L_next;
        }
        q = (Vec3 *) (e + 0x3c);
        d.unk_1C.x = q->x;
        d.unk_1C.y = q->y;
        d.unk_1C.z = q->z;
        r = func_0203f8d0(&d.unk_04, &d.unk_10);
        func_020e96c8(&data_021fbe48, d.unk_04.x, d.unk_04.y, d.unk_04.z);
        func_020e9774(&data_021fbe48, r);
        func_020e9838(&data_021fbe48, d.unk_1C.x, d.unk_1C.y, d.unk_1C.z);
        f1 = 0;
        lo = d.id;
        pd = &d;
        if (pd->id >= 0x21 && lo <= 0x24) {
            f1 = 1;
        }
        if (f1 == 0) {
            if (!(lo >= 0x1f && lo <= 0x20)) {
                goto L2;
            }
        }
        func_ov003_02225404(data_ov003_0223cf70, &d, data_021fbe48);
        goto L_next;
    L2:
        dd = 1;
        cc = 1;
        bb = 1;
        aa = 0;
        if (lo <= 5) {
            aa = 1;
        }
        if (aa == 0) {
            if (!(lo >= 6 && lo <= 0xb)) {
                bb = 0;
            }
        }
        if (bb == 0) {
            if (!(lo >= 0xc && lo <= 0x11)) {
                cc = 0;
            }
        }
        if (cc == 0) {
            if (!((lo >= 0x12 && lo <= 0x19) || lo == 0x1c)) {
                dd = 0;
            }
        }
        if (dd == 0) {
            if (!((lo >= 0x8a && lo <= 0x8f) || (lo >= 0x90 && lo <= 0x95) || (lo >= 0x96 && lo <= 0x9b) ||
                  (lo >= 0x9c && lo <= 0xa3) || lo == 0xa5)) {
                goto L3;
            }
        }
        func_ov003_02225598(data_ov003_0223cf70, &d, data_021fbe48);
        goto L_next;
    L3:
        if (!((lo >= 0x6e && lo <= 0x73) || (lo >= 0x74 && lo <= 0x79) || (lo >= 0x7a && lo <= 0x7f) ||
              (lo >= 0x80 && lo <= 0x87))) {
            goto L4;
        }
        func_ov003_02225538(data_ov003_0223cf70, &d, data_021fbe48);
        goto L_next;
    L4:
        f4 = 0;
        kk = (u16) (lo + 0xffe6);
        if (kk <= 4) {
            if ((1 << kk) & 0x1b) {
                f4 = 1;
            }
        }
        if (f4 == 0) {
            if (lo != 0x88) {
                if (lo != 0x89) {
                    goto L5;
                }
            }
        }
        func_ov003_02225474(data_ov003_0223cf70, &d, data_021fbe48);
        goto L_next;
    L5:
        if (!(lo >= 0xfc && lo <= 0xfd)) {
            goto L6;
        }
        func_ov003_022252fc(data_ov003_0223cf70, &d, data_021fbe48);
        goto L_next;
    L6:
        if (!((lo >= 0x2b && lo <= 0x2e) || (lo >= 0xff && lo <= 0x102) || (lo >= 0x62 && lo <= 0x65) ||
              (lo >= 0xd0 && lo <= 0xd3))) {
            goto L7;
        }
        func_ov003_02225608(data_ov003_0223cf70, &d, data_021fbe48);
        goto L_next;
    L7:
        if (!((lo >= 0x26 && lo <= 0x2a) || (lo >= 0x5d && lo <= 0x61) || (lo >= 0x2f && lo <= 0x56) ||
              (lo >= 0x57 && lo <= 0x5b) || (lo >= 0x66 && lo <= 0x68) || lo == 0x69 || (lo >= 0x6a && lo <= 0x6c) ||
              lo == 0x6d || (lo >= 0xc8 && lo <= 0xcf))) {
            goto L8;
        }
        d.unk_4C.x = d.unk_10.x;
        d.unk_4C.y = d.unk_10.y;
        d.unk_4C.z = d.unk_10.z;
        a10 = *(int *) (e + 0x10);
        a14 = *(int *) (e + 0x14);
        func_ov003_02225768(data_ov003_0223cf70, &d, a10, a14, &d.unk_4C, data_021fbe48);
        goto L_next;
    L8:
        if (lo != 0x25 && lo != 0x5c && lo != 0xc7) {
            goto L9;
        }
        b10 = *(int *) (e + 0x10);
        b14 = *(int *) (e + 0x14);
        func_ov003_02225694(data_ov003_0223cf70, &d, b10, b14, data_021fbe48);
        goto L_next;
    L9:
        if (!((lo >= 0xe3 && lo <= 0xe7) || (lo >= 0xe8 && lo <= 0xfb))) {
            goto L10;
        }
        func_ov003_022253a8(data_ov003_0223cf70, &d, data_021fbe48);
        goto L_next;
    L10:
        if (!((lo >= 0xd4 && lo <= 0xda) || (lo >= 0xdb && lo <= 0xe1))) {
            goto L11;
        }
        func_ov003_02225240(data_ov003_0223cf70, &d, data_021fbe48);
        goto L_next;
    L11:
        if (lo >= 0xa7 && lo <= 0xc6) {
            func_ov003_022251e8(data_ov003_0223cf70, &d, data_021fbe48);
        }
    L_next:
        e += 0xa4;
        i++;
    } while (i < 0x14);
}
