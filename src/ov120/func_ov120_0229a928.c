/* func_ov120_0229a928 @ 0x0229a928, 0x8c bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa7];
    unsigned char unk_A7;
    char pad_A8;
    unsigned char unk_A9;
} SelfType;

extern int func_ov120_0229a448(SelfType *self, int param);
extern void func_ov120_0229a428(SelfType *self, int param);
extern void func_ov120_0229a438(SelfType *self, int param);
extern void func_ov120_0229ad5c(SelfType *self, unsigned char param);

void func_ov120_0229a928(SelfType *self)
{
    if (!func_ov120_0229a448(self, 0x40)) {
        return;
    }

    if (self->unk_A7) {
        self->unk_A7--;
    }

    if (self->unk_A7 == 0) {
        if (func_ov120_0229a448(self, 0x200) != 0) {
            func_ov120_0229a428(self, 0x100);
        } else {
            func_ov120_0229ad5c(self, self->unk_A9);
        }
        self->unk_A7 = 0x0f;
    } else {
        if (self->unk_A7 == 5) {
            if (func_ov120_0229a448(self, 0x200) != 0) {
                func_ov120_0229a438(self, 0x100);
            } else {
                func_ov120_0229ad5c(self, 0xe);
            }
        }
    }
}
