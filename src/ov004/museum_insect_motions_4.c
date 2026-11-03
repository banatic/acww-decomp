/* museum_insect_motions_4: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02242a9c @ 0x02242a9c, 0x48 bytes, Thumb
 * func_ov004_02242a28 @ 0x02242a28, 0x74 bytes, Thumb
 * func_ov004_02242820 @ 0x02242820, 0x208 bytes, Thumb
 */

#include "types.h"

#define B(p, o) (*(u8 *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
#define W(p, o) (*(int *) ((p) + (o)))
#define V(p, o) ((Vec *) ((p) + (o)))
#define FRAME(p) (((u32) W(p, 0xa4) << 4) >> 16)

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02242a28 {
    char unk_00[0x192];
    short ang;
    char unk_194[0x2c8 - 0x194];
    Vec3 pos;
} UnkStruct_02242a28;

typedef struct {
    int x, y, z;
} Vec;

extern int func_ov004_02244be0(void *, int);
extern int func_0200322c(Vec3 *a, Vec3 *b);
extern int func_020e8870(short *a, int b, int c);
extern int func_ov004_02244e38(char *, Vec *);
extern void func_02056fcc(char *, int, u8, int, u16);
extern void func_020550e4(char *, int);
extern char *func_ov004_0223ee38(void);
extern int func_020644cc(int);

void func_ov004_02242a9c(void *self, int v, int n)
{
    if (n % 4 == 0) {
        *(short *) ((char *) self + 0x192) = (short) (v + 0x71c);
    } else if (n % 2 == 0) {
        *(short *) ((char *) self + 0x192) = (short) (v - 0x71c);
    }
    func_ov004_02244be0(self, 0);
}

int func_ov004_02242a28(UnkStruct_02242a28 *a, UnkStruct_02242a28 *b)
{
    short t[2];
    unsigned char f;

    t[0] = a->ang;
    t[1] = b->ang;
    f = (unsigned char) func_020e8870(&t[1], func_0200322c(&b->pos, &a->pos), 0xaaa);
    f &= func_020e8870(&t[0], func_0200322c(&a->pos, &b->pos), 0xaaa);
    a->ang = t[0];
    b->ang = t[1];
    return f != 0;
}

int func_ov004_02242820(char *self)
{
    func_ov004_02244e38(self, V(self, 0x2c8));
    if (*(signed char *) (self + 0x196) == 55) {
        char *anim = self + 0xb0;
        int count = W(anim, 0xa0) >> 12;
        if ((u16) count < 11 && FRAME(anim) <= 2) {
            func_02056fcc(anim + 0x9c, 11, 1, 0x1000, 3);
        } else if ((u16) count < 14 && FRAME(anim) < 11) {
            func_02056fcc(anim + 0x9c, 14, 0, 0x1000, 10);
        } else if ((u16) count > 11 && FRAME(anim) == 13) {
            func_020550e4(anim, 10);
        }
        return 0;
    }
    if (S(self, 0x172) == 25) {
        char *peer = func_ov004_0223ee38();
        u8 choice = func_020644cc(100);
        short *turn = (short *) (self + 0x98);
        if (!func_ov004_02242a28((UnkStruct_02242a28 *) self, (UnkStruct_02242a28 *) peer)) {
            return 0;
        }
        if (choice < 20) {
            W(self, 0x174) = (func_020644cc(8) + 2) * 20;
            S(self, 0x172) = 20;
        } else if (choice < 35) {
            W(self, 0x174) = (func_020644cc(4) + 1) * 20;
            S(self, 0x172) = 21;
            {
                Vec *src = V(peer, 0x2c8), *dest = V(peer, 0x34);
                W(peer, 0x34) = src->x;
                dest->y = src->y;
                dest->z = src->z;
            }
            if (func_020644cc(100) > 50) {
                B(self, 0x170) = 0;
            } else {
                B(self, 0x170) = 1;
            }
        } else if (choice < 50) {
            W(self, 0x174) = (func_020644cc(4) + 1) * 20;
            S(self, 0x172) = 22;
            {
                Vec *src = V(self, 0x2c8), *dest = V(self, 0x34);
                W(self, 0x34) = src->x;
                dest->y = src->y;
                dest->z = src->z;
            }
            if (func_020644cc(100) > 50) {
                B(self, 0x170) = 0;
            } else {
                B(self, 0x170) = 1;
            }
        } else if (choice < 70) {
            W(self, 0x174) = (func_020644cc(4) + 1) * 20;
            S(self, 0x172) = 23;
        } else {
            W(self, 0x174) = (func_020644cc(8) + 1) * 20;
            S(self, 0x172) = 24;
            W(peer, 0x15c) = 0;
        }
        W(self, 0x4c) = 0;
        *turn = func_020644cc(5) + 5;
        if (func_020644cc(100) > 50) {
            *turn = -*turn;
        }
        S(peer, 0x168) = 0;
        S(peer, 0x172) = S(self, 0x172);
        func_ov004_02244e38(peer, V(peer, 0x2c8));
    }
    return 1;
}
