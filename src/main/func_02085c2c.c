/* func_02085c2c @ 0x02085c2c, 0x100 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02085c2c {
    u16 a;
    u16 b;
} UnkStruct_02085c2c;

extern int func_0209fa30(void *x);
extern char data_021f3b85[];
extern int func_02084840(int x);
extern int func_020846cc(int x);
extern UnkStruct_02085c2c *func_020844c4(int x);
extern UnkStruct_02085c2c *func_02084388(int x);
extern int func_02085d2c(int a, int b);
extern UnkStruct_02085c2c *func_020842b8(int x);
extern UnkStruct_02085c2c *func_02084188(int x);
extern UnkStruct_02085c2c *func_02083fa4(void *a, void *b, int c, int d);
extern UnkStruct_02085c2c *func_02084058(int x);
extern u8 data_020d0684[];
extern u8 data_020d0654[];
extern int data_020d0648;

void func_02085c2c(u16 *p)
{
    int flag;
    int t;
    UnkStruct_02085c2c *q;

    flag = func_0209fa30(data_021f3b85);
    t = func_02084840(0);
    if (t == 0) {
        t = func_020846cc(0);
    }
    if (t) {
        *p = 0xfff1;
    } else if ((q = func_020844c4(0)) != 0) {
        *p = q->b;
    } else if ((q = func_02084388(0)) != 0) {
        *p = q->b;
    } else if (flag == 0 && func_02085d2c(0x3d, 0)) {
        *p = 0xd00e;
    } else if ((q = func_020842b8(0)) != 0) {
        *p = q->b;
    } else if ((q = func_02084188(0)) != 0) {
        *p = q->b;
    } else if ((q = func_02083fa4(data_020d0684, data_020d0654, data_020d0648, 0)) != 0) {
        *p = q->b;
    } else if (flag == 0 && func_02085d2c(0x3f, 0)) {
        *p = 0xd00a;
    } else if (flag == 0 && func_02085d2c(0x40, 0)) {
        *p = 0xd00b;
    } else if ((q = func_02084058(0)) != 0) {
        *p = q->b;
    } else {
        *p = 0xfff1;
    }
}
