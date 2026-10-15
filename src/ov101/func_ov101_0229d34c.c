/* func_ov101_0229d34c @ 0x0229d34c, 0x4c bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov002_02209114(void *, unsigned char, int);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);

void func_ov101_0229d34c(unsigned char *p)
{
    if (func_0208e484(p + 0x229c)) {
        func_ov002_02209114(p + 0x2300, p[0xb8], 1);
        p[0xb7] = *(p + p[0xb8] + 0x26ed);
        func_ov002_02208098(p, 0x14);
    }
}
