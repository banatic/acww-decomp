/* func_020f3a0c @ 0x020f3a0c, 0x3c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(void *receiver, void *resource, int count);
extern void func_020f41a4(void *receiver, int count);
extern void func_020f4080(void);
extern int func_020f4038(void);
extern void *func_020eef70(void);
extern int NNS_SndHeapSaveState(void *heap);
extern int func_020f1d84(void *receiver, int sound);
extern void func_020f1004(void *receiver);
extern void func_020f4318(unsigned char *receiver);
extern unsigned char data_021fd1bc[];

// clang-format off
asm void func_020f3a0c(register void *receiver)
{
    stmfd sp!, {r4, lr}
    mov r4, r0
    bl func_020f4318
    ldr r0, =data_021fd1bc
    mov r1, #0x90
    bl func_020f1d84
    mov r0, r4
    bl func_020f4038
    bl func_020eef70
    bl NNS_SndHeapSaveState
    mov r0, #1
    strb r0, [r4, #0x1c]
    ldmfd sp!, {r4, lr}
    bx lr
}
// clang-format on
