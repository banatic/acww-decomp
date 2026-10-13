/* func_02018090 @ 0x02018090, 0x208 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_02018090;

extern int func_020164cc(void *a);
extern int func_02057cf4(void);
extern void func_02057cb8(void *b);
extern int func_02057d0c(int a, void *b);
extern void func_02016764(void *a, void *b, int c, unsigned short d, int e, int f, int g, int h);
extern void func_02091230(int a, void *b, int c, int d);
extern void func_0200442c(void *a, int b, int c, int d);
extern void func_02054188(void *a, int b, int c);
extern void func_02019af0(void *a, int b);
extern int func_020912d4(int a, UnkStruct_02018090 *b, short *c, int d);
extern volatile unsigned short data_020c80f8;

void func_02018090(void *param1, void *param2)
{
    short aa;
    UnkStruct_02018090 v;

    if (func_020164cc((void *) (((char *) param2) + 0x334)) == 0) {
        return;
    }

    switch (func_02057cf4()) {
        case 6:
            func_02057cb8(param2);
            func_02016764((void *) (((char *) param2) + 0x334), param2, 0x28, data_020c80f8, 1, 0x1000, 0, 0);
            func_02091230(0x61, (void *) (((char *) param2) + 0x5c), 0, 0);
            func_0200442c((void *) (((char *) param2) + 0x514), 0x76, 0x7f, 0);
            *(u8 *) (((char *) param1) + 0x98) = 6;
            break;
        case 7:
            if (func_02057d0c(7, param2) == 0) {
                return;
            }
            func_02016764((void *) (((char *) param2) + 0x334), param2, 0x26, data_020c80f8, 3, 0x1000, 0, 0);
            *(u8 *) (((char *) param1) + 0x98) = 7;
            break;
        case 5:
            if (func_02057d0c(5, param2) == 0) {
                return;
            }
            func_02016764((void *) (((char *) param2) + 0x334), param2, 0x27, data_020c80f8, 1, 0x1000, 0, 0);
            func_0200442c((void *) (((char *) param2) + 0x514), 0x4f, 0x7f, 0);
            *(u8 *) (((char *) param1) + 0x98) = 5;
            break;
        case 10:
            if (func_02057d0c(0xa, param2) == 0) {
                return;
            }
            func_02016764((void *) (((char *) param2) + 0x334), param2, 0, data_020c80f8, 0, 0x1000, 0, 0);
            func_02016764((void *) (((char *) param2) + 0x334), param2, 0x139, 0, 0, 0x1000, 0, 1);
            func_02054188((void *) (((char *) param2) + 0xec), 9, 0xe);
            func_02019af0(param1, 1);
            *(u8 *) (((char *) param1) + 0x98) = 0x14;
            break;
        case 11:
            if (func_02057d0c(0xb, param2) == 0) {
                return;
            }
            v.x = *(int *) (((char *) param2) + 0x478);
            v.y = *(int *) (((char *) param2) + 0x47c);
            v.z = *(int *) (((char *) param2) + 0x480);
            aa = *(short *) (((char *) param2) + 0x8e);
            func_02016764((void *) (((char *) param2) + 0x334), param2, 0x29, data_020c80f8, 1, 0x1000, 0, 0);
            *(int *) (((char *) param1) + 0xac) = func_020912d4(0x40, &v, &aa, 0);
            *(u8 *) (((char *) param1) + 0x98) = 0xb;
            break;
        default:
            func_02016764((void *) (((char *) param2) + 0x334), param2, 0x24, data_020c80f8, 0, 0x1000, 0, 0);
            func_02019af0(param1, 1);
            *(u8 *) (((char *) param1) + 0x98) = 0x14;
            break;
    }
}
