/* func_ov096_022a1384 @ 0x022a1384, 0x10 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a098(void);

int func_ov096_022a1384(int arg)
{
    // clang-format off
    asm {
        ldr r1, =0xde0
        add r0, arg, r1
    }
    // clang-format on
    return func_ov094_0229a098();
}
