/* func_ov120_0229ac60 @ 0x0229ac60, 0x2a bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229ac60 {
    unsigned char pad_00[0xa3];
    unsigned char unk_A3;
    unsigned char pad_A4[5];
    unsigned char unk_A9;
} UnkStruct_0229ac60;

extern void func_ov120_0229abec(UnkStruct_0229ac60 *self, int idx);

int func_ov120_0229ac60(UnkStruct_0229ac60 *self)
{
    unsigned char val = self->unk_A9;
    int idx;

    if (val <= 5 || val == 13) {
        idx = 0;
    } else {
        idx = (val - 5) << 4;
    }

    func_ov120_0229abec(self, idx);
    self->unk_A3 = 0xff;
    return 0xff;
}
