/* func_ov110_0229e1cc @ 0x0229e1cc, 0x10 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_ov094_0229a098(void);

unsigned int func_ov110_0229e1cc(unsigned int r0)
{
    // clang-format off
    asm {
        ldr r1, =0xbc0
        add r0, r0, r1
    }
    // clang-format on
    return func_ov094_0229a098();
}
