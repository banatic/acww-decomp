/* func_02069428 @ 0x02069428, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206b97c(void);

// clang-format off
asm void func_02069428(register int *p0)
{
    ldr r2, [r0, #0x24]
    ldr r1, =0x14b8
    add r2, r2, r1
    ldr r1, =0x284
    add r1, r2, r1
    ldr r3, =func_0206b97c
    bx r3
}
// clang-format on
