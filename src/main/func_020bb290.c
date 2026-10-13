/* func_020bb290 @ 0x020bb290, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020bb290 {
    unsigned char pad_00[0x1520];
    int unk_1520;                 // offset 0x1520
    int unk_1524;                 // offset 0x1524
    unsigned char pad_1528[4];    // offset 0x1528
    int unk_152C;                 // offset 0x152c
    int unk_1530;                 // offset 0x1530
    unsigned char pad_1534[0x58]; // offset 0x1534..0x158b
    int unk_158C;                 // offset 0x158c
    int unk_1590;                 // offset 0x1590
};

void func_020bb290(struct UnkStruct_020bb290 *self)
{
    self->unk_1590++;
    if (self->unk_1590 < 0x2a8) {
        return;
    }
    if (self->unk_152C == self->unk_1524) {
        self->unk_158C = 0;
        self->unk_152C = -1;
        self->unk_1530 = 2;
        self->unk_1520 = 0;
        return;
    } else {
        self->unk_158C = 1;
        return;
    }
}
