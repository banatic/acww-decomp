/* func_ov094_0229a47c @ 0x0229a47c, 0x44 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);

struct UnkStruct_0229a47c {
    char pad_00[0xa54];
    unsigned short unk_A54;
    char pad_A56[4];
    unsigned char unk_A5A;
    unsigned char unk_A5B;
    unsigned char unk_A5C;
};

void func_ov094_0229a47c(struct UnkStruct_0229a47c *self, unsigned short value, int mode)
{
    self->unk_A54 = value;
    self->unk_A5A = 0;
    if (mode == 1) {
        self->unk_A5B = 0;
    } else {
        self->unk_A5B = 1;
    }
    if (func_0206fe60() != 0) {
        self->unk_A5C = 0;
    }
}
