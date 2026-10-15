/* func_ov126_0229fc54 @ 0x0229fc54, 0x28 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099658(int argument0);
extern int func_0206fc8c(void);
extern void func_02077d00(void);

int func_ov126_0229fc54(void)
{
    int base;
    int index;
    int result;

    base = func_02099658((int) func_020984e8());
    index = func_0206fc8c();
    // clang-format off
    asm { mov r0, base }
    // clang-format on
    func_02077d00();
    // clang-format off
    asm { mov result, r0 }
    // clang-format on
    result += index * 0x24;
    return result;
}
