/* func_ov004_0221c0f0 @ 0x0221c0f0, 0x134 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a, b, c;
} UnkStruct_0221c0f0;

extern void *func_02095794(int);
extern int func_0201c378(void *self, int a);
extern int func_02019e00(void *p);
extern void func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, u16 i, int j);
extern void func_0201b044(void *a, void *b);
extern int func_0200322c(void *a, void *b);
extern int func_020e8b4c(int a, int b);
extern void func_020147fc(void *a, int b, int c, int d);
extern void func_ov004_0221c844(void *self, int a);

extern u16 data_020c80f8;

void func_ov004_0221c0f0(char *self)
{
    UnkStruct_0221c0f0 t1c;
    UnkStruct_0221c0f0 t28;
    int cnt;
    int dist;
    int ang;

    {
        void *src;
        int a, b, c;
        src = func_02095794(4);
        a = *(int *) src;
        t1c.a = a;
        b = *((int *) src + 1);
        t1c.b = b;
        c = *((int *) src + 2);
        t1c.c = c;
        t28.a = a;
        t28.b = b;
        t28.c = c;
    }

    cnt = func_0201c378(self, 4);

    if (cnt > 0x4000) {
        if (func_02019e00(self + 0x564) == 1) {
            func_02019d0c(self + 0x564, 2, 1, 0, 0, 0x800, 0, 0, 0, data_020c80f8, 0);
        }
    } else {
        if (func_02019e00(self + 0x564) == 2) {
            func_02019d0c(self + 0x564, 1, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
    }

    func_0201b044(self + 0x350, &t28);

    if (*(unsigned char *) (self + 0xa52) != 0) {
        *(unsigned char *) (self + 0xa52) = *(unsigned char *) (self + 0xa52) - 1;
    }

    dist = func_0200322c(self + 0x5c, &t1c);
    ang = *(short *) (self + 0x8e);
    ang = func_020e8b4c(ang, dist);

    if (cnt <= 0x3000 || *(unsigned char *) (self + 0xa52) == 0) {
        func_020147fc(self + 0x618, 0, dist, 0);
        func_ov004_0221c844(self, 9);
    } else if (ang > 0x2000) {
        func_02019d0c(self + 0x564, 4, 2, t28.a, t28.c, 0, dist, 0, 0, data_020c80f8, 0);
    }
}
