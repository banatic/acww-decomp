/* shops_3: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020adb70 @ 0x020adb70, 0x238 bytes, Thumb
 * func_020adb24 @ 0x020adb24, 0x4c bytes, Thumb
 * func_020ada48 @ 0x020ada48, 0xdc bytes, Thumb
 * func_020ada40 @ 0x020ada40, 0x8 bytes, Thumb
 * func_020ada14 @ 0x020ada14, 0x2c bytes, Thumb
 * func_020ad944 @ 0x020ad944, 0xd0 bytes, Thumb
 * func_020ad8f8 @ 0x020ad8f8, 0x4c bytes, Thumb
 * func_020ad8f0 @ 0x020ad8f0, 0x8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u32 b0 : 6;
    u32 b6 : 19;
    u32 b25 : 1;
    u32 b26 : 6;
} BF;

typedef struct {
    u8 b;
    u16 w;
} UnkStruct_020ad944;

extern void func_020af750(void *, int, int);
extern int func_02073d90(int);
extern u16 *func_020af854(void *, int, int);
extern u16 *func_020ae8e4(void *, int, int);
extern u16 *func_020adfa4(void *, int, int);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);
extern int func_020af674(void *, int, int, int);
extern int func_020984e8(void);
extern int func_020996a0(int);
extern unsigned short *func_020adf50(void *record);
extern void func_020ade0c(int, int);
extern int func_ov004_0224627c(int *, int *, int);
extern void func_020afe94(int, int, int, int);
extern int func_020ae850(void *, u16 *);
extern void func_020afdc8(u16 *, int, int);
extern int func_020adfc0(void *, u16 *);
extern void func_02073820(int);
extern void func_020737f0(int, void *, int);
extern void func_02073770(int, int, int);
extern char data_021f395c[];
extern char data_021f3b44[];
extern char data_021f3b30[];
extern u16 data_021f49f4;
extern int data_020ccf94;
extern u8 data_020e54a8;
extern int func_02094ffc(void *);
extern int func_020b65c4(void);
extern unsigned short *func_ov004_02246378(int, int);
extern int func_020af83c(void *, volatile unsigned short *);
extern int func_ov004_0224632c(void *, void *);
extern void *func_02099870(void *);
extern void func_020b0200(void *);
extern unsigned char data_021f49ec[];
extern int func_020afc5c(void);
extern int func_0209782c(void);
extern void func_02061e2c(void *d, void *s);
extern void *func_02062f90(void *d, void *s);
extern int func_0203d7c4(int x, void *p);
extern void func_02066694(void *p);
extern u8 func_020af028(void *p);
extern void *func_0204c7f0(void *p);
extern int func_020979f0(void *p, int x);
extern void func_02066688(void *p);
extern void *func_02062f4c(void *p);
extern void func_02066024(void *a, void *b, void *c, void *d, void *e, void *f);
extern unsigned short func_02065ed0(void *p, u16 v, int x);
extern u8 data_020e4158;
extern u8 data_020e4180;
extern u8 data_020e415c;
extern unsigned short *func_ov004_022460c8(int, int);
extern int func_020ae8cc(void *p, unsigned short *q);

void func_020adb70(int a, int b, int c, int d, int mode, u8 f6, int g7)
{
    int t;
    u16 id;
    BF w1;
    int x;
    int y;
    BF w2;
    int ok;
    unsigned int k;
    int h;

    if (a == 0x3f) {
        func_020af750(data_021f395c, b, d);
        if (func_02073d90(data_020ccf94) == 0) {
            return;
        }
        if (f6 == 0) {
            return;
        }
        w1.b0 = a;
        w1.b6 = b;
        w1.b25 = d;
        w1.b26 = c;
        h = data_020ccf94;
        func_02073820(h);
        func_020737f0(h, &w1, 4);
        func_02073770(h, 0x26, 4);
        return;
    }

    id = data_021f49f4;
    switch (mode) {
        case 0:
            id = *func_020af854(data_021f395c, a, 0);
            break;
        case 1:
            id = *func_020ae8e4(data_021f3b44, a, 0);
            break;
        case 2:
            id = *func_020adfa4(data_021f3b30, a, 0);
            break;
    }

    if (func_0204bcdc(&id) != 0) {
        t = func_0204bc64(&id);
        if (t == func_0204bc64(&data_021f49f4)) {
            ok = 1;
        } else {
            ok = 0;
        }
    } else {
        ok = (id == data_021f49f4) ? 1 : 0;
    }
    if (ok != 0) {
        return;
    }

    switch (mode) {
        case 0:
            func_020af674(data_021f395c, a, b, d);
            if (f6 != 0) {
                func_020ade0c((int) func_020adf50((void *) func_020996a0(func_020984e8())), b);
            }
            if (data_020e54a8 == 1) {
                k = 1;
            } else {
                k = 0;
            }
            if (k != 0) {
                if (func_ov004_0224627c(&x, &y, a) != 0) {
                    if (a == 0x3f) {
                        g7 = 0;
                    }
                    func_020afe94(x, y, c, g7);
                }
            }
            break;
        case 1:
            func_020ae850(data_021f3b44, &id);
            func_020afdc8(&id, c, g7);
            break;
        case 2:
            func_020adfc0(data_021f3b30, &id);
            func_020afdc8(&id, c, g7);
            break;
    }

    if (func_02073d90(data_020ccf94) == 0) {
        return;
    }
    if (f6 == 0) {
        return;
    }
    w2.b0 = a;
    w2.b6 = b;
    w2.b25 = d;
    w2.b26 = c;
    h = data_020ccf94;
    func_02073820(h);
    func_020737f0(h, &w2, 4);
    func_02073770(h, 0x26, 4);
}

void func_020adb24(int p)
{
    int flag;

    if (func_02094ffc((void *) (int) func_02099870((void *) ((int) func_020984e8())))) {
        flag = 0;
    } else {
        flag = 1;
    }
    if (p > 150000) {
        p = 150000;
    }
    func_020adb70(63, p, func_020b65c4(), flag, 0, 1, 0);
}

void func_020ada48(void *a0, void *a1, int a2, int a3)
{
    volatile unsigned short h[2];
    unsigned short v0, v1;
    unsigned int hit;
    int idx, flag;
    unsigned int i;

    h[0] = *func_ov004_02246378((int) a0, (int) a1);
    hit = 0;
    v0 = h[0];
    v1 = h[0];
    if (v1 >= 0x151d && v0 <= 0x151e) {
        hit = 1;
    }
    if (hit > 0 && func_020b65c4() == 0x1d) {
        h[1] = 0xfff1;
        for (i = 0; i < 0x25; i++) {
            func_020af854((void *) ((unsigned char *) data_021f395c), i, (int) (&h[1]));
            hit = 0;
            v0 = h[1];
            v1 = h[1];
            if (v1 >= 0x151d && v0 <= 0x151e) {
                hit = 1;
            }
            if (hit > 0) {
                break;
            }
        }
        idx = i + func_ov004_0224632c(a0, a1);
    } else {
        idx = func_020af83c((void *) ((unsigned char *) data_021f395c), &h[0]);
    }
    if (idx != -1) {
        flag = (func_02094ffc(func_02099870((void *) func_020984e8())) == 0) ? 1 : 0;
        func_020b0200((void *) data_021f49ec);
        func_020adb70(idx, a2, a3, flag, 0, 1, 0);
    }
}

int func_020ada40(void)
{
    return func_020afc5c();
}

int func_020ada14(void)
{
    if (func_02073d90(data_020ccf94) != 0) {
        return 0;
    }
    if (func_0209782c() != 0) {
        return 1;
    }
    return 0;
}

int func_020ad944(void *arg)
{
    UnkStruct_020ad944 s1;
    u8 s2[0x28];
    u8 buffer[0x100];
    u8 *gptr;
    void *v1;
    void *v2;
    void *v3;

    if (func_020ada14() != 0) {
        func_02061e2c(&s1.w, arg);
        func_02062f90(s2, &s1.w);
        func_0203d7c4(1, s2);

        v1 = (((void *) (func_02066694(buffer), buffer)), (void *) func_020984e8());
        gptr = ((u8 *) data_021f395c);
        s1.b = func_020af028(gptr);
        v2 = func_02099870(v1);
        func_02066024(buffer, &s1, &data_020e4180, &data_020e415c, &data_020e4158, v2);
        func_02065ed0(buffer, s1.w, 1);

        v1 = func_0204c7f0(&s1.w);

        if (func_020979f0(buffer, 0) != 0) {
            v3 = func_020adf50((void *) func_020996a0(
                (int) ((((void *) (func_020af750(gptr, (int) v1, 1), gptr)), (void *) func_020984e8()))));
            func_020ade0c((int) v3, (int) v1);
            func_02066688(buffer);
            func_02062f4c(s2);
            return 1;
        } else {
            func_02066688(buffer);
            func_02062f4c(s2);
        }
    }
    return 0;
}

void func_020ad8f8(int a, int b, int c)
{
    unsigned short tmp;
    int res;
    tmp = *func_ov004_022460c8(a, b);
    res = func_020ae8cc((void *) ((int *) data_021f3b44), &tmp);
    if (res != -1) {
        func_020b0200((void *) ((int *) data_021f49ec));
        func_020adb70(res, 0, c, 1, 1, 1, 0);
    }
}

int func_020ad8f0(void)
{
    return func_020afc5c();
}
