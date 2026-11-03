/* pockets_screen_2: 5 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_0229d1d4 @ 0x0229d1d4, 0x94 bytes, Thumb
 * func_ov096_0229d1a0 @ 0x0229d1a0, 0x34 bytes, Thumb
 * func_ov096_0229d16c @ 0x0229d16c, 0x34 bytes, Thumb
 * func_ov096_0229d0e4 @ 0x0229d0e4, 0x86 bytes, Thumb
 * func_ov096_0229cf84 @ 0x0229cf84, 0x160 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229d0e4 {
    u8 pad_00[0xbb];
    u8 unk_BB;
} UnkStruct_0229d0e4;

typedef struct {
    char pad_00[0x294c];
    char unk_294C;
} UnkStruct_0229cf84;

extern int func_ov096_0229c2fc(void *, int);
extern void func_ov002_02208c58(void *, void *, int);
extern int func_ov096_0229f290(void *, int);
extern int func_ov096_0229f200(void *, int);
extern void func_ov002_022098ec(void *, int, int);
extern void func_ov002_02209874(void *, void *);
extern void func_ov002_02209910(void *, int, int);
extern void func_ov002_0220970c(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_0200467c(int);
extern void func_ov096_0229dc48(void *);
extern void func_ov002_022096d8(void *, int);
extern void func_ov096_0229ddd8(void *);
extern int func_0206fe54(void);
extern int func_ov002_02208d4c(void *p, int a, int b);
extern int func_ov096_0229f088(UnkStruct_0229cf84 *self, int a);
extern unsigned short func_ov096_0229f0dc(UnkStruct_0229cf84 *self, int a);
extern int func_0208b500(void);
extern int func_0208d12c(void *argument0);
extern int func_ov096_0229daec(UnkStruct_0229cf84 *self, int a);
extern void func_ov098_022a30a4(UnkStruct_0229cf84 *self, int a);
extern int func_020b67d4(void);
extern void func_ov097_022a28e4(UnkStruct_0229cf84 *self, int a);
extern int func_ov094_02299a90(int a);
extern u8 data_020e54a8;

void func_ov096_0229d1d4(unsigned char *p, int flag)
{
    int result1;
    int a, b;

    result1 = func_ov096_0229c2fc(p, 0x40000);
    func_ov002_02208c58(p + 0x2564, p + 0x294c, result1);

    a = func_ov096_0229f290(p, p[0xb6]);
    b = func_ov096_0229f200(p, p[0xb6]);

    if (p[0xb6] == 0x25) {
        b = 0x68;
        func_ov002_022098ec(p + 0x2564, b, b);
    } else if (flag != 0) {
        func_ov002_02209874(p + 0x2564, p + 0x2418);
    } else {
        func_ov002_02209910(p + 0x2564, a, b);
    }

    func_ov002_0220970c(p + 0x2564, 0);
    func_ov002_02208098((void *) (p), 0x1d);
}

void func_ov096_0229d1a0(void *p)
{
    func_0200467c(0x2a);
    ((unsigned char *) p)[0xbb] = 0x22;
    func_ov096_0229dc48(p);
    func_ov002_022096d8((char *) p + 0x2564, 0);
    func_ov002_02208098((void *) (p), 0x1f);
}

void func_ov096_0229d16c(void *r0)
{
    void *r4 = r0;
    func_0200467c(0x28);
    *(unsigned char *) ((char *) r4 + 0xbe) = 0xf;
    func_ov002_022096d8((char *) r4 + 0x2564, 1);
    func_ov002_02208098((void *) (r4), 0x24);
    func_ov096_0229ddd8(r4);
}

int func_ov096_0229d0e4(UnkStruct_0229d0e4 *self)
{
    switch (self->unk_BB) {
        case 18:
        case 19:
            func_0200467c(0x50);
            break;
        case 20:
            func_0200467c(0x71);
            break;
        case 9:
            func_0200467c(0x24);
            return 0;
        case 2:
        case 22:
        case 23:
            func_0200467c(0x25);
            return 0;
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
            return 0;
        default:
            break;
    }
    return 1;
}

void func_ov096_0229cf84(UnkStruct_0229cf84 *self, int arg)
{
    volatile u16 t;
    int k;
    int id;

    if (func_0206fe54() != 0) {
        func_ov002_02208d4c(&self->unk_294C, 0, 0);
    }
    k = func_ov096_0229f088(self, arg);
    id = func_ov096_0229f0dc(self, arg);
    t = (u16) id;
    if (k == 0) {
        unsigned int ok = 0;
        u16 lo = t;
        u16 hi = t;
        if (hi >= 0x156c && lo <= 0x156c) {
            ok = 1;
        }
        if (ok != 0) {

            if (func_0208d12c((void *) func_0208b500()) != 0) {
                func_ov002_02208d4c(&self->unk_294C, 0xdc, 0x1b);
            } else {
                func_ov002_02208d4c(&self->unk_294C, 0xe1, 0x1c);
            }
        }
    }
    switch (k) {
        case 0: {
            unsigned int ok;
            int q;
            u16 lo, hi;
            if (func_ov096_0229daec(self, id) != 0) {
                ok = (data_020e54a8 == 0) ? 1 : 0;
                if (ok != 0) {
                    q = 1;
                } else {
                    q = 0xa;
                }
                func_ov002_02208d4c(&self->unk_294C, q, 2);
            }
            ok = (data_020e54a8 == 0) ? 1 : 0;
            if (ok != 0) {
                func_ov098_022a30a4(self, id);
            } else if (func_020b67d4() != 0) {
                func_ov097_022a28e4(self, id);
            }
            ok = 0;
            lo = t;
            hi = t;
            if (hi >= 0x1000 && lo <= 0x10ff) {
                ok = 1;
            }
            if (ok != 0) {
                func_ov002_02208d4c(&self->unk_294C, 0x1c, 7);
            } else if (lo >= 0x151f && lo <= 0x151f) {
                func_ov002_02208d4c(&self->unk_294C, 0x1c, 8);
            }
        } break;
        case 1:
            func_ov002_02208d4c(&self->unk_294C, 9, 0x14);
            break;
        case 2:
            if (func_ov094_02299a90(id) == 0) {
                func_ov002_02208d4c(&self->unk_294C, 0x17, 0x14);
            }
            break;
    }
}
