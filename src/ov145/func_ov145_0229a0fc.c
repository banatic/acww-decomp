/* func_ov145_0229a0fc @ 0x0229a0fc, 0x36 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    int unk_A4;
    int unk_A8;
} OV145_0229A0FC_STRUCT;

extern void func_ov145_02299b94(OV145_0229A0FC_STRUCT *, int);

void func_ov145_0229a0fc(OV145_0229A0FC_STRUCT *self)
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
    func_ov145_02299b94(self, result);
    self->unk_A0 = result;
}
