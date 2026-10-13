/* func_020b0730 @ 0x020b0730, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b076c(int *a, int *b, int arg0);
extern int func_0204e414(void);
extern void func_0204f538(int arg0, unsigned short *arg1, int arg2, int arg3, int arg4);

int func_020b0730(int arg0)
{
    unsigned short u16;
    int a, b;
    if (func_020b076c(&a, &b, arg0)) {
        int tmp = func_0204e414();
        u16 = 0xfff1;
        func_0204f538(tmp, &u16, a, b, 0);
        return 1;
    }
    return 1;
}
