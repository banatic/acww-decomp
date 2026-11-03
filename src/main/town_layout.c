/* town_layout: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204e7dc @ 0x0204e7dc, 0x78 bytes, Thumb
 * func_0204e77c @ 0x0204e77c, 0x60 bytes, Thumb
 * func_0204e728 @ 0x0204e728, 0x54 bytes, Thumb
 * func_0204e724 @ 0x0204e724, 0x2 bytes, Thumb
 * func_0204e6f8 @ 0x0204e6f8, 0x2c bytes, Thumb
 * func_0204e6d8 @ 0x0204e6d8, 0x20 bytes, Thumb
 * func_0204e6bc @ 0x0204e6bc, 0x1c bytes, Thumb
 * func_0204e6b8 @ 0x0204e6b8, 0x2 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Point;

// Both loop counters live in one struct whose address is taken.
typedef struct UnkStruct_0204e77c {
    int i;
    int j;
} UnkStruct_0204e77c;

extern unsigned short *func_0204ea00(void *p0, Point *pt);
extern int func_0204d7f8(int r, int z, int v, int b);
extern void func_0204ea40(unsigned char *);
extern int func_020644cc(int arg);
extern void func_0209c574(void *arg);
extern int func_0204e854(void *arg);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_020051b0(void *);
extern void func_02034ce0(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

int func_0204e7dc(void *p0)
{
    Point pt;
    int count;
    int result;
    int startx;
    int startk;
    int flag0;
    unsigned short *p;
    int k;
    int flag;

    count = 0;
    pt.x = 0;
    pt.y = 0;
    result = 0;
    startx = 0;
    startk = 0;
    flag0 = 0;
    for (pt.y = 0; pt.y < 6; pt.y++) {
        for (pt.x = startx; pt.x < 6; pt.x++) {
            p = func_0204ea00(p0, &pt);
            if (p != 0) {
                for (k = startk; k < 0x100; k++) {
                    flag = flag0;
                    if (*p >= 0xe3 && *p <= 0xe7) {
                        flag = 1;
                    }
                    if (flag != 0) {
                        count++;
                    }
                    p++;
                }
            }
        }
    }
    if (count >= 5) {
        result = 1;
    }
    return result;
}

void func_0204e77c(u8 *a, int b)
{
    UnkStruct_0204e77c s;
    int r;

    s.i = 0;
    s.j = 0;
    for (s.j = 0; s.j < 6; s.j++) {
        for (s.i = 0; s.i < 6; s.i++) {
            r = (int) func_0204ea00((void *) a, (Point *) (&s.i));
            if (r != 0) {
                func_0204d7f8(r, 0, (a + s.j * 6)[s.i] & 0xfff, b);
            }
        }
    }
}

void func_0204e728(void *arg0, void *arg1)
{
    int tmp;
    unsigned char *field;

    func_0204ea40(arg0);
    tmp = func_020644cc(3);

    field = (unsigned char *) arg0 + 0x2224;
    *field = (*field & ~3) | ((unsigned char) tmp & 3);

    while (1) {
        func_0209c574(arg0);
        func_0204e77c((u8 *) arg0, (int) arg1);
        if (func_0204e854(arg0) && func_0204e7dc(arg0)) {
            break;
        }
    }
}

void *func_0204e724(void *object)
{
    return object;
}

int func_0204e6f8(int param)
{
    __cxa_vec_ctor((void *) (param), 0x100, 2, (void (*)(void *)) func_02034ce0, (void (*)(void *)) func_020051b0);
    return param;
}

void *func_0204e6d8(void *p)
{
    __cxa_vec_cleanup((void *) (p), 0x100, 2, (void (*)(void *)) func_020051b0);
    return p;
}

void func_0204e6bc(unsigned short *p)
{
    int i;
    for (i = 0; i < 256; i++) {
        *p++ = 0xfff1;
    }
}

void *func_0204e6b8(void *object)
{
    return object;
}
