/* bank_menu_7: 3 functions, module ov132
 * mwccarm 1.2/base -O4,s
 * func_ov132_0229b868 @ 0x0229b868, 0x1e bytes, Thumb
 * func_ov132_0229b84c @ 0x0229b84c, 0x1a bytes, Thumb
 * func_ov132_0229b810 @ 0x0229b810, 0x3c bytes, Thumb
 */

extern void func_ov132_0229b564(void *object);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char arg1);
extern int func_020ee45c(int);
extern void func_ov092_0229929c(int);
extern void func_ov132_0229b534(int);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *);
extern int func_ov132_0229ad70(void *, int);
extern void *func_ov002_02207f60(void *);
extern void func_ov002_0220ad18(void *, void *);

int func_ov132_0229b868(void *obj)
{
    func_ov132_0229b564(obj);
    ((char *) obj)[0x8c] = 0;
    func_ov002_022080a0(obj, 0);
    return 1;
}

int func_ov132_0229b84c(int arg)
{
    func_ov092_0229929c(func_020ee45c(arg));
    func_ov132_0229b534(arg);
    return 1;
}

int func_ov132_0229b810(void *arg)
{
    void *res;
    if (func_0206fe54()) {
        func_ov002_02209eb8((char *) arg + 0x94);
    }
    if (!func_ov132_0229ad70(arg, 1)) {
        return 0;
    }
    res = func_ov002_02207f60(arg);
    arg = (char *) arg + 0xf8;
    func_ov002_0220ad18(arg, res);
    return 1;
}
