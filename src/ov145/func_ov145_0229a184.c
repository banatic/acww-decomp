/* func_ov145_0229a184 @ 0x0229a184, 0x8c bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a184 {
    char pad_00[0xa8];
    int unk_A8;
    char pad_AC[0x80];
    char unk_12C[1];
};

extern unsigned short data_021fbe40;
extern void func_ov145_0229a0fc(struct UnkStruct_0229a184 *);
extern void func_ov145_0229a134(struct UnkStruct_0229a184 *);
extern void func_ov002_0220a4c8(void *receiver);

void func_ov145_0229a184(struct UnkStruct_0229a184 *self)
{
    int orig = self->unk_A8;
    if (data_021fbe40 & 0x40) {
        self->unk_A8 -= 4;
        if (self->unk_A8 < 0) {
            self->unk_A8 = 0;
        }
    } else if (data_021fbe40 & 0x80) {
        self->unk_A8 += 4;
        if (self->unk_A8 > 0x78) {
            self->unk_A8 = 0x78;
        }
    }
    if (orig != self->unk_A8) {
        func_ov145_0229a0fc(self);
        func_ov145_0229a134(self);
        func_ov002_0220a4c8(self->unk_12C);
    }
}
