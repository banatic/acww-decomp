/* func_ov120_0229ac08 @ 0x0229ac08, 0x58 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229ac08;

extern void func_ov120_0229abdc(struct UnkStruct_0229ac08 *self, int index);

struct UnkStruct_0229ac08 {
    unsigned char pad_00[0x98];
    unsigned short unk_98;
    unsigned char pad_9A[0xf];
    unsigned char unk_A9;
};

void func_ov120_0229ac08(struct UnkStruct_0229ac08 *self)
{
    unsigned char v;
    unsigned short cnt;
    int m, r1, r2;

    v = self->unk_A9;
    if (v == 0xe) {
        return;
    }
    if (v == 0xd) {
        func_ov120_0229abdc(self, 0);
        return;
    }
    cnt = self->unk_98;
    m = (cnt + 15) >> 4;
    if (v < m) {
        func_ov120_0229abdc(self, v << 4);
    }
    r1 = self->unk_98 >> 4;
    v = self->unk_A9;
    if (v <= 5) {
        r2 = 0;
    } else {
        r2 = v - 5;
    }
    if (r1 < r2) {
        func_ov120_0229abdc(self, r2 << 4);
    }
}
