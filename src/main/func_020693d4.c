/* func_020693d4 @ 0x020693d4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x24];
    unsigned int unk_24;
} UnkStruct_020693d4;

extern void func_0206b97c(void);

// clang-format off
asm int func_020693d4(register UnkStruct_020693d4 *a)
{
    ldr r2, [r0, #0x24]
    ldr r1, =0x14b8
    add r2, r2, r1
    ldr r1, =0x398
    add r1, r2, r1
    ldr r3, =func_0206b97c
    bx r3
}
// clang-format on
