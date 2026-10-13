/* func_ov147_0229a000 @ 0x0229a000, 0x1c bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_0229a000 *data_021c526c;

struct UnkStruct_0229a000_2 {
    unsigned char pad_00[0xa3];
    unsigned char byte_at_a3;
};

struct UnkStruct_0229a000 {
    unsigned char pad_00[0x248];
    int unk_248;
};

void func_ov147_0229a000(struct UnkStruct_0229a000_2 *self)
{
    if (self->byte_at_a3 == 1) {
        data_021c526c->unk_248 = 0xb;
    }
}
