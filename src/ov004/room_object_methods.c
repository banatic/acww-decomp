/* room_object_methods: 16 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220e758 @ 0x0220e758, 0xb0 bytes, Thumb
 * func_ov004_0220e73c @ 0x0220e73c, 0x1a bytes, Thumb
 * func_ov004_0220e674 @ 0x0220e674, 0xc8 bytes, Thumb
 * func_ov004_0220e640 @ 0x0220e640, 0x32 bytes, Thumb
 * func_ov004_0220e61c @ 0x0220e61c, 0x22 bytes, Thumb
 * func_ov004_0220e5dc @ 0x0220e5dc, 0x3e bytes, Thumb
 * func_ov004_0220e5c8 @ 0x0220e5c8, 0x14 bytes, Thumb
 * func_ov004_0220e5c0 @ 0x0220e5c0, 0x8 bytes, Thumb
 * func_ov004_0220e5b8 @ 0x0220e5b8, 0x8 bytes, Thumb
 * func_ov004_0220e5b0 @ 0x0220e5b0, 0x8 bytes, Thumb
 * func_ov004_0220e5a8 @ 0x0220e5a8, 0x8 bytes, Thumb
 * func_ov004_0220e578 @ 0x0220e578, 0x30 bytes, Thumb
 * func_ov004_0220e574 @ 0x0220e574, 0x2 bytes, Thumb
 * func_ov004_0220e570 @ 0x0220e570, 0x2 bytes, Thumb
 * func_ov004_0220e534 @ 0x0220e534, 0x3c bytes, Thumb
 * func_ov004_0220e504 @ 0x0220e504, 0x30 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0220e758 {
    u8 data[0x24];
};

struct UnkStruct_0220e758_2 {
    int unk_00;
    int unk_04;
};

typedef struct {
    int x, y, z;
} Vec3;

struct UnkStruct_0220e674 {
    u8 data[0x24];
};

struct UnkStruct_0220e674_2 {
    int unk_00;
    int unk_04;
};

extern char *func_ov004_0220db94(struct UnkStruct_0220e758 *l);
extern void func_ov004_0220f27c(void *self, struct UnkStruct_0220e758 *l, int a, int b);
extern struct UnkStruct_0220e758_2 *func_ov004_0220db5c(struct UnkStruct_0220e758 *l, unsigned int i);
extern unsigned int func_ov004_0220db68(struct UnkStruct_0220e758 *l);
extern void func_ov004_0220db90(struct UnkStruct_0220e758 *l);
extern u16 *func_0204f5e0(void *g, int a, int b, int c, int d, int e);
extern int func_0204bcdc(u16 *p);
extern void *data_021c80bc;
extern int func_ov004_0223e7b4(void *, void *);
extern void *func_02095794(int i);
extern void func_0204f794(Vec3 *v, int a, int b);
extern int func_020ea990(void *o, Vec3 *v);
extern int func_0200322c(Vec3 *v, void *o);
extern int data_020ca0ec;
extern void func_ov004_0220fefc(char *argument0, int *argument1);
extern int func_02091230(int a, Vec3 *v, int c, int d);
extern void func_ov004_0220ff4c(void *self, int *p, int a);
extern int func_ov004_0221134c(void *parameter0);
extern int func_ov004_0221132c(void *parameter0);
extern int func_ov004_02211294(void *parameter0);
extern int func_ov004_02211280(char *parameter0);
extern void *func_ov004_0220fde0(void *p);
extern u16 func_0204bc50(void *p, int a);
extern void func_020b3188(int);
extern void func_020b3220(int);
extern int func_ov004_0220cfd0(unsigned char *argument0);
extern int func_ov004_0220cfd4(void *argument0, int argument1);

int func_ov004_0220e758(char *self, int *outa, int *outb, int p3, short p4)
{
    void *g;
    struct UnkStruct_0220e758 l;
    unsigned int i;
    int a;
    int b;
    int ai;
    int bi;
    int k;
    u16 *p;

    func_ov004_0220db94(&l);
    func_ov004_0220f27c(self, &l, p3, p4);
    g = data_021c80bc;
    for (i = 0; i < func_ov004_0220db68(&l); i++) {
        k = *(u8 *) (self + 0x288);
        b = func_ov004_0220db5c(&l, i)->unk_04;
        a = func_ov004_0220db5c(&l, i)->unk_00;
        ai = a >> 4;
        bi = b >> 4;
        p = func_0204f5e0(g, ai, bi, a - (ai << 4), b - (bi << 4), k);
        if (p != 0 && func_0204bcdc(p) != 0) {
            *outa = func_ov004_0220db5c(&l, i)->unk_00;
            *outb = func_ov004_0220db5c(&l, i)->unk_04;
            func_ov004_0220db90(&l);
            return 1;
        }
    }
    func_ov004_0220db90(&l);
    return 0;
}

int func_ov004_0220e73c(char *self, int a1)
{
    // DECLS
    char frame[0xc];
    // ENDDECLS
    *(u16 *) (frame) = 0x0;
    *(u16 *) (frame + 0x2) = a1;
    *(u16 *) (frame + 0x4) = 0x0;
    return func_ov004_0223e7b4(self, frame);
}

void func_ov004_0220e674(char *self, int flag)
{
    void *o;
    int besti2;
    struct UnkStruct_0220e674_2 *e;
    struct UnkStruct_0220e674 l;
    Vec3 a;
    Vec3 b;
    int bestd;
    int best;
    unsigned int i;
    int d;
    int mind;

    o = func_02095794(4);
    if (o != 0) {
        func_ov004_0220db94((struct UnkStruct_0220e758 *) (&l));
        func_ov004_0220f27c(self, (struct UnkStruct_0220e758 *) (&l), 0, 0);
        bestd = 0;
        best = ~bestd;
        besti2 = best;
        mind = data_020ca0ec;
        for (i = 0; i < func_ov004_0220db68((struct UnkStruct_0220e758 *) (&l)); i++) {
            e = (struct UnkStruct_0220e674_2 *) func_ov004_0220db5c((struct UnkStruct_0220e758 *) (&l), i);
            func_0204f794(&a, e->unk_00, ((struct UnkStruct_0220e674_2 *) func_ov004_0220db5c((struct UnkStruct_0220e758 *) (&l), i))->unk_04);
            d = func_020ea990(o, &a);
            if (d > bestd) {
                best = i;
                bestd = d;
            }
            if (d < mind) {
                besti2 = i;
                mind = d;
            }
        }
        if (flag == 0) {
            best = besti2;
        }
        if (best != -1) {
            e = (struct UnkStruct_0220e674_2 *) func_ov004_0220db5c((struct UnkStruct_0220e758 *) (&l), best);
            func_0204f794(&b, e->unk_00, ((struct UnkStruct_0220e674_2 *) func_ov004_0220db5c((struct UnkStruct_0220e758 *) (&l), best))->unk_04);
            func_ov004_0220e73c((char *) (&b), func_0200322c(&b, o));
        }
        func_ov004_0220db90((struct UnkStruct_0220e758 *) (&l));
    }
}

int func_ov004_0220e640(char *self)
{
    // DECLS
    int v1;
    char frame[0xc];
    // ENDDECLS
    v1 = (int) func_02095794(0x4);
    if (v1 != 0x0) {
        func_ov004_0220fefc((char *) (self), (int *) (frame));
        return func_ov004_0220e73c(frame, func_0200322c((Vec3 *) ((int *) (frame)), (void *) ((int *) (v1))));
    }
    return v1;
}

int func_ov004_0220e61c(void *self, Vec3 *src)
{
    Vec3 v;
    v.x = src->x;
    v.y = src->y;
    v.z = src->z;
    return func_02091230(0x3d, &v, 0, 0);
}

void func_ov004_0220e5dc(char *self, int a)
{
    int t0[3];
    int t1[3];
    int out[3];
    int y;

    func_ov004_0220ff4c(self, t0, a);
    func_ov004_0220fefc((char *) self, t1);
    y = *(int *) (self + 0x60);
    out[0] = (t0[0] + t1[0]) >> 1;
    out[1] = y;
    out[2] = (t0[2] + t1[2]) >> 1;
    func_ov004_0220e61c(self, (Vec3 *) out);
}

int func_ov004_0220e5c8(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x76c) == 0x2) {
        return 0x1;
    }
    return 0x0;
}

int func_ov004_0220e5c0(void *arg0)
{
    return func_ov004_0221134c((void *) arg0);
}

int func_ov004_0220e5b8(void *arg0)
{
    return func_ov004_0221132c((void *) arg0);
}

int func_ov004_0220e5b0(void *arg0)
{
    return func_ov004_02211294((void *) arg0);
}

int func_ov004_0220e5a8(char *arg0)
{
    return func_ov004_02211280((char *) arg0);
}

void func_ov004_0220e578(u16 *dst, char *p)
{
    if (*(int *) (p + 0x780) == 0x1c) {
        *dst = 0xfff1;
    } else {
        *dst = func_0204bc50(func_ov004_0220fde0(p), 0);
    }
}

void func_ov004_0220e574(void) {}

void func_ov004_0220e570(void) {}

void func_ov004_0220e534(char *self, int a1, int a2)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x744) != 0x0) {
        if (*(char *) (self + 0x742) == a1) {
            func_020b3220(a2);
        } else {
            if (*(char *) (self + 0x743) == a1) {
                func_020b3188(a2);
            }
        }
    }
}

int func_ov004_0220e504(char *self, int a1, char *a2)
{
    // DECLS
    int v1;
    int v2;
    // ENDDECLS
    v1 = func_ov004_0220cfd4((void *) ((void *) (self + 0x764)), (int) ((int) (a1)));
    if (v1 != 0x0) {
        v2 = func_ov004_0220cfd0((unsigned char *) (self + 0x764));
        *(int *) ((char *) *(int *) (a2 + 0xb8)) = v2;
        return v2;
    }
    return v1;
}
