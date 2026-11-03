/* room_placement: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223b540 @ 0x0223b540, 0x34 bytes, Thumb
 * func_ov004_0223b518 @ 0x0223b518, 0x28 bytes, Thumb
 * func_ov004_0223b4d0 @ 0x0223b4d0, 0x48 bytes, Thumb
 * func_ov004_0223b488 @ 0x0223b488, 0x48 bytes, Thumb
 * func_ov004_0223b440 @ 0x0223b440, 0x48 bytes, Thumb
 * func_ov004_0223b3f8 @ 0x0223b3f8, 0x48 bytes, Thumb
 */

#include "types.h"

extern int func_020961a8(int argument0);
extern int func_ov004_0223b574(int *argument0, void *argument1, void *argument2, int argument3, int argument4);
extern int func_020984e8(void);
extern int func_0209871c(void *argument0, void *argument1);
extern int func_02099870(int argument0);
extern void *data_021dc7bc;

int func_ov004_0223b540(char *self, int a1, int a2)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_020961a8((int) ((int) (0x4)));
    if (v1 != 0x0) {
        return func_ov004_0223b574((int *) (self), (void *) (a1), (void *) ((char *) v1 + 0x5c),
                                   (int) (*(short *) ((char *) v1 + 0x8e)), (int) (a2));
    }
    return 0x0;
}

int func_ov004_0223b518(void)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_020984e8();
    if (v1 != 0x0) {
        return func_0209871c((void *) (&data_021dc7bc), (void *) (func_02099870(v1)));
    }
    return -0x1;
}

int func_ov004_0223b4d0(void *self, unsigned int b, int c)
{
    unsigned int v = (unsigned int) func_ov004_0223b518();
    if (v != (unsigned int) -1) {
        u16 s;
        v = b + (v << 3);
        s = (u16) (v < 0x20 ? 0x3d84 + v * 4 : 0x3d84);
        return func_ov004_0223b540((char *) self, (int) (&s), c);
    }
    return 2;
}

int func_ov004_0223b488(void *self, unsigned int b, int c)
{
    unsigned int v = (unsigned int) func_ov004_0223b518();
    if (v != (unsigned int) -1) {
        u16 s;
        v = b + (v << 3);
        s = (u16) (v < 0x20 ? 0x3ea4 + v * 4 : 0x3ea4);
        return func_ov004_0223b540((char *) self, (int) (&s), c);
    }
    return 2;
}

int func_ov004_0223b440(void *self, unsigned int b, int c)
{
    unsigned int v = (unsigned int) func_ov004_0223b518();
    if (v != (unsigned int) -1) {
        u16 s;
        v = b + (v << 3);
        s = (u16) (v < 0x20 ? 0x4224 + v * 4 : 0x4224);
        return func_ov004_0223b540((char *) self, (int) (&s), c);
    }
    return 2;
}

int func_ov004_0223b3f8(void *self, unsigned int b, int c)
{
    unsigned int v = (unsigned int) func_ov004_0223b518();
    if (v != (unsigned int) -1) {
        u16 s;
        v = b + (v << 3);
        s = (u16) (v < 0x20 ? 0x3f24 + v * 4 : 0x3f24);
        return func_ov004_0223b540((char *) self, (int) (&s), c);
    }
    return 2;
}
