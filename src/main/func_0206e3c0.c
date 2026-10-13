/* func_0206e3c0 @ 0x0206e3c0, 0x2c bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

// setjmp entry: saves all registers into the jmp_buf, then jumps to the Thumb body.
// Hand-written assembly in the original.

extern void func_0206e3f4(void);

// clang-format off
asm void func_0206e3c0(void) {
    dcd 0xe92dffff
    mrs r0, cpsr
    stmdb sp!, {r0}
    mov r0, sp
    add r1, sp, #0x44
    str r1, [sp, #0x38]
    mvn r2, #0
    str r2, [sp, #0x40]
    ldr r3, =func_0206e3f4
    bx r3
}
// clang-format on
