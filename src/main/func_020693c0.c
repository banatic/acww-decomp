/* func_020693c0 @ 0x020693c0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206b97c(void);
struct UnkStruct_020693c0 {
    unsigned char pad_00[0x24];
    unsigned int unk_24;
};
// clang-format off
asm int func_020693c0(register struct UnkStruct_020693c0 *self)
{
    ldr r2, [r0, #0x24]
    ldr r1, =0x18ac
    add r1, r2, r1
    ldr r3, =func_0206b97c
    bx r3
}
// clang-format on
