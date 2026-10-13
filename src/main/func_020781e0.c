/* func_020781e0 @ 0x020781e0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020782d0(void);
extern void func_02138c48(void *a, int b, int c, void (*d)(void));

void *func_020781e0(void *arg)
{
    func_02138c48(arg, 0xf, 0xc4, func_020782d0);
    return arg;
}
