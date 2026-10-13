/* func_ov101_0229da98 @ 0x0229da98, 0x3a bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *p, int a);
extern void func_ov002_022080a0(void *p, int a);
extern void func_ov101_0229cf80(void *p);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);

void func_ov101_0229da98(void *p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0(p, 2);
        func_ov101_0229cf80(p);
    }
    func_ov002_02207e80(p, 6, 0, ~0xf);
    *(int *) ((char *) p + 0x98) = func_ov002_02207f60(p);
}
