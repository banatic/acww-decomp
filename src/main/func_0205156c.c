/* func_0205156c @ 0x0205156c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020516b8(int a, int key);
extern int func_0205171c(int a, int b);

struct UnkStruct_0205156c {
    unsigned char pad_00[0x28];
    int unk_28; // 0x28
    unsigned char pad_2C[0x08];
    int unk_34; // 0x34
    unsigned char pad_38[0x2C];
    int unk_64; // 0x64
    int unk_68; // 0x68
};

void func_0205156c(struct UnkStruct_0205156c *self, int key)
{
    int tmp;

    self->unk_64 = func_020516b8(self->unk_28, key);
    if (self->unk_64 == -1) {
        self->unk_64 = func_020516b8(self->unk_28, 0xff20);
    }

    tmp = func_0205171c(self->unk_28, self->unk_64);
    self->unk_68 = self->unk_68 + tmp;
    self->unk_68 = self->unk_68 + self->unk_34;
}
