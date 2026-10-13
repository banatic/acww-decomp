/* func_ov144_0229a3a4 @ 0x0229a3a4, 0x36 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    int unk_A4;
    int unk_A8;
} OV144_0229A3A4_STRUCT;

extern void func_ov144_02299e6c(OV144_0229A3A4_STRUCT *, int);

void func_ov144_0229a3a4(OV144_0229A3A4_STRUCT *self)
{
    int result;
    int a = self->unk_A4;
    result = (self->unk_A8 * a) / 0x78;
    if (result < 0) {
        result = 0;
    }
    if (result > a) {
        result = a;
    }
    func_ov144_02299e6c(self, result);
    self->unk_A0 = result;
}
