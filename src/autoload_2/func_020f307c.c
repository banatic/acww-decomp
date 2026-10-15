/* func_020f307c @ 0x020f307c, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(void *receiver, void *resource, int count);
extern int func_020f4038(void);
extern void *func_020eef70(void);
extern int NNS_SndHeapSaveState(void *heap);
extern unsigned char data_021fd1bc[];
extern void func_020f41f4(void);

// clang-format off
asm void func_020f307c(register void *receiver)
{
    stmfd sp!, {r4, lr}
    ldr r1, =0x232f4
    mov r4, r0
    mov r2, #17
    bl func_020f4220
    mov r0, r4
    bl func_020f41f4
    mov r0, r4
    bl func_020f4038
    bl func_020eef70
    bl NNS_SndHeapSaveState
    ldr r0, =data_021fd1bc
    mov r1, #0
    strb r1, [r0, #0x62]
    ldmfd sp!, {r4, lr}
    bx lr
}
// clang-format on
