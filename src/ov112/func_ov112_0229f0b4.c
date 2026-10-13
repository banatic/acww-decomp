/* func_ov112_0229f0b4 @ 0x0229f0b4, 0x38 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070a98(void *p, int a, int b, int c, int d, int e, int f);
extern void func_02070a04(void *p, int a, int b);

void func_ov112_0229f0b4(void *base, int idx, int p2, int p3, int p4)
{
    void *p = (char *) base + 0x3fac + idx * 0x6c;
    func_02070a98(p, 4, p2, p3, 15, 10, p4);
    func_02070a04(p, 0, 0);
}
