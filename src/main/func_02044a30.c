/* func_02044a30 @ 0x02044a30, 0x158 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Vec {
    int x;
    int y;
    int z;
} Vec;

extern int data_021c77a0;
extern int data_020db76c;
extern int data_020db768;

extern int func_02049ec4(void *p0);
extern void func_0204f794(Vec *v, int a, int b);
extern int func_02049d78(void *p0);
extern void func_02044df8(void *g, int p3, int kind, int k, int flag, Vec *v, void *p2);
extern int func_02090c2c(int id, Vec *v, int z, void *t);

void func_02044a30(u16 *p0, int *p1, void *p2, int p3)
{
    Vec v1;
    Vec v2;
    int k;
    unsigned int q3;
    unsigned int q2;
    unsigned int q1;
    int b;
    unsigned int q0;
    int kind;
    u16 t;
    int a;
    int flag;

    kind = (u8) func_02049ec4(p0);
    switch (kind) {
        case 0:
            a = 0x44;
            b = 0x6a;
            break;
        case 1:
            a = 0x42;
            b = 0x68;
            break;
        case 2:
            a = 0x3e;
            b = 0x64;
            break;
        case 3:
            if (*p0 == 0x1c || *p0 == 0xa5) {
                a = 0x40;
                b = 0x66;
            } else {
                a = 0x43;
                b = 0x69;
            }
            break;
        case 4:
            a = 0x41;
            b = 0x67;
            break;
        case 5:
            a = 0x3f;
            b = 0x65;
            break;
        case 6:
            a = 0x63;
            b = 0x65;
            break;
    }

    func_0204f794(&v1, p1[0], p1[1]);
    flag = 0;
    q1 = q2 = q3 = 1;
    q0 = 0;
    t = *p0;
    if (t >= 0x6e && t <= 0x73) {
        q0 = 1;
    }
    if (!q0) {
        if (!(t >= 0x74 && t <= 0x79)) {
            q1 = 0;
        }
    }
    if (!q1) {
        if (!(t >= 0x7a && t <= 0x7f)) {
            q2 = 0;
        }
    }
    if (!q2) {
        if (!(t >= 0x80 && t <= 0x87)) {
            q3 = 0;
        }
    }
    if (q3 || t == 0x88 || t == 0x89 || (t >= 0x8a && t <= 0x8f) || (t >= 0x90 && t <= 0x95) || (t >= 0x96 && t <= 0x9b) ||
        (t >= 0x9c && t <= 0xa3) || (int) t == 0xa5 || t == 0xa4) {
        flag = 1;
        k = 0;
    } else {
        k = (u8) func_02049d78(p0);
    }

    v2.x = v1.x;
    v2.y = v1.y;
    v2.z = v1.z;
    func_02044df8(&data_021c77a0, p3, kind, k, flag, &v2, p2);
    func_02090c2c(a, &v1, 0, &data_020db76c);
    if (p3 != 1) {
        func_02090c2c(b, &v1, 0, &data_020db768);
    }
}
