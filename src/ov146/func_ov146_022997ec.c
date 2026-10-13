/* func_ov146_022997ec @ 0x022997ec, 0x4c bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209eec(char *p);

struct UnkStruct_022997ec {
    char pad_00[0xa8];
    int unk_A8;
    char pad_AC[6];
    unsigned char unk_B2;
    char pad_B3[3];
    unsigned char unk_B6;
    char pad_B7[0x1515];
    char unk_15CC;
};

void func_ov146_022997ec(struct UnkStruct_022997ec *param)
{
    int val;

    if (param->unk_B6 == 0) {
        param->unk_B2 = 1;
        return;
    }
    val = func_ov002_02209eec(&param->unk_15CC);
    if (val < 0x38) {
        val = 0x38;
    }
    if (val > 0xa7) {
        val = 0xa7;
    }
    val = val - (0x38 - (param->unk_A8 & 0xf));
    val = (val >> 4) + 3;
    param->unk_B2 = (unsigned char) val;
}
