/* func_ov125_022a0984 @ 0x022a0984, 0x1e bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x8c];
    char unk_8C;
} UnkStruct_022a0984;

extern void func_ov125_022a0510(UnkStruct_022a0984 *p);
extern unsigned char *func_ov002_022080a0(UnkStruct_022a0984 *p, unsigned char arg1);

int func_ov125_022a0984(UnkStruct_022a0984 *p)
{
    func_ov125_022a0510(p);
    p->unk_8C = 0;
    func_ov002_022080a0(p, 0);
    return 1;
}
