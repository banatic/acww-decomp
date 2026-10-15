/* func_ov003_02215164 @ 0x02215164, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02215234(unsigned char *addr, unsigned char *out);
extern int func_ov003_02215240(unsigned char *addr, unsigned char v, int n, int arg2);

void func_ov003_02215164(unsigned char *base, int arg2)
{
    unsigned char val;
    func_ov003_02215234(base + 0x8f0, &val);
    func_ov003_02215240(base, val, 6, arg2);
}
