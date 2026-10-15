/* func_020af31c @ 0x020af31c, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f4a80[];
extern void func_020af880(void *object);
extern void func_020af038(void);
extern void func_02063ce0(void *object, unsigned char a, unsigned char b, unsigned char c);
extern void func_020aed60(void *object, unsigned int *counter);
extern void func_020aed38(void *object, int *counter);
extern void func_020aece8(void *object, unsigned int *counter);
extern void func_020aecb8(void *object, int *counter);
extern void func_020aec90(void *object, int *counter);
extern void func_020aec68(void *object, int *counter);
extern void func_020aec40(void *object, int *counter);
extern void func_020aebcc(void *object, int *counter);
extern void func_020aeb9c(void *object, int *counter);
extern void func_020aeb6c(void *object, int *counter);

// clang-format off
asm void func_020af31c(void *p0, unsigned char p1, unsigned char p2, unsigned char p3)
{
    push {r4, r5, r6, r7, lr}
    sub sp, #4
    add r5, r0, #0
    add r4, r1, #0
    add r6, r2, #0
    add r7, r3, #0
    bl func_020af880
    mov r0, #0
    str r0, [sp]
    ldr r0, =data_021f4a80
    add r1, r4, #0
    add r2, r6, #0
    add r3, r7, #0
    bl func_02063ce0
    add r0, r5, #0
    add r1, sp, #0
    bl func_020aed60
    add r0, r5, #0
    add r1, sp, #0
    bl func_020aed38
    add r0, r5, #0
    add r1, sp, #0
    bl func_020aece8
    add r0, r5, #0
    add r1, sp, #0
    bl func_020aecb8
    add r0, r5, #0
    add r1, sp, #0
    bl func_020aec90
    add r0, r5, #0
    add r1, sp, #0
    bl func_020aec68
    add r0, r5, #0
    add r1, sp, #0
    bl func_020aec40
    add r0, r5, #0
    add r1, sp, #0
    bl func_020aebcc
    add r0, r5, #0
    add r1, sp, #0
    bl func_020aeb9c
    add r0, r5, #0
    add r1, sp, #0
    bl func_020aeb6c
    add r0, r5, #0
    bl func_020af038
    add sp, #4
    pop {r4, r5, r6, r7}
    pop {r3}
    bx r3
}
// clang-format on
