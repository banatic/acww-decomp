/* func_ov003_02228b74 @ 0x02228b74, 0x160 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char data_ov003_0225f76c[];
extern char data_ov003_0225f4dc[];
extern char data_ov003_0223c0b4[];
extern char data_ov003_0223c0c0[];
extern int data_ov003_0223bdac;
extern int data_021fbe94;
extern int data_020ccf94;
extern int func_0205c960(int size, int heapword);
extern void func_0205c944(void);
extern int func_0205c92c(int size, int heapword);
extern void func_0205c910(void);
extern int func_0209d180(void *self, unsigned int count, int a, int b, int size, int (*allocate)(int, int),
                         void (*cleanup)(void));
extern int func_02064b2c(int a, int b, int c, int d);
extern int func_ov003_02227778(char *rec, int h, char *p);
extern void func_0200451c(char *p);
extern int func_0200430c(char *p);
extern int func_02073d90(int a);
extern int func_02073918(int a, int b);
extern int func_0204fee8(u8 a);
extern void func_0204ff00(u8 a, int b, int c, int d, int e);

int func_ov003_02228b74(char *self)
{
    volatile unsigned int outgoing[4];
    char *rec;
    int i;
    int z;
    int m;
    // clang-format off
    asm {
        ldr r0, =0x800
        str r0, [sp]
        ldr r0, =func_0205c960
        str r0, [sp, #4]
    }
    // clang-format on
    outgoing[1] = (unsigned int) func_0205c944;
    outgoing[2] = (unsigned int) data_ov003_0223c0b4;
    // clang-format off
    asm {
        mov r0, self
        add r0, #0x50
        mov r1, #6
        mov r2, #0
        mov r3, r2
        bl func_0209d180
    }
    // clang-format on
    // clang-format off
    asm {
        ldr r0, =0x800
        str r0, [sp]
        ldr r0, =func_0205c92c
        str r0, [sp, #4]
    } // clang-format on
    outgoing[1] = (unsigned int) func_0205c910;
    outgoing[2] = (unsigned int) data_ov003_0223c0c0;
    // clang-format off
    asm {
        mov r0, self
        add r0, #0x68
        mov r1, #1
        ldr r2, =0x400
        mov r3, #0x80
        bl func_0209d180
    }
    // clang-format on
    *(int *) (self + 0x80) = func_02064b2c(data_ov003_0223bdac, data_021fbe94, 4, 0);
    rec = data_ov003_0225f76c;
    i = 0;
    z = i;
    do {
        func_ov003_02227778(rec, *(int *) (self + 0x80), self + 0x50);
        if (i < 3) {
            *(u8 *) (rec + 0x1fc) = 3;
        } else if (i < 6) {
            *(u8 *) (rec + 0x1fc) = 4;
        }
        {
            int *q = (int *) (rec + 0x208);
            q[0] = i;
            q[1] = z;
        }
        *(u8 *) (rec + 0x211) = i;
        *(short *) (rec + 0x212) = i * 0x190 + 0x960;
        func_0200451c(rec);
        func_0200430c(rec + 0x40);
        rec += 0x24c;
        i++;
    } while (i < 6);
    rec = data_ov003_0225f4dc;
    i = 0;
    m = data_020ccf94;
    z = i;
    outgoing[3] = -1;
    do {
        if (func_02073d90(m) != 0 && func_02073918(m, i) == 0 && func_0204fee8(i) == 3) {
            func_0204ff00(i, 6, outgoing[3], z, z);
        }
        func_0200451c(rec);
        rec += 0xa4;
        i++;
    } while (i < 4);
    return 1;
}
