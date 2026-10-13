/* func_ov002_02208764 @ 0x02208764, 0x1a bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

struct S_02208764 {
    char pad_00[0xc];
    int unk_0C;
    char pad_10[0x8];
    unsigned char unk_18;
};

int func_ov002_02208764(struct S_02208764 *self)
{
    switch (self->unk_18) {
        case 2:
            return -self->unk_0C;
        case 3:
            return self->unk_0C;
        default:
            return 0;
    }
}
