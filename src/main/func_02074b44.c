/* func_02074b44 @ 0x02074b44, 0x1e0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x6d];
    u8 unk_6D;
    u8 pad_6E[2];
    int unk_70;
    u8 unk_74;
} UnkStruct_02074b44;

extern void func_0207718c(void);
extern int func_02077afc(int a, int b);
extern void func_02073d64(UnkStruct_02074b44 *g, int a);
extern void func_02073bf0(UnkStruct_02074b44 *g, int a);
extern void func_02073878(UnkStruct_02074b44 *g, int a);
extern void func_02073760(UnkStruct_02074b44 *g, int a);
extern void func_020736ac(UnkStruct_02074b44 *g, int a);
extern void func_02073588(UnkStruct_02074b44 *g, int a);
extern void func_020734c0(UnkStruct_02074b44 *g, int a);
extern void func_0207341c(UnkStruct_02074b44 *g, int a);
extern void func_020733b8(UnkStruct_02074b44 *g, int a);
extern unsigned int func_02073044(void);
extern void func_020ece54(int a, int b, int c, long long d, int f, void *g, void *h);
extern void func_020730c8(void);
extern void func_020ecce4(int a, void (*f)(int, char *, unsigned int));
extern void *func_02073144(UnkStruct_02074b44 *g);
extern void *func_02073138(UnkStruct_02074b44 *g);
extern void MI_CpuFill8(void *dst, int v, int n);
extern void *func_020984e8(void);
extern void *func_02099658(void *h);
extern void func_02077d00(void);
extern void *func_02077c3c(void *p);
extern void *func_02077d68(void *);
extern void MI_CpuCopy8(const void *src, void *dst, int n);
extern void *func_02099870(void *h);
extern void *func_020950a8(void *p);
extern void *func_020642a4(void *p);
extern void *func_02099664(void *h);
extern void func_02077bcc(void);
extern void func_02073100(void);
extern void func_020ecba8(int a, void (*f)(int, char *, unsigned int), int g, int p, char *q);
extern void func_020732b4(UnkStruct_02074b44 *g, int a);

extern void func_02077ae8(int);
extern void func_02075050(int, char *, unsigned int);
extern void func_02099e78(void);

extern UnkStruct_02074b44 *data_020ccf94;
extern u8 data_021dc7a8[];

// clang-format off
asm void func_02074b44(int a0, int a1, int a2)
{
    push {r4, r5, r6, r7, lr}
    sub sp, #0x24
    str r0, [sp, #0x10]
    add r5, r1, #0
    str r2, [sp, #0x14]
    ldr r0, =data_020ccf94
    ldr r4, [r0]
    mov r1, #1
    add r0, r4, #0
    add r0, #0x74
    strb r1, [r0]
    bl func_0207718c
    add r0, r4, #0
    add r0, #0x6d
    ldrb r0, [r0]
    mov r1, #4
    bl func_02077afc
    str r0, [r4, #0x70]
    ldr r0, =0x3000
    mov r1, #4
    bl func_02077afc
    add r1, r0, #0
    add r0, r4, #0
    bl func_02073d64
    ldr r0, =0x9000
    mov r1, #4
    bl func_02077afc
    add r1, r0, #0
    add r0, r4, #0
    bl func_02073bf0
    ldr r0, =0x91a
    mov r1, #4
    bl func_02077afc
    add r1, r0, #0
    add r0, r4, #0
    bl func_02073878
    ldr r0, =0x91a
    mov r1, #4
    bl func_02077afc
    add r1, r0, #0
    add r0, r4, #0
    bl func_02073760
    ldr r0, =0x91a
    mov r1, #4
    bl func_02077afc
    add r1, r0, #0
    add r0, r4, #0
    bl func_020736ac
    ldr r0, =0x91a
    mov r1, #4
    bl func_02077afc
    add r1, r0, #0
    add r0, r4, #0
    bl func_02073588
    ldr r0, =0x91a
    mov r1, #4
    bl func_02077afc
    add r1, r0, #0
    add r0, r4, #0
    bl func_020734c0
    ldr r0, =0xc00
    mov r1, #4
    bl func_02077afc
    add r1, r0, #0
    add r0, r4, #0
    bl func_0207341c
    ldr r0, =0xc00
    mov r1, #4
    bl func_02077afc
    add r1, r0, #0
    add r0, r4, #0
    bl func_020733b8
    bl func_02073044
    str r5, [sp, #4]
    ldr r0, =func_02077afc
    str r0, [sp, #8]
    ldr r0, =func_02077ae8
    str r0, [sp, #0xc]
    ldr r3, =0x004fe752
    mov r0, #0
    str r0, [sp]
    ldr r0, =0x41444d4b
    ldr r1, =0x00c0001b
    mov r2, #1
    bl func_020ece54
    ldr r0, [sp, #0x10]
    add r0, #0xff
    lsl r0, r0, #0x18
    lsr r0, r0, #0x18
    cmp r0, #1
    bhi copy_state
    bl func_020730c8
    ldr r0, [sp, #0x10]
    ldr r1, =func_02075050
    bl func_020ecce4
    b finish
copy_state:
    ldr r0, =data_020ccf94
    ldr r6, [r0]
    add r0, r6, #0
    bl func_02073144
    add r5, r0, #0
    add r0, r6, #0
    bl func_02073138
    add r6, r0, #0
    add r0, r5, #0
    mov r1, #0
    ldr r2, =0x5e0
    bl MI_CpuFill8
    add r0, r6, #0
    mov r1, #0
    mov r2, #0x60
    bl MI_CpuFill8
    bl func_020984e8
    str r0, [sp, #0x18]
    bl func_02099658
    bl func_02077d00
    str r0, [sp, #0x1c]
    mov r7, #0
copy_entries:
    ldr r0, [sp, #0x1c]
    bl func_02077c3c
    bl func_02077d68
    add r2, r7, #0
    mov r1, #0xc
    mul r2, r1
    add r1, r5, r2
    mov r2, #0xc
    bl MI_CpuCopy8
    ldr r0, [sp, #0x1c]
    add r0, #0x24
    str r0, [sp, #0x1c]
    add r7, r7, #1
    cmp r7, #0x20
    blt copy_entries
    ldr r0, [sp, #0x18]
    bl func_02099870
    bl func_020950a8
    add r1, r6, #0
    mov r2, #0xc
    bl MI_CpuCopy8
    ldr r0, =data_021dc7a8
    add r0, r0, #2
    bl func_020642a4
    add r1, r6, #0
    add r1, #0x10
    mov r2, #0xc
    bl MI_CpuCopy8
    ldr r0, [sp, #0x18]
    bl func_02099664
    bl func_02077bcc
    add r1, r6, #0
    add r1, #0x20
    mov r2, #0x40
    bl MI_CpuCopy8
    bl func_02073100
    str r5, [sp]
    ldr r0, [sp, #0x10]
    ldr r1, =func_02075050
    ldr r2, =func_02099e78
    add r3, r6, #0
    bl func_020ecba8
finish:
    add r0, r4, #0
    ldr r1, [sp, #0x14]
    bl func_020732b4
    add sp, #0x24
    pop {r4, r5, r6, r7}
    pop {r3}
    bx r3
}
// clang-format on
