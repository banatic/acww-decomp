/* func_ov004_0222a3cc @ 0x0222a3cc, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222a450(void *dst, int *x, int *y, short *z);
extern int func_ov004_0222a494(void *self, int x, int y, short z, int a, int k);
void func_ov004_0222a3cc(unsigned char *self, int k)
{
    short z;
    int x, y;
    func_ov004_0222a450(self + 0x8f0, &x, &y, &z);
    func_ov004_0222a494(self, x, y, z, 5, k);
}
