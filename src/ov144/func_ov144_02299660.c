/* func_ov144_02299660 @ 0x02299660, 0xe bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

struct func_ov144_02299660_unk {
    unsigned char pad_00[0xb4];
    unsigned short unk_B4;
};

void func_ov144_02299660(struct func_ov144_02299660_unk *self, unsigned short mask)
{
    self->unk_B4 &= ~mask;
}
