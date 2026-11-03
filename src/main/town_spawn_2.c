/* town_spawn_2: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02048418 @ 0x02048418, 0x80 bytes, Thumb
 * func_020483c4 @ 0x020483c4, 0x54 bytes, Thumb
 * func_0204830c @ 0x0204830c, 0xb8 bytes, Thumb
 * func_02048298 @ 0x02048298, 0x74 bytes, Thumb
 * func_02048238 @ 0x02048238, 0x60 bytes, Thumb
 * func_020481a0 @ 0x020481a0, 0x98 bytes, Thumb
 * func_0204811c @ 0x0204811c, 0x84 bytes, Thumb
 */

#include "types.h"

struct Global {
    char pad_00[0x30];
    int : 5;
    int flag : 1;
    int : 26;
};

typedef struct {
    char pad_00[0x18];
    u16 unk_18;
} Cnt;

typedef struct {
    char pad_00[0x18];
    unsigned short n;
} UnkStruct_02048298;

typedef struct {
    char pad_00[0xe];
    unsigned char cnt;
} GlobalA;

typedef struct {
    char pad_00[0x30];
    signed int field : 4;
} GlobalB;

struct UnkStruct_020481a0 {
    int pad_00;
    int w;
    int h;
};

extern unsigned char data_021c79e4[];
extern int func_020644cc(int);
extern int func_02048cb8(int, int, int, int, int, int (*predicate)(int, int, int), int);
extern int func_02048e54(void *, int, int);
extern struct Global data_021c79c4;
extern int func_02048ee4(void *, int, int);
extern void func_0204f800(int *a, int *b, int c, int d, int e, int f);
extern void func_0204a25c(int a, int b, int c, int d, int e);
extern u16 data_020ca59c[];
extern unsigned char data_021c7a08[];
extern void func_02042efc(void *p);
extern unsigned char data_021c80b4[];
extern void *func_0204e414(void);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern void func_0204a200(int a0, void *ctx, int cx, int cz, int dx, int dz, int id, int f);
extern void func_0204f818(int *px, int *pz, void *p);
extern int func_02045d80(int *arr, int k);

void func_02048418(int a, int b, int c, int d)
{
    int v1, v2, i;

    i = 3 - data_021c79e4[0xd];
    v1 = func_020644cc(c - 1);
    v2 = func_020644cc(d - 1);

    while (i > 0) {
        v1 = (v1 + 1 + func_020644cc(c - 1)) % c;
        v2 = (v2 + 1 + func_020644cc(d - 1)) % d;
        func_02048cb8(a, b, v1 + 1, v2 + 1, 0x1549, (((int (*)(int, int, int)) func_02048e54)), 1);
        i--;
    }
}

void func_020483c4(int p0, int p1, int p2, int p3)
{
    int t1, t2;
    if (data_021c79c4.flag) {
        return;
    }
    t1 = func_020644cc(p2 - 1);
    t2 = func_020644cc(p3 - 1);
    func_02048cb8(p0, p1, t1 + 1, t2 + 1, 0x1566, (((int (*)(int, int, int)) func_02048ee4)), 1);
}

int func_0204830c(int p0, int p1, Cnt *cnt, int k, int x, int y)
{
    int start;
    int z6;
    int zok;
    int count;
    int inner;
    int outer;
    int t;
    int ok;
    unsigned int v;
    u16 *r;
    int tv;
    int out1;
    int out2;

    t = cnt->unk_18;
    count = func_020644cc(t);
    cnt->unk_18 = t - 1;
    start = 0;
    zok = 0;
    z6 = 0;
    for (outer = 0; outer < 0x10; outer++) {
        for (inner = start; inner < 0x10; inner++) {
            r = (u16 *) func_0204f5e0((void *) p1, x + 1, y + 1, inner, outer, z6);
            if (r == 0) {
                continue;
            }
            ok = zok;
            v = *r;
            if (v >= 0xe3 && v <= 0xe7) {
                ok = 1;
            }
            if (ok == 0) {
                continue;
            }
            count = count - 1;
            if (count >= 0) {
                continue;
            }
            func_0204f800(&out1, &out2, x + 1, y + 1, inner, outer);
            tv = data_020ca59c[k];
            func_0204a25c(p1, out1, out2, (u16) (tv + (int) (v - 0xe3) % 5), 0);
            return 1;
        }
    }
    return 0;
}

int func_02048298(void *p0, void *p1, int nx, int ny, int p4, int p5)
{
    int j, i;
    int rem;
    UnkStruct_02048298 *e;

    rem = func_020644cc(p5);
    for (i = 0; i < ny; i++) {
        for (j = 0; j < nx; j++) {
            e = (UnkStruct_02048298 *) (data_021c7a08 + j * 0x90 + i * 0x24);

            if ((int) e->n > 0) {
                rem -= e->n;
                if (rem < 0) {
                    if (func_0204830c((int) p0, (int) p1, (Cnt *) e, p4, j, i) != 0) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void func_02048238(int a0, int a1, int a2, int a3)
{
    int count = (*(GlobalA *) data_021c79e4).cnt;
    int i = 0;

    while (i < 4) {
        if (count <= 0) {
            return;
        }
        if (((1 << i) & (*(GlobalB *) &data_021c79c4).field) == 0) {
            if (func_02048298((void *) a0, (void *) a1, a2, a3, i, count)) {
                count--;
            }
        }
        i++;
    }

    func_02042efc((void *) data_021c80b4);
}

void func_020481a0(int a0)
{
    int cx;
    int xmax;
    int cz;
    int ymax;
    volatile int start;
    int dx;
    void *ctx;
    volatile int something;
    unsigned short *p;
    int ok;
    int dz;

    ctx = func_0204e414();
    if (ctx == 0) {
        return;
    }
    xmax = ((struct UnkStruct_020481a0 *) ctx)->w - 2;
    ymax = ((struct UnkStruct_020481a0 *) ctx)->h - 2;
    start = 1;
    something = 1;
    for (cz = 1; cz <= ymax; cz++) {
        for (cx = start; cx <= xmax; cx++) {
            for (dz = 0; dz < 16; dz++) {
                for (dx = 0; dx < 16; dx++) {
                    p = func_0204f5e0(ctx, cx, cz, dx, dz, 0);
                    if (p != 0) {
                        ok = 0;
                        if (*p >= 0xfc && *p <= 0xfd) {
                            ok = something;
                        }
                        if (ok != 0) {
                            func_0204a200(a0, ctx, cx, cz, dx, dz, 0xfff1, 0);
                        }
                    }
                }
            }
        }
    }
}

/* FAKEMATCH: the redundant mask and the empty if keep the z load before the x shift; the plain copies shift x first */
void func_0204811c(int a0, void *p1)
{
    void *ctx;
    unsigned short *o;
    int x;
    int z;
    int arr[2];
    int vx;
    int vz;
    int cx;
    int cz;
    int ok;
    ctx = func_0204e414();
    if ((ctx == 0)) {
        return;
    }
    x = 0;
    z = 0;
    func_0204f818(&x, &z, p1);
    vx = x;
    vz = z;
    cx = vx >> 4;
    if ((z && z) && z) {
    }
    cz = vz >> 4;
    o = func_0204f5e0(ctx, cx, cz, vx - (cx << 4), vz - (cz << 4), 0);
    if (o == 0) {
        return;
    }
    ok = 0;
    if (((*o) >= 0xfc) && ((*o) <= 0xfd)) {
        ok = 1;
    }
    if (ok == 0) {
        return;
    }
    arr[0] = x;
    arr[1] = z;
    if (func_02045d80(arr, 0) >= 0) {
        return;
    }
    func_0204a25c((int) ctx, x, z, 0xfff1, 0);
}
