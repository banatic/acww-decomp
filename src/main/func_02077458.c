/* func_02077458 @ 0x02077458, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02235c94(void *buffer, int index);

// clang-format off
asm void func_02077458(int a0, int a1)
{
    add r2, r1, #0
    mov r1, #0x1a
    ldr r3, =func_ov003_02235c94
    bx r3
}
// clang-format on
