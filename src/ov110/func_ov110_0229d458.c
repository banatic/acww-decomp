/* func_ov110_0229d458 @ 0x0229d458, 0x50 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d5e4(void *a, int b);
extern int func_ov110_0229d5d4(void *a, int b);
extern int func_ov110_0229d590(void *a, int b);
extern void func_ov094_0229aa14(void *p, int v, int c, int d);
extern void func_ov094_0229a9b4(void *p, int v);

void func_ov110_0229d458(void *a, int b, int c, int d)
{
    if (func_ov110_0229d5e4(a, b) != 0 || func_ov110_0229d5d4(a, b) != 0) {
        int v;
        v = func_ov110_0229d590(a, b);
        func_ov094_0229aa14((char *) a + 0x138, v, c, d);
        func_ov094_0229a9b4((char *) a + 0x138, v);
    }
}
