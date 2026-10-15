/* func_020aa888 @ 0x020aa888, 0x138 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020aa888 {
    void *unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    u8 pad_14[0x30 - 0x14];
    u8 unk_30;
} UnkStruct_020aa888;

extern int func_020abd98(void *p);
extern int func_020a7e50(void);
extern int func_020a8028(int *a, int *b);
extern int func_020abcfc(void *p);
extern int func_020abd14(void *p);
extern int _s32_div_f(int a, int b);
extern int func_020a7e44(void);
extern int func_020a7ebc(void);
extern int func_020a7e94(void);
extern void RtcSendPxiCommand(int command);

// clang-format off
asm void func_020aa888(UnkStruct_020aa888 *self)
{
    push {r4, r5, r6, lr}
    sub sp, #8
    add r4, r0, #0
    add r0, #0x30
    ldrb r0, [r0]
    cmp r0, #0
    beq check_interval
    ldr r0, [r4]
    bl func_020abd98
    cmp r0, #0
    beq check_interval
    bl func_020a7e50
    cmp r0, #0
    beq check_keys
    add r0, sp, #0
    add r1, sp, #4
    bl func_020a8028
    cmp r0, #0
    beq reset_speed
    ldr r0, [r4]
    bl func_020abcfc
    add r5, r0, #0
    ldr r0, [r4]
    bl func_020abd14
    add r2, r0, #0
    ldr r1, [sp, #4]
    ldr r0, [r4, #0x10]
    sub r0, r1, r0
    cmp r0, r2
    bge check_upper
    add r0, r2, #0
    b scale_position
check_upper:
    cmp r0, r5
    ble scale_position
    add r0, r5, #0
scale_position:
    sub r0, r0, r5
    lsl r0, r0, #12
    sub r1, r2, r5
    bl _s32_div_f
    str r0, [r4, #8]
reset_speed:
    mov r0, #0
    str r0, [r4, #4]
    b check_interval
check_keys:
    bl func_020a7e44
    cmp r0, #0
    beq check_interval
    bl func_020a7ebc
    add r5, r0, #0
    bl func_020a7e94
    cmp r5, #0
    bne accelerate
    cmp r0, #0
    bne accelerate
    mov r1, #0x28
    str r1, [r4, #4]
    b apply_direction
accelerate:
    ldr r1, [r4, #4]
    add r1, #0x51
    str r1, [r4, #4]
    ldr r2, [r4, #4]
    cmp r2, #0
    bge check_speed_limit
    mov r2, #0
    b store_speed
check_speed_limit:
    ldr r1, =0x199
    cmp r2, r1
    ble store_speed
    add r2, r1, #0
store_speed:
    str r2, [r4, #4]
apply_direction:
    cmp r5, #0
    beq apply_down
    ldr r2, [r4, #8]
    ldr r1, [r4, #4]
    add r1, r2, r1
    str r1, [r4, #8]
apply_down:
    cmp r0, #0
    beq clamp_position
    ldr r1, [r4, #8]
    ldr r0, [r4, #4]
    sub r0, r1, r0
    str r0, [r4, #8]
clamp_position:
    ldr r1, [r4, #8]
    cmp r1, #0
    bge check_position_limit
    mov r1, #0
    b store_position
check_position_limit:
    ldr r0, =0x1000
    cmp r1, r0
    ble store_position
    add r1, r0, #0
store_position:
    str r1, [r4, #8]
check_interval:
    ldr r2, [r4, #0xc]
    ldr r0, [r4, #8]
    sub r1, r0, r2
    cmp r1, #0
    bge check_distance
    neg r1, r1
check_distance:
    cmp r1, #0x51
    blt finish
    cmp r0, r2
    ble descending
    mov r3, #1
    b choose_upper
descending:
    mov r3, #0
choose_upper:
    cmp r3, #0
    beq old_upper
    add r1, r0, #0
    b choose_lower
old_upper:
    add r1, r2, #0
choose_lower:
    cmp r3, #0
    bne find_crossing
    add r2, r0, #0
find_crossing:
    mov r0, #0
    add r6, r0, #0
    ldr r3, =0x199
    b test_boundary
next_boundary:
    add r5, r6, #0
    mul r5, r3
    cmp r5, r2
    blt increment_boundary
    cmp r5, r1
    bge increment_boundary
    mov r0, #1
    b check_end_boundary
increment_boundary:
    add r6, r6, #1
test_boundary:
    cmp r6, #0xa
    blt next_boundary
check_end_boundary:
    ldr r2, =0x1000
    cmp r1, r2
    bne maybe_sound
    mov r0, #1
maybe_sound:
    cmp r0, #0
    beq finish
    mov r0, #0x19
    bl RtcSendPxiCommand
finish:
    ldr r0, [r4, #8]
    str r0, [r4, #0xc]
    add sp, #8
    pop {r4, r5, r6}
    pop {r3}
    bx r3
}
// clang-format on
