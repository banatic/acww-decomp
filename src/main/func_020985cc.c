/* func_020985cc @ 0x020985cc, 0x150 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int data_021d56f0;
extern u16 data_021d56f4[4];
extern void func_020051b0(void);
extern void __register_global_object(u16 *slot, void (*fn)(void), void *arg);
extern void *data_021d572c, *data_021d5720, *data_021d5714, *data_021d5708;

extern void MI_CpuFill8(void *dst, u8 val, unsigned int n);
extern int func_020988d8(int idx);
extern void *func_02099870(void *p);
extern int func_020951bc(void *p);
extern u16 func_020950d0(void *p);
extern void func_02099a38(void *p);
extern int func_020950f8(u16 *p, int n);
extern void func_0209987c(void *self, int a1, int a2, int a3, int s1, int s2, int s3, int s4, int s5, int s6, int s7,
                          u16 *buf);
extern void func_020996bc(void *self, u16 *slot);

void *func_020985cc(char *base, int a1, int a2, int idx)
{
    struct {
        u16 head;
        u16 rest[3];
    } buf;
    void *self;
    void *q;
    int i;
    int n;

    self = 0;
    if (func_020988d8(idx) == 1) {
        if ((data_021d56f0 & 1) == 0) {
            data_021d56f4[0] = 0x3884;
            __register_global_object(&data_021d56f4[0], func_020051b0, &data_021d572c);
            data_021d56f4[1] = 0x3888;
            __register_global_object(&data_021d56f4[1], func_020051b0, &data_021d5720);
            data_021d56f4[2] = 0x388c;
            __register_global_object(&data_021d56f4[2], func_020051b0, &data_021d5714);
            data_021d56f4[3] = 0x3890;
            __register_global_object(&data_021d56f4[3], func_020051b0, &data_021d5708);
            data_021d56f0 |= 1;
        }
        self = base + idx * 0x249c;
        n = 0;
        MI_CpuFill8(buf.rest, 0, 6);
        for (i = 0; i < 4; i++) {
            if (i == idx) {
                continue;
            }
            q = base + i * 0x249c;
            if (func_020951bc(func_02099870(q)) == 1) {
                *(u16 *) ((char *) buf.rest + n * 2) = func_020950d0(func_02099870(q));
                n = (u16) (n + 1);
            }
        }
        func_02099a38(self);
        buf.head = 0xfff1;
        func_0209987c(self, a1, func_020950f8(buf.rest, n), a2, 0, 0, 0, 0, 0, 0, 0, (u16 *) &buf);
        func_020996bc(self, &data_021d56f4[idx & 3]);
    }
    return self;
}
