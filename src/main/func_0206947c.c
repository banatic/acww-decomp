/* func_0206947c @ 0x0206947c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    unsigned int unk_24;
} UnkStruct_0206947c;

extern void func_0206b97c(void);

// clang-format off
asm int func_0206947c(register UnkStruct_0206947c *self)
{
    ldr r2, [r0, #0x24]
    ldr r1, =0x14b8
    add r2, r2, r1
    ldr r1, =0x170
    add r1, r2, r1
    ldr r3, =func_0206b97c
    bx r3
}
// clang-format on
