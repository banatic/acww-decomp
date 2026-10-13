/* func_ov004_02240408 @ 0x02240408, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02240e3c(void *, int, int, int, int, int);
void func_ov004_02240408(char *self)
{
    int *s;
    int *d;
    func_ov004_02240e3c(self, 0x1e, 0x14, 0x28, 0xf, 0x1000);
    *(int *) (self + 0x4c) = 0x71c;
    s = (int *) (self + 0x2c8);
    d = (int *) (self + 0x40);
    *(int *) (self + 0x40) = s[0];
    d[1] = s[1];
    d[2] = s[2];
    *(int *) (self + 0x44) = 0xb00;
}
