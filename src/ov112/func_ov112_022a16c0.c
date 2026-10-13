/* func_ov112_022a16c0 @ 0x022a16c0, 0x3e bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *p, int a);
extern int func_ov002_022080a0(void *p, int a);
extern int func_0206fe60(int a);
extern int func_ov002_02207f60(void *p);
extern void func_ov112_0229fee4(void *p);
extern void func_ov112_0229fe84(void *p);

void func_ov112_022a16c0(void *p)
{
    if (func_ov002_02207f48(p, -1) != 0) {
        if (func_0206fe60(func_ov002_022080a0(p, 2)) != 0) {
            func_ov112_0229fee4(p);
        } else {
            func_ov112_0229fe84(p);
        }
    }
    *(int *) ((char *) p + 0xa8) = func_ov002_02207f60(p);
}
