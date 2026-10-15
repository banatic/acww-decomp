/* func_ov106_0229e860 @ 0x0229e860, 0x2c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a098(void);
extern void func_ov002_0220af94(void);
extern int func_ov002_0220ab84(char *addr, int value);

void func_ov106_0229e860(char *p)
{
    // clang-format off
    asm {
        ldr r0, =0xb80
        add r0, p, r0
    }
    // clang-format on
    func_ov094_0229a098();
    // clang-format off
    asm {
        ldr r0, =0x3fb4
        add r0, p, r0
    }
    // clang-format on
    func_ov002_0220af94();
    func_ov002_0220ab84(p + 0x3fb4, 0x88);
}
