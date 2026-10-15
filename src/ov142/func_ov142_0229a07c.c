/* func_ov142_0229a07c @ 0x0229a07c, 0x1e bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a07c {
    unsigned char pad_00[0xa4];
    void *unk_A4;
};

extern int func_ov142_0229a09c(struct UnkStruct_0229a07c *self);
extern int func_ov142_0229a0d4(struct UnkStruct_0229a07c *self);

int func_ov142_0229a07c(struct UnkStruct_0229a07c *self)
{
    if (self->unk_A4 == 0) {
        return func_ov142_0229a0d4(self);
    } else {
        return func_ov142_0229a09c(self);
    }
}
