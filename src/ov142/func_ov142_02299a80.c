/* func_ov142_02299a80 @ 0x02299a80, 0x36 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    int unk_A4;
    int unk_A8;
} OV142_02299A80_STRUCT;

extern void func_ov142_0229a4d4(OV142_02299A80_STRUCT *, int);

void func_ov142_02299a80(OV142_02299A80_STRUCT *self)
{
    int result;
    int a = self->unk_A4;
    result = (self->unk_A8 * a) / 0x5a;
    if (result < 0) {
        result = 0;
    }
    if (result > a) {
        result = a;
    }
    func_ov142_0229a4d4(self, result);
    self->unk_A0 = result;
}
