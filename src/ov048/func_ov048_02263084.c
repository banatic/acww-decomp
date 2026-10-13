/* func_ov048_02263084 @ 0x02263084, 0xf0 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_0200338c(int, int);
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_02019c6c(void *, int, u16);
extern void func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern void func_02095ab0(void *, int, int);
extern void func_02019c20(void *, int, int, int, int, int);
extern int func_020644cc(int);
extern void func_ov004_02246f7c(void);

extern u16 data_020c80f8;
extern unsigned int data_ov048_0226398c[3];

int func_ov048_02263084(char *self)
{
    char *sub;
    unsigned int buf[3];

    sub = (char *) func_0200338c(0x73, 0) + 0x564;

    if (func_02019e00(self + 0x564) == 3) {
        if (func_02019de8(self + 0x564) != 0) {
            func_02019c6c(self + 0x564, 1, data_020c80f8);
        }
    }

    if (func_02019e00(sub) == 3) {
        if (func_02019de8(sub) != 0) {
            func_02019d0c(sub, 0, 1, 0, 0, 0, 0xffffc000, 0, 0, data_020c80f8, 0);
        }
    }

    if (func_02019e00(self + 0x564) == 0 && func_02019e00(sub) == 0) {
        buf[0] = data_ov048_0226398c[0];
        buf[1] = data_ov048_0226398c[1];
        buf[2] = data_ov048_0226398c[2];
        func_02095ab0(buf, 0x666, 4);

        func_02019c20(self + 0x564, 1, 0x81, 1, data_020c80f8, 0);

        self[0xe70] = (char) (func_020644cc(5) + 5);
        *(u16 *) (self + 0xe6e) = 0x16;
        func_ov004_02246f7c();

        return 1;
    }
    return 0;
}
