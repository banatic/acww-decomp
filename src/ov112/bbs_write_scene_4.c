/* bbs_write_scene_4: 2 functions, module ov112
 * mwccarm 1.2/base -O4,s
 * func_ov112_022a1e48 @ 0x022a1e48, 0x1e bytes, Thumb
 * func_ov112_022a1e2c @ 0x022a1e2c, 0x1a bytes, Thumb
 */

struct UnkStruct_ov112_022a1e48 {
    char pad_00[0x8c];
    char unk_8C;
};

extern void func_ov112_022a1310(void *p);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char arg1);
extern int func_020ee45c(void *obj);
extern void func_ov092_0229929c(void *);
extern void func_ov112_022a12dc(void *obj);

int func_ov112_022a1e48(struct UnkStruct_ov112_022a1e48 *p)
{
    func_ov112_022a1310(p);
    p->unk_8C = 0;
    func_ov002_022080a0(p, 0);
    return 1;
}

int func_ov112_022a1e2c(void *obj)
{
    func_ov092_0229929c((void *) func_020ee45c(obj));
    func_ov112_022a12dc(obj);
    return 1;
}
