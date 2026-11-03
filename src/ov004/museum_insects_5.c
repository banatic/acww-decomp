/* museum_insects_5: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223fab4 @ 0x0223fab4, 0x1c bytes, Thumb
 * func_ov004_0223fa80 @ 0x0223fa80, 0x34 bytes, Thumb
 * func_ov004_0223fa10 @ 0x0223fa10, 0x70 bytes, Thumb
 * func_ov004_0223f9c8 @ 0x0223f9c8, 0x48 bytes, Thumb
 */

#include "types.h"

extern int func_020edf70(unsigned int size);
extern void *func_ov004_0223eba4(char *argument0);
extern char data_ov004_02259a34[];
extern void func_0209d0a4(void *argument0);
extern void *func_0209d238(void *argument0, unsigned short *argument1);
extern void func_ov004_0223fad0(void *argument0, char *argument1);
extern int func_0209d180(void *object, unsigned int count, int a, int b, int c, int (*allocate)(int, int),
                         void (*cleanup)(void), void *context);
extern void func_ov004_0223ef1c(void *);
extern void func_0205c978(void);
extern int func_0205c994(int size, int heapword);

void func_ov004_0223fab4(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_020edf70(0x1a0)))) {
        func_ov004_0223eba4((char *) conditionInput0);
    }
}

int func_ov004_0223fa80(void)
{
    unsigned char i;
    char *p = data_ov004_02259a34;
    for (i = 0; i < 0x20; i++) {
        if (*(int *) (p + 0x198) == 0) {
            return i;
        }
        p += 0x2d8;
    }
    return -1;
}

int func_ov004_0223fa10(char *self, int a1)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0223fa80();
    if (v1 != -0x1) {
        *(u8 *) ((char *) ((void * *) data_ov004_02259a34) + (0x2d8 * v1) + 0x196) = a1;
        *(int *) ((char *) ((void * *) data_ov004_02259a34) + (0x2d8 * v1) + 0x198) = 0x1;
        func_0209d238((void *) ((void *) (self + 0x180)),
                      (unsigned short *) ((unsigned short *) ((char *) ((void * *) data_ov004_02259a34) + (0x2d8 * v1) + 0x284)));
        func_0209d0a4((char *) ((void * *) data_ov004_02259a34) + (0x2d8 * v1) + 0x288);
        func_ov004_0223fad0(self, (char *) ((void * *) data_ov004_02259a34) + (0x2d8 * v1));
        *(void **) ((char *) ((void * *) data_ov004_02259a34) + (0x2d8 * v1) + 0x18) = 0x0;
        *(void **) ((char *) ((void * *) data_ov004_02259a34) + (0x2d8 * v1) + 0x1c) = 0x0;
        return 0x1;
    }
    return 0x0;
}

int func_ov004_0223f9c8(char *self)
{
    func_0209d180(self + 0x180, 0x20, 0x400, 0x40, 0x9c4, func_0205c994, func_0205c978, 0);
    func_ov004_0223ef1c(self);
    return 0x1;
}
