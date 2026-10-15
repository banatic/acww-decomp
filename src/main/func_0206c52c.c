/* func_0206c52c @ 0x0206c52c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x2c];
    char *ptr;
} Self_0206c52c;

typedef struct {
    unsigned char pad_00[0x284];
} Chunk_0206c52c;

extern void func_0206d420(void);

// clang-format off
asm void func_0206c52c(register Self_0206c52c *self)
{
    ldr r2, [r0, #0x2c]
    ldr r1, =0x14b8
    add r2, r2, r1
    ldr r1, =0x284
    add r1, r2, r1
    ldr r3, =func_0206d420
    bx r3
}
// clang-format on
