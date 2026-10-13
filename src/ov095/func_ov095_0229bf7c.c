/* func_ov095_0229bf7c @ 0x0229bf7c, 0x5c bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_022999b0(void *p, int mode);
extern int func_020b9bbc(void *a, void *b, void *c, int d, int e);
extern void func_ov095_022999a0(void *p, int mode);

void func_ov095_0229bf7c(void *p, void *q)
{
    if (func_ov095_022999b0(p, 1)) {
        if (func_020b9bbc((char *) p + 0x232c, (char *) p + 0x2428, q, 0x800, 0)) {
            func_ov095_022999a0(p, 1);
        }
    }
    func_ov095_022999a0(p, 2);
    func_ov095_022999a0(p, 0x200);
}
