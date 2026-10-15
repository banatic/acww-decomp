/* func_020238c8 @ 0x020238c8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0207b410(unsigned int address);
extern void func_0209a778(void);
extern int func_0209bd44(void *);
extern void func_0209bb90(int, int);

extern unsigned char data_021e5a2c[];

// clang-format off
asm void func_020238c8(void)
{
    push {r4, lr}
    ldr r0, =data_021e5a2c
    bl func_0207b410
    bl func_0209a778
    add r4, r0, #0
    bl func_0209bd44
    cmp r0, #0
    beq finish
    add r0, r4, #0
    mov r1, #1
    bl func_0209bb90
finish:
    pop {r4}
    pop {r3}
    bx r3
}
// clang-format on
