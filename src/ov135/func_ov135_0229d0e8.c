/* func_ov135_0229d0e8 @ 0x0229d0e8, 0x40 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_0229bd38(void *param, int a, int b, int c, int d);
extern int func_0206fca4(void);
extern void func_ov134_0229bd2c(void *param);

void func_ov135_0229d0e8(unsigned char *p)
{
    func_ov134_0229bd38(p + 0x2c8, 0, 6, 4, 3);
    if (func_0206fca4() == 0x33) {
        func_ov134_0229bd2c(p + 0x2c8);
    }
    *(p + 0x95) = 0;
    *(unsigned short *) (p + 0x92) = 0;
}
