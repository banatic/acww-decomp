/* func_020693f0 @ 0x020693f0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206b97c(void);
extern char abs_000014b8;
extern char abs_0000033c;

typedef struct {
    char pad_00[0x24];
    unsigned int unk_24;
} Struct020693f0;

// clang-format off
asm void func_020693f0(register Struct020693f0 *self)
{
    ldr r2, [r0, #0x24]
    ldr r1, =abs_000014b8
    add r2, r2, r1
    ldr r1, =abs_0000033c
    add r1, r2, r1
    ldr r3, =func_0206b97c
    bx r3
}
// clang-format on
