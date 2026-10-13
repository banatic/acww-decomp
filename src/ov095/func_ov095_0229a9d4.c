/* func_ov095_0229a9d4 @ 0x0229a9d4, 0x68 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_022999b0(void *, int);

typedef struct UnkStruct_0229a9d4 {
    char pad_00[0x28];
    int unk_28;
    char pad_2C[0x16];
    unsigned char unk_42;
} UnkStruct_0229a9d4;

void func_ov095_0229a9d4(UnkStruct_0229a9d4 *p)
{
    unsigned char v = p->unk_42;
    switch (v) {
        case 0:
            break;
        case 1:
            if (func_ov095_022999b0(p, 8)) {
                p->unk_28 = 0x104;
            } else {
                p->unk_28 = 0x105;
            }
            break;
        case 2:
            p->unk_28 = 0x106;
            break;
        case 5:
            p->unk_28 = 0x108;
            break;
        case 4:
            p->unk_28 = 0x107;
            break;
    }
}
