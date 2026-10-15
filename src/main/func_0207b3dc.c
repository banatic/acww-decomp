/* func_0207b3dc @ 0x0207b3dc, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0207b410(unsigned int address);
extern void func_0209a778(void);
extern int func_0209bd44(void *);
extern int func_0209a774(int address);
extern int func_0207cf14(void *, void *);

// clang-format off
asm int func_0207b3dc(void *base)
{
    push {r4, lr}
    add r4, r0, #0
    bl func_0207b410
    bl func_0209a778
    bl func_0209bd44
    cmp r0, #0
    beq no_record
    add r0, r4, #0
    bl func_0207b410
    bl func_0209a774
    add r1, r0, #0
    add r0, r4, #0
    bl func_0207cf14
    b finish
no_record:
    mov r0, #0
    mvn r0, r0
finish:
    pop {r4}
    pop {r3}
    bx r3
}
// clang-format on
