/* func_0202f464 @ 0x0202f464, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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
extern void func_0202f6f4(u32 *out, Vec2 *a, Vec2 *b, Vec2 *c);
extern int func_0202f660(u32 *mat, int arg);
extern void func_0202f6e8(u32 *mat);

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
