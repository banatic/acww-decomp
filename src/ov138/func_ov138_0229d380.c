/* func_ov138_0229d380 @ 0x0229d380, 0x1e bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229d380 {
    char pad_00[0x8c];
    unsigned char unk_8C;
};

extern void func_ov138_0229cff4(struct UnkStruct_0229d380 *p, int a2);
extern void func_ov002_022080a0(struct UnkStruct_0229d380 *p, int a2);

int func_ov138_0229d380(struct UnkStruct_0229d380 *p, int a2)
{
    func_ov138_0229cff4(p, a2);
    p->unk_8C = 0;
    func_ov002_022080a0(p, 0);
    return 1;
}
