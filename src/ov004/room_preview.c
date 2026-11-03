/* room_preview: 11 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223d2f8 @ 0x0223d2f8, 0x44 bytes, Thumb
 * func_ov004_0223d2d4 @ 0x0223d2d4, 0x24 bytes, Thumb
 * func_ov004_0223d2b0 @ 0x0223d2b0, 0x24 bytes, Thumb
 * func_ov004_0223d2ac @ 0x0223d2ac, 0x4 bytes, Thumb
 * func_ov004_0223d248 @ 0x0223d248, 0x64 bytes, Thumb
 * func_ov004_0223d200 @ 0x0223d200, 0x48 bytes, Thumb
 * func_ov004_0223d08c @ 0x0223d08c, 0x174 bytes, Thumb
 * func_ov004_0223d064 @ 0x0223d064, 0x28 bytes, Thumb
 * func_ov004_0223d054 @ 0x0223d054, 0xe bytes, Thumb
 * func_ov004_0223d044 @ 0x0223d044, 0xe bytes, Thumb
 * func_ov004_0223d03c @ 0x0223d03c, 0x8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[16];
    unsigned long unk_10;
} UnkStruct_0223d2ac;

typedef struct {
    unsigned char pad_00[0x14];
    void *unk_14;
    unsigned char p2[4];
    void *unk_1C;
} UnkStruct_0223d200;

extern void __cxa_vec_ctor();
extern void func_020051b0(void *arg0);
extern void func_02034ce0(unsigned short *arg0);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *data_021fbe94;
extern void *func_020e9948(void *h, int sz);
extern void *func_020ba294(void *object);
extern void *func_0203cbcc(void *object);
extern void func_020e993c(void *, void *);
extern void func_02061b1c(void *p, u16 *item, int k);
extern unsigned int func_0204bd5c(void *p);
extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern void func_020ee470(void *o);
extern int func_ov004_0223b540(int *out, void *p, int k);
extern int func_ov004_0223c660(int a);
extern char data_ov004_022596b0[];

void func_ov004_0223d2b0(char *self);

void *func_ov004_0223d2f8(char *self)
{
    // DECLS
    u32 i;
    // ENDDECLS
    __cxa_vec_ctor(self + 0x8, 0x2, 0x2, (void *) func_02034ce0, (void *) func_020051b0);
    func_ov004_0223d2b0(self);
    for (i = 0; i < 0x2; i++) {
        *(void **) (self + (i << 2) + 0x14) = 0x0;
        *(void **) (self + (i << 2) + 0x1c) = 0x0;
    }
    return self;
}

void *func_ov004_0223d2d4(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223d2b0((char *) self);
    __cxa_vec_cleanup(self + 0x8, 0x2, 0x2, ((void (*)(void *)) func_020051b0));
    return self;
}

void func_ov004_0223d2b0(char *self)
{
    // DECLS
    u32 i;
    // ENDDECLS
    for (i = 0; i < 0x2; i++) {
        *(void **) (self + (i << 2)) = 0x0;
        *(u16 *) (self + (i << 1) + 0x8) = 0xfff1;
        *(u8 *) (self + 0xc) = 0x0;
    }
}

unsigned long func_ov004_0223d2ac(UnkStruct_0223d2ac *p)
{
    return p->unk_10;
}

void func_ov004_0223d248(void *self)
{
    void *h = data_021fbe94;
    unsigned int i;
    void **p;
    void *x;

    for (i = 0; i < 2; i++) {
        p = (void **) ((char *) self + i * 4);
        if (p[5] == 0) {
            p[5] = func_020e9948(h, 0x10c4);
            x = p[5];
            if (x != 0) {
                x = func_020ba294(x);
            }
            p[5] = x;
        }
        if (p[7] == 0) {
            p[7] = func_020e9948(h, 0x20c4);
            x = p[7];
            if (x != 0) {
                x = func_0203cbcc(x);
            }
            p[7] = x;
        }
    }
}

void func_ov004_0223d200(char *self)
{
    void *h = data_021fbe94;
    void *z0 = 0, *z1 = 0;
    unsigned i;
    for (i = 0; i < 2; i++) {
        UnkStruct_0223d200 *e = (UnkStruct_0223d200 *) (self + i * 4);
        if (e->unk_14 != 0) {
            func_020e993c(h, e->unk_14);
            e->unk_14 = z0;
        }
        if (e->unk_1C != 0) {
            func_020e993c(h, e->unk_1C);
            e->unk_1C = z1;
        }
    }
}

static __inline int same(u16 *p, u16 *q)
{
    int t1;

    if (func_0204bcdc((void *) p) != 0) {
        t1 = func_0204bc64((void *) p);
        return (t1 == func_0204bc64((void *) q)) ? 1 : 0;
    }
    return (*p == *q) ? 1 : 0;
}

int func_ov004_0223d08c(void *self, u16 *item)
{
    // DECLS
    unsigned int f;
    unsigned int lo;
    unsigned int hi;
    unsigned int g;
    unsigned int iid;
    unsigned int n;
    unsigned int k;
    unsigned int m;
    u16 *q;
    int *p;
    void *o;
    // ENDDECLS
    volatile u16 id;
    int out;

    func_02061b1c((void *) &id, item, 1);
    f = 0;
    lo = id;
    hi = id;
    if (hi >= 0x1100 && lo <= 0x1143) {
        f = 1;
    }
    if (f != 0) {
        g = 0;
        iid = *item;
        if (iid >= 0x1100 && iid <= 0x1143) {
            g = 1;
        }
        *(int *) ((char *) self + 0x10) = g ? (int) (iid - 0x1100) : -1;
        id = 0x4a64;
    } else if (lo >= 0x1144 && lo <= 0x1187) {
        g = 0;
        iid = *item;
        if (iid >= 0x1144 && iid <= 0x1187) {
            g = 1;
        }
        *(int *) ((char *) self + 0x10) = g ? (int) (iid - 0x1144) : -1;
        id = 0x4a60;
    } else if (lo >= 0x1000 && lo <= 0x10ff) {
        n = func_0204bd5c((void *) &id);
        id = (n < 0x40) ? (0x4a68 + n * 4) : 0x4a68;
    }
    k = *(u8 *) ((char *) self + 0xc) & 1;
    q = (u16 *) ((char *) self + 8) + k;
    if (same(item, q) == 0) {
        o = *(void **) ((char *) self + (*(u8 *) ((char *) self + 0xc) & 1) * 4);
        if (o != 0) {
            func_020ee470(o);
            *(void **) ((char *) self + (*(u8 *) ((char *) self + 0xc) & 1) * 4) = 0;
        }
        m = (u8) ((*(u8 *) ((char *) self + 0xc) + 1) & 1);
        p = (int *) ((char *) self + m * 4);
        if (*(int *) ((char *) self + m * 4) == 0) {
            if (func_ov004_0223b540(&out, (void *) &id, 2) == 3) {
                *p = func_ov004_0223c660(out);
                *(u16 *) ((char *) self + m * 2 + 8) = *item;
                *(u8 *) ((char *) self + 0xc) = (u8) m;
                return 1;
            }
        }
    }
    return 0;
}

void func_ov004_0223d064(int *a)
{
    unsigned int i;
    for (i = 0; i < 2; i++) {
        if (a[i] != 0) {
            func_020ee470((void *) a[i]);
        }
    }
    func_ov004_0223d2b0((char *) a);
}

int func_ov004_0223d054(char *self)
{
    // DECLS
    // ENDDECLS
    return *(int *) (self + ((*(u8 *) (self + 0xc) & 0x1) << 2) + 0x14);
}

int func_ov004_0223d044(char *self)
{
    // DECLS
    // ENDDECLS
    return *(int *) (self + ((*(u8 *) (self + 0xc) & 0x1) << 2) + 0x1c);
}

void *func_ov004_0223d03c(void)
{
    return data_ov004_022596b0;
}
