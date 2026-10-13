/* func_ov003_0222780c @ 0x0222780c, 0xd4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern char data_ov003_0225f4dc[];
extern char *func_020961a8(int idx);
extern int func_0200322c(Vec3 *a, Vec3 *b);
extern void func_ov003_0222a7bc(char *rec, int v, int kind);

int func_ov003_0222780c(int idx, int id, Vec3 *pos)
{
    volatile u16 t;
    Vec3 v;
    int ok;
    u16 lo;
    u16 hi;
    char *rec;
    char *p;
    int d;
    Vec3 *q;
    t = id;
    ok = 0;
    lo = t;
    hi = t;
    if (hi >= 0x12e8 && lo <= 0x131f) {
        ok = 1;
    }
    if (!ok) {
        return 0;
    }
    if (idx < 0 || idx >= 4) {
        return 0;
    }
    rec = &data_ov003_0225f4dc[idx * 0xa4];
    if (*(int *) (rec + 0x40) != 0) {
        return 0;
    }
    p = func_020961a8(idx);
    if (p == 0) {
        return 0;
    }
    q = (Vec3 *) (p + 0x5c);
    v.x = q->x;
    v.y = q->y;
    v.z = q->z;
    d = t - 0x12e8;
    *(int *) (rec + 0x90) = d;
    func_ov003_0222a7bc(rec, func_0200322c(&v, pos), d);
    q = (Vec3 *) (rec + 0x60);
    q->x = v.x;
    q->y = v.y;
    q->z = v.z;
    q = (Vec3 *) (rec + 0x6c);
    q->x = pos->x;
    q->y = pos->y;
    q->z = pos->z;
    q = (Vec3 *) (rec + 0x54);
    q->x = v.x;
    q->y = v.y;
    q->z = v.z;
    *(int *) (rec + 0x7c) = 0;
    *(int *) (rec + 0x48) = 4;
    *(int *) (rec + 0x40) = 1;
    return 1;
}
