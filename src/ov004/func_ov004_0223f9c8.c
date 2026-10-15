/* func_ov004_0223f9c8 @ 0x0223f9c8, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d180(void *object, unsigned int count, int a, int b, int c, int (*allocate)(int, int),
                         void (*cleanup)(void));
extern void func_ov004_0223ef1c(void *);
extern void func_0205c978(void);
extern int func_0205c994(int size, int heapword);

int func_ov004_0223f9c8(char *self)
{
    volatile unsigned int outgoing[4];
    outgoing[0] = 0x9c4;
    outgoing[1] = (unsigned int) func_0205c994;
    outgoing[2] = (unsigned int) func_0205c978;
    outgoing[3] = 0;
    asm {
        ldr r0, =0x180
        add r0, self, r0
        mov r1, #0x20
        ldr r2, =0x400
        mov r3, #0x40
        bl func_0209d180
    }
    func_ov004_0223ef1c(self);
    return 0x1;
}
