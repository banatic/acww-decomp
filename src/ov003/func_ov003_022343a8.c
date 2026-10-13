/* func_ov003_022343a8 @ 0x022343a8, 0x120 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_022343a8;
extern UnkStruct_022343a8 *data_020ccf94;

extern int FX_MulFunc(int a, int b);
extern int func_020e908c(int *p, int *d, int v, int w, int a);
extern int func_0200322c(int *p, int *d);
extern int func_02073dd4(void *a, int b);
extern int func_020a7278(void);
extern void func_0204f818(int *x, int *y, int *p);
extern int func_020e8bb0(int *p, int a, int v, int b, int c);

void func_ov003_022343a8(char *self)
{
    int v;
    int *d;
    int *p;
    s8 k;
    int a;
    int x;
    int y;

    d = (int *) (self + 0x1d4);
    p = (int *) (self + 0x204);
    v = 0x1000 / *(u8 *) (self + 0x257);
    k = *(s8 *) (self + 0x24d);
    switch (k) {
        case 0x15:
            a = 0xcd;
            break;
        case 0x16:
            a = 0x266;
            break;
        default:
            a = 0x385;
            break;
    }
    if (*(u8 *) (self + 0x24a) != 0) {
        a = FX_MulFunc(a, 0x2000);
    }
    if (func_020e908c(p, d, v, 0x1000, a) == 0) {
        *(u8 *) (self + 0x251) = 0x13;
    } else {
        *(short *) (self + 0x23a) = func_0200322c(p, d);
        if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 && func_020a7278() == 0) {
            func_0204f818(&x, &y, p);
            if (x < 0x10 || x > 0x4f || y < 0x10) {
                *(u8 *) (self + 0x251) = 0x13;
            }
        }
    }
    if (*(u8 *) (self + 0x24c) != 0) {
        func_020e8bb0(p + 1, *(int *) (self + 0x228), v, 0x1ec, 0xcd);
    } else if (func_020e8bb0(p + 1, *(int *) (self + 0x228) - 0x1000, v, 0x333, 0xcd) == 0) {
        *(u8 *) (self + 0x24c) = 1;
    }
}
