/* room_shell_5: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02232f24 @ 0x02232f24, 0x68 bytes, Thumb
 * func_ov004_02232edc @ 0x02232edc, 0x48 bytes, Thumb
 * func_ov004_02232c48 @ 0x02232c48, 0x294 bytes, Thumb
 * func_ov004_02232b48 @ 0x02232b48, 0x100 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02232b48 {
    char pad_00[0x20];
    int unk_20;
};

struct UnkStruct_02232b48_2 {
    char pad_00[0x20];
    struct UnkStruct_02232b48 *unk_20;
};

struct UnkStruct_02232b48_3 {
    struct UnkStruct_02232b48_2 *unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
};

extern void func_02004280(void *);
extern int func_02055f1c(void *);
extern void func_ov004_0223226c(void *object);
extern int func_ov004_02232314(void *);
extern int func_ov004_022323b0(void *);
extern void func_ov004_02232508(void *);
extern void func_ov004_02232794(void *);
extern void *data_ov004_022589fc;
extern int func_02034240(void *, int, int, int, int);
extern int func_020341c8(void *, int);
extern void func_0203423c(void *);
extern u8 func_020b65c4(void);
extern int func_020b67e8(int);
extern int func_020b6818(int);
extern int func_02060ee0(void *, int);
extern u16 *func_02061204(int, int *);
extern u16 *func_020611e8(int, int *);
extern int func_020b6694(int);
extern int func_020b66c4(int);
extern u8 *func_0207cec0(void *, int);
extern u8 func_0207f30c(u8 *);
extern u8 func_0207f300(u8 *);
extern int func_020b6744(int);
extern int func_020b6774(int);
extern u16 *func_020349e8(int);
extern u16 *func_020349b8(int);
extern void __register_global_object(u16 *, void *destructor, void *);
extern void func_020051b0(void *object);
extern char data_021ebcd4[];
extern char data_021e5a2c[];
extern int data_ov004_022589f4;
extern int data_ov004_022589f8;
extern u16 data_ov004_02258a6c[6];
extern u16 data_ov004_02258a18[6];
extern char data_ov004_02258ac0;
extern char data_ov004_02258ab4;
extern char data_ov004_02258a0c;
extern char data_ov004_02258a9c;
extern char data_ov004_02258a90;
extern char data_ov004_02258a60;
extern char data_ov004_02258a78;
extern char data_ov004_02258aa8;
extern char data_ov004_02258acc;
extern char data_ov004_02258a3c;
extern char data_ov004_02258a00;
extern char data_ov004_02258a24;
extern struct UnkStruct_02232b48_3 *data_021c80bc;
extern int func_ov004_02232980(void *a, int b, int c);
extern int func_ov004_022326f4(void *a, int b, int c);
extern int func_ov004_02232968(void *a, int b, int c, int d);
extern int func_ov004_022326dc(void *a, int b, int c, int d);
extern int func_ov004_022327a0(void *a, volatile u16 *b, int c, int d);
extern int func_ov004_02232514(void *a, volatile u16 *b, int c, int d);

int func_ov004_02232f24(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02232794(self + 0x128);
    func_ov004_0223226c(self + 0x34fc);
    func_ov004_02232314(self + 0x3460);
    func_ov004_02232508(self + 0x1228);
    func_ov004_022323b0(self + 0x3328);
    func_02055f1c(self + 0x50);
    *(void **) ((char *) &data_ov004_022589fc) = 0x0;
    func_02004280(self + 0x3534);
    return 0x1;
}

void func_ov004_02232edc(char *self)
{
    char buf[0x44];
    int n = 0;
    int i;
    int f = 0;
    for (i = 0; i < 0x10; i++) {
        func_02034240(buf, i, 0xa, 0, 0);
        if (func_020341c8(buf, f) == 0) {
            n++;
        }
        func_0203423c(buf);
    }
    self[0x3522] = n;
}

void func_ov004_02232c48(char *self, u16 *wall, int *outA, u16 *floor, int *outB)
{
    int k = func_020b65c4();
    *outB = 0;
    *outA = *outB;
    if (func_020b67e8(k) != 0) {
        int idx = func_02060ee0(data_021ebcd4, func_020b6818(k));
        if (idx == 0) {
            return;
        }
        *wall = *func_02061204(idx, outA);
        *floor = *func_020611e8(idx, outB);
        return;
    }
    if (func_020b6694(k) != 0) {
        u8 *p = func_0207cec0(data_021e5a2c, func_020b66c4(k));
        u8 a, b;
        if (p == 0) {
            return;
        }
        a = func_0207f30c(p);
        *wall = (a < 0x44) ? (u16) (a + 0x1100) : 0x1100;
        b = func_0207f300(p);
        *floor = (b < 0x44) ? (u16) (b + 0x1144) : 0x1144;
        return;
    }
    if (func_020b6744(k) == 0) {
        return;
    }
    {
        int slot = func_020b6774(k);
        u16 *pw = func_020349e8(k);
        int ok = 0;
        u16 w = *pw;
        u16 *pf;
        int ok2;
        u16 f;
        if (w >= 0x1100 && w <= 0x1143) {
            ok = 1;
        }
        if (ok != 0) {
            *wall = w;
        } else {
            if ((data_ov004_022589f4 & 1) == 0) {
                data_ov004_02258a6c[0] = 0x1140;
                __register_global_object(&data_ov004_02258a6c[0], ((void *) &func_020051b0), &data_ov004_02258ac0);
                data_ov004_02258a6c[1] = 0x1141;
                __register_global_object(&data_ov004_02258a6c[1], ((void *) &func_020051b0), &data_ov004_02258ab4);
                data_ov004_02258a6c[2] = 0x1142;
                __register_global_object(&data_ov004_02258a6c[2], ((void *) &func_020051b0), &data_ov004_02258a0c);
                data_ov004_02258a6c[3] = 0x1143;
                __register_global_object(&data_ov004_02258a6c[3], ((void *) &func_020051b0), &data_ov004_02258a9c);
                data_ov004_02258a6c[4] = 0x1143;
                __register_global_object(&data_ov004_02258a6c[4], ((void *) &func_020051b0), &data_ov004_02258a90);
                data_ov004_02258a6c[5] = 0x1143;
                __register_global_object(&data_ov004_02258a6c[5], ((void *) &func_020051b0), &data_ov004_02258a60);
                data_ov004_022589f4 |= 1;
            }
            *wall = data_ov004_02258a6c[slot];
        }
        pf = func_020349b8(k);
        ok2 = 0;
        f = *pf;
        if (f >= 0x1144 && f <= 0x1187) {
            ok2 = 1;
        }
        if (ok2 != 0) {
            *floor = f;
        } else {
            if ((data_ov004_022589f8 & 1) == 0) {
                data_ov004_02258a18[0] = 0x1184;
                __register_global_object(&data_ov004_02258a18[0], ((void *) &func_020051b0), &data_ov004_02258a78);
                data_ov004_02258a18[1] = 0x1185;
                __register_global_object(&data_ov004_02258a18[1], ((void *) &func_020051b0), &data_ov004_02258aa8);
                data_ov004_02258a18[2] = 0x1186;
                __register_global_object(&data_ov004_02258a18[2], ((void *) &func_020051b0), &data_ov004_02258acc);
                data_ov004_02258a18[3] = 0x1187;
                __register_global_object(&data_ov004_02258a18[3], ((void *) &func_020051b0), &data_ov004_02258a3c);
                data_ov004_02258a18[4] = 0x1187;
                __register_global_object(&data_ov004_02258a18[4], ((void *) &func_020051b0), &data_ov004_02258a00);
                data_ov004_02258a18[5] = 0x1187;
                __register_global_object(&data_ov004_02258a18[5], ((void *) &func_020051b0), &data_ov004_02258a24);
                data_ov004_022589f8 |= 1;
            }
            *floor = data_ov004_02258a18[slot];
        }
    }
}

static __inline int atleast(unsigned int x, unsigned int n)
{
    return x > n;
}

static __inline struct UnkStruct_02232b48_2 *get(void)
{
    struct UnkStruct_02232b48_3 *g = data_021c80bc;

    if (!atleast(g->unk_04, 0) || !atleast(g->unk_08, 0) || g->unk_00 == 0) {
        return 0;
    }
    return g->unk_00;
}

void func_ov004_02232b48(char *self)
{
    // DECLS
    int ok;
    unsigned int lo;
    unsigned int hi;
    struct UnkStruct_02232b48 *r;
    // ENDDECLS
    volatile u16 buf[2];
    int v8;
    int v12;

    r = get()->unk_20;
    func_ov004_02232980(self + 0x128, *(int *) (self + 0xac), r->unk_20);
    func_ov004_022326f4(self + 0x1228, *(int *) (self + 0xac), r->unk_20);
    buf[0] = 0xfff1;
    buf[1] = 0xfff1;
    func_ov004_02232c48((char *) self, (u16 *) (&buf[0]), &v8, (u16 *) (&buf[1]), &v12);

    ok = 0;
    lo = buf[0];
    hi = buf[0];
    if (hi >= 0x1188 && lo <= 0x11a7) {
        ok = 1;
    }
    if (ok != 0) {
        func_ov004_02232968(self + 0x128, 0x1124, *(int *) (self + 0xac), v8);
    }
    ok = 0;
    lo = buf[1];
    hi = buf[1];
    if (hi >= 0x1188 && lo <= 0x11a7) {
        ok = 1;
    }
    if (ok != 0) {
        func_ov004_022326dc(self + 0x1228, 0x1182, *(int *) (self + 0xac), v12);
    }
    func_ov004_022327a0(self + 0x128, &buf[0], *(int *) (self + 0xac), v8);
    func_ov004_02232514(self + 0x1228, &buf[1], *(int *) (self + 0xac), v12);
}
