/* func_ov003_0220f458 @ 0x0220f458, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200fbc4(void *a, int b, int c, int d);

void func_ov003_0220f458(int *p)
{
    int *base = p + 0x1f5;
    func_0200fbc4(p, base[0], base[2], 0xffff8000);
}
