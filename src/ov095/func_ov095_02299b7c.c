/* func_ov095_02299b7c @ 0x02299b7c, 0x38 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299b7c {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
    char pad_30[4];
    int unk_34;
    char pad_38[11];
    unsigned char unk_43;
};

int func_ov095_02299b7c(struct UnkStruct_02299b7c *p)
{
    if (p->unk_28 == 0x103) {
        p->unk_2C = p->unk_34;
    }
    switch (p->unk_43) {
        case 1:
            return p->unk_2C - 0x100;
        case 2:
            return p->unk_2C + 0x100;
        default:
            return p->unk_2C;
    }
}
