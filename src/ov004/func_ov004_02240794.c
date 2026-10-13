/* func_ov004_02240794 @ 0x02240794, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int k);
extern void func_ov004_022407e4(void *self, int a, int b, int c, int d, int e, int f);

void func_ov004_02240794(void *self)
{
    int *p;

    if (func_020644cc(0x64) > 0x32) {
        p = (int *) ((char *) self + 0x2c8);
        p[0] = 0x1a600;
        p[1] = 0x1400;
        p[2] = 0x13c00;
    }
    func_ov004_022407e4(self, 0xc8, 0x3c, 0x28, 0x14, 1, 0xcd);
}
