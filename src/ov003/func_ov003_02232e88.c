/* func_ov003_02232e88 @ 0x02232e88, 0xf0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02232e88;
extern UnkStruct_02232e88 *data_020ccf94;

extern int func_02073dd4(void *a, int b);
extern int func_ov003_02232210(void *self);
extern int func_ov003_02232414(void *self);
extern void func_0204f818(int *x, int *y, int *p);
extern int func_02031acc(int x, int y);
extern int func_02090c2c(int a, int *p, int b, void *c);
extern void func_ov003_02230f60(void *self);
extern int data_020e25d4;

void func_ov003_02232e88(char *self, short *pn)
{
    short t;
    int x;
    int y;
    short n;
    int k;

    t = *(short *) (self + 0x232);
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        if (func_ov003_02232210(self) != 0) {
            return;
        }
    } else if (func_ov003_02232414(self) == 0) {
        return;
    }
    *(short *) (self + 0x232) = t - 1;
    if (t == 5) {
        func_0204f818(&x, &y, (int *) (self + 0x204));
        if (func_02031acc(x, y) == 0 && func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
            func_02090c2c(0x80, (int *) (self + 0x204), 0, &data_020e25d4);
            return;
        }
        *(u8 *) (self + 0x251) = 9;
    } else if (t <= 0) {
        n = *pn;
        if (n < 2) {
            *(short *) (self + 0x23a) = *(short *) (self + 0x23a) - 0xaaa;
        } else {
            k = n + 1;
            if (k % 4 == 0) {
                *(short *) (self + 0x23a) = *(short *) (self + 0x23a) + 0xaaa;
            } else if (k % 2 == 0) {
                *(short *) (self + 0x23a) = *(short *) (self + 0x23a) - 0xaaa;
            }
        }
        *pn = 0;
        func_ov003_02230f60(self);
    }
}
