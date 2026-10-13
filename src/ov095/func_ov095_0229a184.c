/* func_ov095_0229a184 @ 0x0229a184, 0x50 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a184 {
    char pad_00[0x16];
    unsigned char unk_16;
    char pad_17[0x11];
    int unk_28;
};

extern int data_ov095_0229cfdc[];
extern int data_ov095_0229cf8c[];
extern int data_ov095_0229cfc8[];
extern int data_ov095_0229cf78[];
extern int _s32_div_f(int, int);
extern void func_ov095_0229aa74(struct UnkStruct_0229a184 *);

void func_ov095_0229a184(struct UnkStruct_0229a184 *self, int val)
{
    int idx;
    int a1;
    int sum;
    int a3;

    idx = self->unk_16;
    a1 = data_ov095_0229cfdc[idx];
    if (val < a1) {
        val = a1;
    }
    sum = _s32_div_f(val - a1, 20);
    sum += data_ov095_0229cf8c[idx];
    a3 = data_ov095_0229cfc8[idx];
    if (sum > a3) {
        sum = data_ov095_0229cf78[idx];
    }
    self->unk_28 = sum;
    func_ov095_0229aa74(self);
}
