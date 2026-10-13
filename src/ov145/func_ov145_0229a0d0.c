/* func_ov145_0229a0d0 @ 0x0229a0d0, 0x2c bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x9c];
    int unk_9C;
    char pad_A0[4];
    int unk_A4;
    int unk_A8;
} OV142_02299A54_STRUCT;

extern void func_ov145_0229a134(OV142_02299A54_STRUCT *self);

void func_ov145_0229a0d0(OV142_02299A54_STRUCT *self)
{
    if (self->unk_A4 > 0) {
        self->unk_A8 = (self->unk_9C * 120) / self->unk_A4;
        func_ov145_0229a134(self);
    }
}
