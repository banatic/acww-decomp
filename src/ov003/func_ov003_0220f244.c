/* func_ov003_0220f244 @ 0x0220f244, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *p);
extern void func_0200e90c(void *p, int a, int b, int c);
extern int func_0200e894(void *a, void *b);
extern void func_0200e91c(void *p);

int func_ov003_0220f244(void *p0, char p1, int p2, int p3)
{
    char local[28];
    int result;
    func_0200e92c(local);
    func_0200e90c(local, 0x6d, p2, p3);
    local[12] = p1;
    result = func_0200e894(p0, local);
    func_0200e91c(local);
    return result;
}
