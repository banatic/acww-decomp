/* func_02073044 @ 0x02073044, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int v;
    unsigned char unk_04;
} UnkStruct_02073044;
extern UnkStruct_02073044 data_021d11c4;
extern char SDK_OVERLAY_ov065_ID;
extern char SDK_OVERLAY_ov066_ID;
extern char SDK_OVERLAY_ov067_ID;
extern void OS_Terminate(void);
// clang-format off
asm unsigned int func_02073044(void)
{
    push {lr}
    sub sp, #4
    ldr r0, =data_021d11c4
    ldrb r1, [r0, #4]
    cmp r1, #0
    beq active_overlay
    mov r0, #0
    mvn r3, r0
    b check_overlay
active_overlay:
    ldr r3, [r0]
check_overlay:
    ldr r2, =SDK_OVERLAY_ov065_ID
    ldr r1, =SDK_OVERLAY_ov066_ID
    ldr r0, =SDK_OVERLAY_ov067_ID
    cmp r3, r2
    beq valid_overlay
    cmp r3, r1
    beq valid_overlay
    cmp r3, r0
    bne invalid_overlay
valid_overlay:
    mov r0, #1
    b overlay_checked
invalid_overlay:
    mov r0, #0
overlay_checked:
    cmp r0, #0
    bne overlay_return
    bl OS_Terminate
overlay_return:
    add sp, #4
    pop {r3}
    bx r3
}
// clang-format on
