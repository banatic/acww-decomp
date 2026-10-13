/* func_ov125_0229fb1c @ 0x0229fb1c, 0x18 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229fb1c {
    unsigned char pad_00[0x87c];
    unsigned char unk_87C;
};

extern int func_ov125_0229fe40(struct UnkStruct_0229fb1c *, unsigned char);

int func_ov125_0229fb1c(struct UnkStruct_0229fb1c *self)
{
    return func_ov125_0229fe40(self, self->unk_87C) - 11;
}
