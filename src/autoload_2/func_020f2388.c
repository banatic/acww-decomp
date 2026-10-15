/* func_020f2388 @ 0x020f2388, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020eedfc(void);
extern void func_020f0d3c(void);
extern void func_020f1520(void *arg);
extern void func_020f13bc(void *arg);

void func_020f2388(void *arg)
{
    func_020eedfc();
    // clang-format off
    asm {
        mov r0, arg
    }
    // clang-format on
    func_020f0d3c();
    func_020f1520(arg);
    func_020f13bc(arg);
}
