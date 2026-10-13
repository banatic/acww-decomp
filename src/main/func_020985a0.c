/* func_020985a0 @ 0x020985a0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138d6c(void *a, int b, int c, void (*d)(void), void (*e)(void));
extern void func_02099ad0(void);
extern void func_02099bc8(void);

void *func_020985a0(void *arg)
{
    func_02138d6c(arg, 3, 0x249c, func_02099bc8, func_02099ad0);
    return arg;
}
