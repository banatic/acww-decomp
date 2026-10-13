/* func_ov095_0229ac8c @ 0x0229ac8c, 0x34 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229ac8c {
    unsigned char pad_00[0x28];
    int unk_28;
    int unk_2C;
    int unk_30;
};

int func_ov095_0229ac8c(struct UnkStruct_0229ac8c *s)
{
    switch (s->unk_28) {
        case 0x107:
            s->unk_2C = 0xc4;
            s->unk_30 = 0xb6;
            return 1;
        case 0x108:
            s->unk_2C = 0x7c;
            s->unk_30 = 0xb6;
            return 1;
        default:
            return 0;
    }
}
