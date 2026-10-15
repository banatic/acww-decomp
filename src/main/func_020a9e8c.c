/* func_020a9e8c @ 0x020a9e8c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d368(void);
extern void RtcSendPxiCommand(int command);

typedef struct {
    unsigned char pad_00[8];
    int unk_08;
    unsigned char pad_0C[0x188];
    int unk_194;
    char unk_198;
} UnkStruct_020a9e8c;

// clang-format off
asm void func_020a9e8c(UnkStruct_020a9e8c *object)
{
    push {r4, lr}
    add r4, r0, #0
    mov r0, #3
    str r0, [r4, #8]
    mov r1, #1
    ldr r0, =0x198
    strb r1, [r4, r0]
    mov r0, #0x65
    mov r1, #2
    bl func_0209d368
    add r1, r0, #2
    ldr r0, =0x194
    str r1, [r4, r0]
    mov r0, #0x14
    bl RtcSendPxiCommand
    pop {r4}
    pop {r3}
    bx r3
}
// clang-format on
