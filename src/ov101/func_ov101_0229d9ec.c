/* func_ov101_0229d9ec @ 0x0229d9ec, 0x4c bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(char *p, int a);
extern void func_020027f0(int a);
extern void func_ov002_022080a0(char *p, int a);
extern void func_ov101_0229c28c(char *p, int a);
extern void func_ov002_02207e80(char *p, int a, int b, int c);
extern int func_ov002_02207f60(char *p);

void func_ov101_0229d9ec(char *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(6);
        func_ov002_022080a0(p, 5);
        func_ov101_0229c28c(p, 1);
        func_ov101_0229c28c(p, 2);
    } else {
        func_ov002_02207e80(p, 6, 0, -16);
    }
    *(int *) (p + 0x98) = func_ov002_02207f60(p);
}
