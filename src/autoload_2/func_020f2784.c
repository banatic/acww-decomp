/* func_020f2784 @ 0x020f2784, 0x40 bytes, ARM, module autoload_2
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
asm void func_020f2784(register void *receiver)
{
    stmfd sp!, {r4, lr}
    mov r4, r0
    mov r1, #0
    mov r2, #28
    bl func_020f4220
    mov r0, r4
    bl func_020f4038
    bl func_020eef70
    bl NNS_SndHeapSaveState
    ldr r0, =data_021fd1bc
    mov r1, #0
    strb r1, [r0, #0x62]
    bl func_020f1004
    ldmfd sp!, {r4, lr}
    bx lr
}
// clang-format on
