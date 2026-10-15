/* func_ov068_0226ce48 @ 0x0226ce48, 0x12 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_020139ec(void);

void *func_ov068_0226ce48(void *p)
{
    // clang-format off
    asm {
        add r0, #0x3c
    }
    // clang-format on
    func_020139ec();
    return p;
}
