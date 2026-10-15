/* func_ov003_0222a3ec @ 0x0222a3ec, 0x158 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern char data_ov003_0225f4dc[];
extern int data_020ccf94;
extern int func_020912d4(int id, Vec3 *v, int a, int b);
extern void func_020779b8(u8 *p, int a, int b);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned n);
extern void func_02073820(int g);
extern void func_020737f0(int g, u8 *p, int n);
extern void func_02073770(int g, int a, int b);

int func_ov003_0222a3ec(char *self, int flag)
{
    u8 buf[12];
    Vec3 v;
    char *rec;
    Vec3 *q;
    Vec3 *r;
    int k;
    int d;
    int g;
    int kind;
    *(u8 *) (self + 0x1fd) = 1;
    k = *(s8 *) (self + 0x227);
    if (k == -1) {
        return 0;
    }
    rec = &data_ov003_0225f4dc[k * 0xa4];
    *(int *) (rec + 0x40) = 1;
    *(int *) (rec + 0x48) = 1;
    q = (Vec3 *) (self + 0x120);
    r = (Vec3 *) (rec + 0x60);
    r->x = q->x;
    r->y = q->y;
    r->z = q->z;
    *(u8 *) (rec + 0x78) = flag;
    d = *(s8 *) (self + 0x7e);
    *(int *) (rec + 0x90) = d;
    kind = *(u8 *) (self + 0x1ff);
    v.x = q->x;
    v.y = q->y;
    v.z = q->z;
    switch (kind) {
        case 0:
            func_020912d4(0x12, &v, 0, 0);
            break;
        case 1:
            func_020912d4(0x13, &v, 0, 0);
            break;
        case 2:
            func_020912d4(0x14, &v, 0, 0);
            break;
        case 3:
            func_020912d4(0x15, &v, 0, 0);
            break;
        case 4:
            func_020912d4(0x16, &v, 0, 0);
            break;
        case 5:
            func_020912d4(0x17, &v, 0, 0);
            break;
        case 6:
            func_020912d4(0x19, &v, 0, 0);
            break;
        case 7:
            func_020912d4(0x18, &v, 0, 0);
            break;
    }
    buf[0] = 0;
    buf[1] = d;
    func_020779b8(&buf[7], *(int *) (self + 0x120), *(int *) (self + 0x128));
    MI_CpuCopy8(&buf[7], &buf[2], 5);
    g = data_020ccf94;
    func_02073820(g);
    func_020737f0(g, buf, 7);
    func_02073770(g, 0x2a, 4);
    return 1;
}
