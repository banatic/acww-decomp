/* func_0200457c @ 0x0200457c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020f0f34(void);
extern unsigned char data_021fd1bc[];

// clang-format off
asm int func_0200457c(register void *param1)
{
    add r1, r0, #0
    ldr r0, =data_021fd1bc
    ldr r3, =func_020f0f34
    bx r3
}
// clang-format on
