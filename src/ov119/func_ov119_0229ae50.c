/* func_ov119_0229ae50 @ 0x0229ae50, 0x16 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099658(int);
extern void func_02077d00(void);

// clang-format off
asm void *func_ov119_0229ae50(void)
{
    push {lr}
    sub sp, #4
    bl func_020984e8
    bl func_02099658
    bl func_02077d00
    add sp, #4
    pop {r3}
    bx r3
}
// clang-format on
