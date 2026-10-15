/* func_02039cb4 @ 0x02039cb4, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d368(void);

void func_02039cb4(int *self)
{
    int *p;
    int v;

    asm {
        mov r1, #2
        add r0, #0xa4
        str r1, [r0]
        mov r2, #1
        mov r0, self
        add r0, #0xb4
        strb r2, [r0]
    }

    if (self[3] == 0)
    {
        asm { ldr r0, =0x137 }
        v = func_0209d368() + 0x258;
    }
    else
    {
        asm { ldr r0, =0x12d }
        v = func_0209d368() + 0x258;
    }

    self[0x2a] = v;
}