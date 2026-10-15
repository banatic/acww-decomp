/* func_0206c5e0 @ 0x0206c5e0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206d420(void);

// clang-format off
asm int func_0206c5e0(register unsigned int *p)
{
    ldr r2, [r0, #0x2c]
    ldr r1, =0x14b8
    add r1, r2, r1
    ldr r3, =func_0206d420
    bx r3
}
// clang-format on
