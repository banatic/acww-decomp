/* town_map_list_5: 2 functions, module ov120
 * mwccarm 1.2/base -O4,s
 * func_ov120_0229ac60 @ 0x0229ac60, 0x2a bytes, Thumb
 * func_ov120_0229ac08 @ 0x0229ac08, 0x58 bytes, Thumb
 */

typedef struct UnkStruct_0229ac60 {
    unsigned char pad_00[0xa3];
    unsigned char unk_A3;
    unsigned char pad_A4[5];
    unsigned char unk_A9;
} UnkStruct_0229ac60;

struct UnkStruct_0229ac08;

struct UnkStruct_0229ac08 {
    unsigned char pad_00[0x98];
    unsigned short unk_98;
    unsigned char pad_9A[0xf];
    unsigned char unk_A9;
};

extern void func_ov120_0229abec(UnkStruct_0229ac60 *self, int idx);
extern void func_ov120_0229abdc(struct UnkStruct_0229ac08 *self, int index);

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
