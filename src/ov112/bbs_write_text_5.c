/* bbs_write_text_5: 3 functions, module ov112
 * mwccarm 1.2/base -O4,s
 * func_ov112_0229f788 @ 0x0229f788, 0x68 bytes, Thumb
 * func_ov112_0229f784 @ 0x0229f784, 0x2 bytes, Thumb
 * func_ov112_0229f730 @ 0x0229f730, 0x54 bytes, Thumb
 */

typedef struct my_struct {
    unsigned char pad_00[0xb7];
    unsigned char b7;
    unsigned char pad_B8[5];
    unsigned char bd;
    unsigned char be;
    unsigned char bf;
} my_struct;

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
extern void func_ov112_0229f7f0(my_struct *P, int a, int b);
extern void func_ov112_0229fe60(my_struct *P, int v);

int func_ov112_0229f788(my_struct *P)
{
    int g1 = data_021f6c58;
    int g2 = data_021f6c54;

    if (g2 >= 0x48) {
        return 0;
    }
    if (g1 < 0x20 || g1 >= 0xe0) {
        return 0;
    }

    g2 += (P->b7 + 8);
    if (g1 < 0x30) {
        g1 = 0x30;
    }

    func_ov112_0229f7f0(P, g1, g2);
    func_ov112_0229fe60(P, 0x100);

    P->be = P->bd;
    P->bf = P->bd;
    return 1;
}

void func_ov112_0229f784(void *receiver) {}

int func_ov112_0229f730(struct UnkStruct_0229f730 *param)
{
    int a = data_021f6c58;
    int b = data_021f6c54;
    int c = param->unk_BD;
    if (a < 0x30) {
        a = 0x30;
    }
    b += param->unk_B7 + 8;
    func_ov112_0229f7f0((my_struct *) param, a, b);
    param->unk_BF = param->unk_BD;
    return (param->unk_BD == c) ? 0 : 1;
}
