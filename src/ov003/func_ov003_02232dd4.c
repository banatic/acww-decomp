/* func_ov003_02232dd4 @ 0x02232dd4, 0xb4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov003_02235b54(u8 *self, int a, int b);

// clang-format off
asm int func_ov003_02232dd4(register u8 *self)
{
    push {r4, lr}
    mov r4, r0
    mov r1, #0x50
    ldr r2, =0xe38
    bl func_ov003_02235b54
    mov r2, #0
    ldr r1, =0x252
    ldrb r3, [r4, r1]
    cmp r0, #0
    beq scale_direction
    ldr r1, =0x24d
    ldrsb r1, [r4, r1]
    cmp r1, #0x35
    bne heading_from_z
    ldr r2, =0x23c
    ldrsh r2, [r4, r2]
    b adjust_heading
heading_from_z:
    ldr r2, =0x23a
    ldrsh r2, [r4, r2]
adjust_heading:
    cmp r0, #3
    bne small_turn
    cmp r3, #1
    beq large_left
    cmp r3, #0xa
    bne large_right
large_left:
    ldr r0, =0xaaa
    sub r0, r2, r0
    lsl r0, r0, #16
    asr r2, r0, #16
    b store_heading
large_right:
    ldr r0, =0xaaa
    add r0, r2, r0
    lsl r0, r0, #16
    asr r2, r0, #16
    b store_heading
small_turn:
    cmp r0, #1
    beq small_left
    cmp r3, #1
    bne test_right
small_left:
    ldr r0, =0x38e
    sub r0, r2, r0
    lsl r0, r0, #16
    asr r2, r0, #16
    mov r3, #1
    b store_heading
test_right:
    cmp r0, #2
    beq small_right
    cmp r3, #2
    bne store_heading
small_right:
    ldr r0, =0x38e
    add r0, r2, r0
    lsl r0, r0, #16
    asr r2, r0, #16
    mov r3, #2
store_heading:
    cmp r1, #0x35
    bne store_z
    ldr r0, =0x23c
    strh r2, [r4, r0]
    b changed
store_z:
    ldr r0, =0x23a
    strh r2, [r4, r0]
changed:
    mov r2, #1
    b store_direction
scale_direction:
    cmp r3, #0xa
    bhs store_direction
    mov r0, #0xa
    mul r3, r0
    lsl r0, r3, #24
    lsr r3, r0, #24
store_direction:
    ldr r0, =0x252
    strb r3, [r4, r0]
    mov r0, r2
    pop {r4}
    pop {r3}
    bx r3
}
// clang-format on
