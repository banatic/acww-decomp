/* func_ov004_0223f05c @ 0x0223f05c, 0xb4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
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
extern int func_ov004_0223efc4(void *a, void *p);
extern int func_0209d088(void *p);
extern int NNS_G3dMdlGetMdlAlpha(int a, void *b);
extern void func_020acdcc(void *, int, int, int);

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
            if (func_ov004_0223efc4(arg, p) != 0) {
                func_020acdcc(p + 0x2c8, data_ov004_02256308[c].b, 0x9000,
                              (u8) NNS_G3dMdlGetMdlAlpha(func_0209d088(p + 0x288), z2));
            }
        }
        p += 0x2d8;
        i = (u8) (i + 1);
    } while (i < 0x20);
    return 1;
}
