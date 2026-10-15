/* func_ov003_02217070 @ 0x02217070, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_022171ac(char *src, int *b, int *c, int *a);
extern int func_ov003_022171ec(char *p, int *b, int *c, int *a, int p5, int p6);

void func_ov003_02217070(char *p1, int p2)
{
    int a, b, c;
    func_ov003_022171ac(p1 + 0x8f0, &b, &c, &a);
    func_ov003_022171ec(p1, &b, &c, &a, 6, p2);
}
