/* func_ov100_0229e208 @ 0x0229e208, 0x10 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a098(void);
int func_ov100_0229e208(int arg)
{
    // clang-format off
    asm {
        ldr r1, =0xb54
        add r0, arg, r1
    }
    // clang-format on
    return func_ov094_0229a098();
}
