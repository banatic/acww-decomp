/* museum_insects_2: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223f05c @ 0x0223f05c, 0xb4 bytes, Thumb
 * func_ov004_0223efc4 @ 0x0223efc4, 0x98 bytes, Thumb
 * func_ov004_0223ef98 @ 0x0223ef98, 0x2c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0223f05c {
    int x;
    int y;
    int z;
};

struct UnkStruct_0223f05c_2 {
    short a;
    short b;
};

extern struct UnkStruct_0223f05c data_ov004_0225629c;
extern struct UnkStruct_0223f05c_2 data_ov004_02256308[];
extern char data_ov004_02259a34[];
extern void func_0205510c(void *q, void *p);
extern int func_0209d088(void *p);
extern int NNS_G3dMdlGetMdlAlpha(int a, void *b);
extern void func_020acdcc(void *, int, int, int);
extern int func_0209d138(void *);
extern void func_ov004_0223ebf0(void *, int);

int func_ov004_0223efc4(void *unused, char *p);

int func_ov004_0223f05c(void *arg)
{
    char *p = data_ov004_02259a34;
    u8 i = 0;
    void *z1 = 0;
    void *z2 = 0;
    struct UnkStruct_0223f05c tmp;
    void *pp;
    signed char c;
    char *q;
    do {
        if (*(int *) (p + 0x198) == 2) {
            c = *(signed char *) (p + 0x196);
            q = p + 0xb0;
            if (c == 0x30) {
                pp = &tmp;
                tmp = data_ov004_0225629c;
                func_0205510c(q, pp);
            } else {
                func_0205510c(q, z1);
            }
            if (func_ov004_0223efc4(arg, (char *) p) != 0) {
                func_020acdcc(p + 0x2c8, data_ov004_02256308[c].b, 0x9000,
                              (u8) NNS_G3dMdlGetMdlAlpha(func_0209d088(p + 0x288), z2));
            }
        }
        p += 0x2d8;
        i = (u8) (i + 1);
    } while (i < 0x20);
    return 1;
}

int func_ov004_0223efc4(void *unused, char *p)
{
    switch (*(signed char *) (p + 0x196)) {
        case 9:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 24:
        case 25:
        case 31:
        case 33:
        case 34:
        case 35:
        case 36:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 50:
        case 51:
        case 56:
            return 0;
        case 30:
            if (*(short *) (p + 0x172) != 0x19) {
                return 1;
            }
            return 0;
    }
    return 1;
}

int func_ov004_0223ef98(char *self)
{
    // DECLS
    int i;
    // ENDDECLS
    for (i = 0; i < 0x20; i++) {
        func_ov004_0223ebf0(self, i);
    }
    func_0209d138(self + 0x180);
    return 0x1;
}
