/* func_020b14c0 @ 0x020b14c0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020b15b0(int x);
extern void func_020b198c(void *ptr, int x);

void func_020b14c0(int x)
{
    void *res;
    res = func_020b15b0(x);
    func_020b198c(res, x);
    *(unsigned short *) ((char *) res + 0x4A2) &= ~(1 << x);
}
