/* func_ov112_0229f730 @ 0x0229f730, 0x54 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229f730 {
    unsigned char pad_00[0xB7];
    unsigned char unk_B7;
    unsigned char pad_B8[5];
    unsigned char unk_BD;
    unsigned char pad_BE[1];
    unsigned char unk_BF;
};

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern void func_ov112_0229f7f0(struct UnkStruct_0229f730 *, int, int);

int func_ov112_0229f730(struct UnkStruct_0229f730 *param)
{
    int a = data_021f6c58;
    int b = data_021f6c54;
    int c = param->unk_BD;
    if (a < 0x30) {
        a = 0x30;
    }
    b += param->unk_B7 + 8;
    func_ov112_0229f7f0(param, a, b);
    param->unk_BF = param->unk_BD;
    return (param->unk_BD == c) ? 0 : 1;
}
