/* collision_segment: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202f464 @ 0x0202f464, 0xbc bytes, Thumb
 * func_0202f3e4 @ 0x0202f3e4, 0x80 bytes, Thumb
 * func_0202f3e0 @ 0x0202f3e0, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    fx32 x, y;
} Vec2;

typedef struct {
    int unk_00;
    Vec2 a; // offset 0x4
    Vec2 b; // offset 0xc
    Vec2 c; // offset 0x14
} UnkStruct_0202f464;

extern void func_0202f898(Vec2 *out, Vec2 *a, Vec2 *b);
extern int func_0202f7f4(Vec2 *v);
extern void func_0202f8fc(Vec2 *out, fx32 negx, fx32 negy);
extern void func_0202f8c8(Vec2 *out, Vec2 *a, Vec2 *c);
extern void *func_0202f6f4(u32 *out, Vec2 *a, Vec2 *b, Vec2 *c);
extern int func_0202f660(u32 *mat, int arg);
extern void func_0202f6e8(u32 *mat);
extern int *func_0202f874(int *p, int arg);
extern void func_0202f8b4(void *a, void *b);

int func_0202f464(UnkStruct_0202f464 *p, int arg)
{
    Vec2 v1;
    Vec2 v2;
    Vec2 v3;
    Vec2 v4;
    u32 m1[8];
    u32 m2[9];
    int sa, sb;

    func_0202f898(&v1, &p->a, &p->b);
    if (func_0202f7f4(&v1) != 0) {
        func_0202f8fc(&v2, -v1.x, -v1.y);
        func_0202f8c8(&v3, &p->a, &p->c);
        func_0202f6f4(m1, &p->a, &v3, &v1);
        func_0202f8c8(&v4, &p->b, &p->c);
        func_0202f6f4(m2, &p->b, &v4, &v2);

        sa = func_0202f660(m1, arg);
        sb = func_0202f660(m2, arg);

        if (sa >= 0 && sb >= 0) {
            func_0202f6e8(m2);
            func_0202f6e8(m1);
            return 1;
        } else if (sa <= 0 && sb <= 0) {
            func_0202f6e8(m2);
            func_0202f6e8(m1);
            return 1;
        } else {
            func_0202f6e8(m2);
            func_0202f6e8(m1);
            return 0;
        }
    }
    return 0;
}

int func_0202f3e4(void *a0, void *a1, void *a2, int a3)
{
    int v1, v2, absv1;
    int pair[2];

    v1 = func_0202f660((u32 *) a0, (int) a1);
    v2 = func_0202f660((u32 *) a0, (int) a2);
    if (v2 >= 0) {
        absv1 = v1 < 0 ? -v1 : v1;
        if (absv1 <= a3) {
            if (func_0202f464((UnkStruct_0202f464 *) a0, (int) a2) != 0 || func_0202f464((UnkStruct_0202f464 *) a0, (int) a1) != 0) {
                char *p = (char *) a0 + 0x14;
                pair[0] = *(int *) p;
                pair[1] = *(int *) (p + 4);
                func_0202f874(pair, a3 - v1);
                func_0202f8b4(a1, pair);
                return 1;
            }
        } else {
            if (v1 < a3 + 0x200) {
                return 1;
            }
        }
    }
    return 0;
}

int func_0202f3e0(void)
{
    return 1;
}
