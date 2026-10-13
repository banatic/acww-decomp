/* func_ov138_0229cff4 @ 0x0229cff4, 0x38 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_0229bd38(unsigned char *p, int, int, int, int);
extern void func_ov134_0229bd2c(unsigned char *p);

void func_ov138_0229cff4(unsigned char *self)
{
    func_ov134_0229bd38(self + 0x2c8, 3, 6, 4, 3);
    func_ov134_0229bd2c(self + 0x2c8);
    self[0x95] = 0;
    *(unsigned short *) (self + 0x92) = 0;
}
