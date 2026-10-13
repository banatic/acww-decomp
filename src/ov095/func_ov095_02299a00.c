/* func_ov095_02299a00 @ 0x02299a00, 0x52 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02299a00 UnkStruct_02299a00;
struct UnkStruct_02299a00 {
    unsigned char pad_00[0x16];
    unsigned char unk_16;
    unsigned char pad_17[0x24 - 0x17];
    int unk_24;
    int unk_28;
};

extern int func_ov095_0229ce08(UnkStruct_02299a00 *p, int val);

int func_ov095_02299a00(UnkStruct_02299a00 *p)
{
    if (func_ov095_0229ce08(p, p->unk_28) != 0) {
        return -1;
    }
    switch (p->unk_28) {
        case 0xf8:
            if (p->unk_16 == 4) {
                return -1;
            }
            break;
        case 0xf9:
            if (p->unk_16 == 1) {
                return -1;
            }
            break;
        case 0xfa:
            if (p->unk_16 == 2) {
                return -1;
            }
            break;
    }
    p->unk_24 = p->unk_28;
    return p->unk_28;
}
