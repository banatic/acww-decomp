/* func_0206c49c @ 0x0206c49c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206d420(void);

// clang-format off
asm void func_0206c49c(register int *p0)
{
    ldr r2, [r0, #0x2c]
    ldr r1, =0x18ac
    add r1, r2, r1
    add r1, #0xb8
    ldr r3, =func_0206d420
    bx r3
}
// clang-format on
