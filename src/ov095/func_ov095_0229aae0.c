/* func_ov095_0229aae0 @ 0x0229aae0, 0x86 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O1,s
 */

typedef struct UnkStruct_0229aae0 {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
    int unk_30;
} UnkStruct_0229aae0;

extern int func_ov095_0229ac2c(UnkStruct_0229aae0 *);

void func_ov095_0229aae0(UnkStruct_0229aae0 *a)
{
    int v;

    if (func_ov095_0229ac2c(a) != 0) {
        return;
    }
    v = a->unk_28;
    if (v < 0x70) {
        return;
    }
    if (v <= 0x8d) {
        v -= 0x70;
        a->unk_2C = (v % 10) * 20 + 0x12;
        a->unk_30 = ((v / 10) * 2 + 14) * 8;
    } else {
        switch (v) {
            case 0x8e:
                a->unk_2C = 0xda;
                a->unk_30 = 0x70;
                break;
            case 0x8f:
                a->unk_2C = 0xee;
                a->unk_30 = 0x70;
                break;
            case 0x90:
                a->unk_2C = 0xe4;
                a->unk_30 = 0x88;
                break;
            case 0x91:
                a->unk_2C = 0x80;
                a->unk_30 = 0xa0;
                break;
        }
    }
}
