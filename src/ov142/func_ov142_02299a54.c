/* func_ov142_02299a54 @ 0x02299a54, 0x2c bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x9c];
    int unk_9C;
    char pad_A0[4];
    int unk_A4;
    int unk_A8;
} OV142_02299A54_STRUCT;

extern void func_ov142_02299ab8(OV142_02299A54_STRUCT *self);

void func_ov142_02299a54(OV142_02299A54_STRUCT *self)
{
    if (self->unk_A4 > 0) {
        self->unk_A8 = (self->unk_9C * 90) / self->unk_A4;
        func_ov142_02299ab8(self);
    }
}
