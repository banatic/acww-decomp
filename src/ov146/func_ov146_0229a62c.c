/* func_ov146_0229a62c @ 0x0229a62c, 0x78 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov146_0229a5e8(void *);
extern int func_ov146_0229a59c(void *);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov002_0220a374(void *, int);
extern void func_ov146_0229a4b0(void *);

typedef struct {
    unsigned char pad_00[0xa8];
    unsigned int unk_A8;
    unsigned char pad_AC[0xb2 - 0xa8 - 4];
    unsigned char unk_B2;
    unsigned char pad_B3[0x15cc - 0xb2 - 1];
    int unk_15CC;
} UnkStruct_0229a62c;

void func_ov146_0229a62c(UnkStruct_0229a62c *param)
{
    if (param->unk_B2 == 3) {
        unsigned int mask = param->unk_A8 & 0xf;
        if (mask) {
            param->unk_A8 -= mask;
        }
    }
    {
        int v1 = func_ov146_0229a5e8(param);
        int v2 = func_ov146_0229a59c(param);
        func_ov002_0220a0b4(&param->unk_15CC, v1, v2);
    }
    if (param->unk_B2 == 2) {
        func_ov002_0220a374(&param->unk_15CC, 1);
    } else {
        func_ov002_0220a374(&param->unk_15CC, 7);
    }
    func_ov146_0229a4b0(param);
}
