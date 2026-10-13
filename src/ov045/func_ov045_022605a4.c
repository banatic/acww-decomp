/* func_ov045_022605a4 @ 0x022605a4, 0x74 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);

struct UnkStruct_022605a4 {
    char pad_00[0x744];
    unsigned char unk_744;
    unsigned char unk_745;
    char pad_746[6];
    unsigned char unk_74C;
    char pad_74D[3];
    int unk_750;
};

void func_ov045_022605a4(struct UnkStruct_022605a4 *self)
{
    int v;
    int base;

    self->unk_74C = func_020644cc(0x16);

    if (func_020644cc(2) == 0) {
        self->unk_750 = 0;
    } else {
        self->unk_750 = 1;
    }

    v = func_020644cc(2);
    base = self->unk_74C * 2 + 0x1a;
    self->unk_744 = (unsigned char) (base + v + 0x2c * self->unk_750);
    self->unk_745 = (unsigned char) (self->unk_74C + 0x72 + 0x16 * self->unk_750);
}
