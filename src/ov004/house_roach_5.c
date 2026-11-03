/* house_roach_5: 8 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223e520 @ 0x0223e520, 0xd0 bytes, Thumb
 * func_ov004_0223e4a0 @ 0x0223e4a0, 0x80 bytes, Thumb
 * func_ov004_0223e418 @ 0x0223e418, 0x88 bytes, Thumb
 * func_ov004_0223e3ec @ 0x0223e3ec, 0x2c bytes, Thumb
 * func_ov004_0223e3e0 @ 0x0223e3e0, 0xc bytes, Thumb
 * func_ov004_0223e3d4 @ 0x0223e3d4, 0xc bytes, Thumb
 * func_ov004_0223e2f0 @ 0x0223e2f0, 0xe4 bytes, Thumb
 * func_ov004_0223e1f0 @ 0x0223e1f0, 0x100 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern void *func_02003564(void *argument0);
extern void *func_02032c64(void *argument0);
extern void *func_02055210(void *argument0);
extern void *func_02089bd4(void *argument0);
extern void __cxa_vec_ctor();
extern void func_020012dc(void *arg0);
extern void func_020012e8(void *arg0);
extern void *data_0213efe8;
extern void *data_0213f020;
extern void *data_ov004_0225622c;
extern void *func_02032c50(void *);
extern void *func_020551e0(void *);
extern void *func_02089bbc(void *);
extern int func_020e8ce0(void *, void *);
extern void func_020ee62c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *data_020d7244;
extern void *data_020da13c;
extern void *data_0213ff78;
extern void func_020edf54(void *);
extern int data_ov004_02259a14;
extern int func_02082654(int i);
extern unsigned char data_ov004_022561a4[];
extern unsigned char data_ov004_02256274[];
extern void *data_021fbe94;
extern int func_0205556c(void *, unsigned int, void *);
extern void *func_020e99d8(int, void *);
extern void func_020ee4cc(void *, void *);
extern int func_02055140(void *, void *);
extern void *func_02064b18(void *);
extern int func_020e9abc(void *);
extern void func_020e9974(void);
extern void *NNS_G3dGetVisAnmSet(void *);
extern void *func_02107cf0(void *, int);
extern void func_02055060(void *, void *, int, int, unsigned short, unsigned short);
extern void func_02055050(void *);
extern int func_0200430c(void *);
extern void func_ov004_0223df88(char *self);
extern void func_ov004_0223d87c(char *self);
extern int func_02091254(int a, void *b, int c, int d);
extern void func_ov004_0223dc68(char *self, int parameter1);
extern int func_020644cc(int n);
extern void func_020042c0(void *a, Vec3 *v);

void *func_ov004_0223e520(char *self)
{
    // DECLS
    // ENDDECLS
    func_02003564(self);
    *(void **) (self) = &data_ov004_0225622c;
    *(int *) (self + 0xd4) = 0x614;
    *(int *) (self + 0xd8) = 0x6b8;
    func_02032c64(self + 0xdc);
    *(void **) (self + 0x114) = &data_0213efe8;
    *(void **) (self + 0x114) = &data_0213f020;
    func_02055210(self + 0x120);
    func_02089bd4(self + 0x1d8);
    __cxa_vec_ctor(self + 0x230, 0x2, 0xc, (void *) func_020012e8, (void *) func_020012dc);
    __cxa_vec_ctor(self + 0x248, 0x2, 0xc, (void *) func_020012e8, (void *) func_020012dc);
    *(int *) (self + 0x110) = 0x1;
    *(u8 *) (self + 0x260) = 0x0;
    *(u8 *) (self + 0x262) = 0x0;
    *(u16 *) (self + 0x22e) = 0x0;
    *(int *) (self + 0x10c) = 0x3;
    return self;
}

void *func_ov004_0223e4a0(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_0225622c;
    __cxa_vec_cleanup(self + 0x248, 0x2, 0xc, ((void (*)(void *)) func_020012dc));
    __cxa_vec_cleanup(self + 0x230, 0x2, 0xc, ((void (*)(void *)) func_020012dc));
    func_02089bbc(self + 0x1d8);
    func_020551e0(self + 0x120);
    func_02032c50(self + 0xdc);
    *(void **) (self) = &data_020d7244;
    func_020e8ce0(&data_0213ff78, self + 0x50);
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    return self;
}

void *func_ov004_0223e418(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_0225622c;
    __cxa_vec_cleanup(self + 0x248, 0x2, 0xc, ((void (*)(void *)) func_020012dc));
    __cxa_vec_cleanup(self + 0x230, 0x2, 0xc, ((void (*)(void *)) func_020012dc));
    func_02089bbc(self + 0x1d8);
    func_020551e0(self + 0x120);
    func_02032c50(self + 0xdc);
    *(void **) (self) = &data_020d7244;
    func_020e8ce0(&data_0213ff78, self + 0x50);
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}

void func_ov004_0223e3ec(void *receiver)
{
    u8 i = 0;
    int *p = &data_ov004_02259a14;
    do {
        int r = func_02082654(i);
        if (r != 0) {
            *p = r;
        }
        i = i + 1;
    } while (i < 8);
}

int func_ov004_0223e3e0(char *self)
{
    // DECLS
    // ENDDECLS
    return *(int *) (self + 0x264);
}

void func_ov004_0223e3d4(void *self, int v)
{
    *(int *) ((char *) self + 0x264) = v;
}

int func_ov004_0223e2f0(unsigned char *self)
{
    void *heap, *resource;
    short *angle;
    func_0205556c(self + 0x120, 0x474f4b49, data_ov004_022561a4);
    heap = func_020e99d8(0x5000, data_021fbe94);
    func_020ee4cc(self, heap);
    func_02055140(self + 0x120, 0);
    resource = func_02064b18(data_ov004_02256274);
    func_020e9abc(heap);
    func_020e9974();
    func_02055060(self + 0x120, func_02107cf0(NNS_G3dGetVisAnmSet(resource), 0), 0, 0x1000, 0, 0);
    func_02055050(self + 0x120);
    func_0200430c(self + 0x114);
    angle = (short *) (self + 0x92);
    angle[1] = *(short *) (self + 0x8e);
    *(short *) (self + 0x228) = angle[1];
    *(int *) (self + 0x9c) = -0x333;
    *(int *) (self + 0x98) = *(int *) (self + 0xd4);
    self[0x22a] = 0;
    self[0x263] = 0;
    *(int *) (self + 0x264) = 0;
    return 1;
}

void func_ov004_0223e1f0(char *self)
{
    // DECLS
    Vec3 *q;
    int t;
    // ENDDECLS
    Vec3 v;

    if (*(int *) (self + 0x10c) != 2) {
        func_ov004_0223df88(self);
    }
    switch (*(int *) (self + 0x10c)) {
        case 0:
            func_ov004_0223d87c(self);
            break;
        case 1:
            *(int *) (self + 0x98) = *(int *) (self + 0xd4);
            t = *(s16 *) (self + 0x22c);
            *(s16 *) (self + 0x22c) = (s16) (t - 1);
            if (t <= 0) {
                if (*(u8 *) (self + 0x22a) == 0) {
                    *(int *) (self + 0x10c) = 0;
                    *(s16 *) (self + 0x22c) = (s16) (0x14 * (func_020644cc(0xa) + 3));
                }
            }
            break;
        case 2:
            func_02091254(0x50, self + 0x5c, 0, 0);
            *(int *) (self + 8) -= 1;
            *(int *) (self + 0x110) = 2;
            func_ov004_0223dc68(self, (int) (0x2));
            break;
        case 3:
            if (func_020644cc(0x64) > 0x32) {
                *(int *) (self + 0x10c) = 0;
                *(s16 *) (self + 0x22c) = (s16) (0x14 * (func_020644cc(0xa) + 3));
            } else {
                *(int *) (self + 0x10c) = 1;
                *(s16 *) (self + 0x22c) = (s16) (0x14 * (func_020644cc(4) + 3));
            }
            break;
    }
    q = (Vec3 *) (self + 0x5c);
    v.x = q->x;
    v.y = q->y;
    v.z = q->z;
    func_020042c0(self + 0x114, &v);
}
