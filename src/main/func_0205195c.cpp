/* func_0205195c @ 0x0205195c, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0205195c {
  public:
    virtual void v0();
    virtual void v1();
    virtual int getCount();
    virtual void *getBuffer();
};

extern "C" void MI_CpuFill8(void *dest, int ch, unsigned int n);

// clang-format off
extern "C" asm void *func_0205195c(UnkStruct_0205195c *obj)
{
    push {r4, r5, lr}
    sub sp, #4
    add r5, r0, #0
    ldr r1, [r0]
    ldr r1, [r1, #8]
    blx r1
    lsl r4, r0, #1
    add r0, r5, #0
    ldr r1, [r0]
    ldr r1, [r1, #0xc]
    blx r1
    mov r1, #0
    add r2, r4, #0
    bl MI_CpuFill8
    add sp, #4
    pop {r4, r5}
    pop {r3}
    bx r3
}
// clang-format on
