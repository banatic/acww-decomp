/* func_ov122_022a1764 @ 0x022a1764, 0xc bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229b324(void);

void func_ov122_022a1764(int p0)
{
    // clang-format off
    asm {
        mov r0, p0
        add r0, #192
    }
    // clang-format on
    func_ov095_0229b324();
}
