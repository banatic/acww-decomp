/* func_02050588 @ 0x02050588, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020dcd78;
extern struct Param *data_021c8184;
extern int func_0209d180(void *p, unsigned int n, int a, int b, int c, int (*allocate)(int, int), void (*cleanup)(void));
extern int func_0205c8f8(int size, int heapword);
extern void func_0205c8dc(void);
extern int data_020dcef0;

struct Param {
    int unk_00;
    int unk_04;
    int state;
};

int func_02050588(struct Param *param)
{
    volatile unsigned int outgoing[4];
    if (param->state == 0) {
        data_020dcd78 = 4;
    } else if (param->state == 1) {
        data_020dcd78 = 1;
    }
    outgoing[0] = 0x134c;
    outgoing[1] = (unsigned int) func_0205c8f8;
    outgoing[2] = (unsigned int) func_0205c8dc;
    outgoing[3] = (unsigned int) &data_020dcef0;
    asm {
        ldr r0, =0x600
        add r0, param, r0
        ldr r1, =data_020dcd78
        ldr r1, [r1]
        ldr r2, =0x800
        mov r3, #0x80
        bl func_0209d180
    }
    data_021c8184 = param;
    return 1;
}
