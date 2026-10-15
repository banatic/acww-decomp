/* func_02083d78 @ 0x02083d78, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208602c(void);
extern int func_020860b8(int);
extern int func_02087854(int, int);
extern int func_020644cc(int) __attribute__((arm));

int func_02083d78(int a, int b, unsigned short *out)
{
    int x;
    int y;
    x = func_0208602c();
    y = func_020860b8(x);
    func_02087854(y, b);
    out[1] = (unsigned short) func_020644cc(0xffff);
    return 1;
}
