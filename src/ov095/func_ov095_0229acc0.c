/* func_ov095_0229acc0 @ 0x0229acc0, 0x58 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
    int unk_30;
} UnkStruct_0229acc0;

int func_ov095_0229acc0(UnkStruct_0229acc0 *p)
{
    if (p->unk_28 == 0x103) {
        return 1;
    }
    switch (p->unk_28) {
        case 0x104:
            p->unk_2C = 0xca;
            p->unk_30 = 0xb6;
            return 1;
        case 0x105:
            p->unk_2C = 0x58;
            p->unk_30 = 0xb6;
            return 1;
        case 0x106:
            p->unk_2C = 0x74;
            p->unk_30 = 0xb6;
            return 1;
    }
    return 0;
}
