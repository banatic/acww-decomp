/* talk_item_draw: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202d694 @ 0x0202d694, 0x50 bytes, Thumb
 * func_0202d5fc @ 0x0202d5fc, 0x98 bytes, Thumb
 * func_0202d5e4 @ 0x0202d5e4, 0x18 bytes, Thumb
 * func_0202d5cc @ 0x0202d5cc, 0x18 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u32 a;
    u32 b;
} UnkStruct_0202d694;

typedef struct {
    u32 a;
    u32 b;
} Elem;

extern int func_020644cc(int);
extern void func_02063ccc(void *, u32, int);
extern void func_020638d4(void *, UnkStruct_0202d694 *, int, int, int, int, int);
extern void func_02063cc8(void *);
extern u32 data_020c8eb4[];
extern void func_02063884(u16 *out, u32 *buf);
extern int data_020c8f4c;
extern unsigned char data_020c8f98[];

void func_0202d694(void *p)
{
    int idx;
    UnkStruct_0202d694 s;
    UnkStruct_0202d694 c;

    idx = func_020644cc(4);
    func_02063ccc(&s, data_020c8eb4[idx], 0);
    c.a = s.a;
    c.b = s.b;
    func_020638d4(p, &c, 0, 0, 1, 1, 0);
    func_02063cc8(&c);
    func_02063cc8(&s);
}

void func_0202d5fc(u16 *out, Elem *arr, u32 param, u32 param4)
{
    u16 status[2];
    u32 val;
    u32 buf14[2];
    u32 buf1c[2];
    u32 buf24[2];
    u32 buf2c[2];
    u32 idx;

    idx = (u32) func_020644cc(param);
    *out = 0xfff1;
    arr += idx;
    val = arr->b;
    func_02063ccc((void *) buf14, arr->a, arr->b);
    buf24[0] = buf14[0];
    buf24[1] = buf14[1];
    func_020638d4((void *) status, (UnkStruct_0202d694 *) buf24, param4, 0, 1, 1, (int) (&val));
    *out = status[0];
    func_02063cc8(buf24);
    if (*out == 0xfff1) {
        func_02063ccc((void *) buf1c, arr->a, val);
        buf2c[0] = buf1c[0];
        buf2c[1] = buf1c[1];
        func_02063884(&status[1], buf2c);
        *out = status[1];
        func_02063cc8(buf2c);
        func_02063cc8(buf1c);
    }
    func_02063cc8(buf14);
}

void func_0202d5e4(int a, int b)
{
    func_0202d5fc((u16 *) a, (Elem *) (&data_020c8f4c), 3, b);
}

void func_0202d5cc(int arg0, int arg1)
{
    func_0202d5fc((u16 *) arg0, (Elem *) data_020c8f98, 4, arg1);
}
