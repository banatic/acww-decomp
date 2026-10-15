/* func_020694dc @ 0x020694dc, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206b97c(void);

typedef struct {
    char pad_00[0x24];
    unsigned int unk_24;
} UnkStruct_020694dc;

// clang-format off
asm void func_020694dc(register UnkStruct_020694dc *arg)
{
    ldr r2, [r0, #0x24]
    ldr r1, =0x14b8
    add r1, r2, r1
    ldr r3, =func_0206b97c
    bx r3
}
// clang-format on
