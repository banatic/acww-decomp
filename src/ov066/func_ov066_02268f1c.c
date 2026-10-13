/* func_ov066_02268f1c @ 0x02268f1c, 0x7c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    unsigned char pad_00[0x0c];
    unsigned int unk_0C;
    unsigned short unk_10;
    unsigned short unk_12;
} UnkStruct_02268f1c;

extern void MI_CpuCopy8(unsigned int, void *, int);
extern void func_ov066_02268ed4(unsigned short, unsigned int);

void func_ov066_02268f1c(UnkStruct_02268f1c *s)
{
    unsigned short v;
    if (s->unk_10 == 0) {
        return;
    }
    MI_CpuCopy8(s->unk_0C, &v, 4);
    if (v == 0) {
        return;
    }
    if (v == 1) {
        return;
    }
    if (v != 2) {
        return;
    }
    func_ov066_02268ed4(s->unk_12, s->unk_0C);
    return;
}
