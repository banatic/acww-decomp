/* func_ov112_0229f984 @ 0x0229f984, 0x38 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229f984 {
    char pad_00[0xb8];
    unsigned char byte_at_0xb8;
};

extern unsigned char data_021f6c54;
extern void func_020e8a38(unsigned char *ptr, unsigned char val, int count);
extern void func_ov112_0229f9dc(struct UnkStruct_0229f984 *self, unsigned char val);

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
    func_ov112_0229f9dc(self, self->byte_at_0xb8);
}
