/* bbs_write_text_7: 2 functions, module ov112
 * mwccarm 1.2/base -O4,s
 * func_ov112_0229f9bc @ 0x0229f9bc, 0x20 bytes, Thumb
 * func_ov112_0229f984 @ 0x0229f984, 0x38 bytes, Thumb
 */

struct UnkStruct_0229f9bc {
    char pad_00[0xB9];
    unsigned char unk_B9;
    unsigned char unk_BA;
};

struct UnkStruct_0229f984 {
    char pad_00[0xb8];
    unsigned char byte_at_0xb8;
};

extern unsigned char data_021f6c54;
extern void func_ov112_0229f9dc(void *self, int value);
extern int func_020e8a38(unsigned char *ptr, unsigned char val, int count);

void func_ov112_0229f9bc(struct UnkStruct_0229f9bc *self)
{
    func_ov112_0229f9dc(self, self->unk_BA + (data_021f6c54 - self->unk_B9));
}

void func_ov112_0229f984(struct UnkStruct_0229f984 *self)
{
    int t = data_021f6c54 - 0x18;
    if (t < 0) {
        t = 0;
    }
    if (t > 0x28) {
        t = 0x28;
    }
    func_020e8a38(&self->byte_at_0xb8, (unsigned char) t, 2);
    func_ov112_0229f9dc((void *) self, (unsigned char) self->byte_at_0xb8);
}
