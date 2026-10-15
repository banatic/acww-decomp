/* func_ov095_0229bcec @ 0x0229bcec, 0x54 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_022999a8(int a, int b);
extern void func_ov095_022999a0(int a, int b);
extern int func_ov095_0229bd40(int a, int b, int c, int d, int e, int f, int g);

int func_ov095_0229bcec(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7)
{
    if (p6) {
        func_ov095_022999a8(p0, 0x100);
    } else {
        func_ov095_022999a0(p0, 0x40);
        func_ov095_022999a0(p0, 0x80);
        func_ov095_022999a0(p0, 0x100);
    }
    return func_ov095_0229bd40(p0, p1, p2, p3, p4, p6, p7);
}
