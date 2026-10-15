/* func_ov107_0229db24 @ 0x0229db24, 0x24 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a098(void);
extern void func_ov002_0220af94(void);

void func_ov107_0229db24(void *arg0)
{
    // clang-format off
    asm {
        ldr r0, =0xb94
        add r0, arg0, r0
    }
    // clang-format on
    func_ov094_0229a098();
    // clang-format off
    asm {
        ldr r0, =0x2828
        add r0, arg0, r0
    }
    // clang-format on
    func_ov002_0220af94();
}
