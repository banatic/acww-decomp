/* room_objects_5: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223c660 @ 0x0223c660, 0xa0 bytes, Thumb
 * func_ov004_0223c62c @ 0x0223c62c, 0x34 bytes, Thumb
 * func_ov004_0223c5b8 @ 0x0223c5b8, 0x74 bytes, Thumb
 * func_ov004_0223c5a4 @ 0x0223c5a4, 0x14 bytes, Thumb
 */

#include "types.h"

extern void *func_ov004_0223ce84(void);
extern int func_ov004_0223cda4(void *);
extern int func_ov004_02211388(void *);
extern int func_02053de4(int);
extern int func_ov004_0221137c(void *);
extern unsigned int func_ov004_0223c264(int (*)(void *));
extern char *func_ov004_0223c1ec(int (*)(void *), int);
extern void func_ov004_0220d280(void *, int, int);
extern int func_020b65c4(void);
extern void func_02051f4c(int, void *, int);
extern int func_02003348(int, void *, int, int, void *);
extern int func_ov004_02211280(void *);
extern u16 data_ov004_02247f54[];
extern void *data_ov004_022595c0;
extern int func_ov004_02211394(void *, int, void *, int, int, int);
extern void *func_ov004_0223cd50(void);
extern void *func_ov004_0223cc10(void *base, int x, int y, int layer);
extern int func_02034270(void *buf, void *vec, int a, int b);
extern int func_020341c8(void *buf, int flag);
extern void func_0203423c(void *buf);

int func_ov004_0223c660(void *self)
{
    int k, m;
    u16 kind;
    if (func_ov004_0223cda4(func_ov004_0223ce84()) != 0) {
        k = func_02053de4(func_ov004_02211388(self));
        m = func_ov004_0221137c(self);
        if (k >= 0 && k < 0x30) {
            kind = data_ov004_02247f54[k];
        } else {
            kind = data_ov004_02247f54[0];
        }
        if (k == 0x18 && m == 1) {
            if (func_ov004_0223c264(func_ov004_02211280) >= 4) {
                char *o = func_ov004_0223c1ec(func_ov004_02211280, 0);
                if (o != 0) {
                    func_ov004_0220d280(o + 0x740, 1, 0);
                    func_02051f4c(func_020b65c4(), o + 0x5c, 0);
                }
            }
        }
        return func_02003348(kind, self, 0, 0, data_ov004_022595c0);
    }
    return 0;
}

void func_ov004_0223c62c(void *a0, int a1, void *a2, int a3, unsigned char a4, int a5)
{
    func_02053de4((int) a2);
    func_ov004_0223c660((void *) func_ov004_02211394(a0, a1, a2, a3, a4, a5));
}

int func_ov004_0223c5b8(int x, int y)
{
    int v[3];
    char buf[0x40];
    char *o;
    int r;
    o = (char *) func_ov004_0223cc10(func_ov004_0223cd50(), x, y, 0);
    if (o != 0) {
        if (*(u8 *) (o + 0x78c) == 1) {
            return *(int *) (o + 0x60);
        }
        return *(int *) (o + 0x790) + *(int *) (o + 0x60);
    }
    v[0] = (x << 13) + 0x1000;
    v[1] = 0;
    v[2] = (y << 13) + 0x1000;
    func_02034270(buf, v, 0, 0);
    r = func_020341c8(buf, 0);
    func_0203423c(buf);
    return r;
}

int func_ov004_0223c5a4(int *param)
{
    int a;
    int b;
    int *ptr;

    ptr = param;
    a = *ptr >> 13;
    b = *(ptr + 2) >> 13;
    return func_ov004_0223c5b8(a, b);
}
