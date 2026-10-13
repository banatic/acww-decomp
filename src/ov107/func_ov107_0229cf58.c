/* func_ov107_0229cf58 @ 0x0229cf58, 0x38 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov107_0229c2b4(void *, int);
extern void func_ov094_0229a6bc(void *, unsigned int, unsigned int);

struct UnkStruct_ov107 {
    char pad_00[0xa4];
    unsigned int unk_A4;
    unsigned int unk_A8;
    char pad_AC[9];
    unsigned char unk_B5;
    char pad_B6[86];
    char unk_10C;
};

void func_ov107_0229cf58(struct UnkStruct_ov107 *param)
{
    if (func_ov107_0229c2b4(param, 0x20) == 0) {
        if (param->unk_B5 != 0) {
            if (param->unk_B5 == 1) {
                func_ov094_0229a6bc(&param->unk_10C, param->unk_A4, param->unk_A8);
            }
        }
    }
}
