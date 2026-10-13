/* func_ov112_0229f9bc @ 0x0229f9bc, 0x20 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c54;
extern int func_ov112_0229f9dc(void *self, int value);

struct UnkStruct_0229f9bc {
    char pad_00[0xB9];
    unsigned char unk_B9;
    unsigned char unk_BA;
};

int func_ov112_0229f9bc(struct UnkStruct_0229f9bc *self)
{
    return func_ov112_0229f9dc(self, self->unk_BA + (data_021f6c54 - self->unk_B9));
}
