/* func_ov114_0229cbe4 @ 0x0229cbe4, 0xdc bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229cbe4 {
    char pad_00[0x1000];
    struct {
        char data[12];
    } arr[9];
    char pad_106C[0x218];
    int unk_1284;
    int unk_1288;
    int unk_128C;
    int unk_1290;
    char pad_1294[0x25];
    u8 unk_12B9;
} UnkStruct_0229cbe4;

extern int func_ov114_0229c1b8(UnkStruct_0229cbe4 *self, int value);
extern int func_020896b8(int a1, int a2, int a3, int a4, int a5, int a6, int a7);
extern int data_ov114_0229dac0;
extern int data_ov114_0229dae0;
extern int data_ov114_0229dad8;

void func_ov114_0229cbe4(UnkStruct_0229cbe4 *self, int arg1)
{
    int p6 = self->unk_1284;
    int vc = self->unk_1288 + arg1;
    int v10 = self->unk_1290;
    int i = 0;
    int neg_one = ~i;
    int v18, v1c, v20, reset;

    v1c = 0;
    v18 = 0;
    reset = 0;
    v20 = 0;

    do {
        int addr, v14;

        if (func_ov114_0229c1b8(self, self->unk_128C + i) != 0) {
            addr = (int) &self->arr[v10];
            v14 = neg_one;
        } else {
            addr = (int) &data_ov114_0229dac0;
            v14 = 4;
        }

        func_020896b8(1, addr, p6, vc, neg_one, 2, v18);

        if (self->unk_12B9 == (self->unk_128C + i)) {
            func_020896b8(1, (int) &data_ov114_0229dae0, p6, vc, neg_one, 2, v1c);
        }

        func_020896b8(1, (int) &data_ov114_0229dad8, p6, vc, v14, 2, v20);

        p6 += 0x1b;
        v10++;
        if (v10 >= 9) {
            v10 = reset;
        }
        i++;
    } while (i < 9);
}
