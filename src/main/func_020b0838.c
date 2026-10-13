/* func_020b0838 @ 0x020b0838, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b0a80();
extern void func_020b0a84();
extern void func_02138d6c(void *a, int b, int c, void (*d)(), void (*e)());

void *func_020b0838(void *arg)
{
    func_02138d6c(arg, 3, 6, func_020b0a84, func_020b0a80);
    return arg;
}
