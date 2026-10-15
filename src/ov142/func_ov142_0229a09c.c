/* func_ov142_0229a09c @ 0x0229a09c, 0x36 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a09c {
    char pad_00[0xc0];
    unsigned char unk_C0;
    char pad_C1[0xe8 - 0xc0 - 1];
    int value_e8;
};
extern int func_ov002_02209eec(int *ptr);
int func_ov142_0229a09c(struct UnkStruct_0229a09c *self)
{
    if (func_ov002_02209eec(&self->value_e8) < 0x2b) {
        self->unk_C0 = 0x15;
        return 0x15;
    } else if (func_ov002_02209eec(&self->value_e8) > 0x93) {
        self->unk_C0 = 0x16;
        return 0x16;
    } else {
        self->unk_C0 = 0x14;
        return 0x14;
    }
}
