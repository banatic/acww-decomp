/* func_ov108_0229d82c @ 0x0229d82c, 0x24 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a098(void);
extern void func_ov002_0220af94(void);

void func_ov108_0229d82c(void *p)
{
    // clang-format off
    asm {
        ldr r0, =0xd78
        add r0, p, r0
    }
    // clang-format on
    func_ov094_0229a098();
    // clang-format off
    asm {
        ldr r0, =0x2a0c
        add r0, p, r0
    }
    // clang-format on
    func_ov002_0220af94();
}
