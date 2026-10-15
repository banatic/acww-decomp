/* func_020015fc @ 0x020015fc, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MIi_CpuClearFast(unsigned int data, void *dest, unsigned int size);

// clang-format off
asm int func_020015fc(register int data, register void *dest, register unsigned int size)
{
    push {lr}
    sub sp, #4
    str r0, [sp]
    ldr r0, [sp]
    bl MIi_CpuClearFast
    add sp, #4
    pop {r3}
    bx r3
}
// clang-format on
