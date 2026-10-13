/* func_ov003_0221a190 @ 0x0221a190, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020d1a10[4];

struct UnkStruct_0221a190 {
    unsigned char pad_00[0x2f8];
    unsigned int unk_2F8;
    unsigned int unk_2FC;
    unsigned int unk_300;
    unsigned int unk_304;
    unsigned char pad_308[0x70];
    unsigned short unk_378;
};

int func_ov003_0221a190(struct UnkStruct_0221a190 *self)
{
    self->unk_378 &= ~0x10;
    self->unk_378 |= 0x20;
    self->unk_2F8 = data_020d1a10[0];
    self->unk_2FC = data_020d1a10[1];
    self->unk_300 = data_020d1a10[2];
    self->unk_304 = data_020d1a10[3];
    return 1;
}
