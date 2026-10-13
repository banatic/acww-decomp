/* func_ov101_0229c944 @ 0x0229c944, 0x2a bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c944 {
    unsigned char pad_00[0xac];
    unsigned short unk_AC;
    unsigned char unk_AE;
    unsigned char unk_AF;
};

void func_ov101_0229cd40(struct UnkStruct_0229c944 *p, int a, unsigned short ac, unsigned char ae);

void func_ov101_0229c944(struct UnkStruct_0229c944 *p, int a)
{
    if (p->unk_AF == 1) {
        func_ov101_0229cd40(p, a, p->unk_AC, p->unk_AE);
    }
    p->unk_AF = 0;
}
