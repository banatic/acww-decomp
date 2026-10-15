/* func_ov101_0229d1f0 @ 0x0229d1f0, 0x50 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f9c(const unsigned char *p);
extern int func_ov101_0229cd80(const unsigned char *p, int parameter1);
extern void func_ov101_0229ca58(const unsigned char *p);
extern unsigned char *func_ov002_02208098(const unsigned char *p, unsigned char value);
extern void func_ov101_0229ce50(const unsigned char *p, unsigned char c, int n);
extern void func_ov101_0229ca00(const unsigned char *p);

void func_ov101_0229d1f0(unsigned char *p)
{
    if (func_ov002_02209f9c(p + 0x229C) == 0) {
        if (p[0xB3] == p[0xB5]) {
            func_ov101_0229cd80(
                p, (int) (*(
                       unsigned char *) ((char *) (((unsigned int) (((unsigned int) (((unsigned int) (p) + (0x0))) + (0x0))) +
                                                    (0xb5))) +
                                         0)));
            func_ov101_0229ca58(p);
            func_ov002_02208098(p, 6);
        } else {
            func_ov101_0229ce50(p, p[0xB5], 4);
        }
    } else {
        func_ov101_0229ca00(p);
    }
}
