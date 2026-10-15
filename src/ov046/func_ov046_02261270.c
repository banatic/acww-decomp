/* func_ov046_02261270 @ 0x02261270, 0x30 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b1558(void);

typedef void (*Fn)(void *);

typedef struct {
    Fn *vtable;
    char pad_04[0xb0];
    int unk_B4;
    char pad_B8[0x0c];
    unsigned char unk_C4;
    unsigned char unk_C5;
} UnkStruct_02261270;

// clang-format off
asm void func_ov046_02261270(register UnkStruct_02261270 *self, register int v)
{
    push {r4, r5, lr}
    sub sp, #4
    add r5, r0, #0
    add r4, r1, #0
    ldr r1, [r0]
    ldr r1, [r1, #8]
    blx r1
    add r0, r5, #0
    add r0, #0xb4
    str r4, [r0]
    mov r1, #0
    add r0, r5, #0
    add r0, #0xc4
    strb r1, [r0]
    bl func_020b1558
    mov r1, #0x10
    sub r0, r1, r0
    add r5, #0xc5
    strb r0, [r5]
    add sp, #4
    pop {r4, r5}
    pop {r3}
    bx r3
}
// clang-format on
