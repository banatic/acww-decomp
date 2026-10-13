/* func_ov004_0221984c @ 0x0221984c, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220d280(void *p, int a, int b);
extern void func_ov004_0220d058(void *p, int a, int b, int c);
int func_ov004_0221984c(unsigned char *self)
{
    *(int *) (self + 0x848) = 0;
    func_ov004_0220d280(self + 0x740, 0, 0);
    func_ov004_0220d058(self + 0x84c, 0, 1, 0);
    return 1;
}
