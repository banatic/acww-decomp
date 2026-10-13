/* func_ov125_022a063c @ 0x022a063c, 0x28 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(int, int);
extern void func_ov002_022080a0(int, int);
extern void func_ov125_0229fe98(int);
extern int func_ov125_022a0564(int);

int func_ov125_022a063c(int p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0(p, 2);
        func_ov125_0229fe98(p);
    }
    return func_ov125_022a0564(p);
}
