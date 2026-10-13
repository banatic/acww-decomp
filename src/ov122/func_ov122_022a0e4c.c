/* func_ov122_022a0e4c @ 0x022a0e4c, 0x44 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov122_0229f958(void *p);
extern void func_ov122_0229f89c(void *p);
extern void func_ov095_0229b3ec(void *p);
extern void func_ov122_0229f9a8(void *p);
extern int func_ov122_022a0e90(void *p, void *q, int c);
extern void func_ov122_022a15b8(void *p, int a, int c);

int func_ov122_022a0e4c(void *p, void *q)
{
    int v;
    if (func_ov122_0229f958(p)) {
        func_ov122_0229f89c(p);
        func_ov095_0229b3ec((char *) p + 0xc0);
    }
    v = func_ov122_022a0e90(p, q, 1);
    func_ov122_022a15b8(p, 0, 1);
    func_ov122_0229f9a8(p);
    return v;
}
