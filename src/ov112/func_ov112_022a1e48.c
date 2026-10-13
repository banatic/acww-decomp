/* func_ov112_022a1e48 @ 0x022a1e48, 0x1e bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov112_022a1310(void *p);
extern void func_ov002_022080a0(void *p);

struct UnkStruct_ov112_022a1e48 {
    char pad_00[0x8c];
    char unk_8C;
};

int func_ov112_022a1e48(struct UnkStruct_ov112_022a1e48 *p)
{
    func_ov112_022a1310(p);
    p->unk_8C = 0;
    func_ov002_022080a0(p);
    return 1;
}
