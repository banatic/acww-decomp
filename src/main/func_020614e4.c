/* func_020614e4 @ 0x020614e4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *arg1, int arg2, int arg3, void (*arg4)(void));
extern void func_020051b0(void);

void *func_020614e4(void *arg1)
{
    func_02138c48(arg1, 0x100, 2, func_020051b0);
    return arg1;
}
